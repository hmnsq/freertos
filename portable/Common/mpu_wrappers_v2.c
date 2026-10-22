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
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"
#অন্তর্ভাব "queue.h"
#অন্তর্ভাব "timers.h"
#অন্তর্ভাব "event_groups.h"
#অন্তর্ভাব "stream_buffer.h"
#অন্তর্ভাব "mpu_prototypes.h"
#অন্তর্ভাব "mpu_syscall_numbers.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#যদি ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #ifndef config_PROTECTED_KERNEL_OBJECT_POOL_আকার
        #error config_PROTECTED_KERNEL_OBJECT_POOL_আকার must be defined to maximum সংখ্যা of kernel objects in the application.
    #endif

/**
 * @brief Offset added to the index before returning to the user.
 *
 * If the actual handle is stored at index i, ( i + INDEX_OFFSET )
 * is returned to the user.
 */
    #define সূচক_OFFSET    1

/**
 * @brief Opaque type for a kernel object.
 */
    কাঠামো OpaqueObject;
    প্রকারলেখ কাঠামো OpaqueObject * OpaqueObjectHandle_t;

/**
 * @brief Defines kernel object in the kernel object pool.
 */
    প্রকারলেখ কাঠামো KernelObject
    {
        OpaqueObjectHandle_t xInternalObjectHandle;
        uint32_t ulKernelObjectType;
        শূন্য * pv_Kernel_Object_তথ্য;
    } KernelObject_t;

/**
 * @brief Kernel object types.
 */
    #define KERNEL_OBJECT_TYPE_INVALID          ( 0UL )
    #define KERNEL_OBJECT_TYPE_QUEUE            ( 1UL )
    #define KERNEL_OBJECT_TYPE_TASK             ( 2UL )
    #define KERNEL_OBJECT_TYPE_STREAM_বাফার    ( 3UL )
    #define KERNEL_OBJECT_TYPE_EVENT_GROUP      ( 4UL )
    #define KERNEL_OBJECT_TYPE_TIMER            ( 5UL )

