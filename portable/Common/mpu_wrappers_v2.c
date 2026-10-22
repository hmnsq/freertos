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
#وصف_ڪريو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "queue.h"
#ضمن "timers.h"
#ضمن "event_groups.h"
#ضمن "stream_buffer.h"
#ضمن "mpu_prototypes.h"
#ضمن "mpu_syscall_numbers.h"

#وصف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#إذا ( ( پورٽ_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #جيڪڏهن_وصف_نه_ٿيل config_PROTECTED_KERNEL_OBJECT_POOL_سائيز
        #غلطي config_PROTECTED_KERNEL_OBJECT_POOL_سائيز must be defined منزل وڌ_کان_وڌ عدد جو kernel objects اندريون the application.
    #جيڪڏهن_پورو

/**
 * @brief Offset added to the index before returning to the user.
 *
 * If the actual handle is stored at index i, ( i + INDEX_OFFSET )
 * is returned to the user.
 */
    #وصف_ڪريو اشاريو_وٿي    1

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
        OpaqueObjectHandle_t x_اندروني_Object_Handle;
        uint32_t ulKernelObjectType;
        فراغ * pv_Kernel_Object_معلومات;
    } KernelObject_t;

/**
 * @brief Kernel object types.
 */
    #وصف_ڪريو KERNEL_OBJECT_TYPE_INVALID          ( 0UL )
    #وصف_ڪريو KERNEL_OBJECT_TYPE_قطار            ( 1UL )
    #وصف_ڪريو KERNEL_OBJECT_TYPE_TASK             ( 2UL )
    #وصف_ڪريو KERNEL_OBJECT_TYPE_وهڪرو_بفر    ( 3UL )
    #وصف_ڪريو KERNEL_OBJECT_TYPE_EVENT_گروهه      ( 4UL )
    #وصف_ڪريو KERNEL_OBJECT_TYPE_TIMER            ( 5UL )

