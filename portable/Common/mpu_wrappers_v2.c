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
#घोषणा MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#समावेश "FreeRTOS.h"
#समावेश "task.h"
#समावेश "queue.h"
#समावेश "timers.h"
#समावेश "event_groups.h"
#समावेश "stream_buffer.h"
#समावेश "mpu_prototypes.h"
#समावेश "mpu_syscall_numbers.h"

#अघोषित MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#अगर ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #अगर_अघोषित config_PROTECTED_KERNEL_OBJECT_POOL_आकार
        #त्रुटि config_PROTECTED_KERNEL_OBJECT_POOL_आकार must be defined to maximum संख्या of kernel objects in the application.
    #पूर्ण_अगर

/**
 * @brief Offset added to the index before returning to the user.
 *
 * If the actual handle is stored at index i, ( i + INDEX_OFFSET )
 * is returned to the user.
 */
    #घोषणा सूचकांक_OFFSET    1

/**
 * @brief Opaque type for a kernel object.
 */
    काष्ठा OpaqueObject;
    प्रकार काष्ठा OpaqueObject * OpaqueObjectHandle_t;

/**
 * @brief Defines kernel object in the kernel object pool.
 */
    प्रकार काष्ठा KernelObject
    {
        OpaqueObjectHandle_t xInternalObjectHandle;
        uint32_t ulKernelObjectType;
        व्योम * pv_Kernel_Object_तथ्य;
    } KernelObject_t;

/**
 * @brief Kernel object types.
 */
    #घोषणा KERNEL_OBJECT_TYPE_INVALID          ( 0UL )
    #घोषणा KERNEL_OBJECT_TYPE_QUEUE            ( 1UL )
    #घोषणा KERNEL_OBJECT_TYPE_TASK             ( 2UL )
    #घोषणा KERNEL_OBJECT_TYPE_STREAM_बफर    ( 3UL )
    #घोषणा KERNEL_OBJECT_TYPE_EVENT_GROUP      ( 4UL )
    #घोषणा KERNEL_OBJECT_TYPE_TIMER            ( 5UL )

