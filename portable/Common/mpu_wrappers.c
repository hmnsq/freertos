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
#ವ್ಯಾಖ್ಯಾನಿಸು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "queue.h"
#ಅನ್ತರ್ಭಾವ "timers.h"
#ಅನ್ತರ್ಭಾವ "event_groups.h"
#ಅನ್ತರ್ಭಾವ "stream_buffer.h"
#ಅನ್ತರ್ಭಾವ "mpu_prototypes.h"

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( ಪೋರ್ಟ್_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) )

    #ಆದರೆ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
        #ದೋಷ Access control list is not ಲಭ್ಯ with this MPU wrapper. Please ಗಣ configENABLE_ACCESS_CONTROL_LIST ಗಮ್ಯ 0.
    #ಆದರೆ_ಅಂತ್ಯ

    #ಆದರೆ ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 )
        ತಳ_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_ಸಂಕೇತ,
                                    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ pcName,
                                    ಸ್ಥಿರಾಂಕ config_ರಾಶಿ_ಆಳ_TYPE ux_ರಾಶಿ_ಆಳ,
                                    ಶೂನ್ಯ * pvParameters,
                                    UBaseType_t ux_ಆದ್ಯತೆ,
                                    TaskHandle_t * pxCreatedTask ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ux_ಆದ್ಯತೆ = ux_ಆದ್ಯತೆ & ~( ಪೋರ್ಟ್_PRIVILEGE_ಬಿಟ್ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = xTaskCreate( pv_Task_ಸಂಕೇತ, pcName, ux_ರಾಶಿ_ಆಳ, pvParameters, ux_ಆದ್ಯತೆ, pxCreatedTask );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTaskCreate( pv_Task_ಸಂಕೇತ, pcName, ux_ರಾಶಿ_ಆಳ, pvParameters, ux_ಆದ್ಯತೆ, pxCreatedTask );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 )
        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_ಸಂಕೇತ,
                                            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ pcName,
                                            ಸ್ಥಿರಾಂಕ config_ರಾಶಿ_ಆಳ_TYPE ux_ರಾಶಿ_ಆಳ,
                                            ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pvParameters,
                                            UBaseType_t ux_ಆದ್ಯತೆ,
                                            ರಾಶಿ_Type_t * ಸ್ಥಿರಾಂಕ pux_ರಾಶಿ_ಬಫರ್,
                                            StaticTask_t * ಸ್ಥಿರಾಂಕ px_Task_ಬಫರ್ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ux_ಆದ್ಯತೆ = ux_ಆದ್ಯತೆ & ~( ಪೋರ್ಟ್_PRIVILEGE_ಬಿಟ್ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = xTaskCreateStatic( px_Task_ಸಂಕೇತ, pcName, ux_ರಾಶಿ_ಆಳ, pvParameters, ux_ಆದ್ಯತೆ, pux_ರಾಶಿ_ಬಫರ್, px_Task_ಬಫರ್ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTaskCreateStatic( px_Task_ಸಂಕೇತ, pcName, ux_ರಾಶಿ_ಆಳ, pvParameters, ux_ಆದ್ಯತೆ, pux_ರಾಶಿ_ಬಫರ್, px_Task_ಬಫರ್ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_vTaskDelete == 1 )
        ಶೂನ್ಯ MPU_vTaskDelete( TaskHandle_t px_Task_ಗಮ್ಯ_Delete ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                vTaskDelete( px_Task_ಗಮ್ಯ_Delete );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                vTaskDelete( px_Task_ಗಮ್ಯ_Delete );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_xTaskDelayUntil == 1 )
        ತಳ_Type_t MPU_xTaskDelayUntil( TickType_t * ಸ್ಥಿರಾಂಕ px_ಹಿಂದಿನ_Wake_ಸಮಯ,
                                        TickType_t x_ಸಮಯ_Increment ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = xTaskDelayUntil( px_ಹಿಂದಿನ_Wake_ಸಮಯ, x_ಸಮಯ_Increment );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTaskDelayUntil( px_ಹಿಂದಿನ_Wake_ಸಮಯ, x_ಸಮಯ_Increment );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_xTaskAbortDelay == 1 )
        ತಳ_Type_t MPU_xTaskAbortDelay( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = xTaskAbortDelay( xTask );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTaskAbortDelay( xTask );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_vTaskDelay == 1 )
        ಶೂನ್ಯ MPU_vTaskDelay( TickType_t x_Ticks_ಗಮ್ಯ_Delay ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                vTaskDelay( x_Ticks_ಗಮ್ಯ_Delay );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                vTaskDelay( x_Ticks_ಗಮ್ಯ_Delay );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_ux_Task_ಆದ್ಯತೆ_Get == 1 )
        UBaseType_t MPU_ux_Task_ಆದ್ಯತೆ_Get( ಸ್ಥಿರಾಂಕ TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                uxReturn = ux_Task_ಆದ್ಯತೆ_Get( pxTask );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                uxReturn = ux_Task_ಆದ್ಯತೆ_Get( pxTask );
            }

            ಹಿಂತಿರುಗಿ uxReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_v_Task_ಆದ್ಯತೆ_ಗಣ == 1 )
        ಶೂನ್ಯ MPU_v_Task_ಆದ್ಯತೆ_ಗಣ( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_ಆದ್ಯತೆ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                v_Task_ಆದ್ಯತೆ_ಗಣ( pxTask, ux_New_ಆದ್ಯತೆ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                v_Task_ಆದ್ಯತೆ_ಗಣ( pxTask, ux_New_ಆದ್ಯತೆ );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_eTaskGetState == 1 )
        eTaskState MPU_eTaskGetState( TaskHandle_t pxTask ) /* FREERTOS_SYSTEM_CALL */
        {
            eTaskState eReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                eReturn = eTaskGetState( pxTask );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                eReturn = eTaskGetState( pxTask );
            }

            ಹಿಂತಿರುಗಿ eReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TRACE_FACILITY == 1 )
        ಶೂನ್ಯ MPU_vTaskGetInfo( TaskHandle_t xTask,
                               Task_ಸ್ಥಿತಿ_t * px_Task_ಸ್ಥಿತಿ,
                               ತಳ_Type_t x_Get_Free_ರಾಶಿ_Space,
                               eTaskState eState ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                vTaskGetInfo( xTask, px_Task_ಸ್ಥಿತಿ, x_Get_Free_ರಾಶಿ_Space, eState );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                vTaskGetInfo( xTask, px_Task_ಸ್ಥಿತಿ, x_Get_Free_ರಾಶಿ_Space, eState );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
        TaskHandle_t MPU_xTaskGetIdleTaskHandle( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
                xReturn = xTaskGetIdleTaskHandle();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTaskGetIdleTaskHandle();
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_vTaskSuspend == 1 )
        ಶೂನ್ಯ MPU_vTaskSuspend( TaskHandle_t px_Task_ಗಮ್ಯ_Suspend ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                vTaskSuspend( px_Task_ಗಮ್ಯ_Suspend );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                vTaskSuspend( px_Task_ಗಮ್ಯ_Suspend );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_vTaskSuspend == 1 )
        ಶೂನ್ಯ MPU_vTaskResume( TaskHandle_t px_Task_ಗಮ್ಯ_Resume ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                vTaskResume( px_Task_ಗಮ್ಯ_Resume );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                vTaskResume( px_Task_ಗಮ್ಯ_Resume );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ MPU_vTaskSuspendAll( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
    {
        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            vTaskSuspendAll();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            vTaskSuspendAll();
        }
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_xTaskResumeAll( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
    {
        ತಳ_Type_t xReturn;

        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            xReturn = xTaskResumeAll();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xReturn = xTaskResumeAll();
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_ಎಣಿಕೆ( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
    {
        TickType_t xReturn;

        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            xReturn = x_Task_Get_Tick_ಎಣಿಕೆ();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xReturn = x_Task_Get_Tick_ಎಣಿಕೆ();
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            uxReturn = ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            uxReturn = ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks();
        }

        ಹಿಂತಿರುಗಿ uxReturn;
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_xTaskGetHandle == 1 )
        TaskHandle_t MPU_xTaskGetHandle( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pc_Name_ಗಮ್ಯ_Query ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = xTaskGetHandle( pc_Name_ಗಮ್ಯ_Query );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTaskGetHandle( pc_Name_ಗಮ್ಯ_Query );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 ) )
        ಶೂನ್ಯ MPU_vTaskListTasks( ಅಕ್ಷರ * pc_Write_ಬಫರ್,
                                 size_t ux_ಬಫರ್_ಉದ್ದಳತೆ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                vTaskListTasks( pc_Write_ಬಫರ್, ux_ಬಫರ್_ಉದ್ದಳತೆ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                vTaskListTasks( pc_Write_ಬಫರ್, ux_ಬಫರ್_ಉದ್ದಳತೆ );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_TRACE_FACILITY == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 ) )
        ಶೂನ್ಯ MPU_v_Task_Get_ಸತತ_ಸಮಯ_Statistics( ಅಕ್ಷರ * pc_Write_ಬಫರ್,
                                            size_t ux_ಬಫರ್_ಉದ್ದಳತೆ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                v_Task_Get_ಸತತ_ಸಮಯ_Statistics( pc_Write_ಬಫರ್, ux_ಬಫರ್_ಉದ್ದಳತೆ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                v_Task_Get_ಸತತ_ಸಮಯ_Statistics( pc_Write_ಬಫರ್, ux_ಬಫರ್_ಉದ್ದಳತೆ );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( configUSE_STATS_FORMATTING_FUNCTIONS > 0 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            config_ಸತತ_ಸಮಯ_COUNTER_TYPE xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent();
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            config_ಸತತ_ಸಮಯ_COUNTER_TYPE xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter();
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_APPLICATION_TASK_ಟ್ಯಾಗ್ == 1 )
        ಶೂನ್ಯ MPU_v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್( TaskHandle_t xTask,
                                             TaskHookFunction_t px_ಟ್ಯಾಗ್_ಮೌಲ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್( xTask, px_ಟ್ಯಾಗ್_ಮೌಲ್ಯ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್( xTask, px_ಟ್ಯಾಗ್_ಮೌಲ್ಯ );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_APPLICATION_TASK_ಟ್ಯಾಗ್ == 1 )
        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ಟ್ಯಾಗ್( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHookFunction_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_Task_Get_Application_Task_ಟ್ಯಾಗ್( xTask );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_Task_Get_Application_Task_ಟ್ಯಾಗ್( xTask );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_ಸೂಚಕಗಳು != 0 )
        ಶೂನ್ಯ MPU_v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ( TaskHandle_t x_Task_ಗಮ್ಯ_ಗಣ,
                                                    ತಳ_Type_t x_ಸೂಚ್ಯಂಕ,
                                                    ಶೂನ್ಯ * pv_ಮೌಲ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ( x_Task_ಗಮ್ಯ_ಗಣ, x_ಸೂಚ್ಯಂಕ, pv_ಮೌಲ್ಯ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ( x_Task_ಗಮ್ಯ_ಗಣ, x_ಸೂಚ್ಯಂಕ, pv_ಮೌಲ್ಯ );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_ಸೂಚಕಗಳು != 0 )
        ಶೂನ್ಯ * MPU_pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ( TaskHandle_t x_Task_ಗಮ್ಯ_Query,
                                                       ತಳ_Type_t x_ಸೂಚ್ಯಂಕ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಶೂನ್ಯ * pvReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                pvReturn = pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ( x_Task_ಗಮ್ಯ_Query, x_ಸೂಚ್ಯಂಕ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ( x_Task_ಗಮ್ಯ_Query, x_ಸೂಚ್ಯಂಕ );
            }

            ಹಿಂತಿರುಗಿ pvReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_APPLICATION_TASK_ಟ್ಯಾಗ್ == 1 )
        ತಳ_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     ಶೂನ್ಯ * pvParameter ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TRACE_FACILITY == 1 )
        UBaseType_t MPU_uxTaskGetSystemState( Task_ಸ್ಥಿತಿ_t * px_Task_ಸ್ಥಿತಿ_Array,
                                              UBaseType_t ux_Array_ಗಾತ್ರ,
                                              config_ಸತತ_ಸಮಯ_COUNTER_TYPE * pul_ಒಟ್ಟು_ಸತತ_ಸಮಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                uxReturn = uxTaskGetSystemState( px_Task_ಸ್ಥಿತಿ_Array, ux_Array_ಗಾತ್ರ, pul_ಒಟ್ಟು_ಸತತ_ಸಮಯ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                uxReturn = uxTaskGetSystemState( px_Task_ಸ್ಥಿತಿ_Array, ux_Array_ಗಾತ್ರ, pul_ಒಟ್ಟು_ಸತತ_ಸಮಯ );
            }

            ಹಿಂತಿರುಗಿ uxReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_Task_Catch_ಮೇಲೆ_Ticks( TickType_t x_Ticks_ಗಮ್ಯ_Catch_ಮೇಲೆ ) /* FREERTOS_SYSTEM_CALL */
    {
        ತಳ_Type_t xReturn;

        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            xReturn = x_Task_Catch_ಮೇಲೆ_Ticks( x_Ticks_ಗಮ್ಯ_Catch_ಮೇಲೆ );
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xReturn = x_Task_Catch_ಮೇಲೆ_Ticks( x_Ticks_ಗಮ್ಯ_Catch_ಮೇಲೆ );
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark == 1 )
        UBaseType_t MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            UBaseType_t uxReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( xTask );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( xTask );
            }

            ಹಿಂತಿರುಗಿ uxReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2 == 1 )
        config_ರಾಶಿ_ಆಳ_TYPE MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( TaskHandle_t xTask ) /* FREERTOS_SYSTEM_CALL */
        {
            config_ರಾಶಿ_ಆಳ_TYPE uxReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( xTask );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( xTask );
            }

            ಹಿಂತಿರುಗಿ uxReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )
        TaskHandle_t MPU_xTaskGetCurrentTaskHandle( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
                xReturn = xTaskGetCurrentTaskHandle();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTaskGetCurrentTaskHandle();
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_xTaskGetSchedulerState == 1 )
        ತಳ_Type_t MPU_xTaskGetSchedulerState( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = xTaskGetSchedulerState();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTaskGetSchedulerState();
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ MPU_v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State( ಸಮಯ_ಹೊರಹೋಗು_t * ಸ್ಥಿರಾಂಕ px_ಸಮಯ_ಹೊರಹೋಗು ) /* FREERTOS_SYSTEM_CALL */
    {
        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State( px_ಸಮಯ_ಹೊರಹೋಗು );
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State( px_ಸಮಯ_ಹೊರಹೋಗು );
        }
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು( ಸಮಯ_ಹೊರಹೋಗು_t * ಸ್ಥಿರಾಂಕ px_ಸಮಯ_ಹೊರಹೋಗು,
                                         TickType_t * ಸ್ಥಿರಾಂಕ px_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        ತಳ_Type_t xReturn;

        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            xReturn = x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು( px_ಸಮಯ_ಹೊರಹೋಗು, px_Ticks_ಗಮ್ಯ_Wait );
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xReturn = x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು( px_ಸಮಯ_ಹೊರಹೋಗು, px_Ticks_ಗಮ್ಯ_Wait );
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )
        ತಳ_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_ಗಮ್ಯ_Notify,
                                           UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Notify,
                                           uint32_t ul_ಮೌಲ್ಯ,
                                           eNotifyAction eAction,
                                           uint32_t * pul_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = xTaskGenericNotify( x_Task_ಗಮ್ಯ_Notify, ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Notify, ul_ಮೌಲ್ಯ, eAction, pul_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTaskGenericNotify( x_Task_ಗಮ್ಯ_Notify, ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Notify, ul_ಮೌಲ್ಯ, eAction, pul_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )
        ತಳ_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On,
                                               uint32_t ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear_On_ನಮೂದು,
                                               uint32_t ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear_On_Exit,
                                               uint32_t * pul_Notification_ಮೌಲ್ಯ,
                                               TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = xTaskGenericNotifyWait( ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On, ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear_On_ನಮೂದು, ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear_On_Exit, pul_Notification_ಮೌಲ್ಯ, x_Ticks_ಗಮ್ಯ_Wait );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTaskGenericNotifyWait( ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On, ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear_On_ನಮೂದು, ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear_On_Exit, pul_Notification_ಮೌಲ್ಯ, x_Ticks_ಗಮ್ಯ_Wait );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ulTaskGenericNotifyTake( UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On,
                                              ತಳ_Type_t x_Clear_ಎಣಿಕೆ_On_Exit,
                                              TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ulReturn = ulTaskGenericNotifyTake( ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On, x_Clear_ಎಣಿಕೆ_On_Exit, x_Ticks_ಗಮ್ಯ_Wait );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                ulReturn = ulTaskGenericNotifyTake( ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On, x_Clear_ಎಣಿಕೆ_On_Exit, x_Ticks_ಗಮ್ಯ_Wait );
            }

            ಹಿಂತಿರುಗಿ ulReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )
        ತಳ_Type_t MPU_xTaskGenericNotifyStateClear( TaskHandle_t xTask,
                                                     UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = xTaskGenericNotifyStateClear( xTask, ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTaskGenericNotifyStateClear( xTask, ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )
        uint32_t MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( TaskHandle_t xTask,
                                                    UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear,
                                                    uint32_t ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            uint32_t ulReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ulReturn = ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( xTask, ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear, ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                ulReturn = ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( xTask, ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear, ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear );
            }

            ಹಿಂತಿರುಗಿ ulReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 )
        ಸರತಿ_Handle_t MPU_x_ಸರತಿ_Generic_Create( UBaseType_t ux_ಸರತಿ_ಉದ್ದಳತೆ,
                                               UBaseType_t ux_ಅಂಶ_ಗಾತ್ರ,
                                               uint8_t uc_ಸರತಿ_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            ಸರತಿ_Handle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಸರತಿ_Generic_Create( ux_ಸರತಿ_ಉದ್ದಳತೆ, ux_ಅಂಶ_ಗಾತ್ರ, uc_ಸರತಿ_Type );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಸರತಿ_Generic_Create( ux_ಸರತಿ_ಉದ್ದಳತೆ, ux_ಅಂಶ_ಗಾತ್ರ, uc_ಸರತಿ_Type );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 )
        ಸರತಿ_Handle_t MPU_x_ಸರತಿ_Generic_Create_Static( ಸ್ಥಿರಾಂಕ UBaseType_t ux_ಸರತಿ_ಉದ್ದಳತೆ,
                                                     ಸ್ಥಿರಾಂಕ UBaseType_t ux_ಅಂಶ_ಗಾತ್ರ,
                                                     uint8_t * puc_ಸರತಿ_Storage,
                                                     Static_ಸರತಿ_t * px_Static_ಸರತಿ,
                                                     ಸ್ಥಿರಾಂಕ uint8_t uc_ಸರತಿ_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            ಸರತಿ_Handle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಸರತಿ_Generic_Create_Static( ux_ಸರತಿ_ಉದ್ದಳತೆ, ux_ಅಂಶ_ಗಾತ್ರ, puc_ಸರತಿ_Storage, px_Static_ಸರತಿ, uc_ಸರತಿ_Type );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಸರತಿ_Generic_Create_Static( ux_ಸರತಿ_ಉದ್ದಳತೆ, ux_ಅಂಶ_ಗಾತ್ರ, puc_ಸರತಿ_Storage, px_Static_ಸರತಿ, uc_ಸರತಿ_Type );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Generic_Reset( ಸರತಿ_Handle_t px_ಸರತಿ,
                                       ತಳ_Type_t x_New_ಸರತಿ ) /* FREERTOS_SYSTEM_CALL */
    {
        ತಳ_Type_t xReturn;

        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            xReturn = x_ಸರತಿ_Generic_Reset( px_ಸರತಿ, x_New_ಸರತಿ );
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xReturn = x_ಸರತಿ_Generic_Reset( px_ಸರತಿ, x_New_ಸರತಿ );
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Generic_Send( ಸರತಿ_Handle_t x_ಸರತಿ,
                                      ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ,
                                      TickType_t x_Ticks_ಗಮ್ಯ_Wait,
                                      ತಳ_Type_t xCopyPosition ) /* FREERTOS_SYSTEM_CALL */
    {
        ತಳ_Type_t xReturn;

        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            xReturn = x_ಸರತಿ_Generic_Send( x_ಸರತಿ, pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ, x_Ticks_ಗಮ್ಯ_Wait, xCopyPosition );
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xReturn = x_ಸರತಿ_Generic_Send( x_ಸರತಿ, pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ, x_Ticks_ಗಮ್ಯ_Wait, xCopyPosition );
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t px_ಸರತಿ ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            uxReturn = ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ( px_ಸರತಿ );
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            uxReturn = ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ( px_ಸರತಿ );
        }

        ಹಿಂತಿರುಗಿ uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ಸರತಿ_Spaces_ಲಭ್ಯ( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t x_ಸರತಿ ) /* FREERTOS_SYSTEM_CALL */
    {
        UBaseType_t uxReturn;

        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            uxReturn = ux_ಸರತಿ_Spaces_ಲಭ್ಯ( x_ಸರತಿ );
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            uxReturn = ux_ಸರತಿ_Spaces_ಲಭ್ಯ( x_ಸರತಿ );
        }

        ಹಿಂತಿರುಗಿ uxReturn;
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Receive( ಸರತಿ_Handle_t px_ಸರತಿ,
                                  ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                                  TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        ತಳ_Type_t xReturn;

        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            xReturn = x_ಸರತಿ_Receive( px_ಸರತಿ, pv_ಬಫರ್, x_Ticks_ಗಮ್ಯ_Wait );
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xReturn = x_ಸರತಿ_Receive( px_ಸರತಿ, pv_ಬಫರ್, x_Ticks_ಗಮ್ಯ_Wait );
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Peek( ಸರತಿ_Handle_t x_ಸರತಿ,
                               ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                               TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        ತಳ_Type_t xReturn;

        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            xReturn = x_ಸರತಿ_Peek( x_ಸರತಿ, pv_ಬಫರ್, x_Ticks_ಗಮ್ಯ_Wait );
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xReturn = x_ಸರತಿ_Peek( x_ಸರತಿ, pv_ಬಫರ್, x_Ticks_ಗಮ್ಯ_Wait );
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Semaphore_Take( ಸರತಿ_Handle_t x_ಸರತಿ,
                                        TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
    {
        ತಳ_Type_t xReturn;

        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            xReturn = x_ಸರತಿ_Semaphore_Take( x_ಸರತಿ, x_Ticks_ಗಮ್ಯ_Wait );
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            xReturn = x_ಸರತಿ_Semaphore_Take( x_ಸರತಿ, x_Ticks_ಗಮ್ಯ_Wait );
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
        TaskHandle_t MPU_x_ಸರತಿ_Get_Mutex_Holder( ಸರತಿ_Handle_t xSemaphore ) /* FREERTOS_SYSTEM_CALL */
        {
            ಶೂನ್ಯ * xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಸರತಿ_Get_Mutex_Holder( xSemaphore );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಸರತಿ_Get_Mutex_Holder( xSemaphore );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 ) )
        ಸರತಿ_Handle_t MPU_x_ಸರತಿ_Create_Mutex( ಸ್ಥಿರಾಂಕ uint8_t uc_ಸರತಿ_Type ) /* FREERTOS_SYSTEM_CALL */
        {
            ಸರತಿ_Handle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಸರತಿ_Create_Mutex( uc_ಸರತಿ_Type );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಸರತಿ_Create_Mutex( uc_ಸರತಿ_Type );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 ) )
        ಸರತಿ_Handle_t MPU_x_ಸರತಿ_Create_Mutex_Static( ಸ್ಥಿರಾಂಕ uint8_t uc_ಸರತಿ_Type,
                                                   Static_ಸರತಿ_t * px_Static_ಸರತಿ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಸರತಿ_Handle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಸರತಿ_Create_Mutex_Static( uc_ಸರತಿ_Type, px_Static_ಸರತಿ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಸರತಿ_Create_Mutex_Static( uc_ಸರತಿ_Type, px_Static_ಸರತಿ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 ) )
        ಸರತಿ_Handle_t MPU_x_ಸರತಿ_Create_Counting_Semaphore( UBaseType_t ux_ಎಣಿಕೆ_ಮೌಲ್ಯ,
                                                         UBaseType_t ux_Initial_ಎಣಿಕೆ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಸರತಿ_Handle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಸರತಿ_Create_Counting_Semaphore( ux_ಎಣಿಕೆ_ಮೌಲ್ಯ, ux_Initial_ಎಣಿಕೆ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಸರತಿ_Create_Counting_Semaphore( ux_ಎಣಿಕೆ_ಮೌಲ್ಯ, ux_Initial_ಎಣಿಕೆ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 ) )

        ಸರತಿ_Handle_t MPU_x_ಸರತಿ_Create_Counting_Semaphore_Static( ಸ್ಥಿರಾಂಕ UBaseType_t ux_Max_ಎಣಿಕೆ,
                                                               ಸ್ಥಿರಾಂಕ UBaseType_t ux_Initial_ಎಣಿಕೆ,
                                                               Static_ಸರತಿ_t * px_Static_ಸರತಿ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಸರತಿ_Handle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಸರತಿ_Create_Counting_Semaphore_Static( ux_Max_ಎಣಿಕೆ, ux_Initial_ಎಣಿಕೆ, px_Static_ಸರತಿ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಸರತಿ_Create_Counting_Semaphore_Static( ux_Max_ಎಣಿಕೆ, ux_Initial_ಎಣಿಕೆ, px_Static_ಸರತಿ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_RECURSIVE_MUTEXES == 1 )
        ತಳ_Type_t MPU_x_ಸರತಿ_Take_Mutex_Recursive( ಸರತಿ_Handle_t xMutex,
                                                 TickType_t x_ಖಂಡ_ಸಮಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಸರತಿ_Take_Mutex_Recursive( xMutex, x_ಖಂಡ_ಸಮಯ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಸರತಿ_Take_Mutex_Recursive( xMutex, x_ಖಂಡ_ಸಮಯ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_RECURSIVE_MUTEXES == 1 )
        ತಳ_Type_t MPU_x_ಸರತಿ_Give_Mutex_Recursive( ಸರತಿ_Handle_t xMutex ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಸರತಿ_Give_Mutex_Recursive( xMutex );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಸರತಿ_Give_Mutex_Recursive( xMutex );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_USE_ಸರತಿ_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 ) )
        ಸರತಿ_ಗಣ_Handle_t MPU_x_ಸರತಿ_Create_ಗಣ( UBaseType_t ux_Event_ಸರತಿ_ಉದ್ದಳತೆ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಸರತಿ_ಗಣ_Handle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಸರತಿ_Create_ಗಣ( ux_Event_ಸರತಿ_ಉದ್ದಳತೆ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಸರತಿ_Create_ಗಣ( ux_Event_ಸರತಿ_ಉದ್ದಳತೆ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_USE_ಸರತಿ_SETS == 1 ) && ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 ) )
        ಸರತಿ_ಗಣ_Handle_t MPU_x_ಸರತಿ_Create_ಗಣ_Static( ಸ್ಥಿರಾಂಕ UBaseType_t ux_Event_ಸರತಿ_ಉದ್ದಳತೆ,
                                                    uint8_t * puc_ಸರತಿ_Storage,
                                                    Static_ಸರತಿ_t * px_Static_ಸರತಿ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಸರತಿ_ಗಣ_Handle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಸರತಿ_Create_ಗಣ_Static( ux_Event_ಸರತಿ_ಉದ್ದಳತೆ, puc_ಸರತಿ_Storage, px_Static_ಸರತಿ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಸರತಿ_Create_ಗಣ_Static( ux_Event_ಸರತಿ_ಉದ್ದಳತೆ, puc_ಸರತಿ_Storage, px_Static_ಸರತಿ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಸರತಿ_SETS == 1 )
        ಸರತಿ_ಗಣ_Member_Handle_t MPU_x_ಸರತಿ_Select_From_ಗಣ( ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ,
                                                        TickType_t x_ಖಂಡ_ಸಮಯ_Ticks ) /* FREERTOS_SYSTEM_CALL */
        {
            ಸರತಿ_ಗಣ_Member_Handle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಸರತಿ_Select_From_ಗಣ( x_ಸರತಿ_ಗಣ, x_ಖಂಡ_ಸಮಯ_Ticks );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಸರತಿ_Select_From_ಗಣ( x_ಸರತಿ_ಗಣ, x_ಖಂಡ_ಸಮಯ_Ticks );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಸರತಿ_SETS == 1 )
        ತಳ_Type_t MPU_x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ( ಸರತಿ_ಗಣ_Member_Handle_t x_ಸರತಿ_Or_Semaphore,
                                       ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ( x_ಸರತಿ_Or_Semaphore, x_ಸರತಿ_ಗಣ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ( x_ಸರತಿ_Or_Semaphore, x_ಸರತಿ_ಗಣ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಸರತಿ_SETS == 1 )
        ತಳ_Type_t MPU_x_ಸರತಿ_Remove_From_ಗಣ( ಸರತಿ_ಗಣ_Member_Handle_t x_ಸರತಿ_Or_Semaphore,
                                            ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಸರತಿ_Remove_From_ಗಣ( x_ಸರತಿ_Or_Semaphore, x_ಸರತಿ_ಗಣ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಸರತಿ_Remove_From_ಗಣ( x_ಸರತಿ_Or_Semaphore, x_ಸರತಿ_ಗಣ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ config_ಸರತಿ_REGISTRY_ಗಾತ್ರ > 0
        ಶೂನ್ಯ MPU_v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry( ಸರತಿ_Handle_t x_ಸರತಿ,
                                      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pcName ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry( x_ಸರತಿ, pcName );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry( x_ಸರತಿ, pcName );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ಆದರೆ config_ಸರತಿ_REGISTRY_ಗಾತ್ರ > 0
        ಶೂನ್ಯ MPU_v_ಸರತಿ_Unregister_ಸರತಿ( ಸರತಿ_Handle_t x_ಸರತಿ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                v_ಸರತಿ_Unregister_ಸರತಿ( x_ಸರತಿ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                v_ಸರತಿ_Unregister_ಸರತಿ( x_ಸರತಿ );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ಆದರೆ config_ಸರತಿ_REGISTRY_ಗಾತ್ರ > 0
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * MPU_pc_ಸರತಿ_Get_Name( ಸರತಿ_Handle_t x_ಸರತಿ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pcReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                pcReturn = pc_ಸರತಿ_Get_Name( x_ಸರತಿ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                pcReturn = pc_ಸರತಿ_Get_Name( x_ಸರತಿ );
            }

            ಹಿಂತಿರುಗಿ pcReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ MPU_v_ಸರತಿ_Delete( ಸರತಿ_Handle_t x_ಸರತಿ ) /* FREERTOS_SYSTEM_CALL */
    {
        ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
        {
            ಪೋರ್ಟ್_RAISE_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            v_ಸರತಿ_Delete( x_ಸರತಿ );
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

            ಪೋರ್ಟ್_RESET_PRIVILEGE();
            ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            v_ಸರತಿ_Delete( x_ಸರತಿ );
        }
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )
        ಶೂನ್ಯ * MPU_pvTimerGetTimerID( ಸ್ಥಿರಾಂಕ TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ಶೂನ್ಯ * pvReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                pvReturn = pvTimerGetTimerID( xTimer );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                pvReturn = pvTimerGetTimerID( xTimer );
            }

            ಹಿಂತಿರುಗಿ pvReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )
        ಶೂನ್ಯ MPU_v_Timer_ಗಣ_Timer_ID( TimerHandle_t xTimer,
                                   ಶೂನ್ಯ * pvNewID ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                v_Timer_ಗಣ_Timer_ID( xTimer, pvNewID );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                v_Timer_ಗಣ_Timer_ID( xTimer, pvNewID );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )
        ತಳ_Type_t MPU_x_Timer_Is_Timer_ಸಕ್ರಿಯ( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_Timer_Is_Timer_ಸಕ್ರಿಯ( xTimer );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_Timer_Is_Timer_ಸಕ್ರಿಯ( xTimer );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )
        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandle( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            TaskHandle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = xTimerGetTimerDaemonTaskHandle();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTimerGetTimerDaemonTaskHandle();
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )
        ಶೂನ್ಯ MPU_v_Timer_ಗಣ_Reload_ಬಹುಲಕ( TimerHandle_t xTimer,
                                      ಸ್ಥಿರಾಂಕ ತಳ_Type_t xAutoReload ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                v_Timer_ಗಣ_Reload_ಬಹುಲಕ( xTimer, xAutoReload );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                v_Timer_ಗಣ_Reload_ಬಹುಲಕ( xTimer, xAutoReload );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )
        UBaseType_t MPU_ux_Timer_Get_Reload_ಬಹುಲಕ( TimerHandle_t xTimer )
        {
            UBaseType_t uxReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                uxReturn = ux_Timer_Get_Reload_ಬಹುಲಕ( xTimer );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                uxReturn = ux_Timer_Get_Reload_ಬಹುಲಕ( xTimer );
            }

            ಹಿಂತಿರುಗಿ uxReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * MPU_pcTimerGetName( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pcReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                pcReturn = pcTimerGetName( xTimer );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                pcReturn = pcTimerGetName( xTimer );
            }

            ಹಿಂತಿರುಗಿ pcReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )
        TickType_t MPU_xTimerGetPeriod( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = xTimerGetPeriod( xTimer );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTimerGetPeriod( xTimer );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )
        TickType_t MPU_x_Timer_Get_Expiry_ಸಮಯ( TimerHandle_t xTimer ) /* FREERTOS_SYSTEM_CALL */
        {
            TickType_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_Timer_Get_Expiry_ಸಮಯ( xTimer );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_Timer_Get_Expiry_ಸಮಯ( xTimer );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )
        ತಳ_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ಸ್ಥಿರಾಂಕ ತಳ_Type_t xCommandID,
                                                     ಸ್ಥಿರಾಂಕ TickType_t x_Optional_ಮೌಲ್ಯ,
                                                     ತಳ_Type_t * ಸ್ಥಿರಾಂಕ px_Higher_ಆದ್ಯತೆ_Task_Woken,
                                                     ಸ್ಥಿರಾಂಕ TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_ಮೌಲ್ಯ, px_Higher_ಆದ್ಯತೆ_Task_Woken, x_Ticks_ಗಮ್ಯ_Wait );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = xTimerGenericCommandFromTask( xTimer, xCommandID, x_Optional_ಮೌಲ್ಯ, px_Higher_ಆದ್ಯತೆ_Task_Woken, x_Ticks_ಗಮ್ಯ_Wait );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_ಗುಂಪು_Handle_t MPU_x_Event_ಗುಂಪು_Create( ಶೂನ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ಗುಂಪು_Handle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_Event_ಗುಂಪು_Create();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_Event_ಗುಂಪು_Create();
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )
        Event_ಗುಂಪು_Handle_t MPU_x_Event_ಗುಂಪು_Create_Static( Static_Event_ಗುಂಪು_t * px_Event_ಗುಂಪು_ಬಫರ್ ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ಗುಂಪು_Handle_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_Event_ಗುಂಪು_Create_Static( px_Event_ಗುಂಪು_ಬಫರ್ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_Event_ಗುಂಪು_Create_Static( px_Event_ಗುಂಪು_ಬಫರ್ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )
        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                             ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For,
                                             ಸ್ಥಿರಾಂಕ ತಳ_Type_t xClearOnExit,
                                             ಸ್ಥಿರಾಂಕ ತಳ_Type_t x_Wait_For_All_ಬಿಟ್ಟುಗಳು,
                                             TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ಬಿಟ್ಟುಗಳು_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು( x_Event_ಗುಂಪು, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For, xClearOnExit, x_Wait_For_All_ಬಿಟ್ಟುಗಳು, x_Ticks_ಗಮ್ಯ_Wait );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು( x_Event_ಗುಂಪು, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For, xClearOnExit, x_Wait_For_All_ಬಿಟ್ಟುಗಳು, x_Ticks_ಗಮ್ಯ_Wait );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )
        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                              ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ಬಿಟ್ಟುಗಳು_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು( x_Event_ಗುಂಪು, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು( x_Event_ಗುಂಪು, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )
        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                            ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ಬಿಟ್ಟುಗಳು_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು( x_Event_ಗುಂಪು, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು( x_Event_ಗುಂಪು, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )
        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Sync( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                         ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ,
                                         ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For,
                                         TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ಬಿಟ್ಟುಗಳು_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_Event_ಗುಂಪು_Sync( x_Event_ಗುಂಪು, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For, x_Ticks_ಗಮ್ಯ_Wait );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_Event_ಗುಂಪು_Sync( x_Event_ಗುಂಪು, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For, x_Ticks_ಗಮ್ಯ_Wait );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )
        ಶೂನ್ಯ MPU_v_Event_ಗುಂಪು_Delete( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                v_Event_ಗುಂಪು_Delete( x_Event_ಗುಂಪು );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                v_Event_ಗುಂಪು_Delete( x_Event_ಗುಂಪು );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )
        size_t MPU_x_ಹರಿವು_ಬಫರ್_Send( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                      ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * pv_Tx_ದತ್ತಾಂಶ,
                                      size_t x_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                      TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಹರಿವು_ಬಫರ್_Send( x_ಹರಿವು_ಬಫರ್, pv_Tx_ದತ್ತಾಂಶ, x_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು, x_Ticks_ಗಮ್ಯ_Wait );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಹರಿವು_ಬಫರ್_Send( x_ಹರಿವು_ಬಫರ್, pv_Tx_ದತ್ತಾಂಶ, x_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು, x_Ticks_ಗಮ್ಯ_Wait );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )
        size_t MPU_x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು( x_ಹರಿವು_ಬಫರ್ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು( x_ಹರಿವು_ಬಫರ್ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )
        size_t MPU_x_ಹರಿವು_ಬಫರ್_Receive( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                         ಶೂನ್ಯ * pv_Rx_ದತ್ತಾಂಶ,
                                         size_t x_ಬಫರ್_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                         TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಹರಿವು_ಬಫರ್_Receive( x_ಹರಿವು_ಬಫರ್, pv_Rx_ದತ್ತಾಂಶ, x_ಬಫರ್_ಉದ್ದಳತೆ_ಬೈಟುಗಳು, x_Ticks_ಗಮ್ಯ_Wait );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಹರಿವು_ಬಫರ್_Receive( x_ಹರಿವು_ಬಫರ್, pv_Rx_ದತ್ತಾಂಶ, x_ಬಫರ್_ಉದ್ದಳತೆ_ಬೈಟುಗಳು, x_Ticks_ಗಮ್ಯ_Wait );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )
        ಶೂನ್ಯ MPU_v_ಹರಿವು_ಬಫರ್_Delete( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* FREERTOS_SYSTEM_CALL */
        {
            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                v_ಹರಿವು_ಬಫರ್_Delete( x_ಹರಿವು_ಬಫರ್ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                v_ಹರಿವು_ಬಫರ್_Delete( x_ಹರಿವು_ಬಫರ್ );
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )
        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ( x_ಹರಿವು_ಬಫರ್ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ( x_ಹರಿವು_ಬಫರ್ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )
        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು( x_ಹರಿವು_ಬಫರ್ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು( x_ಹರಿವು_ಬಫರ್ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )
        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Reset( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಹರಿವು_ಬಫರ್_Reset( x_ಹರಿವು_ಬಫರ್ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಹರಿವು_ಬಫರ್_Reset( x_ಹರಿವು_ಬಫರ್ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )
        size_t MPU_x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
                xReturn = x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ( x_ಹರಿವು_ಬಫರ್ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ( x_ಹರಿವು_ಬಫರ್ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )
        size_t MPU_x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* FREERTOS_SYSTEM_CALL */
        {
            size_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ( x_ಹರಿವು_ಬಫರ್ );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ( x_ಹರಿವು_ಬಫರ್ );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )
        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                                     size_t xTriggerLevel ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn;

            ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
            {
                ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                xReturn = x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level( x_ಹರಿವು_ಬಫರ್, xTriggerLevel );
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                ಪೋರ್ಟ್_RESET_PRIVILEGE();
                ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                xReturn = x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level( x_ಹರಿವು_ಬಫರ್, xTriggerLevel );
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 ) && ( config_USE_ಹರಿವು_BUFFERS == 1 ) )
        ಹರಿವು_ಬಫರ್_Handle_t MPU_x_ಹರಿವು_ಬಫರ್_Generic_Create( size_t x_ಬಫರ್_ಗಾತ್ರ_ಬೈಟುಗಳು,
                                                             size_t x_Trigger_Level_ಬೈಟುಗಳು,
                                                             ತಳ_Type_t x_ಹರಿವು_ಬಫರ್_Type,
                                                             ಹರಿವು_ಬಫರ್_Callback_Function_t pxSendCompletedCallback,
                                                             ಹರಿವು_ಬಫರ್_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            ಹರಿವು_ಬಫರ್_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ಖಾಲಿ ) &&
                          ( pxReceiveCompletedCallback == ಖಾಲಿ ) );

            ಆದರೆ( ( pxSendCompletedCallback == ಖಾಲಿ ) &&
                ( pxReceiveCompletedCallback == ಖಾಲಿ ) )
            {
                ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
                {
                    ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                    ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                    xReturn = x_ಹರಿವು_ಬಫರ್_Generic_Create( x_ಬಫರ್_ಗಾತ್ರ_ಬೈಟುಗಳು,
                                                          x_Trigger_Level_ಬೈಟುಗಳು,
                                                          x_ಹರಿವು_ಬಫರ್_Type,
                                                          ಖಾಲಿ,
                                                          ಖಾಲಿ );
                    ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                    ಪೋರ್ಟ್_RESET_PRIVILEGE();
                    ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    xReturn = x_ಹರಿವು_ಬಫರ್_Generic_Create( x_ಬಫರ್_ಗಾತ್ರ_ಬೈಟುಗಳು,
                                                          x_Trigger_Level_ಬೈಟುಗಳು,
                                                          x_ಹರಿವು_ಬಫರ್_Type,
                                                          ಖಾಲಿ,
                                                          ಖಾಲಿ );
                }
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                trace_ಹರಿವು_ಬಫರ್_CREATE_FAILED( x_ಹರಿವು_ಬಫರ್_Type );
                xReturn = ಖಾಲಿ;
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 ) && ( config_USE_ಹರಿವು_BUFFERS == 1 ) )
        ಹರಿವು_ಬಫರ್_Handle_t MPU_x_ಹರಿವು_ಬಫರ್_Generic_Create_Static( size_t x_ಬಫರ್_ಗಾತ್ರ_ಬೈಟುಗಳು,
                                                                   size_t x_Trigger_Level_ಬೈಟುಗಳು,
                                                                   ತಳ_Type_t x_ಹರಿವು_ಬಫರ್_Type,
                                                                   uint8_t * ಸ್ಥಿರಾಂಕ puc_ಹರಿವು_ಬಫರ್_Storage_Area,
                                                                   Static_ಹರಿವು_ಬಫರ್_t * ಸ್ಥಿರಾಂಕ px_Static_ಹರಿವು_ಬಫರ್,
                                                                   ಹರಿವು_ಬಫರ್_Callback_Function_t pxSendCompletedCallback,
                                                                   ಹರಿವು_ಬಫರ್_Callback_Function_t pxReceiveCompletedCallback ) /* FREERTOS_SYSTEM_CALL */
        {
            ಹರಿವು_ಬಫರ್_Handle_t xReturn;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ಖಾಲಿ ) &&
                          ( pxReceiveCompletedCallback == ಖಾಲಿ ) );

            ಆದರೆ( ( pxSendCompletedCallback == ಖಾಲಿ ) &&
                ( pxReceiveCompletedCallback == ಖಾಲಿ ) )
            {
                ಆದರೆ( ಪೋರ್ಟ್_IS_PRIVILEGED() == pdFALSE )
                {
                    ಪೋರ್ಟ್_RAISE_PRIVILEGE();
                    ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                    xReturn = x_ಹರಿವು_ಬಫರ್_Generic_Create_Static( x_ಬಫರ್_ಗಾತ್ರ_ಬೈಟುಗಳು,
                                                                x_Trigger_Level_ಬೈಟುಗಳು,
                                                                x_ಹರಿವು_ಬಫರ್_Type,
                                                                puc_ಹರಿವು_ಬಫರ್_Storage_Area,
                                                                px_Static_ಹರಿವು_ಬಫರ್,
                                                                ಖಾಲಿ,
                                                                ಖಾಲಿ );
                    ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();

                    ಪೋರ್ಟ್_RESET_PRIVILEGE();
                    ಪೋರ್ಟ್_ಸ್ಮರಣೆ_BARRIER();
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    xReturn = x_ಹರಿವು_ಬಫರ್_Generic_Create_Static( x_ಬಫರ್_ಗಾತ್ರ_ಬೈಟುಗಳು,
                                                                x_Trigger_Level_ಬೈಟುಗಳು,
                                                                x_ಹರಿವು_ಬಫರ್_Type,
                                                                puc_ಹರಿವು_ಬಫರ್_Storage_Area,
                                                                px_Static_ಹರಿವು_ಬಫರ್,
                                                                ಖಾಲಿ,
                                                                ಖಾಲಿ );
                }
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                trace_ಹರಿವು_ಬಫರ್_CREATE_STATIC_FAILED( xReturn, x_ಹರಿವು_ಬಫರ್_Type );
                xReturn = ಖಾಲಿ;
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
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

    #ಆದರೆ configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #ಅನ್ತರ್ಭಾವ "application_defined_privileged_functions.h"
    #ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 1 ) ) */
/*-----------------------------------------------------------*/