/**
 * @brief Checks whether an external index is valid or not.
 */
    #وصف_ڪريو IS_EXTERNAL_اشاريو_VALID( l_اشاريو )   \
    ( ( ( ( l_اشاريو ) >= اشاريو_وٿي ) &&       \
        ( ( l_اشاريو ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_سائيز + اشاريو_وٿي ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Checks whether an internal index is valid or not.
 */
    #وصف_ڪريو IS_اندروني_اشاريو_VALID( l_اشاريو )   \
    ( ( ( ( l_اشاريو ) >= 0 ) &&                  \
        ( ( l_اشاريو ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_سائيز ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Converts an internal index into external.
 */
    #وصف_ڪريو CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو )    ( ( l_اشاريو ) + اشاريو_وٿي )

/**
 * @brief Converts an external index into internal.
 */
    #وصف_ڪريو CONVERT_منزل_اندروني_اشاريو( l_اشاريو )    ( ( l_اشاريو ) - اشاريو_وٿي )

/**
 * @brief Max value that fits in a UBaseType_t type.
 */
    #وصف_ڪريو mpuUBASETYPE_MAX    ( ~( ( UBaseType_t ) 0 ) )

/**
 * @brief Check if multiplying a and b will result in overflow.
 */
    #وصف_ڪريو mpu_MULTIPLY_BASETYPE_WILL_حد_کان_مٿي( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( mpuUBASETYPE_MAX / ( a ) ) ) )

/**
 * @brief Get the index of a free slot in the kernel object pool.
 *
 * If a free slot is found, this function marks the slot as
 * "not free".
 *
 * @return Index of a free slot is returned, if a free slot is
 *         found. Otherwise -1 is returned.
 */
    ساكن int32_t MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Set the given index as free in the kernel object pool.
 *
 * @param lIndex The index to set as free.
 */
    ساكن فراغ MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( int32_t l_اشاريو ) PRIVILEGED_FUNCTION;

/**
 * @brief Get the index at which a given kernel object is stored.
 *
 * @param xHandle The given kernel object handle.
 * @param ulKernelObjectType The kernel object type.
 *
 * @return Index at which the kernel object is stored if it is a valid
 *         handle, -1 otherwise.
 */
    ساكن int32_t MPU_Get_اشاريو_For_Handle( OpaqueObjectHandle_t xHandle,
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
    ساكن فراغ MPU_Store_Handle_And_معلومات_At_اشاريو( int32_t l_اشاريو,
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
    ساكن OpaqueObjectHandle_t MPU_Get_Handle_At_اشاريو( int32_t l_اشاريو,
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
        ساكن فراغ MPU_TimerCallback( TimerHandle_t x_اندروني_Handle ) PRIVILEGED_FUNCTION;

    #جيڪڏهن_پورو /* #if ( configUSE_TIMERS == 1 ) */

/*
 * Wrappers to keep all the casting in one place.
 */
    #وصف_ڪريو MPU_Store_قطار_Handle_At_اشاريو( l_اشاريو, xHandle )                 MPU_Store_Handle_And_معلومات_At_اشاريو( ( l_اشاريو ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_قطار )
    #وصف_ڪريو MPU_Get_قطار_Handle_At_اشاريو( l_اشاريو )                            ( قطار_Handle_t ) MPU_Get_Handle_At_اشاريو( ( l_اشاريو ), KERNEL_OBJECT_TYPE_قطار )

    #إذا ( config_USE_قطار_SETS == 1 )
        #وصف_ڪريو MPU_Store_قطار_سيٽ_Handle_At_اشاريو( l_اشاريو, xHandle )          MPU_Store_Handle_And_معلومات_At_اشاريو( ( l_اشاريو ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_قطار )
        #وصف_ڪريو MPU_Get_قطار_سيٽ_Handle_At_اشاريو( l_اشاريو )                     ( قطار_سيٽ_Handle_t ) MPU_Get_Handle_At_اشاريو( ( l_اشاريو ), KERNEL_OBJECT_TYPE_قطار )
        #وصف_ڪريو MPU_Store_قطار_سيٽ_Member_Handle_At_اشاريو( l_اشاريو, xHandle )    MPU_Store_Handle_And_معلومات_At_اشاريو( ( l_اشاريو ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_قطار )
        #وصف_ڪريو MPU_Get_قطار_سيٽ_Member_Handle_At_اشاريو( l_اشاريو )               ( قطار_سيٽ_Member_Handle_t ) MPU_Get_Handle_At_اشاريو( ( l_اشاريو ), KERNEL_OBJECT_TYPE_قطار )
        #وصف_ڪريو MPU_Get_اشاريو_For_قطار_سيٽ_Member_Handle( xHandle )             MPU_Get_اشاريو_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_قطار )
    #جيڪڏهن_پورو

/*
 * Wrappers to keep all the casting in one place for Task APIs.
 */
    #وصف_ڪريو MPU_Store_Task_Handle_At_اشاريو( l_اشاريو, xHandle )            MPU_Store_Handle_And_معلومات_At_اشاريو( ( l_اشاريو ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_TASK )
    #وصف_ڪريو MPU_Get_Task_Handle_At_اشاريو( l_اشاريو )                       ( TaskHandle_t ) MPU_Get_Handle_At_اشاريو( ( l_اشاريو ), KERNEL_OBJECT_TYPE_TASK )
    #وصف_ڪريو MPU_Get_اشاريو_For_Task_Handle( xHandle )                     MPU_Get_اشاريو_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TASK )

    #إذا ( configUSE_EVENT_GROUPS == 1 )
/*
 * Wrappers to keep all the casting in one place for Event Group APIs.
 */
        #وصف_ڪريو MPU_Store_Event_گروهه_Handle_At_اشاريو( l_اشاريو, xHandle )      MPU_Store_Handle_And_معلومات_At_اشاريو( ( l_اشاريو ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_EVENT_گروهه )
        #وصف_ڪريو MPU_Get_Event_گروهه_Handle_At_اشاريو( l_اشاريو )                 ( Event_گروهه_Handle_t ) MPU_Get_Handle_At_اشاريو( ( l_اشاريو ), KERNEL_OBJECT_TYPE_EVENT_گروهه )
        #وصف_ڪريو MPU_Get_اشاريو_For_Event_گروهه_Handle( xHandle )               MPU_Get_اشاريو_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_EVENT_گروهه )

    #جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Stream Buffer APIs.
 */
        #وصف_ڪريو MPU_Store_وهڪرو_بفر_Handle_At_اشاريو( l_اشاريو, xHandle )    MPU_Store_Handle_And_معلومات_At_اشاريو( ( l_اشاريو ), ( OpaqueObjectHandle_t ) ( xHandle), عدم, KERNEL_OBJECT_TYPE_وهڪرو_بفر )
        #وصف_ڪريو MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( l_اشاريو )               ( وهڪرو_بفر_Handle_t ) MPU_Get_Handle_At_اشاريو( ( l_اشاريو ), KERNEL_OBJECT_TYPE_وهڪرو_بفر )
        #وصف_ڪريو MPU_Get_اشاريو_For_وهڪرو_بفر_Handle( xHandle )             MPU_Get_اشاريو_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_وهڪرو_بفر )

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

    #إذا ( configUSE_TIMERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Timer APIs.
 */
        #وصف_ڪريو MPU_Store_Timer_Handle_At_اشاريو( l_اشاريو, xHandle, pxApplicationCallback )    MPU_Store_Handle_And_معلومات_At_اشاريو( ( l_اشاريو ), ( OpaqueObjectHandle_t ) ( xHandle ), ( فراغ * ) ( pxApplicationCallback ), KERNEL_OBJECT_TYPE_TIMER )
        #وصف_ڪريو MPU_Get_Timer_Handle_At_اشاريو( l_اشاريو )                                      ( TimerHandle_t ) MPU_Get_Handle_At_اشاريو( ( l_اشاريو ), KERNEL_OBJECT_TYPE_TIMER )
        #وصف_ڪريو MPU_Get_اشاريو_For_Timer_Handle( xHandle )                                    MPU_Get_اشاريو_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TIMER )

    #جيڪڏهن_پورو /* #if ( configUSE_TIMERS == 1 ) */

/*-----------------------------------------------------------*/

/**
 * @brief Kernel object pool.
 */
    PRIVILEGED_معلومات ساكن KernelObject_t xKernelObjectPool[ config_PROTECTED_KERNEL_OBJECT_POOL_سائيز ] = { 0 };
/*-----------------------------------------------------------*/

    ساكن int32_t MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_Free_اشاريو = -1;

        /* This function is called only from resource create APIs
         * which are not supposed to be called from ISRs. Therefore,
         * we only need to suspend the scheduler and do not require
         * critical section. */
        vTaskSuspendAll();
        {
            لكل( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_سائيز; i++ )
            {
                إذا( xKernelObjectPool[ i ].x_اندروني_Object_Handle == عدم )
                {
                    /* Mark this index as not free. */
                    xKernelObjectPool[ i ].x_اندروني_Object_Handle = ( OpaqueObjectHandle_t ) ( ~0U );
                    l_Free_اشاريو = i;
                    اكسر;
                }
            }
        }
        ( فراغ ) xTaskResumeAll();

        أرجع l_Free_اشاريو;
    }
/*-----------------------------------------------------------*/

    ساكن فراغ MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( int32_t l_اشاريو ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_اندروني_اشاريو_VALID( l_اشاريو ) != pdFALSE );

        taskENTER_CRITICAL();
        {
            xKernelObjectPool[ l_اشاريو ].x_اندروني_Object_Handle = عدم;
            xKernelObjectPool[ l_اشاريو ].ulKernelObjectType = KERNEL_OBJECT_TYPE_INVALID;
            xKernelObjectPool[ l_اشاريو ].pv_Kernel_Object_معلومات = عدم;
        }
        taskEXIT_CRITICAL();
    }
/*-----------------------------------------------------------*/

    ساكن int32_t MPU_Get_اشاريو_For_Handle( OpaqueObjectHandle_t xHandle,
                                          uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_اشاريو = -1;

        configASSERT( xHandle != عدم );

        لكل( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_سائيز; i++ )
        {
            إذا( ( xKernelObjectPool[ i ].x_اندروني_Object_Handle == xHandle ) &&
                ( xKernelObjectPool[ i ].ulKernelObjectType == ulKernelObjectType ) )
            {
                l_اشاريو = i;
                اكسر;
            }
        }

        أرجع l_اشاريو;
    }
/*-----------------------------------------------------------*/

    ساكن فراغ MPU_Store_Handle_And_معلومات_At_اشاريو( int32_t l_اشاريو,
                                               OpaqueObjectHandle_t xHandle,
                                               فراغ * pv_Kernel_Object_معلومات,
                                               uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_اندروني_اشاريو_VALID( l_اشاريو ) != pdFALSE );
        xKernelObjectPool[ l_اشاريو ].x_اندروني_Object_Handle = xHandle;
        xKernelObjectPool[ l_اشاريو ].ulKernelObjectType = ulKernelObjectType;
        xKernelObjectPool[ l_اشاريو ].pv_Kernel_Object_معلومات = pv_Kernel_Object_معلومات;
    }
/*-----------------------------------------------------------*/

    ساكن OpaqueObjectHandle_t MPU_Get_Handle_At_اشاريو( int32_t l_اشاريو,
                                                      uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        OpaqueObjectHandle_t xObjectHandle = عدم;

        configASSERT( IS_اندروني_اشاريو_VALID( l_اشاريو ) != pdFALSE );

        إذا( xKernelObjectPool[ l_اشاريو ].ulKernelObjectType == ulKernelObjectType )
        {
            xObjectHandle = xKernelObjectPool[ l_اشاريو ].x_اندروني_Object_Handle;
        }

        أرجع xObjectHandle;
    }
/*-----------------------------------------------------------*/

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        فراغ v_Grant_Access_منزل_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                         int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;

            إذا( IS_EXTERNAL_اشاريو_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                إذا( xExternalTaskHandle == عدم )
                {
                    v_پورٽ_Grant_Access_منزل_Kernel_Object( xExternalTaskHandle, CONVERT_منزل_اندروني_اشاريو( lExternalKernelObjectHandle ) );
                }
                وإلا
                {
                    l_External_Task_اشاريو = ( int32_t ) xExternalTaskHandle;

                    إذا( IS_EXTERNAL_اشاريو_VALID( l_External_Task_اشاريو ) != pdFALSE )
                    {
                        x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_External_Task_اشاريو ) );

                        إذا( x_اندروني_Task_Handle != عدم )
                        {
                            v_پورٽ_Grant_Access_منزل_Kernel_Object( x_اندروني_Task_Handle,
                                                            CONVERT_منزل_اندروني_اشاريو( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #جيڪڏهن_پورو /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        فراغ v_Revoke_Access_منزل_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                          int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;

            إذا( IS_EXTERNAL_اشاريو_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                إذا( xExternalTaskHandle == عدم )
                {
                    v_پورٽ_Revoke_Access_منزل_Kernel_Object( xExternalTaskHandle, CONVERT_منزل_اندروني_اشاريو( lExternalKernelObjectHandle ) );
                }
                وإلا
                {
                    l_External_Task_اشاريو = ( int32_t ) xExternalTaskHandle;

                    إذا( IS_EXTERNAL_اشاريو_VALID( l_External_Task_اشاريو ) != pdFALSE )
                    {
                        x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_External_Task_اشاريو ) );

                        إذا( x_اندروني_Task_Handle != عدم )
                        {
                            v_پورٽ_Revoke_Access_منزل_Kernel_Object( x_اندروني_Task_Handle,
                                                             CONVERT_منزل_اندروني_اشاريو( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #جيڪڏهن_پورو /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ساكن فراغ MPU_TimerCallback( TimerHandle_t x_اندروني_Handle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t i, l_اشاريو = -1;
            TimerHandle_t xExternalHandle = عدم;
            TimerCallbackFunction_t px_Application_Call_پٺ = عدم;

            /* Coming from the timer task and therefore, should be valid. */
            configASSERT( x_اندروني_Handle != عدم );

            لكل( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_سائيز; i++ )
            {
                إذا( ( ( TimerHandle_t ) xKernelObjectPool[ i ].x_اندروني_Object_Handle == x_اندروني_Handle ) &&
                    ( xKernelObjectPool[ i ].ulKernelObjectType == KERNEL_OBJECT_TYPE_TIMER ) )
                {
                    l_اشاريو = i;
                    اكسر;
                }
            }

            configASSERT( l_اشاريو != -1 );
            xExternalHandle = ( TimerHandle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );

            px_Application_Call_پٺ = ( TimerCallbackFunction_t ) xKernelObjectPool[ l_اشاريو ].pv_Kernel_Object_معلومات;
            px_Application_Call_پٺ( xExternalHandle );
        }

    #جيڪڏهن_پورو /* #if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for tasks APIs.                   */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskDelayUntil == 1 )

        بنياد_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ثابت px_اڳيون_Wake_وقت,
                                            TickType_t x_وقت_Increment ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ثابت px_اڳيون_Wake_وقت,
                                            TickType_t x_وقت_Increment ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            بنياد_Type_t x_Is_اڳيون_Wake_وقت_Accessible = pdFALSE;

            إذا( ( px_اڳيون_Wake_وقت != عدم ) && ( x_وقت_Increment > 0U ) )
            {
                x_Is_اڳيون_Wake_وقت_Accessible = x_پورٽ_Is_Authorized_منزل_Access_بفر( px_اڳيون_Wake_وقت,
                                                                                 حجم( TickType_t ),
                                                                                 ( tskMPU_WRITE_PERMISSION | tskMPU_READ_PERMISSION ) );

                إذا( x_Is_اڳيون_Wake_وقت_Accessible == pdTRUE )
                {
                    xReturn = xTaskDelayUntil( px_اڳيون_Wake_وقت, x_وقت_Increment );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskAbortDelay == 1 )

        بنياد_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = ( int32_t ) xTask;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                {
                    x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Task_Handle != عدم )
                    {
                        xReturn = xTaskAbortDelay( x_اندروني_Task_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelay == 1 )

        فراغ MPU_vTaskDelayImpl( TickType_t x_Ticks_منزل_Delay ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskDelayImpl( TickType_t x_Ticks_منزل_Delay ) /* PRIVILEGED_FUNCTION */
        {
            vTaskDelay( x_Ticks_منزل_Delay );
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_ترجيح_Get == 1 )

        UBaseType_t MPU_ux_Task_ترجيح_Get_Impl( ثابت TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_ترجيح_Get_Impl( ثابت TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;

            إذا( pxTask == عدم )
            {
                uxReturn = ux_Task_ترجيح_Get( pxTask );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) pxTask;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_اندروني_Task_Handle != عدم )
                        {
                            uxReturn = ux_Task_ترجيح_Get( x_اندروني_Task_Handle );
                        }
                    }
                }
            }

            أرجع uxReturn;
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            eTaskState eReturn = eInvalid;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            l_اشاريو = ( int32_t ) pxTask;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                {
                    x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Task_Handle != عدم )
                    {
                        eReturn = eTaskGetState( x_اندروني_Task_Handle );
                    }
                }
            }

            أرجع eReturn;
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        فراغ MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_حالت_t * px_Task_حالت,
                                   بنياد_Type_t x_Get_Free_ڍير_Space,
                                   eTaskState eState ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_حالت_t * px_Task_حالت,
                                   بنياد_Type_t x_Get_Free_ڍير_Space,
                                   eTaskState eState ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            بنياد_Type_t x_Is_Task_حالت_Writeable = pdFALSE;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            x_Is_Task_حالت_Writeable = x_پورٽ_Is_Authorized_منزل_Access_بفر( px_Task_حالت,
                                                                      حجم( Task_حالت_t ),
                                                                      tskMPU_WRITE_PERMISSION );

            إذا( x_Is_Task_حالت_Writeable == pdTRUE )
            {
                إذا( xTask == عدم )
                {
                    vTaskGetInfo( xTask, px_Task_حالت, x_Get_Free_ڍير_Space, eState );
                }
                وإلا
                {
                    l_اشاريو = ( int32_t ) xTask;

                    إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                        {
                            x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                            إذا( x_اندروني_Task_Handle != عدم )
                            {
                                vTaskGetInfo( x_اندروني_Task_Handle, px_Task_حالت, x_Get_Free_ڍير_Space, eState );
                            }
                        }
                    }
                }
            }
        }

    #جيڪڏهن_پورو /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( فراغ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xIdleTaskHandle = عدم;

            xIdleTaskHandle = xTaskGetIdleTaskHandle();

            أرجع xIdleTaskHandle;
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )

        فراغ MPU_vTaskSuspendImpl( TaskHandle_t px_Task_منزل_Suspend ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskSuspendImpl( TaskHandle_t px_Task_منزل_Suspend ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( px_Task_منزل_Suspend == عدم )
            {
                vTaskSuspend( px_Task_منزل_Suspend );
            }
            وإلا
            {
                /* After the scheduler starts, only privileged tasks are allowed
                 * to suspend other tasks. */
                #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )
                    إذا( ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) || ( پورٽ_IS_TASK_PRIVILEGED() == pdTRUE ) )
                #وإلا
                    إذا( پورٽ_IS_TASK_PRIVILEGED() == pdTRUE )
                #جيڪڏهن_پورو
                {
                    l_اشاريو = ( int32_t ) px_Task_منزل_Suspend;

                    إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                        {
                            x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                            إذا( x_اندروني_Task_Handle != عدم )
                            {
                                vTaskSuspend( x_اندروني_Task_Handle );
                            }
                        }
                    }
                }
            }
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )

        فراغ MPU_vTaskResumeImpl( TaskHandle_t px_Task_منزل_Resume ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskResumeImpl( TaskHandle_t px_Task_منزل_Resume ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            l_اشاريو = ( int32_t ) px_Task_منزل_Resume;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                {
                    x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Task_Handle != عدم )
                    {
                        vTaskResume( x_اندروني_Task_Handle );
                    }
                }
            }
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_ڳڻپ_Impl( فراغ ) PRIVILEGED_FUNCTION;

    TickType_t MPU_x_Task_Get_Tick_ڳڻپ_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        TickType_t xReturn;

        xReturn = x_Task_Get_Tick_ڳڻپ();

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_عدد_جو_Tasks_Impl( فراغ ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Task_Get_عدد_جو_Tasks_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn;

        uxReturn = ux_Task_Get_عدد_جو_Tasks();

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_لاڳيتو_وقت_STATS == 1 )

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_لاڳيتو_وقت_Counter_Impl( ثابت TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_لاڳيتو_وقت_Counter_Impl( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_لاڳيتو_وقت_COUNTER_TYPE xReturn = 0;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                xReturn = ul_Task_Get_لاڳيتو_وقت_Counter( xTask );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_اندروني_Task_Handle != عدم )
                        {
                            xReturn = ul_Task_Get_لاڳيتو_وقت_Counter( x_اندروني_Task_Handle );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_لاڳيتو_وقت_STATS == 1 )

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_لاڳيتو_وقت_Percent_Impl( ثابت TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_لاڳيتو_وقت_Percent_Impl( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_لاڳيتو_وقت_COUNTER_TYPE xReturn = 0;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                xReturn = ul_Task_Get_لاڳيتو_وقت_Percent( xTask );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_اندروني_Task_Handle != عدم )
                        {
                            xReturn = ul_Task_Get_لاڳيتو_وقت_Percent( x_اندروني_Task_Handle );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_لاڳيتو_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Percent_Impl( فراغ ) PRIVILEGED_FUNCTION;

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Percent_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            config_لاڳيتو_وقت_COUNTER_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_لاڳيتو_وقت_Percent();

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_لاڳيتو_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Counter_Impl( فراغ ) PRIVILEGED_FUNCTION;

        config_لاڳيتو_وقت_COUNTER_TYPE MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Counter_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            config_لاڳيتو_وقت_COUNTER_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_لاڳيتو_وقت_Counter();

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٽيگ == 1 )

        فراغ MPU_v_Task_سيٽ_Application_Task_ٽيگ_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_ٽيگ_قدر ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Task_سيٽ_Application_Task_ٽيگ_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_ٽيگ_قدر ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                v_Task_سيٽ_Application_Task_ٽيگ( xTask, px_ٽيگ_قدر );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_اندروني_Task_Handle != عدم )
                        {
                            v_Task_سيٽ_Application_Task_ٽيگ( x_اندروني_Task_Handle, px_ٽيگ_قدر );
                        }
                    }
                }
            }
        }

    #جيڪڏهن_پورو /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٽيگ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٽيگ_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٽيگ_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = عدم;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                xReturn = x_Task_Get_Application_Task_ٽيگ( xTask );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_اندروني_Task_Handle != عدم )
                        {
                            xReturn = x_Task_Get_Application_Task_ٽيگ( x_اندروني_Task_Handle );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_انگ_THREAD_LOCAL_STORAGE_اشارا != 0 )

        فراغ MPU_v_Task_سيٽ_Thread_Local_Storage_اشارو_Impl( TaskHandle_t x_Task_منزل_سيٽ,
                                                        بنياد_Type_t x_اشاريو,
                                                        فراغ * pv_قدر ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Task_سيٽ_Thread_Local_Storage_اشارو_Impl( TaskHandle_t x_Task_منزل_سيٽ,
                                                        بنياد_Type_t x_اشاريو,
                                                        فراغ * pv_قدر ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( x_Task_منزل_سيٽ == عدم )
            {
                v_Task_سيٽ_Thread_Local_Storage_اشارو( x_Task_منزل_سيٽ, x_اشاريو, pv_قدر );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) x_Task_منزل_سيٽ;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_اندروني_Task_Handle != عدم )
                        {
                            v_Task_سيٽ_Thread_Local_Storage_اشارو( x_اندروني_Task_Handle, x_اشاريو, pv_قدر );
                        }
                    }
                }
            }
        }

    #جيڪڏهن_پورو /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_انگ_THREAD_LOCAL_STORAGE_اشارا != 0 )

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشارو_Impl( TaskHandle_t x_Task_منزل_Query,
                                                           بنياد_Type_t x_اشاريو ) PRIVILEGED_FUNCTION;

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشارو_Impl( TaskHandle_t x_Task_منزل_Query,
                                                           بنياد_Type_t x_اشاريو ) /* PRIVILEGED_FUNCTION */
        {
            فراغ * pvReturn = عدم;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( x_Task_منزل_Query == عدم )
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_اشارو( x_Task_منزل_Query, x_اشاريو );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) x_Task_منزل_Query;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_اندروني_Task_Handle != عدم )
                        {
                            pvReturn = pv_Task_Get_Thread_Local_Storage_اشارو( x_اندروني_Task_Handle, x_اشاريو );
                        }
                    }
                }
            }

            أرجع pvReturn;
        }

    #جيڪڏهن_پورو /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_حالت_t * px_Task_حالت_Array,
                                                  UBaseType_t ux_Array_سائيز,
                                                  config_لاڳيتو_وقت_COUNTER_TYPE * pul_ڪل_لاڳيتو_وقت ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_حالت_t * px_Task_حالت_Array,
                                                  UBaseType_t ux_Array_سائيز,
                                                  config_لاڳيتو_وقت_COUNTER_TYPE * pul_ڪل_لاڳيتو_وقت ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            بنياد_Type_t x_Is_Task_حالت_Array_Writeable = pdFALSE;
            بنياد_Type_t x_Is_ڪل_لاڳيتو_وقت_Writeable = pdFALSE;

            إذا( mpu_MULTIPLY_BASETYPE_WILL_حد_کان_مٿي( حجم( Task_حالت_t ), ux_Array_سائيز ) == 0 )
            {
                x_Is_Task_حالت_Array_Writeable = x_پورٽ_Is_Authorized_منزل_Access_بفر( px_Task_حالت_Array,
                                                                               حجم( Task_حالت_t ) * ( size_t ) ux_Array_سائيز,
                                                                               tskMPU_WRITE_PERMISSION );

                إذا( pul_ڪل_لاڳيتو_وقت != عدم )
                {
                    x_Is_ڪل_لاڳيتو_وقت_Writeable = x_پورٽ_Is_Authorized_منزل_Access_بفر( pul_ڪل_لاڳيتو_وقت,
                                                                                حجم( config_لاڳيتو_وقت_COUNTER_TYPE ),
                                                                                tskMPU_WRITE_PERMISSION );
                }

                إذا( ( x_Is_Task_حالت_Array_Writeable == pdTRUE ) &&
                    ( ( pul_ڪل_لاڳيتو_وقت == عدم ) || ( x_Is_ڪل_لاڳيتو_وقت_Writeable == pdTRUE ) ) )
                {
                    uxReturn = uxTaskGetSystemState( px_Task_حالت_Array, ux_Array_سائيز, pul_ڪل_لاڳيتو_وقت );
                }
            }

            أرجع uxReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ڍير_مٿاهون_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_Get_ڍير_مٿاهون_Water_Mark( xTask );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_اندروني_Task_Handle != عدم )
                        {
                            uxReturn = ux_Task_Get_ڍير_مٿاهون_Water_Mark( x_اندروني_Task_Handle );
                        }
                    }
                }
            }

            أرجع uxReturn;
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ڍير_مٿاهون_Water_Mark2 == 1 )

        config_ڍير_اونهائي_TYPE MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark2_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_ڍير_اونهائي_TYPE MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark2_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_ڍير_اونهائي_TYPE uxReturn = 0;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_Get_ڍير_مٿاهون_Water_Mark2( xTask );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_اندروني_Task_Handle != عدم )
                        {
                            uxReturn = ux_Task_Get_ڍير_مٿاهون_Water_Mark2( x_اندروني_Task_Handle );
                        }
                    }
                }
            }

            أرجع uxReturn;
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( فراغ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            TaskHandle_t xExternalTaskHandle = عدم;
            int32_t l_اشاريو;

            x_اندروني_Task_Handle = xTaskGetCurrentTaskHandle();

            إذا( x_اندروني_Task_Handle != عدم )
            {
                l_اشاريو = MPU_Get_اشاريو_For_Task_Handle( x_اندروني_Task_Handle );

                إذا( l_اشاريو != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
            }

            أرجع xExternalTaskHandle;
        }

    #جيڪڏهن_پورو /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )

        بنياد_Type_t MPU_xTaskGetSchedulerStateImpl( فراغ ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_xTaskGetSchedulerStateImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = taskSCHEDULER_NOT_STARTED;

            xReturn = xTaskGetSchedulerState();

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_v_Task_سيٽ_وقت_ٻاهريون_State_Impl( وقت_ٻاهريون_t * ثابت px_وقت_ٻاهريون ) PRIVILEGED_FUNCTION;

    فراغ MPU_v_Task_سيٽ_وقت_ٻاهريون_State_Impl( وقت_ٻاهريون_t * ثابت px_وقت_ٻاهريون ) /* PRIVILEGED_FUNCTION */
    {
        بنياد_Type_t x_Is_وقت_ٻاهريون_Writeable = pdFALSE;

        إذا( px_وقت_ٻاهريون != عدم )
        {
            x_Is_وقت_ٻاهريون_Writeable = x_پورٽ_Is_Authorized_منزل_Access_بفر( px_وقت_ٻاهريون,
                                                                   حجم( وقت_ٻاهريون_t ),
                                                                   tskMPU_WRITE_PERMISSION );

            إذا( x_Is_وقت_ٻاهريون_Writeable == pdTRUE )
            {
                v_Task_سيٽ_وقت_ٻاهريون_State( px_وقت_ٻاهريون );
            }
        }
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_Task_Check_For_وقت_ٻاهريون_Impl( وقت_ٻاهريون_t * ثابت px_وقت_ٻاهريون,
                                             TickType_t * ثابت px_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

    بنياد_Type_t MPU_x_Task_Check_For_وقت_ٻاهريون_Impl( وقت_ٻاهريون_t * ثابت px_وقت_ٻاهريون,
                                             TickType_t * ثابت px_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
    {
        بنياد_Type_t xReturn = pdFALSE;
        بنياد_Type_t x_Is_وقت_ٻاهريون_Writeable = pdFALSE;
        بنياد_Type_t x_Is_Ticks_منزل_Wait_Writeable = pdFALSE;

        إذا( ( px_وقت_ٻاهريون != عدم ) && ( px_Ticks_منزل_Wait != عدم ) )
        {
            x_Is_وقت_ٻاهريون_Writeable = x_پورٽ_Is_Authorized_منزل_Access_بفر( px_وقت_ٻاهريون,
                                                                   حجم( وقت_ٻاهريون_t ),
                                                                   tskMPU_WRITE_PERMISSION );
            x_Is_Ticks_منزل_Wait_Writeable = x_پورٽ_Is_Authorized_منزل_Access_بفر( px_Ticks_منزل_Wait,
                                                                       حجم( TickType_t ),
                                                                       tskMPU_WRITE_PERMISSION );

            إذا( ( x_Is_وقت_ٻاهريون_Writeable == pdTRUE ) && ( x_Is_Ticks_منزل_Wait_Writeable == pdTRUE ) )
            {
                xReturn = x_Task_Check_For_وقت_ٻاهريون( px_وقت_ٻاهريون, px_Ticks_منزل_Wait );
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنياد_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_منزل_Notify,
                                           UBaseType_t ux_اشاريو_منزل_Notify,
                                           uint32_t ul_قدر,
                                           eNotifyAction eAction,
                                           uint32_t * pul_اڳيون_Notification_قدر ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyParams_t xParams;

            xParams.x_Task_منزل_Notify = x_Task_منزل_Notify;
            xParams.ux_اشاريو_منزل_Notify = ux_اشاريو_منزل_Notify;
            xParams.ul_قدر = ul_قدر;
            xParams.eAction = eAction;
            xParams.pul_اڳيون_Notification_قدر = pul_اڳيون_Notification_قدر;

            xReturn = MPU_x_Task_Generic_Notify_داخلا( &( xParams ) );

            أرجع xReturn;
        }

        بنياد_Type_t MPU_xTaskGenericNotifyImpl( ثابت xTaskGenericNotifyParams_t * pxParams ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_xTaskGenericNotifyImpl( ثابت xTaskGenericNotifyParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            بنياد_Type_t x_Is_اڳيون_Notification_قدر_Writeable = pdFALSE;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;
            بنياد_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورٽ_Is_Authorized_منزل_Access_بفر( pxParams,
                                                                      حجم( xTaskGenericNotifyParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( ( pxParams->ux_اشاريو_منزل_Notify < configTASK_NOTIFICATION_ARRAY_ENTRIES ) &&
                    ( ( pxParams->eAction == eNoAction ) ||
                      ( pxParams->eAction == e_سيٽ_بٽ ) ||
                      ( pxParams->eAction == eIncrement ) ||
                      ( pxParams->eAction == e_سيٽ_قدر_With_Overwrite ) ||
                      ( pxParams->eAction == e_سيٽ_قدر_Without_Overwrite ) ) )
                {
                    إذا( pxParams->pul_اڳيون_Notification_قدر != عدم )
                    {
                        x_Is_اڳيون_Notification_قدر_Writeable = x_پورٽ_Is_Authorized_منزل_Access_بفر( pxParams->pul_اڳيون_Notification_قدر,
                                                                                                 حجم( uint32_t ),
                                                                                                 tskMPU_WRITE_PERMISSION );
                    }

                    إذا( ( pxParams->pul_اڳيون_Notification_قدر == عدم ) ||
                        ( x_Is_اڳيون_Notification_قدر_Writeable == pdTRUE ) )
                    {
                        l_اشاريو = ( int32_t ) ( pxParams->x_Task_منزل_Notify );

                        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                            إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                            {
                                x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                                إذا( x_اندروني_Task_Handle != عدم )
                                {
                                    xReturn = xTaskGenericNotify( x_اندروني_Task_Handle,
                                                                  pxParams->ux_اشاريو_منزل_Notify,
                                                                  pxParams->ul_قدر,
                                                                  pxParams->eAction,
                                                                  pxParams->pul_اڳيون_Notification_قدر );
                                }
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنياد_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_اشاريو_منزل_Wait_On,
                                               uint32_t ul_بٽ_منزل_Clear_On_داخلا,
                                               uint32_t ul_بٽ_منزل_Clear_On_Exit,
                                               uint32_t * pul_Notification_قدر,
                                               TickType_t x_Ticks_منزل_Wait )
        {
            بنياد_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyWaitParams_t xParams;

            xParams.ux_اشاريو_منزل_Wait_On = ux_اشاريو_منزل_Wait_On;
            xParams.ul_بٽ_منزل_Clear_On_داخلا = ul_بٽ_منزل_Clear_On_داخلا;
            xParams.ul_بٽ_منزل_Clear_On_Exit = ul_بٽ_منزل_Clear_On_Exit;
            xParams.pul_Notification_قدر = pul_Notification_قدر;
            xParams.x_Ticks_منزل_Wait = x_Ticks_منزل_Wait;

            xReturn = MPU_x_Task_Generic_Notify_Wait_داخلا( &( xParams ) );

            أرجع xReturn;
        }

        بنياد_Type_t MPU_xTaskGenericNotifyWaitImpl( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_xTaskGenericNotifyWaitImpl( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            بنياد_Type_t x_Is_Notification_قدر_Writable = pdFALSE;
            بنياد_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورٽ_Is_Authorized_منزل_Access_بفر( pxParams,
                                                                      حجم( xTaskGenericNotifyWaitParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( pxParams->ux_اشاريو_منزل_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
                {
                    إذا( pxParams->pul_Notification_قدر != عدم )
                    {
                        x_Is_Notification_قدر_Writable = x_پورٽ_Is_Authorized_منزل_Access_بفر( pxParams->pul_Notification_قدر,
                                                                                        حجم( uint32_t ),
                                                                                        tskMPU_WRITE_PERMISSION );
                    }

                    إذا( ( pxParams->pul_Notification_قدر == عدم ) ||
                        ( x_Is_Notification_قدر_Writable == pdTRUE ) )
                    {
                        xReturn = xTaskGenericNotifyWait( pxParams->ux_اشاريو_منزل_Wait_On,
                                                          pxParams->ul_بٽ_منزل_Clear_On_داخلا,
                                                          pxParams->ul_بٽ_منزل_Clear_On_Exit,
                                                          pxParams->pul_Notification_قدر,
                                                          pxParams->x_Ticks_منزل_Wait );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_اشاريو_منزل_Wait_On,
                                                  بنياد_Type_t x_Clear_ڳڻپ_On_Exit,
                                                  TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_اشاريو_منزل_Wait_On,
                                                  بنياد_Type_t x_Clear_ڳڻپ_On_Exit,
                                                  TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;

            إذا( ux_اشاريو_منزل_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ulReturn = ulTaskGenericNotifyTake( ux_اشاريو_منزل_Wait_On, x_Clear_ڳڻپ_On_Exit, x_Ticks_منزل_Wait );
            }

            أرجع ulReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنياد_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_اشاريو_منزل_Clear ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_اشاريو_منزل_Clear ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( ux_اشاريو_منزل_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                إذا( xTask == عدم )
                {
                    xReturn = xTaskGenericNotifyStateClear( xTask, ux_اشاريو_منزل_Clear );
                }
                وإلا
                {
                    l_اشاريو = ( int32_t ) xTask;

                    إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                        {
                            x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                            إذا( x_اندروني_Task_Handle != عدم )
                            {
                                xReturn = xTaskGenericNotifyStateClear( x_اندروني_Task_Handle, ux_اشاريو_منزل_Clear );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_اشاريو_منزل_Clear,
                                                        uint32_t ul_بٽ_منزل_Clear ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_اشاريو_منزل_Clear,
                                                        uint32_t ul_بٽ_منزل_Clear ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( ux_اشاريو_منزل_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                إذا( xTask == عدم )
                {
                    ulReturn = ul_Task_Generic_Notify_قدر_Clear( xTask, ux_اشاريو_منزل_Clear, ul_بٽ_منزل_Clear );
                }
                وإلا
                {
                    l_اشاريو = ( int32_t ) xTask;

                    إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                        {
                            x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                            إذا( x_اندروني_Task_Handle != عدم )
                            {
                                ulReturn = ul_Task_Generic_Notify_قدر_Clear( x_اندروني_Task_Handle, ux_اشاريو_منزل_Clear, ul_بٽ_منزل_Clear );
                            }
                        }
                    }
                }
            }

            أرجع ulReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Task APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ورهاست == 1 )

        بنياد_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_ڪوڊ,
                                    ثابت حرف * ثابت pcName,
                                    ثابت config_ڍير_اونهائي_TYPE ux_ڍير_اونهائي,
                                    فراغ * pvParameters,
                                    UBaseType_t ux_ترجيح,
                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                /* xTaskCreate() can only be used to create privileged tasks in MPU port. */
                إذا( ( ux_ترجيح & پورٽ_PRIVILEGE_ٻٽو_انگ ) != 0 )
                {
                    xReturn = xTaskCreate( pv_Task_ڪوڊ, pcName, ux_ڍير_اونهائي, pvParameters, ux_ترجيح, &( x_اندروني_Task_Handle ) );

                    إذا( ( xReturn == pdPASS ) && ( x_اندروني_Task_Handle != عدم ) )
                    {
                        MPU_Store_Task_Handle_At_اشاريو( l_اشاريو, x_اندروني_Task_Handle );

                        إذا( pxCreatedTask != عدم )
                        {
                            *pxCreatedTask = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                        }
                    }
                    وإلا
                    {
                        MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ورهاست == 1 )

        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_ڪوڊ,
                                            ثابت حرف * ثابت pcName,
                                            ثابت config_ڍير_اونهائي_TYPE ux_ڍير_اونهائي,
                                            فراغ * ثابت pvParameters,
                                            UBaseType_t ux_ترجيح,
                                            ڍير_Type_t * ثابت pux_ڍير_بفر,
                                            StaticTask_t * ثابت px_Task_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xExternalTaskHandle = عدم;
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                x_اندروني_Task_Handle = xTaskCreateStatic( px_Task_ڪوڊ, pcName, ux_ڍير_اونهائي, pvParameters, ux_ترجيح, pux_ڍير_بفر, px_Task_بفر );

                إذا( x_اندروني_Task_Handle != عدم )
                {
                    MPU_Store_Task_Handle_At_اشاريو( l_اشاريو, x_اندروني_Task_Handle );

                    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        إذا( ( ux_ترجيح & پورٽ_PRIVILEGE_ٻٽو_انگ ) == 0 )
                        {
                            v_پورٽ_Grant_Access_منزل_Kernel_Object( x_اندروني_Task_Handle, l_اشاريو );
                        }
                    }
                    #جيڪڏهن_پورو

                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع xExternalTaskHandle;
        }

    #جيڪڏهن_پورو /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelete == 1 )

        فراغ MPU_vTaskDelete( TaskHandle_t px_Task_منزل_Delete ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            int32_t l_اشاريو;

            إذا( px_Task_منزل_Delete == عدم )
            {
                x_اندروني_Task_Handle = xTaskGetCurrentTaskHandle();
                l_اشاريو = MPU_Get_اشاريو_For_Task_Handle( x_اندروني_Task_Handle );

                إذا( l_اشاريو != -1 )
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }

                vTaskDelete( x_اندروني_Task_Handle );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) px_Task_منزل_Delete;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Task_Handle != عدم )
                    {
                        MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );
                        vTaskDelete( x_اندروني_Task_Handle );
                    }
                }
            }
        }

    #جيڪڏهن_پورو /* #if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/


    #إذا ( INCLUDE_v_Task_ترجيح_سيٽ == 1 )

        فراغ MPU_v_Task_ترجيح_سيٽ( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_ترجيح ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            int32_t l_اشاريو;

            إذا( pxTask == عدم )
            {
                v_Task_ترجيح_سيٽ( pxTask, ux_New_ترجيح );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) pxTask;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Task_Handle != عدم )
                    {
                        v_Task_ترجيح_سيٽ( x_اندروني_Task_Handle, ux_New_ترجيح );
                    }
                }
            }
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetHandle == 1 )

        TaskHandle_t MPU_xTaskGetHandle( ثابت حرف * pc_Name_منزل_Query ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            TaskHandle_t xExternalTaskHandle = عدم;
            int32_t l_اشاريو;

            x_اندروني_Task_Handle = xTaskGetHandle( pc_Name_منزل_Query );

            إذا( x_اندروني_Task_Handle != عدم )
            {
                l_اشاريو = MPU_Get_اشاريو_For_Task_Handle( x_اندروني_Task_Handle );

                إذا( l_اشاريو != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
            }

            أرجع xExternalTaskHandle;
        }

    #جيڪڏهن_پورو /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/


    #إذا ( config_USE_APPLICATION_TASK_ٽيگ == 1 )

        بنياد_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     فراغ * pvParameter ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Task_Handle != عدم )
                    {
                        xReturn = xTaskCallApplicationTaskHook( x_اندروني_Task_Handle, pvParameter );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ورهاست == 1 )

        بنياد_Type_t MPU_xTaskCreateRestricted( ثابت TaskParameters_t * ثابت pxTaskDefinition,
                                              TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                xReturn = xTaskCreateRestricted( pxTaskDefinition, &( x_اندروني_Task_Handle ) );

                إذا( ( xReturn == pdPASS ) && ( x_اندروني_Task_Handle != عدم ) )
                {
                    MPU_Store_Task_Handle_At_اشاريو( l_اشاريو, x_اندروني_Task_Handle );

                    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        إذا( ( pxTaskDefinition->ux_ترجيح & پورٽ_PRIVILEGE_ٻٽو_انگ ) == 0 )
                        {
                            v_پورٽ_Grant_Access_منزل_Kernel_Object( x_اندروني_Task_Handle, l_اشاريو );
                        }
                    }
                    #جيڪڏهن_پورو

                    إذا( pxCreatedTask != عدم )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                    }
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ورهاست == 1 )

        بنياد_Type_t MPU_xTaskCreateRestrictedStatic( ثابت TaskParameters_t * ثابت pxTaskDefinition,
                                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                xReturn = xTaskCreateRestrictedStatic( pxTaskDefinition, &( x_اندروني_Task_Handle ) );

                إذا( ( xReturn == pdPASS ) && ( x_اندروني_Task_Handle != عدم ) )
                {
                    MPU_Store_Task_Handle_At_اشاريو( l_اشاريو, x_اندروني_Task_Handle );

                    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        إذا( ( pxTaskDefinition->ux_ترجيح & پورٽ_PRIVILEGE_ٻٽو_انگ ) == 0 )
                        {
                            v_پورٽ_Grant_Access_منزل_Kernel_Object( x_اندروني_Task_Handle, l_اشاريو );
                        }
                    }
                    #جيڪڏهن_پورو

                    إذا( pxCreatedTask != عدم )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                    }
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    فراغ MPU_vTaskAllocateMPURegions( TaskHandle_t x_Task_منزل_Modify,
                                      ثابت يادگيري_Region_t * ثابت xRegions ) /* PRIVILEGED_FUNCTION */
    {
        TaskHandle_t x_اندروني_Task_Handle = عدم;
        int32_t l_اشاريو;

        إذا( x_Task_منزل_Modify == عدم )
        {
            vTaskAllocateMPURegions( x_Task_منزل_Modify, xRegions );
        }
        وإلا
        {
            l_اشاريو = ( int32_t ) x_Task_منزل_Modify;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_Task_Handle != عدم )
                {
                    vTaskAllocateMPURegions( x_اندروني_Task_Handle, xRegions );
                }
            }
        }
    }
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ورهاست == 1 )

        بنياد_Type_t MPU_xTaskGetStaticBuffers( TaskHandle_t xTask,
                                              ڍير_Type_t ** ppux_ڍير_بفر,
                                              StaticTask_t ** ppx_Task_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندروني_Task_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t xReturn = pdFALSE;

            إذا( xTask == عدم )
            {
                x_اندروني_Task_Handle = xTaskGetCurrentTaskHandle();
                xReturn = xTaskGetStaticBuffers( x_اندروني_Task_Handle, ppux_ڍير_بفر, ppx_Task_بفر );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Task_Handle != عدم )
                    {
                        xReturn = xTaskGetStaticBuffers( x_اندروني_Task_Handle, ppux_ڍير_بفر, ppx_Task_بفر );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    حرف * MPU_pcTaskGetName( TaskHandle_t x_Task_منزل_Query ) /* PRIVILEGED_FUNCTION */
    {
        حرف * pcReturn = عدم;
        int32_t l_اشاريو;
        TaskHandle_t x_اندروني_Task_Handle = عدم;

        إذا( x_Task_منزل_Query == عدم )
        {
            pcReturn = pcTaskGetName( x_Task_منزل_Query );
        }
        وإلا
        {
            l_اشاريو = ( int32_t ) x_Task_منزل_Query;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_Task_Handle != عدم )
                {
                    pcReturn = pcTaskGetName( x_اندروني_Task_Handle );
                }
            }
        }

        أرجع pcReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_ترجيح_Get == 1 )

        UBaseType_t MPU_ux_Task_ترجيح_Get_From_ISR( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_ترجيح_Get_From_ISR( xTask );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Task_Handle != عدم )
                    {
                        uxReturn = ux_Task_ترجيح_Get_From_ISR( x_اندروني_Task_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #جيڪڏهن_پورو /* #if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_ux_Task_ترجيح_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_بنياد_ترجيح_Get( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_بنياد_ترجيح_Get( xTask );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Task_Handle != عدم )
                    {
                        uxReturn = ux_Task_بنياد_ترجيح_Get( x_اندروني_Task_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #جيڪڏهن_پورو /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_ux_Task_ترجيح_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_بنياد_ترجيح_Get_From_ISR( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_بنياد_ترجيح_Get_From_ISR( xTask );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Task_Handle != عدم )
                    {
                        uxReturn = ux_Task_بنياد_ترجيح_Get_From_ISR( x_اندروني_Task_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #جيڪڏهن_پورو /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

        بنياد_Type_t MPU_xTaskResumeFromISR( TaskHandle_t x_Task_منزل_Resume ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;

            l_اشاريو = ( int32_t ) x_Task_منزل_Resume;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_Task_Handle != عدم )
                {
                    xReturn = xTaskResumeFromISR( x_اندروني_Task_Handle );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )*/
/*---------------------------------------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٽيگ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٽيگ_From_ISR( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = عدم;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                xReturn = x_Task_Get_Application_Task_ٽيگ_From_ISR( xTask );
            }
            وإلا
            {
                l_اشاريو = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Task_Handle != عدم )
                    {
                        xReturn = x_Task_Get_Application_Task_ٽيگ_From_ISR( x_اندروني_Task_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنياد_Type_t MPU_xTaskGenericNotifyFromISR( TaskHandle_t x_Task_منزل_Notify,
                                                  UBaseType_t ux_اشاريو_منزل_Notify,
                                                  uint32_t ul_قدر,
                                                  eNotifyAction eAction,
                                                  uint32_t * pul_اڳيون_Notification_قدر,
                                                  بنياد_Type_t * px_Higher_ترجيح_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;

            l_اشاريو = ( int32_t ) x_Task_منزل_Notify;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_Task_Handle != عدم )
                {
                    xReturn = xTaskGenericNotifyFromISR( x_اندروني_Task_Handle, ux_اشاريو_منزل_Notify, ul_قدر, eAction, pul_اڳيون_Notification_قدر, px_Higher_ترجيح_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        فراغ MPU_vTaskGenericNotifyGiveFromISR( TaskHandle_t x_Task_منزل_Notify,
                                                UBaseType_t ux_اشاريو_منزل_Notify,
                                                بنياد_Type_t * px_Higher_ترجيح_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاريو;
            TaskHandle_t x_اندروني_Task_Handle = عدم;

            l_اشاريو = ( int32_t ) x_Task_منزل_Notify;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_Task_Handle = MPU_Get_Task_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_Task_Handle != عدم )
                {
                    vTaskGenericNotifyGiveFromISR( x_اندروني_Task_Handle, ux_اشاريو_منزل_Notify, px_Higher_ترجيح_Task_Woken );
                }
            }
        }
    #جيڪڏهن_پورو /*#if ( configUSE_TASK_NOTIFICATIONS == 1 )*/
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for queue APIs.                   */
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Generic_Send_Impl( قطار_Handle_t x_قطار,
                                          ثابت فراغ * ثابت pv_شي_منزل_قطار,
                                          TickType_t x_Ticks_منزل_Wait,
                                          بنياد_Type_t xCopyPosition ) PRIVILEGED_FUNCTION;

    بنياد_Type_t MPU_x_قطار_Generic_Send_Impl( قطار_Handle_t x_قطار,
                                          ثابت فراغ * ثابت pv_شي_منزل_قطار,
                                          TickType_t x_Ticks_منزل_Wait,
                                          بنياد_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاريو;
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;
        بنياد_Type_t xReturn = pdFAIL;
        بنياد_Type_t x_Is_شي_منزل_قطار_Readable = pdFALSE;
        بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;
        UBaseType_t ux_قطار_شي_سائيز, ux_قطار_ڊيگهائي;

        l_اشاريو = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
            {
                x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_قطار_Handle != عدم )
                {
                    ux_قطار_شي_سائيز = ux_قطار_Get_قطار_شي_سائيز( x_اندروني_قطار_Handle );
                    ux_قطار_ڊيگهائي = ux_قطار_Get_قطار_ڊيگهائي( x_اندروني_قطار_Handle );

                    إذا( ( !( ( pv_شي_منزل_قطار == عدم ) && ( ux_قطار_شي_سائيز != ( UBaseType_t ) 0U ) ) ) &&
                        ( !( ( xCopyPosition == قطار_OVERWRITE ) && ( ux_قطار_ڊيگهائي != ( UBaseType_t ) 1U ) ) )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                        #جيڪڏهن_پورو
                        )
                    {
                        إذا( pv_شي_منزل_قطار != عدم )
                        {
                            x_Is_شي_منزل_قطار_Readable = x_پورٽ_Is_Authorized_منزل_Access_بفر( pv_شي_منزل_قطار,
                                                                                      ux_قطار_شي_سائيز,
                                                                                      tskMPU_READ_PERMISSION );
                        }

                        إذا( ( pv_شي_منزل_قطار == عدم ) || ( x_Is_شي_منزل_قطار_Readable == pdTRUE ) )
                        {
                            xReturn = x_قطار_Generic_Send( x_اندروني_قطار_Handle, pv_شي_منزل_قطار, x_Ticks_منزل_Wait, xCopyPosition );
                        }
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Messages_انتظار_Impl( ثابت قطار_Handle_t px_قطار ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_قطار_Messages_انتظار_Impl( ثابت قطار_Handle_t px_قطار ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاريو;
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;
        UBaseType_t uxReturn = 0;
        بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;

        l_اشاريو = ( int32_t ) px_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
            {
                x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_قطار_Handle != عدم )
                {
                    uxReturn = ux_قطار_Messages_انتظار( x_اندروني_قطار_Handle );
                }
            }
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Spaces_موجود_Impl( ثابت قطار_Handle_t x_قطار ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_قطار_Spaces_موجود_Impl( ثابت قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاريو;
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;
        UBaseType_t uxReturn = 0;
        بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;

        l_اشاريو = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
            {
                x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_قطار_Handle != عدم )
                {
                    uxReturn = ux_قطار_Spaces_موجود( x_اندروني_قطار_Handle );
                }
            }
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Receive_Impl( قطار_Handle_t px_قطار,
                                      فراغ * ثابت pv_بفر,
                                      TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

    بنياد_Type_t MPU_x_قطار_Receive_Impl( قطار_Handle_t px_قطار,
                                      فراغ * ثابت pv_بفر,
                                      TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاريو;
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;
        بنياد_Type_t xReturn = pdFAIL;
        بنياد_Type_t x_Is_Receive_بفر_Writable = pdFALSE;
        بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;
        UBaseType_t ux_قطار_شي_سائيز;

        l_اشاريو = ( int32_t ) px_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
            {
                x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_قطار_Handle != عدم )
                {
                    ux_قطار_شي_سائيز = ux_قطار_Get_قطار_شي_سائيز( x_اندروني_قطار_Handle );

                    إذا( ( !( ( ( pv_بفر ) == عدم ) && ( ux_قطار_شي_سائيز != ( UBaseType_t ) 0U ) ) )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                        #جيڪڏهن_پورو
                        )
                    {
                        x_Is_Receive_بفر_Writable = x_پورٽ_Is_Authorized_منزل_Access_بفر( pv_بفر,
                                                                                    ux_قطار_شي_سائيز,
                                                                                    tskMPU_WRITE_PERMISSION );

                        إذا( x_Is_Receive_بفر_Writable == pdTRUE )
                        {
                            xReturn = x_قطار_Receive( x_اندروني_قطار_Handle, pv_بفر, x_Ticks_منزل_Wait );
                        }
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Peek_Impl( قطار_Handle_t x_قطار,
                                   فراغ * ثابت pv_بفر,
                                   TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

    بنياد_Type_t MPU_x_قطار_Peek_Impl( قطار_Handle_t x_قطار,
                                   فراغ * ثابت pv_بفر,
                                   TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاريو;
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;
        بنياد_Type_t xReturn = pdFAIL;
        بنياد_Type_t x_Is_Receive_بفر_Writable = pdFALSE;
        UBaseType_t ux_قطار_شي_سائيز;
        بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;

        l_اشاريو = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
            {
                x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_قطار_Handle != عدم )
                {
                    ux_قطار_شي_سائيز = ux_قطار_Get_قطار_شي_سائيز( x_اندروني_قطار_Handle );

                    إذا( ( !( ( ( pv_بفر ) == عدم ) && ( ux_قطار_شي_سائيز != ( UBaseType_t ) 0U ) ) )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                        #جيڪڏهن_پورو
                        )
                    {
                        x_Is_Receive_بفر_Writable = x_پورٽ_Is_Authorized_منزل_Access_بفر( pv_بفر,
                                                                                    ux_قطار_شي_سائيز,
                                                                                    tskMPU_WRITE_PERMISSION );

                        إذا( x_Is_Receive_بفر_Writable == pdTRUE )
                        {
                            xReturn = x_قطار_Peek( x_اندروني_قطار_Handle, pv_بفر, x_Ticks_منزل_Wait );
                        }
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Semaphore_Take_Impl( قطار_Handle_t x_قطار,
                                            TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

    بنياد_Type_t MPU_x_قطار_Semaphore_Take_Impl( قطار_Handle_t x_قطار,
                                            TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاريو;
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;
        بنياد_Type_t xReturn = pdFAIL;
        UBaseType_t ux_قطار_شي_سائيز;
        بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;

        l_اشاريو = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
            {
                x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_قطار_Handle != عدم )
                {
                    ux_قطار_شي_سائيز = ux_قطار_Get_قطار_شي_سائيز( x_اندروني_قطار_Handle );

                    إذا( ( ux_قطار_شي_سائيز == 0U )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                        #جيڪڏهن_پورو
                        )
                    {
                        xReturn = x_قطار_Semaphore_Take( x_اندروني_قطار_Handle, x_Ticks_منزل_Wait );
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder_Impl( قطار_Handle_t xSemaphore ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder_Impl( قطار_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_اندروني_Handle = عدم;
            TaskHandle_t xMutexHolderTaskExternalHandle = عدم;
            int32_t l_اشاريو, l_Mutex_Holder_Task_اشاريو;
            قطار_Handle_t x_اندروني_قطار_Handle = عدم;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;


            l_اشاريو = ( int32_t ) xSemaphore;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
                {
                    x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_قطار_Handle != عدم )
                    {
                        x_Mutex_Holder_Task_اندروني_Handle = x_قطار_Get_Mutex_Holder( x_اندروني_قطار_Handle );

                        إذا( x_Mutex_Holder_Task_اندروني_Handle != عدم )
                        {
                            l_Mutex_Holder_Task_اشاريو = MPU_Get_اشاريو_For_Task_Handle( x_Mutex_Holder_Task_اندروني_Handle );

                            إذا( l_Mutex_Holder_Task_اشاريو != -1 )
                            {
                                xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_منزل_EXTERNAL_اشاريو( l_Mutex_Holder_Task_اشاريو ) );
                            }
                        }
                    }
                }
            }

            أرجع xMutexHolderTaskExternalHandle;
        }

    #جيڪڏهن_پورو /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        بنياد_Type_t MPU_x_قطار_Take_Mutex_Recursive_Impl( قطار_Handle_t xMutex,
                                                     TickType_t x_بلاڪ_وقت ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_x_قطار_Take_Mutex_Recursive_Impl( قطار_Handle_t xMutex,
                                                     TickType_t x_بلاڪ_وقت ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;
            int32_t l_اشاريو;
            قطار_Handle_t x_اندروني_قطار_Handle = عدم;
            UBaseType_t ux_قطار_شي_سائيز;

            l_اشاريو = ( int32_t ) xMutex;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
                {
                    x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_قطار_Handle != عدم )
                    {
                        ux_قطار_شي_سائيز = ux_قطار_Get_قطار_شي_سائيز( x_اندروني_قطار_Handle );

                        إذا( ux_قطار_شي_سائيز == 0 )
                        {
                            xReturn = x_قطار_Take_Mutex_Recursive( x_اندروني_قطار_Handle, x_بلاڪ_وقت );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        بنياد_Type_t MPU_x_قطار_Give_Mutex_Recursive_Impl( قطار_Handle_t xMutex ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_x_قطار_Give_Mutex_Recursive_Impl( قطار_Handle_t xMutex ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;
            int32_t l_اشاريو;
            قطار_Handle_t x_اندروني_قطار_Handle = عدم;

            l_اشاريو = ( int32_t ) xMutex;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
                {
                    x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_قطار_Handle != عدم )
                    {
                        xReturn = x_قطار_Give_Mutex_Recursive( x_اندروني_قطار_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )

        قطار_سيٽ_Member_Handle_t MPU_x_قطار_Select_From_سيٽ_Impl( قطار_سيٽ_Handle_t x_قطار_سيٽ,
                                                            TickType_t x_بلاڪ_وقت_Ticks ) PRIVILEGED_FUNCTION;

        قطار_سيٽ_Member_Handle_t MPU_x_قطار_Select_From_سيٽ_Impl( قطار_سيٽ_Handle_t x_قطار_سيٽ,
                                                            TickType_t x_بلاڪ_وقت_Ticks ) /* PRIVILEGED_FUNCTION */
        {
            قطار_سيٽ_Handle_t x_اندروني_قطار_سيٽ_Handle = عدم;
            قطار_سيٽ_Member_Handle_t x_Selected_Member_اندروني = عدم;
            قطار_سيٽ_Member_Handle_t xSelectedMemberExternal = عدم;
            int32_t l_اشاريو_قطار_سيٽ, l_اشاريو_Selected_Member;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار_سيٽ = pdFALSE;

            l_اشاريو_قطار_سيٽ = ( int32_t ) x_قطار_سيٽ;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو_قطار_سيٽ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار_سيٽ = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو_قطار_سيٽ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار_سيٽ == pdTRUE )
                {
                    x_اندروني_قطار_سيٽ_Handle = MPU_Get_قطار_سيٽ_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو_قطار_سيٽ ) );

                    إذا( x_اندروني_قطار_سيٽ_Handle != عدم )
                    {
                        x_Selected_Member_اندروني = x_قطار_Select_From_سيٽ( x_اندروني_قطار_سيٽ_Handle, x_بلاڪ_وقت_Ticks );

                        إذا( x_Selected_Member_اندروني != عدم )
                        {
                            l_اشاريو_Selected_Member = MPU_Get_اشاريو_For_قطار_سيٽ_Member_Handle( x_Selected_Member_اندروني );

                            إذا( l_اشاريو_Selected_Member != -1 )
                            {
                                xSelectedMemberExternal = ( قطار_سيٽ_Member_Handle_t ) ( CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو_Selected_Member ) );
                            }
                        }
                    }
                }
            }

            أرجع xSelectedMemberExternal;
        }

    #جيڪڏهن_پورو /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )

        بنياد_Type_t MPU_x_قطار_جوڙيو_منزل_سيٽ_Impl( قطار_سيٽ_Member_Handle_t x_قطار_Or_Semaphore,
                                           قطار_سيٽ_Handle_t x_قطار_سيٽ ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_x_قطار_جوڙيو_منزل_سيٽ_Impl( قطار_سيٽ_Member_Handle_t x_قطار_Or_Semaphore,
                                           قطار_سيٽ_Handle_t x_قطار_سيٽ ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            قطار_سيٽ_Member_Handle_t x_اندروني_قطار_سيٽ_Member_Handle = عدم;
            قطار_سيٽ_Handle_t x_اندروني_قطار_سيٽ_Handle = عدم;
            int32_t l_اشاريو_قطار_سيٽ, l_اشاريو_قطار_سيٽ_Member;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار_سيٽ = pdFALSE;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار_سيٽ_Member = pdFALSE;

            l_اشاريو_قطار_سيٽ = ( int32_t ) x_قطار_سيٽ;
            l_اشاريو_قطار_سيٽ_Member = ( int32_t ) x_قطار_Or_Semaphore;

            إذا( ( IS_EXTERNAL_اشاريو_VALID( l_اشاريو_قطار_سيٽ ) != pdFALSE ) &&
                ( IS_EXTERNAL_اشاريو_VALID( l_اشاريو_قطار_سيٽ_Member ) != pdFALSE ) )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار_سيٽ = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو_قطار_سيٽ ) );
                x_Calling_Task_Is_Authorized_منزل_Access_قطار_سيٽ_Member = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو_قطار_سيٽ_Member ) );

                إذا( ( x_Calling_Task_Is_Authorized_منزل_Access_قطار_سيٽ == pdTRUE ) && ( x_Calling_Task_Is_Authorized_منزل_Access_قطار_سيٽ_Member == pdTRUE ) )
                {
                    x_اندروني_قطار_سيٽ_Handle = MPU_Get_قطار_سيٽ_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو_قطار_سيٽ ) );
                    x_اندروني_قطار_سيٽ_Member_Handle = MPU_Get_قطار_سيٽ_Member_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو_قطار_سيٽ_Member ) );

                    إذا( ( x_اندروني_قطار_سيٽ_Handle != عدم ) && ( x_اندروني_قطار_سيٽ_Member_Handle != عدم ) )
                    {
                        xReturn = x_قطار_جوڙيو_منزل_سيٽ( x_اندروني_قطار_سيٽ_Member_Handle, x_اندروني_قطار_سيٽ_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا config_قطار_REGISTRY_سائيز > 0

        فراغ MPU_v_قطار_جوڙيو_منزل_Registry_Impl( قطار_Handle_t x_قطار,
                                          ثابت حرف * pcName ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_قطار_جوڙيو_منزل_Registry_Impl( قطار_Handle_t x_قطار,
                                          ثابت حرف * pcName ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاريو;
            قطار_Handle_t x_اندروني_قطار_Handle = عدم;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;

            l_اشاريو = ( int32_t ) x_قطار;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
                {
                    x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_قطار_Handle != عدم )
                    {
                        v_قطار_جوڙيو_منزل_Registry( x_اندروني_قطار_Handle, pcName );
                    }
                }
            }
        }

    #جيڪڏهن_پورو /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_قطار_REGISTRY_سائيز > 0

        فراغ MPU_v_قطار_Unregister_قطار_Impl( قطار_Handle_t x_قطار ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_قطار_Unregister_قطار_Impl( قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاريو;
            قطار_Handle_t x_اندروني_قطار_Handle = عدم;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;

            l_اشاريو = ( int32_t ) x_قطار;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
                {
                    x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_قطار_Handle != عدم )
                    {
                        v_قطار_Unregister_قطار( x_اندروني_قطار_Handle );
                    }
                }
            }
        }

    #جيڪڏهن_پورو /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_قطار_REGISTRY_سائيز > 0

        ثابت حرف * MPU_pc_قطار_Get_Name_Impl( قطار_Handle_t x_قطار ) PRIVILEGED_FUNCTION;

        ثابت حرف * MPU_pc_قطار_Get_Name_Impl( قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
        {
            ثابت حرف * pcReturn = عدم;
            قطار_Handle_t x_اندروني_قطار_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;

            l_اشاريو = ( int32_t ) x_قطار;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
                {
                    x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_قطار_Handle != عدم )
                    {
                        pcReturn = pc_قطار_Get_Name( x_اندروني_قطار_Handle );
                    }
                }
            }

            أرجع pcReturn;
        }

    #جيڪڏهن_پورو /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Queue APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    فراغ MPU_v_قطار_Delete( قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;
        int32_t l_اشاريو;

        l_اشاريو = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_اندروني_قطار_Handle != عدم )
            {
                v_قطار_Delete( x_اندروني_قطار_Handle );
                MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );
            }
        }
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_ورهاست == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Mutex( ثابت uint8_t uc_قطار_Type ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندروني_قطار_Handle = عدم;
            قطار_Handle_t x_External_قطار_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                x_اندروني_قطار_Handle = x_قطار_Create_Mutex( uc_قطار_Type );

                إذا( x_اندروني_قطار_Handle != عدم )
                {
                    MPU_Store_قطار_Handle_At_اشاريو( l_اشاريو, x_اندروني_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع x_External_قطار_Handle;
        }

    #جيڪڏهن_پورو /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_ورهاست == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Mutex_Static( ثابت uint8_t uc_قطار_Type,
                                                   Static_قطار_t * px_Static_قطار ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندروني_قطار_Handle = عدم;
            قطار_Handle_t x_External_قطار_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                x_اندروني_قطار_Handle = x_قطار_Create_Mutex_Static( uc_قطار_Type, px_Static_قطار );

                إذا( x_اندروني_قطار_Handle != عدم )
                {
                    MPU_Store_قطار_Handle_At_اشاريو( l_اشاريو, x_اندروني_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع x_External_قطار_Handle;
        }

    #جيڪڏهن_پورو /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_ورهاست == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Counting_Semaphore( UBaseType_t ux_ڳڻپ_قدر,
                                                         UBaseType_t ux_Initial_ڳڻپ ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندروني_قطار_Handle = عدم;
            قطار_Handle_t x_External_قطار_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                x_اندروني_قطار_Handle = x_قطار_Create_Counting_Semaphore( ux_ڳڻپ_قدر, ux_Initial_ڳڻپ );

                إذا( x_اندروني_قطار_Handle != عدم )
                {
                    MPU_Store_قطار_Handle_At_اشاريو( l_اشاريو, x_اندروني_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع x_External_قطار_Handle;
        }

    #جيڪڏهن_پورو /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_ورهاست == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Counting_Semaphore_Static( ثابت UBaseType_t ux_Max_ڳڻپ,
                                                               ثابت UBaseType_t ux_Initial_ڳڻپ,
                                                               Static_قطار_t * px_Static_قطار ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندروني_قطار_Handle = عدم;
            قطار_Handle_t x_External_قطار_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                x_اندروني_قطار_Handle = x_قطار_Create_Counting_Semaphore_Static( ux_Max_ڳڻپ, ux_Initial_ڳڻپ, px_Static_قطار );

                إذا( x_اندروني_قطار_Handle != عدم )
                {
                    MPU_Store_قطار_Handle_At_اشاريو( l_اشاريو, x_اندروني_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع x_External_قطار_Handle;
        }

    #جيڪڏهن_پورو /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ورهاست == 1 )

        قطار_Handle_t MPU_x_قطار_Generic_Create( UBaseType_t ux_قطار_ڊيگهائي,
                                               UBaseType_t ux_شي_سائيز,
                                               uint8_t uc_قطار_Type ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندروني_قطار_Handle = عدم;
            قطار_Handle_t x_External_قطار_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                x_اندروني_قطار_Handle = x_قطار_Generic_Create( ux_قطار_ڊيگهائي, ux_شي_سائيز, uc_قطار_Type );

                إذا( x_اندروني_قطار_Handle != عدم )
                {
                    MPU_Store_قطار_Handle_At_اشاريو( l_اشاريو, x_اندروني_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع x_External_قطار_Handle;
        }

    #جيڪڏهن_پورو /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ورهاست == 1 )

        قطار_Handle_t MPU_x_قطار_Generic_Create_Static( ثابت UBaseType_t ux_قطار_ڊيگهائي,
                                                     ثابت UBaseType_t ux_شي_سائيز,
                                                     uint8_t * puc_قطار_Storage,
                                                     Static_قطار_t * px_Static_قطار,
                                                     ثابت uint8_t uc_قطار_Type ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندروني_قطار_Handle = عدم;
            قطار_Handle_t x_External_قطار_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                x_اندروني_قطار_Handle = x_قطار_Generic_Create_Static( ux_قطار_ڊيگهائي, ux_شي_سائيز, puc_قطار_Storage, px_Static_قطار, uc_قطار_Type );

                إذا( x_اندروني_قطار_Handle != عدم )
                {
                    MPU_Store_قطار_Handle_At_اشاريو( l_اشاريو, x_اندروني_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع x_External_قطار_Handle;
        }

    #جيڪڏهن_پورو /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Generic_Reset( قطار_Handle_t x_قطار,
                                       بنياد_Type_t x_New_قطار ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاريو;
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;
        بنياد_Type_t xReturn = pdFAIL;

        l_اشاريو = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_اندروني_قطار_Handle != عدم )
            {
                xReturn = x_قطار_Generic_Reset( x_اندروني_قطار_Handle, x_New_قطار );
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_قطار_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_ورهاست == 1 ) )

        قطار_سيٽ_Handle_t MPU_x_قطار_Create_سيٽ( UBaseType_t ux_Event_قطار_ڊيگهائي ) /* PRIVILEGED_FUNCTION */
        {
            قطار_سيٽ_Handle_t x_اندروني_قطار_سيٽ_Handle = عدم;
            قطار_سيٽ_Handle_t x_External_قطار_سيٽ_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                x_اندروني_قطار_سيٽ_Handle = x_قطار_Create_سيٽ( ux_Event_قطار_ڊيگهائي );

                إذا( x_اندروني_قطار_سيٽ_Handle != عدم )
                {
                    MPU_Store_قطار_سيٽ_Handle_At_اشاريو( l_اشاريو, x_اندروني_قطار_سيٽ_Handle );
                    x_External_قطار_سيٽ_Handle = ( قطار_سيٽ_Handle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع x_External_قطار_سيٽ_Handle;
        }

    #جيڪڏهن_پورو /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_قطار_SETS == 1 ) && ( config_SUPPORT_STATIC_ورهاست == 1 ) )

        قطار_سيٽ_Handle_t MPU_x_قطار_Create_سيٽ_Static( ثابت UBaseType_t ux_Event_قطار_ڊيگهائي,
                                                    uint8_t * puc_قطار_Storage,
                                                    Static_قطار_t * px_Static_قطار ) /* PRIVILEGED_FUNCTION */
        {
            قطار_سيٽ_Handle_t x_اندروني_قطار_سيٽ_Handle = عدم;
            قطار_سيٽ_Handle_t x_External_قطار_سيٽ_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                x_اندروني_قطار_سيٽ_Handle = x_قطار_Create_سيٽ_Static( ux_Event_قطار_ڊيگهائي, puc_قطار_Storage, px_Static_قطار );

                إذا( x_اندروني_قطار_سيٽ_Handle != عدم )
                {
                    MPU_Store_قطار_سيٽ_Handle_At_اشاريو( l_اشاريو, x_اندروني_قطار_سيٽ_Handle );
                    x_External_قطار_سيٽ_Handle = ( قطار_سيٽ_Handle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع x_External_قطار_سيٽ_Handle;
        }

    #جيڪڏهن_پورو /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )

        بنياد_Type_t MPU_x_قطار_Remove_From_سيٽ( قطار_سيٽ_Member_Handle_t x_قطار_Or_Semaphore,
                                            قطار_سيٽ_Handle_t x_قطار_سيٽ ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            قطار_سيٽ_Member_Handle_t x_اندروني_قطار_سيٽ_Member_Handle = عدم;
            قطار_سيٽ_Handle_t x_اندروني_قطار_سيٽ_Handle = عدم;
            int32_t l_اشاريو_قطار_سيٽ, l_اشاريو_قطار_سيٽ_Member;

            l_اشاريو_قطار_سيٽ = ( int32_t ) x_قطار_سيٽ;
            l_اشاريو_قطار_سيٽ_Member = ( int32_t ) x_قطار_Or_Semaphore;

            إذا( ( IS_EXTERNAL_اشاريو_VALID( l_اشاريو_قطار_سيٽ ) != pdFALSE ) &&
                ( IS_EXTERNAL_اشاريو_VALID( l_اشاريو_قطار_سيٽ_Member ) != pdFALSE ) )
            {
                x_اندروني_قطار_سيٽ_Handle = MPU_Get_قطار_سيٽ_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو_قطار_سيٽ ) );
                x_اندروني_قطار_سيٽ_Member_Handle = MPU_Get_قطار_سيٽ_Member_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو_قطار_سيٽ_Member ) );

                إذا( ( x_اندروني_قطار_سيٽ_Handle != عدم ) && ( x_اندروني_قطار_سيٽ_Member_Handle != عدم ) )
                {
                    xReturn = x_قطار_Remove_From_سيٽ( x_اندروني_قطار_سيٽ_Member_Handle, x_اندروني_قطار_سيٽ_Handle );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ورهاست == 1 )

        بنياد_Type_t MPU_x_قطار_Generic_Get_Static_Buffers( قطار_Handle_t x_قطار,
                                                      uint8_t ** ppuc_قطار_Storage,
                                                      Static_قطار_t ** ppx_Static_قطار ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاريو;
            قطار_Handle_t x_اندروني_قطار_Handle = عدم;
            بنياد_Type_t xReturn = pdFALSE;

            l_اشاريو = ( int32_t ) x_قطار;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_قطار_Handle != عدم )
                {
                    xReturn = x_قطار_Generic_Get_Static_Buffers( x_اندروني_قطار_Handle, ppuc_قطار_Storage, ppx_Static_قطار );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /*if ( configSUPPORT_STATIC_ALLOCATION == 1 )*/
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Generic_Send_From_ISR( قطار_Handle_t x_قطار,
                                             ثابت فراغ * ثابت pv_شي_منزل_قطار,
                                             بنياد_Type_t * ثابت px_Higher_ترجيح_Task_Woken,
                                             ثابت بنياد_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        بنياد_Type_t xReturn = pdFAIL;
        int32_t l_اشاريو;
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;

        l_اشاريو = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_اندروني_قطار_Handle != عدم )
            {
                xReturn = x_قطار_Generic_Send_From_ISR( x_اندروني_قطار_Handle, pv_شي_منزل_قطار, px_Higher_ترجيح_Task_Woken, xCopyPosition );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Give_From_ISR( قطار_Handle_t x_قطار,
                                      بنياد_Type_t * ثابت px_Higher_ترجيح_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        بنياد_Type_t xReturn = pdFAIL;
        int32_t l_اشاريو;
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;

        l_اشاريو = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_اندروني_قطار_Handle != عدم )
            {
                xReturn = x_قطار_Give_From_ISR( x_اندروني_قطار_Handle, px_Higher_ترجيح_Task_Woken );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Peek_From_ISR( قطار_Handle_t x_قطار,
                                      فراغ * ثابت pv_بفر ) /* PRIVILEGED_FUNCTION */
    {
        بنياد_Type_t xReturn = pdFAIL;
        int32_t l_اشاريو;
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;

        l_اشاريو = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_اندروني_قطار_Handle != عدم )
            {
                xReturn = x_قطار_Peek_From_ISR( x_اندروني_قطار_Handle, pv_بفر );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Receive_From_ISR( قطار_Handle_t x_قطار,
                                         فراغ * ثابت pv_بفر,
                                         بنياد_Type_t * ثابت px_Higher_ترجيح_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        بنياد_Type_t xReturn = pdFAIL;
        int32_t l_اشاريو;
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;

        l_اشاريو = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_اندروني_قطار_Handle != عدم )
            {
                xReturn = x_قطار_Receive_From_ISR( x_اندروني_قطار_Handle, pv_بفر, px_Higher_ترجيح_Task_Woken );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Is_قطار_خالي_جايون_From_ISR( ثابت قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        بنياد_Type_t xReturn = pdFAIL;
        int32_t l_اشاريو;
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;

        l_اشاريو = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_اندروني_قطار_Handle != عدم )
            {
                xReturn = x_قطار_Is_قطار_خالي_جايون_From_ISR( x_اندروني_قطار_Handle );
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    بنياد_Type_t MPU_x_قطار_Is_قطار_ڀريل_From_ISR( ثابت قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        بنياد_Type_t xReturn = pdFAIL;
        int32_t l_اشاريو;
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;

        l_اشاريو = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_اندروني_قطار_Handle != عدم )
            {
                xReturn = x_قطار_Is_قطار_ڀريل_From_ISR( x_اندروني_قطار_Handle );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Messages_انتظار_From_ISR( ثابت قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn = 0;
        int32_t l_اشاريو;
        قطار_Handle_t x_اندروني_قطار_Handle = عدم;

        l_اشاريو = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_اندروني_قطار_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_اندروني_قطار_Handle != عدم )
            {
                uxReturn = ux_قطار_Messages_انتظار_From_ISR( x_اندروني_قطار_Handle );
            }
        }

        أرجع uxReturn;
    }

/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder_From_ISR( قطار_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_اندروني_Handle = عدم;
            TaskHandle_t xMutexHolderTaskExternalHandle = عدم;
            int32_t l_اشاريو, l_Mutex_Holder_Task_اشاريو;
            قطار_Handle_t x_اندروني_Semaphore_Handle = عدم;

            l_اشاريو = ( int32_t ) xSemaphore;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_Semaphore_Handle = MPU_Get_قطار_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_Semaphore_Handle != عدم )
                {
                    x_Mutex_Holder_Task_اندروني_Handle = x_قطار_Get_Mutex_Holder( x_اندروني_Semaphore_Handle );

                    إذا( x_Mutex_Holder_Task_اندروني_Handle != عدم )
                    {
                        l_Mutex_Holder_Task_اشاريو = MPU_Get_اشاريو_For_Task_Handle( x_Mutex_Holder_Task_اندروني_Handle );

                        إذا( l_Mutex_Holder_Task_اشاريو != -1 )
                        {
                            xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_منزل_EXTERNAL_اشاريو( l_Mutex_Holder_Task_اشاريو ) );
                        }
                    }
                }
            }

            أرجع xMutexHolderTaskExternalHandle;
        }

    #جيڪڏهن_پورو /* #if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )

        قطار_سيٽ_Member_Handle_t MPU_x_قطار_Select_From_سيٽ_From_ISR( قطار_سيٽ_Handle_t x_قطار_سيٽ ) /* PRIVILEGED_FUNCTION */
        {
            قطار_سيٽ_Handle_t x_اندروني_قطار_سيٽ_Handle = عدم;
            قطار_سيٽ_Member_Handle_t x_Selected_Member_اندروني = عدم;
            قطار_سيٽ_Member_Handle_t xSelectedMemberExternal = عدم;
            int32_t l_اشاريو_قطار_سيٽ, l_اشاريو_Selected_Member;

            l_اشاريو_قطار_سيٽ = ( int32_t ) x_قطار_سيٽ;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو_قطار_سيٽ ) != pdFALSE )
            {
                x_اندروني_قطار_سيٽ_Handle = MPU_Get_قطار_سيٽ_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو_قطار_سيٽ ) );

                إذا( x_اندروني_قطار_سيٽ_Handle != عدم )
                {
                    x_Selected_Member_اندروني = x_قطار_Select_From_سيٽ_From_ISR( x_اندروني_قطار_سيٽ_Handle );

                    إذا( x_Selected_Member_اندروني != عدم )
                    {
                        l_اشاريو_Selected_Member = MPU_Get_اشاريو_For_قطار_سيٽ_Member_Handle( x_Selected_Member_اندروني );

                        إذا( l_اشاريو_Selected_Member != -1 )
                        {
                            xSelectedMemberExternal = ( قطار_سيٽ_Member_Handle_t ) ( CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو_Selected_Member ) );
                        }
                    }
                }
            }

            أرجع xSelectedMemberExternal;
        }

    #جيڪڏهن_پورو /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for timers APIs.                  */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ * MPU_pvTimerGetTimerIDImpl( ثابت TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        فراغ * MPU_pvTimerGetTimerIDImpl( ثابت TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            فراغ * pvReturn = عدم;
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاريو = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندروني_Timer_Handle = MPU_Get_Timer_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Timer_Handle != عدم )
                    {
                        pvReturn = pvTimerGetTimerID( x_اندروني_Timer_Handle );
                    }
                }
            }

            أرجع pvReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_سيٽ_Timer_IDImpl( TimerHandle_t xTimer,
                                       فراغ * pvNewID ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Timer_سيٽ_Timer_IDImpl( TimerHandle_t xTimer,
                                       فراغ * pvNewID ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاريو = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندروني_Timer_Handle = MPU_Get_Timer_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Timer_Handle != عدم )
                    {
                        v_Timer_سيٽ_Timer_ID( x_اندروني_Timer_Handle, pvNewID );
                    }
                }
            }
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنياد_Type_t MPU_x_Timer_Is_Timer_سرگرم_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_x_Timer_Is_Timer_سرگرم_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاريو = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندروني_Timer_Handle = MPU_Get_Timer_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Timer_Handle != عدم )
                    {
                        xReturn = x_Timer_Is_Timer_سرگرم( x_اندروني_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( فراغ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xReturn;

            xReturn = xTimerGetTimerDaemonTaskHandle();

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنياد_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ثابت بنياد_Type_t xCommandID,
                                                     ثابت TickType_t x_Optional_قدر,
                                                     بنياد_Type_t * ثابت px_Higher_ترجيح_Task_Woken,
                                                     ثابت TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            بنياد_Type_t xReturn = pdFALSE;
            xTimerGenericCommandFromTaskParams_t xParams;

            xParams.xTimer = xTimer;
            xParams.xCommandID = xCommandID;
            xParams.x_Optional_قدر = x_Optional_قدر;
            xParams.px_Higher_ترجيح_Task_Woken = px_Higher_ترجيح_Task_Woken;
            xParams.x_Ticks_منزل_Wait = x_Ticks_منزل_Wait;

            xReturn = MPU_x_Timer_Generic_Command_From_Task_داخلا( &( xParams ) );

            أرجع xReturn;
        }

        بنياد_Type_t MPU_xTimerGenericCommandFromTaskImpl( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_xTimerGenericCommandFromTaskImpl( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Is_Higher_ترجيح_Task_Woken_Writeable = pdFALSE;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;
            بنياد_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورٽ_Is_Authorized_منزل_Access_بفر( pxParams,
                                                                      حجم( xTimerGenericCommandFromTaskParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( pxParams->xCommandID < tmr_پهريون_FROM_ISR_COMMAND )
                {
                    إذا( pxParams->px_Higher_ترجيح_Task_Woken != عدم )
                    {
                        x_Is_Higher_ترجيح_Task_Woken_Writeable = x_پورٽ_Is_Authorized_منزل_Access_بفر( pxParams->px_Higher_ترجيح_Task_Woken,
                                                                                               حجم( بنياد_Type_t ),
                                                                                               tskMPU_WRITE_PERMISSION );
                    }

                    إذا( ( pxParams->px_Higher_ترجيح_Task_Woken == عدم ) ||
                        ( x_Is_Higher_ترجيح_Task_Woken_Writeable == pdTRUE ) )
                    {
                        l_اشاريو = ( int32_t ) ( pxParams->xTimer );

                        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                            إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                            {
                                x_اندروني_Timer_Handle = MPU_Get_Timer_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                                إذا( x_اندروني_Timer_Handle != عدم )
                                {
                                    xReturn = xTimerGenericCommandFromTask( x_اندروني_Timer_Handle,
                                                                            pxParams->xCommandID,
                                                                            pxParams->x_Optional_قدر,
                                                                            pxParams->px_Higher_ترجيح_Task_Woken,
                                                                            pxParams->x_Ticks_منزل_Wait );
                                }
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ثابت حرف * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ثابت حرف * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ثابت حرف * pcReturn = عدم;
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاريو = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندروني_Timer_Handle = MPU_Get_Timer_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Timer_Handle != عدم )
                    {
                        pcReturn = pcTimerGetName( x_اندروني_Timer_Handle );
                    }
                }
            }

            أرجع pcReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_سيٽ_Reload_گهڻائي_Impl( TimerHandle_t xTimer,
                                          ثابت بنياد_Type_t xAutoReload ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Timer_سيٽ_Reload_گهڻائي_Impl( TimerHandle_t xTimer,
                                          ثابت بنياد_Type_t xAutoReload ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاريو = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندروني_Timer_Handle = MPU_Get_Timer_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Timer_Handle != عدم )
                    {
                        v_Timer_سيٽ_Reload_گهڻائي( x_اندروني_Timer_Handle, xAutoReload );
                    }
                }
            }
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنياد_Type_t MPU_x_Timer_Get_Reload_گهڻائي_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_x_Timer_Get_Reload_گهڻائي_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاريو = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندروني_Timer_Handle = MPU_Get_Timer_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Timer_Handle != عدم )
                    {
                        xReturn = x_Timer_Get_Reload_گهڻائي( x_اندروني_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_گهڻائي_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Timer_Get_Reload_گهڻائي_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاريو = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندروني_Timer_Handle = MPU_Get_Timer_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Timer_Handle != عدم )
                    {
                        uxReturn = ux_Timer_Get_Reload_گهڻائي( x_اندروني_Timer_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاريو = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندروني_Timer_Handle = MPU_Get_Timer_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Timer_Handle != عدم )
                    {
                        xReturn = xTimerGetPeriod( x_اندروني_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_وقت_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_x_Timer_Get_Expiry_وقت_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاريو = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندروني_Timer_Handle = MPU_Get_Timer_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Timer_Handle != عدم )
                    {
                        xReturn = x_Timer_Get_Expiry_وقت( x_اندروني_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Timer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ورهاست == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreate( ثابت حرف * ثابت pcTimerName,
                                        ثابت TickType_t x_Timer_Period_اندريون_Ticks,
                                        ثابت بنياد_Type_t xAutoReload,
                                        فراغ * ثابت pvTimerID,
                                        TimerCallbackFunction_t pxCallbackFunction ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            TimerHandle_t xExternalTimerHandle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                x_اندروني_Timer_Handle = xTimerCreate( pcTimerName, x_Timer_Period_اندريون_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback );

                إذا( x_اندروني_Timer_Handle != عدم )
                {
                    MPU_Store_Timer_Handle_At_اشاريو( l_اشاريو, x_اندروني_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع xExternalTimerHandle;
        }

    #جيڪڏهن_پورو /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ورهاست == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreateStatic( ثابت حرف * ثابت pcTimerName,
                                              ثابت TickType_t x_Timer_Period_اندريون_Ticks,
                                              ثابت بنياد_Type_t xAutoReload,
                                              فراغ * ثابت pvTimerID,
                                              TimerCallbackFunction_t pxCallbackFunction,
                                              StaticTimer_t * px_Timer_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            TimerHandle_t xExternalTimerHandle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                x_اندروني_Timer_Handle = xTimerCreateStatic( pcTimerName, x_Timer_Period_اندريون_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback, px_Timer_بفر );

                إذا( x_اندروني_Timer_Handle != عدم )
                {
                    MPU_Store_Timer_Handle_At_اشاريو( l_اشاريو, x_اندروني_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع xExternalTimerHandle;
        }

    #جيڪڏهن_پورو /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ورهاست == 1 ) && ( configUSE_TIMERS == 1 )

        بنياد_Type_t MPU_x_Timer_Get_Static_بفر( TimerHandle_t xTimer,
                                              StaticTimer_t ** ppx_Timer_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t xReturn = pdFALSE;

            l_اشاريو = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_Timer_Handle = MPU_Get_Timer_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_Timer_Handle != عدم )
                {
                    xReturn = x_Timer_Get_Static_بفر( x_اندروني_Timer_Handle, ppx_Timer_بفر );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنياد_Type_t MPU_xTimerGenericCommandFromISR( TimerHandle_t xTimer,
                                                    ثابت بنياد_Type_t xCommandID,
                                                    ثابت TickType_t x_Optional_قدر,
                                                    بنياد_Type_t * ثابت px_Higher_ترجيح_Task_Woken,
                                                    ثابت TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_Timer_Handle = MPU_Get_Timer_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_Timer_Handle != عدم )
                {
                    xReturn = xTimerGenericCommandFromISR( x_اندروني_Timer_Handle, xCommandID, x_Optional_قدر, px_Higher_ترجيح_Task_Woken, x_Ticks_منزل_Wait );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        بنياد_Type_t MPU_xTimerDelete( TimerHandle_t xTimer, TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندروني_Timer_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_Timer_Handle = MPU_Get_Timer_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_Timer_Handle != عدم )
                {
                    xReturn = xTimerGenericCommandFromTask( x_اندروني_Timer_Handle,
                                                            tmrCOMMAND_DELETE,
                                                            0U, /* xOptionalValue */
                                                            عدم, /* pxHigherPriorityTaskWoken */
                                                            x_Ticks_منزل_Wait );
                    إذا( xReturn != pdFALSE )
                    {
                        MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for event group APIs.              */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بٽ_t MPU_x_Event_گروهه_Wait_بٽ( Event_گروهه_Handle_t x_Event_گروهه,
                                             ثابت Event_بٽ_t ux_بٽ_منزل_Wait_For,
                                             ثابت بنياد_Type_t xClearOnExit,
                                             ثابت بنياد_Type_t x_Wait_For_All_بٽ,
                                             TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٽ_t xReturn = 0;
            x_Event_گروهه_Wait_بٽ_Params_t xParams;

            xParams.x_Event_گروهه = x_Event_گروهه;
            xParams.ux_بٽ_منزل_Wait_For = ux_بٽ_منزل_Wait_For;
            xParams.xClearOnExit = xClearOnExit;
            xParams.x_Wait_For_All_بٽ = x_Wait_For_All_بٽ;
            xParams.x_Ticks_منزل_Wait = x_Ticks_منزل_Wait;

            xReturn = MPU_x_Event_گروهه_Wait_بٽ_داخلا( &( xParams ) );

            أرجع xReturn;
        }

        Event_بٽ_t MPU_x_Event_گروهه_Wait_بٽ_Impl( ثابت x_Event_گروهه_Wait_بٽ_Params_t * pxParams ) PRIVILEGED_FUNCTION;

        Event_بٽ_t MPU_x_Event_گروهه_Wait_بٽ_Impl( ثابت x_Event_گروهه_Wait_بٽ_Params_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٽ_t xReturn = 0;
            Event_گروهه_Handle_t x_اندروني_Event_گروهه_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه = pdFALSE;
            بنياد_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورٽ_Is_Authorized_منزل_Access_بفر( pxParams,
                                                                      حجم( x_Event_گروهه_Wait_بٽ_Params_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( ( ( pxParams->ux_بٽ_منزل_Wait_For & event_EVENT_بٽ_CONTROL_بائيٽون ) == 0U ) &&
                    ( pxParams->ux_بٽ_منزل_Wait_For != 0U )
                    #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                        && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( pxParams->x_Ticks_منزل_Wait != 0U ) ) )
                    #جيڪڏهن_پورو
                    )
                {
                    l_اشاريو = ( int32_t ) ( pxParams->x_Event_گروهه );

                    إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه == pdTRUE )
                        {
                            x_اندروني_Event_گروهه_Handle = MPU_Get_Event_گروهه_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                            إذا( x_اندروني_Event_گروهه_Handle != عدم )
                            {
                                xReturn = x_Event_گروهه_Wait_بٽ( x_اندروني_Event_گروهه_Handle,
                                                               pxParams->ux_بٽ_منزل_Wait_For,
                                                               pxParams->xClearOnExit,
                                                               pxParams->x_Wait_For_All_بٽ,
                                                               pxParams->x_Ticks_منزل_Wait );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بٽ_t MPU_x_Event_گروهه_Clear_بٽ_Impl( Event_گروهه_Handle_t x_Event_گروهه,
                                                  ثابت Event_بٽ_t ux_بٽ_منزل_Clear ) PRIVILEGED_FUNCTION;

        Event_بٽ_t MPU_x_Event_گروهه_Clear_بٽ_Impl( Event_گروهه_Handle_t x_Event_گروهه,
                                                  ثابت Event_بٽ_t ux_بٽ_منزل_Clear ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٽ_t xReturn = 0;
            Event_گروهه_Handle_t x_اندروني_Event_گروهه_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه = pdFALSE;

            إذا( ( ux_بٽ_منزل_Clear & event_EVENT_بٽ_CONTROL_بائيٽون ) == 0U )
            {
                l_اشاريو = ( int32_t ) x_Event_گروهه;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه == pdTRUE )
                    {
                        x_اندروني_Event_گروهه_Handle = MPU_Get_Event_گروهه_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_اندروني_Event_گروهه_Handle != عدم )
                        {
                            xReturn = x_Event_گروهه_Clear_بٽ( x_اندروني_Event_گروهه_Handle, ux_بٽ_منزل_Clear );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بٽ_t MPU_x_Event_گروهه_سيٽ_بٽ_Impl( Event_گروهه_Handle_t x_Event_گروهه,
                                                ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ ) PRIVILEGED_FUNCTION;

        Event_بٽ_t MPU_x_Event_گروهه_سيٽ_بٽ_Impl( Event_گروهه_Handle_t x_Event_گروهه,
                                                ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٽ_t xReturn = 0;
            Event_گروهه_Handle_t x_اندروني_Event_گروهه_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه = pdFALSE;

            إذا( ( ux_بٽ_منزل_سيٽ & event_EVENT_بٽ_CONTROL_بائيٽون ) == 0U )
            {
                l_اشاريو = ( int32_t ) x_Event_گروهه;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه == pdTRUE )
                    {
                        x_اندروني_Event_گروهه_Handle = MPU_Get_Event_گروهه_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_اندروني_Event_گروهه_Handle != عدم )
                        {
                            xReturn = x_Event_گروهه_سيٽ_بٽ( x_اندروني_Event_گروهه_Handle, ux_بٽ_منزل_سيٽ );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بٽ_t MPU_x_Event_گروهه_Sync_Impl( Event_گروهه_Handle_t x_Event_گروهه,
                                             ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ,
                                             ثابت Event_بٽ_t ux_بٽ_منزل_Wait_For,
                                             TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

        Event_بٽ_t MPU_x_Event_گروهه_Sync_Impl( Event_گروهه_Handle_t x_Event_گروهه,
                                             ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ,
                                             ثابت Event_بٽ_t ux_بٽ_منزل_Wait_For,
                                             TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٽ_t xReturn = 0;
            Event_گروهه_Handle_t x_اندروني_Event_گروهه_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه = pdFALSE;

            إذا( ( ( ux_بٽ_منزل_Wait_For & event_EVENT_بٽ_CONTROL_بائيٽون ) == 0U ) &&
                ( ux_بٽ_منزل_Wait_For != 0U )
                #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                    && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                #جيڪڏهن_پورو
                )
            {
                l_اشاريو = ( int32_t ) x_Event_گروهه;

                إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه == pdTRUE )
                    {
                        x_اندروني_Event_گروهه_Handle = MPU_Get_Event_گروهه_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_اندروني_Event_گروهه_Handle != عدم )
                        {
                            xReturn = x_Event_گروهه_Sync( x_اندروني_Event_گروهه_Handle, ux_بٽ_منزل_سيٽ, ux_بٽ_منزل_Wait_For, x_Ticks_منزل_Wait );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_گروهه_Get_عدد_Impl( فراغ * x_Event_گروهه ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Event_گروهه_Get_عدد_Impl( فراغ * x_Event_گروهه ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t xReturn = 0;
            Event_گروهه_Handle_t x_اندروني_Event_گروهه_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه = pdFALSE;

            l_اشاريو = ( int32_t ) x_Event_گروهه;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه == pdTRUE )
                {
                    x_اندروني_Event_گروهه_Handle = MPU_Get_Event_گروهه_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Event_گروهه_Handle != عدم )
                    {
                        xReturn = ux_Event_گروهه_Get_عدد( x_اندروني_Event_گروهه_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        فراغ MPU_v_Event_گروهه_سيٽ_عدد_Impl( فراغ * x_Event_گروهه,
                                           UBaseType_t ux_Event_گروهه_عدد ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Event_گروهه_سيٽ_عدد_Impl( فراغ * x_Event_گروهه,
                                           UBaseType_t ux_Event_گروهه_عدد ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروهه_Handle_t x_اندروني_Event_گروهه_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه = pdFALSE;

            l_اشاريو = ( int32_t ) x_Event_گروهه;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_گروهه == pdTRUE )
                {
                    x_اندروني_Event_گروهه_Handle = MPU_Get_Event_گروهه_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_Event_گروهه_Handle != عدم )
                    {
                        v_Event_گروهه_سيٽ_عدد( x_اندروني_Event_گروهه_Handle, ux_Event_گروهه_عدد );
                    }
                }
            }
        }

    #جيڪڏهن_پورو /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Event Group APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_ورهاست == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_گروهه_Handle_t MPU_x_Event_گروهه_Create( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروهه_Handle_t x_اندروني_Event_گروهه_Handle = عدم;
            Event_گروهه_Handle_t x_External_Event_گروهه_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                x_اندروني_Event_گروهه_Handle = x_Event_گروهه_Create();

                إذا( x_اندروني_Event_گروهه_Handle != عدم )
                {
                    MPU_Store_Event_گروهه_Handle_At_اشاريو( l_اشاريو, x_اندروني_Event_گروهه_Handle );
                    x_External_Event_گروهه_Handle = ( Event_گروهه_Handle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع x_External_Event_گروهه_Handle;
        }

    #جيڪڏهن_پورو /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ورهاست == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_گروهه_Handle_t MPU_x_Event_گروهه_Create_Static( Static_Event_گروهه_t * px_Event_گروهه_بفر ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروهه_Handle_t x_اندروني_Event_گروهه_Handle = عدم;
            Event_گروهه_Handle_t x_External_Event_گروهه_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

            إذا( l_اشاريو != -1 )
            {
                x_اندروني_Event_گروهه_Handle = x_Event_گروهه_Create_Static( px_Event_گروهه_بفر );

                إذا( x_اندروني_Event_گروهه_Handle != عدم )
                {
                    MPU_Store_Event_گروهه_Handle_At_اشاريو( l_اشاريو, x_اندروني_Event_گروهه_Handle );
                    x_External_Event_گروهه_Handle = ( Event_گروهه_Handle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                }
                وإلا
                {
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                }
            }

            أرجع x_External_Event_گروهه_Handle;
        }

    #جيڪڏهن_پورو /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        فراغ MPU_v_Event_گروهه_Delete( Event_گروهه_Handle_t x_Event_گروهه ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروهه_Handle_t x_اندروني_Event_گروهه_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = ( int32_t ) x_Event_گروهه;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_Event_گروهه_Handle = MPU_Get_Event_گروهه_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_Event_گروهه_Handle != عدم )
                {
                    v_Event_گروهه_Delete( x_اندروني_Event_گروهه_Handle );
                    MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );
                }
            }
        }

    #جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ورهاست == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        بنياد_Type_t MPU_x_Event_گروهه_Get_Static_بفر( Event_گروهه_Handle_t x_Event_گروهه,
                                                   Static_Event_گروهه_t ** ppx_Event_گروهه_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            Event_گروهه_Handle_t x_اندروني_Event_گروهه_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = ( int32_t ) x_Event_گروهه;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_Event_گروهه_Handle = MPU_Get_Event_گروهه_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_Event_گروهه_Handle != عدم )
                {
                    xReturn = x_Event_گروهه_Get_Static_بفر( x_اندروني_Event_گروهه_Handle, ppx_Event_گروهه_بفر );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        بنياد_Type_t MPU_x_Event_گروهه_Clear_بٽ_From_ISR( Event_گروهه_Handle_t x_Event_گروهه,
                                                    ثابت Event_بٽ_t ux_بٽ_منزل_Clear ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            Event_گروهه_Handle_t x_اندروني_Event_گروهه_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = ( int32_t ) x_Event_گروهه;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_Event_گروهه_Handle = MPU_Get_Event_گروهه_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_Event_گروهه_Handle != عدم )
                {
                    xReturn = x_Event_گروهه_Clear_بٽ_From_ISR( x_اندروني_Event_گروهه_Handle, ux_بٽ_منزل_Clear );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        بنياد_Type_t MPU_x_Event_گروهه_سيٽ_بٽ_From_ISR( Event_گروهه_Handle_t x_Event_گروهه,
                                                  ثابت Event_بٽ_t ux_بٽ_منزل_سيٽ,
                                                  بنياد_Type_t * px_Higher_ترجيح_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            Event_گروهه_Handle_t x_اندروني_Event_گروهه_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = ( int32_t ) x_Event_گروهه;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_Event_گروهه_Handle = MPU_Get_Event_گروهه_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_Event_گروهه_Handle != عدم )
                {
                    xReturn = x_Event_گروهه_سيٽ_بٽ_From_ISR( x_اندروني_Event_گروهه_Handle, ux_بٽ_منزل_سيٽ, px_Higher_ترجيح_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بٽ_t MPU_x_Event_گروهه_Get_بٽ_From_ISR( Event_گروهه_Handle_t x_Event_گروهه ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٽ_t xReturn = 0;
            Event_گروهه_Handle_t x_اندروني_Event_گروهه_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = ( int32_t ) x_Event_گروهه;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_Event_گروهه_Handle = MPU_Get_Event_گروهه_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_Event_گروهه_Handle != عدم )
                {
                    xReturn = x_Event_گروهه_Get_بٽ_From_ISR( x_اندروني_Event_گروهه_Handle );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for stream buffer APIs.            */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

        size_t MPU_x_وهڪرو_بفر_Send_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                          ثابت فراغ * pv_Tx_معلومات,
                                          size_t x_معلومات_ڊيگهائي_بائيٽون,
                                          TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_وهڪرو_بفر_Send_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                          ثابت فراغ * pv_Tx_معلومات,
                                          size_t x_معلومات_ڊيگهائي_بائيٽون,
                                          TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Is_Tx_معلومات_بفر_Readable = pdFALSE;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = pdFALSE;

            إذا( pv_Tx_معلومات != عدم )
            {
                x_Is_Tx_معلومات_بفر_Readable = x_پورٽ_Is_Authorized_منزل_Access_بفر( pv_Tx_معلومات,
                                                                           x_معلومات_ڊيگهائي_بائيٽون,
                                                                           tskMPU_READ_PERMISSION );

                إذا( x_Is_Tx_معلومات_بفر_Readable == pdTRUE )
                {
                    l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

                    إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر == pdTRUE )
                        {
                            x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                            إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                            {
                                xReturn = x_وهڪرو_بفر_Send( x_اندروني_وهڪرو_بفر_Handle, pv_Tx_معلومات, x_معلومات_ڊيگهائي_بائيٽون, x_Ticks_منزل_Wait );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

        size_t MPU_x_وهڪرو_بفر_Receive_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                             فراغ * pv_Rx_معلومات,
                                             size_t x_بفر_ڊيگهائي_بائيٽون,
                                             TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_وهڪرو_بفر_Receive_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                             فراغ * pv_Rx_معلومات,
                                             size_t x_بفر_ڊيگهائي_بائيٽون,
                                             TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Is_Rx_معلومات_بفر_Writeable = pdFALSE;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = pdFALSE;

            إذا( pv_Rx_معلومات != عدم )
            {
                x_Is_Rx_معلومات_بفر_Writeable = x_پورٽ_Is_Authorized_منزل_Access_بفر( pv_Rx_معلومات,
                                                                            x_بفر_ڊيگهائي_بائيٽون,
                                                                            tskMPU_WRITE_PERMISSION );

                إذا( x_Is_Rx_معلومات_بفر_Writeable == pdTRUE )
                {
                    l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

                    إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر == pdTRUE )
                        {
                            x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                            إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                            {
                                xReturn = x_وهڪرو_بفر_Receive( x_اندروني_وهڪرو_بفر_Handle, pv_Rx_معلومات, x_بفر_ڊيگهائي_بائيٽون, x_Ticks_منزل_Wait );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

        بنياد_Type_t MPU_x_وهڪرو_بفر_Is_ڀريل_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_x_وهڪرو_بفر_Is_ڀريل_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = pdFALSE;

            l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر == pdTRUE )
                {
                    x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                    {
                        xReturn = x_وهڪرو_بفر_Is_ڀريل( x_اندروني_وهڪرو_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

        بنياد_Type_t MPU_x_وهڪرو_بفر_Is_خالي_جايون_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_x_وهڪرو_بفر_Is_خالي_جايون_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = pdFALSE;

            l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر == pdTRUE )
                {
                    x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                    {
                        xReturn = x_وهڪرو_بفر_Is_خالي_جايون( x_اندروني_وهڪرو_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

        size_t MPU_x_وهڪرو_بفر_Spaces_موجود_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_وهڪرو_بفر_Spaces_موجود_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = pdFALSE;

            l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر == pdTRUE )
                {
                    x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                    {
                        xReturn = x_وهڪرو_بفر_Spaces_موجود( x_اندروني_وهڪرو_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

        size_t MPU_x_وهڪرو_بفر_بائيٽون_موجود_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_وهڪرو_بفر_بائيٽون_موجود_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = pdFALSE;

            l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر == pdTRUE )
                {
                    x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                    {
                        xReturn = x_وهڪرو_بفر_بائيٽون_موجود( x_اندروني_وهڪرو_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

        بنياد_Type_t MPU_x_وهڪرو_بفر_سيٽ_Trigger_Level_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                                         size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

        بنياد_Type_t MPU_x_وهڪرو_بفر_سيٽ_Trigger_Level_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                                         size_t xTriggerLevel ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = pdFALSE;

            l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر == pdTRUE )
                {
                    x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                    {
                        xReturn = x_وهڪرو_بفر_سيٽ_Trigger_Level( x_اندروني_وهڪرو_بفر_Handle, xTriggerLevel );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

        size_t MPU_x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون_Impl( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;
            بنياد_Type_t x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = pdFALSE;

            l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر = x_پورٽ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_وهڪرو_بفر == pdTRUE )
                {
                    x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                    إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                    {
                        xReturn = x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون( x_اندروني_وهڪرو_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Stream Buffer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_ورهاست == 1 ) && ( config_USE_وهڪرو_BUFFERS == 1 ) )

        وهڪرو_بفر_Handle_t MPU_x_وهڪرو_بفر_Generic_Create( size_t x_بفر_سائيز_بائيٽون,
                                                             size_t x_Trigger_Level_بائيٽون,
                                                             بنياد_Type_t x_وهڪرو_بفر_Type,
                                                             وهڪرو_بفر_Callback_Function_t pxSendCompletedCallback,
                                                             وهڪرو_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            وهڪرو_بفر_Handle_t x_External_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == عدم ) &&
                          ( pxReceiveCompletedCallback == عدم ) );

            إذا( ( pxSendCompletedCallback == عدم ) &&
                ( pxReceiveCompletedCallback == عدم ) )
            {
                l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

                إذا( l_اشاريو != -1 )
                {
                    x_اندروني_وهڪرو_بفر_Handle = x_وهڪرو_بفر_Generic_Create( x_بفر_سائيز_بائيٽون,
                                                                              x_Trigger_Level_بائيٽون,
                                                                              x_وهڪرو_بفر_Type,
                                                                              عدم,
                                                                              عدم );

                    إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                    {
                        MPU_Store_وهڪرو_بفر_Handle_At_اشاريو( l_اشاريو, x_اندروني_وهڪرو_بفر_Handle );
                        x_External_وهڪرو_بفر_Handle = ( وهڪرو_بفر_Handle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                    }
                    وإلا
                    {
                        MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                    }
                }
            }
            وإلا
            {
                trace_وهڪرو_بفر_CREATE_FAILED( x_وهڪرو_بفر_Type );
                x_External_وهڪرو_بفر_Handle = عدم;
            }

            أرجع x_External_وهڪرو_بفر_Handle;
        }

    #جيڪڏهن_پورو /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ورهاست == 1 ) && ( config_USE_وهڪرو_BUFFERS == 1 ) )

        وهڪرو_بفر_Handle_t MPU_x_وهڪرو_بفر_Generic_Create_Static( size_t x_بفر_سائيز_بائيٽون,
                                                                   size_t x_Trigger_Level_بائيٽون,
                                                                   بنياد_Type_t x_وهڪرو_بفر_Type,
                                                                   uint8_t * ثابت puc_وهڪرو_بفر_Storage_Area,
                                                                   Static_وهڪرو_بفر_t * ثابت px_Static_وهڪرو_بفر,
                                                                   وهڪرو_بفر_Callback_Function_t pxSendCompletedCallback,
                                                                   وهڪرو_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            وهڪرو_بفر_Handle_t x_External_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == عدم ) &&
                          ( pxReceiveCompletedCallback == عدم ) );

            إذا( ( pxSendCompletedCallback == عدم ) &&
                ( pxReceiveCompletedCallback == عدم ) )
            {
                l_اشاريو = MPU_Get_Free_اشاريو_اندريون_Kernel_Object_Pool();

                إذا( l_اشاريو != -1 )
                {
                    x_اندروني_وهڪرو_بفر_Handle = x_وهڪرو_بفر_Generic_Create_Static( x_بفر_سائيز_بائيٽون,
                                                                                    x_Trigger_Level_بائيٽون,
                                                                                    x_وهڪرو_بفر_Type,
                                                                                    puc_وهڪرو_بفر_Storage_Area,
                                                                                    px_Static_وهڪرو_بفر,
                                                                                    عدم,
                                                                                    عدم );

                    إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                    {
                        MPU_Store_وهڪرو_بفر_Handle_At_اشاريو( l_اشاريو, x_اندروني_وهڪرو_بفر_Handle );
                        x_External_وهڪرو_بفر_Handle = ( وهڪرو_بفر_Handle_t ) CONVERT_منزل_EXTERNAL_اشاريو( l_اشاريو );
                    }
                    وإلا
                    {
                        MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( l_اشاريو );
                    }
                }
            }
            وإلا
            {
                trace_وهڪرو_بفر_CREATE_STATIC_FAILED( xReturn, x_وهڪرو_بفر_Type );
                x_External_وهڪرو_بفر_Handle = عدم;
            }

            أرجع x_External_وهڪرو_بفر_Handle;
        }

    #جيڪڏهن_پورو /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

        فراغ MPU_v_وهڪرو_بفر_Delete( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* PRIVILEGED_FUNCTION */
        {
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                {
                    v_وهڪرو_بفر_Delete( x_اندروني_وهڪرو_بفر_Handle );
                }

                MPU_سيٽ_اشاريو_Free_اندريون_Kernel_Object_Pool( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );
            }
        }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

        بنياد_Type_t MPU_x_وهڪرو_بفر_Reset( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                {
                    xReturn = x_وهڪرو_بفر_Reset( x_اندروني_وهڪرو_بفر_Handle );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ورهاست == 1 ) && ( config_USE_وهڪرو_BUFFERS == 1 ) )

        بنياد_Type_t MPU_x_وهڪرو_بفر_Get_Static_Buffers( وهڪرو_بفر_Handle_t x_وهڪرو_Buffers,
                                                      uint8_t * ppuc_وهڪرو_بفر_Storage_Area,
                                                      Static_وهڪرو_بفر_t * ppx_Static_وهڪرو_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = ( int32_t ) x_وهڪرو_Buffers;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                {
                    xReturn = MPU_x_وهڪرو_بفر_Get_Static_Buffers( x_اندروني_وهڪرو_بفر_Handle, ppuc_وهڪرو_بفر_Storage_Area, ppx_Static_وهڪرو_بفر );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

    size_t MPU_x_وهڪرو_بفر_Send_From_ISR( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                         ثابت فراغ * pv_Tx_معلومات,
                                         size_t x_معلومات_ڊيگهائي_بائيٽون,
                                         بنياد_Type_t * ثابت px_Higher_ترجيح_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
        int32_t l_اشاريو;

        l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
            {
                xReturn = x_وهڪرو_بفر_Send_From_ISR( x_اندروني_وهڪرو_بفر_Handle, pv_Tx_معلومات, x_معلومات_ڊيگهائي_بائيٽون, px_Higher_ترجيح_Task_Woken );
            }
        }

        أرجع xReturn;
    }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

    size_t MPU_x_وهڪرو_بفر_Receive_From_ISR( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                            فراغ * pv_Rx_معلومات,
                                            size_t x_بفر_ڊيگهائي_بائيٽون,
                                            بنياد_Type_t * ثابت px_Higher_ترجيح_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
        int32_t l_اشاريو;

        l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

        إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
        {
            x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

            إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
            {
                xReturn = x_وهڪرو_بفر_Receive_From_ISR( x_اندروني_وهڪرو_بفر_Handle, pv_Rx_معلومات, x_بفر_ڊيگهائي_بائيٽون, px_Higher_ترجيح_Task_Woken );
            }
        }

        أرجع xReturn;
    }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

        بنياد_Type_t MPU_x_وهڪرو_بفر_Send_Completed_From_ISR( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                                          بنياد_Type_t * px_Higher_ترجيح_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                {
                    xReturn = x_وهڪرو_بفر_Send_Completed_From_ISR( x_اندروني_وهڪرو_بفر_Handle, px_Higher_ترجيح_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

        بنياد_Type_t MPU_x_وهڪرو_بفر_Receive_Completed_From_ISR( وهڪرو_بفر_Handle_t x_وهڪرو_بفر,
                                                             بنياد_Type_t * px_Higher_ترجيح_Task_Woken ) /*PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFALSE;
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                {
                    xReturn = x_وهڪرو_بفر_Receive_Completed_From_ISR( x_اندروني_وهڪرو_بفر_Handle, px_Higher_ترجيح_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

    #إذا ( config_USE_وهڪرو_BUFFERS == 1 )

        بنياد_Type_t MPU_x_وهڪرو_بفر_Reset_From_ISR( وهڪرو_بفر_Handle_t x_وهڪرو_بفر ) /*PRIVILEGED_FUNCTION */
        {
            بنياد_Type_t xReturn = pdFAIL;
            وهڪرو_بفر_Handle_t x_اندروني_وهڪرو_بفر_Handle = عدم;
            int32_t l_اشاريو;

            l_اشاريو = ( int32_t ) x_وهڪرو_بفر;

            إذا( IS_EXTERNAL_اشاريو_VALID( l_اشاريو ) != pdFALSE )
            {
                x_اندروني_وهڪرو_بفر_Handle = MPU_Get_وهڪرو_بفر_Handle_At_اشاريو( CONVERT_منزل_اندروني_اشاريو( l_اشاريو ) );

                إذا( x_اندروني_وهڪرو_بفر_Handle != عدم )
                {
                    xReturn = x_وهڪرو_بفر_Reset_From_ISR( x_اندروني_وهڪرو_بفر_Handle );
                }
            }

            أرجع xReturn;
        }

    #جيڪڏهن_پورو /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h. */

    #إذا configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #ضمن "application_defined_privileged_functions.h"
    #جيڪڏهن_پورو
/*-----------------------------------------------------------*/

/**
 * @brief Array of system call implementation functions.
 *
 * The index in the array MUST match the corresponding system call number
 * defined in mpu_wrappers.h.
 */
    PRIVILEGED_معلومات UBaseType_t uxSystemCallImplementations[ انگ_SYSTEM_CALLS ] =
    {
        #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_xTaskGenericNotifyImpl,                     /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyWaitImpl,                 /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #جيڪڏهن_پورو

        #إذا ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_xTimerGenericCommandFromTaskImpl,           /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #جيڪڏهن_پورو

        #إذا ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_گروهه_Wait_بٽ_Impl,                    /* SYSTEM_CALL_xEventGroupWaitBits. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupWaitBits. */
        #جيڪڏهن_پورو

        /* The system calls above this line take 5 parameters. */

        #إذا ( INCLUDE_xTaskDelayUntil == 1 )
            ( UBaseType_t ) MPU_xTaskDelayUntilImpl,                        /* SYSTEM_CALL_xTaskDelayUntil. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskDelayUntil. */
        #جيڪڏهن_پورو

        #إذا ( INCLUDE_xTaskAbortDelay == 1 )
            ( UBaseType_t ) MPU_xTaskAbortDelayImpl,                        /* SYSTEM_CALL_xTaskAbortDelay. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskAbortDelay. */
        #جيڪڏهن_پورو

        #إذا ( INCLUDE_vTaskDelay == 1 )
            ( UBaseType_t ) MPU_vTaskDelayImpl,                             /* SYSTEM_CALL_vTaskDelay. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskDelay. */
        #جيڪڏهن_پورو

        #إذا ( INCLUDE_ux_Task_ترجيح_Get == 1 )
            ( UBaseType_t ) MPU_ux_Task_ترجيح_Get_Impl,                      /* SYSTEM_CALL_uxTaskPriorityGet. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskPriorityGet. */
        #جيڪڏهن_پورو

        #إذا ( INCLUDE_eTaskGetState == 1 )
            ( UBaseType_t ) MPU_eTaskGetStateImpl,                          /* SYSTEM_CALL_eTaskGetState. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_eTaskGetState. */
        #جيڪڏهن_پورو

        #إذا ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_vTaskGetInfoImpl,                           /* SYSTEM_CALL_vTaskGetInfo. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskGetInfo. */
        #جيڪڏهن_پورو

        #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
            ( UBaseType_t ) MPU_xTaskGetIdleTaskHandleImpl,                 /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #جيڪڏهن_پورو

        #إذا ( INCLUDE_vTaskSuspend == 1 )
            ( UBaseType_t ) MPU_vTaskSuspendImpl,                           /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) MPU_vTaskResumeImpl,                            /* SYSTEM_CALL_vTaskResume. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskResume. */
        #جيڪڏهن_پورو

        ( UBaseType_t ) MPU_x_Task_Get_Tick_ڳڻپ_Impl,                          /* SYSTEM_CALL_xTaskGetTickCount. */
        ( UBaseType_t ) MPU_ux_Task_Get_عدد_جو_Tasks_Impl,                     /* SYSTEM_CALL_uxTaskGetNumberOfTasks. */

        #إذا ( config_GENERATE_لاڳيتو_وقت_STATS == 1 )
            ( UBaseType_t ) MPU_ul_Task_Get_لاڳيتو_وقت_Counter_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) MPU_ul_Task_Get_لاڳيتو_وقت_Percent_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #جيڪڏهن_پورو

        #إذا ( ( config_GENERATE_لاڳيتو_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Percent_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_لاڳيتو_وقت_Counter_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #جيڪڏهن_پورو

        #إذا ( config_USE_APPLICATION_TASK_ٽيگ == 1 )
            ( UBaseType_t ) MPU_v_Task_سيٽ_Application_Task_ٽيگ_Impl,             /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) MPU_x_Task_Get_Application_Task_ٽيگ_Impl,             /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #جيڪڏهن_پورو

        #إذا ( config_انگ_THREAD_LOCAL_STORAGE_اشارا != 0 )
            ( UBaseType_t ) MPU_v_Task_سيٽ_Thread_Local_Storage_اشارو_Impl,      /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) MPU_pv_Task_Get_Thread_Local_Storage_اشارو_Impl,     /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #جيڪڏهن_پورو

        #إذا ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_uxTaskGetSystemStateImpl,                   /* SYSTEM_CALL_uxTaskGetSystemState. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetSystemState. */
        #جيڪڏهن_پورو

        #إذا ( INCLUDE_ux_Task_Get_ڍير_مٿاهون_Water_Mark == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark_Impl,            /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #جيڪڏهن_پورو

        #إذا ( INCLUDE_ux_Task_Get_ڍير_مٿاهون_Water_Mark2 == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ڍير_مٿاهون_Water_Mark2_Impl,           /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #جيڪڏهن_پورو

        #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )
            ( UBaseType_t ) MPU_xTaskGetCurrentTaskHandleImpl,              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #جيڪڏهن_پورو

        #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )
            ( UBaseType_t ) MPU_xTaskGetSchedulerStateImpl,                 /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #جيڪڏهن_پورو

        ( UBaseType_t ) MPU_v_Task_سيٽ_وقت_ٻاهريون_State_Impl,                       /* SYSTEM_CALL_vTaskSetTimeOutState. */
        ( UBaseType_t ) MPU_x_Task_Check_For_وقت_ٻاهريون_Impl,                       /* SYSTEM_CALL_xTaskCheckForTimeOut. */

        #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_ulTaskGenericNotifyTakeImpl,                /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyStateClearImpl,           /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) MPU_ul_Task_Generic_Notify_قدر_Clear_Impl,          /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #جيڪڏهن_پورو

        ( UBaseType_t ) MPU_x_قطار_Generic_Send_Impl,                          /* SYSTEM_CALL_xQueueGenericSend. */
        ( UBaseType_t ) MPU_ux_قطار_Messages_انتظار_Impl,                     /* SYSTEM_CALL_uxQueueMessagesWaiting. */
        ( UBaseType_t ) MPU_ux_قطار_Spaces_موجود_Impl,                     /* SYSTEM_CALL_uxQueueSpacesAvailable. */
        ( UBaseType_t ) MPU_x_قطار_Receive_Impl,                              /* SYSTEM_CALL_xQueueReceive. */
        ( UBaseType_t ) MPU_x_قطار_Peek_Impl,                                 /* SYSTEM_CALL_xQueuePeek. */
        ( UBaseType_t ) MPU_x_قطار_Semaphore_Take_Impl,                        /* SYSTEM_CALL_xQueueSemaphoreTake. */

        #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
            ( UBaseType_t ) MPU_x_قطار_Get_Mutex_Holder_Impl,                   /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #جيڪڏهن_پورو

        #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )
            ( UBaseType_t ) MPU_x_قطار_Take_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) MPU_x_قطار_Give_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #جيڪڏهن_پورو

        #إذا ( config_USE_قطار_SETS == 1 )
            ( UBaseType_t ) MPU_x_قطار_Select_From_سيٽ_Impl,                    /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) MPU_x_قطار_جوڙيو_منزل_سيٽ_Impl,                         /* SYSTEM_CALL_xQueueAddToSet. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueAddToSet. */
        #جيڪڏهن_پورو

        #إذا config_قطار_REGISTRY_سائيز > 0
            ( UBaseType_t ) MPU_v_قطار_جوڙيو_منزل_Registry_Impl,                    /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) MPU_v_قطار_Unregister_قطار_Impl,                  /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) MPU_pc_قطار_Get_Name_Impl,                         /* SYSTEM_CALL_pcQueueGetName. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcQueueGetName. */
        #جيڪڏهن_پورو

        #إذا ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_pvTimerGetTimerIDImpl,                      /* SYSTEM_CALL_pvTimerGetTimerID. */
            ( UBaseType_t ) MPU_v_Timer_سيٽ_Timer_IDImpl,                       /* SYSTEM_CALL_vTimerSetTimerID. */
            ( UBaseType_t ) MPU_x_Timer_Is_Timer_سرگرم_Impl,                    /* SYSTEM_CALL_xTimerIsTimerActive. */
            ( UBaseType_t ) MPU_xTimerGetTimerDaemonTaskHandleImpl,         /* SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle. */
            ( UBaseType_t ) MPU_pcTimerGetNameImpl,                         /* SYSTEM_CALL_pcTimerGetName. */
            ( UBaseType_t ) MPU_v_Timer_سيٽ_Reload_گهڻائي_Impl,                    /* SYSTEM_CALL_vTimerSetReloadMode. */
            ( UBaseType_t ) MPU_x_Timer_Get_Reload_گهڻائي_Impl,                    /* SYSTEM_CALL_xTimerGetReloadMode. */
            ( UBaseType_t ) MPU_ux_Timer_Get_Reload_گهڻائي_Impl,                   /* SYSTEM_CALL_uxTimerGetReloadMode. */
            ( UBaseType_t ) MPU_xTimerGetPeriodImpl,                        /* SYSTEM_CALL_xTimerGetPeriod. */
            ( UBaseType_t ) MPU_x_Timer_Get_Expiry_وقت_Impl,                    /* SYSTEM_CALL_xTimerGetExpiryTime. */
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
        #جيڪڏهن_پورو

        #إذا ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_گروهه_Clear_بٽ_Impl,                   /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) MPU_x_Event_گروهه_سيٽ_بٽ_Impl,                     /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) MPU_x_Event_گروهه_Sync_Impl,                        /* SYSTEM_CALL_xEventGroupSync. */

            #إذا ( configUSE_TRACE_FACILITY == 1 )
                ( UBaseType_t ) MPU_ux_Event_گروهه_Get_عدد_Impl,              /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) MPU_v_Event_گروهه_سيٽ_عدد_Impl,               /* SYSTEM_CALL_vEventGroupSetNumber. */
            #وإلا
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_vEventGroupSetNumber. */
            #جيڪڏهن_پورو
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSync. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxEventGroupGetNumber. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vEventGroupSetNumber. */
        #جيڪڏهن_پورو

        #إذا ( config_USE_وهڪرو_BUFFERS == 1 )
            ( UBaseType_t ) MPU_x_وهڪرو_بفر_Send_Impl,                      /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) MPU_x_وهڪرو_بفر_Receive_Impl,                   /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) MPU_x_وهڪرو_بفر_Is_ڀريل_Impl,                    /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) MPU_x_وهڪرو_بفر_Is_خالي_جايون_Impl,                   /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) MPU_x_وهڪرو_بفر_Spaces_موجود_Impl,           /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) MPU_x_وهڪرو_بفر_بائيٽون_موجود_Impl,            /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) MPU_x_وهڪرو_بفر_سيٽ_Trigger_Level_Impl,           /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) MPU_x_وهڪرو_بفر_ايندڙ_پيغام_ڊيگهائي_بائيٽون_Impl     /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #جيڪڏهن_پورو

    };
/*-----------------------------------------------------------*/

#جيڪڏهن_پورو /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/
