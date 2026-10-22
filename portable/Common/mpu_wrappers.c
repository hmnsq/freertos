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
#परिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "queue.h"
#अन्तर्भाव "timers.h"
#अन्तर्भाव "event_groups.h"
#अन्तर्भाव "stream_buffer.h"
#अन्तर्भाव "mpu_prototypes.h"

#अपरिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#यदि ( ( पत्तनम्_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #दोषः Access control list is not उपलब्धम् with this MPU wrapper. Please समुच्चयः configENABLE_ACCESS_CONTROL_LIST गन्तव्यम् 0.
    #यदि_अन्तः

    #यदि ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 )
        आधारः_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_संहिता,
                                    ध्रुव वर्ण * ध्रुव pcName,
                                    ध्रुव config_राशिः_गभीरता_TYPE ux_राशिः_गभीरता,
                                    शून्य * pvParameters,
                                    UBaseType_t ux_प्राथमिकता,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                ux_प्राथमिकता = ux_प्राथमिकता & ~( पत्तनम्_PRIVILEGE_BIT );
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xTaskCreate( pv_Task_संहिता, pcName, ux_राशिः_गभीरता, pvParameters, ux_प्राथमिकता, pxCreatedTask );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskCreate( pv_Task_संहिता, pcName, ux_राशिः_गभीरता, pvParameters, ux_प्राथमिकता, pxCreatedTask );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #यदि ( config_SUPPORT_STATIC_आवण्टनम् == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_संहिता,
                                            ध्रुव वर्ण * ध्रुव pcName,
                                            ध्रुव config_राशिः_गभीरता_TYPE ux_राशिः_गभीरता,
                                            शून्य * ध्रुव pvParameters,
                                            UBaseType_t ux_प्राथमिकता,
                                            राशिः_Type_t * ध्रुव pux_राशिः_बफर,
                                            StaticTask_t * ध्रुव px_Task_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                ux_प्राथमिकता = ux_प्राथमिकता & ~( पत्तनम्_PRIVILEGE_BIT );
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xTaskCreateStatic( px_Task_संहिता, pcName, ux_राशिः_गभीरता, pvParameters, ux_प्राथमिकता, pux_राशिः_बफर, px_Task_बफर );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskCreateStatic( px_Task_संहिता, pcName, ux_राशिः_गभीरता, pvParameters, ux_प्राथमिकता, pux_राशिः_बफर, px_Task_बफर );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskDelete == 1 )
        शून्य MPU_vTaskDelete( TaskHandle_t px_Task_गन्तव्यम्_Delete ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                vTaskDelete( px_Task_गन्तव्यम्_Delete );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                vTaskDelete( px_Task_गन्तव्यम्_Delete );
            }
        }
    #यदि_अन्तः /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskDelayUntil == 1 )
        आधारः_Type_t MPU_xTaskDelayUntil( TickType_t * ध्रुव pxPreviousWakeTime,
                                        TickType_t xTimeIncrement ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskAbortDelay == 1 )
        आधारः_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xTaskAbortDelay( xTask );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskAbortDelay( xTask );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskDelay == 1 )
        शून्य MPU_vTaskDelay( TickType_t x_Ticks_गन्तव्यम्_Delay ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                vTaskDelay( x_Ticks_गन्तव्यम्_Delay );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                vTaskDelay( x_Ticks_गन्तव्यम्_Delay );
            }
        }
    #यदि_अन्तः /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_प्राथमिकता_Get == 1 )
        UBaseType_t MPU_ux_Task_प्राथमिकता_Get( ध्रुव TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                uxReturn = ux_Task_प्राथमिकता_Get( pxTask );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                uxReturn = ux_Task_प्राथमिकता_Get( pxTask );
            }

            प्रत्यागम uxReturn;
        }
    #यदि_अन्तः /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_v_Task_प्राथमिकता_समुच्चयः == 1 )
        शून्य MPU_v_Task_प्राथमिकता_समुच्चयः( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_प्राथमिकता ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                v_Task_प्राथमिकता_समुच्चयः( pxTask, ux_New_प्राथमिकता );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                v_Task_प्राथमिकता_समुच्चयः( pxTask, ux_New_प्राथमिकता );
            }
        }
    #यदि_अन्तः /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                eReturn = eTaskGetState( pxTask );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                eReturn = eTaskGetState( pxTask );
            }

            प्रत्यागम eReturn;
        }
    #यदि_अन्तः /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TRACE_FACILITY == 1 )
        शून्य MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_स्थितिः_t * px_Task_स्थितिः,
                               आधारः_Type_t x_Get_Free_राशिः_Space,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                vTaskGetInfo( xTask, px_Task_स्थितिः, x_Get_Free_राशिः_Space, eState );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                vTaskGetInfo( xTask, px_Task_स्थितिः, x_Get_Free_राशिः_Space, eState );
            }
        }
    #यदि_अन्तः /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( शून्य ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
                xReturn = xTaskGetIdleTaskHandle();
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGetIdleTaskHandle();
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskSuspend == 1 )
        शून्य MPU_vTaskSuspend( TaskHandle_t px_Task_गन्तव्यम्_Suspend ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                vTaskSuspend( px_Task_गन्तव्यम्_Suspend );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                vTaskSuspend( px_Task_गन्तव्यम्_Suspend );
            }
        }
    #यदि_अन्तः /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskSuspend == 1 )
        शून्य MPU_vTaskResume( TaskHandle_t px_Task_गन्तव्यम्_Resume ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                vTaskResume( px_Task_गन्तव्यम्_Resume );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                vTaskResume( px_Task_गन्तव्यम्_Resume );
            }
        }
    #यदि_अन्तः /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    शून्य MPU_vTaskSuspendAll( शून्य ) /* FREERTOS_SYSTEM_CALL */
    {
        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            vTaskSuspendAll();
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            vTaskSuspendAll();
        }
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xTaskResumeAll( शून्य ) /* FREERTOS_SYSTEM_CALL */
    {
        आधारः_Type_t xReturn;

        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            xReturn = xTaskResumeAll();
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            xReturn = xTaskResumeAll();
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_गणनम्( शून्य ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            xReturn = x_Task_Get_Tick_गणनम्();
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            xReturn = x_Task_Get_Tick_गणनम्();
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks( शून्य ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            uxReturn = ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks();
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            uxReturn = ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks();
        }

        प्रत्यागम uxReturn;
    }
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( ध्रुव वर्ण * pc_Name_गन्तव्यम्_Query ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xTaskGetHandle( pc_Name_गन्तव्यम्_Query );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGetHandle( pc_Name_गन्तव्यम्_Query );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 ) )
        शून्य MPU_vTaskListTasks( वर्ण * pc_Write_बफर,
                                 size_t ux_बफर_दीर्घता ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                vTaskListTasks( pc_Write_बफर, ux_बफर_दीर्घता );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                vTaskListTasks( pc_Write_बफर, ux_बफर_दीर्घता );
            }
        }
    #यदि_अन्तः /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_GENERATE_सततम्_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 ) )
        शून्य MPU_v_Task_Get_सततम्_Time_Statistics( वर्ण * pc_Write_बफर,
                                            size_t ux_बफर_दीर्घता ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                v_Task_Get_सततम्_Time_Statistics( pc_Write_बफर, ux_बफर_दीर्घता );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                v_Task_Get_सततम्_Time_Statistics( pc_Write_बफर, ux_बफर_दीर्घता );
            }
        }
    #यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_GENERATE_सततम्_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_Percent( शून्य ) /* FREERTOS_SYSTEM_CALL */
        {
            config_सततम्_TIME_गणक_TYPE xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = ul_Task_Get_Idle_सततम्_Time_Percent();
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = ul_Task_Get_Idle_सततम्_Time_Percent();
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_GENERATE_सततम्_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_गणक( शून्य ) /* FREERTOS_SYSTEM_CALL */
        {
            config_सततम्_TIME_गणक_TYPE xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = ul_Task_Get_Idle_सततम्_Time_गणक();
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = ul_Task_Get_Idle_सततम्_Time_गणक();
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_APPLICATION_TASK_चिह्नकम् == 1 )
        शून्य MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्( TaskHandle_t xTask,
                                             TaskHookFunction_t px_चिह्नकम्_मानम् ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                v_Task_समुच्चयः_Application_Task_चिह्नकम्( xTask, px_चिह्नकम्_मानम् );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                v_Task_समुच्चयः_Application_Task_चिह्नकम्( xTask, px_चिह्नकम्_मानम् );
            }
        }
    #यदि_अन्तः /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_APPLICATION_TASK_चिह्नकम् == 1 )
        TaskHookFunction_t MPU_x_Task_Get_Application_Task_चिह्नकम्( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_Task_Get_Application_Task_चिह्नकम्( xTask );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Task_Get_Application_Task_चिह्नकम्( xTask );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_अङ्कः_THREAD_LOCAL_STORAGE_सूचकाः != 0 )
        शून्य MPU_v_Task_समुच्चयः_Thread_Local_Storage_Pointer( TaskHandle_t x_Task_गन्तव्यम्_समुच्चयः,
                                                    आधारः_Type_t x_सूचकांक,
                                                    शून्य * pv_मानम् ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                v_Task_समुच्चयः_Thread_Local_Storage_Pointer( x_Task_गन्तव्यम्_समुच्चयः, x_सूचकांक, pv_मानम् );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                v_Task_समुच्चयः_Thread_Local_Storage_Pointer( x_Task_गन्तव्यम्_समुच्चयः, x_सूचकांक, pv_मानम् );
            }
        }
    #यदि_अन्तः /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_अङ्कः_THREAD_LOCAL_STORAGE_सूचकाः != 0 )
        शून्य * MPU_pvTaskGetThreadLocalStoragePointer( TaskHandle_t x_Task_गन्तव्यम्_Query,
                                                       आधारः_Type_t x_सूचकांक ) /* FREERTOS_SYSTEM_CALL */
        {
            शून्य * pvReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                pvReturn = pvTaskGetThreadLocalStoragePointer( x_Task_गन्तव्यम्_Query, x_सूचकांक );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                pvReturn = pvTaskGetThreadLocalStoragePointer( x_Task_गन्तव्यम्_Query, x_सूचकांक );
            }

            प्रत्यागम pvReturn;
        }
    #यदि_अन्तः /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_APPLICATION_TASK_चिह्नकम् == 1 )
        आधारः_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     शून्य * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( Task_स्थितिः_t * px_Task_स्थितिः_Array,
                                              UBaseType_t ux_Array_आकार,
                                              config_सततम्_TIME_गणक_TYPE * pul_योग_सततम्_Time ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                uxReturn = uxTaskGetSystemState( px_Task_स्थितिः_Array, ux_Array_आकार, pul_योग_सततम्_Time );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                uxReturn = uxTaskGetSystemState( px_Task_स्थितिः_Array, ux_Array_आकार, pul_योग_सततम्_Time );
            }

            प्रत्यागम uxReturn;
        }
    #यदि_अन्तः /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_x_Task_Catch_ऊर्ध्वम्_Ticks( TickType_t x_Ticks_गन्तव्यम्_Catch_ऊर्ध्वम् ) /* FREERTOS_SYSTEM_CALL */
    {
        आधारः_Type_t xReturn;

        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            xReturn = x_Task_Catch_ऊर्ध्वम्_Ticks( x_Ticks_गन्तव्यम्_Catch_ऊर्ध्वम् );
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            xReturn = x_Task_Catch_ऊर्ध्वम्_Ticks( x_Ticks_गन्तव्यम्_Catch_ऊर्ध्वम् );
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_Get_राशिः_उच्चः_Water_Mark == 1 )
        UBaseType_t MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                uxReturn = ux_Task_Get_राशिः_उच्चः_Water_Mark( xTask );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                uxReturn = ux_Task_Get_राशिः_उच्चः_Water_Mark( xTask );
            }

            प्रत्यागम uxReturn;
        }
    #यदि_अन्तः /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_Get_राशिः_उच्चः_Water_Mark2 == 1 )
        config_राशिः_गभीरता_TYPE MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            config_राशिः_गभीरता_TYPE uxReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                uxReturn = ux_Task_Get_राशिः_उच्चः_Water_Mark2( xTask );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                uxReturn = ux_Task_Get_राशिः_उच्चः_Water_Mark2( xTask );
            }

            प्रत्यागम uxReturn;
        }
    #यदि_अन्तः /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( शून्य ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
                xReturn = xTaskGetCurrentTaskHandle();
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGetCurrentTaskHandle();
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskGetSchedulerState == 1 )
        आधारः_Type_t MPU_xTaskGetSchedulerState( शून्य ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xTaskGetSchedulerState();
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGetSchedulerState();
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    शून्य MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम् ) /* FREERTOS_SYSTEM_CALL */
    {
        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            v_Task_समुच्चयः_Time_बहिर्गमनम्_State( px_Time_बहिर्गमनम् );
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            v_Task_समुच्चयः_Time_बहिर्गमनम्_State( px_Time_बहिर्गमनम् );
        }
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_x_Task_Check_For_Time_बहिर्गमनम्( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम्,
                                         TickType_t * ध्रुव px_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        आधारः_Type_t xReturn;

        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            xReturn = x_Task_Check_For_Time_बहिर्गमनम्( px_Time_बहिर्गमनम्, px_Ticks_गन्तव्यम्_Wait );
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            xReturn = x_Task_Check_For_Time_बहिर्गमनम्( px_Time_बहिर्गमनम्, px_Ticks_गन्तव्यम्_Wait );
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )
        आधारः_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_गन्तव्यम्_Notify,
                                           UBaseType_t ux_सूचकांक_गन्तव्यम्_Notify,
                                           uint32_t ul_मानम्,
                                           eNotifyAction eAction,
                                           uint32_t * pul_Previous_Notification_मानम् ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xTaskGenericNotify( x_Task_गन्तव्यम्_Notify, ux_सूचकांक_गन्तव्यम्_Notify, ul_मानम्, eAction, pul_Previous_Notification_मानम् );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGenericNotify( x_Task_गन्तव्यम्_Notify, ux_सूचकांक_गन्तव्यम्_Notify, ul_मानम्, eAction, pul_Previous_Notification_मानम् );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )
        आधारः_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_सूचकांक_गन्तव्यम्_Wait_On,
                                               uint32_t ul_द्वयङ्काः_गन्तव्यम्_Clear_On_प्रविष्टिः,
                                               uint32_t ul_द्वयङ्काः_गन्तव्यम्_Clear_On_Exit,
                                               uint32_t * pul_Notification_मानम्,
                                               TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xTaskGenericNotifyWait( ux_सूचकांक_गन्तव्यम्_Wait_On, ul_द्वयङ्काः_गन्तव्यम्_Clear_On_प्रविष्टिः, ul_द्वयङ्काः_गन्तव्यम्_Clear_On_Exit, pul_Notification_मानम्, x_Ticks_गन्तव्यम्_Wait );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGenericNotifyWait( ux_सूचकांक_गन्तव्यम्_Wait_On, ul_द्वयङ्काः_गन्तव्यम्_Clear_On_प्रविष्टिः, ul_द्वयङ्काः_गन्तव्यम्_Clear_On_Exit, pul_Notification_मानम्, x_Ticks_गन्तव्यम्_Wait );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_सूचकांक_गन्तव्यम्_Wait_On,
                                              आधारः_Type_t x_Clear_गणनम्_On_Exit,
                                              TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( ux_सूचकांक_गन्तव्यम्_Wait_On, x_Clear_गणनम्_On_Exit, x_Ticks_गन्तव्यम्_Wait );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                ulReturn = ulTaskGenericNotifyTake( ux_सूचकांक_गन्तव्यम्_Wait_On, x_Clear_गणनम्_On_Exit, x_Ticks_गन्तव्यम्_Wait );
            }

            प्रत्यागम ulReturn;
        }
    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )
        आधारः_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, ux_सूचकांक_गन्तव्यम्_Clear );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, ux_सूचकांक_गन्तव्यम्_Clear );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ul_Task_Generic_Notify_मानम्_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear,
                                                    uint32_t ul_द्वयङ्काः_गन्तव्यम्_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                ulReturn = ul_Task_Generic_Notify_मानम्_Clear( xTask, ux_सूचकांक_गन्तव्यम्_Clear, ul_द्वयङ्काः_गन्तव्यम्_Clear );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                ulReturn = ul_Task_Generic_Notify_मानम्_Clear( xTask, ux_सूचकांक_गन्तव्यम्_Clear, ul_द्वयङ्काः_गन्तव्यम्_Clear );
            }

            प्रत्यागम ulReturn;
        }
    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 )
        QueueHandle_t MPU_xQueueGenericCreate( UBaseType_t ux_Queue_दीर्घता,
                                               UBaseType_t ux_Item_आकार,
                                               uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xQueueGenericCreate( ux_Queue_दीर्घता, ux_Item_आकार, ucQueueType );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueGenericCreate( ux_Queue_दीर्घता, ux_Item_आकार, ucQueueType );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_SUPPORT_STATIC_आवण्टनम् == 1 )
        QueueHandle_t MPU_xQueueGenericCreateStatic( ध्रुव UBaseType_t ux_Queue_दीर्घता,
                                                     ध्रुव UBaseType_t ux_Item_आकार,
                                                     uint8_t * pucQueueStorage,
                                                     StaticQueue_t * pxStaticQueue,
                                                     ध्रुव uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xQueueGenericCreateStatic( ux_Queue_दीर्घता, ux_Item_आकार, pucQueueStorage, pxStaticQueue, ucQueueType );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueGenericCreateStatic( ux_Queue_दीर्घता, ux_Item_आकार, pucQueueStorage, pxStaticQueue, ucQueueType );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueGenericReset( QueueHandle_t pxQueue,
                                       आधारः_Type_t xNewQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        आधारः_Type_t xReturn;

        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            xReturn = xQueueGenericReset( pxQueue, xNewQueue );
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            xReturn = xQueueGenericReset( pxQueue, xNewQueue );
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueGenericSend( QueueHandle_t xQueue,
                                      ध्रुव शून्य * ध्रुव pv_Item_गन्तव्यम्_Queue,
                                      TickType_t x_Ticks_गन्तव्यम्_Wait,
                                      आधारः_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        आधारः_Type_t xReturn;

        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            xReturn = xQueueGenericSend( xQueue, pv_Item_गन्तव्यम्_Queue, x_Ticks_गन्तव्यम्_Wait, xCopyPosition );
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            xReturn = xQueueGenericSend( xQueue, pv_Item_गन्तव्यम्_Queue, x_Ticks_गन्तव्यम्_Wait, xCopyPosition );
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Queue_Messages_प्रतीक्षा( ध्रुव QueueHandle_t pxQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            uxReturn = ux_Queue_Messages_प्रतीक्षा( pxQueue );
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            uxReturn = ux_Queue_Messages_प्रतीक्षा( pxQueue );
        }

        प्रत्यागम uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Queue_Spaces_उपलब्धम्( ध्रुव QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            uxReturn = ux_Queue_Spaces_उपलब्धम्( xQueue );
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            uxReturn = ux_Queue_Spaces_उपलब्धम्( xQueue );
        }

        प्रत्यागम uxReturn;
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueReceive( QueueHandle_t pxQueue,
                                  शून्य * ध्रुव pv_बफर,
                                  TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        आधारः_Type_t xReturn;

        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            xReturn = xQueueReceive( pxQueue, pv_बफर, x_Ticks_गन्तव्यम्_Wait );
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            xReturn = xQueueReceive( pxQueue, pv_बफर, x_Ticks_गन्तव्यम्_Wait );
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueuePeek( QueueHandle_t xQueue,
                               शून्य * ध्रुव pv_बफर,
                               TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        आधारः_Type_t xReturn;

        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            xReturn = xQueuePeek( xQueue, pv_बफर, x_Ticks_गन्तव्यम्_Wait );
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            xReturn = xQueuePeek( xQueue, pv_बफर, x_Ticks_गन्तव्यम्_Wait );
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueSemaphoreTake( QueueHandle_t xQueue,
                                        TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        आधारः_Type_t xReturn;

        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            xReturn = xQueueSemaphoreTake( xQueue, x_Ticks_गन्तव्यम्_Wait );
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            xReturn = xQueueSemaphoreTake( xQueue, x_Ticks_गन्तव्यम्_Wait );
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_xQueueGetMutexHolder( QueueHandle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            शून्य * xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xQueueGetMutexHolder( xSemaphore );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueGetMutexHolder( xSemaphore );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 ) )
        QueueHandle_t MPU_xQueueCreateMutex( ध्रुव uint8_t ucQueueType ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xQueueCreateMutex( ucQueueType );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueCreateMutex( ucQueueType );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_आवण्टनम् == 1 ) )
        QueueHandle_t MPU_xQueueCreateMutexStatic( ध्रुव uint8_t ucQueueType,
                                                   StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 ) )
        QueueHandle_t MPU_xQueueCreateCountingSemaphore( UBaseType_t ux_गणनम्_मानम्,
                                                         UBaseType_t ux_Initial_गणनम् ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xQueueCreateCountingSemaphore( ux_गणनम्_मानम्, ux_Initial_गणनम् );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueCreateCountingSemaphore( ux_गणनम्_मानम्, ux_Initial_गणनम् );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_आवण्टनम् == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphoreStatic( ध्रुव UBaseType_t ux_Max_गणनम्,
                                                               ध्रुव UBaseType_t ux_Initial_गणनम्,
                                                               StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            QueueHandle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xQueueCreateCountingSemaphoreStatic( ux_Max_गणनम्, ux_Initial_गणनम्, pxStaticQueue );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueCreateCountingSemaphoreStatic( ux_Max_गणनम्, ux_Initial_गणनम्, pxStaticQueue );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_RECURSIVE_MUTEXES == 1 )
        आधारः_Type_t MPU_xQueueTakeMutexRecursive( QueueHandle_t xMutex,
                                                 TickType_t x_खण्डम्_Time ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xQueueTakeMutexRecursive( xMutex, x_खण्डम्_Time );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueTakeMutexRecursive( xMutex, x_खण्डम्_Time );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_RECURSIVE_MUTEXES == 1 )
        आधारः_Type_t MPU_xQueueGiveMutexRecursive( QueueHandle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xQueueGiveMutexRecursive( xMutex );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xQueueGiveMutexRecursive( xMutex );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_QUEUE_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 ) )
        Queue_समुच्चयः_Handle_t MPU_x_Queue_Create_समुच्चयः( UBaseType_t ux_Event_Queue_दीर्घता ) /* FREERTOS_SYSTEM_CALL */
        {
            Queue_समुच्चयः_Handle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_Queue_Create_समुच्चयः( ux_Event_Queue_दीर्घता );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Queue_Create_समुच्चयः( ux_Event_Queue_दीर्घता );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_QUEUE_SETS == 1 ) && ( config_SUPPORT_STATIC_आवण्टनम् == 1 ) )
        Queue_समुच्चयः_Handle_t MPU_x_Queue_Create_समुच्चयः_Static( ध्रुव UBaseType_t ux_Event_Queue_दीर्घता,
                                                    uint8_t * pucQueueStorage,
                                                    StaticQueue_t * pxStaticQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            Queue_समुच्चयः_Handle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_Queue_Create_समुच्चयः_Static( ux_Event_Queue_दीर्घता, pucQueueStorage, pxStaticQueue );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Queue_Create_समुच्चयः_Static( ux_Event_Queue_दीर्घता, pucQueueStorage, pxStaticQueue );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_QUEUE_SETS == 1 )
        Queue_समुच्चयः_Member_Handle_t MPU_x_Queue_Select_From_समुच्चयः( Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः,
                                                        TickType_t x_खण्डम्_Time_Ticks ) /* FREERTOS_SYSTEM_CALL */
        {
            Queue_समुच्चयः_Member_Handle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_Queue_Select_From_समुच्चयः( x_Queue_समुच्चयः, x_खण्डम्_Time_Ticks );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Queue_Select_From_समुच्चयः( x_Queue_समुच्चयः, x_खण्डम्_Time_Ticks );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_QUEUE_SETS == 1 )
        आधारः_Type_t MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः( Queue_समुच्चयः_Member_Handle_t xQueueOrSemaphore,
                                       Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः( xQueueOrSemaphore, x_Queue_समुच्चयः );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः( xQueueOrSemaphore, x_Queue_समुच्चयः );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_QUEUE_SETS == 1 )
        आधारः_Type_t MPU_x_Queue_Remove_From_समुच्चयः( Queue_समुच्चयः_Member_Handle_t xQueueOrSemaphore,
                                            Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_Queue_Remove_From_समुच्चयः( xQueueOrSemaphore, x_Queue_समुच्चयः );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Queue_Remove_From_समुच्चयः( xQueueOrSemaphore, x_Queue_समुच्चयः );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि config_QUEUE_REGISTRY_आकार > 0
        शून्य MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry( QueueHandle_t xQueue,
                                      ध्रुव वर्ण * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                v_Queue_सङ्कलय_गन्तव्यम्_Registry( xQueue, pcName );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                v_Queue_सङ्कलय_गन्तव्यम्_Registry( xQueue, pcName );
            }
        }
    #यदि_अन्तः /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #यदि config_QUEUE_REGISTRY_आकार > 0
        शून्य MPU_vQueueUnregisterQueue( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                vQueueUnregisterQueue( xQueue );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                vQueueUnregisterQueue( xQueue );
            }
        }
    #यदि_अन्तः /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #यदि config_QUEUE_REGISTRY_आकार > 0
        ध्रुव वर्ण * MPU_pcQueueGetName( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
        {
            ध्रुव वर्ण * pcReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                pcReturn = pcQueueGetName( xQueue );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                pcReturn = pcQueueGetName( xQueue );
            }

            प्रत्यागम pcReturn;
        }
    #यदि_अन्तः /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    शून्य MPU_vQueueDelete( QueueHandle_t xQueue ) /* FREERTOS_SYSTEM_CALL */
    {
        यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
        {
            पत्तनम्_RAISE_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();

            vQueueDelete( xQueue );
            पत्तनम्_स्मृतिः_BARRIER();

            पत्तनम्_RESET_PRIVILEGE();
            पत्तनम्_स्मृतिः_BARRIER();
        }
        अन्यथा
        {
            vQueueDelete( xQueue );
        }
    }
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        शून्य * MPU_pvTimerGetTimerID( ध्रुव TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            शून्य * pvReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                pvReturn = pvTimerGetTimerID( xTimer );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                pvReturn = pvTimerGetTimerID( xTimer );
            }

            प्रत्यागम pvReturn;
        }
    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        शून्य MPU_v_Timer_समुच्चयः_Timer_ID( TimerHandle_t xTimer,
                                   शून्य * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                v_Timer_समुच्चयः_Timer_ID( xTimer, pvNewID );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                v_Timer_समुच्चयः_Timer_ID( xTimer, pvNewID );
            }
        }
    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        आधारः_Type_t MPU_x_Timer_Is_Timer_सक्रिय( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_Timer_Is_Timer_सक्रिय( xTimer );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Timer_Is_Timer_सक्रिय( xTimer );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( शून्य ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xTimerGetTimerDaemonTaskHandle();
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTimerGetTimerDaemonTaskHandle();
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        शून्य MPU_v_Timer_समुच्चयः_Reload_बहुलकम्( TimerHandle_t xTimer,
                                      ध्रुव आधारः_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                v_Timer_समुच्चयः_Reload_बहुलकम्( xTimer, xAutoReload );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                v_Timer_समुच्चयः_Reload_बहुलकम्( xTimer, xAutoReload );
            }
        }
    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_ux_Timer_Get_Reload_बहुलकम्( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                uxReturn = ux_Timer_Get_Reload_बहुलकम्( xTimer );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                uxReturn = ux_Timer_Get_Reload_बहुलकम्( xTimer );
            }

            प्रत्यागम uxReturn;
        }
    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        ध्रुव वर्ण * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ध्रुव वर्ण * pcReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                pcReturn = pcTimerGetName( xTimer );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                pcReturn = pcTimerGetName( xTimer );
            }

            प्रत्यागम pcReturn;
        }
    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xTimerGetPeriod( xTimer );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTimerGetPeriod( xTimer );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetExpiryTime( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xTimerGetExpiryTime( xTimer );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTimerGetExpiryTime( xTimer );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )
        आधारः_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ध्रुव आधारः_Type_t xCommandID,
                                                     ध्रुव TickType_t x_Optional_मानम्,
                                                     आधारः_Type_t * ध्रुव px_Higher_प्राथमिकता_Task_Woken,
                                                     ध्रुव TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_मानम्, px_Higher_प्राथमिकता_Task_Woken, x_Ticks_गन्तव्यम्_Wait );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_मानम्, px_Higher_प्राथमिकता_Task_Woken, x_Ticks_गन्तव्यम्_Wait );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_गणः_Handle_t MPU_x_Event_गणः_Create( शून्य ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_गणः_Handle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_Event_गणः_Create();
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Event_गणः_Create();
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_SUPPORT_STATIC_आवण्टनम् == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_गणः_Handle_t MPU_x_Event_गणः_Create_Static( Static_Event_गणः_t * px_Event_गणः_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_गणः_Handle_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_Event_गणः_Create_Static( px_Event_गणः_बफर );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Event_गणः_Create_Static( px_Event_गणः_बफर );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )
        Event_द्वयङ्काः_t MPU_x_Event_गणः_Wait_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                             ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Wait_For,
                                             ध्रुव आधारः_Type_t xClearOnExit,
                                             ध्रुव आधारः_Type_t x_Wait_For_All_द्वयङ्काः,
                                             TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_द्वयङ्काः_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_Event_गणः_Wait_द्वयङ्काः( x_Event_गणः, ux_द्वयङ्काः_गन्तव्यम्_Wait_For, xClearOnExit, x_Wait_For_All_द्वयङ्काः, x_Ticks_गन्तव्यम्_Wait );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Event_गणः_Wait_द्वयङ्काः( x_Event_गणः, ux_द्वयङ्काः_गन्तव्यम्_Wait_For, xClearOnExit, x_Wait_For_All_द्वयङ्काः, x_Ticks_गन्तव्यम्_Wait );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )
        Event_द्वयङ्काः_t MPU_x_Event_गणः_Clear_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                              ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_द्वयङ्काः_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_Event_गणः_Clear_द्वयङ्काः( x_Event_गणः, ux_द्वयङ्काः_गन्तव्यम्_Clear );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Event_गणः_Clear_द्वयङ्काः( x_Event_गणः, ux_द्वयङ्काः_गन्तव्यम्_Clear );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )
        Event_द्वयङ्काः_t MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                            ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_द्वयङ्काः_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_Event_गणः_समुच्चयः_द्वयङ्काः( x_Event_गणः, ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Event_गणः_समुच्चयः_द्वयङ्काः( x_Event_गणः, ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )
        Event_द्वयङ्काः_t MPU_x_Event_गणः_Sync( Event_गणः_Handle_t x_Event_गणः,
                                         ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः,
                                         ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Wait_For,
                                         TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_द्वयङ्काः_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_Event_गणः_Sync( x_Event_गणः, ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः, ux_द्वयङ्काः_गन्तव्यम्_Wait_For, x_Ticks_गन्तव्यम्_Wait );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_Event_गणः_Sync( x_Event_गणः, ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः, ux_द्वयङ्काः_गन्तव्यम्_Wait_For, x_Ticks_गन्तव्यम्_Wait );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )
        शून्य MPU_v_Event_गणः_Delete( Event_गणः_Handle_t x_Event_गणः ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                v_Event_गणः_Delete( x_Event_गणः );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                v_Event_गणः_Delete( x_Event_गणः );
            }
        }
    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )
        size_t MPU_x_प्रवाहः_बफर_Send( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                      ध्रुव शून्य * pv_Tx_दत्त,
                                      size_t x_दत्त_दीर्घता_अष्टकानि,
                                      TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_प्रवाहः_बफर_Send( x_प्रवाहः_बफर, pv_Tx_दत्त, x_दत्त_दीर्घता_अष्टकानि, x_Ticks_गन्तव्यम्_Wait );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_प्रवाहः_बफर_Send( x_प्रवाहः_बफर, pv_Tx_दत्त, x_दत्त_दीर्घता_अष्टकानि, x_Ticks_गन्तव्यम्_Wait );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )
        size_t MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि( x_प्रवाहः_बफर );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि( x_प्रवाहः_बफर );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )
        size_t MPU_x_प्रवाहः_बफर_Receive( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                         शून्य * pv_Rx_दत्त,
                                         size_t x_बफर_दीर्घता_अष्टकानि,
                                         TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_प्रवाहः_बफर_Receive( x_प्रवाहः_बफर, pv_Rx_दत्त, x_बफर_दीर्घता_अष्टकानि, x_Ticks_गन्तव्यम्_Wait );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_प्रवाहः_बफर_Receive( x_प्रवाहः_बफर, pv_Rx_दत्त, x_बफर_दीर्घता_अष्टकानि, x_Ticks_गन्तव्यम्_Wait );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )
        शून्य MPU_v_प्रवाहः_बफर_Delete( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                v_प्रवाहः_बफर_Delete( x_प्रवाहः_बफर );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                v_प्रवाहः_बफर_Delete( x_प्रवाहः_बफर );
            }
        }
    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )
        आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_पूर्णम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_प्रवाहः_बफर_Is_पूर्णम्( x_प्रवाहः_बफर );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_प्रवाहः_बफर_Is_पूर्णम्( x_प्रवाहः_बफर );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )
        आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_रिक्तानि( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_प्रवाहः_बफर_Is_रिक्तानि( x_प्रवाहः_बफर );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_प्रवाहः_बफर_Is_रिक्तानि( x_प्रवाहः_बफर );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )
        आधारः_Type_t MPU_x_प्रवाहः_बफर_Reset( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_प्रवाहः_बफर_Reset( x_प्रवाहः_बफर );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_प्रवाहः_बफर_Reset( x_प्रवाहः_बफर );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )
        size_t MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
                xReturn = x_प्रवाहः_बफर_Spaces_उपलब्धम्( x_प्रवाहः_बफर );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_प्रवाहः_बफर_Spaces_उपलब्धम्( x_प्रवाहः_बफर );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )
        size_t MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्( x_प्रवाहः_बफर );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्( x_प्रवाहः_बफर );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )
        आधारः_Type_t MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                                     size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn;

            यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
            {
                पत्तनम्_RAISE_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();

                xReturn = x_प्रवाहः_बफर_समुच्चयः_Trigger_Level( x_प्रवाहः_बफर, xTriggerLevel );
                पत्तनम्_स्मृतिः_BARRIER();

                पत्तनम्_RESET_PRIVILEGE();
                पत्तनम्_स्मृतिः_BARRIER();
            }
            अन्यथा
            {
                xReturn = x_प्रवाहः_बफर_समुच्चयः_Trigger_Level( x_प्रवाहः_बफर, xTriggerLevel );
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 ) && ( config_USE_प्रवाहः_BUFFERS == 1 ) )
        प्रवाहः_बफर_Handle_t MPU_x_प्रवाहः_बफर_Generic_Create( size_t x_बफर_आकार_अष्टकानि,
                                                             size_t x_Trigger_Level_अष्टकानि,
                                                             आधारः_Type_t x_प्रवाहः_बफर_Type,
                                                             प्रवाहः_बफर_Callback_Function_t pxSendCompletedCallback,
                                                             प्रवाहः_बफर_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            प्रवाहः_बफर_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == रिक्त ) &&
                          ( pxReceiveCompletedCallback == रिक्त ) );

            यदि( ( pxSendCompletedCallback == रिक्त ) &&
                ( pxReceiveCompletedCallback == रिक्त ) )
            {
                यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
                {
                    पत्तनम्_RAISE_PRIVILEGE();
                    पत्तनम्_स्मृतिः_BARRIER();

                    xReturn = x_प्रवाहः_बफर_Generic_Create( x_बफर_आकार_अष्टकानि,
                                                          x_Trigger_Level_अष्टकानि,
                                                          x_प्रवाहः_बफर_Type,
                                                          रिक्त,
                                                          रिक्त );
                    पत्तनम्_स्मृतिः_BARRIER();

                    पत्तनम्_RESET_PRIVILEGE();
                    पत्तनम्_स्मृतिः_BARRIER();
                }
                अन्यथा
                {
                    xReturn = x_प्रवाहः_बफर_Generic_Create( x_बफर_आकार_अष्टकानि,
                                                          x_Trigger_Level_अष्टकानि,
                                                          x_प्रवाहः_बफर_Type,
                                                          रिक्त,
                                                          रिक्त );
                }
            }
            अन्यथा
            {
                trace_प्रवाहः_बफर_CREATE_FAILED( x_प्रवाहः_बफर_Type );
                xReturn = रिक्त;
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_SUPPORT_STATIC_आवण्टनम् == 1 ) && ( config_USE_प्रवाहः_BUFFERS == 1 ) )
        प्रवाहः_बफर_Handle_t MPU_x_प्रवाहः_बफर_Generic_Create_Static( size_t x_बफर_आकार_अष्टकानि,
                                                                   size_t x_Trigger_Level_अष्टकानि,
                                                                   आधारः_Type_t x_प्रवाहः_बफर_Type,
                                                                   uint8_t * ध्रुव puc_प्रवाहः_बफर_Storage_Area,
                                                                   Static_प्रवाहः_बफर_t * ध्रुव px_Static_प्रवाहः_बफर,
                                                                   प्रवाहः_बफर_Callback_Function_t pxSendCompletedCallback,
                                                                   प्रवाहः_बफर_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            प्रवाहः_बफर_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == रिक्त ) &&
                          ( pxReceiveCompletedCallback == रिक्त ) );

            यदि( ( pxSendCompletedCallback == रिक्त ) &&
                ( pxReceiveCompletedCallback == रिक्त ) )
            {
                यदि( पत्तनम्_IS_PRIVILEGED() == pdFALSE )
                {
                    पत्तनम्_RAISE_PRIVILEGE();
                    पत्तनम्_स्मृतिः_BARRIER();

                    xReturn = x_प्रवाहः_बफर_Generic_Create_Static( x_बफर_आकार_अष्टकानि,
                                                                x_Trigger_Level_अष्टकानि,
                                                                x_प्रवाहः_बफर_Type,
                                                                puc_प्रवाहः_बफर_Storage_Area,
                                                                px_Static_प्रवाहः_बफर,
                                                                रिक्त,
                                                                रिक्त );
                    पत्तनम्_स्मृतिः_BARRIER();

                    पत्तनम्_RESET_PRIVILEGE();
                    पत्तनम्_स्मृतिः_BARRIER();
                }
                अन्यथा
                {
                    xReturn = x_प्रवाहः_बफर_Generic_Create_Static( x_बफर_आकार_अष्टकानि,
                                                                x_Trigger_Level_अष्टकानि,
                                                                x_प्रवाहः_बफर_Type,
                                                                puc_प्रवाहः_बफर_Storage_Area,
                                                                px_Static_प्रवाहः_बफर,
                                                                रिक्त,
                                                                रिक्त );
                }
            }
            अन्यथा
            {
                trace_प्रवाहः_बफर_CREATE_STATIC_FAILED( xReturn, x_प्रवाहः_बफर_Type );
                xReturn = रिक्त;
            }

            प्रत्यागम xReturn;
        }
    #यदि_अन्तः /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
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

    #यदि configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #अन्तर्भाव "application_defined_privileged_functions.h"
    #यदि_अन्तः
/*-----------------------------------------------------------*/

#यदि_अन्तः /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
