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
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "queue.h"
#ಅನ್ತರ್ಭಾವ "timers.h"
#ಅನ್ತರ್ಭಾವ "event_groups.h"
#ಅನ್ತರ್ಭಾವ "stream_buffer.h"
#ಅನ್ತರ್ಭಾವ "mpu_prototypes.h"
#ಅನ್ತರ್ಭಾವ "mpu_syscall_numbers.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#ಯದಿ ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #ifndef configPROTECTED_KERNEL_OBJECT_POOL_SIZE
        #error configPROTECTED_KERNEL_OBJECT_POOL_SIZE must be defined to maximum ಸಂಖ್ಯೆ of kernel objects in the application.
    #endif

/**
 * @brief Offset added to the index before returning to the user.
 *
 * If the actual handle is stored at index i, ( i + INDEX_OFFSET )
 * is returned to the user.
 */
    #define INDEX_OFFSET    1

/**
 * @brief Opaque type for a kernel object.
 */
    ಸಂರಚನಾ OpaqueObject;
    ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ OpaqueObject * OpaqueObjectHandle_t;

/**
 * @brief Defines kernel object in the kernel object pool.
 */
    ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ KernelObject
    {
        OpaqueObjectHandle_t xInternalObjectHandle;
        uint32_t ulKernelObjectType;
        ಶೂನ್ಯ * pvKernelObjectData;
    } KernelObject_t;

/**
 * @brief Kernel object types.
 */
    #define KERNEL_OBJECT_TYPE_INVALID          ( 0UL )
    #define KERNEL_OBJECT_TYPE_QUEUE            ( 1UL )
    #define KERNEL_OBJECT_TYPE_TASK             ( 2UL )
    #define KERNEL_OBJECT_TYPE_STREAM_BUFFER    ( 3UL )
    #define KERNEL_OBJECT_TYPE_EVENT_GROUP      ( 4UL )
    #define KERNEL_OBJECT_TYPE_TIMER            ( 5UL )

