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
#నిర్వచించు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "queue.h"
#అన్తర్భావ "timers.h"
#అన్తర్భావ "event_groups.h"
#అన్తర్భావ "stream_buffer.h"
#అన్తర్భావ "mpu_prototypes.h"

#నిర్వచనం_రద్దు MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( పోర్టు_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #ఒకవేళ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #దోషం Access control list is not అందుబాటు with this MPU wrapper. Please సమితి configENABLE_ACCESS_CONTROL_LIST గమ్యం 0.
    #అయితే_ముగింపు

    #ఒకవేళ ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 )
        పునాది_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_సంకేతం,
                                    స్థిరరాశి అక్షరం * స్థిరరాశి pcName,
                                    స్థిరరాశి config_దొంతర_లోతు_TYPE ux_దొంతర_లోతు,
                                    శూన్య * pvParameters,
                                    UBaseType_t ux_ప్రాధాన్యత,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                ux_ప్రాధాన్యత = ux_ప్రాధాన్యత & ~( పోర్టు_PRIVILEGE_బిట్టు );
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = xTaskCreate( pv_Task_సంకేతం, pcName, ux_దొంతర_లోతు, pvParameters, ux_ప్రాధాన్యత, pxCreatedTask );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTaskCreate( pv_Task_సంకేతం, pcName, ux_దొంతర_లోతు, pvParameters, ux_ప్రాధాన్యత, pxCreatedTask );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_SUPPORT_STATIC_కేటాయింపు == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_సంకేతం,
                                            స్థిరరాశి అక్షరం * స్థిరరాశి pcName,
                                            స్థిరరాశి config_దొంతర_లోతు_TYPE ux_దొంతర_లోతు,
                                            శూన్య * స్థిరరాశి pvParameters,
                                            UBaseType_t ux_ప్రాధాన్యత,
                                            దొంతర_Type_t * స్థిరరాశి pux_దొంతర_బఫరు,
                                            StaticTask_t * స్థిరరాశి px_Task_బఫరు ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                ux_ప్రాధాన్యత = ux_ప్రాధాన్యత & ~( పోర్టు_PRIVILEGE_బిట్టు );
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = xTaskCreateStatic( px_Task_సంకేతం, pcName, ux_దొంతర_లోతు, pvParameters, ux_ప్రాధాన్యత, pux_దొంతర_బఫరు, px_Task_బఫరు );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTaskCreateStatic( px_Task_సంకేతం, pcName, ux_దొంతర_లోతు, pvParameters, ux_ప్రాధాన్యత, pux_దొంతర_బఫరు, px_Task_బఫరు );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_vTaskDelete == 1 )
        శూన్య MPU_vTaskDelete( TaskHandle_t px_Task_గమ్యం_Delete ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                vTaskDelete( px_Task_గమ్యం_Delete );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                vTaskDelete( px_Task_గమ్యం_Delete );
            }
        }
    #అయితే_ముగింపు /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskDelayUntil == 1 )
        పునాది_Type_t MPU_xTaskDelayUntil( TickType_t * స్థిరరాశి px_మునుపటి_Wake_సమయం,
                                        TickType_t x_సమయం_Increment ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = xTaskDelayUntil( px_మునుపటి_Wake_సమయం, x_సమయం_Increment );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTaskDelayUntil( px_మునుపటి_Wake_సమయం, x_సమయం_Increment );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskAbortDelay == 1 )
        పునాది_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = xTaskAbortDelay( xTask );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTaskAbortDelay( xTask );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_vTaskDelay == 1 )
        శూన్య MPU_vTaskDelay( TickType_t x_Ticks_గమ్యం_Delay ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                vTaskDelay( x_Ticks_గమ్యం_Delay );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                vTaskDelay( x_Ticks_గమ్యం_Delay );
            }
        }
    #అయితే_ముగింపు /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_ux_Task_ప్రాధాన్యత_Get == 1 )
        UBaseType_t MPU_ux_Task_ప్రాధాన్యత_Get( స్థిరరాశి TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                uxReturn = ux_Task_ప్రాధాన్యత_Get( pxTask );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                uxReturn = ux_Task_ప్రాధాన్యత_Get( pxTask );
            }

            తిరిగి uxReturn;
        }
    #అయితే_ముగింపు /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_v_Task_ప్రాధాన్యత_సమితి == 1 )
        శూన్య MPU_v_Task_ప్రాధాన్యత_సమితి( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_ప్రాధాన్యత ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                v_Task_ప్రాధాన్యత_సమితి( pxTask, ux_New_ప్రాధాన్యత );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                v_Task_ప్రాధాన్యత_సమితి( pxTask, ux_New_ప్రాధాన్యత );
            }
        }
    #అయితే_ముగింపు /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                eReturn = eTaskGetState( pxTask );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                eReturn = eTaskGetState( pxTask );
            }

            తిరిగి eReturn;
        }
    #అయితే_ముగింపు /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TRACE_FACILITY == 1 )
        శూన్య MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_స్థితి_t * px_Task_స్థితి,
                               పునాది_Type_t x_Get_Free_దొంతర_Space,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                vTaskGetInfo( xTask, px_Task_స్థితి, x_Get_Free_దొంతర_Space, eState );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                vTaskGetInfo( xTask, px_Task_స్థితి, x_Get_Free_దొంతర_Space, eState );
            }
        }
    #అయితే_ముగింపు /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( శూన్య ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
                xReturn = xTaskGetIdleTaskHandle();
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTaskGetIdleTaskHandle();
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_vTaskSuspend == 1 )
        శూన్య MPU_vTaskSuspend( TaskHandle_t px_Task_గమ్యం_Suspend ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                vTaskSuspend( px_Task_గమ్యం_Suspend );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                vTaskSuspend( px_Task_గమ్యం_Suspend );
            }
        }
    #అయితే_ముగింపు /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_vTaskSuspend == 1 )
        శూన్య MPU_vTaskResume( TaskHandle_t px_Task_గమ్యం_Resume ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                vTaskResume( px_Task_గమ్యం_Resume );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                vTaskResume( px_Task_గమ్యం_Resume );
            }
        }
    #అయితే_ముగింపు /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    శూన్య MPU_vTaskSuspendAll( శూన్య ) /* FREERTOS_SYSTEM_CALL */
    {
        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            vTaskSuspendAll();
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            vTaskSuspendAll();
        }
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_xTaskResumeAll( శూన్య ) /* FREERTOS_SYSTEM_CALL */
    {
        పునాది_Type_t xReturn;

        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            xReturn = xTaskResumeAll();
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            xReturn = xTaskResumeAll();
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_లెక్క( శూన్య ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            xReturn = x_Task_Get_Tick_లెక్క();
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            xReturn = x_Task_Get_Tick_లెక్క();
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks( శూన్య ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            uxReturn = ux_Task_Get_సంఖ్య_యొక్క_Tasks();
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            uxReturn = ux_Task_Get_సంఖ్య_యొక్క_Tasks();
        }

        తిరిగి uxReturn;
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( స్థిరరాశి అక్షరం * pc_Name_గమ్యం_Query ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = xTaskGetHandle( pc_Name_గమ్యం_Query );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTaskGetHandle( pc_Name_గమ్యం_Query );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 ) )
        శూన్య MPU_vTaskListTasks( అక్షరం * pc_Write_బఫరు,
                                 size_t ux_బఫరు_నిడివి ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                vTaskListTasks( pc_Write_బఫరు, ux_బఫరు_నిడివి );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                vTaskListTasks( pc_Write_బఫరు, ux_బఫరు_నిడివి );
            }
        }
    #అయితే_ముగింపు /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 ) )
        శూన్య MPU_v_Task_Get_నిరంతరం_సమయం_Statistics( అక్షరం * pc_Write_బఫరు,
                                            size_t ux_బఫరు_నిడివి ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                v_Task_Get_నిరంతరం_సమయం_Statistics( pc_Write_బఫరు, ux_బఫరు_నిడివి );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                v_Task_Get_నిరంతరం_సమయం_Statistics( pc_Write_బఫరు, ux_బఫరు_నిడివి );
            }
        }
    #అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent( శూన్య ) /* FREERTOS_SYSTEM_CALL */
        {
            config_నిరంతరం_సమయం_COUNTER_TYPE xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = ul_Task_Get_Idle_నిరంతరం_సమయం_Percent();
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = ul_Task_Get_Idle_నిరంతరం_సమయం_Percent();
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter( శూన్య ) /* FREERTOS_SYSTEM_CALL */
        {
            config_నిరంతరం_సమయం_COUNTER_TYPE xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = ul_Task_Get_Idle_నిరంతరం_సమయం_Counter();
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = ul_Task_Get_Idle_నిరంతరం_సమయం_Counter();
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )
        శూన్య MPU_v_Task_సమితి_Application_Task_ట్యాగ్( TaskHandle_t xTask,
                                             TaskHookFunction_t px_ట్యాగ్_విలువ ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                v_Task_సమితి_Application_Task_ట్యాగ్( xTask, px_ట్యాగ్_విలువ );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                v_Task_సమితి_Application_Task_ట్యాగ్( xTask, px_ట్యాగ్_విలువ );
            }
        }
    #అయితే_ముగింపు /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )
        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ట్యాగ్( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_Task_Get_Application_Task_ట్యాగ్( xTask );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_Task_Get_Application_Task_ట్యాగ్( xTask );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_అంకె_THREAD_LOCAL_STORAGE_సూచికలు != 0 )
        శూన్య MPU_v_Task_సమితి_Thread_Local_Storage_సూచిక( TaskHandle_t x_Task_గమ్యం_సమితి,
                                                    పునాది_Type_t x_సూచీ,
                                                    శూన్య * pv_విలువ ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                v_Task_సమితి_Thread_Local_Storage_సూచిక( x_Task_గమ్యం_సమితి, x_సూచీ, pv_విలువ );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                v_Task_సమితి_Thread_Local_Storage_సూచిక( x_Task_గమ్యం_సమితి, x_సూచీ, pv_విలువ );
            }
        }
    #అయితే_ముగింపు /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_అంకె_THREAD_LOCAL_STORAGE_సూచికలు != 0 )
        శూన్య * MPU_pv_Task_Get_Thread_Local_Storage_సూచిక( TaskHandle_t x_Task_గమ్యం_Query,
                                                       పునాది_Type_t x_సూచీ ) /* FREERTOS_SYSTEM_CALL */
        {
            శూన్య * pvReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                pvReturn = pv_Task_Get_Thread_Local_Storage_సూచిక( x_Task_గమ్యం_Query, x_సూచీ );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_సూచిక( x_Task_గమ్యం_Query, x_సూచీ );
            }

            తిరిగి pvReturn;
        }
    #అయితే_ముగింపు /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )
        పునాది_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     శూన్య * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( Task_స్థితి_t * px_Task_స్థితి_Array,
                                              UBaseType_t ux_Array_కొలత,
                                              config_నిరంతరం_సమయం_COUNTER_TYPE * pul_మొత్తం_నిరంతరం_సమయం ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                uxReturn = uxTaskGetSystemState( px_Task_స్థితి_Array, ux_Array_కొలత, pul_మొత్తం_నిరంతరం_సమయం );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                uxReturn = uxTaskGetSystemState( px_Task_స్థితి_Array, ux_Array_కొలత, pul_మొత్తం_నిరంతరం_సమయం );
            }

            తిరిగి uxReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_Task_Catch_పైకి_Ticks( TickType_t x_Ticks_గమ్యం_Catch_పైకి ) /* FREERTOS_SYSTEM_CALL */
    {
        పునాది_Type_t xReturn;

        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            xReturn = x_Task_Catch_పైకి_Ticks( x_Ticks_గమ్యం_Catch_పైకి );
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            xReturn = x_Task_Catch_పైకి_Ticks( x_Ticks_గమ్యం_Catch_పైకి );
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_ux_Task_Get_దొంతర_ఎగువ_Water_Mark == 1 )
        UBaseType_t MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                uxReturn = ux_Task_Get_దొంతర_ఎగువ_Water_Mark( xTask );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                uxReturn = ux_Task_Get_దొంతర_ఎగువ_Water_Mark( xTask );
            }

            తిరిగి uxReturn;
        }
    #అయితే_ముగింపు /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2 == 1 )
        config_దొంతర_లోతు_TYPE MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            config_దొంతర_లోతు_TYPE uxReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                uxReturn = ux_Task_Get_దొంతర_ఎగువ_Water_Mark2( xTask );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                uxReturn = ux_Task_Get_దొంతర_ఎగువ_Water_Mark2( xTask );
            }

            తిరిగి uxReturn;
        }
    #అయితే_ముగింపు /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( శూన్య ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
                xReturn = xTaskGetCurrentTaskHandle();
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTaskGetCurrentTaskHandle();
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskGetSchedulerState == 1 )
        పునాది_Type_t MPU_xTaskGetSchedulerState( శూన్య ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = xTaskGetSchedulerState();
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTaskGetSchedulerState();
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    శూన్య MPU_v_Task_సమితి_సమయం_బహిర్గతం_State( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం ) /* FREERTOS_SYSTEM_CALL */
    {
        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            v_Task_సమితి_సమయం_బహిర్గతం_State( px_సమయం_బహిర్గతం );
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            v_Task_సమితి_సమయం_బహిర్గతం_State( px_సమయం_బహిర్గతం );
        }
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_Task_Check_For_సమయం_బహిర్గతం( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం,
                                         TickType_t * స్థిరరాశి px_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        పునాది_Type_t xReturn;

        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            xReturn = x_Task_Check_For_సమయం_బహిర్గతం( px_సమయం_బహిర్గతం, px_Ticks_గమ్యం_Wait );
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            xReturn = x_Task_Check_For_సమయం_బహిర్గతం( px_సమయం_బహిర్గతం, px_Ticks_గమ్యం_Wait );
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )
        పునాది_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_గమ్యం_Notify,
                                           UBaseType_t ux_సూచీ_గమ్యం_Notify,
                                           uint32_t ul_విలువ,
                                           eNotifyAction eAction,
                                           uint32_t * pul_మునుపటి_Notification_విలువ ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = xTaskGenericNotify( x_Task_గమ్యం_Notify, ux_సూచీ_గమ్యం_Notify, ul_విలువ, eAction, pul_మునుపటి_Notification_విలువ );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTaskGenericNotify( x_Task_గమ్యం_Notify, ux_సూచీ_గమ్యం_Notify, ul_విలువ, eAction, pul_మునుపటి_Notification_విలువ );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )
        పునాది_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_సూచీ_గమ్యం_Wait_On,
                                               uint32_t ul_బిట్లు_గమ్యం_Clear_On_నమోదు,
                                               uint32_t ul_బిట్లు_గమ్యం_Clear_On_Exit,
                                               uint32_t * pul_Notification_విలువ,
                                               TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = xTaskGenericNotifyWait( ux_సూచీ_గమ్యం_Wait_On, ul_బిట్లు_గమ్యం_Clear_On_నమోదు, ul_బిట్లు_గమ్యం_Clear_On_Exit, pul_Notification_విలువ, x_Ticks_గమ్యం_Wait );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTaskGenericNotifyWait( ux_సూచీ_గమ్యం_Wait_On, ul_బిట్లు_గమ్యం_Clear_On_నమోదు, ul_బిట్లు_గమ్యం_Clear_On_Exit, pul_Notification_విలువ, x_Ticks_గమ్యం_Wait );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_సూచీ_గమ్యం_Wait_On,
                                              పునాది_Type_t x_Clear_లెక్క_On_Exit,
                                              TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( ux_సూచీ_గమ్యం_Wait_On, x_Clear_లెక్క_On_Exit, x_Ticks_గమ్యం_Wait );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                ulReturn = ulTaskGenericNotifyTake( ux_సూచీ_గమ్యం_Wait_On, x_Clear_లెక్క_On_Exit, x_Ticks_గమ్యం_Wait );
            }

            తిరిగి ulReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )
        పునాది_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_సూచీ_గమ్యం_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, ux_సూచీ_గమ్యం_Clear );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, ux_సూచీ_గమ్యం_Clear );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ul_Task_Generic_Notify_విలువ_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_సూచీ_గమ్యం_Clear,
                                                    uint32_t ul_బిట్లు_గమ్యం_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                ulReturn = ul_Task_Generic_Notify_విలువ_Clear( xTask, ux_సూచీ_గమ్యం_Clear, ul_బిట్లు_గమ్యం_Clear );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                ulReturn = ul_Task_Generic_Notify_విలువ_Clear( xTask, ux_సూచీ_గమ్యం_Clear, ul_బిట్లు_గమ్యం_Clear );
            }

            తిరిగి ulReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 )
        వరుస_Handle_t MPU_x_వరుస_Generic_Create( UBaseType_t ux_వరుస_నిడివి,
                                               UBaseType_t ux_అంశం_కొలత,
                                               uint8_t uc_వరుస_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            వరుస_Handle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_వరుస_Generic_Create( ux_వరుస_నిడివి, ux_అంశం_కొలత, uc_వరుస_Type );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_వరుస_Generic_Create( ux_వరుస_నిడివి, ux_అంశం_కొలత, uc_వరుస_Type );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_SUPPORT_STATIC_కేటాయింపు == 1 )
        వరుస_Handle_t MPU_x_వరుస_Generic_Create_Static( స్థిరరాశి UBaseType_t ux_వరుస_నిడివి,
                                                     స్థిరరాశి UBaseType_t ux_అంశం_కొలత,
                                                     uint8_t * puc_వరుస_Storage,
                                                     Static_వరుస_t * px_Static_వరుస,
                                                     స్థిరరాశి uint8_t uc_వరుస_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            వరుస_Handle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_వరుస_Generic_Create_Static( ux_వరుస_నిడివి, ux_అంశం_కొలత, puc_వరుస_Storage, px_Static_వరుస, uc_వరుస_Type );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_వరుస_Generic_Create_Static( ux_వరుస_నిడివి, ux_అంశం_కొలత, puc_వరుస_Storage, px_Static_వరుస, uc_వరుస_Type );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Generic_Reset( వరుస_Handle_t px_వరుస,
                                       పునాది_Type_t x_New_వరుస ) /* FREERTOS_SYSTEM_CALL */
    {
        పునాది_Type_t xReturn;

        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            xReturn = x_వరుస_Generic_Reset( px_వరుస, x_New_వరుస );
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            xReturn = x_వరుస_Generic_Reset( px_వరుస, x_New_వరుస );
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Generic_Send( వరుస_Handle_t x_వరుస,
                                      స్థిరరాశి శూన్య * స్థిరరాశి pv_అంశం_గమ్యం_వరుస,
                                      TickType_t x_Ticks_గమ్యం_Wait,
                                      పునాది_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        పునాది_Type_t xReturn;

        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            xReturn = x_వరుస_Generic_Send( x_వరుస, pv_అంశం_గమ్యం_వరుస, x_Ticks_గమ్యం_Wait, xCopyPosition );
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            xReturn = x_వరుస_Generic_Send( x_వరుస, pv_అంశం_గమ్యం_వరుస, x_Ticks_గమ్యం_Wait, xCopyPosition );
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_వరుస_Messages_నిరీక్షణ( స్థిరరాశి వరుస_Handle_t px_వరుస ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            uxReturn = ux_వరుస_Messages_నిరీక్షణ( px_వరుస );
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            uxReturn = ux_వరుస_Messages_నిరీక్షణ( px_వరుస );
        }

        తిరిగి uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_వరుస_Spaces_అందుబాటు( స్థిరరాశి వరుస_Handle_t x_వరుస ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            uxReturn = ux_వరుస_Spaces_అందుబాటు( x_వరుస );
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            uxReturn = ux_వరుస_Spaces_అందుబాటు( x_వరుస );
        }

        తిరిగి uxReturn;
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Receive( వరుస_Handle_t px_వరుస,
                                  శూన్య * స్థిరరాశి pv_బఫరు,
                                  TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        పునాది_Type_t xReturn;

        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            xReturn = x_వరుస_Receive( px_వరుస, pv_బఫరు, x_Ticks_గమ్యం_Wait );
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            xReturn = x_వరుస_Receive( px_వరుస, pv_బఫరు, x_Ticks_గమ్యం_Wait );
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Peek( వరుస_Handle_t x_వరుస,
                               శూన్య * స్థిరరాశి pv_బఫరు,
                               TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        పునాది_Type_t xReturn;

        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            xReturn = x_వరుస_Peek( x_వరుస, pv_బఫరు, x_Ticks_గమ్యం_Wait );
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            xReturn = x_వరుస_Peek( x_వరుస, pv_బఫరు, x_Ticks_గమ్యం_Wait );
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Semaphore_Take( వరుస_Handle_t x_వరుస,
                                        TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        పునాది_Type_t xReturn;

        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            xReturn = x_వరుస_Semaphore_Take( x_వరుస, x_Ticks_గమ్యం_Wait );
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            xReturn = x_వరుస_Semaphore_Take( x_వరుస, x_Ticks_గమ్యం_Wait );
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_x_వరుస_Get_Mutex_Holder( వరుస_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            శూన్య * xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_వరుస_Get_Mutex_Holder( xSemaphore );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_వరుస_Get_Mutex_Holder( xSemaphore );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 ) )
        వరుస_Handle_t MPU_x_వరుస_Create_Mutex( స్థిరరాశి uint8_t uc_వరుస_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            వరుస_Handle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_వరుస_Create_Mutex( uc_వరుస_Type );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_వరుస_Create_Mutex( uc_వరుస_Type );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_కేటాయింపు == 1 ) )
        వరుస_Handle_t MPU_x_వరుస_Create_Mutex_Static( స్థిరరాశి uint8_t uc_వరుస_Type,
                                                   Static_వరుస_t * px_Static_వరుస ) /* FREERTOS_SYSTEM_CALL */
        {
            వరుస_Handle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_వరుస_Create_Mutex_Static( uc_వరుస_Type, px_Static_వరుస );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_వరుస_Create_Mutex_Static( uc_వరుస_Type, px_Static_వరుస );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 ) )
        వరుస_Handle_t MPU_x_వరుస_Create_Counting_Semaphore( UBaseType_t ux_లెక్క_విలువ,
                                                         UBaseType_t ux_Initial_లెక్క ) /* FREERTOS_SYSTEM_CALL */
        {
            వరుస_Handle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_వరుస_Create_Counting_Semaphore( ux_లెక్క_విలువ, ux_Initial_లెక్క );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_వరుస_Create_Counting_Semaphore( ux_లెక్క_విలువ, ux_Initial_లెక్క );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_కేటాయింపు == 1 ) )

        వరుస_Handle_t MPU_x_వరుస_Create_Counting_Semaphore_Static( స్థిరరాశి UBaseType_t ux_Max_లెక్క,
                                                               స్థిరరాశి UBaseType_t ux_Initial_లెక్క,
                                                               Static_వరుస_t * px_Static_వరుస ) /* FREERTOS_SYSTEM_CALL */
        {
            వరుస_Handle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_వరుస_Create_Counting_Semaphore_Static( ux_Max_లెక్క, ux_Initial_లెక్క, px_Static_వరుస );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_వరుస_Create_Counting_Semaphore_Static( ux_Max_లెక్క, ux_Initial_లెక్క, px_Static_వరుస );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_RECURSIVE_MUTEXES == 1 )
        పునాది_Type_t MPU_x_వరుస_Take_Mutex_Recursive( వరుస_Handle_t xMutex,
                                                 TickType_t x_ఖండం_సమయం ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_వరుస_Take_Mutex_Recursive( xMutex, x_ఖండం_సమయం );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_వరుస_Take_Mutex_Recursive( xMutex, x_ఖండం_సమయం );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_RECURSIVE_MUTEXES == 1 )
        పునాది_Type_t MPU_x_వరుస_Give_Mutex_Recursive( వరుస_Handle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_వరుస_Give_Mutex_Recursive( xMutex );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_వరుస_Give_Mutex_Recursive( xMutex );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_USE_వరుస_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 ) )
        వరుస_సమితి_Handle_t MPU_x_వరుస_Create_సమితి( UBaseType_t ux_Event_వరుస_నిడివి ) /* FREERTOS_SYSTEM_CALL */
        {
            వరుస_సమితి_Handle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_వరుస_Create_సమితి( ux_Event_వరుస_నిడివి );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_వరుస_Create_సమితి( ux_Event_వరుస_నిడివి );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_USE_వరుస_SETS == 1 ) && ( config_SUPPORT_STATIC_కేటాయింపు == 1 ) )
        వరుస_సమితి_Handle_t MPU_x_వరుస_Create_సమితి_Static( స్థిరరాశి UBaseType_t ux_Event_వరుస_నిడివి,
                                                    uint8_t * puc_వరుస_Storage,
                                                    Static_వరుస_t * px_Static_వరుస ) /* FREERTOS_SYSTEM_CALL */
        {
            వరుస_సమితి_Handle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_వరుస_Create_సమితి_Static( ux_Event_వరుస_నిడివి, puc_వరుస_Storage, px_Static_వరుస );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_వరుస_Create_సమితి_Static( ux_Event_వరుస_నిడివి, puc_వరుస_Storage, px_Static_వరుస );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_వరుస_SETS == 1 )
        వరుస_సమితి_Member_Handle_t MPU_x_వరుస_Select_From_సమితి( వరుస_సమితి_Handle_t x_వరుస_సమితి,
                                                        TickType_t x_ఖండం_సమయం_Ticks ) /* FREERTOS_SYSTEM_CALL */
        {
            వరుస_సమితి_Member_Handle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_వరుస_Select_From_సమితి( x_వరుస_సమితి, x_ఖండం_సమయం_Ticks );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_వరుస_Select_From_సమితి( x_వరుస_సమితి, x_ఖండం_సమయం_Ticks );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_వరుస_SETS == 1 )
        పునాది_Type_t MPU_x_వరుస_కూడు_గమ్యం_సమితి( వరుస_సమితి_Member_Handle_t x_వరుస_Or_Semaphore,
                                       వరుస_సమితి_Handle_t x_వరుస_సమితి ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_వరుస_కూడు_గమ్యం_సమితి( x_వరుస_Or_Semaphore, x_వరుస_సమితి );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_వరుస_కూడు_గమ్యం_సమితి( x_వరుస_Or_Semaphore, x_వరుస_సమితి );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_వరుస_SETS == 1 )
        పునాది_Type_t MPU_x_వరుస_Remove_From_సమితి( వరుస_సమితి_Member_Handle_t x_వరుస_Or_Semaphore,
                                            వరుస_సమితి_Handle_t x_వరుస_సమితి ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_వరుస_Remove_From_సమితి( x_వరుస_Or_Semaphore, x_వరుస_సమితి );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_వరుస_Remove_From_సమితి( x_వరుస_Or_Semaphore, x_వరుస_సమితి );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ config_వరుస_REGISTRY_కొలత > 0
        శూన్య MPU_v_వరుస_కూడు_గమ్యం_Registry( వరుస_Handle_t x_వరుస,
                                      స్థిరరాశి అక్షరం * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                v_వరుస_కూడు_గమ్యం_Registry( x_వరుస, pcName );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                v_వరుస_కూడు_గమ్యం_Registry( x_వరుస, pcName );
            }
        }
    #అయితే_ముగింపు /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ఒకవేళ config_వరుస_REGISTRY_కొలత > 0
        శూన్య MPU_v_వరుస_Unregister_వరుస( వరుస_Handle_t x_వరుస ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                v_వరుస_Unregister_వరుస( x_వరుస );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                v_వరుస_Unregister_వరుస( x_వరుస );
            }
        }
    #అయితే_ముగింపు /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ఒకవేళ config_వరుస_REGISTRY_కొలత > 0
        స్థిరరాశి అక్షరం * MPU_pc_వరుస_Get_Name( వరుస_Handle_t x_వరుస ) /* FREERTOS_SYSTEM_CALL */
        {
            స్థిరరాశి అక్షరం * pcReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                pcReturn = pc_వరుస_Get_Name( x_వరుస );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                pcReturn = pc_వరుస_Get_Name( x_వరుస );
            }

            తిరిగి pcReturn;
        }
    #అయితే_ముగింపు /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    శూన్య MPU_v_వరుస_Delete( వరుస_Handle_t x_వరుస ) /* FREERTOS_SYSTEM_CALL */
    {
        ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
        {
            పోర్టు_RAISE_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();

            v_వరుస_Delete( x_వరుస );
            పోర్టు_జ్ఞాపకం_BARRIER();

            పోర్టు_RESET_PRIVILEGE();
            పోర్టు_జ్ఞాపకం_BARRIER();
        }
        లేకపోతే
        {
            v_వరుస_Delete( x_వరుస );
        }
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )
        శూన్య * MPU_pvTimerGetTimerID( స్థిరరాశి TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            శూన్య * pvReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                pvReturn = pvTimerGetTimerID( xTimer );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                pvReturn = pvTimerGetTimerID( xTimer );
            }

            తిరిగి pvReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )
        శూన్య MPU_v_Timer_సమితి_Timer_ID( TimerHandle_t xTimer,
                                   శూన్య * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                v_Timer_సమితి_Timer_ID( xTimer, pvNewID );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                v_Timer_సమితి_Timer_ID( xTimer, pvNewID );
            }
        }
    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )
        పునాది_Type_t MPU_x_Timer_Is_Timer_చురుకైన( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_Timer_Is_Timer_చురుకైన( xTimer );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_Timer_Is_Timer_చురుకైన( xTimer );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( శూన్య ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = xTimerGetTimerDaemonTaskHandle();
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTimerGetTimerDaemonTaskHandle();
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )
        శూన్య MPU_v_Timer_సమితి_Reload_బహుళకం( TimerHandle_t xTimer,
                                      స్థిరరాశి పునాది_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                v_Timer_సమితి_Reload_బహుళకం( xTimer, xAutoReload );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                v_Timer_సమితి_Reload_బహుళకం( xTimer, xAutoReload );
            }
        }
    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_ux_Timer_Get_Reload_బహుళకం( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                uxReturn = ux_Timer_Get_Reload_బహుళకం( xTimer );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                uxReturn = ux_Timer_Get_Reload_బహుళకం( xTimer );
            }

            తిరిగి uxReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )
        స్థిరరాశి అక్షరం * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            స్థిరరాశి అక్షరం * pcReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                pcReturn = pcTimerGetName( xTimer );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                pcReturn = pcTimerGetName( xTimer );
            }

            తిరిగి pcReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = xTimerGetPeriod( xTimer );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTimerGetPeriod( xTimer );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )
        TickType_t MPU_x_Timer_Get_Expiry_సమయం( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_Timer_Get_Expiry_సమయం( xTimer );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_Timer_Get_Expiry_సమయం( xTimer );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )
        పునాది_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     స్థిరరాశి పునాది_Type_t xCommandID,
                                                     స్థిరరాశి TickType_t x_Optional_విలువ,
                                                     పునాది_Type_t * స్థిరరాశి px_Higher_ప్రాధాన్యత_Task_Woken,
                                                     స్థిరరాశి TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_విలువ, px_Higher_ప్రాధాన్యత_Task_Woken, x_Ticks_గమ్యం_Wait );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_విలువ, px_Higher_ప్రాధాన్యత_Task_Woken, x_Ticks_గమ్యం_Wait );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_సమూహం_Handle_t MPU_x_Event_సమూహం_Create( శూన్య ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_సమూహం_Handle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_Event_సమూహం_Create();
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_Event_సమూహం_Create();
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_SUPPORT_STATIC_కేటాయింపు == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_సమూహం_Handle_t MPU_x_Event_సమూహం_Create_Static( Static_Event_సమూహం_t * px_Event_సమూహం_బఫరు ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_సమూహం_Handle_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_Event_సమూహం_Create_Static( px_Event_సమూహం_బఫరు );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_Event_సమూహం_Create_Static( px_Event_సమూహం_బఫరు );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )
        Event_బిట్లు_t MPU_x_Event_సమూహం_Wait_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                             స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Wait_For,
                                             స్థిరరాశి పునాది_Type_t xClearOnExit,
                                             స్థిరరాశి పునాది_Type_t x_Wait_For_All_బిట్లు,
                                             TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_బిట్లు_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_Event_సమూహం_Wait_బిట్లు( x_Event_సమూహం, ux_బిట్లు_గమ్యం_Wait_For, xClearOnExit, x_Wait_For_All_బిట్లు, x_Ticks_గమ్యం_Wait );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_Event_సమూహం_Wait_బిట్లు( x_Event_సమూహం, ux_బిట్లు_గమ్యం_Wait_For, xClearOnExit, x_Wait_For_All_బిట్లు, x_Ticks_గమ్యం_Wait );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )
        Event_బిట్లు_t MPU_x_Event_సమూహం_Clear_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                              స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_బిట్లు_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_Event_సమూహం_Clear_బిట్లు( x_Event_సమూహం, ux_బిట్లు_గమ్యం_Clear );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_Event_సమూహం_Clear_బిట్లు( x_Event_సమూహం, ux_బిట్లు_గమ్యం_Clear );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )
        Event_బిట్లు_t MPU_x_Event_సమూహం_సమితి_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                            స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_బిట్లు_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_Event_సమూహం_సమితి_బిట్లు( x_Event_సమూహం, ux_బిట్లు_గమ్యం_సమితి );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_Event_సమూహం_సమితి_బిట్లు( x_Event_సమూహం, ux_బిట్లు_గమ్యం_సమితి );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )
        Event_బిట్లు_t MPU_x_Event_సమూహం_Sync( Event_సమూహం_Handle_t x_Event_సమూహం,
                                         స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి,
                                         స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Wait_For,
                                         TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_బిట్లు_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_Event_సమూహం_Sync( x_Event_సమూహం, ux_బిట్లు_గమ్యం_సమితి, ux_బిట్లు_గమ్యం_Wait_For, x_Ticks_గమ్యం_Wait );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_Event_సమూహం_Sync( x_Event_సమూహం, ux_బిట్లు_గమ్యం_సమితి, ux_బిట్లు_గమ్యం_Wait_For, x_Ticks_గమ్యం_Wait );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )
        శూన్య MPU_v_Event_సమూహం_Delete( Event_సమూహం_Handle_t x_Event_సమూహం ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                v_Event_సమూహం_Delete( x_Event_సమూహం );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                v_Event_సమూహం_Delete( x_Event_సమూహం );
            }
        }
    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )
        size_t MPU_x_ప్రవాహం_బఫరు_Send( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                      స్థిరరాశి శూన్య * pv_Tx_దత్తాంశం,
                                      size_t x_దత్తాంశం_నిడివి_బైట్లు,
                                      TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_ప్రవాహం_బఫరు_Send( x_ప్రవాహం_బఫరు, pv_Tx_దత్తాంశం, x_దత్తాంశం_నిడివి_బైట్లు, x_Ticks_గమ్యం_Wait );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_ప్రవాహం_బఫరు_Send( x_ప్రవాహం_బఫరు, pv_Tx_దత్తాంశం, x_దత్తాంశం_నిడివి_బైట్లు, x_Ticks_గమ్యం_Wait );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )
        size_t MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు( x_ప్రవాహం_బఫరు );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు( x_ప్రవాహం_బఫరు );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )
        size_t MPU_x_ప్రవాహం_బఫరు_Receive( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                         శూన్య * pv_Rx_దత్తాంశం,
                                         size_t x_బఫరు_నిడివి_బైట్లు,
                                         TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_ప్రవాహం_బఫరు_Receive( x_ప్రవాహం_బఫరు, pv_Rx_దత్తాంశం, x_బఫరు_నిడివి_బైట్లు, x_Ticks_గమ్యం_Wait );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_ప్రవాహం_బఫరు_Receive( x_ప్రవాహం_బఫరు, pv_Rx_దత్తాంశం, x_బఫరు_నిడివి_బైట్లు, x_Ticks_గమ్యం_Wait );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )
        శూన్య MPU_v_ప్రవాహం_బఫరు_Delete( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* FREERTOS_SYSTEM_CALL */
        {
            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                v_ప్రవాహం_బఫరు_Delete( x_ప్రవాహం_బఫరు );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                v_ప్రవాహం_బఫరు_Delete( x_ప్రవాహం_బఫరు );
            }
        }
    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )
        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_నిండిన( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_ప్రవాహం_బఫరు_Is_నిండిన( x_ప్రవాహం_బఫరు );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_ప్రవాహం_బఫరు_Is_నిండిన( x_ప్రవాహం_బఫరు );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )
        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_ప్రవాహం_బఫరు_Is_ఖాళీలు( x_ప్రవాహం_బఫరు );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_ప్రవాహం_బఫరు_Is_ఖాళీలు( x_ప్రవాహం_బఫరు );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )
        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Reset( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_ప్రవాహం_బఫరు_Reset( x_ప్రవాహం_బఫరు );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_ప్రవాహం_బఫరు_Reset( x_ప్రవాహం_బఫరు );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )
        size_t MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
                xReturn = x_ప్రవాహం_బఫరు_Spaces_అందుబాటు( x_ప్రవాహం_బఫరు );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_ప్రవాహం_బఫరు_Spaces_అందుబాటు( x_ప్రవాహం_బఫరు );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )
        size_t MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు( x_ప్రవాహం_బఫరు );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు( x_ప్రవాహం_బఫరు );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )
        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                                     size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn;

            ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
            {
                పోర్టు_RAISE_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();

                xReturn = x_ప్రవాహం_బఫరు_సమితి_Trigger_Level( x_ప్రవాహం_బఫరు, xTriggerLevel );
                పోర్టు_జ్ఞాపకం_BARRIER();

                పోర్టు_RESET_PRIVILEGE();
                పోర్టు_జ్ఞాపకం_BARRIER();
            }
            లేకపోతే
            {
                xReturn = x_ప్రవాహం_బఫరు_సమితి_Trigger_Level( x_ప్రవాహం_బఫరు, xTriggerLevel );
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 ) && ( config_USE_ప్రవాహం_BUFFERS == 1 ) )
        ప్రవాహం_బఫరు_Handle_t MPU_x_ప్రవాహం_బఫరు_Generic_Create( size_t x_బఫరు_కొలత_బైట్లు,
                                                             size_t x_Trigger_Level_బైట్లు,
                                                             పునాది_Type_t x_ప్రవాహం_బఫరు_Type,
                                                             ప్రవాహం_బఫరు_Callback_Function_t pxSendCompletedCallback,
                                                             ప్రవాహం_బఫరు_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            ప్రవాహం_బఫరు_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ఖాళీ ) &&
                          ( pxReceiveCompletedCallback == ఖాళీ ) );

            ఒకవేళ( ( pxSendCompletedCallback == ఖాళీ ) &&
                ( pxReceiveCompletedCallback == ఖాళీ ) )
            {
                ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
                {
                    పోర్టు_RAISE_PRIVILEGE();
                    పోర్టు_జ్ఞాపకం_BARRIER();

                    xReturn = x_ప్రవాహం_బఫరు_Generic_Create( x_బఫరు_కొలత_బైట్లు,
                                                          x_Trigger_Level_బైట్లు,
                                                          x_ప్రవాహం_బఫరు_Type,
                                                          ఖాళీ,
                                                          ఖాళీ );
                    పోర్టు_జ్ఞాపకం_BARRIER();

                    పోర్టు_RESET_PRIVILEGE();
                    పోర్టు_జ్ఞాపకం_BARRIER();
                }
                లేకపోతే
                {
                    xReturn = x_ప్రవాహం_బఫరు_Generic_Create( x_బఫరు_కొలత_బైట్లు,
                                                          x_Trigger_Level_బైట్లు,
                                                          x_ప్రవాహం_బఫరు_Type,
                                                          ఖాళీ,
                                                          ఖాళీ );
                }
            }
            లేకపోతే
            {
                trace_ప్రవాహం_బఫరు_CREATE_FAILED( x_ప్రవాహం_బఫరు_Type );
                xReturn = ఖాళీ;
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_SUPPORT_STATIC_కేటాయింపు == 1 ) && ( config_USE_ప్రవాహం_BUFFERS == 1 ) )
        ప్రవాహం_బఫరు_Handle_t MPU_x_ప్రవాహం_బఫరు_Generic_Create_Static( size_t x_బఫరు_కొలత_బైట్లు,
                                                                   size_t x_Trigger_Level_బైట్లు,
                                                                   పునాది_Type_t x_ప్రవాహం_బఫరు_Type,
                                                                   uint8_t * స్థిరరాశి puc_ప్రవాహం_బఫరు_Storage_Area,
                                                                   Static_ప్రవాహం_బఫరు_t * స్థిరరాశి px_Static_ప్రవాహం_బఫరు,
                                                                   ప్రవాహం_బఫరు_Callback_Function_t pxSendCompletedCallback,
                                                                   ప్రవాహం_బఫరు_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            ప్రవాహం_బఫరు_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ఖాళీ ) &&
                          ( pxReceiveCompletedCallback == ఖాళీ ) );

            ఒకవేళ( ( pxSendCompletedCallback == ఖాళీ ) &&
                ( pxReceiveCompletedCallback == ఖాళీ ) )
            {
                ఒకవేళ( పోర్టు_IS_PRIVILEGED() == pdFALSE )
                {
                    పోర్టు_RAISE_PRIVILEGE();
                    పోర్టు_జ్ఞాపకం_BARRIER();

                    xReturn = x_ప్రవాహం_బఫరు_Generic_Create_Static( x_బఫరు_కొలత_బైట్లు,
                                                                x_Trigger_Level_బైట్లు,
                                                                x_ప్రవాహం_బఫరు_Type,
                                                                puc_ప్రవాహం_బఫరు_Storage_Area,
                                                                px_Static_ప్రవాహం_బఫరు,
                                                                ఖాళీ,
                                                                ఖాళీ );
                    పోర్టు_జ్ఞాపకం_BARRIER();

                    పోర్టు_RESET_PRIVILEGE();
                    పోర్టు_జ్ఞాపకం_BARRIER();
                }
                లేకపోతే
                {
                    xReturn = x_ప్రవాహం_బఫరు_Generic_Create_Static( x_బఫరు_కొలత_బైట్లు,
                                                                x_Trigger_Level_బైట్లు,
                                                                x_ప్రవాహం_బఫరు_Type,
                                                                puc_ప్రవాహం_బఫరు_Storage_Area,
                                                                px_Static_ప్రవాహం_బఫరు,
                                                                ఖాళీ,
                                                                ఖాళీ );
                }
            }
            లేకపోతే
            {
                trace_ప్రవాహం_బఫరు_CREATE_STATIC_FAILED( xReturn, x_ప్రవాహం_బఫరు_Type );
                xReturn = ఖాళీ;
            }

            తిరిగి xReturn;
        }
    #అయితే_ముగింపు /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
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

    #ఒకవేళ configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #అన్తర్భావ "application_defined_privileged_functions.h"
    #అయితే_ముగింపు
/*-----------------------------------------------------------*/

#అయితే_ముగింపు /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
