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
#تعریف_کرو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "queue.h"
#ضمن "timers.h"
#ضمن "event_groups.h"
#ضمن "stream_buffer.h"
#ضمن "mpu_prototypes.h"
#ضمن "mpu_syscall_numbers.h"

#تعریف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#إذا ( ( پورٹ_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #جے_بنا_تعریف config_PROTECTED_KERNEL_OBJECT_POOL_ناپ
        #غلطی config_PROTECTED_KERNEL_OBJECT_POOL_ناپ must be defined منزل ودھ_توں_ودھ نمبر دا kernel objects وچ the application.
    #جے_انت

/**
 * @brief Offset added to the index before returning to the user.
 *
 * If the actual handle is stored at index i, ( i + INDEX_OFFSET )
 * is returned to the user.
 */
    #تعریف_کرو اشاریہ_وتھ    1

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
        OpaqueObjectHandle_t x_اندرونی_Object_Handle;
        uint32_t ulKernelObjectType;
        فراغ * pv_Kernel_Object_انکڑے;
    } KernelObject_t;

/**
 * @brief Kernel object types.
 */
    #تعریف_کرو KERNEL_OBJECT_TYPE_INVALID          ( 0UL )
    #تعریف_کرو KERNEL_OBJECT_TYPE_قطار            ( 1UL )
    #تعریف_کرو KERNEL_OBJECT_TYPE_TASK             ( 2UL )
    #تعریف_کرو KERNEL_OBJECT_TYPE_دھارا_بفر    ( 3UL )
    #تعریف_کرو KERNEL_OBJECT_TYPE_EVENT_گروہ      ( 4UL )
    #تعریف_کرو KERNEL_OBJECT_TYPE_TIMER            ( 5UL )

