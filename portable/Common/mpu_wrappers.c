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
#تعریف_کن MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "queue.h"
#ضمن "timers.h"
#ضمن "event_groups.h"
#ضمن "stream_buffer.h"
#ضمن "mpu_prototypes.h"

#لغو_تعریف MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#إذا ( ( پورت_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #خطا Access control list is not موجود with this MPU wrapper. Please مجموعه configENABLE_ACCESS_CONTROL_LIST مقصد 0.
    #پایان_اگر

    #إذا ( config_SUPPORT_DYNAMIC_تخصیص == 1 )
        پایه_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_کد,
                                    ثابت حرف * ثابت pcName,
                                    ثابت config_پشته_عمق_TYPE ux_پشته_عمق,
                                    فراغ * pvParameters,
                                    UBaseType_t ux_اولویت,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                ux_اولویت = ux_اولویت & ~( پورت_PRIVILEGE_بیت );
                پورت_حافظه_BARRIER();

                xReturn = xTaskCreate( pv_Task_کد, pcName, ux_پشته_عمق, pvParameters, ux_اولویت, pxCreatedTask );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskCreate( pv_Task_کد, pcName, ux_پشته_عمق, pvParameters, ux_اولویت, pxCreatedTask );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_تخصیص == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_کد,
                                            ثابت حرف * ثابت pcName,
                                            ثابت config_پشته_عمق_TYPE ux_پشته_عمق,
                                            فراغ * ثابت pvParameters,
                                            UBaseType_t ux_اولویت,
                                            پشته_Type_t * ثابت pux_پشته_میانگیر,
                                            StaticTask_t * ثابت px_Task_میانگیر ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                ux_اولویت = ux_اولویت & ~( پورت_PRIVILEGE_بیت );
                پورت_حافظه_BARRIER();

                xReturn = xTaskCreateStatic( px_Task_کد, pcName, ux_پشته_عمق, pvParameters, ux_اولویت, pux_پشته_میانگیر, px_Task_میانگیر );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskCreateStatic( px_Task_کد, pcName, ux_پشته_عمق, pvParameters, ux_اولویت, pux_پشته_میانگیر, px_Task_میانگیر );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelete == 1 )
        فراغ MPU_vTaskDelete( TaskHandle_t px_Task_مقصد_Delete ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                vTaskDelete( px_Task_مقصد_Delete );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                vTaskDelete( px_Task_مقصد_Delete );
            }
        }
    #پایان_اگر /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskDelayUntil == 1 )
        پایه_Type_t MPU_xTaskDelayUntil( TickType_t * ثابت px_قبلی_Wake_زمان,
                                        TickType_t x_زمان_Increment ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = xTaskDelayUntil( px_قبلی_Wake_زمان, x_زمان_Increment );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskDelayUntil( px_قبلی_Wake_زمان, x_زمان_Increment );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskAbortDelay == 1 )
        پایه_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = xTaskAbortDelay( xTask );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskAbortDelay( xTask );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelay == 1 )
        فراغ MPU_vTaskDelay( TickType_t x_Ticks_مقصد_Delay ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                vTaskDelay( x_Ticks_مقصد_Delay );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                vTaskDelay( x_Ticks_مقصد_Delay );
            }
        }
    #پایان_اگر /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_اولویت_Get == 1 )
        UBaseType_t MPU_ux_Task_اولویت_Get( ثابت TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                uxReturn = ux_Task_اولویت_Get( pxTask );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Task_اولویت_Get( pxTask );
            }

            أرجع uxReturn;
        }
    #پایان_اگر /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_v_Task_اولویت_مجموعه == 1 )
        فراغ MPU_v_Task_اولویت_مجموعه( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_اولویت ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                v_Task_اولویت_مجموعه( pxTask, ux_New_اولویت );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                v_Task_اولویت_مجموعه( pxTask, ux_New_اولویت );
            }
        }
    #پایان_اگر /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                eReturn = eTaskGetState( pxTask );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                eReturn = eTaskGetState( pxTask );
            }

            أرجع eReturn;
        }
    #پایان_اگر /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )
        فراغ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_وضعیت_t * px_Task_وضعیت,
                               پایه_Type_t x_Get_Free_پشته_Space,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                vTaskGetInfo( xTask, px_Task_وضعیت, x_Get_Free_پشته_Space, eState );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                vTaskGetInfo( xTask, px_Task_وضعیت, x_Get_Free_پشته_Space, eState );
            }
        }
    #پایان_اگر /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();
                xReturn = xTaskGetIdleTaskHandle();
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetIdleTaskHandle();
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )
        فراغ MPU_vTaskSuspend( TaskHandle_t px_Task_مقصد_Suspend ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                vTaskSuspend( px_Task_مقصد_Suspend );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                vTaskSuspend( px_Task_مقصد_Suspend );
            }
        }
    #پایان_اگر /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )
        فراغ MPU_vTaskResume( TaskHandle_t px_Task_مقصد_Resume ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                vTaskResume( px_Task_مقصد_Resume );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                vTaskResume( px_Task_مقصد_Resume );
            }
        }
    #پایان_اگر /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_vTaskSuspendAll( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            vTaskSuspendAll();
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            vTaskSuspendAll();
        }
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_xTaskResumeAll( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        پایه_Type_t xReturn;

        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            xReturn = xTaskResumeAll();
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = xTaskResumeAll();
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_شمار( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            xReturn = x_Task_Get_Tick_شمار();
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_Task_Get_Tick_شمار();
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_عدد_از_Tasks( فراغ ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            uxReturn = ux_Task_Get_عدد_از_Tasks();
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            uxReturn = ux_Task_Get_عدد_از_Tasks();
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( ثابت حرف * pc_Name_مقصد_Query ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = xTaskGetHandle( pc_Name_مقصد_Query );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetHandle( pc_Name_مقصد_Query );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )
        فراغ MPU_vTaskListTasks( حرف * pc_Write_میانگیر,
                                 size_t ux_میانگیر_درازی ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                vTaskListTasks( pc_Write_میانگیر, ux_میانگیر_درازی );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                vTaskListTasks( pc_Write_میانگیر, ux_میانگیر_درازی );
            }
        }
    #پایان_اگر /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_پیاپی_زمان_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )
        فراغ MPU_v_Task_Get_پیاپی_زمان_Statistics( حرف * pc_Write_میانگیر,
                                            size_t ux_میانگیر_درازی ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                v_Task_Get_پیاپی_زمان_Statistics( pc_Write_میانگیر, ux_میانگیر_درازی );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                v_Task_Get_پیاپی_زمان_Statistics( pc_Write_میانگیر, ux_میانگیر_درازی );
            }
        }
    #پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_پیاپی_زمان_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            config_پیاپی_زمان_COUNTER_TYPE xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = ul_Task_Get_Idle_پیاپی_زمان_Percent();
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = ul_Task_Get_Idle_پیاپی_زمان_Percent();
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_پیاپی_زمان_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            config_پیاپی_زمان_COUNTER_TYPE xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = ul_Task_Get_Idle_پیاپی_زمان_Counter();
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = ul_Task_Get_Idle_پیاپی_زمان_Counter();
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )
        فراغ MPU_v_Task_مجموعه_Application_Task_برچسب( TaskHandle_t xTask,
                                             TaskHookFunction_t px_برچسب_مقدار ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                v_Task_مجموعه_Application_Task_برچسب( xTask, px_برچسب_مقدار );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                v_Task_مجموعه_Application_Task_برچسب( xTask, px_برچسب_مقدار );
            }
        }
    #پایان_اگر /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )
        TaskHookFunction_t MPU_x_Task_Get_Application_Task_برچسب( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_Task_Get_Application_Task_برچسب( xTask );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Task_Get_Application_Task_برچسب( xTask );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_رقم_THREAD_LOCAL_STORAGE_اشارهگرها != 0 )
        فراغ MPU_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر( TaskHandle_t x_Task_مقصد_مجموعه,
                                                    پایه_Type_t x_شاخص,
                                                    فراغ * pv_مقدار ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                v_Task_مجموعه_Thread_Local_Storage_اشاره_گر( x_Task_مقصد_مجموعه, x_شاخص, pv_مقدار );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                v_Task_مجموعه_Thread_Local_Storage_اشاره_گر( x_Task_مقصد_مجموعه, x_شاخص, pv_مقدار );
            }
        }
    #پایان_اگر /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_رقم_THREAD_LOCAL_STORAGE_اشارهگرها != 0 )
        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر( TaskHandle_t x_Task_مقصد_Query,
                                                       پایه_Type_t x_شاخص ) /* FREERTOS_SYSTEM_CALL */
        {
            فراغ * pvReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                pvReturn = pv_Task_Get_Thread_Local_Storage_اشاره_گر( x_Task_مقصد_Query, x_شاخص );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_اشاره_گر( x_Task_مقصد_Query, x_شاخص );
            }

            أرجع pvReturn;
        }
    #پایان_اگر /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )
        پایه_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     فراغ * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( Task_وضعیت_t * px_Task_وضعیت_Array,
                                              UBaseType_t ux_Array_اندازه,
                                              config_پیاپی_زمان_COUNTER_TYPE * pul_مجموع_پیاپی_زمان ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                uxReturn = uxTaskGetSystemState( px_Task_وضعیت_Array, ux_Array_اندازه, pul_مجموع_پیاپی_زمان );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                uxReturn = uxTaskGetSystemState( px_Task_وضعیت_Array, ux_Array_اندازه, pul_مجموع_پیاپی_زمان );
            }

            أرجع uxReturn;
        }
    #پایان_اگر /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_Task_Catch_به_بالا_Ticks( TickType_t x_Ticks_مقصد_Catch_به_بالا ) /* FREERTOS_SYSTEM_CALL */
    {
        پایه_Type_t xReturn;

        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            xReturn = x_Task_Catch_به_بالا_Ticks( x_Ticks_مقصد_Catch_به_بالا );
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_Task_Catch_به_بالا_Ticks( x_Ticks_مقصد_Catch_به_بالا );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_پشته_بالا_Water_Mark == 1 )
        UBaseType_t MPU_ux_Task_Get_پشته_بالا_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                uxReturn = ux_Task_Get_پشته_بالا_Water_Mark( xTask );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Task_Get_پشته_بالا_Water_Mark( xTask );
            }

            أرجع uxReturn;
        }
    #پایان_اگر /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_پشته_بالا_Water_Mark2 == 1 )
        config_پشته_عمق_TYPE MPU_ux_Task_Get_پشته_بالا_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            config_پشته_عمق_TYPE uxReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                uxReturn = ux_Task_Get_پشته_بالا_Water_Mark2( xTask );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Task_Get_پشته_بالا_Water_Mark2( xTask );
            }

            أرجع uxReturn;
        }
    #پایان_اگر /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();
                xReturn = xTaskGetCurrentTaskHandle();
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetCurrentTaskHandle();
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )
        پایه_Type_t MPU_xTaskGetSchedulerState( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = xTaskGetSchedulerState();
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGetSchedulerState();
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_v_Task_مجموعه_زمان_بیرون_State( زمان_بیرون_t * ثابت px_زمان_بیرون ) /* FREERTOS_SYSTEM_CALL */
    {
        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            v_Task_مجموعه_زمان_بیرون_State( px_زمان_بیرون );
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            v_Task_مجموعه_زمان_بیرون_State( px_زمان_بیرون );
        }
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_Task_Check_For_زمان_بیرون( زمان_بیرون_t * ثابت px_زمان_بیرون,
                                         TickType_t * ثابت px_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        پایه_Type_t xReturn;

        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            xReturn = x_Task_Check_For_زمان_بیرون( px_زمان_بیرون, px_Ticks_مقصد_Wait );
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_Task_Check_For_زمان_بیرون( px_زمان_بیرون, px_Ticks_مقصد_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        پایه_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_مقصد_Notify,
                                           UBaseType_t ux_شاخص_مقصد_Notify,
                                           uint32_t ul_مقدار,
                                           eNotifyAction eAction,
                                           uint32_t * pul_قبلی_Notification_مقدار ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = xTaskGenericNotify( x_Task_مقصد_Notify, ux_شاخص_مقصد_Notify, ul_مقدار, eAction, pul_قبلی_Notification_مقدار );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGenericNotify( x_Task_مقصد_Notify, ux_شاخص_مقصد_Notify, ul_مقدار, eAction, pul_قبلی_Notification_مقدار );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        پایه_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_شاخص_مقصد_Wait_On,
                                               uint32_t ul_بیتها_مقصد_Clear_On_مدخل,
                                               uint32_t ul_بیتها_مقصد_Clear_On_Exit,
                                               uint32_t * pul_Notification_مقدار,
                                               TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = xTaskGenericNotifyWait( ux_شاخص_مقصد_Wait_On, ul_بیتها_مقصد_Clear_On_مدخل, ul_بیتها_مقصد_Clear_On_Exit, pul_Notification_مقدار, x_Ticks_مقصد_Wait );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGenericNotifyWait( ux_شاخص_مقصد_Wait_On, ul_بیتها_مقصد_Clear_On_مدخل, ul_بیتها_مقصد_Clear_On_Exit, pul_Notification_مقدار, x_Ticks_مقصد_Wait );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_شاخص_مقصد_Wait_On,
                                              پایه_Type_t x_Clear_شمار_On_Exit,
                                              TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( ux_شاخص_مقصد_Wait_On, x_Clear_شمار_On_Exit, x_Ticks_مقصد_Wait );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                ulReturn = ulTaskGenericNotifyTake( ux_شاخص_مقصد_Wait_On, x_Clear_شمار_On_Exit, x_Ticks_مقصد_Wait );
            }

            أرجع ulReturn;
        }
    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        پایه_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_شاخص_مقصد_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, ux_شاخص_مقصد_Clear );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, ux_شاخص_مقصد_Clear );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ul_Task_Generic_Notify_مقدار_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_شاخص_مقصد_Clear,
                                                    uint32_t ul_بیتها_مقصد_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                ulReturn = ul_Task_Generic_Notify_مقدار_Clear( xTask, ux_شاخص_مقصد_Clear, ul_بیتها_مقصد_Clear );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                ulReturn = ul_Task_Generic_Notify_مقدار_Clear( xTask, ux_شاخص_مقصد_Clear, ul_بیتها_مقصد_Clear );
            }

            أرجع ulReturn;
        }
    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_تخصیص == 1 )
        صف_Handle_t MPU_x_صف_Generic_Create( UBaseType_t ux_صف_درازی,
                                               UBaseType_t ux_قلم_اندازه,
                                               uint8_t uc_صف_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            صف_Handle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_صف_Generic_Create( ux_صف_درازی, ux_قلم_اندازه, uc_صف_Type );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_صف_Generic_Create( ux_صف_درازی, ux_قلم_اندازه, uc_صف_Type );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_تخصیص == 1 )
        صف_Handle_t MPU_x_صف_Generic_Create_Static( ثابت UBaseType_t ux_صف_درازی,
                                                     ثابت UBaseType_t ux_قلم_اندازه,
                                                     uint8_t * puc_صف_Storage,
                                                     Static_صف_t * px_Static_صف,
                                                     ثابت uint8_t uc_صف_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            صف_Handle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_صف_Generic_Create_Static( ux_صف_درازی, ux_قلم_اندازه, puc_صف_Storage, px_Static_صف, uc_صف_Type );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_صف_Generic_Create_Static( ux_صف_درازی, ux_قلم_اندازه, puc_صف_Storage, px_Static_صف, uc_صف_Type );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Generic_Reset( صف_Handle_t px_صف,
                                       پایه_Type_t x_New_صف ) /* FREERTOS_SYSTEM_CALL */
    {
        پایه_Type_t xReturn;

        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            xReturn = x_صف_Generic_Reset( px_صف, x_New_صف );
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_صف_Generic_Reset( px_صف, x_New_صف );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Generic_Send( صف_Handle_t x_صف,
                                      ثابت فراغ * ثابت pv_قلم_مقصد_صف,
                                      TickType_t x_Ticks_مقصد_Wait,
                                      پایه_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        پایه_Type_t xReturn;

        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            xReturn = x_صف_Generic_Send( x_صف, pv_قلم_مقصد_صف, x_Ticks_مقصد_Wait, xCopyPosition );
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_صف_Generic_Send( x_صف, pv_قلم_مقصد_صف, x_Ticks_مقصد_Wait, xCopyPosition );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_صف_Messages_انتظار( ثابت صف_Handle_t px_صف ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            uxReturn = ux_صف_Messages_انتظار( px_صف );
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            uxReturn = ux_صف_Messages_انتظار( px_صف );
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_صف_Spaces_موجود( ثابت صف_Handle_t x_صف ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            uxReturn = ux_صف_Spaces_موجود( x_صف );
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            uxReturn = ux_صف_Spaces_موجود( x_صف );
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Receive( صف_Handle_t px_صف,
                                  فراغ * ثابت pv_میانگیر,
                                  TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        پایه_Type_t xReturn;

        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            xReturn = x_صف_Receive( px_صف, pv_میانگیر, x_Ticks_مقصد_Wait );
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_صف_Receive( px_صف, pv_میانگیر, x_Ticks_مقصد_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Peek( صف_Handle_t x_صف,
                               فراغ * ثابت pv_میانگیر,
                               TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        پایه_Type_t xReturn;

        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            xReturn = x_صف_Peek( x_صف, pv_میانگیر, x_Ticks_مقصد_Wait );
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_صف_Peek( x_صف, pv_میانگیر, x_Ticks_مقصد_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Semaphore_Take( صف_Handle_t x_صف,
                                        TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        پایه_Type_t xReturn;

        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            xReturn = x_صف_Semaphore_Take( x_صف, x_Ticks_مقصد_Wait );
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            xReturn = x_صف_Semaphore_Take( x_صف, x_Ticks_مقصد_Wait );
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_x_صف_Get_Mutex_Holder( صف_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            فراغ * xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_صف_Get_Mutex_Holder( xSemaphore );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_صف_Get_Mutex_Holder( xSemaphore );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )
        صف_Handle_t MPU_x_صف_Create_Mutex( ثابت uint8_t uc_صف_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            صف_Handle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_صف_Create_Mutex( uc_صف_Type );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_صف_Create_Mutex( uc_صف_Type );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_تخصیص == 1 ) )
        صف_Handle_t MPU_x_صف_Create_Mutex_Static( ثابت uint8_t uc_صف_Type,
                                                   Static_صف_t * px_Static_صف ) /* FREERTOS_SYSTEM_CALL */
        {
            صف_Handle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_صف_Create_Mutex_Static( uc_صف_Type, px_Static_صف );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_صف_Create_Mutex_Static( uc_صف_Type, px_Static_صف );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )
        صف_Handle_t MPU_x_صف_Create_Counting_Semaphore( UBaseType_t ux_شمار_مقدار,
                                                         UBaseType_t ux_Initial_شمار ) /* FREERTOS_SYSTEM_CALL */
        {
            صف_Handle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_صف_Create_Counting_Semaphore( ux_شمار_مقدار, ux_Initial_شمار );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_صف_Create_Counting_Semaphore( ux_شمار_مقدار, ux_Initial_شمار );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_تخصیص == 1 ) )

        صف_Handle_t MPU_x_صف_Create_Counting_Semaphore_Static( ثابت UBaseType_t ux_Max_شمار,
                                                               ثابت UBaseType_t ux_Initial_شمار,
                                                               Static_صف_t * px_Static_صف ) /* FREERTOS_SYSTEM_CALL */
        {
            صف_Handle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_صف_Create_Counting_Semaphore_Static( ux_Max_شمار, ux_Initial_شمار, px_Static_صف );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_صف_Create_Counting_Semaphore_Static( ux_Max_شمار, ux_Initial_شمار, px_Static_صف );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )
        پایه_Type_t MPU_x_صف_Take_Mutex_Recursive( صف_Handle_t xMutex,
                                                 TickType_t x_بلوک_زمان ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_صف_Take_Mutex_Recursive( xMutex, x_بلوک_زمان );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_صف_Take_Mutex_Recursive( xMutex, x_بلوک_زمان );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )
        پایه_Type_t MPU_x_صف_Give_Mutex_Recursive( صف_Handle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_صف_Give_Mutex_Recursive( xMutex );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_صف_Give_Mutex_Recursive( xMutex );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_صف_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )
        صف_مجموعه_Handle_t MPU_x_صف_Create_مجموعه( UBaseType_t ux_Event_صف_درازی ) /* FREERTOS_SYSTEM_CALL */
        {
            صف_مجموعه_Handle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_صف_Create_مجموعه( ux_Event_صف_درازی );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_صف_Create_مجموعه( ux_Event_صف_درازی );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_صف_SETS == 1 ) && ( config_SUPPORT_STATIC_تخصیص == 1 ) )
        صف_مجموعه_Handle_t MPU_x_صف_Create_مجموعه_Static( ثابت UBaseType_t ux_Event_صف_درازی,
                                                    uint8_t * puc_صف_Storage,
                                                    Static_صف_t * px_Static_صف ) /* FREERTOS_SYSTEM_CALL */
        {
            صف_مجموعه_Handle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_صف_Create_مجموعه_Static( ux_Event_صف_درازی, puc_صف_Storage, px_Static_صف );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_صف_Create_مجموعه_Static( ux_Event_صف_درازی, puc_صف_Storage, px_Static_صف );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_صف_SETS == 1 )
        صف_مجموعه_Member_Handle_t MPU_x_صف_Select_From_مجموعه( صف_مجموعه_Handle_t x_صف_مجموعه,
                                                        TickType_t x_بلوک_زمان_Ticks ) /* FREERTOS_SYSTEM_CALL */
        {
            صف_مجموعه_Member_Handle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_صف_Select_From_مجموعه( x_صف_مجموعه, x_بلوک_زمان_Ticks );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_صف_Select_From_مجموعه( x_صف_مجموعه, x_بلوک_زمان_Ticks );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_صف_SETS == 1 )
        پایه_Type_t MPU_x_صف_جمع_کن_مقصد_مجموعه( صف_مجموعه_Member_Handle_t x_صف_Or_Semaphore,
                                       صف_مجموعه_Handle_t x_صف_مجموعه ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_صف_جمع_کن_مقصد_مجموعه( x_صف_Or_Semaphore, x_صف_مجموعه );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_صف_جمع_کن_مقصد_مجموعه( x_صف_Or_Semaphore, x_صف_مجموعه );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_صف_SETS == 1 )
        پایه_Type_t MPU_x_صف_Remove_From_مجموعه( صف_مجموعه_Member_Handle_t x_صف_Or_Semaphore,
                                            صف_مجموعه_Handle_t x_صف_مجموعه ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_صف_Remove_From_مجموعه( x_صف_Or_Semaphore, x_صف_مجموعه );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_صف_Remove_From_مجموعه( x_صف_Or_Semaphore, x_صف_مجموعه );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا config_صف_REGISTRY_اندازه > 0
        فراغ MPU_v_صف_جمع_کن_مقصد_Registry( صف_Handle_t x_صف,
                                      ثابت حرف * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                v_صف_جمع_کن_مقصد_Registry( x_صف, pcName );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                v_صف_جمع_کن_مقصد_Registry( x_صف, pcName );
            }
        }
    #پایان_اگر /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_صف_REGISTRY_اندازه > 0
        فراغ MPU_v_صف_Unregister_صف( صف_Handle_t x_صف ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                v_صف_Unregister_صف( x_صف );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                v_صف_Unregister_صف( x_صف );
            }
        }
    #پایان_اگر /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_صف_REGISTRY_اندازه > 0
        ثابت حرف * MPU_pc_صف_Get_Name( صف_Handle_t x_صف ) /* FREERTOS_SYSTEM_CALL */
        {
            ثابت حرف * pcReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                pcReturn = pc_صف_Get_Name( x_صف );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                pcReturn = pc_صف_Get_Name( x_صف );
            }

            أرجع pcReturn;
        }
    #پایان_اگر /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    فراغ MPU_v_صف_Delete( صف_Handle_t x_صف ) /* FREERTOS_SYSTEM_CALL */
    {
        إذا( پورت_IS_PRIVILEGED() == pdFALSE )
        {
            پورت_RAISE_PRIVILEGE();
            پورت_حافظه_BARRIER();

            v_صف_Delete( x_صف );
            پورت_حافظه_BARRIER();

            پورت_RESET_PRIVILEGE();
            پورت_حافظه_BARRIER();
        }
        وإلا
        {
            v_صف_Delete( x_صف );
        }
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        فراغ * MPU_pvTimerGetTimerID( ثابت TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            فراغ * pvReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                pvReturn = pvTimerGetTimerID( xTimer );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                pvReturn = pvTimerGetTimerID( xTimer );
            }

            أرجع pvReturn;
        }
    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        فراغ MPU_v_Timer_مجموعه_Timer_ID( TimerHandle_t xTimer,
                                   فراغ * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                v_Timer_مجموعه_Timer_ID( xTimer, pvNewID );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                v_Timer_مجموعه_Timer_ID( xTimer, pvNewID );
            }
        }
    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        پایه_Type_t MPU_x_Timer_Is_Timer_فعال( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_Timer_Is_Timer_فعال( xTimer );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Timer_Is_Timer_فعال( xTimer );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = xTimerGetTimerDaemonTaskHandle();
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTimerGetTimerDaemonTaskHandle();
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        فراغ MPU_v_Timer_مجموعه_Reload_نما( TimerHandle_t xTimer,
                                      ثابت پایه_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                v_Timer_مجموعه_Reload_نما( xTimer, xAutoReload );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                v_Timer_مجموعه_Reload_نما( xTimer, xAutoReload );
            }
        }
    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_ux_Timer_Get_Reload_نما( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                uxReturn = ux_Timer_Get_Reload_نما( xTimer );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                uxReturn = ux_Timer_Get_Reload_نما( xTimer );
            }

            أرجع uxReturn;
        }
    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        ثابت حرف * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ثابت حرف * pcReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                pcReturn = pcTimerGetName( xTimer );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                pcReturn = pcTimerGetName( xTimer );
            }

            أرجع pcReturn;
        }
    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = xTimerGetPeriod( xTimer );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTimerGetPeriod( xTimer );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        TickType_t MPU_x_Timer_Get_Expiry_زمان( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_Timer_Get_Expiry_زمان( xTimer );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Timer_Get_Expiry_زمان( xTimer );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )
        پایه_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ثابت پایه_Type_t xCommandID,
                                                     ثابت TickType_t x_Optional_مقدار,
                                                     پایه_Type_t * ثابت px_Higher_اولویت_Task_Woken,
                                                     ثابت TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_مقدار, px_Higher_اولویت_Task_Woken, x_Ticks_مقصد_Wait );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_مقدار, px_Higher_اولویت_Task_Woken, x_Ticks_مقصد_Wait );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_گروه_Handle_t MPU_x_Event_گروه_Create( فراغ ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_گروه_Handle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_Event_گروه_Create();
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروه_Create();
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_گروه_Handle_t MPU_x_Event_گروه_Create_Static( Static_Event_گروه_t * px_Event_گروه_میانگیر ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_گروه_Handle_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_Event_گروه_Create_Static( px_Event_گروه_میانگیر );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروه_Create_Static( px_Event_گروه_میانگیر );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بیتها_t MPU_x_Event_گروه_Wait_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                             ثابت Event_بیتها_t ux_بیتها_مقصد_Wait_For,
                                             ثابت پایه_Type_t xClearOnExit,
                                             ثابت پایه_Type_t x_Wait_For_All_بیتها,
                                             TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بیتها_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_Event_گروه_Wait_بیتها( x_Event_گروه, ux_بیتها_مقصد_Wait_For, xClearOnExit, x_Wait_For_All_بیتها, x_Ticks_مقصد_Wait );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروه_Wait_بیتها( x_Event_گروه, ux_بیتها_مقصد_Wait_For, xClearOnExit, x_Wait_For_All_بیتها, x_Ticks_مقصد_Wait );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بیتها_t MPU_x_Event_گروه_Clear_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                              ثابت Event_بیتها_t ux_بیتها_مقصد_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بیتها_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_Event_گروه_Clear_بیتها( x_Event_گروه, ux_بیتها_مقصد_Clear );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروه_Clear_بیتها( x_Event_گروه, ux_بیتها_مقصد_Clear );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بیتها_t MPU_x_Event_گروه_مجموعه_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                            ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بیتها_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_Event_گروه_مجموعه_بیتها( x_Event_گروه, ux_بیتها_مقصد_مجموعه );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروه_مجموعه_بیتها( x_Event_گروه, ux_بیتها_مقصد_مجموعه );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        Event_بیتها_t MPU_x_Event_گروه_Sync( Event_گروه_Handle_t x_Event_گروه,
                                         ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه,
                                         ثابت Event_بیتها_t ux_بیتها_مقصد_Wait_For,
                                         TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بیتها_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_Event_گروه_Sync( x_Event_گروه, ux_بیتها_مقصد_مجموعه, ux_بیتها_مقصد_Wait_For, x_Ticks_مقصد_Wait );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_Event_گروه_Sync( x_Event_گروه, ux_بیتها_مقصد_مجموعه, ux_بیتها_مقصد_Wait_For, x_Ticks_مقصد_Wait );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )
        فراغ MPU_v_Event_گروه_Delete( Event_گروه_Handle_t x_Event_گروه ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                v_Event_گروه_Delete( x_Event_گروه );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                v_Event_گروه_Delete( x_Event_گروه );
            }
        }
    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )
        size_t MPU_x_جریان_میانگیر_Send( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                      ثابت فراغ * pv_Tx_داده,
                                      size_t x_داده_درازی_بایتها,
                                      TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_جریان_میانگیر_Send( x_جریان_میانگیر, pv_Tx_داده, x_داده_درازی_بایتها, x_Ticks_مقصد_Wait );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_جریان_میانگیر_Send( x_جریان_میانگیر, pv_Tx_داده, x_داده_درازی_بایتها, x_Ticks_مقصد_Wait );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )
        size_t MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_جریان_میانگیر_بعدی_پیام_درازی_بایتها( x_جریان_میانگیر );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_جریان_میانگیر_بعدی_پیام_درازی_بایتها( x_جریان_میانگیر );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )
        size_t MPU_x_جریان_میانگیر_Receive( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                         فراغ * pv_Rx_داده,
                                         size_t x_میانگیر_درازی_بایتها,
                                         TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_جریان_میانگیر_Receive( x_جریان_میانگیر, pv_Rx_داده, x_میانگیر_درازی_بایتها, x_Ticks_مقصد_Wait );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_جریان_میانگیر_Receive( x_جریان_میانگیر, pv_Rx_داده, x_میانگیر_درازی_بایتها, x_Ticks_مقصد_Wait );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )
        فراغ MPU_v_جریان_میانگیر_Delete( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* FREERTOS_SYSTEM_CALL */
        {
            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                v_جریان_میانگیر_Delete( x_جریان_میانگیر );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                v_جریان_میانگیر_Delete( x_جریان_میانگیر );
            }
        }
    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )
        پایه_Type_t MPU_x_جریان_میانگیر_Is_پر( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_جریان_میانگیر_Is_پر( x_جریان_میانگیر );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_جریان_میانگیر_Is_پر( x_جریان_میانگیر );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )
        پایه_Type_t MPU_x_جریان_میانگیر_Is_خالی( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_جریان_میانگیر_Is_خالی( x_جریان_میانگیر );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_جریان_میانگیر_Is_خالی( x_جریان_میانگیر );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )
        پایه_Type_t MPU_x_جریان_میانگیر_Reset( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_جریان_میانگیر_Reset( x_جریان_میانگیر );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_جریان_میانگیر_Reset( x_جریان_میانگیر );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )
        size_t MPU_x_جریان_میانگیر_Spaces_موجود( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();
                xReturn = x_جریان_میانگیر_Spaces_موجود( x_جریان_میانگیر );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_جریان_میانگیر_Spaces_موجود( x_جریان_میانگیر );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )
        size_t MPU_x_جریان_میانگیر_بایتها_موجود( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_جریان_میانگیر_بایتها_موجود( x_جریان_میانگیر );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_جریان_میانگیر_بایتها_موجود( x_جریان_میانگیر );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )
        پایه_Type_t MPU_x_جریان_میانگیر_مجموعه_Trigger_Level( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                                     size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn;

            إذا( پورت_IS_PRIVILEGED() == pdFALSE )
            {
                پورت_RAISE_PRIVILEGE();
                پورت_حافظه_BARRIER();

                xReturn = x_جریان_میانگیر_مجموعه_Trigger_Level( x_جریان_میانگیر, xTriggerLevel );
                پورت_حافظه_BARRIER();

                پورت_RESET_PRIVILEGE();
                پورت_حافظه_BARRIER();
            }
            وإلا
            {
                xReturn = x_جریان_میانگیر_مجموعه_Trigger_Level( x_جریان_میانگیر, xTriggerLevel );
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) && ( config_USE_جریان_BUFFERS == 1 ) )
        جریان_میانگیر_Handle_t MPU_x_جریان_میانگیر_Generic_Create( size_t x_میانگیر_اندازه_بایتها,
                                                             size_t x_Trigger_Level_بایتها,
                                                             پایه_Type_t x_جریان_میانگیر_Type,
                                                             جریان_میانگیر_Callback_Function_t pxSendCompletedCallback,
                                                             جریان_میانگیر_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            جریان_میانگیر_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == عدم ) &&
                          ( pxReceiveCompletedCallback == عدم ) );

            إذا( ( pxSendCompletedCallback == عدم ) &&
                ( pxReceiveCompletedCallback == عدم ) )
            {
                إذا( پورت_IS_PRIVILEGED() == pdFALSE )
                {
                    پورت_RAISE_PRIVILEGE();
                    پورت_حافظه_BARRIER();

                    xReturn = x_جریان_میانگیر_Generic_Create( x_میانگیر_اندازه_بایتها,
                                                          x_Trigger_Level_بایتها,
                                                          x_جریان_میانگیر_Type,
                                                          عدم,
                                                          عدم );
                    پورت_حافظه_BARRIER();

                    پورت_RESET_PRIVILEGE();
                    پورت_حافظه_BARRIER();
                }
                وإلا
                {
                    xReturn = x_جریان_میانگیر_Generic_Create( x_میانگیر_اندازه_بایتها,
                                                          x_Trigger_Level_بایتها,
                                                          x_جریان_میانگیر_Type,
                                                          عدم,
                                                          عدم );
                }
            }
            وإلا
            {
                trace_جریان_میانگیر_CREATE_FAILED( x_جریان_میانگیر_Type );
                xReturn = عدم;
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( config_USE_جریان_BUFFERS == 1 ) )
        جریان_میانگیر_Handle_t MPU_x_جریان_میانگیر_Generic_Create_Static( size_t x_میانگیر_اندازه_بایتها,
                                                                   size_t x_Trigger_Level_بایتها,
                                                                   پایه_Type_t x_جریان_میانگیر_Type,
                                                                   uint8_t * ثابت puc_جریان_میانگیر_Storage_Area,
                                                                   Static_جریان_میانگیر_t * ثابت px_Static_جریان_میانگیر,
                                                                   جریان_میانگیر_Callback_Function_t pxSendCompletedCallback,
                                                                   جریان_میانگیر_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            جریان_میانگیر_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == عدم ) &&
                          ( pxReceiveCompletedCallback == عدم ) );

            إذا( ( pxSendCompletedCallback == عدم ) &&
                ( pxReceiveCompletedCallback == عدم ) )
            {
                إذا( پورت_IS_PRIVILEGED() == pdFALSE )
                {
                    پورت_RAISE_PRIVILEGE();
                    پورت_حافظه_BARRIER();

                    xReturn = x_جریان_میانگیر_Generic_Create_Static( x_میانگیر_اندازه_بایتها,
                                                                x_Trigger_Level_بایتها,
                                                                x_جریان_میانگیر_Type,
                                                                puc_جریان_میانگیر_Storage_Area,
                                                                px_Static_جریان_میانگیر,
                                                                عدم,
                                                                عدم );
                    پورت_حافظه_BARRIER();

                    پورت_RESET_PRIVILEGE();
                    پورت_حافظه_BARRIER();
                }
                وإلا
                {
                    xReturn = x_جریان_میانگیر_Generic_Create_Static( x_میانگیر_اندازه_بایتها,
                                                                x_Trigger_Level_بایتها,
                                                                x_جریان_میانگیر_Type,
                                                                puc_جریان_میانگیر_Storage_Area,
                                                                px_Static_جریان_میانگیر,
                                                                عدم,
                                                                عدم );
                }
            }
            وإلا
            {
                trace_جریان_میانگیر_CREATE_STATIC_FAILED( xReturn, x_جریان_میانگیر_Type );
                xReturn = عدم;
            }

            أرجع xReturn;
        }
    #پایان_اگر /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
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
    #پایان_اگر
/*-----------------------------------------------------------*/

#پایان_اگر /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
