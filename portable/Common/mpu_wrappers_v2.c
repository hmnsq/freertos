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
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"
#അന്തര്ഭാവ "queue.h"
#അന്തര്ഭാവ "timers.h"
#അന്തര്ഭാവ "event_groups.h"
#അന്തര്ഭാവ "stream_buffer.h"
#അന്തര്ഭാവ "mpu_prototypes.h"
#അന്തര്ഭാവ "mpu_syscall_numbers.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#എങ്കിൽ ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #ifndef configPROTECTED_KERNEL_OBJECT_POOL_SIZE
        #error configPROTECTED_KERNEL_OBJECT_POOL_SIZE must be defined to maximum സംഖ്യ of kernel objects in the application.
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
    ഘടന OpaqueObject;
    തരനിർവചനം ഘടന OpaqueObject * OpaqueObjectHandle_t;

/**
 * @brief Defines kernel object in the kernel object pool.
 */
    തരനിർവചനം ഘടന KernelObject
    {
        OpaqueObjectHandle_t xInternalObjectHandle;
        uint32_t ulKernelObjectType;
        ശൂന്യം * pvKernelObjectData;
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
    സ്ഥിതം int32_t MPU_GetFreeIndexInKernelObjectPool( ശൂന്യം ) PRIVILEGED_FUNCTION;

/**
 * @brief Set the given index as free in the kernel object pool.
 *
 * @param lIndex The index to set as free.
 */
    സ്ഥിതം ശൂന്യം MPU_SetIndexFreeInKernelObjectPool( int32_t lIndex ) PRIVILEGED_FUNCTION;

/**
 * @brief Get the index at which a given kernel object is stored.
 *
 * @param xHandle The given kernel object handle.
 * @param ulKernelObjectType The kernel object type.
 *
 * @return Index at which the kernel object is stored if it is a valid
 *         handle, -1 otherwise.
 */
    സ്ഥിതം int32_t MPU_GetIndexForHandle( OpaqueObjectHandle_t xHandle,
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
    സ്ഥിതം ശൂന്യം MPU_StoreHandleAndDataAtIndex( int32_t lIndex,
                                               OpaqueObjectHandle_t xHandle,
                                               ശൂന്യം * pvKernelObjectData,
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
    സ്ഥിതം OpaqueObjectHandle_t MPU_GetHandleAtIndex( int32_t lIndex,
                                                      uint32_t ulKernelObjectType ) PRIVILEGED_FUNCTION;

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

/**
 * @brief The function registered as callback for all the timers.
 *
 * We intercept all the timer callbacks so that we can call application
 * callbacks with opaque handle.
 *
 * @param xInternalHandle The internal timer handle.
 */
        സ്ഥിതം ശൂന്യം MPU_TimerCallback( TimerHandle_t xInternalHandle ) PRIVILEGED_FUNCTION;

    #endif /* #if ( configUSE_TIMERS == 1 ) */

/*
 * Wrappers to keep all the casting in one place.
 */
    #define MPU_StoreQueueHandleAtIndex( lIndex, xHandle )                 MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), ശൂന്യ, KERNEL_OBJECT_TYPE_QUEUE )
    #define MPU_GetQueueHandleAtIndex( lIndex )                            ( QueueHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_QUEUE )

    #എങ്കിൽ ( configUSE_QUEUE_SETS == 1 )
        #define MPU_StoreQueueSetHandleAtIndex( lIndex, xHandle )          MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), ശൂന്യ, KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_GetQueueSetHandleAtIndex( lIndex )                     ( QueueSetHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_StoreQueueSetMemberHandleAtIndex( lIndex, xHandle )    MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), ശൂന്യ, KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_GetQueueSetMemberHandleAtIndex( lIndex )               ( QueueSetMemberHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_GetIndexForQueueSetMemberHandle( xHandle )             MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_QUEUE )
    #endif

/*
 * Wrappers to keep all the casting in one place for Task APIs.
 */
    #define MPU_StoreTaskHandleAtIndex( lIndex, xHandle )            MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), ശൂന്യ, KERNEL_OBJECT_TYPE_TASK )
    #define MPU_GetTaskHandleAtIndex( lIndex )                       ( TaskHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_TASK )
    #define MPU_GetIndexForTaskHandle( xHandle )                     MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TASK )

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )
/*
 * Wrappers to keep all the casting in one place for Event Group APIs.
 */
        #define MPU_StoreEventGroupHandleAtIndex( lIndex, xHandle )      MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), ശൂന്യ, KERNEL_OBJECT_TYPE_EVENT_GROUP )
        #define MPU_GetEventGroupHandleAtIndex( lIndex )                 ( EventGroupHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_EVENT_GROUP )
        #define MPU_GetIndexForEventGroupHandle( xHandle )               MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_EVENT_GROUP )

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Stream Buffer APIs.
 */
        #define MPU_StoreStreamBufferHandleAtIndex( lIndex, xHandle )    MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle), ശൂന്യ, KERNEL_OBJECT_TYPE_STREAM_BUFFER )
        #define MPU_GetStreamBufferHandleAtIndex( lIndex )               ( StreamBufferHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_STREAM_BUFFER )
        #define MPU_GetIndexForStreamBufferHandle( xHandle )             MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_STREAM_BUFFER )

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

    #എങ്കിൽ ( configUSE_TIMERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Timer APIs.
 */
        #define MPU_StoreTimerHandleAtIndex( lIndex, xHandle, pxApplicationCallback )    MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), ( ശൂന്യം * ) ( pxApplicationCallback ), KERNEL_OBJECT_TYPE_TIMER )
        #define MPU_GetTimerHandleAtIndex( lIndex )                                      ( TimerHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_TIMER )
        #define MPU_GetIndexForTimerHandle( xHandle )                                    MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TIMER )

    #endif /* #if ( configUSE_TIMERS == 1 ) */

/*-----------------------------------------------------------*/

/**
 * @brief Kernel object pool.
 */
    PRIVILEGED_DATA സ്ഥിതം KernelObject_t xKernelObjectPool[ configPROTECTED_KERNEL_OBJECT_POOL_SIZE ] = { 0 };
/*-----------------------------------------------------------*/

    സ്ഥിതം int32_t MPU_GetFreeIndexInKernelObjectPool( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, lFreeIndex = -1;

        /* This function is called only from resource create APIs
         * which are not supposed to be called from ISRs. Therefore,
         * we only need to suspend the scheduler and do not require
         * critical section. */
        vTaskSuspendAll();
        {
            വേണ്ടി( i = 0; i < configPROTECTED_KERNEL_OBJECT_POOL_SIZE; i++ )
            {
                എങ്കിൽ( xKernelObjectPool[ i ].xInternalObjectHandle == ശൂന്യ )
                {
                    /* Mark this index as not free. */
                    xKernelObjectPool[ i ].xInternalObjectHandle = ( OpaqueObjectHandle_t ) ( ~0U );
                    lFreeIndex = i;
                    നിർത്തുക;
                }
            }
        }
        ( ശൂന്യം ) xTaskResumeAll();

        തിരികെ lFreeIndex;
    }
/*-----------------------------------------------------------*/

    സ്ഥിതം ശൂന്യം MPU_SetIndexFreeInKernelObjectPool( int32_t lIndex ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_INTERNAL_INDEX_VALID( lIndex ) != pdFALSE );

        taskENTER_CRITICAL();
        {
            xKernelObjectPool[ lIndex ].xInternalObjectHandle = ശൂന്യ;
            xKernelObjectPool[ lIndex ].ulKernelObjectType = KERNEL_OBJECT_TYPE_INVALID;
            xKernelObjectPool[ lIndex ].pvKernelObjectData = ശൂന്യ;
        }
        taskEXIT_CRITICAL();
    }
/*-----------------------------------------------------------*/

    സ്ഥിതം int32_t MPU_GetIndexForHandle( OpaqueObjectHandle_t xHandle,
                                          uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, lIndex = -1;

        configASSERT( xHandle != ശൂന്യ );

        വേണ്ടി( i = 0; i < configPROTECTED_KERNEL_OBJECT_POOL_SIZE; i++ )
        {
            എങ്കിൽ( ( xKernelObjectPool[ i ].xInternalObjectHandle == xHandle ) &&
                ( xKernelObjectPool[ i ].ulKernelObjectType == ulKernelObjectType ) )
            {
                lIndex = i;
                നിർത്തുക;
            }
        }

        തിരികെ lIndex;
    }
/*-----------------------------------------------------------*/

    സ്ഥിതം ശൂന്യം MPU_StoreHandleAndDataAtIndex( int32_t lIndex,
                                               OpaqueObjectHandle_t xHandle,
                                               ശൂന്യം * pvKernelObjectData,
                                               uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_INTERNAL_INDEX_VALID( lIndex ) != pdFALSE );
        xKernelObjectPool[ lIndex ].xInternalObjectHandle = xHandle;
        xKernelObjectPool[ lIndex ].ulKernelObjectType = ulKernelObjectType;
        xKernelObjectPool[ lIndex ].pvKernelObjectData = pvKernelObjectData;
    }
