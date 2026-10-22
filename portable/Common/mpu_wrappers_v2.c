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
#تعریف_کړه MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "queue.h"
#ضمن "timers.h"
#ضمن "event_groups.h"
#ضمن "stream_buffer.h"
#ضمن "mpu_prototypes.h"
#ضمن "mpu_syscall_numbers.h"

#تعریف_لغوه MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#إذا ( ( پورټ_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #که_نه_تعریف_شوی config_PROTECTED_KERNEL_OBJECT_POOL_اندازه
        #تېروتنه config_PROTECTED_KERNEL_OBJECT_POOL_اندازه must be defined منزل اعظمي شمېره د kernel objects دننه the application.
    #د_که_پای

/**
 * @brief Offset added to the index before returning to the user.
 *
 * If the actual handle is stored at index i, ( i + INDEX_OFFSET )
 * is returned to the user.
 */
    #تعریف_کړه شاخص_دننه_واټن    1

/**
 * @brief Opaque type for a kernel object.
 */
    بنية OpaqueObject;
    تعريفنوع بنية OpaqueObject * OpaqueObjectHandle_t;

/**
 * @brief Defines kernel object in the kernel object pool.
 */
    تعريفنوع بنية KernelObject
    {
        OpaqueObjectHandle_t x_دننی_Object_Handle;
        uint32_t ulKernelObjectType;
        فراغ * pv_Kernel_Object_معلومات;
    } KernelObject_t;

/**
 * @brief Kernel object types.
 */
    #تعریف_کړه KERNEL_OBJECT_TYPE_INVALID          ( 0UL )
    #تعریف_کړه KERNEL_OBJECT_TYPE_کتار            ( 1UL )
    #تعریف_کړه KERNEL_OBJECT_TYPE_TASK             ( 2UL )
    #تعریف_کړه KERNEL_OBJECT_TYPE_بهیر_بفر    ( 3UL )
    #تعریف_کړه KERNEL_OBJECT_TYPE_EVENT_ډله      ( 4UL )
    #تعریف_کړه KERNEL_OBJECT_TYPE_TIMER            ( 5UL )

