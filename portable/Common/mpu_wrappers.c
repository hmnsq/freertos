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
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "queue.h"
#ضمن "timers.h"
#ضمن "event_groups.h"
#ضمن "stream_buffer.h"
#ضمن "mpu_prototypes.h"

#تعریف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#إذا ( ( پورٹ_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #غلطی Access control list is not دستیاب with this MPU wrapper. Please سیٹ configENABLE_ACCESS_CONTROL_LIST منزل 0.
    #جے_انت

    #إذا ( config_SUPPORT_DYNAMIC_ونڈ == 1 )
        ادھار_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_کوڈ,
                                    ثابت حرف * ثابت pcName,
                                    ثابت config_ڈھیر_ڈونگھائی_TYPE ux_ڈھیر_ڈونگھائی,
                                    فراغ * pvParameters,
                                    UBaseType_t ux_ترجیح,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                ux_ترجیح = ux_ترجیح & ~( پورٹ_PRIVILEGE_ثنائی_ہندسہ );
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskCreate( pv_Task_کوڈ, pcName, ux_ڈھیر_ڈونگھائی, pvParameters, ux_ترجیح, pxCreatedTask );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskCreate( pv_Task_کوڈ, pcName, ux_ڈھیر_ڈونگھائی, pvParameters, ux_ترجیح, pxCreatedTask );
            }

            أرجع xReturn;
        }
    #جے_انت /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ونڈ == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_کوڈ,
                                            ثابت حرف * ثابت pcName,
                                            ثابت config_ڈھیر_ڈونگھائی_TYPE ux_ڈھیر_ڈونگھائی,
                                            فراغ * ثابت pvParameters,
                                            UBaseType_t ux_ترجیح,
                                            ڈھیر_Type_t * ثابت pux_ڈھیر_بفر,
                                            StaticTask_t * ثابت px_Task_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                ux_ترجیح = ux_ترجیح & ~( پورٹ_PRIVILEGE_ثنائی_ہندسہ );
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskCreateStatic( px_Task_کوڈ, pcName, ux_ڈھیر_ڈونگھائی, pvParameters, ux_ترجیح, pux_ڈھیر_بفر, px_Task_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskCreateStatic( px_Task_کوڈ, pcName, ux_ڈھیر_ڈونگھائی, pvParameters, ux_ترجیح, pux_ڈھیر_بفر, px_Task_بفر );
            }

            أرجع xReturn;
        }
    #جے_انت /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelete == 1 )
        فراغ MPU_vTaskDelete( TaskHandle_t px_Task_منزل_Delete ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                vTaskDelete( px_Task_منزل_Delete );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                vTaskDelete( px_Task_منزل_Delete );
            }
        }
    #جے_انت /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskDelayUntil == 1 )
        ادھار_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_پچھلا_Wake_ویلا,
                                        TickType_t x_ویلا_Increment ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskDelayUntil( px_پچھلا_Wake_ویلا, x_ویلا_Increment );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskDelayUntil( px_پچھلا_Wake_ویلا, x_ویلا_Increment );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskAbortDelay == 1 )
        ادھار_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskAbortDelay( xTask );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskAbortDelay( xTask );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelay == 1 )
        فراغ MPU_vTaskDelay( TickType_t x_Ticks_منزل_Delay ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                vTaskDelay( x_Ticks_منزل_Delay );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                vTaskDelay( x_Ticks_منزل_Delay );
            }
        }
    #جے_انت /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_ترجیح_Get == 1 )
        UBaseType_t MPU_ux_Task_ترجیح_Get( ثابت TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                uxReturn = ux_Task_ترجیح_Get( pxTask );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Task_ترجیح_Get( pxTask );
            }

            أرجع uxReturn;
        }
    #جے_انت /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_v_Task_ترجیح_سیٹ == 1 )
        فراغ MPU_v_Task_ترجیح_سیٹ( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_ترجیح ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_Task_ترجیح_سیٹ( pxTask, ux_New_ترجیح );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                v_Task_ترجیح_سیٹ( pxTask, ux_New_ترجیح );
            }
        }
    #جے_انت /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                eReturn = eTaskGetState( pxTask );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                eReturn = eTaskGetState( pxTask );
            }

            أرجع eReturn;
        }
    #جے_انت /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )
        فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_حالت_t * px_Task_حالت,
                               ادھار_Type_t x_Get_Free_ڈھیر_Space,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                vTaskGetInfo( xTask, px_Task_حالت, x_Get_Free_ڈھیر_Space, eState );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                vTaskGetInfo( xTask, px_Task_حالت, x_Get_Free_ڈھیر_Space, eState );
            }
        }
    #جے_انت /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
                xReturn = xTaskGetIdleTaskHandle();
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetIdleTaskHandle();
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )
        فراغ MPU_vTaskSuspend( TaskHandle_t px_Task_منزل_Suspend ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                vTaskSuspend( px_Task_منزل_Suspend );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                vTaskSuspend( px_Task_منزل_Suspend );
            }
        }
    #جے_انت /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )
        فراغ MPU_vTaskResume( TaskHandle_t px_Task_منزل_Resume ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                vTaskResume( px_Task_منزل_Resume );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                vTaskResume( px_Task_منزل_Resume );
            }
        }
    #جے_انت /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_vTaskSuspendAll( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            vTaskSuspendAll();
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            vTaskSuspendAll();
        }
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_xTaskResumeAll( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        ادھار_Type_t xReturn;

        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = xTaskResumeAll();
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            xReturn = xTaskResumeAll();
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_گنتی( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_Task_Get_Tick_گنتی();
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            xReturn = x_Task_Get_Tick_گنتی();
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_نمبر_دا_Tasks( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            uxReturn = ux_Task_Get_نمبر_دا_Tasks();
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            uxReturn = ux_Task_Get_نمبر_دا_Tasks();
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( ثابت حرف * pc_Name_منزل_Query ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskGetHandle( pc_Name_منزل_Query );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetHandle( pc_Name_منزل_Query );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_ونڈ == 1 ) )
        فراغ MPU_vTaskListTasks( حرف * pc_Write_بفر,
                                 size_t ux_بفر_لمائی ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                vTaskListTasks( pc_Write_بفر, ux_بفر_لمائی );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                vTaskListTasks( pc_Write_بفر, ux_بفر_لمائی );
            }
        }
    #جے_انت /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_لگاتار_ویلا_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_ونڈ == 1 ) )
        فراغ MPU_v_Task_Get_لگاتار_ویلا_Statistics( حرف * pc_Write_بفر,
                                            size_t ux_بفر_لمائی ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_Task_Get_لگاتار_ویلا_Statistics( pc_Write_بفر, ux_بفر_لمائی );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                v_Task_Get_لگاتار_ویلا_Statistics( pc_Write_بفر, ux_بفر_لمائی );
            }
        }
    #جے_انت /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_لگاتار_ویلا_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_Idle_لگاتار_ویلا_Percent( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            config_لگاتار_ویلا_COUNTER_TYPE xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = ul_Task_Get_Idle_لگاتار_ویلا_Percent();
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = ul_Task_Get_Idle_لگاتار_ویلا_Percent();
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_لگاتار_ویلا_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_Idle_لگاتار_ویلا_Counter( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            config_لگاتار_ویلا_COUNTER_TYPE xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = ul_Task_Get_Idle_لگاتار_ویلا_Counter();
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = ul_Task_Get_Idle_لگاتار_ویلا_Counter();
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٹیگ == 1 )
        فراغ MPU_v_Task_سیٹ_Application_Task_ٹیگ( TaskHandle_t xTask,
                                             TaskHookFunction_t px_ٹیگ_قدر ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_Task_سیٹ_Application_Task_ٹیگ( xTask, px_ٹیگ_قدر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                v_Task_سیٹ_Application_Task_ٹیگ( xTask, px_ٹیگ_قدر );
            }
        }
    #جے_انت /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٹیگ == 1 )
        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٹیگ( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Task_Get_Application_Task_ٹیگ( xTask );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_Task_Get_Application_Task_ٹیگ( xTask );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_عدد_THREAD_LOCAL_STORAGE_سوچکاں != 0 )
        فراغ MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_منزل_سیٹ,
                                                    ادھار_Type_t x_اشاریہ,
                                                    فراغ * pv_قدر ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( x_Task_منزل_سیٹ, x_اشاریہ, pv_قدر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( x_Task_منزل_سیٹ, x_اشاریہ, pv_قدر );
            }
        }
    #جے_انت /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_عدد_THREAD_LOCAL_STORAGE_سوچکاں != 0 )
        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر( TaskHandle_t x_Task_منزل_Query,
                                                       ادھار_Type_t x_اشاریہ ) /* FREERTOS_SYSTEM_CALL */
        {
            فراغ * pvReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                pvReturn = pv_Task_Get_Thread_Local_Storage_اشارہ_گر( x_Task_منزل_Query, x_اشاریہ );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_اشارہ_گر( x_Task_منزل_Query, x_اشاریہ );
            }

            أرجع pvReturn;
        }
    #جے_انت /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٹیگ == 1 )
        ادھار_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     فراغ * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( Task_حالت_t * px_Task_حالت_Array,
                                              UBaseType_t ux_Array_ناپ,
                                              config_لگاتار_ویلا_COUNTER_TYPE * pul_کل_لگاتار_ویلا ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                uxReturn = uxTaskGetSystemState( px_Task_حالت_Array, ux_Array_ناپ, pul_کل_لگاتار_ویلا );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                uxReturn = uxTaskGetSystemState( px_Task_حالت_Array, ux_Array_ناپ, pul_کل_لگاتار_ویلا );
            }

            أرجع uxReturn;
        }
    #جے_انت /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_Task_Catch_اتے_Ticks( TickType_t x_Ticks_منزل_Catch_اتے ) /* FREERTOS_SYSTEM_CALL */
    {
        ادھار_Type_t xReturn;

        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_Task_Catch_اتے_Ticks( x_Ticks_منزل_Catch_اتے );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            xReturn = x_Task_Catch_اتے_Ticks( x_Ticks_منزل_Catch_اتے );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark == 1 )
        UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark( xTask );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark( xTask );
            }

            أرجع uxReturn;
        }
    #جے_انت /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark2 == 1 )
        config_ڈھیر_ڈونگھائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            config_ڈھیر_ڈونگھائی_TYPE uxReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark2( xTask );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark2( xTask );
            }

            أرجع uxReturn;
        }
    #جے_انت /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
                xReturn = xTaskGetCurrentTaskHandle();
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetCurrentTaskHandle();
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )
        ادھار_Type_t MPU_xTaskGetSchedulerState( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskGetSchedulerState();
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetSchedulerState();
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_v_Task_سیٹ_ویلا_باہرلا_State( ویلا_باہرلا_t * ثابت px_ویلا_باہرلا ) /* FREERTOS_SYSTEM_CALL */
    {
        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            v_Task_سیٹ_ویلا_باہرلا_State( px_ویلا_باہرلا );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            v_Task_سیٹ_ویلا_باہرلا_State( px_ویلا_باہرلا );
        }
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_Task_Check_For_ویلا_باہرلا( ویلا_باہرلا_t * ثابت px_ویلا_باہرلا,
                                         TickType_t * ثابت px_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        ادھار_Type_t xReturn;

        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_Task_Check_For_ویلا_باہرلا( px_ویلا_باہرلا, px_Ticks_منزل_Wait );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            xReturn = x_Task_Check_For_ویلا_باہرلا( px_ویلا_باہرلا, px_Ticks_منزل_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        ادھار_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_منزل_Notify,
                                           UBaseType_t ux_اشاریہ_منزل_Notify,
                                           uint32_t ul_قدر,
                                           eNotifyAction eAction,
                                           uint32_t * pul_پچھلا_Notification_قدر ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskGenericNotify( x_Task_منزل_Notify, ux_اشاریہ_منزل_Notify, ul_قدر, eAction, pul_پچھلا_Notification_قدر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGenericNotify( x_Task_منزل_Notify, ux_اشاریہ_منزل_Notify, ul_قدر, eAction, pul_پچھلا_Notification_قدر );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        ادھار_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_اشاریہ_منزل_Wait_On,
                                               uint32_t ul_بٹ_منزل_Clear_On_اندراج,
                                               uint32_t ul_بٹ_منزل_Clear_On_Exit,
                                               uint32_t * pul_Notification_قدر,
                                               TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskGenericNotifyWait( ux_اشاریہ_منزل_Wait_On, ul_بٹ_منزل_Clear_On_اندراج, ul_بٹ_منزل_Clear_On_Exit, pul_Notification_قدر, x_Ticks_منزل_Wait );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGenericNotifyWait( ux_اشاریہ_منزل_Wait_On, ul_بٹ_منزل_Clear_On_اندراج, ul_بٹ_منزل_Clear_On_Exit, pul_Notification_قدر, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_اشاریہ_منزل_Wait_On,
                                              ادھار_Type_t x_Clear_گنتی_On_Exit,
                                              TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( ux_اشاریہ_منزل_Wait_On, x_Clear_گنتی_On_Exit, x_Ticks_منزل_Wait );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                ulReturn = ulTaskGenericNotifyTake( ux_اشاریہ_منزل_Wait_On, x_Clear_گنتی_On_Exit, x_Ticks_منزل_Wait );
            }

            أرجع ulReturn;
        }
    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        ادھار_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_اشاریہ_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, ux_اشاریہ_منزل_Clear );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, ux_اشاریہ_منزل_Clear );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_اشاریہ_منزل_Clear,
                                                    uint32_t ul_بٹ_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                ulReturn = ul_Task_Generic_Notify_قدر_Clear( xTask, ux_اشاریہ_منزل_Clear, ul_بٹ_منزل_Clear );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                ulReturn = ul_Task_Generic_Notify_قدر_Clear( xTask, ux_اشاریہ_منزل_Clear, ul_بٹ_منزل_Clear );
            }

            أرجع ulReturn;
        }
    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ونڈ == 1 )
        قطار_Handle_t MPU_x_قطار_Generic_Create( UBaseType_t ux_قطار_لمائی,
                                               UBaseType_t ux_شے_ناپ,
                                               uint8_t uc_قطار_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Generic_Create( ux_قطار_لمائی, ux_شے_ناپ, uc_قطار_Type );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Generic_Create( ux_قطار_لمائی, ux_شے_ناپ, uc_قطار_Type );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ونڈ == 1 )
        قطار_Handle_t MPU_x_قطار_Generic_Create_Static( ثابت UBaseType_t ux_قطار_لمائی,
                                                     ثابت UBaseType_t ux_شے_ناپ,
                                                     uint8_t * puc_قطار_Storage,
                                                     Static_قطار_t * px_Static_قطار,
                                                     ثابت uint8_t uc_قطار_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Generic_Create_Static( ux_قطار_لمائی, ux_شے_ناپ, puc_قطار_Storage, px_Static_قطار, uc_قطار_Type );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Generic_Create_Static( ux_قطار_لمائی, ux_شے_ناپ, puc_قطار_Storage, px_Static_قطار, uc_قطار_Type );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Generic_Reset( قطار_Handle_t px_قطار,
                                       ادھار_Type_t x_New_قطار ) /* FREERTOS_SYSTEM_CALL */
    {
        ادھار_Type_t xReturn;

        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_قطار_Generic_Reset( px_قطار, x_New_قطار );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            xReturn = x_قطار_Generic_Reset( px_قطار, x_New_قطار );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Generic_Send( قطار_Handle_t x_قطار,
                                      ثابت فراغ * ثابت pv_شے_منزل_قطار,
                                      TickType_t x_Ticks_منزل_Wait,
                                      ادھار_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        ادھار_Type_t xReturn;

        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_قطار_Generic_Send( x_قطار, pv_شے_منزل_قطار, x_Ticks_منزل_Wait, xCopyPosition );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            xReturn = x_قطار_Generic_Send( x_قطار, pv_شے_منزل_قطار, x_Ticks_منزل_Wait, xCopyPosition );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Messages_اڈیک( ثابت قطار_Handle_t px_قطار ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            uxReturn = ux_قطار_Messages_اڈیک( px_قطار );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            uxReturn = ux_قطار_Messages_اڈیک( px_قطار );
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Spaces_دستیاب( ثابت قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            uxReturn = ux_قطار_Spaces_دستیاب( x_قطار );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            uxReturn = ux_قطار_Spaces_دستیاب( x_قطار );
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Receive( قطار_Handle_t px_قطار,
                                  فراغ * ثابت pv_بفر,
                                  TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        ادھار_Type_t xReturn;

        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_قطار_Receive( px_قطار, pv_بفر, x_Ticks_منزل_Wait );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            xReturn = x_قطار_Receive( px_قطار, pv_بفر, x_Ticks_منزل_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Peek( قطار_Handle_t x_قطار,
                               فراغ * ثابت pv_بفر,
                               TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        ادھار_Type_t xReturn;

        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_قطار_Peek( x_قطار, pv_بفر, x_Ticks_منزل_Wait );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            xReturn = x_قطار_Peek( x_قطار, pv_بفر, x_Ticks_منزل_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Semaphore_Take( قطار_Handle_t x_قطار,
                                        TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        ادھار_Type_t xReturn;

        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            xReturn = x_قطار_Semaphore_Take( x_قطار, x_Ticks_منزل_Wait );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            xReturn = x_قطار_Semaphore_Take( x_قطار, x_Ticks_منزل_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder( قطار_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            فراغ * xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Get_Mutex_Holder( xSemaphore );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Get_Mutex_Holder( xSemaphore );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_ونڈ == 1 ) )
        قطار_Handle_t MPU_x_قطار_Create_Mutex( ثابت uint8_t uc_قطار_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Create_Mutex( uc_قطار_Type );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Create_Mutex( uc_قطار_Type );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_ونڈ == 1 ) )
        قطار_Handle_t MPU_x_قطار_Create_Mutex_Static( ثابت uint8_t uc_قطار_Type,
                                                   Static_قطار_t * px_Static_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Create_Mutex_Static( uc_قطار_Type, px_Static_قطار );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Create_Mutex_Static( uc_قطار_Type, px_Static_قطار );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_ونڈ == 1 ) )
        قطار_Handle_t MPU_x_قطار_Create_Counting_Semaphore( UBaseType_t ux_گنتی_قدر,
                                                         UBaseType_t ux_Initial_گنتی ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Create_Counting_Semaphore( ux_گنتی_قدر, ux_Initial_گنتی );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Create_Counting_Semaphore( ux_گنتی_قدر, ux_Initial_گنتی );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_ونڈ == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Counting_Semaphore_Static( ثابت UBaseType_t ux_Max_گنتی,
                                                               ثابت UBaseType_t ux_Initial_گنتی,
                                                               Static_قطار_t * px_Static_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_Handle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Create_Counting_Semaphore_Static( ux_Max_گنتی, ux_Initial_گنتی, px_Static_قطار );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Create_Counting_Semaphore_Static( ux_Max_گنتی, ux_Initial_گنتی, px_Static_قطار );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )
        ادھار_Type_t MPU_x_قطار_Take_Mutex_Recursive( قطار_Handle_t xMutex,
                                                 TickType_t x_بلاک_ویلا ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Take_Mutex_Recursive( xMutex, x_بلاک_ویلا );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Take_Mutex_Recursive( xMutex, x_بلاک_ویلا );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )
        ادھار_Type_t MPU_x_قطار_Give_Mutex_Recursive( قطار_Handle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Give_Mutex_Recursive( xMutex );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Give_Mutex_Recursive( xMutex );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_قطار_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_ونڈ == 1 ) )
        قطار_سیٹ_Handle_t MPU_x_قطار_Create_سیٹ( UBaseType_t ux_Event_قطار_لمائی ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_سیٹ_Handle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Create_سیٹ( ux_Event_قطار_لمائی );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Create_سیٹ( ux_Event_قطار_لمائی );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_قطار_SETS == 1 ) && ( config_SUPPORT_STATIC_ونڈ == 1 ) )
        قطار_سیٹ_Handle_t MPU_x_قطار_Create_سیٹ_Static( ثابت UBaseType_t ux_Event_قطار_لمائی,
                                                    uint8_t * puc_قطار_Storage,
                                                    Static_قطار_t * px_Static_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_سیٹ_Handle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Create_سیٹ_Static( ux_Event_قطار_لمائی, puc_قطار_Storage, px_Static_قطار );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Create_سیٹ_Static( ux_Event_قطار_لمائی, puc_قطار_Storage, px_Static_قطار );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )
        قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                        TickType_t x_بلاک_ویلا_Ticks ) /* FREERTOS_SYSTEM_CALL */
        {
            قطار_سیٹ_Member_Handle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Select_From_سیٹ( x_قطار_سیٹ, x_بلاک_ویلا_Ticks );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Select_From_سیٹ( x_قطار_سیٹ, x_بلاک_ویلا_Ticks );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )
        ادھار_Type_t MPU_x_قطار_جوڑو_منزل_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                       قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_جوڑو_منزل_سیٹ( x_قطار_Or_Semaphore, x_قطار_سیٹ );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_جوڑو_منزل_سیٹ( x_قطار_Or_Semaphore, x_قطار_سیٹ );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )
        ادھار_Type_t MPU_x_قطار_Remove_From_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                            قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_قطار_Remove_From_سیٹ( x_قطار_Or_Semaphore, x_قطار_سیٹ );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_قطار_Remove_From_سیٹ( x_قطار_Or_Semaphore, x_قطار_سیٹ );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا config_قطار_REGISTRY_ناپ > 0
        فراغ MPU_v_قطار_جوڑو_منزل_Registry( قطار_Handle_t x_قطار,
                                      ثابت حرف * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_قطار_جوڑو_منزل_Registry( x_قطار, pcName );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                v_قطار_جوڑو_منزل_Registry( x_قطار, pcName );
            }
        }
    #جے_انت /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_قطار_REGISTRY_ناپ > 0
        فراغ MPU_v_قطار_Unregister_قطار( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_قطار_Unregister_قطار( x_قطار );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                v_قطار_Unregister_قطار( x_قطار );
            }
        }
    #جے_انت /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_قطار_REGISTRY_ناپ > 0
        ثابت حرف * MPU_pc_قطار_Get_Name( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
        {
            ثابت حرف * pcReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                pcReturn = pc_قطار_Get_Name( x_قطار );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                pcReturn = pc_قطار_Get_Name( x_قطار );
            }

            أرجع pcReturn;
        }
    #جے_انت /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    فراغ MPU_v_قطار_Delete( قطار_Handle_t x_قطار ) /* FREERTOS_SYSTEM_CALL */
    {
        إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
        {
            پورٹ_RAISE_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();

            v_قطار_Delete( x_قطار );
            پورٹ_حافظہ_BARRIER();

            پورٹ_RESET_PRIVILEGE();
            پورٹ_حافظہ_BARRIER();
        }
        وإلا
        {
            v_قطار_Delete( x_قطار );
        }
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            فراغ * pvReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                pvReturn = pvTimerGetTimerID( xTimer );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                pvReturn = pvTimerGetTimerID( xTimer );
            }

            أرجع pvReturn;
        }
    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        فراغ MPU_v_Timer_سیٹ_Timer_ID( TimerHandle_t xTimer,
                                   فراغ * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_Timer_سیٹ_Timer_ID( xTimer, pvNewID );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                v_Timer_سیٹ_Timer_ID( xTimer, pvNewID );
            }
        }
    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        ادھار_Type_t MPU_x_Timer_Is_Timer_سرگرم( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Timer_Is_Timer_سرگرم( xTimer );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_Timer_Is_Timer_سرگرم( xTimer );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTimerGetTimerDaemonTaskHandle();
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTimerGetTimerDaemonTaskHandle();
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        فراغ MPU_v_Timer_سیٹ_Reload_منوال( TimerHandle_t xTimer,
                                      ثابت ادھار_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_Timer_سیٹ_Reload_منوال( xTimer, xAutoReload );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                v_Timer_سیٹ_Reload_منوال( xTimer, xAutoReload );
            }
        }
    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_ux_Timer_Get_Reload_منوال( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                uxReturn = ux_Timer_Get_Reload_منوال( xTimer );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Timer_Get_Reload_منوال( xTimer );
            }

            أرجع uxReturn;
        }
    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ثابت حرف * pcReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                pcReturn = pcTimerGetName( xTimer );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                pcReturn = pcTimerGetName( xTimer );
            }

            أرجع pcReturn;
        }
    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTimerGetPeriod( xTimer );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTimerGetPeriod( xTimer );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        TickType_t MPU_x_Timer_Get_Expiry_ویلا( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Timer_Get_Expiry_ویلا( xTimer );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_Timer_Get_Expiry_ویلا( xTimer );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        ادھار_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ثابت ادھار_Type_t xCommandID,
                                                     ثابت TickType_t x_Optional_قدر,
                                                     ادھار_Type_t * ثابت px_Higher_ترجیح_Task_Woken,
                                                     ثابت TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_قدر, px_Higher_ترجیح_Task_Woken, x_Ticks_منزل_Wait );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_قدر, px_Higher_ترجیح_Task_Woken, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_ونڈ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_گروہ_Handle_t MPU_x_Event_گروہ_Create( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_گروہ_Handle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Event_گروہ_Create();
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروہ_Create();
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ونڈ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_گروہ_Handle_t MPU_x_Event_گروہ_Create_Static( Static_Event_گروہ_t * px_Event_گروہ_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_گروہ_Handle_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Event_گروہ_Create_Static( px_Event_گروہ_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروہ_Create_Static( px_Event_گروہ_بفر );
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                             ثابت Event_بٹ_t ux_بٹ_منزل_Wait_For,
                                             ثابت ادھار_Type_t xClearOnExit,
                                             ثابت ادھار_Type_t x_Wait_For_All_بٹ,
                                             TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٹ_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Event_گروہ_Wait_بٹ( x_Event_گروہ, ux_بٹ_منزل_Wait_For, xClearOnExit, x_Wait_For_All_بٹ, x_Ticks_منزل_Wait );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروہ_Wait_بٹ( x_Event_گروہ, ux_بٹ_منزل_Wait_For, xClearOnExit, x_Wait_For_All_بٹ, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                              ثابت Event_بٹ_t ux_بٹ_منزل_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٹ_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Event_گروہ_Clear_بٹ( x_Event_گروہ, ux_بٹ_منزل_Clear );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروہ_Clear_بٹ( x_Event_گروہ, ux_بٹ_منزل_Clear );
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                            ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٹ_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Event_گروہ_سیٹ_بٹ( x_Event_گروہ, ux_بٹ_منزل_سیٹ );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروہ_سیٹ_بٹ( x_Event_گروہ, ux_بٹ_منزل_سیٹ );
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بٹ_t MPU_x_Event_گروہ_Sync( Event_گروہ_Handle_t x_Event_گروہ,
                                         ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ,
                                         ثابت Event_بٹ_t ux_بٹ_منزل_Wait_For,
                                         TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٹ_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_Event_گروہ_Sync( x_Event_گروہ, ux_بٹ_منزل_سیٹ, ux_بٹ_منزل_Wait_For, x_Ticks_منزل_Wait );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروہ_Sync( x_Event_گروہ, ux_بٹ_منزل_سیٹ, ux_بٹ_منزل_Wait_For, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        فراغ MPU_v_Event_گروہ_Delete( Event_گروہ_Handle_t x_Event_گروہ ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_Event_گروہ_Delete( x_Event_گروہ );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                v_Event_گروہ_Delete( x_Event_گروہ );
            }
        }
    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )
        size_t MPU_x_دھارا_بفر_Send( دھارا_بفر_Handle_t x_دھارا_بفر,
                                      ثابت فراغ * pv_Tx_انکڑے,
                                      size_t x_انکڑے_لمائی_بائٹاں,
                                      TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_Send( x_دھارا_بفر, pv_Tx_انکڑے, x_انکڑے_لمائی_بائٹاں, x_Ticks_منزل_Wait );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_دھارا_بفر_Send( x_دھارا_بفر, pv_Tx_انکڑے, x_انکڑے_لمائی_بائٹاں, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )
        size_t MPU_x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں( x_دھارا_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں( x_دھارا_بفر );
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )
        size_t MPU_x_دھارا_بفر_Receive( دھارا_بفر_Handle_t x_دھارا_بفر,
                                         فراغ * pv_Rx_انکڑے,
                                         size_t x_بفر_لمائی_بائٹاں,
                                         TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_Receive( x_دھارا_بفر, pv_Rx_انکڑے, x_بفر_لمائی_بائٹاں, x_Ticks_منزل_Wait );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_دھارا_بفر_Receive( x_دھارا_بفر, pv_Rx_انکڑے, x_بفر_لمائی_بائٹاں, x_Ticks_منزل_Wait );
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )
        فراغ MPU_v_دھارا_بفر_Delete( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                v_دھارا_بفر_Delete( x_دھارا_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                v_دھارا_بفر_Delete( x_دھارا_بفر );
            }
        }
    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )
        ادھار_Type_t MPU_x_دھارا_بفر_Is_بھریا( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_Is_بھریا( x_دھارا_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_دھارا_بفر_Is_بھریا( x_دھارا_بفر );
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )
        ادھار_Type_t MPU_x_دھارا_بفر_Is_خالی_تھاواں( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_Is_خالی_تھاواں( x_دھارا_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_دھارا_بفر_Is_خالی_تھاواں( x_دھارا_بفر );
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )
        ادھار_Type_t MPU_x_دھارا_بفر_Reset( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_Reset( x_دھارا_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_دھارا_بفر_Reset( x_دھارا_بفر );
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )
        size_t MPU_x_دھارا_بفر_Spaces_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
                xReturn = x_دھارا_بفر_Spaces_دستیاب( x_دھارا_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_دھارا_بفر_Spaces_دستیاب( x_دھارا_بفر );
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )
        size_t MPU_x_دھارا_بفر_بائٹاں_دستیاب( دھارا_بفر_Handle_t x_دھارا_بفر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_بائٹاں_دستیاب( x_دھارا_بفر );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_دھارا_بفر_بائٹاں_دستیاب( x_دھارا_بفر );
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )
        ادھار_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                     size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn;

            إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
            {
                پورٹ_RAISE_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();

                xReturn = x_دھارا_بفر_سیٹ_Trigger_Level( x_دھارا_بفر, xTriggerLevel );
                پورٹ_حافظہ_BARRIER();

                پورٹ_RESET_PRIVILEGE();
                پورٹ_حافظہ_BARRIER();
            }
            وإلا
            {
                xReturn = x_دھارا_بفر_سیٹ_Trigger_Level( x_دھارا_بفر, xTriggerLevel );
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_ونڈ == 1 ) && ( config_USE_دھارا_BUFFERS == 1 ) )
        دھارا_بفر_Handle_t MPU_x_دھارا_بفر_Generic_Create( size_t x_بفر_ناپ_بائٹاں,
                                                             size_t x_Trigger_Level_بائٹاں,
                                                             ادھار_Type_t x_دھارا_بفر_Type,
                                                             دھارا_بفر_Callback_Function_t pxSendCompletedCallback,
                                                             دھارا_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            دھارا_بفر_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == عدم ) &&
                          ( pxReceiveCompletedCallback == عدم ) );

            إذا( ( pxSendCompletedCallback == عدم ) &&
                ( pxReceiveCompletedCallback == عدم ) )
            {
                إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
                {
                    پورٹ_RAISE_PRIVILEGE();
                    پورٹ_حافظہ_BARRIER();

                    xReturn = x_دھارا_بفر_Generic_Create( x_بفر_ناپ_بائٹاں,
                                                          x_Trigger_Level_بائٹاں,
                                                          x_دھارا_بفر_Type,
                                                          عدم,
                                                          عدم );
                    پورٹ_حافظہ_BARRIER();

                    پورٹ_RESET_PRIVILEGE();
                    پورٹ_حافظہ_BARRIER();
                }
                وإلا
                {
                    xReturn = x_دھارا_بفر_Generic_Create( x_بفر_ناپ_بائٹاں,
                                                          x_Trigger_Level_بائٹاں,
                                                          x_دھارا_بفر_Type,
                                                          عدم,
                                                          عدم );
                }
            }
            وإلا
            {
                trace_دھارا_بفر_CREATE_FAILED( x_دھارا_بفر_Type );
                xReturn = عدم;
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ونڈ == 1 ) && ( config_USE_دھارا_BUFFERS == 1 ) )
        دھارا_بفر_Handle_t MPU_x_دھارا_بفر_Generic_Create_Static( size_t x_بفر_ناپ_بائٹاں,
                                                                   size_t x_Trigger_Level_بائٹاں,
                                                                   ادھار_Type_t x_دھارا_بفر_Type,
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
            configASSERT( ( pxSendCompletedCallback == عدم ) &&
                          ( pxReceiveCompletedCallback == عدم ) );

            إذا( ( pxSendCompletedCallback == عدم ) &&
                ( pxReceiveCompletedCallback == عدم ) )
            {
                إذا( پورٹ_IS_PRIVILEGED() == pdFALSE )
                {
                    پورٹ_RAISE_PRIVILEGE();
                    پورٹ_حافظہ_BARRIER();

                    xReturn = x_دھارا_بفر_Generic_Create_Static( x_بفر_ناپ_بائٹاں,
                                                                x_Trigger_Level_بائٹاں,
                                                                x_دھارا_بفر_Type,
                                                                puc_دھارا_بفر_Storage_Area,
                                                                px_Static_دھارا_بفر,
                                                                عدم,
                                                                عدم );
                    پورٹ_حافظہ_BARRIER();

                    پورٹ_RESET_PRIVILEGE();
                    پورٹ_حافظہ_BARRIER();
                }
                وإلا
                {
                    xReturn = x_دھارا_بفر_Generic_Create_Static( x_بفر_ناپ_بائٹاں,
                                                                x_Trigger_Level_بائٹاں,
                                                                x_دھارا_بفر_Type,
                                                                puc_دھارا_بفر_Storage_Area,
                                                                px_Static_دھارا_بفر,
                                                                عدم,
                                                                عدم );
                }
            }
            وإلا
            {
                trace_دھارا_بفر_CREATE_STATIC_FAILED( xReturn, x_دھارا_بفر_Type );
                xReturn = عدم;
            }

            أرجع xReturn;
        }
    #جے_انت /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
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

    #إذا configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #ضمن "application_defined_privileged_functions.h"
    #جے_انت
/*-----------------------------------------------------------*/

#جے_انت /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