/**
 * @brief Checks whether an external index is valid or not.
 */
    #define IS_EXTERNAL_INDEX_VALID( lIndex )   \
    ( ( ( ( lIndex ) >= INDEX_OFFSET ) &&       \
        ( ( lIndex ) < ( configPROTECTED_KERNEL_OBJECT_POOL_SIZE + INDEX_OFFSET ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Checks whether an internal index is valid or not.
 */
    #define IS_INTERNAL_INDEX_VALID( lIndex )   \
    ( ( ( ( lIndex ) >= 0 ) &&                  \
        ( ( lIndex ) < ( configPROTECTED_KERNEL_OBJECT_POOL_SIZE ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Converts an internal index into external.
 */
    #define CONVERT_TO_EXTERNAL_INDEX( lIndex )    ( ( lIndex ) + INDEX_OFFSET )

/**
 * @brief Converts an external index into internal.
 */
    #define CONVERT_TO_INTERNAL_INDEX( lIndex )    ( ( lIndex ) - INDEX_OFFSET )

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
    ಸ್ಥಿರ int32_t MPU_GetFreeIndexInKernelObjectPool( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/**
 * @brief Set the given index as free in the kernel object pool.
 *
 * @param lIndex The index to set as free.
 */
    ಸ್ಥಿರ ಶೂನ್ಯ MPU_SetIndexFreeInKernelObjectPool( int32_t lIndex ) PRIVILEGED_FUNCTION;

/**
 * @brief Get the index at which a given kernel object is stored.
 *
 * @param xHandle The given kernel object handle.
 * @param ulKernelObjectType The kernel object type.
 *
 * @return Index at which the kernel object is stored if it is a valid
 *         handle, -1 otherwise.
 */
    ಸ್ಥಿರ int32_t MPU_GetIndexForHandle( OpaqueObjectHandle_t xHandle,
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
    ಸ್ಥಿರ ಶೂನ್ಯ MPU_StoreHandleAndDataAtIndex( int32_t lIndex,
                                               OpaqueObjectHandle_t xHandle,
                                               ಶೂನ್ಯ * pvKernelObjectData,
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
    ಸ್ಥಿರ OpaqueObjectHandle_t MPU_GetHandleAtIndex( int32_t lIndex,
                                                      uint32_t ulKernelObjectType ) PRIVILEGED_FUNCTION;

    #ಯದಿ ( configUSE_TIMERS == 1 )

/**
 * @brief The function registered as callback for all the timers.
 *
 * We intercept all the timer callbacks so that we can call application
 * callbacks with opaque handle.
 *
 * @param xInternalHandle The internal timer handle.
 */
        ಸ್ಥಿರ ಶೂನ್ಯ MPU_TimerCallback( TimerHandle_t xInternalHandle ) PRIVILEGED_FUNCTION;

    #endif /* #if ( configUSE_TIMERS == 1 ) */

/*
 * Wrappers to keep all the casting in one place.
 */
    #define MPU_StoreQueueHandleAtIndex( lIndex, xHandle )                 MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), ರಿಕ್ತ, KERNEL_OBJECT_TYPE_QUEUE )
    #define MPU_GetQueueHandleAtIndex( lIndex )                            ( QueueHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_QUEUE )

    #ಯದಿ ( configUSE_QUEUE_SETS == 1 )
        #define MPU_StoreQueueSetHandleAtIndex( lIndex, xHandle )          MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), ರಿಕ್ತ, KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_GetQueueSetHandleAtIndex( lIndex )                     ( QueueSetHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_StoreQueueSetMemberHandleAtIndex( lIndex, xHandle )    MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), ರಿಕ್ತ, KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_GetQueueSetMemberHandleAtIndex( lIndex )               ( QueueSetMemberHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_GetIndexForQueueSetMemberHandle( xHandle )             MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_QUEUE )
    #endif

/*
 * Wrappers to keep all the casting in one place for Task APIs.
 */
    #define MPU_StoreTaskHandleAtIndex( lIndex, xHandle )            MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), ರಿಕ್ತ, KERNEL_OBJECT_TYPE_TASK )
    #define MPU_GetTaskHandleAtIndex( lIndex )                       ( TaskHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_TASK )
    #define MPU_GetIndexForTaskHandle( xHandle )                     MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TASK )

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )
/*
 * Wrappers to keep all the casting in one place for Event Group APIs.
 */
        #define MPU_StoreEventGroupHandleAtIndex( lIndex, xHandle )      MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), ರಿಕ್ತ, KERNEL_OBJECT_TYPE_EVENT_GROUP )
        #define MPU_GetEventGroupHandleAtIndex( lIndex )                 ( EventGroupHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_EVENT_GROUP )
        #define MPU_GetIndexForEventGroupHandle( xHandle )               MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_EVENT_GROUP )

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Stream Buffer APIs.
 */
        #define MPU_StoreStreamBufferHandleAtIndex( lIndex, xHandle )    MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle), ರಿಕ್ತ, KERNEL_OBJECT_TYPE_STREAM_BUFFER )
        #define MPU_GetStreamBufferHandleAtIndex( lIndex )               ( StreamBufferHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_STREAM_BUFFER )
        #define MPU_GetIndexForStreamBufferHandle( xHandle )             MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_STREAM_BUFFER )

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

    #ಯದಿ ( configUSE_TIMERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Timer APIs.
 */
        #define MPU_StoreTimerHandleAtIndex( lIndex, xHandle, pxApplicationCallback )    MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), ( ಶೂನ್ಯ * ) ( pxApplicationCallback ), KERNEL_OBJECT_TYPE_TIMER )
        #define MPU_GetTimerHandleAtIndex( lIndex )                                      ( TimerHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_TIMER )
        #define MPU_GetIndexForTimerHandle( xHandle )                                    MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TIMER )

    #endif /* #if ( configUSE_TIMERS == 1 ) */

/*-----------------------------------------------------------*/

/**
 * @brief Kernel object pool.
 */
    PRIVILEGED_DATA ಸ್ಥಿರ KernelObject_t xKernelObjectPool[ configPROTECTED_KERNEL_OBJECT_POOL_SIZE ] = { 0 };
/*-----------------------------------------------------------*/

    ಸ್ಥಿರ int32_t MPU_GetFreeIndexInKernelObjectPool( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, lFreeIndex = -1;

        /* This function is called only from resource create APIs
         * which are not supposed to be called from ISRs. Therefore,
         * we only need to suspend the scheduler and do not require
         * critical section. */
        vTaskSuspendAll();
        {
            ಪ್ರತಿ( i = 0; i < configPROTECTED_KERNEL_OBJECT_POOL_SIZE; i++ )
            {
                ಯದಿ( xKernelObjectPool[ i ].xInternalObjectHandle == ರಿಕ್ತ )
                {
                    /* Mark this index as not free. */
                    xKernelObjectPool[ i ].xInternalObjectHandle = ( OpaqueObjectHandle_t ) ( ~0U );
                    lFreeIndex = i;
                    ಭಙ್ಗ;
                }
            }
        }
        ( ಶೂನ್ಯ ) xTaskResumeAll();

        ಪ್ರತ್ಯಾಗಮ lFreeIndex;
    }
/*-----------------------------------------------------------*/

    ಸ್ಥಿರ ಶೂನ್ಯ MPU_SetIndexFreeInKernelObjectPool( int32_t lIndex ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_INTERNAL_INDEX_VALID( lIndex ) != pdFALSE );

        taskENTER_CRITICAL();
        {
            xKernelObjectPool[ lIndex ].xInternalObjectHandle = ರಿಕ್ತ;
            xKernelObjectPool[ lIndex ].ulKernelObjectType = KERNEL_OBJECT_TYPE_INVALID;
            xKernelObjectPool[ lIndex ].pvKernelObjectData = ರಿಕ್ತ;
        }
        taskEXIT_CRITICAL();
    }
/*-----------------------------------------------------------*/

    ಸ್ಥಿರ int32_t MPU_GetIndexForHandle( OpaqueObjectHandle_t xHandle,
                                          uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, lIndex = -1;

        configASSERT( xHandle != ರಿಕ್ತ );

        ಪ್ರತಿ( i = 0; i < configPROTECTED_KERNEL_OBJECT_POOL_SIZE; i++ )
        {
            ಯದಿ( ( xKernelObjectPool[ i ].xInternalObjectHandle == xHandle ) &&
                ( xKernelObjectPool[ i ].ulKernelObjectType == ulKernelObjectType ) )
            {
                lIndex = i;
                ಭಙ್ಗ;
            }
        }

        ಪ್ರತ್ಯಾಗಮ lIndex;
    }
/*-----------------------------------------------------------*/

    ಸ್ಥಿರ ಶೂನ್ಯ MPU_StoreHandleAndDataAtIndex( int32_t lIndex,
                                               OpaqueObjectHandle_t xHandle,
                                               ಶೂನ್ಯ * pvKernelObjectData,
                                               uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_INTERNAL_INDEX_VALID( lIndex ) != pdFALSE );
        xKernelObjectPool[ lIndex ].xInternalObjectHandle = xHandle;
        xKernelObjectPool[ lIndex ].ulKernelObjectType = ulKernelObjectType;
        xKernelObjectPool[ lIndex ].pvKernelObjectData = pvKernelObjectData;
    }
/*-----------------------------------------------------------*/

    ಸ್ಥಿರ OpaqueObjectHandle_t MPU_GetHandleAtIndex( int32_t lIndex,
                                                      uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        OpaqueObjectHandle_t xObjectHandle = ರಿಕ್ತ;

        configASSERT( IS_INTERNAL_INDEX_VALID( lIndex ) != pdFALSE );

        ಯದಿ( xKernelObjectPool[ lIndex ].ulKernelObjectType == ulKernelObjectType )
        {
            xObjectHandle = xKernelObjectPool[ lIndex ].xInternalObjectHandle;
        }

        ಪ್ರತ್ಯಾಗಮ xObjectHandle;
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ಶೂನ್ಯ vGrantAccessToKernelObject( TaskHandle_t xExternalTaskHandle,
                                         int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lExternalTaskIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                ಯದಿ( xExternalTaskHandle == ರಿಕ್ತ )
                {
                    vPortGrantAccessToKernelObject( xExternalTaskHandle, CONVERT_TO_INTERNAL_INDEX( lExternalKernelObjectHandle ) );
                }
                ಅನ್ಯಥಾ
                {
                    lExternalTaskIndex = ( int32_t ) xExternalTaskHandle;

                    ಯದಿ( IS_EXTERNAL_INDEX_VALID( lExternalTaskIndex ) != pdFALSE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lExternalTaskIndex ) );

                        ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle,
                                                            CONVERT_TO_INTERNAL_INDEX( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #endif /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ಶೂನ್ಯ vRevokeAccessToKernelObject( TaskHandle_t xExternalTaskHandle,
                                          int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lExternalTaskIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                ಯದಿ( xExternalTaskHandle == ರಿಕ್ತ )
                {
                    vPortRevokeAccessToKernelObject( xExternalTaskHandle, CONVERT_TO_INTERNAL_INDEX( lExternalKernelObjectHandle ) );
                }
                ಅನ್ಯಥಾ
                {
                    lExternalTaskIndex = ( int32_t ) xExternalTaskHandle;

                    ಯದಿ( IS_EXTERNAL_INDEX_VALID( lExternalTaskIndex ) != pdFALSE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lExternalTaskIndex ) );

                        ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                        {
                            vPortRevokeAccessToKernelObject( xInternalTaskHandle,
                                                             CONVERT_TO_INTERNAL_INDEX( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #endif /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        ಸ್ಥಿರ ಶೂನ್ಯ MPU_TimerCallback( TimerHandle_t xInternalHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t i, lIndex = -1;
            TimerHandle_t xExternalHandle = ರಿಕ್ತ;
            TimerCallbackFunction_t pxApplicationCallBack = ರಿಕ್ತ;

            /* Coming from the timer task and therefore, should be valid. */
            configASSERT( xInternalHandle != ರಿಕ್ತ );

            ಪ್ರತಿ( i = 0; i < configPROTECTED_KERNEL_OBJECT_POOL_SIZE; i++ )
            {
                ಯದಿ( ( ( TimerHandle_t ) xKernelObjectPool[ i ].xInternalObjectHandle == xInternalHandle ) &&
                    ( xKernelObjectPool[ i ].ulKernelObjectType == KERNEL_OBJECT_TYPE_TIMER ) )
                {
                    lIndex = i;
                    ಭಙ್ಗ;
                }
            }

            configASSERT( lIndex != -1 );
            xExternalHandle = ( TimerHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );

            pxApplicationCallBack = ( TimerCallbackFunction_t ) xKernelObjectPool[ lIndex ].pvKernelObjectData;
            pxApplicationCallBack( xExternalHandle );
        }

    #endif /* #if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for tasks APIs.                   */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_xTaskDelayUntil == 1 )

        BaseType_t MPU_xTaskDelayUntilImpl( TickType_t * ಧ್ರುವ pxPreviousWakeTime,
                                            TickType_t xTimeIncrement ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskDelayUntilImpl( TickType_t * ಧ್ರುವ pxPreviousWakeTime,
                                            TickType_t xTimeIncrement ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xIsPreviousWakeTimeAccessible = pdFALSE;

            ಯದಿ( ( pxPreviousWakeTime != ರಿಕ್ತ ) && ( xTimeIncrement > 0U ) )
            {
                xIsPreviousWakeTimeAccessible = xPortIsAuthorizedToAccessBuffer( pxPreviousWakeTime,
                                                                                 ಪರಿಮಾಣ( TickType_t ),
                                                                                 ( tskMPU_WRITE_PERMISSION | tskMPU_READ_PERMISSION ) );

                ಯದಿ( xIsPreviousWakeTimeAccessible == pdTRUE )
                {
                    xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_xTaskAbortDelay == 1 )

        BaseType_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = ( int32_t ) xTask;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                    {
                        xReturn = xTaskAbortDelay( xInternalTaskHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_vTaskDelay == 1 )

        ಶೂನ್ಯ MPU_vTaskDelayImpl( TickType_t xTicksToDelay ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_vTaskDelayImpl( TickType_t xTicksToDelay ) /* PRIVILEGED_FUNCTION */
        {
            vTaskDelay( xTicksToDelay );
        }

    #endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_uxTaskPriorityGet == 1 )

        UBaseType_t MPU_uxTaskPriorityGetImpl( ಧ್ರುವ TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskPriorityGetImpl( ಧ್ರುವ TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

            ಯದಿ( pxTask == ರಿಕ್ತ )
            {
                uxReturn = uxTaskPriorityGet( pxTask );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) pxTask;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                        {
                            uxReturn = uxTaskPriorityGet( xInternalTaskHandle );
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ uxReturn;
        }

    #endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            eTaskState eReturn = eInvalid;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            lIndex = ( int32_t ) pxTask;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                    {
                        eReturn = eTaskGetState( xInternalTaskHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ eReturn;
        }

    #endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TRACE_FACILITY == 1 )

        ಶೂನ್ಯ MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   TaskStatus_t * pxTaskStatus,
                                   BaseType_t x_Get_Free_ರಾಶಿ_Space,
                                   eTaskState eState ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   TaskStatus_t * pxTaskStatus,
                                   BaseType_t x_Get_Free_ರಾಶಿ_Space,
                                   eTaskState eState ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            BaseType_t xIsTaskStatusWriteable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            xIsTaskStatusWriteable = xPortIsAuthorizedToAccessBuffer( pxTaskStatus,
                                                                      ಪರಿಮಾಣ( TaskStatus_t ),
                                                                      tskMPU_WRITE_PERMISSION );

            ಯದಿ( xIsTaskStatusWriteable == pdTRUE )
            {
                ಯದಿ( xTask == ರಿಕ್ತ )
                {
                    vTaskGetInfo( xTask, pxTaskStatus, x_Get_Free_ರಾಶಿ_Space, eState );
                }
                ಅನ್ಯಥಾ
                {
                    lIndex = ( int32_t ) xTask;

                    ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                            {
                                vTaskGetInfo( xInternalTaskHandle, pxTaskStatus, x_Get_Free_ರಾಶಿ_Space, eState );
                            }
                        }
                    }
                }
            }
        }

    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xIdleTaskHandle = ರಿಕ್ತ;

            xIdleTaskHandle = xTaskGetIdleTaskHandle();

            ಪ್ರತ್ಯಾಗಮ xIdleTaskHandle;
        }

    #endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_vTaskSuspend == 1 )

        ಶೂನ್ಯ MPU_vTaskSuspendImpl( TaskHandle_t pxTaskToSuspend ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_vTaskSuspendImpl( TaskHandle_t pxTaskToSuspend ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ಯದಿ( pxTaskToSuspend == ರಿಕ್ತ )
            {
                vTaskSuspend( pxTaskToSuspend );
            }
            ಅನ್ಯಥಾ
            {
                /* After the scheduler starts, only privileged tasks are allowed
                 * to suspend other tasks. */
                #ಯದಿ ( INCLUDE_xTaskGetSchedulerState == 1 )
                    ಯದಿ( ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) || ( portIS_TASK_PRIVILEGED() == pdTRUE ) )
                #ಅನ್ಯಥಾ
                    ಯದಿ( portIS_TASK_PRIVILEGED() == pdTRUE )
                #endif
                {
                    lIndex = ( int32_t ) pxTaskToSuspend;

                    ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
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

    #ಯದಿ ( INCLUDE_vTaskSuspend == 1 )

        ಶೂನ್ಯ MPU_vTaskResumeImpl( TaskHandle_t pxTaskToResume ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_vTaskResumeImpl( TaskHandle_t pxTaskToResume ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            lIndex = ( int32_t ) pxTaskToResume;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                    {
                        vTaskResume( xInternalTaskHandle );
                    }
                }
            }
        }

    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_ಎಣಿಕೆ_Impl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

    TickType_t MPU_x_Task_Get_Tick_ಎಣಿಕೆ_Impl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        TickType_t xReturn;

        xReturn = x_Task_Get_Tick_ಎಣಿಕೆ();

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_ಸಂಖ್ಯೆ_Of_Tasks_Impl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Task_Get_ಸಂಖ್ಯೆ_Of_Tasks_Impl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn;

        uxReturn = ux_Task_Get_ಸಂಖ್ಯೆ_Of_Tasks();

        ಪ್ರತ್ಯಾಗಮ uxReturn;
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( configGENERATE_RUN_TIME_STATS == 1 )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimeCounterImpl( ಧ್ರುವ TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimeCounterImpl( ಧ್ರುವ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            configRUN_TIME_COUNTER_TYPE xReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ಯದಿ( xTask == ರಿಕ್ತ )
            {
                xReturn = ulTaskGetRunTimeCounter( xTask );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) xTask;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                        {
                            xReturn = ulTaskGetRunTimeCounter( xInternalTaskHandle );
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configGENERATE_RUN_TIME_STATS == 1 )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimePercentImpl( ಧ್ರುವ TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimePercentImpl( ಧ್ರುವ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            configRUN_TIME_COUNTER_TYPE xReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ಯದಿ( xTask == ರಿಕ್ತ )
            {
                xReturn = ulTaskGetRunTimePercent( xTask );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) xTask;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                        {
                            xReturn = ulTaskGetRunTimePercent( xInternalTaskHandle );
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercentImpl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercentImpl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            configRUN_TIME_COUNTER_TYPE xReturn;

            xReturn = ulTaskGetIdleRunTimePercent();

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounterImpl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounterImpl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            configRUN_TIME_COUNTER_TYPE xReturn;

            xReturn = ulTaskGetIdleRunTimeCounter();

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_APPLICATION_TASK_TAG == 1 )

        ಶೂನ್ಯ MPU_vTaskSetApplicationTaskTagImpl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_Tag_ಮೌಲ್ಯ ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_vTaskSetApplicationTaskTagImpl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_Tag_ಮೌಲ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ಯದಿ( xTask == ರಿಕ್ತ )
            {
                vTaskSetApplicationTaskTag( xTask, px_Tag_ಮೌಲ್ಯ );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) xTask;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                        {
                            vTaskSetApplicationTaskTag( xInternalTaskHandle, px_Tag_ಮೌಲ್ಯ );
                        }
                    }
                }
            }
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_APPLICATION_TASK_TAG == 1 )

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = ರಿಕ್ತ;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ಯದಿ( xTask == ರಿಕ್ತ )
            {
                xReturn = xTaskGetApplicationTaskTag( xTask );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) xTask;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                        {
                            xReturn = xTaskGetApplicationTaskTag( xInternalTaskHandle );
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        ಶೂನ್ಯ MPU_vTaskSetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToSet,
                                                        BaseType_t xIndex,
                                                        ಶೂನ್ಯ * pv_ಮೌಲ್ಯ ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_vTaskSetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToSet,
                                                        BaseType_t xIndex,
                                                        ಶೂನ್ಯ * pv_ಮೌಲ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ಯದಿ( xTaskToSet == ರಿಕ್ತ )
            {
                vTaskSetThreadLocalStoragePointer( xTaskToSet, xIndex, pv_ಮೌಲ್ಯ );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) xTaskToSet;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                        {
                            vTaskSetThreadLocalStoragePointer( xInternalTaskHandle, xIndex, pv_ಮೌಲ್ಯ );
                        }
                    }
                }
            }
        }

    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        ಶೂನ್ಯ * MPU_pvTaskGetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToQuery,
                                                           BaseType_t xIndex ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ * MPU_pvTaskGetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToQuery,
                                                           BaseType_t xIndex ) /* PRIVILEGED_FUNCTION */
        {
            ಶೂನ್ಯ * pvReturn = ರಿಕ್ತ;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ಯದಿ( xTaskToQuery == ರಿಕ್ತ )
            {
                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, xIndex );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) xTaskToQuery;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                        {
                            pvReturn = pvTaskGetThreadLocalStoragePointer( xInternalTaskHandle, xIndex );
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ pvReturn;
        }

    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemStateImpl( TaskStatus_t * pxTaskStatusArray,
                                                  UBaseType_t uxArraySize,
                                                  configRUN_TIME_COUNTER_TYPE * pulTotalRunTime ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskGetSystemStateImpl( TaskStatus_t * pxTaskStatusArray,
                                                  UBaseType_t uxArraySize,
                                                  configRUN_TIME_COUNTER_TYPE * pulTotalRunTime ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            BaseType_t xIsTaskStatusArrayWriteable = pdFALSE;
            BaseType_t xIsTotalRunTimeWriteable = pdFALSE;

            ಯದಿ( mpuMULTIPLY_BASETYPE_WILL_OVERFLOW( ಪರಿಮಾಣ( TaskStatus_t ), uxArraySize ) == 0 )
            {
                xIsTaskStatusArrayWriteable = xPortIsAuthorizedToAccessBuffer( pxTaskStatusArray,
                                                                               ಪರಿಮಾಣ( TaskStatus_t ) * ( size_t ) uxArraySize,
                                                                               tskMPU_WRITE_PERMISSION );

                ಯದಿ( pulTotalRunTime != ರಿಕ್ತ )
                {
                    xIsTotalRunTimeWriteable = xPortIsAuthorizedToAccessBuffer( pulTotalRunTime,
                                                                                ಪರಿಮಾಣ( configRUN_TIME_COUNTER_TYPE ),
                                                                                tskMPU_WRITE_PERMISSION );
                }

                ಯದಿ( ( xIsTaskStatusArrayWriteable == pdTRUE ) &&
                    ( ( pulTotalRunTime == ರಿಕ್ತ ) || ( xIsTotalRunTimeWriteable == pdTRUE ) ) )
                {
                    uxReturn = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, pulTotalRunTime );
                }
            }

            ಪ್ರತ್ಯಾಗಮ uxReturn;
        }

    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ಯದಿ( xTask == ರಿಕ್ತ )
            {
                uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( xTask );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) xTask;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                        {
                            uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( xInternalTaskHandle );
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ uxReturn;
        }

    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2 == 1 )

        config_ರಾಶಿ_DEPTH_TYPE MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_ರಾಶಿ_DEPTH_TYPE MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_ರಾಶಿ_DEPTH_TYPE uxReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ಯದಿ( xTask == ರಿಕ್ತ )
            {
                uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( xTask );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) xTask;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                        {
                            uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( xInternalTaskHandle );
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ uxReturn;
        }

    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            TaskHandle_t xExternalTaskHandle = ರಿಕ್ತ;
            int32_t lIndex;

            xInternalTaskHandle = xTaskGetCurrentTaskHandle();

            ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
            {
                lIndex = MPU_GetIndexForTaskHandle( xInternalTaskHandle );

                ಯದಿ( lIndex != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalTaskHandle;
        }

    #endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_xTaskGetSchedulerState == 1 )

        BaseType_t MPU_xTaskGetSchedulerStateImpl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGetSchedulerStateImpl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = taskSCHEDULER_NOT_STARTED;

            xReturn = xTaskGetSchedulerState();

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ MPU_vTaskSetTimeOutStateImpl( TimeOut_t * ಧ್ರುವ pxTimeOut ) PRIVILEGED_FUNCTION;

    ಶೂನ್ಯ MPU_vTaskSetTimeOutStateImpl( TimeOut_t * ಧ್ರುವ pxTimeOut ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xIsTimeOutWriteable = pdFALSE;

        ಯದಿ( pxTimeOut != ರಿಕ್ತ )
        {
            xIsTimeOutWriteable = xPortIsAuthorizedToAccessBuffer( pxTimeOut,
                                                                   ಪರಿಮಾಣ( TimeOut_t ),
                                                                   tskMPU_WRITE_PERMISSION );

            ಯದಿ( xIsTimeOutWriteable == pdTRUE )
            {
                vTaskSetTimeOutState( pxTimeOut );
            }
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCheckForTimeOutImpl( TimeOut_t * ಧ್ರುವ pxTimeOut,
                                             TickType_t * ಧ್ರುವ pxTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xTaskCheckForTimeOutImpl( TimeOut_t * ಧ್ರುವ pxTimeOut,
                                             TickType_t * ಧ್ರುವ pxTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFALSE;
        BaseType_t xIsTimeOutWriteable = pdFALSE;
        BaseType_t xIsTicksToWaitWriteable = pdFALSE;

        ಯದಿ( ( pxTimeOut != ರಿಕ್ತ ) && ( pxTicksToWait != ರಿಕ್ತ ) )
        {
            xIsTimeOutWriteable = xPortIsAuthorizedToAccessBuffer( pxTimeOut,
                                                                   ಪರಿಮಾಣ( TimeOut_t ),
                                                                   tskMPU_WRITE_PERMISSION );
            xIsTicksToWaitWriteable = xPortIsAuthorizedToAccessBuffer( pxTicksToWait,
                                                                       ಪರಿಮಾಣ( TickType_t ),
                                                                       tskMPU_WRITE_PERMISSION );

            ಯದಿ( ( xIsTimeOutWriteable == pdTRUE ) && ( xIsTicksToWaitWriteable == pdTRUE ) )
            {
                xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
            }
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotify( TaskHandle_t xTaskToNotify,
                                           UBaseType_t uxIndexToNotify,
                                           uint32_t ul_ಮೌಲ್ಯ,
                                           eNotifyAction eAction,
                                           uint32_t * pul_Previous_Notification_ಮೌಲ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn = pdFAIL;
            xTaskGenericNotifyParams_t xParams;

            xParams.xTaskToNotify = xTaskToNotify;
            xParams.uxIndexToNotify = uxIndexToNotify;
            xParams.ul_ಮೌಲ್ಯ = ul_ಮೌಲ್ಯ;
            xParams.eAction = eAction;
            xParams.pul_Previous_Notification_ಮೌಲ್ಯ = pul_Previous_Notification_ಮೌಲ್ಯ;

            xReturn = MPU_xTaskGenericNotifyEntry( &( xParams ) );

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

        BaseType_t MPU_xTaskGenericNotifyImpl( ಧ್ರುವ xTaskGenericNotifyParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyImpl( ಧ್ರುವ xTaskGenericNotifyParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            BaseType_t x_Is_Previous_Notification_ಮೌಲ್ಯ_Writeable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            ಯದಿ( pxParams != ರಿಕ್ತ )
            {
                xAreParamsReadable = xPortIsAuthorizedToAccessBuffer( pxParams,
                                                                      ಪರಿಮಾಣ( xTaskGenericNotifyParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ಯದಿ( xAreParamsReadable == pdTRUE )
            {
                ಯದಿ( ( pxParams->uxIndexToNotify < configTASK_NOTIFICATION_ARRAY_ENTRIES ) &&
                    ( ( pxParams->eAction == eNoAction ) ||
                      ( pxParams->eAction == eSetBits ) ||
                      ( pxParams->eAction == eIncrement ) ||
                      ( pxParams->eAction == e_Set_ಮೌಲ್ಯ_With_Overwrite ) ||
                      ( pxParams->eAction == e_Set_ಮೌಲ್ಯ_Without_Overwrite ) ) )
                {
                    ಯದಿ( pxParams->pul_Previous_Notification_ಮೌಲ್ಯ != ರಿಕ್ತ )
                    {
                        x_Is_Previous_Notification_ಮೌಲ್ಯ_Writeable = xPortIsAuthorizedToAccessBuffer( pxParams->pul_Previous_Notification_ಮೌಲ್ಯ,
                                                                                                 ಪರಿಮಾಣ( uint32_t ),
                                                                                                 tskMPU_WRITE_PERMISSION );
                    }

                    ಯದಿ( ( pxParams->pul_Previous_Notification_ಮೌಲ್ಯ == ರಿಕ್ತ ) ||
                        ( x_Is_Previous_Notification_ಮೌಲ್ಯ_Writeable == pdTRUE ) )
                    {
                        lIndex = ( int32_t ) ( pxParams->xTaskToNotify );

                        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                        {
                            xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                            {
                                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                                ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                                {
                                    xReturn = xTaskGenericNotify( xInternalTaskHandle,
                                                                  pxParams->uxIndexToNotify,
                                                                  pxParams->ul_ಮೌಲ್ಯ,
                                                                  pxParams->eAction,
                                                                  pxParams->pul_Previous_Notification_ಮೌಲ್ಯ );
                                }
                            }
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyWait( UBaseType_t uxIndexToWaitOn,
                                               uint32_t ulBitsToClearOnEntry,
                                               uint32_t ulBitsToClearOnExit,
                                               uint32_t * pul_Notification_ಮೌಲ್ಯ,
                                               TickType_t xTicksToWait )
        {
            BaseType_t xReturn = pdFAIL;
            xTaskGenericNotifyWaitParams_t xParams;

            xParams.uxIndexToWaitOn = uxIndexToWaitOn;
            xParams.ulBitsToClearOnEntry = ulBitsToClearOnEntry;
            xParams.ulBitsToClearOnExit = ulBitsToClearOnExit;
            xParams.pul_Notification_ಮೌಲ್ಯ = pul_Notification_ಮೌಲ್ಯ;
            xParams.xTicksToWait = xTicksToWait;

            xReturn = MPU_xTaskGenericNotifyWaitEntry( &( xParams ) );

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

        BaseType_t MPU_xTaskGenericNotifyWaitImpl( ಧ್ರುವ xTaskGenericNotifyWaitParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyWaitImpl( ಧ್ರುವ xTaskGenericNotifyWaitParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t x_Is_Notification_ಮೌಲ್ಯ_Writable = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            ಯದಿ( pxParams != ರಿಕ್ತ )
            {
                xAreParamsReadable = xPortIsAuthorizedToAccessBuffer( pxParams,
                                                                      ಪರಿಮಾಣ( xTaskGenericNotifyWaitParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ಯದಿ( xAreParamsReadable == pdTRUE )
            {
                ಯದಿ( pxParams->uxIndexToWaitOn < configTASK_NOTIFICATION_ARRAY_ENTRIES )
                {
                    ಯದಿ( pxParams->pul_Notification_ಮೌಲ್ಯ != ರಿಕ್ತ )
                    {
                        x_Is_Notification_ಮೌಲ್ಯ_Writable = xPortIsAuthorizedToAccessBuffer( pxParams->pul_Notification_ಮೌಲ್ಯ,
                                                                                        ಪರಿಮಾಣ( uint32_t ),
                                                                                        tskMPU_WRITE_PERMISSION );
                    }

                    ಯದಿ( ( pxParams->pul_Notification_ಮೌಲ್ಯ == ರಿಕ್ತ ) ||
                        ( x_Is_Notification_ಮೌಲ್ಯ_Writable == pdTRUE ) )
                    {
                        xReturn = xTaskGenericNotifyWait( pxParams->uxIndexToWaitOn,
                                                          pxParams->ulBitsToClearOnEntry,
                                                          pxParams->ulBitsToClearOnExit,
                                                          pxParams->pul_Notification_ಮೌಲ್ಯ,
                                                          pxParams->xTicksToWait );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t uxIndexToWaitOn,
                                                  BaseType_t x_Clear_ಎಣಿಕೆ_On_Exit,
                                                  TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t uxIndexToWaitOn,
                                                  BaseType_t x_Clear_ಎಣಿಕೆ_On_Exit,
                                                  TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;

            ಯದಿ( uxIndexToWaitOn < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ulReturn = ulTaskGenericNotifyTake( uxIndexToWaitOn, x_Clear_ಎಣಿಕೆ_On_Exit, xTicksToWait );
            }

            ಪ್ರತ್ಯಾಗಮ ulReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t uxIndexToClear ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t uxIndexToClear ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ಯದಿ( uxIndexToClear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ಯದಿ( xTask == ರಿಕ್ತ )
                {
                    xReturn = xTaskGenericNotifyStateClear( xTask, uxIndexToClear );
                }
                ಅನ್ಯಥಾ
                {
                    lIndex = ( int32_t ) xTask;

                    ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                            {
                                xReturn = xTaskGenericNotifyStateClear( xInternalTaskHandle, uxIndexToClear );
                            }
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t uxIndexToClear,
                                                        uint32_t ulBitsToClear ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t uxIndexToClear,
                                                        uint32_t ulBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ಯದಿ( uxIndexToClear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ಯದಿ( xTask == ರಿಕ್ತ )
                {
                    ulReturn = ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( xTask, uxIndexToClear, ulBitsToClear );
                }
                ಅನ್ಯಥಾ
                {
                    lIndex = ( int32_t ) xTask;

                    ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                            {
                                ulReturn = ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( xInternalTaskHandle, uxIndexToClear, ulBitsToClear );
                            }
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ ulReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Task APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreate( TaskFunction_t pvTaskCode,
                                    ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ pcName,
                                    ಧ್ರುವ config_ರಾಶಿ_DEPTH_TYPE ux_ರಾಶಿ_Depth,
                                    ಶೂನ್ಯ * pvParameters,
                                    UBaseType_t uxPriority,
                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                /* xTaskCreate() can only be used to create privileged tasks in MPU port. */
                ಯದಿ( ( uxPriority & portPRIVILEGE_BIT ) != 0 )
                {
                    xReturn = xTaskCreate( pvTaskCode, pcName, ux_ರಾಶಿ_Depth, pvParameters, uxPriority, &( xInternalTaskHandle ) );

                    ಯದಿ( ( xReturn == pdPASS ) && ( xInternalTaskHandle != ರಿಕ್ತ ) )
                    {
                        MPU_StoreTaskHandleAtIndex( lIndex, xInternalTaskHandle );

                        ಯದಿ( pxCreatedTask != ರಿಕ್ತ )
                        {
                            *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                        }
                    }
                    ಅನ್ಯಥಾ
                    {
                        MPU_SetIndexFreeInKernelObjectPool( lIndex );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                            ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ pcName,
                                            ಧ್ರುವ config_ರಾಶಿ_DEPTH_TYPE ux_ರಾಶಿ_Depth,
                                            ಶೂನ್ಯ * ಧ್ರುವ pvParameters,
                                            UBaseType_t uxPriority,
                                            ರಾಶಿ_Type_t * ಧ್ರುವ pux_ರಾಶಿ_Buffer,
                                            StaticTask_t * ಧ್ರುವ pxTaskBuffer ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xExternalTaskHandle = ರಿಕ್ತ;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xInternalTaskHandle = xTaskCreateStatic( pxTaskCode, pcName, ux_ರಾಶಿ_Depth, pvParameters, uxPriority, pux_ರಾಶಿ_Buffer, pxTaskBuffer );

                ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                {
                    MPU_StoreTaskHandleAtIndex( lIndex, xInternalTaskHandle );

                    #ಯದಿ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ಯದಿ( ( uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, lIndex );
                        }
                    }
                    #endif

                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalTaskHandle;
        }

    #endif /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_vTaskDelete == 1 )

        ಶೂನ್ಯ MPU_vTaskDelete( TaskHandle_t pxTaskToDelete ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            int32_t lIndex;

            ಯದಿ( pxTaskToDelete == ರಿಕ್ತ )
            {
                xInternalTaskHandle = xTaskGetCurrentTaskHandle();
                lIndex = MPU_GetIndexForTaskHandle( xInternalTaskHandle );

                ಯದಿ( lIndex != -1 )
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }

                vTaskDelete( xInternalTaskHandle );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) pxTaskToDelete;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                    {
                        MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
                        vTaskDelete( xInternalTaskHandle );
                    }
                }
            }
        }

    #endif /* #if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/


    #ಯದಿ ( INCLUDE_vTaskPrioritySet == 1 )

        ಶೂನ್ಯ MPU_vTaskPrioritySet( TaskHandle_t pxTask,
                                   UBaseType_t uxNewPriority ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            int32_t lIndex;

            ಯದಿ( pxTask == ರಿಕ್ತ )
            {
                vTaskPrioritySet( pxTask, uxNewPriority );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) pxTask;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                    {
                        vTaskPrioritySet( xInternalTaskHandle, uxNewPriority );
                    }
                }
            }
        }

    #endif /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_xTaskGetHandle == 1 )

        TaskHandle_t MPU_xTaskGetHandle( ಧ್ರುವ ವರ್ಣ * pcNameToQuery ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            TaskHandle_t xExternalTaskHandle = ರಿಕ್ತ;
            int32_t lIndex;

            xInternalTaskHandle = xTaskGetHandle( pcNameToQuery );

            ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
            {
                lIndex = MPU_GetIndexForTaskHandle( xInternalTaskHandle );

                ಯದಿ( lIndex != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalTaskHandle;
        }

    #endif /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/


    #ಯದಿ ( configUSE_APPLICATION_TASK_TAG == 1 )

        BaseType_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     ಶೂನ್ಯ * pvParameter ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

            ಯದಿ( xTask == ರಿಕ್ತ )
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) xTask;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                    {
                        xReturn = xTaskCallApplicationTaskHook( xInternalTaskHandle, pvParameter );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreateRestricted( ಧ್ರುವ TaskParameters_t * ಧ್ರುವ pxTaskDefinition,
                                              TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xReturn = xTaskCreateRestricted( pxTaskDefinition, &( xInternalTaskHandle ) );

                ಯದಿ( ( xReturn == pdPASS ) && ( xInternalTaskHandle != ರಿಕ್ತ ) )
                {
                    MPU_StoreTaskHandleAtIndex( lIndex, xInternalTaskHandle );

                    #ಯದಿ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ಯದಿ( ( pxTaskDefinition->uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, lIndex );
                        }
                    }
                    #endif

                    ಯದಿ( pxCreatedTask != ರಿಕ್ತ )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                    }
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreateRestrictedStatic( ಧ್ರುವ TaskParameters_t * ಧ್ರುವ pxTaskDefinition,
                                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xReturn = xTaskCreateRestrictedStatic( pxTaskDefinition, &( xInternalTaskHandle ) );

                ಯದಿ( ( xReturn == pdPASS ) && ( xInternalTaskHandle != ರಿಕ್ತ ) )
                {
                    MPU_StoreTaskHandleAtIndex( lIndex, xInternalTaskHandle );

                    #ಯದಿ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ಯದಿ( ( pxTaskDefinition->uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, lIndex );
                        }
                    }
                    #endif

                    ಯದಿ( pxCreatedTask != ರಿಕ್ತ )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                    }
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ MPU_vTaskAllocateMPURegions( TaskHandle_t xTaskToModify,
                                      ಧ್ರುವ MemoryRegion_t * ಧ್ರುವ xRegions ) /* PRIVILEGED_FUNCTION */
    {
        TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
        int32_t lIndex;

        ಯದಿ( xTaskToModify == ರಿಕ್ತ )
        {
            vTaskAllocateMPURegions( xTaskToModify, xRegions );
        }
        ಅನ್ಯಥಾ
        {
            lIndex = ( int32_t ) xTaskToModify;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                {
                    vTaskAllocateMPURegions( xInternalTaskHandle, xRegions );
                }
            }
        }
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskGetStaticBuffers( TaskHandle_t xTask,
                                              ರಾಶಿ_Type_t ** ppux_ರಾಶಿ_Buffer,
                                              StaticTask_t ** ppxTaskBuffer ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xReturn = pdFALSE;

            ಯದಿ( xTask == ರಿಕ್ತ )
            {
                xInternalTaskHandle = xTaskGetCurrentTaskHandle();
                xReturn = xTaskGetStaticBuffers( xInternalTaskHandle, ppux_ರಾಶಿ_Buffer, ppxTaskBuffer );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) xTask;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                    {
                        xReturn = xTaskGetStaticBuffers( xInternalTaskHandle, ppux_ರಾಶಿ_Buffer, ppxTaskBuffer );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    ವರ್ಣ * MPU_pcTaskGetName( TaskHandle_t xTaskToQuery ) /* PRIVILEGED_FUNCTION */
    {
        ವರ್ಣ * pcReturn = ರಿಕ್ತ;
        int32_t lIndex;
        TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

        ಯದಿ( xTaskToQuery == ರಿಕ್ತ )
        {
            pcReturn = pcTaskGetName( xTaskToQuery );
        }
        ಅನ್ಯಥಾ
        {
            lIndex = ( int32_t ) xTaskToQuery;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                {
                    pcReturn = pcTaskGetName( xInternalTaskHandle );
                }
            }
        }

        ಪ್ರತ್ಯಾಗಮ pcReturn;
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( INCLUDE_uxTaskPriorityGet == 1 )

        UBaseType_t MPU_uxTaskPriorityGetFromISR( ಧ್ರುವ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

            ಯದಿ( xTask == ರಿಕ್ತ )
            {
                uxReturn = uxTaskPriorityGetFromISR( xTask );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) xTask;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                    {
                        uxReturn = uxTaskPriorityGetFromISR( xInternalTaskHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ uxReturn;
        }

    #endif /* #if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_uxTaskBasePriorityGet( ಧ್ರುವ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

            ಯದಿ( xTask == ರಿಕ್ತ )
            {
                uxReturn = uxTaskBasePriorityGet( xTask );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) xTask;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                    {
                        uxReturn = uxTaskBasePriorityGet( xInternalTaskHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ uxReturn;
        }

    #endif /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_uxTaskBasePriorityGetFromISR( ಧ್ರುವ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

            ಯದಿ( xTask == ರಿಕ್ತ )
            {
                uxReturn = uxTaskBasePriorityGetFromISR( xTask );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) xTask;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                    {
                        uxReturn = uxTaskBasePriorityGetFromISR( xInternalTaskHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ uxReturn;
        }

    #endif /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

        BaseType_t MPU_xTaskResumeFromISR( TaskHandle_t xTaskToResume ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

            lIndex = ( int32_t ) xTaskToResume;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                {
                    xReturn = xTaskResumeFromISR( xInternalTaskHandle );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )*/
/*---------------------------------------------------------------------------------------*/

    #ಯದಿ ( configUSE_APPLICATION_TASK_TAG == 1 )

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagFromISR( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = ರಿಕ್ತ;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

            ಯದಿ( xTask == ರಿಕ್ತ )
            {
                xReturn = xTaskGetApplicationTaskTagFromISR( xTask );
            }
            ಅನ್ಯಥಾ
            {
                lIndex = ( int32_t ) xTask;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                    {
                        xReturn = xTaskGetApplicationTaskTagFromISR( xInternalTaskHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyFromISR( TaskHandle_t xTaskToNotify,
                                                  UBaseType_t uxIndexToNotify,
                                                  uint32_t ul_ಮೌಲ್ಯ,
                                                  eNotifyAction eAction,
                                                  uint32_t * pul_Previous_Notification_ಮೌಲ್ಯ,
                                                  BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

            lIndex = ( int32_t ) xTaskToNotify;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                {
                    xReturn = xTaskGenericNotifyFromISR( xInternalTaskHandle, uxIndexToNotify, ul_ಮೌಲ್ಯ, eAction, pul_Previous_Notification_ಮೌಲ್ಯ, pxHigherPriorityTaskWoken );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ಶೂನ್ಯ MPU_vTaskGenericNotifyGiveFromISR( TaskHandle_t xTaskToNotify,
                                                UBaseType_t uxIndexToNotify,
                                                BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ರಿಕ್ತ;

            lIndex = ( int32_t ) xTaskToNotify;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalTaskHandle != ರಿಕ್ತ )
                {
                    vTaskGenericNotifyGiveFromISR( xInternalTaskHandle, uxIndexToNotify, pxHigherPriorityTaskWoken );
                }
            }
        }
    #endif /*#if ( configUSE_TASK_NOTIFICATIONS == 1 )*/
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for queue APIs.                   */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSendImpl( QueueHandle_t xQueue,
                                          ಧ್ರುವ ಶೂನ್ಯ * ಧ್ರುವ pvItemToQueue,
                                          TickType_t xTicksToWait,
                                          BaseType_t xCopyPosition ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueGenericSendImpl( QueueHandle_t xQueue,
                                          ಧ್ರುವ ಶೂನ್ಯ * ಧ್ರುವ pvItemToQueue,
                                          TickType_t xTicksToWait,
                                          BaseType_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
        BaseType_t xReturn = pdFAIL;
        BaseType_t xIsItemToQueueReadable = pdFALSE;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
        UBaseType_t uxQueueItemSize, uxQueueLength;

        lIndex = ( int32_t ) xQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                {
                    uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );
                    uxQueueLength = uxQueueGetQueueLength( xInternalQueueHandle );

                    ಯದಿ( ( !( ( pvItemToQueue == ರಿಕ್ತ ) && ( uxQueueItemSize != ( UBaseType_t ) 0U ) ) ) &&
                        ( !( ( xCopyPosition == queueOVERWRITE ) && ( uxQueueLength != ( UBaseType_t ) 1U ) ) )
                        #ಯದಿ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        ಯದಿ( pvItemToQueue != ರಿಕ್ತ )
                        {
                            xIsItemToQueueReadable = xPortIsAuthorizedToAccessBuffer( pvItemToQueue,
                                                                                      uxQueueItemSize,
                                                                                      tskMPU_READ_PERMISSION );
                        }

                        ಯದಿ( ( pvItemToQueue == ರಿಕ್ತ ) || ( xIsItemToQueueReadable == pdTRUE ) )
                        {
                            xReturn = xQueueGenericSend( xInternalQueueHandle, pvItemToQueue, xTicksToWait, xCopyPosition );
                        }
                    }
                }
            }
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaitingImpl( ಧ್ರುವ QueueHandle_t pxQueue ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_uxQueueMessagesWaitingImpl( ಧ್ರುವ QueueHandle_t pxQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
        UBaseType_t uxReturn = 0;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        lIndex = ( int32_t ) pxQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                {
                    uxReturn = uxQueueMessagesWaiting( xInternalQueueHandle );
                }
            }
        }

        ಪ್ರತ್ಯಾಗಮ uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueSpacesAvailableImpl( ಧ್ರುವ QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_uxQueueSpacesAvailableImpl( ಧ್ರುವ QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
        UBaseType_t uxReturn = 0;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        lIndex = ( int32_t ) xQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                {
                    uxReturn = uxQueueSpacesAvailable( xInternalQueueHandle );
                }
            }
        }

        ಪ್ರತ್ಯಾಗಮ uxReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceiveImpl( QueueHandle_t pxQueue,
                                      ಶೂನ್ಯ * ಧ್ರುವ pvBuffer,
                                      TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueReceiveImpl( QueueHandle_t pxQueue,
                                      ಶೂನ್ಯ * ಧ್ರುವ pvBuffer,
                                      TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
        BaseType_t xReturn = pdFAIL;
        BaseType_t xIsReceiveBufferWritable = pdFALSE;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
        UBaseType_t uxQueueItemSize;

        lIndex = ( int32_t ) pxQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                {
                    uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );

                    ಯದಿ( ( !( ( ( pvBuffer ) == ರಿಕ್ತ ) && ( uxQueueItemSize != ( UBaseType_t ) 0U ) ) )
                        #ಯದಿ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        xIsReceiveBufferWritable = xPortIsAuthorizedToAccessBuffer( pvBuffer,
                                                                                    uxQueueItemSize,
                                                                                    tskMPU_WRITE_PERMISSION );

                        ಯದಿ( xIsReceiveBufferWritable == pdTRUE )
                        {
                            xReturn = xQueueReceive( xInternalQueueHandle, pvBuffer, xTicksToWait );
                        }
                    }
                }
            }
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeekImpl( QueueHandle_t xQueue,
                                   ಶೂನ್ಯ * ಧ್ರುವ pvBuffer,
                                   TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueuePeekImpl( QueueHandle_t xQueue,
                                   ಶೂನ್ಯ * ಧ್ರುವ pvBuffer,
                                   TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
        BaseType_t xReturn = pdFAIL;
        BaseType_t xIsReceiveBufferWritable = pdFALSE;
        UBaseType_t uxQueueItemSize;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        lIndex = ( int32_t ) xQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                {
                    uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );

                    ಯದಿ( ( !( ( ( pvBuffer ) == ರಿಕ್ತ ) && ( uxQueueItemSize != ( UBaseType_t ) 0U ) ) )
                        #ಯದಿ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        xIsReceiveBufferWritable = xPortIsAuthorizedToAccessBuffer( pvBuffer,
                                                                                    uxQueueItemSize,
                                                                                    tskMPU_WRITE_PERMISSION );

                        ಯದಿ( xIsReceiveBufferWritable == pdTRUE )
                        {
                            xReturn = xQueuePeek( xInternalQueueHandle, pvBuffer, xTicksToWait );
                        }
                    }
                }
            }
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueSemaphoreTakeImpl( QueueHandle_t xQueue,
                                            TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueSemaphoreTakeImpl( QueueHandle_t xQueue,
                                            TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
        BaseType_t xReturn = pdFAIL;
        UBaseType_t uxQueueItemSize;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        lIndex = ( int32_t ) xQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                {
                    uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );

                    ಯದಿ( ( uxQueueItemSize == 0U )
                        #ಯದಿ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        xReturn = xQueueSemaphoreTake( xInternalQueueHandle, xTicksToWait );
                    }
                }
            }
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolderImpl( QueueHandle_t xSemaphore ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xQueueGetMutexHolderImpl( QueueHandle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xMutexHolderTaskInternalHandle = ರಿಕ್ತ;
            TaskHandle_t xMutexHolderTaskExternalHandle = ರಿಕ್ತ;
            int32_t lIndex, lMutexHolderTaskIndex;
            QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;


            lIndex = ( int32_t ) xSemaphore;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                    {
                        xMutexHolderTaskInternalHandle = xQueueGetMutexHolder( xInternalQueueHandle );

                        ಯದಿ( xMutexHolderTaskInternalHandle != ರಿಕ್ತ )
                        {
                            lMutexHolderTaskIndex = MPU_GetIndexForTaskHandle( xMutexHolderTaskInternalHandle );

                            ಯದಿ( lMutexHolderTaskIndex != -1 )
                            {
                                xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_TO_EXTERNAL_INDEX( lMutexHolderTaskIndex ) );
                            }
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xMutexHolderTaskExternalHandle;
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueTakeMutexRecursiveImpl( QueueHandle_t xMutex,
                                                     TickType_t xBlockTime ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueTakeMutexRecursiveImpl( QueueHandle_t xMutex,
                                                     TickType_t xBlockTime ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
            UBaseType_t uxQueueItemSize;

            lIndex = ( int32_t ) xMutex;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                    {
                        uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );

                        ಯದಿ( uxQueueItemSize == 0 )
                        {
                            xReturn = xQueueTakeMutexRecursive( xInternalQueueHandle, xBlockTime );
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueGiveMutexRecursiveImpl( QueueHandle_t xMutex ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueGiveMutexRecursiveImpl( QueueHandle_t xMutex ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;

            lIndex = ( int32_t ) xMutex;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                    {
                        xReturn = xQueueGiveMutexRecursive( xInternalQueueHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_QUEUE_SETS == 1 )

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetImpl( QueueSetHandle_t xQueueSet,
                                                            TickType_t xBlockTimeTicks ) PRIVILEGED_FUNCTION;

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetImpl( QueueSetHandle_t xQueueSet,
                                                            TickType_t xBlockTimeTicks ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = ರಿಕ್ತ;
            QueueSetMemberHandle_t xSelectedMemberInternal = ರಿಕ್ತ;
            QueueSetMemberHandle_t xSelectedMemberExternal = ರಿಕ್ತ;
            int32_t lIndexQueueSet, lIndexSelectedMember;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSet = pdFALSE;

            lIndexQueueSet = ( int32_t ) xQueueSet;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSet ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueueSet = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessQueueSet == pdTRUE )
                {
                    xInternalQueueSetHandle = MPU_GetQueueSetHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );

                    ಯದಿ( xInternalQueueSetHandle != ರಿಕ್ತ )
                    {
                        xSelectedMemberInternal = xQueueSelectFromSet( xInternalQueueSetHandle, xBlockTimeTicks );

                        ಯದಿ( xSelectedMemberInternal != ರಿಕ್ತ )
                        {
                            lIndexSelectedMember = MPU_GetIndexForQueueSetMemberHandle( xSelectedMemberInternal );

                            ಯದಿ( lIndexSelectedMember != -1 )
                            {
                                xSelectedMemberExternal = ( QueueSetMemberHandle_t ) ( CONVERT_TO_EXTERNAL_INDEX( lIndexSelectedMember ) );
                            }
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xSelectedMemberExternal;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_QUEUE_SETS == 1 )

        BaseType_t MPU_xQueueAddToSetImpl( QueueSetMemberHandle_t xQueueOrSemaphore,
                                           QueueSetHandle_t xQueueSet ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueAddToSetImpl( QueueSetMemberHandle_t xQueueOrSemaphore,
                                           QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            QueueSetMemberHandle_t xInternalQueueSetMemberHandle = ರಿಕ್ತ;
            QueueSetHandle_t xInternalQueueSetHandle = ರಿಕ್ತ;
            int32_t lIndexQueueSet, lIndexQueueSetMember;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSet = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSetMember = pdFALSE;

            lIndexQueueSet = ( int32_t ) xQueueSet;
            lIndexQueueSetMember = ( int32_t ) xQueueOrSemaphore;

            ಯದಿ( ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSet ) != pdFALSE ) &&
                ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSetMember ) != pdFALSE ) )
            {
                xCallingTaskIsAuthorizedToAccessQueueSet = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );
                xCallingTaskIsAuthorizedToAccessQueueSetMember = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSetMember ) );

                ಯದಿ( ( xCallingTaskIsAuthorizedToAccessQueueSet == pdTRUE ) && ( xCallingTaskIsAuthorizedToAccessQueueSetMember == pdTRUE ) )
                {
                    xInternalQueueSetHandle = MPU_GetQueueSetHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );
                    xInternalQueueSetMemberHandle = MPU_GetQueueSetMemberHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSetMember ) );

                    ಯದಿ( ( xInternalQueueSetHandle != ರಿಕ್ತ ) && ( xInternalQueueSetMemberHandle != ರಿಕ್ತ ) )
                    {
                        xReturn = xQueueAddToSet( xInternalQueueSetMemberHandle, xInternalQueueSetHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ configQUEUE_REGISTRY_SIZE > 0

        ಶೂನ್ಯ MPU_vQueueAddToRegistryImpl( QueueHandle_t xQueue,
                                          ಧ್ರುವ ವರ್ಣ * pcName ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_vQueueAddToRegistryImpl( QueueHandle_t xQueue,
                                          ಧ್ರುವ ವರ್ಣ * pcName ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            lIndex = ( int32_t ) xQueue;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                    {
                        vQueueAddToRegistry( xInternalQueueHandle, pcName );
                    }
                }
            }
        }

    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ಯದಿ configQUEUE_REGISTRY_SIZE > 0

        ಶೂನ್ಯ MPU_vQueueUnregisterQueueImpl( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_vQueueUnregisterQueueImpl( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            lIndex = ( int32_t ) xQueue;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                    {
                        vQueueUnregisterQueue( xInternalQueueHandle );
                    }
                }
            }
        }

    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ಯದಿ configQUEUE_REGISTRY_SIZE > 0

        ಧ್ರುವ ವರ್ಣ * MPU_pcQueueGetNameImpl( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

        ಧ್ರುವ ವರ್ಣ * MPU_pcQueueGetNameImpl( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
        {
            ಧ್ರುವ ವರ್ಣ * pcReturn = ರಿಕ್ತ;
            QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            lIndex = ( int32_t ) xQueue;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                    {
                        pcReturn = pcQueueGetName( xInternalQueueHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ pcReturn;
        }

    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Queue APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ MPU_vQueueDelete( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
        int32_t lIndex;

        lIndex = ( int32_t ) xQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
            {
                vQueueDelete( xInternalQueueHandle );
                MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
            }
        }
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateMutex( ಧ್ರುವ uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
            QueueHandle_t xExternalQueueHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueCreateMutex( ucQueueType );

                ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateMutexStatic( ಧ್ರುವ uint8_t ucQueueType,
                                                   StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
            QueueHandle_t xExternalQueueHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );

                ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphore( UBaseType_t ux_ಎಣಿಕೆ_ಮೌಲ್ಯ,
                                                         UBaseType_t ux_Initial_ಎಣಿಕೆ ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
            QueueHandle_t xExternalQueueHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueCreateCountingSemaphore( ux_ಎಣಿಕೆ_ಮೌಲ್ಯ, ux_Initial_ಎಣಿಕೆ );

                ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphoreStatic( ಧ್ರುವ UBaseType_t ux_Max_ಎಣಿಕೆ,
                                                               ಧ್ರುವ UBaseType_t ux_Initial_ಎಣಿಕೆ,
                                                               StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
            QueueHandle_t xExternalQueueHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueCreateCountingSemaphoreStatic( ux_Max_ಎಣಿಕೆ, ux_Initial_ಎಣಿಕೆ, pxStaticQueue );

                ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        QueueHandle_t MPU_xQueueGenericCreate( UBaseType_t uxQueueLength,
                                               UBaseType_t uxItemSize,
                                               uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
            QueueHandle_t xExternalQueueHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueGenericCreate( uxQueueLength, uxItemSize, ucQueueType );

                ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalQueueHandle;
        }

    #endif /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        QueueHandle_t MPU_xQueueGenericCreateStatic( ಧ್ರುವ UBaseType_t uxQueueLength,
                                                     ಧ್ರುವ UBaseType_t uxItemSize,
                                                     uint8_t * pucQueueStorage,
                                                     StaticQueue_t * pxStaticQueue,
                                                     ಧ್ರುವ uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
            QueueHandle_t xExternalQueueHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueGenericCreateStatic( uxQueueLength, uxItemSize, pucQueueStorage, pxStaticQueue, ucQueueType );

                ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalQueueHandle;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericReset( QueueHandle_t xQueue,
                                       BaseType_t xNewQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
        BaseType_t xReturn = pdFAIL;

        lIndex = ( int32_t ) xQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
            {
                xReturn = xQueueGenericReset( xInternalQueueHandle, xNewQueue );
            }
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueSetHandle_t MPU_xQueueCreateSet( UBaseType_t uxEventQueueLength ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = ರಿಕ್ತ;
            QueueSetHandle_t xExternalQueueSetHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xInternalQueueSetHandle = xQueueCreateSet( uxEventQueueLength );

                ಯದಿ( xInternalQueueSetHandle != ರಿಕ್ತ )
                {
                    MPU_StoreQueueSetHandleAtIndex( lIndex, xInternalQueueSetHandle );
                    xExternalQueueSetHandle = ( QueueSetHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalQueueSetHandle;
        }

    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueSetHandle_t MPU_xQueueCreateSetStatic( ಧ್ರುವ UBaseType_t uxEventQueueLength,
                                                    uint8_t * pucQueueStorage,
                                                    StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = ರಿಕ್ತ;
            QueueSetHandle_t xExternalQueueSetHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xInternalQueueSetHandle = xQueueCreateSetStatic( uxEventQueueLength, pucQueueStorage, pxStaticQueue );

                ಯದಿ( xInternalQueueSetHandle != ರಿಕ್ತ )
                {
                    MPU_StoreQueueSetHandleAtIndex( lIndex, xInternalQueueSetHandle );
                    xExternalQueueSetHandle = ( QueueSetHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalQueueSetHandle;
        }

    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_QUEUE_SETS == 1 )

        BaseType_t MPU_xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                            QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            QueueSetMemberHandle_t xInternalQueueSetMemberHandle = ರಿಕ್ತ;
            QueueSetHandle_t xInternalQueueSetHandle = ರಿಕ್ತ;
            int32_t lIndexQueueSet, lIndexQueueSetMember;

            lIndexQueueSet = ( int32_t ) xQueueSet;
            lIndexQueueSetMember = ( int32_t ) xQueueOrSemaphore;

            ಯದಿ( ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSet ) != pdFALSE ) &&
                ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSetMember ) != pdFALSE ) )
            {
                xInternalQueueSetHandle = MPU_GetQueueSetHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );
                xInternalQueueSetMemberHandle = MPU_GetQueueSetMemberHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSetMember ) );

                ಯದಿ( ( xInternalQueueSetHandle != ರಿಕ್ತ ) && ( xInternalQueueSetMemberHandle != ರಿಕ್ತ ) )
                {
                    xReturn = xQueueRemoveFromSet( xInternalQueueSetMemberHandle, xInternalQueueSetHandle );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xQueueGenericGetStaticBuffers( QueueHandle_t xQueue,
                                                      uint8_t ** ppucQueueStorage,
                                                      StaticQueue_t ** ppxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;
            BaseType_t xReturn = pdFALSE;

            lIndex = ( int32_t ) xQueue;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
                {
                    xReturn = xQueueGenericGetStaticBuffers( xInternalQueueHandle, ppucQueueStorage, ppxStaticQueue );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /*if ( configSUPPORT_STATIC_ALLOCATION == 1 )*/
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSendFromISR( QueueHandle_t xQueue,
                                             ಧ್ರುವ ಶೂನ್ಯ * ಧ್ರುವ pvItemToQueue,
                                             BaseType_t * ಧ್ರುವ pxHigherPriorityTaskWoken,
                                             ಧ್ರುವ BaseType_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;

        lIndex = ( int32_t ) xQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
            {
                xReturn = xQueueGenericSendFromISR( xInternalQueueHandle, pvItemToQueue, pxHigherPriorityTaskWoken, xCopyPosition );
            }
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGiveFromISR( QueueHandle_t xQueue,
                                      BaseType_t * ಧ್ರುವ pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;

        lIndex = ( int32_t ) xQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
            {
                xReturn = xQueueGiveFromISR( xInternalQueueHandle, pxHigherPriorityTaskWoken );
            }
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeekFromISR( QueueHandle_t xQueue,
                                      ಶೂನ್ಯ * ಧ್ರುವ pvBuffer ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;

        lIndex = ( int32_t ) xQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
            {
                xReturn = xQueuePeekFromISR( xInternalQueueHandle, pvBuffer );
            }
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceiveFromISR( QueueHandle_t xQueue,
                                         ಶೂನ್ಯ * ಧ್ರುವ pvBuffer,
                                         BaseType_t * ಧ್ರುವ pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;

        lIndex = ( int32_t ) xQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
            {
                xReturn = xQueueReceiveFromISR( xInternalQueueHandle, pvBuffer, pxHigherPriorityTaskWoken );
            }
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueIsQueueEmptyFromISR( ಧ್ರುವ QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;

        lIndex = ( int32_t ) xQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
            {
                xReturn = xQueueIsQueueEmptyFromISR( xInternalQueueHandle );
            }
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueIsQueueFullFromISR( ಧ್ರುವ QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;

        lIndex = ( int32_t ) xQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
            {
                xReturn = xQueueIsQueueFullFromISR( xInternalQueueHandle );
            }
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }

/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaitingFromISR( ಧ್ರುವ QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn = 0;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ರಿಕ್ತ;

        lIndex = ( int32_t ) xQueue;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xInternalQueueHandle != ರಿಕ್ತ )
            {
                uxReturn = uxQueueMessagesWaitingFromISR( xInternalQueueHandle );
            }
        }

        ಪ್ರತ್ಯಾಗಮ uxReturn;
    }

/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolderFromISR( QueueHandle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xMutexHolderTaskInternalHandle = ರಿಕ್ತ;
            TaskHandle_t xMutexHolderTaskExternalHandle = ರಿಕ್ತ;
            int32_t lIndex, lMutexHolderTaskIndex;
            QueueHandle_t xInternalSemaphoreHandle = ರಿಕ್ತ;

            lIndex = ( int32_t ) xSemaphore;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalSemaphoreHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalSemaphoreHandle != ರಿಕ್ತ )
                {
                    xMutexHolderTaskInternalHandle = xQueueGetMutexHolder( xInternalSemaphoreHandle );

                    ಯದಿ( xMutexHolderTaskInternalHandle != ರಿಕ್ತ )
                    {
                        lMutexHolderTaskIndex = MPU_GetIndexForTaskHandle( xMutexHolderTaskInternalHandle );

                        ಯದಿ( lMutexHolderTaskIndex != -1 )
                        {
                            xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_TO_EXTERNAL_INDEX( lMutexHolderTaskIndex ) );
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xMutexHolderTaskExternalHandle;
        }

    #endif /* #if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_QUEUE_SETS == 1 )

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetFromISR( QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = ರಿಕ್ತ;
            QueueSetMemberHandle_t xSelectedMemberInternal = ರಿಕ್ತ;
            QueueSetMemberHandle_t xSelectedMemberExternal = ರಿಕ್ತ;
            int32_t lIndexQueueSet, lIndexSelectedMember;

            lIndexQueueSet = ( int32_t ) xQueueSet;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSet ) != pdFALSE )
            {
                xInternalQueueSetHandle = MPU_GetQueueSetHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );

                ಯದಿ( xInternalQueueSetHandle != ರಿಕ್ತ )
                {
                    xSelectedMemberInternal = xQueueSelectFromSetFromISR( xInternalQueueSetHandle );

                    ಯದಿ( xSelectedMemberInternal != ರಿಕ್ತ )
                    {
                        lIndexSelectedMember = MPU_GetIndexForQueueSetMemberHandle( xSelectedMemberInternal );

                        ಯದಿ( lIndexSelectedMember != -1 )
                        {
                            xSelectedMemberExternal = ( QueueSetMemberHandle_t ) ( CONVERT_TO_EXTERNAL_INDEX( lIndexSelectedMember ) );
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xSelectedMemberExternal;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for timers APIs.                  */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        ಶೂನ್ಯ * MPU_pvTimerGetTimerIDImpl( ಧ್ರುವ TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ * MPU_pvTimerGetTimerIDImpl( ಧ್ರುವ TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ಶೂನ್ಯ * pvReturn = ರಿಕ್ತ;
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                    {
                        pvReturn = pvTimerGetTimerID( xInternalTimerHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ pvReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        ಶೂನ್ಯ MPU_vTimerSetTimerIDImpl( TimerHandle_t xTimer,
                                       ಶೂನ್ಯ * pvNewID ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_vTimerSetTimerIDImpl( TimerHandle_t xTimer,
                                       ಶೂನ್ಯ * pvNewID ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                    {
                        vTimerSetTimerID( xInternalTimerHandle, pvNewID );
                    }
                }
            }
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerIsTimerActiveImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerIsTimerActiveImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                    {
                        xReturn = xTimerIsTimerActive( xInternalTimerHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xReturn;

            xReturn = xTimerGetTimerDaemonTaskHandle();

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ಧ್ರುವ BaseType_t xCommandID,
                                                     ಧ್ರುವ TickType_t x_Optional_ಮೌಲ್ಯ,
                                                     BaseType_t * ಧ್ರುವ pxHigherPriorityTaskWoken,
                                                     ಧ್ರುವ TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn = pdFALSE;
            xTimerGenericCommandFromTaskParams_t xParams;

            xParams.xTimer = xTimer;
            xParams.xCommandID = xCommandID;
            xParams.x_Optional_ಮೌಲ್ಯ = x_Optional_ಮೌಲ್ಯ;
            xParams.pxHigherPriorityTaskWoken = pxHigherPriorityTaskWoken;
            xParams.xTicksToWait = xTicksToWait;

            xReturn = MPU_xTimerGenericCommandFromTaskEntry( &( xParams ) );

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

        BaseType_t MPU_xTimerGenericCommandFromTaskImpl( ಧ್ರುವ xTimerGenericCommandFromTaskParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerGenericCommandFromTaskImpl( ಧ್ರುವ xTimerGenericCommandFromTaskParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xIsHigherPriorityTaskWokenWriteable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            ಯದಿ( pxParams != ರಿಕ್ತ )
            {
                xAreParamsReadable = xPortIsAuthorizedToAccessBuffer( pxParams,
                                                                      ಪರಿಮಾಣ( xTimerGenericCommandFromTaskParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ಯದಿ( xAreParamsReadable == pdTRUE )
            {
                ಯದಿ( pxParams->xCommandID < tmrFIRST_FROM_ISR_COMMAND )
                {
                    ಯದಿ( pxParams->pxHigherPriorityTaskWoken != ರಿಕ್ತ )
                    {
                        xIsHigherPriorityTaskWokenWriteable = xPortIsAuthorizedToAccessBuffer( pxParams->pxHigherPriorityTaskWoken,
                                                                                               ಪರಿಮಾಣ( BaseType_t ),
                                                                                               tskMPU_WRITE_PERMISSION );
                    }

                    ಯದಿ( ( pxParams->pxHigherPriorityTaskWoken == ರಿಕ್ತ ) ||
                        ( xIsHigherPriorityTaskWokenWriteable == pdTRUE ) )
                    {
                        lIndex = ( int32_t ) ( pxParams->xTimer );

                        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                        {
                            xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ಯದಿ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                            {
                                xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                                ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                                {
                                    xReturn = xTimerGenericCommandFromTask( xInternalTimerHandle,
                                                                            pxParams->xCommandID,
                                                                            pxParams->x_Optional_ಮೌಲ್ಯ,
                                                                            pxParams->pxHigherPriorityTaskWoken,
                                                                            pxParams->xTicksToWait );
                                }
                            }
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        ಧ್ರುವ ವರ್ಣ * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ಧ್ರುವ ವರ್ಣ * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ಧ್ರುವ ವರ್ಣ * pcReturn = ರಿಕ್ತ;
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                    {
                        pcReturn = pcTimerGetName( xInternalTimerHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ pcReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        ಶೂನ್ಯ MPU_vTimerSetReloadModeImpl( TimerHandle_t xTimer,
                                          ಧ್ರುವ BaseType_t xAutoReload ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_vTimerSetReloadModeImpl( TimerHandle_t xTimer,
                                          ಧ್ರುವ BaseType_t xAutoReload ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                    {
                        vTimerSetReloadMode( xInternalTimerHandle, xAutoReload );
                    }
                }
            }
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGetReloadModeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerGetReloadModeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                    {
                        xReturn = xTimerGetReloadMode( xInternalTimerHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_uxTimerGetReloadModeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTimerGetReloadModeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                    {
                        uxReturn = uxTimerGetReloadMode( xInternalTimerHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ uxReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                    {
                        xReturn = xTimerGetPeriod( xInternalTimerHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetExpiryTimeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetExpiryTimeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                    {
                        xReturn = xTimerGetExpiryTime( xInternalTimerHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Timer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreate( ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ pcTimerName,
                                        ಧ್ರುವ TickType_t xTimerPeriodInTicks,
                                        ಧ್ರುವ BaseType_t xAutoReload,
                                        ಶೂನ್ಯ * ಧ್ರುವ pvTimerID,
                                        TimerCallbackFunction_t pxCallbackFunction ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            TimerHandle_t xExternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xInternalTimerHandle = xTimerCreate( pcTimerName, xTimerPeriodInTicks, xAutoReload, pvTimerID, MPU_TimerCallback );

                ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                {
                    MPU_StoreTimerHandleAtIndex( lIndex, xInternalTimerHandle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalTimerHandle;
        }

    #endif /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreateStatic( ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ pcTimerName,
                                              ಧ್ರುವ TickType_t xTimerPeriodInTicks,
                                              ಧ್ರುವ BaseType_t xAutoReload,
                                              ಶೂನ್ಯ * ಧ್ರುವ pvTimerID,
                                              TimerCallbackFunction_t pxCallbackFunction,
                                              StaticTimer_t * pxTimerBuffer ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            TimerHandle_t xExternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xInternalTimerHandle = xTimerCreateStatic( pcTimerName, xTimerPeriodInTicks, xAutoReload, pvTimerID, MPU_TimerCallback, pxTimerBuffer );

                ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                {
                    MPU_StoreTimerHandleAtIndex( lIndex, xInternalTimerHandle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalTimerHandle;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGetStaticBuffer( TimerHandle_t xTimer,
                                              StaticTimer_t ** ppxTimerBuffer ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xReturn = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                {
                    xReturn = xTimerGetStaticBuffer( xInternalTimerHandle, ppxTimerBuffer );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGenericCommandFromISR( TimerHandle_t xTimer,
                                                    ಧ್ರುವ BaseType_t xCommandID,
                                                    ಧ್ರುವ TickType_t x_Optional_ಮೌಲ್ಯ,
                                                    BaseType_t * ಧ್ರುವ pxHigherPriorityTaskWoken,
                                                    ಧ್ರುವ TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = ( int32_t ) xTimer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                {
                    xReturn = xTimerGenericCommandFromISR( xInternalTimerHandle, xCommandID, x_Optional_ಮೌಲ್ಯ, pxHigherPriorityTaskWoken, xTicksToWait );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerDelete( TimerHandle_t xTimer, TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = ( int32_t ) xTimer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalTimerHandle != ರಿಕ್ತ )
                {
                    xReturn = xTimerGenericCommandFromTask( xInternalTimerHandle,
                                                            tmrCOMMAND_DELETE,
                                                            0U, /* xOptionalValue */
                                                            ರಿಕ್ತ, /* pxHigherPriorityTaskWoken */
                                                            xTicksToWait );
                    ಯದಿ( xReturn != pdFALSE )
                    {
                        MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for event group APIs.              */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
                                             ಧ್ರುವ EventBits_t uxBitsToWaitFor,
                                             ಧ್ರುವ BaseType_t xClearOnExit,
                                             ಧ್ರುವ BaseType_t xWaitForAllBits,
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

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

        EventBits_t MPU_xEventGroupWaitBitsImpl( ಧ್ರುವ xEventGroupWaitBitsParams_t * pxParams ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupWaitBitsImpl( ಧ್ರುವ xEventGroupWaitBitsParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            ಯದಿ( pxParams != ರಿಕ್ತ )
            {
                xAreParamsReadable = xPortIsAuthorizedToAccessBuffer( pxParams,
                                                                      ಪರಿಮಾಣ( xEventGroupWaitBitsParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ಯದಿ( xAreParamsReadable == pdTRUE )
            {
                ಯದಿ( ( ( pxParams->uxBitsToWaitFor & eventEVENT_BITS_CONTROL_BYTES ) == 0U ) &&
                    ( pxParams->uxBitsToWaitFor != 0U )
                    #ಯದಿ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                        && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( pxParams->xTicksToWait != 0U ) ) )
                    #endif
                    )
                {
                    lIndex = ( int32_t ) ( pxParams->xEventGroup );

                    ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                        {
                            xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ಯದಿ( xInternalEventGroupHandle != ರಿಕ್ತ )
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

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupClearBitsImpl( EventGroupHandle_t xEventGroup,
                                                  ಧ್ರುವ EventBits_t uxBitsToClear ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupClearBitsImpl( EventGroupHandle_t xEventGroup,
                                                  ಧ್ರುವ EventBits_t uxBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            ಯದಿ( ( uxBitsToClear & eventEVENT_BITS_CONTROL_BYTES ) == 0U )
            {
                lIndex = ( int32_t ) xEventGroup;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xInternalEventGroupHandle != ರಿಕ್ತ )
                        {
                            xReturn = xEventGroupClearBits( xInternalEventGroupHandle, uxBitsToClear );
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSetBitsImpl( EventGroupHandle_t xEventGroup,
                                                ಧ್ರುವ EventBits_t uxBitsToSet ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupSetBitsImpl( EventGroupHandle_t xEventGroup,
                                                ಧ್ರುವ EventBits_t uxBitsToSet ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            ಯದಿ( ( uxBitsToSet & eventEVENT_BITS_CONTROL_BYTES ) == 0U )
            {
                lIndex = ( int32_t ) xEventGroup;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xInternalEventGroupHandle != ರಿಕ್ತ )
                        {
                            xReturn = xEventGroupSetBits( xInternalEventGroupHandle, uxBitsToSet );
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSyncImpl( EventGroupHandle_t xEventGroup,
                                             ಧ್ರುವ EventBits_t uxBitsToSet,
                                             ಧ್ರುವ EventBits_t uxBitsToWaitFor,
                                             TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupSyncImpl( EventGroupHandle_t xEventGroup,
                                             ಧ್ರುವ EventBits_t uxBitsToSet,
                                             ಧ್ರುವ EventBits_t uxBitsToWaitFor,
                                             TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            ಯದಿ( ( ( uxBitsToWaitFor & eventEVENT_BITS_CONTROL_BYTES ) == 0U ) &&
                ( uxBitsToWaitFor != 0U )
                #ಯದಿ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                    && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                #endif
                )
            {
                lIndex = ( int32_t ) xEventGroup;

                ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xInternalEventGroupHandle != ರಿಕ್ತ )
                        {
                            xReturn = xEventGroupSync( xInternalEventGroupHandle, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_Group_Get_ಸಂಖ್ಯೆ_Impl( ಶೂನ್ಯ * xEventGroup ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Event_Group_Get_ಸಂಖ್ಯೆ_Impl( ಶೂನ್ಯ * xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            lIndex = ( int32_t ) xEventGroup;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                {
                    xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalEventGroupHandle != ರಿಕ್ತ )
                    {
                        xReturn = ux_Event_Group_Get_ಸಂಖ್ಯೆ( xInternalEventGroupHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        ಶೂನ್ಯ MPU_v_Event_Group_Set_ಸಂಖ್ಯೆ_Impl( ಶೂನ್ಯ * xEventGroup,
                                           UBaseType_t ux_Event_Group_ಸಂಖ್ಯೆ ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_v_Event_Group_Set_ಸಂಖ್ಯೆ_Impl( ಶೂನ್ಯ * xEventGroup,
                                           UBaseType_t ux_Event_Group_ಸಂಖ್ಯೆ ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            lIndex = ( int32_t ) xEventGroup;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                {
                    xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalEventGroupHandle != ರಿಕ್ತ )
                    {
                        v_Event_Group_Set_ಸಂಖ್ಯೆ( xInternalEventGroupHandle, ux_Event_Group_ಸಂಖ್ಯೆ );
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

    #ಯದಿ ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        EventGroupHandle_t MPU_xEventGroupCreate( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = ರಿಕ್ತ;
            EventGroupHandle_t xExternalEventGroupHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xInternalEventGroupHandle = xEventGroupCreate();

                ಯದಿ( xInternalEventGroupHandle != ರಿಕ್ತ )
                {
                    MPU_StoreEventGroupHandleAtIndex( lIndex, xInternalEventGroupHandle );
                    xExternalEventGroupHandle = ( EventGroupHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalEventGroupHandle;
        }

    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        EventGroupHandle_t MPU_xEventGroupCreateStatic( StaticEventGroup_t * pxEventGroupBuffer ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = ರಿಕ್ತ;
            EventGroupHandle_t xExternalEventGroupHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ಯದಿ( lIndex != -1 )
            {
                xInternalEventGroupHandle = xEventGroupCreateStatic( pxEventGroupBuffer );

                ಯದಿ( xInternalEventGroupHandle != ರಿಕ್ತ )
                {
                    MPU_StoreEventGroupHandleAtIndex( lIndex, xInternalEventGroupHandle );
                    xExternalEventGroupHandle = ( EventGroupHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ಅನ್ಯಥಾ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xExternalEventGroupHandle;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )

        ಶೂನ್ಯ MPU_vEventGroupDelete( EventGroupHandle_t xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalEventGroupHandle != ರಿಕ್ತ )
                {
                    vEventGroupDelete( xInternalEventGroupHandle );
                    MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
                }
            }
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        BaseType_t MPU_xEventGroupGetStaticBuffer( EventGroupHandle_t xEventGroup,
                                                   StaticEventGroup_t ** ppxEventGroupBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalEventGroupHandle != ರಿಕ್ತ )
                {
                    xReturn = xEventGroupGetStaticBuffer( xInternalEventGroupHandle, ppxEventGroupBuffer );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        BaseType_t MPU_xEventGroupClearBitsFromISR( EventGroupHandle_t xEventGroup,
                                                    ಧ್ರುವ EventBits_t uxBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalEventGroupHandle != ರಿಕ್ತ )
                {
                    xReturn = xEventGroupClearBitsFromISR( xInternalEventGroupHandle, uxBitsToClear );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        BaseType_t MPU_xEventGroupSetBitsFromISR( EventGroupHandle_t xEventGroup,
                                                  ಧ್ರುವ EventBits_t uxBitsToSet,
                                                  BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalEventGroupHandle != ರಿಕ್ತ )
                {
                    xReturn = xEventGroupSetBitsFromISR( xInternalEventGroupHandle, uxBitsToSet, pxHigherPriorityTaskWoken );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupGetBitsFromISR( EventGroupHandle_t xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalEventGroupHandle != ರಿಕ್ತ )
                {
                    xReturn = xEventGroupGetBitsFromISR( xInternalEventGroupHandle );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for stream buffer APIs.            */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferSendImpl( StreamBufferHandle_t xStreamBuffer,
                                          ಧ್ರುವ ಶೂನ್ಯ * pvTxData,
                                          size_t xDataLengthBytes,
                                          TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferSendImpl( StreamBufferHandle_t xStreamBuffer,
                                          ಧ್ರುವ ಶೂನ್ಯ * pvTxData,
                                          size_t xDataLengthBytes,
                                          TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xIsTxDataBufferReadable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            ಯದಿ( pvTxData != ರಿಕ್ತ )
            {
                xIsTxDataBufferReadable = xPortIsAuthorizedToAccessBuffer( pvTxData,
                                                                           xDataLengthBytes,
                                                                           tskMPU_READ_PERMISSION );

                ಯದಿ( xIsTxDataBufferReadable == pdTRUE )
                {
                    lIndex = ( int32_t ) xStreamBuffer;

                    ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                        {
                            xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                            {
                                xReturn = xStreamBufferSend( xInternalStreamBufferHandle, pvTxData, xDataLengthBytes, xTicksToWait );
                            }
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferReceiveImpl( StreamBufferHandle_t xStreamBuffer,
                                             ಶೂನ್ಯ * pvRxData,
                                             size_t xBufferLengthBytes,
                                             TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferReceiveImpl( StreamBufferHandle_t xStreamBuffer,
                                             ಶೂನ್ಯ * pvRxData,
                                             size_t xBufferLengthBytes,
                                             TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xIsRxDataBufferWriteable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            ಯದಿ( pvRxData != ರಿಕ್ತ )
            {
                xIsRxDataBufferWriteable = xPortIsAuthorizedToAccessBuffer( pvRxData,
                                                                            xBufferLengthBytes,
                                                                            tskMPU_WRITE_PERMISSION );

                ಯದಿ( xIsRxDataBufferWriteable == pdTRUE )
                {
                    lIndex = ( int32_t ) xStreamBuffer;

                    ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ಯದಿ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                        {
                            xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                            {
                                xReturn = xStreamBufferReceive( xInternalStreamBufferHandle, pvRxData, xBufferLengthBytes, xTicksToWait );
                            }
                        }
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferIsFullImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xStreamBufferIsFullImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                    {
                        xReturn = xStreamBufferIsFull( xInternalStreamBufferHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferIsEmptyImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xStreamBufferIsEmptyImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                    {
                        xReturn = xStreamBufferIsEmpty( xInternalStreamBufferHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferSpacesAvailableImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferSpacesAvailableImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                    {
                        xReturn = xStreamBufferSpacesAvailable( xInternalStreamBufferHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferBytesAvailableImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferBytesAvailableImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                    {
                        xReturn = xStreamBufferBytesAvailable( xInternalStreamBufferHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferSetTriggerLevelImpl( StreamBufferHandle_t xStreamBuffer,
                                                         size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xStreamBufferSetTriggerLevelImpl( StreamBufferHandle_t xStreamBuffer,
                                                         size_t xTriggerLevel ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                    {
                        xReturn = xStreamBufferSetTriggerLevel( xInternalStreamBufferHandle, xTriggerLevel );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferNextMessageLengthBytesImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferNextMessageLengthBytesImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                    {
                        xReturn = xStreamBufferNextMessageLengthBytes( xInternalStreamBufferHandle );
                    }
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Stream Buffer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        StreamBufferHandle_t MPU_xStreamBufferGenericCreate( size_t xBufferSizeBytes,
                                                             size_t xTriggerLevelBytes,
                                                             BaseType_t xStreamBufferType,
                                                             StreamBufferCallbackFunction_t pxSendCompletedCallback,
                                                             StreamBufferCallbackFunction_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            StreamBufferHandle_t xExternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ರಿಕ್ತ ) &&
                          ( pxReceiveCompletedCallback == ರಿಕ್ತ ) );

            ಯದಿ( ( pxSendCompletedCallback == ರಿಕ್ತ ) &&
                ( pxReceiveCompletedCallback == ರಿಕ್ತ ) )
            {
                lIndex = MPU_GetFreeIndexInKernelObjectPool();

                ಯದಿ( lIndex != -1 )
                {
                    xInternalStreamBufferHandle = xStreamBufferGenericCreate( xBufferSizeBytes,
                                                                              xTriggerLevelBytes,
                                                                              xStreamBufferType,
                                                                              ರಿಕ್ತ,
                                                                              ರಿಕ್ತ );

                    ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                    {
                        MPU_StoreStreamBufferHandleAtIndex( lIndex, xInternalStreamBufferHandle );
                        xExternalStreamBufferHandle = ( StreamBufferHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                    }
                    ಅನ್ಯಥಾ
                    {
                        MPU_SetIndexFreeInKernelObjectPool( lIndex );
                    }
                }
            }
            ಅನ್ಯಥಾ
            {
                traceSTREAM_BUFFER_CREATE_FAILED( xStreamBufferType );
                xExternalStreamBufferHandle = ರಿಕ್ತ;
            }

            ಪ್ರತ್ಯಾಗಮ xExternalStreamBufferHandle;
        }

    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        StreamBufferHandle_t MPU_xStreamBufferGenericCreateStatic( size_t xBufferSizeBytes,
                                                                   size_t xTriggerLevelBytes,
                                                                   BaseType_t xStreamBufferType,
                                                                   uint8_t * ಧ್ರುವ pucStreamBufferStorageArea,
                                                                   StaticStreamBuffer_t * ಧ್ರುವ pxStaticStreamBuffer,
                                                                   StreamBufferCallbackFunction_t pxSendCompletedCallback,
                                                                   StreamBufferCallbackFunction_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            StreamBufferHandle_t xExternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ರಿಕ್ತ ) &&
                          ( pxReceiveCompletedCallback == ರಿಕ್ತ ) );

            ಯದಿ( ( pxSendCompletedCallback == ರಿಕ್ತ ) &&
                ( pxReceiveCompletedCallback == ರಿಕ್ತ ) )
            {
                lIndex = MPU_GetFreeIndexInKernelObjectPool();

                ಯದಿ( lIndex != -1 )
                {
                    xInternalStreamBufferHandle = xStreamBufferGenericCreateStatic( xBufferSizeBytes,
                                                                                    xTriggerLevelBytes,
                                                                                    xStreamBufferType,
                                                                                    pucStreamBufferStorageArea,
                                                                                    pxStaticStreamBuffer,
                                                                                    ರಿಕ್ತ,
                                                                                    ರಿಕ್ತ );

                    ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                    {
                        MPU_StoreStreamBufferHandleAtIndex( lIndex, xInternalStreamBufferHandle );
                        xExternalStreamBufferHandle = ( StreamBufferHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                    }
                    ಅನ್ಯಥಾ
                    {
                        MPU_SetIndexFreeInKernelObjectPool( lIndex );
                    }
                }
            }
            ಅನ್ಯಥಾ
            {
                traceSTREAM_BUFFER_CREATE_STATIC_FAILED( xReturn, xStreamBufferType );
                xExternalStreamBufferHandle = ರಿಕ್ತ;
            }

            ಪ್ರತ್ಯಾಗಮ xExternalStreamBufferHandle;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        ಶೂನ್ಯ MPU_vStreamBufferDelete( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                {
                    vStreamBufferDelete( xInternalStreamBufferHandle );
                }

                MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
            }
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferReset( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                {
                    xReturn = xStreamBufferReset( xInternalStreamBufferHandle );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        BaseType_t MPU_xStreamBufferGetStaticBuffers( StreamBufferHandle_t xStreamBuffers,
                                                      uint8_t * ppucStreamBufferStorageArea,
                                                      StaticStreamBuffer_t * ppxStaticStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffers;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                {
                    xReturn = MPU_xStreamBufferGetStaticBuffers( xInternalStreamBufferHandle, ppucStreamBufferStorageArea, ppxStaticStreamBuffer );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

    size_t MPU_xStreamBufferSendFromISR( StreamBufferHandle_t xStreamBuffer,
                                         ಧ್ರುವ ಶೂನ್ಯ * pvTxData,
                                         size_t xDataLengthBytes,
                                         BaseType_t * ಧ್ರುವ pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
        int32_t lIndex;

        lIndex = ( int32_t ) xStreamBuffer;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
            {
                xReturn = xStreamBufferSendFromISR( xInternalStreamBufferHandle, pvTxData, xDataLengthBytes, pxHigherPriorityTaskWoken );
            }
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

    size_t MPU_xStreamBufferReceiveFromISR( StreamBufferHandle_t xStreamBuffer,
                                            ಶೂನ್ಯ * pvRxData,
                                            size_t xBufferLengthBytes,
                                            BaseType_t * ಧ್ರುವ pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
        int32_t lIndex;

        lIndex = ( int32_t ) xStreamBuffer;

        ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
            {
                xReturn = xStreamBufferReceiveFromISR( xInternalStreamBufferHandle, pvRxData, xBufferLengthBytes, pxHigherPriorityTaskWoken );
            }
        }

        ಪ್ರತ್ಯಾಗಮ xReturn;
    }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferSendCompletedFromISR( StreamBufferHandle_t xStreamBuffer,
                                                          BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                {
                    xReturn = xStreamBufferSendCompletedFromISR( xInternalStreamBufferHandle, pxHigherPriorityTaskWoken );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferReceiveCompletedFromISR( StreamBufferHandle_t xStreamBuffer,
                                                             BaseType_t * pxHigherPriorityTaskWoken ) /*PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                {
                    xReturn = xStreamBufferReceiveCompletedFromISR( xInternalStreamBufferHandle, pxHigherPriorityTaskWoken );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

    #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferResetFromISR( StreamBufferHandle_t xStreamBuffer ) /*PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            StreamBufferHandle_t xInternalStreamBufferHandle = ರಿಕ್ತ;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            ಯದಿ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ಯದಿ( xInternalStreamBufferHandle != ರಿಕ್ತ )
                {
                    xReturn = xStreamBufferResetFromISR( xInternalStreamBufferHandle );
                }
            }

            ಪ್ರತ್ಯಾಗಮ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h. */

    #ಯದಿ configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #ಅನ್ತರ್ಭಾವ "application_defined_privileged_functions.h"
    #endif
/*-----------------------------------------------------------*/

/**
 * @brief Array of system call implementation functions.
 *
 * The index in the array MUST match the corresponding system call number
 * defined in mpu_wrappers.h.
 */
    PRIVILEGED_DATA UBaseType_t uxSystemCallImplementations[ ಅಂಕೆ_SYSTEM_CALLS ] =
    {
        #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_xTaskGenericNotifyImpl,                     /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyWaitImpl,                 /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #endif

        #ಯದಿ ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_xTimerGenericCommandFromTaskImpl,           /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #endif

        #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_xEventGroupWaitBitsImpl,                    /* SYSTEM_CALL_xEventGroupWaitBits. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupWaitBits. */
        #endif

        /* The system calls above this line take 5 parameters. */

        #ಯದಿ ( INCLUDE_xTaskDelayUntil == 1 )
            ( UBaseType_t ) MPU_xTaskDelayUntilImpl,                        /* SYSTEM_CALL_xTaskDelayUntil. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskDelayUntil. */
        #endif

        #ಯದಿ ( INCLUDE_xTaskAbortDelay == 1 )
            ( UBaseType_t ) MPU_xTaskAbortDelayImpl,                        /* SYSTEM_CALL_xTaskAbortDelay. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskAbortDelay. */
        #endif

        #ಯದಿ ( INCLUDE_vTaskDelay == 1 )
            ( UBaseType_t ) MPU_vTaskDelayImpl,                             /* SYSTEM_CALL_vTaskDelay. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskDelay. */
        #endif

        #ಯದಿ ( INCLUDE_uxTaskPriorityGet == 1 )
            ( UBaseType_t ) MPU_uxTaskPriorityGetImpl,                      /* SYSTEM_CALL_uxTaskPriorityGet. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskPriorityGet. */
        #endif

        #ಯದಿ ( INCLUDE_eTaskGetState == 1 )
            ( UBaseType_t ) MPU_eTaskGetStateImpl,                          /* SYSTEM_CALL_eTaskGetState. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_eTaskGetState. */
        #endif

        #ಯದಿ ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_vTaskGetInfoImpl,                           /* SYSTEM_CALL_vTaskGetInfo. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskGetInfo. */
        #endif

        #ಯದಿ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
            ( UBaseType_t ) MPU_xTaskGetIdleTaskHandleImpl,                 /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #endif

        #ಯದಿ ( INCLUDE_vTaskSuspend == 1 )
            ( UBaseType_t ) MPU_vTaskSuspendImpl,                           /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) MPU_vTaskResumeImpl,                            /* SYSTEM_CALL_vTaskResume. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskResume. */
        #endif

        ( UBaseType_t ) MPU_x_Task_Get_Tick_ಎಣಿಕೆ_Impl,                          /* SYSTEM_CALL_xTaskGetTickCount. */
        ( UBaseType_t ) MPU_ux_Task_Get_ಸಂಖ್ಯೆ_Of_Tasks_Impl,                     /* SYSTEM_CALL_uxTaskGetNumberOfTasks. */

        #ಯದಿ ( configGENERATE_RUN_TIME_STATS == 1 )
            ( UBaseType_t ) MPU_ulTaskGetRunTimeCounterImpl,                /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) MPU_ulTaskGetRunTimePercentImpl,                /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #endif

        #ಯದಿ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
            ( UBaseType_t ) MPU_ulTaskGetIdleRunTimePercentImpl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) MPU_ulTaskGetIdleRunTimeCounterImpl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #endif

        #ಯದಿ ( configUSE_APPLICATION_TASK_TAG == 1 )
            ( UBaseType_t ) MPU_vTaskSetApplicationTaskTagImpl,             /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) MPU_xTaskGetApplicationTaskTagImpl,             /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #endif

        #ಯದಿ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_POINTERS != 0 )
            ( UBaseType_t ) MPU_vTaskSetThreadLocalStoragePointerImpl,      /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) MPU_pvTaskGetThreadLocalStoragePointerImpl,     /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #endif

        #ಯದಿ ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_uxTaskGetSystemStateImpl,                   /* SYSTEM_CALL_uxTaskGetSystemState. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetSystemState. */
        #endif

        #ಯದಿ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark_Impl,            /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #endif

        #ಯದಿ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2 == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2_Impl,           /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #endif

        #ಯದಿ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )
            ( UBaseType_t ) MPU_xTaskGetCurrentTaskHandleImpl,              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #endif

        #ಯದಿ ( INCLUDE_xTaskGetSchedulerState == 1 )
            ( UBaseType_t ) MPU_xTaskGetSchedulerStateImpl,                 /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #endif

        ( UBaseType_t ) MPU_vTaskSetTimeOutStateImpl,                       /* SYSTEM_CALL_vTaskSetTimeOutState. */
        ( UBaseType_t ) MPU_xTaskCheckForTimeOutImpl,                       /* SYSTEM_CALL_xTaskCheckForTimeOut. */

        #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_ulTaskGenericNotifyTakeImpl,                /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyStateClearImpl,           /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear_Impl,          /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #ಅನ್ಯಥಾ
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

        #ಯದಿ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
            ( UBaseType_t ) MPU_xQueueGetMutexHolderImpl,                   /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #endif

        #ಯದಿ ( configUSE_RECURSIVE_MUTEXES == 1 )
            ( UBaseType_t ) MPU_xQueueTakeMutexRecursiveImpl,               /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) MPU_xQueueGiveMutexRecursiveImpl,               /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #endif

        #ಯದಿ ( configUSE_QUEUE_SETS == 1 )
            ( UBaseType_t ) MPU_xQueueSelectFromSetImpl,                    /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) MPU_xQueueAddToSetImpl,                         /* SYSTEM_CALL_xQueueAddToSet. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueAddToSet. */
        #endif

        #ಯದಿ configQUEUE_REGISTRY_SIZE > 0
            ( UBaseType_t ) MPU_vQueueAddToRegistryImpl,                    /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) MPU_vQueueUnregisterQueueImpl,                  /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) MPU_pcQueueGetNameImpl,                         /* SYSTEM_CALL_pcQueueGetName. */
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcQueueGetName. */
        #endif

        #ಯದಿ ( configUSE_TIMERS == 1 )
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
        #ಅನ್ಯಥಾ
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

        #ಯದಿ ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_xEventGroupClearBitsImpl,                   /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) MPU_xEventGroupSetBitsImpl,                     /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) MPU_xEventGroupSyncImpl,                        /* SYSTEM_CALL_xEventGroupSync. */

            #ಯದಿ ( configUSE_TRACE_FACILITY == 1 )
                ( UBaseType_t ) MPU_ux_Event_Group_Get_ಸಂಖ್ಯೆ_Impl,              /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) MPU_v_Event_Group_Set_ಸಂಖ್ಯೆ_Impl,               /* SYSTEM_CALL_vEventGroupSetNumber. */
            #ಅನ್ಯಥಾ
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_vEventGroupSetNumber. */
            #endif
        #ಅನ್ಯಥಾ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSync. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxEventGroupGetNumber. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vEventGroupSetNumber. */
        #endif

        #ಯದಿ ( configUSE_STREAM_BUFFERS == 1 )
            ( UBaseType_t ) MPU_xStreamBufferSendImpl,                      /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) MPU_xStreamBufferReceiveImpl,                   /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) MPU_xStreamBufferIsFullImpl,                    /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) MPU_xStreamBufferIsEmptyImpl,                   /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) MPU_xStreamBufferSpacesAvailableImpl,           /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) MPU_xStreamBufferBytesAvailableImpl,            /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) MPU_xStreamBufferSetTriggerLevelImpl,           /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) MPU_xStreamBufferNextMessageLengthBytesImpl     /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #ಅನ್ಯಥಾ
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