/**
 * @brief Checks whether an external index is valid or not.
 */
    #تعریف_کړه IS_EXTERNAL_شاخص_VALID( l_شاخص )   \
    ( ( ( ( l_شاخص ) >= شاخص_دننه_واټن ) &&       \
        ( ( l_شاخص ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_اندازه + شاخص_دننه_واټن ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Checks whether an internal index is valid or not.
 */
    #تعریف_کړه IS_دننی_شاخص_VALID( l_شاخص )   \
    ( ( ( ( l_شاخص ) >= 0 ) &&                  \
        ( ( l_شاخص ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_اندازه ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Converts an internal index into external.
 */
    #تعریف_کړه CONVERT_منزل_EXTERNAL_شاخص( l_شاخص )    ( ( l_شاخص ) + شاخص_دننه_واټن )

/**
 * @brief Converts an external index into internal.
 */
    #تعریف_کړه CONVERT_منزل_دننی_شاخص( l_شاخص )    ( ( l_شاخص ) - شاخص_دننه_واټن )

/**
 * @brief Max value that fits in a UBaseType_t type.
 */
    #تعریف_کړه mpuUBASETYPE_MAX    ( ~( ( UBaseType_t ) 0 ) )

/**
 * @brief Check if multiplying a and b will result in overflow.
 */
    #تعریف_کړه mpu_MULTIPLY_BASETYPE_WILL_ډکېدنه( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( mpuUBASETYPE_MAX / ( a ) ) ) )

/**
 * @brief Get the index of a free slot in the kernel object pool.
 *
 * If a free slot is found, this function marks the slot as
 * "not free".
 *
 * @return Index of a free slot is returned, if a free slot is
 *         found. Otherwise -1 is returned.
 */
    ساكن int32_t MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Set the given index as free in the kernel object pool.
 *
 * @param lIndex The index to set as free.
 */
    ساكن فراغ MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( int32_t l_شاخص ) PRIVILEGED_FUNCTION;

/**
 * @brief Get the index at which a given kernel object is stored.
 *
 * @param xHandle The given kernel object handle.
 * @param ulKernelObjectType The kernel object type.
 *
 * @return Index at which the kernel object is stored if it is a valid
 *         handle, -1 otherwise.
 */
    ساكن int32_t MPU_Get_شاخص_For_Handle( OpaqueObjectHandle_t xHandle,
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
    ساكن فراغ MPU_Store_Handle_And_معلومات_At_شاخص( int32_t l_شاخص,
                                               OpaqueObjectHandle_t xHandle,
                                               فراغ * pv_Kernel_Object_معلومات,
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
    ساكن OpaqueObjectHandle_t MPU_Get_Handle_At_شاخص( int32_t l_شاخص,
                                                      uint32_t ulKernelObjectType ) PRIVILEGED_FUNCTION;

    #إذا ( configUSE_TIMERS == 1 )

/**
 * @brief The function registered as callback for all the timers.
 *
 * We intercept all the timer callbacks so that we can call application
 * callbacks with opaque handle.
 *
 * @param xInternalHandle The internal timer handle.
 */
        ساكن فراغ MPU_TimerCallback( TimerHandle_t x_دننی_Handle ) PRIVILEGED_FUNCTION;

    #د_که_پای /* #if ( configUSE_TIMERS == 1 ) */

/*
 * Wrappers to keep all the casting in one place.
 */
    #تعریف_کړه MPU_Store_کتار_Handle_At_شاخص( l_شاخص, xHandle )                 MPU_Store_Handle_And_معلومات_At_شاخص( ( l_شاخص ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_کتار )
    #تعریف_کړه MPU_Get_کتار_Handle_At_شاخص( l_شاخص )                            ( کتار_Handle_t ) MPU_Get_Handle_At_شاخص( ( l_شاخص ), KERNEL_OBJECT_TYPE_کتار )

    #إذا ( config_USE_کتار_SETS == 1 )
        #تعریف_کړه MPU_Store_کتار_سېټ_Handle_At_شاخص( l_شاخص, xHandle )          MPU_Store_Handle_And_معلومات_At_شاخص( ( l_شاخص ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_کتار )
        #تعریف_کړه MPU_Get_کتار_سېټ_Handle_At_شاخص( l_شاخص )                     ( کتار_سېټ_Handle_t ) MPU_Get_Handle_At_شاخص( ( l_شاخص ), KERNEL_OBJECT_TYPE_کتار )
        #تعریف_کړه MPU_Store_کتار_سېټ_Member_Handle_At_شاخص( l_شاخص, xHandle )    MPU_Store_Handle_And_معلومات_At_شاخص( ( l_شاخص ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_کتار )
        #تعریف_کړه MPU_Get_کتار_سېټ_Member_Handle_At_شاخص( l_شاخص )               ( کتار_سېټ_Member_Handle_t ) MPU_Get_Handle_At_شاخص( ( l_شاخص ), KERNEL_OBJECT_TYPE_کتار )
        #تعریف_کړه MPU_Get_شاخص_For_کتار_سېټ_Member_Handle( xHandle )             MPU_Get_شاخص_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_کتار )
    #د_که_پای

/*
 * Wrappers to keep all the casting in one place for Task APIs.
 */
    #تعریف_کړه MPU_Store_Task_Handle_At_شاخص( l_شاخص, xHandle )            MPU_Store_Handle_And_معلومات_At_شاخص( ( l_شاخص ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_TASK )
    #تعریف_کړه MPU_Get_Task_Handle_At_شاخص( l_شاخص )                       ( TaskHandle_t ) MPU_Get_Handle_At_شاخص( ( l_شاخص ), KERNEL_OBJECT_TYPE_TASK )
    #تعریف_کړه MPU_Get_شاخص_For_Task_Handle( xHandle )                     MPU_Get_شاخص_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TASK )

    #إذا ( configUSE_EVENT_GROUPS == 1 )
/*
 * Wrappers to keep all the casting in one place for Event Group APIs.
 */
        #تعریف_کړه MPU_Store_Event_ډله_Handle_At_شاخص( l_شاخص, xHandle )      MPU_Store_Handle_And_معلومات_At_شاخص( ( l_شاخص ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_EVENT_ډله )
        #تعریف_کړه MPU_Get_Event_ډله_Handle_At_شاخص( l_شاخص )                 ( Event_ډله_Handle_t ) MPU_Get_Handle_At_شاخص( ( l_شاخص ), KERNEL_OBJECT_TYPE_EVENT_ډله )
        #تعریف_کړه MPU_Get_شاخص_For_Event_ډله_Handle( xHandle )               MPU_Get_شاخص_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_EVENT_ډله )

    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */

    #إذا ( config_USE_بهیر_BUFFERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Stream Buffer APIs.
 */
        #تعریف_کړه MPU_Store_بهیر_بفر_Handle_At_شاخص( l_شاخص, xHandle )    MPU_Store_Handle_And_معلومات_At_شاخص( ( l_شاخص ), ( OpaqueObjectHandle_t ) ( xHandle), عدم, KERNEL_OBJECT_TYPE_بهیر_بفر )
        #تعریف_کړه MPU_Get_بهیر_بفر_Handle_At_شاخص( l_شاخص )               ( بهیر_بفر_Handle_t ) MPU_Get_Handle_At_شاخص( ( l_شاخص ), KERNEL_OBJECT_TYPE_بهیر_بفر )
        #تعریف_کړه MPU_Get_شاخص_For_بهیر_بفر_Handle( xHandle )             MPU_Get_شاخص_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_بهیر_بفر )

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

    #إذا ( configUSE_TIMERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Timer APIs.
 */
        #تعریف_کړه MPU_Store_Timer_Handle_At_شاخص( l_شاخص, xHandle, pxApplicationCallback )    MPU_Store_Handle_And_معلومات_At_شاخص( ( l_شاخص ), ( OpaqueObjectHandle_t ) ( xHandle ), ( فراغ * ) ( pxApplicationCallback ), KERNEL_OBJECT_TYPE_TIMER )
        #تعریف_کړه MPU_Get_Timer_Handle_At_شاخص( l_شاخص )                                      ( TimerHandle_t ) MPU_Get_Handle_At_شاخص( ( l_شاخص ), KERNEL_OBJECT_TYPE_TIMER )
        #تعریف_کړه MPU_Get_شاخص_For_Timer_Handle( xHandle )                                    MPU_Get_شاخص_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TIMER )

    #د_که_پای /* #if ( configUSE_TIMERS == 1 ) */

/*-----------------------------------------------------------*/

/**
 * @brief Kernel object pool.
 */
    PRIVILEGED_معلومات ساكن KernelObject_t xKernelObjectPool[ config_PROTECTED_KERNEL_OBJECT_POOL_اندازه ] = { 0 };
/*-----------------------------------------------------------*/

    ساكن int32_t MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_Free_شاخص = -1;

        /* This function is called only from resource create APIs
         * which are not supposed to be called from ISRs. Therefore,
         * we only need to suspend the scheduler and do not require
         * critical section. */
        vTaskSuspendAll();
        {
            لكل( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_اندازه; i++ )
            {
                إذا( xKernelObjectPool[ i ].x_دننی_Object_Handle == عدم )
                {
                    /* Mark this index as not free. */
                    xKernelObjectPool[ i ].x_دننی_Object_Handle = ( OpaqueObjectHandle_t ) ( ~0U );
                    l_Free_شاخص = i;
                    اكسر;
                }
            }
        }
        ( فراغ ) xTaskResumeAll();

        أرجع l_Free_شاخص;
    }
/*-----------------------------------------------------------*/

    ساكن فراغ MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( int32_t l_شاخص ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_دننی_شاخص_VALID( l_شاخص ) != pdFALSE );

        taskENTER_CRITICAL();
        {
            xKernelObjectPool[ l_شاخص ].x_دننی_Object_Handle = عدم;
            xKernelObjectPool[ l_شاخص ].ulKernelObjectType = KERNEL_OBJECT_TYPE_INVALID;
            xKernelObjectPool[ l_شاخص ].pv_Kernel_Object_معلومات = عدم;
        }
        taskEXIT_CRITICAL();
    }
/*-----------------------------------------------------------*/

    ساكن int32_t MPU_Get_شاخص_For_Handle( OpaqueObjectHandle_t xHandle,
                                          uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_شاخص = -1;

        configASSERT( xHandle != عدم );

        لكل( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_اندازه; i++ )
        {
            إذا( ( xKernelObjectPool[ i ].x_دننی_Object_Handle == xHandle ) &&
                ( xKernelObjectPool[ i ].ulKernelObjectType == ulKernelObjectType ) )
            {
                l_شاخص = i;
                اكسر;
            }
        }

        أرجع l_شاخص;
    }
/*-----------------------------------------------------------*/

    ساكن فراغ MPU_Store_Handle_And_معلومات_At_شاخص( int32_t l_شاخص,
                                               OpaqueObjectHandle_t xHandle,
                                               فراغ * pv_Kernel_Object_معلومات,
                                               uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_دننی_شاخص_VALID( l_شاخص ) != pdFALSE );
        xKernelObjectPool[ l_شاخص ].x_دننی_Object_Handle = xHandle;
        xKernelObjectPool[ l_شاخص ].ulKernelObjectType = ulKernelObjectType;
        xKernelObjectPool[ l_شاخص ].pv_Kernel_Object_معلومات = pv_Kernel_Object_معلومات;
    }
/*-----------------------------------------------------------*/

    ساكن OpaqueObjectHandle_t MPU_Get_Handle_At_شاخص( int32_t l_شاخص,
                                                      uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        OpaqueObjectHandle_t xObjectHandle = عدم;

        configASSERT( IS_دننی_شاخص_VALID( l_شاخص ) != pdFALSE );

        إذا( xKernelObjectPool[ l_شاخص ].ulKernelObjectType == ulKernelObjectType )
        {
            xObjectHandle = xKernelObjectPool[ l_شاخص ].x_دننی_Object_Handle;
        }

        أرجع xObjectHandle;
    }
/*-----------------------------------------------------------*/

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        فراغ v_Grant_Access_منزل_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                         int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;

            إذا( IS_EXTERNAL_شاخص_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                إذا( xExternalTaskHandle == عدم )
                {
                    v_پورټ_Grant_Access_منزل_Kernel_Object( xExternalTaskHandle, CONVERT_منزل_دننی_شاخص( lExternalKernelObjectHandle ) );
                }
                وإلا
                {
                    l_External_Task_شاخص = ( int32_t ) xExternalTaskHandle;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_External_Task_شاخص ) != pdFALSE )
                    {
                        x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_External_Task_شاخص ) );

                        إذا( x_دننی_Task_Handle != عدم )
                        {
                            v_پورټ_Grant_Access_منزل_Kernel_Object( x_دننی_Task_Handle,
                                                            CONVERT_منزل_دننی_شاخص( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #د_که_پای /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        فراغ v_Revoke_Access_منزل_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                          int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;

            إذا( IS_EXTERNAL_شاخص_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                إذا( xExternalTaskHandle == عدم )
                {
                    v_پورټ_Revoke_Access_منزل_Kernel_Object( xExternalTaskHandle, CONVERT_منزل_دننی_شاخص( lExternalKernelObjectHandle ) );
                }
                وإلا
                {
                    l_External_Task_شاخص = ( int32_t ) xExternalTaskHandle;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_External_Task_شاخص ) != pdFALSE )
                    {
                        x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_External_Task_شاخص ) );

                        إذا( x_دننی_Task_Handle != عدم )
                        {
                            v_پورټ_Revoke_Access_منزل_Kernel_Object( x_دننی_Task_Handle,
                                                             CONVERT_منزل_دننی_شاخص( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #د_که_پای /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ساكن فراغ MPU_TimerCallback( TimerHandle_t x_دننی_Handle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t i, l_شاخص = -1;
            TimerHandle_t xExternalHandle = عدم;
            TimerCallbackFunction_t px_Application_Call_شا = عدم;

            /* Coming from the timer task and therefore, should be valid. */
            configASSERT( x_دننی_Handle != عدم );

            لكل( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_اندازه; i++ )
            {
                إذا( ( ( TimerHandle_t ) xKernelObjectPool[ i ].x_دننی_Object_Handle == x_دننی_Handle ) &&
                    ( xKernelObjectPool[ i ].ulKernelObjectType == KERNEL_OBJECT_TYPE_TIMER ) )
                {
                    l_شاخص = i;
                    اكسر;
                }
            }

            configASSERT( l_شاخص != -1 );
            xExternalHandle = ( TimerHandle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );

            px_Application_Call_شا = ( TimerCallbackFunction_t ) xKernelObjectPool[ l_شاخص ].pv_Kernel_Object_معلومات;
            px_Application_Call_شا( xExternalHandle );
        }

    #د_که_پای /* #if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for tasks APIs.                   */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskDelayUntil == 1 )

        بنسټ_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ثابت px_پخوانی_Wake_وخت,
                                            TickType_t x_وخت_Increment ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ثابت px_پخوانی_Wake_وخت,
                                            TickType_t x_وخت_Increment ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            بنسټ_Type_t x_Is_پخوانی_Wake_وخت_Accessible = pdFALSE;

            إذا( ( px_پخوانی_Wake_وخت != عدم ) && ( x_وخت_Increment > 0U ) )
            {
                x_Is_پخوانی_Wake_وخت_Accessible = x_پورټ_Is_Authorized_منزل_Access_بفر( px_پخوانی_Wake_وخت,
                                                                                 حجم( TickType_t ),
                                                                                 ( tskMPU_WRITE_PERMISSION | tskMPU_READ_PERMISSION ) );

                إذا( x_Is_پخوانی_Wake_وخت_Accessible == pdTRUE )
                {
                    xReturn = xTaskDelayUntil( px_پخوانی_Wake_وخت, x_وخت_Increment );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskAbortDelay == 1 )

        بنسټ_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) xTask;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                {
                    x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Task_Handle != عدم )
                    {
                        xReturn = xTaskAbortDelay( x_دننی_Task_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelay == 1 )

        فراغ MPU_vTaskDelayImpl( TickType_t x_Ticks_منزل_Delay ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskDelayImpl( TickType_t x_Ticks_منزل_Delay ) /* PRIVILEGED_FUNCTION */
        {
            vTaskDelay( x_Ticks_منزل_Delay );
        }

    #د_که_پای /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_لومړیتوب_Get == 1 )

        UBaseType_t MPU_ux_Task_لومړیتوب_Get_Impl( ثابت TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_لومړیتوب_Get_Impl( ثابت TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;

            إذا( pxTask == عدم )
            {
                uxReturn = ux_Task_لومړیتوب_Get( pxTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) pxTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_دننی_Task_Handle != عدم )
                        {
                            uxReturn = ux_Task_لومړیتوب_Get( x_دننی_Task_Handle );
                        }
                    }
                }
            }

            أرجع uxReturn;
        }

    #د_که_پای /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            eTaskState eReturn = eInvalid;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            l_شاخص = ( int32_t ) pxTask;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                {
                    x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Task_Handle != عدم )
                    {
                        eReturn = eTaskGetState( x_دننی_Task_Handle );
                    }
                }
            }

            أرجع eReturn;
        }

    #د_که_پای /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        فراغ MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_حالت_t * px_Task_حالت,
                                   بنسټ_Type_t x_Get_Free_ډېری_Space,
                                   eTaskState eState ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_حالت_t * px_Task_حالت,
                                   بنسټ_Type_t x_Get_Free_ډېری_Space,
                                   eTaskState eState ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            بنسټ_Type_t x_Is_Task_حالت_Writeable = pdFALSE;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            x_Is_Task_حالت_Writeable = x_پورټ_Is_Authorized_منزل_Access_بفر( px_Task_حالت,
                                                                      حجم( Task_حالت_t ),
                                                                      tskMPU_WRITE_PERMISSION );

            إذا( x_Is_Task_حالت_Writeable == pdTRUE )
            {
                إذا( xTask == عدم )
                {
                    vTaskGetInfo( xTask, px_Task_حالت, x_Get_Free_ډېری_Space, eState );
                }
                وإلا
                {
                    l_شاخص = ( int32_t ) xTask;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                        {
                            x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                            إذا( x_دننی_Task_Handle != عدم )
                            {
                                vTaskGetInfo( x_دننی_Task_Handle, px_Task_حالت, x_Get_Free_ډېری_Space, eState );
                            }
                        }
                    }
                }
            }
        }

    #د_که_پای /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( فراغ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xIdleTaskHandle = عدم;

            xIdleTaskHandle = xTaskGetIdleTaskHandle();

            أرجع xIdleTaskHandle;
        }

    #د_که_پای /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )

        فراغ MPU_vTaskSuspendImpl( TaskHandle_t px_Task_منزل_Suspend ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskSuspendImpl( TaskHandle_t px_Task_منزل_Suspend ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( px_Task_منزل_Suspend == عدم )
            {
                vTaskSuspend( px_Task_منزل_Suspend );
            }
            وإلا
            {
                /* After the scheduler starts, only privileged tasks are allowed
                 * to suspend other tasks. */
                #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )
                    إذا( ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) || ( پورټ_IS_TASK_PRIVILEGED() == pdTRUE ) )
                #وإلا
                    إذا( پورټ_IS_TASK_PRIVILEGED() == pdTRUE )
                #د_که_پای
                {
                    l_شاخص = ( int32_t ) px_Task_منزل_Suspend;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                        {
                            x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                            إذا( x_دننی_Task_Handle != عدم )
                            {
                                vTaskSuspend( x_دننی_Task_Handle );
                            }
                        }
                    }
                }
            }
        }

    #د_که_پای /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )

        فراغ MPU_vTaskResumeImpl( TaskHandle_t px_Task_منزل_Resume ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskResumeImpl( TaskHandle_t px_Task_منزل_Resume ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            l_شاخص = ( int32_t ) px_Task_منزل_Resume;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                {
                    x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Task_Handle != عدم )
                    {
                        vTaskResume( x_دننی_Task_Handle );
                    }
                }
            }
        }

    #د_که_پای /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_شمېر_Impl( فراغ ) PRIVILEGED_FUNCTION;

    TickType_t MPU_x_Task_Get_Tick_شمېر_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        TickType_t xReturn;

        xReturn = x_Task_Get_Tick_شمېر();

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_شمېره_د_Tasks_Impl( فراغ ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Task_Get_شمېره_د_Tasks_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn;

        uxReturn = ux_Task_Get_شمېره_د_Tasks();

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_پرلپسې_وخت_STATS == 1 )

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_پرلپسې_وخت_Counter_Impl( ثابت TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_پرلپسې_وخت_Counter_Impl( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_پرلپسې_وخت_COUNTER_TYPE xReturn = 0;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                xReturn = ul_Task_Get_پرلپسې_وخت_Counter( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_دننی_Task_Handle != عدم )
                        {
                            xReturn = ul_Task_Get_پرلپسې_وخت_Counter( x_دننی_Task_Handle );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_پرلپسې_وخت_STATS == 1 )

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_پرلپسې_وخت_Percent_Impl( ثابت TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_پرلپسې_وخت_Percent_Impl( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_پرلپسې_وخت_COUNTER_TYPE xReturn = 0;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                xReturn = ul_Task_Get_پرلپسې_وخت_Percent( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_دننی_Task_Handle != عدم )
                        {
                            xReturn = ul_Task_Get_پرلپسې_وخت_Percent( x_دننی_Task_Handle );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_پرلپسې_وخت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_Idle_پرلپسې_وخت_Percent_Impl( فراغ ) PRIVILEGED_FUNCTION;

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_Idle_پرلپسې_وخت_Percent_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            config_پرلپسې_وخت_COUNTER_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_پرلپسې_وخت_Percent();

            أرجع xReturn;
        }

    #د_که_پای /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_پرلپسې_وخت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_Idle_پرلپسې_وخت_Counter_Impl( فراغ ) PRIVILEGED_FUNCTION;

        config_پرلپسې_وخت_COUNTER_TYPE MPU_ul_Task_Get_Idle_پرلپسې_وخت_Counter_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            config_پرلپسې_وخت_COUNTER_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_پرلپسې_وخت_Counter();

            أرجع xReturn;
        }

    #د_که_پای /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_نښان == 1 )

        فراغ MPU_v_Task_سېټ_Application_Task_نښان_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_نښان_ارزښت ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Task_سېټ_Application_Task_نښان_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_نښان_ارزښت ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_دننی_Task_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                v_Task_سېټ_Application_Task_نښان( xTask, px_نښان_ارزښت );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_دننی_Task_Handle != عدم )
                        {
                            v_Task_سېټ_Application_Task_نښان( x_دننی_Task_Handle, px_نښان_ارزښت );
                        }
                    }
                }
            }
        }

    #د_که_پای /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_نښان == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_نښان_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_نښان_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = عدم;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                xReturn = x_Task_Get_Application_Task_نښان( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_دننی_Task_Handle != عدم )
                        {
                            xReturn = x_Task_Get_Application_Task_نښان( x_دننی_Task_Handle );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_عدد_THREAD_LOCAL_STORAGE_اشارې != 0 )

        فراغ MPU_v_Task_سېټ_Thread_Local_Storage_اشاره_ګر_Impl( TaskHandle_t x_Task_منزل_سېټ,
                                                        بنسټ_Type_t x_شاخص,
                                                        فراغ * pv_ارزښت ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Task_سېټ_Thread_Local_Storage_اشاره_ګر_Impl( TaskHandle_t x_Task_منزل_سېټ,
                                                        بنسټ_Type_t x_شاخص,
                                                        فراغ * pv_ارزښت ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( x_Task_منزل_سېټ == عدم )
            {
                v_Task_سېټ_Thread_Local_Storage_اشاره_ګر( x_Task_منزل_سېټ, x_شاخص, pv_ارزښت );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) x_Task_منزل_سېټ;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_دننی_Task_Handle != عدم )
                        {
                            v_Task_سېټ_Thread_Local_Storage_اشاره_ګر( x_دننی_Task_Handle, x_شاخص, pv_ارزښت );
                        }
                    }
                }
            }
        }

    #د_که_پای /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_عدد_THREAD_LOCAL_STORAGE_اشارې != 0 )

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_ګر_Impl( TaskHandle_t x_Task_منزل_Query,
                                                           بنسټ_Type_t x_شاخص ) PRIVILEGED_FUNCTION;

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_ګر_Impl( TaskHandle_t x_Task_منزل_Query,
                                                           بنسټ_Type_t x_شاخص ) /* PRIVILEGED_FUNCTION */
        {
            فراغ * pvReturn = عدم;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( x_Task_منزل_Query == عدم )
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_اشاره_ګر( x_Task_منزل_Query, x_شاخص );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) x_Task_منزل_Query;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_دننی_Task_Handle != عدم )
                        {
                            pvReturn = pv_Task_Get_Thread_Local_Storage_اشاره_ګر( x_دننی_Task_Handle, x_شاخص );
                        }
                    }
                }
            }

            أرجع pvReturn;
        }

    #د_که_پای /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_حالت_t * px_Task_حالت_Array,
                                                  UBaseType_t ux_Array_اندازه,
                                                  config_پرلپسې_وخت_COUNTER_TYPE * pul_ټول_پرلپسې_وخت ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_حالت_t * px_Task_حالت_Array,
                                                  UBaseType_t ux_Array_اندازه,
                                                  config_پرلپسې_وخت_COUNTER_TYPE * pul_ټول_پرلپسې_وخت ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            بنسټ_Type_t x_Is_Task_حالت_Array_Writeable = pdFALSE;
            بنسټ_Type_t x_Is_ټول_پرلپسې_وخت_Writeable = pdFALSE;

            إذا( mpu_MULTIPLY_BASETYPE_WILL_ډکېدنه( حجم( Task_حالت_t ), ux_Array_اندازه ) == 0 )
            {
                x_Is_Task_حالت_Array_Writeable = x_پورټ_Is_Authorized_منزل_Access_بفر( px_Task_حالت_Array,
                                                                               حجم( Task_حالت_t ) * ( size_t ) ux_Array_اندازه,
                                                                               tskMPU_WRITE_PERMISSION );

                إذا( pul_ټول_پرلپسې_وخت != عدم )
                {
                    x_Is_ټول_پرلپسې_وخت_Writeable = x_پورټ_Is_Authorized_منزل_Access_بفر( pul_ټول_پرلپسې_وخت,
                                                                                حجم( config_پرلپسې_وخت_COUNTER_TYPE ),
                                                                                tskMPU_WRITE_PERMISSION );
                }

                إذا( ( x_Is_Task_حالت_Array_Writeable == pdTRUE ) &&
                    ( ( pul_ټول_پرلپسې_وخت == عدم ) || ( x_Is_ټول_پرلپسې_وخت_Writeable == pdTRUE ) ) )
                {
                    uxReturn = uxTaskGetSystemState( px_Task_حالت_Array, ux_Array_اندازه, pul_ټول_پرلپسې_وخت );
                }
            }

            أرجع uxReturn;
        }

    #د_که_پای /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ډېری_لوړ_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ډېری_لوړ_Water_Mark_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_Get_ډېری_لوړ_Water_Mark_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_Get_ډېری_لوړ_Water_Mark( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_دننی_Task_Handle != عدم )
                        {
                            uxReturn = ux_Task_Get_ډېری_لوړ_Water_Mark( x_دننی_Task_Handle );
                        }
                    }
                }
            }

            أرجع uxReturn;
        }

    #د_که_پای /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ډېری_لوړ_Water_Mark2 == 1 )

        config_ډېری_ژوروالی_TYPE MPU_ux_Task_Get_ډېری_لوړ_Water_Mark2_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_ډېری_ژوروالی_TYPE MPU_ux_Task_Get_ډېری_لوړ_Water_Mark2_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_ډېری_ژوروالی_TYPE uxReturn = 0;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_Get_ډېری_لوړ_Water_Mark2( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_دننی_Task_Handle != عدم )
                        {
                            uxReturn = ux_Task_Get_ډېری_لوړ_Water_Mark2( x_دننی_Task_Handle );
                        }
                    }
                }
            }

            أرجع uxReturn;
        }

    #د_که_پای /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( فراغ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_دننی_Task_Handle = عدم;
            TaskHandle_t xExternalTaskHandle = عدم;
            int32_t l_شاخص;

            x_دننی_Task_Handle = xTaskGetCurrentTaskHandle();

            إذا( x_دننی_Task_Handle != عدم )
            {
                l_شاخص = MPU_Get_شاخص_For_Task_Handle( x_دننی_Task_Handle );

                إذا( l_شاخص != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
            }

            أرجع xExternalTaskHandle;
        }

    #د_که_پای /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )

        بنسټ_Type_t MPU_xTaskGetSchedulerStateImpl( فراغ ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_xTaskGetSchedulerStateImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = taskSCHEDULER_NOT_STARTED;

            xReturn = xTaskGetSchedulerState();

            أرجع xReturn;
        }

    #د_که_پای /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_v_Task_سېټ_وخت_بهر_State_Impl( وخت_بهر_t * ثابت px_وخت_بهر ) PRIVILEGED_FUNCTION;

    فراغ MPU_v_Task_سېټ_وخت_بهر_State_Impl( وخت_بهر_t * ثابت px_وخت_بهر ) /* PRIVILEGED_FUNCTION */
    {
        بنسټ_Type_t x_Is_وخت_بهر_Writeable = pdFALSE;

        إذا( px_وخت_بهر != عدم )
        {
            x_Is_وخت_بهر_Writeable = x_پورټ_Is_Authorized_منزل_Access_بفر( px_وخت_بهر,
                                                                   حجم( وخت_بهر_t ),
                                                                   tskMPU_WRITE_PERMISSION );

            إذا( x_Is_وخت_بهر_Writeable == pdTRUE )
            {
                v_Task_سېټ_وخت_بهر_State( px_وخت_بهر );
            }
        }
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_Task_Check_For_وخت_بهر_Impl( وخت_بهر_t * ثابت px_وخت_بهر,
                                             TickType_t * ثابت px_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

    بنسټ_Type_t MPU_x_Task_Check_For_وخت_بهر_Impl( وخت_بهر_t * ثابت px_وخت_بهر,
                                             TickType_t * ثابت px_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
    {
        بنسټ_Type_t xReturn = pdFALSE;
        بنسټ_Type_t x_Is_وخت_بهر_Writeable = pdFALSE;
        بنسټ_Type_t x_Is_Ticks_منزل_Wait_Writeable = pdFALSE;

        إذا( ( px_وخت_بهر != عدم ) && ( px_Ticks_منزل_Wait != عدم ) )
        {
            x_Is_وخت_بهر_Writeable = x_پورټ_Is_Authorized_منزل_Access_بفر( px_وخت_بهر,
                                                                   حجم( وخت_بهر_t ),
                                                                   tskMPU_WRITE_PERMISSION );
            x_Is_Ticks_منزل_Wait_Writeable = x_پورټ_Is_Authorized_منزل_Access_بفر( px_Ticks_منزل_Wait,
                                                                       حجم( TickType_t ),
                                                                       tskMPU_WRITE_PERMISSION );

            إذا( ( x_Is_وخت_بهر_Writeable == pdTRUE ) && ( x_Is_Ticks_منزل_Wait_Writeable == pdTRUE ) )
            {
                xReturn = x_Task_Check_For_وخت_بهر( px_وخت_بهر, px_Ticks_منزل_Wait );
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنسټ_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_منزل_Notify,
                                           UBaseType_t ux_شاخص_منزل_Notify,
                                           uint32_t ul_ارزښت,
                                           eNotifyAction eAction,
                                           uint32_t * pul_پخوانی_Notification_ارزښت ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyParams_t xParams;

            xParams.x_Task_منزل_Notify = x_Task_منزل_Notify;
            xParams.ux_شاخص_منزل_Notify = ux_شاخص_منزل_Notify;
            xParams.ul_ارزښت = ul_ارزښت;
            xParams.eAction = eAction;
            xParams.pul_پخوانی_Notification_ارزښت = pul_پخوانی_Notification_ارزښت;

            xReturn = MPU_x_Task_Generic_Notify_ثبت( &( xParams ) );

            أرجع xReturn;
        }

        بنسټ_Type_t MPU_xTaskGenericNotifyImpl( ثابت xTaskGenericNotifyParams_t * pxParams ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_xTaskGenericNotifyImpl( ثابت xTaskGenericNotifyParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            بنسټ_Type_t x_Is_پخوانی_Notification_ارزښت_Writeable = pdFALSE;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;
            بنسټ_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورټ_Is_Authorized_منزل_Access_بفر( pxParams,
                                                                      حجم( xTaskGenericNotifyParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( ( pxParams->ux_شاخص_منزل_Notify < configTASK_NOTIFICATION_ARRAY_ENTRIES ) &&
                    ( ( pxParams->eAction == eNoAction ) ||
                      ( pxParams->eAction == e_سېټ_بټونه ) ||
                      ( pxParams->eAction == eIncrement ) ||
                      ( pxParams->eAction == e_سېټ_ارزښت_With_Overwrite ) ||
                      ( pxParams->eAction == e_سېټ_ارزښت_Without_Overwrite ) ) )
                {
                    إذا( pxParams->pul_پخوانی_Notification_ارزښت != عدم )
                    {
                        x_Is_پخوانی_Notification_ارزښت_Writeable = x_پورټ_Is_Authorized_منزل_Access_بفر( pxParams->pul_پخوانی_Notification_ارزښت,
                                                                                                 حجم( uint32_t ),
                                                                                                 tskMPU_WRITE_PERMISSION );
                    }

                    إذا( ( pxParams->pul_پخوانی_Notification_ارزښت == عدم ) ||
                        ( x_Is_پخوانی_Notification_ارزښت_Writeable == pdTRUE ) )
                    {
                        l_شاخص = ( int32_t ) ( pxParams->x_Task_منزل_Notify );

                        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                            إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                            {
                                x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                                إذا( x_دننی_Task_Handle != عدم )
                                {
                                    xReturn = xTaskGenericNotify( x_دننی_Task_Handle,
                                                                  pxParams->ux_شاخص_منزل_Notify,
                                                                  pxParams->ul_ارزښت,
                                                                  pxParams->eAction,
                                                                  pxParams->pul_پخوانی_Notification_ارزښت );
                                }
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنسټ_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_شاخص_منزل_Wait_On,
                                               uint32_t ul_بټونه_منزل_Clear_On_ثبت,
                                               uint32_t ul_بټونه_منزل_Clear_On_Exit,
                                               uint32_t * pul_Notification_ارزښت,
                                               TickType_t x_Ticks_منزل_Wait )
        {
            بنسټ_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyWaitParams_t xParams;

            xParams.ux_شاخص_منزل_Wait_On = ux_شاخص_منزل_Wait_On;
            xParams.ul_بټونه_منزل_Clear_On_ثبت = ul_بټونه_منزل_Clear_On_ثبت;
            xParams.ul_بټونه_منزل_Clear_On_Exit = ul_بټونه_منزل_Clear_On_Exit;
            xParams.pul_Notification_ارزښت = pul_Notification_ارزښت;
            xParams.x_Ticks_منزل_Wait = x_Ticks_منزل_Wait;

            xReturn = MPU_x_Task_Generic_Notify_Wait_ثبت( &( xParams ) );

            أرجع xReturn;
        }

        بنسټ_Type_t MPU_xTaskGenericNotifyWaitImpl( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_xTaskGenericNotifyWaitImpl( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            بنسټ_Type_t x_Is_Notification_ارزښت_Writable = pdFALSE;
            بنسټ_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورټ_Is_Authorized_منزل_Access_بفر( pxParams,
                                                                      حجم( xTaskGenericNotifyWaitParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( pxParams->ux_شاخص_منزل_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
                {
                    إذا( pxParams->pul_Notification_ارزښت != عدم )
                    {
                        x_Is_Notification_ارزښت_Writable = x_پورټ_Is_Authorized_منزل_Access_بفر( pxParams->pul_Notification_ارزښت,
                                                                                        حجم( uint32_t ),
                                                                                        tskMPU_WRITE_PERMISSION );
                    }

                    إذا( ( pxParams->pul_Notification_ارزښت == عدم ) ||
                        ( x_Is_Notification_ارزښت_Writable == pdTRUE ) )
                    {
                        xReturn = xTaskGenericNotifyWait( pxParams->ux_شاخص_منزل_Wait_On,
                                                          pxParams->ul_بټونه_منزل_Clear_On_ثبت,
                                                          pxParams->ul_بټونه_منزل_Clear_On_Exit,
                                                          pxParams->pul_Notification_ارزښت,
                                                          pxParams->x_Ticks_منزل_Wait );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_شاخص_منزل_Wait_On,
                                                  بنسټ_Type_t x_Clear_شمېر_On_Exit,
                                                  TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_شاخص_منزل_Wait_On,
                                                  بنسټ_Type_t x_Clear_شمېر_On_Exit,
                                                  TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;

            إذا( ux_شاخص_منزل_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ulReturn = ulTaskGenericNotifyTake( ux_شاخص_منزل_Wait_On, x_Clear_شمېر_On_Exit, x_Ticks_منزل_Wait );
            }

            أرجع ulReturn;
        }

    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنسټ_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_شاخص_منزل_Clear ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_شاخص_منزل_Clear ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( ux_شاخص_منزل_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                إذا( xTask == عدم )
                {
                    xReturn = xTaskGenericNotifyStateClear( xTask, ux_شاخص_منزل_Clear );
                }
                وإلا
                {
                    l_شاخص = ( int32_t ) xTask;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                        {
                            x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                            إذا( x_دننی_Task_Handle != عدم )
                            {
                                xReturn = xTaskGenericNotifyStateClear( x_دننی_Task_Handle, ux_شاخص_منزل_Clear );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_ارزښت_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_شاخص_منزل_Clear,
                                                        uint32_t ul_بټونه_منزل_Clear ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ul_Task_Generic_Notify_ارزښت_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_شاخص_منزل_Clear,
                                                        uint32_t ul_بټونه_منزل_Clear ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( ux_شاخص_منزل_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                إذا( xTask == عدم )
                {
                    ulReturn = ul_Task_Generic_Notify_ارزښت_Clear( xTask, ux_شاخص_منزل_Clear, ul_بټونه_منزل_Clear );
                }
                وإلا
                {
                    l_شاخص = ( int32_t ) xTask;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                        {
                            x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                            إذا( x_دننی_Task_Handle != عدم )
                            {
                                ulReturn = ul_Task_Generic_Notify_ارزښت_Clear( x_دننی_Task_Handle, ux_شاخص_منزل_Clear, ul_بټونه_منزل_Clear );
                            }
                        }
                    }
                }
            }

            أرجع ulReturn;
        }

    #د_که_پای /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Task APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ویش == 1 )

        بنسټ_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_کوډ,
                                    ثابت حرف * ثابت pcName,
                                    ثابت config_ډېری_ژوروالی_TYPE ux_ډېری_ژوروالی,
                                    فراغ * pvParameters,
                                    UBaseType_t ux_لومړیتوب,
                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                /* xTaskCreate() can only be used to create privileged tasks in MPU port. */
                إذا( ( ux_لومړیتوب & پورټ_PRIVILEGE_بټ ) != 0 )
                {
                    xReturn = xTaskCreate( pv_Task_کوډ, pcName, ux_ډېری_ژوروالی, pvParameters, ux_لومړیتوب, &( x_دننی_Task_Handle ) );

                    إذا( ( xReturn == pdPASS ) && ( x_دننی_Task_Handle != عدم ) )
                    {
                        MPU_Store_Task_Handle_At_شاخص( l_شاخص, x_دننی_Task_Handle );

                        إذا( pxCreatedTask != عدم )
                        {
                            *pxCreatedTask = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                        }
                    }
                    وإلا
                    {
                        MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ویش == 1 )

        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_کوډ,
                                            ثابت حرف * ثابت pcName,
                                            ثابت config_ډېری_ژوروالی_TYPE ux_ډېری_ژوروالی,
                                            فراغ * ثابت pvParameters,
                                            UBaseType_t ux_لومړیتوب,
                                            ډېری_Type_t * ثابت pux_ډېری_بفر,
                                            StaticTask_t * ثابت px_Task_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xExternalTaskHandle = عدم;
            TaskHandle_t x_دننی_Task_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_دننی_Task_Handle = xTaskCreateStatic( px_Task_کوډ, pcName, ux_ډېری_ژوروالی, pvParameters, ux_لومړیتوب, pux_ډېری_بفر, px_Task_بفر );

                إذا( x_دننی_Task_Handle != عدم )
                {
                    MPU_Store_Task_Handle_At_شاخص( l_شاخص, x_دننی_Task_Handle );

                    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        إذا( ( ux_لومړیتوب & پورټ_PRIVILEGE_بټ ) == 0 )
                        {
                            v_پورټ_Grant_Access_منزل_Kernel_Object( x_دننی_Task_Handle, l_شاخص );
                        }
                    }
                    #د_که_پای

                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع xExternalTaskHandle;
        }

    #د_که_پای /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelete == 1 )

        فراغ MPU_vTaskDelete( TaskHandle_t px_Task_منزل_Delete ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_دننی_Task_Handle = عدم;
            int32_t l_شاخص;

            إذا( px_Task_منزل_Delete == عدم )
            {
                x_دننی_Task_Handle = xTaskGetCurrentTaskHandle();
                l_شاخص = MPU_Get_شاخص_For_Task_Handle( x_دننی_Task_Handle );

                إذا( l_شاخص != -1 )
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }

                vTaskDelete( x_دننی_Task_Handle );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) px_Task_منزل_Delete;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Task_Handle != عدم )
                    {
                        MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( CONVERT_منزل_دننی_شاخص( l_شاخص ) );
                        vTaskDelete( x_دننی_Task_Handle );
                    }
                }
            }
        }

    #د_که_پای /* #if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/


    #إذا ( INCLUDE_v_Task_لومړیتوب_سېټ == 1 )

        فراغ MPU_v_Task_لومړیتوب_سېټ( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_لومړیتوب ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_دننی_Task_Handle = عدم;
            int32_t l_شاخص;

            إذا( pxTask == عدم )
            {
                v_Task_لومړیتوب_سېټ( pxTask, ux_New_لومړیتوب );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) pxTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Task_Handle != عدم )
                    {
                        v_Task_لومړیتوب_سېټ( x_دننی_Task_Handle, ux_New_لومړیتوب );
                    }
                }
            }
        }

    #د_که_پای /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetHandle == 1 )

        TaskHandle_t MPU_xTaskGetHandle( ثابت حرف * pc_Name_منزل_Query ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_دننی_Task_Handle = عدم;
            TaskHandle_t xExternalTaskHandle = عدم;
            int32_t l_شاخص;

            x_دننی_Task_Handle = xTaskGetHandle( pc_Name_منزل_Query );

            إذا( x_دننی_Task_Handle != عدم )
            {
                l_شاخص = MPU_Get_شاخص_For_Task_Handle( x_دننی_Task_Handle );

                إذا( l_شاخص != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
            }

            أرجع xExternalTaskHandle;
        }

    #د_که_پای /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/


    #إذا ( config_USE_APPLICATION_TASK_نښان == 1 )

        بنسټ_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     فراغ * pvParameter ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Task_Handle != عدم )
                    {
                        xReturn = xTaskCallApplicationTaskHook( x_دننی_Task_Handle, pvParameter );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ویش == 1 )

        بنسټ_Type_t MPU_xTaskCreateRestricted( ثابت TaskParameters_t * ثابت pxTaskDefinition,
                                              TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                xReturn = xTaskCreateRestricted( pxTaskDefinition, &( x_دننی_Task_Handle ) );

                إذا( ( xReturn == pdPASS ) && ( x_دننی_Task_Handle != عدم ) )
                {
                    MPU_Store_Task_Handle_At_شاخص( l_شاخص, x_دننی_Task_Handle );

                    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        إذا( ( pxTaskDefinition->ux_لومړیتوب & پورټ_PRIVILEGE_بټ ) == 0 )
                        {
                            v_پورټ_Grant_Access_منزل_Kernel_Object( x_دننی_Task_Handle, l_شاخص );
                        }
                    }
                    #د_که_پای

                    إذا( pxCreatedTask != عدم )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                    }
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ویش == 1 )

        بنسټ_Type_t MPU_xTaskCreateRestrictedStatic( ثابت TaskParameters_t * ثابت pxTaskDefinition,
                                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                xReturn = xTaskCreateRestrictedStatic( pxTaskDefinition, &( x_دننی_Task_Handle ) );

                إذا( ( xReturn == pdPASS ) && ( x_دننی_Task_Handle != عدم ) )
                {
                    MPU_Store_Task_Handle_At_شاخص( l_شاخص, x_دننی_Task_Handle );

                    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        إذا( ( pxTaskDefinition->ux_لومړیتوب & پورټ_PRIVILEGE_بټ ) == 0 )
                        {
                            v_پورټ_Grant_Access_منزل_Kernel_Object( x_دننی_Task_Handle, l_شاخص );
                        }
                    }
                    #د_که_پای

                    إذا( pxCreatedTask != عدم )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                    }
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    فراغ MPU_vTaskAllocateMPURegions( TaskHandle_t x_Task_منزل_Modify,
                                      ثابت حافظه_Region_t * ثابت xRegions ) /* PRIVILEGED_FUNCTION */
    {
        TaskHandle_t x_دننی_Task_Handle = عدم;
        int32_t l_شاخص;

        إذا( x_Task_منزل_Modify == عدم )
        {
            vTaskAllocateMPURegions( x_Task_منزل_Modify, xRegions );
        }
        وإلا
        {
            l_شاخص = ( int32_t ) x_Task_منزل_Modify;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_Task_Handle != عدم )
                {
                    vTaskAllocateMPURegions( x_دننی_Task_Handle, xRegions );
                }
            }
        }
    }
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ویش == 1 )

        بنسټ_Type_t MPU_xTaskGetStaticBuffers( TaskHandle_t xTask,
                                              ډېری_Type_t ** ppux_ډېری_بفر,
                                              StaticTask_t ** ppx_Task_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_دننی_Task_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t xReturn = pdFALSE;

            إذا( xTask == عدم )
            {
                x_دننی_Task_Handle = xTaskGetCurrentTaskHandle();
                xReturn = xTaskGetStaticBuffers( x_دننی_Task_Handle, ppux_ډېری_بفر, ppx_Task_بفر );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Task_Handle != عدم )
                    {
                        xReturn = xTaskGetStaticBuffers( x_دننی_Task_Handle, ppux_ډېری_بفر, ppx_Task_بفر );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    حرف * MPU_pcTaskGetName( TaskHandle_t x_Task_منزل_Query ) /* PRIVILEGED_FUNCTION */
    {
        حرف * pcReturn = عدم;
        int32_t l_شاخص;
        TaskHandle_t x_دننی_Task_Handle = عدم;

        إذا( x_Task_منزل_Query == عدم )
        {
            pcReturn = pcTaskGetName( x_Task_منزل_Query );
        }
        وإلا
        {
            l_شاخص = ( int32_t ) x_Task_منزل_Query;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_Task_Handle != عدم )
                {
                    pcReturn = pcTaskGetName( x_دننی_Task_Handle );
                }
            }
        }

        أرجع pcReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_لومړیتوب_Get == 1 )

        UBaseType_t MPU_ux_Task_لومړیتوب_Get_From_ISR( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_لومړیتوب_Get_From_ISR( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Task_Handle != عدم )
                    {
                        uxReturn = ux_Task_لومړیتوب_Get_From_ISR( x_دننی_Task_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #د_که_پای /* #if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_ux_Task_لومړیتوب_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_بنسټ_لومړیتوب_Get( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_بنسټ_لومړیتوب_Get( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Task_Handle != عدم )
                    {
                        uxReturn = ux_Task_بنسټ_لومړیتوب_Get( x_دننی_Task_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #د_که_پای /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_ux_Task_لومړیتوب_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_بنسټ_لومړیتوب_Get_From_ISR( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_بنسټ_لومړیتوب_Get_From_ISR( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Task_Handle != عدم )
                    {
                        uxReturn = ux_Task_بنسټ_لومړیتوب_Get_From_ISR( x_دننی_Task_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #د_که_پای /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

        بنسټ_Type_t MPU_xTaskResumeFromISR( TaskHandle_t x_Task_منزل_Resume ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;

            l_شاخص = ( int32_t ) x_Task_منزل_Resume;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_Task_Handle != عدم )
                {
                    xReturn = xTaskResumeFromISR( x_دننی_Task_Handle );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )*/
/*---------------------------------------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_نښان == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_نښان_From_ISR( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = عدم;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                xReturn = x_Task_Get_Application_Task_نښان_From_ISR( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Task_Handle != عدم )
                    {
                        xReturn = x_Task_Get_Application_Task_نښان_From_ISR( x_دننی_Task_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنسټ_Type_t MPU_xTaskGenericNotifyFromISR( TaskHandle_t x_Task_منزل_Notify,
                                                  UBaseType_t ux_شاخص_منزل_Notify,
                                                  uint32_t ul_ارزښت,
                                                  eNotifyAction eAction,
                                                  uint32_t * pul_پخوانی_Notification_ارزښت,
                                                  بنسټ_Type_t * px_Higher_لومړیتوب_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;

            l_شاخص = ( int32_t ) x_Task_منزل_Notify;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_Task_Handle != عدم )
                {
                    xReturn = xTaskGenericNotifyFromISR( x_دننی_Task_Handle, ux_شاخص_منزل_Notify, ul_ارزښت, eAction, pul_پخوانی_Notification_ارزښت, px_Higher_لومړیتوب_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        فراغ MPU_vTaskGenericNotifyGiveFromISR( TaskHandle_t x_Task_منزل_Notify,
                                                UBaseType_t ux_شاخص_منزل_Notify,
                                                بنسټ_Type_t * px_Higher_لومړیتوب_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            TaskHandle_t x_دننی_Task_Handle = عدم;

            l_شاخص = ( int32_t ) x_Task_منزل_Notify;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_Task_Handle != عدم )
                {
                    vTaskGenericNotifyGiveFromISR( x_دننی_Task_Handle, ux_شاخص_منزل_Notify, px_Higher_لومړیتوب_Task_Woken );
                }
            }
        }
    #د_که_پای /*#if ( configUSE_TASK_NOTIFICATIONS == 1 )*/
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for queue APIs.                   */
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Generic_Send_Impl( کتار_Handle_t x_کتار,
                                          ثابت فراغ * ثابت pv_توکی_منزل_کتار,
                                          TickType_t x_Ticks_منزل_Wait,
                                          بنسټ_Type_t xCopyPosition ) PRIVILEGED_FUNCTION;

    بنسټ_Type_t MPU_x_کتار_Generic_Send_Impl( کتار_Handle_t x_کتار,
                                          ثابت فراغ * ثابت pv_توکی_منزل_کتار,
                                          TickType_t x_Ticks_منزل_Wait,
                                          بنسټ_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_شاخص;
        کتار_Handle_t x_دننی_کتار_Handle = عدم;
        بنسټ_Type_t xReturn = pdFAIL;
        بنسټ_Type_t x_Is_توکی_منزل_کتار_Readable = pdFALSE;
        بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار = pdFALSE;
        UBaseType_t ux_کتار_توکی_اندازه, ux_کتار_اوږدتیا;

        l_شاخص = ( int32_t ) x_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_کتار = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_کتار == pdTRUE )
            {
                x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_کتار_Handle != عدم )
                {
                    ux_کتار_توکی_اندازه = ux_کتار_Get_کتار_توکی_اندازه( x_دننی_کتار_Handle );
                    ux_کتار_اوږدتیا = ux_کتار_Get_کتار_اوږدتیا( x_دننی_کتار_Handle );

                    إذا( ( !( ( pv_توکی_منزل_کتار == عدم ) && ( ux_کتار_توکی_اندازه != ( UBaseType_t ) 0U ) ) ) &&
                        ( !( ( xCopyPosition == کتار_OVERWRITE ) && ( ux_کتار_اوږدتیا != ( UBaseType_t ) 1U ) ) )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                        #د_که_پای
                        )
                    {
                        إذا( pv_توکی_منزل_کتار != عدم )
                        {
                            x_Is_توکی_منزل_کتار_Readable = x_پورټ_Is_Authorized_منزل_Access_بفر( pv_توکی_منزل_کتار,
                                                                                      ux_کتار_توکی_اندازه,
                                                                                      tskMPU_READ_PERMISSION );
                        }

                        إذا( ( pv_توکی_منزل_کتار == عدم ) || ( x_Is_توکی_منزل_کتار_Readable == pdTRUE ) )
                        {
                            xReturn = x_کتار_Generic_Send( x_دننی_کتار_Handle, pv_توکی_منزل_کتار, x_Ticks_منزل_Wait, xCopyPosition );
                        }
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_کتار_Messages_انتظار_Impl( ثابت کتار_Handle_t px_کتار ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_کتار_Messages_انتظار_Impl( ثابت کتار_Handle_t px_کتار ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_شاخص;
        کتار_Handle_t x_دننی_کتار_Handle = عدم;
        UBaseType_t uxReturn = 0;
        بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار = pdFALSE;

        l_شاخص = ( int32_t ) px_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_کتار = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_کتار == pdTRUE )
            {
                x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_کتار_Handle != عدم )
                {
                    uxReturn = ux_کتار_Messages_انتظار( x_دننی_کتار_Handle );
                }
            }
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_کتار_Spaces_شته_Impl( ثابت کتار_Handle_t x_کتار ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_کتار_Spaces_شته_Impl( ثابت کتار_Handle_t x_کتار ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_شاخص;
        کتار_Handle_t x_دننی_کتار_Handle = عدم;
        UBaseType_t uxReturn = 0;
        بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار = pdFALSE;

        l_شاخص = ( int32_t ) x_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_کتار = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_کتار == pdTRUE )
            {
                x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_کتار_Handle != عدم )
                {
                    uxReturn = ux_کتار_Spaces_شته( x_دننی_کتار_Handle );
                }
            }
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Receive_Impl( کتار_Handle_t px_کتار,
                                      فراغ * ثابت pv_بفر,
                                      TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

    بنسټ_Type_t MPU_x_کتار_Receive_Impl( کتار_Handle_t px_کتار,
                                      فراغ * ثابت pv_بفر,
                                      TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_شاخص;
        کتار_Handle_t x_دننی_کتار_Handle = عدم;
        بنسټ_Type_t xReturn = pdFAIL;
        بنسټ_Type_t x_Is_Receive_بفر_Writable = pdFALSE;
        بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار = pdFALSE;
        UBaseType_t ux_کتار_توکی_اندازه;

        l_شاخص = ( int32_t ) px_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_کتار = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_کتار == pdTRUE )
            {
                x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_کتار_Handle != عدم )
                {
                    ux_کتار_توکی_اندازه = ux_کتار_Get_کتار_توکی_اندازه( x_دننی_کتار_Handle );

                    إذا( ( !( ( ( pv_بفر ) == عدم ) && ( ux_کتار_توکی_اندازه != ( UBaseType_t ) 0U ) ) )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                        #د_که_پای
                        )
                    {
                        x_Is_Receive_بفر_Writable = x_پورټ_Is_Authorized_منزل_Access_بفر( pv_بفر,
                                                                                    ux_کتار_توکی_اندازه,
                                                                                    tskMPU_WRITE_PERMISSION );

                        إذا( x_Is_Receive_بفر_Writable == pdTRUE )
                        {
                            xReturn = x_کتار_Receive( x_دننی_کتار_Handle, pv_بفر, x_Ticks_منزل_Wait );
                        }
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Peek_Impl( کتار_Handle_t x_کتار,
                                   فراغ * ثابت pv_بفر,
                                   TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

    بنسټ_Type_t MPU_x_کتار_Peek_Impl( کتار_Handle_t x_کتار,
                                   فراغ * ثابت pv_بفر,
                                   TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_شاخص;
        کتار_Handle_t x_دننی_کتار_Handle = عدم;
        بنسټ_Type_t xReturn = pdFAIL;
        بنسټ_Type_t x_Is_Receive_بفر_Writable = pdFALSE;
        UBaseType_t ux_کتار_توکی_اندازه;
        بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار = pdFALSE;

        l_شاخص = ( int32_t ) x_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_کتار = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_کتار == pdTRUE )
            {
                x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_کتار_Handle != عدم )
                {
                    ux_کتار_توکی_اندازه = ux_کتار_Get_کتار_توکی_اندازه( x_دننی_کتار_Handle );

                    إذا( ( !( ( ( pv_بفر ) == عدم ) && ( ux_کتار_توکی_اندازه != ( UBaseType_t ) 0U ) ) )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                        #د_که_پای
                        )
                    {
                        x_Is_Receive_بفر_Writable = x_پورټ_Is_Authorized_منزل_Access_بفر( pv_بفر,
                                                                                    ux_کتار_توکی_اندازه,
                                                                                    tskMPU_WRITE_PERMISSION );

                        إذا( x_Is_Receive_بفر_Writable == pdTRUE )
                        {
                            xReturn = x_کتار_Peek( x_دننی_کتار_Handle, pv_بفر, x_Ticks_منزل_Wait );
                        }
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Semaphore_Take_Impl( کتار_Handle_t x_کتار,
                                            TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

    بنسټ_Type_t MPU_x_کتار_Semaphore_Take_Impl( کتار_Handle_t x_کتار,
                                            TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_شاخص;
        کتار_Handle_t x_دننی_کتار_Handle = عدم;
        بنسټ_Type_t xReturn = pdFAIL;
        UBaseType_t ux_کتار_توکی_اندازه;
        بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار = pdFALSE;

        l_شاخص = ( int32_t ) x_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_کتار = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_کتار == pdTRUE )
            {
                x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_کتار_Handle != عدم )
                {
                    ux_کتار_توکی_اندازه = ux_کتار_Get_کتار_توکی_اندازه( x_دننی_کتار_Handle );

                    إذا( ( ux_کتار_توکی_اندازه == 0U )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                        #د_که_پای
                        )
                    {
                        xReturn = x_کتار_Semaphore_Take( x_دننی_کتار_Handle, x_Ticks_منزل_Wait );
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_کتار_Get_Mutex_Holder_Impl( کتار_Handle_t xSemaphore ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_x_کتار_Get_Mutex_Holder_Impl( کتار_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_دننی_Handle = عدم;
            TaskHandle_t xMutexHolderTaskExternalHandle = عدم;
            int32_t l_شاخص, l_Mutex_Holder_Task_شاخص;
            کتار_Handle_t x_دننی_کتار_Handle = عدم;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار = pdFALSE;


            l_شاخص = ( int32_t ) xSemaphore;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_کتار = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_کتار == pdTRUE )
                {
                    x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_کتار_Handle != عدم )
                    {
                        x_Mutex_Holder_Task_دننی_Handle = x_کتار_Get_Mutex_Holder( x_دننی_کتار_Handle );

                        إذا( x_Mutex_Holder_Task_دننی_Handle != عدم )
                        {
                            l_Mutex_Holder_Task_شاخص = MPU_Get_شاخص_For_Task_Handle( x_Mutex_Holder_Task_دننی_Handle );

                            إذا( l_Mutex_Holder_Task_شاخص != -1 )
                            {
                                xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_منزل_EXTERNAL_شاخص( l_Mutex_Holder_Task_شاخص ) );
                            }
                        }
                    }
                }
            }

            أرجع xMutexHolderTaskExternalHandle;
        }

    #د_که_پای /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        بنسټ_Type_t MPU_x_کتار_Take_Mutex_Recursive_Impl( کتار_Handle_t xMutex,
                                                     TickType_t x_بلاک_وخت ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_x_کتار_Take_Mutex_Recursive_Impl( کتار_Handle_t xMutex,
                                                     TickType_t x_بلاک_وخت ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار = pdFALSE;
            int32_t l_شاخص;
            کتار_Handle_t x_دننی_کتار_Handle = عدم;
            UBaseType_t ux_کتار_توکی_اندازه;

            l_شاخص = ( int32_t ) xMutex;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_کتار = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_کتار == pdTRUE )
                {
                    x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_کتار_Handle != عدم )
                    {
                        ux_کتار_توکی_اندازه = ux_کتار_Get_کتار_توکی_اندازه( x_دننی_کتار_Handle );

                        إذا( ux_کتار_توکی_اندازه == 0 )
                        {
                            xReturn = x_کتار_Take_Mutex_Recursive( x_دننی_کتار_Handle, x_بلاک_وخت );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        بنسټ_Type_t MPU_x_کتار_Give_Mutex_Recursive_Impl( کتار_Handle_t xMutex ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_x_کتار_Give_Mutex_Recursive_Impl( کتار_Handle_t xMutex ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار = pdFALSE;
            int32_t l_شاخص;
            کتار_Handle_t x_دننی_کتار_Handle = عدم;

            l_شاخص = ( int32_t ) xMutex;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_کتار = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_کتار == pdTRUE )
                {
                    x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_کتار_Handle != عدم )
                    {
                        xReturn = x_کتار_Give_Mutex_Recursive( x_دننی_کتار_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_کتار_SETS == 1 )

        کتار_سېټ_Member_Handle_t MPU_x_کتار_Select_From_سېټ_Impl( کتار_سېټ_Handle_t x_کتار_سېټ,
                                                            TickType_t x_بلاک_وخت_Ticks ) PRIVILEGED_FUNCTION;

        کتار_سېټ_Member_Handle_t MPU_x_کتار_Select_From_سېټ_Impl( کتار_سېټ_Handle_t x_کتار_سېټ,
                                                            TickType_t x_بلاک_وخت_Ticks ) /* PRIVILEGED_FUNCTION */
        {
            کتار_سېټ_Handle_t x_دننی_کتار_سېټ_Handle = عدم;
            کتار_سېټ_Member_Handle_t x_Selected_Member_دننی = عدم;
            کتار_سېټ_Member_Handle_t xSelectedMemberExternal = عدم;
            int32_t l_شاخص_کتار_سېټ, l_شاخص_Selected_Member;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار_سېټ = pdFALSE;

            l_شاخص_کتار_سېټ = ( int32_t ) x_کتار_سېټ;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص_کتار_سېټ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_کتار_سېټ = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص_کتار_سېټ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_کتار_سېټ == pdTRUE )
                {
                    x_دننی_کتار_سېټ_Handle = MPU_Get_کتار_سېټ_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص_کتار_سېټ ) );

                    إذا( x_دننی_کتار_سېټ_Handle != عدم )
                    {
                        x_Selected_Member_دننی = x_کتار_Select_From_سېټ( x_دننی_کتار_سېټ_Handle, x_بلاک_وخت_Ticks );

                        إذا( x_Selected_Member_دننی != عدم )
                        {
                            l_شاخص_Selected_Member = MPU_Get_شاخص_For_کتار_سېټ_Member_Handle( x_Selected_Member_دننی );

                            إذا( l_شاخص_Selected_Member != -1 )
                            {
                                xSelectedMemberExternal = ( کتار_سېټ_Member_Handle_t ) ( CONVERT_منزل_EXTERNAL_شاخص( l_شاخص_Selected_Member ) );
                            }
                        }
                    }
                }
            }

            أرجع xSelectedMemberExternal;
        }

    #د_که_پای /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_کتار_SETS == 1 )

        بنسټ_Type_t MPU_x_کتار_جمع_کړه_منزل_سېټ_Impl( کتار_سېټ_Member_Handle_t x_کتار_Or_Semaphore,
                                           کتار_سېټ_Handle_t x_کتار_سېټ ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_x_کتار_جمع_کړه_منزل_سېټ_Impl( کتار_سېټ_Member_Handle_t x_کتار_Or_Semaphore,
                                           کتار_سېټ_Handle_t x_کتار_سېټ ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            کتار_سېټ_Member_Handle_t x_دننی_کتار_سېټ_Member_Handle = عدم;
            کتار_سېټ_Handle_t x_دننی_کتار_سېټ_Handle = عدم;
            int32_t l_شاخص_کتار_سېټ, l_شاخص_کتار_سېټ_Member;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار_سېټ = pdFALSE;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار_سېټ_Member = pdFALSE;

            l_شاخص_کتار_سېټ = ( int32_t ) x_کتار_سېټ;
            l_شاخص_کتار_سېټ_Member = ( int32_t ) x_کتار_Or_Semaphore;

            إذا( ( IS_EXTERNAL_شاخص_VALID( l_شاخص_کتار_سېټ ) != pdFALSE ) &&
                ( IS_EXTERNAL_شاخص_VALID( l_شاخص_کتار_سېټ_Member ) != pdFALSE ) )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_کتار_سېټ = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص_کتار_سېټ ) );
                x_Calling_Task_Is_Authorized_منزل_Access_کتار_سېټ_Member = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص_کتار_سېټ_Member ) );

                إذا( ( x_Calling_Task_Is_Authorized_منزل_Access_کتار_سېټ == pdTRUE ) && ( x_Calling_Task_Is_Authorized_منزل_Access_کتار_سېټ_Member == pdTRUE ) )
                {
                    x_دننی_کتار_سېټ_Handle = MPU_Get_کتار_سېټ_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص_کتار_سېټ ) );
                    x_دننی_کتار_سېټ_Member_Handle = MPU_Get_کتار_سېټ_Member_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص_کتار_سېټ_Member ) );

                    إذا( ( x_دننی_کتار_سېټ_Handle != عدم ) && ( x_دننی_کتار_سېټ_Member_Handle != عدم ) )
                    {
                        xReturn = x_کتار_جمع_کړه_منزل_سېټ( x_دننی_کتار_سېټ_Member_Handle, x_دننی_کتار_سېټ_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا config_کتار_REGISTRY_اندازه > 0

        فراغ MPU_v_کتار_جمع_کړه_منزل_Registry_Impl( کتار_Handle_t x_کتار,
                                          ثابت حرف * pcName ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_کتار_جمع_کړه_منزل_Registry_Impl( کتار_Handle_t x_کتار,
                                          ثابت حرف * pcName ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            کتار_Handle_t x_دننی_کتار_Handle = عدم;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار = pdFALSE;

            l_شاخص = ( int32_t ) x_کتار;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_کتار = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_کتار == pdTRUE )
                {
                    x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_کتار_Handle != عدم )
                    {
                        v_کتار_جمع_کړه_منزل_Registry( x_دننی_کتار_Handle, pcName );
                    }
                }
            }
        }

    #د_که_پای /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_کتار_REGISTRY_اندازه > 0

        فراغ MPU_v_کتار_Unregister_کتار_Impl( کتار_Handle_t x_کتار ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_کتار_Unregister_کتار_Impl( کتار_Handle_t x_کتار ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            کتار_Handle_t x_دننی_کتار_Handle = عدم;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار = pdFALSE;

            l_شاخص = ( int32_t ) x_کتار;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_کتار = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_کتار == pdTRUE )
                {
                    x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_کتار_Handle != عدم )
                    {
                        v_کتار_Unregister_کتار( x_دننی_کتار_Handle );
                    }
                }
            }
        }

    #د_که_پای /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_کتار_REGISTRY_اندازه > 0

        ثابت حرف * MPU_pc_کتار_Get_Name_Impl( کتار_Handle_t x_کتار ) PRIVILEGED_FUNCTION;

        ثابت حرف * MPU_pc_کتار_Get_Name_Impl( کتار_Handle_t x_کتار ) /* PRIVILEGED_FUNCTION */
        {
            ثابت حرف * pcReturn = عدم;
            کتار_Handle_t x_دننی_کتار_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_کتار = pdFALSE;

            l_شاخص = ( int32_t ) x_کتار;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_کتار = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_کتار == pdTRUE )
                {
                    x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_کتار_Handle != عدم )
                    {
                        pcReturn = pc_کتار_Get_Name( x_دننی_کتار_Handle );
                    }
                }
            }

            أرجع pcReturn;
        }

    #د_که_پای /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Queue APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    فراغ MPU_v_کتار_Delete( کتار_Handle_t x_کتار ) /* PRIVILEGED_FUNCTION */
    {
        کتار_Handle_t x_دننی_کتار_Handle = عدم;
        int32_t l_شاخص;

        l_شاخص = ( int32_t ) x_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_دننی_کتار_Handle != عدم )
            {
                v_کتار_Delete( x_دننی_کتار_Handle );
                MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( CONVERT_منزل_دننی_شاخص( l_شاخص ) );
            }
        }
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_ویش == 1 ) )

        کتار_Handle_t MPU_x_کتار_Create_Mutex( ثابت uint8_t uc_کتار_Type ) /* PRIVILEGED_FUNCTION */
        {
            کتار_Handle_t x_دننی_کتار_Handle = عدم;
            کتار_Handle_t x_External_کتار_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_دننی_کتار_Handle = x_کتار_Create_Mutex( uc_کتار_Type );

                إذا( x_دننی_کتار_Handle != عدم )
                {
                    MPU_Store_کتار_Handle_At_شاخص( l_شاخص, x_دننی_کتار_Handle );
                    x_External_کتار_Handle = ( کتار_Handle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_کتار_Handle;
        }

    #د_که_پای /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_ویش == 1 ) )

        کتار_Handle_t MPU_x_کتار_Create_Mutex_Static( ثابت uint8_t uc_کتار_Type,
                                                   Static_کتار_t * px_Static_کتار ) /* PRIVILEGED_FUNCTION */
        {
            کتار_Handle_t x_دننی_کتار_Handle = عدم;
            کتار_Handle_t x_External_کتار_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_دننی_کتار_Handle = x_کتار_Create_Mutex_Static( uc_کتار_Type, px_Static_کتار );

                إذا( x_دننی_کتار_Handle != عدم )
                {
                    MPU_Store_کتار_Handle_At_شاخص( l_شاخص, x_دننی_کتار_Handle );
                    x_External_کتار_Handle = ( کتار_Handle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_کتار_Handle;
        }

    #د_که_پای /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_ویش == 1 ) )

        کتار_Handle_t MPU_x_کتار_Create_Counting_Semaphore( UBaseType_t ux_شمېر_ارزښت,
                                                         UBaseType_t ux_Initial_شمېر ) /* PRIVILEGED_FUNCTION */
        {
            کتار_Handle_t x_دننی_کتار_Handle = عدم;
            کتار_Handle_t x_External_کتار_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_دننی_کتار_Handle = x_کتار_Create_Counting_Semaphore( ux_شمېر_ارزښت, ux_Initial_شمېر );

                إذا( x_دننی_کتار_Handle != عدم )
                {
                    MPU_Store_کتار_Handle_At_شاخص( l_شاخص, x_دننی_کتار_Handle );
                    x_External_کتار_Handle = ( کتار_Handle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_کتار_Handle;
        }

    #د_که_پای /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_ویش == 1 ) )

        کتار_Handle_t MPU_x_کتار_Create_Counting_Semaphore_Static( ثابت UBaseType_t ux_Max_شمېر,
                                                               ثابت UBaseType_t ux_Initial_شمېر,
                                                               Static_کتار_t * px_Static_کتار ) /* PRIVILEGED_FUNCTION */
        {
            کتار_Handle_t x_دننی_کتار_Handle = عدم;
            کتار_Handle_t x_External_کتار_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_دننی_کتار_Handle = x_کتار_Create_Counting_Semaphore_Static( ux_Max_شمېر, ux_Initial_شمېر, px_Static_کتار );

                إذا( x_دننی_کتار_Handle != عدم )
                {
                    MPU_Store_کتار_Handle_At_شاخص( l_شاخص, x_دننی_کتار_Handle );
                    x_External_کتار_Handle = ( کتار_Handle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_کتار_Handle;
        }

    #د_که_پای /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ویش == 1 )

        کتار_Handle_t MPU_x_کتار_Generic_Create( UBaseType_t ux_کتار_اوږدتیا,
                                               UBaseType_t ux_توکی_اندازه,
                                               uint8_t uc_کتار_Type ) /* PRIVILEGED_FUNCTION */
        {
            کتار_Handle_t x_دننی_کتار_Handle = عدم;
            کتار_Handle_t x_External_کتار_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_دننی_کتار_Handle = x_کتار_Generic_Create( ux_کتار_اوږدتیا, ux_توکی_اندازه, uc_کتار_Type );

                إذا( x_دننی_کتار_Handle != عدم )
                {
                    MPU_Store_کتار_Handle_At_شاخص( l_شاخص, x_دننی_کتار_Handle );
                    x_External_کتار_Handle = ( کتار_Handle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_کتار_Handle;
        }

    #د_که_پای /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ویش == 1 )

        کتار_Handle_t MPU_x_کتار_Generic_Create_Static( ثابت UBaseType_t ux_کتار_اوږدتیا,
                                                     ثابت UBaseType_t ux_توکی_اندازه,
                                                     uint8_t * puc_کتار_Storage,
                                                     Static_کتار_t * px_Static_کتار,
                                                     ثابت uint8_t uc_کتار_Type ) /* PRIVILEGED_FUNCTION */
        {
            کتار_Handle_t x_دننی_کتار_Handle = عدم;
            کتار_Handle_t x_External_کتار_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_دننی_کتار_Handle = x_کتار_Generic_Create_Static( ux_کتار_اوږدتیا, ux_توکی_اندازه, puc_کتار_Storage, px_Static_کتار, uc_کتار_Type );

                إذا( x_دننی_کتار_Handle != عدم )
                {
                    MPU_Store_کتار_Handle_At_شاخص( l_شاخص, x_دننی_کتار_Handle );
                    x_External_کتار_Handle = ( کتار_Handle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_کتار_Handle;
        }

    #د_که_پای /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Generic_Reset( کتار_Handle_t x_کتار,
                                       بنسټ_Type_t x_New_کتار ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_شاخص;
        کتار_Handle_t x_دننی_کتار_Handle = عدم;
        بنسټ_Type_t xReturn = pdFAIL;

        l_شاخص = ( int32_t ) x_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_دننی_کتار_Handle != عدم )
            {
                xReturn = x_کتار_Generic_Reset( x_دننی_کتار_Handle, x_New_کتار );
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_کتار_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_ویش == 1 ) )

        کتار_سېټ_Handle_t MPU_x_کتار_Create_سېټ( UBaseType_t ux_Event_کتار_اوږدتیا ) /* PRIVILEGED_FUNCTION */
        {
            کتار_سېټ_Handle_t x_دننی_کتار_سېټ_Handle = عدم;
            کتار_سېټ_Handle_t x_External_کتار_سېټ_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_دننی_کتار_سېټ_Handle = x_کتار_Create_سېټ( ux_Event_کتار_اوږدتیا );

                إذا( x_دننی_کتار_سېټ_Handle != عدم )
                {
                    MPU_Store_کتار_سېټ_Handle_At_شاخص( l_شاخص, x_دننی_کتار_سېټ_Handle );
                    x_External_کتار_سېټ_Handle = ( کتار_سېټ_Handle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_کتار_سېټ_Handle;
        }

    #د_که_پای /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_کتار_SETS == 1 ) && ( config_SUPPORT_STATIC_ویش == 1 ) )

        کتار_سېټ_Handle_t MPU_x_کتار_Create_سېټ_Static( ثابت UBaseType_t ux_Event_کتار_اوږدتیا,
                                                    uint8_t * puc_کتار_Storage,
                                                    Static_کتار_t * px_Static_کتار ) /* PRIVILEGED_FUNCTION */
        {
            کتار_سېټ_Handle_t x_دننی_کتار_سېټ_Handle = عدم;
            کتار_سېټ_Handle_t x_External_کتار_سېټ_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_دننی_کتار_سېټ_Handle = x_کتار_Create_سېټ_Static( ux_Event_کتار_اوږدتیا, puc_کتار_Storage, px_Static_کتار );

                إذا( x_دننی_کتار_سېټ_Handle != عدم )
                {
                    MPU_Store_کتار_سېټ_Handle_At_شاخص( l_شاخص, x_دننی_کتار_سېټ_Handle );
                    x_External_کتار_سېټ_Handle = ( کتار_سېټ_Handle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_کتار_سېټ_Handle;
        }

    #د_که_پای /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_کتار_SETS == 1 )

        بنسټ_Type_t MPU_x_کتار_Remove_From_سېټ( کتار_سېټ_Member_Handle_t x_کتار_Or_Semaphore,
                                            کتار_سېټ_Handle_t x_کتار_سېټ ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            کتار_سېټ_Member_Handle_t x_دننی_کتار_سېټ_Member_Handle = عدم;
            کتار_سېټ_Handle_t x_دننی_کتار_سېټ_Handle = عدم;
            int32_t l_شاخص_کتار_سېټ, l_شاخص_کتار_سېټ_Member;

            l_شاخص_کتار_سېټ = ( int32_t ) x_کتار_سېټ;
            l_شاخص_کتار_سېټ_Member = ( int32_t ) x_کتار_Or_Semaphore;

            إذا( ( IS_EXTERNAL_شاخص_VALID( l_شاخص_کتار_سېټ ) != pdFALSE ) &&
                ( IS_EXTERNAL_شاخص_VALID( l_شاخص_کتار_سېټ_Member ) != pdFALSE ) )
            {
                x_دننی_کتار_سېټ_Handle = MPU_Get_کتار_سېټ_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص_کتار_سېټ ) );
                x_دننی_کتار_سېټ_Member_Handle = MPU_Get_کتار_سېټ_Member_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص_کتار_سېټ_Member ) );

                إذا( ( x_دننی_کتار_سېټ_Handle != عدم ) && ( x_دننی_کتار_سېټ_Member_Handle != عدم ) )
                {
                    xReturn = x_کتار_Remove_From_سېټ( x_دننی_کتار_سېټ_Member_Handle, x_دننی_کتار_سېټ_Handle );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ویش == 1 )

        بنسټ_Type_t MPU_x_کتار_Generic_Get_Static_Buffers( کتار_Handle_t x_کتار,
                                                      uint8_t ** ppuc_کتار_Storage,
                                                      Static_کتار_t ** ppx_Static_کتار ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            کتار_Handle_t x_دننی_کتار_Handle = عدم;
            بنسټ_Type_t xReturn = pdFALSE;

            l_شاخص = ( int32_t ) x_کتار;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_کتار_Handle != عدم )
                {
                    xReturn = x_کتار_Generic_Get_Static_Buffers( x_دننی_کتار_Handle, ppuc_کتار_Storage, ppx_Static_کتار );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /*if ( configSUPPORT_STATIC_ALLOCATION == 1 )*/
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Generic_Send_From_ISR( کتار_Handle_t x_کتار,
                                             ثابت فراغ * ثابت pv_توکی_منزل_کتار,
                                             بنسټ_Type_t * ثابت px_Higher_لومړیتوب_Task_Woken,
                                             ثابت بنسټ_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        بنسټ_Type_t xReturn = pdFAIL;
        int32_t l_شاخص;
        کتار_Handle_t x_دننی_کتار_Handle = عدم;

        l_شاخص = ( int32_t ) x_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_دننی_کتار_Handle != عدم )
            {
                xReturn = x_کتار_Generic_Send_From_ISR( x_دننی_کتار_Handle, pv_توکی_منزل_کتار, px_Higher_لومړیتوب_Task_Woken, xCopyPosition );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Give_From_ISR( کتار_Handle_t x_کتار,
                                      بنسټ_Type_t * ثابت px_Higher_لومړیتوب_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        بنسټ_Type_t xReturn = pdFAIL;
        int32_t l_شاخص;
        کتار_Handle_t x_دننی_کتار_Handle = عدم;

        l_شاخص = ( int32_t ) x_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_دننی_کتار_Handle != عدم )
            {
                xReturn = x_کتار_Give_From_ISR( x_دننی_کتار_Handle, px_Higher_لومړیتوب_Task_Woken );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Peek_From_ISR( کتار_Handle_t x_کتار,
                                      فراغ * ثابت pv_بفر ) /* PRIVILEGED_FUNCTION */
    {
        بنسټ_Type_t xReturn = pdFAIL;
        int32_t l_شاخص;
        کتار_Handle_t x_دننی_کتار_Handle = عدم;

        l_شاخص = ( int32_t ) x_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_دننی_کتار_Handle != عدم )
            {
                xReturn = x_کتار_Peek_From_ISR( x_دننی_کتار_Handle, pv_بفر );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Receive_From_ISR( کتار_Handle_t x_کتار,
                                         فراغ * ثابت pv_بفر,
                                         بنسټ_Type_t * ثابت px_Higher_لومړیتوب_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        بنسټ_Type_t xReturn = pdFAIL;
        int32_t l_شاخص;
        کتار_Handle_t x_دننی_کتار_Handle = عدم;

        l_شاخص = ( int32_t ) x_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_دننی_کتار_Handle != عدم )
            {
                xReturn = x_کتار_Receive_From_ISR( x_دننی_کتار_Handle, pv_بفر, px_Higher_لومړیتوب_Task_Woken );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Is_کتار_تشه_From_ISR( ثابت کتار_Handle_t x_کتار ) /* PRIVILEGED_FUNCTION */
    {
        بنسټ_Type_t xReturn = pdFAIL;
        int32_t l_شاخص;
        کتار_Handle_t x_دننی_کتار_Handle = عدم;

        l_شاخص = ( int32_t ) x_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_دننی_کتار_Handle != عدم )
            {
                xReturn = x_کتار_Is_کتار_تشه_From_ISR( x_دننی_کتار_Handle );
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    بنسټ_Type_t MPU_x_کتار_Is_کتار_ډک_From_ISR( ثابت کتار_Handle_t x_کتار ) /* PRIVILEGED_FUNCTION */
    {
        بنسټ_Type_t xReturn = pdFAIL;
        int32_t l_شاخص;
        کتار_Handle_t x_دننی_کتار_Handle = عدم;

        l_شاخص = ( int32_t ) x_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_دننی_کتار_Handle != عدم )
            {
                xReturn = x_کتار_Is_کتار_ډک_From_ISR( x_دننی_کتار_Handle );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_کتار_Messages_انتظار_From_ISR( ثابت کتار_Handle_t x_کتار ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn = 0;
        int32_t l_شاخص;
        کتار_Handle_t x_دننی_کتار_Handle = عدم;

        l_شاخص = ( int32_t ) x_کتار;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_دننی_کتار_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_دننی_کتار_Handle != عدم )
            {
                uxReturn = ux_کتار_Messages_انتظار_From_ISR( x_دننی_کتار_Handle );
            }
        }

        أرجع uxReturn;
    }

/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_کتار_Get_Mutex_Holder_From_ISR( کتار_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_دننی_Handle = عدم;
            TaskHandle_t xMutexHolderTaskExternalHandle = عدم;
            int32_t l_شاخص, l_Mutex_Holder_Task_شاخص;
            کتار_Handle_t x_دننی_Semaphore_Handle = عدم;

            l_شاخص = ( int32_t ) xSemaphore;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_Semaphore_Handle = MPU_Get_کتار_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_Semaphore_Handle != عدم )
                {
                    x_Mutex_Holder_Task_دننی_Handle = x_کتار_Get_Mutex_Holder( x_دننی_Semaphore_Handle );

                    إذا( x_Mutex_Holder_Task_دننی_Handle != عدم )
                    {
                        l_Mutex_Holder_Task_شاخص = MPU_Get_شاخص_For_Task_Handle( x_Mutex_Holder_Task_دننی_Handle );

                        إذا( l_Mutex_Holder_Task_شاخص != -1 )
                        {
                            xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_منزل_EXTERNAL_شاخص( l_Mutex_Holder_Task_شاخص ) );
                        }
                    }
                }
            }

            أرجع xMutexHolderTaskExternalHandle;
        }

    #د_که_پای /* #if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_کتار_SETS == 1 )

        کتار_سېټ_Member_Handle_t MPU_x_کتار_Select_From_سېټ_From_ISR( کتار_سېټ_Handle_t x_کتار_سېټ ) /* PRIVILEGED_FUNCTION */
        {
            کتار_سېټ_Handle_t x_دننی_کتار_سېټ_Handle = عدم;
            کتار_سېټ_Member_Handle_t x_Selected_Member_دننی = عدم;
            کتار_سېټ_Member_Handle_t xSelectedMemberExternal = عدم;
            int32_t l_شاخص_کتار_سېټ, l_شاخص_Selected_Member;

            l_شاخص_کتار_سېټ = ( int32_t ) x_کتار_سېټ;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص_کتار_سېټ ) != pdFALSE )
            {
                x_دننی_کتار_سېټ_Handle = MPU_Get_کتار_سېټ_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص_کتار_سېټ ) );

                إذا( x_دننی_کتار_سېټ_Handle != عدم )
                {
                    x_Selected_Member_دننی = x_کتار_Select_From_سېټ_From_ISR( x_دننی_کتار_سېټ_Handle );

                    إذا( x_Selected_Member_دننی != عدم )
                    {
                        l_شاخص_Selected_Member = MPU_Get_شاخص_For_کتار_سېټ_Member_Handle( x_Selected_Member_دننی );

                        إذا( l_شاخص_Selected_Member != -1 )
                        {
                            xSelectedMemberExternal = ( کتار_سېټ_Member_Handle_t ) ( CONVERT_منزل_EXTERNAL_شاخص( l_شاخص_Selected_Member ) );
                        }
                    }
                }
            }

            أرجع xSelectedMemberExternal;
        }

    #د_که_پای /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for timers APIs.                  */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ * MPU_pvTimerGetTimerIDImpl( ثابت TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        فراغ * MPU_pvTimerGetTimerIDImpl( ثابت TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            فراغ * pvReturn = عدم;
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_دننی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Timer_Handle != عدم )
                    {
                        pvReturn = pvTimerGetTimerID( x_دننی_Timer_Handle );
                    }
                }
            }

            أرجع pvReturn;
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_سېټ_Timer_IDImpl( TimerHandle_t xTimer,
                                       فراغ * pvNewID ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Timer_سېټ_Timer_IDImpl( TimerHandle_t xTimer,
                                       فراغ * pvNewID ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_دننی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Timer_Handle != عدم )
                    {
                        v_Timer_سېټ_Timer_ID( x_دننی_Timer_Handle, pvNewID );
                    }
                }
            }
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنسټ_Type_t MPU_x_Timer_Is_Timer_فعال_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_x_Timer_Is_Timer_فعال_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_دننی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Timer_Handle != عدم )
                    {
                        xReturn = x_Timer_Is_Timer_فعال( x_دننی_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( فراغ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xReturn;

            xReturn = xTimerGetTimerDaemonTaskHandle();

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنسټ_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ثابت بنسټ_Type_t xCommandID,
                                                     ثابت TickType_t x_Optional_ارزښت,
                                                     بنسټ_Type_t * ثابت px_Higher_لومړیتوب_Task_Woken,
                                                     ثابت TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            xTimerGenericCommandFromTaskParams_t xParams;

            xParams.xTimer = xTimer;
            xParams.xCommandID = xCommandID;
            xParams.x_Optional_ارزښت = x_Optional_ارزښت;
            xParams.px_Higher_لومړیتوب_Task_Woken = px_Higher_لومړیتوب_Task_Woken;
            xParams.x_Ticks_منزل_Wait = x_Ticks_منزل_Wait;

            xReturn = MPU_x_Timer_Generic_Command_From_Task_ثبت( &( xParams ) );

            أرجع xReturn;
        }

        بنسټ_Type_t MPU_xTimerGenericCommandFromTaskImpl( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_xTimerGenericCommandFromTaskImpl( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Is_Higher_لومړیتوب_Task_Woken_Writeable = pdFALSE;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;
            بنسټ_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورټ_Is_Authorized_منزل_Access_بفر( pxParams,
                                                                      حجم( xTimerGenericCommandFromTaskParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( pxParams->xCommandID < tmr_لومړی_FROM_ISR_COMMAND )
                {
                    إذا( pxParams->px_Higher_لومړیتوب_Task_Woken != عدم )
                    {
                        x_Is_Higher_لومړیتوب_Task_Woken_Writeable = x_پورټ_Is_Authorized_منزل_Access_بفر( pxParams->px_Higher_لومړیتوب_Task_Woken,
                                                                                               حجم( بنسټ_Type_t ),
                                                                                               tskMPU_WRITE_PERMISSION );
                    }

                    إذا( ( pxParams->px_Higher_لومړیتوب_Task_Woken == عدم ) ||
                        ( x_Is_Higher_لومړیتوب_Task_Woken_Writeable == pdTRUE ) )
                    {
                        l_شاخص = ( int32_t ) ( pxParams->xTimer );

                        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                            إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                            {
                                x_دننی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                                إذا( x_دننی_Timer_Handle != عدم )
                                {
                                    xReturn = xTimerGenericCommandFromTask( x_دننی_Timer_Handle,
                                                                            pxParams->xCommandID,
                                                                            pxParams->x_Optional_ارزښت,
                                                                            pxParams->px_Higher_لومړیتوب_Task_Woken,
                                                                            pxParams->x_Ticks_منزل_Wait );
                                }
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ثابت حرف * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ثابت حرف * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ثابت حرف * pcReturn = عدم;
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_دننی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Timer_Handle != عدم )
                    {
                        pcReturn = pcTimerGetName( x_دننی_Timer_Handle );
                    }
                }
            }

            أرجع pcReturn;
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_سېټ_Reload_ډېرپېښ_Impl( TimerHandle_t xTimer,
                                          ثابت بنسټ_Type_t xAutoReload ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Timer_سېټ_Reload_ډېرپېښ_Impl( TimerHandle_t xTimer,
                                          ثابت بنسټ_Type_t xAutoReload ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_دننی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Timer_Handle != عدم )
                    {
                        v_Timer_سېټ_Reload_ډېرپېښ( x_دننی_Timer_Handle, xAutoReload );
                    }
                }
            }
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنسټ_Type_t MPU_x_Timer_Get_Reload_ډېرپېښ_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_x_Timer_Get_Reload_ډېرپېښ_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_دننی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Timer_Handle != عدم )
                    {
                        xReturn = x_Timer_Get_Reload_ډېرپېښ( x_دننی_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_ډېرپېښ_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Timer_Get_Reload_ډېرپېښ_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_دننی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Timer_Handle != عدم )
                    {
                        uxReturn = ux_Timer_Get_Reload_ډېرپېښ( x_دننی_Timer_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_دننی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Timer_Handle != عدم )
                    {
                        xReturn = xTimerGetPeriod( x_دننی_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_وخت_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_x_Timer_Get_Expiry_وخت_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_دننی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Timer_Handle != عدم )
                    {
                        xReturn = x_Timer_Get_Expiry_وخت( x_دننی_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Timer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ویش == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreate( ثابت حرف * ثابت pcTimerName,
                                        ثابت TickType_t x_Timer_Period_دننه_Ticks,
                                        ثابت بنسټ_Type_t xAutoReload,
                                        فراغ * ثابت pvTimerID,
                                        TimerCallbackFunction_t pxCallbackFunction ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            TimerHandle_t xExternalTimerHandle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_دننی_Timer_Handle = xTimerCreate( pcTimerName, x_Timer_Period_دننه_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback );

                إذا( x_دننی_Timer_Handle != عدم )
                {
                    MPU_Store_Timer_Handle_At_شاخص( l_شاخص, x_دننی_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع xExternalTimerHandle;
        }

    #د_که_پای /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ویش == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreateStatic( ثابت حرف * ثابت pcTimerName,
                                              ثابت TickType_t x_Timer_Period_دننه_Ticks,
                                              ثابت بنسټ_Type_t xAutoReload,
                                              فراغ * ثابت pvTimerID,
                                              TimerCallbackFunction_t pxCallbackFunction,
                                              StaticTimer_t * px_Timer_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            TimerHandle_t xExternalTimerHandle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_دننی_Timer_Handle = xTimerCreateStatic( pcTimerName, x_Timer_Period_دننه_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback, px_Timer_بفر );

                إذا( x_دننی_Timer_Handle != عدم )
                {
                    MPU_Store_Timer_Handle_At_شاخص( l_شاخص, x_دننی_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع xExternalTimerHandle;
        }

    #د_که_پای /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ویش == 1 ) && ( configUSE_TIMERS == 1 )

        بنسټ_Type_t MPU_x_Timer_Get_Static_بفر( TimerHandle_t xTimer,
                                              StaticTimer_t ** ppx_Timer_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t xReturn = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_Timer_Handle != عدم )
                {
                    xReturn = x_Timer_Get_Static_بفر( x_دننی_Timer_Handle, ppx_Timer_بفر );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنسټ_Type_t MPU_xTimerGenericCommandFromISR( TimerHandle_t xTimer,
                                                    ثابت بنسټ_Type_t xCommandID,
                                                    ثابت TickType_t x_Optional_ارزښت,
                                                    بنسټ_Type_t * ثابت px_Higher_لومړیتوب_Task_Woken,
                                                    ثابت TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_Timer_Handle != عدم )
                {
                    xReturn = xTimerGenericCommandFromISR( x_دننی_Timer_Handle, xCommandID, x_Optional_ارزښت, px_Higher_لومړیتوب_Task_Woken, x_Ticks_منزل_Wait );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنسټ_Type_t MPU_xTimerDelete( TimerHandle_t xTimer, TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_دننی_Timer_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_Timer_Handle != عدم )
                {
                    xReturn = xTimerGenericCommandFromTask( x_دننی_Timer_Handle,
                                                            tmrCOMMAND_DELETE,
                                                            0U, /* xOptionalValue */
                                                            عدم, /* pxHigherPriorityTaskWoken */
                                                            x_Ticks_منزل_Wait );
                    إذا( xReturn != pdFALSE )
                    {
                        MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( CONVERT_منزل_دننی_شاخص( l_شاخص ) );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for event group APIs.              */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بټونه_t MPU_x_Event_ډله_Wait_بټونه( Event_ډله_Handle_t x_Event_ډله,
                                             ثابت Event_بټونه_t ux_بټونه_منزل_Wait_For,
                                             ثابت بنسټ_Type_t xClearOnExit,
                                             ثابت بنسټ_Type_t x_Wait_For_All_بټونه,
                                             TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بټونه_t xReturn = 0;
            x_Event_ډله_Wait_بټونه_Params_t xParams;

            xParams.x_Event_ډله = x_Event_ډله;
            xParams.ux_بټونه_منزل_Wait_For = ux_بټونه_منزل_Wait_For;
            xParams.xClearOnExit = xClearOnExit;
            xParams.x_Wait_For_All_بټونه = x_Wait_For_All_بټونه;
            xParams.x_Ticks_منزل_Wait = x_Ticks_منزل_Wait;

            xReturn = MPU_x_Event_ډله_Wait_بټونه_ثبت( &( xParams ) );

            أرجع xReturn;
        }

        Event_بټونه_t MPU_x_Event_ډله_Wait_بټونه_Impl( ثابت x_Event_ډله_Wait_بټونه_Params_t * pxParams ) PRIVILEGED_FUNCTION;

        Event_بټونه_t MPU_x_Event_ډله_Wait_بټونه_Impl( ثابت x_Event_ډله_Wait_بټونه_Params_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            Event_بټونه_t xReturn = 0;
            Event_ډله_Handle_t x_دننی_Event_ډله_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله = pdFALSE;
            بنسټ_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورټ_Is_Authorized_منزل_Access_بفر( pxParams,
                                                                      حجم( x_Event_ډله_Wait_بټونه_Params_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( ( ( pxParams->ux_بټونه_منزل_Wait_For & event_EVENT_بټونه_CONTROL_بایټونه ) == 0U ) &&
                    ( pxParams->ux_بټونه_منزل_Wait_For != 0U )
                    #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                        && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( pxParams->x_Ticks_منزل_Wait != 0U ) ) )
                    #د_که_پای
                    )
                {
                    l_شاخص = ( int32_t ) ( pxParams->x_Event_ډله );

                    إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله == pdTRUE )
                        {
                            x_دننی_Event_ډله_Handle = MPU_Get_Event_ډله_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                            إذا( x_دننی_Event_ډله_Handle != عدم )
                            {
                                xReturn = x_Event_ډله_Wait_بټونه( x_دننی_Event_ډله_Handle,
                                                               pxParams->ux_بټونه_منزل_Wait_For,
                                                               pxParams->xClearOnExit,
                                                               pxParams->x_Wait_For_All_بټونه,
                                                               pxParams->x_Ticks_منزل_Wait );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بټونه_t MPU_x_Event_ډله_Clear_بټونه_Impl( Event_ډله_Handle_t x_Event_ډله,
                                                  ثابت Event_بټونه_t ux_بټونه_منزل_Clear ) PRIVILEGED_FUNCTION;

        Event_بټونه_t MPU_x_Event_ډله_Clear_بټونه_Impl( Event_ډله_Handle_t x_Event_ډله,
                                                  ثابت Event_بټونه_t ux_بټونه_منزل_Clear ) /* PRIVILEGED_FUNCTION */
        {
            Event_بټونه_t xReturn = 0;
            Event_ډله_Handle_t x_دننی_Event_ډله_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله = pdFALSE;

            إذا( ( ux_بټونه_منزل_Clear & event_EVENT_بټونه_CONTROL_بایټونه ) == 0U )
            {
                l_شاخص = ( int32_t ) x_Event_ډله;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله == pdTRUE )
                    {
                        x_دننی_Event_ډله_Handle = MPU_Get_Event_ډله_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_دننی_Event_ډله_Handle != عدم )
                        {
                            xReturn = x_Event_ډله_Clear_بټونه( x_دننی_Event_ډله_Handle, ux_بټونه_منزل_Clear );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بټونه_t MPU_x_Event_ډله_سېټ_بټونه_Impl( Event_ډله_Handle_t x_Event_ډله,
                                                ثابت Event_بټونه_t ux_بټونه_منزل_سېټ ) PRIVILEGED_FUNCTION;

        Event_بټونه_t MPU_x_Event_ډله_سېټ_بټونه_Impl( Event_ډله_Handle_t x_Event_ډله,
                                                ثابت Event_بټونه_t ux_بټونه_منزل_سېټ ) /* PRIVILEGED_FUNCTION */
        {
            Event_بټونه_t xReturn = 0;
            Event_ډله_Handle_t x_دننی_Event_ډله_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله = pdFALSE;

            إذا( ( ux_بټونه_منزل_سېټ & event_EVENT_بټونه_CONTROL_بایټونه ) == 0U )
            {
                l_شاخص = ( int32_t ) x_Event_ډله;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله == pdTRUE )
                    {
                        x_دننی_Event_ډله_Handle = MPU_Get_Event_ډله_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_دننی_Event_ډله_Handle != عدم )
                        {
                            xReturn = x_Event_ډله_سېټ_بټونه( x_دننی_Event_ډله_Handle, ux_بټونه_منزل_سېټ );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بټونه_t MPU_x_Event_ډله_Sync_Impl( Event_ډله_Handle_t x_Event_ډله,
                                             ثابت Event_بټونه_t ux_بټونه_منزل_سېټ,
                                             ثابت Event_بټونه_t ux_بټونه_منزل_Wait_For,
                                             TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

        Event_بټونه_t MPU_x_Event_ډله_Sync_Impl( Event_ډله_Handle_t x_Event_ډله,
                                             ثابت Event_بټونه_t ux_بټونه_منزل_سېټ,
                                             ثابت Event_بټونه_t ux_بټونه_منزل_Wait_For,
                                             TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            Event_بټونه_t xReturn = 0;
            Event_ډله_Handle_t x_دننی_Event_ډله_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله = pdFALSE;

            إذا( ( ( ux_بټونه_منزل_Wait_For & event_EVENT_بټونه_CONTROL_بایټونه ) == 0U ) &&
                ( ux_بټونه_منزل_Wait_For != 0U )
                #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                    && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                #د_که_پای
                )
            {
                l_شاخص = ( int32_t ) x_Event_ډله;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله == pdTRUE )
                    {
                        x_دننی_Event_ډله_Handle = MPU_Get_Event_ډله_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_دننی_Event_ډله_Handle != عدم )
                        {
                            xReturn = x_Event_ډله_Sync( x_دننی_Event_ډله_Handle, ux_بټونه_منزل_سېټ, ux_بټونه_منزل_Wait_For, x_Ticks_منزل_Wait );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_ډله_Get_شمېره_Impl( فراغ * x_Event_ډله ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Event_ډله_Get_شمېره_Impl( فراغ * x_Event_ډله ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t xReturn = 0;
            Event_ډله_Handle_t x_دننی_Event_ډله_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله = pdFALSE;

            l_شاخص = ( int32_t ) x_Event_ډله;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله == pdTRUE )
                {
                    x_دننی_Event_ډله_Handle = MPU_Get_Event_ډله_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Event_ډله_Handle != عدم )
                    {
                        xReturn = ux_Event_ډله_Get_شمېره( x_دننی_Event_ډله_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        فراغ MPU_v_Event_ډله_سېټ_شمېره_Impl( فراغ * x_Event_ډله,
                                           UBaseType_t ux_Event_ډله_شمېره ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Event_ډله_سېټ_شمېره_Impl( فراغ * x_Event_ډله,
                                           UBaseType_t ux_Event_ډله_شمېره ) /* PRIVILEGED_FUNCTION */
        {
            Event_ډله_Handle_t x_دننی_Event_ډله_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله = pdFALSE;

            l_شاخص = ( int32_t ) x_Event_ډله;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_ډله == pdTRUE )
                {
                    x_دننی_Event_ډله_Handle = MPU_Get_Event_ډله_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_Event_ډله_Handle != عدم )
                    {
                        v_Event_ډله_سېټ_شمېره( x_دننی_Event_ډله_Handle, ux_Event_ډله_شمېره );
                    }
                }
            }
        }

    #د_که_پای /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Event Group APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_ویش == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_ډله_Handle_t MPU_x_Event_ډله_Create( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            Event_ډله_Handle_t x_دننی_Event_ډله_Handle = عدم;
            Event_ډله_Handle_t x_External_Event_ډله_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_دننی_Event_ډله_Handle = x_Event_ډله_Create();

                إذا( x_دننی_Event_ډله_Handle != عدم )
                {
                    MPU_Store_Event_ډله_Handle_At_شاخص( l_شاخص, x_دننی_Event_ډله_Handle );
                    x_External_Event_ډله_Handle = ( Event_ډله_Handle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_Event_ډله_Handle;
        }

    #د_که_پای /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ویش == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_ډله_Handle_t MPU_x_Event_ډله_Create_Static( Static_Event_ډله_t * px_Event_ډله_بفر ) /* PRIVILEGED_FUNCTION */
        {
            Event_ډله_Handle_t x_دننی_Event_ډله_Handle = عدم;
            Event_ډله_Handle_t x_External_Event_ډله_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_دننی_Event_ډله_Handle = x_Event_ډله_Create_Static( px_Event_ډله_بفر );

                إذا( x_دننی_Event_ډله_Handle != عدم )
                {
                    MPU_Store_Event_ډله_Handle_At_شاخص( l_شاخص, x_دننی_Event_ډله_Handle );
                    x_External_Event_ډله_Handle = ( Event_ډله_Handle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_Event_ډله_Handle;
        }

    #د_که_پای /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        فراغ MPU_v_Event_ډله_Delete( Event_ډله_Handle_t x_Event_ډله ) /* PRIVILEGED_FUNCTION */
        {
            Event_ډله_Handle_t x_دننی_Event_ډله_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_Event_ډله;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_Event_ډله_Handle = MPU_Get_Event_ډله_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_Event_ډله_Handle != عدم )
                {
                    v_Event_ډله_Delete( x_دننی_Event_ډله_Handle );
                    MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( CONVERT_منزل_دننی_شاخص( l_شاخص ) );
                }
            }
        }

    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ویش == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        بنسټ_Type_t MPU_x_Event_ډله_Get_Static_بفر( Event_ډله_Handle_t x_Event_ډله,
                                                   Static_Event_ډله_t ** ppx_Event_ډله_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            Event_ډله_Handle_t x_دننی_Event_ډله_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_Event_ډله;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_Event_ډله_Handle = MPU_Get_Event_ډله_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_Event_ډله_Handle != عدم )
                {
                    xReturn = x_Event_ډله_Get_Static_بفر( x_دننی_Event_ډله_Handle, ppx_Event_ډله_بفر );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        بنسټ_Type_t MPU_x_Event_ډله_Clear_بټونه_From_ISR( Event_ډله_Handle_t x_Event_ډله,
                                                    ثابت Event_بټونه_t ux_بټونه_منزل_Clear ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            Event_ډله_Handle_t x_دننی_Event_ډله_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_Event_ډله;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_Event_ډله_Handle = MPU_Get_Event_ډله_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_Event_ډله_Handle != عدم )
                {
                    xReturn = x_Event_ډله_Clear_بټونه_From_ISR( x_دننی_Event_ډله_Handle, ux_بټونه_منزل_Clear );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        بنسټ_Type_t MPU_x_Event_ډله_سېټ_بټونه_From_ISR( Event_ډله_Handle_t x_Event_ډله,
                                                  ثابت Event_بټونه_t ux_بټونه_منزل_سېټ,
                                                  بنسټ_Type_t * px_Higher_لومړیتوب_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            Event_ډله_Handle_t x_دننی_Event_ډله_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_Event_ډله;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_Event_ډله_Handle = MPU_Get_Event_ډله_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_Event_ډله_Handle != عدم )
                {
                    xReturn = x_Event_ډله_سېټ_بټونه_From_ISR( x_دننی_Event_ډله_Handle, ux_بټونه_منزل_سېټ, px_Higher_لومړیتوب_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بټونه_t MPU_x_Event_ډله_Get_بټونه_From_ISR( Event_ډله_Handle_t x_Event_ډله ) /* PRIVILEGED_FUNCTION */
        {
            Event_بټونه_t xReturn = 0;
            Event_ډله_Handle_t x_دننی_Event_ډله_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_Event_ډله;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_Event_ډله_Handle = MPU_Get_Event_ډله_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_Event_ډله_Handle != عدم )
                {
                    xReturn = x_Event_ډله_Get_بټونه_From_ISR( x_دننی_Event_ډله_Handle );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for stream buffer APIs.            */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        size_t MPU_x_بهیر_بفر_Send_Impl( بهیر_بفر_Handle_t x_بهیر_بفر,
                                          ثابت فراغ * pv_Tx_معلومات,
                                          size_t x_معلومات_اوږدتیا_بایټونه,
                                          TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_بهیر_بفر_Send_Impl( بهیر_بفر_Handle_t x_بهیر_بفر,
                                          ثابت فراغ * pv_Tx_معلومات,
                                          size_t x_معلومات_اوږدتیا_بایټونه,
                                          TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Is_Tx_معلومات_بفر_Readable = pdFALSE;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = pdFALSE;

            إذا( pv_Tx_معلومات != عدم )
            {
                x_Is_Tx_معلومات_بفر_Readable = x_پورټ_Is_Authorized_منزل_Access_بفر( pv_Tx_معلومات,
                                                                           x_معلومات_اوږدتیا_بایټونه,
                                                                           tskMPU_READ_PERMISSION );

                إذا( x_Is_Tx_معلومات_بفر_Readable == pdTRUE )
                {
                    l_شاخص = ( int32_t ) x_بهیر_بفر;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر == pdTRUE )
                        {
                            x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                            إذا( x_دننی_بهیر_بفر_Handle != عدم )
                            {
                                xReturn = x_بهیر_بفر_Send( x_دننی_بهیر_بفر_Handle, pv_Tx_معلومات, x_معلومات_اوږدتیا_بایټونه, x_Ticks_منزل_Wait );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        size_t MPU_x_بهیر_بفر_Receive_Impl( بهیر_بفر_Handle_t x_بهیر_بفر,
                                             فراغ * pv_Rx_معلومات,
                                             size_t x_بفر_اوږدتیا_بایټونه,
                                             TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_بهیر_بفر_Receive_Impl( بهیر_بفر_Handle_t x_بهیر_بفر,
                                             فراغ * pv_Rx_معلومات,
                                             size_t x_بفر_اوږدتیا_بایټونه,
                                             TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Is_Rx_معلومات_بفر_Writeable = pdFALSE;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = pdFALSE;

            إذا( pv_Rx_معلومات != عدم )
            {
                x_Is_Rx_معلومات_بفر_Writeable = x_پورټ_Is_Authorized_منزل_Access_بفر( pv_Rx_معلومات,
                                                                            x_بفر_اوږدتیا_بایټونه,
                                                                            tskMPU_WRITE_PERMISSION );

                إذا( x_Is_Rx_معلومات_بفر_Writeable == pdTRUE )
                {
                    l_شاخص = ( int32_t ) x_بهیر_بفر;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر == pdTRUE )
                        {
                            x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                            إذا( x_دننی_بهیر_بفر_Handle != عدم )
                            {
                                xReturn = x_بهیر_بفر_Receive( x_دننی_بهیر_بفر_Handle, pv_Rx_معلومات, x_بفر_اوږدتیا_بایټونه, x_Ticks_منزل_Wait );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        بنسټ_Type_t MPU_x_بهیر_بفر_Is_ډک_Impl( بهیر_بفر_Handle_t x_بهیر_بفر ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_x_بهیر_بفر_Is_ډک_Impl( بهیر_بفر_Handle_t x_بهیر_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = pdFALSE;

            l_شاخص = ( int32_t ) x_بهیر_بفر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر == pdTRUE )
                {
                    x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_بهیر_بفر_Handle != عدم )
                    {
                        xReturn = x_بهیر_بفر_Is_ډک( x_دننی_بهیر_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        بنسټ_Type_t MPU_x_بهیر_بفر_Is_تشه_Impl( بهیر_بفر_Handle_t x_بهیر_بفر ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_x_بهیر_بفر_Is_تشه_Impl( بهیر_بفر_Handle_t x_بهیر_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = pdFALSE;

            l_شاخص = ( int32_t ) x_بهیر_بفر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر == pdTRUE )
                {
                    x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_بهیر_بفر_Handle != عدم )
                    {
                        xReturn = x_بهیر_بفر_Is_تشه( x_دننی_بهیر_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        size_t MPU_x_بهیر_بفر_Spaces_شته_Impl( بهیر_بفر_Handle_t x_بهیر_بفر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_بهیر_بفر_Spaces_شته_Impl( بهیر_بفر_Handle_t x_بهیر_بفر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = pdFALSE;

            l_شاخص = ( int32_t ) x_بهیر_بفر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر == pdTRUE )
                {
                    x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_بهیر_بفر_Handle != عدم )
                    {
                        xReturn = x_بهیر_بفر_Spaces_شته( x_دننی_بهیر_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        size_t MPU_x_بهیر_بفر_بایټونه_شته_Impl( بهیر_بفر_Handle_t x_بهیر_بفر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_بهیر_بفر_بایټونه_شته_Impl( بهیر_بفر_Handle_t x_بهیر_بفر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = pdFALSE;

            l_شاخص = ( int32_t ) x_بهیر_بفر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر == pdTRUE )
                {
                    x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_بهیر_بفر_Handle != عدم )
                    {
                        xReturn = x_بهیر_بفر_بایټونه_شته( x_دننی_بهیر_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        بنسټ_Type_t MPU_x_بهیر_بفر_سېټ_Trigger_Level_Impl( بهیر_بفر_Handle_t x_بهیر_بفر,
                                                         size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

        بنسټ_Type_t MPU_x_بهیر_بفر_سېټ_Trigger_Level_Impl( بهیر_بفر_Handle_t x_بهیر_بفر,
                                                         size_t xTriggerLevel ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = pdFALSE;

            l_شاخص = ( int32_t ) x_بهیر_بفر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر == pdTRUE )
                {
                    x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_بهیر_بفر_Handle != عدم )
                    {
                        xReturn = x_بهیر_بفر_سېټ_Trigger_Level( x_دننی_بهیر_بفر_Handle, xTriggerLevel );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        size_t MPU_x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه_Impl( بهیر_بفر_Handle_t x_بهیر_بفر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه_Impl( بهیر_بفر_Handle_t x_بهیر_بفر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;
            بنسټ_Type_t x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = pdFALSE;

            l_شاخص = ( int32_t ) x_بهیر_بفر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر = x_پورټ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_بهیر_بفر == pdTRUE )
                {
                    x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                    إذا( x_دننی_بهیر_بفر_Handle != عدم )
                    {
                        xReturn = x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه( x_دننی_بهیر_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Stream Buffer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_ویش == 1 ) && ( config_USE_بهیر_BUFFERS == 1 ) )

        بهیر_بفر_Handle_t MPU_x_بهیر_بفر_Generic_Create( size_t x_بفر_اندازه_بایټونه,
                                                             size_t x_Trigger_Level_بایټونه,
                                                             بنسټ_Type_t x_بهیر_بفر_Type,
                                                             بهیر_بفر_Callback_Function_t pxSendCompletedCallback,
                                                             بهیر_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            بهیر_بفر_Handle_t x_External_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == عدم ) &&
                          ( pxReceiveCompletedCallback == عدم ) );

            إذا( ( pxSendCompletedCallback == عدم ) &&
                ( pxReceiveCompletedCallback == عدم ) )
            {
                l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

                إذا( l_شاخص != -1 )
                {
                    x_دننی_بهیر_بفر_Handle = x_بهیر_بفر_Generic_Create( x_بفر_اندازه_بایټونه,
                                                                              x_Trigger_Level_بایټونه,
                                                                              x_بهیر_بفر_Type,
                                                                              عدم,
                                                                              عدم );

                    إذا( x_دننی_بهیر_بفر_Handle != عدم )
                    {
                        MPU_Store_بهیر_بفر_Handle_At_شاخص( l_شاخص, x_دننی_بهیر_بفر_Handle );
                        x_External_بهیر_بفر_Handle = ( بهیر_بفر_Handle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                    }
                    وإلا
                    {
                        MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                    }
                }
            }
            وإلا
            {
                trace_بهیر_بفر_CREATE_FAILED( x_بهیر_بفر_Type );
                x_External_بهیر_بفر_Handle = عدم;
            }

            أرجع x_External_بهیر_بفر_Handle;
        }

    #د_که_پای /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ویش == 1 ) && ( config_USE_بهیر_BUFFERS == 1 ) )

        بهیر_بفر_Handle_t MPU_x_بهیر_بفر_Generic_Create_Static( size_t x_بفر_اندازه_بایټونه,
                                                                   size_t x_Trigger_Level_بایټونه,
                                                                   بنسټ_Type_t x_بهیر_بفر_Type,
                                                                   uint8_t * ثابت puc_بهیر_بفر_Storage_Area,
                                                                   Static_بهیر_بفر_t * ثابت px_Static_بهیر_بفر,
                                                                   بهیر_بفر_Callback_Function_t pxSendCompletedCallback,
                                                                   بهیر_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            بهیر_بفر_Handle_t x_External_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == عدم ) &&
                          ( pxReceiveCompletedCallback == عدم ) );

            إذا( ( pxSendCompletedCallback == عدم ) &&
                ( pxReceiveCompletedCallback == عدم ) )
            {
                l_شاخص = MPU_Get_Free_شاخص_دننه_Kernel_Object_Pool();

                إذا( l_شاخص != -1 )
                {
                    x_دننی_بهیر_بفر_Handle = x_بهیر_بفر_Generic_Create_Static( x_بفر_اندازه_بایټونه,
                                                                                    x_Trigger_Level_بایټونه,
                                                                                    x_بهیر_بفر_Type,
                                                                                    puc_بهیر_بفر_Storage_Area,
                                                                                    px_Static_بهیر_بفر,
                                                                                    عدم,
                                                                                    عدم );

                    إذا( x_دننی_بهیر_بفر_Handle != عدم )
                    {
                        MPU_Store_بهیر_بفر_Handle_At_شاخص( l_شاخص, x_دننی_بهیر_بفر_Handle );
                        x_External_بهیر_بفر_Handle = ( بهیر_بفر_Handle_t ) CONVERT_منزل_EXTERNAL_شاخص( l_شاخص );
                    }
                    وإلا
                    {
                        MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( l_شاخص );
                    }
                }
            }
            وإلا
            {
                trace_بهیر_بفر_CREATE_STATIC_FAILED( xReturn, x_بهیر_بفر_Type );
                x_External_بهیر_بفر_Handle = عدم;
            }

            أرجع x_External_بهیر_بفر_Handle;
        }

    #د_که_پای /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        فراغ MPU_v_بهیر_بفر_Delete( بهیر_بفر_Handle_t x_بهیر_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_بهیر_بفر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_بهیر_بفر_Handle != عدم )
                {
                    v_بهیر_بفر_Delete( x_دننی_بهیر_بفر_Handle );
                }

                MPU_سېټ_شاخص_Free_دننه_Kernel_Object_Pool( CONVERT_منزل_دننی_شاخص( l_شاخص ) );
            }
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        بنسټ_Type_t MPU_x_بهیر_بفر_Reset( بهیر_بفر_Handle_t x_بهیر_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_بهیر_بفر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_بهیر_بفر_Handle != عدم )
                {
                    xReturn = x_بهیر_بفر_Reset( x_دننی_بهیر_بفر_Handle );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ویش == 1 ) && ( config_USE_بهیر_BUFFERS == 1 ) )

        بنسټ_Type_t MPU_x_بهیر_بفر_Get_Static_Buffers( بهیر_بفر_Handle_t x_بهیر_Buffers,
                                                      uint8_t * ppuc_بهیر_بفر_Storage_Area,
                                                      Static_بهیر_بفر_t * ppx_Static_بهیر_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_بهیر_Buffers;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_بهیر_بفر_Handle != عدم )
                {
                    xReturn = MPU_x_بهیر_بفر_Get_Static_Buffers( x_دننی_بهیر_بفر_Handle, ppuc_بهیر_بفر_Storage_Area, ppx_Static_بهیر_بفر );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

    size_t MPU_x_بهیر_بفر_Send_From_ISR( بهیر_بفر_Handle_t x_بهیر_بفر,
                                         ثابت فراغ * pv_Tx_معلومات,
                                         size_t x_معلومات_اوږدتیا_بایټونه,
                                         بنسټ_Type_t * ثابت px_Higher_لومړیتوب_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
        int32_t l_شاخص;

        l_شاخص = ( int32_t ) x_بهیر_بفر;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_دننی_بهیر_بفر_Handle != عدم )
            {
                xReturn = x_بهیر_بفر_Send_From_ISR( x_دننی_بهیر_بفر_Handle, pv_Tx_معلومات, x_معلومات_اوږدتیا_بایټونه, px_Higher_لومړیتوب_Task_Woken );
            }
        }

        أرجع xReturn;
    }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

    size_t MPU_x_بهیر_بفر_Receive_From_ISR( بهیر_بفر_Handle_t x_بهیر_بفر,
                                            فراغ * pv_Rx_معلومات,
                                            size_t x_بفر_اوږدتیا_بایټونه,
                                            بنسټ_Type_t * ثابت px_Higher_لومړیتوب_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
        int32_t l_شاخص;

        l_شاخص = ( int32_t ) x_بهیر_بفر;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

            إذا( x_دننی_بهیر_بفر_Handle != عدم )
            {
                xReturn = x_بهیر_بفر_Receive_From_ISR( x_دننی_بهیر_بفر_Handle, pv_Rx_معلومات, x_بفر_اوږدتیا_بایټونه, px_Higher_لومړیتوب_Task_Woken );
            }
        }

        أرجع xReturn;
    }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        بنسټ_Type_t MPU_x_بهیر_بفر_Send_Completed_From_ISR( بهیر_بفر_Handle_t x_بهیر_بفر,
                                                          بنسټ_Type_t * px_Higher_لومړیتوب_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_بهیر_بفر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_بهیر_بفر_Handle != عدم )
                {
                    xReturn = x_بهیر_بفر_Send_Completed_From_ISR( x_دننی_بهیر_بفر_Handle, px_Higher_لومړیتوب_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        بنسټ_Type_t MPU_x_بهیر_بفر_Receive_Completed_From_ISR( بهیر_بفر_Handle_t x_بهیر_بفر,
                                                             بنسټ_Type_t * px_Higher_لومړیتوب_Task_Woken ) /*PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFALSE;
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_بهیر_بفر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_بهیر_بفر_Handle != عدم )
                {
                    xReturn = x_بهیر_بفر_Receive_Completed_From_ISR( x_دننی_بهیر_بفر_Handle, px_Higher_لومړیتوب_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

    #إذا ( config_USE_بهیر_BUFFERS == 1 )

        بنسټ_Type_t MPU_x_بهیر_بفر_Reset_From_ISR( بهیر_بفر_Handle_t x_بهیر_بفر ) /*PRIVILEGED_FUNCTION */
        {
            بنسټ_Type_t xReturn = pdFAIL;
            بهیر_بفر_Handle_t x_دننی_بهیر_بفر_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_بهیر_بفر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_دننی_بهیر_بفر_Handle = MPU_Get_بهیر_بفر_Handle_At_شاخص( CONVERT_منزل_دننی_شاخص( l_شاخص ) );

                إذا( x_دننی_بهیر_بفر_Handle != عدم )
                {
                    xReturn = x_بهیر_بفر_Reset_From_ISR( x_دننی_بهیر_بفر_Handle );
                }
            }

            أرجع xReturn;
        }

    #د_که_پای /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h. */

    #إذا configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #ضمن "application_defined_privileged_functions.h"
    #د_که_پای
/*-----------------------------------------------------------*/

/**
 * @brief Array of system call implementation functions.
 *
 * The index in the array MUST match the corresponding system call number
 * defined in mpu_wrappers.h.
 */
    PRIVILEGED_معلومات UBaseType_t uxSystemCallImplementations[ عدد_SYSTEM_CALLS ] =
    {
        #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_xTaskGenericNotifyImpl,                     /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyWaitImpl,                 /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #د_که_پای

        #إذا ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_xTimerGenericCommandFromTaskImpl,           /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #د_که_پای

        #إذا ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_ډله_Wait_بټونه_Impl,                    /* SYSTEM_CALL_xEventGroupWaitBits. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupWaitBits. */
        #د_که_پای

        /* The system calls above this line take 5 parameters. */

        #إذا ( INCLUDE_xTaskDelayUntil == 1 )
            ( UBaseType_t ) MPU_xTaskDelayUntilImpl,                        /* SYSTEM_CALL_xTaskDelayUntil. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskDelayUntil. */
        #د_که_پای

        #إذا ( INCLUDE_xTaskAbortDelay == 1 )
            ( UBaseType_t ) MPU_xTaskAbortDelayImpl,                        /* SYSTEM_CALL_xTaskAbortDelay. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskAbortDelay. */
        #د_که_پای

        #إذا ( INCLUDE_vTaskDelay == 1 )
            ( UBaseType_t ) MPU_vTaskDelayImpl,                             /* SYSTEM_CALL_vTaskDelay. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskDelay. */
        #د_که_پای

        #إذا ( INCLUDE_ux_Task_لومړیتوب_Get == 1 )
            ( UBaseType_t ) MPU_ux_Task_لومړیتوب_Get_Impl,                      /* SYSTEM_CALL_uxTaskPriorityGet. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskPriorityGet. */
        #د_که_پای

        #إذا ( INCLUDE_eTaskGetState == 1 )
            ( UBaseType_t ) MPU_eTaskGetStateImpl,                          /* SYSTEM_CALL_eTaskGetState. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_eTaskGetState. */
        #د_که_پای

        #إذا ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_vTaskGetInfoImpl,                           /* SYSTEM_CALL_vTaskGetInfo. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskGetInfo. */
        #د_که_پای

        #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
            ( UBaseType_t ) MPU_xTaskGetIdleTaskHandleImpl,                 /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #د_که_پای

        #إذا ( INCLUDE_vTaskSuspend == 1 )
            ( UBaseType_t ) MPU_vTaskSuspendImpl,                           /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) MPU_vTaskResumeImpl,                            /* SYSTEM_CALL_vTaskResume. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskResume. */
        #د_که_پای

        ( UBaseType_t ) MPU_x_Task_Get_Tick_شمېر_Impl,                          /* SYSTEM_CALL_xTaskGetTickCount. */
        ( UBaseType_t ) MPU_ux_Task_Get_شمېره_د_Tasks_Impl,                     /* SYSTEM_CALL_uxTaskGetNumberOfTasks. */

        #إذا ( config_GENERATE_پرلپسې_وخت_STATS == 1 )
            ( UBaseType_t ) MPU_ul_Task_Get_پرلپسې_وخت_Counter_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) MPU_ul_Task_Get_پرلپسې_وخت_Percent_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #د_که_پای

        #إذا ( ( config_GENERATE_پرلپسې_وخت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_پرلپسې_وخت_Percent_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_پرلپسې_وخت_Counter_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #د_که_پای

        #إذا ( config_USE_APPLICATION_TASK_نښان == 1 )
            ( UBaseType_t ) MPU_v_Task_سېټ_Application_Task_نښان_Impl,             /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) MPU_x_Task_Get_Application_Task_نښان_Impl,             /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #د_که_پای

        #إذا ( config_عدد_THREAD_LOCAL_STORAGE_اشارې != 0 )
            ( UBaseType_t ) MPU_v_Task_سېټ_Thread_Local_Storage_اشاره_ګر_Impl,      /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) MPU_pv_Task_Get_Thread_Local_Storage_اشاره_ګر_Impl,     /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #د_که_پای

        #إذا ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_uxTaskGetSystemStateImpl,                   /* SYSTEM_CALL_uxTaskGetSystemState. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetSystemState. */
        #د_که_پای

        #إذا ( INCLUDE_ux_Task_Get_ډېری_لوړ_Water_Mark == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ډېری_لوړ_Water_Mark_Impl,            /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #د_که_پای

        #إذا ( INCLUDE_ux_Task_Get_ډېری_لوړ_Water_Mark2 == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ډېری_لوړ_Water_Mark2_Impl,           /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #د_که_پای

        #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )
            ( UBaseType_t ) MPU_xTaskGetCurrentTaskHandleImpl,              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #د_که_پای

        #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )
            ( UBaseType_t ) MPU_xTaskGetSchedulerStateImpl,                 /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #د_که_پای

        ( UBaseType_t ) MPU_v_Task_سېټ_وخت_بهر_State_Impl,                       /* SYSTEM_CALL_vTaskSetTimeOutState. */
        ( UBaseType_t ) MPU_x_Task_Check_For_وخت_بهر_Impl,                       /* SYSTEM_CALL_xTaskCheckForTimeOut. */

        #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_ulTaskGenericNotifyTakeImpl,                /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyStateClearImpl,           /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) MPU_ul_Task_Generic_Notify_ارزښت_Clear_Impl,          /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #د_که_پای

        ( UBaseType_t ) MPU_x_کتار_Generic_Send_Impl,                          /* SYSTEM_CALL_xQueueGenericSend. */
        ( UBaseType_t ) MPU_ux_کتار_Messages_انتظار_Impl,                     /* SYSTEM_CALL_uxQueueMessagesWaiting. */
        ( UBaseType_t ) MPU_ux_کتار_Spaces_شته_Impl,                     /* SYSTEM_CALL_uxQueueSpacesAvailable. */
        ( UBaseType_t ) MPU_x_کتار_Receive_Impl,                              /* SYSTEM_CALL_xQueueReceive. */
        ( UBaseType_t ) MPU_x_کتار_Peek_Impl,                                 /* SYSTEM_CALL_xQueuePeek. */
        ( UBaseType_t ) MPU_x_کتار_Semaphore_Take_Impl,                        /* SYSTEM_CALL_xQueueSemaphoreTake. */

        #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
            ( UBaseType_t ) MPU_x_کتار_Get_Mutex_Holder_Impl,                   /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #د_که_پای

        #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )
            ( UBaseType_t ) MPU_x_کتار_Take_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) MPU_x_کتار_Give_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #د_که_پای

        #إذا ( config_USE_کتار_SETS == 1 )
            ( UBaseType_t ) MPU_x_کتار_Select_From_سېټ_Impl,                    /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) MPU_x_کتار_جمع_کړه_منزل_سېټ_Impl,                         /* SYSTEM_CALL_xQueueAddToSet. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueAddToSet. */
        #د_که_پای

        #إذا config_کتار_REGISTRY_اندازه > 0
            ( UBaseType_t ) MPU_v_کتار_جمع_کړه_منزل_Registry_Impl,                    /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) MPU_v_کتار_Unregister_کتار_Impl,                  /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) MPU_pc_کتار_Get_Name_Impl,                         /* SYSTEM_CALL_pcQueueGetName. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcQueueGetName. */
        #د_که_پای

        #إذا ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_pvTimerGetTimerIDImpl,                      /* SYSTEM_CALL_pvTimerGetTimerID. */
            ( UBaseType_t ) MPU_v_Timer_سېټ_Timer_IDImpl,                       /* SYSTEM_CALL_vTimerSetTimerID. */
            ( UBaseType_t ) MPU_x_Timer_Is_Timer_فعال_Impl,                    /* SYSTEM_CALL_xTimerIsTimerActive. */
            ( UBaseType_t ) MPU_xTimerGetTimerDaemonTaskHandleImpl,         /* SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle. */
            ( UBaseType_t ) MPU_pcTimerGetNameImpl,                         /* SYSTEM_CALL_pcTimerGetName. */
            ( UBaseType_t ) MPU_v_Timer_سېټ_Reload_ډېرپېښ_Impl,                    /* SYSTEM_CALL_vTimerSetReloadMode. */
            ( UBaseType_t ) MPU_x_Timer_Get_Reload_ډېرپېښ_Impl,                    /* SYSTEM_CALL_xTimerGetReloadMode. */
            ( UBaseType_t ) MPU_ux_Timer_Get_Reload_ډېرپېښ_Impl,                   /* SYSTEM_CALL_uxTimerGetReloadMode. */
            ( UBaseType_t ) MPU_xTimerGetPeriodImpl,                        /* SYSTEM_CALL_xTimerGetPeriod. */
            ( UBaseType_t ) MPU_x_Timer_Get_Expiry_وخت_Impl,                    /* SYSTEM_CALL_xTimerGetExpiryTime. */
        #وإلا
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
        #د_که_پای

        #إذا ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_ډله_Clear_بټونه_Impl,                   /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) MPU_x_Event_ډله_سېټ_بټونه_Impl,                     /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) MPU_x_Event_ډله_Sync_Impl,                        /* SYSTEM_CALL_xEventGroupSync. */

            #إذا ( configUSE_TRACE_FACILITY == 1 )
                ( UBaseType_t ) MPU_ux_Event_ډله_Get_شمېره_Impl,              /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) MPU_v_Event_ډله_سېټ_شمېره_Impl,               /* SYSTEM_CALL_vEventGroupSetNumber. */
            #وإلا
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_vEventGroupSetNumber. */
            #د_که_پای
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSync. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxEventGroupGetNumber. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vEventGroupSetNumber. */
        #د_که_پای

        #إذا ( config_USE_بهیر_BUFFERS == 1 )
            ( UBaseType_t ) MPU_x_بهیر_بفر_Send_Impl,                      /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) MPU_x_بهیر_بفر_Receive_Impl,                   /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) MPU_x_بهیر_بفر_Is_ډک_Impl,                    /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) MPU_x_بهیر_بفر_Is_تشه_Impl,                   /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) MPU_x_بهیر_بفر_Spaces_شته_Impl,           /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) MPU_x_بهیر_بفر_بایټونه_شته_Impl,            /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) MPU_x_بهیر_بفر_سېټ_Trigger_Level_Impl,           /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) MPU_x_بهیر_بفر_بل_پیغام_اوږدتیا_بایټونه_Impl     /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #د_که_پای

    };
/*-----------------------------------------------------------*/

#د_که_پای /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/