/**
 * @brief Checks whether an external index is valid or not.
 */
    #घोषणा IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक )   \
    ( ( ( ( l_सूचकांक ) >= सूचकांक_OFFSET ) &&       \
        ( ( l_सूचकांक ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_आकार + सूचकांक_OFFSET ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Checks whether an internal index is valid or not.
 */
    #घोषणा IS_INTERNAL_सूचकांक_VALID( l_सूचकांक )   \
    ( ( ( ( l_सूचकांक ) >= 0 ) &&                  \
        ( ( l_सूचकांक ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_आकार ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Converts an internal index into external.
 */
    #घोषणा CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक )    ( ( l_सूचकांक ) + सूचकांक_OFFSET )

/**
 * @brief Converts an external index into internal.
 */
    #घोषणा CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक )    ( ( l_सूचकांक ) - सूचकांक_OFFSET )

/**
 * @brief Max value that fits in a UBaseType_t type.
 */
    #घोषणा mpuUBASETYPE_MAX    ( ~( ( UBaseType_t ) 0 ) )

/**
 * @brief Check if multiplying a and b will result in overflow.
 */
    #घोषणा mpuMULTIPLY_BASETYPE_WILL_OVERFLOW( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( mpuUBASETYPE_MAX / ( a ) ) ) )

/**
 * @brief Get the index of a free slot in the kernel object pool.
 *
 * If a free slot is found, this function marks the slot as
 * "not free".
 *
 * @return Index of a free slot is returned, if a free slot is
 *         found. Otherwise -1 is returned.
 */
    अटल int32_t MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool( व्योम ) PRIVILEGED_FUNCTION;

/**
 * @brief Set the given index as free in the kernel object pool.
 *
 * @param lIndex The index to set as free.
 */
    अटल व्योम MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( int32_t l_सूचकांक ) PRIVILEGED_FUNCTION;

/**
 * @brief Get the index at which a given kernel object is stored.
 *
 * @param xHandle The given kernel object handle.
 * @param ulKernelObjectType The kernel object type.
 *
 * @return Index at which the kernel object is stored if it is a valid
 *         handle, -1 otherwise.
 */
    अटल int32_t MPU_Get_सूचकांक_For_Handle( OpaqueObjectHandle_t xHandle,
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
    अटल व्योम MPU_Store_Handle_And_तथ्य_At_सूचकांक( int32_t l_सूचकांक,
                                               OpaqueObjectHandle_t xHandle,
                                               व्योम * pv_Kernel_Object_तथ्य,
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
    अटल OpaqueObjectHandle_t MPU_Get_Handle_At_सूचकांक( int32_t l_सूचकांक,
                                                      uint32_t ulKernelObjectType ) PRIVILEGED_FUNCTION;

    #अगर ( configUSE_TIMERS == 1 )

/**
 * @brief The function registered as callback for all the timers.
 *
 * We intercept all the timer callbacks so that we can call application
 * callbacks with opaque handle.
 *
 * @param xInternalHandle The internal timer handle.
 */
        अटल व्योम MPU_TimerCallback( TimerHandle_t xInternalHandle ) PRIVILEGED_FUNCTION;

    #पूर्ण_अगर /* #if ( configUSE_TIMERS == 1 ) */

/*
 * Wrappers to keep all the casting in one place.
 */
    #घोषणा MPU_Store_Queue_Handle_At_सूचकांक( l_सूचकांक, xHandle )                 MPU_Store_Handle_And_तथ्य_At_सूचकांक( ( l_सूचकांक ), ( OpaqueObjectHandle_t ) ( xHandle ), शून्य, KERNEL_OBJECT_TYPE_QUEUE )
    #घोषणा MPU_Get_Queue_Handle_At_सूचकांक( l_सूचकांक )                            ( QueueHandle_t ) MPU_Get_Handle_At_सूचकांक( ( l_सूचकांक ), KERNEL_OBJECT_TYPE_QUEUE )

    #अगर ( configUSE_QUEUE_SETS == 1 )
        #घोषणा MPU_Store_Queue_Set_Handle_At_सूचकांक( l_सूचकांक, xHandle )          MPU_Store_Handle_And_तथ्य_At_सूचकांक( ( l_सूचकांक ), ( OpaqueObjectHandle_t ) ( xHandle ), शून्य, KERNEL_OBJECT_TYPE_QUEUE )
        #घोषणा MPU_Get_Queue_Set_Handle_At_सूचकांक( l_सूचकांक )                     ( QueueSetHandle_t ) MPU_Get_Handle_At_सूचकांक( ( l_सूचकांक ), KERNEL_OBJECT_TYPE_QUEUE )
        #घोषणा MPU_Store_Queue_Set_Member_Handle_At_सूचकांक( l_सूचकांक, xHandle )    MPU_Store_Handle_And_तथ्य_At_सूचकांक( ( l_सूचकांक ), ( OpaqueObjectHandle_t ) ( xHandle ), शून्य, KERNEL_OBJECT_TYPE_QUEUE )
        #घोषणा MPU_Get_Queue_Set_Member_Handle_At_सूचकांक( l_सूचकांक )               ( QueueSetMemberHandle_t ) MPU_Get_Handle_At_सूचकांक( ( l_सूचकांक ), KERNEL_OBJECT_TYPE_QUEUE )
        #घोषणा MPU_Get_सूचकांक_For_Queue_Set_Member_Handle( xHandle )             MPU_Get_सूचकांक_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_QUEUE )
    #पूर्ण_अगर

/*
 * Wrappers to keep all the casting in one place for Task APIs.
 */
    #घोषणा MPU_Store_Task_Handle_At_सूचकांक( l_सूचकांक, xHandle )            MPU_Store_Handle_And_तथ्य_At_सूचकांक( ( l_सूचकांक ), ( OpaqueObjectHandle_t ) ( xHandle ), शून्य, KERNEL_OBJECT_TYPE_TASK )
    #घोषणा MPU_Get_Task_Handle_At_सूचकांक( l_सूचकांक )                       ( TaskHandle_t ) MPU_Get_Handle_At_सूचकांक( ( l_सूचकांक ), KERNEL_OBJECT_TYPE_TASK )
    #घोषणा MPU_Get_सूचकांक_For_Task_Handle( xHandle )                     MPU_Get_सूचकांक_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TASK )

    #अगर ( configUSE_EVENT_GROUPS == 1 )
/*
 * Wrappers to keep all the casting in one place for Event Group APIs.
 */
        #घोषणा MPU_Store_Event_Group_Handle_At_सूचकांक( l_सूचकांक, xHandle )      MPU_Store_Handle_And_तथ्य_At_सूचकांक( ( l_सूचकांक ), ( OpaqueObjectHandle_t ) ( xHandle ), शून्य, KERNEL_OBJECT_TYPE_EVENT_GROUP )
        #घोषणा MPU_Get_Event_Group_Handle_At_सूचकांक( l_सूचकांक )                 ( EventGroupHandle_t ) MPU_Get_Handle_At_सूचकांक( ( l_सूचकांक ), KERNEL_OBJECT_TYPE_EVENT_GROUP )
        #घोषणा MPU_Get_सूचकांक_For_Event_Group_Handle( xHandle )               MPU_Get_सूचकांक_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_EVENT_GROUP )

    #पूर्ण_अगर /* #if ( configUSE_EVENT_GROUPS == 1 ) */

    #अगर ( configUSE_STREAM_BUFFERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Stream Buffer APIs.
 */
        #घोषणा MPU_Store_Stream_बफर_Handle_At_सूचकांक( l_सूचकांक, xHandle )    MPU_Store_Handle_And_तथ्य_At_सूचकांक( ( l_सूचकांक ), ( OpaqueObjectHandle_t ) ( xHandle), शून्य, KERNEL_OBJECT_TYPE_STREAM_बफर )
        #घोषणा MPU_Get_Stream_बफर_Handle_At_सूचकांक( l_सूचकांक )               ( Stream_बफर_Handle_t ) MPU_Get_Handle_At_सूचकांक( ( l_सूचकांक ), KERNEL_OBJECT_TYPE_STREAM_बफर )
        #घोषणा MPU_Get_सूचकांक_For_Stream_बफर_Handle( xHandle )             MPU_Get_सूचकांक_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_STREAM_बफर )

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

    #अगर ( configUSE_TIMERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Timer APIs.
 */
        #घोषणा MPU_Store_Timer_Handle_At_सूचकांक( l_सूचकांक, xHandle, pxApplicationCallback )    MPU_Store_Handle_And_तथ्य_At_सूचकांक( ( l_सूचकांक ), ( OpaqueObjectHandle_t ) ( xHandle ), ( व्योम * ) ( pxApplicationCallback ), KERNEL_OBJECT_TYPE_TIMER )
        #घोषणा MPU_Get_Timer_Handle_At_सूचकांक( l_सूचकांक )                                      ( TimerHandle_t ) MPU_Get_Handle_At_सूचकांक( ( l_सूचकांक ), KERNEL_OBJECT_TYPE_TIMER )
        #घोषणा MPU_Get_सूचकांक_For_Timer_Handle( xHandle )                                    MPU_Get_सूचकांक_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TIMER )

    #पूर्ण_अगर /* #if ( configUSE_TIMERS == 1 ) */

/*-----------------------------------------------------------*/

/**
 * @brief Kernel object pool.
 */
    PRIVILEGED_तथ्य अटल KernelObject_t xKernelObjectPool[ config_PROTECTED_KERNEL_OBJECT_POOL_आकार ] = { 0 };
/*-----------------------------------------------------------*/

    अटल int32_t MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool( व्योम ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_Free_सूचकांक = -1;

        /* This function is called only from resource create APIs
         * which are not supposed to be called from ISRs. Therefore,
         * we only need to suspend the scheduler and do not require
         * critical section. */
        vTaskSuspendAll();
        {
            क्रम( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_आकार; i++ )
            {
                अगर( xKernelObjectPool[ i ].xInternalObjectHandle == शून्य )
                {
                    /* Mark this index as not free. */
                    xKernelObjectPool[ i ].xInternalObjectHandle = ( OpaqueObjectHandle_t ) ( ~0U );
                    l_Free_सूचकांक = i;
                    अवरोध;
                }
            }
        }
        ( व्योम ) xTaskResumeAll();

        वापस l_Free_सूचकांक;
    }
/*-----------------------------------------------------------*/

    अटल व्योम MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( int32_t l_सूचकांक ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_INTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE );

        taskENTER_CRITICAL();
        {
            xKernelObjectPool[ l_सूचकांक ].xInternalObjectHandle = शून्य;
            xKernelObjectPool[ l_सूचकांक ].ulKernelObjectType = KERNEL_OBJECT_TYPE_INVALID;
            xKernelObjectPool[ l_सूचकांक ].pv_Kernel_Object_तथ्य = शून्य;
        }
        taskEXIT_CRITICAL();
    }
/*-----------------------------------------------------------*/

    अटल int32_t MPU_Get_सूचकांक_For_Handle( OpaqueObjectHandle_t xHandle,
                                          uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_सूचकांक = -1;

        configASSERT( xHandle != शून्य );

        क्रम( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_आकार; i++ )
        {
            अगर( ( xKernelObjectPool[ i ].xInternalObjectHandle == xHandle ) &&
                ( xKernelObjectPool[ i ].ulKernelObjectType == ulKernelObjectType ) )
            {
                l_सूचकांक = i;
                अवरोध;
            }
        }

        वापस l_सूचकांक;
    }
/*-----------------------------------------------------------*/

    अटल व्योम MPU_Store_Handle_And_तथ्य_At_सूचकांक( int32_t l_सूचकांक,
                                               OpaqueObjectHandle_t xHandle,
                                               व्योम * pv_Kernel_Object_तथ्य,
                                               uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_INTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE );
        xKernelObjectPool[ l_सूचकांक ].xInternalObjectHandle = xHandle;
        xKernelObjectPool[ l_सूचकांक ].ulKernelObjectType = ulKernelObjectType;
        xKernelObjectPool[ l_सूचकांक ].pv_Kernel_Object_तथ्य = pv_Kernel_Object_तथ्य;
    }
/*-----------------------------------------------------------*/

    अटल OpaqueObjectHandle_t MPU_Get_Handle_At_सूचकांक( int32_t l_सूचकांक,
                                                      uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        OpaqueObjectHandle_t xObjectHandle = शून्य;

        configASSERT( IS_INTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE );

        अगर( xKernelObjectPool[ l_सूचकांक ].ulKernelObjectType == ulKernelObjectType )
        {
            xObjectHandle = xKernelObjectPool[ l_सूचकांक ].xInternalObjectHandle;
        }

        वापस xObjectHandle;
    }
/*-----------------------------------------------------------*/

    #अगर ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        व्योम vGrantAccessToKernelObject( TaskHandle_t xExternalTaskHandle,
                                         int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;

            अगर( IS_EXTERNAL_सूचकांक_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                अगर( xExternalTaskHandle == शून्य )
                {
                    vPortGrantAccessToKernelObject( xExternalTaskHandle, CONVERT_TO_INTERNAL_सूचकांक( lExternalKernelObjectHandle ) );
                }
                अन्यथा
                {
                    l_External_Task_सूचकांक = ( int32_t ) xExternalTaskHandle;

                    अगर( IS_EXTERNAL_सूचकांक_VALID( l_External_Task_सूचकांक ) != pdFALSE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_External_Task_सूचकांक ) );

                        अगर( xInternalTaskHandle != शून्य )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle,
                                                            CONVERT_TO_INTERNAL_सूचकांक( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #पूर्ण_अगर /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        व्योम vRevokeAccessToKernelObject( TaskHandle_t xExternalTaskHandle,
                                          int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;

            अगर( IS_EXTERNAL_सूचकांक_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                अगर( xExternalTaskHandle == शून्य )
                {
                    vPortRevokeAccessToKernelObject( xExternalTaskHandle, CONVERT_TO_INTERNAL_सूचकांक( lExternalKernelObjectHandle ) );
                }
                अन्यथा
                {
                    l_External_Task_सूचकांक = ( int32_t ) xExternalTaskHandle;

                    अगर( IS_EXTERNAL_सूचकांक_VALID( l_External_Task_सूचकांक ) != pdFALSE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_External_Task_सूचकांक ) );

                        अगर( xInternalTaskHandle != शून्य )
                        {
                            vPortRevokeAccessToKernelObject( xInternalTaskHandle,
                                                             CONVERT_TO_INTERNAL_सूचकांक( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #पूर्ण_अगर /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )

        अटल व्योम MPU_TimerCallback( TimerHandle_t xInternalHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t i, l_सूचकांक = -1;
            TimerHandle_t xExternalHandle = शून्य;
            TimerCallbackFunction_t pxApplicationCallBack = शून्य;

            /* Coming from the timer task and therefore, should be valid. */
            configASSERT( xInternalHandle != शून्य );

            क्रम( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_आकार; i++ )
            {
                अगर( ( ( TimerHandle_t ) xKernelObjectPool[ i ].xInternalObjectHandle == xInternalHandle ) &&
                    ( xKernelObjectPool[ i ].ulKernelObjectType == KERNEL_OBJECT_TYPE_TIMER ) )
                {
                    l_सूचकांक = i;
                    अवरोध;
                }
            }

            configASSERT( l_सूचकांक != -1 );
            xExternalHandle = ( TimerHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );

            pxApplicationCallBack = ( TimerCallbackFunction_t ) xKernelObjectPool[ l_सूचकांक ].pv_Kernel_Object_तथ्य;
            pxApplicationCallBack( xExternalHandle );
        }

    #पूर्ण_अगर /* #if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for tasks APIs.                   */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_xTaskDelayUntil == 1 )

        BaseType_t MPU_xTaskDelayUntilImpl( TickType_t * स्थिर pxPreviousWakeTime,
                                            TickType_t xTimeIncrement ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskDelayUntilImpl( TickType_t * स्थिर pxPreviousWakeTime,
                                            TickType_t xTimeIncrement ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xIsPreviousWakeTimeAccessible = pdFALSE;

            अगर( ( pxPreviousWakeTime != शून्य ) && ( xTimeIncrement > 0U ) )
            {
                xIsPreviousWakeTimeAccessible = x_Port_Is_Authorized_To_Access_बफर( pxPreviousWakeTime,
                                                                                 माप( TickType_t ),
                                                                                 ( tskMPU_WRITE_PERMISSION | tskMPU_READ_PERMISSION ) );

                अगर( xIsPreviousWakeTimeAccessible == pdTRUE )
                {
                    xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_xTaskAbortDelay == 1 )

        BaseType_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            TaskHandle_t xInternalTaskHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) xTask;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTaskHandle != शून्य )
                    {
                        xReturn = xTaskAbortDelay( xInternalTaskHandle );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_vTaskDelay == 1 )

        व्योम MPU_vTaskDelayImpl( TickType_t xTicksToDelay ) PRIVILEGED_FUNCTION;

        व्योम MPU_vTaskDelayImpl( TickType_t xTicksToDelay ) /* PRIVILEGED_FUNCTION */
        {
            vTaskDelay( xTicksToDelay );
        }

    #पूर्ण_अगर /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_uxTaskPriorityGet == 1 )

        UBaseType_t MPU_uxTaskPriorityGetImpl( स्थिर TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskPriorityGetImpl( स्थिर TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;

            अगर( pxTask == शून्य )
            {
                uxReturn = uxTaskPriorityGet( pxTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) pxTask;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xInternalTaskHandle != शून्य )
                        {
                            uxReturn = uxTaskPriorityGet( xInternalTaskHandle );
                        }
                    }
                }
            }

            वापस uxReturn;
        }

    #पूर्ण_अगर /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            eTaskState eReturn = eInvalid;
            TaskHandle_t xInternalTaskHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            l_सूचकांक = ( int32_t ) pxTask;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTaskHandle != शून्य )
                    {
                        eReturn = eTaskGetState( xInternalTaskHandle );
                    }
                }
            }

            वापस eReturn;
        }

    #पूर्ण_अगर /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TRACE_FACILITY == 1 )

        व्योम MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   TaskStatus_t * pxTaskStatus,
                                   BaseType_t x_Get_Free_ढेर_Space,
                                   eTaskState eState ) PRIVILEGED_FUNCTION;

        व्योम MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   TaskStatus_t * pxTaskStatus,
                                   BaseType_t x_Get_Free_ढेर_Space,
                                   eTaskState eState ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;
            BaseType_t xIsTaskStatusWriteable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            xIsTaskStatusWriteable = x_Port_Is_Authorized_To_Access_बफर( pxTaskStatus,
                                                                      माप( TaskStatus_t ),
                                                                      tskMPU_WRITE_PERMISSION );

            अगर( xIsTaskStatusWriteable == pdTRUE )
            {
                अगर( xTask == शून्य )
                {
                    vTaskGetInfo( xTask, pxTaskStatus, x_Get_Free_ढेर_Space, eState );
                }
                अन्यथा
                {
                    l_सूचकांक = ( int32_t ) xTask;

                    अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                            अगर( xInternalTaskHandle != शून्य )
                            {
                                vTaskGetInfo( xInternalTaskHandle, pxTaskStatus, x_Get_Free_ढेर_Space, eState );
                            }
                        }
                    }
                }
            }
        }

    #पूर्ण_अगर /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( व्योम ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( व्योम ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xIdleTaskHandle = शून्य;

            xIdleTaskHandle = xTaskGetIdleTaskHandle();

            वापस xIdleTaskHandle;
        }

    #पूर्ण_अगर /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_vTaskSuspend == 1 )

        व्योम MPU_vTaskSuspendImpl( TaskHandle_t pxTaskToSuspend ) PRIVILEGED_FUNCTION;

        व्योम MPU_vTaskSuspendImpl( TaskHandle_t pxTaskToSuspend ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            अगर( pxTaskToSuspend == शून्य )
            {
                vTaskSuspend( pxTaskToSuspend );
            }
            अन्यथा
            {
                /* After the scheduler starts, only privileged tasks are allowed
                 * to suspend other tasks. */
                #अगर ( INCLUDE_xTaskGetSchedulerState == 1 )
                    अगर( ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) || ( portIS_TASK_PRIVILEGED() == pdTRUE ) )
                #अन्यथा
                    अगर( portIS_TASK_PRIVILEGED() == pdTRUE )
                #पूर्ण_अगर
                {
                    l_सूचकांक = ( int32_t ) pxTaskToSuspend;

                    अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                            अगर( xInternalTaskHandle != शून्य )
                            {
                                vTaskSuspend( xInternalTaskHandle );
                            }
                        }
                    }
                }
            }
        }

    #पूर्ण_अगर /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_vTaskSuspend == 1 )

        व्योम MPU_vTaskResumeImpl( TaskHandle_t pxTaskToResume ) PRIVILEGED_FUNCTION;

        व्योम MPU_vTaskResumeImpl( TaskHandle_t pxTaskToResume ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            l_सूचकांक = ( int32_t ) pxTaskToResume;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTaskHandle != शून्य )
                    {
                        vTaskResume( xInternalTaskHandle );
                    }
                }
            }
        }

    #पूर्ण_अगर /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_गिनती_Impl( व्योम ) PRIVILEGED_FUNCTION;

    TickType_t MPU_x_Task_Get_Tick_गिनती_Impl( व्योम ) /* PRIVILEGED_FUNCTION */
    {
        TickType_t xReturn;

        xReturn = x_Task_Get_Tick_गिनती();

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_संख्या_Of_Tasks_Impl( व्योम ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Task_Get_संख्या_Of_Tasks_Impl( व्योम ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn;

        uxReturn = ux_Task_Get_संख्या_Of_Tasks();

        वापस uxReturn;
    }
/*-----------------------------------------------------------*/

    #अगर ( configGENERATE_RUN_TIME_STATS == 1 )

        config_RUN_TIME_गणक_TYPE MPU_ul_Task_Get_Run_Time_गणक_Impl( स्थिर TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_RUN_TIME_गणक_TYPE MPU_ul_Task_Get_Run_Time_गणक_Impl( स्थिर TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_RUN_TIME_गणक_TYPE xReturn = 0;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            अगर( xTask == शून्य )
            {
                xReturn = ul_Task_Get_Run_Time_गणक( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xInternalTaskHandle != शून्य )
                        {
                            xReturn = ul_Task_Get_Run_Time_गणक( xInternalTaskHandle );
                        }
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configGENERATE_RUN_TIME_STATS == 1 )

        config_RUN_TIME_गणक_TYPE MPU_ulTaskGetRunTimePercentImpl( स्थिर TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_RUN_TIME_गणक_TYPE MPU_ulTaskGetRunTimePercentImpl( स्थिर TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_RUN_TIME_गणक_TYPE xReturn = 0;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            अगर( xTask == शून्य )
            {
                xReturn = ulTaskGetRunTimePercent( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xInternalTaskHandle != शून्य )
                        {
                            xReturn = ulTaskGetRunTimePercent( xInternalTaskHandle );
                        }
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_RUN_TIME_गणक_TYPE MPU_ulTaskGetIdleRunTimePercentImpl( व्योम ) PRIVILEGED_FUNCTION;

        config_RUN_TIME_गणक_TYPE MPU_ulTaskGetIdleRunTimePercentImpl( व्योम ) /* PRIVILEGED_FUNCTION */
        {
            config_RUN_TIME_गणक_TYPE xReturn;

            xReturn = ulTaskGetIdleRunTimePercent();

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_RUN_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_Run_Time_गणक_Impl( व्योम ) PRIVILEGED_FUNCTION;

        config_RUN_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_Run_Time_गणक_Impl( व्योम ) /* PRIVILEGED_FUNCTION */
        {
            config_RUN_TIME_गणक_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_Run_Time_गणक();

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_APPLICATION_TASK_TAG == 1 )

        व्योम MPU_vTaskSetApplicationTaskTagImpl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_Tag_मूल्य ) PRIVILEGED_FUNCTION;

        व्योम MPU_vTaskSetApplicationTaskTagImpl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_Tag_मूल्य ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            अगर( xTask == शून्य )
            {
                vTaskSetApplicationTaskTag( xTask, px_Tag_मूल्य );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xInternalTaskHandle != शून्य )
                        {
                            vTaskSetApplicationTaskTag( xInternalTaskHandle, px_Tag_मूल्य );
                        }
                    }
                }
            }
        }

    #पूर्ण_अगर /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_APPLICATION_TASK_TAG == 1 )

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = शून्य;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            अगर( xTask == शून्य )
            {
                xReturn = xTaskGetApplicationTaskTag( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xInternalTaskHandle != शून्य )
                        {
                            xReturn = xTaskGetApplicationTaskTag( xInternalTaskHandle );
                        }
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( config_अंक_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        व्योम MPU_vTaskSetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToSet,
                                                        BaseType_t x_सूचकांक,
                                                        व्योम * pv_मूल्य ) PRIVILEGED_FUNCTION;

        व्योम MPU_vTaskSetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToSet,
                                                        BaseType_t x_सूचकांक,
                                                        व्योम * pv_मूल्य ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            अगर( xTaskToSet == शून्य )
            {
                vTaskSetThreadLocalStoragePointer( xTaskToSet, x_सूचकांक, pv_मूल्य );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTaskToSet;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xInternalTaskHandle != शून्य )
                        {
                            vTaskSetThreadLocalStoragePointer( xInternalTaskHandle, x_सूचकांक, pv_मूल्य );
                        }
                    }
                }
            }
        }

    #पूर्ण_अगर /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #अगर ( config_अंक_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        व्योम * MPU_pvTaskGetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToQuery,
                                                           BaseType_t x_सूचकांक ) PRIVILEGED_FUNCTION;

        व्योम * MPU_pvTaskGetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToQuery,
                                                           BaseType_t x_सूचकांक ) /* PRIVILEGED_FUNCTION */
        {
            व्योम * pvReturn = शून्य;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            अगर( xTaskToQuery == शून्य )
            {
                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, x_सूचकांक );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTaskToQuery;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xInternalTaskHandle != शून्य )
                        {
                            pvReturn = pvTaskGetThreadLocalStoragePointer( xInternalTaskHandle, x_सूचकांक );
                        }
                    }
                }
            }

            वापस pvReturn;
        }

    #पूर्ण_अगर /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemStateImpl( TaskStatus_t * pxTaskStatusArray,
                                                  UBaseType_t ux_Array_आकार,
                                                  config_RUN_TIME_गणक_TYPE * pul_योग_Run_Time ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskGetSystemStateImpl( TaskStatus_t * pxTaskStatusArray,
                                                  UBaseType_t ux_Array_आकार,
                                                  config_RUN_TIME_गणक_TYPE * pul_योग_Run_Time ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            BaseType_t xIsTaskStatusArrayWriteable = pdFALSE;
            BaseType_t x_Is_योग_Run_Time_Writeable = pdFALSE;

            अगर( mpuMULTIPLY_BASETYPE_WILL_OVERFLOW( माप( TaskStatus_t ), ux_Array_आकार ) == 0 )
            {
                xIsTaskStatusArrayWriteable = x_Port_Is_Authorized_To_Access_बफर( pxTaskStatusArray,
                                                                               माप( TaskStatus_t ) * ( माप_प्रकार ) ux_Array_आकार,
                                                                               tskMPU_WRITE_PERMISSION );

                अगर( pul_योग_Run_Time != शून्य )
                {
                    x_Is_योग_Run_Time_Writeable = x_Port_Is_Authorized_To_Access_बफर( pul_योग_Run_Time,
                                                                                माप( config_RUN_TIME_गणक_TYPE ),
                                                                                tskMPU_WRITE_PERMISSION );
                }

                अगर( ( xIsTaskStatusArrayWriteable == pdTRUE ) &&
                    ( ( pul_योग_Run_Time == शून्य ) || ( x_Is_योग_Run_Time_Writeable == pdTRUE ) ) )
                {
                    uxReturn = uxTaskGetSystemState( pxTaskStatusArray, ux_Array_आकार, pul_योग_Run_Time );
                }
            }

            वापस uxReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_ux_Task_Get_ढेर_ऊपरी_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ढेर_ऊपरी_Water_Mark_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_Get_ढेर_ऊपरी_Water_Mark_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            अगर( xTask == शून्य )
            {
                uxReturn = ux_Task_Get_ढेर_ऊपरी_Water_Mark( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xInternalTaskHandle != शून्य )
                        {
                            uxReturn = ux_Task_Get_ढेर_ऊपरी_Water_Mark( xInternalTaskHandle );
                        }
                    }
                }
            }

            वापस uxReturn;
        }

    #पूर्ण_अगर /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_ux_Task_Get_ढेर_ऊपरी_Water_Mark2 == 1 )

        config_ढेर_DEPTH_TYPE MPU_ux_Task_Get_ढेर_ऊपरी_Water_Mark2_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_ढेर_DEPTH_TYPE MPU_ux_Task_Get_ढेर_ऊपरी_Water_Mark2_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_ढेर_DEPTH_TYPE uxReturn = 0;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            अगर( xTask == शून्य )
            {
                uxReturn = ux_Task_Get_ढेर_ऊपरी_Water_Mark2( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xInternalTaskHandle != शून्य )
                        {
                            uxReturn = ux_Task_Get_ढेर_ऊपरी_Water_Mark2( xInternalTaskHandle );
                        }
                    }
                }
            }

            वापस uxReturn;
        }

    #पूर्ण_अगर /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( व्योम ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( व्योम ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = शून्य;
            TaskHandle_t xExternalTaskHandle = शून्य;
            int32_t l_सूचकांक;

            xInternalTaskHandle = xTaskGetCurrentTaskHandle();

            अगर( xInternalTaskHandle != शून्य )
            {
                l_सूचकांक = MPU_Get_सूचकांक_For_Task_Handle( xInternalTaskHandle );

                अगर( l_सूचकांक != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
            }

            वापस xExternalTaskHandle;
        }

    #पूर्ण_अगर /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_xTaskGetSchedulerState == 1 )

        BaseType_t MPU_xTaskGetSchedulerStateImpl( व्योम ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGetSchedulerStateImpl( व्योम ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = taskSCHEDULER_NOT_STARTED;

            xReturn = xTaskGetSchedulerState();

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    व्योम MPU_vTaskSetTimeOutStateImpl( TimeOut_t * स्थिर pxTimeOut ) PRIVILEGED_FUNCTION;

    व्योम MPU_vTaskSetTimeOutStateImpl( TimeOut_t * स्थिर pxTimeOut ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xIsTimeOutWriteable = pdFALSE;

        अगर( pxTimeOut != शून्य )
        {
            xIsTimeOutWriteable = x_Port_Is_Authorized_To_Access_बफर( pxTimeOut,
                                                                   माप( TimeOut_t ),
                                                                   tskMPU_WRITE_PERMISSION );

            अगर( xIsTimeOutWriteable == pdTRUE )
            {
                vTaskSetTimeOutState( pxTimeOut );
            }
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCheckForTimeOutImpl( TimeOut_t * स्थिर pxTimeOut,
                                             TickType_t * स्थिर pxTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xTaskCheckForTimeOutImpl( TimeOut_t * स्थिर pxTimeOut,
                                             TickType_t * स्थिर pxTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFALSE;
        BaseType_t xIsTimeOutWriteable = pdFALSE;
        BaseType_t xIsTicksToWaitWriteable = pdFALSE;

        अगर( ( pxTimeOut != शून्य ) && ( pxTicksToWait != शून्य ) )
        {
            xIsTimeOutWriteable = x_Port_Is_Authorized_To_Access_बफर( pxTimeOut,
                                                                   माप( TimeOut_t ),
                                                                   tskMPU_WRITE_PERMISSION );
            xIsTicksToWaitWriteable = x_Port_Is_Authorized_To_Access_बफर( pxTicksToWait,
                                                                       माप( TickType_t ),
                                                                       tskMPU_WRITE_PERMISSION );

            अगर( ( xIsTimeOutWriteable == pdTRUE ) && ( xIsTicksToWaitWriteable == pdTRUE ) )
            {
                xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
            }
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotify( TaskHandle_t xTaskToNotify,
                                           UBaseType_t ux_सूचकांक_To_Notify,
                                           uint32_t ul_मूल्य,
                                           eNotifyAction eAction,
                                           uint32_t * pul_Previous_Notification_मूल्य ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn = pdFAIL;
            xTaskGenericNotifyParams_t xParams;

            xParams.xTaskToNotify = xTaskToNotify;
            xParams.ux_सूचकांक_To_Notify = ux_सूचकांक_To_Notify;
            xParams.ul_मूल्य = ul_मूल्य;
            xParams.eAction = eAction;
            xParams.pul_Previous_Notification_मूल्य = pul_Previous_Notification_मूल्य;

            xReturn = MPU_xTaskGenericNotifyEntry( &( xParams ) );

            वापस xReturn;
        }

        BaseType_t MPU_xTaskGenericNotifyImpl( स्थिर xTaskGenericNotifyParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyImpl( स्थिर xTaskGenericNotifyParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;
            BaseType_t x_Is_Previous_Notification_मूल्य_Writeable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            अगर( pxParams != शून्य )
            {
                xAreParamsReadable = x_Port_Is_Authorized_To_Access_बफर( pxParams,
                                                                      माप( xTaskGenericNotifyParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            अगर( xAreParamsReadable == pdTRUE )
            {
                अगर( ( pxParams->ux_सूचकांक_To_Notify < configTASK_NOTIFICATION_ARRAY_ENTRIES ) &&
                    ( ( pxParams->eAction == eNoAction ) ||
                      ( pxParams->eAction == eSetBits ) ||
                      ( pxParams->eAction == eIncrement ) ||
                      ( pxParams->eAction == e_Set_मूल्य_With_Overwrite ) ||
                      ( pxParams->eAction == e_Set_मूल्य_Without_Overwrite ) ) )
                {
                    अगर( pxParams->pul_Previous_Notification_मूल्य != शून्य )
                    {
                        x_Is_Previous_Notification_मूल्य_Writeable = x_Port_Is_Authorized_To_Access_बफर( pxParams->pul_Previous_Notification_मूल्य,
                                                                                                 माप( uint32_t ),
                                                                                                 tskMPU_WRITE_PERMISSION );
                    }

                    अगर( ( pxParams->pul_Previous_Notification_मूल्य == शून्य ) ||
                        ( x_Is_Previous_Notification_मूल्य_Writeable == pdTRUE ) )
                    {
                        l_सूचकांक = ( int32_t ) ( pxParams->xTaskToNotify );

                        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                        {
                            xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                            अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                            {
                                xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                                अगर( xInternalTaskHandle != शून्य )
                                {
                                    xReturn = xTaskGenericNotify( xInternalTaskHandle,
                                                                  pxParams->ux_सूचकांक_To_Notify,
                                                                  pxParams->ul_मूल्य,
                                                                  pxParams->eAction,
                                                                  pxParams->pul_Previous_Notification_मूल्य );
                                }
                            }
                        }
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_सूचकांक_To_Wait_On,
                                               uint32_t ulBitsToClearOnEntry,
                                               uint32_t ulBitsToClearOnExit,
                                               uint32_t * pul_Notification_मूल्य,
                                               TickType_t xTicksToWait )
        {
            BaseType_t xReturn = pdFAIL;
            xTaskGenericNotifyWaitParams_t xParams;

            xParams.ux_सूचकांक_To_Wait_On = ux_सूचकांक_To_Wait_On;
            xParams.ulBitsToClearOnEntry = ulBitsToClearOnEntry;
            xParams.ulBitsToClearOnExit = ulBitsToClearOnExit;
            xParams.pul_Notification_मूल्य = pul_Notification_मूल्य;
            xParams.xTicksToWait = xTicksToWait;

            xReturn = MPU_xTaskGenericNotifyWaitEntry( &( xParams ) );

            वापस xReturn;
        }

        BaseType_t MPU_xTaskGenericNotifyWaitImpl( स्थिर xTaskGenericNotifyWaitParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyWaitImpl( स्थिर xTaskGenericNotifyWaitParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t x_Is_Notification_मूल्य_Writable = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            अगर( pxParams != शून्य )
            {
                xAreParamsReadable = x_Port_Is_Authorized_To_Access_बफर( pxParams,
                                                                      माप( xTaskGenericNotifyWaitParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            अगर( xAreParamsReadable == pdTRUE )
            {
                अगर( pxParams->ux_सूचकांक_To_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
                {
                    अगर( pxParams->pul_Notification_मूल्य != शून्य )
                    {
                        x_Is_Notification_मूल्य_Writable = x_Port_Is_Authorized_To_Access_बफर( pxParams->pul_Notification_मूल्य,
                                                                                        माप( uint32_t ),
                                                                                        tskMPU_WRITE_PERMISSION );
                    }

                    अगर( ( pxParams->pul_Notification_मूल्य == शून्य ) ||
                        ( x_Is_Notification_मूल्य_Writable == pdTRUE ) )
                    {
                        xReturn = xTaskGenericNotifyWait( pxParams->ux_सूचकांक_To_Wait_On,
                                                          pxParams->ulBitsToClearOnEntry,
                                                          pxParams->ulBitsToClearOnExit,
                                                          pxParams->pul_Notification_मूल्य,
                                                          pxParams->xTicksToWait );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_सूचकांक_To_Wait_On,
                                                  BaseType_t x_Clear_गिनती_On_Exit,
                                                  TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_सूचकांक_To_Wait_On,
                                                  BaseType_t x_Clear_गिनती_On_Exit,
                                                  TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;

            अगर( ux_सूचकांक_To_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ulReturn = ulTaskGenericNotifyTake( ux_सूचकांक_To_Wait_On, x_Clear_गिनती_On_Exit, xTicksToWait );
            }

            वापस ulReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_सूचकांक_To_Clear ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_सूचकांक_To_Clear ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            अगर( ux_सूचकांक_To_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                अगर( xTask == शून्य )
                {
                    xReturn = xTaskGenericNotifyStateClear( xTask, ux_सूचकांक_To_Clear );
                }
                अन्यथा
                {
                    l_सूचकांक = ( int32_t ) xTask;

                    अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                            अगर( xInternalTaskHandle != शून्य )
                            {
                                xReturn = xTaskGenericNotifyStateClear( xInternalTaskHandle, ux_सूचकांक_To_Clear );
                            }
                        }
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_मूल्य_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_सूचकांक_To_Clear,
                                                        uint32_t ulBitsToClear ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ul_Task_Generic_Notify_मूल्य_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_सूचकांक_To_Clear,
                                                        uint32_t ulBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            अगर( ux_सूचकांक_To_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                अगर( xTask == शून्य )
                {
                    ulReturn = ul_Task_Generic_Notify_मूल्य_Clear( xTask, ux_सूचकांक_To_Clear, ulBitsToClear );
                }
                अन्यथा
                {
                    l_सूचकांक = ( int32_t ) xTask;

                    अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                            अगर( xInternalTaskHandle != शून्य )
                            {
                                ulReturn = ul_Task_Generic_Notify_मूल्य_Clear( xInternalTaskHandle, ux_सूचकांक_To_Clear, ulBitsToClear );
                            }
                        }
                    }
                }
            }

            वापस ulReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Task APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #अगर ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreate( TaskFunction_t pvTaskCode,
                                    स्थिर अक्षर * स्थिर pcName,
                                    स्थिर config_ढेर_DEPTH_TYPE ux_ढेर_Depth,
                                    व्योम * pvParameters,
                                    UBaseType_t uxPriority,
                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                /* xTaskCreate() can only be used to create privileged tasks in MPU port. */
                अगर( ( uxPriority & portPRIVILEGE_BIT ) != 0 )
                {
                    xReturn = xTaskCreate( pvTaskCode, pcName, ux_ढेर_Depth, pvParameters, uxPriority, &( xInternalTaskHandle ) );

                    अगर( ( xReturn == pdPASS ) && ( xInternalTaskHandle != शून्य ) )
                    {
                        MPU_Store_Task_Handle_At_सूचकांक( l_सूचकांक, xInternalTaskHandle );

                        अगर( pxCreatedTask != शून्य )
                        {
                            *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                        }
                    }
                    अन्यथा
                    {
                        MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #अगर ( configSUPPORT_STATIC_ALLOCATION == 1 )

        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                            स्थिर अक्षर * स्थिर pcName,
                                            स्थिर config_ढेर_DEPTH_TYPE ux_ढेर_Depth,
                                            व्योम * स्थिर pvParameters,
                                            UBaseType_t uxPriority,
                                            ढेर_Type_t * स्थिर pux_ढेर_बफर,
                                            StaticTask_t * स्थिर px_Task_बफर ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xExternalTaskHandle = शून्य;
            TaskHandle_t xInternalTaskHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xInternalTaskHandle = xTaskCreateStatic( pxTaskCode, pcName, ux_ढेर_Depth, pvParameters, uxPriority, pux_ढेर_बफर, px_Task_बफर );

                अगर( xInternalTaskHandle != शून्य )
                {
                    MPU_Store_Task_Handle_At_सूचकांक( l_सूचकांक, xInternalTaskHandle );

                    #अगर ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        अगर( ( uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, l_सूचकांक );
                        }
                    }
                    #पूर्ण_अगर

                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xExternalTaskHandle;
        }

    #पूर्ण_अगर /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_vTaskDelete == 1 )

        व्योम MPU_vTaskDelete( TaskHandle_t pxTaskToDelete ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = शून्य;
            int32_t l_सूचकांक;

            अगर( pxTaskToDelete == शून्य )
            {
                xInternalTaskHandle = xTaskGetCurrentTaskHandle();
                l_सूचकांक = MPU_Get_सूचकांक_For_Task_Handle( xInternalTaskHandle );

                अगर( l_सूचकांक != -1 )
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }

                vTaskDelete( xInternalTaskHandle );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) pxTaskToDelete;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTaskHandle != शून्य )
                    {
                        MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );
                        vTaskDelete( xInternalTaskHandle );
                    }
                }
            }
        }

    #पूर्ण_अगर /* #if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/


    #अगर ( INCLUDE_vTaskPrioritySet == 1 )

        व्योम MPU_vTaskPrioritySet( TaskHandle_t pxTask,
                                   UBaseType_t uxNewPriority ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = शून्य;
            int32_t l_सूचकांक;

            अगर( pxTask == शून्य )
            {
                vTaskPrioritySet( pxTask, uxNewPriority );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) pxTask;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTaskHandle != शून्य )
                    {
                        vTaskPrioritySet( xInternalTaskHandle, uxNewPriority );
                    }
                }
            }
        }

    #पूर्ण_अगर /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_xTaskGetHandle == 1 )

        TaskHandle_t MPU_xTaskGetHandle( स्थिर अक्षर * pcNameToQuery ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = शून्य;
            TaskHandle_t xExternalTaskHandle = शून्य;
            int32_t l_सूचकांक;

            xInternalTaskHandle = xTaskGetHandle( pcNameToQuery );

            अगर( xInternalTaskHandle != शून्य )
            {
                l_सूचकांक = MPU_Get_सूचकांक_For_Task_Handle( xInternalTaskHandle );

                अगर( l_सूचकांक != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
            }

            वापस xExternalTaskHandle;
        }

    #पूर्ण_अगर /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/


    #अगर ( configUSE_APPLICATION_TASK_TAG == 1 )

        BaseType_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     व्योम * pvParameter ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;

            अगर( xTask == शून्य )
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTaskHandle != शून्य )
                    {
                        xReturn = xTaskCallApplicationTaskHook( xInternalTaskHandle, pvParameter );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreateRestricted( स्थिर TaskParameters_t * स्थिर pxTaskDefinition,
                                              TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xReturn = xTaskCreateRestricted( pxTaskDefinition, &( xInternalTaskHandle ) );

                अगर( ( xReturn == pdPASS ) && ( xInternalTaskHandle != शून्य ) )
                {
                    MPU_Store_Task_Handle_At_सूचकांक( l_सूचकांक, xInternalTaskHandle );

                    #अगर ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        अगर( ( pxTaskDefinition->uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, l_सूचकांक );
                        }
                    }
                    #पूर्ण_अगर

                    अगर( pxCreatedTask != शून्य )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                    }
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #अगर ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreateRestrictedStatic( स्थिर TaskParameters_t * स्थिर pxTaskDefinition,
                                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xReturn = xTaskCreateRestrictedStatic( pxTaskDefinition, &( xInternalTaskHandle ) );

                अगर( ( xReturn == pdPASS ) && ( xInternalTaskHandle != शून्य ) )
                {
                    MPU_Store_Task_Handle_At_सूचकांक( l_सूचकांक, xInternalTaskHandle );

                    #अगर ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        अगर( ( pxTaskDefinition->uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, l_सूचकांक );
                        }
                    }
                    #पूर्ण_अगर

                    अगर( pxCreatedTask != शून्य )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                    }
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    व्योम MPU_vTaskAllocateMPURegions( TaskHandle_t xTaskToModify,
                                      स्थिर MemoryRegion_t * स्थिर xRegions ) /* PRIVILEGED_FUNCTION */
    {
        TaskHandle_t xInternalTaskHandle = शून्य;
        int32_t l_सूचकांक;

        अगर( xTaskToModify == शून्य )
        {
            vTaskAllocateMPURegions( xTaskToModify, xRegions );
        }
        अन्यथा
        {
            l_सूचकांक = ( int32_t ) xTaskToModify;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalTaskHandle != शून्य )
                {
                    vTaskAllocateMPURegions( xInternalTaskHandle, xRegions );
                }
            }
        }
    }
/*-----------------------------------------------------------*/

    #अगर ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskGetStaticBuffers( TaskHandle_t xTask,
                                              ढेर_Type_t ** ppux_ढेर_बफर,
                                              StaticTask_t ** ppx_Task_बफर ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xReturn = pdFALSE;

            अगर( xTask == शून्य )
            {
                xInternalTaskHandle = xTaskGetCurrentTaskHandle();
                xReturn = xTaskGetStaticBuffers( xInternalTaskHandle, ppux_ढेर_बफर, ppx_Task_बफर );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTaskHandle != शून्य )
                    {
                        xReturn = xTaskGetStaticBuffers( xInternalTaskHandle, ppux_ढेर_बफर, ppx_Task_बफर );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    अक्षर * MPU_pcTaskGetName( TaskHandle_t xTaskToQuery ) /* PRIVILEGED_FUNCTION */
    {
        अक्षर * pcReturn = शून्य;
        int32_t l_सूचकांक;
        TaskHandle_t xInternalTaskHandle = शून्य;

        अगर( xTaskToQuery == शून्य )
        {
            pcReturn = pcTaskGetName( xTaskToQuery );
        }
        अन्यथा
        {
            l_सूचकांक = ( int32_t ) xTaskToQuery;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalTaskHandle != शून्य )
                {
                    pcReturn = pcTaskGetName( xInternalTaskHandle );
                }
            }
        }

        वापस pcReturn;
    }
/*-----------------------------------------------------------*/

    #अगर ( INCLUDE_uxTaskPriorityGet == 1 )

        UBaseType_t MPU_uxTaskPriorityGetFromISR( स्थिर TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;

            अगर( xTask == शून्य )
            {
                uxReturn = uxTaskPriorityGetFromISR( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTaskHandle != शून्य )
                    {
                        uxReturn = uxTaskPriorityGetFromISR( xInternalTaskHandle );
                    }
                }
            }

            वापस uxReturn;
        }

    #पूर्ण_अगर /* #if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_uxTaskBasePriorityGet( स्थिर TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;

            अगर( xTask == शून्य )
            {
                uxReturn = uxTaskBasePriorityGet( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTaskHandle != शून्य )
                    {
                        uxReturn = uxTaskBasePriorityGet( xInternalTaskHandle );
                    }
                }
            }

            वापस uxReturn;
        }

    #पूर्ण_अगर /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_uxTaskBasePriorityGetFromISR( स्थिर TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;

            अगर( xTask == शून्य )
            {
                uxReturn = uxTaskBasePriorityGetFromISR( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTaskHandle != शून्य )
                    {
                        uxReturn = uxTaskBasePriorityGetFromISR( xInternalTaskHandle );
                    }
                }
            }

            वापस uxReturn;
        }

    #पूर्ण_अगर /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

        BaseType_t MPU_xTaskResumeFromISR( TaskHandle_t xTaskToResume ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;

            l_सूचकांक = ( int32_t ) xTaskToResume;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalTaskHandle != शून्य )
                {
                    xReturn = xTaskResumeFromISR( xInternalTaskHandle );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )*/
/*---------------------------------------------------------------------------------------*/

    #अगर ( configUSE_APPLICATION_TASK_TAG == 1 )

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagFromISR( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = शून्य;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;

            अगर( xTask == शून्य )
            {
                xReturn = xTaskGetApplicationTaskTagFromISR( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTaskHandle != शून्य )
                    {
                        xReturn = xTaskGetApplicationTaskTagFromISR( xInternalTaskHandle );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyFromISR( TaskHandle_t xTaskToNotify,
                                                  UBaseType_t ux_सूचकांक_To_Notify,
                                                  uint32_t ul_मूल्य,
                                                  eNotifyAction eAction,
                                                  uint32_t * pul_Previous_Notification_मूल्य,
                                                  BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;

            l_सूचकांक = ( int32_t ) xTaskToNotify;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalTaskHandle != शून्य )
                {
                    xReturn = xTaskGenericNotifyFromISR( xInternalTaskHandle, ux_सूचकांक_To_Notify, ul_मूल्य, eAction, pul_Previous_Notification_मूल्य, pxHigherPriorityTaskWoken );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )

        व्योम MPU_vTaskGenericNotifyGiveFromISR( TaskHandle_t xTaskToNotify,
                                                UBaseType_t ux_सूचकांक_To_Notify,
                                                BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            TaskHandle_t xInternalTaskHandle = शून्य;

            l_सूचकांक = ( int32_t ) xTaskToNotify;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalTaskHandle != शून्य )
                {
                    vTaskGenericNotifyGiveFromISR( xInternalTaskHandle, ux_सूचकांक_To_Notify, pxHigherPriorityTaskWoken );
                }
            }
        }
    #पूर्ण_अगर /*#if ( configUSE_TASK_NOTIFICATIONS == 1 )*/
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for queue APIs.                   */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSendImpl( QueueHandle_t xQueue,
                                          स्थिर व्योम * स्थिर pvItemToQueue,
                                          TickType_t xTicksToWait,
                                          BaseType_t xCopyPosition ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueGenericSendImpl( QueueHandle_t xQueue,
                                          स्थिर व्योम * स्थिर pvItemToQueue,
                                          TickType_t xTicksToWait,
                                          BaseType_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_सूचकांक;
        QueueHandle_t xInternalQueueHandle = शून्य;
        BaseType_t xReturn = pdFAIL;
        BaseType_t xIsItemToQueueReadable = pdFALSE;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
        UBaseType_t ux_Queue_Item_आकार, ux_Queue_लंबाई;

        l_सूचकांक = ( int32_t ) xQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalQueueHandle != शून्य )
                {
                    ux_Queue_Item_आकार = ux_Queue_Get_Queue_Item_आकार( xInternalQueueHandle );
                    ux_Queue_लंबाई = ux_Queue_Get_Queue_लंबाई( xInternalQueueHandle );

                    अगर( ( !( ( pvItemToQueue == शून्य ) && ( ux_Queue_Item_आकार != ( UBaseType_t ) 0U ) ) ) &&
                        ( !( ( xCopyPosition == queueOVERWRITE ) && ( ux_Queue_लंबाई != ( UBaseType_t ) 1U ) ) )
                        #अगर ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #पूर्ण_अगर
                        )
                    {
                        अगर( pvItemToQueue != शून्य )
                        {
                            xIsItemToQueueReadable = x_Port_Is_Authorized_To_Access_बफर( pvItemToQueue,
                                                                                      ux_Queue_Item_आकार,
                                                                                      tskMPU_READ_PERMISSION );
                        }

                        अगर( ( pvItemToQueue == शून्य ) || ( xIsItemToQueueReadable == pdTRUE ) )
                        {
                            xReturn = xQueueGenericSend( xInternalQueueHandle, pvItemToQueue, xTicksToWait, xCopyPosition );
                        }
                    }
                }
            }
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaitingImpl( स्थिर QueueHandle_t pxQueue ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_uxQueueMessagesWaitingImpl( स्थिर QueueHandle_t pxQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_सूचकांक;
        QueueHandle_t xInternalQueueHandle = शून्य;
        UBaseType_t uxReturn = 0;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        l_सूचकांक = ( int32_t ) pxQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalQueueHandle != शून्य )
                {
                    uxReturn = uxQueueMessagesWaiting( xInternalQueueHandle );
                }
            }
        }

        वापस uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueSpacesAvailableImpl( स्थिर QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_uxQueueSpacesAvailableImpl( स्थिर QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_सूचकांक;
        QueueHandle_t xInternalQueueHandle = शून्य;
        UBaseType_t uxReturn = 0;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        l_सूचकांक = ( int32_t ) xQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalQueueHandle != शून्य )
                {
                    uxReturn = uxQueueSpacesAvailable( xInternalQueueHandle );
                }
            }
        }

        वापस uxReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceiveImpl( QueueHandle_t pxQueue,
                                      व्योम * स्थिर pv_बफर,
                                      TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueReceiveImpl( QueueHandle_t pxQueue,
                                      व्योम * स्थिर pv_बफर,
                                      TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_सूचकांक;
        QueueHandle_t xInternalQueueHandle = शून्य;
        BaseType_t xReturn = pdFAIL;
        BaseType_t x_Is_Receive_बफर_Writable = pdFALSE;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
        UBaseType_t ux_Queue_Item_आकार;

        l_सूचकांक = ( int32_t ) pxQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalQueueHandle != शून्य )
                {
                    ux_Queue_Item_आकार = ux_Queue_Get_Queue_Item_आकार( xInternalQueueHandle );

                    अगर( ( !( ( ( pv_बफर ) == शून्य ) && ( ux_Queue_Item_आकार != ( UBaseType_t ) 0U ) ) )
                        #अगर ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #पूर्ण_अगर
                        )
                    {
                        x_Is_Receive_बफर_Writable = x_Port_Is_Authorized_To_Access_बफर( pv_बफर,
                                                                                    ux_Queue_Item_आकार,
                                                                                    tskMPU_WRITE_PERMISSION );

                        अगर( x_Is_Receive_बफर_Writable == pdTRUE )
                        {
                            xReturn = xQueueReceive( xInternalQueueHandle, pv_बफर, xTicksToWait );
                        }
                    }
                }
            }
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeekImpl( QueueHandle_t xQueue,
                                   व्योम * स्थिर pv_बफर,
                                   TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueuePeekImpl( QueueHandle_t xQueue,
                                   व्योम * स्थिर pv_बफर,
                                   TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_सूचकांक;
        QueueHandle_t xInternalQueueHandle = शून्य;
        BaseType_t xReturn = pdFAIL;
        BaseType_t x_Is_Receive_बफर_Writable = pdFALSE;
        UBaseType_t ux_Queue_Item_आकार;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        l_सूचकांक = ( int32_t ) xQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalQueueHandle != शून्य )
                {
                    ux_Queue_Item_आकार = ux_Queue_Get_Queue_Item_आकार( xInternalQueueHandle );

                    अगर( ( !( ( ( pv_बफर ) == शून्य ) && ( ux_Queue_Item_आकार != ( UBaseType_t ) 0U ) ) )
                        #अगर ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #पूर्ण_अगर
                        )
                    {
                        x_Is_Receive_बफर_Writable = x_Port_Is_Authorized_To_Access_बफर( pv_बफर,
                                                                                    ux_Queue_Item_आकार,
                                                                                    tskMPU_WRITE_PERMISSION );

                        अगर( x_Is_Receive_बफर_Writable == pdTRUE )
                        {
                            xReturn = xQueuePeek( xInternalQueueHandle, pv_बफर, xTicksToWait );
                        }
                    }
                }
            }
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueSemaphoreTakeImpl( QueueHandle_t xQueue,
                                            TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueSemaphoreTakeImpl( QueueHandle_t xQueue,
                                            TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_सूचकांक;
        QueueHandle_t xInternalQueueHandle = शून्य;
        BaseType_t xReturn = pdFAIL;
        UBaseType_t ux_Queue_Item_आकार;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        l_सूचकांक = ( int32_t ) xQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalQueueHandle != शून्य )
                {
                    ux_Queue_Item_आकार = ux_Queue_Get_Queue_Item_आकार( xInternalQueueHandle );

                    अगर( ( ux_Queue_Item_आकार == 0U )
                        #अगर ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #पूर्ण_अगर
                        )
                    {
                        xReturn = xQueueSemaphoreTake( xInternalQueueHandle, xTicksToWait );
                    }
                }
            }
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolderImpl( QueueHandle_t xSemaphore ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xQueueGetMutexHolderImpl( QueueHandle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xMutexHolderTaskInternalHandle = शून्य;
            TaskHandle_t xMutexHolderTaskExternalHandle = शून्य;
            int32_t l_सूचकांक, l_Mutex_Holder_Task_सूचकांक;
            QueueHandle_t xInternalQueueHandle = शून्य;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;


            l_सूचकांक = ( int32_t ) xSemaphore;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalQueueHandle != शून्य )
                    {
                        xMutexHolderTaskInternalHandle = xQueueGetMutexHolder( xInternalQueueHandle );

                        अगर( xMutexHolderTaskInternalHandle != शून्य )
                        {
                            l_Mutex_Holder_Task_सूचकांक = MPU_Get_सूचकांक_For_Task_Handle( xMutexHolderTaskInternalHandle );

                            अगर( l_Mutex_Holder_Task_सूचकांक != -1 )
                            {
                                xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_TO_EXTERNAL_सूचकांक( l_Mutex_Holder_Task_सूचकांक ) );
                            }
                        }
                    }
                }
            }

            वापस xMutexHolderTaskExternalHandle;
        }

    #पूर्ण_अगर /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueTakeMutexRecursiveImpl( QueueHandle_t xMutex,
                                                     TickType_t xBlockTime ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueTakeMutexRecursiveImpl( QueueHandle_t xMutex,
                                                     TickType_t xBlockTime ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
            int32_t l_सूचकांक;
            QueueHandle_t xInternalQueueHandle = शून्य;
            UBaseType_t ux_Queue_Item_आकार;

            l_सूचकांक = ( int32_t ) xMutex;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalQueueHandle != शून्य )
                    {
                        ux_Queue_Item_आकार = ux_Queue_Get_Queue_Item_आकार( xInternalQueueHandle );

                        अगर( ux_Queue_Item_आकार == 0 )
                        {
                            xReturn = xQueueTakeMutexRecursive( xInternalQueueHandle, xBlockTime );
                        }
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueGiveMutexRecursiveImpl( QueueHandle_t xMutex ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueGiveMutexRecursiveImpl( QueueHandle_t xMutex ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
            int32_t l_सूचकांक;
            QueueHandle_t xInternalQueueHandle = शून्य;

            l_सूचकांक = ( int32_t ) xMutex;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalQueueHandle != शून्य )
                    {
                        xReturn = xQueueGiveMutexRecursive( xInternalQueueHandle );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_QUEUE_SETS == 1 )

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetImpl( QueueSetHandle_t xQueueSet,
                                                            TickType_t xBlockTimeTicks ) PRIVILEGED_FUNCTION;

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetImpl( QueueSetHandle_t xQueueSet,
                                                            TickType_t xBlockTimeTicks ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = शून्य;
            QueueSetMemberHandle_t xSelectedMemberInternal = शून्य;
            QueueSetMemberHandle_t xSelectedMemberExternal = शून्य;
            int32_t l_सूचकांक_Queue_Set, l_सूचकांक_Selected_Member;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSet = pdFALSE;

            l_सूचकांक_Queue_Set = ( int32_t ) xQueueSet;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक_Queue_Set ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueueSet = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक_Queue_Set ) );

                अगर( xCallingTaskIsAuthorizedToAccessQueueSet == pdTRUE )
                {
                    xInternalQueueSetHandle = MPU_Get_Queue_Set_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक_Queue_Set ) );

                    अगर( xInternalQueueSetHandle != शून्य )
                    {
                        xSelectedMemberInternal = xQueueSelectFromSet( xInternalQueueSetHandle, xBlockTimeTicks );

                        अगर( xSelectedMemberInternal != शून्य )
                        {
                            l_सूचकांक_Selected_Member = MPU_Get_सूचकांक_For_Queue_Set_Member_Handle( xSelectedMemberInternal );

                            अगर( l_सूचकांक_Selected_Member != -1 )
                            {
                                xSelectedMemberExternal = ( QueueSetMemberHandle_t ) ( CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक_Selected_Member ) );
                            }
                        }
                    }
                }
            }

            वापस xSelectedMemberExternal;
        }

    #पूर्ण_अगर /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_QUEUE_SETS == 1 )

        BaseType_t MPU_xQueueAddToSetImpl( QueueSetMemberHandle_t xQueueOrSemaphore,
                                           QueueSetHandle_t xQueueSet ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueAddToSetImpl( QueueSetMemberHandle_t xQueueOrSemaphore,
                                           QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            QueueSetMemberHandle_t xInternalQueueSetMemberHandle = शून्य;
            QueueSetHandle_t xInternalQueueSetHandle = शून्य;
            int32_t l_सूचकांक_Queue_Set, l_सूचकांक_Queue_Set_Member;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSet = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSetMember = pdFALSE;

            l_सूचकांक_Queue_Set = ( int32_t ) xQueueSet;
            l_सूचकांक_Queue_Set_Member = ( int32_t ) xQueueOrSemaphore;

            अगर( ( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक_Queue_Set ) != pdFALSE ) &&
                ( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक_Queue_Set_Member ) != pdFALSE ) )
            {
                xCallingTaskIsAuthorizedToAccessQueueSet = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक_Queue_Set ) );
                xCallingTaskIsAuthorizedToAccessQueueSetMember = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक_Queue_Set_Member ) );

                अगर( ( xCallingTaskIsAuthorizedToAccessQueueSet == pdTRUE ) && ( xCallingTaskIsAuthorizedToAccessQueueSetMember == pdTRUE ) )
                {
                    xInternalQueueSetHandle = MPU_Get_Queue_Set_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक_Queue_Set ) );
                    xInternalQueueSetMemberHandle = MPU_Get_Queue_Set_Member_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक_Queue_Set_Member ) );

                    अगर( ( xInternalQueueSetHandle != शून्य ) && ( xInternalQueueSetMemberHandle != शून्य ) )
                    {
                        xReturn = xQueueAddToSet( xInternalQueueSetMemberHandle, xInternalQueueSetHandle );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर config_QUEUE_REGISTRY_आकार > 0

        व्योम MPU_vQueueAddToRegistryImpl( QueueHandle_t xQueue,
                                          स्थिर अक्षर * pcName ) PRIVILEGED_FUNCTION;

        व्योम MPU_vQueueAddToRegistryImpl( QueueHandle_t xQueue,
                                          स्थिर अक्षर * pcName ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            QueueHandle_t xInternalQueueHandle = शून्य;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            l_सूचकांक = ( int32_t ) xQueue;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalQueueHandle != शून्य )
                    {
                        vQueueAddToRegistry( xInternalQueueHandle, pcName );
                    }
                }
            }
        }

    #पूर्ण_अगर /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #अगर config_QUEUE_REGISTRY_आकार > 0

        व्योम MPU_vQueueUnregisterQueueImpl( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

        व्योम MPU_vQueueUnregisterQueueImpl( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            QueueHandle_t xInternalQueueHandle = शून्य;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            l_सूचकांक = ( int32_t ) xQueue;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalQueueHandle != शून्य )
                    {
                        vQueueUnregisterQueue( xInternalQueueHandle );
                    }
                }
            }
        }

    #पूर्ण_अगर /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #अगर config_QUEUE_REGISTRY_आकार > 0

        स्थिर अक्षर * MPU_pcQueueGetNameImpl( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

        स्थिर अक्षर * MPU_pcQueueGetNameImpl( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
        {
            स्थिर अक्षर * pcReturn = शून्य;
            QueueHandle_t xInternalQueueHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            l_सूचकांक = ( int32_t ) xQueue;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalQueueHandle != शून्य )
                    {
                        pcReturn = pcQueueGetName( xInternalQueueHandle );
                    }
                }
            }

            वापस pcReturn;
        }

    #पूर्ण_अगर /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Queue APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    व्योम MPU_vQueueDelete( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        QueueHandle_t xInternalQueueHandle = शून्य;
        int32_t l_सूचकांक;

        l_सूचकांक = ( int32_t ) xQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xInternalQueueHandle != शून्य )
            {
                vQueueDelete( xInternalQueueHandle );
                MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );
            }
        }
    }
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateMutex( स्थिर uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = शून्य;
            QueueHandle_t xExternalQueueHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xInternalQueueHandle = xQueueCreateMutex( ucQueueType );

                अगर( xInternalQueueHandle != शून्य )
                {
                    MPU_Store_Queue_Handle_At_सूचकांक( l_सूचकांक, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xExternalQueueHandle;
        }

    #पूर्ण_अगर /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateMutexStatic( स्थिर uint8_t ucQueueType,
                                                   StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = शून्य;
            QueueHandle_t xExternalQueueHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xInternalQueueHandle = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );

                अगर( xInternalQueueHandle != शून्य )
                {
                    MPU_Store_Queue_Handle_At_सूचकांक( l_सूचकांक, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xExternalQueueHandle;
        }

    #पूर्ण_अगर /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphore( UBaseType_t ux_गिनती_मूल्य,
                                                         UBaseType_t ux_Initial_गिनती ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = शून्य;
            QueueHandle_t xExternalQueueHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xInternalQueueHandle = xQueueCreateCountingSemaphore( ux_गिनती_मूल्य, ux_Initial_गिनती );

                अगर( xInternalQueueHandle != शून्य )
                {
                    MPU_Store_Queue_Handle_At_सूचकांक( l_सूचकांक, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xExternalQueueHandle;
        }

    #पूर्ण_अगर /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphoreStatic( स्थिर UBaseType_t ux_Max_गिनती,
                                                               स्थिर UBaseType_t ux_Initial_गिनती,
                                                               StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = शून्य;
            QueueHandle_t xExternalQueueHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xInternalQueueHandle = xQueueCreateCountingSemaphoreStatic( ux_Max_गिनती, ux_Initial_गिनती, pxStaticQueue );

                अगर( xInternalQueueHandle != शून्य )
                {
                    MPU_Store_Queue_Handle_At_सूचकांक( l_सूचकांक, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xExternalQueueHandle;
        }

    #पूर्ण_अगर /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        QueueHandle_t MPU_xQueueGenericCreate( UBaseType_t ux_Queue_लंबाई,
                                               UBaseType_t ux_Item_आकार,
                                               uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = शून्य;
            QueueHandle_t xExternalQueueHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xInternalQueueHandle = xQueueGenericCreate( ux_Queue_लंबाई, ux_Item_आकार, ucQueueType );

                अगर( xInternalQueueHandle != शून्य )
                {
                    MPU_Store_Queue_Handle_At_सूचकांक( l_सूचकांक, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xExternalQueueHandle;
        }

    #पूर्ण_अगर /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configSUPPORT_STATIC_ALLOCATION == 1 )

        QueueHandle_t MPU_xQueueGenericCreateStatic( स्थिर UBaseType_t ux_Queue_लंबाई,
                                                     स्थिर UBaseType_t ux_Item_आकार,
                                                     uint8_t * pucQueueStorage,
                                                     StaticQueue_t * pxStaticQueue,
                                                     स्थिर uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = शून्य;
            QueueHandle_t xExternalQueueHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xInternalQueueHandle = xQueueGenericCreateStatic( ux_Queue_लंबाई, ux_Item_आकार, pucQueueStorage, pxStaticQueue, ucQueueType );

                अगर( xInternalQueueHandle != शून्य )
                {
                    MPU_Store_Queue_Handle_At_सूचकांक( l_सूचकांक, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xExternalQueueHandle;
        }

    #पूर्ण_अगर /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericReset( QueueHandle_t xQueue,
                                       BaseType_t xNewQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_सूचकांक;
        QueueHandle_t xInternalQueueHandle = शून्य;
        BaseType_t xReturn = pdFAIL;

        l_सूचकांक = ( int32_t ) xQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xInternalQueueHandle != शून्य )
            {
                xReturn = xQueueGenericReset( xInternalQueueHandle, xNewQueue );
            }
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueSetHandle_t MPU_xQueueCreateSet( UBaseType_t ux_Event_Queue_लंबाई ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = शून्य;
            QueueSetHandle_t xExternalQueueSetHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xInternalQueueSetHandle = xQueueCreateSet( ux_Event_Queue_लंबाई );

                अगर( xInternalQueueSetHandle != शून्य )
                {
                    MPU_Store_Queue_Set_Handle_At_सूचकांक( l_सूचकांक, xInternalQueueSetHandle );
                    xExternalQueueSetHandle = ( QueueSetHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xExternalQueueSetHandle;
        }

    #पूर्ण_अगर /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueSetHandle_t MPU_xQueueCreateSetStatic( स्थिर UBaseType_t ux_Event_Queue_लंबाई,
                                                    uint8_t * pucQueueStorage,
                                                    StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = शून्य;
            QueueSetHandle_t xExternalQueueSetHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xInternalQueueSetHandle = xQueueCreateSetStatic( ux_Event_Queue_लंबाई, pucQueueStorage, pxStaticQueue );

                अगर( xInternalQueueSetHandle != शून्य )
                {
                    MPU_Store_Queue_Set_Handle_At_सूचकांक( l_सूचकांक, xInternalQueueSetHandle );
                    xExternalQueueSetHandle = ( QueueSetHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xExternalQueueSetHandle;
        }

    #पूर्ण_अगर /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_QUEUE_SETS == 1 )

        BaseType_t MPU_xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                            QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            QueueSetMemberHandle_t xInternalQueueSetMemberHandle = शून्य;
            QueueSetHandle_t xInternalQueueSetHandle = शून्य;
            int32_t l_सूचकांक_Queue_Set, l_सूचकांक_Queue_Set_Member;

            l_सूचकांक_Queue_Set = ( int32_t ) xQueueSet;
            l_सूचकांक_Queue_Set_Member = ( int32_t ) xQueueOrSemaphore;

            अगर( ( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक_Queue_Set ) != pdFALSE ) &&
                ( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक_Queue_Set_Member ) != pdFALSE ) )
            {
                xInternalQueueSetHandle = MPU_Get_Queue_Set_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक_Queue_Set ) );
                xInternalQueueSetMemberHandle = MPU_Get_Queue_Set_Member_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक_Queue_Set_Member ) );

                अगर( ( xInternalQueueSetHandle != शून्य ) && ( xInternalQueueSetMemberHandle != शून्य ) )
                {
                    xReturn = xQueueRemoveFromSet( xInternalQueueSetMemberHandle, xInternalQueueSetHandle );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xQueueGenericGetStaticBuffers( QueueHandle_t xQueue,
                                                      uint8_t ** ppucQueueStorage,
                                                      StaticQueue_t ** ppxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            QueueHandle_t xInternalQueueHandle = शून्य;
            BaseType_t xReturn = pdFALSE;

            l_सूचकांक = ( int32_t ) xQueue;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalQueueHandle != शून्य )
                {
                    xReturn = xQueueGenericGetStaticBuffers( xInternalQueueHandle, ppucQueueStorage, ppxStaticQueue );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /*if ( configSUPPORT_STATIC_ALLOCATION == 1 )*/
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSendFromISR( QueueHandle_t xQueue,
                                             स्थिर व्योम * स्थिर pvItemToQueue,
                                             BaseType_t * स्थिर pxHigherPriorityTaskWoken,
                                             स्थिर BaseType_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t l_सूचकांक;
        QueueHandle_t xInternalQueueHandle = शून्य;

        l_सूचकांक = ( int32_t ) xQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xInternalQueueHandle != शून्य )
            {
                xReturn = xQueueGenericSendFromISR( xInternalQueueHandle, pvItemToQueue, pxHigherPriorityTaskWoken, xCopyPosition );
            }
        }

        वापस xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGiveFromISR( QueueHandle_t xQueue,
                                      BaseType_t * स्थिर pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t l_सूचकांक;
        QueueHandle_t xInternalQueueHandle = शून्य;

        l_सूचकांक = ( int32_t ) xQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xInternalQueueHandle != शून्य )
            {
                xReturn = xQueueGiveFromISR( xInternalQueueHandle, pxHigherPriorityTaskWoken );
            }
        }

        वापस xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeekFromISR( QueueHandle_t xQueue,
                                      व्योम * स्थिर pv_बफर ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t l_सूचकांक;
        QueueHandle_t xInternalQueueHandle = शून्य;

        l_सूचकांक = ( int32_t ) xQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xInternalQueueHandle != शून्य )
            {
                xReturn = xQueuePeekFromISR( xInternalQueueHandle, pv_बफर );
            }
        }

        वापस xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceiveFromISR( QueueHandle_t xQueue,
                                         व्योम * स्थिर pv_बफर,
                                         BaseType_t * स्थिर pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t l_सूचकांक;
        QueueHandle_t xInternalQueueHandle = शून्य;

        l_सूचकांक = ( int32_t ) xQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xInternalQueueHandle != शून्य )
            {
                xReturn = xQueueReceiveFromISR( xInternalQueueHandle, pv_बफर, pxHigherPriorityTaskWoken );
            }
        }

        वापस xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueIsQueueEmptyFromISR( स्थिर QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t l_सूचकांक;
        QueueHandle_t xInternalQueueHandle = शून्य;

        l_सूचकांक = ( int32_t ) xQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xInternalQueueHandle != शून्य )
            {
                xReturn = xQueueIsQueueEmptyFromISR( xInternalQueueHandle );
            }
        }

        वापस xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueIsQueueFullFromISR( स्थिर QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t l_सूचकांक;
        QueueHandle_t xInternalQueueHandle = शून्य;

        l_सूचकांक = ( int32_t ) xQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xInternalQueueHandle != शून्य )
            {
                xReturn = xQueueIsQueueFullFromISR( xInternalQueueHandle );
            }
        }

        वापस xReturn;
    }