/*-----------------------------------------------------------*/

    സ്ഥിതം OpaqueObjectHandle_t MPU_GetHandleAtIndex( int32_t lIndex,
                                                      uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        OpaqueObjectHandle_t xObjectHandle = ശൂന്യ;

        configASSERT( IS_INTERNAL_INDEX_VALID( lIndex ) != pdFALSE );

        എങ്കിൽ( xKernelObjectPool[ lIndex ].ulKernelObjectType == ulKernelObjectType )
        {
            xObjectHandle = xKernelObjectPool[ lIndex ].xInternalObjectHandle;
        }

        തിരികെ xObjectHandle;
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ശൂന്യം vGrantAccessToKernelObject( TaskHandle_t xExternalTaskHandle,
                                         int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lExternalTaskIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                എങ്കിൽ( xExternalTaskHandle == ശൂന്യ )
                {
                    vPortGrantAccessToKernelObject( xExternalTaskHandle, CONVERT_TO_INTERNAL_INDEX( lExternalKernelObjectHandle ) );
                }
                അല്ലെങ്കിൽ
                {
                    lExternalTaskIndex = ( int32_t ) xExternalTaskHandle;

                    എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lExternalTaskIndex ) != pdFALSE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lExternalTaskIndex ) );

                        എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
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

    #എങ്കിൽ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ശൂന്യം vRevokeAccessToKernelObject( TaskHandle_t xExternalTaskHandle,
                                          int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lExternalTaskIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                എങ്കിൽ( xExternalTaskHandle == ശൂന്യ )
                {
                    vPortRevokeAccessToKernelObject( xExternalTaskHandle, CONVERT_TO_INTERNAL_INDEX( lExternalKernelObjectHandle ) );
                }
                അല്ലെങ്കിൽ
                {
                    lExternalTaskIndex = ( int32_t ) xExternalTaskHandle;

                    എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lExternalTaskIndex ) != pdFALSE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lExternalTaskIndex ) );

                        എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
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

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        സ്ഥിതം ശൂന്യം MPU_TimerCallback( TimerHandle_t xInternalHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t i, lIndex = -1;
            TimerHandle_t xExternalHandle = ശൂന്യ;
            TimerCallbackFunction_t pxApplicationCallBack = ശൂന്യ;

            /* Coming from the timer task and therefore, should be valid. */
            configASSERT( xInternalHandle != ശൂന്യ );

            വേണ്ടി( i = 0; i < configPROTECTED_KERNEL_OBJECT_POOL_SIZE; i++ )
            {
                എങ്കിൽ( ( ( TimerHandle_t ) xKernelObjectPool[ i ].xInternalObjectHandle == xInternalHandle ) &&
                    ( xKernelObjectPool[ i ].ulKernelObjectType == KERNEL_OBJECT_TYPE_TIMER ) )
                {
                    lIndex = i;
                    നിർത്തുക;
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

    #എങ്കിൽ ( INCLUDE_xTaskDelayUntil == 1 )

        BaseType_t MPU_xTaskDelayUntilImpl( TickType_t * സ്ഥിരം pxPreviousWakeTime,
                                            TickType_t xTimeIncrement ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskDelayUntilImpl( TickType_t * സ്ഥിരം pxPreviousWakeTime,
                                            TickType_t xTimeIncrement ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xIsPreviousWakeTimeAccessible = pdFALSE;

            എങ്കിൽ( ( pxPreviousWakeTime != ശൂന്യ ) && ( xTimeIncrement > 0U ) )
            {
                xIsPreviousWakeTimeAccessible = xPortIsAuthorizedToAccessBuffer( pxPreviousWakeTime,
                                                                                 വലുപ്പം( TickType_t ),
                                                                                 ( tskMPU_WRITE_PERMISSION | tskMPU_READ_PERMISSION ) );

                എങ്കിൽ( xIsPreviousWakeTimeAccessible == pdTRUE )
                {
                    xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_xTaskAbortDelay == 1 )

        BaseType_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = ( int32_t ) xTask;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                    {
                        xReturn = xTaskAbortDelay( xInternalTaskHandle );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_vTaskDelay == 1 )

        ശൂന്യം MPU_vTaskDelayImpl( TickType_t xTicksToDelay ) PRIVILEGED_FUNCTION;

        ശൂന്യം MPU_vTaskDelayImpl( TickType_t xTicksToDelay ) /* PRIVILEGED_FUNCTION */
        {
            vTaskDelay( xTicksToDelay );
        }

    #endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_uxTaskPriorityGet == 1 )

        UBaseType_t MPU_uxTaskPriorityGetImpl( സ്ഥിരം TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskPriorityGetImpl( സ്ഥിരം TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;

            എങ്കിൽ( pxTask == ശൂന്യ )
            {
                uxReturn = uxTaskPriorityGet( pxTask );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) pxTask;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                        {
                            uxReturn = uxTaskPriorityGet( xInternalTaskHandle );
                        }
                    }
                }
            }

            തിരികെ uxReturn;
        }

    #endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            eTaskState eReturn = eInvalid;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            lIndex = ( int32_t ) pxTask;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                    {
                        eReturn = eTaskGetState( xInternalTaskHandle );
                    }
                }
            }

            തിരികെ eReturn;
        }

    #endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TRACE_FACILITY == 1 )

        ശൂന്യം MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   TaskStatus_t * pxTaskStatus,
                                   BaseType_t x_Get_Free_അട്ടി_Space,
                                   eTaskState eState ) PRIVILEGED_FUNCTION;

        ശൂന്യം MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   TaskStatus_t * pxTaskStatus,
                                   BaseType_t x_Get_Free_അട്ടി_Space,
                                   eTaskState eState ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            BaseType_t xIsTaskStatusWriteable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            xIsTaskStatusWriteable = xPortIsAuthorizedToAccessBuffer( pxTaskStatus,
                                                                      വലുപ്പം( TaskStatus_t ),
                                                                      tskMPU_WRITE_PERMISSION );

            എങ്കിൽ( xIsTaskStatusWriteable == pdTRUE )
            {
                എങ്കിൽ( xTask == ശൂന്യ )
                {
                    vTaskGetInfo( xTask, pxTaskStatus, x_Get_Free_അട്ടി_Space, eState );
                }
                അല്ലെങ്കിൽ
                {
                    lIndex = ( int32_t ) xTask;

                    എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                            {
                                vTaskGetInfo( xInternalTaskHandle, pxTaskStatus, x_Get_Free_അട്ടി_Space, eState );
                            }
                        }
                    }
                }
            }
        }

    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( ശൂന്യം ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xIdleTaskHandle = ശൂന്യ;

            xIdleTaskHandle = xTaskGetIdleTaskHandle();

            തിരികെ xIdleTaskHandle;
        }

    #endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_vTaskSuspend == 1 )

        ശൂന്യം MPU_vTaskSuspendImpl( TaskHandle_t pxTaskToSuspend ) PRIVILEGED_FUNCTION;

        ശൂന്യം MPU_vTaskSuspendImpl( TaskHandle_t pxTaskToSuspend ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            എങ്കിൽ( pxTaskToSuspend == ശൂന്യ )
            {
                vTaskSuspend( pxTaskToSuspend );
            }
            അല്ലെങ്കിൽ
            {
                /* After the scheduler starts, only privileged tasks are allowed
                 * to suspend other tasks. */
                #എങ്കിൽ ( INCLUDE_xTaskGetSchedulerState == 1 )
                    എങ്കിൽ( ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) || ( portIS_TASK_PRIVILEGED() == pdTRUE ) )
                #അല്ലെങ്കിൽ
                    എങ്കിൽ( portIS_TASK_PRIVILEGED() == pdTRUE )
                #endif
                {
                    lIndex = ( int32_t ) pxTaskToSuspend;

                    എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
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

    #എങ്കിൽ ( INCLUDE_vTaskSuspend == 1 )

        ശൂന്യം MPU_vTaskResumeImpl( TaskHandle_t pxTaskToResume ) PRIVILEGED_FUNCTION;

        ശൂന്യം MPU_vTaskResumeImpl( TaskHandle_t pxTaskToResume ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            lIndex = ( int32_t ) pxTaskToResume;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                    {
                        vTaskResume( xInternalTaskHandle );
                    }
                }
            }
        }

    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_എണ്ണം_Impl( ശൂന്യം ) PRIVILEGED_FUNCTION;

    TickType_t MPU_x_Task_Get_Tick_എണ്ണം_Impl( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
    {
        TickType_t xReturn;

        xReturn = x_Task_Get_Tick_എണ്ണം();

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_സംഖ്യ_Of_Tasks_Impl( ശൂന്യം ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Task_Get_സംഖ്യ_Of_Tasks_Impl( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn;

        uxReturn = ux_Task_Get_സംഖ്യ_Of_Tasks();

        തിരികെ uxReturn;
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configGENERATE_RUN_TIME_STATS == 1 )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimeCounterImpl( സ്ഥിരം TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimeCounterImpl( സ്ഥിരം TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            configRUN_TIME_COUNTER_TYPE xReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            എങ്കിൽ( xTask == ശൂന്യ )
            {
                xReturn = ulTaskGetRunTimeCounter( xTask );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) xTask;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                        {
                            xReturn = ulTaskGetRunTimeCounter( xInternalTaskHandle );
                        }
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configGENERATE_RUN_TIME_STATS == 1 )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimePercentImpl( സ്ഥിരം TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimePercentImpl( സ്ഥിരം TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            configRUN_TIME_COUNTER_TYPE xReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            എങ്കിൽ( xTask == ശൂന്യ )
            {
                xReturn = ulTaskGetRunTimePercent( xTask );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) xTask;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                        {
                            xReturn = ulTaskGetRunTimePercent( xInternalTaskHandle );
                        }
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercentImpl( ശൂന്യം ) PRIVILEGED_FUNCTION;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercentImpl( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
        {
            configRUN_TIME_COUNTER_TYPE xReturn;

            xReturn = ulTaskGetIdleRunTimePercent();

            തിരികെ xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounterImpl( ശൂന്യം ) PRIVILEGED_FUNCTION;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounterImpl( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
        {
            configRUN_TIME_COUNTER_TYPE xReturn;

            xReturn = ulTaskGetIdleRunTimeCounter();

            തിരികെ xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_APPLICATION_TASK_TAG == 1 )

        ശൂന്യം MPU_vTaskSetApplicationTaskTagImpl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_Tag_മൂല്യം ) PRIVILEGED_FUNCTION;

        ശൂന്യം MPU_vTaskSetApplicationTaskTagImpl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_Tag_മൂല്യം ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            എങ്കിൽ( xTask == ശൂന്യ )
            {
                vTaskSetApplicationTaskTag( xTask, px_Tag_മൂല്യം );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) xTask;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                        {
                            vTaskSetApplicationTaskTag( xInternalTaskHandle, px_Tag_മൂല്യം );
                        }
                    }
                }
            }
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_APPLICATION_TASK_TAG == 1 )

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = ശൂന്യ;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            എങ്കിൽ( xTask == ശൂന്യ )
            {
                xReturn = xTaskGetApplicationTaskTag( xTask );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) xTask;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                        {
                            xReturn = xTaskGetApplicationTaskTag( xInternalTaskHandle );
                        }
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( config_അക്കം_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        ശൂന്യം MPU_vTaskSetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToSet,
                                                        BaseType_t xIndex,
                                                        ശൂന്യം * pv_മൂല്യം ) PRIVILEGED_FUNCTION;

        ശൂന്യം MPU_vTaskSetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToSet,
                                                        BaseType_t xIndex,
                                                        ശൂന്യം * pv_മൂല്യം ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            എങ്കിൽ( xTaskToSet == ശൂന്യ )
            {
                vTaskSetThreadLocalStoragePointer( xTaskToSet, xIndex, pv_മൂല്യം );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) xTaskToSet;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                        {
                            vTaskSetThreadLocalStoragePointer( xInternalTaskHandle, xIndex, pv_മൂല്യം );
                        }
                    }
                }
            }
        }

    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( config_അക്കം_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        ശൂന്യം * MPU_pvTaskGetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToQuery,
                                                           BaseType_t xIndex ) PRIVILEGED_FUNCTION;

        ശൂന്യം * MPU_pvTaskGetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToQuery,
                                                           BaseType_t xIndex ) /* PRIVILEGED_FUNCTION */
        {
            ശൂന്യം * pvReturn = ശൂന്യ;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            എങ്കിൽ( xTaskToQuery == ശൂന്യ )
            {
                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, xIndex );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) xTaskToQuery;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                        {
                            pvReturn = pvTaskGetThreadLocalStoragePointer( xInternalTaskHandle, xIndex );
                        }
                    }
                }
            }

            തിരികെ pvReturn;
        }

    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TRACE_FACILITY == 1 )

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

            എങ്കിൽ( mpuMULTIPLY_BASETYPE_WILL_OVERFLOW( വലുപ്പം( TaskStatus_t ), uxArraySize ) == 0 )
            {
                xIsTaskStatusArrayWriteable = xPortIsAuthorizedToAccessBuffer( pxTaskStatusArray,
                                                                               വലുപ്പം( TaskStatus_t ) * ( size_t ) uxArraySize,
                                                                               tskMPU_WRITE_PERMISSION );

                എങ്കിൽ( pulTotalRunTime != ശൂന്യ )
                {
                    xIsTotalRunTimeWriteable = xPortIsAuthorizedToAccessBuffer( pulTotalRunTime,
                                                                                വലുപ്പം( configRUN_TIME_COUNTER_TYPE ),
                                                                                tskMPU_WRITE_PERMISSION );
                }

                എങ്കിൽ( ( xIsTaskStatusArrayWriteable == pdTRUE ) &&
                    ( ( pulTotalRunTime == ശൂന്യ ) || ( xIsTotalRunTimeWriteable == pdTRUE ) ) )
                {
                    uxReturn = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, pulTotalRunTime );
                }
            }

            തിരികെ uxReturn;
        }

    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            എങ്കിൽ( xTask == ശൂന്യ )
            {
                uxReturn = ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark( xTask );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) xTask;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                        {
                            uxReturn = ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark( xInternalTaskHandle );
                        }
                    }
                }
            }

            തിരികെ uxReturn;
        }

    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2 == 1 )

        config_അട്ടി_DEPTH_TYPE MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_അട്ടി_DEPTH_TYPE MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_അട്ടി_DEPTH_TYPE uxReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            എങ്കിൽ( xTask == ശൂന്യ )
            {
                uxReturn = ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2( xTask );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) xTask;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                        {
                            uxReturn = ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2( xInternalTaskHandle );
                        }
                    }
                }
            }

            തിരികെ uxReturn;
        }

    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( ശൂന്യം ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            TaskHandle_t xExternalTaskHandle = ശൂന്യ;
            int32_t lIndex;

            xInternalTaskHandle = xTaskGetCurrentTaskHandle();

            എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
            {
                lIndex = MPU_GetIndexForTaskHandle( xInternalTaskHandle );

                എങ്കിൽ( lIndex != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
            }

            തിരികെ xExternalTaskHandle;
        }

    #endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_xTaskGetSchedulerState == 1 )

        BaseType_t MPU_xTaskGetSchedulerStateImpl( ശൂന്യം ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGetSchedulerStateImpl( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = taskSCHEDULER_NOT_STARTED;

            xReturn = xTaskGetSchedulerState();

            തിരികെ xReturn;
        }

    #endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    ശൂന്യം MPU_vTaskSetTimeOutStateImpl( TimeOut_t * സ്ഥിരം pxTimeOut ) PRIVILEGED_FUNCTION;

    ശൂന്യം MPU_vTaskSetTimeOutStateImpl( TimeOut_t * സ്ഥിരം pxTimeOut ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xIsTimeOutWriteable = pdFALSE;

        എങ്കിൽ( pxTimeOut != ശൂന്യ )
        {
            xIsTimeOutWriteable = xPortIsAuthorizedToAccessBuffer( pxTimeOut,
                                                                   വലുപ്പം( TimeOut_t ),
                                                                   tskMPU_WRITE_PERMISSION );

            എങ്കിൽ( xIsTimeOutWriteable == pdTRUE )
            {
                vTaskSetTimeOutState( pxTimeOut );
            }
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCheckForTimeOutImpl( TimeOut_t * സ്ഥിരം pxTimeOut,
                                             TickType_t * സ്ഥിരം pxTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xTaskCheckForTimeOutImpl( TimeOut_t * സ്ഥിരം pxTimeOut,
                                             TickType_t * സ്ഥിരം pxTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFALSE;
        BaseType_t xIsTimeOutWriteable = pdFALSE;
        BaseType_t xIsTicksToWaitWriteable = pdFALSE;

        എങ്കിൽ( ( pxTimeOut != ശൂന്യ ) && ( pxTicksToWait != ശൂന്യ ) )
        {
            xIsTimeOutWriteable = xPortIsAuthorizedToAccessBuffer( pxTimeOut,
                                                                   വലുപ്പം( TimeOut_t ),
                                                                   tskMPU_WRITE_PERMISSION );
            xIsTicksToWaitWriteable = xPortIsAuthorizedToAccessBuffer( pxTicksToWait,
                                                                       വലുപ്പം( TickType_t ),
                                                                       tskMPU_WRITE_PERMISSION );

            എങ്കിൽ( ( xIsTimeOutWriteable == pdTRUE ) && ( xIsTicksToWaitWriteable == pdTRUE ) )
            {
                xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
            }
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotify( TaskHandle_t xTaskToNotify,
                                           UBaseType_t uxIndexToNotify,
                                           uint32_t ul_മൂല്യം,
                                           eNotifyAction eAction,
                                           uint32_t * pul_Previous_Notification_മൂല്യം ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn = pdFAIL;
            xTaskGenericNotifyParams_t xParams;

            xParams.xTaskToNotify = xTaskToNotify;
            xParams.uxIndexToNotify = uxIndexToNotify;
            xParams.ul_മൂല്യം = ul_മൂല്യം;
            xParams.eAction = eAction;
            xParams.pul_Previous_Notification_മൂല്യം = pul_Previous_Notification_മൂല്യം;

            xReturn = MPU_xTaskGenericNotifyEntry( &( xParams ) );

            തിരികെ xReturn;
        }

        BaseType_t MPU_xTaskGenericNotifyImpl( സ്ഥിരം xTaskGenericNotifyParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyImpl( സ്ഥിരം xTaskGenericNotifyParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            BaseType_t x_Is_Previous_Notification_മൂല്യം_Writeable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            എങ്കിൽ( pxParams != ശൂന്യ )
            {
                xAreParamsReadable = xPortIsAuthorizedToAccessBuffer( pxParams,
                                                                      വലുപ്പം( xTaskGenericNotifyParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            എങ്കിൽ( xAreParamsReadable == pdTRUE )
            {
                എങ്കിൽ( ( pxParams->uxIndexToNotify < configTASK_NOTIFICATION_ARRAY_ENTRIES ) &&
                    ( ( pxParams->eAction == eNoAction ) ||
                      ( pxParams->eAction == eSetBits ) ||
                      ( pxParams->eAction == eIncrement ) ||
                      ( pxParams->eAction == e_Set_മൂല്യം_With_Overwrite ) ||
                      ( pxParams->eAction == e_Set_മൂല്യം_Without_Overwrite ) ) )
                {
                    എങ്കിൽ( pxParams->pul_Previous_Notification_മൂല്യം != ശൂന്യ )
                    {
                        x_Is_Previous_Notification_മൂല്യം_Writeable = xPortIsAuthorizedToAccessBuffer( pxParams->pul_Previous_Notification_മൂല്യം,
                                                                                                 വലുപ്പം( uint32_t ),
                                                                                                 tskMPU_WRITE_PERMISSION );
                    }

                    എങ്കിൽ( ( pxParams->pul_Previous_Notification_മൂല്യം == ശൂന്യ ) ||
                        ( x_Is_Previous_Notification_മൂല്യം_Writeable == pdTRUE ) )
                    {
                        lIndex = ( int32_t ) ( pxParams->xTaskToNotify );

                        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                        {
                            xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                            {
                                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                                എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                                {
                                    xReturn = xTaskGenericNotify( xInternalTaskHandle,
                                                                  pxParams->uxIndexToNotify,
                                                                  pxParams->ul_മൂല്യം,
                                                                  pxParams->eAction,
                                                                  pxParams->pul_Previous_Notification_മൂല്യം );
                                }
                            }
                        }
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyWait( UBaseType_t uxIndexToWaitOn,
                                               uint32_t ulBitsToClearOnEntry,
                                               uint32_t ulBitsToClearOnExit,
                                               uint32_t * pul_Notification_മൂല്യം,
                                               TickType_t xTicksToWait )
        {
            BaseType_t xReturn = pdFAIL;
            xTaskGenericNotifyWaitParams_t xParams;

            xParams.uxIndexToWaitOn = uxIndexToWaitOn;
            xParams.ulBitsToClearOnEntry = ulBitsToClearOnEntry;
            xParams.ulBitsToClearOnExit = ulBitsToClearOnExit;
            xParams.pul_Notification_മൂല്യം = pul_Notification_മൂല്യം;
            xParams.xTicksToWait = xTicksToWait;

            xReturn = MPU_xTaskGenericNotifyWaitEntry( &( xParams ) );

            തിരികെ xReturn;
        }

        BaseType_t MPU_xTaskGenericNotifyWaitImpl( സ്ഥിരം xTaskGenericNotifyWaitParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyWaitImpl( സ്ഥിരം xTaskGenericNotifyWaitParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t x_Is_Notification_മൂല്യം_Writable = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            എങ്കിൽ( pxParams != ശൂന്യ )
            {
                xAreParamsReadable = xPortIsAuthorizedToAccessBuffer( pxParams,
                                                                      വലുപ്പം( xTaskGenericNotifyWaitParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            എങ്കിൽ( xAreParamsReadable == pdTRUE )
            {
                എങ്കിൽ( pxParams->uxIndexToWaitOn < configTASK_NOTIFICATION_ARRAY_ENTRIES )
                {
                    എങ്കിൽ( pxParams->pul_Notification_മൂല്യം != ശൂന്യ )
                    {
                        x_Is_Notification_മൂല്യം_Writable = xPortIsAuthorizedToAccessBuffer( pxParams->pul_Notification_മൂല്യം,
                                                                                        വലുപ്പം( uint32_t ),
                                                                                        tskMPU_WRITE_PERMISSION );
                    }

                    എങ്കിൽ( ( pxParams->pul_Notification_മൂല്യം == ശൂന്യ ) ||
                        ( x_Is_Notification_മൂല്യം_Writable == pdTRUE ) )
                    {
                        xReturn = xTaskGenericNotifyWait( pxParams->uxIndexToWaitOn,
                                                          pxParams->ulBitsToClearOnEntry,
                                                          pxParams->ulBitsToClearOnExit,
                                                          pxParams->pul_Notification_മൂല്യം,
                                                          pxParams->xTicksToWait );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t uxIndexToWaitOn,
                                                  BaseType_t x_Clear_എണ്ണം_On_Exit,
                                                  TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t uxIndexToWaitOn,
                                                  BaseType_t x_Clear_എണ്ണം_On_Exit,
                                                  TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;

            എങ്കിൽ( uxIndexToWaitOn < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ulReturn = ulTaskGenericNotifyTake( uxIndexToWaitOn, x_Clear_എണ്ണം_On_Exit, xTicksToWait );
            }

            തിരികെ ulReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t uxIndexToClear ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t uxIndexToClear ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            എങ്കിൽ( uxIndexToClear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                എങ്കിൽ( xTask == ശൂന്യ )
                {
                    xReturn = xTaskGenericNotifyStateClear( xTask, uxIndexToClear );
                }
                അല്ലെങ്കിൽ
                {
                    lIndex = ( int32_t ) xTask;

                    എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                            {
                                xReturn = xTaskGenericNotifyStateClear( xInternalTaskHandle, uxIndexToClear );
                            }
                        }
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_മൂല്യം_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t uxIndexToClear,
                                                        uint32_t ulBitsToClear ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ul_Task_Generic_Notify_മൂല്യം_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t uxIndexToClear,
                                                        uint32_t ulBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            എങ്കിൽ( uxIndexToClear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                എങ്കിൽ( xTask == ശൂന്യ )
                {
                    ulReturn = ul_Task_Generic_Notify_മൂല്യം_Clear( xTask, uxIndexToClear, ulBitsToClear );
                }
                അല്ലെങ്കിൽ
                {
                    lIndex = ( int32_t ) xTask;

                    എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                            {
                                ulReturn = ul_Task_Generic_Notify_മൂല്യം_Clear( xInternalTaskHandle, uxIndexToClear, ulBitsToClear );
                            }
                        }
                    }
                }
            }

            തിരികെ ulReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Task APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreate( TaskFunction_t pvTaskCode,
                                    സ്ഥിരം അക്ഷരം * സ്ഥിരം pcName,
                                    സ്ഥിരം config_അട്ടി_DEPTH_TYPE ux_അട്ടി_Depth,
                                    ശൂന്യം * pvParameters,
                                    UBaseType_t uxPriority,
                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                /* xTaskCreate() can only be used to create privileged tasks in MPU port. */
                എങ്കിൽ( ( uxPriority & portPRIVILEGE_BIT ) != 0 )
                {
                    xReturn = xTaskCreate( pvTaskCode, pcName, ux_അട്ടി_Depth, pvParameters, uxPriority, &( xInternalTaskHandle ) );

                    എങ്കിൽ( ( xReturn == pdPASS ) && ( xInternalTaskHandle != ശൂന്യ ) )
                    {
                        MPU_StoreTaskHandleAtIndex( lIndex, xInternalTaskHandle );

                        എങ്കിൽ( pxCreatedTask != ശൂന്യ )
                        {
                            *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                        }
                    }
                    അല്ലെങ്കിൽ
                    {
                        MPU_SetIndexFreeInKernelObjectPool( lIndex );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                            സ്ഥിരം അക്ഷരം * സ്ഥിരം pcName,
                                            സ്ഥിരം config_അട്ടി_DEPTH_TYPE ux_അട്ടി_Depth,
                                            ശൂന്യം * സ്ഥിരം pvParameters,
                                            UBaseType_t uxPriority,
                                            അട്ടി_Type_t * സ്ഥിരം pux_അട്ടി_Buffer,
                                            StaticTask_t * സ്ഥിരം pxTaskBuffer ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xExternalTaskHandle = ശൂന്യ;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xInternalTaskHandle = xTaskCreateStatic( pxTaskCode, pcName, ux_അട്ടി_Depth, pvParameters, uxPriority, pux_അട്ടി_Buffer, pxTaskBuffer );

                എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                {
                    MPU_StoreTaskHandleAtIndex( lIndex, xInternalTaskHandle );

                    #എങ്കിൽ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        എങ്കിൽ( ( uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, lIndex );
                        }
                    }
                    #endif

                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xExternalTaskHandle;
        }

    #endif /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_vTaskDelete == 1 )

        ശൂന്യം MPU_vTaskDelete( TaskHandle_t pxTaskToDelete ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            int32_t lIndex;

            എങ്കിൽ( pxTaskToDelete == ശൂന്യ )
            {
                xInternalTaskHandle = xTaskGetCurrentTaskHandle();
                lIndex = MPU_GetIndexForTaskHandle( xInternalTaskHandle );

                എങ്കിൽ( lIndex != -1 )
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }

                vTaskDelete( xInternalTaskHandle );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) pxTaskToDelete;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                    {
                        MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
                        vTaskDelete( xInternalTaskHandle );
                    }
                }
            }
        }

    #endif /* #if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/


    #എങ്കിൽ ( INCLUDE_vTaskPrioritySet == 1 )

        ശൂന്യം MPU_vTaskPrioritySet( TaskHandle_t pxTask,
                                   UBaseType_t uxNewPriority ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            int32_t lIndex;

            എങ്കിൽ( pxTask == ശൂന്യ )
            {
                vTaskPrioritySet( pxTask, uxNewPriority );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) pxTask;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                    {
                        vTaskPrioritySet( xInternalTaskHandle, uxNewPriority );
                    }
                }
            }
        }

    #endif /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_xTaskGetHandle == 1 )

        TaskHandle_t MPU_xTaskGetHandle( സ്ഥിരം അക്ഷരം * pcNameToQuery ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            TaskHandle_t xExternalTaskHandle = ശൂന്യ;
            int32_t lIndex;

            xInternalTaskHandle = xTaskGetHandle( pcNameToQuery );

            എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
            {
                lIndex = MPU_GetIndexForTaskHandle( xInternalTaskHandle );

                എങ്കിൽ( lIndex != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
            }

            തിരികെ xExternalTaskHandle;
        }

    #endif /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/


    #എങ്കിൽ ( configUSE_APPLICATION_TASK_TAG == 1 )

        BaseType_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     ശൂന്യം * pvParameter ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;

            എങ്കിൽ( xTask == ശൂന്യ )
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) xTask;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                    {
                        xReturn = xTaskCallApplicationTaskHook( xInternalTaskHandle, pvParameter );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreateRestricted( സ്ഥിരം TaskParameters_t * സ്ഥിരം pxTaskDefinition,
                                              TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xReturn = xTaskCreateRestricted( pxTaskDefinition, &( xInternalTaskHandle ) );

                എങ്കിൽ( ( xReturn == pdPASS ) && ( xInternalTaskHandle != ശൂന്യ ) )
                {
                    MPU_StoreTaskHandleAtIndex( lIndex, xInternalTaskHandle );

                    #എങ്കിൽ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        എങ്കിൽ( ( pxTaskDefinition->uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, lIndex );
                        }
                    }
                    #endif

                    എങ്കിൽ( pxCreatedTask != ശൂന്യ )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                    }
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreateRestrictedStatic( സ്ഥിരം TaskParameters_t * സ്ഥിരം pxTaskDefinition,
                                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xReturn = xTaskCreateRestrictedStatic( pxTaskDefinition, &( xInternalTaskHandle ) );

                എങ്കിൽ( ( xReturn == pdPASS ) && ( xInternalTaskHandle != ശൂന്യ ) )
                {
                    MPU_StoreTaskHandleAtIndex( lIndex, xInternalTaskHandle );

                    #എങ്കിൽ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        എങ്കിൽ( ( pxTaskDefinition->uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, lIndex );
                        }
                    }
                    #endif

                    എങ്കിൽ( pxCreatedTask != ശൂന്യ )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                    }
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    ശൂന്യം MPU_vTaskAllocateMPURegions( TaskHandle_t xTaskToModify,
                                      സ്ഥിരം MemoryRegion_t * സ്ഥിരം xRegions ) /* PRIVILEGED_FUNCTION */
    {
        TaskHandle_t xInternalTaskHandle = ശൂന്യ;
        int32_t lIndex;

        എങ്കിൽ( xTaskToModify == ശൂന്യ )
        {
            vTaskAllocateMPURegions( xTaskToModify, xRegions );
        }
        അല്ലെങ്കിൽ
        {
            lIndex = ( int32_t ) xTaskToModify;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                {
                    vTaskAllocateMPURegions( xInternalTaskHandle, xRegions );
                }
            }
        }
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskGetStaticBuffers( TaskHandle_t xTask,
                                              അട്ടി_Type_t ** ppux_അട്ടി_Buffer,
                                              StaticTask_t ** ppxTaskBuffer ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xReturn = pdFALSE;

            എങ്കിൽ( xTask == ശൂന്യ )
            {
                xInternalTaskHandle = xTaskGetCurrentTaskHandle();
                xReturn = xTaskGetStaticBuffers( xInternalTaskHandle, ppux_അട്ടി_Buffer, ppxTaskBuffer );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) xTask;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                    {
                        xReturn = xTaskGetStaticBuffers( xInternalTaskHandle, ppux_അട്ടി_Buffer, ppxTaskBuffer );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    അക്ഷരം * MPU_pcTaskGetName( TaskHandle_t xTaskToQuery ) /* PRIVILEGED_FUNCTION */
    {
        അക്ഷരം * pcReturn = ശൂന്യ;
        int32_t lIndex;
        TaskHandle_t xInternalTaskHandle = ശൂന്യ;

        എങ്കിൽ( xTaskToQuery == ശൂന്യ )
        {
            pcReturn = pcTaskGetName( xTaskToQuery );
        }
        അല്ലെങ്കിൽ
        {
            lIndex = ( int32_t ) xTaskToQuery;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                {
                    pcReturn = pcTaskGetName( xInternalTaskHandle );
                }
            }
        }

        തിരികെ pcReturn;
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( INCLUDE_uxTaskPriorityGet == 1 )

        UBaseType_t MPU_uxTaskPriorityGetFromISR( സ്ഥിരം TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;

            എങ്കിൽ( xTask == ശൂന്യ )
            {
                uxReturn = uxTaskPriorityGetFromISR( xTask );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) xTask;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                    {
                        uxReturn = uxTaskPriorityGetFromISR( xInternalTaskHandle );
                    }
                }
            }

            തിരികെ uxReturn;
        }

    #endif /* #if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_uxTaskBasePriorityGet( സ്ഥിരം TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;

            എങ്കിൽ( xTask == ശൂന്യ )
            {
                uxReturn = uxTaskBasePriorityGet( xTask );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) xTask;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                    {
                        uxReturn = uxTaskBasePriorityGet( xInternalTaskHandle );
                    }
                }
            }

            തിരികെ uxReturn;
        }

    #endif /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_uxTaskBasePriorityGetFromISR( സ്ഥിരം TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;

            എങ്കിൽ( xTask == ശൂന്യ )
            {
                uxReturn = uxTaskBasePriorityGetFromISR( xTask );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) xTask;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                    {
                        uxReturn = uxTaskBasePriorityGetFromISR( xInternalTaskHandle );
                    }
                }
            }

            തിരികെ uxReturn;
        }

    #endif /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

        BaseType_t MPU_xTaskResumeFromISR( TaskHandle_t xTaskToResume ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;

            lIndex = ( int32_t ) xTaskToResume;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                {
                    xReturn = xTaskResumeFromISR( xInternalTaskHandle );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )*/
/*---------------------------------------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_APPLICATION_TASK_TAG == 1 )

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagFromISR( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = ശൂന്യ;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;

            എങ്കിൽ( xTask == ശൂന്യ )
            {
                xReturn = xTaskGetApplicationTaskTagFromISR( xTask );
            }
            അല്ലെങ്കിൽ
            {
                lIndex = ( int32_t ) xTask;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                    {
                        xReturn = xTaskGetApplicationTaskTagFromISR( xInternalTaskHandle );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyFromISR( TaskHandle_t xTaskToNotify,
                                                  UBaseType_t uxIndexToNotify,
                                                  uint32_t ul_മൂല്യം,
                                                  eNotifyAction eAction,
                                                  uint32_t * pul_Previous_Notification_മൂല്യം,
                                                  BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;

            lIndex = ( int32_t ) xTaskToNotify;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
                {
                    xReturn = xTaskGenericNotifyFromISR( xInternalTaskHandle, uxIndexToNotify, ul_മൂല്യം, eAction, pul_Previous_Notification_മൂല്യം, pxHigherPriorityTaskWoken );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ശൂന്യം MPU_vTaskGenericNotifyGiveFromISR( TaskHandle_t xTaskToNotify,
                                                UBaseType_t uxIndexToNotify,
                                                BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = ശൂന്യ;

            lIndex = ( int32_t ) xTaskToNotify;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalTaskHandle != ശൂന്യ )
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
                                          സ്ഥിരം ശൂന്യം * സ്ഥിരം pvItemToQueue,
                                          TickType_t xTicksToWait,
                                          BaseType_t xCopyPosition ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueGenericSendImpl( QueueHandle_t xQueue,
                                          സ്ഥിരം ശൂന്യം * സ്ഥിരം pvItemToQueue,
                                          TickType_t xTicksToWait,
                                          BaseType_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;
        BaseType_t xReturn = pdFAIL;
        BaseType_t xIsItemToQueueReadable = pdFALSE;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
        UBaseType_t uxQueueItemSize, uxQueueLength;

        lIndex = ( int32_t ) xQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                {
                    uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );
                    uxQueueLength = uxQueueGetQueueLength( xInternalQueueHandle );

                    എങ്കിൽ( ( !( ( pvItemToQueue == ശൂന്യ ) && ( uxQueueItemSize != ( UBaseType_t ) 0U ) ) ) &&
                        ( !( ( xCopyPosition == queueOVERWRITE ) && ( uxQueueLength != ( UBaseType_t ) 1U ) ) )
                        #എങ്കിൽ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        എങ്കിൽ( pvItemToQueue != ശൂന്യ )
                        {
                            xIsItemToQueueReadable = xPortIsAuthorizedToAccessBuffer( pvItemToQueue,
                                                                                      uxQueueItemSize,
                                                                                      tskMPU_READ_PERMISSION );
                        }

                        എങ്കിൽ( ( pvItemToQueue == ശൂന്യ ) || ( xIsItemToQueueReadable == pdTRUE ) )
                        {
                            xReturn = xQueueGenericSend( xInternalQueueHandle, pvItemToQueue, xTicksToWait, xCopyPosition );
                        }
                    }
                }
            }
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaitingImpl( സ്ഥിരം QueueHandle_t pxQueue ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_uxQueueMessagesWaitingImpl( സ്ഥിരം QueueHandle_t pxQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;
        UBaseType_t uxReturn = 0;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        lIndex = ( int32_t ) pxQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                {
                    uxReturn = uxQueueMessagesWaiting( xInternalQueueHandle );
                }
            }
        }

        തിരികെ uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueSpacesAvailableImpl( സ്ഥിരം QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_uxQueueSpacesAvailableImpl( സ്ഥിരം QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;
        UBaseType_t uxReturn = 0;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        lIndex = ( int32_t ) xQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                {
                    uxReturn = uxQueueSpacesAvailable( xInternalQueueHandle );
                }
            }
        }

        തിരികെ uxReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceiveImpl( QueueHandle_t pxQueue,
                                      ശൂന്യം * സ്ഥിരം pvBuffer,
                                      TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueReceiveImpl( QueueHandle_t pxQueue,
                                      ശൂന്യം * സ്ഥിരം pvBuffer,
                                      TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;
        BaseType_t xReturn = pdFAIL;
        BaseType_t xIsReceiveBufferWritable = pdFALSE;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
        UBaseType_t uxQueueItemSize;

        lIndex = ( int32_t ) pxQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                {
                    uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );

                    എങ്കിൽ( ( !( ( ( pvBuffer ) == ശൂന്യ ) && ( uxQueueItemSize != ( UBaseType_t ) 0U ) ) )
                        #എങ്കിൽ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        xIsReceiveBufferWritable = xPortIsAuthorizedToAccessBuffer( pvBuffer,
                                                                                    uxQueueItemSize,
                                                                                    tskMPU_WRITE_PERMISSION );

                        എങ്കിൽ( xIsReceiveBufferWritable == pdTRUE )
                        {
                            xReturn = xQueueReceive( xInternalQueueHandle, pvBuffer, xTicksToWait );
                        }
                    }
                }
            }
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeekImpl( QueueHandle_t xQueue,
                                   ശൂന്യം * സ്ഥിരം pvBuffer,
                                   TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueuePeekImpl( QueueHandle_t xQueue,
                                   ശൂന്യം * സ്ഥിരം pvBuffer,
                                   TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;
        BaseType_t xReturn = pdFAIL;
        BaseType_t xIsReceiveBufferWritable = pdFALSE;
        UBaseType_t uxQueueItemSize;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        lIndex = ( int32_t ) xQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                {
                    uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );

                    എങ്കിൽ( ( !( ( ( pvBuffer ) == ശൂന്യ ) && ( uxQueueItemSize != ( UBaseType_t ) 0U ) ) )
                        #എങ്കിൽ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        xIsReceiveBufferWritable = xPortIsAuthorizedToAccessBuffer( pvBuffer,
                                                                                    uxQueueItemSize,
                                                                                    tskMPU_WRITE_PERMISSION );

                        എങ്കിൽ( xIsReceiveBufferWritable == pdTRUE )
                        {
                            xReturn = xQueuePeek( xInternalQueueHandle, pvBuffer, xTicksToWait );
                        }
                    }
                }
            }
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueSemaphoreTakeImpl( QueueHandle_t xQueue,
                                            TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueSemaphoreTakeImpl( QueueHandle_t xQueue,
                                            TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;
        BaseType_t xReturn = pdFAIL;
        UBaseType_t uxQueueItemSize;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        lIndex = ( int32_t ) xQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                {
                    uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );

                    എങ്കിൽ( ( uxQueueItemSize == 0U )
                        #എങ്കിൽ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        xReturn = xQueueSemaphoreTake( xInternalQueueHandle, xTicksToWait );
                    }
                }
            }
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolderImpl( QueueHandle_t xSemaphore ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xQueueGetMutexHolderImpl( QueueHandle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xMutexHolderTaskInternalHandle = ശൂന്യ;
            TaskHandle_t xMutexHolderTaskExternalHandle = ശൂന്യ;
            int32_t lIndex, lMutexHolderTaskIndex;
            QueueHandle_t xInternalQueueHandle = ശൂന്യ;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;


            lIndex = ( int32_t ) xSemaphore;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                    {
                        xMutexHolderTaskInternalHandle = xQueueGetMutexHolder( xInternalQueueHandle );

                        എങ്കിൽ( xMutexHolderTaskInternalHandle != ശൂന്യ )
                        {
                            lMutexHolderTaskIndex = MPU_GetIndexForTaskHandle( xMutexHolderTaskInternalHandle );

                            എങ്കിൽ( lMutexHolderTaskIndex != -1 )
                            {
                                xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_TO_EXTERNAL_INDEX( lMutexHolderTaskIndex ) );
                            }
                        }
                    }
                }
            }

            തിരികെ xMutexHolderTaskExternalHandle;
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueTakeMutexRecursiveImpl( QueueHandle_t xMutex,
                                                     TickType_t xBlockTime ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueTakeMutexRecursiveImpl( QueueHandle_t xMutex,
                                                     TickType_t xBlockTime ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = ശൂന്യ;
            UBaseType_t uxQueueItemSize;

            lIndex = ( int32_t ) xMutex;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                    {
                        uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );

                        എങ്കിൽ( uxQueueItemSize == 0 )
                        {
                            xReturn = xQueueTakeMutexRecursive( xInternalQueueHandle, xBlockTime );
                        }
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueGiveMutexRecursiveImpl( QueueHandle_t xMutex ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueGiveMutexRecursiveImpl( QueueHandle_t xMutex ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = ശൂന്യ;

            lIndex = ( int32_t ) xMutex;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                    {
                        xReturn = xQueueGiveMutexRecursive( xInternalQueueHandle );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_QUEUE_SETS == 1 )

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetImpl( QueueSetHandle_t xQueueSet,
                                                            TickType_t xBlockTimeTicks ) PRIVILEGED_FUNCTION;

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetImpl( QueueSetHandle_t xQueueSet,
                                                            TickType_t xBlockTimeTicks ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = ശൂന്യ;
            QueueSetMemberHandle_t xSelectedMemberInternal = ശൂന്യ;
            QueueSetMemberHandle_t xSelectedMemberExternal = ശൂന്യ;
            int32_t lIndexQueueSet, lIndexSelectedMember;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSet = pdFALSE;

            lIndexQueueSet = ( int32_t ) xQueueSet;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSet ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueueSet = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessQueueSet == pdTRUE )
                {
                    xInternalQueueSetHandle = MPU_GetQueueSetHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );

                    എങ്കിൽ( xInternalQueueSetHandle != ശൂന്യ )
                    {
                        xSelectedMemberInternal = xQueueSelectFromSet( xInternalQueueSetHandle, xBlockTimeTicks );

                        എങ്കിൽ( xSelectedMemberInternal != ശൂന്യ )
                        {
                            lIndexSelectedMember = MPU_GetIndexForQueueSetMemberHandle( xSelectedMemberInternal );

                            എങ്കിൽ( lIndexSelectedMember != -1 )
                            {
                                xSelectedMemberExternal = ( QueueSetMemberHandle_t ) ( CONVERT_TO_EXTERNAL_INDEX( lIndexSelectedMember ) );
                            }
                        }
                    }
                }
            }

            തിരികെ xSelectedMemberExternal;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_QUEUE_SETS == 1 )

        BaseType_t MPU_xQueueAddToSetImpl( QueueSetMemberHandle_t xQueueOrSemaphore,
                                           QueueSetHandle_t xQueueSet ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueAddToSetImpl( QueueSetMemberHandle_t xQueueOrSemaphore,
                                           QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            QueueSetMemberHandle_t xInternalQueueSetMemberHandle = ശൂന്യ;
            QueueSetHandle_t xInternalQueueSetHandle = ശൂന്യ;
            int32_t lIndexQueueSet, lIndexQueueSetMember;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSet = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSetMember = pdFALSE;

            lIndexQueueSet = ( int32_t ) xQueueSet;
            lIndexQueueSetMember = ( int32_t ) xQueueOrSemaphore;

            എങ്കിൽ( ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSet ) != pdFALSE ) &&
                ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSetMember ) != pdFALSE ) )
            {
                xCallingTaskIsAuthorizedToAccessQueueSet = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );
                xCallingTaskIsAuthorizedToAccessQueueSetMember = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSetMember ) );

                എങ്കിൽ( ( xCallingTaskIsAuthorizedToAccessQueueSet == pdTRUE ) && ( xCallingTaskIsAuthorizedToAccessQueueSetMember == pdTRUE ) )
                {
                    xInternalQueueSetHandle = MPU_GetQueueSetHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );
                    xInternalQueueSetMemberHandle = MPU_GetQueueSetMemberHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSetMember ) );

                    എങ്കിൽ( ( xInternalQueueSetHandle != ശൂന്യ ) && ( xInternalQueueSetMemberHandle != ശൂന്യ ) )
                    {
                        xReturn = xQueueAddToSet( xInternalQueueSetMemberHandle, xInternalQueueSetHandle );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ configQUEUE_REGISTRY_SIZE > 0

        ശൂന്യം MPU_vQueueAddToRegistryImpl( QueueHandle_t xQueue,
                                          സ്ഥിരം അക്ഷരം * pcName ) PRIVILEGED_FUNCTION;

        ശൂന്യം MPU_vQueueAddToRegistryImpl( QueueHandle_t xQueue,
                                          സ്ഥിരം അക്ഷരം * pcName ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = ശൂന്യ;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            lIndex = ( int32_t ) xQueue;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                    {
                        vQueueAddToRegistry( xInternalQueueHandle, pcName );
                    }
                }
            }
        }

    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #എങ്കിൽ configQUEUE_REGISTRY_SIZE > 0

        ശൂന്യം MPU_vQueueUnregisterQueueImpl( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

        ശൂന്യം MPU_vQueueUnregisterQueueImpl( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = ശൂന്യ;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            lIndex = ( int32_t ) xQueue;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                    {
                        vQueueUnregisterQueue( xInternalQueueHandle );
                    }
                }
            }
        }

    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #എങ്കിൽ configQUEUE_REGISTRY_SIZE > 0

        സ്ഥിരം അക്ഷരം * MPU_pcQueueGetNameImpl( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

        സ്ഥിരം അക്ഷരം * MPU_pcQueueGetNameImpl( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
        {
            സ്ഥിരം അക്ഷരം * pcReturn = ശൂന്യ;
            QueueHandle_t xInternalQueueHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            lIndex = ( int32_t ) xQueue;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                    {
                        pcReturn = pcQueueGetName( xInternalQueueHandle );
                    }
                }
            }

            തിരികെ pcReturn;
        }

    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Queue APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    ശൂന്യം MPU_vQueueDelete( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;
        int32_t lIndex;

        lIndex = ( int32_t ) xQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
            {
                vQueueDelete( xInternalQueueHandle );
                MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
            }
        }
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateMutex( സ്ഥിരം uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ശൂന്യ;
            QueueHandle_t xExternalQueueHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueCreateMutex( ucQueueType );

                എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateMutexStatic( സ്ഥിരം uint8_t ucQueueType,
                                                   StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ശൂന്യ;
            QueueHandle_t xExternalQueueHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );

                എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphore( UBaseType_t ux_എണ്ണം_മൂല്യം,
                                                         UBaseType_t ux_Initial_എണ്ണം ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ശൂന്യ;
            QueueHandle_t xExternalQueueHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueCreateCountingSemaphore( ux_എണ്ണം_മൂല്യം, ux_Initial_എണ്ണം );

                എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphoreStatic( സ്ഥിരം UBaseType_t ux_Max_എണ്ണം,
                                                               സ്ഥിരം UBaseType_t ux_Initial_എണ്ണം,
                                                               StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ശൂന്യ;
            QueueHandle_t xExternalQueueHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueCreateCountingSemaphoreStatic( ux_Max_എണ്ണം, ux_Initial_എണ്ണം, pxStaticQueue );

                എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        QueueHandle_t MPU_xQueueGenericCreate( UBaseType_t uxQueueLength,
                                               UBaseType_t uxItemSize,
                                               uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ശൂന്യ;
            QueueHandle_t xExternalQueueHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueGenericCreate( uxQueueLength, uxItemSize, ucQueueType );

                എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xExternalQueueHandle;
        }

    #endif /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        QueueHandle_t MPU_xQueueGenericCreateStatic( സ്ഥിരം UBaseType_t uxQueueLength,
                                                     സ്ഥിരം UBaseType_t uxItemSize,
                                                     uint8_t * pucQueueStorage,
                                                     StaticQueue_t * pxStaticQueue,
                                                     സ്ഥിരം uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = ശൂന്യ;
            QueueHandle_t xExternalQueueHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueGenericCreateStatic( uxQueueLength, uxItemSize, pucQueueStorage, pxStaticQueue, ucQueueType );

                എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xExternalQueueHandle;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericReset( QueueHandle_t xQueue,
                                       BaseType_t xNewQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;
        BaseType_t xReturn = pdFAIL;

        lIndex = ( int32_t ) xQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
            {
                xReturn = xQueueGenericReset( xInternalQueueHandle, xNewQueue );
            }
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueSetHandle_t MPU_xQueueCreateSet( UBaseType_t uxEventQueueLength ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = ശൂന്യ;
            QueueSetHandle_t xExternalQueueSetHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xInternalQueueSetHandle = xQueueCreateSet( uxEventQueueLength );

                എങ്കിൽ( xInternalQueueSetHandle != ശൂന്യ )
                {
                    MPU_StoreQueueSetHandleAtIndex( lIndex, xInternalQueueSetHandle );
                    xExternalQueueSetHandle = ( QueueSetHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xExternalQueueSetHandle;
        }

    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueSetHandle_t MPU_xQueueCreateSetStatic( സ്ഥിരം UBaseType_t uxEventQueueLength,
                                                    uint8_t * pucQueueStorage,
                                                    StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = ശൂന്യ;
            QueueSetHandle_t xExternalQueueSetHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xInternalQueueSetHandle = xQueueCreateSetStatic( uxEventQueueLength, pucQueueStorage, pxStaticQueue );

                എങ്കിൽ( xInternalQueueSetHandle != ശൂന്യ )
                {
                    MPU_StoreQueueSetHandleAtIndex( lIndex, xInternalQueueSetHandle );
                    xExternalQueueSetHandle = ( QueueSetHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xExternalQueueSetHandle;
        }

    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_QUEUE_SETS == 1 )

        BaseType_t MPU_xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                            QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            QueueSetMemberHandle_t xInternalQueueSetMemberHandle = ശൂന്യ;
            QueueSetHandle_t xInternalQueueSetHandle = ശൂന്യ;
            int32_t lIndexQueueSet, lIndexQueueSetMember;

            lIndexQueueSet = ( int32_t ) xQueueSet;
            lIndexQueueSetMember = ( int32_t ) xQueueOrSemaphore;

            എങ്കിൽ( ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSet ) != pdFALSE ) &&
                ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSetMember ) != pdFALSE ) )
            {
                xInternalQueueSetHandle = MPU_GetQueueSetHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );
                xInternalQueueSetMemberHandle = MPU_GetQueueSetMemberHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSetMember ) );

                എങ്കിൽ( ( xInternalQueueSetHandle != ശൂന്യ ) && ( xInternalQueueSetMemberHandle != ശൂന്യ ) )
                {
                    xReturn = xQueueRemoveFromSet( xInternalQueueSetMemberHandle, xInternalQueueSetHandle );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xQueueGenericGetStaticBuffers( QueueHandle_t xQueue,
                                                      uint8_t ** ppucQueueStorage,
                                                      StaticQueue_t ** ppxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = ശൂന്യ;
            BaseType_t xReturn = pdFALSE;

            lIndex = ( int32_t ) xQueue;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
                {
                    xReturn = xQueueGenericGetStaticBuffers( xInternalQueueHandle, ppucQueueStorage, ppxStaticQueue );
                }
            }

            തിരികെ xReturn;
        }

    #endif /*if ( configSUPPORT_STATIC_ALLOCATION == 1 )*/
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSendFromISR( QueueHandle_t xQueue,
                                             സ്ഥിരം ശൂന്യം * സ്ഥിരം pvItemToQueue,
                                             BaseType_t * സ്ഥിരം pxHigherPriorityTaskWoken,
                                             സ്ഥിരം BaseType_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;

        lIndex = ( int32_t ) xQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
            {
                xReturn = xQueueGenericSendFromISR( xInternalQueueHandle, pvItemToQueue, pxHigherPriorityTaskWoken, xCopyPosition );
            }
        }

        തിരികെ xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGiveFromISR( QueueHandle_t xQueue,
                                      BaseType_t * സ്ഥിരം pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;

        lIndex = ( int32_t ) xQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
            {
                xReturn = xQueueGiveFromISR( xInternalQueueHandle, pxHigherPriorityTaskWoken );
            }
        }

        തിരികെ xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeekFromISR( QueueHandle_t xQueue,
                                      ശൂന്യം * സ്ഥിരം pvBuffer ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;

        lIndex = ( int32_t ) xQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
            {
                xReturn = xQueuePeekFromISR( xInternalQueueHandle, pvBuffer );
            }
        }

        തിരികെ xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceiveFromISR( QueueHandle_t xQueue,
                                         ശൂന്യം * സ്ഥിരം pvBuffer,
                                         BaseType_t * സ്ഥിരം pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;

        lIndex = ( int32_t ) xQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
            {
                xReturn = xQueueReceiveFromISR( xInternalQueueHandle, pvBuffer, pxHigherPriorityTaskWoken );
            }
        }

        തിരികെ xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueIsQueueEmptyFromISR( സ്ഥിരം QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;

        lIndex = ( int32_t ) xQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
            {
                xReturn = xQueueIsQueueEmptyFromISR( xInternalQueueHandle );
            }
        }

        തിരികെ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueIsQueueFullFromISR( സ്ഥിരം QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;

        lIndex = ( int32_t ) xQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
            {
                xReturn = xQueueIsQueueFullFromISR( xInternalQueueHandle );
            }
        }

        തിരികെ xReturn;
    }

/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaitingFromISR( സ്ഥിരം QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn = 0;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = ശൂന്യ;

        lIndex = ( int32_t ) xQueue;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xInternalQueueHandle != ശൂന്യ )
            {
                uxReturn = uxQueueMessagesWaitingFromISR( xInternalQueueHandle );
            }
        }

        തിരികെ uxReturn;
    }

/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolderFromISR( QueueHandle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xMutexHolderTaskInternalHandle = ശൂന്യ;
            TaskHandle_t xMutexHolderTaskExternalHandle = ശൂന്യ;
            int32_t lIndex, lMutexHolderTaskIndex;
            QueueHandle_t xInternalSemaphoreHandle = ശൂന്യ;

            lIndex = ( int32_t ) xSemaphore;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalSemaphoreHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalSemaphoreHandle != ശൂന്യ )
                {
                    xMutexHolderTaskInternalHandle = xQueueGetMutexHolder( xInternalSemaphoreHandle );

                    എങ്കിൽ( xMutexHolderTaskInternalHandle != ശൂന്യ )
                    {
                        lMutexHolderTaskIndex = MPU_GetIndexForTaskHandle( xMutexHolderTaskInternalHandle );

                        എങ്കിൽ( lMutexHolderTaskIndex != -1 )
                        {
                            xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_TO_EXTERNAL_INDEX( lMutexHolderTaskIndex ) );
                        }
                    }
                }
            }

            തിരികെ xMutexHolderTaskExternalHandle;
        }

    #endif /* #if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_QUEUE_SETS == 1 )

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetFromISR( QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = ശൂന്യ;
            QueueSetMemberHandle_t xSelectedMemberInternal = ശൂന്യ;
            QueueSetMemberHandle_t xSelectedMemberExternal = ശൂന്യ;
            int32_t lIndexQueueSet, lIndexSelectedMember;

            lIndexQueueSet = ( int32_t ) xQueueSet;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSet ) != pdFALSE )
            {
                xInternalQueueSetHandle = MPU_GetQueueSetHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );

                എങ്കിൽ( xInternalQueueSetHandle != ശൂന്യ )
                {
                    xSelectedMemberInternal = xQueueSelectFromSetFromISR( xInternalQueueSetHandle );

                    എങ്കിൽ( xSelectedMemberInternal != ശൂന്യ )
                    {
                        lIndexSelectedMember = MPU_GetIndexForQueueSetMemberHandle( xSelectedMemberInternal );

                        എങ്കിൽ( lIndexSelectedMember != -1 )
                        {
                            xSelectedMemberExternal = ( QueueSetMemberHandle_t ) ( CONVERT_TO_EXTERNAL_INDEX( lIndexSelectedMember ) );
                        }
                    }
                }
            }

            തിരികെ xSelectedMemberExternal;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for timers APIs.                  */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        ശൂന്യം * MPU_pvTimerGetTimerIDImpl( സ്ഥിരം TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ശൂന്യം * MPU_pvTimerGetTimerIDImpl( സ്ഥിരം TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ശൂന്യം * pvReturn = ശൂന്യ;
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                    {
                        pvReturn = pvTimerGetTimerID( xInternalTimerHandle );
                    }
                }
            }

            തിരികെ pvReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        ശൂന്യം MPU_vTimerSetTimerIDImpl( TimerHandle_t xTimer,
                                       ശൂന്യം * pvNewID ) PRIVILEGED_FUNCTION;

        ശൂന്യം MPU_vTimerSetTimerIDImpl( TimerHandle_t xTimer,
                                       ശൂന്യം * pvNewID ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                    {
                        vTimerSetTimerID( xInternalTimerHandle, pvNewID );
                    }
                }
            }
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerIsTimerActiveImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerIsTimerActiveImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                    {
                        xReturn = xTimerIsTimerActive( xInternalTimerHandle );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( ശൂന്യം ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xReturn;

            xReturn = xTimerGetTimerDaemonTaskHandle();

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     സ്ഥിരം BaseType_t xCommandID,
                                                     സ്ഥിരം TickType_t x_Optional_മൂല്യം,
                                                     BaseType_t * സ്ഥിരം pxHigherPriorityTaskWoken,
                                                     സ്ഥിരം TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn = pdFALSE;
            xTimerGenericCommandFromTaskParams_t xParams;

            xParams.xTimer = xTimer;
            xParams.xCommandID = xCommandID;
            xParams.x_Optional_മൂല്യം = x_Optional_മൂല്യം;
            xParams.pxHigherPriorityTaskWoken = pxHigherPriorityTaskWoken;
            xParams.xTicksToWait = xTicksToWait;

            xReturn = MPU_xTimerGenericCommandFromTaskEntry( &( xParams ) );

            തിരികെ xReturn;
        }

        BaseType_t MPU_xTimerGenericCommandFromTaskImpl( സ്ഥിരം xTimerGenericCommandFromTaskParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerGenericCommandFromTaskImpl( സ്ഥിരം xTimerGenericCommandFromTaskParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xIsHigherPriorityTaskWokenWriteable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            എങ്കിൽ( pxParams != ശൂന്യ )
            {
                xAreParamsReadable = xPortIsAuthorizedToAccessBuffer( pxParams,
                                                                      വലുപ്പം( xTimerGenericCommandFromTaskParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            എങ്കിൽ( xAreParamsReadable == pdTRUE )
            {
                എങ്കിൽ( pxParams->xCommandID < tmrFIRST_FROM_ISR_COMMAND )
                {
                    എങ്കിൽ( pxParams->pxHigherPriorityTaskWoken != ശൂന്യ )
                    {
                        xIsHigherPriorityTaskWokenWriteable = xPortIsAuthorizedToAccessBuffer( pxParams->pxHigherPriorityTaskWoken,
                                                                                               വലുപ്പം( BaseType_t ),
                                                                                               tskMPU_WRITE_PERMISSION );
                    }

                    എങ്കിൽ( ( pxParams->pxHigherPriorityTaskWoken == ശൂന്യ ) ||
                        ( xIsHigherPriorityTaskWokenWriteable == pdTRUE ) )
                    {
                        lIndex = ( int32_t ) ( pxParams->xTimer );

                        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                        {
                            xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                            {
                                xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                                എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                                {
                                    xReturn = xTimerGenericCommandFromTask( xInternalTimerHandle,
                                                                            pxParams->xCommandID,
                                                                            pxParams->x_Optional_മൂല്യം,
                                                                            pxParams->pxHigherPriorityTaskWoken,
                                                                            pxParams->xTicksToWait );
                                }
                            }
                        }
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        സ്ഥിരം അക്ഷരം * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        സ്ഥിരം അക്ഷരം * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            സ്ഥിരം അക്ഷരം * pcReturn = ശൂന്യ;
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                    {
                        pcReturn = pcTimerGetName( xInternalTimerHandle );
                    }
                }
            }

            തിരികെ pcReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        ശൂന്യം MPU_vTimerSetReloadModeImpl( TimerHandle_t xTimer,
                                          സ്ഥിരം BaseType_t xAutoReload ) PRIVILEGED_FUNCTION;

        ശൂന്യം MPU_vTimerSetReloadModeImpl( TimerHandle_t xTimer,
                                          സ്ഥിരം BaseType_t xAutoReload ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                    {
                        vTimerSetReloadMode( xInternalTimerHandle, xAutoReload );
                    }
                }
            }
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGetReloadModeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerGetReloadModeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                    {
                        xReturn = xTimerGetReloadMode( xInternalTimerHandle );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_uxTimerGetReloadModeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTimerGetReloadModeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                    {
                        uxReturn = uxTimerGetReloadMode( xInternalTimerHandle );
                    }
                }
            }

            തിരികെ uxReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                    {
                        xReturn = xTimerGetPeriod( xInternalTimerHandle );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetExpiryTimeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetExpiryTimeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                    {
                        xReturn = xTimerGetExpiryTime( xInternalTimerHandle );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Timer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreate( സ്ഥിരം അക്ഷരം * സ്ഥിരം pcTimerName,
                                        സ്ഥിരം TickType_t xTimerPeriodInTicks,
                                        സ്ഥിരം BaseType_t xAutoReload,
                                        ശൂന്യം * സ്ഥിരം pvTimerID,
                                        TimerCallbackFunction_t pxCallbackFunction ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            TimerHandle_t xExternalTimerHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xInternalTimerHandle = xTimerCreate( pcTimerName, xTimerPeriodInTicks, xAutoReload, pvTimerID, MPU_TimerCallback );

                എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                {
                    MPU_StoreTimerHandleAtIndex( lIndex, xInternalTimerHandle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xExternalTimerHandle;
        }

    #endif /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreateStatic( സ്ഥിരം അക്ഷരം * സ്ഥിരം pcTimerName,
                                              സ്ഥിരം TickType_t xTimerPeriodInTicks,
                                              സ്ഥിരം BaseType_t xAutoReload,
                                              ശൂന്യം * സ്ഥിരം pvTimerID,
                                              TimerCallbackFunction_t pxCallbackFunction,
                                              StaticTimer_t * pxTimerBuffer ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            TimerHandle_t xExternalTimerHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xInternalTimerHandle = xTimerCreateStatic( pcTimerName, xTimerPeriodInTicks, xAutoReload, pvTimerID, MPU_TimerCallback, pxTimerBuffer );

                എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                {
                    MPU_StoreTimerHandleAtIndex( lIndex, xInternalTimerHandle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xExternalTimerHandle;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGetStaticBuffer( TimerHandle_t xTimer,
                                              StaticTimer_t ** ppxTimerBuffer ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xReturn = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                {
                    xReturn = xTimerGetStaticBuffer( xInternalTimerHandle, ppxTimerBuffer );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGenericCommandFromISR( TimerHandle_t xTimer,
                                                    സ്ഥിരം BaseType_t xCommandID,
                                                    സ്ഥിരം TickType_t x_Optional_മൂല്യം,
                                                    BaseType_t * സ്ഥിരം pxHigherPriorityTaskWoken,
                                                    സ്ഥിരം TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = ( int32_t ) xTimer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                {
                    xReturn = xTimerGenericCommandFromISR( xInternalTimerHandle, xCommandID, x_Optional_മൂല്യം, pxHigherPriorityTaskWoken, xTicksToWait );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerDelete( TimerHandle_t xTimer, TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = ( int32_t ) xTimer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalTimerHandle != ശൂന്യ )
                {
                    xReturn = xTimerGenericCommandFromTask( xInternalTimerHandle,
                                                            tmrCOMMAND_DELETE,
                                                            0U, /* xOptionalValue */
                                                            ശൂന്യ, /* pxHigherPriorityTaskWoken */
                                                            xTicksToWait );
                    എങ്കിൽ( xReturn != pdFALSE )
                    {
                        MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for event group APIs.              */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
                                             സ്ഥിരം EventBits_t uxBitsToWaitFor,
                                             സ്ഥിരം BaseType_t xClearOnExit,
                                             സ്ഥിരം BaseType_t xWaitForAllBits,
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

            തിരികെ xReturn;
        }

        EventBits_t MPU_xEventGroupWaitBitsImpl( സ്ഥിരം xEventGroupWaitBitsParams_t * pxParams ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupWaitBitsImpl( സ്ഥിരം xEventGroupWaitBitsParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            എങ്കിൽ( pxParams != ശൂന്യ )
            {
                xAreParamsReadable = xPortIsAuthorizedToAccessBuffer( pxParams,
                                                                      വലുപ്പം( xEventGroupWaitBitsParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            എങ്കിൽ( xAreParamsReadable == pdTRUE )
            {
                എങ്കിൽ( ( ( pxParams->uxBitsToWaitFor & eventEVENT_BITS_CONTROL_BYTES ) == 0U ) &&
                    ( pxParams->uxBitsToWaitFor != 0U )
                    #എങ്കിൽ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                        && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( pxParams->xTicksToWait != 0U ) ) )
                    #endif
                    )
                {
                    lIndex = ( int32_t ) ( pxParams->xEventGroup );

                    എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                        {
                            xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            എങ്കിൽ( xInternalEventGroupHandle != ശൂന്യ )
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

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupClearBitsImpl( EventGroupHandle_t xEventGroup,
                                                  സ്ഥിരം EventBits_t uxBitsToClear ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupClearBitsImpl( EventGroupHandle_t xEventGroup,
                                                  സ്ഥിരം EventBits_t uxBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            എങ്കിൽ( ( uxBitsToClear & eventEVENT_BITS_CONTROL_BYTES ) == 0U )
            {
                lIndex = ( int32_t ) xEventGroup;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xInternalEventGroupHandle != ശൂന്യ )
                        {
                            xReturn = xEventGroupClearBits( xInternalEventGroupHandle, uxBitsToClear );
                        }
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSetBitsImpl( EventGroupHandle_t xEventGroup,
                                                സ്ഥിരം EventBits_t uxBitsToSet ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupSetBitsImpl( EventGroupHandle_t xEventGroup,
                                                സ്ഥിരം EventBits_t uxBitsToSet ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            എങ്കിൽ( ( uxBitsToSet & eventEVENT_BITS_CONTROL_BYTES ) == 0U )
            {
                lIndex = ( int32_t ) xEventGroup;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xInternalEventGroupHandle != ശൂന്യ )
                        {
                            xReturn = xEventGroupSetBits( xInternalEventGroupHandle, uxBitsToSet );
                        }
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSyncImpl( EventGroupHandle_t xEventGroup,
                                             സ്ഥിരം EventBits_t uxBitsToSet,
                                             സ്ഥിരം EventBits_t uxBitsToWaitFor,
                                             TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupSyncImpl( EventGroupHandle_t xEventGroup,
                                             സ്ഥിരം EventBits_t uxBitsToSet,
                                             സ്ഥിരം EventBits_t uxBitsToWaitFor,
                                             TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            എങ്കിൽ( ( ( uxBitsToWaitFor & eventEVENT_BITS_CONTROL_BYTES ) == 0U ) &&
                ( uxBitsToWaitFor != 0U )
                #എങ്കിൽ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                    && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                #endif
                )
            {
                lIndex = ( int32_t ) xEventGroup;

                എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xInternalEventGroupHandle != ശൂന്യ )
                        {
                            xReturn = xEventGroupSync( xInternalEventGroupHandle, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
                        }
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_Group_Get_സംഖ്യ_Impl( ശൂന്യം * xEventGroup ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Event_Group_Get_സംഖ്യ_Impl( ശൂന്യം * xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            lIndex = ( int32_t ) xEventGroup;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                {
                    xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalEventGroupHandle != ശൂന്യ )
                    {
                        xReturn = ux_Event_Group_Get_സംഖ്യ( xInternalEventGroupHandle );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        ശൂന്യം MPU_v_Event_Group_Set_സംഖ്യ_Impl( ശൂന്യം * xEventGroup,
                                           UBaseType_t ux_Event_Group_സംഖ്യ ) PRIVILEGED_FUNCTION;

        ശൂന്യം MPU_v_Event_Group_Set_സംഖ്യ_Impl( ശൂന്യം * xEventGroup,
                                           UBaseType_t ux_Event_Group_സംഖ്യ ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            lIndex = ( int32_t ) xEventGroup;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                {
                    xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalEventGroupHandle != ശൂന്യ )
                    {
                        v_Event_Group_Set_സംഖ്യ( xInternalEventGroupHandle, ux_Event_Group_സംഖ്യ );
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

    #എങ്കിൽ ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        EventGroupHandle_t MPU_xEventGroupCreate( ശൂന്യം ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = ശൂന്യ;
            EventGroupHandle_t xExternalEventGroupHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xInternalEventGroupHandle = xEventGroupCreate();

                എങ്കിൽ( xInternalEventGroupHandle != ശൂന്യ )
                {
                    MPU_StoreEventGroupHandleAtIndex( lIndex, xInternalEventGroupHandle );
                    xExternalEventGroupHandle = ( EventGroupHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xExternalEventGroupHandle;
        }

    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        EventGroupHandle_t MPU_xEventGroupCreateStatic( StaticEventGroup_t * pxEventGroupBuffer ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = ശൂന്യ;
            EventGroupHandle_t xExternalEventGroupHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            എങ്കിൽ( lIndex != -1 )
            {
                xInternalEventGroupHandle = xEventGroupCreateStatic( pxEventGroupBuffer );

                എങ്കിൽ( xInternalEventGroupHandle != ശൂന്യ )
                {
                    MPU_StoreEventGroupHandleAtIndex( lIndex, xInternalEventGroupHandle );
                    xExternalEventGroupHandle = ( EventGroupHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                അല്ലെങ്കിൽ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            തിരികെ xExternalEventGroupHandle;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )

        ശൂന്യം MPU_vEventGroupDelete( EventGroupHandle_t xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalEventGroupHandle != ശൂന്യ )
                {
                    vEventGroupDelete( xInternalEventGroupHandle );
                    MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
                }
            }
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        BaseType_t MPU_xEventGroupGetStaticBuffer( EventGroupHandle_t xEventGroup,
                                                   StaticEventGroup_t ** ppxEventGroupBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalEventGroupHandle != ശൂന്യ )
                {
                    xReturn = xEventGroupGetStaticBuffer( xInternalEventGroupHandle, ppxEventGroupBuffer );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        BaseType_t MPU_xEventGroupClearBitsFromISR( EventGroupHandle_t xEventGroup,
                                                    സ്ഥിരം EventBits_t uxBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalEventGroupHandle != ശൂന്യ )
                {
                    xReturn = xEventGroupClearBitsFromISR( xInternalEventGroupHandle, uxBitsToClear );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        BaseType_t MPU_xEventGroupSetBitsFromISR( EventGroupHandle_t xEventGroup,
                                                  സ്ഥിരം EventBits_t uxBitsToSet,
                                                  BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalEventGroupHandle != ശൂന്യ )
                {
                    xReturn = xEventGroupSetBitsFromISR( xInternalEventGroupHandle, uxBitsToSet, pxHigherPriorityTaskWoken );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupGetBitsFromISR( EventGroupHandle_t xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalEventGroupHandle != ശൂന്യ )
                {
                    xReturn = xEventGroupGetBitsFromISR( xInternalEventGroupHandle );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for stream buffer APIs.            */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferSendImpl( StreamBufferHandle_t xStreamBuffer,
                                          സ്ഥിരം ശൂന്യം * pvTxData,
                                          size_t xDataLengthBytes,
                                          TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferSendImpl( StreamBufferHandle_t xStreamBuffer,
                                          സ്ഥിരം ശൂന്യം * pvTxData,
                                          size_t xDataLengthBytes,
                                          TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xIsTxDataBufferReadable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            എങ്കിൽ( pvTxData != ശൂന്യ )
            {
                xIsTxDataBufferReadable = xPortIsAuthorizedToAccessBuffer( pvTxData,
                                                                           xDataLengthBytes,
                                                                           tskMPU_READ_PERMISSION );

                എങ്കിൽ( xIsTxDataBufferReadable == pdTRUE )
                {
                    lIndex = ( int32_t ) xStreamBuffer;

                    എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                        {
                            xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                            {
                                xReturn = xStreamBufferSend( xInternalStreamBufferHandle, pvTxData, xDataLengthBytes, xTicksToWait );
                            }
                        }
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferReceiveImpl( StreamBufferHandle_t xStreamBuffer,
                                             ശൂന്യം * pvRxData,
                                             size_t xBufferLengthBytes,
                                             TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferReceiveImpl( StreamBufferHandle_t xStreamBuffer,
                                             ശൂന്യം * pvRxData,
                                             size_t xBufferLengthBytes,
                                             TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xIsRxDataBufferWriteable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            എങ്കിൽ( pvRxData != ശൂന്യ )
            {
                xIsRxDataBufferWriteable = xPortIsAuthorizedToAccessBuffer( pvRxData,
                                                                            xBufferLengthBytes,
                                                                            tskMPU_WRITE_PERMISSION );

                എങ്കിൽ( xIsRxDataBufferWriteable == pdTRUE )
                {
                    lIndex = ( int32_t ) xStreamBuffer;

                    എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        എങ്കിൽ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                        {
                            xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                            {
                                xReturn = xStreamBufferReceive( xInternalStreamBufferHandle, pvRxData, xBufferLengthBytes, xTicksToWait );
                            }
                        }
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferIsFullImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xStreamBufferIsFullImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                    {
                        xReturn = xStreamBufferIsFull( xInternalStreamBufferHandle );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferIsEmptyImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xStreamBufferIsEmptyImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                    {
                        xReturn = xStreamBufferIsEmpty( xInternalStreamBufferHandle );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferSpacesAvailableImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferSpacesAvailableImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                    {
                        xReturn = xStreamBufferSpacesAvailable( xInternalStreamBufferHandle );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferBytesAvailableImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferBytesAvailableImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                    {
                        xReturn = xStreamBufferBytesAvailable( xInternalStreamBufferHandle );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferSetTriggerLevelImpl( StreamBufferHandle_t xStreamBuffer,
                                                         size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xStreamBufferSetTriggerLevelImpl( StreamBufferHandle_t xStreamBuffer,
                                                         size_t xTriggerLevel ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                    {
                        xReturn = xStreamBufferSetTriggerLevel( xInternalStreamBufferHandle, xTriggerLevel );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferNextMessageLengthBytesImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferNextMessageLengthBytesImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                    {
                        xReturn = xStreamBufferNextMessageLengthBytes( xInternalStreamBufferHandle );
                    }
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Stream Buffer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        StreamBufferHandle_t MPU_xStreamBufferGenericCreate( size_t xBufferSizeBytes,
                                                             size_t xTriggerLevelBytes,
                                                             BaseType_t xStreamBufferType,
                                                             StreamBufferCallbackFunction_t pxSendCompletedCallback,
                                                             StreamBufferCallbackFunction_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            StreamBufferHandle_t xExternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ശൂന്യ ) &&
                          ( pxReceiveCompletedCallback == ശൂന്യ ) );

            എങ്കിൽ( ( pxSendCompletedCallback == ശൂന്യ ) &&
                ( pxReceiveCompletedCallback == ശൂന്യ ) )
            {
                lIndex = MPU_GetFreeIndexInKernelObjectPool();

                എങ്കിൽ( lIndex != -1 )
                {
                    xInternalStreamBufferHandle = xStreamBufferGenericCreate( xBufferSizeBytes,
                                                                              xTriggerLevelBytes,
                                                                              xStreamBufferType,
                                                                              ശൂന്യ,
                                                                              ശൂന്യ );

                    എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                    {
                        MPU_StoreStreamBufferHandleAtIndex( lIndex, xInternalStreamBufferHandle );
                        xExternalStreamBufferHandle = ( StreamBufferHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                    }
                    അല്ലെങ്കിൽ
                    {
                        MPU_SetIndexFreeInKernelObjectPool( lIndex );
                    }
                }
            }
            അല്ലെങ്കിൽ
            {
                traceSTREAM_BUFFER_CREATE_FAILED( xStreamBufferType );
                xExternalStreamBufferHandle = ശൂന്യ;
            }

            തിരികെ xExternalStreamBufferHandle;
        }

    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        StreamBufferHandle_t MPU_xStreamBufferGenericCreateStatic( size_t xBufferSizeBytes,
                                                                   size_t xTriggerLevelBytes,
                                                                   BaseType_t xStreamBufferType,
                                                                   uint8_t * സ്ഥിരം pucStreamBufferStorageArea,
                                                                   StaticStreamBuffer_t * സ്ഥിരം pxStaticStreamBuffer,
                                                                   StreamBufferCallbackFunction_t pxSendCompletedCallback,
                                                                   StreamBufferCallbackFunction_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            StreamBufferHandle_t xExternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ശൂന്യ ) &&
                          ( pxReceiveCompletedCallback == ശൂന്യ ) );

            എങ്കിൽ( ( pxSendCompletedCallback == ശൂന്യ ) &&
                ( pxReceiveCompletedCallback == ശൂന്യ ) )
            {
                lIndex = MPU_GetFreeIndexInKernelObjectPool();

                എങ്കിൽ( lIndex != -1 )
                {
                    xInternalStreamBufferHandle = xStreamBufferGenericCreateStatic( xBufferSizeBytes,
                                                                                    xTriggerLevelBytes,
                                                                                    xStreamBufferType,
                                                                                    pucStreamBufferStorageArea,
                                                                                    pxStaticStreamBuffer,
                                                                                    ശൂന്യ,
                                                                                    ശൂന്യ );

                    എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                    {
                        MPU_StoreStreamBufferHandleAtIndex( lIndex, xInternalStreamBufferHandle );
                        xExternalStreamBufferHandle = ( StreamBufferHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                    }
                    അല്ലെങ്കിൽ
                    {
                        MPU_SetIndexFreeInKernelObjectPool( lIndex );
                    }
                }
            }
            അല്ലെങ്കിൽ
            {
                traceSTREAM_BUFFER_CREATE_STATIC_FAILED( xReturn, xStreamBufferType );
                xExternalStreamBufferHandle = ശൂന്യ;
            }

            തിരികെ xExternalStreamBufferHandle;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        ശൂന്യം MPU_vStreamBufferDelete( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                {
                    vStreamBufferDelete( xInternalStreamBufferHandle );
                }

                MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
            }
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferReset( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                {
                    xReturn = xStreamBufferReset( xInternalStreamBufferHandle );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        BaseType_t MPU_xStreamBufferGetStaticBuffers( StreamBufferHandle_t xStreamBuffers,
                                                      uint8_t * ppucStreamBufferStorageArea,
                                                      StaticStreamBuffer_t * ppxStaticStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffers;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                {
                    xReturn = MPU_xStreamBufferGetStaticBuffers( xInternalStreamBufferHandle, ppucStreamBufferStorageArea, ppxStaticStreamBuffer );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

    size_t MPU_xStreamBufferSendFromISR( StreamBufferHandle_t xStreamBuffer,
                                         സ്ഥിരം ശൂന്യം * pvTxData,
                                         size_t xDataLengthBytes,
                                         BaseType_t * സ്ഥിരം pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
        int32_t lIndex;

        lIndex = ( int32_t ) xStreamBuffer;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
            {
                xReturn = xStreamBufferSendFromISR( xInternalStreamBufferHandle, pvTxData, xDataLengthBytes, pxHigherPriorityTaskWoken );
            }
        }

        തിരികെ xReturn;
    }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

    size_t MPU_xStreamBufferReceiveFromISR( StreamBufferHandle_t xStreamBuffer,
                                            ശൂന്യം * pvRxData,
                                            size_t xBufferLengthBytes,
                                            BaseType_t * സ്ഥിരം pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
        int32_t lIndex;

        lIndex = ( int32_t ) xStreamBuffer;

        എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
            {
                xReturn = xStreamBufferReceiveFromISR( xInternalStreamBufferHandle, pvRxData, xBufferLengthBytes, pxHigherPriorityTaskWoken );
            }
        }

        തിരികെ xReturn;
    }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferSendCompletedFromISR( StreamBufferHandle_t xStreamBuffer,
                                                          BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                {
                    xReturn = xStreamBufferSendCompletedFromISR( xInternalStreamBufferHandle, pxHigherPriorityTaskWoken );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferReceiveCompletedFromISR( StreamBufferHandle_t xStreamBuffer,
                                                             BaseType_t * pxHigherPriorityTaskWoken ) /*PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                {
                    xReturn = xStreamBufferReceiveCompletedFromISR( xInternalStreamBufferHandle, pxHigherPriorityTaskWoken );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

    #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferResetFromISR( StreamBufferHandle_t xStreamBuffer ) /*PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            StreamBufferHandle_t xInternalStreamBufferHandle = ശൂന്യ;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            എങ്കിൽ( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                എങ്കിൽ( xInternalStreamBufferHandle != ശൂന്യ )
                {
                    xReturn = xStreamBufferResetFromISR( xInternalStreamBufferHandle );
                }
            }

            തിരികെ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h. */

    #എങ്കിൽ configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #അന്തര്ഭാവ "application_defined_privileged_functions.h"
    #endif
/*-----------------------------------------------------------*/

/**
 * @brief Array of system call implementation functions.
 *
 * The index in the array MUST match the corresponding system call number
 * defined in mpu_wrappers.h.
 */
    PRIVILEGED_DATA UBaseType_t uxSystemCallImplementations[ അക്കം_SYSTEM_CALLS ] =
    {
        #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_xTaskGenericNotifyImpl,                     /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyWaitImpl,                 /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #endif

        #എങ്കിൽ ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_xTimerGenericCommandFromTaskImpl,           /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #endif

        #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_xEventGroupWaitBitsImpl,                    /* SYSTEM_CALL_xEventGroupWaitBits. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupWaitBits. */
        #endif

        /* The system calls above this line take 5 parameters. */

        #എങ്കിൽ ( INCLUDE_xTaskDelayUntil == 1 )
            ( UBaseType_t ) MPU_xTaskDelayUntilImpl,                        /* SYSTEM_CALL_xTaskDelayUntil. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskDelayUntil. */
        #endif

        #എങ്കിൽ ( INCLUDE_xTaskAbortDelay == 1 )
            ( UBaseType_t ) MPU_xTaskAbortDelayImpl,                        /* SYSTEM_CALL_xTaskAbortDelay. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskAbortDelay. */
        #endif

        #എങ്കിൽ ( INCLUDE_vTaskDelay == 1 )
            ( UBaseType_t ) MPU_vTaskDelayImpl,                             /* SYSTEM_CALL_vTaskDelay. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskDelay. */
        #endif

        #എങ്കിൽ ( INCLUDE_uxTaskPriorityGet == 1 )
            ( UBaseType_t ) MPU_uxTaskPriorityGetImpl,                      /* SYSTEM_CALL_uxTaskPriorityGet. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskPriorityGet. */
        #endif

        #എങ്കിൽ ( INCLUDE_eTaskGetState == 1 )
            ( UBaseType_t ) MPU_eTaskGetStateImpl,                          /* SYSTEM_CALL_eTaskGetState. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_eTaskGetState. */
        #endif

        #എങ്കിൽ ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_vTaskGetInfoImpl,                           /* SYSTEM_CALL_vTaskGetInfo. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskGetInfo. */
        #endif

        #എങ്കിൽ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
            ( UBaseType_t ) MPU_xTaskGetIdleTaskHandleImpl,                 /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #endif

        #എങ്കിൽ ( INCLUDE_vTaskSuspend == 1 )
            ( UBaseType_t ) MPU_vTaskSuspendImpl,                           /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) MPU_vTaskResumeImpl,                            /* SYSTEM_CALL_vTaskResume. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskResume. */
        #endif

        ( UBaseType_t ) MPU_x_Task_Get_Tick_എണ്ണം_Impl,                          /* SYSTEM_CALL_xTaskGetTickCount. */
        ( UBaseType_t ) MPU_ux_Task_Get_സംഖ്യ_Of_Tasks_Impl,                     /* SYSTEM_CALL_uxTaskGetNumberOfTasks. */

        #എങ്കിൽ ( configGENERATE_RUN_TIME_STATS == 1 )
            ( UBaseType_t ) MPU_ulTaskGetRunTimeCounterImpl,                /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) MPU_ulTaskGetRunTimePercentImpl,                /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #endif

        #എങ്കിൽ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
            ( UBaseType_t ) MPU_ulTaskGetIdleRunTimePercentImpl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) MPU_ulTaskGetIdleRunTimeCounterImpl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #endif

        #എങ്കിൽ ( configUSE_APPLICATION_TASK_TAG == 1 )
            ( UBaseType_t ) MPU_vTaskSetApplicationTaskTagImpl,             /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) MPU_xTaskGetApplicationTaskTagImpl,             /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #endif

        #എങ്കിൽ ( config_അക്കം_THREAD_LOCAL_STORAGE_POINTERS != 0 )
            ( UBaseType_t ) MPU_vTaskSetThreadLocalStoragePointerImpl,      /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) MPU_pvTaskGetThreadLocalStoragePointerImpl,     /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #endif

        #എങ്കിൽ ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_uxTaskGetSystemStateImpl,                   /* SYSTEM_CALL_uxTaskGetSystemState. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetSystemState. */
        #endif

        #എങ്കിൽ ( INCLUDE_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark_Impl,            /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #endif

        #എങ്കിൽ ( INCLUDE_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2 == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_അട്ടി_മുകളിലെ_Water_Mark2_Impl,           /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #endif

        #എങ്കിൽ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )
            ( UBaseType_t ) MPU_xTaskGetCurrentTaskHandleImpl,              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #endif

        #എങ്കിൽ ( INCLUDE_xTaskGetSchedulerState == 1 )
            ( UBaseType_t ) MPU_xTaskGetSchedulerStateImpl,                 /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #endif

        ( UBaseType_t ) MPU_vTaskSetTimeOutStateImpl,                       /* SYSTEM_CALL_vTaskSetTimeOutState. */
        ( UBaseType_t ) MPU_xTaskCheckForTimeOutImpl,                       /* SYSTEM_CALL_xTaskCheckForTimeOut. */

        #എങ്കിൽ ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_ulTaskGenericNotifyTakeImpl,                /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyStateClearImpl,           /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) MPU_ul_Task_Generic_Notify_മൂല്യം_Clear_Impl,          /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #അല്ലെങ്കിൽ
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

        #എങ്കിൽ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
            ( UBaseType_t ) MPU_xQueueGetMutexHolderImpl,                   /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #endif

        #എങ്കിൽ ( configUSE_RECURSIVE_MUTEXES == 1 )
            ( UBaseType_t ) MPU_xQueueTakeMutexRecursiveImpl,               /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) MPU_xQueueGiveMutexRecursiveImpl,               /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #endif

        #എങ്കിൽ ( configUSE_QUEUE_SETS == 1 )
            ( UBaseType_t ) MPU_xQueueSelectFromSetImpl,                    /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) MPU_xQueueAddToSetImpl,                         /* SYSTEM_CALL_xQueueAddToSet. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueAddToSet. */
        #endif

        #എങ്കിൽ configQUEUE_REGISTRY_SIZE > 0
            ( UBaseType_t ) MPU_vQueueAddToRegistryImpl,                    /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) MPU_vQueueUnregisterQueueImpl,                  /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) MPU_pcQueueGetNameImpl,                         /* SYSTEM_CALL_pcQueueGetName. */
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcQueueGetName. */
        #endif

        #എങ്കിൽ ( configUSE_TIMERS == 1 )
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
        #അല്ലെങ്കിൽ
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

        #എങ്കിൽ ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_xEventGroupClearBitsImpl,                   /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) MPU_xEventGroupSetBitsImpl,                     /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) MPU_xEventGroupSyncImpl,                        /* SYSTEM_CALL_xEventGroupSync. */

            #എങ്കിൽ ( configUSE_TRACE_FACILITY == 1 )
                ( UBaseType_t ) MPU_ux_Event_Group_Get_സംഖ്യ_Impl,              /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) MPU_v_Event_Group_Set_സംഖ്യ_Impl,               /* SYSTEM_CALL_vEventGroupSetNumber. */
            #അല്ലെങ്കിൽ
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_vEventGroupSetNumber. */
            #endif
        #അല്ലെങ്കിൽ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSync. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxEventGroupGetNumber. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vEventGroupSetNumber. */
        #endif

        #എങ്കിൽ ( configUSE_STREAM_BUFFERS == 1 )
            ( UBaseType_t ) MPU_xStreamBufferSendImpl,                      /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) MPU_xStreamBufferReceiveImpl,                   /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) MPU_xStreamBufferIsFullImpl,                    /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) MPU_xStreamBufferIsEmptyImpl,                   /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) MPU_xStreamBufferSpacesAvailableImpl,           /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) MPU_xStreamBufferBytesAvailableImpl,            /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) MPU_xStreamBufferSetTriggerLevelImpl,           /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) MPU_xStreamBufferNextMessageLengthBytesImpl     /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #അല്ലെങ്കിൽ
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
