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
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "event_groups.h"
#include "stream_buffer.h"
#include "mpu_prototypes.h"
#include "mpu_syscall_numbers.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#ᮚᮦᮔ᮪ ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #ifndef configPROTECTED_KERNEL_OBJECT_POOL_SIZE
        #error configPROTECTED_KERNEL_OBJECT_POOL_SIZE must be defined to maximum number of kernel objects in the application.
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
    sa_nracanaa OpaqueObject;
    typedef sa_nracanaa OpaqueObject * OpaqueObjectHandle_t;

/**
 * @brief Defines kernel object in the kernel object pool.
 */
    typedef sa_nracanaa KernelObject
    {
        OpaqueObjectHandle_t xInternalObjectHandle;
        uint32_t ulKernelObjectType;
        void * pvKernelObjectData;
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
    static int32_t MPU_GetFreeIndexInKernelObjectPool( void ) PRIVILEGED_FUNCTION;

/**
 * @brief Set the given index as free in the kernel object pool.
 *
 * @param lIndex The index to set as free.
 */
    static void MPU_SetIndexFreeInKernelObjectPool( int32_t lIndex ) PRIVILEGED_FUNCTION;

/**
 * @brief Get the index at which a given kernel object is stored.
 *
 * @param xHandle The given kernel object handle.
 * @param ulKernelObjectType The kernel object type.
 *
 * @return Index at which the kernel object is stored if it is a valid
 *         handle, -1 otherwise.
 */
    static int32_t MPU_GetIndexForHandle( OpaqueObjectHandle_t xHandle,
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
    static void MPU_StoreHandleAndDataAtIndex( int32_t lIndex,
                                               OpaqueObjectHandle_t xHandle,
                                               void * pvKernelObjectData,
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
    static OpaqueObjectHandle_t MPU_GetHandleAtIndex( int32_t lIndex,
                                                      uint32_t ulKernelObjectType ) PRIVILEGED_FUNCTION;

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

/**
 * @brief The function registered as callback for all the timers.
 *
 * We intercept all the timer callbacks so that we can call application
 * callbacks with opaque handle.
 *
 * @param xInternalHandle The internal timer handle.
 */
        static void MPU_TimerCallback( TimerHandle_t xInternalHandle ) PRIVILEGED_FUNCTION;

    #endif /* #if ( configUSE_TIMERS == 1 ) */

/*
 * Wrappers to keep all the casting in one place.
 */
    #define MPU_StoreQueueHandleAtIndex( lIndex, xHandle )                 MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), NULL, KERNEL_OBJECT_TYPE_QUEUE )
    #define MPU_GetQueueHandleAtIndex( lIndex )                            ( QueueHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_QUEUE )

    #ᮚᮦᮔ᮪ ( configUSE_QUEUE_SETS == 1 )
        #define MPU_StoreQueueSetHandleAtIndex( lIndex, xHandle )          MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), NULL, KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_GetQueueSetHandleAtIndex( lIndex )                     ( QueueSetHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_StoreQueueSetMemberHandleAtIndex( lIndex, xHandle )    MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), NULL, KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_GetQueueSetMemberHandleAtIndex( lIndex )               ( QueueSetMemberHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_QUEUE )
        #define MPU_GetIndexForQueueSetMemberHandle( xHandle )             MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_QUEUE )
    #endif

/*
 * Wrappers to keep all the casting in one place for Task APIs.
 */
    #define MPU_StoreTaskHandleAtIndex( lIndex, xHandle )            MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), NULL, KERNEL_OBJECT_TYPE_TASK )
    #define MPU_GetTaskHandleAtIndex( lIndex )                       ( TaskHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_TASK )
    #define MPU_GetIndexForTaskHandle( xHandle )                     MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TASK )

    #ᮚᮦᮔ᮪ ( configUSE_EVENT_GROUPS == 1 )
/*
 * Wrappers to keep all the casting in one place for Event Group APIs.
 */
        #define MPU_StoreEventGroupHandleAtIndex( lIndex, xHandle )      MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), NULL, KERNEL_OBJECT_TYPE_EVENT_GROUP )
        #define MPU_GetEventGroupHandleAtIndex( lIndex )                 ( EventGroupHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_EVENT_GROUP )
        #define MPU_GetIndexForEventGroupHandle( xHandle )               MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_EVENT_GROUP )

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Stream Buffer APIs.
 */
        #define MPU_StoreStreamBufferHandleAtIndex( lIndex, xHandle )    MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle), NULL, KERNEL_OBJECT_TYPE_STREAM_BUFFER )
        #define MPU_GetStreamBufferHandleAtIndex( lIndex )               ( StreamBufferHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_STREAM_BUFFER )
        #define MPU_GetIndexForStreamBufferHandle( xHandle )             MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_STREAM_BUFFER )

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Timer APIs.
 */
        #define MPU_StoreTimerHandleAtIndex( lIndex, xHandle, pxApplicationCallback )    MPU_StoreHandleAndDataAtIndex( ( lIndex ), ( OpaqueObjectHandle_t ) ( xHandle ), ( void * ) ( pxApplicationCallback ), KERNEL_OBJECT_TYPE_TIMER )
        #define MPU_GetTimerHandleAtIndex( lIndex )                                      ( TimerHandle_t ) MPU_GetHandleAtIndex( ( lIndex ), KERNEL_OBJECT_TYPE_TIMER )
        #define MPU_GetIndexForTimerHandle( xHandle )                                    MPU_GetIndexForHandle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TIMER )

    #endif /* #if ( configUSE_TIMERS == 1 ) */

/*-----------------------------------------------------------*/

/**
 * @brief Kernel object pool.
 */
    PRIVILEGED_DATA static KernelObject_t xKernelObjectPool[ configPROTECTED_KERNEL_OBJECT_POOL_SIZE ] = { 0 };
/*-----------------------------------------------------------*/

    static int32_t MPU_GetFreeIndexInKernelObjectPool( void ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, lFreeIndex = -1;

        /* This function is called only from resource create APIs
         * which are not supposed to be called from ISRs. Therefore,
         * we only need to suspend the scheduler and do not require
         * critical section. */
        vTaskSuspendAll();
        {
            for( i = 0; i < configPROTECTED_KERNEL_OBJECT_POOL_SIZE; i++ )
            {
                ᮚᮦᮔ᮪( xKernelObjectPool[ i ].xInternalObjectHandle == NULL )
                {
                    /* Mark this index as not free. */
                    xKernelObjectPool[ i ].xInternalObjectHandle = ( OpaqueObjectHandle_t ) ( ~0U );
                    lFreeIndex = i;
                    bha_nga;
                }
            }
        }
        ( void ) xTaskResumeAll();

        ᮝᮜᮤ lFreeIndex;
    }
/*-----------------------------------------------------------*/

    static void MPU_SetIndexFreeInKernelObjectPool( int32_t lIndex ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_INTERNAL_INDEX_VALID( lIndex ) != pdFALSE );

        taskENTER_CRITICAL();
        {
            xKernelObjectPool[ lIndex ].xInternalObjectHandle = NULL;
            xKernelObjectPool[ lIndex ].ulKernelObjectType = KERNEL_OBJECT_TYPE_INVALID;
            xKernelObjectPool[ lIndex ].pvKernelObjectData = NULL;
        }
        taskEXIT_CRITICAL();
    }
/*-----------------------------------------------------------*/

    static int32_t MPU_GetIndexForHandle( OpaqueObjectHandle_t xHandle,
                                          uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, lIndex = -1;

        configASSERT( xHandle != NULL );

        for( i = 0; i < configPROTECTED_KERNEL_OBJECT_POOL_SIZE; i++ )
        {
            ᮚᮦᮔ᮪( ( xKernelObjectPool[ i ].xInternalObjectHandle == xHandle ) &&
                ( xKernelObjectPool[ i ].ulKernelObjectType == ulKernelObjectType ) )
            {
                lIndex = i;
                bha_nga;
            }
        }

        ᮝᮜᮤ lIndex;
    }
/*-----------------------------------------------------------*/

    static void MPU_StoreHandleAndDataAtIndex( int32_t lIndex,
                                               OpaqueObjectHandle_t xHandle,
                                               void * pvKernelObjectData,
                                               uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_INTERNAL_INDEX_VALID( lIndex ) != pdFALSE );
        xKernelObjectPool[ lIndex ].xInternalObjectHandle = xHandle;
        xKernelObjectPool[ lIndex ].ulKernelObjectType = ulKernelObjectType;
        xKernelObjectPool[ lIndex ].pvKernelObjectData = pvKernelObjectData;
    }
/*-----------------------------------------------------------*/

    static OpaqueObjectHandle_t MPU_GetHandleAtIndex( int32_t lIndex,
                                                      uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        OpaqueObjectHandle_t xObjectHandle = NULL;

        configASSERT( IS_INTERNAL_INDEX_VALID( lIndex ) != pdFALSE );

        ᮚᮦᮔ᮪( xKernelObjectPool[ lIndex ].ulKernelObjectType == ulKernelObjectType )
        {
            xObjectHandle = xKernelObjectPool[ lIndex ].xInternalObjectHandle;
        }

        ᮝᮜᮤ xObjectHandle;
    }
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        void vGrantAccessToKernelObject( TaskHandle_t xExternalTaskHandle,
                                         int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lExternalTaskIndex;
            TaskHandle_t xInternalTaskHandle = NULL;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                ᮚᮦᮔ᮪( xExternalTaskHandle == NULL )
                {
                    vPortGrantAccessToKernelObject( xExternalTaskHandle, CONVERT_TO_INTERNAL_INDEX( lExternalKernelObjectHandle ) );
                }
                ᮜᮤᮚ
                {
                    lExternalTaskIndex = ( int32_t ) xExternalTaskHandle;

                    ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lExternalTaskIndex ) != pdFALSE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lExternalTaskIndex ) );

                        ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
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

    #ᮚᮦᮔ᮪ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        void vRevokeAccessToKernelObject( TaskHandle_t xExternalTaskHandle,
                                          int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lExternalTaskIndex;
            TaskHandle_t xInternalTaskHandle = NULL;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                ᮚᮦᮔ᮪( xExternalTaskHandle == NULL )
                {
                    vPortRevokeAccessToKernelObject( xExternalTaskHandle, CONVERT_TO_INTERNAL_INDEX( lExternalKernelObjectHandle ) );
                }
                ᮜᮤᮚ
                {
                    lExternalTaskIndex = ( int32_t ) xExternalTaskHandle;

                    ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lExternalTaskIndex ) != pdFALSE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lExternalTaskIndex ) );

                        ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
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

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

        static void MPU_TimerCallback( TimerHandle_t xInternalHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t i, lIndex = -1;
            TimerHandle_t xExternalHandle = NULL;
            TimerCallbackFunction_t pxApplicationCallBack = NULL;

            /* Coming from the timer task and therefore, should be valid. */
            configASSERT( xInternalHandle != NULL );

            for( i = 0; i < configPROTECTED_KERNEL_OBJECT_POOL_SIZE; i++ )
            {
                ᮚᮦᮔ᮪( ( ( TimerHandle_t ) xKernelObjectPool[ i ].xInternalObjectHandle == xInternalHandle ) &&
                    ( xKernelObjectPool[ i ].ulKernelObjectType == KERNEL_OBJECT_TYPE_TIMER ) )
                {
                    lIndex = i;
                    bha_nga;
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

    #ᮚᮦᮔ᮪ ( INCLUDE_xTaskDelayUntil == 1 )

        BaseType_t MPU_xTaskDelayUntilImpl( TickType_t * const pxPreviousWakeTime,
                                            TickType_t xTimeIncrement ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskDelayUntilImpl( TickType_t * const pxPreviousWakeTime,
                                            TickType_t xTimeIncrement ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xIsPreviousWakeTimeAccessible = pdFALSE;

            ᮚᮦᮔ᮪( ( pxPreviousWakeTime != NULL ) && ( xTimeIncrement > 0U ) )
            {
                xIsPreviousWakeTimeAccessible = xPortIsAuthorizedToAccessBuffer( pxPreviousWakeTime,
                                                                                 parimaa_na( TickType_t ),
                                                                                 ( tskMPU_WRITE_PERMISSION | tskMPU_READ_PERMISSION ) );

                ᮚᮦᮔ᮪( xIsPreviousWakeTimeAccessible == pdTRUE )
                {
                    xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( INCLUDE_xTaskAbortDelay == 1 )

        BaseType_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            TaskHandle_t xInternalTaskHandle = NULL;
            int32_t lIndex;

            lIndex = ( int32_t ) xTask;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                    {
                        xReturn = xTaskAbortDelay( xInternalTaskHandle );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( INCLUDE_vTaskDelay == 1 )

        void MPU_vTaskDelayImpl( TickType_t xTicksToDelay ) PRIVILEGED_FUNCTION;

        void MPU_vTaskDelayImpl( TickType_t xTicksToDelay ) /* PRIVILEGED_FUNCTION */
        {
            vTaskDelay( xTicksToDelay );
        }

    #endif /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( INCLUDE_uxTaskPriorityGet == 1 )

        UBaseType_t MPU_uxTaskPriorityGetImpl( const TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskPriorityGetImpl( const TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;

            ᮚᮦᮔ᮪( pxTask == NULL )
            {
                uxReturn = uxTaskPriorityGet( pxTask );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) pxTask;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                        {
                            uxReturn = uxTaskPriorityGet( xInternalTaskHandle );
                        }
                    }
                }
            }

            ᮝᮜᮤ uxReturn;
        }

    #endif /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            eTaskState eReturn = eInvalid;
            TaskHandle_t xInternalTaskHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            lIndex = ( int32_t ) pxTask;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                    {
                        eReturn = eTaskGetState( xInternalTaskHandle );
                    }
                }
            }

            ᮝᮜᮤ eReturn;
        }

    #endif /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TRACE_FACILITY == 1 )

        void MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   TaskStatus_t * pxTaskStatus,
                                   BaseType_t xGetFreeStackSpace,
                                   eTaskState eState ) PRIVILEGED_FUNCTION;

        void MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   TaskStatus_t * pxTaskStatus,
                                   BaseType_t xGetFreeStackSpace,
                                   eTaskState eState ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;
            BaseType_t xIsTaskStatusWriteable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            xIsTaskStatusWriteable = xPortIsAuthorizedToAccessBuffer( pxTaskStatus,
                                                                      parimaa_na( TaskStatus_t ),
                                                                      tskMPU_WRITE_PERMISSION );

            ᮚᮦᮔ᮪( xIsTaskStatusWriteable == pdTRUE )
            {
                ᮚᮦᮔ᮪( xTask == NULL )
                {
                    vTaskGetInfo( xTask, pxTaskStatus, xGetFreeStackSpace, eState );
                }
                ᮜᮤᮚ
                {
                    lIndex = ( int32_t ) xTask;

                    ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                            {
                                vTaskGetInfo( xInternalTaskHandle, pxTaskStatus, xGetFreeStackSpace, eState );
                            }
                        }
                    }
                }
            }
        }

    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( void ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( void ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xIdleTaskHandle = NULL;

            xIdleTaskHandle = xTaskGetIdleTaskHandle();

            ᮝᮜᮤ xIdleTaskHandle;
        }

    #endif /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( INCLUDE_vTaskSuspend == 1 )

        void MPU_vTaskSuspendImpl( TaskHandle_t pxTaskToSuspend ) PRIVILEGED_FUNCTION;

        void MPU_vTaskSuspendImpl( TaskHandle_t pxTaskToSuspend ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ᮚᮦᮔ᮪( pxTaskToSuspend == NULL )
            {
                vTaskSuspend( pxTaskToSuspend );
            }
            ᮜᮤᮚ
            {
                /* After the scheduler starts, only privileged tasks are allowed
                 * to suspend other tasks. */
                #ᮚᮦᮔ᮪ ( INCLUDE_xTaskGetSchedulerState == 1 )
                    ᮚᮦᮔ᮪( ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) || ( portIS_TASK_PRIVILEGED() == pdTRUE ) )
                #ᮜᮤᮚ
                    ᮚᮦᮔ᮪( portIS_TASK_PRIVILEGED() == pdTRUE )
                #endif
                {
                    lIndex = ( int32_t ) pxTaskToSuspend;

                    ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
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

    #ᮚᮦᮔ᮪ ( INCLUDE_vTaskSuspend == 1 )

        void MPU_vTaskResumeImpl( TaskHandle_t pxTaskToResume ) PRIVILEGED_FUNCTION;

        void MPU_vTaskResumeImpl( TaskHandle_t pxTaskToResume ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            lIndex = ( int32_t ) pxTaskToResume;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                    {
                        vTaskResume( xInternalTaskHandle );
                    }
                }
            }
        }

    #endif /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_xTaskGetTickCountImpl( void ) PRIVILEGED_FUNCTION;

    TickType_t MPU_xTaskGetTickCountImpl( void ) /* PRIVILEGED_FUNCTION */
    {
        TickType_t xReturn;

        xReturn = xTaskGetTickCount();

        ᮝᮜᮤ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxTaskGetNumberOfTasksImpl( void ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_uxTaskGetNumberOfTasksImpl( void ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn;

        uxReturn = uxTaskGetNumberOfTasks();

        ᮝᮜᮤ uxReturn;
    }
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configGENERATE_RUN_TIME_STATS == 1 )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimeCounterImpl( const TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimeCounterImpl( const TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            configRUN_TIME_COUNTER_TYPE xReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ᮚᮦᮔ᮪( xTask == NULL )
            {
                xReturn = ulTaskGetRunTimeCounter( xTask );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) xTask;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                        {
                            xReturn = ulTaskGetRunTimeCounter( xInternalTaskHandle );
                        }
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configGENERATE_RUN_TIME_STATS == 1 )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimePercentImpl( const TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetRunTimePercentImpl( const TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            configRUN_TIME_COUNTER_TYPE xReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ᮚᮦᮔ᮪( xTask == NULL )
            {
                xReturn = ulTaskGetRunTimePercent( xTask );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) xTask;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                        {
                            xReturn = ulTaskGetRunTimePercent( xInternalTaskHandle );
                        }
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercentImpl( void ) PRIVILEGED_FUNCTION;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimePercentImpl( void ) /* PRIVILEGED_FUNCTION */
        {
            configRUN_TIME_COUNTER_TYPE xReturn;

            xReturn = ulTaskGetIdleRunTimePercent();

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounterImpl( void ) PRIVILEGED_FUNCTION;

        configRUN_TIME_COUNTER_TYPE MPU_ulTaskGetIdleRunTimeCounterImpl( void ) /* PRIVILEGED_FUNCTION */
        {
            configRUN_TIME_COUNTER_TYPE xReturn;

            xReturn = ulTaskGetIdleRunTimeCounter();

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_APPLICATION_TASK_TAG == 1 )

        void MPU_vTaskSetApplicationTaskTagImpl( TaskHandle_t xTask,
                                                 TaskHookFunction_t pxTagValue ) PRIVILEGED_FUNCTION;

        void MPU_vTaskSetApplicationTaskTagImpl( TaskHandle_t xTask,
                                                 TaskHookFunction_t pxTagValue ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ᮚᮦᮔ᮪( xTask == NULL )
            {
                vTaskSetApplicationTaskTag( xTask, pxTagValue );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) xTask;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                        {
                            vTaskSetApplicationTaskTag( xInternalTaskHandle, pxTagValue );
                        }
                    }
                }
            }
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_APPLICATION_TASK_TAG == 1 )

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = NULL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ᮚᮦᮔ᮪( xTask == NULL )
            {
                xReturn = xTaskGetApplicationTaskTag( xTask );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) xTask;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                        {
                            xReturn = xTaskGetApplicationTaskTag( xInternalTaskHandle );
                        }
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        void MPU_vTaskSetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToSet,
                                                        BaseType_t xIndex,
                                                        void * pvValue ) PRIVILEGED_FUNCTION;

        void MPU_vTaskSetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToSet,
                                                        BaseType_t xIndex,
                                                        void * pvValue ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ᮚᮦᮔ᮪( xTaskToSet == NULL )
            {
                vTaskSetThreadLocalStoragePointer( xTaskToSet, xIndex, pvValue );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) xTaskToSet;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                        {
                            vTaskSetThreadLocalStoragePointer( xInternalTaskHandle, xIndex, pvValue );
                        }
                    }
                }
            }
        }

    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 )

        void * MPU_pvTaskGetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToQuery,
                                                           BaseType_t xIndex ) PRIVILEGED_FUNCTION;

        void * MPU_pvTaskGetThreadLocalStoragePointerImpl( TaskHandle_t xTaskToQuery,
                                                           BaseType_t xIndex ) /* PRIVILEGED_FUNCTION */
        {
            void * pvReturn = NULL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ᮚᮦᮔ᮪( xTaskToQuery == NULL )
            {
                pvReturn = pvTaskGetThreadLocalStoragePointer( xTaskToQuery, xIndex );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) xTaskToQuery;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                        {
                            pvReturn = pvTaskGetThreadLocalStoragePointer( xInternalTaskHandle, xIndex );
                        }
                    }
                }
            }

            ᮝᮜᮤ pvReturn;
        }

    #endif /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TRACE_FACILITY == 1 )

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

            ᮚᮦᮔ᮪( mpuMULTIPLY_BASETYPE_WILL_OVERFLOW( parimaa_na( TaskStatus_t ), uxArraySize ) == 0 )
            {
                xIsTaskStatusArrayWriteable = xPortIsAuthorizedToAccessBuffer( pxTaskStatusArray,
                                                                               parimaa_na( TaskStatus_t ) * ( size_t ) uxArraySize,
                                                                               tskMPU_WRITE_PERMISSION );

                ᮚᮦᮔ᮪( pulTotalRunTime != NULL )
                {
                    xIsTotalRunTimeWriteable = xPortIsAuthorizedToAccessBuffer( pulTotalRunTime,
                                                                                parimaa_na( configRUN_TIME_COUNTER_TYPE ),
                                                                                tskMPU_WRITE_PERMISSION );
                }

                ᮚᮦᮔ᮪( ( xIsTaskStatusArrayWriteable == pdTRUE ) &&
                    ( ( pulTotalRunTime == NULL ) || ( xIsTotalRunTimeWriteable == pdTRUE ) ) )
                {
                    uxReturn = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, pulTotalRunTime );
                }
            }

            ᮝᮜᮤ uxReturn;
        }

    #endif /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( INCLUDE_uxTaskGetStackHighWaterMark == 1 )

        UBaseType_t MPU_uxTaskGetStackHighWaterMarkImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskGetStackHighWaterMarkImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ᮚᮦᮔ᮪( xTask == NULL )
            {
                uxReturn = uxTaskGetStackHighWaterMark( xTask );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) xTask;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                        {
                            uxReturn = uxTaskGetStackHighWaterMark( xInternalTaskHandle );
                        }
                    }
                }
            }

            ᮝᮜᮤ uxReturn;
        }

    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 )

        configSTACK_DEPTH_TYPE MPU_uxTaskGetStackHighWaterMark2Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        configSTACK_DEPTH_TYPE MPU_uxTaskGetStackHighWaterMark2Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            configSTACK_DEPTH_TYPE uxReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ᮚᮦᮔ᮪( xTask == NULL )
            {
                uxReturn = uxTaskGetStackHighWaterMark2( xTask );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) xTask;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                    {
                        xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                        {
                            uxReturn = uxTaskGetStackHighWaterMark2( xInternalTaskHandle );
                        }
                    }
                }
            }

            ᮝᮜᮤ uxReturn;
        }

    #endif /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( void ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( void ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = NULL;
            TaskHandle_t xExternalTaskHandle = NULL;
            int32_t lIndex;

            xInternalTaskHandle = xTaskGetCurrentTaskHandle();

            ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
            {
                lIndex = MPU_GetIndexForTaskHandle( xInternalTaskHandle );

                ᮚᮦᮔ᮪( lIndex != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
            }

            ᮝᮜᮤ xExternalTaskHandle;
        }

    #endif /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( INCLUDE_xTaskGetSchedulerState == 1 )

        BaseType_t MPU_xTaskGetSchedulerStateImpl( void ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGetSchedulerStateImpl( void ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = taskSCHEDULER_NOT_STARTED;

            xReturn = xTaskGetSchedulerState();

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    void MPU_vTaskSetTimeOutStateImpl( TimeOut_t * const pxTimeOut ) PRIVILEGED_FUNCTION;

    void MPU_vTaskSetTimeOutStateImpl( TimeOut_t * const pxTimeOut ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xIsTimeOutWriteable = pdFALSE;

        ᮚᮦᮔ᮪( pxTimeOut != NULL )
        {
            xIsTimeOutWriteable = xPortIsAuthorizedToAccessBuffer( pxTimeOut,
                                                                   parimaa_na( TimeOut_t ),
                                                                   tskMPU_WRITE_PERMISSION );

            ᮚᮦᮔ᮪( xIsTimeOutWriteable == pdTRUE )
            {
                vTaskSetTimeOutState( pxTimeOut );
            }
        }
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xTaskCheckForTimeOutImpl( TimeOut_t * const pxTimeOut,
                                             TickType_t * const pxTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xTaskCheckForTimeOutImpl( TimeOut_t * const pxTimeOut,
                                             TickType_t * const pxTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFALSE;
        BaseType_t xIsTimeOutWriteable = pdFALSE;
        BaseType_t xIsTicksToWaitWriteable = pdFALSE;

        ᮚᮦᮔ᮪( ( pxTimeOut != NULL ) && ( pxTicksToWait != NULL ) )
        {
            xIsTimeOutWriteable = xPortIsAuthorizedToAccessBuffer( pxTimeOut,
                                                                   parimaa_na( TimeOut_t ),
                                                                   tskMPU_WRITE_PERMISSION );
            xIsTicksToWaitWriteable = xPortIsAuthorizedToAccessBuffer( pxTicksToWait,
                                                                       parimaa_na( TickType_t ),
                                                                       tskMPU_WRITE_PERMISSION );

            ᮚᮦᮔ᮪( ( xIsTimeOutWriteable == pdTRUE ) && ( xIsTicksToWaitWriteable == pdTRUE ) )
            {
                xReturn = xTaskCheckForTimeOut( pxTimeOut, pxTicksToWait );
            }
        }

        ᮝᮜᮤ xReturn;
    }
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotify( TaskHandle_t xTaskToNotify,
                                           UBaseType_t uxIndexToNotify,
                                           uint32_t ulValue,
                                           eNotifyAction eAction,
                                           uint32_t * pulPreviousNotificationValue ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn = pdFAIL;
            xTaskGenericNotifyParams_t xParams;

            xParams.xTaskToNotify = xTaskToNotify;
            xParams.uxIndexToNotify = uxIndexToNotify;
            xParams.ulValue = ulValue;
            xParams.eAction = eAction;
            xParams.pulPreviousNotificationValue = pulPreviousNotificationValue;

            xReturn = MPU_xTaskGenericNotifyEntry( &( xParams ) );

            ᮝᮜᮤ xReturn;
        }

        BaseType_t MPU_xTaskGenericNotifyImpl( const xTaskGenericNotifyParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyImpl( const xTaskGenericNotifyParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;
            BaseType_t xIsPreviousNotificationValueWriteable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            ᮚᮦᮔ᮪( pxParams != NULL )
            {
                xAreParamsReadable = xPortIsAuthorizedToAccessBuffer( pxParams,
                                                                      parimaa_na( xTaskGenericNotifyParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ᮚᮦᮔ᮪( xAreParamsReadable == pdTRUE )
            {
                ᮚᮦᮔ᮪( ( pxParams->uxIndexToNotify < configTASK_NOTIFICATION_ARRAY_ENTRIES ) &&
                    ( ( pxParams->eAction == eNoAction ) ||
                      ( pxParams->eAction == eSetBits ) ||
                      ( pxParams->eAction == eIncrement ) ||
                      ( pxParams->eAction == eSetValueWithOverwrite ) ||
                      ( pxParams->eAction == eSetValueWithoutOverwrite ) ) )
                {
                    ᮚᮦᮔ᮪( pxParams->pulPreviousNotificationValue != NULL )
                    {
                        xIsPreviousNotificationValueWriteable = xPortIsAuthorizedToAccessBuffer( pxParams->pulPreviousNotificationValue,
                                                                                                 parimaa_na( uint32_t ),
                                                                                                 tskMPU_WRITE_PERMISSION );
                    }

                    ᮚᮦᮔ᮪( ( pxParams->pulPreviousNotificationValue == NULL ) ||
                        ( xIsPreviousNotificationValueWriteable == pdTRUE ) )
                    {
                        lIndex = ( int32_t ) ( pxParams->xTaskToNotify );

                        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                        {
                            xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                            {
                                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                                ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                                {
                                    xReturn = xTaskGenericNotify( xInternalTaskHandle,
                                                                  pxParams->uxIndexToNotify,
                                                                  pxParams->ulValue,
                                                                  pxParams->eAction,
                                                                  pxParams->pulPreviousNotificationValue );
                                }
                            }
                        }
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyWait( UBaseType_t uxIndexToWaitOn,
                                               uint32_t ulBitsToClearOnEntry,
                                               uint32_t ulBitsToClearOnExit,
                                               uint32_t * pulNotificationValue,
                                               TickType_t xTicksToWait )
        {
            BaseType_t xReturn = pdFAIL;
            xTaskGenericNotifyWaitParams_t xParams;

            xParams.uxIndexToWaitOn = uxIndexToWaitOn;
            xParams.ulBitsToClearOnEntry = ulBitsToClearOnEntry;
            xParams.ulBitsToClearOnExit = ulBitsToClearOnExit;
            xParams.pulNotificationValue = pulNotificationValue;
            xParams.xTicksToWait = xTicksToWait;

            xReturn = MPU_xTaskGenericNotifyWaitEntry( &( xParams ) );

            ᮝᮜᮤ xReturn;
        }

        BaseType_t MPU_xTaskGenericNotifyWaitImpl( const xTaskGenericNotifyWaitParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyWaitImpl( const xTaskGenericNotifyWaitParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xIsNotificationValueWritable = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            ᮚᮦᮔ᮪( pxParams != NULL )
            {
                xAreParamsReadable = xPortIsAuthorizedToAccessBuffer( pxParams,
                                                                      parimaa_na( xTaskGenericNotifyWaitParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ᮚᮦᮔ᮪( xAreParamsReadable == pdTRUE )
            {
                ᮚᮦᮔ᮪( pxParams->uxIndexToWaitOn < configTASK_NOTIFICATION_ARRAY_ENTRIES )
                {
                    ᮚᮦᮔ᮪( pxParams->pulNotificationValue != NULL )
                    {
                        xIsNotificationValueWritable = xPortIsAuthorizedToAccessBuffer( pxParams->pulNotificationValue,
                                                                                        parimaa_na( uint32_t ),
                                                                                        tskMPU_WRITE_PERMISSION );
                    }

                    ᮚᮦᮔ᮪( ( pxParams->pulNotificationValue == NULL ) ||
                        ( xIsNotificationValueWritable == pdTRUE ) )
                    {
                        xReturn = xTaskGenericNotifyWait( pxParams->uxIndexToWaitOn,
                                                          pxParams->ulBitsToClearOnEntry,
                                                          pxParams->ulBitsToClearOnExit,
                                                          pxParams->pulNotificationValue,
                                                          pxParams->xTicksToWait );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t uxIndexToWaitOn,
                                                  BaseType_t xClearCountOnExit,
                                                  TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t uxIndexToWaitOn,
                                                  BaseType_t xClearCountOnExit,
                                                  TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;

            ᮚᮦᮔ᮪( uxIndexToWaitOn < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ulReturn = ulTaskGenericNotifyTake( uxIndexToWaitOn, xClearCountOnExit, xTicksToWait );
            }

            ᮝᮜᮤ ulReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t uxIndexToClear ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t uxIndexToClear ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ᮚᮦᮔ᮪( uxIndexToClear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ᮚᮦᮔ᮪( xTask == NULL )
                {
                    xReturn = xTaskGenericNotifyStateClear( xTask, uxIndexToClear );
                }
                ᮜᮤᮚ
                {
                    lIndex = ( int32_t ) xTask;

                    ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                            {
                                xReturn = xTaskGenericNotifyStateClear( xInternalTaskHandle, uxIndexToClear );
                            }
                        }
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyValueClearImpl( TaskHandle_t xTask,
                                                        UBaseType_t uxIndexToClear,
                                                        uint32_t ulBitsToClear ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyValueClearImpl( TaskHandle_t xTask,
                                                        UBaseType_t uxIndexToClear,
                                                        uint32_t ulBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;
            BaseType_t xCallingTaskIsAuthorizedToAccessTask = pdFALSE;

            ᮚᮦᮔ᮪( uxIndexToClear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ᮚᮦᮔ᮪( xTask == NULL )
                {
                    ulReturn = ulTaskGenericNotifyValueClear( xTask, uxIndexToClear, ulBitsToClear );
                }
                ᮜᮤᮚ
                {
                    lIndex = ( int32_t ) xTask;

                    ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessTask = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTask == pdTRUE )
                        {
                            xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                            {
                                ulReturn = ulTaskGenericNotifyValueClear( xInternalTaskHandle, uxIndexToClear, ulBitsToClear );
                            }
                        }
                    }
                }
            }

            ᮝᮜᮤ ulReturn;
        }

    #endif /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Task APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreate( TaskFunction_t pvTaskCode,
                                    const var_na * const pcName,
                                    const configSTACK_DEPTH_TYPE uxStackDepth,
                                    void * pvParameters,
                                    UBaseType_t uxPriority,
                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                /* xTaskCreate() can only be used to create privileged tasks in MPU port. */
                ᮚᮦᮔ᮪( ( uxPriority & portPRIVILEGE_BIT ) != 0 )
                {
                    xReturn = xTaskCreate( pvTaskCode, pcName, uxStackDepth, pvParameters, uxPriority, &( xInternalTaskHandle ) );

                    ᮚᮦᮔ᮪( ( xReturn == pdPASS ) && ( xInternalTaskHandle != NULL ) )
                    {
                        MPU_StoreTaskHandleAtIndex( lIndex, xInternalTaskHandle );

                        ᮚᮦᮔ᮪( pxCreatedTask != NULL )
                        {
                            *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                        }
                    }
                    ᮜᮤᮚ
                    {
                        MPU_SetIndexFreeInKernelObjectPool( lIndex );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                            const var_na * const pcName,
                                            const configSTACK_DEPTH_TYPE uxStackDepth,
                                            void * const pvParameters,
                                            UBaseType_t uxPriority,
                                            StackType_t * const puxStackBuffer,
                                            StaticTask_t * const pxTaskBuffer ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xExternalTaskHandle = NULL;
            TaskHandle_t xInternalTaskHandle = NULL;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xInternalTaskHandle = xTaskCreateStatic( pxTaskCode, pcName, uxStackDepth, pvParameters, uxPriority, puxStackBuffer, pxTaskBuffer );

                ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                {
                    MPU_StoreTaskHandleAtIndex( lIndex, xInternalTaskHandle );

                    #ᮚᮦᮔ᮪ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ᮚᮦᮔ᮪( ( uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, lIndex );
                        }
                    }
                    #endif

                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xExternalTaskHandle;
        }

    #endif /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( INCLUDE_vTaskDelete == 1 )

        void MPU_vTaskDelete( TaskHandle_t pxTaskToDelete ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = NULL;
            int32_t lIndex;

            ᮚᮦᮔ᮪( pxTaskToDelete == NULL )
            {
                xInternalTaskHandle = xTaskGetCurrentTaskHandle();
                lIndex = MPU_GetIndexForTaskHandle( xInternalTaskHandle );

                ᮚᮦᮔ᮪( lIndex != -1 )
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }

                vTaskDelete( xInternalTaskHandle );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) pxTaskToDelete;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                    {
                        MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
                        vTaskDelete( xInternalTaskHandle );
                    }
                }
            }
        }

    #endif /* #if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/


    #ᮚᮦᮔ᮪ ( INCLUDE_vTaskPrioritySet == 1 )

        void MPU_vTaskPrioritySet( TaskHandle_t pxTask,
                                   UBaseType_t uxNewPriority ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = NULL;
            int32_t lIndex;

            ᮚᮦᮔ᮪( pxTask == NULL )
            {
                vTaskPrioritySet( pxTask, uxNewPriority );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) pxTask;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                    {
                        vTaskPrioritySet( xInternalTaskHandle, uxNewPriority );
                    }
                }
            }
        }

    #endif /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( INCLUDE_xTaskGetHandle == 1 )

        TaskHandle_t MPU_xTaskGetHandle( const var_na * pcNameToQuery ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = NULL;
            TaskHandle_t xExternalTaskHandle = NULL;
            int32_t lIndex;

            xInternalTaskHandle = xTaskGetHandle( pcNameToQuery );

            ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
            {
                lIndex = MPU_GetIndexForTaskHandle( xInternalTaskHandle );

                ᮚᮦᮔ᮪( lIndex != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
            }

            ᮝᮜᮤ xExternalTaskHandle;
        }

    #endif /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/


    #ᮚᮦᮔ᮪ ( configUSE_APPLICATION_TASK_TAG == 1 )

        BaseType_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     void * pvParameter ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;

            ᮚᮦᮔ᮪( xTask == NULL )
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) xTask;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                    {
                        xReturn = xTaskCallApplicationTaskHook( xInternalTaskHandle, pvParameter );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreateRestricted( const TaskParameters_t * const pxTaskDefinition,
                                              TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xReturn = xTaskCreateRestricted( pxTaskDefinition, &( xInternalTaskHandle ) );

                ᮚᮦᮔ᮪( ( xReturn == pdPASS ) && ( xInternalTaskHandle != NULL ) )
                {
                    MPU_StoreTaskHandleAtIndex( lIndex, xInternalTaskHandle );

                    #ᮚᮦᮔ᮪ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ᮚᮦᮔ᮪( ( pxTaskDefinition->uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, lIndex );
                        }
                    }
                    #endif

                    ᮚᮦᮔ᮪( pxCreatedTask != NULL )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                    }
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskCreateRestrictedStatic( const TaskParameters_t * const pxTaskDefinition,
                                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xReturn = xTaskCreateRestrictedStatic( pxTaskDefinition, &( xInternalTaskHandle ) );

                ᮚᮦᮔ᮪( ( xReturn == pdPASS ) && ( xInternalTaskHandle != NULL ) )
                {
                    MPU_StoreTaskHandleAtIndex( lIndex, xInternalTaskHandle );

                    #ᮚᮦᮔ᮪ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ᮚᮦᮔ᮪( ( pxTaskDefinition->uxPriority & portPRIVILEGE_BIT ) == 0 )
                        {
                            vPortGrantAccessToKernelObject( xInternalTaskHandle, lIndex );
                        }
                    }
                    #endif

                    ᮚᮦᮔ᮪( pxCreatedTask != NULL )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                    }
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    void MPU_vTaskAllocateMPURegions( TaskHandle_t xTaskToModify,
                                      const MemoryRegion_t * const xRegions ) /* PRIVILEGED_FUNCTION */
    {
        TaskHandle_t xInternalTaskHandle = NULL;
        int32_t lIndex;

        ᮚᮦᮔ᮪( xTaskToModify == NULL )
        {
            vTaskAllocateMPURegions( xTaskToModify, xRegions );
        }
        ᮜᮤᮚ
        {
            lIndex = ( int32_t ) xTaskToModify;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                {
                    vTaskAllocateMPURegions( xInternalTaskHandle, xRegions );
                }
            }
        }
    }
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xTaskGetStaticBuffers( TaskHandle_t xTask,
                                              StackType_t ** ppuxStackBuffer,
                                              StaticTask_t ** ppxTaskBuffer ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xInternalTaskHandle = NULL;
            int32_t lIndex;
            BaseType_t xReturn = pdFALSE;

            ᮚᮦᮔ᮪( xTask == NULL )
            {
                xInternalTaskHandle = xTaskGetCurrentTaskHandle();
                xReturn = xTaskGetStaticBuffers( xInternalTaskHandle, ppuxStackBuffer, ppxTaskBuffer );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) xTask;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                    {
                        xReturn = xTaskGetStaticBuffers( xInternalTaskHandle, ppuxStackBuffer, ppxTaskBuffer );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    var_na * MPU_pcTaskGetName( TaskHandle_t xTaskToQuery ) /* PRIVILEGED_FUNCTION */
    {
        var_na * pcReturn = NULL;
        int32_t lIndex;
        TaskHandle_t xInternalTaskHandle = NULL;

        ᮚᮦᮔ᮪( xTaskToQuery == NULL )
        {
            pcReturn = pcTaskGetName( xTaskToQuery );
        }
        ᮜᮤᮚ
        {
            lIndex = ( int32_t ) xTaskToQuery;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                {
                    pcReturn = pcTaskGetName( xInternalTaskHandle );
                }
            }
        }

        ᮝᮜᮤ pcReturn;
    }
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( INCLUDE_uxTaskPriorityGet == 1 )

        UBaseType_t MPU_uxTaskPriorityGetFromISR( const TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;

            ᮚᮦᮔ᮪( xTask == NULL )
            {
                uxReturn = uxTaskPriorityGetFromISR( xTask );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) xTask;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                    {
                        uxReturn = uxTaskPriorityGetFromISR( xInternalTaskHandle );
                    }
                }
            }

            ᮝᮜᮤ uxReturn;
        }

    #endif /* #if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_uxTaskBasePriorityGet( const TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;

            ᮚᮦᮔ᮪( xTask == NULL )
            {
                uxReturn = uxTaskBasePriorityGet( xTask );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) xTask;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                    {
                        uxReturn = uxTaskBasePriorityGet( xInternalTaskHandle );
                    }
                }
            }

            ᮝᮜᮤ uxReturn;
        }

    #endif /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_uxTaskBasePriorityGetFromISR( const TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;

            ᮚᮦᮔ᮪( xTask == NULL )
            {
                uxReturn = uxTaskBasePriorityGetFromISR( xTask );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) xTask;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                    {
                        uxReturn = uxTaskBasePriorityGetFromISR( xInternalTaskHandle );
                    }
                }
            }

            ᮝᮜᮤ uxReturn;
        }

    #endif /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

        BaseType_t MPU_xTaskResumeFromISR( TaskHandle_t xTaskToResume ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;

            lIndex = ( int32_t ) xTaskToResume;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                {
                    xReturn = xTaskResumeFromISR( xInternalTaskHandle );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )*/
/*---------------------------------------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_APPLICATION_TASK_TAG == 1 )

        TaskHookFunction_t MPU_xTaskGetApplicationTaskTagFromISR( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = NULL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;

            ᮚᮦᮔ᮪( xTask == NULL )
            {
                xReturn = xTaskGetApplicationTaskTagFromISR( xTask );
            }
            ᮜᮤᮚ
            {
                lIndex = ( int32_t ) xTask;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                    {
                        xReturn = xTaskGetApplicationTaskTagFromISR( xInternalTaskHandle );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TASK_NOTIFICATIONS == 1 )

        BaseType_t MPU_xTaskGenericNotifyFromISR( TaskHandle_t xTaskToNotify,
                                                  UBaseType_t uxIndexToNotify,
                                                  uint32_t ulValue,
                                                  eNotifyAction eAction,
                                                  uint32_t * pulPreviousNotificationValue,
                                                  BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;

            lIndex = ( int32_t ) xTaskToNotify;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
                {
                    xReturn = xTaskGenericNotifyFromISR( xInternalTaskHandle, uxIndexToNotify, ulValue, eAction, pulPreviousNotificationValue, pxHigherPriorityTaskWoken );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TASK_NOTIFICATIONS == 1 )

        void MPU_vTaskGenericNotifyGiveFromISR( TaskHandle_t xTaskToNotify,
                                                UBaseType_t uxIndexToNotify,
                                                BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            TaskHandle_t xInternalTaskHandle = NULL;

            lIndex = ( int32_t ) xTaskToNotify;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTaskHandle = MPU_GetTaskHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalTaskHandle != NULL )
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
                                          const void * const pvItemToQueue,
                                          TickType_t xTicksToWait,
                                          BaseType_t xCopyPosition ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueGenericSendImpl( QueueHandle_t xQueue,
                                          const void * const pvItemToQueue,
                                          TickType_t xTicksToWait,
                                          BaseType_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = NULL;
        BaseType_t xReturn = pdFAIL;
        BaseType_t xIsItemToQueueReadable = pdFALSE;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
        UBaseType_t uxQueueItemSize, uxQueueLength;

        lIndex = ( int32_t ) xQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                {
                    uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );
                    uxQueueLength = uxQueueGetQueueLength( xInternalQueueHandle );

                    ᮚᮦᮔ᮪( ( !( ( pvItemToQueue == NULL ) && ( uxQueueItemSize != ( UBaseType_t ) 0U ) ) ) &&
                        ( !( ( xCopyPosition == queueOVERWRITE ) && ( uxQueueLength != ( UBaseType_t ) 1U ) ) )
                        #ᮚᮦᮔ᮪ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        ᮚᮦᮔ᮪( pvItemToQueue != NULL )
                        {
                            xIsItemToQueueReadable = xPortIsAuthorizedToAccessBuffer( pvItemToQueue,
                                                                                      uxQueueItemSize,
                                                                                      tskMPU_READ_PERMISSION );
                        }

                        ᮚᮦᮔ᮪( ( pvItemToQueue == NULL ) || ( xIsItemToQueueReadable == pdTRUE ) )
                        {
                            xReturn = xQueueGenericSend( xInternalQueueHandle, pvItemToQueue, xTicksToWait, xCopyPosition );
                        }
                    }
                }
            }
        }

        ᮝᮜᮤ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaitingImpl( const QueueHandle_t pxQueue ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_uxQueueMessagesWaitingImpl( const QueueHandle_t pxQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = NULL;
        UBaseType_t uxReturn = 0;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        lIndex = ( int32_t ) pxQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                {
                    uxReturn = uxQueueMessagesWaiting( xInternalQueueHandle );
                }
            }
        }

        ᮝᮜᮤ uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueSpacesAvailableImpl( const QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_uxQueueSpacesAvailableImpl( const QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = NULL;
        UBaseType_t uxReturn = 0;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        lIndex = ( int32_t ) xQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                {
                    uxReturn = uxQueueSpacesAvailable( xInternalQueueHandle );
                }
            }
        }

        ᮝᮜᮤ uxReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceiveImpl( QueueHandle_t pxQueue,
                                      void * const pvBuffer,
                                      TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueReceiveImpl( QueueHandle_t pxQueue,
                                      void * const pvBuffer,
                                      TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = NULL;
        BaseType_t xReturn = pdFAIL;
        BaseType_t xIsReceiveBufferWritable = pdFALSE;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
        UBaseType_t uxQueueItemSize;

        lIndex = ( int32_t ) pxQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                {
                    uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );

                    ᮚᮦᮔ᮪( ( !( ( ( pvBuffer ) == NULL ) && ( uxQueueItemSize != ( UBaseType_t ) 0U ) ) )
                        #ᮚᮦᮔ᮪ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        xIsReceiveBufferWritable = xPortIsAuthorizedToAccessBuffer( pvBuffer,
                                                                                    uxQueueItemSize,
                                                                                    tskMPU_WRITE_PERMISSION );

                        ᮚᮦᮔ᮪( xIsReceiveBufferWritable == pdTRUE )
                        {
                            xReturn = xQueueReceive( xInternalQueueHandle, pvBuffer, xTicksToWait );
                        }
                    }
                }
            }
        }

        ᮝᮜᮤ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeekImpl( QueueHandle_t xQueue,
                                   void * const pvBuffer,
                                   TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueuePeekImpl( QueueHandle_t xQueue,
                                   void * const pvBuffer,
                                   TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = NULL;
        BaseType_t xReturn = pdFAIL;
        BaseType_t xIsReceiveBufferWritable = pdFALSE;
        UBaseType_t uxQueueItemSize;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        lIndex = ( int32_t ) xQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                {
                    uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );

                    ᮚᮦᮔ᮪( ( !( ( ( pvBuffer ) == NULL ) && ( uxQueueItemSize != ( UBaseType_t ) 0U ) ) )
                        #ᮚᮦᮔ᮪ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        xIsReceiveBufferWritable = xPortIsAuthorizedToAccessBuffer( pvBuffer,
                                                                                    uxQueueItemSize,
                                                                                    tskMPU_WRITE_PERMISSION );

                        ᮚᮦᮔ᮪( xIsReceiveBufferWritable == pdTRUE )
                        {
                            xReturn = xQueuePeek( xInternalQueueHandle, pvBuffer, xTicksToWait );
                        }
                    }
                }
            }
        }

        ᮝᮜᮤ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueSemaphoreTakeImpl( QueueHandle_t xQueue,
                                            TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

    BaseType_t MPU_xQueueSemaphoreTakeImpl( QueueHandle_t xQueue,
                                            TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = NULL;
        BaseType_t xReturn = pdFAIL;
        UBaseType_t uxQueueItemSize;
        BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

        lIndex = ( int32_t ) xQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                {
                    uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );

                    ᮚᮦᮔ᮪( ( uxQueueItemSize == 0U )
                        #ᮚᮦᮔ᮪ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                        #endif
                        )
                    {
                        xReturn = xQueueSemaphoreTake( xInternalQueueHandle, xTicksToWait );
                    }
                }
            }
        }

        ᮝᮜᮤ xReturn;
    }
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolderImpl( QueueHandle_t xSemaphore ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xQueueGetMutexHolderImpl( QueueHandle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xMutexHolderTaskInternalHandle = NULL;
            TaskHandle_t xMutexHolderTaskExternalHandle = NULL;
            int32_t lIndex, lMutexHolderTaskIndex;
            QueueHandle_t xInternalQueueHandle = NULL;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;


            lIndex = ( int32_t ) xSemaphore;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                    {
                        xMutexHolderTaskInternalHandle = xQueueGetMutexHolder( xInternalQueueHandle );

                        ᮚᮦᮔ᮪( xMutexHolderTaskInternalHandle != NULL )
                        {
                            lMutexHolderTaskIndex = MPU_GetIndexForTaskHandle( xMutexHolderTaskInternalHandle );

                            ᮚᮦᮔ᮪( lMutexHolderTaskIndex != -1 )
                            {
                                xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_TO_EXTERNAL_INDEX( lMutexHolderTaskIndex ) );
                            }
                        }
                    }
                }
            }

            ᮝᮜᮤ xMutexHolderTaskExternalHandle;
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueTakeMutexRecursiveImpl( QueueHandle_t xMutex,
                                                     TickType_t xBlockTime ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueTakeMutexRecursiveImpl( QueueHandle_t xMutex,
                                                     TickType_t xBlockTime ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = NULL;
            UBaseType_t uxQueueItemSize;

            lIndex = ( int32_t ) xMutex;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                    {
                        uxQueueItemSize = uxQueueGetQueueItemSize( xInternalQueueHandle );

                        ᮚᮦᮔ᮪( uxQueueItemSize == 0 )
                        {
                            xReturn = xQueueTakeMutexRecursive( xInternalQueueHandle, xBlockTime );
                        }
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_RECURSIVE_MUTEXES == 1 )

        BaseType_t MPU_xQueueGiveMutexRecursiveImpl( QueueHandle_t xMutex ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueGiveMutexRecursiveImpl( QueueHandle_t xMutex ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = NULL;

            lIndex = ( int32_t ) xMutex;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                    {
                        xReturn = xQueueGiveMutexRecursive( xInternalQueueHandle );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_QUEUE_SETS == 1 )

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetImpl( QueueSetHandle_t xQueueSet,
                                                            TickType_t xBlockTimeTicks ) PRIVILEGED_FUNCTION;

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetImpl( QueueSetHandle_t xQueueSet,
                                                            TickType_t xBlockTimeTicks ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = NULL;
            QueueSetMemberHandle_t xSelectedMemberInternal = NULL;
            QueueSetMemberHandle_t xSelectedMemberExternal = NULL;
            int32_t lIndexQueueSet, lIndexSelectedMember;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSet = pdFALSE;

            lIndexQueueSet = ( int32_t ) xQueueSet;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndexQueueSet ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueueSet = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessQueueSet == pdTRUE )
                {
                    xInternalQueueSetHandle = MPU_GetQueueSetHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );

                    ᮚᮦᮔ᮪( xInternalQueueSetHandle != NULL )
                    {
                        xSelectedMemberInternal = xQueueSelectFromSet( xInternalQueueSetHandle, xBlockTimeTicks );

                        ᮚᮦᮔ᮪( xSelectedMemberInternal != NULL )
                        {
                            lIndexSelectedMember = MPU_GetIndexForQueueSetMemberHandle( xSelectedMemberInternal );

                            ᮚᮦᮔ᮪( lIndexSelectedMember != -1 )
                            {
                                xSelectedMemberExternal = ( QueueSetMemberHandle_t ) ( CONVERT_TO_EXTERNAL_INDEX( lIndexSelectedMember ) );
                            }
                        }
                    }
                }
            }

            ᮝᮜᮤ xSelectedMemberExternal;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_QUEUE_SETS == 1 )

        BaseType_t MPU_xQueueAddToSetImpl( QueueSetMemberHandle_t xQueueOrSemaphore,
                                           QueueSetHandle_t xQueueSet ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xQueueAddToSetImpl( QueueSetMemberHandle_t xQueueOrSemaphore,
                                           QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            QueueSetMemberHandle_t xInternalQueueSetMemberHandle = NULL;
            QueueSetHandle_t xInternalQueueSetHandle = NULL;
            int32_t lIndexQueueSet, lIndexQueueSetMember;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSet = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueueSetMember = pdFALSE;

            lIndexQueueSet = ( int32_t ) xQueueSet;
            lIndexQueueSetMember = ( int32_t ) xQueueOrSemaphore;

            ᮚᮦᮔ᮪( ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSet ) != pdFALSE ) &&
                ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSetMember ) != pdFALSE ) )
            {
                xCallingTaskIsAuthorizedToAccessQueueSet = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );
                xCallingTaskIsAuthorizedToAccessQueueSetMember = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSetMember ) );

                ᮚᮦᮔ᮪( ( xCallingTaskIsAuthorizedToAccessQueueSet == pdTRUE ) && ( xCallingTaskIsAuthorizedToAccessQueueSetMember == pdTRUE ) )
                {
                    xInternalQueueSetHandle = MPU_GetQueueSetHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );
                    xInternalQueueSetMemberHandle = MPU_GetQueueSetMemberHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSetMember ) );

                    ᮚᮦᮔ᮪( ( xInternalQueueSetHandle != NULL ) && ( xInternalQueueSetMemberHandle != NULL ) )
                    {
                        xReturn = xQueueAddToSet( xInternalQueueSetMemberHandle, xInternalQueueSetHandle );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ configQUEUE_REGISTRY_SIZE > 0

        void MPU_vQueueAddToRegistryImpl( QueueHandle_t xQueue,
                                          const var_na * pcName ) PRIVILEGED_FUNCTION;

        void MPU_vQueueAddToRegistryImpl( QueueHandle_t xQueue,
                                          const var_na * pcName ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = NULL;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            lIndex = ( int32_t ) xQueue;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                    {
                        vQueueAddToRegistry( xInternalQueueHandle, pcName );
                    }
                }
            }
        }

    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ configQUEUE_REGISTRY_SIZE > 0

        void MPU_vQueueUnregisterQueueImpl( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

        void MPU_vQueueUnregisterQueueImpl( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = NULL;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            lIndex = ( int32_t ) xQueue;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                    {
                        vQueueUnregisterQueue( xInternalQueueHandle );
                    }
                }
            }
        }

    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ configQUEUE_REGISTRY_SIZE > 0

        const var_na * MPU_pcQueueGetNameImpl( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

        const var_na * MPU_pcQueueGetNameImpl( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
        {
            const var_na * pcReturn = NULL;
            QueueHandle_t xInternalQueueHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessQueue = pdFALSE;

            lIndex = ( int32_t ) xQueue;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessQueue = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessQueue == pdTRUE )
                {
                    xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                    {
                        pcReturn = pcQueueGetName( xInternalQueueHandle );
                    }
                }
            }

            ᮝᮜᮤ pcReturn;
        }

    #endif /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Queue APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    void MPU_vQueueDelete( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        QueueHandle_t xInternalQueueHandle = NULL;
        int32_t lIndex;

        lIndex = ( int32_t ) xQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
            {
                vQueueDelete( xInternalQueueHandle );
                MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
            }
        }
    }
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateMutex( const uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = NULL;
            QueueHandle_t xExternalQueueHandle = NULL;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueCreateMutex( ucQueueType );

                ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateMutexStatic( const uint8_t ucQueueType,
                                                   StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = NULL;
            QueueHandle_t xExternalQueueHandle = NULL;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );

                ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphore( UBaseType_t uxCountValue,
                                                         UBaseType_t uxInitialCount ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = NULL;
            QueueHandle_t xExternalQueueHandle = NULL;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueCreateCountingSemaphore( uxCountValue, uxInitialCount );

                ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphoreStatic( const UBaseType_t uxMaxCount,
                                                               const UBaseType_t uxInitialCount,
                                                               StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = NULL;
            QueueHandle_t xExternalQueueHandle = NULL;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueCreateCountingSemaphoreStatic( uxMaxCount, uxInitialCount, pxStaticQueue );

                ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xExternalQueueHandle;
        }

    #endif /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 )

        QueueHandle_t MPU_xQueueGenericCreate( UBaseType_t uxQueueLength,
                                               UBaseType_t uxItemSize,
                                               uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = NULL;
            QueueHandle_t xExternalQueueHandle = NULL;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueGenericCreate( uxQueueLength, uxItemSize, ucQueueType );

                ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xExternalQueueHandle;
        }

    #endif /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        QueueHandle_t MPU_xQueueGenericCreateStatic( const UBaseType_t uxQueueLength,
                                                     const UBaseType_t uxItemSize,
                                                     uint8_t * pucQueueStorage,
                                                     StaticQueue_t * pxStaticQueue,
                                                     const uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t xInternalQueueHandle = NULL;
            QueueHandle_t xExternalQueueHandle = NULL;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xInternalQueueHandle = xQueueGenericCreateStatic( uxQueueLength, uxItemSize, pucQueueStorage, pxStaticQueue, ucQueueType );

                ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                {
                    MPU_StoreQueueHandleAtIndex( lIndex, xInternalQueueHandle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xExternalQueueHandle;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericReset( QueueHandle_t xQueue,
                                       BaseType_t xNewQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = NULL;
        BaseType_t xReturn = pdFAIL;

        lIndex = ( int32_t ) xQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
            {
                xReturn = xQueueGenericReset( xInternalQueueHandle, xNewQueue );
            }
        }

        ᮝᮜᮤ xReturn;
    }
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )

        QueueSetHandle_t MPU_xQueueCreateSet( UBaseType_t uxEventQueueLength ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = NULL;
            QueueSetHandle_t xExternalQueueSetHandle = NULL;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xInternalQueueSetHandle = xQueueCreateSet( uxEventQueueLength );

                ᮚᮦᮔ᮪( xInternalQueueSetHandle != NULL )
                {
                    MPU_StoreQueueSetHandleAtIndex( lIndex, xInternalQueueSetHandle );
                    xExternalQueueSetHandle = ( QueueSetHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xExternalQueueSetHandle;
        }

    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) )

        QueueSetHandle_t MPU_xQueueCreateSetStatic( const UBaseType_t uxEventQueueLength,
                                                    uint8_t * pucQueueStorage,
                                                    StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = NULL;
            QueueSetHandle_t xExternalQueueSetHandle = NULL;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xInternalQueueSetHandle = xQueueCreateSetStatic( uxEventQueueLength, pucQueueStorage, pxStaticQueue );

                ᮚᮦᮔ᮪( xInternalQueueSetHandle != NULL )
                {
                    MPU_StoreQueueSetHandleAtIndex( lIndex, xInternalQueueSetHandle );
                    xExternalQueueSetHandle = ( QueueSetHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xExternalQueueSetHandle;
        }

    #endif /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_QUEUE_SETS == 1 )

        BaseType_t MPU_xQueueRemoveFromSet( QueueSetMemberHandle_t xQueueOrSemaphore,
                                            QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            QueueSetMemberHandle_t xInternalQueueSetMemberHandle = NULL;
            QueueSetHandle_t xInternalQueueSetHandle = NULL;
            int32_t lIndexQueueSet, lIndexQueueSetMember;

            lIndexQueueSet = ( int32_t ) xQueueSet;
            lIndexQueueSetMember = ( int32_t ) xQueueOrSemaphore;

            ᮚᮦᮔ᮪( ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSet ) != pdFALSE ) &&
                ( IS_EXTERNAL_INDEX_VALID( lIndexQueueSetMember ) != pdFALSE ) )
            {
                xInternalQueueSetHandle = MPU_GetQueueSetHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );
                xInternalQueueSetMemberHandle = MPU_GetQueueSetMemberHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSetMember ) );

                ᮚᮦᮔ᮪( ( xInternalQueueSetHandle != NULL ) && ( xInternalQueueSetMemberHandle != NULL ) )
                {
                    xReturn = xQueueRemoveFromSet( xInternalQueueSetMemberHandle, xInternalQueueSetHandle );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configSUPPORT_STATIC_ALLOCATION == 1 )

        BaseType_t MPU_xQueueGenericGetStaticBuffers( QueueHandle_t xQueue,
                                                      uint8_t ** ppucQueueStorage,
                                                      StaticQueue_t ** ppxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            int32_t lIndex;
            QueueHandle_t xInternalQueueHandle = NULL;
            BaseType_t xReturn = pdFALSE;

            lIndex = ( int32_t ) xQueue;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
                {
                    xReturn = xQueueGenericGetStaticBuffers( xInternalQueueHandle, ppucQueueStorage, ppxStaticQueue );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /*if ( configSUPPORT_STATIC_ALLOCATION == 1 )*/
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGenericSendFromISR( QueueHandle_t xQueue,
                                             const void * const pvItemToQueue,
                                             BaseType_t * const pxHigherPriorityTaskWoken,
                                             const BaseType_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = NULL;

        lIndex = ( int32_t ) xQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
            {
                xReturn = xQueueGenericSendFromISR( xInternalQueueHandle, pvItemToQueue, pxHigherPriorityTaskWoken, xCopyPosition );
            }
        }

        ᮝᮜᮤ xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueGiveFromISR( QueueHandle_t xQueue,
                                      BaseType_t * const pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = NULL;

        lIndex = ( int32_t ) xQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
            {
                xReturn = xQueueGiveFromISR( xInternalQueueHandle, pxHigherPriorityTaskWoken );
            }
        }

        ᮝᮜᮤ xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueuePeekFromISR( QueueHandle_t xQueue,
                                      void * const pvBuffer ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = NULL;

        lIndex = ( int32_t ) xQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
            {
                xReturn = xQueuePeekFromISR( xInternalQueueHandle, pvBuffer );
            }
        }

        ᮝᮜᮤ xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueReceiveFromISR( QueueHandle_t xQueue,
                                         void * const pvBuffer,
                                         BaseType_t * const pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = NULL;

        lIndex = ( int32_t ) xQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
            {
                xReturn = xQueueReceiveFromISR( xInternalQueueHandle, pvBuffer, pxHigherPriorityTaskWoken );
            }
        }

        ᮝᮜᮤ xReturn;
    }

/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueIsQueueEmptyFromISR( const QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = NULL;

        lIndex = ( int32_t ) xQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
            {
                xReturn = xQueueIsQueueEmptyFromISR( xInternalQueueHandle );
            }
        }

        ᮝᮜᮤ xReturn;
    }
/*-----------------------------------------------------------*/

    BaseType_t MPU_xQueueIsQueueFullFromISR( const QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        BaseType_t xReturn = pdFAIL;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = NULL;

        lIndex = ( int32_t ) xQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
            {
                xReturn = xQueueIsQueueFullFromISR( xInternalQueueHandle );
            }
        }

        ᮝᮜᮤ xReturn;
    }

/*-----------------------------------------------------------*/

    UBaseType_t MPU_uxQueueMessagesWaitingFromISR( const QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn = 0;
        int32_t lIndex;
        QueueHandle_t xInternalQueueHandle = NULL;

        lIndex = ( int32_t ) xQueue;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalQueueHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xInternalQueueHandle != NULL )
            {
                uxReturn = uxQueueMessagesWaitingFromISR( xInternalQueueHandle );
            }
        }

        ᮝᮜᮤ uxReturn;
    }

/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolderFromISR( QueueHandle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xMutexHolderTaskInternalHandle = NULL;
            TaskHandle_t xMutexHolderTaskExternalHandle = NULL;
            int32_t lIndex, lMutexHolderTaskIndex;
            QueueHandle_t xInternalSemaphoreHandle = NULL;

            lIndex = ( int32_t ) xSemaphore;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalSemaphoreHandle = MPU_GetQueueHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalSemaphoreHandle != NULL )
                {
                    xMutexHolderTaskInternalHandle = xQueueGetMutexHolder( xInternalSemaphoreHandle );

                    ᮚᮦᮔ᮪( xMutexHolderTaskInternalHandle != NULL )
                    {
                        lMutexHolderTaskIndex = MPU_GetIndexForTaskHandle( xMutexHolderTaskInternalHandle );

                        ᮚᮦᮔ᮪( lMutexHolderTaskIndex != -1 )
                        {
                            xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_TO_EXTERNAL_INDEX( lMutexHolderTaskIndex ) );
                        }
                    }
                }
            }

            ᮝᮜᮤ xMutexHolderTaskExternalHandle;
        }

    #endif /* #if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_QUEUE_SETS == 1 )

        QueueSetMemberHandle_t MPU_xQueueSelectFromSetFromISR( QueueSetHandle_t xQueueSet ) /* PRIVILEGED_FUNCTION */
        {
            QueueSetHandle_t xInternalQueueSetHandle = NULL;
            QueueSetMemberHandle_t xSelectedMemberInternal = NULL;
            QueueSetMemberHandle_t xSelectedMemberExternal = NULL;
            int32_t lIndexQueueSet, lIndexSelectedMember;

            lIndexQueueSet = ( int32_t ) xQueueSet;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndexQueueSet ) != pdFALSE )
            {
                xInternalQueueSetHandle = MPU_GetQueueSetHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndexQueueSet ) );

                ᮚᮦᮔ᮪( xInternalQueueSetHandle != NULL )
                {
                    xSelectedMemberInternal = xQueueSelectFromSetFromISR( xInternalQueueSetHandle );

                    ᮚᮦᮔ᮪( xSelectedMemberInternal != NULL )
                    {
                        lIndexSelectedMember = MPU_GetIndexForQueueSetMemberHandle( xSelectedMemberInternal );

                        ᮚᮦᮔ᮪( lIndexSelectedMember != -1 )
                        {
                            xSelectedMemberExternal = ( QueueSetMemberHandle_t ) ( CONVERT_TO_EXTERNAL_INDEX( lIndexSelectedMember ) );
                        }
                    }
                }
            }

            ᮝᮜᮤ xSelectedMemberExternal;
        }

    #endif /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for timers APIs.                  */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

        void * MPU_pvTimerGetTimerIDImpl( const TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        void * MPU_pvTimerGetTimerIDImpl( const TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            void * pvReturn = NULL;
            TimerHandle_t xInternalTimerHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                    {
                        pvReturn = pvTimerGetTimerID( xInternalTimerHandle );
                    }
                }
            }

            ᮝᮜᮤ pvReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

        void MPU_vTimerSetTimerIDImpl( TimerHandle_t xTimer,
                                       void * pvNewID ) PRIVILEGED_FUNCTION;

        void MPU_vTimerSetTimerIDImpl( TimerHandle_t xTimer,
                                       void * pvNewID ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                    {
                        vTimerSetTimerID( xInternalTimerHandle, pvNewID );
                    }
                }
            }
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerIsTimerActiveImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerIsTimerActiveImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                    {
                        xReturn = xTimerIsTimerActive( xInternalTimerHandle );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( void ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( void ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xReturn;

            xReturn = xTimerGetTimerDaemonTaskHandle();

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     const BaseType_t xCommandID,
                                                     const TickType_t xOptionalValue,
                                                     BaseType_t * const pxHigherPriorityTaskWoken,
                                                     const TickType_t xTicksToWait ) /* FREERTOS_SYSTEM_CALL */
        {
            BaseType_t xReturn = pdFALSE;
            xTimerGenericCommandFromTaskParams_t xParams;

            xParams.xTimer = xTimer;
            xParams.xCommandID = xCommandID;
            xParams.xOptionalValue = xOptionalValue;
            xParams.pxHigherPriorityTaskWoken = pxHigherPriorityTaskWoken;
            xParams.xTicksToWait = xTicksToWait;

            xReturn = MPU_xTimerGenericCommandFromTaskEntry( &( xParams ) );

            ᮝᮜᮤ xReturn;
        }

        BaseType_t MPU_xTimerGenericCommandFromTaskImpl( const xTimerGenericCommandFromTaskParams_t * pxParams ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerGenericCommandFromTaskImpl( const xTimerGenericCommandFromTaskParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = NULL;
            int32_t lIndex;
            BaseType_t xIsHigherPriorityTaskWokenWriteable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            ᮚᮦᮔ᮪( pxParams != NULL )
            {
                xAreParamsReadable = xPortIsAuthorizedToAccessBuffer( pxParams,
                                                                      parimaa_na( xTimerGenericCommandFromTaskParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ᮚᮦᮔ᮪( xAreParamsReadable == pdTRUE )
            {
                ᮚᮦᮔ᮪( pxParams->xCommandID < tmrFIRST_FROM_ISR_COMMAND )
                {
                    ᮚᮦᮔ᮪( pxParams->pxHigherPriorityTaskWoken != NULL )
                    {
                        xIsHigherPriorityTaskWokenWriteable = xPortIsAuthorizedToAccessBuffer( pxParams->pxHigherPriorityTaskWoken,
                                                                                               parimaa_na( BaseType_t ),
                                                                                               tskMPU_WRITE_PERMISSION );
                    }

                    ᮚᮦᮔ᮪( ( pxParams->pxHigherPriorityTaskWoken == NULL ) ||
                        ( xIsHigherPriorityTaskWokenWriteable == pdTRUE ) )
                    {
                        lIndex = ( int32_t ) ( pxParams->xTimer );

                        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                        {
                            xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                            {
                                xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                                ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                                {
                                    xReturn = xTimerGenericCommandFromTask( xInternalTimerHandle,
                                                                            pxParams->xCommandID,
                                                                            pxParams->xOptionalValue,
                                                                            pxParams->pxHigherPriorityTaskWoken,
                                                                            pxParams->xTicksToWait );
                                }
                            }
                        }
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

        const var_na * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        const var_na * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            const var_na * pcReturn = NULL;
            TimerHandle_t xInternalTimerHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                    {
                        pcReturn = pcTimerGetName( xInternalTimerHandle );
                    }
                }
            }

            ᮝᮜᮤ pcReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

        void MPU_vTimerSetReloadModeImpl( TimerHandle_t xTimer,
                                          const BaseType_t xAutoReload ) PRIVILEGED_FUNCTION;

        void MPU_vTimerSetReloadModeImpl( TimerHandle_t xTimer,
                                          const BaseType_t xAutoReload ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                    {
                        vTimerSetReloadMode( xInternalTimerHandle, xAutoReload );
                    }
                }
            }
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGetReloadModeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xTimerGetReloadModeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                    {
                        xReturn = xTimerGetReloadMode( xInternalTimerHandle );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_uxTimerGetReloadModeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTimerGetReloadModeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            TimerHandle_t xInternalTimerHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                    {
                        uxReturn = uxTimerGetReloadMode( xInternalTimerHandle );
                    }
                }
            }

            ᮝᮜᮤ uxReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t xInternalTimerHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                    {
                        xReturn = xTimerGetPeriod( xInternalTimerHandle );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetExpiryTimeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetExpiryTimeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t xInternalTimerHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessTimer = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessTimer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessTimer == pdTRUE )
                {
                    xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                    {
                        xReturn = xTimerGetExpiryTime( xInternalTimerHandle );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Timer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreate( const var_na * const pcTimerName,
                                        const TickType_t xTimerPeriodInTicks,
                                        const BaseType_t xAutoReload,
                                        void * const pvTimerID,
                                        TimerCallbackFunction_t pxCallbackFunction ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = NULL;
            TimerHandle_t xExternalTimerHandle = NULL;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xInternalTimerHandle = xTimerCreate( pcTimerName, xTimerPeriodInTicks, xAutoReload, pvTimerID, MPU_TimerCallback );

                ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                {
                    MPU_StoreTimerHandleAtIndex( lIndex, xInternalTimerHandle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xExternalTimerHandle;
        }

    #endif /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreateStatic( const var_na * const pcTimerName,
                                              const TickType_t xTimerPeriodInTicks,
                                              const BaseType_t xAutoReload,
                                              void * const pvTimerID,
                                              TimerCallbackFunction_t pxCallbackFunction,
                                              StaticTimer_t * pxTimerBuffer ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = NULL;
            TimerHandle_t xExternalTimerHandle = NULL;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xInternalTimerHandle = xTimerCreateStatic( pcTimerName, xTimerPeriodInTicks, xAutoReload, pvTimerID, MPU_TimerCallback, pxTimerBuffer );

                ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                {
                    MPU_StoreTimerHandleAtIndex( lIndex, xInternalTimerHandle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xExternalTimerHandle;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGetStaticBuffer( TimerHandle_t xTimer,
                                              StaticTimer_t ** ppxTimerBuffer ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t xInternalTimerHandle = NULL;
            int32_t lIndex;
            BaseType_t xReturn = pdFALSE;

            lIndex = ( int32_t ) xTimer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                {
                    xReturn = xTimerGetStaticBuffer( xInternalTimerHandle, ppxTimerBuffer );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerGenericCommandFromISR( TimerHandle_t xTimer,
                                                    const BaseType_t xCommandID,
                                                    const TickType_t xOptionalValue,
                                                    BaseType_t * const pxHigherPriorityTaskWoken,
                                                    const TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = NULL;
            int32_t lIndex;

            lIndex = ( int32_t ) xTimer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                {
                    xReturn = xTimerGenericCommandFromISR( xInternalTimerHandle, xCommandID, xOptionalValue, pxHigherPriorityTaskWoken, xTicksToWait );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )

        BaseType_t MPU_xTimerDelete( TimerHandle_t xTimer, TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            TimerHandle_t xInternalTimerHandle = NULL;
            int32_t lIndex;

            lIndex = ( int32_t ) xTimer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalTimerHandle = MPU_GetTimerHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalTimerHandle != NULL )
                {
                    xReturn = xTimerGenericCommandFromTask( xInternalTimerHandle,
                                                            tmrCOMMAND_DELETE,
                                                            0U, /* xOptionalValue */
                                                            NULL, /* pxHigherPriorityTaskWoken */
                                                            xTicksToWait );
                    ᮚᮦᮔ᮪( xReturn != pdFALSE )
                    {
                        MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for event group APIs.              */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupWaitBits( EventGroupHandle_t xEventGroup,
                                             const EventBits_t uxBitsToWaitFor,
                                             const BaseType_t xClearOnExit,
                                             const BaseType_t xWaitForAllBits,
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

            ᮝᮜᮤ xReturn;
        }

        EventBits_t MPU_xEventGroupWaitBitsImpl( const xEventGroupWaitBitsParams_t * pxParams ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupWaitBitsImpl( const xEventGroupWaitBitsParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;
            BaseType_t xAreParamsReadable = pdFALSE;

            ᮚᮦᮔ᮪( pxParams != NULL )
            {
                xAreParamsReadable = xPortIsAuthorizedToAccessBuffer( pxParams,
                                                                      parimaa_na( xEventGroupWaitBitsParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ᮚᮦᮔ᮪( xAreParamsReadable == pdTRUE )
            {
                ᮚᮦᮔ᮪( ( ( pxParams->uxBitsToWaitFor & eventEVENT_BITS_CONTROL_BYTES ) == 0U ) &&
                    ( pxParams->uxBitsToWaitFor != 0U )
                    #ᮚᮦᮔ᮪ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                        && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( pxParams->xTicksToWait != 0U ) ) )
                    #endif
                    )
                {
                    lIndex = ( int32_t ) ( pxParams->xEventGroup );

                    ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                        {
                            xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ᮚᮦᮔ᮪( xInternalEventGroupHandle != NULL )
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

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupClearBitsImpl( EventGroupHandle_t xEventGroup,
                                                  const EventBits_t uxBitsToClear ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupClearBitsImpl( EventGroupHandle_t xEventGroup,
                                                  const EventBits_t uxBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            ᮚᮦᮔ᮪( ( uxBitsToClear & eventEVENT_BITS_CONTROL_BYTES ) == 0U )
            {
                lIndex = ( int32_t ) xEventGroup;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xInternalEventGroupHandle != NULL )
                        {
                            xReturn = xEventGroupClearBits( xInternalEventGroupHandle, uxBitsToClear );
                        }
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSetBitsImpl( EventGroupHandle_t xEventGroup,
                                                const EventBits_t uxBitsToSet ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupSetBitsImpl( EventGroupHandle_t xEventGroup,
                                                const EventBits_t uxBitsToSet ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            ᮚᮦᮔ᮪( ( uxBitsToSet & eventEVENT_BITS_CONTROL_BYTES ) == 0U )
            {
                lIndex = ( int32_t ) xEventGroup;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xInternalEventGroupHandle != NULL )
                        {
                            xReturn = xEventGroupSetBits( xInternalEventGroupHandle, uxBitsToSet );
                        }
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupSyncImpl( EventGroupHandle_t xEventGroup,
                                             const EventBits_t uxBitsToSet,
                                             const EventBits_t uxBitsToWaitFor,
                                             TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        EventBits_t MPU_xEventGroupSyncImpl( EventGroupHandle_t xEventGroup,
                                             const EventBits_t uxBitsToSet,
                                             const EventBits_t uxBitsToWaitFor,
                                             TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            ᮚᮦᮔ᮪( ( ( uxBitsToWaitFor & eventEVENT_BITS_CONTROL_BYTES ) == 0U ) &&
                ( uxBitsToWaitFor != 0U )
                #ᮚᮦᮔ᮪ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                    && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( xTicksToWait != 0U ) ) )
                #endif
                )
            {
                lIndex = ( int32_t ) xEventGroup;

                ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                {
                    xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                    {
                        xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xInternalEventGroupHandle != NULL )
                        {
                            xReturn = xEventGroupSync( xInternalEventGroupHandle, uxBitsToSet, uxBitsToWaitFor, xTicksToWait );
                        }
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_uxEventGroupGetNumberImpl( void * xEventGroup ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxEventGroupGetNumberImpl( void * xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            lIndex = ( int32_t ) xEventGroup;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                {
                    xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalEventGroupHandle != NULL )
                    {
                        xReturn = uxEventGroupGetNumber( xInternalEventGroupHandle );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        void MPU_vEventGroupSetNumberImpl( void * xEventGroup,
                                           UBaseType_t uxEventGroupNumber ) PRIVILEGED_FUNCTION;

        void MPU_vEventGroupSetNumberImpl( void * xEventGroup,
                                           UBaseType_t uxEventGroupNumber ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessEventGroup = pdFALSE;

            lIndex = ( int32_t ) xEventGroup;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessEventGroup = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessEventGroup == pdTRUE )
                {
                    xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalEventGroupHandle != NULL )
                    {
                        vEventGroupSetNumber( xInternalEventGroupHandle, uxEventGroupNumber );
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

    #ᮚᮦᮔ᮪ ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        EventGroupHandle_t MPU_xEventGroupCreate( void ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = NULL;
            EventGroupHandle_t xExternalEventGroupHandle = NULL;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xInternalEventGroupHandle = xEventGroupCreate();

                ᮚᮦᮔ᮪( xInternalEventGroupHandle != NULL )
                {
                    MPU_StoreEventGroupHandleAtIndex( lIndex, xInternalEventGroupHandle );
                    xExternalEventGroupHandle = ( EventGroupHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xExternalEventGroupHandle;
        }

    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        EventGroupHandle_t MPU_xEventGroupCreateStatic( StaticEventGroup_t * pxEventGroupBuffer ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = NULL;
            EventGroupHandle_t xExternalEventGroupHandle = NULL;
            int32_t lIndex;

            lIndex = MPU_GetFreeIndexInKernelObjectPool();

            ᮚᮦᮔ᮪( lIndex != -1 )
            {
                xInternalEventGroupHandle = xEventGroupCreateStatic( pxEventGroupBuffer );

                ᮚᮦᮔ᮪( xInternalEventGroupHandle != NULL )
                {
                    MPU_StoreEventGroupHandleAtIndex( lIndex, xInternalEventGroupHandle );
                    xExternalEventGroupHandle = ( EventGroupHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                }
                ᮜᮤᮚ
                {
                    MPU_SetIndexFreeInKernelObjectPool( lIndex );
                }
            }

            ᮝᮜᮤ xExternalEventGroupHandle;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_EVENT_GROUPS == 1 )

        void MPU_vEventGroupDelete( EventGroupHandle_t xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            EventGroupHandle_t xInternalEventGroupHandle = NULL;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalEventGroupHandle != NULL )
                {
                    vEventGroupDelete( xInternalEventGroupHandle );
                    MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
                }
            }
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        BaseType_t MPU_xEventGroupGetStaticBuffer( EventGroupHandle_t xEventGroup,
                                                   StaticEventGroup_t ** ppxEventGroupBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = NULL;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalEventGroupHandle != NULL )
                {
                    xReturn = xEventGroupGetStaticBuffer( xInternalEventGroupHandle, ppxEventGroupBuffer );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        BaseType_t MPU_xEventGroupClearBitsFromISR( EventGroupHandle_t xEventGroup,
                                                    const EventBits_t uxBitsToClear ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = NULL;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalEventGroupHandle != NULL )
                {
                    xReturn = xEventGroupClearBitsFromISR( xInternalEventGroupHandle, uxBitsToClear );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        BaseType_t MPU_xEventGroupSetBitsFromISR( EventGroupHandle_t xEventGroup,
                                                  const EventBits_t uxBitsToSet,
                                                  BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            EventGroupHandle_t xInternalEventGroupHandle = NULL;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalEventGroupHandle != NULL )
                {
                    xReturn = xEventGroupSetBitsFromISR( xInternalEventGroupHandle, uxBitsToSet, pxHigherPriorityTaskWoken );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_EVENT_GROUPS == 1 )

        EventBits_t MPU_xEventGroupGetBitsFromISR( EventGroupHandle_t xEventGroup ) /* PRIVILEGED_FUNCTION */
        {
            EventBits_t xReturn = 0;
            EventGroupHandle_t xInternalEventGroupHandle = NULL;
            int32_t lIndex;

            lIndex = ( int32_t ) xEventGroup;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalEventGroupHandle = MPU_GetEventGroupHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalEventGroupHandle != NULL )
                {
                    xReturn = xEventGroupGetBitsFromISR( xInternalEventGroupHandle );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for stream buffer APIs.            */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferSendImpl( StreamBufferHandle_t xStreamBuffer,
                                          const void * pvTxData,
                                          size_t xDataLengthBytes,
                                          TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferSendImpl( StreamBufferHandle_t xStreamBuffer,
                                          const void * pvTxData,
                                          size_t xDataLengthBytes,
                                          TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            int32_t lIndex;
            BaseType_t xIsTxDataBufferReadable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            ᮚᮦᮔ᮪( pvTxData != NULL )
            {
                xIsTxDataBufferReadable = xPortIsAuthorizedToAccessBuffer( pvTxData,
                                                                           xDataLengthBytes,
                                                                           tskMPU_READ_PERMISSION );

                ᮚᮦᮔ᮪( xIsTxDataBufferReadable == pdTRUE )
                {
                    lIndex = ( int32_t ) xStreamBuffer;

                    ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                        {
                            xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                            {
                                xReturn = xStreamBufferSend( xInternalStreamBufferHandle, pvTxData, xDataLengthBytes, xTicksToWait );
                            }
                        }
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferReceiveImpl( StreamBufferHandle_t xStreamBuffer,
                                             void * pvRxData,
                                             size_t xBufferLengthBytes,
                                             TickType_t xTicksToWait ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferReceiveImpl( StreamBufferHandle_t xStreamBuffer,
                                             void * pvRxData,
                                             size_t xBufferLengthBytes,
                                             TickType_t xTicksToWait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            int32_t lIndex;
            BaseType_t xIsRxDataBufferWriteable = pdFALSE;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            ᮚᮦᮔ᮪( pvRxData != NULL )
            {
                xIsRxDataBufferWriteable = xPortIsAuthorizedToAccessBuffer( pvRxData,
                                                                            xBufferLengthBytes,
                                                                            tskMPU_WRITE_PERMISSION );

                ᮚᮦᮔ᮪( xIsRxDataBufferWriteable == pdTRUE )
                {
                    lIndex = ( int32_t ) xStreamBuffer;

                    ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
                    {
                        xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                        ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                        {
                            xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                            ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                            {
                                xReturn = xStreamBufferReceive( xInternalStreamBufferHandle, pvRxData, xBufferLengthBytes, xTicksToWait );
                            }
                        }
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferIsFullImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xStreamBufferIsFullImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                    {
                        xReturn = xStreamBufferIsFull( xInternalStreamBufferHandle );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferIsEmptyImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xStreamBufferIsEmptyImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                    {
                        xReturn = xStreamBufferIsEmpty( xInternalStreamBufferHandle );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferSpacesAvailableImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferSpacesAvailableImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                    {
                        xReturn = xStreamBufferSpacesAvailable( xInternalStreamBufferHandle );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferBytesAvailableImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferBytesAvailableImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                    {
                        xReturn = xStreamBufferBytesAvailable( xInternalStreamBufferHandle );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferSetTriggerLevelImpl( StreamBufferHandle_t xStreamBuffer,
                                                         size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

        BaseType_t MPU_xStreamBufferSetTriggerLevelImpl( StreamBufferHandle_t xStreamBuffer,
                                                         size_t xTriggerLevel ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                    {
                        xReturn = xStreamBufferSetTriggerLevel( xInternalStreamBufferHandle, xTriggerLevel );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

        size_t MPU_xStreamBufferNextMessageLengthBytesImpl( StreamBufferHandle_t xStreamBuffer ) PRIVILEGED_FUNCTION;

        size_t MPU_xStreamBufferNextMessageLengthBytesImpl( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            int32_t lIndex;
            BaseType_t xCallingTaskIsAuthorizedToAccessStreamBuffer = pdFALSE;

            lIndex = ( int32_t ) xStreamBuffer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xCallingTaskIsAuthorizedToAccessStreamBuffer = xPortIsAuthorizedToAccessKernelObject( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xCallingTaskIsAuthorizedToAccessStreamBuffer == pdTRUE )
                {
                    xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                    ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                    {
                        xReturn = xStreamBufferNextMessageLengthBytes( xInternalStreamBufferHandle );
                    }
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Stream Buffer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        StreamBufferHandle_t MPU_xStreamBufferGenericCreate( size_t xBufferSizeBytes,
                                                             size_t xTriggerLevelBytes,
                                                             BaseType_t xStreamBufferType,
                                                             StreamBufferCallbackFunction_t pxSendCompletedCallback,
                                                             StreamBufferCallbackFunction_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            StreamBufferHandle_t xExternalStreamBufferHandle = NULL;
            int32_t lIndex;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == NULL ) &&
                          ( pxReceiveCompletedCallback == NULL ) );

            ᮚᮦᮔ᮪( ( pxSendCompletedCallback == NULL ) &&
                ( pxReceiveCompletedCallback == NULL ) )
            {
                lIndex = MPU_GetFreeIndexInKernelObjectPool();

                ᮚᮦᮔ᮪( lIndex != -1 )
                {
                    xInternalStreamBufferHandle = xStreamBufferGenericCreate( xBufferSizeBytes,
                                                                              xTriggerLevelBytes,
                                                                              xStreamBufferType,
                                                                              NULL,
                                                                              NULL );

                    ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                    {
                        MPU_StoreStreamBufferHandleAtIndex( lIndex, xInternalStreamBufferHandle );
                        xExternalStreamBufferHandle = ( StreamBufferHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                    }
                    ᮜᮤᮚ
                    {
                        MPU_SetIndexFreeInKernelObjectPool( lIndex );
                    }
                }
            }
            ᮜᮤᮚ
            {
                traceSTREAM_BUFFER_CREATE_FAILED( xStreamBufferType );
                xExternalStreamBufferHandle = NULL;
            }

            ᮝᮜᮤ xExternalStreamBufferHandle;
        }

    #endif /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        StreamBufferHandle_t MPU_xStreamBufferGenericCreateStatic( size_t xBufferSizeBytes,
                                                                   size_t xTriggerLevelBytes,
                                                                   BaseType_t xStreamBufferType,
                                                                   uint8_t * const pucStreamBufferStorageArea,
                                                                   StaticStreamBuffer_t * const pxStaticStreamBuffer,
                                                                   StreamBufferCallbackFunction_t pxSendCompletedCallback,
                                                                   StreamBufferCallbackFunction_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            StreamBufferHandle_t xExternalStreamBufferHandle = NULL;
            int32_t lIndex;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == NULL ) &&
                          ( pxReceiveCompletedCallback == NULL ) );

            ᮚᮦᮔ᮪( ( pxSendCompletedCallback == NULL ) &&
                ( pxReceiveCompletedCallback == NULL ) )
            {
                lIndex = MPU_GetFreeIndexInKernelObjectPool();

                ᮚᮦᮔ᮪( lIndex != -1 )
                {
                    xInternalStreamBufferHandle = xStreamBufferGenericCreateStatic( xBufferSizeBytes,
                                                                                    xTriggerLevelBytes,
                                                                                    xStreamBufferType,
                                                                                    pucStreamBufferStorageArea,
                                                                                    pxStaticStreamBuffer,
                                                                                    NULL,
                                                                                    NULL );

                    ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                    {
                        MPU_StoreStreamBufferHandleAtIndex( lIndex, xInternalStreamBufferHandle );
                        xExternalStreamBufferHandle = ( StreamBufferHandle_t ) CONVERT_TO_EXTERNAL_INDEX( lIndex );
                    }
                    ᮜᮤᮚ
                    {
                        MPU_SetIndexFreeInKernelObjectPool( lIndex );
                    }
                }
            }
            ᮜᮤᮚ
            {
                traceSTREAM_BUFFER_CREATE_STATIC_FAILED( xReturn, xStreamBufferType );
                xExternalStreamBufferHandle = NULL;
            }

            ᮝᮜᮤ xExternalStreamBufferHandle;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

        void MPU_vStreamBufferDelete( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                {
                    vStreamBufferDelete( xInternalStreamBufferHandle );
                }

                MPU_SetIndexFreeInKernelObjectPool( CONVERT_TO_INTERNAL_INDEX( lIndex ) );
            }
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferReset( StreamBufferHandle_t xStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                {
                    xReturn = xStreamBufferReset( xInternalStreamBufferHandle );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) )

        BaseType_t MPU_xStreamBufferGetStaticBuffers( StreamBufferHandle_t xStreamBuffers,
                                                      uint8_t * ppucStreamBufferStorageArea,
                                                      StaticStreamBuffer_t * ppxStaticStreamBuffer ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffers;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                {
                    xReturn = MPU_xStreamBufferGetStaticBuffers( xInternalStreamBufferHandle, ppucStreamBufferStorageArea, ppxStaticStreamBuffer );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

    size_t MPU_xStreamBufferSendFromISR( StreamBufferHandle_t xStreamBuffer,
                                         const void * pvTxData,
                                         size_t xDataLengthBytes,
                                         BaseType_t * const pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
        int32_t lIndex;

        lIndex = ( int32_t ) xStreamBuffer;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
            {
                xReturn = xStreamBufferSendFromISR( xInternalStreamBufferHandle, pvTxData, xDataLengthBytes, pxHigherPriorityTaskWoken );
            }
        }

        ᮝᮜᮤ xReturn;
    }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

    size_t MPU_xStreamBufferReceiveFromISR( StreamBufferHandle_t xStreamBuffer,
                                            void * pvRxData,
                                            size_t xBufferLengthBytes,
                                            BaseType_t * const pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
        int32_t lIndex;

        lIndex = ( int32_t ) xStreamBuffer;

        ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
        {
            xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

            ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
            {
                xReturn = xStreamBufferReceiveFromISR( xInternalStreamBufferHandle, pvRxData, xBufferLengthBytes, pxHigherPriorityTaskWoken );
            }
        }

        ᮝᮜᮤ xReturn;
    }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferSendCompletedFromISR( StreamBufferHandle_t xStreamBuffer,
                                                          BaseType_t * pxHigherPriorityTaskWoken ) /* PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                {
                    xReturn = xStreamBufferSendCompletedFromISR( xInternalStreamBufferHandle, pxHigherPriorityTaskWoken );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferReceiveCompletedFromISR( StreamBufferHandle_t xStreamBuffer,
                                                             BaseType_t * pxHigherPriorityTaskWoken ) /*PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFALSE;
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                {
                    xReturn = xStreamBufferReceiveCompletedFromISR( xInternalStreamBufferHandle, pxHigherPriorityTaskWoken );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

    #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )

        BaseType_t MPU_xStreamBufferResetFromISR( StreamBufferHandle_t xStreamBuffer ) /*PRIVILEGED_FUNCTION */
        {
            BaseType_t xReturn = pdFAIL;
            StreamBufferHandle_t xInternalStreamBufferHandle = NULL;
            int32_t lIndex;

            lIndex = ( int32_t ) xStreamBuffer;

            ᮚᮦᮔ᮪( IS_EXTERNAL_INDEX_VALID( lIndex ) != pdFALSE )
            {
                xInternalStreamBufferHandle = MPU_GetStreamBufferHandleAtIndex( CONVERT_TO_INTERNAL_INDEX( lIndex ) );

                ᮚᮦᮔ᮪( xInternalStreamBufferHandle != NULL )
                {
                    xReturn = xStreamBufferResetFromISR( xInternalStreamBufferHandle );
                }
            }

            ᮝᮜᮤ xReturn;
        }

    #endif /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h. */

    #ᮚᮦᮔ᮪ configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #include "application_defined_privileged_functions.h"
    #endif
/*-----------------------------------------------------------*/

/**
 * @brief Array of system call implementation functions.
 *
 * The index in the array MUST match the corresponding system call number
 * defined in mpu_wrappers.h.
 */
    PRIVILEGED_DATA UBaseType_t uxSystemCallImplementations[ NUM_SYSTEM_CALLS ] =
    {
        #ᮚᮦᮔ᮪ ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_xTaskGenericNotifyImpl,                     /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyWaitImpl,                 /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #endif

        #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_xTimerGenericCommandFromTaskImpl,           /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #endif

        #ᮚᮦᮔ᮪ ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_xEventGroupWaitBitsImpl,                    /* SYSTEM_CALL_xEventGroupWaitBits. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupWaitBits. */
        #endif

        /* The system calls above this line take 5 parameters. */

        #ᮚᮦᮔ᮪ ( INCLUDE_xTaskDelayUntil == 1 )
            ( UBaseType_t ) MPU_xTaskDelayUntilImpl,                        /* SYSTEM_CALL_xTaskDelayUntil. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskDelayUntil. */
        #endif

        #ᮚᮦᮔ᮪ ( INCLUDE_xTaskAbortDelay == 1 )
            ( UBaseType_t ) MPU_xTaskAbortDelayImpl,                        /* SYSTEM_CALL_xTaskAbortDelay. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskAbortDelay. */
        #endif

        #ᮚᮦᮔ᮪ ( INCLUDE_vTaskDelay == 1 )
            ( UBaseType_t ) MPU_vTaskDelayImpl,                             /* SYSTEM_CALL_vTaskDelay. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskDelay. */
        #endif

        #ᮚᮦᮔ᮪ ( INCLUDE_uxTaskPriorityGet == 1 )
            ( UBaseType_t ) MPU_uxTaskPriorityGetImpl,                      /* SYSTEM_CALL_uxTaskPriorityGet. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskPriorityGet. */
        #endif

        #ᮚᮦᮔ᮪ ( INCLUDE_eTaskGetState == 1 )
            ( UBaseType_t ) MPU_eTaskGetStateImpl,                          /* SYSTEM_CALL_eTaskGetState. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_eTaskGetState. */
        #endif

        #ᮚᮦᮔ᮪ ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_vTaskGetInfoImpl,                           /* SYSTEM_CALL_vTaskGetInfo. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskGetInfo. */
        #endif

        #ᮚᮦᮔ᮪ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
            ( UBaseType_t ) MPU_xTaskGetIdleTaskHandleImpl,                 /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #endif

        #ᮚᮦᮔ᮪ ( INCLUDE_vTaskSuspend == 1 )
            ( UBaseType_t ) MPU_vTaskSuspendImpl,                           /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) MPU_vTaskResumeImpl,                            /* SYSTEM_CALL_vTaskResume. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskResume. */
        #endif

        ( UBaseType_t ) MPU_xTaskGetTickCountImpl,                          /* SYSTEM_CALL_xTaskGetTickCount. */
        ( UBaseType_t ) MPU_uxTaskGetNumberOfTasksImpl,                     /* SYSTEM_CALL_uxTaskGetNumberOfTasks. */

        #ᮚᮦᮔ᮪ ( configGENERATE_RUN_TIME_STATS == 1 )
            ( UBaseType_t ) MPU_ulTaskGetRunTimeCounterImpl,                /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) MPU_ulTaskGetRunTimePercentImpl,                /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #endif

        #ᮚᮦᮔ᮪ ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
            ( UBaseType_t ) MPU_ulTaskGetIdleRunTimePercentImpl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) MPU_ulTaskGetIdleRunTimeCounterImpl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #endif

        #ᮚᮦᮔ᮪ ( configUSE_APPLICATION_TASK_TAG == 1 )
            ( UBaseType_t ) MPU_vTaskSetApplicationTaskTagImpl,             /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) MPU_xTaskGetApplicationTaskTagImpl,             /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #endif

        #ᮚᮦᮔ᮪ ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 )
            ( UBaseType_t ) MPU_vTaskSetThreadLocalStoragePointerImpl,      /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) MPU_pvTaskGetThreadLocalStoragePointerImpl,     /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #endif

        #ᮚᮦᮔ᮪ ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_uxTaskGetSystemStateImpl,                   /* SYSTEM_CALL_uxTaskGetSystemState. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetSystemState. */
        #endif

        #ᮚᮦᮔ᮪ ( INCLUDE_uxTaskGetStackHighWaterMark == 1 )
            ( UBaseType_t ) MPU_uxTaskGetStackHighWaterMarkImpl,            /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #endif

        #ᮚᮦᮔ᮪ ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 )
            ( UBaseType_t ) MPU_uxTaskGetStackHighWaterMark2Impl,           /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #endif

        #ᮚᮦᮔ᮪ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )
            ( UBaseType_t ) MPU_xTaskGetCurrentTaskHandleImpl,              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #endif

        #ᮚᮦᮔ᮪ ( INCLUDE_xTaskGetSchedulerState == 1 )
            ( UBaseType_t ) MPU_xTaskGetSchedulerStateImpl,                 /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #endif

        ( UBaseType_t ) MPU_vTaskSetTimeOutStateImpl,                       /* SYSTEM_CALL_vTaskSetTimeOutState. */
        ( UBaseType_t ) MPU_xTaskCheckForTimeOutImpl,                       /* SYSTEM_CALL_xTaskCheckForTimeOut. */

        #ᮚᮦᮔ᮪ ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_ulTaskGenericNotifyTakeImpl,                /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyStateClearImpl,           /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) MPU_ulTaskGenericNotifyValueClearImpl,          /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #ᮜᮤᮚ
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

        #ᮚᮦᮔ᮪ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
            ( UBaseType_t ) MPU_xQueueGetMutexHolderImpl,                   /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #endif

        #ᮚᮦᮔ᮪ ( configUSE_RECURSIVE_MUTEXES == 1 )
            ( UBaseType_t ) MPU_xQueueTakeMutexRecursiveImpl,               /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) MPU_xQueueGiveMutexRecursiveImpl,               /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #endif

        #ᮚᮦᮔ᮪ ( configUSE_QUEUE_SETS == 1 )
            ( UBaseType_t ) MPU_xQueueSelectFromSetImpl,                    /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) MPU_xQueueAddToSetImpl,                         /* SYSTEM_CALL_xQueueAddToSet. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueAddToSet. */
        #endif

        #ᮚᮦᮔ᮪ configQUEUE_REGISTRY_SIZE > 0
            ( UBaseType_t ) MPU_vQueueAddToRegistryImpl,                    /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) MPU_vQueueUnregisterQueueImpl,                  /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) MPU_pcQueueGetNameImpl,                         /* SYSTEM_CALL_pcQueueGetName. */
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcQueueGetName. */
        #endif

        #ᮚᮦᮔ᮪ ( configUSE_TIMERS == 1 )
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
        #ᮜᮤᮚ
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

        #ᮚᮦᮔ᮪ ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_xEventGroupClearBitsImpl,                   /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) MPU_xEventGroupSetBitsImpl,                     /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) MPU_xEventGroupSyncImpl,                        /* SYSTEM_CALL_xEventGroupSync. */

            #ᮚᮦᮔ᮪ ( configUSE_TRACE_FACILITY == 1 )
                ( UBaseType_t ) MPU_uxEventGroupGetNumberImpl,              /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) MPU_vEventGroupSetNumberImpl,               /* SYSTEM_CALL_vEventGroupSetNumber. */
            #ᮜᮤᮚ
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_vEventGroupSetNumber. */
            #endif
        #ᮜᮤᮚ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSync. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxEventGroupGetNumber. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vEventGroupSetNumber. */
        #endif

        #ᮚᮦᮔ᮪ ( configUSE_STREAM_BUFFERS == 1 )
            ( UBaseType_t ) MPU_xStreamBufferSendImpl,                      /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) MPU_xStreamBufferReceiveImpl,                   /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) MPU_xStreamBufferIsFullImpl,                    /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) MPU_xStreamBufferIsEmptyImpl,                   /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) MPU_xStreamBufferSpacesAvailableImpl,           /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) MPU_xStreamBufferBytesAvailableImpl,            /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) MPU_xStreamBufferSetTriggerLevelImpl,           /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) MPU_xStreamBufferNextMessageLengthBytesImpl     /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #ᮜᮤᮚ
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