/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaitingFromISR( स्थिर QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn = 0;
        int32_t l_सूचकांक;
        QueueHandle_t xInternalQueueHandle = शून्य;

        l_सूचकांक = ( int32_t ) xQueue;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( xInternalQueueHandle != शून्य )
            {
                uxReturn = uxQueueMessagesWaitingFromISR( xInternalQueueHandle );
            }
        }

        वापस uxReturn;
    }

/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolderFromISR( QueueHandle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xMutexHolderTaskInternalHandle = शून्य;
            TaskHandle_t xMutexHolderTaskExternalHandle = शून्य;
            int32_t l_सूचकांक, l_Mutex_Holder_Task_सूचकांक;
            QueueHandle_t xInternalSemaphoreHandle = शून्य;

            l_सूचकांक = ( int32_t ) xSemaphore;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalSemaphoreHandle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalSemaphoreHandle != शून्य )
                {
                    xMutexHolderTaskInternalHandle = xQueueGetMutexHolder( xInternalSemaphoreHandle );

                    अगर( xMutexHolderTaskInternalHandle != शून्य )
                    {
                        l_Mutex_Holder_Task_सूचकांक = MPU_Get_सूचकांक_For_Task_Handle( xMutexHolderTaskInternalHandle );

                        अगर( l_Mutex_Holder_Task_सूचकांक != -1 )
                        {
                            xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_TO_EXTERNAL_सूचकांक( l_Mutex_Holder_Task_सूचकांक ) );
                        }
                    }
                }
            }

            वापस xMutexHolderTaskExternalHandle;
        }

    #पूर्ण_अगर /* #if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_QUEUE_SETS == 1 )

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetFromISR( QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = शून्य;
            QueueSetMemberHandle_t xSelectedMemberInternal = शून्य;
            QueueSetMemberHandle_t xSelectedMemberExternal = शून्य;
            int32_t l_सूचकांक_Queue_Set, l_सूचकांक_Selected_Member;

            l_सूचकांक_Queue_Set = ( int32_t ) xQueueSet;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक_Queue_Set ) != pdFALSE )
            {
                xInternalQueueSetHandle = MPU_Get_Queue_Set_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक_Queue_Set ) );

                अगर( xInternalQueueSetHandle != शून्य )
                {
                    xSelectedMemberInternal = xQueueSelectFromSetFromISR( xInternalQueueSetHandle );

                    अगर( xSelectedMemberInternal != शून्य )
                    {
                        l_सूचकांक_Selected_Member = MPU_Get_सूचकांक_For_Queue_Set_Member_Handle( xSelectedMemberInternal );

                        अगर( l_सूचकांक_Selected_Member != -1 )
                        {
                            xSelectedMemberExternal = ( QueueSetMemberHandle_t ) ( CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक_Selected_Member ) );
                        }
                    }
                }
            }

            वापस xSelectedMemberExternal;
        }

    #पूर्ण_अगर /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for timers APIs.                  */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )

        व्योम * MPU_pvTimerGetTimerIDImpl( स्थिर TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        व्योम * MPU_pvTimerGetTimerIDImpl( स्थिर TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            व्योम * pvReturn = शून्य;
            TimerHandle_t xInternalTimerHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTimerHandle != शून्य )
                    {
                        pvReturn = pvTimerGetTimerID( xInternalTimerHandle );
                    }
                }
            }

            वापस pvReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )

        व्योम MPU_vTimerSetTimerIDImpl( TimerHandle_t xTimer,
                                       व्योम * pvNewID ) PRIVILEGED_FUNCTION;

        व्योम MPU_vTimerSetTimerIDImpl( TimerHandle_t xTimer,
                                       व्योम * pvNewID ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTimerHandle != शून्य )
                    {
                        vTimerSetTimerID( xInternalTimerHandle, pvNewID );
                    }
                }
            }
        }

    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerIsTimerActiveImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerIsTimerActiveImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTimerHandle != शून्य )
                    {
                        xReturn = xTimerIsTimerActive( xInternalTimerHandle );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( व्योम ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( व्योम ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xReturn;

            xReturn = xTimerGetTimerDaemonTaskHandle();

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     स्थिर BaseType_t xCommandID,
                                                     स्थिर TickType_t x_Optional_मूल्य,
                                                     BaseType_t * स्थिर pxHigherPriorityTaskWoken,
                                                     स्थिर TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn = pdFALSE;
            xTimerGenericCommandFromTaskParams_t xParams;

            xParams.xTimer = xTimer;
            xParams.xCommandID = xCommandID;
            xParams.x_Optional_मूल्य = x_Optional_मूल्य;
            xParams.pxHigherPriorityTaskWoken = pxHigherPriorityTaskWoken;
            xParams.xTicksToWait = xTicksToWait;

            xReturn = MPU_xTimerGenericCommandFromTaskEntry( &( xParams ) );

            वापस xReturn;
        }

        BaseType_t MPU_xTimerGenericCommandFromTaskImpl( स्थिर xTimerGenericCommandFromTaskParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerGenericCommandFromTaskImpl( स्थिर xTimerGenericCommandFromTaskParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xIsHigherPriorityTaskWokenWriteable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            अगर( pxParams != शून्य )
            {
                xAreParamsReadable = x_Port_Is_Authorized_To_Access_बफर( pxParams,
                                                                      माप( xTimerGenericCommandFromTaskParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            अगर( xAreParamsReadable == pdTRUE )
            {
                अगर( pxParams->xCommandID < tmrFIRST_FROM_ISR_COMMAND )
                {
                    अगर( pxParams->pxHigherPriorityTaskWoken != शून्य )
                    {
                        xIsHigherPriorityTaskWokenWriteable = x_Port_Is_Authorized_To_Access_बफर( pxParams->pxHigherPriorityTaskWoken,
                                                                                               माप( BaseType_t ),
                                                                                               tskMPU_WRITE_PERMISSION );
                    }

                    अगर( ( pxParams->pxHigherPriorityTaskWoken == शून्य ) ||
                        ( xIsHigherPriorityTaskWokenWriteable == pdTRUE ) )
                    {
                        l_सूचकांक = ( int32_t ) ( pxParams->xTimer );

                        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                        {
                            xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                            अगर( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                            {
                                xInternalTimerHandle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                                अगर( xInternalTimerHandle != शून्य )
                                {
                                    xReturn = xTimerGenericCommandFromTask( xInternalTimerHandle,
                                                                            pxParams->xCommandID,
                                                                            pxParams->x_Optional_मूल्य,
                                                                            pxParams->pxHigherPriorityTaskWoken,
                                                                            pxParams->xTicksToWait );
                                }
                            }
                        }
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )

        स्थिर अक्षर * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        स्थिर अक्षर * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            स्थिर अक्षर * pcReturn = शून्य;
            TimerHandle_t xInternalTimerHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTimerHandle != शून्य )
                    {
                        pcReturn = pcTimerGetName( xInternalTimerHandle );
                    }
                }
            }

            वापस pcReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )

        व्योम MPU_vTimerSetReloadModeImpl( TimerHandle_t xTimer,
                                          स्थिर BaseType_t xAutoReload ) PRIVILEGED_FUNCTION;

        व्योम MPU_vTimerSetReloadModeImpl( TimerHandle_t xTimer,
                                          स्थिर BaseType_t xAutoReload ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTimerHandle != शून्य )
                    {
                        vTimerSetReloadMode( xInternalTimerHandle, xAutoReload );
                    }
                }
            }
        }

    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGetReloadModeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerGetReloadModeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTimerHandle != शून्य )
                    {
                        xReturn = xTimerGetReloadMode( xInternalTimerHandle );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_uxTimerGetReloadModeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTimerGetReloadModeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            TimerHandle_t xInternalTimerHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTimerHandle != शून्य )
                    {
                        uxReturn = uxTimerGetReloadMode( xInternalTimerHandle );
                    }
                }
            }

            वापस uxReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t xInternalTimerHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTimerHandle != शून्य )
                    {
                        xReturn = xTimerGetPeriod( xInternalTimerHandle );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetExpiryTimeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetExpiryTimeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t xInternalTimerHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalTimerHandle != शून्य )
                    {
                        xReturn = xTimerGetExpiryTime( xInternalTimerHandle );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Timer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #अगर ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreate( स्थिर अक्षर * स्थिर pcTimerName,
                                        स्थिर TickType_t xTimerPeriodInTicks,
                                        स्थिर BaseType_t xAutoReload,
                                        व्योम * स्थिर pvTimerID,
                                        TimerCallbackFunction_t pxCallbackFunction ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = शून्य;
            TimerHandle_t xExternalTimerHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xInternalTimerHandle = xTimerCreate( pcTimerName, xTimerPeriodInTicks, xAutoReload, pvTimerID, MPU_TimerCallback );

                अगर( xInternalTimerHandle != शून्य )
                {
                    MPU_Store_Timer_Handle_At_सूचकांक( l_सूचकांक, xInternalTimerHandle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xExternalTimerHandle;
        }

    #पूर्ण_अगर /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreateStatic( स्थिर अक्षर * स्थिर pcTimerName,
                                              स्थिर TickType_t xTimerPeriodInTicks,
                                              स्थिर BaseType_t xAutoReload,
                                              व्योम * स्थिर pvTimerID,
                                              TimerCallbackFunction_t pxCallbackFunction,
                                              StaticTimer_t * px_Timer_बफर ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = शून्य;
            TimerHandle_t xExternalTimerHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xInternalTimerHandle = xTimerCreateStatic( pcTimerName, xTimerPeriodInTicks, xAutoReload, pvTimerID, MPU_TimerCallback, px_Timer_बफर );

                अगर( xInternalTimerHandle != शून्य )
                {
                    MPU_Store_Timer_Handle_At_सूचकांक( l_सूचकांक, xInternalTimerHandle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xExternalTimerHandle;
        }

    #पूर्ण_अगर /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        BaseType_t MPU_x_Timer_Get_Static_बफर( TimerHandle_t xTimer,
                                              StaticTimer_t ** ppx_Timer_बफर ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xReturn = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalTimerHandle != शून्य )
                {
                    xReturn = x_Timer_Get_Static_बफर( xInternalTimerHandle, ppx_Timer_बफर );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGenericCommandFromISR( TimerHandle_t xTimer,
                                                    स्थिर BaseType_t xCommandID,
                                                    स्थिर TickType_t x_Optional_मूल्य,
                                                    BaseType_t * स्थिर pxHigherPriorityTaskWoken,
                                                    स्थिर TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) xTimer;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalTimerHandle != शून्य )
                {
                    xReturn = xTimerGenericCommandFromISR( xInternalTimerHandle, xCommandID, x_Optional_मूल्य, pxHigherPriorityTaskWoken, xTicksToWait );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerDelete( TimerHandle_t xTimer, TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) xTimer;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalTimerHandle != शून्य )
                {
                    xReturn = xTimerGenericCommandFromTask( xInternalTimerHandle,
                                                            tmrCOMMAND_DELETE,
                                                            0U, /* xOptionalValue */
                                                            शून्य, /* pxHigherPriorityTaskWoken */
                                                            xTicksToWait );
                    अगर( xReturn != pdFALSE )
                    {
                        MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for event group APIs.              */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
                                             स्थिर EventBits_t uxBitsToWaitFor,
                                             स्थिर BaseType_t xClearOnExit,
                                             स्थिर BaseType_t xWaitForAllBits,
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

            वापस xReturn;
        }

        EventBits_t MPU_xEventGroupWaitBitsImpl( स्थिर xEventGroupWaitBitsParams_t * pxParams ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupWaitBitsImpl( स्थिर xEventGroupWaitBitsParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            अगर( pxParams != शून्य )
            {
                xAreParamsReadable = x_Port_Is_Authorized_To_Access_बफर( pxParams,
                                                                      माप( xEventGroupWaitBitsParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            अगर( xAreParamsReadable == pdTRUE )
            {
                अगर( ( ( pxParams->uxBitsToWaitFor & eventEVENT_BITS_CONTROL_BYTES ) == 0U ) &&
                    ( pxParams->uxBitsToWaitFor != 0U )
                    #अगर ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                        && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( pxParams->xTicksToWait != 0U ) ) )
                    #पूर्ण_अगर
                    )
                {
                    l_सूचकांक = ( int32_t ) ( pxParams->xEventGroup );

                    अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                        {
                            xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                            अगर( xInternalEventGroupHandle != शून्य )
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

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupClearBitsImpl( EventGroupHandle_t xEventGroup,
                                                  स्थिर EventBits_t uxBitsToClear ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupClearBitsImpl( EventGroupHandle_t xEventGroup,
                                                  स्थिर EventBits_t uxBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            अगर( ( uxBitsToClear & eventEVENT_BITS_CONTROL_BYTES ) == 0U )
            {
                l_सूचकांक = ( int32_t ) xEventGroup;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xInternalEventGroupHandle != शून्य )
                        {
                            xReturn = xEventGroupClearBits( xInternalEventGroupHandle, uxBitsToClear );
                        }
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSetBitsImpl( EventGroupHandle_t xEventGroup,
                                                स्थिर EventBits_t uxBitsToSet ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupSetBitsImpl( EventGroupHandle_t xEventGroup,
                                                स्थिर EventBits_t uxBitsToSet ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            अगर( ( uxBitsToSet & eventEVENT_BITS_CONTROL_BYTES ) == 0U )
            {
                l_सूचकांक = ( int32_t ) xEventGroup;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xInternalEventGroupHandle != शून्य )
                        {
                            xReturn = xEventGroupSetBits( xInternalEventGroupHandle, uxBitsToSet );
                        }
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSyncImpl( EventGroupHandle_t xEventGroup,
                                             स्थिर EventBits_t uxBitsToSet,
                                             स्थिर EventBits_t uxBitsToWaitFor,
                                             TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupSyncImpl( EventGroupHandle_t xEventGroup,
                                             स्थिर EventBits_t uxBitsToSet,
                                             स्थिर EventBits_t uxBitsToWaitFor,
                                             TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            अगर( ( ( uxBitsToWaitFor & eventEVENT_BITS_CONTROL_BYTES ) == 0U ) &&
                ( uxBitsToWaitFor != 0U )
                #अगर ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                    && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                #पूर्ण_अगर
                )
            {
                l_सूचकांक = ( int32_t ) xEventGroup;

                अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( xInternalEventGroupHandle != शून्य )
                        {
                            xReturn = xEventGroupSync( xInternalEventGroupHandle, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
                        }
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_Group_Get_संख्या_Impl( व्योम * xEventGroup ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Event_Group_Get_संख्या_Impl( व्योम * xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            l_सूचकांक = ( int32_t ) xEventGroup;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                {
                    xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalEventGroupHandle != शून्य )
                    {
                        xReturn = ux_Event_Group_Get_संख्या( xInternalEventGroupHandle );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        व्योम MPU_v_Event_Group_Set_संख्या_Impl( व्योम * xEventGroup,
                                           UBaseType_t ux_Event_Group_संख्या ) PRIVILEGED_FUNCTION;

        व्योम MPU_v_Event_Group_Set_संख्या_Impl( व्योम * xEventGroup,
                                           UBaseType_t ux_Event_Group_संख्या ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            l_सूचकांक = ( int32_t ) xEventGroup;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                {
                    xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( xInternalEventGroupHandle != शून्य )
                    {
                        v_Event_Group_Set_संख्या( xInternalEventGroupHandle, ux_Event_Group_संख्या );
                    }
                }
            }
        }

    #पूर्ण_अगर /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Event Group APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #अगर ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        EventGroupHandle_t MPU_xEventGroupCreate( व्योम ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = शून्य;
            EventGroupHandle_t xExternalEventGroupHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xInternalEventGroupHandle = xEventGroupCreate();

                अगर( xInternalEventGroupHandle != शून्य )
                {
                    MPU_Store_Event_Group_Handle_At_सूचकांक( l_सूचकांक, xInternalEventGroupHandle );
                    xExternalEventGroupHandle = ( EventGroupHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xExternalEventGroupHandle;
        }

    #पूर्ण_अगर /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        EventGroupHandle_t MPU_xEventGroupCreateStatic( StaticEventGroup_t * px_Event_Group_बफर ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = शून्य;
            EventGroupHandle_t xExternalEventGroupHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

            अगर( l_सूचकांक != -1 )
            {
                xInternalEventGroupHandle = xEventGroupCreateStatic( px_Event_Group_बफर );

                अगर( xInternalEventGroupHandle != शून्य )
                {
                    MPU_Store_Event_Group_Handle_At_सूचकांक( l_सूचकांक, xInternalEventGroupHandle );
                    xExternalEventGroupHandle = ( EventGroupHandle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            वापस xExternalEventGroupHandle;
        }

    #पूर्ण_अगर /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_EVENT_GROUPS == 1 )

        व्योम MPU_vEventGroupDelete( EventGroupHandle_t xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) xEventGroup;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalEventGroupHandle != शून्य )
                {
                    vEventGroupDelete( xInternalEventGroupHandle );
                    MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );
                }
            }
        }

    #पूर्ण_अगर /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        BaseType_t MPU_x_Event_Group_Get_Static_बफर( EventGroupHandle_t xEventGroup,
                                                   StaticEventGroup_t ** ppx_Event_Group_बफर ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) xEventGroup;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalEventGroupHandle != शून्य )
                {
                    xReturn = x_Event_Group_Get_Static_बफर( xInternalEventGroupHandle, ppx_Event_Group_बफर );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        BaseType_t MPU_xEventGroupClearBitsFromISR( EventGroupHandle_t xEventGroup,
                                                    स्थिर EventBits_t uxBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) xEventGroup;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalEventGroupHandle != शून्य )
                {
                    xReturn = xEventGroupClearBitsFromISR( xInternalEventGroupHandle, uxBitsToClear );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        BaseType_t MPU_xEventGroupSetBitsFromISR( EventGroupHandle_t xEventGroup,
                                                  स्थिर EventBits_t uxBitsToSet,
                                                  BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) xEventGroup;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalEventGroupHandle != शून्य )
                {
                    xReturn = xEventGroupSetBitsFromISR( xInternalEventGroupHandle, uxBitsToSet, pxHigherPriorityTaskWoken );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupGetBitsFromISR( EventGroupHandle_t xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) xEventGroup;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_Get_Event_Group_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( xInternalEventGroupHandle != शून्य )
                {
                    xReturn = xEventGroupGetBitsFromISR( xInternalEventGroupHandle );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for stream buffer APIs.            */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

        माप_प्रकार MPU_x_Stream_बफर_Send_Impl( Stream_बफर_Handle_t x_Stream_बफर,
                                          स्थिर व्योम * pv_Tx_तथ्य,
                                          माप_प्रकार x_तथ्य_लंबाई_Bytes,
                                          TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        माप_प्रकार MPU_x_Stream_बफर_Send_Impl( Stream_बफर_Handle_t x_Stream_बफर,
                                          स्थिर व्योम * pv_Tx_तथ्य,
                                          माप_प्रकार x_तथ्य_लंबाई_Bytes,
                                          TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            माप_प्रकार xReturn = 0;
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t x_Is_Tx_तथ्य_बफर_Readable = pdFALSE;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = pdFALSE;

            अगर( pv_Tx_तथ्य != शून्य )
            {
                x_Is_Tx_तथ्य_बफर_Readable = x_Port_Is_Authorized_To_Access_बफर( pv_Tx_तथ्य,
                                                                           x_तथ्य_लंबाई_Bytes,
                                                                           tskMPU_READ_PERMISSION );

                अगर( x_Is_Tx_तथ्य_बफर_Readable == pdTRUE )
                {
                    l_सूचकांक = ( int32_t ) x_Stream_बफर;

                    अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( x_Calling_Task_Is_Authorized_To_Access_Stream_बफर == pdTRUE )
                        {
                            x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                            अगर( x_Internal_Stream_बफर_Handle != शून्य )
                            {
                                xReturn = x_Stream_बफर_Send( x_Internal_Stream_बफर_Handle, pv_Tx_तथ्य, x_तथ्य_लंबाई_Bytes, xTicksToWait );
                            }
                        }
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

        माप_प्रकार MPU_x_Stream_बफर_Receive_Impl( Stream_बफर_Handle_t x_Stream_बफर,
                                             व्योम * pv_Rx_तथ्य,
                                             माप_प्रकार x_बफर_लंबाई_Bytes,
                                             TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        माप_प्रकार MPU_x_Stream_बफर_Receive_Impl( Stream_बफर_Handle_t x_Stream_बफर,
                                             व्योम * pv_Rx_तथ्य,
                                             माप_प्रकार x_बफर_लंबाई_Bytes,
                                             TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            माप_प्रकार xReturn = 0;
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t x_Is_Rx_तथ्य_बफर_Writeable = pdFALSE;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = pdFALSE;

            अगर( pv_Rx_तथ्य != शून्य )
            {
                x_Is_Rx_तथ्य_बफर_Writeable = x_Port_Is_Authorized_To_Access_बफर( pv_Rx_तथ्य,
                                                                            x_बफर_लंबाई_Bytes,
                                                                            tskMPU_WRITE_PERMISSION );

                अगर( x_Is_Rx_तथ्य_बफर_Writeable == pdTRUE )
                {
                    l_सूचकांक = ( int32_t ) x_Stream_बफर;

                    अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                        अगर( x_Calling_Task_Is_Authorized_To_Access_Stream_बफर == pdTRUE )
                        {
                            x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                            अगर( x_Internal_Stream_बफर_Handle != शून्य )
                            {
                                xReturn = x_Stream_बफर_Receive( x_Internal_Stream_बफर_Handle, pv_Rx_तथ्य, x_बफर_लंबाई_Bytes, xTicksToWait );
                            }
                        }
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_बफर_Is_Full_Impl( Stream_बफर_Handle_t x_Stream_बफर ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_x_Stream_बफर_Is_Full_Impl( Stream_बफर_Handle_t x_Stream_बफर ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = pdFALSE;

            l_सूचकांक = ( int32_t ) x_Stream_बफर;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( x_Calling_Task_Is_Authorized_To_Access_Stream_बफर == pdTRUE )
                {
                    x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( x_Internal_Stream_बफर_Handle != शून्य )
                    {
                        xReturn = x_Stream_बफर_Is_Full( x_Internal_Stream_बफर_Handle );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_बफर_Is_Empty_Impl( Stream_बफर_Handle_t x_Stream_बफर ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_x_Stream_बफर_Is_Empty_Impl( Stream_बफर_Handle_t x_Stream_बफर ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = pdFALSE;

            l_सूचकांक = ( int32_t ) x_Stream_बफर;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( x_Calling_Task_Is_Authorized_To_Access_Stream_बफर == pdTRUE )
                {
                    x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( x_Internal_Stream_बफर_Handle != शून्य )
                    {
                        xReturn = x_Stream_बफर_Is_Empty( x_Internal_Stream_बफर_Handle );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

        माप_प्रकार MPU_x_Stream_बफर_Spaces_Available_Impl( Stream_बफर_Handle_t x_Stream_बफर ) PRIVILEGED_FUNCTION;

        माप_प्रकार MPU_x_Stream_बफर_Spaces_Available_Impl( Stream_बफर_Handle_t x_Stream_बफर ) /* PRIVILEGED_FUNCTION */
        {
            माप_प्रकार xReturn = 0;
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = pdFALSE;

            l_सूचकांक = ( int32_t ) x_Stream_बफर;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( x_Calling_Task_Is_Authorized_To_Access_Stream_बफर == pdTRUE )
                {
                    x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( x_Internal_Stream_बफर_Handle != शून्य )
                    {
                        xReturn = x_Stream_बफर_Spaces_Available( x_Internal_Stream_बफर_Handle );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

        माप_प्रकार MPU_x_Stream_बफर_Bytes_Available_Impl( Stream_बफर_Handle_t x_Stream_बफर ) PRIVILEGED_FUNCTION;

        माप_प्रकार MPU_x_Stream_बफर_Bytes_Available_Impl( Stream_बफर_Handle_t x_Stream_बफर ) /* PRIVILEGED_FUNCTION */
        {
            माप_प्रकार xReturn = 0;
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = pdFALSE;

            l_सूचकांक = ( int32_t ) x_Stream_बफर;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( x_Calling_Task_Is_Authorized_To_Access_Stream_बफर == pdTRUE )
                {
                    x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( x_Internal_Stream_बफर_Handle != शून्य )
                    {
                        xReturn = x_Stream_बफर_Bytes_Available( x_Internal_Stream_बफर_Handle );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_बफर_Set_Trigger_Level_Impl( Stream_बफर_Handle_t x_Stream_बफर,
                                                         माप_प्रकार xTriggerLevel ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_x_Stream_बफर_Set_Trigger_Level_Impl( Stream_बफर_Handle_t x_Stream_बफर,
                                                         माप_प्रकार xTriggerLevel ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = pdFALSE;

            l_सूचकांक = ( int32_t ) x_Stream_बफर;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( x_Calling_Task_Is_Authorized_To_Access_Stream_बफर == pdTRUE )
                {
                    x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( x_Internal_Stream_बफर_Handle != शून्य )
                    {
                        xReturn = x_Stream_बफर_Set_Trigger_Level( x_Internal_Stream_बफर_Handle, xTriggerLevel );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

        माप_प्रकार MPU_x_Stream_बफर_अग्र_Message_लंबाई_Bytes_Impl( Stream_बफर_Handle_t x_Stream_बफर ) PRIVILEGED_FUNCTION;

        माप_प्रकार MPU_x_Stream_बफर_अग्र_Message_लंबाई_Bytes_Impl( Stream_बफर_Handle_t x_Stream_बफर ) /* PRIVILEGED_FUNCTION */
        {
            माप_प्रकार xReturn = 0;
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;
            BaseType_t x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = pdFALSE;

            l_सूचकांक = ( int32_t ) x_Stream_बफर;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_To_Access_Stream_बफर = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( x_Calling_Task_Is_Authorized_To_Access_Stream_बफर == pdTRUE )
                {
                    x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                    अगर( x_Internal_Stream_बफर_Handle != शून्य )
                    {
                        xReturn = x_Stream_बफर_अग्र_Message_लंबाई_Bytes( x_Internal_Stream_बफर_Handle );
                    }
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Stream Buffer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #अगर ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        Stream_बफर_Handle_t MPU_x_Stream_बफर_Generic_Create( माप_प्रकार x_बफर_आकार_Bytes,
                                                             माप_प्रकार xTriggerLevelBytes,
                                                             BaseType_t x_Stream_बफर_Type,
                                                             Stream_बफर_Callback_Function_t pxSendCompletedCallback,
                                                             Stream_बफर_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            Stream_बफर_Handle_t x_External_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == शून्य ) &&
                          ( pxReceiveCompletedCallback == शून्य ) );

            अगर( ( pxSendCompletedCallback == शून्य ) &&
                ( pxReceiveCompletedCallback == शून्य ) )
            {
                l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

                अगर( l_सूचकांक != -1 )
                {
                    x_Internal_Stream_बफर_Handle = x_Stream_बफर_Generic_Create( x_बफर_आकार_Bytes,
                                                                              xTriggerLevelBytes,
                                                                              x_Stream_बफर_Type,
                                                                              शून्य,
                                                                              शून्य );

                    अगर( x_Internal_Stream_बफर_Handle != शून्य )
                    {
                        MPU_Store_Stream_बफर_Handle_At_सूचकांक( l_सूचकांक, x_Internal_Stream_बफर_Handle );
                        x_External_Stream_बफर_Handle = ( Stream_बफर_Handle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                    }
                    अन्यथा
                    {
                        MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                    }
                }
            }
            अन्यथा
            {
                trace_STREAM_बफर_CREATE_FAILED( x_Stream_बफर_Type );
                x_External_Stream_बफर_Handle = शून्य;
            }

            वापस x_External_Stream_बफर_Handle;
        }

    #पूर्ण_अगर /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        Stream_बफर_Handle_t MPU_x_Stream_बफर_Generic_Create_Static( माप_प्रकार x_बफर_आकार_Bytes,
                                                                   माप_प्रकार xTriggerLevelBytes,
                                                                   BaseType_t x_Stream_बफर_Type,
                                                                   uint8_t * स्थिर puc_Stream_बफर_Storage_Area,
                                                                   Static_Stream_बफर_t * स्थिर px_Static_Stream_बफर,
                                                                   Stream_बफर_Callback_Function_t pxSendCompletedCallback,
                                                                   Stream_बफर_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            Stream_बफर_Handle_t x_External_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == शून्य ) &&
                          ( pxReceiveCompletedCallback == शून्य ) );

            अगर( ( pxSendCompletedCallback == शून्य ) &&
                ( pxReceiveCompletedCallback == शून्य ) )
            {
                l_सूचकांक = MPU_Get_Free_सूचकांक_In_Kernel_Object_Pool();

                अगर( l_सूचकांक != -1 )
                {
                    x_Internal_Stream_बफर_Handle = x_Stream_बफर_Generic_Create_Static( x_बफर_आकार_Bytes,
                                                                                    xTriggerLevelBytes,
                                                                                    x_Stream_बफर_Type,
                                                                                    puc_Stream_बफर_Storage_Area,
                                                                                    px_Static_Stream_बफर,
                                                                                    शून्य,
                                                                                    शून्य );

                    अगर( x_Internal_Stream_बफर_Handle != शून्य )
                    {
                        MPU_Store_Stream_बफर_Handle_At_सूचकांक( l_सूचकांक, x_Internal_Stream_बफर_Handle );
                        x_External_Stream_बफर_Handle = ( Stream_बफर_Handle_t ) CONVERT_TO_EXTERNAL_सूचकांक( l_सूचकांक );
                    }
                    अन्यथा
                    {
                        MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( l_सूचकांक );
                    }
                }
            }
            अन्यथा
            {
                trace_STREAM_बफर_CREATE_STATIC_FAILED( xReturn, x_Stream_बफर_Type );
                x_External_Stream_बफर_Handle = शून्य;
            }

            वापस x_External_Stream_बफर_Handle;
        }

    #पूर्ण_अगर /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

        व्योम MPU_v_Stream_बफर_Delete( Stream_बफर_Handle_t x_Stream_बफर ) /* PRIVILEGED_FUNCTION */
        {
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_Stream_बफर;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( x_Internal_Stream_बफर_Handle != शून्य )
                {
                    v_Stream_बफर_Delete( x_Internal_Stream_बफर_Handle );
                }

                MPU_Set_सूचकांक_Free_In_Kernel_Object_Pool( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );
            }
        }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_बफर_Reset( Stream_बफर_Handle_t x_Stream_बफर ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_Stream_बफर;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( x_Internal_Stream_बफर_Handle != शून्य )
                {
                    xReturn = x_Stream_बफर_Reset( x_Internal_Stream_बफर_Handle );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        BaseType_t MPU_x_Stream_बफर_Get_Static_Buffers( Stream_बफर_Handle_t xStreamBuffers,
                                                      uint8_t * ppuc_Stream_बफर_Storage_Area,
                                                      Static_Stream_बफर_t * ppx_Static_Stream_बफर ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) xStreamBuffers;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( x_Internal_Stream_बफर_Handle != शून्य )
                {
                    xReturn = MPU_x_Stream_बफर_Get_Static_Buffers( x_Internal_Stream_बफर_Handle, ppuc_Stream_बफर_Storage_Area, ppx_Static_Stream_बफर );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

    माप_प्रकार MPU_x_Stream_बफर_Send_From_ISR( Stream_बफर_Handle_t x_Stream_बफर,
                                         स्थिर व्योम * pv_Tx_तथ्य,
                                         माप_प्रकार x_तथ्य_लंबाई_Bytes,
                                         BaseType_t * स्थिर pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        माप_प्रकार xReturn = 0;
        Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
        int32_t l_सूचकांक;

        l_सूचकांक = ( int32_t ) x_Stream_बफर;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( x_Internal_Stream_बफर_Handle != शून्य )
            {
                xReturn = x_Stream_बफर_Send_From_ISR( x_Internal_Stream_बफर_Handle, pv_Tx_तथ्य, x_तथ्य_लंबाई_Bytes, pxHigherPriorityTaskWoken );
            }
        }

        वापस xReturn;
    }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

    माप_प्रकार MPU_x_Stream_बफर_Receive_From_ISR( Stream_बफर_Handle_t x_Stream_बफर,
                                            व्योम * pv_Rx_तथ्य,
                                            माप_प्रकार x_बफर_लंबाई_Bytes,
                                            BaseType_t * स्थिर pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        माप_प्रकार xReturn = 0;
        Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
        int32_t l_सूचकांक;

        l_सूचकांक = ( int32_t ) x_Stream_बफर;

        अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

            अगर( x_Internal_Stream_बफर_Handle != शून्य )
            {
                xReturn = x_Stream_बफर_Receive_From_ISR( x_Internal_Stream_बफर_Handle, pv_Rx_तथ्य, x_बफर_लंबाई_Bytes, pxHigherPriorityTaskWoken );
            }
        }

        वापस xReturn;
    }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_बफर_Send_Completed_From_ISR( Stream_बफर_Handle_t x_Stream_बफर,
                                                          BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_Stream_बफर;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( x_Internal_Stream_बफर_Handle != शून्य )
                {
                    xReturn = x_Stream_बफर_Send_Completed_From_ISR( x_Internal_Stream_बफर_Handle, pxHigherPriorityTaskWoken );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_बफर_Receive_Completed_From_ISR( Stream_बफर_Handle_t x_Stream_बफर,
                                                             BaseType_t * pxHigherPriorityTaskWoken ) /*PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_Stream_बफर;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( x_Internal_Stream_बफर_Handle != शून्य )
                {
                    xReturn = x_Stream_बफर_Receive_Completed_From_ISR( x_Internal_Stream_बफर_Handle, pxHigherPriorityTaskWoken );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

    #अगर ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_x_Stream_बफर_Reset_From_ISR( Stream_बफर_Handle_t x_Stream_बफर ) /*PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            Stream_बफर_Handle_t x_Internal_Stream_बफर_Handle = शून्य;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_Stream_बफर;

            अगर( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Internal_Stream_बफर_Handle = MPU_Get_Stream_बफर_Handle_At_सूचकांक( CONVERT_TO_INTERNAL_सूचकांक( l_सूचकांक ) );

                अगर( x_Internal_Stream_बफर_Handle != शून्य )
                {
                    xReturn = x_Stream_बफर_Reset_From_ISR( x_Internal_Stream_बफर_Handle );
                }
            }

            वापस xReturn;
        }

    #पूर्ण_अगर /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h. */

    #अगर configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #समावेश "application_defined_privileged_functions.h"
    #पूर्ण_अगर
/*-----------------------------------------------------------*/

/**
 * @brief Array of system call implementation functions.
 *
 * The index in the array MUST match the corresponding system call number
 * defined in mpu_wrappers.h.
 */
    PRIVILEGED_तथ्य UBaseType_t uxSystemCallImplementations[ अंक_SYSTEM_CALLS ] =
    {
        #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_xTaskGenericNotifyImpl,                     /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyWaitImpl,                 /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #पूर्ण_अगर

        #अगर ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_xTimerGenericCommandFromTaskImpl,           /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #पूर्ण_अगर

        #अगर ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_xEventGroupWaitBitsImpl,                    /* SYSTEM_CALL_xEventGroupWaitBits. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupWaitBits. */
        #पूर्ण_अगर

        /* The system calls above this line take 5 parameters. */

        #अगर ( INCLUDE_xTaskDelayUntil == 1 )
            ( UBaseType_t ) MPU_xTaskDelayUntilImpl,                        /* SYSTEM_CALL_xTaskDelayUntil. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskDelayUntil. */
        #पूर्ण_अगर

        #अगर ( INCLUDE_xTaskAbortDelay == 1 )
            ( UBaseType_t ) MPU_xTaskAbortDelayImpl,                        /* SYSTEM_CALL_xTaskAbortDelay. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskAbortDelay. */
        #पूर्ण_अगर

        #अगर ( INCLUDE_vTaskDelay == 1 )
            ( UBaseType_t ) MPU_vTaskDelayImpl,                             /* SYSTEM_CALL_vTaskDelay. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskDelay. */
        #पूर्ण_अगर

        #अगर ( INCLUDE_uxTaskPriorityGet == 1 )
            ( UBaseType_t ) MPU_uxTaskPriorityGetImpl,                      /* SYSTEM_CALL_uxTaskPriorityGet. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskPriorityGet. */
        #पूर्ण_अगर

        #अगर ( INCLUDE_eTaskGetState == 1 )
            ( UBaseType_t ) MPU_eTaskGetStateImpl,                          /* SYSTEM_CALL_eTaskGetState. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_eTaskGetState. */
        #पूर्ण_अगर

        #अगर ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_vTaskGetInfoImpl,                           /* SYSTEM_CALL_vTaskGetInfo. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskGetInfo. */
        #पूर्ण_अगर

        #अगर ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
            ( UBaseType_t ) MPU_xTaskGetIdleTaskHandleImpl,                 /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #पूर्ण_अगर

        #अगर ( INCLUDE_vTaskSuspend == 1 )
            ( UBaseType_t ) MPU_vTaskSuspendImpl,                           /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) MPU_vTaskResumeImpl,                            /* SYSTEM_CALL_vTaskResume. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskResume. */
        #पूर्ण_अगर

        ( UBaseType_t ) MPU_x_Task_Get_Tick_गिनती_Impl,                          /* SYSTEM_CALL_xTaskGetTickCount. */
        ( UBaseType_t ) MPU_ux_Task_Get_संख्या_Of_Tasks_Impl,                     /* SYSTEM_CALL_uxTaskGetNumberOfTasks. */

        #अगर ( configGENERATE_RUN_TIME_STATS == 1 )
            ( UBaseType_t ) MPU_ul_Task_Get_Run_Time_गणक_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) MPU_ulTaskGetRunTimePercentImpl,                /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #पूर्ण_अगर

        #अगर ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
            ( UBaseType_t ) MPU_ulTaskGetIdleRunTimePercentImpl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_Run_Time_गणक_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #पूर्ण_अगर

        #अगर ( configUSE_APPLICATION_TASK_TAG == 1 )
            ( UBaseType_t ) MPU_vTaskSetApplicationTaskTagImpl,             /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) MPU_xTaskGetApplicationTaskTagImpl,             /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #पूर्ण_अगर

        #अगर ( config_अंक_THREAD_LOCAL_STORAGE_POINTERS != 0 )
            ( UBaseType_t ) MPU_vTaskSetThreadLocalStoragePointerImpl,      /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) MPU_pvTaskGetThreadLocalStoragePointerImpl,     /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #पूर्ण_अगर

        #अगर ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_uxTaskGetSystemStateImpl,                   /* SYSTEM_CALL_uxTaskGetSystemState. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetSystemState. */
        #पूर्ण_अगर

        #अगर ( INCLUDE_ux_Task_Get_ढेर_ऊपरी_Water_Mark == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ढेर_ऊपरी_Water_Mark_Impl,            /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #पूर्ण_अगर

        #अगर ( INCLUDE_ux_Task_Get_ढेर_ऊपरी_Water_Mark2 == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ढेर_ऊपरी_Water_Mark2_Impl,           /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #पूर्ण_अगर

        #अगर ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )
            ( UBaseType_t ) MPU_xTaskGetCurrentTaskHandleImpl,              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #पूर्ण_अगर

        #अगर ( INCLUDE_xTaskGetSchedulerState == 1 )
            ( UBaseType_t ) MPU_xTaskGetSchedulerStateImpl,                 /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #पूर्ण_अगर

        ( UBaseType_t ) MPU_vTaskSetTimeOutStateImpl,                       /* SYSTEM_CALL_vTaskSetTimeOutState. */
        ( UBaseType_t ) MPU_xTaskCheckForTimeOutImpl,                       /* SYSTEM_CALL_xTaskCheckForTimeOut. */

        #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_ulTaskGenericNotifyTakeImpl,                /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyStateClearImpl,           /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) MPU_ul_Task_Generic_Notify_मूल्य_Clear_Impl,          /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #पूर्ण_अगर

        ( UBaseType_t ) MPU_xQueueGenericSendImpl,                          /* SYSTEM_CALL_xQueueGenericSend. */
        ( UBaseType_t ) MPU_uxQueueMessagesWaitingImpl,                     /* SYSTEM_CALL_uxQueueMessagesWaiting. */
        ( UBaseType_t ) MPU_uxQueueSpacesAvailableImpl,                     /* SYSTEM_CALL_uxQueueSpacesAvailable. */
        ( UBaseType_t ) MPU_xQueueReceiveImpl,                              /* SYSTEM_CALL_xQueueReceive. */
        ( UBaseType_t ) MPU_xQueuePeekImpl,                                 /* SYSTEM_CALL_xQueuePeek. */
        ( UBaseType_t ) MPU_xQueueSemaphoreTakeImpl,                        /* SYSTEM_CALL_xQueueSemaphoreTake. */

        #अगर ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
            ( UBaseType_t ) MPU_xQueueGetMutexHolderImpl,                   /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #पूर्ण_अगर

        #अगर ( configUSE_RECURSIVE_MUTEXES == 1 )
            ( UBaseType_t ) MPU_xQueueTakeMutexRecursiveImpl,               /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) MPU_xQueueGiveMutexRecursiveImpl,               /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #पूर्ण_अगर

        #अगर ( configUSE_QUEUE_SETS == 1 )
            ( UBaseType_t ) MPU_xQueueSelectFromSetImpl,                    /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) MPU_xQueueAddToSetImpl,                         /* SYSTEM_CALL_xQueueAddToSet. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueAddToSet. */
        #पूर्ण_अगर

        #अगर config_QUEUE_REGISTRY_आकार > 0
            ( UBaseType_t ) MPU_vQueueAddToRegistryImpl,                    /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) MPU_vQueueUnregisterQueueImpl,                  /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) MPU_pcQueueGetNameImpl,                         /* SYSTEM_CALL_pcQueueGetName. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcQueueGetName. */
        #पूर्ण_अगर

        #अगर ( configUSE_TIMERS == 1 )
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
        #अन्यथा
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
        #पूर्ण_अगर

        #अगर ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_xEventGroupClearBitsImpl,                   /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) MPU_xEventGroupSetBitsImpl,                     /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) MPU_xEventGroupSyncImpl,                        /* SYSTEM_CALL_xEventGroupSync. */

            #अगर ( configUSE_TRACE_FACILITY == 1 )
                ( UBaseType_t ) MPU_ux_Event_Group_Get_संख्या_Impl,              /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) MPU_v_Event_Group_Set_संख्या_Impl,               /* SYSTEM_CALL_vEventGroupSetNumber. */
            #अन्यथा
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_vEventGroupSetNumber. */
            #पूर्ण_अगर
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSync. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxEventGroupGetNumber. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vEventGroupSetNumber. */
        #पूर्ण_अगर

        #अगर ( configUSE_STREAM_BUFFERS == 1 )
            ( UBaseType_t ) MPU_x_Stream_बफर_Send_Impl,                      /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) MPU_x_Stream_बफर_Receive_Impl,                   /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) MPU_x_Stream_बफर_Is_Full_Impl,                    /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) MPU_x_Stream_बफर_Is_Empty_Impl,                   /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) MPU_x_Stream_बफर_Spaces_Available_Impl,           /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) MPU_x_Stream_बफर_Bytes_Available_Impl,            /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) MPU_x_Stream_बफर_Set_Trigger_Level_Impl,           /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) MPU_x_Stream_बफर_अग्र_Message_लंबाई_Bytes_Impl     /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #पूर्ण_अगर

    };
/*-----------------------------------------------------------*/

#पूर्ण_अगर /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/
