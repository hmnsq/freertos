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

/*
 * Implementation of the wrapper functions used to raise the processor privilege
 * before calling a standard FreeRTOS API function.
 */

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#تعریف_کرو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"
#شامل "queue.h"
#شامل "timers.h"
#شامل "event_groups.h"
#شامل "stream_buffer.h"
#شامل "mpu_prototypes.h"

#تعریف_منسوخ MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#اگر ( ( پورٹ_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #اگر ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #غلطی Access control list is not دستیاب with this MPU wrapper. Please سیٹ configENABLE_ACCESS_CONTROL_LIST مقصد 0.
    #اگر_ختم

    #اگر ( config_SUPPORT_DYNAMIC_تخصیص == 1 )
        بنیاد_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_رمز,
                                    ثابت حرف * ثابت pcName,
                                    ثابت config_ڈھیر_گہرائی_TYPE ux_ڈھیر_گہرائی,
                                    خالی * pvParameters,
                                    UBaseType_t ux_ترجیح,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                ux_ترجیح = ux_ترجیح & ~( پورٹ_PRIVILEGE_ثنائی_ہندسہ );
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskCreate( pv_Task_رمز, pcName, ux_ڈھیر_گہرائی, pvParameters, ux_ترجیح, pxCreatedTask );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTaskCreate( pv_Task_رمز, pcName, ux_ڈھیر_گہرائی, pvParameters, ux_ترجیح, pxCreatedTask );
            }

            واپس xReturn;
        }
    #اگر_ختم /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #اگر ( config_SUPPORT_STATIC_تخصیص == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_رمز,
                                            ثابت حرف * ثابت pcName,
                                            ثابت config_ڈھیر_گہرائی_TYPE ux_ڈھیر_گہرائی,
                                            خالی * ثابت pvParameters,
                                            UBaseType_t ux_ترجیح,
                                            ڈھیر_Type_t * ثابت pux_ڈھیر_بفر,
                                            StaticTask_t * ثابت px_Task_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                ux_ترجیح = ux_ترجیح & ~( پورٹ_PRIVILEGE_ثنائی_ہندسہ );
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskCreateStatic( px_Task_رمز, pcName, ux_ڈھیر_گہرائی, pvParameters, ux_ترجیح, pux_ڈھیر_بفر, px_Task_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTaskCreateStatic( px_Task_رمز, pcName, ux_ڈھیر_گہرائی, pvParameters, ux_ترجیح, pux_ڈھیر_بفر, px_Task_بفر );
            }

            واپس xReturn;
        }
    #اگر_ختم /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_vTaskDelete == 1 )
        خالی MPU_vTaskDelete( TaskHandle_t px_Task_مقصد_Delete ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                vTaskDelete( px_Task_مقصد_Delete );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                vTaskDelete( px_Task_مقصد_Delete );
            }
        }
    #اگر_ختم /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskDelayUntil == 1 )
        بنیاد_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پچھلا_Wake_وقت,
                                        TickType_t x_وقت_Increment ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskDelayUntil( px_پچھلا_Wake_وقت, x_وقت_Increment );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTaskDelayUntil( px_پچھلا_Wake_وقت, x_وقت_Increment );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskAbortDelay == 1 )
        بنیاد_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskAbortDelay( xTask );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTaskAbortDelay( xTask );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_vTaskDelay == 1 )
        خالی MPU_vTaskDelay( TickType_t x_Ticks_مقصد_Delay ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                vTaskDelay( x_Ticks_مقصد_Delay );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                vTaskDelay( x_Ticks_مقصد_Delay );
            }
        }
    #اگر_ختم /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_ux_Task_ترجیح_Get == 1 )
        UBaseType_t MPU_ux_Task_ترجیح_Get( ثابت TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                uxReturn = ux_Task_ترجیح_Get( pxTask );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                uxReturn = ux_Task_ترجیح_Get( pxTask );
            }

            واپس uxReturn;
        }
    #اگر_ختم /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_v_Task_ترجیح_سیٹ == 1 )
        خالی MPU_v_Task_ترجیح_سیٹ( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_ترجیح ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_Task_ترجیح_سیٹ( pxTask, ux_New_ترجیح );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                v_Task_ترجیح_سیٹ( pxTask, ux_New_ترجیح );
            }
        }
    #اگر_ختم /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                eReturn = eTaskGetState( pxTask );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                eReturn = eTaskGetState( pxTask );
            }

            واپس eReturn;
        }
    #اگر_ختم /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TRACE_FACILITY == 1 )
        خالی MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_حالت_t * px_Task_حالت,
                               بنیاد_Type_t x_Get_Free_ڈھیر_Space,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                vTaskGetInfo( xTask, px_Task_حالت, x_Get_Free_ڈھیر_Space, eState );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                vTaskGetInfo( xTask, px_Task_حالت, x_Get_Free_ڈھیر_Space, eState );
            }
        }
    #اگر_ختم /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( خالی ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
                xReturn = xTaskGetIdleTaskHandle();
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTaskGetIdleTaskHandle();
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_vTaskSuspend == 1 )
        خالی MPU_vTaskSuspend( TaskHandle_t px_Task_مقصد_Suspend ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                vTaskSuspend( px_Task_مقصد_Suspend );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                vTaskSuspend( px_Task_مقصد_Suspend );
            }
        }
    #اگر_ختم /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_vTaskSuspend == 1 )
        خالی MPU_vTaskResume( TaskHandle_t px_Task_مقصد_Resume ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                vTaskResume( px_Task_مقصد_Resume );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                vTaskResume( px_Task_مقصد_Resume );
            }
        }
    #اگر_ختم /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    خالی MPU_vTaskSuspendAll( خالی ) /* FREERTOS_SYSTEM_CALL */
    {
        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            vTaskSuspendAll();
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            vTaskSuspendAll();
        }
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_xTaskResumeAll( خالی ) /* FREERTOS_SYSTEM_CALL */
    {
        بنیاد_Type_t xReturn;

        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = xTaskResumeAll();
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            xReturn = xTaskResumeAll();
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_گنتی( خالی ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_Task_Get_Tick_گنتی();
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            xReturn = x_Task_Get_Tick_گنتی();
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_نمبر_کا_Tasks( خالی ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            uxReturn = ux_Task_Get_نمبر_کا_Tasks();
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            uxReturn = ux_Task_Get_نمبر_کا_Tasks();
        }

        واپس uxReturn;
    }
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( ثابت حرف * pc_Name_مقصد_Query ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskGetHandle( pc_Name_مقصد_Query );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTaskGetHandle( pc_Name_مقصد_Query );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )
        خالی MPU_vTaskListTasks( حرف * pc_Write_بفر,
                                 size_t ux_بفر_لمبائی ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                vTaskListTasks( pc_Write_بفر, ux_بفر_لمبائی );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                vTaskListTasks( pc_Write_بفر, ux_بفر_لمبائی );
            }
        }
    #اگر_ختم /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_GENERATE_تسلسل_وقت_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )
        خالی MPU_v_Task_Get_تسلسل_وقت_Statistics( حرف * pc_Write_بفر,
                                            size_t ux_بفر_لمبائی ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_Task_Get_تسلسل_وقت_Statistics( pc_Write_بفر, ux_بفر_لمبائی );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                v_Task_Get_تسلسل_وقت_Statistics( pc_Write_بفر, ux_بفر_لمبائی );
            }
        }
    #اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_GENERATE_تسلسل_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent( خالی ) /* FREERTOS_SYSTEM_CALL */
        {
            config_تسلسل_وقت_شمار_TYPE xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = ul_Task_Get_Idle_تسلسل_وقت_Percent();
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = ul_Task_Get_Idle_تسلسل_وقت_Percent();
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_GENERATE_تسلسل_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار( خالی ) /* FREERTOS_SYSTEM_CALL */
        {
            config_تسلسل_وقت_شمار_TYPE xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = ul_Task_Get_Idle_تسلسل_وقت_شمار();
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = ul_Task_Get_Idle_تسلسل_وقت_شمار();
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_APPLICATION_TASK_لیبل == 1 )
        خالی MPU_v_Task_سیٹ_Application_Task_لیبل( TaskHandle_t xTask,
                                             TaskHookFunction_t px_لیبل_قدر ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_Task_سیٹ_Application_Task_لیبل( xTask, px_لیبل_قدر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                v_Task_سیٹ_Application_Task_لیبل( xTask, px_لیبل_قدر );
            }
        }
    #اگر_ختم /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_APPLICATION_TASK_لیبل == 1 )
        TaskHookFunction_t MPU_x_Task_Get_Application_Task_لیبل( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Task_Get_Application_Task_لیبل( xTask );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_Task_Get_Application_Task_لیبل( xTask );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_عدد_THREAD_LOCAL_STORAGE_اشارے != 0 )
        خالی MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_مقصد_سیٹ,
                                                    بنیاد_Type_t x_اشاریہ,
                                                    خالی * pv_قدر ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( x_Task_مقصد_سیٹ, x_اشاریہ, pv_قدر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( x_Task_مقصد_سیٹ, x_اشاریہ, pv_قدر );
            }
        }
    #اگر_ختم /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_عدد_THREAD_LOCAL_STORAGE_اشارے != 0 )
        خالی * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_مقصد_Query,
                                                       بنیاد_Type_t x_اشاریہ ) /* FREERTOS_SYSTEM_CALL */
        {
            خالی * pvReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                pvReturn = pv_Task_Get_Thread_Local_Storage_اشارہ_گر( x_Task_مقصد_Query, x_اشاریہ );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_اشارہ_گر( x_Task_مقصد_Query, x_اشاریہ );
            }

            واپس pvReturn;
        }
    #اگر_ختم /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_APPLICATION_TASK_لیبل == 1 )
        بنیاد_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     خالی * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * px_Task_حالت_Array,
                                              UBaseType_t ux_Array_سائز,
                                              config_تسلسل_وقت_شمار_TYPE * pul_کل_تسلسل_وقت ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                uxReturn = uxTaskGetSystemState( px_Task_حالت_Array, ux_Array_سائز, pul_کل_تسلسل_وقت );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                uxReturn = uxTaskGetSystemState( px_Task_حالت_Array, ux_Array_سائز, pul_کل_تسلسل_وقت );
            }

            واپس uxReturn;
        }
    #اگر_ختم /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_Task_Catch_اوپر_Ticks( TickType_t x_Ticks_مقصد_Catch_اوپر ) /* FREERTOS_SYSTEM_CALL */
    {
        بنیاد_Type_t xReturn;

        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_Task_Catch_اوپر_Ticks( x_Ticks_مقصد_Catch_اوپر );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            xReturn = x_Task_Catch_اوپر_Ticks( x_Ticks_مقصد_Catch_اوپر );
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark == 1 )
        UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark( xTask );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark( xTask );
            }

            واپس uxReturn;
        }
    #اگر_ختم /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark2 == 1 )
        config_ڈھیر_گہرائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            config_ڈھیر_گہرائی_TYPE uxReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark2( xTask );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark2( xTask );
            }

            واپس uxReturn;
        }
    #اگر_ختم /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( خالی ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
                xReturn = xTaskGetCurrentTaskHandle();
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTaskGetCurrentTaskHandle();
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskGetSchedulerState == 1 )
        بنیاد_Type_t MPU_xTaskGetSchedulerState( خالی ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskGetSchedulerState();
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTaskGetSchedulerState();
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    خالی MPU_v_Task_سیٹ_وقت_برآمد_State( وقت_برآمد_t * ثابت px_وقت_برآمد ) /* FREERTOS_SYSTEM_CALL */
    {
        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            v_Task_سیٹ_وقت_برآمد_State( px_وقت_برآمد );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            v_Task_سیٹ_وقت_برآمد_State( px_وقت_برآمد );
        }
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_Task_Check_For_وقت_برآمد( وقت_برآمد_t * ثابت px_وقت_برآمد,
                                         TickType_t * ثابت px_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        بنیاد_Type_t xReturn;

        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_Task_Check_For_وقت_برآمد( px_وقت_برآمد, px_Ticks_مقصد_Wait );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            xReturn = x_Task_Check_For_وقت_برآمد( px_وقت_برآمد, px_Ticks_مقصد_Wait );
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )
        بنیاد_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_مقصد_Notify,
                                           UBaseType_t ux_اشاریہ_مقصد_Notify,
                                           uint32_t ul_قدر,
                                           eNotifyAction eAction,
                                           uint32_t * pul_پچھلا_Notification_قدر ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskGenericNotify( x_Task_مقصد_Notify, ux_اشاریہ_مقصد_Notify, ul_قدر, eAction, pul_پچھلا_Notification_قدر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTaskGenericNotify( x_Task_مقصد_Notify, ux_اشاریہ_مقصد_Notify, ul_قدر, eAction, pul_پچھلا_Notification_قدر );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )
        بنیاد_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_اشاریہ_مقصد_Wait_On,
                                               uint32_t ul_بٹ_مقصد_Clear_On_اندراج,
                                               uint32_t ul_بٹ_مقصد_Clear_On_Exit,
                                               uint32_t * pul_Notification_قدر,
                                               TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskGenericNotifyWait( ux_اشاریہ_مقصد_Wait_On, ul_بٹ_مقصد_Clear_On_اندراج, ul_بٹ_مقصد_Clear_On_Exit, pul_Notification_قدر, x_Ticks_مقصد_Wait );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTaskGenericNotifyWait( ux_اشاریہ_مقصد_Wait_On, ul_بٹ_مقصد_Clear_On_اندراج, ul_بٹ_مقصد_Clear_On_Exit, pul_Notification_قدر, x_Ticks_مقصد_Wait );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاریہ_مقصد_Wait_On,
                                              بنیاد_Type_t x_Clear_گنتی_On_Exit,
                                              TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( ux_اشاریہ_مقصد_Wait_On, x_Clear_گنتی_On_Exit, x_Ticks_مقصد_Wait );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                ulReturn = ulTaskGenericNotifyTake( ux_اشاریہ_مقصد_Wait_On, x_Clear_گنتی_On_Exit, x_Ticks_مقصد_Wait );
            }

            واپس ulReturn;
        }
    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )
        بنیاد_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_اشاریہ_مقصد_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, ux_اشاریہ_مقصد_Clear );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, ux_اشاریہ_مقصد_Clear );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_اشاریہ_مقصد_Clear,
                                                    uint32_t ul_بٹ_مقصد_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                ulReturn = ul_Task_Generic_Notify_قدر_Clear( xTask, ux_اشاریہ_مقصد_Clear, ul_بٹ_مقصد_Clear );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                ulReturn = ul_Task_Generic_Notify_قدر_Clear( xTask, ux_اشاریہ_مقصد_Clear, ul_بٹ_مقصد_Clear );
            }

            واپس ulReturn;
        }
    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_SUPPORT_DYNAMIC_تخصیص == 1 )
        قطار_Handle_t MPU_x_قطار_Generic_Create( UBaseType_t ux_قطار_لمبائی,
                                               UBaseType_t ux_شے_سائز,
                                               uint8_t uc_قطار_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Generic_Create( ux_قطار_لمبائی, ux_شے_سائز, uc_قطار_Type );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_قطار_Generic_Create( ux_قطار_لمبائی, ux_شے_سائز, uc_قطار_Type );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_SUPPORT_STATIC_تخصیص == 1 )
        قطار_Handle_t MPU_x_قطار_Generic_Create_Static( ثابت UBaseType_t ux_قطار_لمبائی,
                                                     ثابت UBaseType_t ux_شے_سائز,
                                                     uint8_t * puc_قطار_Storage,
                                                     Static_قطار_t * px_Static_قطار,
                                                     ثابت uint8_t uc_قطار_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Generic_Create_Static( ux_قطار_لمبائی, ux_شے_سائز, puc_قطار_Storage, px_Static_قطار, uc_قطار_Type );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_قطار_Generic_Create_Static( ux_قطار_لمبائی, ux_شے_سائز, puc_قطار_Storage, px_Static_قطار, uc_قطار_Type );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Generic_Reset( قطار_Handle_t px_قطار,
                                       بنیاد_Type_t x_New_قطار ) /* FREERTOS_SYSTEM_CALL */
    {
        بنیاد_Type_t xReturn;

        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_قطار_Generic_Reset( px_قطار, x_New_قطار );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            xReturn = x_قطار_Generic_Reset( px_قطار, x_New_قطار );
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                      ثابت خالی * ثابت pv_شے_مقصد_قطار,
                                      TickType_t x_Ticks_مقصد_Wait,
                                      بنیاد_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        بنیاد_Type_t xReturn;

        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_قطار_Generic_Send( x_قطار, pv_شے_مقصد_قطار, x_Ticks_مقصد_Wait, xCopyPosition );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            xReturn = x_قطار_Generic_Send( x_قطار, pv_شے_مقصد_قطار, x_Ticks_مقصد_Wait, xCopyPosition );
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Messages_انتظار( ثابت قطار_Handle_t px_قطار ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            uxReturn = ux_قطار_Messages_انتظار( px_قطار );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            uxReturn = ux_قطار_Messages_انتظار( px_قطار );
        }

        واپس uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Spaces_دستیاب( ثابت قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            uxReturn = ux_قطار_Spaces_دستیاب( x_قطار );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            uxReturn = ux_قطار_Spaces_دستیاب( x_قطار );
        }

        واپس uxReturn;
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Receive( قطار_Handle_t px_قطار,
                                  خالی * ثابت pv_بفر,
                                  TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        بنیاد_Type_t xReturn;

        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_قطار_Receive( px_قطار, pv_بفر, x_Ticks_مقصد_Wait );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            xReturn = x_قطار_Receive( px_قطار, pv_بفر, x_Ticks_مقصد_Wait );
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                               خالی * ثابت pv_بفر,
                               TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        بنیاد_Type_t xReturn;

        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_قطار_Peek( x_قطار, pv_بفر, x_Ticks_مقصد_Wait );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            xReturn = x_قطار_Peek( x_قطار, pv_بفر, x_Ticks_مقصد_Wait );
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                        TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        بنیاد_Type_t xReturn;

        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_قطار_Semaphore_Take( x_قطار, x_Ticks_مقصد_Wait );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            xReturn = x_قطار_Semaphore_Take( x_قطار, x_Ticks_مقصد_Wait );
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            خالی * xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Get_Mutex_Holder( xSemaphore );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_قطار_Get_Mutex_Holder( xSemaphore );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )
        قطار_Handle_t MPU_x_قطار_Create_Mutex( ثابت uint8_t uc_قطار_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Create_Mutex( uc_قطار_Type );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_قطار_Create_Mutex( uc_قطار_Type );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_تخصیص == 1 ) )
        قطار_Handle_t MPU_x_قطار_Create_Mutex_Static( ثابت uint8_t uc_قطار_Type,
                                                   Static_قطار_t * px_Static_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Create_Mutex_Static( uc_قطار_Type, px_Static_قطار );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_قطار_Create_Mutex_Static( uc_قطار_Type, px_Static_قطار );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )
        قطار_Handle_t MPU_x_قطار_Create_Counting_Semaphore( UBaseType_t ux_گنتی_قدر,
                                                         UBaseType_t ux_Initial_گنتی ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Create_Counting_Semaphore( ux_گنتی_قدر, ux_Initial_گنتی );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_قطار_Create_Counting_Semaphore( ux_گنتی_قدر, ux_Initial_گنتی );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_تخصیص == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Counting_Semaphore_Static( ثابت UBaseType_t ux_Max_گنتی,
                                                               ثابت UBaseType_t ux_Initial_گنتی,
                                                               Static_قطار_t * px_Static_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Create_Counting_Semaphore_Static( ux_Max_گنتی, ux_Initial_گنتی, px_Static_قطار );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_قطار_Create_Counting_Semaphore_Static( ux_Max_گنتی, ux_Initial_گنتی, px_Static_قطار );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_RECURSIVE_MUTEXES == 1 )
        بنیاد_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                                 TickType_t x_بلاک_وقت ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Take_Mutex_Recursive( xMutex, x_بلاک_وقت );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_قطار_Take_Mutex_Recursive( xMutex, x_بلاک_وقت );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_RECURSIVE_MUTEXES == 1 )
        بنیاد_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Give_Mutex_Recursive( xMutex );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_قطار_Give_Mutex_Recursive( xMutex );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_USE_قطار_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )
        قطار_سیٹ_Handle_t MPU_x_قطار_Create_سیٹ( UBaseType_t ux_Event_قطار_لمبائی ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_سیٹ_Handle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Create_سیٹ( ux_Event_قطار_لمبائی );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_قطار_Create_سیٹ( ux_Event_قطار_لمبائی );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_USE_قطار_SETS == 1 ) && ( config_SUPPORT_STATIC_تخصیص == 1 ) )
        قطار_سیٹ_Handle_t MPU_x_قطار_Create_سیٹ_Static( ثابت UBaseType_t ux_Event_قطار_لمبائی,
                                                    uint8_t * puc_قطار_Storage,
                                                    Static_قطار_t * px_Static_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_سیٹ_Handle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Create_سیٹ_Static( ux_Event_قطار_لمبائی, puc_قطار_Storage, px_Static_قطار );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_قطار_Create_سیٹ_Static( ux_Event_قطار_لمبائی, puc_قطار_Storage, px_Static_قطار );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_قطار_SETS == 1 )
        قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                        TickType_t x_بلاک_وقت_Ticks ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_سیٹ_Member_Handle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Select_From_سیٹ( x_قطار_سیٹ, x_بلاک_وقت_Ticks );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_قطار_Select_From_سیٹ( x_قطار_سیٹ, x_بلاک_وقت_Ticks );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_قطار_SETS == 1 )
        بنیاد_Type_t MPU_x_قطار_جوڑو_مقصد_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                       قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_جوڑو_مقصد_سیٹ( x_قطار_Or_Semaphore, x_قطار_سیٹ );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_قطار_جوڑو_مقصد_سیٹ( x_قطار_Or_Semaphore, x_قطار_سیٹ );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_قطار_SETS == 1 )
        بنیاد_Type_t MPU_x_قطار_Remove_From_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                            قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Remove_From_سیٹ( x_قطار_Or_Semaphore, x_قطار_سیٹ );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_قطار_Remove_From_سیٹ( x_قطار_Or_Semaphore, x_قطار_سیٹ );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر config_قطار_REGISTRY_سائز > 0
        خالی MPU_v_قطار_جوڑو_مقصد_Registry( قطار_Handle_t x_قطار,
                                      ثابت حرف * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_قطار_جوڑو_مقصد_Registry( x_قطار, pcName );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                v_قطار_جوڑو_مقصد_Registry( x_قطار, pcName );
            }
        }
    #اگر_ختم /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #اگر config_قطار_REGISTRY_سائز > 0
        خالی MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_قطار_Unregister_قطار( x_قطار );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                v_قطار_Unregister_قطار( x_قطار );
            }
        }
    #اگر_ختم /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #اگر config_قطار_REGISTRY_سائز > 0
        ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            ثابت حرف * pcReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                pcReturn = pc_قطار_Get_Name( x_قطار );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                pcReturn = pc_قطار_Get_Name( x_قطار );
            }

            واپس pcReturn;
        }
    #اگر_ختم /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    خالی MPU_v_قطار_Delete( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
    {
        اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            v_قطار_Delete( x_قطار );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        ورنہ
        {
            v_قطار_Delete( x_قطار );
        }
    }
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )
        خالی * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            خالی * pvReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                pvReturn = pvTimerGetTimerID( xTimer );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                pvReturn = pvTimerGetTimerID( xTimer );
            }

            واپس pvReturn;
        }
    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )
        خالی MPU_v_Timer_سیٹ_Timer_ID( TimerHandle_t xTimer,
                                   خالی * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_Timer_سیٹ_Timer_ID( xTimer, pvNewID );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                v_Timer_سیٹ_Timer_ID( xTimer, pvNewID );
            }
        }
    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )
        بنیاد_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Timer_Is_Timer_فعال( xTimer );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_Timer_Is_Timer_فعال( xTimer );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( خالی ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTimerGetTimerDaemonTaskHandle();
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTimerGetTimerDaemonTaskHandle();
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )
        خالی MPU_v_Timer_سیٹ_Reload_منوال( TimerHandle_t xTimer,
                                      ثابت بنیاد_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_Timer_سیٹ_Reload_منوال( xTimer, xAutoReload );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                v_Timer_سیٹ_Reload_منوال( xTimer, xAutoReload );
            }
        }
    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_ux_Timer_Get_Reload_منوال( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                uxReturn = ux_Timer_Get_Reload_منوال( xTimer );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                uxReturn = ux_Timer_Get_Reload_منوال( xTimer );
            }

            واپس uxReturn;
        }
    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )
        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ثابت حرف * pcReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                pcReturn = pcTimerGetName( xTimer );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                pcReturn = pcTimerGetName( xTimer );
            }

            واپس pcReturn;
        }
    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTimerGetPeriod( xTimer );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTimerGetPeriod( xTimer );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )
        TickType_t MPU_x_Timer_Get_Expiry_وقت( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Timer_Get_Expiry_وقت( xTimer );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_Timer_Get_Expiry_وقت( xTimer );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )
        بنیاد_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ثابت بنیاد_Type_t xCommandID,
                                                     ثابت TickType_t x_Optional_قدر,
                                                     بنیاد_Type_t * ثابت px_Higher_ترجیح_Task_Woken,
                                                     ثابت TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_قدر, px_Higher_ترجیح_Task_Woken, x_Ticks_مقصد_Wait );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_قدر, px_Higher_ترجیح_Task_Woken, x_Ticks_مقصد_Wait );
            }

            واپس xReturn;
        }
    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_گروہ_Handle_t MPU_x_Event_گروہ_Create( خالی ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_گروہ_Handle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Event_گروہ_Create();
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_Event_گروہ_Create();
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_گروہ_Handle_t MPU_x_Event_گروہ_Create_Static( Static_Event_گروہ_t * px_Event_گروہ_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_گروہ_Handle_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Event_گروہ_Create_Static( px_Event_گروہ_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_Event_گروہ_Create_Static( px_Event_گروہ_بفر );
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )
        Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                             ثابت Event_بٹ_t ux_بٹ_مقصد_Wait_For,
                                             ثابت بنیاد_Type_t xClearOnExit,
                                             ثابت بنیاد_Type_t x_Wait_For_All_بٹ,
                                             TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٹ_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Event_گروہ_Wait_بٹ( x_Event_گروہ, ux_بٹ_مقصد_Wait_For, xClearOnExit, x_Wait_For_All_بٹ, x_Ticks_مقصد_Wait );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_Event_گروہ_Wait_بٹ( x_Event_گروہ, ux_بٹ_مقصد_Wait_For, xClearOnExit, x_Wait_For_All_بٹ, x_Ticks_مقصد_Wait );
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )
        Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                              ثابت Event_بٹ_t ux_بٹ_مقصد_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٹ_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Event_گروہ_Clear_بٹ( x_Event_گروہ, ux_بٹ_مقصد_Clear );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_Event_گروہ_Clear_بٹ( x_Event_گروہ, ux_بٹ_مقصد_Clear );
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )
        Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                            ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٹ_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Event_گروہ_سیٹ_بٹ( x_Event_گروہ, ux_بٹ_مقصد_سیٹ );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_Event_گروہ_سیٹ_بٹ( x_Event_گروہ, ux_بٹ_مقصد_سیٹ );
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )
        Event_بٹ_t MPU_x_Event_گروہ_Sync( Event_گروہ_Handle_t x_Event_گروہ,
                                         ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ,
                                         ثابت Event_بٹ_t ux_بٹ_مقصد_Wait_For,
                                         TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٹ_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Event_گروہ_Sync( x_Event_گروہ, ux_بٹ_مقصد_سیٹ, ux_بٹ_مقصد_Wait_For, x_Ticks_مقصد_Wait );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_Event_گروہ_Sync( x_Event_گروہ, ux_بٹ_مقصد_سیٹ, ux_بٹ_مقصد_Wait_For, x_Ticks_مقصد_Wait );
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )
        خالی MPU_v_Event_گروہ_Delete( Event_گروہ_Handle_t x_Event_گروہ ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_Event_گروہ_Delete( x_Event_گروہ );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                v_Event_گروہ_Delete( x_Event_گروہ );
            }
        }
    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )
        size_t MPU_x_دھارا_بفر_Send( دھارا_بفر_Handle_t x_دھارا_بفر,
                                      ثابت خالی * pv_Tx_ڈیٹا,
                                      size_t x_ڈیٹا_لمبائی_بائٹیں,
                                      TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_Send( x_دھارا_بفر, pv_Tx_ڈیٹا, x_ڈیٹا_لمبائی_بائٹیں, x_Ticks_مقصد_Wait );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_دھارا_بفر_Send( x_دھارا_بفر, pv_Tx_ڈیٹا, x_ڈیٹا_لمبائی_بائٹیں, x_Ticks_مقصد_Wait );
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )
        size_t MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں( x_دھارا_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں( x_دھارا_بفر );
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )
        size_t MPU_x_دھارا_بفر_Receive( دھارا_بفر_Handle_t x_دھارا_بفر,
                                         خالی * pv_Rx_ڈیٹا,
                                         size_t x_بفر_لمبائی_بائٹیں,
                                         TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_Receive( x_دھارا_بفر, pv_Rx_ڈیٹا, x_بفر_لمبائی_بائٹیں, x_Ticks_مقصد_Wait );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_دھارا_بفر_Receive( x_دھارا_بفر, pv_Rx_ڈیٹا, x_بفر_لمبائی_بائٹیں, x_Ticks_مقصد_Wait );
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )
        خالی MPU_v_دھارا_بفر_Delete( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_دھارا_بفر_Delete( x_دھارا_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                v_دھارا_بفر_Delete( x_دھارا_بفر );
            }
        }
    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )
        بنیاد_Type_t MPU_x_دھارا_بفر_Is_بھرا( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_Is_بھرا( x_دھارا_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_دھارا_بفر_Is_بھرا( x_دھارا_بفر );
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )
        بنیاد_Type_t MPU_x_دھارا_بفر_Is_خالی_خانے( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_Is_خالی_خانے( x_دھارا_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_دھارا_بفر_Is_خالی_خانے( x_دھارا_بفر );
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )
        بنیاد_Type_t MPU_x_دھارا_بفر_Reset( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_Reset( x_دھارا_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_دھارا_بفر_Reset( x_دھارا_بفر );
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )
        size_t MPU_x_دھارا_بفر_Spaces_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
                xReturn = x_دھارا_بفر_Spaces_دستیاب( x_دھارا_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_دھارا_بفر_Spaces_دستیاب( x_دھارا_بفر );
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )
        size_t MPU_x_دھارا_بفر_بائٹیں_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_بائٹیں_دستیاب( x_دھارا_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_دھارا_بفر_بائٹیں_دستیاب( x_دھارا_بفر );
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )
        بنیاد_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                     size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn;

            اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_سیٹ_Trigger_Level( x_دھارا_بفر, xTriggerLevel );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            ورنہ
            {
                xReturn = x_دھارا_بفر_سیٹ_Trigger_Level( x_دھارا_بفر, xTriggerLevel );
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) && ( config_USE_دھارا_BUFFERS == 1 ) )
        دھارا_بفر_Handle_t MPU_x_دھارا_بفر_Generic_Create( size_t x_بفر_سائز_بائٹیں,
                                                             size_t x_Trigger_Level_بائٹیں,
                                                             بنیاد_Type_t x_دھارا_بفر_Type,
                                                             دھارا_بفر_Callback_Function_t pxSendCompletedCallback,
                                                             دھارا_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            دھارا_بفر_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == تہی ) &&
                          ( pxReceiveCompletedCallback == تہی ) );

            اگر( ( pxSendCompletedCallback == تہی ) &&
                ( pxReceiveCompletedCallback == تہی ) )
            {
                اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
                {
                    پورٹ_RAISE_PRIVILEGE();
                    پورٹ_حافظہ_BARRIER();

                    xReturn = x_دھارا_بفر_Generic_Create( x_بفر_سائز_بائٹیں,
                                                          x_Trigger_Level_بائٹیں,
                                                          x_دھارا_بفر_Type,
                                                          تہی,
                                                          تہی );
                    پورٹ_حافظہ_BARRIER();

                    پورٹ_RESET_PRIVILEGE();
                    پورٹ_حافظہ_BARRIER();
                }
                ورنہ
                {
                    xReturn = x_دھارا_بفر_Generic_Create( x_بفر_سائز_بائٹیں,
                                                          x_Trigger_Level_بائٹیں,
                                                          x_دھارا_بفر_Type,
                                                          تہی,
                                                          تہی );
                }
            }
            ورنہ
            {
                trace_دھارا_بفر_CREATE_FAILED( x_دھارا_بفر_Type );
                xReturn = تہی;
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( config_USE_دھارا_BUFFERS == 1 ) )
        دھارا_بفر_Handle_t MPU_x_دھارا_بفر_Generic_Create_Static( size_t x_بفر_سائز_بائٹیں,
                                                                   size_t x_Trigger_Level_بائٹیں,
                                                                   بنیاد_Type_t x_دھارا_بفر_Type,
                                                                   uint8_t * ثابت puc_دھارا_بفر_Storage_Area,
                                                                   Static_دھارا_بفر_t * ثابت px_Static_دھارا_بفر,
                                                                   دھارا_بفر_Callback_Function_t pxSendCompletedCallback,
                                                                   دھارا_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            دھارا_بفر_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == تہی ) &&
                          ( pxReceiveCompletedCallback == تہی ) );

            اگر( ( pxSendCompletedCallback == تہی ) &&
                ( pxReceiveCompletedCallback == تہی ) )
            {
                اگر( پورٹ_IS_PRIVILEGED() == pdFALSE )
                {
                    پورٹ_RAISE_PRIVILEGE();
                    پورٹ_حافظہ_BARRIER();

                    xReturn = x_دھارا_بفر_Generic_Create_Static( x_بفر_سائز_بائٹیں,
                                                                x_Trigger_Level_بائٹیں,
                                                                x_دھارا_بفر_Type,
                                                                puc_دھارا_بفر_Storage_Area,
                                                                px_Static_دھارا_بفر,
                                                                تہی,
                                                                تہی );
                    پورٹ_حافظہ_BARRIER();

                    پورٹ_RESET_PRIVILEGE();
                    پورٹ_حافظہ_BARRIER();
                }
                ورنہ
                {
                    xReturn = x_دھارا_بفر_Generic_Create_Static( x_بفر_سائز_بائٹیں,
                                                                x_Trigger_Level_بائٹیں,
                                                                x_دھارا_بفر_Type,
                                                                puc_دھارا_بفر_Storage_Area,
                                                                px_Static_دھارا_بفر,
                                                                تہی,
                                                                تہی );
                }
            }
            ورنہ
            {
                trace_دھارا_بفر_CREATE_STATIC_FAILED( xReturn, x_دھارا_بفر_Type );
                xReturn = تہی;
            }

            واپس xReturn;
        }
    #اگر_ختم /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/


/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h.  The functions
 * must take the same format as those above whereby the privilege state on exit
 * equals the privilege state on entry.  For example:
 *
 * void MPU_FunctionName( [parameters ] ) FREERTOS_SYSTEM_CALL;
 * void MPU_FunctionName( [parameters ] )
 * {
 *      if( portIS_PRIVILEGED() == pdFALSE )
 *      {
 *          portRAISE_PRIVILEGE();
 *          portMEMORY_BARRIER();
 *
 *          FunctionName( [parameters ] );
 *          portMEMORY_BARRIER();
 *
 *          portRESET_PRIVILEGE();
 *          portMEMORY_BARRIER();
 *      }
 *      else
 *      {
 *          FunctionName( [parameters ] );
 *      }
 * }
 */

    #اگر configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #شامل "application_defined_privileged_functions.h"
    #اگر_ختم
/*-----------------------------------------------------------*/

#اگر_ختم /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