/**
 * @brief Checks whether an external index is valid or not.
 */
    #define IS_EXTERNAL_সূচক_VALID( l_সূচক )   \
    ( ( ( ( l_সূচক ) >= সূচক_OFFSET ) &&       \
        ( ( l_সূচক ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_আকার + সূচক_OFFSET ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Checks whether an internal index is valid or not.
 */
    #define IS_INTERNAL_সূচক_VALID( l_সূচক )   \
    ( ( ( ( l_সূচক ) >= 0 ) &&                  \
        ( ( l_সূচক ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_আকার ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Converts an internal index into external.
 */
    #define CONVERT_TO_EXTERNAL_সূচক( l_সূচক )    ( ( l_সূচক ) + সূচক_OFFSET )

/**
 * @brief Converts an external index into internal.
 */
    #define CONVERT_TO_INTERNAL_সূচক( l_সূচক )    ( ( l_সূচক ) - সূচক_OFFSET )

/**
 * @brief Max value that fits in a UBaseType_t type.
 */
    #define mpuUBASETYPE_MAX    ( ~( ( UBaseType_t ) 0 ) )

/**
 * @brief Check if multiplying a and b will result in overflow.
 */
    #define mpuMULTIPLY_BASETYPE_WILL_OVERFLOW( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( mpuUBASETYPE_MAX / ( a ) ) ) )

/**
 * @brief Get the index of a free slot in the kernel object pool.
 *
 * If a free slot is found, this function marks the slot as
 * "not free".
 *
 * @return Index of a free slot is returned, if a free slot is
 *         found. Otherwise -1 is returned.
 */
    স্থির int32_t MPU_Get_Free_সূচক_In_Kernel_Object_Pool( শূন্য ) PRIVILEGED_FUNCTION;

/**
 * @brief Set the given index as free in the kernel object pool.
 *
 * @param lIndex The index to set as free.
 */
    স্থির শূন্য MPU_Set_সূচক_Free_In_Kernel_Object_Pool( int32_t l_সূচক ) PRIVILEGED_FUNCTION;

/**
 * @brief Get the index at which a given kernel object is stored.
 *
 * @param xHandle The given kernel object handle.
 * @param ulKernelObjectType The kernel object type.
 *
 * @return Index at which the kernel object is stored if it is a valid
 *         handle, -1 otherwise.
 */
    স্থির int32_t MPU_Get_সূচক_For_Handle( OpaqueObjectHandle_t xHandle,
                                          uint32_t ulKernelObjectType ) PRIVILEGED_FUNCTION;

/**
 * @brief Store the given kernel object handle at the given index in
 *        the kernel object pool.
 *
 * @param lIndex Index to store the given handle at.
 * @param xHandle Kernel object handle to store.
 * @param pvKernelObjectData The data associated with the kernel object.
 *        Currently, only used for timer objects to store timer callback.
 * @param ulKernelObjectType The kernel object type.
 */
    স্থির শূন্য MPU_Store_Handle_And_তথ্য_At_সূচক( int32_t l_সূচক,
                                               OpaqueObjectHandle_t xHandle,
                                               শূন্য * pv_Kernel_Object_তথ্য,
                                               uint32_t ulKernelObjectType ) PRIVILEGED_FUNCTION;

/**
 * @brief Get the kernel object handle at the given index from
 *        the kernel object pool.
 *
 * @param lIndex Index at which to get the kernel object handle.
 * @param ulKernelObjectType The kernel object type.
 *
 * @return The kernel object handle at the index.
 */
    স্থির OpaqueObjectHandle_t MPU_Get_Handle_At_সূচক( int32_t l_সূচক,
                                                      uint32_t ulKernelObjectType ) PRIVILEGED_FUNCTION;

    #যদি ( configUSE_TIMERS == 1 )

/**
 * @brief The function registered as callback for all the timers.
 *
 * We intercept all the timer callbacks so that we can call application
 * callbacks with opaque handle.
 *
 * @param xInternalHandle The internal timer handle.
 */
        স্থির শূন্য MPU_TimerCallback( TimerHandle_t xInternalHandle ) PRIVILEGED_FUNCTION;

    #endif /* #if ( configUSE_TIMERS == 1 ) */

/*
 * Wrappers to keep all the casting in one place.
 */
    #define MPU_Store_Queue_Handle_At_সূচক( l_সূচক, xHandle )                 MPU_Store_Handle_And_তথ্য_At_সূচক( ( l_সূচক ), ( OpaqueObjectHandle_t ) ( xHandle ), ফাঁকা, KERNEL_OBJECT_TYPE_QUEUE )
    #define MPU_Get_Queue_Handle_At_সূচক( l_সূচক )                            ( QueueHandle_t ) MPU_Get_Handle_At_সূচক( ( l_সূচক ), KERNEL_OBJECT_TYPE_QUEUE )

    #যদি ( configUSE_QUEUE_SETS == 1 )
        #define MPU_Store_Queue_Set_Handle_At_সূচক( l_সূচক, xHandle )          MPU_Store_Handle_And_তথ্য_At_সূচক( ( l_সূচক ), ( OpaqueObjectHandle_t ) ( xHandle ), ফাঁকা, KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_Get_Queue_Set_Handle_At_সূচক( l_সূচক )                     ( QueueSetHandle_t ) MPU_Get_Handle_At_সূচক( ( l_সূচক ), KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_Store_Queue_Set_Member_Handle_At_সূচক( l_সূচক, xHandle )    MPU_Store_Handle_And_তথ্য_At_সূচক( ( l_সূচক ), ( OpaqueObjectHandle_t ) ( xHandle ), ফাঁকা, KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_Get_Queue_Set_Member_Handle_At_সূচক( l_সূচক )               ( QueueSetMemberHandle_t ) MPU_Get_Handle_At_সূচক( ( l_সূচক ), KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_Get_সূচক_For_Queue_Set_Member_Handle( xHandle )             MPU_Get_সূচক_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_QUEUE )
    #endif

/*
 * Wrappers to keep all the casting in one place for Task APIs.
 */
    #define MPU_Store_Task_Handle_At_সূচক( l_সূচক, xHandle )            MPU_Store_Handle_And_তথ্য_At_সূচক( ( l_সূচক ), ( OpaqueObjectHandle_t ) ( xHandle ), ফাঁকা, KERNEL_OBJECT_TYPE_TASK )
    #define MPU_Get_Task_Handle_At_সূচক( l_সূচক )                       ( TaskHandle_t ) MPU_Get_Handle_At_সূচক( ( l_সূচক ), KERNEL_OBJECT_TYPE_TASK )
    #define MPU_Get_সূচক_For_Task_Handle( xHandle )                     MPU_Get_সূচক_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TASK )

    #যদি ( configUSE_EVENT_GROUPS == 1 )
/*
 * Wrappers to keep all the casting in one place for Event Group APIs.
 */
        #define MPU_Store_Event_Group_Handle_At_সূচক( l_সূচক, xHandle )      MPU_Store_Handle_And_তথ্য_At_সূচক( ( l_সূচক ), ( OpaqueObjectHandle_t ) ( xHandle ), ফাঁকা, KERNEL_OBJECT_TYPE_EVENT_GROUP )
        #define MPU_Get_Event_Group_Handle_At_সূচক( l_সূচক )                 ( EventGroupHandle_t ) MPU_Get_Handle_At_সূচক( ( l_সূচক ), KERNEL_OBJECT_TYPE_EVENT_GROUP )
        #define MPU_Get_সূচক_For_Event_Group_Handle( xHandle )               MPU_Get_সূচক_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_EVENT_GROUP )

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */

    #যদি ( configUSE_STREAM_BUFFERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Stream Buffer APIs.
 */
        #define MPU_Store_Stream_বাফার_Handle_At_সূচক( l_সূচক, xHandle )    MPU_Store_Handle_And_তথ্য_At_সূচক( ( l_সূচক ), ( OpaqueObjectHandle_t ) ( xHandle), ফাঁকা, KERNEL_OBJECT_TYPE_STREAM_বাফার )
        #define MPU_Get_Stream_বাফার_Handle_At_সূচক( l_সূচক )               ( Stream_বাফার_Handle_t ) MPU_Get_Handle_At_সূচক( ( l_সূচক ), KERNEL_OBJECT_TYPE_STREAM_বাফার )
        #define MPU_Get_সূচক_For_Stream_বাফার_Handle( xHandle )             MPU_Get_সূচক_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_STREAM_বাফার )

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

    #যদি ( configUSE_TIMERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Timer APIs.
 */
        #define MPU_Store_Timer_Handle_At_সূচক( l_সূচক, xHandle, pxApplicationCallback )    MPU_Store_Handle_And_তথ্য_At_সূচক( ( l_সূচক ), ( OpaqueObjectHandle_t ) ( xHandle ), ( শূন্য * ) ( pxApplicationCallback ), KERNEL_OBJECT_TYPE_TIMER )
        #define MPU_Get_Timer_Handle_At_সূচক( l_সূচক )                                      ( TimerHandle_t ) MPU_Get_Handle_At_সূচক( ( l_সূচক ), KERNEL_OBJECT_TYPE_TIMER )
        #define MPU_Get_সূচক_For_Timer_Handle( xHandle )                                    MPU_Get_সূচক_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TIMER )

    #endif /* #if ( configUSE_TIMERS == 1 ) */

/*-----------------------------------------------------------*/

/**
 * @brief Kernel object pool.
 */
    PRIVILEGED_তথ্য স্থির KernelObject_t xKernelObjectPool[ config_PROTECTED_KERNEL_OBJECT_POOL_আকার ] = { 0 };
/*-----------------------------------------------------------*/

    স্থির int32_t MPU_Get_Free_সূচক_In_Kernel_Object_Pool( শূন্য ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_Free_সূচক = -1;

        /* This function is called only from resource create APIs
         * which are not supposed to be called from ISRs. Therefore,
         * we only need to suspend the scheduler and do not require
         * critical section. */
        vTaskSuspendAll();
        {
            জন্য( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_আকার; i++ )
            {
                যদি( xKernelObjectPool[ i ].xInternalObjectHandle == ফাঁকা )
                {
                    /* Mark this index as not free. */
                    xKernelObjectPool[ i ].xInternalObjectHandle = ( OpaqueObjectHandle_t ) ( ~0U );
                    l_Free_সূচক = i;
                    বিরতি;
                }
            }
        }
        ( শূন্য ) xTaskResumeAll();

        ফেরত l_Free_সূচক;
    }
/*-----------------------------------------------------------*/

    স্থির শূন্য MPU_Set_সূচক_Free_In_Kernel_Object_Pool( int32_t l_সূচক ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_INTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE );

        taskENTER_CRITICAL();
        {
            xKernelObjectPool[ l_সূচক ].xInternalObjectHandle = ফাঁকা;
            xKernelObjectPool[ l_সূচক ].ulKernelObjectType = KERNEL_OBJECT_TYPE_INVALID;
            xKernelObjectPool[ l_সূচক ].pv_Kernel_Object_তথ্য = ফাঁকা;
        }
        taskEXIT_CRITICAL();
    }
/*-----------------------------------------------------------*/

    স্থির int32_t MPU_Get_সূচক_For_Handle( OpaqueObjectHandle_t xHandle,
                                          uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_সূচক = -1;

        configASSERT( xHandle != ফাঁকা );

        জন্য( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_আকার; i++ )
        {
            যদি( ( xKernelObjectPool[ i ].xInternalObjectHandle == xHandle ) &&
                ( xKernelObjectPool[ i ].ulKernelObjectType == ulKernelObjectType ) )
            {
                l_সূচক = i;
                বিরতি;
            }
        }

        ফেরত l_সূচক;
    }
/*-----------------------------------------------------------*/

    স্থির শূন্য MPU_Store_Handle_And_তথ্য_At_সূচক( int32_t l_সূচক,
                                               OpaqueObjectHandle_t xHandle,
                                               শূন্য * pv_Kernel_Object_তথ্য,
                                               uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_INTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE );
        xKernelObjectPool[ l_সূচক ].xInternalObjectHandle = xHandle;
        xKernelObjectPool[ l_সূচক ].ulKernelObjectType = ulKernelObjectType;
        xKernelObjectPool[ l_সূচক ].pv_Kernel_Object_তথ্য = pv_Kernel_Object_তথ্য;
    }
/*-----------------------------------------------------------*/

    স্থির OpaqueObjectHandle_t MPU_Get_Handle_At_সূচক( int32_t l_সূচক,
                                                      uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        OpaqueObjectHandle_t xObjectHandle = ফাঁকা;

        configASSERT( IS_INTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE );

        যদি( xKernelObjectPool[ l_সূচক ].ulKernelObjectType == ulKernelObjectType )
        {
            xObjectHandle = xKernelObjectPool[ l_সূচক ].xInternalObjectHandle;
        }

        ফেরত xObjectHandle;
    }
/*-----------------------------------------------------------*/

    #যদি ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        শূন্য vGrantAccessToKernelObject( TaskHandle_t xExternalTaskHandle,
                                         int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;

            যদি( IS_EXTERNAL_সূচক_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                যদি( xExternalTaskHandle == ফাঁকা )
                {
                    vPortGrantAccessToKernelObject( xExternalTaskHandle, CONVERT_TO_INTERNAL_সূচক( lExternalKernelObjectHandle ) );
                }
                অন্যথা
                {
                    l_External_Task_সূচক = ( int32_t ) xExternalTaskHandle;

                    যদি( IS_EXTERNAL_সূচক_VALID( l_External_Task_সূচক ) != pdFALSE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_External_Task_সূচক ) );

                        যদি( xInternalTaskHandle != ফাঁকা )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle,
                                                            CONVERT_TO_INTERNAL_সূচক( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #endif /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        শূন্য vRevokeAccessToKernelObject( TaskHandle_t xExternalTaskHandle,
                                          int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;

            যদি( IS_EXTERNAL_সূচক_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                যদি( xExternalTaskHandle == ফাঁকা )
                {
                    vPortRevokeAccessToKernelObject( xExternalTaskHandle, CONVERT_TO_INTERNAL_সূচক( lExternalKernelObjectHandle ) );
                }
                অন্যথা
                {
                    l_External_Task_সূচক = ( int32_t ) xExternalTaskHandle;

                    যদি( IS_EXTERNAL_সূচক_VALID( l_External_Task_সূচক ) != pdFALSE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_External_Task_সূচক ) );

                        যদি( xInternalTaskHandle != ফাঁকা )
                        {
                            vPortRevokeAccessToKernelObject( xInternalTaskHandle,
                                                             CONVERT_TO_INTERNAL_সূচক( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #endif /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        স্থির শূন্য MPU_TimerCallback( TimerHandle_t xInternalHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t i, l_সূচক = -1;
            TimerHandle_t xExternalHandle = ফাঁকা;
            TimerCallbackFunction_t pxApplicationCallBack = ফাঁকা;

            /* Coming from the timer task and therefore, should be valid. */
            configASSERT( xInternalHandle != ফাঁকা );

            জন্য( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_আকার; i++ )
            {
                যদি( ( ( TimerHandle_t ) xKernelObjectPool[ i ].xInternalObjectHandle == xInternalHandle ) &&
                    ( xKernelObjectPool[ i ].ulKernelObjectType == KERNEL_OBJECT_TYPE_TIMER ) )
                {
                    l_সূচক = i;
                    বিরতি;
                }
            }

            configASSERT( l_সূচক != -1 );
            xExternalHandle = ( TimerHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );

            pxApplicationCallBack = ( TimerCallbackFunction_t ) xKernelObjectPool[ l_সূচক ].pv_Kernel_Object_তথ্য;
            pxApplicationCallBack( xExternalHandle );
        }

    #endif /* #if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for tasks APIs.                   */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_xTaskDelayUntil == 1 )

        BaseType_t MPU_xTaskDelayUntilImpl( TickType_t * ধ্রুবক pxPreviousWakeTime,
                                            TickType_t xTimeIncrement ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskDelayUntilImpl( TickType_t * ধ্রুবক pxPreviousWakeTime,
                                            TickType_t xTimeIncrement ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xIsPreviousWakeTimeAccessible = pdFALSE;

            যদি( ( pxPreviousWakeTime != ফাঁকা ) && ( xTimeIncrement > 0U ) )
            {
                xIsPreviousWakeTimeAccessible = x_Port_Is_Authorized_To_Access_বাফার( pxPreviousWakeTime,
                                                                                 আকার( TickType_t ),
                                                                                 ( tskMPU_WRITE_PERMISSION | tskMPU_READ_PERMISSION ) );

                যদি( xIsPreviousWakeTimeAccessible == pdTRUE )
                {
                    xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_xTaskAbortDelay == 1 )

        BaseType_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = ( int32_t ) xTask;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTaskHandle != ফাঁকা )
                    {
                        xReturn = xTaskAbortDelay( xInternalTaskHandle );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_vTaskDelay == 1 )

        শূন্য MPU_vTaskDelayImpl( TickType_t xTicksToDelay ) PRIVILEGED_FUNCTION;

        শূন্য MPU_vTaskDelayImpl( TickType_t xTicksToDelay ) /* PRIVILEGED_FUNCTION */
        {
            vTaskDelay( xTicksToDelay );
        }

    #endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_uxTaskPriorityGet == 1 )

        UBaseType_t MPU_uxTaskPriorityGetImpl( ধ্রুবক TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskPriorityGetImpl( ধ্রুবক TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;

            যদি( pxTask == ফাঁকা )
            {
                uxReturn = uxTaskPriorityGet( pxTask );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) pxTask;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xInternalTaskHandle != ফাঁকা )
                        {
                            uxReturn = uxTaskPriorityGet( xInternalTaskHandle );
                        }
                    }
                }
            }

            ফেরত uxReturn;
        }

    #endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            eTaskState eReturn = eInvalid;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            l_সূচক = ( int32_t ) pxTask;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTaskHandle != ফাঁকা )
                    {
                        eReturn = eTaskGetState( xInternalTaskHandle );
                    }
                }
            }

            ফেরত eReturn;
        }

    #endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TRACE_FACILITY == 1 )

        শূন্য MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   TaskStatus_t * pxTaskStatus,
                                   BaseType_t x_Get_Free_স্তূপ_Space,
                                   eTaskState eState ) PRIVILEGED_FUNCTION;

        শূন্য MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   TaskStatus_t * pxTaskStatus,
                                   BaseType_t x_Get_Free_স্তূপ_Space,
                                   eTaskState eState ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            BaseType_t xIsTaskStatusWriteable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            xIsTaskStatusWriteable = x_Port_Is_Authorized_To_Access_বাফার( pxTaskStatus,
                                                                      আকার( TaskStatus_t ),
                                                                      tskMPU_WRITE_PERMISSION );

            যদি( xIsTaskStatusWriteable == pdTRUE )
            {
                যদি( xTask == ফাঁকা )
                {
                    vTaskGetInfo( xTask, pxTaskStatus, x_Get_Free_স্তূপ_Space, eState );
                }
                অন্যথা
                {
                    l_সূচক = ( int32_t ) xTask;

                    যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                            যদি( xInternalTaskHandle != ফাঁকা )
                            {
                                vTaskGetInfo( xInternalTaskHandle, pxTaskStatus, x_Get_Free_স্তূপ_Space, eState );
                            }
                        }
                    }
                }
            }
        }

    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( শূন্য ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( শূন্য ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xIdleTaskHandle = ফাঁকা;

            xIdleTaskHandle = xTaskGetIdleTaskHandle();

            ফেরত xIdleTaskHandle;
        }

    #endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_vTaskSuspend == 1 )

        শূন্য MPU_vTaskSuspendImpl( TaskHandle_t pxTaskToSuspend ) PRIVILEGED_FUNCTION;

        শূন্য MPU_vTaskSuspendImpl( TaskHandle_t pxTaskToSuspend ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            যদি( pxTaskToSuspend == ফাঁকা )
            {
                vTaskSuspend( pxTaskToSuspend );
            }
            অন্যথা
            {
                /* After the scheduler starts, only privileged tasks are allowed
                 * to suspend other tasks. */
                #যদি ( INCLUDE_xTaskGetSchedulerState == 1 )
                    যদি( ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) || ( portIS_TASK_PRIVILEGED() == pdTRUE ) )
                #অন্যথা
                    যদি( portIS_TASK_PRIVILEGED() == pdTRUE )
                #endif
                {
                    l_সূচক = ( int32_t ) pxTaskToSuspend;

                    যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                            যদি( xInternalTaskHandle != ফাঁকা )
                            {
                                vTaskSuspend( xInternalTaskHandle );
                            }
                        }
                    }
                }
            }
        }

    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_vTaskSuspend == 1 )

        শূন্য MPU_vTaskResumeImpl( TaskHandle_t pxTaskToResume ) PRIVILEGED_FUNCTION;

        শূন্য MPU_vTaskResumeImpl( TaskHandle_t pxTaskToResume ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            l_সূচক = ( int32_t ) pxTaskToResume;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTaskHandle != ফাঁকা )
                    {
                        vTaskResume( xInternalTaskHandle );
                    }
                }
            }
        }

    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_গুনতি_Impl( শূন্য ) PRIVILEGED_FUNCTION;

    TickType_t MPU_x_Task_Get_Tick_গুনতি_Impl( শূন্য ) /* PRIVILEGED_FUNCTION */
    {
        TickType_t xReturn;

        xReturn = x_Task_Get_Tick_গুনতি();

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_সংখ্যা_Of_Tasks_Impl( শূন্য ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Task_Get_সংখ্যা_Of_Tasks_Impl( শূন্য ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn;

        uxReturn = ux_Task_Get_সংখ্যা_Of_Tasks();

        ফেরত uxReturn;
    }
/*-----------------------------------------------------------*/

    #যদি ( configGENERATE_RUN_TIME_STATS == 1 )

        config_RUN_TIME_গণক_TYPE MPU_ul_Task_Get_Run_Time_গণক_Impl( ধ্রুবক TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_RUN_TIME_গণক_TYPE MPU_ul_Task_Get_Run_Time_গণক_Impl( ধ্রুবক TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_RUN_TIME_গণক_TYPE xReturn = 0;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            যদি( xTask == ফাঁকা )
            {
                xReturn = ul_Task_Get_Run_Time_গণক( xTask );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) xTask;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xInternalTaskHandle != ফাঁকা )
                        {
                            xReturn = ul_Task_Get_Run_Time_গণক( xInternalTaskHandle );
                        }
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configGENERATE_RUN_TIME_STATS == 1 )

        config_RUN_TIME_গণক_TYPE MPU_ulTaskGetRunTimePercentImpl( ধ্রুবক TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_RUN_TIME_গণক_TYPE MPU_ulTaskGetRunTimePercentImpl( ধ্রুবক TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_RUN_TIME_গণক_TYPE xReturn = 0;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            যদি( xTask == ফাঁকা )
            {
                xReturn = ulTaskGetRunTimePercent( xTask );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) xTask;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xInternalTaskHandle != ফাঁকা )
                        {
                            xReturn = ulTaskGetRunTimePercent( xInternalTaskHandle );
                        }
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_RUN_TIME_গণক_TYPE MPU_ulTaskGetIdleRunTimePercentImpl( শূন্য ) PRIVILEGED_FUNCTION;

        config_RUN_TIME_গণক_TYPE MPU_ulTaskGetIdleRunTimePercentImpl( শূন্য ) /* PRIVILEGED_FUNCTION */
        {
            config_RUN_TIME_গণক_TYPE xReturn;

            xReturn = ulTaskGetIdleRunTimePercent();

            ফেরত xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_RUN_TIME_গণক_TYPE MPU_ul_Task_Get_Idle_Run_Time_গণক_Impl( শূন্য ) PRIVILEGED_FUNCTION;

        config_RUN_TIME_গণক_TYPE MPU_ul_Task_Get_Idle_Run_Time_গণক_Impl( শূন্য ) /* PRIVILEGED_FUNCTION */
        {
            config_RUN_TIME_গণক_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_Run_Time_গণক();

            ফেরত xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_APPLICATION_TASK_TAG == 1 )

        শূন্য MPU_vTaskSetApplicationTaskTagImpl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_Tag_মান ) PRIVILEGED_FUNCTION;

        শূন্য MPU_vTaskSetApplicationTaskTagImpl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_Tag_মান ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            যদি( xTask == ফাঁকা )
            {
                vTaskSetApplicationTaskTag( xTask, px_Tag_মান );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) xTask;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xInternalTaskHandle != ফাঁকা )
                        {
                            vTaskSetApplicationTaskTag( xInternalTaskHandle, px_Tag_মান );
                        }
                    }
                }
            }
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_APPLICATION_TASK_TAG == 1 )

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = ফাঁকা;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            যদি( xTask == ফাঁকা )
            {
                xReturn = xTaskGetApplicationTaskTag( xTask );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) xTask;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xInternalTaskHandle != ফাঁকা )
                        {
                            xReturn = xTaskGetApplicationTaskTag( xInternalTaskHandle );
                        }
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( config_অঙ্ক_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        শূন্য MPU_vTaskSetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToSet,
                                                        BaseType_t x_সূচক,
                                                        শূন্য * pv_মান ) PRIVILEGED_FUNCTION;

        শূন্য MPU_vTaskSetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToSet,
                                                        BaseType_t x_সূচক,
                                                        শূন্য * pv_মান ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            যদি( xTaskToSet == ফাঁকা )
            {
                vTaskSetThreadLocalStoragePointer( xTaskToSet, x_সূচক, pv_মান );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) xTaskToSet;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xInternalTaskHandle != ফাঁকা )
                        {
                            vTaskSetThreadLocalStoragePointer( xInternalTaskHandle, x_সূচক, pv_মান );
                        }
                    }
                }
            }
        }

    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #যদি ( config_অঙ্ক_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        শূন্য * MPU_pvTaskGetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToQuery,
                                                           BaseType_t x_সূচক ) PRIVILEGED_FUNCTION;

        শূন্য * MPU_pvTaskGetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToQuery,
                                                           BaseType_t x_সূচক ) /* PRIVILEGED_FUNCTION */
        {
            শূন্য * pvReturn = ফাঁকা;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            যদি( xTaskToQuery == ফাঁকা )
            {
                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, x_সূচক );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) xTaskToQuery;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xInternalTaskHandle != ফাঁকা )
                        {
                            pvReturn = pvTaskGetThreadLocalStoragePointer( xInternalTaskHandle, x_সূচক );
                        }
                    }
                }
            }

            ফেরত pvReturn;
        }

    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemStateImpl( TaskStatus_t * pxTaskStatusArray,
                                                  UBaseType_t ux_Array_আকার,
                                                  config_RUN_TIME_গণক_TYPE * pul_যোগ_Run_Time ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskGetSystemStateImpl( TaskStatus_t * pxTaskStatusArray,
                                                  UBaseType_t ux_Array_আকার,
                                                  config_RUN_TIME_গণক_TYPE * pul_যোগ_Run_Time ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            BaseType_t xIsTaskStatusArrayWriteable = pdFALSE;
            BaseType_t x_Is_যোগ_Run_Time_Writeable = pdFALSE;

            যদি( mpuMULTIPLY_BASETYPE_WILL_OVERFLOW( আকার( TaskStatus_t ), ux_Array_আকার ) == 0 )
            {
                xIsTaskStatusArrayWriteable = x_Port_Is_Authorized_To_Access_বাফার( pxTaskStatusArray,
                                                                               আকার( TaskStatus_t ) * ( size_t ) ux_Array_আকার,
                                                                               tskMPU_WRITE_PERMISSION );

                যদি( pul_যোগ_Run_Time != ফাঁকা )
                {
                    x_Is_যোগ_Run_Time_Writeable = x_Port_Is_Authorized_To_Access_বাফার( pul_যোগ_Run_Time,
                                                                                আকার( config_RUN_TIME_গণক_TYPE ),
                                                                                tskMPU_WRITE_PERMISSION );
                }

                যদি( ( xIsTaskStatusArrayWriteable == pdTRUE ) &&
                    ( ( pul_যোগ_Run_Time == ফাঁকা ) || ( x_Is_যোগ_Run_Time_Writeable == pdTRUE ) ) )
                {
                    uxReturn = uxTaskGetSystemState( pxTaskStatusArray, ux_Array_আকার, pul_যোগ_Run_Time );
                }
            }

            ফেরত uxReturn;
        }

    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_ux_Task_Get_স্তূপ_উপরের_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            যদি( xTask == ফাঁকা )
            {
                uxReturn = ux_Task_Get_স্তূপ_উপরের_Water_Mark( xTask );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) xTask;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xInternalTaskHandle != ফাঁকা )
                        {
                            uxReturn = ux_Task_Get_স্তূপ_উপরের_Water_Mark( xInternalTaskHandle );
                        }
                    }
                }
            }

            ফেরত uxReturn;
        }

    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_ux_Task_Get_স্তূপ_উপরের_Water_Mark2 == 1 )

        config_স্তূপ_DEPTH_TYPE MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark2_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_স্তূপ_DEPTH_TYPE MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark2_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_স্তূপ_DEPTH_TYPE uxReturn = 0;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            যদি( xTask == ফাঁকা )
            {
                uxReturn = ux_Task_Get_স্তূপ_উপরের_Water_Mark2( xTask );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) xTask;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xInternalTaskHandle != ফাঁকা )
                        {
                            uxReturn = ux_Task_Get_স্তূপ_উপরের_Water_Mark2( xInternalTaskHandle );
                        }
                    }
                }
            }

            ফেরত uxReturn;
        }

    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( শূন্য ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( শূন্য ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            TaskHandle_t xExternalTaskHandle = ফাঁকা;
            int32_t l_সূচক;

            xInternalTaskHandle = xTaskGetCurrentTaskHandle();

            যদি( xInternalTaskHandle != ফাঁকা )
            {
                l_সূচক = MPU_Get_সূচক_For_Task_Handle( xInternalTaskHandle );

                যদি( l_সূচক != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
            }

            ফেরত xExternalTaskHandle;
        }

    #endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_xTaskGetSchedulerState == 1 )

        BaseType_t MPU_xTaskGetSchedulerStateImpl( শূন্য ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGetSchedulerStateImpl( শূন্য ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = taskSCHEDULER_NOT_STARTED;

            xReturn = xTaskGetSchedulerState();

            ফেরত xReturn;
        }

    #endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    শূন্য MPU_vTaskSetTimeOutStateImpl( TimeOut_t * ধ্রুবক pxTimeOut ) PRIVILEGED_FUNCTION;

    শূন্য MPU_vTaskSetTimeOutStateImpl( TimeOut_t * ধ্রুবক pxTimeOut ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xIsTimeOutWriteable = pdFALSE;

        যদি( pxTimeOut != ফাঁকা )
        {
            xIsTimeOutWriteable = x_Port_Is_Authorized_To_Access_বাফার( pxTimeOut,
                                                                   আকার( TimeOut_t ),
                                                                   tskMPU_WRITE_PERMISSION );

            যদি( xIsTimeOutWriteable == pdTRUE )
            {
                vTaskSetTimeOutState( pxTimeOut );
            }
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCheckForTimeOutImpl( TimeOut_t * ধ্রুবক pxTimeOut,
                                             TickType_t * ধ্রুবক pxTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xTaskCheckForTimeOutImpl( TimeOut_t * ধ্রুবক pxTimeOut,
                                             TickType_t * ধ্রুবক pxTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFALSE;
        BaseType_t xIsTimeOutWriteable = pdFALSE;
        BaseType_t xIsTicksToWaitWriteable = pdFALSE;

        যদি( ( pxTimeOut != ফাঁকা ) && ( pxTicksToWait != ফাঁকা ) )
        {
            xIsTimeOutWriteable = x_Port_Is_Authorized_To_Access_বাফার( pxTimeOut,
                                                                   আকার( TimeOut_t ),
                                                                   tskMPU_WRITE_PERMISSION );
            xIsTicksToWaitWriteable = x_Port_Is_Authorized_To_Access_বাফার( pxTicksToWait,
                                                                       আকার( TickType_t ),
                                                                       tskMPU_WRITE_PERMISSION );

            যদি( ( xIsTimeOutWriteable == pdTRUE ) && ( xIsTicksToWaitWriteable == pdTRUE ) )
            {
                xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
            }
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotify( TaskHandle_t xTaskToNotify,
                                           UBaseType_t ux_সূচক_To_Notify,
                                           uint32_t ul_মান,
                                           eNotifyAction eAction,
                                           uint32_t * pul_Previous_Notification_মান ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn = pdFAIL;
            xTaskGenericNotifyParams_t xParams;

            xParams.xTaskToNotify = xTaskToNotify;
            xParams.ux_সূচক_To_Notify = ux_সূচক_To_Notify;
            xParams.ul_মান = ul_মান;
            xParams.eAction = eAction;
            xParams.pul_Previous_Notification_মান = pul_Previous_Notification_মান;

            xReturn = MPU_xTaskGenericNotifyEntry( &( xParams ) );

            ফেরত xReturn;
        }

        BaseType_t MPU_xTaskGenericNotifyImpl( ধ্রুবক xTaskGenericNotifyParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyImpl( ধ্রুবক xTaskGenericNotifyParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            BaseType_t x_Is_Previous_Notification_মান_Writeable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            যদি( pxParams != ফাঁকা )
            {
                xAreParamsReadable = x_Port_Is_Authorized_To_Access_বাফার( pxParams,
                                                                      আকার( xTaskGenericNotifyParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            যদি( xAreParamsReadable == pdTRUE )
            {
                যদি( ( pxParams->ux_সূচক_To_Notify < configTASK_NOTIFICATION_ARRAY_ENTRIES ) &&
                    ( ( pxParams->eAction == eNoAction ) ||
                      ( pxParams->eAction == eSetBits ) ||
                      ( pxParams->eAction == eIncrement ) ||
                      ( pxParams->eAction == e_Set_মান_With_Overwrite ) ||
                      ( pxParams->eAction == e_Set_মান_Without_Overwrite ) ) )
                {
                    যদি( pxParams->pul_Previous_Notification_মান != ফাঁকা )
                    {
                        x_Is_Previous_Notification_মান_Writeable = x_Port_Is_Authorized_To_Access_বাফার( pxParams->pul_Previous_Notification_মান,
                                                                                                 আকার( uint32_t ),
                                                                                                 tskMPU_WRITE_PERMISSION );
                    }

                    যদি( ( pxParams->pul_Previous_Notification_মান == ফাঁকা ) ||
                        ( x_Is_Previous_Notification_মান_Writeable == pdTRUE ) )
                    {
                        l_সূচক = ( int32_t ) ( pxParams->xTaskToNotify );

                        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                        {
                            xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                            যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                            {
                                xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                                যদি( xInternalTaskHandle != ফাঁকা )
                                {
                                    xReturn = xTaskGenericNotify( xInternalTaskHandle,
                                                                  pxParams->ux_সূচক_To_Notify,
                                                                  pxParams->ul_মান,
                                                                  pxParams->eAction,
                                                                  pxParams->pul_Previous_Notification_মান );
                                }
                            }
                        }
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_সূচক_To_Wait_On,
                                               uint32_t ulBitsToClearOnEntry,
                                               uint32_t ulBitsToClearOnExit,
                                               uint32_t * pul_Notification_মান,
                                               TickType_t xTicksToWait )
        {
            BaseType_t xReturn = pdFAIL;
            xTaskGenericNotifyWaitParams_t xParams;

            xParams.ux_সূচক_To_Wait_On = ux_সূচক_To_Wait_On;
            xParams.ulBitsToClearOnEntry = ulBitsToClearOnEntry;
            xParams.ulBitsToClearOnExit = ulBitsToClearOnExit;
            xParams.pul_Notification_মান = pul_Notification_মান;
            xParams.xTicksToWait = xTicksToWait;

            xReturn = MPU_xTaskGenericNotifyWaitEntry( &( xParams ) );

            ফেরত xReturn;
        }

        BaseType_t MPU_xTaskGenericNotifyWaitImpl( ধ্রুবক xTaskGenericNotifyWaitParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyWaitImpl( ধ্রুবক xTaskGenericNotifyWaitParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t x_Is_Notification_মান_Writable = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            যদি( pxParams != ফাঁকা )
            {
                xAreParamsReadable = x_Port_Is_Authorized_To_Access_বাফার( pxParams,
                                                                      আকার( xTaskGenericNotifyWaitParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            যদি( xAreParamsReadable == pdTRUE )
            {
                যদি( pxParams->ux_সূচক_To_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
                {
                    যদি( pxParams->pul_Notification_মান != ফাঁকা )
                    {
                        x_Is_Notification_মান_Writable = x_Port_Is_Authorized_To_Access_বাফার( pxParams->pul_Notification_মান,
                                                                                        আকার( uint32_t ),
                                                                                        tskMPU_WRITE_PERMISSION );
                    }

                    যদি( ( pxParams->pul_Notification_মান == ফাঁকা ) ||
                        ( x_Is_Notification_মান_Writable == pdTRUE ) )
                    {
                        xReturn = xTaskGenericNotifyWait( pxParams->ux_সূচক_To_Wait_On,
                                                          pxParams->ulBitsToClearOnEntry,
                                                          pxParams->ulBitsToClearOnExit,
                                                          pxParams->pul_Notification_মান,
                                                          pxParams->xTicksToWait );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_সূচক_To_Wait_On,
                                                  BaseType_t x_Clear_গুনতি_On_Exit,
                                                  TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_সূচক_To_Wait_On,
                                                  BaseType_t x_Clear_গুনতি_On_Exit,
                                                  TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;

            যদি( ux_সূচক_To_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ulReturn = ulTaskGenericNotifyTake( ux_সূচক_To_Wait_On, x_Clear_গুনতি_On_Exit, xTicksToWait );
            }

            ফেরত ulReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_সূচক_To_Clear ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_সূচক_To_Clear ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            যদি( ux_সূচক_To_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                যদি( xTask == ফাঁকা )
                {
                    xReturn = xTaskGenericNotifyStateClear( xTask, ux_সূচক_To_Clear );
                }
                অন্যথা
                {
                    l_সূচক = ( int32_t ) xTask;

                    যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                            যদি( xInternalTaskHandle != ফাঁকা )
                            {
                                xReturn = xTaskGenericNotifyStateClear( xInternalTaskHandle, ux_সূচক_To_Clear );
                            }
                        }
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_মান_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_সূচক_To_Clear,
                                                        uint32_t ulBitsToClear ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ul_Task_Generic_Notify_মান_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_সূচক_To_Clear,
                                                        uint32_t ulBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            যদি( ux_সূচক_To_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                যদি( xTask == ফাঁকা )
                {
                    ulReturn = ul_Task_Generic_Notify_মান_Clear( xTask, ux_সূচক_To_Clear, ulBitsToClear );
                }
                অন্যথা
                {
                    l_সূচক = ( int32_t ) xTask;

                    যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                            যদি( xInternalTaskHandle != ফাঁকা )
                            {
                                ulReturn = ul_Task_Generic_Notify_মান_Clear( xInternalTaskHandle, ux_সূচক_To_Clear, ulBitsToClear );
                            }
                        }
                    }
                }
            }

            ফেরত ulReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Task APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #যদি ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreate( TaskFunction_t pvTaskCode,
                                    ধ্রুবক অক্ষর * ধ্রুবক pcName,
                                    ধ্রুবক config_স্তূপ_DEPTH_TYPE ux_স্তূপ_Depth,
                                    শূন্য * pvParameters,
                                    UBaseType_t uxPriority,
                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                /* xTaskCreate() can only be used to create privileged tasks in MPU port. */
                যদি( ( uxPriority & portPRIVILEGE_BIT ) != 0 )
                {
                    xReturn = xTaskCreate( pvTaskCode, pcName, ux_স্তূপ_Depth, pvParameters, uxPriority, &( xInternalTaskHandle ) );

                    যদি( ( xReturn == pdPASS ) && ( xInternalTaskHandle != ফাঁকা ) )
                    {
                        MPU_Store_Task_Handle_At_সূচক( l_সূচক, xInternalTaskHandle );

                        যদি( pxCreatedTask != ফাঁকা )
                        {
                            *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                        }
                    }
                    অন্যথা
                    {
                        MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #যদি ( configSUPPORT_STATIC_ALLOCATION == 1 )

        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                            ধ্রুবক অক্ষর * ধ্রুবক pcName,
                                            ধ্রুবক config_স্তূপ_DEPTH_TYPE ux_স্তূপ_Depth,
                                            শূন্য * ধ্রুবক pvParameters,
                                            UBaseType_t uxPriority,
                                            স্তূপ_Type_t * ধ্রুবক pux_স্তূপ_বাফার,
                                            StaticTask_t * ধ্রুবক px_Task_বাফার ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xExternalTaskHandle = ফাঁকা;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xInternalTaskHandle = xTaskCreateStatic( pxTaskCode, pcName, ux_স্তূপ_Depth, pvParameters, uxPriority, pux_স্তূপ_বাফার, px_Task_বাফার );

                যদি( xInternalTaskHandle != ফাঁকা )
                {
                    MPU_Store_Task_Handle_At_সূচক( l_সূচক, xInternalTaskHandle );

                    #যদি ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        যদি( ( uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, l_সূচক );
                        }
                    }
                    #endif

                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xExternalTaskHandle;
        }

    #endif /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_vTaskDelete == 1 )

        শূন্য MPU_vTaskDelete( TaskHandle_t pxTaskToDelete ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            int32_t l_সূচক;

            যদি( pxTaskToDelete == ফাঁকা )
            {
                xInternalTaskHandle = xTaskGetCurrentTaskHandle();
                l_সূচক = MPU_Get_সূচক_For_Task_Handle( xInternalTaskHandle );

                যদি( l_সূচক != -1 )
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }

                vTaskDelete( xInternalTaskHandle );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) pxTaskToDelete;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTaskHandle != ফাঁকা )
                    {
                        MPU_Set_সূচক_Free_In_Kernel_Object_Pool( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );
                        vTaskDelete( xInternalTaskHandle );
                    }
                }
            }
        }

    #endif /* #if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/


    #যদি ( INCLUDE_vTaskPrioritySet == 1 )

        শূন্য MPU_vTaskPrioritySet( TaskHandle_t pxTask,
                                   UBaseType_t uxNewPriority ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            int32_t l_সূচক;

            যদি( pxTask == ফাঁকা )
            {
                vTaskPrioritySet( pxTask, uxNewPriority );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) pxTask;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTaskHandle != ফাঁকা )
                    {
                        vTaskPrioritySet( xInternalTaskHandle, uxNewPriority );
                    }
                }
            }
        }

    #endif /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_xTaskGetHandle == 1 )

        TaskHandle_t MPU_xTaskGetHandle( ধ্রুবক অক্ষর * pcNameToQuery ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            TaskHandle_t xExternalTaskHandle = ফাঁকা;
            int32_t l_সূচক;

            xInternalTaskHandle = xTaskGetHandle( pcNameToQuery );

            যদি( xInternalTaskHandle != ফাঁকা )
            {
                l_সূচক = MPU_Get_সূচক_For_Task_Handle( xInternalTaskHandle );

                যদি( l_সূচক != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
            }

            ফেরত xExternalTaskHandle;
        }

    #endif /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/


    #যদি ( configUSE_APPLICATION_TASK_TAG == 1 )

        BaseType_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     শূন্য * pvParameter ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;

            যদি( xTask == ফাঁকা )
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) xTask;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTaskHandle != ফাঁকা )
                    {
                        xReturn = xTaskCallApplicationTaskHook( xInternalTaskHandle, pvParameter );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreateRestricted( ধ্রুবক TaskParameters_t * ধ্রুবক pxTaskDefinition,
                                              TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xReturn = xTaskCreateRestricted( pxTaskDefinition, &( xInternalTaskHandle ) );

                যদি( ( xReturn == pdPASS ) && ( xInternalTaskHandle != ফাঁকা ) )
                {
                    MPU_Store_Task_Handle_At_সূচক( l_সূচক, xInternalTaskHandle );

                    #যদি ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        যদি( ( pxTaskDefinition->uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, l_সূচক );
                        }
                    }
                    #endif

                    যদি( pxCreatedTask != ফাঁকা )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                    }
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xReturn;
        }

    #endif /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #যদি ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreateRestrictedStatic( ধ্রুবক TaskParameters_t * ধ্রুবক pxTaskDefinition,
                                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xReturn = xTaskCreateRestrictedStatic( pxTaskDefinition, &( xInternalTaskHandle ) );

                যদি( ( xReturn == pdPASS ) && ( xInternalTaskHandle != ফাঁকা ) )
                {
                    MPU_Store_Task_Handle_At_সূচক( l_সূচক, xInternalTaskHandle );

                    #যদি ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        যদি( ( pxTaskDefinition->uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, l_সূচক );
                        }
                    }
                    #endif

                    যদি( pxCreatedTask != ফাঁকা )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                    }
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xReturn;
        }

    #endif /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    শূন্য MPU_vTaskAllocateMPURegions( TaskHandle_t xTaskToModify,
                                      ধ্রুবক MemoryRegion_t * ধ্রুবক xRegions ) /* PRIVILEGED_FUNCTION */
    {
        TaskHandle_t xInternalTaskHandle = ফাঁকা;
        int32_t l_সূচক;

        যদি( xTaskToModify == ফাঁকা )
        {
            vTaskAllocateMPURegions( xTaskToModify, xRegions );
        }
        অন্যথা
        {
            l_সূচক = ( int32_t ) xTaskToModify;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalTaskHandle != ফাঁকা )
                {
                    vTaskAllocateMPURegions( xInternalTaskHandle, xRegions );
                }
            }
        }
    }
/*-----------------------------------------------------------*/

    #যদি ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskGetStaticBuffers( TaskHandle_t xTask,
                                              স্তূপ_Type_t ** ppux_স্তূপ_বাফার,
                                              StaticTask_t ** ppx_Task_বাফার ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xReturn = pdFALSE;

            যদি( xTask == ফাঁকা )
            {
                xInternalTaskHandle = xTaskGetCurrentTaskHandle();
                xReturn = xTaskGetStaticBuffers( xInternalTaskHandle, ppux_স্তূপ_বাফার, ppx_Task_বাফার );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) xTask;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTaskHandle != ফাঁকা )
                    {
                        xReturn = xTaskGetStaticBuffers( xInternalTaskHandle, ppux_স্তূপ_বাফার, ppx_Task_বাফার );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    অক্ষর * MPU_pcTaskGetName( TaskHandle_t xTaskToQuery ) /* PRIVILEGED_FUNCTION */
    {
        অক্ষর * pcReturn = ফাঁকা;
        int32_t l_সূচক;
        TaskHandle_t xInternalTaskHandle = ফাঁকা;

        যদি( xTaskToQuery == ফাঁকা )
        {
            pcReturn = pcTaskGetName( xTaskToQuery );
        }
        অন্যথা
        {
            l_সূচক = ( int32_t ) xTaskToQuery;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalTaskHandle != ফাঁকা )
                {
                    pcReturn = pcTaskGetName( xInternalTaskHandle );
                }
            }
        }

        ফেরত pcReturn;
    }
/*-----------------------------------------------------------*/

    #যদি ( INCLUDE_uxTaskPriorityGet == 1 )

        UBaseType_t MPU_uxTaskPriorityGetFromISR( ধ্রুবক TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;

            যদি( xTask == ফাঁকা )
            {
                uxReturn = uxTaskPriorityGetFromISR( xTask );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) xTask;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTaskHandle != ফাঁকা )
                    {
                        uxReturn = uxTaskPriorityGetFromISR( xInternalTaskHandle );
                    }
                }
            }

            ফেরত uxReturn;
        }

    #endif /* #if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_uxTaskBasePriorityGet( ধ্রুবক TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;

            যদি( xTask == ফাঁকা )
            {
                uxReturn = uxTaskBasePriorityGet( xTask );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) xTask;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTaskHandle != ফাঁকা )
                    {
                        uxReturn = uxTaskBasePriorityGet( xInternalTaskHandle );
                    }
                }
            }

            ফেরত uxReturn;
        }

    #endif /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_uxTaskBasePriorityGetFromISR( ধ্রুবক TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;

            যদি( xTask == ফাঁকা )
            {
                uxReturn = uxTaskBasePriorityGetFromISR( xTask );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) xTask;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTaskHandle != ফাঁকা )
                    {
                        uxReturn = uxTaskBasePriorityGetFromISR( xInternalTaskHandle );
                    }
                }
            }

            ফেরত uxReturn;
        }

    #endif /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

        BaseType_t MPU_xTaskResumeFromISR( TaskHandle_t xTaskToResume ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;

            l_সূচক = ( int32_t ) xTaskToResume;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalTaskHandle != ফাঁকা )
                {
                    xReturn = xTaskResumeFromISR( xInternalTaskHandle );
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )*/
/*---------------------------------------------------------------------------------------*/

    #যদি ( configUSE_APPLICATION_TASK_TAG == 1 )

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagFromISR( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = ফাঁকা;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;

            যদি( xTask == ফাঁকা )
            {
                xReturn = xTaskGetApplicationTaskTagFromISR( xTask );
            }
            অন্যথা
            {
                l_সূচক = ( int32_t ) xTask;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTaskHandle != ফাঁকা )
                    {
                        xReturn = xTaskGetApplicationTaskTagFromISR( xInternalTaskHandle );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyFromISR( TaskHandle_t xTaskToNotify,
                                                  UBaseType_t ux_সূচক_To_Notify,
                                                  uint32_t ul_মান,
                                                  eNotifyAction eAction,
                                                  uint32_t * pul_Previous_Notification_মান,
                                                  BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;

            l_সূচক = ( int32_t ) xTaskToNotify;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalTaskHandle != ফাঁকা )
                {
                    xReturn = xTaskGenericNotifyFromISR( xInternalTaskHandle, ux_সূচক_To_Notify, ul_মান, eAction, pul_Previous_Notification_মান, pxHigherPriorityTaskWoken );
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )

        শূন্য MPU_vTaskGenericNotifyGiveFromISR( TaskHandle_t xTaskToNotify,
                                                UBaseType_t ux_সূচক_To_Notify,
                                                BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_সূচক;
            TaskHandle_t xInternalTaskHandle = ফাঁকা;

            l_সূচক = ( int32_t ) xTaskToNotify;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_Get_Task_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalTaskHandle != ফাঁকা )
                {
                    vTaskGenericNotifyGiveFromISR( xInternalTaskHandle, ux_সূচক_To_Notify, pxHigherPriorityTaskWoken );
                }
            }
        }
    #endif /*#if ( configUSE_TASK_NOTIFICATIONS == 1 )*/
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for queue APIs.                   */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSendImpl( QueueHandle_t xQueue,
                                          ধ্রুবক শূন্য * ধ্রুবক pvItemToQueue,
                                          TickType_t xTicksToWait,
                                          BaseType_t xCopyPosition ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueGenericSendImpl( QueueHandle_t xQueue,
                                          ধ্রুবক শূন্য * ধ্রুবক pvItemToQueue,
                                          TickType_t xTicksToWait,
                                          BaseType_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_সূচক;
        QueueHandle_t xInternalQueueHandle = ফাঁকা;
        BaseType_t xReturn = pdFAIL;
        BaseType_t xIsItemToQueueReadable = pdFALSE;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
        UBaseType_t ux_Queue_Item_আকার, ux_Queue_দৈর্ঘ্য;

        l_সূচক = ( int32_t ) xQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalQueueHandle != ফাঁকা )
                {
                    ux_Queue_Item_আকার = ux_Queue_Get_Queue_Item_আকার( xInternalQueueHandle );
                    ux_Queue_দৈর্ঘ্য = ux_Queue_Get_Queue_দৈর্ঘ্য( xInternalQueueHandle );

                    যদি( ( !( ( pvItemToQueue == ফাঁকা ) && ( ux_Queue_Item_আকার != ( UBaseType_t ) 0U ) ) ) &&
                        ( !( ( xCopyPosition == queueOVERWRITE ) && ( ux_Queue_দৈর্ঘ্য != ( UBaseType_t ) 1U ) ) )
                        #যদি ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        যদি( pvItemToQueue != ফাঁকা )
                        {
                            xIsItemToQueueReadable = x_Port_Is_Authorized_To_Access_বাফার( pvItemToQueue,
                                                                                      ux_Queue_Item_আকার,
                                                                                      tskMPU_READ_PERMISSION );
                        }

                        যদি( ( pvItemToQueue == ফাঁকা ) || ( xIsItemToQueueReadable == pdTRUE ) )
                        {
                            xReturn = xQueueGenericSend( xInternalQueueHandle, pvItemToQueue, xTicksToWait, xCopyPosition );
                        }
                    }
                }
            }
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaitingImpl( ধ্রুবক QueueHandle_t pxQueue ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_uxQueueMessagesWaitingImpl( ধ্রুবক QueueHandle_t pxQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_সূচক;
        QueueHandle_t xInternalQueueHandle = ফাঁকা;
        UBaseType_t uxReturn = 0;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        l_সূচক = ( int32_t ) pxQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalQueueHandle != ফাঁকা )
                {
                    uxReturn = uxQueueMessagesWaiting( xInternalQueueHandle );
                }
            }
        }

        ফেরত uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueSpacesAvailableImpl( ধ্রুবক QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_uxQueueSpacesAvailableImpl( ধ্রুবক QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_সূচক;
        QueueHandle_t xInternalQueueHandle = ফাঁকা;
        UBaseType_t uxReturn = 0;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        l_সূচক = ( int32_t ) xQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalQueueHandle != ফাঁকা )
                {
                    uxReturn = uxQueueSpacesAvailable( xInternalQueueHandle );
                }
            }
        }

        ফেরত uxReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceiveImpl( QueueHandle_t pxQueue,
                                      শূন্য * ধ্রুবক pv_বাফার,
                                      TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueReceiveImpl( QueueHandle_t pxQueue,
                                      শূন্য * ধ্রুবক pv_বাফার,
                                      TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_সূচক;
        QueueHandle_t xInternalQueueHandle = ফাঁকা;
        BaseType_t xReturn = pdFAIL;
        BaseType_t x_Is_Receive_বাফার_Writable = pdFALSE;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
        UBaseType_t ux_Queue_Item_আকার;

        l_সূচক = ( int32_t ) pxQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalQueueHandle != ফাঁকা )
                {
                    ux_Queue_Item_আকার = ux_Queue_Get_Queue_Item_আকার( xInternalQueueHandle );

                    যদি( ( !( ( ( pv_বাফার ) == ফাঁকা ) && ( ux_Queue_Item_আকার != ( UBaseType_t ) 0U ) ) )
                        #যদি ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        x_Is_Receive_বাফার_Writable = x_Port_Is_Authorized_To_Access_বাফার( pv_বাফার,
                                                                                    ux_Queue_Item_আকার,
                                                                                    tskMPU_WRITE_PERMISSION );

                        যদি( x_Is_Receive_বাফার_Writable == pdTRUE )
                        {
                            xReturn = xQueueReceive( xInternalQueueHandle, pv_বাফার, xTicksToWait );
                        }
                    }
                }
            }
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeekImpl( QueueHandle_t xQueue,
                                   শূন্য * ধ্রুবক pv_বাফার,
                                   TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueuePeekImpl( QueueHandle_t xQueue,
                                   শূন্য * ধ্রুবক pv_বাফার,
                                   TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_সূচক;
        QueueHandle_t xInternalQueueHandle = ফাঁকা;
        BaseType_t xReturn = pdFAIL;
        BaseType_t x_Is_Receive_বাফার_Writable = pdFALSE;
        UBaseType_t ux_Queue_Item_আকার;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        l_সূচক = ( int32_t ) xQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalQueueHandle != ফাঁকা )
                {
                    ux_Queue_Item_আকার = ux_Queue_Get_Queue_Item_আকার( xInternalQueueHandle );

                    যদি( ( !( ( ( pv_বাফার ) == ফাঁকা ) && ( ux_Queue_Item_আকার != ( UBaseType_t ) 0U ) ) )
                        #যদি ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        x_Is_Receive_বাফার_Writable = x_Port_Is_Authorized_To_Access_বাফার( pv_বাফার,
                                                                                    ux_Queue_Item_আকার,
                                                                                    tskMPU_WRITE_PERMISSION );

                        যদি( x_Is_Receive_বাফার_Writable == pdTRUE )
                        {
                            xReturn = xQueuePeek( xInternalQueueHandle, pv_বাফার, xTicksToWait );
                        }
                    }
                }
            }
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueSemaphoreTakeImpl( QueueHandle_t xQueue,
                                            TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueSemaphoreTakeImpl( QueueHandle_t xQueue,
                                            TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_সূচক;
        QueueHandle_t xInternalQueueHandle = ফাঁকা;
        BaseType_t xReturn = pdFAIL;
        UBaseType_t ux_Queue_Item_আকার;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        l_সূচক = ( int32_t ) xQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalQueueHandle != ফাঁকা )
                {
                    ux_Queue_Item_আকার = ux_Queue_Get_Queue_Item_আকার( xInternalQueueHandle );

                    যদি( ( ux_Queue_Item_আকার == 0U )
                        #যদি ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        xReturn = xQueueSemaphoreTake( xInternalQueueHandle, xTicksToWait );
                    }
                }
            }
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolderImpl( QueueHandle_t xSemaphore ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xQueueGetMutexHolderImpl( QueueHandle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xMutexHolderTaskInternalHandle = ফাঁকা;
            TaskHandle_t xMutexHolderTaskExternalHandle = ফাঁকা;
            int32_t l_সূচক, l_Mutex_Holder_Task_সূচক;
            QueueHandle_t xInternalQueueHandle = ফাঁকা;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;


            l_সূচক = ( int32_t ) xSemaphore;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalQueueHandle != ফাঁকা )
                    {
                        xMutexHolderTaskInternalHandle = xQueueGetMutexHolder( xInternalQueueHandle );

                        যদি( xMutexHolderTaskInternalHandle != ফাঁকা )
                        {
                            l_Mutex_Holder_Task_সূচক = MPU_Get_সূচক_For_Task_Handle( xMutexHolderTaskInternalHandle );

                            যদি( l_Mutex_Holder_Task_সূচক != -1 )
                            {
                                xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_TO_EXTERNAL_সূচক( l_Mutex_Holder_Task_সূচক ) );
                            }
                        }
                    }
                }
            }

            ফেরত xMutexHolderTaskExternalHandle;
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueTakeMutexRecursiveImpl( QueueHandle_t xMutex,
                                                     TickType_t xBlockTime ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueTakeMutexRecursiveImpl( QueueHandle_t xMutex,
                                                     TickType_t xBlockTime ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
            int32_t l_সূচক;
            QueueHandle_t xInternalQueueHandle = ফাঁকা;
            UBaseType_t ux_Queue_Item_আকার;

            l_সূচক = ( int32_t ) xMutex;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalQueueHandle != ফাঁকা )
                    {
                        ux_Queue_Item_আকার = ux_Queue_Get_Queue_Item_আকার( xInternalQueueHandle );

                        যদি( ux_Queue_Item_আকার == 0 )
                        {
                            xReturn = xQueueTakeMutexRecursive( xInternalQueueHandle, xBlockTime );
                        }
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueGiveMutexRecursiveImpl( QueueHandle_t xMutex ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueGiveMutexRecursiveImpl( QueueHandle_t xMutex ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
            int32_t l_সূচক;
            QueueHandle_t xInternalQueueHandle = ফাঁকা;

            l_সূচক = ( int32_t ) xMutex;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalQueueHandle != ফাঁকা )
                    {
                        xReturn = xQueueGiveMutexRecursive( xInternalQueueHandle );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_QUEUE_SETS == 1 )

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetImpl( QueueSetHandle_t xQueueSet,
                                                            TickType_t xBlockTimeTicks ) PRIVILEGED_FUNCTION;

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetImpl( QueueSetHandle_t xQueueSet,
                                                            TickType_t xBlockTimeTicks ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = ফাঁকা;
            QueueSetMemberHandle_t xSelectedMemberInternal = ফাঁকা;
            QueueSetMemberHandle_t xSelectedMemberExternal = ফাঁকা;
            int32_t l_সূচক_Queue_Set, l_সূচক_Selected_Member;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSet = pdFALSE;

            l_সূচক_Queue_Set = ( int32_t ) xQueueSet;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক_Queue_Set ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueueSet = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক_Queue_Set ) );

                যদি( xCallingTaskIsAuthorizedToAccessQueueSet == pdTRUE )
                {
                    xInternalQueueSetHandle = MPU_Get_Queue_Set_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক_Queue_Set ) );

                    যদি( xInternalQueueSetHandle != ফাঁকা )
                    {
                        xSelectedMemberInternal = xQueueSelectFromSet( xInternalQueueSetHandle, xBlockTimeTicks );

                        যদি( xSelectedMemberInternal != ফাঁকা )
                        {
                            l_সূচক_Selected_Member = MPU_Get_সূচক_For_Queue_Set_Member_Handle( xSelectedMemberInternal );

                            যদি( l_সূচক_Selected_Member != -1 )
                            {
                                xSelectedMemberExternal = ( QueueSetMemberHandle_t ) ( CONVERT_TO_EXTERNAL_সূচক( l_সূচক_Selected_Member ) );
                            }
                        }
                    }
                }
            }

            ফেরত xSelectedMemberExternal;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_QUEUE_SETS == 1 )

        BaseType_t MPU_xQueueAddToSetImpl( QueueSetMemberHandle_t xQueueOrSemaphore,
                                           QueueSetHandle_t xQueueSet ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueAddToSetImpl( QueueSetMemberHandle_t xQueueOrSemaphore,
                                           QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            QueueSetMemberHandle_t xInternalQueueSetMemberHandle = ফাঁকা;
            QueueSetHandle_t xInternalQueueSetHandle = ফাঁকা;
            int32_t l_সূচক_Queue_Set, l_সূচক_Queue_Set_Member;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSet = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSetMember = pdFALSE;

            l_সূচক_Queue_Set = ( int32_t ) xQueueSet;
            l_সূচক_Queue_Set_Member = ( int32_t ) xQueueOrSemaphore;

            যদি( ( IS_EXTERNAL_সূচক_VALID( l_সূচক_Queue_Set ) != pdFALSE ) &&
                ( IS_EXTERNAL_সূচক_VALID( l_সূচক_Queue_Set_Member ) != pdFALSE ) )
            {
                xCallingTaskIsAuthorizedToAccessQueueSet = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক_Queue_Set ) );
                xCallingTaskIsAuthorizedToAccessQueueSetMember = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক_Queue_Set_Member ) );

                যদি( ( xCallingTaskIsAuthorizedToAccessQueueSet == pdTRUE ) && ( xCallingTaskIsAuthorizedToAccessQueueSetMember == pdTRUE ) )
                {
                    xInternalQueueSetHandle = MPU_Get_Queue_Set_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক_Queue_Set ) );
                    xInternalQueueSetMemberHandle = MPU_Get_Queue_Set_Member_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক_Queue_Set_Member ) );

                    যদি( ( xInternalQueueSetHandle != ফাঁকা ) && ( xInternalQueueSetMemberHandle != ফাঁকা ) )
                    {
                        xReturn = xQueueAddToSet( xInternalQueueSetMemberHandle, xInternalQueueSetHandle );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি config_QUEUE_REGISTRY_আকার > 0

        শূন্য MPU_vQueueAddToRegistryImpl( QueueHandle_t xQueue,
                                          ধ্রুবক অক্ষর * pcName ) PRIVILEGED_FUNCTION;

        শূন্য MPU_vQueueAddToRegistryImpl( QueueHandle_t xQueue,
                                          ধ্রুবক অক্ষর * pcName ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_সূচক;
            QueueHandle_t xInternalQueueHandle = ফাঁকা;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            l_সূচক = ( int32_t ) xQueue;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalQueueHandle != ফাঁকা )
                    {
                        vQueueAddToRegistry( xInternalQueueHandle, pcName );
                    }
                }
            }
        }

    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #যদি config_QUEUE_REGISTRY_আকার > 0

        শূন্য MPU_vQueueUnregisterQueueImpl( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

        শূন্য MPU_vQueueUnregisterQueueImpl( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_সূচক;
            QueueHandle_t xInternalQueueHandle = ফাঁকা;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            l_সূচক = ( int32_t ) xQueue;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalQueueHandle != ফাঁকা )
                    {
                        vQueueUnregisterQueue( xInternalQueueHandle );
                    }
                }
            }
        }

    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #যদি config_QUEUE_REGISTRY_আকার > 0

        ধ্রুবক অক্ষর * MPU_pcQueueGetNameImpl( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

        ধ্রুবক অক্ষর * MPU_pcQueueGetNameImpl( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
        {
            ধ্রুবক অক্ষর * pcReturn = ফাঁকা;
            QueueHandle_t xInternalQueueHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            l_সূচক = ( int32_t ) xQueue;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalQueueHandle != ফাঁকা )
                    {
                        pcReturn = pcQueueGetName( xInternalQueueHandle );
                    }
                }
            }

            ফেরত pcReturn;
        }

    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Queue APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    শূন্য MPU_vQueueDelete( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        QueueHandle_t xInternalQueueHandle = ফাঁকা;
        int32_t l_সূচক;

        l_সূচক = ( int32_t ) xQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xInternalQueueHandle != ফাঁকা )
            {
                vQueueDelete( xInternalQueueHandle );
                MPU_Set_সূচক_Free_In_Kernel_Object_Pool( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );
            }
        }
    }
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateMutex( ধ্রুবক uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ফাঁকা;
            QueueHandle_t xExternalQueueHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xInternalQueueHandle = xQueueCreateMutex( ucQueueType );

                যদি( xInternalQueueHandle != ফাঁকা )
                {
                    MPU_Store_Queue_Handle_At_সূচক( l_সূচক, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateMutexStatic( ধ্রুবক uint8_t ucQueueType,
                                                   StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ফাঁকা;
            QueueHandle_t xExternalQueueHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xInternalQueueHandle = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );

                যদি( xInternalQueueHandle != ফাঁকা )
                {
                    MPU_Store_Queue_Handle_At_সূচক( l_সূচক, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphore( UBaseType_t ux_গুনতি_মান,
                                                         UBaseType_t ux_Initial_গুনতি ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ফাঁকা;
            QueueHandle_t xExternalQueueHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xInternalQueueHandle = xQueueCreateCountingSemaphore( ux_গুনতি_মান, ux_Initial_গুনতি );

                যদি( xInternalQueueHandle != ফাঁকা )
                {
                    MPU_Store_Queue_Handle_At_সূচক( l_সূচক, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphoreStatic( ধ্রুবক UBaseType_t ux_Max_গুনতি,
                                                               ধ্রুবক UBaseType_t ux_Initial_গুনতি,
                                                               StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ফাঁকা;
            QueueHandle_t xExternalQueueHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xInternalQueueHandle = xQueueCreateCountingSemaphoreStatic( ux_Max_গুনতি, ux_Initial_গুনতি, pxStaticQueue );

                যদি( xInternalQueueHandle != ফাঁকা )
                {
                    MPU_Store_Queue_Handle_At_সূচক( l_সূচক, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        QueueHandle_t MPU_xQueueGenericCreate( UBaseType_t ux_Queue_দৈর্ঘ্য,
                                               UBaseType_t ux_Item_আকার,
                                               uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ফাঁকা;
            QueueHandle_t xExternalQueueHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xInternalQueueHandle = xQueueGenericCreate( ux_Queue_দৈর্ঘ্য, ux_Item_আকার, ucQueueType );

                যদি( xInternalQueueHandle != ফাঁকা )
                {
                    MPU_Store_Queue_Handle_At_সূচক( l_সূচক, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xExternalQueueHandle;
        }

    #endif /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configSUPPORT_STATIC_ALLOCATION == 1 )

        QueueHandle_t MPU_xQueueGenericCreateStatic( ধ্রুবক UBaseType_t ux_Queue_দৈর্ঘ্য,
                                                     ধ্রুবক UBaseType_t ux_Item_আকার,
                                                     uint8_t * pucQueueStorage,
                                                     StaticQueue_t * pxStaticQueue,
                                                     ধ্রুবক uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ফাঁকা;
            QueueHandle_t xExternalQueueHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xInternalQueueHandle = xQueueGenericCreateStatic( ux_Queue_দৈর্ঘ্য, ux_Item_আকার, pucQueueStorage, pxStaticQueue, ucQueueType );

                যদি( xInternalQueueHandle != ফাঁকা )
                {
                    MPU_Store_Queue_Handle_At_সূচক( l_সূচক, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xExternalQueueHandle;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericReset( QueueHandle_t xQueue,
                                       BaseType_t xNewQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_সূচক;
        QueueHandle_t xInternalQueueHandle = ফাঁকা;
        BaseType_t xReturn = pdFAIL;

        l_সূচক = ( int32_t ) xQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xInternalQueueHandle != ফাঁকা )
            {
                xReturn = xQueueGenericReset( xInternalQueueHandle, xNewQueue );
            }
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueSetHandle_t MPU_xQueueCreateSet( UBaseType_t ux_Event_Queue_দৈর্ঘ্য ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = ফাঁকা;
            QueueSetHandle_t xExternalQueueSetHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xInternalQueueSetHandle = xQueueCreateSet( ux_Event_Queue_দৈর্ঘ্য );

                যদি( xInternalQueueSetHandle != ফাঁকা )
                {
                    MPU_Store_Queue_Set_Handle_At_সূচক( l_সূচক, xInternalQueueSetHandle );
                    xExternalQueueSetHandle = ( QueueSetHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xExternalQueueSetHandle;
        }

    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueSetHandle_t MPU_xQueueCreateSetStatic( ধ্রুবক UBaseType_t ux_Event_Queue_দৈর্ঘ্য,
                                                    uint8_t * pucQueueStorage,
                                                    StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = ফাঁকা;
            QueueSetHandle_t xExternalQueueSetHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xInternalQueueSetHandle = xQueueCreateSetStatic( ux_Event_Queue_দৈর্ঘ্য, pucQueueStorage, pxStaticQueue );

                যদি( xInternalQueueSetHandle != ফাঁকা )
                {
                    MPU_Store_Queue_Set_Handle_At_সূচক( l_সূচক, xInternalQueueSetHandle );
                    xExternalQueueSetHandle = ( QueueSetHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xExternalQueueSetHandle;
        }

    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_QUEUE_SETS == 1 )

        BaseType_t MPU_xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                            QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            QueueSetMemberHandle_t xInternalQueueSetMemberHandle = ফাঁকা;
            QueueSetHandle_t xInternalQueueSetHandle = ফাঁকা;
            int32_t l_সূচক_Queue_Set, l_সূচক_Queue_Set_Member;

            l_সূচক_Queue_Set = ( int32_t ) xQueueSet;
            l_সূচক_Queue_Set_Member = ( int32_t ) xQueueOrSemaphore;

            যদি( ( IS_EXTERNAL_সূচক_VALID( l_সূচক_Queue_Set ) != pdFALSE ) &&
                ( IS_EXTERNAL_সূচক_VALID( l_সূচক_Queue_Set_Member ) != pdFALSE ) )
            {
                xInternalQueueSetHandle = MPU_Get_Queue_Set_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক_Queue_Set ) );
                xInternalQueueSetMemberHandle = MPU_Get_Queue_Set_Member_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক_Queue_Set_Member ) );

                যদি( ( xInternalQueueSetHandle != ফাঁকা ) && ( xInternalQueueSetMemberHandle != ফাঁকা ) )
                {
                    xReturn = xQueueRemoveFromSet( xInternalQueueSetMemberHandle, xInternalQueueSetHandle );
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xQueueGenericGetStaticBuffers( QueueHandle_t xQueue,
                                                      uint8_t ** ppucQueueStorage,
                                                      StaticQueue_t ** ppxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_সূচক;
            QueueHandle_t xInternalQueueHandle = ফাঁকা;
            BaseType_t xReturn = pdFALSE;

            l_সূচক = ( int32_t ) xQueue;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalQueueHandle != ফাঁকা )
                {
                    xReturn = xQueueGenericGetStaticBuffers( xInternalQueueHandle, ppucQueueStorage, ppxStaticQueue );
                }
            }

            ফেরত xReturn;
        }

    #endif /*if ( configSUPPORT_STATIC_ALLOCATION == 1 )*/
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSendFromISR( QueueHandle_t xQueue,
                                             ধ্রুবক শূন্য * ধ্রুবক pvItemToQueue,
                                             BaseType_t * ধ্রুবক pxHigherPriorityTaskWoken,
                                             ধ্রুবক BaseType_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t l_সূচক;
        QueueHandle_t xInternalQueueHandle = ফাঁকা;

        l_সূচক = ( int32_t ) xQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xInternalQueueHandle != ফাঁকা )
            {
                xReturn = xQueueGenericSendFromISR( xInternalQueueHandle, pvItemToQueue, pxHigherPriorityTaskWoken, xCopyPosition );
            }
        }

        ফেরত xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGiveFromISR( QueueHandle_t xQueue,
                                      BaseType_t * ধ্রুবক pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t l_সূচক;
        QueueHandle_t xInternalQueueHandle = ফাঁকা;

        l_সূচক = ( int32_t ) xQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xInternalQueueHandle != ফাঁকা )
            {
                xReturn = xQueueGiveFromISR( xInternalQueueHandle, pxHigherPriorityTaskWoken );
            }
        }

        ফেরত xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeekFromISR( QueueHandle_t xQueue,
                                      শূন্য * ধ্রুবক pv_বাফার ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t l_সূচক;
        QueueHandle_t xInternalQueueHandle = ফাঁকা;

        l_সূচক = ( int32_t ) xQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xInternalQueueHandle != ফাঁকা )
            {
                xReturn = xQueuePeekFromISR( xInternalQueueHandle, pv_বাফার );
            }
        }

        ফেরত xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceiveFromISR( QueueHandle_t xQueue,
                                         শূন্য * ধ্রুবক pv_বাফার,
                                         BaseType_t * ধ্রুবক pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t l_সূচক;
        QueueHandle_t xInternalQueueHandle = ফাঁকা;

        l_সূচক = ( int32_t ) xQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xInternalQueueHandle != ফাঁকা )
            {
                xReturn = xQueueReceiveFromISR( xInternalQueueHandle, pv_বাফার, pxHigherPriorityTaskWoken );
            }
        }

        ফেরত xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueIsQueueEmptyFromISR( ধ্রুবক QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t l_সূচক;
        QueueHandle_t xInternalQueueHandle = ফাঁকা;

        l_সূচক = ( int32_t ) xQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xInternalQueueHandle != ফাঁকা )
            {
                xReturn = xQueueIsQueueEmptyFromISR( xInternalQueueHandle );
            }
        }

        ফেরত xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueIsQueueFullFromISR( ধ্রুবক QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t l_সূচক;
        QueueHandle_t xInternalQueueHandle = ফাঁকা;

        l_সূচক = ( int32_t ) xQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xInternalQueueHandle != ফাঁকা )
            {
                xReturn = xQueueIsQueueFullFromISR( xInternalQueueHandle );
            }
        }

        ফেরত xReturn;
    }

/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaitingFromISR( ধ্রুবক QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn = 0;
        int32_t l_সূচক;
        QueueHandle_t xInternalQueueHandle = ফাঁকা;

        l_সূচক = ( int32_t ) xQueue;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( xInternalQueueHandle != ফাঁকা )
            {
                uxReturn = uxQueueMessagesWaitingFromISR( xInternalQueueHandle );
            }
        }

        ফেরত uxReturn;
    }

/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolderFromISR( QueueHandle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xMutexHolderTaskInternalHandle = ফাঁকা;
            TaskHandle_t xMutexHolderTaskExternalHandle = ফাঁকা;
            int32_t l_সূচক, l_Mutex_Holder_Task_সূচক;
            QueueHandle_t xInternalSemaphoreHandle = ফাঁকা;

            l_সূচক = ( int32_t ) xSemaphore;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalSemaphoreHandle = MPU_Get_Queue_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalSemaphoreHandle != ফাঁকা )
                {
                    xMutexHolderTaskInternalHandle = xQueueGetMutexHolder( xInternalSemaphoreHandle );

                    যদি( xMutexHolderTaskInternalHandle != ফাঁকা )
                    {
                        l_Mutex_Holder_Task_সূচক = MPU_Get_সূচক_For_Task_Handle( xMutexHolderTaskInternalHandle );

                        যদি( l_Mutex_Holder_Task_সূচক != -1 )
                        {
                            xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_TO_EXTERNAL_সূচক( l_Mutex_Holder_Task_সূচক ) );
                        }
                    }
                }
            }

            ফেরত xMutexHolderTaskExternalHandle;
        }

    #endif /* #if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_QUEUE_SETS == 1 )

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetFromISR( QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = ফাঁকা;
            QueueSetMemberHandle_t xSelectedMemberInternal = ফাঁকা;
            QueueSetMemberHandle_t xSelectedMemberExternal = ফাঁকা;
            int32_t l_সূচক_Queue_Set, l_সূচক_Selected_Member;

            l_সূচক_Queue_Set = ( int32_t ) xQueueSet;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক_Queue_Set ) != pdFALSE )
            {
                xInternalQueueSetHandle = MPU_Get_Queue_Set_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক_Queue_Set ) );

                যদি( xInternalQueueSetHandle != ফাঁকা )
                {
                    xSelectedMemberInternal = xQueueSelectFromSetFromISR( xInternalQueueSetHandle );

                    যদি( xSelectedMemberInternal != ফাঁকা )
                    {
                        l_সূচক_Selected_Member = MPU_Get_সূচক_For_Queue_Set_Member_Handle( xSelectedMemberInternal );

                        যদি( l_সূচক_Selected_Member != -1 )
                        {
                            xSelectedMemberExternal = ( QueueSetMemberHandle_t ) ( CONVERT_TO_EXTERNAL_সূচক( l_সূচক_Selected_Member ) );
                        }
                    }
                }
            }

            ফেরত xSelectedMemberExternal;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for timers APIs.                  */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        শূন্য * MPU_pvTimerGetTimerIDImpl( ধ্রুবক TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        শূন্য * MPU_pvTimerGetTimerIDImpl( ধ্রুবক TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            শূন্য * pvReturn = ফাঁকা;
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_সূচক = ( int32_t ) xTimer;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTimerHandle != ফাঁকা )
                    {
                        pvReturn = pvTimerGetTimerID( xInternalTimerHandle );
                    }
                }
            }

            ফেরত pvReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        শূন্য MPU_vTimerSetTimerIDImpl( TimerHandle_t xTimer,
                                       শূন্য * pvNewID ) PRIVILEGED_FUNCTION;

        শূন্য MPU_vTimerSetTimerIDImpl( TimerHandle_t xTimer,
                                       শূন্য * pvNewID ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_সূচক = ( int32_t ) xTimer;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTimerHandle != ফাঁকা )
                    {
                        vTimerSetTimerID( xInternalTimerHandle, pvNewID );
                    }
                }
            }
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerIsTimerActiveImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerIsTimerActiveImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_সূচক = ( int32_t ) xTimer;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTimerHandle != ফাঁকা )
                    {
                        xReturn = xTimerIsTimerActive( xInternalTimerHandle );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( শূন্য ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( শূন্য ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xReturn;

            xReturn = xTimerGetTimerDaemonTaskHandle();

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ধ্রুবক BaseType_t xCommandID,
                                                     ধ্রুবক TickType_t x_Optional_মান,
                                                     BaseType_t * ধ্রুবক pxHigherPriorityTaskWoken,
                                                     ধ্রুবক TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn = pdFALSE;
            xTimerGenericCommandFromTaskParams_t xParams;

            xParams.xTimer = xTimer;
            xParams.xCommandID = xCommandID;
            xParams.x_Optional_মান = x_Optional_মান;
            xParams.pxHigherPriorityTaskWoken = pxHigherPriorityTaskWoken;
            xParams.xTicksToWait = xTicksToWait;

            xReturn = MPU_xTimerGenericCommandFromTaskEntry( &( xParams ) );

            ফেরত xReturn;
        }

        BaseType_t MPU_xTimerGenericCommandFromTaskImpl( ধ্রুবক xTimerGenericCommandFromTaskParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerGenericCommandFromTaskImpl( ধ্রুবক xTimerGenericCommandFromTaskParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xIsHigherPriorityTaskWokenWriteable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            যদি( pxParams != ফাঁকা )
            {
                xAreParamsReadable = x_Port_Is_Authorized_To_Access_বাফার( pxParams,
                                                                      আকার( xTimerGenericCommandFromTaskParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            যদি( xAreParamsReadable == pdTRUE )
            {
                যদি( pxParams->xCommandID < tmrFIRST_FROM_ISR_COMMAND )
                {
                    যদি( pxParams->pxHigherPriorityTaskWoken != ফাঁকা )
                    {
                        xIsHigherPriorityTaskWokenWriteable = x_Port_Is_Authorized_To_Access_বাফার( pxParams->pxHigherPriorityTaskWoken,
                                                                                               আকার( BaseType_t ),
                                                                                               tskMPU_WRITE_PERMISSION );
                    }

                    যদি( ( pxParams->pxHigherPriorityTaskWoken == ফাঁকা ) ||
                        ( xIsHigherPriorityTaskWokenWriteable == pdTRUE ) )
                    {
                        l_সূচক = ( int32_t ) ( pxParams->xTimer );

                        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                        {
                            xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                            যদি( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                            {
                                xInternalTimerHandle = MPU_Get_Timer_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                                যদি( xInternalTimerHandle != ফাঁকা )
                                {
                                    xReturn = xTimerGenericCommandFromTask( xInternalTimerHandle,
                                                                            pxParams->xCommandID,
                                                                            pxParams->x_Optional_মান,
                                                                            pxParams->pxHigherPriorityTaskWoken,
                                                                            pxParams->xTicksToWait );
                                }
                            }
                        }
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        ধ্রুবক অক্ষর * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ধ্রুবক অক্ষর * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ধ্রুবক অক্ষর * pcReturn = ফাঁকা;
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_সূচক = ( int32_t ) xTimer;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTimerHandle != ফাঁকা )
                    {
                        pcReturn = pcTimerGetName( xInternalTimerHandle );
                    }
                }
            }

            ফেরত pcReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        শূন্য MPU_vTimerSetReloadModeImpl( TimerHandle_t xTimer,
                                          ধ্রুবক BaseType_t xAutoReload ) PRIVILEGED_FUNCTION;

        শূন্য MPU_vTimerSetReloadModeImpl( TimerHandle_t xTimer,
                                          ধ্রুবক BaseType_t xAutoReload ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_সূচক = ( int32_t ) xTimer;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTimerHandle != ফাঁকা )
                    {
                        vTimerSetReloadMode( xInternalTimerHandle, xAutoReload );
                    }
                }
            }
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGetReloadModeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerGetReloadModeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_সূচক = ( int32_t ) xTimer;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTimerHandle != ফাঁকা )
                    {
                        xReturn = xTimerGetReloadMode( xInternalTimerHandle );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_uxTimerGetReloadModeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTimerGetReloadModeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_সূচক = ( int32_t ) xTimer;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTimerHandle != ফাঁকা )
                    {
                        uxReturn = uxTimerGetReloadMode( xInternalTimerHandle );
                    }
                }
            }

            ফেরত uxReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_সূচক = ( int32_t ) xTimer;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTimerHandle != ফাঁকা )
                    {
                        xReturn = xTimerGetPeriod( xInternalTimerHandle );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetExpiryTimeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetExpiryTimeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_সূচক = ( int32_t ) xTimer;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalTimerHandle != ফাঁকা )
                    {
                        xReturn = xTimerGetExpiryTime( xInternalTimerHandle );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Timer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #যদি ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreate( ধ্রুবক অক্ষর * ধ্রুবক pcTimerName,
                                        ধ্রুবক TickType_t xTimerPeriodInTicks,
                                        ধ্রুবক BaseType_t xAutoReload,
                                        শূন্য * ধ্রুবক pvTimerID,
                                        TimerCallbackFunction_t pxCallbackFunction ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            TimerHandle_t xExternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xInternalTimerHandle = xTimerCreate( pcTimerName, xTimerPeriodInTicks, xAutoReload, pvTimerID, MPU_TimerCallback );

                যদি( xInternalTimerHandle != ফাঁকা )
                {
                    MPU_Store_Timer_Handle_At_সূচক( l_সূচক, xInternalTimerHandle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xExternalTimerHandle;
        }

    #endif /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreateStatic( ধ্রুবক অক্ষর * ধ্রুবক pcTimerName,
                                              ধ্রুবক TickType_t xTimerPeriodInTicks,
                                              ধ্রুবক BaseType_t xAutoReload,
                                              শূন্য * ধ্রুবক pvTimerID,
                                              TimerCallbackFunction_t pxCallbackFunction,
                                              StaticTimer_t * px_Timer_বাফার ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            TimerHandle_t xExternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xInternalTimerHandle = xTimerCreateStatic( pcTimerName, xTimerPeriodInTicks, xAutoReload, pvTimerID, MPU_TimerCallback, px_Timer_বাফার );

                যদি( xInternalTimerHandle != ফাঁকা )
                {
                    MPU_Store_Timer_Handle_At_সূচক( l_সূচক, xInternalTimerHandle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xExternalTimerHandle;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        BaseType_t MPU_x_Timer_Get_Static_বাফার( TimerHandle_t xTimer,
                                              StaticTimer_t ** ppx_Timer_বাফার ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xReturn = pdFALSE;

            l_সূচক = ( int32_t ) xTimer;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_Get_Timer_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalTimerHandle != ফাঁকা )
                {
                    xReturn = x_Timer_Get_Static_বাফার( xInternalTimerHandle, ppx_Timer_বাফার );
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGenericCommandFromISR( TimerHandle_t xTimer,
                                                    ধ্রুবক BaseType_t xCommandID,
                                                    ধ্রুবক TickType_t x_Optional_মান,
                                                    BaseType_t * ধ্রুবক pxHigherPriorityTaskWoken,
                                                    ধ্রুবক TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = ( int32_t ) xTimer;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_Get_Timer_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalTimerHandle != ফাঁকা )
                {
                    xReturn = xTimerGenericCommandFromISR( xInternalTimerHandle, xCommandID, x_Optional_মান, pxHigherPriorityTaskWoken, xTicksToWait );
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerDelete( TimerHandle_t xTimer, TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = ( int32_t ) xTimer;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_Get_Timer_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalTimerHandle != ফাঁকা )
                {
                    xReturn = xTimerGenericCommandFromTask( xInternalTimerHandle,
                                                            tmrCOMMAND_DELETE,
                                                            0U, /* xOptionalValue */
                                                            ফাঁকা, /* pxHigherPriorityTaskWoken */
                                                            xTicksToWait );
                    যদি( xReturn != pdFALSE )
                    {
                        MPU_Set_সূচক_Free_In_Kernel_Object_Pool( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for event group APIs.              */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
                                             ধ্রুবক EventBits_t uxBitsToWaitFor,
                                             ধ্রুবক BaseType_t xClearOnExit,
                                             ধ্রুবক BaseType_t xWaitForAllBits,
                                             TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            EventBits_t xReturn = 0;
            xEventGroupWaitBitsParams_t xParams;

            xParams.xEventGroup = xEventGroup;
            xParams.uxBitsToWaitFor = uxBitsToWaitFor;
            xParams.xClearOnExit = xClearOnExit;
            xParams.xWaitForAllBits = xWaitForAllBits;
            xParams.xTicksToWait = xTicksToWait;

            xReturn = MPU_xEventGroupWaitBitsEntry( &( xParams ) );

            ফেরত xReturn;
        }

        EventBits_t MPU_xEventGroupWaitBitsImpl( ধ্রুবক xEventGroupWaitBitsParams_t * pxParams ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupWaitBitsImpl( ধ্রুবক xEventGroupWaitBitsParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            যদি( pxParams != ফাঁকা )
            {
                xAreParamsReadable = x_Port_Is_Authorized_To_Access_বাফার( pxParams,
                                                                      আকার( xEventGroupWaitBitsParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            যদি( xAreParamsReadable == pdTRUE )
            {
                যদি( ( ( pxParams->uxBitsToWaitFor & eventEVENT_BITS_CONTROL_BYTES ) == 0U ) &&
                    ( pxParams->uxBitsToWaitFor != 0U )
                    #যদি ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                        && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( pxParams->xTicksToWait != 0U ) ) )
                    #endif
                    )
                {
                    l_সূচক = ( int32_t ) ( pxParams->xEventGroup );

                    যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                        {
                            xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                            যদি( xInternalEventGroupHandle != ফাঁকা )
                            {
                                xReturn = xEventGroupWaitBits( xInternalEventGroupHandle,
                                                               pxParams->uxBitsToWaitFor,
                                                               pxParams->xClearOnExit,
                                                               pxParams->xWaitForAllBits,
                                                               pxParams->xTicksToWait );
                            }
                        }
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupClearBitsImpl( EventGroupHandle_t xEventGroup,
                                                  ধ্রুবক EventBits_t uxBitsToClear ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupClearBitsImpl( EventGroupHandle_t xEventGroup,
                                                  ধ্রুবক EventBits_t uxBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            যদি( ( uxBitsToClear & eventEVENT_BITS_CONTROL_BYTES ) == 0U )
            {
                l_সূচক = ( int32_t ) xEventGroup;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xInternalEventGroupHandle != ফাঁকা )
                        {
                            xReturn = xEventGroupClearBits( xInternalEventGroupHandle, uxBitsToClear );
                        }
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSetBitsImpl( EventGroupHandle_t xEventGroup,
                                                ধ্রুবক EventBits_t uxBitsToSet ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupSetBitsImpl( EventGroupHandle_t xEventGroup,
                                                ধ্রুবক EventBits_t uxBitsToSet ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            যদি( ( uxBitsToSet & eventEVENT_BITS_CONTROL_BYTES ) == 0U )
            {
                l_সূচক = ( int32_t ) xEventGroup;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xInternalEventGroupHandle != ফাঁকা )
                        {
                            xReturn = xEventGroupSetBits( xInternalEventGroupHandle, uxBitsToSet );
                        }
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSyncImpl( EventGroupHandle_t xEventGroup,
                                             ধ্রুবক EventBits_t uxBitsToSet,
                                             ধ্রুবক EventBits_t uxBitsToWaitFor,
                                             TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupSyncImpl( EventGroupHandle_t xEventGroup,
                                             ধ্রুবক EventBits_t uxBitsToSet,
                                             ধ্রুবক EventBits_t uxBitsToWaitFor,
                                             TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            যদি( ( ( uxBitsToWaitFor & eventEVENT_BITS_CONTROL_BYTES ) == 0U ) &&
                ( uxBitsToWaitFor != 0U )
                #যদি ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                    && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                #endif
                )
            {
                l_সূচক = ( int32_t ) xEventGroup;

                যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( xInternalEventGroupHandle != ফাঁকা )
                        {
                            xReturn = xEventGroupSync( xInternalEventGroupHandle, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
                        }
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_Group_Get_সংখ্যা_Impl( শূন্য * xEventGroup ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Event_Group_Get_সংখ্যা_Impl( শূন্য * xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            l_সূচক = ( int32_t ) xEventGroup;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                {
                    xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalEventGroupHandle != ফাঁকা )
                    {
                        xReturn = ux_Event_Group_Get_সংখ্যা( xInternalEventGroupHandle );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        শূন্য MPU_v_Event_Group_Set_সংখ্যা_Impl( শূন্য * xEventGroup,
                                           UBaseType_t ux_Event_Group_সংখ্যা ) PRIVILEGED_FUNCTION;

        শূন্য MPU_v_Event_Group_Set_সংখ্যা_Impl( শূন্য * xEventGroup,
                                           UBaseType_t ux_Event_Group_সংখ্যা ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            l_সূচক = ( int32_t ) xEventGroup;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                {
                    xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( xInternalEventGroupHandle != ফাঁকা )
                    {
                        v_Event_Group_Set_সংখ্যা( xInternalEventGroupHandle, ux_Event_Group_সংখ্যা );
                    }
                }
            }
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Event Group APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #যদি ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        EventGroupHandle_t MPU_xEventGroupCreate( শূন্য ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = ফাঁকা;
            EventGroupHandle_t xExternalEventGroupHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xInternalEventGroupHandle = xEventGroupCreate();

                যদি( xInternalEventGroupHandle != ফাঁকা )
                {
                    MPU_Store_Event_Group_Handle_At_সূচক( l_সূচক, xInternalEventGroupHandle );
                    xExternalEventGroupHandle = ( EventGroupHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xExternalEventGroupHandle;
        }

    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        EventGroupHandle_t MPU_xEventGroupCreateStatic( StaticEventGroup_t * px_Event_Group_বাফার ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = ফাঁকা;
            EventGroupHandle_t xExternalEventGroupHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

            যদি( l_সূচক != -1 )
            {
                xInternalEventGroupHandle = xEventGroupCreateStatic( px_Event_Group_বাফার );

                যদি( xInternalEventGroupHandle != ফাঁকা )
                {
                    MPU_Store_Event_Group_Handle_At_সূচক( l_সূচক, xInternalEventGroupHandle );
                    xExternalEventGroupHandle = ( EventGroupHandle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                }
                অন্যথা
                {
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                }
            }

            ফেরত xExternalEventGroupHandle;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )

        শূন্য MPU_vEventGroupDelete( EventGroupHandle_t xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = ( int32_t ) xEventGroup;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalEventGroupHandle != ফাঁকা )
                {
                    vEventGroupDelete( xInternalEventGroupHandle );
                    MPU_Set_সূচক_Free_In_Kernel_Object_Pool( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );
                }
            }
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        BaseType_t MPU_x_Event_Group_Get_Static_বাফার( EventGroupHandle_t xEventGroup,
                                                   StaticEventGroup_t ** ppx_Event_Group_বাফার ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = ( int32_t ) xEventGroup;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalEventGroupHandle != ফাঁকা )
                {
                    xReturn = x_Event_Group_Get_Static_বাফার( xInternalEventGroupHandle, ppx_Event_Group_বাফার );
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        BaseType_t MPU_xEventGroupClearBitsFromISR( EventGroupHandle_t xEventGroup,
                                                    ধ্রুবক EventBits_t uxBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = ( int32_t ) xEventGroup;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalEventGroupHandle != ফাঁকা )
                {
                    xReturn = xEventGroupClearBitsFromISR( xInternalEventGroupHandle, uxBitsToClear );
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        BaseType_t MPU_xEventGroupSetBitsFromISR( EventGroupHandle_t xEventGroup,
                                                  ধ্রুবক EventBits_t uxBitsToSet,
                                                  BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = ( int32_t ) xEventGroup;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalEventGroupHandle != ফাঁকা )
                {
                    xReturn = xEventGroupSetBitsFromISR( xInternalEventGroupHandle, uxBitsToSet, pxHigherPriorityTaskWoken );
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupGetBitsFromISR( EventGroupHandle_t xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = ( int32_t ) xEventGroup;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( xInternalEventGroupHandle != ফাঁকা )
                {
                    xReturn = xEventGroupGetBitsFromISR( xInternalEventGroupHandle );
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for stream buffer APIs.            */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_x_Stream_বাফার_Send_Impl( Stream_বাফার_Handle_t x_Stream_বাফার,
                                          ধ্রুবক শূন্য * pv_Tx_তথ্য,
                                          size_t x_তথ্য_দৈর্ঘ্য_Bytes,
                                          TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_Stream_বাফার_Send_Impl( Stream_বাফার_Handle_t x_Stream_বাফার,
                                          ধ্রুবক শূন্য * pv_Tx_তথ্য,
                                          size_t x_তথ্য_দৈর্ঘ্য_Bytes,
                                          TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t x_Is_Tx_তথ্য_বাফার_Readable = pdFALSE;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = pdFALSE;

            যদি( pv_Tx_তথ্য != ফাঁকা )
            {
                x_Is_Tx_তথ্য_বাফার_Readable = x_Port_Is_Authorized_To_Access_বাফার( pv_Tx_তথ্য,
                                                                           x_তথ্য_দৈর্ঘ্য_Bytes,
                                                                           tskMPU_READ_PERMISSION );

                যদি( x_Is_Tx_তথ্য_বাফার_Readable == pdTRUE )
                {
                    l_সূচক = ( int32_t ) x_Stream_বাফার;

                    যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার == pdTRUE )
                        {
                            x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                            যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                            {
                                xReturn = x_Stream_বাফার_Send( x_Internal_Stream_বাফার_Handle, pv_Tx_তথ্য, x_তথ্য_দৈর্ঘ্য_Bytes, xTicksToWait );
                            }
                        }
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_x_Stream_বাফার_Receive_Impl( Stream_বাফার_Handle_t x_Stream_বাফার,
                                             শূন্য * pv_Rx_তথ্য,
                                             size_t x_বাফার_দৈর্ঘ্য_Bytes,
                                             TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_Stream_বাফার_Receive_Impl( Stream_বাফার_Handle_t x_Stream_বাফার,
                                             শূন্য * pv_Rx_তথ্য,
                                             size_t x_বাফার_দৈর্ঘ্য_Bytes,
                                             TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t x_Is_Rx_তথ্য_বাফার_Writeable = pdFALSE;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = pdFALSE;

            যদি( pv_Rx_তথ্য != ফাঁকা )
            {
                x_Is_Rx_তথ্য_বাফার_Writeable = x_Port_Is_Authorized_To_Access_বাফার( pv_Rx_তথ্য,
                                                                            x_বাফার_দৈর্ঘ্য_Bytes,
                                                                            tskMPU_WRITE_PERMISSION );

                যদি( x_Is_Rx_তথ্য_বাফার_Writeable == pdTRUE )
                {
                    l_সূচক = ( int32_t ) x_Stream_বাফার;

                    যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                        যদি( x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার == pdTRUE )
                        {
                            x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                            যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                            {
                                xReturn = x_Stream_বাফার_Receive( x_Internal_Stream_বাফার_Handle, pv_Rx_তথ্য, x_বাফার_দৈর্ঘ্য_Bytes, xTicksToWait );
                            }
                        }
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_বাফার_Is_Full_Impl( Stream_বাফার_Handle_t x_Stream_বাফার ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_x_Stream_বাফার_Is_Full_Impl( Stream_বাফার_Handle_t x_Stream_বাফার ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = pdFALSE;

            l_সূচক = ( int32_t ) x_Stream_বাফার;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার == pdTRUE )
                {
                    x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                    {
                        xReturn = x_Stream_বাফার_Is_Full( x_Internal_Stream_বাফার_Handle );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_বাফার_Is_Empty_Impl( Stream_বাফার_Handle_t x_Stream_বাফার ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_x_Stream_বাফার_Is_Empty_Impl( Stream_বাফার_Handle_t x_Stream_বাফার ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = pdFALSE;

            l_সূচক = ( int32_t ) x_Stream_বাফার;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার == pdTRUE )
                {
                    x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                    {
                        xReturn = x_Stream_বাফার_Is_Empty( x_Internal_Stream_বাফার_Handle );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_x_Stream_বাফার_Spaces_Available_Impl( Stream_বাফার_Handle_t x_Stream_বাফার ) PRIVILEGED_FUNCTION;

        size_t MPU_x_Stream_বাফার_Spaces_Available_Impl( Stream_বাফার_Handle_t x_Stream_বাফার ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = pdFALSE;

            l_সূচক = ( int32_t ) x_Stream_বাফার;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার == pdTRUE )
                {
                    x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                    {
                        xReturn = x_Stream_বাফার_Spaces_Available( x_Internal_Stream_বাফার_Handle );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_x_Stream_বাফার_Bytes_Available_Impl( Stream_বাফার_Handle_t x_Stream_বাফার ) PRIVILEGED_FUNCTION;

        size_t MPU_x_Stream_বাফার_Bytes_Available_Impl( Stream_বাফার_Handle_t x_Stream_বাফার ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = pdFALSE;

            l_সূচক = ( int32_t ) x_Stream_বাফার;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার == pdTRUE )
                {
                    x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                    {
                        xReturn = x_Stream_বাফার_Bytes_Available( x_Internal_Stream_বাফার_Handle );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_বাফার_Set_Trigger_Level_Impl( Stream_বাফার_Handle_t x_Stream_বাফার,
                                                         size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_x_Stream_বাফার_Set_Trigger_Level_Impl( Stream_বাফার_Handle_t x_Stream_বাফার,
                                                         size_t xTriggerLevel ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = pdFALSE;

            l_সূচক = ( int32_t ) x_Stream_বাফার;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার == pdTRUE )
                {
                    x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                    {
                        xReturn = x_Stream_বাফার_Set_Trigger_Level( x_Internal_Stream_বাফার_Handle, xTriggerLevel );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes_Impl( Stream_বাফার_Handle_t x_Stream_বাফার ) PRIVILEGED_FUNCTION;

        size_t MPU_x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes_Impl( Stream_বাফার_Handle_t x_Stream_বাফার ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = pdFALSE;

            l_সূচক = ( int32_t ) x_Stream_বাফার;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( x_Calling_Task_Is_Authorized_To_Access_Stream_বাফার == pdTRUE )
                {
                    x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                    যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                    {
                        xReturn = x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes( x_Internal_Stream_বাফার_Handle );
                    }
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Stream Buffer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #যদি ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        Stream_বাফার_Handle_t MPU_x_Stream_বাফার_Generic_Create( size_t x_বাফার_আকার_Bytes,
                                                             size_t xTriggerLevelBytes,
                                                             BaseType_t x_Stream_বাফার_Type,
                                                             Stream_বাফার_Callback_Function_t pxSendCompletedCallback,
                                                             Stream_বাফার_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            Stream_বাফার_Handle_t x_External_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ফাঁকা ) &&
                          ( pxReceiveCompletedCallback == ফাঁকা ) );

            যদি( ( pxSendCompletedCallback == ফাঁকা ) &&
                ( pxReceiveCompletedCallback == ফাঁকা ) )
            {
                l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

                যদি( l_সূচক != -1 )
                {
                    x_Internal_Stream_বাফার_Handle = x_Stream_বাফার_Generic_Create( x_বাফার_আকার_Bytes,
                                                                              xTriggerLevelBytes,
                                                                              x_Stream_বাফার_Type,
                                                                              ফাঁকা,
                                                                              ফাঁকা );

                    যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                    {
                        MPU_Store_Stream_বাফার_Handle_At_সূচক( l_সূচক, x_Internal_Stream_বাফার_Handle );
                        x_External_Stream_বাফার_Handle = ( Stream_বাফার_Handle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                    }
                    অন্যথা
                    {
                        MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                    }
                }
            }
            অন্যথা
            {
                trace_STREAM_বাফার_CREATE_FAILED( x_Stream_বাফার_Type );
                x_External_Stream_বাফার_Handle = ফাঁকা;
            }

            ফেরত x_External_Stream_বাফার_Handle;
        }

    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        Stream_বাফার_Handle_t MPU_x_Stream_বাফার_Generic_Create_Static( size_t x_বাফার_আকার_Bytes,
                                                                   size_t xTriggerLevelBytes,
                                                                   BaseType_t x_Stream_বাফার_Type,
                                                                   uint8_t * ধ্রুবক puc_Stream_বাফার_Storage_Area,
                                                                   Static_Stream_বাফার_t * ধ্রুবক px_Static_Stream_বাফার,
                                                                   Stream_বাফার_Callback_Function_t pxSendCompletedCallback,
                                                                   Stream_বাফার_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            Stream_বাফার_Handle_t x_External_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ফাঁকা ) &&
                          ( pxReceiveCompletedCallback == ফাঁকা ) );

            যদি( ( pxSendCompletedCallback == ফাঁকা ) &&
                ( pxReceiveCompletedCallback == ফাঁকা ) )
            {
                l_সূচক = MPU_Get_Free_সূচক_In_Kernel_Object_Pool();

                যদি( l_সূচক != -1 )
                {
                    x_Internal_Stream_বাফার_Handle = x_Stream_বাফার_Generic_Create_Static( x_বাফার_আকার_Bytes,
                                                                                    xTriggerLevelBytes,
                                                                                    x_Stream_বাফার_Type,
                                                                                    puc_Stream_বাফার_Storage_Area,
                                                                                    px_Static_Stream_বাফার,
                                                                                    ফাঁকা,
                                                                                    ফাঁকা );

                    যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                    {
                        MPU_Store_Stream_বাফার_Handle_At_সূচক( l_সূচক, x_Internal_Stream_বাফার_Handle );
                        x_External_Stream_বাফার_Handle = ( Stream_বাফার_Handle_t ) CONVERT_TO_EXTERNAL_সূচক( l_সূচক );
                    }
                    অন্যথা
                    {
                        MPU_Set_সূচক_Free_In_Kernel_Object_Pool( l_সূচক );
                    }
                }
            }
            অন্যথা
            {
                trace_STREAM_বাফার_CREATE_STATIC_FAILED( xReturn, x_Stream_বাফার_Type );
                x_External_Stream_বাফার_Handle = ফাঁকা;
            }

            ফেরত x_External_Stream_বাফার_Handle;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        শূন্য MPU_v_Stream_বাফার_Delete( Stream_বাফার_Handle_t x_Stream_বাফার ) /* PRIVILEGED_FUNCTION */
        {
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = ( int32_t ) x_Stream_বাফার;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                {
                    v_Stream_বাফার_Delete( x_Internal_Stream_বাফার_Handle );
                }

                MPU_Set_সূচক_Free_In_Kernel_Object_Pool( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );
            }
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_বাফার_Reset( Stream_বাফার_Handle_t x_Stream_বাফার ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = ( int32_t ) x_Stream_বাফার;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                {
                    xReturn = x_Stream_বাফার_Reset( x_Internal_Stream_বাফার_Handle );
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        BaseType_t MPU_x_Stream_বাফার_Get_Static_Buffers( Stream_বাফার_Handle_t xStreamBuffers,
                                                      uint8_t * ppuc_Stream_বাফার_Storage_Area,
                                                      Static_Stream_বাফার_t * ppx_Static_Stream_বাফার ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = ( int32_t ) xStreamBuffers;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                {
                    xReturn = MPU_x_Stream_বাফার_Get_Static_Buffers( x_Internal_Stream_বাফার_Handle, ppuc_Stream_বাফার_Storage_Area, ppx_Static_Stream_বাফার );
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

    size_t MPU_x_Stream_বাফার_Send_From_ISR( Stream_বাফার_Handle_t x_Stream_বাফার,
                                         ধ্রুবক শূন্য * pv_Tx_তথ্য,
                                         size_t x_তথ্য_দৈর্ঘ্য_Bytes,
                                         BaseType_t * ধ্রুবক pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
        int32_t l_সূচক;

        l_সূচক = ( int32_t ) x_Stream_বাফার;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
            {
                xReturn = x_Stream_বাফার_Send_From_ISR( x_Internal_Stream_বাফার_Handle, pv_Tx_তথ্য, x_তথ্য_দৈর্ঘ্য_Bytes, pxHigherPriorityTaskWoken );
            }
        }

        ফেরত xReturn;
    }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

    size_t MPU_x_Stream_বাফার_Receive_From_ISR( Stream_বাফার_Handle_t x_Stream_বাফার,
                                            শূন্য * pv_Rx_তথ্য,
                                            size_t x_বাফার_দৈর্ঘ্য_Bytes,
                                            BaseType_t * ধ্রুবক pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
        int32_t l_সূচক;

        l_সূচক = ( int32_t ) x_Stream_বাফার;

        যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
        {
            x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

            যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
            {
                xReturn = x_Stream_বাফার_Receive_From_ISR( x_Internal_Stream_বাফার_Handle, pv_Rx_তথ্য, x_বাফার_দৈর্ঘ্য_Bytes, pxHigherPriorityTaskWoken );
            }
        }

        ফেরত xReturn;
    }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_বাফার_Send_Completed_From_ISR( Stream_বাফার_Handle_t x_Stream_বাফার,
                                                          BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = ( int32_t ) x_Stream_বাফার;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                {
                    xReturn = x_Stream_বাফার_Send_Completed_From_ISR( x_Internal_Stream_বাফার_Handle, pxHigherPriorityTaskWoken );
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_বাফার_Receive_Completed_From_ISR( Stream_বাফার_Handle_t x_Stream_বাফার,
                                                             BaseType_t * pxHigherPriorityTaskWoken ) /*PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = ( int32_t ) x_Stream_বাফার;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                {
                    xReturn = x_Stream_বাফার_Receive_Completed_From_ISR( x_Internal_Stream_বাফার_Handle, pxHigherPriorityTaskWoken );
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

    #যদি ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_বাফার_Reset_From_ISR( Stream_বাফার_Handle_t x_Stream_বাফার ) /*PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            Stream_বাফার_Handle_t x_Internal_Stream_বাফার_Handle = ফাঁকা;
            int32_t l_সূচক;

            l_সূচক = ( int32_t ) x_Stream_বাফার;

            যদি( IS_EXTERNAL_সূচক_VALID( l_সূচক ) != pdFALSE )
            {
                x_Internal_Stream_বাফার_Handle = MPU_Get_Stream_বাফার_Handle_At_সূচক( CONVERT_TO_INTERNAL_সূচক( l_সূচক ) );

                যদি( x_Internal_Stream_বাফার_Handle != ফাঁকা )
                {
                    xReturn = x_Stream_বাফার_Reset_From_ISR( x_Internal_Stream_বাফার_Handle );
                }
            }

            ফেরত xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h. */

    #যদি configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #অন্তর্ভাব "application_defined_privileged_functions.h"
    #endif
/*-----------------------------------------------------------*/

/**
 * @brief Array of system call implementation functions.
 *
 * The index in the array MUST match the corresponding system call number
 * defined in mpu_wrappers.h.
 */
    PRIVILEGED_তথ্য UBaseType_t uxSystemCallImplementations[ অঙ্ক_SYSTEM_CALLS ] =
    {
        #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_xTaskGenericNotifyImpl,                     /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyWaitImpl,                 /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #endif

        #যদি ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_xTimerGenericCommandFromTaskImpl,           /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #endif

        #যদি ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_xEventGroupWaitBitsImpl,                    /* SYSTEM_CALL_xEventGroupWaitBits. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupWaitBits. */
        #endif

        /* The system calls above this line take 5 parameters. */

        #যদি ( INCLUDE_xTaskDelayUntil == 1 )
            ( UBaseType_t ) MPU_xTaskDelayUntilImpl,                        /* SYSTEM_CALL_xTaskDelayUntil. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskDelayUntil. */
        #endif

        #যদি ( INCLUDE_xTaskAbortDelay == 1 )
            ( UBaseType_t ) MPU_xTaskAbortDelayImpl,                        /* SYSTEM_CALL_xTaskAbortDelay. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskAbortDelay. */
        #endif

        #যদি ( INCLUDE_vTaskDelay == 1 )
            ( UBaseType_t ) MPU_vTaskDelayImpl,                             /* SYSTEM_CALL_vTaskDelay. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskDelay. */
        #endif

        #যদি ( INCLUDE_uxTaskPriorityGet == 1 )
            ( UBaseType_t ) MPU_uxTaskPriorityGetImpl,                      /* SYSTEM_CALL_uxTaskPriorityGet. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskPriorityGet. */
        #endif

        #যদি ( INCLUDE_eTaskGetState == 1 )
            ( UBaseType_t ) MPU_eTaskGetStateImpl,                          /* SYSTEM_CALL_eTaskGetState. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_eTaskGetState. */
        #endif

        #যদি ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_vTaskGetInfoImpl,                           /* SYSTEM_CALL_vTaskGetInfo. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskGetInfo. */
        #endif

        #যদি ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
            ( UBaseType_t ) MPU_xTaskGetIdleTaskHandleImpl,                 /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #endif

        #যদি ( INCLUDE_vTaskSuspend == 1 )
            ( UBaseType_t ) MPU_vTaskSuspendImpl,                           /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) MPU_vTaskResumeImpl,                            /* SYSTEM_CALL_vTaskResume. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskResume. */
        #endif

        ( UBaseType_t ) MPU_x_Task_Get_Tick_গুনতি_Impl,                          /* SYSTEM_CALL_xTaskGetTickCount. */
        ( UBaseType_t ) MPU_ux_Task_Get_সংখ্যা_Of_Tasks_Impl,                     /* SYSTEM_CALL_uxTaskGetNumberOfTasks. */

        #যদি ( configGENERATE_RUN_TIME_STATS == 1 )
            ( UBaseType_t ) MPU_ul_Task_Get_Run_Time_গণক_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) MPU_ulTaskGetRunTimePercentImpl,                /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #endif

        #যদি ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
            ( UBaseType_t ) MPU_ulTaskGetIdleRunTimePercentImpl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_Run_Time_গণক_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #endif

        #যদি ( configUSE_APPLICATION_TASK_TAG == 1 )
            ( UBaseType_t ) MPU_vTaskSetApplicationTaskTagImpl,             /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) MPU_xTaskGetApplicationTaskTagImpl,             /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #endif

        #যদি ( config_অঙ্ক_THREAD_LOCAL_STORAGE_POINTERS != 0 )
            ( UBaseType_t ) MPU_vTaskSetThreadLocalStoragePointerImpl,      /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) MPU_pvTaskGetThreadLocalStoragePointerImpl,     /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #endif

        #যদি ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_uxTaskGetSystemStateImpl,                   /* SYSTEM_CALL_uxTaskGetSystemState. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetSystemState. */
        #endif

        #যদি ( INCLUDE_ux_Task_Get_স্তূপ_উপরের_Water_Mark == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark_Impl,            /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #endif

        #যদি ( INCLUDE_ux_Task_Get_স্তূপ_উপরের_Water_Mark2 == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_স্তূপ_উপরের_Water_Mark2_Impl,           /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #endif

        #যদি ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )
            ( UBaseType_t ) MPU_xTaskGetCurrentTaskHandleImpl,              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #endif

        #যদি ( INCLUDE_xTaskGetSchedulerState == 1 )
            ( UBaseType_t ) MPU_xTaskGetSchedulerStateImpl,                 /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #endif

        ( UBaseType_t ) MPU_vTaskSetTimeOutStateImpl,                       /* SYSTEM_CALL_vTaskSetTimeOutState. */
        ( UBaseType_t ) MPU_xTaskCheckForTimeOutImpl,                       /* SYSTEM_CALL_xTaskCheckForTimeOut. */

        #যদি ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_ulTaskGenericNotifyTakeImpl,                /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyStateClearImpl,           /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) MPU_ul_Task_Generic_Notify_মান_Clear_Impl,          /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #endif

        ( UBaseType_t ) MPU_xQueueGenericSendImpl,                          /* SYSTEM_CALL_xQueueGenericSend. */
        ( UBaseType_t ) MPU_uxQueueMessagesWaitingImpl,                     /* SYSTEM_CALL_uxQueueMessagesWaiting. */
        ( UBaseType_t ) MPU_uxQueueSpacesAvailableImpl,                     /* SYSTEM_CALL_uxQueueSpacesAvailable. */
        ( UBaseType_t ) MPU_xQueueReceiveImpl,                              /* SYSTEM_CALL_xQueueReceive. */
        ( UBaseType_t ) MPU_xQueuePeekImpl,                                 /* SYSTEM_CALL_xQueuePeek. */
        ( UBaseType_t ) MPU_xQueueSemaphoreTakeImpl,                        /* SYSTEM_CALL_xQueueSemaphoreTake. */

        #যদি ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
            ( UBaseType_t ) MPU_xQueueGetMutexHolderImpl,                   /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #endif

        #যদি ( configUSE_RECURSIVE_MUTEXES == 1 )
            ( UBaseType_t ) MPU_xQueueTakeMutexRecursiveImpl,               /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) MPU_xQueueGiveMutexRecursiveImpl,               /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #endif

        #যদি ( configUSE_QUEUE_SETS == 1 )
            ( UBaseType_t ) MPU_xQueueSelectFromSetImpl,                    /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) MPU_xQueueAddToSetImpl,                         /* SYSTEM_CALL_xQueueAddToSet. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueAddToSet. */
        #endif

        #যদি config_QUEUE_REGISTRY_আকার > 0
            ( UBaseType_t ) MPU_vQueueAddToRegistryImpl,                    /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) MPU_vQueueUnregisterQueueImpl,                  /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) MPU_pcQueueGetNameImpl,                         /* SYSTEM_CALL_pcQueueGetName. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcQueueGetName. */
        #endif

        #যদি ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_pvTimerGetTimerIDImpl,                      /* SYSTEM_CALL_pvTimerGetTimerID. */
            ( UBaseType_t ) MPU_vTimerSetTimerIDImpl,                       /* SYSTEM_CALL_vTimerSetTimerID. */
            ( UBaseType_t ) MPU_xTimerIsTimerActiveImpl,                    /* SYSTEM_CALL_xTimerIsTimerActive. */
            ( UBaseType_t ) MPU_xTimerGetTimerDaemonTaskHandleImpl,         /* SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle. */
            ( UBaseType_t ) MPU_pcTimerGetNameImpl,                         /* SYSTEM_CALL_pcTimerGetName. */
            ( UBaseType_t ) MPU_vTimerSetReloadModeImpl,                    /* SYSTEM_CALL_vTimerSetReloadMode. */
            ( UBaseType_t ) MPU_xTimerGetReloadModeImpl,                    /* SYSTEM_CALL_xTimerGetReloadMode. */
            ( UBaseType_t ) MPU_uxTimerGetReloadModeImpl,                   /* SYSTEM_CALL_uxTimerGetReloadMode. */
            ( UBaseType_t ) MPU_xTimerGetPeriodImpl,                        /* SYSTEM_CALL_xTimerGetPeriod. */
            ( UBaseType_t ) MPU_xTimerGetExpiryTimeImpl,                    /* SYSTEM_CALL_xTimerGetExpiryTime. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTimerGetTimerID. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTimerSetTimerID. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerIsTimerActive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcTimerGetName. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTimerSetReloadMode. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGetReloadMode. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTimerGetReloadMode. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGetPeriod. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGetExpiryTime. */
        #endif

        #যদি ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_xEventGroupClearBitsImpl,                   /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) MPU_xEventGroupSetBitsImpl,                     /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) MPU_xEventGroupSyncImpl,                        /* SYSTEM_CALL_xEventGroupSync. */

            #যদি ( configUSE_TRACE_FACILITY == 1 )
                ( UBaseType_t ) MPU_ux_Event_Group_Get_সংখ্যা_Impl,              /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) MPU_v_Event_Group_Set_সংখ্যা_Impl,               /* SYSTEM_CALL_vEventGroupSetNumber. */
            #অন্যথা
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_vEventGroupSetNumber. */
            #endif
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSync. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxEventGroupGetNumber. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vEventGroupSetNumber. */
        #endif

        #যদি ( configUSE_STREAM_BUFFERS == 1 )
            ( UBaseType_t ) MPU_x_Stream_বাফার_Send_Impl,                      /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) MPU_x_Stream_বাফার_Receive_Impl,                   /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) MPU_x_Stream_বাফার_Is_Full_Impl,                    /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) MPU_x_Stream_বাফার_Is_Empty_Impl,                   /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) MPU_x_Stream_বাফার_Spaces_Available_Impl,           /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) MPU_x_Stream_বাফার_Bytes_Available_Impl,            /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) MPU_x_Stream_বাফার_Set_Trigger_Level_Impl,           /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) MPU_x_Stream_বাফার_পরবর্তী_Message_দৈর্ঘ্য_Bytes_Impl     /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #অন্যথা
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #endif

    };
/*-----------------------------------------------------------*/

#endif /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/