/**
 * @brief Checks whether an external index is valid or not.
 */
    #تعریف_کرو IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ )   \
    ( ( ( ( l_اشاریہ ) >= اشاریہ_وتھ ) &&       \
        ( ( l_اشاریہ ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_ناپ + اشاریہ_وتھ ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Checks whether an internal index is valid or not.
 */
    #تعریف_کرو IS_اندرونی_اشاریہ_VALID( l_اشاریہ )   \
    ( ( ( ( l_اشاریہ ) >= 0 ) &&                  \
        ( ( l_اشاریہ ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_ناپ ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Converts an internal index into external.
 */
    #تعریف_کرو CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ )    ( ( l_اشاریہ ) + اشاریہ_وتھ )

/**
 * @brief Converts an external index into internal.
 */
    #تعریف_کرو CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ )    ( ( l_اشاریہ ) - اشاریہ_وتھ )

/**
 * @brief Max value that fits in a UBaseType_t type.
 */
    #تعریف_کرو mpuUBASETYPE_MAX    ( ~( ( UBaseType_t ) 0 ) )

/**
 * @brief Check if multiplying a and b will result in overflow.
 */
    #تعریف_کرو mpu_MULTIPLY_BASETYPE_WILL_حد_توں_ودھ( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( mpuUBASETYPE_MAX / ( a ) ) ) )

/**
 * @brief Get the index of a free slot in the kernel object pool.
 *
 * If a free slot is found, this function marks the slot as
 * "not free".
 *
 * @return Index of a free slot is returned, if a free slot is
 *         found. Otherwise -1 is returned.
 */
    ساكن int32_t MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Set the given index as free in the kernel object pool.
 *
 * @param lIndex The index to set as free.
 */
    ساكن فراغ MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( int32_t l_اشاریہ ) PRIVILEGED_FUNCTION;

/**
 * @brief Get the index at which a given kernel object is stored.
 *
 * @param xHandle The given kernel object handle.
 * @param ulKernelObjectType The kernel object type.
 *
 * @return Index at which the kernel object is stored if it is a valid
 *         handle, -1 otherwise.
 */
    ساكن int32_t MPU_Get_اشاریہ_For_Handle( OpaqueObjectHandle_t xHandle,
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
    ساكن فراغ MPU_Store_Handle_And_انکڑے_At_اشاریہ( int32_t l_اشاریہ,
                                               OpaqueObjectHandle_t xHandle,
                                               فراغ * pv_Kernel_Object_انکڑے,
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
    ساكن OpaqueObjectHandle_t MPU_Get_Handle_At_اشاریہ( int32_t l_اشاریہ,
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
        ساكن فراغ MPU_TimerCallback( TimerHandle_t x_اندرونی_Handle ) PRIVILEGED_FUNCTION;

    #جے_انت /* #if ( configUSE_TIMERS == 1 ) */

/*
 * Wrappers to keep all the casting in one place.
 */
    #تعریف_کرو MPU_Store_قطار_Handle_At_اشاریہ( l_اشاریہ, xHandle )                 MPU_Store_Handle_And_انکڑے_At_اشاریہ( ( l_اشاریہ ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_قطار )
    #تعریف_کرو MPU_Get_قطار_Handle_At_اشاریہ( l_اشاریہ )                            ( قطار_Handle_t ) MPU_Get_Handle_At_اشاریہ( ( l_اشاریہ ), KERNEL_OBJECT_TYPE_قطار )

    #إذا ( config_USE_قطار_SETS == 1 )
        #تعریف_کرو MPU_Store_قطار_سیٹ_Handle_At_اشاریہ( l_اشاریہ, xHandle )          MPU_Store_Handle_And_انکڑے_At_اشاریہ( ( l_اشاریہ ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_قطار )
        #تعریف_کرو MPU_Get_قطار_سیٹ_Handle_At_اشاریہ( l_اشاریہ )                     ( قطار_سیٹ_Handle_t ) MPU_Get_Handle_At_اشاریہ( ( l_اشاریہ ), KERNEL_OBJECT_TYPE_قطار )
        #تعریف_کرو MPU_Store_قطار_سیٹ_Member_Handle_At_اشاریہ( l_اشاریہ, xHandle )    MPU_Store_Handle_And_انکڑے_At_اشاریہ( ( l_اشاریہ ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_قطار )
        #تعریف_کرو MPU_Get_قطار_سیٹ_Member_Handle_At_اشاریہ( l_اشاریہ )               ( قطار_سیٹ_Member_Handle_t ) MPU_Get_Handle_At_اشاریہ( ( l_اشاریہ ), KERNEL_OBJECT_TYPE_قطار )
        #تعریف_کرو MPU_Get_اشاریہ_For_قطار_سیٹ_Member_Handle( xHandle )             MPU_Get_اشاریہ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_قطار )
    #جے_انت

/*
 * Wrappers to keep all the casting in one place for Task APIs.
 */
    #تعریف_کرو MPU_Store_Task_Handle_At_اشاریہ( l_اشاریہ, xHandle )            MPU_Store_Handle_And_انکڑے_At_اشاریہ( ( l_اشاریہ ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_TASK )
    #تعریف_کرو MPU_Get_Task_Handle_At_اشاریہ( l_اشاریہ )                       ( TaskHandle_t ) MPU_Get_Handle_At_اشاریہ( ( l_اشاریہ ), KERNEL_OBJECT_TYPE_TASK )
    #تعریف_کرو MPU_Get_اشاریہ_For_Task_Handle( xHandle )                     MPU_Get_اشاریہ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TASK )

    #إذا ( configUSE_EVENT_GROUPS == 1 )
/*
 * Wrappers to keep all the casting in one place for Event Group APIs.
 */
        #تعریف_کرو MPU_Store_Event_گروہ_Handle_At_اشاریہ( l_اشاریہ, xHandle )      MPU_Store_Handle_And_انکڑے_At_اشاریہ( ( l_اشاریہ ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_EVENT_گروہ )
        #تعریف_کرو MPU_Get_Event_گروہ_Handle_At_اشاریہ( l_اشاریہ )                 ( Event_گروہ_Handle_t ) MPU_Get_Handle_At_اشاریہ( ( l_اشاریہ ), KERNEL_OBJECT_TYPE_EVENT_گروہ )
        #تعریف_کرو MPU_Get_اشاریہ_For_Event_گروہ_Handle( xHandle )               MPU_Get_اشاریہ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_EVENT_گروہ )

    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */

    #إذا ( config_USE_دھارا_BUFFERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Stream Buffer APIs.
 */
        #تعریف_کرو MPU_Store_دھارا_بفر_Handle_At_اشاریہ( l_اشاریہ, xHandle )    MPU_Store_Handle_And_انکڑے_At_اشاریہ( ( l_اشاریہ ), ( OpaqueObjectHandle_t ) ( xHandle), عدم, KERNEL_OBJECT_TYPE_دھارا_بفر )
        #تعریف_کرو MPU_Get_دھارا_بفر_Handle_At_اشاریہ( l_اشاریہ )               ( دھارا_بفر_Handle_t ) MPU_Get_Handle_At_اشاریہ( ( l_اشاریہ ), KERNEL_OBJECT_TYPE_دھارا_بفر )
        #تعریف_کرو MPU_Get_اشاریہ_For_دھارا_بفر_Handle( xHandle )             MPU_Get_اشاریہ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_دھارا_بفر )

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

    #إذا ( configUSE_TIMERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Timer APIs.
 */
        #تعریف_کرو MPU_Store_Timer_Handle_At_اشاریہ( l_اشاریہ, xHandle, pxApplicationCallback )    MPU_Store_Handle_And_انکڑے_At_اشاریہ( ( l_اشاریہ ), ( OpaqueObjectHandle_t ) ( xHandle ), ( فراغ * ) ( pxApplicationCallback ), KERNEL_OBJECT_TYPE_TIMER )
        #تعریف_کرو MPU_Get_Timer_Handle_At_اشاریہ( l_اشاریہ )                                      ( TimerHandle_t ) MPU_Get_Handle_At_اشاریہ( ( l_اشاریہ ), KERNEL_OBJECT_TYPE_TIMER )
        #تعریف_کرو MPU_Get_اشاریہ_For_Timer_Handle( xHandle )                                    MPU_Get_اشاریہ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TIMER )

    #جے_انت /* #if ( configUSE_TIMERS == 1 ) */

/*-----------------------------------------------------------*/

/**
 * @brief Kernel object pool.
 */
    PRIVILEGED_انکڑے ساكن KernelObject_t xKernelObjectPool[ config_PROTECTED_KERNEL_OBJECT_POOL_ناپ ] = { 0 };
/*-----------------------------------------------------------*/

    ساكن int32_t MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_Free_اشاریہ = -1;

        /* This function is called only from resource create APIs
         * which are not supposed to be called from ISRs. Therefore,
         * we only need to suspend the scheduler and do not require
         * critical section. */
        vTaskSuspendAll();
        {
            لكل( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_ناپ; i++ )
            {
                إذا( xKernelObjectPool[ i ].x_اندرونی_Object_Handle == عدم )
                {
                    /* Mark this index as not free. */
                    xKernelObjectPool[ i ].x_اندرونی_Object_Handle = ( OpaqueObjectHandle_t ) ( ~0U );
                    l_Free_اشاریہ = i;
                    اكسر;
                }
            }
        }
        ( فراغ ) xTaskResumeAll();

        أرجع l_Free_اشاریہ;
    }
/*-----------------------------------------------------------*/

    ساكن فراغ MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( int32_t l_اشاریہ ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_اندرونی_اشاریہ_VALID( l_اشاریہ ) != pdFALSE );

        taskENTER_CRITICAL();
        {
            xKernelObjectPool[ l_اشاریہ ].x_اندرونی_Object_Handle = عدم;
            xKernelObjectPool[ l_اشاریہ ].ulKernelObjectType = KERNEL_OBJECT_TYPE_INVALID;
            xKernelObjectPool[ l_اشاریہ ].pv_Kernel_Object_انکڑے = عدم;
        }
        taskEXIT_CRITICAL();
    }
/*-----------------------------------------------------------*/

    ساكن int32_t MPU_Get_اشاریہ_For_Handle( OpaqueObjectHandle_t xHandle,
                                          uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_اشاریہ = -1;

        configASSERT( xHandle != عدم );

        لكل( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_ناپ; i++ )
        {
            إذا( ( xKernelObjectPool[ i ].x_اندرونی_Object_Handle == xHandle ) &&
                ( xKernelObjectPool[ i ].ulKernelObjectType == ulKernelObjectType ) )
            {
                l_اشاریہ = i;
                اكسر;
            }
        }

        أرجع l_اشاریہ;
    }
/*-----------------------------------------------------------*/

    ساكن فراغ MPU_Store_Handle_And_انکڑے_At_اشاریہ( int32_t l_اشاریہ,
                                               OpaqueObjectHandle_t xHandle,
                                               فراغ * pv_Kernel_Object_انکڑے,
                                               uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_اندرونی_اشاریہ_VALID( l_اشاریہ ) != pdFALSE );
        xKernelObjectPool[ l_اشاریہ ].x_اندرونی_Object_Handle = xHandle;
        xKernelObjectPool[ l_اشاریہ ].ulKernelObjectType = ulKernelObjectType;
        xKernelObjectPool[ l_اشاریہ ].pv_Kernel_Object_انکڑے = pv_Kernel_Object_انکڑے;
    }
/*-----------------------------------------------------------*/

    ساكن OpaqueObjectHandle_t MPU_Get_Handle_At_اشاریہ( int32_t l_اشاریہ,
                                                      uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        OpaqueObjectHandle_t xObjectHandle = عدم;

        configASSERT( IS_اندرونی_اشاریہ_VALID( l_اشاریہ ) != pdFALSE );

        إذا( xKernelObjectPool[ l_اشاریہ ].ulKernelObjectType == ulKernelObjectType )
        {
            xObjectHandle = xKernelObjectPool[ l_اشاریہ ].x_اندرونی_Object_Handle;
        }

        أرجع xObjectHandle;
    }
/*-----------------------------------------------------------*/

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        فراغ v_Grant_Access_منزل_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                         int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;

            إذا( IS_EXTERNAL_اشاریہ_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                إذا( xExternalTaskHandle == عدم )
                {
                    v_پورٹ_Grant_Access_منزل_Kernel_Object( xExternalTaskHandle, CONVERT_منزل_اندرونی_اشاریہ( lExternalKernelObjectHandle ) );
                }
                وإلا
                {
                    l_External_Task_اشاریہ = ( int32_t ) xExternalTaskHandle;

                    إذا( IS_EXTERNAL_اشاریہ_VALID( l_External_Task_اشاریہ ) != pdFALSE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_External_Task_اشاریہ ) );

                        إذا( x_اندرونی_Task_Handle != عدم )
                        {
                            v_پورٹ_Grant_Access_منزل_Kernel_Object( x_اندرونی_Task_Handle,
                                                            CONVERT_منزل_اندرونی_اشاریہ( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #جے_انت /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        فراغ v_Revoke_Access_منزل_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                          int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;

            إذا( IS_EXTERNAL_اشاریہ_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                إذا( xExternalTaskHandle == عدم )
                {
                    v_پورٹ_Revoke_Access_منزل_Kernel_Object( xExternalTaskHandle, CONVERT_منزل_اندرونی_اشاریہ( lExternalKernelObjectHandle ) );
                }
                وإلا
                {
                    l_External_Task_اشاریہ = ( int32_t ) xExternalTaskHandle;

                    إذا( IS_EXTERNAL_اشاریہ_VALID( l_External_Task_اشاریہ ) != pdFALSE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_External_Task_اشاریہ ) );

                        إذا( x_اندرونی_Task_Handle != عدم )
                        {
                            v_پورٹ_Revoke_Access_منزل_Kernel_Object( x_اندرونی_Task_Handle,
                                                             CONVERT_منزل_اندرونی_اشاریہ( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #جے_انت /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ساكن فراغ MPU_TimerCallback( TimerHandle_t x_اندرونی_Handle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t i, l_اشاریہ = -1;
            TimerHandle_t xExternalHandle = عدم;
            TimerCallbackFunction_t px_Application_Call_پٹھ = عدم;

            /* Coming from the timer task and therefore, should be valid. */
            configASSERT( x_اندرونی_Handle != عدم );

            لكل( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_ناپ; i++ )
            {
                إذا( ( ( TimerHandle_t ) xKernelObjectPool[ i ].x_اندرونی_Object_Handle == x_اندرونی_Handle ) &&
                    ( xKernelObjectPool[ i ].ulKernelObjectType == KERNEL_OBJECT_TYPE_TIMER ) )
                {
                    l_اشاریہ = i;
                    اكسر;
                }
            }

            configASSERT( l_اشاریہ != -1 );
            xExternalHandle = ( TimerHandle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );

            px_Application_Call_پٹھ = ( TimerCallbackFunction_t ) xKernelObjectPool[ l_اشاریہ ].pv_Kernel_Object_انکڑے;
            px_Application_Call_پٹھ( xExternalHandle );
        }

    #جے_انت /* #if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for tasks APIs.                   */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskDelayUntil == 1 )

        ادھار_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ثابت px_پچھلا_Wake_ویلا,
                                            TickType_t x_ویلا_Increment ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ثابت px_پچھلا_Wake_ویلا,
                                            TickType_t x_ویلا_Increment ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            ادھار_Type_t x_Is_پچھلا_Wake_ویلا_Accessible = pdFALSE;

            إذا( ( px_پچھلا_Wake_ویلا != عدم ) && ( x_ویلا_Increment > 0U ) )
            {
                x_Is_پچھلا_Wake_ویلا_Accessible = x_پورٹ_Is_Authorized_منزل_Access_بفر( px_پچھلا_Wake_ویلا,
                                                                                 حجم( TickType_t ),
                                                                                 ( tskMPU_WRITE_PERMISSION | tskMPU_READ_PERMISSION ) );

                إذا( x_Is_پچھلا_Wake_ویلا_Accessible == pdTRUE )
                {
                    xReturn = xTaskDelayUntil( px_پچھلا_Wake_ویلا, x_ویلا_Increment );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskAbortDelay == 1 )

        ادھار_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) xTask;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Task_Handle != عدم )
                    {
                        xReturn = xTaskAbortDelay( x_اندرونی_Task_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelay == 1 )

        فراغ MPU_vTaskDelayImpl( TickType_t x_Ticks_منزل_Delay ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskDelayImpl( TickType_t x_Ticks_منزل_Delay ) /* PRIVILEGED_FUNCTION */
        {
            vTaskDelay( x_Ticks_منزل_Delay );
        }

    #جے_انت /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_ترجیح_Get == 1 )

        UBaseType_t MPU_ux_Task_ترجیح_Get_Impl( ثابت TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_ترجیح_Get_Impl( ثابت TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;

            إذا( pxTask == عدم )
            {
                uxReturn = ux_Task_ترجیح_Get( pxTask );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) pxTask;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_اندرونی_Task_Handle != عدم )
                        {
                            uxReturn = ux_Task_ترجیح_Get( x_اندرونی_Task_Handle );
                        }
                    }
                }
            }

            أرجع uxReturn;
        }

    #جے_انت /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            eTaskState eReturn = eInvalid;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            l_اشاریہ = ( int32_t ) pxTask;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Task_Handle != عدم )
                    {
                        eReturn = eTaskGetState( x_اندرونی_Task_Handle );
                    }
                }
            }

            أرجع eReturn;
        }

    #جے_انت /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        فراغ MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_حالت_t * px_Task_حالت,
                                   ادھار_Type_t x_Get_Free_ڈھیر_Space,
                                   eTaskState eState ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_حالت_t * px_Task_حالت,
                                   ادھار_Type_t x_Get_Free_ڈھیر_Space,
                                   eTaskState eState ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            ادھار_Type_t x_Is_Task_حالت_Writeable = pdFALSE;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            x_Is_Task_حالت_Writeable = x_پورٹ_Is_Authorized_منزل_Access_بفر( px_Task_حالت,
                                                                      حجم( Task_حالت_t ),
                                                                      tskMPU_WRITE_PERMISSION );

            إذا( x_Is_Task_حالت_Writeable == pdTRUE )
            {
                إذا( xTask == عدم )
                {
                    vTaskGetInfo( xTask, px_Task_حالت, x_Get_Free_ڈھیر_Space, eState );
                }
                وإلا
                {
                    l_اشاریہ = ( int32_t ) xTask;

                    إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                        {
                            x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                            إذا( x_اندرونی_Task_Handle != عدم )
                            {
                                vTaskGetInfo( x_اندرونی_Task_Handle, px_Task_حالت, x_Get_Free_ڈھیر_Space, eState );
                            }
                        }
                    }
                }
            }
        }

    #جے_انت /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( فراغ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xIdleTaskHandle = عدم;

            xIdleTaskHandle = xTaskGetIdleTaskHandle();

            أرجع xIdleTaskHandle;
        }

    #جے_انت /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )

        فراغ MPU_vTaskSuspendImpl( TaskHandle_t px_Task_منزل_Suspend ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskSuspendImpl( TaskHandle_t px_Task_منزل_Suspend ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( px_Task_منزل_Suspend == عدم )
            {
                vTaskSuspend( px_Task_منزل_Suspend );
            }
            وإلا
            {
                /* After the scheduler starts, only privileged tasks are allowed
                 * to suspend other tasks. */
                #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )
                    إذا( ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) || ( پورٹ_IS_TASK_PRIVILEGED() == pdTRUE ) )
                #وإلا
                    إذا( پورٹ_IS_TASK_PRIVILEGED() == pdTRUE )
                #جے_انت
                {
                    l_اشاریہ = ( int32_t ) px_Task_منزل_Suspend;

                    إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                        {
                            x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                            إذا( x_اندرونی_Task_Handle != عدم )
                            {
                                vTaskSuspend( x_اندرونی_Task_Handle );
                            }
                        }
                    }
                }
            }
        }

    #جے_انت /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )

        فراغ MPU_vTaskResumeImpl( TaskHandle_t px_Task_منزل_Resume ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskResumeImpl( TaskHandle_t px_Task_منزل_Resume ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            l_اشاریہ = ( int32_t ) px_Task_منزل_Resume;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Task_Handle != عدم )
                    {
                        vTaskResume( x_اندرونی_Task_Handle );
                    }
                }
            }
        }

    #جے_انت /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_گنتی_Impl( فراغ ) PRIVILEGED_FUNCTION;

    TickType_t MPU_x_Task_Get_Tick_گنتی_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        TickType_t xReturn;

        xReturn = x_Task_Get_Tick_گنتی();

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_نمبر_دا_Tasks_Impl( فراغ ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Task_Get_نمبر_دا_Tasks_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn;

        uxReturn = ux_Task_Get_نمبر_دا_Tasks();

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_لگاتار_ویلا_STATS == 1 )

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_لگاتار_ویلا_Counter_Impl( ثابت TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_لگاتار_ویلا_Counter_Impl( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_لگاتار_ویلا_COUNTER_TYPE xReturn = 0;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                xReturn = ul_Task_Get_لگاتار_ویلا_Counter( xTask );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_اندرونی_Task_Handle != عدم )
                        {
                            xReturn = ul_Task_Get_لگاتار_ویلا_Counter( x_اندرونی_Task_Handle );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_لگاتار_ویلا_STATS == 1 )

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_لگاتار_ویلا_Percent_Impl( ثابت TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_لگاتار_ویلا_Percent_Impl( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_لگاتار_ویلا_COUNTER_TYPE xReturn = 0;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                xReturn = ul_Task_Get_لگاتار_ویلا_Percent( xTask );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_اندرونی_Task_Handle != عدم )
                        {
                            xReturn = ul_Task_Get_لگاتار_ویلا_Percent( x_اندرونی_Task_Handle );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_لگاتار_ویلا_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_Idle_لگاتار_ویلا_Percent_Impl( فراغ ) PRIVILEGED_FUNCTION;

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_Idle_لگاتار_ویلا_Percent_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            config_لگاتار_ویلا_COUNTER_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_لگاتار_ویلا_Percent();

            أرجع xReturn;
        }

    #جے_انت /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_لگاتار_ویلا_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_Idle_لگاتار_ویلا_Counter_Impl( فراغ ) PRIVILEGED_FUNCTION;

        config_لگاتار_ویلا_COUNTER_TYPE MPU_ul_Task_Get_Idle_لگاتار_ویلا_Counter_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            config_لگاتار_ویلا_COUNTER_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_لگاتار_ویلا_Counter();

            أرجع xReturn;
        }

    #جے_انت /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٹیگ == 1 )

        فراغ MPU_v_Task_سیٹ_Application_Task_ٹیگ_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_ٹیگ_قدر ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Task_سیٹ_Application_Task_ٹیگ_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_ٹیگ_قدر ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                v_Task_سیٹ_Application_Task_ٹیگ( xTask, px_ٹیگ_قدر );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_اندرونی_Task_Handle != عدم )
                        {
                            v_Task_سیٹ_Application_Task_ٹیگ( x_اندرونی_Task_Handle, px_ٹیگ_قدر );
                        }
                    }
                }
            }
        }

    #جے_انت /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٹیگ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٹیگ_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٹیگ_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = عدم;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                xReturn = x_Task_Get_Application_Task_ٹیگ( xTask );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_اندرونی_Task_Handle != عدم )
                        {
                            xReturn = x_Task_Get_Application_Task_ٹیگ( x_اندرونی_Task_Handle );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_عدد_THREAD_LOCAL_STORAGE_سوچکاں != 0 )

        فراغ MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر_Impl( TaskHandle_t x_Task_منزل_سیٹ,
                                                        ادھار_Type_t x_اشاریہ,
                                                        فراغ * pv_قدر ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر_Impl( TaskHandle_t x_Task_منزل_سیٹ,
                                                        ادھار_Type_t x_اشاریہ,
                                                        فراغ * pv_قدر ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( x_Task_منزل_سیٹ == عدم )
            {
                v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( x_Task_منزل_سیٹ, x_اشاریہ, pv_قدر );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) x_Task_منزل_سیٹ;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_اندرونی_Task_Handle != عدم )
                        {
                            v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( x_اندرونی_Task_Handle, x_اشاریہ, pv_قدر );
                        }
                    }
                }
            }
        }

    #جے_انت /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_عدد_THREAD_LOCAL_STORAGE_سوچکاں != 0 )

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر_Impl( TaskHandle_t x_Task_منزل_Query,
                                                           ادھار_Type_t x_اشاریہ ) PRIVILEGED_FUNCTION;

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر_Impl( TaskHandle_t x_Task_منزل_Query,
                                                           ادھار_Type_t x_اشاریہ ) /* PRIVILEGED_FUNCTION */
        {
            فراغ * pvReturn = عدم;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( x_Task_منزل_Query == عدم )
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_اشارہ_گر( x_Task_منزل_Query, x_اشاریہ );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) x_Task_منزل_Query;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_اندرونی_Task_Handle != عدم )
                        {
                            pvReturn = pv_Task_Get_Thread_Local_Storage_اشارہ_گر( x_اندرونی_Task_Handle, x_اشاریہ );
                        }
                    }
                }
            }

            أرجع pvReturn;
        }

    #جے_انت /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_حالت_t * px_Task_حالت_Array,
                                                  UBaseType_t ux_Array_ناپ,
                                                  config_لگاتار_ویلا_COUNTER_TYPE * pul_کل_لگاتار_ویلا ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_حالت_t * px_Task_حالت_Array,
                                                  UBaseType_t ux_Array_ناپ,
                                                  config_لگاتار_ویلا_COUNTER_TYPE * pul_کل_لگاتار_ویلا ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            ادھار_Type_t x_Is_Task_حالت_Array_Writeable = pdFALSE;
            ادھار_Type_t x_Is_کل_لگاتار_ویلا_Writeable = pdFALSE;

            إذا( mpu_MULTIPLY_BASETYPE_WILL_حد_توں_ودھ( حجم( Task_حالت_t ), ux_Array_ناپ ) == 0 )
            {
                x_Is_Task_حالت_Array_Writeable = x_پورٹ_Is_Authorized_منزل_Access_بفر( px_Task_حالت_Array,
                                                                               حجم( Task_حالت_t ) * ( size_t ) ux_Array_ناپ,
                                                                               tskMPU_WRITE_PERMISSION );

                إذا( pul_کل_لگاتار_ویلا != عدم )
                {
                    x_Is_کل_لگاتار_ویلا_Writeable = x_پورٹ_Is_Authorized_منزل_Access_بفر( pul_کل_لگاتار_ویلا,
                                                                                حجم( config_لگاتار_ویلا_COUNTER_TYPE ),
                                                                                tskMPU_WRITE_PERMISSION );
                }

                إذا( ( x_Is_Task_حالت_Array_Writeable == pdTRUE ) &&
                    ( ( pul_کل_لگاتار_ویلا == عدم ) || ( x_Is_کل_لگاتار_ویلا_Writeable == pdTRUE ) ) )
                {
                    uxReturn = uxTaskGetSystemState( px_Task_حالت_Array, ux_Array_ناپ, pul_کل_لگاتار_ویلا );
                }
            }

            أرجع uxReturn;
        }

    #جے_انت /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark( xTask );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_اندرونی_Task_Handle != عدم )
                        {
                            uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark( x_اندرونی_Task_Handle );
                        }
                    }
                }
            }

            أرجع uxReturn;
        }

    #جے_انت /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark2 == 1 )

        config_ڈھیر_ڈونگھائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_ڈھیر_ڈونگھائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_ڈھیر_ڈونگھائی_TYPE uxReturn = 0;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark2( xTask );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_اندرونی_Task_Handle != عدم )
                        {
                            uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark2( x_اندرونی_Task_Handle );
                        }
                    }
                }
            }

            أرجع uxReturn;
        }

    #جے_انت /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( فراغ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            TaskHandle_t xExternalTaskHandle = عدم;
            int32_t l_اشاریہ;

            x_اندرونی_Task_Handle = xTaskGetCurrentTaskHandle();

            إذا( x_اندرونی_Task_Handle != عدم )
            {
                l_اشاریہ = MPU_Get_اشاریہ_For_Task_Handle( x_اندرونی_Task_Handle );

                إذا( l_اشاریہ != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
            }

            أرجع xExternalTaskHandle;
        }

    #جے_انت /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )

        ادھار_Type_t MPU_xTaskGetSchedulerStateImpl( فراغ ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_xTaskGetSchedulerStateImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = taskSCHEDULER_NOT_STARTED;

            xReturn = xTaskGetSchedulerState();

            أرجع xReturn;
        }

    #جے_انت /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_v_Task_سیٹ_ویلا_باہرلا_State_Impl( ویلا_باہرلا_t * ثابت px_ویلا_باہرلا ) PRIVILEGED_FUNCTION;

    فراغ MPU_v_Task_سیٹ_ویلا_باہرلا_State_Impl( ویلا_باہرلا_t * ثابت px_ویلا_باہرلا ) /* PRIVILEGED_FUNCTION */
    {
        ادھار_Type_t x_Is_ویلا_باہرلا_Writeable = pdFALSE;

        إذا( px_ویلا_باہرلا != عدم )
        {
            x_Is_ویلا_باہرلا_Writeable = x_پورٹ_Is_Authorized_منزل_Access_بفر( px_ویلا_باہرلا,
                                                                   حجم( ویلا_باہرلا_t ),
                                                                   tskMPU_WRITE_PERMISSION );

            إذا( x_Is_ویلا_باہرلا_Writeable == pdTRUE )
            {
                v_Task_سیٹ_ویلا_باہرلا_State( px_ویلا_باہرلا );
            }
        }
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_Task_Check_For_ویلا_باہرلا_Impl( ویلا_باہرلا_t * ثابت px_ویلا_باہرلا,
                                             TickType_t * ثابت px_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

    ادھار_Type_t MPU_x_Task_Check_For_ویلا_باہرلا_Impl( ویلا_باہرلا_t * ثابت px_ویلا_باہرلا,
                                             TickType_t * ثابت px_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
    {
        ادھار_Type_t xReturn = pdFALSE;
        ادھار_Type_t x_Is_ویلا_باہرلا_Writeable = pdFALSE;
        ادھار_Type_t x_Is_Ticks_منزل_Wait_Writeable = pdFALSE;

        إذا( ( px_ویلا_باہرلا != عدم ) && ( px_Ticks_منزل_Wait != عدم ) )
        {
            x_Is_ویلا_باہرلا_Writeable = x_پورٹ_Is_Authorized_منزل_Access_بفر( px_ویلا_باہرلا,
                                                                   حجم( ویلا_باہرلا_t ),
                                                                   tskMPU_WRITE_PERMISSION );
            x_Is_Ticks_منزل_Wait_Writeable = x_پورٹ_Is_Authorized_منزل_Access_بفر( px_Ticks_منزل_Wait,
                                                                       حجم( TickType_t ),
                                                                       tskMPU_WRITE_PERMISSION );

            إذا( ( x_Is_ویلا_باہرلا_Writeable == pdTRUE ) && ( x_Is_Ticks_منزل_Wait_Writeable == pdTRUE ) )
            {
                xReturn = x_Task_Check_For_ویلا_باہرلا( px_ویلا_باہرلا, px_Ticks_منزل_Wait );
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        ادھار_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_منزل_Notify,
                                           UBaseType_t ux_اشاریہ_منزل_Notify,
                                           uint32_t ul_قدر,
                                           eNotifyAction eAction,
                                           uint32_t * pul_پچھلا_Notification_قدر ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyParams_t xParams;

            xParams.x_Task_منزل_Notify = x_Task_منزل_Notify;
            xParams.ux_اشاریہ_منزل_Notify = ux_اشاریہ_منزل_Notify;
            xParams.ul_قدر = ul_قدر;
            xParams.eAction = eAction;
            xParams.pul_پچھلا_Notification_قدر = pul_پچھلا_Notification_قدر;

            xReturn = MPU_x_Task_Generic_Notify_اندراج( &( xParams ) );

            أرجع xReturn;
        }

        ادھار_Type_t MPU_xTaskGenericNotifyImpl( ثابت xTaskGenericNotifyParams_t * pxParams ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_xTaskGenericNotifyImpl( ثابت xTaskGenericNotifyParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            ادھار_Type_t x_Is_پچھلا_Notification_قدر_Writeable = pdFALSE;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;
            ادھار_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورٹ_Is_Authorized_منزل_Access_بفر( pxParams,
                                                                      حجم( xTaskGenericNotifyParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( ( pxParams->ux_اشاریہ_منزل_Notify < configTASK_NOTIFICATION_ARRAY_ENTRIES ) &&
                    ( ( pxParams->eAction == eNoAction ) ||
                      ( pxParams->eAction == e_سیٹ_بٹ ) ||
                      ( pxParams->eAction == eIncrement ) ||
                      ( pxParams->eAction == e_سیٹ_قدر_With_Overwrite ) ||
                      ( pxParams->eAction == e_سیٹ_قدر_Without_Overwrite ) ) )
                {
                    إذا( pxParams->pul_پچھلا_Notification_قدر != عدم )
                    {
                        x_Is_پچھلا_Notification_قدر_Writeable = x_پورٹ_Is_Authorized_منزل_Access_بفر( pxParams->pul_پچھلا_Notification_قدر,
                                                                                                 حجم( uint32_t ),
                                                                                                 tskMPU_WRITE_PERMISSION );
                    }

                    إذا( ( pxParams->pul_پچھلا_Notification_قدر == عدم ) ||
                        ( x_Is_پچھلا_Notification_قدر_Writeable == pdTRUE ) )
                    {
                        l_اشاریہ = ( int32_t ) ( pxParams->x_Task_منزل_Notify );

                        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                            إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                            {
                                x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                                إذا( x_اندرونی_Task_Handle != عدم )
                                {
                                    xReturn = xTaskGenericNotify( x_اندرونی_Task_Handle,
                                                                  pxParams->ux_اشاریہ_منزل_Notify,
                                                                  pxParams->ul_قدر,
                                                                  pxParams->eAction,
                                                                  pxParams->pul_پچھلا_Notification_قدر );
                                }
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        ادھار_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_اشاریہ_منزل_Wait_On,
                                               uint32_t ul_بٹ_منزل_Clear_On_اندراج,
                                               uint32_t ul_بٹ_منزل_Clear_On_Exit,
                                               uint32_t * pul_Notification_قدر,
                                               TickType_t x_Ticks_منزل_Wait )
        {
            ادھار_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyWaitParams_t xParams;

            xParams.ux_اشاریہ_منزل_Wait_On = ux_اشاریہ_منزل_Wait_On;
            xParams.ul_بٹ_منزل_Clear_On_اندراج = ul_بٹ_منزل_Clear_On_اندراج;
            xParams.ul_بٹ_منزل_Clear_On_Exit = ul_بٹ_منزل_Clear_On_Exit;
            xParams.pul_Notification_قدر = pul_Notification_قدر;
            xParams.x_Ticks_منزل_Wait = x_Ticks_منزل_Wait;

            xReturn = MPU_x_Task_Generic_Notify_Wait_اندراج( &( xParams ) );

            أرجع xReturn;
        }

        ادھار_Type_t MPU_xTaskGenericNotifyWaitImpl( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_xTaskGenericNotifyWaitImpl( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            ادھار_Type_t x_Is_Notification_قدر_Writable = pdFALSE;
            ادھار_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورٹ_Is_Authorized_منزل_Access_بفر( pxParams,
                                                                      حجم( xTaskGenericNotifyWaitParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( pxParams->ux_اشاریہ_منزل_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
                {
                    إذا( pxParams->pul_Notification_قدر != عدم )
                    {
                        x_Is_Notification_قدر_Writable = x_پورٹ_Is_Authorized_منزل_Access_بفر( pxParams->pul_Notification_قدر,
                                                                                        حجم( uint32_t ),
                                                                                        tskMPU_WRITE_PERMISSION );
                    }

                    إذا( ( pxParams->pul_Notification_قدر == عدم ) ||
                        ( x_Is_Notification_قدر_Writable == pdTRUE ) )
                    {
                        xReturn = xTaskGenericNotifyWait( pxParams->ux_اشاریہ_منزل_Wait_On,
                                                          pxParams->ul_بٹ_منزل_Clear_On_اندراج,
                                                          pxParams->ul_بٹ_منزل_Clear_On_Exit,
                                                          pxParams->pul_Notification_قدر,
                                                          pxParams->x_Ticks_منزل_Wait );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_اشاریہ_منزل_Wait_On,
                                                  ادھار_Type_t x_Clear_گنتی_On_Exit,
                                                  TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_اشاریہ_منزل_Wait_On,
                                                  ادھار_Type_t x_Clear_گنتی_On_Exit,
                                                  TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;

            إذا( ux_اشاریہ_منزل_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ulReturn = ulTaskGenericNotifyTake( ux_اشاریہ_منزل_Wait_On, x_Clear_گنتی_On_Exit, x_Ticks_منزل_Wait );
            }

            أرجع ulReturn;
        }

    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        ادھار_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_اشاریہ_منزل_Clear ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_اشاریہ_منزل_Clear ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( ux_اشاریہ_منزل_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                إذا( xTask == عدم )
                {
                    xReturn = xTaskGenericNotifyStateClear( xTask, ux_اشاریہ_منزل_Clear );
                }
                وإلا
                {
                    l_اشاریہ = ( int32_t ) xTask;

                    إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                        {
                            x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                            إذا( x_اندرونی_Task_Handle != عدم )
                            {
                                xReturn = xTaskGenericNotifyStateClear( x_اندرونی_Task_Handle, ux_اشاریہ_منزل_Clear );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_اشاریہ_منزل_Clear,
                                                        uint32_t ul_بٹ_منزل_Clear ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_اشاریہ_منزل_Clear,
                                                        uint32_t ul_بٹ_منزل_Clear ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Task = pdFALSE;

            إذا( ux_اشاریہ_منزل_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                إذا( xTask == عدم )
                {
                    ulReturn = ul_Task_Generic_Notify_قدر_Clear( xTask, ux_اشاریہ_منزل_Clear, ul_بٹ_منزل_Clear );
                }
                وإلا
                {
                    l_اشاریہ = ( int32_t ) xTask;

                    إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Task = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Task == pdTRUE )
                        {
                            x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                            إذا( x_اندرونی_Task_Handle != عدم )
                            {
                                ulReturn = ul_Task_Generic_Notify_قدر_Clear( x_اندرونی_Task_Handle, ux_اشاریہ_منزل_Clear, ul_بٹ_منزل_Clear );
                            }
                        }
                    }
                }
            }

            أرجع ulReturn;
        }

    #جے_انت /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Task APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ونڈ == 1 )

        ادھار_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_کوڈ,
                                    ثابت حرف * ثابت pcName,
                                    ثابت config_ڈھیر_ڈونگھائی_TYPE ux_ڈھیر_ڈونگھائی,
                                    فراغ * pvParameters,
                                    UBaseType_t ux_ترجیح,
                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                /* xTaskCreate() can only be used to create privileged tasks in MPU port. */
                إذا( ( ux_ترجیح & پورٹ_PRIVILEGE_ثنائی_ہندسہ ) != 0 )
                {
                    xReturn = xTaskCreate( pv_Task_کوڈ, pcName, ux_ڈھیر_ڈونگھائی, pvParameters, ux_ترجیح, &( x_اندرونی_Task_Handle ) );

                    إذا( ( xReturn == pdPASS ) && ( x_اندرونی_Task_Handle != عدم ) )
                    {
                        MPU_Store_Task_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Task_Handle );

                        إذا( pxCreatedTask != عدم )
                        {
                            *pxCreatedTask = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                        }
                    }
                    وإلا
                    {
                        MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ونڈ == 1 )

        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_کوڈ,
                                            ثابت حرف * ثابت pcName,
                                            ثابت config_ڈھیر_ڈونگھائی_TYPE ux_ڈھیر_ڈونگھائی,
                                            فراغ * ثابت pvParameters,
                                            UBaseType_t ux_ترجیح,
                                            ڈھیر_Type_t * ثابت pux_ڈھیر_بفر,
                                            StaticTask_t * ثابت px_Task_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xExternalTaskHandle = عدم;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                x_اندرونی_Task_Handle = xTaskCreateStatic( px_Task_کوڈ, pcName, ux_ڈھیر_ڈونگھائی, pvParameters, ux_ترجیح, pux_ڈھیر_بفر, px_Task_بفر );

                إذا( x_اندرونی_Task_Handle != عدم )
                {
                    MPU_Store_Task_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Task_Handle );

                    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        إذا( ( ux_ترجیح & پورٹ_PRIVILEGE_ثنائی_ہندسہ ) == 0 )
                        {
                            v_پورٹ_Grant_Access_منزل_Kernel_Object( x_اندرونی_Task_Handle, l_اشاریہ );
                        }
                    }
                    #جے_انت

                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع xExternalTaskHandle;
        }

    #جے_انت /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelete == 1 )

        فراغ MPU_vTaskDelete( TaskHandle_t px_Task_منزل_Delete ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            int32_t l_اشاریہ;

            إذا( px_Task_منزل_Delete == عدم )
            {
                x_اندرونی_Task_Handle = xTaskGetCurrentTaskHandle();
                l_اشاریہ = MPU_Get_اشاریہ_For_Task_Handle( x_اندرونی_Task_Handle );

                إذا( l_اشاریہ != -1 )
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }

                vTaskDelete( x_اندرونی_Task_Handle );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) px_Task_منزل_Delete;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Task_Handle != عدم )
                    {
                        MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );
                        vTaskDelete( x_اندرونی_Task_Handle );
                    }
                }
            }
        }

    #جے_انت /* #if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/


    #إذا ( INCLUDE_v_Task_ترجیح_سیٹ == 1 )

        فراغ MPU_v_Task_ترجیح_سیٹ( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_ترجیح ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            int32_t l_اشاریہ;

            إذا( pxTask == عدم )
            {
                v_Task_ترجیح_سیٹ( pxTask, ux_New_ترجیح );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) pxTask;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Task_Handle != عدم )
                    {
                        v_Task_ترجیح_سیٹ( x_اندرونی_Task_Handle, ux_New_ترجیح );
                    }
                }
            }
        }

    #جے_انت /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetHandle == 1 )

        TaskHandle_t MPU_xTaskGetHandle( ثابت حرف * pc_Name_منزل_Query ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            TaskHandle_t xExternalTaskHandle = عدم;
            int32_t l_اشاریہ;

            x_اندرونی_Task_Handle = xTaskGetHandle( pc_Name_منزل_Query );

            إذا( x_اندرونی_Task_Handle != عدم )
            {
                l_اشاریہ = MPU_Get_اشاریہ_For_Task_Handle( x_اندرونی_Task_Handle );

                إذا( l_اشاریہ != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
            }

            أرجع xExternalTaskHandle;
        }

    #جے_انت /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/


    #إذا ( config_USE_APPLICATION_TASK_ٹیگ == 1 )

        ادھار_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     فراغ * pvParameter ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Task_Handle != عدم )
                    {
                        xReturn = xTaskCallApplicationTaskHook( x_اندرونی_Task_Handle, pvParameter );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ونڈ == 1 )

        ادھار_Type_t MPU_xTaskCreateRestricted( ثابت TaskParameters_t * ثابت pxTaskDefinition,
                                              TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                xReturn = xTaskCreateRestricted( pxTaskDefinition, &( x_اندرونی_Task_Handle ) );

                إذا( ( xReturn == pdPASS ) && ( x_اندرونی_Task_Handle != عدم ) )
                {
                    MPU_Store_Task_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Task_Handle );

                    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        إذا( ( pxTaskDefinition->ux_ترجیح & پورٹ_PRIVILEGE_ثنائی_ہندسہ ) == 0 )
                        {
                            v_پورٹ_Grant_Access_منزل_Kernel_Object( x_اندرونی_Task_Handle, l_اشاریہ );
                        }
                    }
                    #جے_انت

                    إذا( pxCreatedTask != عدم )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                    }
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ونڈ == 1 )

        ادھار_Type_t MPU_xTaskCreateRestrictedStatic( ثابت TaskParameters_t * ثابت pxTaskDefinition,
                                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                xReturn = xTaskCreateRestrictedStatic( pxTaskDefinition, &( x_اندرونی_Task_Handle ) );

                إذا( ( xReturn == pdPASS ) && ( x_اندرونی_Task_Handle != عدم ) )
                {
                    MPU_Store_Task_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Task_Handle );

                    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        إذا( ( pxTaskDefinition->ux_ترجیح & پورٹ_PRIVILEGE_ثنائی_ہندسہ ) == 0 )
                        {
                            v_پورٹ_Grant_Access_منزل_Kernel_Object( x_اندرونی_Task_Handle, l_اشاریہ );
                        }
                    }
                    #جے_انت

                    إذا( pxCreatedTask != عدم )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                    }
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    فراغ MPU_vTaskAllocateMPURegions( TaskHandle_t x_Task_منزل_Modify,
                                      ثابت حافظہ_Region_t * ثابت xRegions ) /* PRIVILEGED_FUNCTION */
    {
        TaskHandle_t x_اندرونی_Task_Handle = عدم;
        int32_t l_اشاریہ;

        إذا( x_Task_منزل_Modify == عدم )
        {
            vTaskAllocateMPURegions( x_Task_منزل_Modify, xRegions );
        }
        وإلا
        {
            l_اشاریہ = ( int32_t ) x_Task_منزل_Modify;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_Task_Handle != عدم )
                {
                    vTaskAllocateMPURegions( x_اندرونی_Task_Handle, xRegions );
                }
            }
        }
    }
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ونڈ == 1 )

        ادھار_Type_t MPU_xTaskGetStaticBuffers( TaskHandle_t xTask,
                                              ڈھیر_Type_t ** ppux_ڈھیر_بفر,
                                              StaticTask_t ** ppx_Task_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندرونی_Task_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t xReturn = pdFALSE;

            إذا( xTask == عدم )
            {
                x_اندرونی_Task_Handle = xTaskGetCurrentTaskHandle();
                xReturn = xTaskGetStaticBuffers( x_اندرونی_Task_Handle, ppux_ڈھیر_بفر, ppx_Task_بفر );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Task_Handle != عدم )
                    {
                        xReturn = xTaskGetStaticBuffers( x_اندرونی_Task_Handle, ppux_ڈھیر_بفر, ppx_Task_بفر );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    حرف * MPU_pcTaskGetName( TaskHandle_t x_Task_منزل_Query ) /* PRIVILEGED_FUNCTION */
    {
        حرف * pcReturn = عدم;
        int32_t l_اشاریہ;
        TaskHandle_t x_اندرونی_Task_Handle = عدم;

        إذا( x_Task_منزل_Query == عدم )
        {
            pcReturn = pcTaskGetName( x_Task_منزل_Query );
        }
        وإلا
        {
            l_اشاریہ = ( int32_t ) x_Task_منزل_Query;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_Task_Handle != عدم )
                {
                    pcReturn = pcTaskGetName( x_اندرونی_Task_Handle );
                }
            }
        }

        أرجع pcReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_ترجیح_Get == 1 )

        UBaseType_t MPU_ux_Task_ترجیح_Get_From_ISR( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_ترجیح_Get_From_ISR( xTask );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Task_Handle != عدم )
                    {
                        uxReturn = ux_Task_ترجیح_Get_From_ISR( x_اندرونی_Task_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #جے_انت /* #if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_ux_Task_ترجیح_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_ادھار_ترجیح_Get( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_ادھار_ترجیح_Get( xTask );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Task_Handle != عدم )
                    {
                        uxReturn = ux_Task_ادھار_ترجیح_Get( x_اندرونی_Task_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #جے_انت /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_ux_Task_ترجیح_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_ادھار_ترجیح_Get_From_ISR( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_ادھار_ترجیح_Get_From_ISR( xTask );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Task_Handle != عدم )
                    {
                        uxReturn = ux_Task_ادھار_ترجیح_Get_From_ISR( x_اندرونی_Task_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #جے_انت /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

        ادھار_Type_t MPU_xTaskResumeFromISR( TaskHandle_t x_Task_منزل_Resume ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;

            l_اشاریہ = ( int32_t ) x_Task_منزل_Resume;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_Task_Handle != عدم )
                {
                    xReturn = xTaskResumeFromISR( x_اندرونی_Task_Handle );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )*/
/*---------------------------------------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_ٹیگ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ٹیگ_From_ISR( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = عدم;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                xReturn = x_Task_Get_Application_Task_ٹیگ_From_ISR( xTask );
            }
            وإلا
            {
                l_اشاریہ = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Task_Handle != عدم )
                    {
                        xReturn = x_Task_Get_Application_Task_ٹیگ_From_ISR( x_اندرونی_Task_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        ادھار_Type_t MPU_xTaskGenericNotifyFromISR( TaskHandle_t x_Task_منزل_Notify,
                                                  UBaseType_t ux_اشاریہ_منزل_Notify,
                                                  uint32_t ul_قدر,
                                                  eNotifyAction eAction,
                                                  uint32_t * pul_پچھلا_Notification_قدر,
                                                  ادھار_Type_t * px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;

            l_اشاریہ = ( int32_t ) x_Task_منزل_Notify;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_Task_Handle != عدم )
                {
                    xReturn = xTaskGenericNotifyFromISR( x_اندرونی_Task_Handle, ux_اشاریہ_منزل_Notify, ul_قدر, eAction, pul_پچھلا_Notification_قدر, px_Higher_ترجیح_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        فراغ MPU_vTaskGenericNotifyGiveFromISR( TaskHandle_t x_Task_منزل_Notify,
                                                UBaseType_t ux_اشاریہ_منزل_Notify,
                                                ادھار_Type_t * px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = عدم;

            l_اشاریہ = ( int32_t ) x_Task_منزل_Notify;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_Task_Handle != عدم )
                {
                    vTaskGenericNotifyGiveFromISR( x_اندرونی_Task_Handle, ux_اشاریہ_منزل_Notify, px_Higher_ترجیح_Task_Woken );
                }
            }
        }
    #جے_انت /*#if ( configUSE_TASK_NOTIFICATIONS == 1 )*/
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for queue APIs.                   */
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Generic_Send_Impl( قطار_Handle_t x_قطار,
                                          ثابت فراغ * ثابت pv_شے_منزل_قطار,
                                          TickType_t x_Ticks_منزل_Wait,
                                          ادھار_Type_t xCopyPosition ) PRIVILEGED_FUNCTION;

    ادھار_Type_t MPU_x_قطار_Generic_Send_Impl( قطار_Handle_t x_قطار,
                                          ثابت فراغ * ثابت pv_شے_منزل_قطار,
                                          TickType_t x_Ticks_منزل_Wait,
                                          ادھار_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
        ادھار_Type_t xReturn = pdFAIL;
        ادھار_Type_t x_Is_شے_منزل_قطار_Readable = pdFALSE;
        ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;
        UBaseType_t ux_قطار_شے_ناپ, ux_قطار_لمائی;

        l_اشاریہ = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
            {
                x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_قطار_Handle != عدم )
                {
                    ux_قطار_شے_ناپ = ux_قطار_Get_قطار_شے_ناپ( x_اندرونی_قطار_Handle );
                    ux_قطار_لمائی = ux_قطار_Get_قطار_لمائی( x_اندرونی_قطار_Handle );

                    إذا( ( !( ( pv_شے_منزل_قطار == عدم ) && ( ux_قطار_شے_ناپ != ( UBaseType_t ) 0U ) ) ) &&
                        ( !( ( xCopyPosition == قطار_OVERWRITE ) && ( ux_قطار_لمائی != ( UBaseType_t ) 1U ) ) )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                        #جے_انت
                        )
                    {
                        إذا( pv_شے_منزل_قطار != عدم )
                        {
                            x_Is_شے_منزل_قطار_Readable = x_پورٹ_Is_Authorized_منزل_Access_بفر( pv_شے_منزل_قطار,
                                                                                      ux_قطار_شے_ناپ,
                                                                                      tskMPU_READ_PERMISSION );
                        }

                        إذا( ( pv_شے_منزل_قطار == عدم ) || ( x_Is_شے_منزل_قطار_Readable == pdTRUE ) )
                        {
                            xReturn = x_قطار_Generic_Send( x_اندرونی_قطار_Handle, pv_شے_منزل_قطار, x_Ticks_منزل_Wait, xCopyPosition );
                        }
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Messages_اڈیک_Impl( ثابت قطار_Handle_t px_قطار ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_قطار_Messages_اڈیک_Impl( ثابت قطار_Handle_t px_قطار ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
        UBaseType_t uxReturn = 0;
        ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;

        l_اشاریہ = ( int32_t ) px_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
            {
                x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_قطار_Handle != عدم )
                {
                    uxReturn = ux_قطار_Messages_اڈیک( x_اندرونی_قطار_Handle );
                }
            }
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Spaces_دستیاب_Impl( ثابت قطار_Handle_t x_قطار ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_قطار_Spaces_دستیاب_Impl( ثابت قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
        UBaseType_t uxReturn = 0;
        ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;

        l_اشاریہ = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
            {
                x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_قطار_Handle != عدم )
                {
                    uxReturn = ux_قطار_Spaces_دستیاب( x_اندرونی_قطار_Handle );
                }
            }
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Receive_Impl( قطار_Handle_t px_قطار,
                                      فراغ * ثابت pv_بفر,
                                      TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

    ادھار_Type_t MPU_x_قطار_Receive_Impl( قطار_Handle_t px_قطار,
                                      فراغ * ثابت pv_بفر,
                                      TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
        ادھار_Type_t xReturn = pdFAIL;
        ادھار_Type_t x_Is_Receive_بفر_Writable = pdFALSE;
        ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;
        UBaseType_t ux_قطار_شے_ناپ;

        l_اشاریہ = ( int32_t ) px_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
            {
                x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_قطار_Handle != عدم )
                {
                    ux_قطار_شے_ناپ = ux_قطار_Get_قطار_شے_ناپ( x_اندرونی_قطار_Handle );

                    إذا( ( !( ( ( pv_بفر ) == عدم ) && ( ux_قطار_شے_ناپ != ( UBaseType_t ) 0U ) ) )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                        #جے_انت
                        )
                    {
                        x_Is_Receive_بفر_Writable = x_پورٹ_Is_Authorized_منزل_Access_بفر( pv_بفر,
                                                                                    ux_قطار_شے_ناپ,
                                                                                    tskMPU_WRITE_PERMISSION );

                        إذا( x_Is_Receive_بفر_Writable == pdTRUE )
                        {
                            xReturn = x_قطار_Receive( x_اندرونی_قطار_Handle, pv_بفر, x_Ticks_منزل_Wait );
                        }
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Peek_Impl( قطار_Handle_t x_قطار,
                                   فراغ * ثابت pv_بفر,
                                   TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

    ادھار_Type_t MPU_x_قطار_Peek_Impl( قطار_Handle_t x_قطار,
                                   فراغ * ثابت pv_بفر,
                                   TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
        ادھار_Type_t xReturn = pdFAIL;
        ادھار_Type_t x_Is_Receive_بفر_Writable = pdFALSE;
        UBaseType_t ux_قطار_شے_ناپ;
        ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;

        l_اشاریہ = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
            {
                x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_قطار_Handle != عدم )
                {
                    ux_قطار_شے_ناپ = ux_قطار_Get_قطار_شے_ناپ( x_اندرونی_قطار_Handle );

                    إذا( ( !( ( ( pv_بفر ) == عدم ) && ( ux_قطار_شے_ناپ != ( UBaseType_t ) 0U ) ) )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                        #جے_انت
                        )
                    {
                        x_Is_Receive_بفر_Writable = x_پورٹ_Is_Authorized_منزل_Access_بفر( pv_بفر,
                                                                                    ux_قطار_شے_ناپ,
                                                                                    tskMPU_WRITE_PERMISSION );

                        إذا( x_Is_Receive_بفر_Writable == pdTRUE )
                        {
                            xReturn = x_قطار_Peek( x_اندرونی_قطار_Handle, pv_بفر, x_Ticks_منزل_Wait );
                        }
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Semaphore_Take_Impl( قطار_Handle_t x_قطار,
                                            TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

    ادھار_Type_t MPU_x_قطار_Semaphore_Take_Impl( قطار_Handle_t x_قطار,
                                            TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
        ادھار_Type_t xReturn = pdFAIL;
        UBaseType_t ux_قطار_شے_ناپ;
        ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;

        l_اشاریہ = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
            {
                x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_قطار_Handle != عدم )
                {
                    ux_قطار_شے_ناپ = ux_قطار_Get_قطار_شے_ناپ( x_اندرونی_قطار_Handle );

                    إذا( ( ux_قطار_شے_ناپ == 0U )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                        #جے_انت
                        )
                    {
                        xReturn = x_قطار_Semaphore_Take( x_اندرونی_قطار_Handle, x_Ticks_منزل_Wait );
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
            TaskHandle_t x_Mutex_Holder_Task_اندرونی_Handle = عدم;
            TaskHandle_t xMutexHolderTaskExternalHandle = عدم;
            int32_t l_اشاریہ, l_Mutex_Holder_Task_اشاریہ;
            قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;


            l_اشاریہ = ( int32_t ) xSemaphore;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
                {
                    x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_قطار_Handle != عدم )
                    {
                        x_Mutex_Holder_Task_اندرونی_Handle = x_قطار_Get_Mutex_Holder( x_اندرونی_قطار_Handle );

                        إذا( x_Mutex_Holder_Task_اندرونی_Handle != عدم )
                        {
                            l_Mutex_Holder_Task_اشاریہ = MPU_Get_اشاریہ_For_Task_Handle( x_Mutex_Holder_Task_اندرونی_Handle );

                            إذا( l_Mutex_Holder_Task_اشاریہ != -1 )
                            {
                                xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_منزل_EXTERNAL_اشاریہ( l_Mutex_Holder_Task_اشاریہ ) );
                            }
                        }
                    }
                }
            }

            أرجع xMutexHolderTaskExternalHandle;
        }

    #جے_انت /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        ادھار_Type_t MPU_x_قطار_Take_Mutex_Recursive_Impl( قطار_Handle_t xMutex,
                                                     TickType_t x_بلاک_ویلا ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_x_قطار_Take_Mutex_Recursive_Impl( قطار_Handle_t xMutex,
                                                     TickType_t x_بلاک_ویلا ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;
            int32_t l_اشاریہ;
            قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
            UBaseType_t ux_قطار_شے_ناپ;

            l_اشاریہ = ( int32_t ) xMutex;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
                {
                    x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_قطار_Handle != عدم )
                    {
                        ux_قطار_شے_ناپ = ux_قطار_Get_قطار_شے_ناپ( x_اندرونی_قطار_Handle );

                        إذا( ux_قطار_شے_ناپ == 0 )
                        {
                            xReturn = x_قطار_Take_Mutex_Recursive( x_اندرونی_قطار_Handle, x_بلاک_ویلا );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        ادھار_Type_t MPU_x_قطار_Give_Mutex_Recursive_Impl( قطار_Handle_t xMutex ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_x_قطار_Give_Mutex_Recursive_Impl( قطار_Handle_t xMutex ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;
            int32_t l_اشاریہ;
            قطار_Handle_t x_اندرونی_قطار_Handle = عدم;

            l_اشاریہ = ( int32_t ) xMutex;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
                {
                    x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_قطار_Handle != عدم )
                    {
                        xReturn = x_قطار_Give_Mutex_Recursive( x_اندرونی_قطار_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )

        قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ_Impl( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                            TickType_t x_بلاک_ویلا_Ticks ) PRIVILEGED_FUNCTION;

        قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ_Impl( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                            TickType_t x_بلاک_ویلا_Ticks ) /* PRIVILEGED_FUNCTION */
        {
            قطار_سیٹ_Handle_t x_اندرونی_قطار_سیٹ_Handle = عدم;
            قطار_سیٹ_Member_Handle_t x_Selected_Member_اندرونی = عدم;
            قطار_سیٹ_Member_Handle_t xSelectedMemberExternal = عدم;
            int32_t l_اشاریہ_قطار_سیٹ, l_اشاریہ_Selected_Member;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار_سیٹ = pdFALSE;

            l_اشاریہ_قطار_سیٹ = ( int32_t ) x_قطار_سیٹ;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ_قطار_سیٹ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار_سیٹ = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار_سیٹ == pdTRUE )
                {
                    x_اندرونی_قطار_سیٹ_Handle = MPU_Get_قطار_سیٹ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ ) );

                    إذا( x_اندرونی_قطار_سیٹ_Handle != عدم )
                    {
                        x_Selected_Member_اندرونی = x_قطار_Select_From_سیٹ( x_اندرونی_قطار_سیٹ_Handle, x_بلاک_ویلا_Ticks );

                        إذا( x_Selected_Member_اندرونی != عدم )
                        {
                            l_اشاریہ_Selected_Member = MPU_Get_اشاریہ_For_قطار_سیٹ_Member_Handle( x_Selected_Member_اندرونی );

                            إذا( l_اشاریہ_Selected_Member != -1 )
                            {
                                xSelectedMemberExternal = ( قطار_سیٹ_Member_Handle_t ) ( CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ_Selected_Member ) );
                            }
                        }
                    }
                }
            }

            أرجع xSelectedMemberExternal;
        }

    #جے_انت /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )

        ادھار_Type_t MPU_x_قطار_جوڑو_منزل_سیٹ_Impl( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                           قطار_سیٹ_Handle_t x_قطار_سیٹ ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_x_قطار_جوڑو_منزل_سیٹ_Impl( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                           قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            قطار_سیٹ_Member_Handle_t x_اندرونی_قطار_سیٹ_Member_Handle = عدم;
            قطار_سیٹ_Handle_t x_اندرونی_قطار_سیٹ_Handle = عدم;
            int32_t l_اشاریہ_قطار_سیٹ, l_اشاریہ_قطار_سیٹ_Member;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار_سیٹ = pdFALSE;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار_سیٹ_Member = pdFALSE;

            l_اشاریہ_قطار_سیٹ = ( int32_t ) x_قطار_سیٹ;
            l_اشاریہ_قطار_سیٹ_Member = ( int32_t ) x_قطار_Or_Semaphore;

            إذا( ( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ_قطار_سیٹ ) != pdFALSE ) &&
                ( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ_قطار_سیٹ_Member ) != pdFALSE ) )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار_سیٹ = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ ) );
                x_Calling_Task_Is_Authorized_منزل_Access_قطار_سیٹ_Member = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ_Member ) );

                إذا( ( x_Calling_Task_Is_Authorized_منزل_Access_قطار_سیٹ == pdTRUE ) && ( x_Calling_Task_Is_Authorized_منزل_Access_قطار_سیٹ_Member == pdTRUE ) )
                {
                    x_اندرونی_قطار_سیٹ_Handle = MPU_Get_قطار_سیٹ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ ) );
                    x_اندرونی_قطار_سیٹ_Member_Handle = MPU_Get_قطار_سیٹ_Member_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ_Member ) );

                    إذا( ( x_اندرونی_قطار_سیٹ_Handle != عدم ) && ( x_اندرونی_قطار_سیٹ_Member_Handle != عدم ) )
                    {
                        xReturn = x_قطار_جوڑو_منزل_سیٹ( x_اندرونی_قطار_سیٹ_Member_Handle, x_اندرونی_قطار_سیٹ_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا config_قطار_REGISTRY_ناپ > 0

        فراغ MPU_v_قطار_جوڑو_منزل_Registry_Impl( قطار_Handle_t x_قطار,
                                          ثابت حرف * pcName ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_قطار_جوڑو_منزل_Registry_Impl( قطار_Handle_t x_قطار,
                                          ثابت حرف * pcName ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;

            l_اشاریہ = ( int32_t ) x_قطار;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
                {
                    x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_قطار_Handle != عدم )
                    {
                        v_قطار_جوڑو_منزل_Registry( x_اندرونی_قطار_Handle, pcName );
                    }
                }
            }
        }

    #جے_انت /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_قطار_REGISTRY_ناپ > 0

        فراغ MPU_v_قطار_Unregister_قطار_Impl( قطار_Handle_t x_قطار ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_قطار_Unregister_قطار_Impl( قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;

            l_اشاریہ = ( int32_t ) x_قطار;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
                {
                    x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_قطار_Handle != عدم )
                    {
                        v_قطار_Unregister_قطار( x_اندرونی_قطار_Handle );
                    }
                }
            }
        }

    #جے_انت /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_قطار_REGISTRY_ناپ > 0

        ثابت حرف * MPU_pc_قطار_Get_Name_Impl( قطار_Handle_t x_قطار ) PRIVILEGED_FUNCTION;

        ثابت حرف * MPU_pc_قطار_Get_Name_Impl( قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
        {
            ثابت حرف * pcReturn = عدم;
            قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_قطار = pdFALSE;

            l_اشاریہ = ( int32_t ) x_قطار;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_قطار = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_قطار == pdTRUE )
                {
                    x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_قطار_Handle != عدم )
                    {
                        pcReturn = pc_قطار_Get_Name( x_اندرونی_قطار_Handle );
                    }
                }
            }

            أرجع pcReturn;
        }

    #جے_انت /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Queue APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    فراغ MPU_v_قطار_Delete( قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
        int32_t l_اشاریہ;

        l_اشاریہ = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_اندرونی_قطار_Handle != عدم )
            {
                v_قطار_Delete( x_اندرونی_قطار_Handle );
                MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );
            }
        }
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_ونڈ == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Mutex( ثابت uint8_t uc_قطار_Type ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
            قطار_Handle_t x_External_قطار_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_Handle = x_قطار_Create_Mutex( uc_قطار_Type );

                إذا( x_اندرونی_قطار_Handle != عدم )
                {
                    MPU_Store_قطار_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع x_External_قطار_Handle;
        }

    #جے_انت /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_ونڈ == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Mutex_Static( ثابت uint8_t uc_قطار_Type,
                                                   Static_قطار_t * px_Static_قطار ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
            قطار_Handle_t x_External_قطار_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_Handle = x_قطار_Create_Mutex_Static( uc_قطار_Type, px_Static_قطار );

                إذا( x_اندرونی_قطار_Handle != عدم )
                {
                    MPU_Store_قطار_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع x_External_قطار_Handle;
        }

    #جے_انت /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_ونڈ == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Counting_Semaphore( UBaseType_t ux_گنتی_قدر,
                                                         UBaseType_t ux_Initial_گنتی ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
            قطار_Handle_t x_External_قطار_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_Handle = x_قطار_Create_Counting_Semaphore( ux_گنتی_قدر, ux_Initial_گنتی );

                إذا( x_اندرونی_قطار_Handle != عدم )
                {
                    MPU_Store_قطار_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع x_External_قطار_Handle;
        }

    #جے_انت /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_ونڈ == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Counting_Semaphore_Static( ثابت UBaseType_t ux_Max_گنتی,
                                                               ثابت UBaseType_t ux_Initial_گنتی,
                                                               Static_قطار_t * px_Static_قطار ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
            قطار_Handle_t x_External_قطار_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_Handle = x_قطار_Create_Counting_Semaphore_Static( ux_Max_گنتی, ux_Initial_گنتی, px_Static_قطار );

                إذا( x_اندرونی_قطار_Handle != عدم )
                {
                    MPU_Store_قطار_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع x_External_قطار_Handle;
        }

    #جے_انت /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ونڈ == 1 )

        قطار_Handle_t MPU_x_قطار_Generic_Create( UBaseType_t ux_قطار_لمائی,
                                               UBaseType_t ux_شے_ناپ,
                                               uint8_t uc_قطار_Type ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
            قطار_Handle_t x_External_قطار_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_Handle = x_قطار_Generic_Create( ux_قطار_لمائی, ux_شے_ناپ, uc_قطار_Type );

                إذا( x_اندرونی_قطار_Handle != عدم )
                {
                    MPU_Store_قطار_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع x_External_قطار_Handle;
        }

    #جے_انت /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ونڈ == 1 )

        قطار_Handle_t MPU_x_قطار_Generic_Create_Static( ثابت UBaseType_t ux_قطار_لمائی,
                                                     ثابت UBaseType_t ux_شے_ناپ,
                                                     uint8_t * puc_قطار_Storage,
                                                     Static_قطار_t * px_Static_قطار,
                                                     ثابت uint8_t uc_قطار_Type ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
            قطار_Handle_t x_External_قطار_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_Handle = x_قطار_Generic_Create_Static( ux_قطار_لمائی, ux_شے_ناپ, puc_قطار_Storage, px_Static_قطار, uc_قطار_Type );

                إذا( x_اندرونی_قطار_Handle != عدم )
                {
                    MPU_Store_قطار_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع x_External_قطار_Handle;
        }

    #جے_انت /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Generic_Reset( قطار_Handle_t x_قطار,
                                       ادھار_Type_t x_New_قطار ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
        ادھار_Type_t xReturn = pdFAIL;

        l_اشاریہ = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_اندرونی_قطار_Handle != عدم )
            {
                xReturn = x_قطار_Generic_Reset( x_اندرونی_قطار_Handle, x_New_قطار );
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_قطار_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_ونڈ == 1 ) )

        قطار_سیٹ_Handle_t MPU_x_قطار_Create_سیٹ( UBaseType_t ux_Event_قطار_لمائی ) /* PRIVILEGED_FUNCTION */
        {
            قطار_سیٹ_Handle_t x_اندرونی_قطار_سیٹ_Handle = عدم;
            قطار_سیٹ_Handle_t x_External_قطار_سیٹ_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_سیٹ_Handle = x_قطار_Create_سیٹ( ux_Event_قطار_لمائی );

                إذا( x_اندرونی_قطار_سیٹ_Handle != عدم )
                {
                    MPU_Store_قطار_سیٹ_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_سیٹ_Handle );
                    x_External_قطار_سیٹ_Handle = ( قطار_سیٹ_Handle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع x_External_قطار_سیٹ_Handle;
        }

    #جے_انت /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_قطار_SETS == 1 ) && ( config_SUPPORT_STATIC_ونڈ == 1 ) )

        قطار_سیٹ_Handle_t MPU_x_قطار_Create_سیٹ_Static( ثابت UBaseType_t ux_Event_قطار_لمائی,
                                                    uint8_t * puc_قطار_Storage,
                                                    Static_قطار_t * px_Static_قطار ) /* PRIVILEGED_FUNCTION */
        {
            قطار_سیٹ_Handle_t x_اندرونی_قطار_سیٹ_Handle = عدم;
            قطار_سیٹ_Handle_t x_External_قطار_سیٹ_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_سیٹ_Handle = x_قطار_Create_سیٹ_Static( ux_Event_قطار_لمائی, puc_قطار_Storage, px_Static_قطار );

                إذا( x_اندرونی_قطار_سیٹ_Handle != عدم )
                {
                    MPU_Store_قطار_سیٹ_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_سیٹ_Handle );
                    x_External_قطار_سیٹ_Handle = ( قطار_سیٹ_Handle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع x_External_قطار_سیٹ_Handle;
        }

    #جے_انت /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )

        ادھار_Type_t MPU_x_قطار_Remove_From_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                            قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            قطار_سیٹ_Member_Handle_t x_اندرونی_قطار_سیٹ_Member_Handle = عدم;
            قطار_سیٹ_Handle_t x_اندرونی_قطار_سیٹ_Handle = عدم;
            int32_t l_اشاریہ_قطار_سیٹ, l_اشاریہ_قطار_سیٹ_Member;

            l_اشاریہ_قطار_سیٹ = ( int32_t ) x_قطار_سیٹ;
            l_اشاریہ_قطار_سیٹ_Member = ( int32_t ) x_قطار_Or_Semaphore;

            إذا( ( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ_قطار_سیٹ ) != pdFALSE ) &&
                ( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ_قطار_سیٹ_Member ) != pdFALSE ) )
            {
                x_اندرونی_قطار_سیٹ_Handle = MPU_Get_قطار_سیٹ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ ) );
                x_اندرونی_قطار_سیٹ_Member_Handle = MPU_Get_قطار_سیٹ_Member_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ_Member ) );

                إذا( ( x_اندرونی_قطار_سیٹ_Handle != عدم ) && ( x_اندرونی_قطار_سیٹ_Member_Handle != عدم ) )
                {
                    xReturn = x_قطار_Remove_From_سیٹ( x_اندرونی_قطار_سیٹ_Member_Handle, x_اندرونی_قطار_سیٹ_Handle );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ونڈ == 1 )

        ادھار_Type_t MPU_x_قطار_Generic_Get_Static_Buffers( قطار_Handle_t x_قطار,
                                                      uint8_t ** ppuc_قطار_Storage,
                                                      Static_قطار_t ** ppx_Static_قطار ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            قطار_Handle_t x_اندرونی_قطار_Handle = عدم;
            ادھار_Type_t xReturn = pdFALSE;

            l_اشاریہ = ( int32_t ) x_قطار;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_قطار_Handle != عدم )
                {
                    xReturn = x_قطار_Generic_Get_Static_Buffers( x_اندرونی_قطار_Handle, ppuc_قطار_Storage, ppx_Static_قطار );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /*if ( configSUPPORT_STATIC_ALLOCATION == 1 )*/
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Generic_Send_From_ISR( قطار_Handle_t x_قطار,
                                             ثابت فراغ * ثابت pv_شے_منزل_قطار,
                                             ادھار_Type_t * ثابت px_Higher_ترجیح_Task_Woken,
                                             ثابت ادھار_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        ادھار_Type_t xReturn = pdFAIL;
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;

        l_اشاریہ = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_اندرونی_قطار_Handle != عدم )
            {
                xReturn = x_قطار_Generic_Send_From_ISR( x_اندرونی_قطار_Handle, pv_شے_منزل_قطار, px_Higher_ترجیح_Task_Woken, xCopyPosition );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Give_From_ISR( قطار_Handle_t x_قطار,
                                      ادھار_Type_t * ثابت px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        ادھار_Type_t xReturn = pdFAIL;
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;

        l_اشاریہ = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_اندرونی_قطار_Handle != عدم )
            {
                xReturn = x_قطار_Give_From_ISR( x_اندرونی_قطار_Handle, px_Higher_ترجیح_Task_Woken );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Peek_From_ISR( قطار_Handle_t x_قطار,
                                      فراغ * ثابت pv_بفر ) /* PRIVILEGED_FUNCTION */
    {
        ادھار_Type_t xReturn = pdFAIL;
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;

        l_اشاریہ = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_اندرونی_قطار_Handle != عدم )
            {
                xReturn = x_قطار_Peek_From_ISR( x_اندرونی_قطار_Handle, pv_بفر );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Receive_From_ISR( قطار_Handle_t x_قطار,
                                         فراغ * ثابت pv_بفر,
                                         ادھار_Type_t * ثابت px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        ادھار_Type_t xReturn = pdFAIL;
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;

        l_اشاریہ = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_اندرونی_قطار_Handle != عدم )
            {
                xReturn = x_قطار_Receive_From_ISR( x_اندرونی_قطار_Handle, pv_بفر, px_Higher_ترجیح_Task_Woken );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Is_قطار_خالی_تھاواں_From_ISR( ثابت قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        ادھار_Type_t xReturn = pdFAIL;
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;

        l_اشاریہ = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_اندرونی_قطار_Handle != عدم )
            {
                xReturn = x_قطار_Is_قطار_خالی_تھاواں_From_ISR( x_اندرونی_قطار_Handle );
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    ادھار_Type_t MPU_x_قطار_Is_قطار_بھریا_From_ISR( ثابت قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        ادھار_Type_t xReturn = pdFAIL;
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;

        l_اشاریہ = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_اندرونی_قطار_Handle != عدم )
            {
                xReturn = x_قطار_Is_قطار_بھریا_From_ISR( x_اندرونی_قطار_Handle );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Messages_اڈیک_From_ISR( ثابت قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn = 0;
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = عدم;

        l_اشاریہ = ( int32_t ) x_قطار;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_اندرونی_قطار_Handle != عدم )
            {
                uxReturn = ux_قطار_Messages_اڈیک_From_ISR( x_اندرونی_قطار_Handle );
            }
        }

        أرجع uxReturn;
    }

/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder_From_ISR( قطار_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_اندرونی_Handle = عدم;
            TaskHandle_t xMutexHolderTaskExternalHandle = عدم;
            int32_t l_اشاریہ, l_Mutex_Holder_Task_اشاریہ;
            قطار_Handle_t x_اندرونی_Semaphore_Handle = عدم;

            l_اشاریہ = ( int32_t ) xSemaphore;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Semaphore_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_Semaphore_Handle != عدم )
                {
                    x_Mutex_Holder_Task_اندرونی_Handle = x_قطار_Get_Mutex_Holder( x_اندرونی_Semaphore_Handle );

                    إذا( x_Mutex_Holder_Task_اندرونی_Handle != عدم )
                    {
                        l_Mutex_Holder_Task_اشاریہ = MPU_Get_اشاریہ_For_Task_Handle( x_Mutex_Holder_Task_اندرونی_Handle );

                        إذا( l_Mutex_Holder_Task_اشاریہ != -1 )
                        {
                            xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_منزل_EXTERNAL_اشاریہ( l_Mutex_Holder_Task_اشاریہ ) );
                        }
                    }
                }
            }

            أرجع xMutexHolderTaskExternalHandle;
        }

    #جے_انت /* #if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_قطار_SETS == 1 )

        قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ_From_ISR( قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* PRIVILEGED_FUNCTION */
        {
            قطار_سیٹ_Handle_t x_اندرونی_قطار_سیٹ_Handle = عدم;
            قطار_سیٹ_Member_Handle_t x_Selected_Member_اندرونی = عدم;
            قطار_سیٹ_Member_Handle_t xSelectedMemberExternal = عدم;
            int32_t l_اشاریہ_قطار_سیٹ, l_اشاریہ_Selected_Member;

            l_اشاریہ_قطار_سیٹ = ( int32_t ) x_قطار_سیٹ;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ_قطار_سیٹ ) != pdFALSE )
            {
                x_اندرونی_قطار_سیٹ_Handle = MPU_Get_قطار_سیٹ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ ) );

                إذا( x_اندرونی_قطار_سیٹ_Handle != عدم )
                {
                    x_Selected_Member_اندرونی = x_قطار_Select_From_سیٹ_From_ISR( x_اندرونی_قطار_سیٹ_Handle );

                    إذا( x_Selected_Member_اندرونی != عدم )
                    {
                        l_اشاریہ_Selected_Member = MPU_Get_اشاریہ_For_قطار_سیٹ_Member_Handle( x_Selected_Member_اندرونی );

                        إذا( l_اشاریہ_Selected_Member != -1 )
                        {
                            xSelectedMemberExternal = ( قطار_سیٹ_Member_Handle_t ) ( CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ_Selected_Member ) );
                        }
                    }
                }
            }

            أرجع xSelectedMemberExternal;
        }

    #جے_انت /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for timers APIs.                  */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ * MPU_pvTimerGetTimerIDImpl( ثابت TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        فراغ * MPU_pvTimerGetTimerIDImpl( ثابت TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            فراغ * pvReturn = عدم;
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Timer_Handle != عدم )
                    {
                        pvReturn = pvTimerGetTimerID( x_اندرونی_Timer_Handle );
                    }
                }
            }

            أرجع pvReturn;
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_سیٹ_Timer_IDImpl( TimerHandle_t xTimer,
                                       فراغ * pvNewID ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Timer_سیٹ_Timer_IDImpl( TimerHandle_t xTimer,
                                       فراغ * pvNewID ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Timer_Handle != عدم )
                    {
                        v_Timer_سیٹ_Timer_ID( x_اندرونی_Timer_Handle, pvNewID );
                    }
                }
            }
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ادھار_Type_t MPU_x_Timer_Is_Timer_سرگرم_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_x_Timer_Is_Timer_سرگرم_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Timer_Handle != عدم )
                    {
                        xReturn = x_Timer_Is_Timer_سرگرم( x_اندرونی_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( فراغ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xReturn;

            xReturn = xTimerGetTimerDaemonTaskHandle();

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ادھار_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ثابت ادھار_Type_t xCommandID,
                                                     ثابت TickType_t x_Optional_قدر,
                                                     ادھار_Type_t * ثابت px_Higher_ترجیح_Task_Woken,
                                                     ثابت TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            ادھار_Type_t xReturn = pdFALSE;
            xTimerGenericCommandFromTaskParams_t xParams;

            xParams.xTimer = xTimer;
            xParams.xCommandID = xCommandID;
            xParams.x_Optional_قدر = x_Optional_قدر;
            xParams.px_Higher_ترجیح_Task_Woken = px_Higher_ترجیح_Task_Woken;
            xParams.x_Ticks_منزل_Wait = x_Ticks_منزل_Wait;

            xReturn = MPU_x_Timer_Generic_Command_From_Task_اندراج( &( xParams ) );

            أرجع xReturn;
        }

        ادھار_Type_t MPU_xTimerGenericCommandFromTaskImpl( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_xTimerGenericCommandFromTaskImpl( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Is_Higher_ترجیح_Task_Woken_Writeable = pdFALSE;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;
            ادھار_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورٹ_Is_Authorized_منزل_Access_بفر( pxParams,
                                                                      حجم( xTimerGenericCommandFromTaskParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( pxParams->xCommandID < tmr_پہلا_FROM_ISR_COMMAND )
                {
                    إذا( pxParams->px_Higher_ترجیح_Task_Woken != عدم )
                    {
                        x_Is_Higher_ترجیح_Task_Woken_Writeable = x_پورٹ_Is_Authorized_منزل_Access_بفر( pxParams->px_Higher_ترجیح_Task_Woken,
                                                                                               حجم( ادھار_Type_t ),
                                                                                               tskMPU_WRITE_PERMISSION );
                    }

                    إذا( ( pxParams->px_Higher_ترجیح_Task_Woken == عدم ) ||
                        ( x_Is_Higher_ترجیح_Task_Woken_Writeable == pdTRUE ) )
                    {
                        l_اشاریہ = ( int32_t ) ( pxParams->xTimer );

                        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                            إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                            {
                                x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                                إذا( x_اندرونی_Timer_Handle != عدم )
                                {
                                    xReturn = xTimerGenericCommandFromTask( x_اندرونی_Timer_Handle,
                                                                            pxParams->xCommandID,
                                                                            pxParams->x_Optional_قدر,
                                                                            pxParams->px_Higher_ترجیح_Task_Woken,
                                                                            pxParams->x_Ticks_منزل_Wait );
                                }
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ثابت حرف * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ثابت حرف * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ثابت حرف * pcReturn = عدم;
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Timer_Handle != عدم )
                    {
                        pcReturn = pcTimerGetName( x_اندرونی_Timer_Handle );
                    }
                }
            }

            أرجع pcReturn;
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_سیٹ_Reload_منوال_Impl( TimerHandle_t xTimer,
                                          ثابت ادھار_Type_t xAutoReload ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Timer_سیٹ_Reload_منوال_Impl( TimerHandle_t xTimer,
                                          ثابت ادھار_Type_t xAutoReload ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Timer_Handle != عدم )
                    {
                        v_Timer_سیٹ_Reload_منوال( x_اندرونی_Timer_Handle, xAutoReload );
                    }
                }
            }
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ادھار_Type_t MPU_x_Timer_Get_Reload_منوال_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_x_Timer_Get_Reload_منوال_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Timer_Handle != عدم )
                    {
                        xReturn = x_Timer_Get_Reload_منوال( x_اندرونی_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_منوال_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Timer_Get_Reload_منوال_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Timer_Handle != عدم )
                    {
                        uxReturn = ux_Timer_Get_Reload_منوال( x_اندرونی_Timer_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Timer_Handle != عدم )
                    {
                        xReturn = xTimerGetPeriod( x_اندرونی_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_ویلا_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_x_Timer_Get_Expiry_ویلا_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Timer = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Timer_Handle != عدم )
                    {
                        xReturn = x_Timer_Get_Expiry_ویلا( x_اندرونی_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Timer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_ونڈ == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreate( ثابت حرف * ثابت pcTimerName,
                                        ثابت TickType_t x_Timer_Period_وچ_Ticks,
                                        ثابت ادھار_Type_t xAutoReload,
                                        فراغ * ثابت pvTimerID,
                                        TimerCallbackFunction_t pxCallbackFunction ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            TimerHandle_t xExternalTimerHandle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                x_اندرونی_Timer_Handle = xTimerCreate( pcTimerName, x_Timer_Period_وچ_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback );

                إذا( x_اندرونی_Timer_Handle != عدم )
                {
                    MPU_Store_Timer_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع xExternalTimerHandle;
        }

    #جے_انت /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ونڈ == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreateStatic( ثابت حرف * ثابت pcTimerName,
                                              ثابت TickType_t x_Timer_Period_وچ_Ticks,
                                              ثابت ادھار_Type_t xAutoReload,
                                              فراغ * ثابت pvTimerID,
                                              TimerCallbackFunction_t pxCallbackFunction,
                                              StaticTimer_t * px_Timer_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            TimerHandle_t xExternalTimerHandle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                x_اندرونی_Timer_Handle = xTimerCreateStatic( pcTimerName, x_Timer_Period_وچ_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback, px_Timer_بفر );

                إذا( x_اندرونی_Timer_Handle != عدم )
                {
                    MPU_Store_Timer_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع xExternalTimerHandle;
        }

    #جے_انت /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_ونڈ == 1 ) && ( configUSE_TIMERS == 1 )

        ادھار_Type_t MPU_x_Timer_Get_Static_بفر( TimerHandle_t xTimer,
                                              StaticTimer_t ** ppx_Timer_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t xReturn = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_Timer_Handle != عدم )
                {
                    xReturn = x_Timer_Get_Static_بفر( x_اندرونی_Timer_Handle, ppx_Timer_بفر );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ادھار_Type_t MPU_xTimerGenericCommandFromISR( TimerHandle_t xTimer,
                                                    ثابت ادھار_Type_t xCommandID,
                                                    ثابت TickType_t x_Optional_قدر,
                                                    ادھار_Type_t * ثابت px_Higher_ترجیح_Task_Woken,
                                                    ثابت TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_Timer_Handle != عدم )
                {
                    xReturn = xTimerGenericCommandFromISR( x_اندرونی_Timer_Handle, xCommandID, x_Optional_قدر, px_Higher_ترجیح_Task_Woken, x_Ticks_منزل_Wait );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ادھار_Type_t MPU_xTimerDelete( TimerHandle_t xTimer, TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندرونی_Timer_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_Timer_Handle != عدم )
                {
                    xReturn = xTimerGenericCommandFromTask( x_اندرونی_Timer_Handle,
                                                            tmrCOMMAND_DELETE,
                                                            0U, /* xOptionalValue */
                                                            عدم, /* pxHigherPriorityTaskWoken */
                                                            x_Ticks_منزل_Wait );
                    إذا( xReturn != pdFALSE )
                    {
                        MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for event group APIs.              */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                             ثابت Event_بٹ_t ux_بٹ_منزل_Wait_For,
                                             ثابت ادھار_Type_t xClearOnExit,
                                             ثابت ادھار_Type_t x_Wait_For_All_بٹ,
                                             TickType_t x_Ticks_منزل_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٹ_t xReturn = 0;
            x_Event_گروہ_Wait_بٹ_Params_t xParams;

            xParams.x_Event_گروہ = x_Event_گروہ;
            xParams.ux_بٹ_منزل_Wait_For = ux_بٹ_منزل_Wait_For;
            xParams.xClearOnExit = xClearOnExit;
            xParams.x_Wait_For_All_بٹ = x_Wait_For_All_بٹ;
            xParams.x_Ticks_منزل_Wait = x_Ticks_منزل_Wait;

            xReturn = MPU_x_Event_گروہ_Wait_بٹ_اندراج( &( xParams ) );

            أرجع xReturn;
        }

        Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ_Impl( ثابت x_Event_گروہ_Wait_بٹ_Params_t * pxParams ) PRIVILEGED_FUNCTION;

        Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ_Impl( ثابت x_Event_گروہ_Wait_بٹ_Params_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٹ_t xReturn = 0;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ = pdFALSE;
            ادھار_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورٹ_Is_Authorized_منزل_Access_بفر( pxParams,
                                                                      حجم( x_Event_گروہ_Wait_بٹ_Params_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( ( ( pxParams->ux_بٹ_منزل_Wait_For & event_EVENT_بٹ_CONTROL_بائٹاں ) == 0U ) &&
                    ( pxParams->ux_بٹ_منزل_Wait_For != 0U )
                    #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                        && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( pxParams->x_Ticks_منزل_Wait != 0U ) ) )
                    #جے_انت
                    )
                {
                    l_اشاریہ = ( int32_t ) ( pxParams->x_Event_گروہ );

                    إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ == pdTRUE )
                        {
                            x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                            إذا( x_اندرونی_Event_گروہ_Handle != عدم )
                            {
                                xReturn = x_Event_گروہ_Wait_بٹ( x_اندرونی_Event_گروہ_Handle,
                                                               pxParams->ux_بٹ_منزل_Wait_For,
                                                               pxParams->xClearOnExit,
                                                               pxParams->x_Wait_For_All_بٹ,
                                                               pxParams->x_Ticks_منزل_Wait );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ_Impl( Event_گروہ_Handle_t x_Event_گروہ,
                                                  ثابت Event_بٹ_t ux_بٹ_منزل_Clear ) PRIVILEGED_FUNCTION;

        Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ_Impl( Event_گروہ_Handle_t x_Event_گروہ,
                                                  ثابت Event_بٹ_t ux_بٹ_منزل_Clear ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٹ_t xReturn = 0;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ = pdFALSE;

            إذا( ( ux_بٹ_منزل_Clear & event_EVENT_بٹ_CONTROL_بائٹاں ) == 0U )
            {
                l_اشاریہ = ( int32_t ) x_Event_گروہ;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ == pdTRUE )
                    {
                        x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_اندرونی_Event_گروہ_Handle != عدم )
                        {
                            xReturn = x_Event_گروہ_Clear_بٹ( x_اندرونی_Event_گروہ_Handle, ux_بٹ_منزل_Clear );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ_Impl( Event_گروہ_Handle_t x_Event_گروہ,
                                                ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ ) PRIVILEGED_FUNCTION;

        Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ_Impl( Event_گروہ_Handle_t x_Event_گروہ,
                                                ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٹ_t xReturn = 0;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ = pdFALSE;

            إذا( ( ux_بٹ_منزل_سیٹ & event_EVENT_بٹ_CONTROL_بائٹاں ) == 0U )
            {
                l_اشاریہ = ( int32_t ) x_Event_گروہ;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ == pdTRUE )
                    {
                        x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_اندرونی_Event_گروہ_Handle != عدم )
                        {
                            xReturn = x_Event_گروہ_سیٹ_بٹ( x_اندرونی_Event_گروہ_Handle, ux_بٹ_منزل_سیٹ );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Sync_Impl( Event_گروہ_Handle_t x_Event_گروہ,
                                             ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ,
                                             ثابت Event_بٹ_t ux_بٹ_منزل_Wait_For,
                                             TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

        Event_بٹ_t MPU_x_Event_گروہ_Sync_Impl( Event_گروہ_Handle_t x_Event_گروہ,
                                             ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ,
                                             ثابت Event_بٹ_t ux_بٹ_منزل_Wait_For,
                                             TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٹ_t xReturn = 0;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ = pdFALSE;

            إذا( ( ( ux_بٹ_منزل_Wait_For & event_EVENT_بٹ_CONTROL_بائٹاں ) == 0U ) &&
                ( ux_بٹ_منزل_Wait_For != 0U )
                #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                    && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_منزل_Wait != 0U ) ) )
                #جے_انت
                )
            {
                l_اشاریہ = ( int32_t ) x_Event_گروہ;

                إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ == pdTRUE )
                    {
                        x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_اندرونی_Event_گروہ_Handle != عدم )
                        {
                            xReturn = x_Event_گروہ_Sync( x_اندرونی_Event_گروہ_Handle, ux_بٹ_منزل_سیٹ, ux_بٹ_منزل_Wait_For, x_Ticks_منزل_Wait );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_گروہ_Get_نمبر_Impl( فراغ * x_Event_گروہ ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Event_گروہ_Get_نمبر_Impl( فراغ * x_Event_گروہ ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t xReturn = 0;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ = pdFALSE;

            l_اشاریہ = ( int32_t ) x_Event_گروہ;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ == pdTRUE )
                {
                    x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Event_گروہ_Handle != عدم )
                    {
                        xReturn = ux_Event_گروہ_Get_نمبر( x_اندرونی_Event_گروہ_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        فراغ MPU_v_Event_گروہ_سیٹ_نمبر_Impl( فراغ * x_Event_گروہ,
                                           UBaseType_t ux_Event_گروہ_نمبر ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Event_گروہ_سیٹ_نمبر_Impl( فراغ * x_Event_گروہ,
                                           UBaseType_t ux_Event_گروہ_نمبر ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ = pdFALSE;

            l_اشاریہ = ( int32_t ) x_Event_گروہ;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_Event_گروہ == pdTRUE )
                {
                    x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_Event_گروہ_Handle != عدم )
                    {
                        v_Event_گروہ_سیٹ_نمبر( x_اندرونی_Event_گروہ_Handle, ux_Event_گروہ_نمبر );
                    }
                }
            }
        }

    #جے_انت /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Event Group APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_ونڈ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_گروہ_Handle_t MPU_x_Event_گروہ_Create( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = عدم;
            Event_گروہ_Handle_t x_External_Event_گروہ_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                x_اندرونی_Event_گروہ_Handle = x_Event_گروہ_Create();

                إذا( x_اندرونی_Event_گروہ_Handle != عدم )
                {
                    MPU_Store_Event_گروہ_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Event_گروہ_Handle );
                    x_External_Event_گروہ_Handle = ( Event_گروہ_Handle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع x_External_Event_گروہ_Handle;
        }

    #جے_انت /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ونڈ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_گروہ_Handle_t MPU_x_Event_گروہ_Create_Static( Static_Event_گروہ_t * px_Event_گروہ_بفر ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = عدم;
            Event_گروہ_Handle_t x_External_Event_گروہ_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

            إذا( l_اشاریہ != -1 )
            {
                x_اندرونی_Event_گروہ_Handle = x_Event_گروہ_Create_Static( px_Event_گروہ_بفر );

                إذا( x_اندرونی_Event_گروہ_Handle != عدم )
                {
                    MPU_Store_Event_گروہ_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Event_گروہ_Handle );
                    x_External_Event_گروہ_Handle = ( Event_گروہ_Handle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                وإلا
                {
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            أرجع x_External_Event_گروہ_Handle;
        }

    #جے_انت /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        فراغ MPU_v_Event_گروہ_Delete( Event_گروہ_Handle_t x_Event_گروہ ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_Event_گروہ;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_Event_گروہ_Handle != عدم )
                {
                    v_Event_گروہ_Delete( x_اندرونی_Event_گروہ_Handle );
                    MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );
                }
            }
        }

    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ونڈ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        ادھار_Type_t MPU_x_Event_گروہ_Get_Static_بفر( Event_گروہ_Handle_t x_Event_گروہ,
                                                   Static_Event_گروہ_t ** ppx_Event_گروہ_بفر ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_Event_گروہ;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_Event_گروہ_Handle != عدم )
                {
                    xReturn = x_Event_گروہ_Get_Static_بفر( x_اندرونی_Event_گروہ_Handle, ppx_Event_گروہ_بفر );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        ادھار_Type_t MPU_x_Event_گروہ_Clear_بٹ_From_ISR( Event_گروہ_Handle_t x_Event_گروہ,
                                                    ثابت Event_بٹ_t ux_بٹ_منزل_Clear ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_Event_گروہ;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_Event_گروہ_Handle != عدم )
                {
                    xReturn = x_Event_گروہ_Clear_بٹ_From_ISR( x_اندرونی_Event_گروہ_Handle, ux_بٹ_منزل_Clear );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        ادھار_Type_t MPU_x_Event_گروہ_سیٹ_بٹ_From_ISR( Event_گروہ_Handle_t x_Event_گروہ,
                                                  ثابت Event_بٹ_t ux_بٹ_منزل_سیٹ,
                                                  ادھار_Type_t * px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_Event_گروہ;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_Event_گروہ_Handle != عدم )
                {
                    xReturn = x_Event_گروہ_سیٹ_بٹ_From_ISR( x_اندرونی_Event_گروہ_Handle, ux_بٹ_منزل_سیٹ, px_Higher_ترجیح_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Get_بٹ_From_ISR( Event_گروہ_Handle_t x_Event_گروہ ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٹ_t xReturn = 0;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_Event_گروہ;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_Event_گروہ_Handle != عدم )
                {
                    xReturn = x_Event_گروہ_Get_بٹ_From_ISR( x_اندرونی_Event_گروہ_Handle );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for stream buffer APIs.            */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_Send_Impl( دھارا_بفر_Handle_t x_دھارا_بفر,
                                          ثابت فراغ * pv_Tx_انکڑے,
                                          size_t x_انکڑے_لمائی_بائٹاں,
                                          TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_دھارا_بفر_Send_Impl( دھارا_بفر_Handle_t x_دھارا_بفر,
                                          ثابت فراغ * pv_Tx_انکڑے,
                                          size_t x_انکڑے_لمائی_بائٹاں,
                                          TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Is_Tx_انکڑے_بفر_Readable = pdFALSE;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = pdFALSE;

            إذا( pv_Tx_انکڑے != عدم )
            {
                x_Is_Tx_انکڑے_بفر_Readable = x_پورٹ_Is_Authorized_منزل_Access_بفر( pv_Tx_انکڑے,
                                                                           x_انکڑے_لمائی_بائٹاں,
                                                                           tskMPU_READ_PERMISSION );

                إذا( x_Is_Tx_انکڑے_بفر_Readable == pdTRUE )
                {
                    l_اشاریہ = ( int32_t ) x_دھارا_بفر;

                    إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر == pdTRUE )
                        {
                            x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                            إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                            {
                                xReturn = x_دھارا_بفر_Send( x_اندرونی_دھارا_بفر_Handle, pv_Tx_انکڑے, x_انکڑے_لمائی_بائٹاں, x_Ticks_منزل_Wait );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_Receive_Impl( دھارا_بفر_Handle_t x_دھارا_بفر,
                                             فراغ * pv_Rx_انکڑے,
                                             size_t x_بفر_لمائی_بائٹاں,
                                             TickType_t x_Ticks_منزل_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_دھارا_بفر_Receive_Impl( دھارا_بفر_Handle_t x_دھارا_بفر,
                                             فراغ * pv_Rx_انکڑے,
                                             size_t x_بفر_لمائی_بائٹاں,
                                             TickType_t x_Ticks_منزل_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Is_Rx_انکڑے_بفر_Writeable = pdFALSE;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = pdFALSE;

            إذا( pv_Rx_انکڑے != عدم )
            {
                x_Is_Rx_انکڑے_بفر_Writeable = x_پورٹ_Is_Authorized_منزل_Access_بفر( pv_Rx_انکڑے,
                                                                            x_بفر_لمائی_بائٹاں,
                                                                            tskMPU_WRITE_PERMISSION );

                إذا( x_Is_Rx_انکڑے_بفر_Writeable == pdTRUE )
                {
                    l_اشاریہ = ( int32_t ) x_دھارا_بفر;

                    إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                        إذا( x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر == pdTRUE )
                        {
                            x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                            إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                            {
                                xReturn = x_دھارا_بفر_Receive( x_اندرونی_دھارا_بفر_Handle, pv_Rx_انکڑے, x_بفر_لمائی_بائٹاں, x_Ticks_منزل_Wait );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        ادھار_Type_t MPU_x_دھارا_بفر_Is_بھریا_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_x_دھارا_بفر_Is_بھریا_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = pdFALSE;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر == pdTRUE )
                {
                    x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                    {
                        xReturn = x_دھارا_بفر_Is_بھریا( x_اندرونی_دھارا_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        ادھار_Type_t MPU_x_دھارا_بفر_Is_خالی_تھاواں_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_x_دھارا_بفر_Is_خالی_تھاواں_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = pdFALSE;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر == pdTRUE )
                {
                    x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                    {
                        xReturn = x_دھارا_بفر_Is_خالی_تھاواں( x_اندرونی_دھارا_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_Spaces_دستیاب_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_دھارا_بفر_Spaces_دستیاب_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = pdFALSE;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر == pdTRUE )
                {
                    x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                    {
                        xReturn = x_دھارا_بفر_Spaces_دستیاب( x_اندرونی_دھارا_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_بائٹاں_دستیاب_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_دھارا_بفر_بائٹاں_دستیاب_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = pdFALSE;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر == pdTRUE )
                {
                    x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                    {
                        xReturn = x_دھارا_بفر_بائٹاں_دستیاب( x_اندرونی_دھارا_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        ادھار_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level_Impl( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                         size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

        ادھار_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level_Impl( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                         size_t xTriggerLevel ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = pdFALSE;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر == pdTRUE )
                {
                    x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                    {
                        xReturn = x_دھارا_بفر_سیٹ_Trigger_Level( x_اندرونی_دھارا_بفر_Handle, xTriggerLevel );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;
            ادھار_Type_t x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = pdFALSE;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر = x_پورٹ_Is_Authorized_منزل_Access_Kernel_Object( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_Calling_Task_Is_Authorized_منزل_Access_دھارا_بفر == pdTRUE )
                {
                    x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                    إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                    {
                        xReturn = x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں( x_اندرونی_دھارا_بفر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Stream Buffer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_ونڈ == 1 ) && ( config_USE_دھارا_BUFFERS == 1 ) )

        دھارا_بفر_Handle_t MPU_x_دھارا_بفر_Generic_Create( size_t x_بفر_ناپ_بائٹاں,
                                                             size_t x_Trigger_Level_بائٹاں,
                                                             ادھار_Type_t x_دھارا_بفر_Type,
                                                             دھارا_بفر_Callback_Function_t pxSendCompletedCallback,
                                                             دھارا_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            دھارا_بفر_Handle_t x_External_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == عدم ) &&
                          ( pxReceiveCompletedCallback == عدم ) );

            إذا( ( pxSendCompletedCallback == عدم ) &&
                ( pxReceiveCompletedCallback == عدم ) )
            {
                l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

                إذا( l_اشاریہ != -1 )
                {
                    x_اندرونی_دھارا_بفر_Handle = x_دھارا_بفر_Generic_Create( x_بفر_ناپ_بائٹاں,
                                                                              x_Trigger_Level_بائٹاں,
                                                                              x_دھارا_بفر_Type,
                                                                              عدم,
                                                                              عدم );

                    إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                    {
                        MPU_Store_دھارا_بفر_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_دھارا_بفر_Handle );
                        x_External_دھارا_بفر_Handle = ( دھارا_بفر_Handle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                    }
                    وإلا
                    {
                        MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                    }
                }
            }
            وإلا
            {
                trace_دھارا_بفر_CREATE_FAILED( x_دھارا_بفر_Type );
                x_External_دھارا_بفر_Handle = عدم;
            }

            أرجع x_External_دھارا_بفر_Handle;
        }

    #جے_انت /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ونڈ == 1 ) && ( config_USE_دھارا_BUFFERS == 1 ) )

        دھارا_بفر_Handle_t MPU_x_دھارا_بفر_Generic_Create_Static( size_t x_بفر_ناپ_بائٹاں,
                                                                   size_t x_Trigger_Level_بائٹاں,
                                                                   ادھار_Type_t x_دھارا_بفر_Type,
                                                                   uint8_t * ثابت puc_دھارا_بفر_Storage_Area,
                                                                   Static_دھارا_بفر_t * ثابت px_Static_دھارا_بفر,
                                                                   دھارا_بفر_Callback_Function_t pxSendCompletedCallback,
                                                                   دھارا_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            دھارا_بفر_Handle_t x_External_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == عدم ) &&
                          ( pxReceiveCompletedCallback == عدم ) );

            إذا( ( pxSendCompletedCallback == عدم ) &&
                ( pxReceiveCompletedCallback == عدم ) )
            {
                l_اشاریہ = MPU_Get_Free_اشاریہ_وچ_Kernel_Object_Pool();

                إذا( l_اشاریہ != -1 )
                {
                    x_اندرونی_دھارا_بفر_Handle = x_دھارا_بفر_Generic_Create_Static( x_بفر_ناپ_بائٹاں,
                                                                                    x_Trigger_Level_بائٹاں,
                                                                                    x_دھارا_بفر_Type,
                                                                                    puc_دھارا_بفر_Storage_Area,
                                                                                    px_Static_دھارا_بفر,
                                                                                    عدم,
                                                                                    عدم );

                    إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                    {
                        MPU_Store_دھارا_بفر_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_دھارا_بفر_Handle );
                        x_External_دھارا_بفر_Handle = ( دھارا_بفر_Handle_t ) CONVERT_منزل_EXTERNAL_اشاریہ( l_اشاریہ );
                    }
                    وإلا
                    {
                        MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( l_اشاریہ );
                    }
                }
            }
            وإلا
            {
                trace_دھارا_بفر_CREATE_STATIC_FAILED( xReturn, x_دھارا_بفر_Type );
                x_External_دھارا_بفر_Handle = عدم;
            }

            أرجع x_External_دھارا_بفر_Handle;
        }

    #جے_انت /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        فراغ MPU_v_دھارا_بفر_Delete( دھارا_بفر_Handle_t x_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                {
                    v_دھارا_بفر_Delete( x_اندرونی_دھارا_بفر_Handle );
                }

                MPU_سیٹ_اشاریہ_Free_وچ_Kernel_Object_Pool( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );
            }
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        ادھار_Type_t MPU_x_دھارا_بفر_Reset( دھارا_بفر_Handle_t x_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                {
                    xReturn = x_دھارا_بفر_Reset( x_اندرونی_دھارا_بفر_Handle );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_ونڈ == 1 ) && ( config_USE_دھارا_BUFFERS == 1 ) )

        ادھار_Type_t MPU_x_دھارا_بفر_Get_Static_Buffers( دھارا_بفر_Handle_t x_دھارا_Buffers,
                                                      uint8_t * ppuc_دھارا_بفر_Storage_Area,
                                                      Static_دھارا_بفر_t * ppx_Static_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_دھارا_Buffers;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                {
                    xReturn = MPU_x_دھارا_بفر_Get_Static_Buffers( x_اندرونی_دھارا_بفر_Handle, ppuc_دھارا_بفر_Storage_Area, ppx_Static_دھارا_بفر );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

    size_t MPU_x_دھارا_بفر_Send_From_ISR( دھارا_بفر_Handle_t x_دھارا_بفر,
                                         ثابت فراغ * pv_Tx_انکڑے,
                                         size_t x_انکڑے_لمائی_بائٹاں,
                                         ادھار_Type_t * ثابت px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
        int32_t l_اشاریہ;

        l_اشاریہ = ( int32_t ) x_دھارا_بفر;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
            {
                xReturn = x_دھارا_بفر_Send_From_ISR( x_اندرونی_دھارا_بفر_Handle, pv_Tx_انکڑے, x_انکڑے_لمائی_بائٹاں, px_Higher_ترجیح_Task_Woken );
            }
        }

        أرجع xReturn;
    }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

    size_t MPU_x_دھارا_بفر_Receive_From_ISR( دھارا_بفر_Handle_t x_دھارا_بفر,
                                            فراغ * pv_Rx_انکڑے,
                                            size_t x_بفر_لمائی_بائٹاں,
                                            ادھار_Type_t * ثابت px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
        int32_t l_اشاریہ;

        l_اشاریہ = ( int32_t ) x_دھارا_بفر;

        إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

            إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
            {
                xReturn = x_دھارا_بفر_Receive_From_ISR( x_اندرونی_دھارا_بفر_Handle, pv_Rx_انکڑے, x_بفر_لمائی_بائٹاں, px_Higher_ترجیح_Task_Woken );
            }
        }

        أرجع xReturn;
    }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        ادھار_Type_t MPU_x_دھارا_بفر_Send_Completed_From_ISR( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                          ادھار_Type_t * px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                {
                    xReturn = x_دھارا_بفر_Send_Completed_From_ISR( x_اندرونی_دھارا_بفر_Handle, px_Higher_ترجیح_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        ادھار_Type_t MPU_x_دھارا_بفر_Receive_Completed_From_ISR( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                             ادھار_Type_t * px_Higher_ترجیح_Task_Woken ) /*PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFALSE;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                {
                    xReturn = x_دھارا_بفر_Receive_Completed_From_ISR( x_اندرونی_دھارا_بفر_Handle, px_Higher_ترجیح_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

    #إذا ( config_USE_دھارا_BUFFERS == 1 )

        ادھار_Type_t MPU_x_دھارا_بفر_Reset_From_ISR( دھارا_بفر_Handle_t x_دھارا_بفر ) /*PRIVILEGED_FUNCTION */
        {
            ادھار_Type_t xReturn = pdFAIL;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = عدم;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            إذا( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_منزل_اندرونی_اشاریہ( l_اشاریہ ) );

                إذا( x_اندرونی_دھارا_بفر_Handle != عدم )
                {
                    xReturn = x_دھارا_بفر_Reset_From_ISR( x_اندرونی_دھارا_بفر_Handle );
                }
            }

            أرجع xReturn;
        }

    #جے_انت /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h. */

    #إذا configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #ضمن "application_defined_privileged_functions.h"
    #جے_انت
/*-----------------------------------------------------------*/

/**
 * @brief Array of system call implementation functions.
 *
 * The index in the array MUST match the corresponding system call number
 * defined in mpu_wrappers.h.
 */
    PRIVILEGED_انکڑے UBaseType_t uxSystemCallImplementations[ عدد_SYSTEM_CALLS ] =
    {
        #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_xTaskGenericNotifyImpl,                     /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyWaitImpl,                 /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #جے_انت

        #إذا ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_xTimerGenericCommandFromTaskImpl,           /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #جے_انت

        #إذا ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_گروہ_Wait_بٹ_Impl,                    /* SYSTEM_CALL_xEventGroupWaitBits. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupWaitBits. */
        #جے_انت

        /* The system calls above this line take 5 parameters. */

        #إذا ( INCLUDE_xTaskDelayUntil == 1 )
            ( UBaseType_t ) MPU_xTaskDelayUntilImpl,                        /* SYSTEM_CALL_xTaskDelayUntil. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskDelayUntil. */
        #جے_انت

        #إذا ( INCLUDE_xTaskAbortDelay == 1 )
            ( UBaseType_t ) MPU_xTaskAbortDelayImpl,                        /* SYSTEM_CALL_xTaskAbortDelay. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskAbortDelay. */
        #جے_انت

        #إذا ( INCLUDE_vTaskDelay == 1 )
            ( UBaseType_t ) MPU_vTaskDelayImpl,                             /* SYSTEM_CALL_vTaskDelay. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskDelay. */
        #جے_انت

        #إذا ( INCLUDE_ux_Task_ترجیح_Get == 1 )
            ( UBaseType_t ) MPU_ux_Task_ترجیح_Get_Impl,                      /* SYSTEM_CALL_uxTaskPriorityGet. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskPriorityGet. */
        #جے_انت

        #إذا ( INCLUDE_eTaskGetState == 1 )
            ( UBaseType_t ) MPU_eTaskGetStateImpl,                          /* SYSTEM_CALL_eTaskGetState. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_eTaskGetState. */
        #جے_انت

        #إذا ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_vTaskGetInfoImpl,                           /* SYSTEM_CALL_vTaskGetInfo. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskGetInfo. */
        #جے_انت

        #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
            ( UBaseType_t ) MPU_xTaskGetIdleTaskHandleImpl,                 /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #جے_انت

        #إذا ( INCLUDE_vTaskSuspend == 1 )
            ( UBaseType_t ) MPU_vTaskSuspendImpl,                           /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) MPU_vTaskResumeImpl,                            /* SYSTEM_CALL_vTaskResume. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskResume. */
        #جے_انت

        ( UBaseType_t ) MPU_x_Task_Get_Tick_گنتی_Impl,                          /* SYSTEM_CALL_xTaskGetTickCount. */
        ( UBaseType_t ) MPU_ux_Task_Get_نمبر_دا_Tasks_Impl,                     /* SYSTEM_CALL_uxTaskGetNumberOfTasks. */

        #إذا ( config_GENERATE_لگاتار_ویلا_STATS == 1 )
            ( UBaseType_t ) MPU_ul_Task_Get_لگاتار_ویلا_Counter_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) MPU_ul_Task_Get_لگاتار_ویلا_Percent_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #جے_انت

        #إذا ( ( config_GENERATE_لگاتار_ویلا_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_لگاتار_ویلا_Percent_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_لگاتار_ویلا_Counter_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #جے_انت

        #إذا ( config_USE_APPLICATION_TASK_ٹیگ == 1 )
            ( UBaseType_t ) MPU_v_Task_سیٹ_Application_Task_ٹیگ_Impl,             /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) MPU_x_Task_Get_Application_Task_ٹیگ_Impl,             /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #جے_انت

        #إذا ( config_عدد_THREAD_LOCAL_STORAGE_سوچکاں != 0 )
            ( UBaseType_t ) MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر_Impl,      /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر_Impl,     /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #جے_انت

        #إذا ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_uxTaskGetSystemStateImpl,                   /* SYSTEM_CALL_uxTaskGetSystemState. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetSystemState. */
        #جے_انت

        #إذا ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark_Impl,            /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #جے_انت

        #إذا ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark2 == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2_Impl,           /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #جے_انت

        #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )
            ( UBaseType_t ) MPU_xTaskGetCurrentTaskHandleImpl,              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #جے_انت

        #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )
            ( UBaseType_t ) MPU_xTaskGetSchedulerStateImpl,                 /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #جے_انت

        ( UBaseType_t ) MPU_v_Task_سیٹ_ویلا_باہرلا_State_Impl,                       /* SYSTEM_CALL_vTaskSetTimeOutState. */
        ( UBaseType_t ) MPU_x_Task_Check_For_ویلا_باہرلا_Impl,                       /* SYSTEM_CALL_xTaskCheckForTimeOut. */

        #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_ulTaskGenericNotifyTakeImpl,                /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyStateClearImpl,           /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) MPU_ul_Task_Generic_Notify_قدر_Clear_Impl,          /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #جے_انت

        ( UBaseType_t ) MPU_x_قطار_Generic_Send_Impl,                          /* SYSTEM_CALL_xQueueGenericSend. */
        ( UBaseType_t ) MPU_ux_قطار_Messages_اڈیک_Impl,                     /* SYSTEM_CALL_uxQueueMessagesWaiting. */
        ( UBaseType_t ) MPU_ux_قطار_Spaces_دستیاب_Impl,                     /* SYSTEM_CALL_uxQueueSpacesAvailable. */
        ( UBaseType_t ) MPU_x_قطار_Receive_Impl,                              /* SYSTEM_CALL_xQueueReceive. */
        ( UBaseType_t ) MPU_x_قطار_Peek_Impl,                                 /* SYSTEM_CALL_xQueuePeek. */
        ( UBaseType_t ) MPU_x_قطار_Semaphore_Take_Impl,                        /* SYSTEM_CALL_xQueueSemaphoreTake. */

        #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
            ( UBaseType_t ) MPU_x_قطار_Get_Mutex_Holder_Impl,                   /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #جے_انت

        #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )
            ( UBaseType_t ) MPU_x_قطار_Take_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) MPU_x_قطار_Give_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #جے_انت

        #إذا ( config_USE_قطار_SETS == 1 )
            ( UBaseType_t ) MPU_x_قطار_Select_From_سیٹ_Impl,                    /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) MPU_x_قطار_جوڑو_منزل_سیٹ_Impl,                         /* SYSTEM_CALL_xQueueAddToSet. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueAddToSet. */
        #جے_انت

        #إذا config_قطار_REGISTRY_ناپ > 0
            ( UBaseType_t ) MPU_v_قطار_جوڑو_منزل_Registry_Impl,                    /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) MPU_v_قطار_Unregister_قطار_Impl,                  /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) MPU_pc_قطار_Get_Name_Impl,                         /* SYSTEM_CALL_pcQueueGetName. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcQueueGetName. */
        #جے_انت

        #إذا ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_pvTimerGetTimerIDImpl,                      /* SYSTEM_CALL_pvTimerGetTimerID. */
            ( UBaseType_t ) MPU_v_Timer_سیٹ_Timer_IDImpl,                       /* SYSTEM_CALL_vTimerSetTimerID. */
            ( UBaseType_t ) MPU_x_Timer_Is_Timer_سرگرم_Impl,                    /* SYSTEM_CALL_xTimerIsTimerActive. */
            ( UBaseType_t ) MPU_xTimerGetTimerDaemonTaskHandleImpl,         /* SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle. */
            ( UBaseType_t ) MPU_pcTimerGetNameImpl,                         /* SYSTEM_CALL_pcTimerGetName. */
            ( UBaseType_t ) MPU_v_Timer_سیٹ_Reload_منوال_Impl,                    /* SYSTEM_CALL_vTimerSetReloadMode. */
            ( UBaseType_t ) MPU_x_Timer_Get_Reload_منوال_Impl,                    /* SYSTEM_CALL_xTimerGetReloadMode. */
            ( UBaseType_t ) MPU_ux_Timer_Get_Reload_منوال_Impl,                   /* SYSTEM_CALL_uxTimerGetReloadMode. */
            ( UBaseType_t ) MPU_xTimerGetPeriodImpl,                        /* SYSTEM_CALL_xTimerGetPeriod. */
            ( UBaseType_t ) MPU_x_Timer_Get_Expiry_ویلا_Impl,                    /* SYSTEM_CALL_xTimerGetExpiryTime. */
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
        #جے_انت

        #إذا ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_گروہ_Clear_بٹ_Impl,                   /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) MPU_x_Event_گروہ_سیٹ_بٹ_Impl,                     /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) MPU_x_Event_گروہ_Sync_Impl,                        /* SYSTEM_CALL_xEventGroupSync. */

            #إذا ( configUSE_TRACE_FACILITY == 1 )
                ( UBaseType_t ) MPU_ux_Event_گروہ_Get_نمبر_Impl,              /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) MPU_v_Event_گروہ_سیٹ_نمبر_Impl,               /* SYSTEM_CALL_vEventGroupSetNumber. */
            #وإلا
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_vEventGroupSetNumber. */
            #جے_انت
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSync. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxEventGroupGetNumber. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vEventGroupSetNumber. */
        #جے_انت

        #إذا ( config_USE_دھارا_BUFFERS == 1 )
            ( UBaseType_t ) MPU_x_دھارا_بفر_Send_Impl,                      /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) MPU_x_دھارا_بفر_Receive_Impl,                   /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) MPU_x_دھارا_بفر_Is_بھریا_Impl,                    /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) MPU_x_دھارا_بفر_Is_خالی_تھاواں_Impl,                   /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) MPU_x_دھارا_بفر_Spaces_دستیاب_Impl,           /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) MPU_x_دھارا_بفر_بائٹاں_دستیاب_Impl,            /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) MPU_x_دھارا_بفر_سیٹ_Trigger_Level_Impl,           /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) MPU_x_دھارا_بفر_اگلا_سنیہا_لمائی_بائٹاں_Impl     /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #جے_انت

    };
/*-----------------------------------------------------------*/

#جے_انت /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/
