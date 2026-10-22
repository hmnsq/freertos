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
#تعریف_کن MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "queue.h"
#ضمن "timers.h"
#ضمن "event_groups.h"
#ضمن "stream_buffer.h"
#ضمن "mpu_prototypes.h"
#ضمن "mpu_syscall_numbers.h"

#لغو_تعریف MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#إذا ( ( پورت_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #اگر_تعریف_نشده config_PROTECTED_KERNEL_OBJECT_POOL_اندازه
        #خطا config_PROTECTED_KERNEL_OBJECT_POOL_اندازه must be defined مقصد بیشینه عدد از kernel objects درون the application.
    #پایان_اگر

/**
 * @brief Offset added to the index before returning to the user.
 *
 * If the actual handle is stored at index i, ( i + INDEX_OFFSET )
 * is returned to the user.
 */
    #تعریف_کن شاخص_جابه_جایی    1

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
        OpaqueObjectHandle_t x_داخلی_Object_Handle;
        uint32_t ulKernelObjectType;
        فراغ * pv_Kernel_Object_داده;
    } KernelObject_t;

/**
 * @brief Kernel object types.
 */
    #تعریف_کن KERNEL_OBJECT_TYPE_INVALID          ( 0UL )
    #تعریف_کن KERNEL_OBJECT_TYPE_صف            ( 1UL )
    #تعریف_کن KERNEL_OBJECT_TYPE_TASK             ( 2UL )
    #تعریف_کن KERNEL_OBJECT_TYPE_جریان_میانگیر    ( 3UL )
    #تعریف_کن KERNEL_OBJECT_TYPE_EVENT_گروه      ( 4UL )
    #تعریف_کن KERNEL_OBJECT_TYPE_TIMER            ( 5UL )

/**
 * @brief Checks whether an external index is valid or not.
 */
    #تعریف_کن IS_EXTERNAL_شاخص_VALID( l_شاخص )   \
    ( ( ( ( l_شاخص ) >= شاخص_جابه_جایی ) &&       \
        ( ( l_شاخص ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_اندازه + شاخص_جابه_جایی ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Checks whether an internal index is valid or not.
 */
    #تعریف_کن IS_داخلی_شاخص_VALID( l_شاخص )   \
    ( ( ( ( l_شاخص ) >= 0 ) &&                  \
        ( ( l_شاخص ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_اندازه ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Converts an internal index into external.
 */
    #تعریف_کن CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص )    ( ( l_شاخص ) + شاخص_جابه_جایی )

/**
 * @brief Converts an external index into internal.
 */
    #تعریف_کن CONVERT_مقصد_داخلی_شاخص( l_شاخص )    ( ( l_شاخص ) - شاخص_جابه_جایی )

/**
 * @brief Max value that fits in a UBaseType_t type.
 */
    #تعریف_کن mpuUBASETYPE_MAX    ( ~( ( UBaseType_t ) 0 ) )

/**
 * @brief Check if multiplying a and b will result in overflow.
 */
    #تعریف_کن mpu_MULTIPLY_BASETYPE_WILL_سرریز( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( mpuUBASETYPE_MAX / ( a ) ) ) )

/**
 * @brief Get the index of a free slot in the kernel object pool.
 *
 * If a free slot is found, this function marks the slot as
 * "not free".
 *
 * @return Index of a free slot is returned, if a free slot is
 *         found. Otherwise -1 is returned.
 */
    ساكن int32_t MPU_Get_Free_شاخص_درون_Kernel_Object_Pool( فراغ ) PRIVILEGED_FUNCTION;

/**
 * @brief Set the given index as free in the kernel object pool.
 *
 * @param lIndex The index to set as free.
 */
    ساكن فراغ MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( int32_t l_شاخص ) PRIVILEGED_FUNCTION;

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
    ساكن فراغ MPU_Store_Handle_And_داده_At_شاخص( int32_t l_شاخص,
                                               OpaqueObjectHandle_t xHandle,
                                               فراغ * pv_Kernel_Object_داده,
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
        ساكن فراغ MPU_TimerCallback( TimerHandle_t x_داخلی_Handle ) PRIVILEGED_FUNCTION;

    #پایان_اگر /* #if ( configUSE_TIMERS == 1 ) */

/*
 * Wrappers to keep all the casting in one place.
 */
    #تعریف_کن MPU_Store_صف_Handle_At_شاخص( l_شاخص, xHandle )                 MPU_Store_Handle_And_داده_At_شاخص( ( l_شاخص ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_صف )
    #تعریف_کن MPU_Get_صف_Handle_At_شاخص( l_شاخص )                            ( صف_Handle_t ) MPU_Get_Handle_At_شاخص( ( l_شاخص ), KERNEL_OBJECT_TYPE_صف )

    #إذا ( config_USE_صف_SETS == 1 )
        #تعریف_کن MPU_Store_صف_مجموعه_Handle_At_شاخص( l_شاخص, xHandle )          MPU_Store_Handle_And_داده_At_شاخص( ( l_شاخص ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_صف )
        #تعریف_کن MPU_Get_صف_مجموعه_Handle_At_شاخص( l_شاخص )                     ( صف_مجموعه_Handle_t ) MPU_Get_Handle_At_شاخص( ( l_شاخص ), KERNEL_OBJECT_TYPE_صف )
        #تعریف_کن MPU_Store_صف_مجموعه_Member_Handle_At_شاخص( l_شاخص, xHandle )    MPU_Store_Handle_And_داده_At_شاخص( ( l_شاخص ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_صف )
        #تعریف_کن MPU_Get_صف_مجموعه_Member_Handle_At_شاخص( l_شاخص )               ( صف_مجموعه_Member_Handle_t ) MPU_Get_Handle_At_شاخص( ( l_شاخص ), KERNEL_OBJECT_TYPE_صف )
        #تعریف_کن MPU_Get_شاخص_For_صف_مجموعه_Member_Handle( xHandle )             MPU_Get_شاخص_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_صف )
    #پایان_اگر

/*
 * Wrappers to keep all the casting in one place for Task APIs.
 */
    #تعریف_کن MPU_Store_Task_Handle_At_شاخص( l_شاخص, xHandle )            MPU_Store_Handle_And_داده_At_شاخص( ( l_شاخص ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_TASK )
    #تعریف_کن MPU_Get_Task_Handle_At_شاخص( l_شاخص )                       ( TaskHandle_t ) MPU_Get_Handle_At_شاخص( ( l_شاخص ), KERNEL_OBJECT_TYPE_TASK )
    #تعریف_کن MPU_Get_شاخص_For_Task_Handle( xHandle )                     MPU_Get_شاخص_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TASK )

    #إذا ( configUSE_EVENT_GROUPS == 1 )
/*
 * Wrappers to keep all the casting in one place for Event Group APIs.
 */
        #تعریف_کن MPU_Store_Event_گروه_Handle_At_شاخص( l_شاخص, xHandle )      MPU_Store_Handle_And_داده_At_شاخص( ( l_شاخص ), ( OpaqueObjectHandle_t ) ( xHandle ), عدم, KERNEL_OBJECT_TYPE_EVENT_گروه )
        #تعریف_کن MPU_Get_Event_گروه_Handle_At_شاخص( l_شاخص )                 ( Event_گروه_Handle_t ) MPU_Get_Handle_At_شاخص( ( l_شاخص ), KERNEL_OBJECT_TYPE_EVENT_گروه )
        #تعریف_کن MPU_Get_شاخص_For_Event_گروه_Handle( xHandle )               MPU_Get_شاخص_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_EVENT_گروه )

    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */

    #إذا ( config_USE_جریان_BUFFERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Stream Buffer APIs.
 */
        #تعریف_کن MPU_Store_جریان_میانگیر_Handle_At_شاخص( l_شاخص, xHandle )    MPU_Store_Handle_And_داده_At_شاخص( ( l_شاخص ), ( OpaqueObjectHandle_t ) ( xHandle), عدم, KERNEL_OBJECT_TYPE_جریان_میانگیر )
        #تعریف_کن MPU_Get_جریان_میانگیر_Handle_At_شاخص( l_شاخص )               ( جریان_میانگیر_Handle_t ) MPU_Get_Handle_At_شاخص( ( l_شاخص ), KERNEL_OBJECT_TYPE_جریان_میانگیر )
        #تعریف_کن MPU_Get_شاخص_For_جریان_میانگیر_Handle( xHandle )             MPU_Get_شاخص_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_جریان_میانگیر )

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

    #إذا ( configUSE_TIMERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Timer APIs.
 */
        #تعریف_کن MPU_Store_Timer_Handle_At_شاخص( l_شاخص, xHandle, pxApplicationCallback )    MPU_Store_Handle_And_داده_At_شاخص( ( l_شاخص ), ( OpaqueObjectHandle_t ) ( xHandle ), ( فراغ * ) ( pxApplicationCallback ), KERNEL_OBJECT_TYPE_TIMER )
        #تعریف_کن MPU_Get_Timer_Handle_At_شاخص( l_شاخص )                                      ( TimerHandle_t ) MPU_Get_Handle_At_شاخص( ( l_شاخص ), KERNEL_OBJECT_TYPE_TIMER )
        #تعریف_کن MPU_Get_شاخص_For_Timer_Handle( xHandle )                                    MPU_Get_شاخص_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TIMER )

    #پایان_اگر /* #if ( configUSE_TIMERS == 1 ) */

/*-----------------------------------------------------------*/

/**
 * @brief Kernel object pool.
 */
    PRIVILEGED_داده ساكن KernelObject_t xKernelObjectPool[ config_PROTECTED_KERNEL_OBJECT_POOL_اندازه ] = { 0 };
/*-----------------------------------------------------------*/

    ساكن int32_t MPU_Get_Free_شاخص_درون_Kernel_Object_Pool( فراغ ) /* PRIVILEGED_FUNCTION */
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
                إذا( xKernelObjectPool[ i ].x_داخلی_Object_Handle == عدم )
                {
                    /* Mark this index as not free. */
                    xKernelObjectPool[ i ].x_داخلی_Object_Handle = ( OpaqueObjectHandle_t ) ( ~0U );
                    l_Free_شاخص = i;
                    اكسر;
                }
            }
        }
        ( فراغ ) xTaskResumeAll();

        أرجع l_Free_شاخص;
    }
/*-----------------------------------------------------------*/

    ساكن فراغ MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( int32_t l_شاخص ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_داخلی_شاخص_VALID( l_شاخص ) != pdFALSE );

        taskENTER_CRITICAL();
        {
            xKernelObjectPool[ l_شاخص ].x_داخلی_Object_Handle = عدم;
            xKernelObjectPool[ l_شاخص ].ulKernelObjectType = KERNEL_OBJECT_TYPE_INVALID;
            xKernelObjectPool[ l_شاخص ].pv_Kernel_Object_داده = عدم;
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
            إذا( ( xKernelObjectPool[ i ].x_داخلی_Object_Handle == xHandle ) &&
                ( xKernelObjectPool[ i ].ulKernelObjectType == ulKernelObjectType ) )
            {
                l_شاخص = i;
                اكسر;
            }
        }

        أرجع l_شاخص;
    }
/*-----------------------------------------------------------*/

    ساكن فراغ MPU_Store_Handle_And_داده_At_شاخص( int32_t l_شاخص,
                                               OpaqueObjectHandle_t xHandle,
                                               فراغ * pv_Kernel_Object_داده,
                                               uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_داخلی_شاخص_VALID( l_شاخص ) != pdFALSE );
        xKernelObjectPool[ l_شاخص ].x_داخلی_Object_Handle = xHandle;
        xKernelObjectPool[ l_شاخص ].ulKernelObjectType = ulKernelObjectType;
        xKernelObjectPool[ l_شاخص ].pv_Kernel_Object_داده = pv_Kernel_Object_داده;
    }
/*-----------------------------------------------------------*/

    ساكن OpaqueObjectHandle_t MPU_Get_Handle_At_شاخص( int32_t l_شاخص,
                                                      uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        OpaqueObjectHandle_t xObjectHandle = عدم;

        configASSERT( IS_داخلی_شاخص_VALID( l_شاخص ) != pdFALSE );

        إذا( xKernelObjectPool[ l_شاخص ].ulKernelObjectType == ulKernelObjectType )
        {
            xObjectHandle = xKernelObjectPool[ l_شاخص ].x_داخلی_Object_Handle;
        }

        أرجع xObjectHandle;
    }
/*-----------------------------------------------------------*/

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        فراغ v_Grant_Access_مقصد_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                         int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;

            إذا( IS_EXTERNAL_شاخص_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                إذا( xExternalTaskHandle == عدم )
                {
                    v_پورت_Grant_Access_مقصد_Kernel_Object( xExternalTaskHandle, CONVERT_مقصد_داخلی_شاخص( lExternalKernelObjectHandle ) );
                }
                وإلا
                {
                    l_External_Task_شاخص = ( int32_t ) xExternalTaskHandle;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_External_Task_شاخص ) != pdFALSE )
                    {
                        x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_External_Task_شاخص ) );

                        إذا( x_داخلی_Task_Handle != عدم )
                        {
                            v_پورت_Grant_Access_مقصد_Kernel_Object( x_داخلی_Task_Handle,
                                                            CONVERT_مقصد_داخلی_شاخص( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #پایان_اگر /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        فراغ v_Revoke_Access_مقصد_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                          int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;

            إذا( IS_EXTERNAL_شاخص_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                إذا( xExternalTaskHandle == عدم )
                {
                    v_پورت_Revoke_Access_مقصد_Kernel_Object( xExternalTaskHandle, CONVERT_مقصد_داخلی_شاخص( lExternalKernelObjectHandle ) );
                }
                وإلا
                {
                    l_External_Task_شاخص = ( int32_t ) xExternalTaskHandle;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_External_Task_شاخص ) != pdFALSE )
                    {
                        x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_External_Task_شاخص ) );

                        إذا( x_داخلی_Task_Handle != عدم )
                        {
                            v_پورت_Revoke_Access_مقصد_Kernel_Object( x_داخلی_Task_Handle,
                                                             CONVERT_مقصد_داخلی_شاخص( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #پایان_اگر /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ساكن فراغ MPU_TimerCallback( TimerHandle_t x_داخلی_Handle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t i, l_شاخص = -1;
            TimerHandle_t xExternalHandle = عدم;
            TimerCallbackFunction_t px_Application_Call_پشت = عدم;

            /* Coming from the timer task and therefore, should be valid. */
            configASSERT( x_داخلی_Handle != عدم );

            لكل( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_اندازه; i++ )
            {
                إذا( ( ( TimerHandle_t ) xKernelObjectPool[ i ].x_داخلی_Object_Handle == x_داخلی_Handle ) &&
                    ( xKernelObjectPool[ i ].ulKernelObjectType == KERNEL_OBJECT_TYPE_TIMER ) )
                {
                    l_شاخص = i;
                    اكسر;
                }
            }

            configASSERT( l_شاخص != -1 );
            xExternalHandle = ( TimerHandle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );

            px_Application_Call_پشت = ( TimerCallbackFunction_t ) xKernelObjectPool[ l_شاخص ].pv_Kernel_Object_داده;
            px_Application_Call_پشت( xExternalHandle );
        }

    #پایان_اگر /* #if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for tasks APIs.                   */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskDelayUntil == 1 )

        پایه_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ثابت px_قبلی_Wake_زمان,
                                            TickType_t x_زمان_Increment ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ثابت px_قبلی_Wake_زمان,
                                            TickType_t x_زمان_Increment ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            پایه_Type_t x_Is_قبلی_Wake_زمان_Accessible = pdFALSE;

            إذا( ( px_قبلی_Wake_زمان != عدم ) && ( x_زمان_Increment > 0U ) )
            {
                x_Is_قبلی_Wake_زمان_Accessible = x_پورت_Is_Authorized_مقصد_Access_میانگیر( px_قبلی_Wake_زمان,
                                                                                 حجم( TickType_t ),
                                                                                 ( tskMPU_WRITE_PERMISSION | tskMPU_READ_PERMISSION ) );

                إذا( x_Is_قبلی_Wake_زمان_Accessible == pdTRUE )
                {
                    xReturn = xTaskDelayUntil( px_قبلی_Wake_زمان, x_زمان_Increment );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskAbortDelay == 1 )

        پایه_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) xTask;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                {
                    x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Task_Handle != عدم )
                    {
                        xReturn = xTaskAbortDelay( x_داخلی_Task_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelay == 1 )

        فراغ MPU_vTaskDelayImpl( TickType_t x_Ticks_مقصد_Delay ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskDelayImpl( TickType_t x_Ticks_مقصد_Delay ) /* PRIVILEGED_FUNCTION */
        {
            vTaskDelay( x_Ticks_مقصد_Delay );
        }

    #پایان_اگر /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_اولویت_Get == 1 )

        UBaseType_t MPU_ux_Task_اولویت_Get_Impl( ثابت TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_اولویت_Get_Impl( ثابت TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;

            إذا( pxTask == عدم )
            {
                uxReturn = ux_Task_اولویت_Get( pxTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) pxTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_داخلی_Task_Handle != عدم )
                        {
                            uxReturn = ux_Task_اولویت_Get( x_داخلی_Task_Handle );
                        }
                    }
                }
            }

            أرجع uxReturn;
        }

    #پایان_اگر /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            eTaskState eReturn = eInvalid;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            l_شاخص = ( int32_t ) pxTask;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                {
                    x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Task_Handle != عدم )
                    {
                        eReturn = eTaskGetState( x_داخلی_Task_Handle );
                    }
                }
            }

            أرجع eReturn;
        }

    #پایان_اگر /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        فراغ MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_وضعیت_t * px_Task_وضعیت,
                                   پایه_Type_t x_Get_Free_پشته_Space,
                                   eTaskState eState ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_وضعیت_t * px_Task_وضعیت,
                                   پایه_Type_t x_Get_Free_پشته_Space,
                                   eTaskState eState ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            پایه_Type_t x_Is_Task_وضعیت_Writeable = pdFALSE;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            x_Is_Task_وضعیت_Writeable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( px_Task_وضعیت,
                                                                      حجم( Task_وضعیت_t ),
                                                                      tskMPU_WRITE_PERMISSION );

            إذا( x_Is_Task_وضعیت_Writeable == pdTRUE )
            {
                إذا( xTask == عدم )
                {
                    vTaskGetInfo( xTask, px_Task_وضعیت, x_Get_Free_پشته_Space, eState );
                }
                وإلا
                {
                    l_شاخص = ( int32_t ) xTask;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                        {
                            x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                            إذا( x_داخلی_Task_Handle != عدم )
                            {
                                vTaskGetInfo( x_داخلی_Task_Handle, px_Task_وضعیت, x_Get_Free_پشته_Space, eState );
                            }
                        }
                    }
                }
            }
        }

    #پایان_اگر /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( فراغ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xIdleTaskHandle = عدم;

            xIdleTaskHandle = xTaskGetIdleTaskHandle();

            أرجع xIdleTaskHandle;
        }

    #پایان_اگر /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )

        فراغ MPU_vTaskSuspendImpl( TaskHandle_t px_Task_مقصد_Suspend ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskSuspendImpl( TaskHandle_t px_Task_مقصد_Suspend ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            إذا( px_Task_مقصد_Suspend == عدم )
            {
                vTaskSuspend( px_Task_مقصد_Suspend );
            }
            وإلا
            {
                /* After the scheduler starts, only privileged tasks are allowed
                 * to suspend other tasks. */
                #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )
                    إذا( ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) || ( پورت_IS_TASK_PRIVILEGED() == pdTRUE ) )
                #وإلا
                    إذا( پورت_IS_TASK_PRIVILEGED() == pdTRUE )
                #پایان_اگر
                {
                    l_شاخص = ( int32_t ) px_Task_مقصد_Suspend;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                        {
                            x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                            إذا( x_داخلی_Task_Handle != عدم )
                            {
                                vTaskSuspend( x_داخلی_Task_Handle );
                            }
                        }
                    }
                }
            }
        }

    #پایان_اگر /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskSuspend == 1 )

        فراغ MPU_vTaskResumeImpl( TaskHandle_t px_Task_مقصد_Resume ) PRIVILEGED_FUNCTION;

        فراغ MPU_vTaskResumeImpl( TaskHandle_t px_Task_مقصد_Resume ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            l_شاخص = ( int32_t ) px_Task_مقصد_Resume;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                {
                    x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Task_Handle != عدم )
                    {
                        vTaskResume( x_داخلی_Task_Handle );
                    }
                }
            }
        }

    #پایان_اگر /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_شمار_Impl( فراغ ) PRIVILEGED_FUNCTION;

    TickType_t MPU_x_Task_Get_Tick_شمار_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        TickType_t xReturn;

        xReturn = x_Task_Get_Tick_شمار();

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_عدد_از_Tasks_Impl( فراغ ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Task_Get_عدد_از_Tasks_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn;

        uxReturn = ux_Task_Get_عدد_از_Tasks();

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_پیاپی_زمان_STATS == 1 )

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Counter_Impl( ثابت TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Counter_Impl( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_پیاپی_زمان_COUNTER_TYPE xReturn = 0;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                xReturn = ul_Task_Get_پیاپی_زمان_Counter( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_داخلی_Task_Handle != عدم )
                        {
                            xReturn = ul_Task_Get_پیاپی_زمان_Counter( x_داخلی_Task_Handle );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_GENERATE_پیاپی_زمان_STATS == 1 )

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Percent_Impl( ثابت TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_پیاپی_زمان_Percent_Impl( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_پیاپی_زمان_COUNTER_TYPE xReturn = 0;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                xReturn = ul_Task_Get_پیاپی_زمان_Percent( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_داخلی_Task_Handle != عدم )
                        {
                            xReturn = ul_Task_Get_پیاپی_زمان_Percent( x_داخلی_Task_Handle );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_پیاپی_زمان_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent_Impl( فراغ ) PRIVILEGED_FUNCTION;

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            config_پیاپی_زمان_COUNTER_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_پیاپی_زمان_Percent();

            أرجع xReturn;
        }

    #پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_GENERATE_پیاپی_زمان_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter_Impl( فراغ ) PRIVILEGED_FUNCTION;

        config_پیاپی_زمان_COUNTER_TYPE MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter_Impl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            config_پیاپی_زمان_COUNTER_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_پیاپی_زمان_Counter();

            أرجع xReturn;
        }

    #پایان_اگر /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )

        فراغ MPU_v_Task_مجموعه_Application_Task_برچسب_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_برچسب_مقدار ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Task_مجموعه_Application_Task_برچسب_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_برچسب_مقدار ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                v_Task_مجموعه_Application_Task_برچسب( xTask, px_برچسب_مقدار );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_داخلی_Task_Handle != عدم )
                        {
                            v_Task_مجموعه_Application_Task_برچسب( x_داخلی_Task_Handle, px_برچسب_مقدار );
                        }
                    }
                }
            }
        }

    #پایان_اگر /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_برچسب_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_برچسب_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = عدم;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                xReturn = x_Task_Get_Application_Task_برچسب( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_داخلی_Task_Handle != عدم )
                        {
                            xReturn = x_Task_Get_Application_Task_برچسب( x_داخلی_Task_Handle );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_رقم_THREAD_LOCAL_STORAGE_اشارهگرها != 0 )

        فراغ MPU_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر_Impl( TaskHandle_t x_Task_مقصد_مجموعه,
                                                        پایه_Type_t x_شاخص,
                                                        فراغ * pv_مقدار ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر_Impl( TaskHandle_t x_Task_مقصد_مجموعه,
                                                        پایه_Type_t x_شاخص,
                                                        فراغ * pv_مقدار ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            إذا( x_Task_مقصد_مجموعه == عدم )
            {
                v_Task_مجموعه_Thread_Local_Storage_اشاره_گر( x_Task_مقصد_مجموعه, x_شاخص, pv_مقدار );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) x_Task_مقصد_مجموعه;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_داخلی_Task_Handle != عدم )
                        {
                            v_Task_مجموعه_Thread_Local_Storage_اشاره_گر( x_داخلی_Task_Handle, x_شاخص, pv_مقدار );
                        }
                    }
                }
            }
        }

    #پایان_اگر /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_رقم_THREAD_LOCAL_STORAGE_اشارهگرها != 0 )

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر_Impl( TaskHandle_t x_Task_مقصد_Query,
                                                           پایه_Type_t x_شاخص ) PRIVILEGED_FUNCTION;

        فراغ * MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر_Impl( TaskHandle_t x_Task_مقصد_Query,
                                                           پایه_Type_t x_شاخص ) /* PRIVILEGED_FUNCTION */
        {
            فراغ * pvReturn = عدم;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            إذا( x_Task_مقصد_Query == عدم )
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_اشاره_گر( x_Task_مقصد_Query, x_شاخص );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) x_Task_مقصد_Query;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_داخلی_Task_Handle != عدم )
                        {
                            pvReturn = pv_Task_Get_Thread_Local_Storage_اشاره_گر( x_داخلی_Task_Handle, x_شاخص );
                        }
                    }
                }
            }

            أرجع pvReturn;
        }

    #پایان_اگر /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_وضعیت_t * px_Task_وضعیت_Array,
                                                  UBaseType_t ux_Array_اندازه,
                                                  config_پیاپی_زمان_COUNTER_TYPE * pul_مجموع_پیاپی_زمان ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_وضعیت_t * px_Task_وضعیت_Array,
                                                  UBaseType_t ux_Array_اندازه,
                                                  config_پیاپی_زمان_COUNTER_TYPE * pul_مجموع_پیاپی_زمان ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            پایه_Type_t x_Is_Task_وضعیت_Array_Writeable = pdFALSE;
            پایه_Type_t x_Is_مجموع_پیاپی_زمان_Writeable = pdFALSE;

            إذا( mpu_MULTIPLY_BASETYPE_WILL_سرریز( حجم( Task_وضعیت_t ), ux_Array_اندازه ) == 0 )
            {
                x_Is_Task_وضعیت_Array_Writeable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( px_Task_وضعیت_Array,
                                                                               حجم( Task_وضعیت_t ) * ( size_t ) ux_Array_اندازه,
                                                                               tskMPU_WRITE_PERMISSION );

                إذا( pul_مجموع_پیاپی_زمان != عدم )
                {
                    x_Is_مجموع_پیاپی_زمان_Writeable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( pul_مجموع_پیاپی_زمان,
                                                                                حجم( config_پیاپی_زمان_COUNTER_TYPE ),
                                                                                tskMPU_WRITE_PERMISSION );
                }

                إذا( ( x_Is_Task_وضعیت_Array_Writeable == pdTRUE ) &&
                    ( ( pul_مجموع_پیاپی_زمان == عدم ) || ( x_Is_مجموع_پیاپی_زمان_Writeable == pdTRUE ) ) )
                {
                    uxReturn = uxTaskGetSystemState( px_Task_وضعیت_Array, ux_Array_اندازه, pul_مجموع_پیاپی_زمان );
                }
            }

            أرجع uxReturn;
        }

    #پایان_اگر /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_پشته_بالا_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_پشته_بالا_Water_Mark_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_Get_پشته_بالا_Water_Mark_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_Get_پشته_بالا_Water_Mark( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_داخلی_Task_Handle != عدم )
                        {
                            uxReturn = ux_Task_Get_پشته_بالا_Water_Mark( x_داخلی_Task_Handle );
                        }
                    }
                }
            }

            أرجع uxReturn;
        }

    #پایان_اگر /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_Get_پشته_بالا_Water_Mark2 == 1 )

        config_پشته_عمق_TYPE MPU_ux_Task_Get_پشته_بالا_Water_Mark2_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_پشته_عمق_TYPE MPU_ux_Task_Get_پشته_بالا_Water_Mark2_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_پشته_عمق_TYPE uxReturn = 0;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_Get_پشته_بالا_Water_Mark2( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_داخلی_Task_Handle != عدم )
                        {
                            uxReturn = ux_Task_Get_پشته_بالا_Water_Mark2( x_داخلی_Task_Handle );
                        }
                    }
                }
            }

            أرجع uxReturn;
        }

    #پایان_اگر /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( فراغ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            TaskHandle_t xExternalTaskHandle = عدم;
            int32_t l_شاخص;

            x_داخلی_Task_Handle = xTaskGetCurrentTaskHandle();

            إذا( x_داخلی_Task_Handle != عدم )
            {
                l_شاخص = MPU_Get_شاخص_For_Task_Handle( x_داخلی_Task_Handle );

                إذا( l_شاخص != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
            }

            أرجع xExternalTaskHandle;
        }

    #پایان_اگر /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )

        پایه_Type_t MPU_xTaskGetSchedulerStateImpl( فراغ ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_xTaskGetSchedulerStateImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = taskSCHEDULER_NOT_STARTED;

            xReturn = xTaskGetSchedulerState();

            أرجع xReturn;
        }

    #پایان_اگر /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    فراغ MPU_v_Task_مجموعه_زمان_بیرون_State_Impl( زمان_بیرون_t * ثابت px_زمان_بیرون ) PRIVILEGED_FUNCTION;

    فراغ MPU_v_Task_مجموعه_زمان_بیرون_State_Impl( زمان_بیرون_t * ثابت px_زمان_بیرون ) /* PRIVILEGED_FUNCTION */
    {
        پایه_Type_t x_Is_زمان_بیرون_Writeable = pdFALSE;

        إذا( px_زمان_بیرون != عدم )
        {
            x_Is_زمان_بیرون_Writeable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( px_زمان_بیرون,
                                                                   حجم( زمان_بیرون_t ),
                                                                   tskMPU_WRITE_PERMISSION );

            إذا( x_Is_زمان_بیرون_Writeable == pdTRUE )
            {
                v_Task_مجموعه_زمان_بیرون_State( px_زمان_بیرون );
            }
        }
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_Task_Check_For_زمان_بیرون_Impl( زمان_بیرون_t * ثابت px_زمان_بیرون,
                                             TickType_t * ثابت px_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

    پایه_Type_t MPU_x_Task_Check_For_زمان_بیرون_Impl( زمان_بیرون_t * ثابت px_زمان_بیرون,
                                             TickType_t * ثابت px_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
    {
        پایه_Type_t xReturn = pdFALSE;
        پایه_Type_t x_Is_زمان_بیرون_Writeable = pdFALSE;
        پایه_Type_t x_Is_Ticks_مقصد_Wait_Writeable = pdFALSE;

        إذا( ( px_زمان_بیرون != عدم ) && ( px_Ticks_مقصد_Wait != عدم ) )
        {
            x_Is_زمان_بیرون_Writeable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( px_زمان_بیرون,
                                                                   حجم( زمان_بیرون_t ),
                                                                   tskMPU_WRITE_PERMISSION );
            x_Is_Ticks_مقصد_Wait_Writeable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( px_Ticks_مقصد_Wait,
                                                                       حجم( TickType_t ),
                                                                       tskMPU_WRITE_PERMISSION );

            إذا( ( x_Is_زمان_بیرون_Writeable == pdTRUE ) && ( x_Is_Ticks_مقصد_Wait_Writeable == pdTRUE ) )
            {
                xReturn = x_Task_Check_For_زمان_بیرون( px_زمان_بیرون, px_Ticks_مقصد_Wait );
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        پایه_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_مقصد_Notify,
                                           UBaseType_t ux_شاخص_مقصد_Notify,
                                           uint32_t ul_مقدار,
                                           eNotifyAction eAction,
                                           uint32_t * pul_قبلی_Notification_مقدار ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyParams_t xParams;

            xParams.x_Task_مقصد_Notify = x_Task_مقصد_Notify;
            xParams.ux_شاخص_مقصد_Notify = ux_شاخص_مقصد_Notify;
            xParams.ul_مقدار = ul_مقدار;
            xParams.eAction = eAction;
            xParams.pul_قبلی_Notification_مقدار = pul_قبلی_Notification_مقدار;

            xReturn = MPU_x_Task_Generic_Notify_مدخل( &( xParams ) );

            أرجع xReturn;
        }

        پایه_Type_t MPU_xTaskGenericNotifyImpl( ثابت xTaskGenericNotifyParams_t * pxParams ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_xTaskGenericNotifyImpl( ثابت xTaskGenericNotifyParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            پایه_Type_t x_Is_قبلی_Notification_مقدار_Writeable = pdFALSE;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;
            پایه_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( pxParams,
                                                                      حجم( xTaskGenericNotifyParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( ( pxParams->ux_شاخص_مقصد_Notify < configTASK_NOTIFICATION_ARRAY_ENTRIES ) &&
                    ( ( pxParams->eAction == eNoAction ) ||
                      ( pxParams->eAction == e_مجموعه_بیتها ) ||
                      ( pxParams->eAction == eIncrement ) ||
                      ( pxParams->eAction == e_مجموعه_مقدار_With_Overwrite ) ||
                      ( pxParams->eAction == e_مجموعه_مقدار_Without_Overwrite ) ) )
                {
                    إذا( pxParams->pul_قبلی_Notification_مقدار != عدم )
                    {
                        x_Is_قبلی_Notification_مقدار_Writeable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( pxParams->pul_قبلی_Notification_مقدار,
                                                                                                 حجم( uint32_t ),
                                                                                                 tskMPU_WRITE_PERMISSION );
                    }

                    إذا( ( pxParams->pul_قبلی_Notification_مقدار == عدم ) ||
                        ( x_Is_قبلی_Notification_مقدار_Writeable == pdTRUE ) )
                    {
                        l_شاخص = ( int32_t ) ( pxParams->x_Task_مقصد_Notify );

                        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                            إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                            {
                                x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                                إذا( x_داخلی_Task_Handle != عدم )
                                {
                                    xReturn = xTaskGenericNotify( x_داخلی_Task_Handle,
                                                                  pxParams->ux_شاخص_مقصد_Notify,
                                                                  pxParams->ul_مقدار,
                                                                  pxParams->eAction,
                                                                  pxParams->pul_قبلی_Notification_مقدار );
                                }
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        پایه_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_شاخص_مقصد_Wait_On,
                                               uint32_t ul_بیتها_مقصد_Clear_On_مدخل,
                                               uint32_t ul_بیتها_مقصد_Clear_On_Exit,
                                               uint32_t * pul_Notification_مقدار,
                                               TickType_t x_Ticks_مقصد_Wait )
        {
            پایه_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyWaitParams_t xParams;

            xParams.ux_شاخص_مقصد_Wait_On = ux_شاخص_مقصد_Wait_On;
            xParams.ul_بیتها_مقصد_Clear_On_مدخل = ul_بیتها_مقصد_Clear_On_مدخل;
            xParams.ul_بیتها_مقصد_Clear_On_Exit = ul_بیتها_مقصد_Clear_On_Exit;
            xParams.pul_Notification_مقدار = pul_Notification_مقدار;
            xParams.x_Ticks_مقصد_Wait = x_Ticks_مقصد_Wait;

            xReturn = MPU_x_Task_Generic_Notify_Wait_مدخل( &( xParams ) );

            أرجع xReturn;
        }

        پایه_Type_t MPU_xTaskGenericNotifyWaitImpl( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_xTaskGenericNotifyWaitImpl( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            پایه_Type_t x_Is_Notification_مقدار_Writable = pdFALSE;
            پایه_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( pxParams,
                                                                      حجم( xTaskGenericNotifyWaitParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( pxParams->ux_شاخص_مقصد_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
                {
                    إذا( pxParams->pul_Notification_مقدار != عدم )
                    {
                        x_Is_Notification_مقدار_Writable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( pxParams->pul_Notification_مقدار,
                                                                                        حجم( uint32_t ),
                                                                                        tskMPU_WRITE_PERMISSION );
                    }

                    إذا( ( pxParams->pul_Notification_مقدار == عدم ) ||
                        ( x_Is_Notification_مقدار_Writable == pdTRUE ) )
                    {
                        xReturn = xTaskGenericNotifyWait( pxParams->ux_شاخص_مقصد_Wait_On,
                                                          pxParams->ul_بیتها_مقصد_Clear_On_مدخل,
                                                          pxParams->ul_بیتها_مقصد_Clear_On_Exit,
                                                          pxParams->pul_Notification_مقدار,
                                                          pxParams->x_Ticks_مقصد_Wait );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_شاخص_مقصد_Wait_On,
                                                  پایه_Type_t x_Clear_شمار_On_Exit,
                                                  TickType_t x_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_شاخص_مقصد_Wait_On,
                                                  پایه_Type_t x_Clear_شمار_On_Exit,
                                                  TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;

            إذا( ux_شاخص_مقصد_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ulReturn = ulTaskGenericNotifyTake( ux_شاخص_مقصد_Wait_On, x_Clear_شمار_On_Exit, x_Ticks_مقصد_Wait );
            }

            أرجع ulReturn;
        }

    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        پایه_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_شاخص_مقصد_Clear ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_شاخص_مقصد_Clear ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            إذا( ux_شاخص_مقصد_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                إذا( xTask == عدم )
                {
                    xReturn = xTaskGenericNotifyStateClear( xTask, ux_شاخص_مقصد_Clear );
                }
                وإلا
                {
                    l_شاخص = ( int32_t ) xTask;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                        {
                            x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                            إذا( x_داخلی_Task_Handle != عدم )
                            {
                                xReturn = xTaskGenericNotifyStateClear( x_داخلی_Task_Handle, ux_شاخص_مقصد_Clear );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_مقدار_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_شاخص_مقصد_Clear,
                                                        uint32_t ul_بیتها_مقصد_Clear ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ul_Task_Generic_Notify_مقدار_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_شاخص_مقصد_Clear,
                                                        uint32_t ul_بیتها_مقصد_Clear ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            إذا( ux_شاخص_مقصد_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                إذا( xTask == عدم )
                {
                    ulReturn = ul_Task_Generic_Notify_مقدار_Clear( xTask, ux_شاخص_مقصد_Clear, ul_بیتها_مقصد_Clear );
                }
                وإلا
                {
                    l_شاخص = ( int32_t ) xTask;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                        {
                            x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                            إذا( x_داخلی_Task_Handle != عدم )
                            {
                                ulReturn = ul_Task_Generic_Notify_مقدار_Clear( x_داخلی_Task_Handle, ux_شاخص_مقصد_Clear, ul_بیتها_مقصد_Clear );
                            }
                        }
                    }
                }
            }

            أرجع ulReturn;
        }

    #پایان_اگر /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Task APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_تخصیص == 1 )

        پایه_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_کد,
                                    ثابت حرف * ثابت pcName,
                                    ثابت config_پشته_عمق_TYPE ux_پشته_عمق,
                                    فراغ * pvParameters,
                                    UBaseType_t ux_اولویت,
                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                /* xTaskCreate() can only be used to create privileged tasks in MPU port. */
                إذا( ( ux_اولویت & پورت_PRIVILEGE_بیت ) != 0 )
                {
                    xReturn = xTaskCreate( pv_Task_کد, pcName, ux_پشته_عمق, pvParameters, ux_اولویت, &( x_داخلی_Task_Handle ) );

                    إذا( ( xReturn == pdPASS ) && ( x_داخلی_Task_Handle != عدم ) )
                    {
                        MPU_Store_Task_Handle_At_شاخص( l_شاخص, x_داخلی_Task_Handle );

                        إذا( pxCreatedTask != عدم )
                        {
                            *pxCreatedTask = ( TaskHandle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                        }
                    }
                    وإلا
                    {
                        MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_تخصیص == 1 )

        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_کد,
                                            ثابت حرف * ثابت pcName,
                                            ثابت config_پشته_عمق_TYPE ux_پشته_عمق,
                                            فراغ * ثابت pvParameters,
                                            UBaseType_t ux_اولویت,
                                            پشته_Type_t * ثابت pux_پشته_میانگیر,
                                            StaticTask_t * ثابت px_Task_میانگیر ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xExternalTaskHandle = عدم;
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_داخلی_Task_Handle = xTaskCreateStatic( px_Task_کد, pcName, ux_پشته_عمق, pvParameters, ux_اولویت, pux_پشته_میانگیر, px_Task_میانگیر );

                إذا( x_داخلی_Task_Handle != عدم )
                {
                    MPU_Store_Task_Handle_At_شاخص( l_شاخص, x_داخلی_Task_Handle );

                    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        إذا( ( ux_اولویت & پورت_PRIVILEGE_بیت ) == 0 )
                        {
                            v_پورت_Grant_Access_مقصد_Kernel_Object( x_داخلی_Task_Handle, l_شاخص );
                        }
                    }
                    #پایان_اگر

                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع xExternalTaskHandle;
        }

    #پایان_اگر /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_vTaskDelete == 1 )

        فراغ MPU_vTaskDelete( TaskHandle_t px_Task_مقصد_Delete ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            int32_t l_شاخص;

            إذا( px_Task_مقصد_Delete == عدم )
            {
                x_داخلی_Task_Handle = xTaskGetCurrentTaskHandle();
                l_شاخص = MPU_Get_شاخص_For_Task_Handle( x_داخلی_Task_Handle );

                إذا( l_شاخص != -1 )
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }

                vTaskDelete( x_داخلی_Task_Handle );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) px_Task_مقصد_Delete;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Task_Handle != عدم )
                    {
                        MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );
                        vTaskDelete( x_داخلی_Task_Handle );
                    }
                }
            }
        }

    #پایان_اگر /* #if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/


    #إذا ( INCLUDE_v_Task_اولویت_مجموعه == 1 )

        فراغ MPU_v_Task_اولویت_مجموعه( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_اولویت ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            int32_t l_شاخص;

            إذا( pxTask == عدم )
            {
                v_Task_اولویت_مجموعه( pxTask, ux_New_اولویت );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) pxTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Task_Handle != عدم )
                    {
                        v_Task_اولویت_مجموعه( x_داخلی_Task_Handle, ux_New_اولویت );
                    }
                }
            }
        }

    #پایان_اگر /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_xTaskGetHandle == 1 )

        TaskHandle_t MPU_xTaskGetHandle( ثابت حرف * pc_Name_مقصد_Query ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            TaskHandle_t xExternalTaskHandle = عدم;
            int32_t l_شاخص;

            x_داخلی_Task_Handle = xTaskGetHandle( pc_Name_مقصد_Query );

            إذا( x_داخلی_Task_Handle != عدم )
            {
                l_شاخص = MPU_Get_شاخص_For_Task_Handle( x_داخلی_Task_Handle );

                إذا( l_شاخص != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
            }

            أرجع xExternalTaskHandle;
        }

    #پایان_اگر /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/


    #إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )

        پایه_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     فراغ * pvParameter ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Task_Handle != عدم )
                    {
                        xReturn = xTaskCallApplicationTaskHook( x_داخلی_Task_Handle, pvParameter );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_تخصیص == 1 )

        پایه_Type_t MPU_xTaskCreateRestricted( ثابت TaskParameters_t * ثابت pxTaskDefinition,
                                              TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                xReturn = xTaskCreateRestricted( pxTaskDefinition, &( x_داخلی_Task_Handle ) );

                إذا( ( xReturn == pdPASS ) && ( x_داخلی_Task_Handle != عدم ) )
                {
                    MPU_Store_Task_Handle_At_شاخص( l_شاخص, x_داخلی_Task_Handle );

                    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        إذا( ( pxTaskDefinition->ux_اولویت & پورت_PRIVILEGE_بیت ) == 0 )
                        {
                            v_پورت_Grant_Access_مقصد_Kernel_Object( x_داخلی_Task_Handle, l_شاخص );
                        }
                    }
                    #پایان_اگر

                    إذا( pxCreatedTask != عدم )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                    }
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_تخصیص == 1 )

        پایه_Type_t MPU_xTaskCreateRestrictedStatic( ثابت TaskParameters_t * ثابت pxTaskDefinition,
                                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                xReturn = xTaskCreateRestrictedStatic( pxTaskDefinition, &( x_داخلی_Task_Handle ) );

                إذا( ( xReturn == pdPASS ) && ( x_داخلی_Task_Handle != عدم ) )
                {
                    MPU_Store_Task_Handle_At_شاخص( l_شاخص, x_داخلی_Task_Handle );

                    #إذا ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        إذا( ( pxTaskDefinition->ux_اولویت & پورت_PRIVILEGE_بیت ) == 0 )
                        {
                            v_پورت_Grant_Access_مقصد_Kernel_Object( x_داخلی_Task_Handle, l_شاخص );
                        }
                    }
                    #پایان_اگر

                    إذا( pxCreatedTask != عدم )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                    }
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    فراغ MPU_vTaskAllocateMPURegions( TaskHandle_t x_Task_مقصد_Modify,
                                      ثابت حافظه_Region_t * ثابت xRegions ) /* PRIVILEGED_FUNCTION */
    {
        TaskHandle_t x_داخلی_Task_Handle = عدم;
        int32_t l_شاخص;

        إذا( x_Task_مقصد_Modify == عدم )
        {
            vTaskAllocateMPURegions( x_Task_مقصد_Modify, xRegions );
        }
        وإلا
        {
            l_شاخص = ( int32_t ) x_Task_مقصد_Modify;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_Task_Handle != عدم )
                {
                    vTaskAllocateMPURegions( x_داخلی_Task_Handle, xRegions );
                }
            }
        }
    }
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_تخصیص == 1 )

        پایه_Type_t MPU_xTaskGetStaticBuffers( TaskHandle_t xTask,
                                              پشته_Type_t ** ppux_پشته_میانگیر,
                                              StaticTask_t ** ppx_Task_میانگیر ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_داخلی_Task_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t xReturn = pdFALSE;

            إذا( xTask == عدم )
            {
                x_داخلی_Task_Handle = xTaskGetCurrentTaskHandle();
                xReturn = xTaskGetStaticBuffers( x_داخلی_Task_Handle, ppux_پشته_میانگیر, ppx_Task_میانگیر );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Task_Handle != عدم )
                    {
                        xReturn = xTaskGetStaticBuffers( x_داخلی_Task_Handle, ppux_پشته_میانگیر, ppx_Task_میانگیر );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    حرف * MPU_pcTaskGetName( TaskHandle_t x_Task_مقصد_Query ) /* PRIVILEGED_FUNCTION */
    {
        حرف * pcReturn = عدم;
        int32_t l_شاخص;
        TaskHandle_t x_داخلی_Task_Handle = عدم;

        إذا( x_Task_مقصد_Query == عدم )
        {
            pcReturn = pcTaskGetName( x_Task_مقصد_Query );
        }
        وإلا
        {
            l_شاخص = ( int32_t ) x_Task_مقصد_Query;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_Task_Handle != عدم )
                {
                    pcReturn = pcTaskGetName( x_داخلی_Task_Handle );
                }
            }
        }

        أرجع pcReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( INCLUDE_ux_Task_اولویت_Get == 1 )

        UBaseType_t MPU_ux_Task_اولویت_Get_From_ISR( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_اولویت_Get_From_ISR( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Task_Handle != عدم )
                    {
                        uxReturn = ux_Task_اولویت_Get_From_ISR( x_داخلی_Task_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #پایان_اگر /* #if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_ux_Task_اولویت_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_پایه_اولویت_Get( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_پایه_اولویت_Get( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Task_Handle != عدم )
                    {
                        uxReturn = ux_Task_پایه_اولویت_Get( x_داخلی_Task_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #پایان_اگر /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_ux_Task_اولویت_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_پایه_اولویت_Get_From_ISR( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                uxReturn = ux_Task_پایه_اولویت_Get_From_ISR( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Task_Handle != عدم )
                    {
                        uxReturn = ux_Task_پایه_اولویت_Get_From_ISR( x_داخلی_Task_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #پایان_اگر /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

        پایه_Type_t MPU_xTaskResumeFromISR( TaskHandle_t x_Task_مقصد_Resume ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;

            l_شاخص = ( int32_t ) x_Task_مقصد_Resume;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_Task_Handle != عدم )
                {
                    xReturn = xTaskResumeFromISR( x_داخلی_Task_Handle );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )*/
/*---------------------------------------------------------------------------------------*/

    #إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_برچسب_From_ISR( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = عدم;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;

            إذا( xTask == عدم )
            {
                xReturn = x_Task_Get_Application_Task_برچسب_From_ISR( xTask );
            }
            وإلا
            {
                l_شاخص = ( int32_t ) xTask;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Task_Handle != عدم )
                    {
                        xReturn = x_Task_Get_Application_Task_برچسب_From_ISR( x_داخلی_Task_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        پایه_Type_t MPU_xTaskGenericNotifyFromISR( TaskHandle_t x_Task_مقصد_Notify,
                                                  UBaseType_t ux_شاخص_مقصد_Notify,
                                                  uint32_t ul_مقدار,
                                                  eNotifyAction eAction,
                                                  uint32_t * pul_قبلی_Notification_مقدار,
                                                  پایه_Type_t * px_Higher_اولویت_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;

            l_شاخص = ( int32_t ) x_Task_مقصد_Notify;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_Task_Handle != عدم )
                {
                    xReturn = xTaskGenericNotifyFromISR( x_داخلی_Task_Handle, ux_شاخص_مقصد_Notify, ul_مقدار, eAction, pul_قبلی_Notification_مقدار, px_Higher_اولویت_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )

        فراغ MPU_vTaskGenericNotifyGiveFromISR( TaskHandle_t x_Task_مقصد_Notify,
                                                UBaseType_t ux_شاخص_مقصد_Notify,
                                                پایه_Type_t * px_Higher_اولویت_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            TaskHandle_t x_داخلی_Task_Handle = عدم;

            l_شاخص = ( int32_t ) x_Task_مقصد_Notify;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_Task_Handle = MPU_Get_Task_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_Task_Handle != عدم )
                {
                    vTaskGenericNotifyGiveFromISR( x_داخلی_Task_Handle, ux_شاخص_مقصد_Notify, px_Higher_اولویت_Task_Woken );
                }
            }
        }
    #پایان_اگر /*#if ( configUSE_TASK_NOTIFICATIONS == 1 )*/
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for queue APIs.                   */
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Generic_Send_Impl( صف_Handle_t x_صف,
                                          ثابت فراغ * ثابت pv_قلم_مقصد_صف,
                                          TickType_t x_Ticks_مقصد_Wait,
                                          پایه_Type_t xCopyPosition ) PRIVILEGED_FUNCTION;

    پایه_Type_t MPU_x_صف_Generic_Send_Impl( صف_Handle_t x_صف,
                                          ثابت فراغ * ثابت pv_قلم_مقصد_صف,
                                          TickType_t x_Ticks_مقصد_Wait,
                                          پایه_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_شاخص;
        صف_Handle_t x_داخلی_صف_Handle = عدم;
        پایه_Type_t xReturn = pdFAIL;
        پایه_Type_t x_Is_قلم_مقصد_صف_Readable = pdFALSE;
        پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف = pdFALSE;
        UBaseType_t ux_صف_قلم_اندازه, ux_صف_درازی;

        l_شاخص = ( int32_t ) x_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_مقصد_Access_صف = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_Calling_Task_Is_Authorized_مقصد_Access_صف == pdTRUE )
            {
                x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_صف_Handle != عدم )
                {
                    ux_صف_قلم_اندازه = ux_صف_Get_صف_قلم_اندازه( x_داخلی_صف_Handle );
                    ux_صف_درازی = ux_صف_Get_صف_درازی( x_داخلی_صف_Handle );

                    إذا( ( !( ( pv_قلم_مقصد_صف == عدم ) && ( ux_صف_قلم_اندازه != ( UBaseType_t ) 0U ) ) ) &&
                        ( !( ( xCopyPosition == صف_OVERWRITE ) && ( ux_صف_درازی != ( UBaseType_t ) 1U ) ) )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_مقصد_Wait != 0U ) ) )
                        #پایان_اگر
                        )
                    {
                        إذا( pv_قلم_مقصد_صف != عدم )
                        {
                            x_Is_قلم_مقصد_صف_Readable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( pv_قلم_مقصد_صف,
                                                                                      ux_صف_قلم_اندازه,
                                                                                      tskMPU_READ_PERMISSION );
                        }

                        إذا( ( pv_قلم_مقصد_صف == عدم ) || ( x_Is_قلم_مقصد_صف_Readable == pdTRUE ) )
                        {
                            xReturn = x_صف_Generic_Send( x_داخلی_صف_Handle, pv_قلم_مقصد_صف, x_Ticks_مقصد_Wait, xCopyPosition );
                        }
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_صف_Messages_انتظار_Impl( ثابت صف_Handle_t px_صف ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_صف_Messages_انتظار_Impl( ثابت صف_Handle_t px_صف ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_شاخص;
        صف_Handle_t x_داخلی_صف_Handle = عدم;
        UBaseType_t uxReturn = 0;
        پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف = pdFALSE;

        l_شاخص = ( int32_t ) px_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_مقصد_Access_صف = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_Calling_Task_Is_Authorized_مقصد_Access_صف == pdTRUE )
            {
                x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_صف_Handle != عدم )
                {
                    uxReturn = ux_صف_Messages_انتظار( x_داخلی_صف_Handle );
                }
            }
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_صف_Spaces_موجود_Impl( ثابت صف_Handle_t x_صف ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_صف_Spaces_موجود_Impl( ثابت صف_Handle_t x_صف ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_شاخص;
        صف_Handle_t x_داخلی_صف_Handle = عدم;
        UBaseType_t uxReturn = 0;
        پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف = pdFALSE;

        l_شاخص = ( int32_t ) x_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_مقصد_Access_صف = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_Calling_Task_Is_Authorized_مقصد_Access_صف == pdTRUE )
            {
                x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_صف_Handle != عدم )
                {
                    uxReturn = ux_صف_Spaces_موجود( x_داخلی_صف_Handle );
                }
            }
        }

        أرجع uxReturn;
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Receive_Impl( صف_Handle_t px_صف,
                                      فراغ * ثابت pv_میانگیر,
                                      TickType_t x_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

    پایه_Type_t MPU_x_صف_Receive_Impl( صف_Handle_t px_صف,
                                      فراغ * ثابت pv_میانگیر,
                                      TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_شاخص;
        صف_Handle_t x_داخلی_صف_Handle = عدم;
        پایه_Type_t xReturn = pdFAIL;
        پایه_Type_t x_Is_Receive_میانگیر_Writable = pdFALSE;
        پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف = pdFALSE;
        UBaseType_t ux_صف_قلم_اندازه;

        l_شاخص = ( int32_t ) px_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_مقصد_Access_صف = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_Calling_Task_Is_Authorized_مقصد_Access_صف == pdTRUE )
            {
                x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_صف_Handle != عدم )
                {
                    ux_صف_قلم_اندازه = ux_صف_Get_صف_قلم_اندازه( x_داخلی_صف_Handle );

                    إذا( ( !( ( ( pv_میانگیر ) == عدم ) && ( ux_صف_قلم_اندازه != ( UBaseType_t ) 0U ) ) )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_مقصد_Wait != 0U ) ) )
                        #پایان_اگر
                        )
                    {
                        x_Is_Receive_میانگیر_Writable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( pv_میانگیر,
                                                                                    ux_صف_قلم_اندازه,
                                                                                    tskMPU_WRITE_PERMISSION );

                        إذا( x_Is_Receive_میانگیر_Writable == pdTRUE )
                        {
                            xReturn = x_صف_Receive( x_داخلی_صف_Handle, pv_میانگیر, x_Ticks_مقصد_Wait );
                        }
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Peek_Impl( صف_Handle_t x_صف,
                                   فراغ * ثابت pv_میانگیر,
                                   TickType_t x_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

    پایه_Type_t MPU_x_صف_Peek_Impl( صف_Handle_t x_صف,
                                   فراغ * ثابت pv_میانگیر,
                                   TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_شاخص;
        صف_Handle_t x_داخلی_صف_Handle = عدم;
        پایه_Type_t xReturn = pdFAIL;
        پایه_Type_t x_Is_Receive_میانگیر_Writable = pdFALSE;
        UBaseType_t ux_صف_قلم_اندازه;
        پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف = pdFALSE;

        l_شاخص = ( int32_t ) x_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_مقصد_Access_صف = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_Calling_Task_Is_Authorized_مقصد_Access_صف == pdTRUE )
            {
                x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_صف_Handle != عدم )
                {
                    ux_صف_قلم_اندازه = ux_صف_Get_صف_قلم_اندازه( x_داخلی_صف_Handle );

                    إذا( ( !( ( ( pv_میانگیر ) == عدم ) && ( ux_صف_قلم_اندازه != ( UBaseType_t ) 0U ) ) )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_مقصد_Wait != 0U ) ) )
                        #پایان_اگر
                        )
                    {
                        x_Is_Receive_میانگیر_Writable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( pv_میانگیر,
                                                                                    ux_صف_قلم_اندازه,
                                                                                    tskMPU_WRITE_PERMISSION );

                        إذا( x_Is_Receive_میانگیر_Writable == pdTRUE )
                        {
                            xReturn = x_صف_Peek( x_داخلی_صف_Handle, pv_میانگیر, x_Ticks_مقصد_Wait );
                        }
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Semaphore_Take_Impl( صف_Handle_t x_صف,
                                            TickType_t x_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

    پایه_Type_t MPU_x_صف_Semaphore_Take_Impl( صف_Handle_t x_صف,
                                            TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_شاخص;
        صف_Handle_t x_داخلی_صف_Handle = عدم;
        پایه_Type_t xReturn = pdFAIL;
        UBaseType_t ux_صف_قلم_اندازه;
        پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف = pdFALSE;

        l_شاخص = ( int32_t ) x_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_مقصد_Access_صف = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_Calling_Task_Is_Authorized_مقصد_Access_صف == pdTRUE )
            {
                x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_صف_Handle != عدم )
                {
                    ux_صف_قلم_اندازه = ux_صف_Get_صف_قلم_اندازه( x_داخلی_صف_Handle );

                    إذا( ( ux_صف_قلم_اندازه == 0U )
                        #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_مقصد_Wait != 0U ) ) )
                        #پایان_اگر
                        )
                    {
                        xReturn = x_صف_Semaphore_Take( x_داخلی_صف_Handle, x_Ticks_مقصد_Wait );
                    }
                }
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_صف_Get_Mutex_Holder_Impl( صف_Handle_t xSemaphore ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_x_صف_Get_Mutex_Holder_Impl( صف_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_داخلی_Handle = عدم;
            TaskHandle_t xMutexHolderTaskExternalHandle = عدم;
            int32_t l_شاخص, l_Mutex_Holder_Task_شاخص;
            صف_Handle_t x_داخلی_صف_Handle = عدم;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف = pdFALSE;


            l_شاخص = ( int32_t ) xSemaphore;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_صف = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_صف == pdTRUE )
                {
                    x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_صف_Handle != عدم )
                    {
                        x_Mutex_Holder_Task_داخلی_Handle = x_صف_Get_Mutex_Holder( x_داخلی_صف_Handle );

                        إذا( x_Mutex_Holder_Task_داخلی_Handle != عدم )
                        {
                            l_Mutex_Holder_Task_شاخص = MPU_Get_شاخص_For_Task_Handle( x_Mutex_Holder_Task_داخلی_Handle );

                            إذا( l_Mutex_Holder_Task_شاخص != -1 )
                            {
                                xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_مقصد_EXTERNAL_شاخص( l_Mutex_Holder_Task_شاخص ) );
                            }
                        }
                    }
                }
            }

            أرجع xMutexHolderTaskExternalHandle;
        }

    #پایان_اگر /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        پایه_Type_t MPU_x_صف_Take_Mutex_Recursive_Impl( صف_Handle_t xMutex,
                                                     TickType_t x_بلوک_زمان ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_x_صف_Take_Mutex_Recursive_Impl( صف_Handle_t xMutex,
                                                     TickType_t x_بلوک_زمان ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف = pdFALSE;
            int32_t l_شاخص;
            صف_Handle_t x_داخلی_صف_Handle = عدم;
            UBaseType_t ux_صف_قلم_اندازه;

            l_شاخص = ( int32_t ) xMutex;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_صف = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_صف == pdTRUE )
                {
                    x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_صف_Handle != عدم )
                    {
                        ux_صف_قلم_اندازه = ux_صف_Get_صف_قلم_اندازه( x_داخلی_صف_Handle );

                        إذا( ux_صف_قلم_اندازه == 0 )
                        {
                            xReturn = x_صف_Take_Mutex_Recursive( x_داخلی_صف_Handle, x_بلوک_زمان );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )

        پایه_Type_t MPU_x_صف_Give_Mutex_Recursive_Impl( صف_Handle_t xMutex ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_x_صف_Give_Mutex_Recursive_Impl( صف_Handle_t xMutex ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف = pdFALSE;
            int32_t l_شاخص;
            صف_Handle_t x_داخلی_صف_Handle = عدم;

            l_شاخص = ( int32_t ) xMutex;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_صف = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_صف == pdTRUE )
                {
                    x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_صف_Handle != عدم )
                    {
                        xReturn = x_صف_Give_Mutex_Recursive( x_داخلی_صف_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_صف_SETS == 1 )

        صف_مجموعه_Member_Handle_t MPU_x_صف_Select_From_مجموعه_Impl( صف_مجموعه_Handle_t x_صف_مجموعه,
                                                            TickType_t x_بلوک_زمان_Ticks ) PRIVILEGED_FUNCTION;

        صف_مجموعه_Member_Handle_t MPU_x_صف_Select_From_مجموعه_Impl( صف_مجموعه_Handle_t x_صف_مجموعه,
                                                            TickType_t x_بلوک_زمان_Ticks ) /* PRIVILEGED_FUNCTION */
        {
            صف_مجموعه_Handle_t x_داخلی_صف_مجموعه_Handle = عدم;
            صف_مجموعه_Member_Handle_t x_Selected_Member_داخلی = عدم;
            صف_مجموعه_Member_Handle_t xSelectedMemberExternal = عدم;
            int32_t l_شاخص_صف_مجموعه, l_شاخص_Selected_Member;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف_مجموعه = pdFALSE;

            l_شاخص_صف_مجموعه = ( int32_t ) x_صف_مجموعه;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص_صف_مجموعه ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_صف_مجموعه = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص_صف_مجموعه ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_صف_مجموعه == pdTRUE )
                {
                    x_داخلی_صف_مجموعه_Handle = MPU_Get_صف_مجموعه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص_صف_مجموعه ) );

                    إذا( x_داخلی_صف_مجموعه_Handle != عدم )
                    {
                        x_Selected_Member_داخلی = x_صف_Select_From_مجموعه( x_داخلی_صف_مجموعه_Handle, x_بلوک_زمان_Ticks );

                        إذا( x_Selected_Member_داخلی != عدم )
                        {
                            l_شاخص_Selected_Member = MPU_Get_شاخص_For_صف_مجموعه_Member_Handle( x_Selected_Member_داخلی );

                            إذا( l_شاخص_Selected_Member != -1 )
                            {
                                xSelectedMemberExternal = ( صف_مجموعه_Member_Handle_t ) ( CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص_Selected_Member ) );
                            }
                        }
                    }
                }
            }

            أرجع xSelectedMemberExternal;
        }

    #پایان_اگر /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_صف_SETS == 1 )

        پایه_Type_t MPU_x_صف_جمع_کن_مقصد_مجموعه_Impl( صف_مجموعه_Member_Handle_t x_صف_Or_Semaphore,
                                           صف_مجموعه_Handle_t x_صف_مجموعه ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_x_صف_جمع_کن_مقصد_مجموعه_Impl( صف_مجموعه_Member_Handle_t x_صف_Or_Semaphore,
                                           صف_مجموعه_Handle_t x_صف_مجموعه ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            صف_مجموعه_Member_Handle_t x_داخلی_صف_مجموعه_Member_Handle = عدم;
            صف_مجموعه_Handle_t x_داخلی_صف_مجموعه_Handle = عدم;
            int32_t l_شاخص_صف_مجموعه, l_شاخص_صف_مجموعه_Member;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف_مجموعه = pdFALSE;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف_مجموعه_Member = pdFALSE;

            l_شاخص_صف_مجموعه = ( int32_t ) x_صف_مجموعه;
            l_شاخص_صف_مجموعه_Member = ( int32_t ) x_صف_Or_Semaphore;

            إذا( ( IS_EXTERNAL_شاخص_VALID( l_شاخص_صف_مجموعه ) != pdFALSE ) &&
                ( IS_EXTERNAL_شاخص_VALID( l_شاخص_صف_مجموعه_Member ) != pdFALSE ) )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_صف_مجموعه = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص_صف_مجموعه ) );
                x_Calling_Task_Is_Authorized_مقصد_Access_صف_مجموعه_Member = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص_صف_مجموعه_Member ) );

                إذا( ( x_Calling_Task_Is_Authorized_مقصد_Access_صف_مجموعه == pdTRUE ) && ( x_Calling_Task_Is_Authorized_مقصد_Access_صف_مجموعه_Member == pdTRUE ) )
                {
                    x_داخلی_صف_مجموعه_Handle = MPU_Get_صف_مجموعه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص_صف_مجموعه ) );
                    x_داخلی_صف_مجموعه_Member_Handle = MPU_Get_صف_مجموعه_Member_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص_صف_مجموعه_Member ) );

                    إذا( ( x_داخلی_صف_مجموعه_Handle != عدم ) && ( x_داخلی_صف_مجموعه_Member_Handle != عدم ) )
                    {
                        xReturn = x_صف_جمع_کن_مقصد_مجموعه( x_داخلی_صف_مجموعه_Member_Handle, x_داخلی_صف_مجموعه_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا config_صف_REGISTRY_اندازه > 0

        فراغ MPU_v_صف_جمع_کن_مقصد_Registry_Impl( صف_Handle_t x_صف,
                                          ثابت حرف * pcName ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_صف_جمع_کن_مقصد_Registry_Impl( صف_Handle_t x_صف,
                                          ثابت حرف * pcName ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            صف_Handle_t x_داخلی_صف_Handle = عدم;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف = pdFALSE;

            l_شاخص = ( int32_t ) x_صف;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_صف = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_صف == pdTRUE )
                {
                    x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_صف_Handle != عدم )
                    {
                        v_صف_جمع_کن_مقصد_Registry( x_داخلی_صف_Handle, pcName );
                    }
                }
            }
        }

    #پایان_اگر /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_صف_REGISTRY_اندازه > 0

        فراغ MPU_v_صف_Unregister_صف_Impl( صف_Handle_t x_صف ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_صف_Unregister_صف_Impl( صف_Handle_t x_صف ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            صف_Handle_t x_داخلی_صف_Handle = عدم;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف = pdFALSE;

            l_شاخص = ( int32_t ) x_صف;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_صف = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_صف == pdTRUE )
                {
                    x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_صف_Handle != عدم )
                    {
                        v_صف_Unregister_صف( x_داخلی_صف_Handle );
                    }
                }
            }
        }

    #پایان_اگر /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #إذا config_صف_REGISTRY_اندازه > 0

        ثابت حرف * MPU_pc_صف_Get_Name_Impl( صف_Handle_t x_صف ) PRIVILEGED_FUNCTION;

        ثابت حرف * MPU_pc_صف_Get_Name_Impl( صف_Handle_t x_صف ) /* PRIVILEGED_FUNCTION */
        {
            ثابت حرف * pcReturn = عدم;
            صف_Handle_t x_داخلی_صف_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_صف = pdFALSE;

            l_شاخص = ( int32_t ) x_صف;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_صف = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_صف == pdTRUE )
                {
                    x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_صف_Handle != عدم )
                    {
                        pcReturn = pc_صف_Get_Name( x_داخلی_صف_Handle );
                    }
                }
            }

            أرجع pcReturn;
        }

    #پایان_اگر /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Queue APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    فراغ MPU_v_صف_Delete( صف_Handle_t x_صف ) /* PRIVILEGED_FUNCTION */
    {
        صف_Handle_t x_داخلی_صف_Handle = عدم;
        int32_t l_شاخص;

        l_شاخص = ( int32_t ) x_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_داخلی_صف_Handle != عدم )
            {
                v_صف_Delete( x_داخلی_صف_Handle );
                MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );
            }
        }
    }
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )

        صف_Handle_t MPU_x_صف_Create_Mutex( ثابت uint8_t uc_صف_Type ) /* PRIVILEGED_FUNCTION */
        {
            صف_Handle_t x_داخلی_صف_Handle = عدم;
            صف_Handle_t x_External_صف_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_داخلی_صف_Handle = x_صف_Create_Mutex( uc_صف_Type );

                إذا( x_داخلی_صف_Handle != عدم )
                {
                    MPU_Store_صف_Handle_At_شاخص( l_شاخص, x_داخلی_صف_Handle );
                    x_External_صف_Handle = ( صف_Handle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_صف_Handle;
        }

    #پایان_اگر /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_تخصیص == 1 ) )

        صف_Handle_t MPU_x_صف_Create_Mutex_Static( ثابت uint8_t uc_صف_Type,
                                                   Static_صف_t * px_Static_صف ) /* PRIVILEGED_FUNCTION */
        {
            صف_Handle_t x_داخلی_صف_Handle = عدم;
            صف_Handle_t x_External_صف_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_داخلی_صف_Handle = x_صف_Create_Mutex_Static( uc_صف_Type, px_Static_صف );

                إذا( x_داخلی_صف_Handle != عدم )
                {
                    MPU_Store_صف_Handle_At_شاخص( l_شاخص, x_داخلی_صف_Handle );
                    x_External_صف_Handle = ( صف_Handle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_صف_Handle;
        }

    #پایان_اگر /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )

        صف_Handle_t MPU_x_صف_Create_Counting_Semaphore( UBaseType_t ux_شمار_مقدار,
                                                         UBaseType_t ux_Initial_شمار ) /* PRIVILEGED_FUNCTION */
        {
            صف_Handle_t x_داخلی_صف_Handle = عدم;
            صف_Handle_t x_External_صف_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_داخلی_صف_Handle = x_صف_Create_Counting_Semaphore( ux_شمار_مقدار, ux_Initial_شمار );

                إذا( x_داخلی_صف_Handle != عدم )
                {
                    MPU_Store_صف_Handle_At_شاخص( l_شاخص, x_داخلی_صف_Handle );
                    x_External_صف_Handle = ( صف_Handle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_صف_Handle;
        }

    #پایان_اگر /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_تخصیص == 1 ) )

        صف_Handle_t MPU_x_صف_Create_Counting_Semaphore_Static( ثابت UBaseType_t ux_Max_شمار,
                                                               ثابت UBaseType_t ux_Initial_شمار,
                                                               Static_صف_t * px_Static_صف ) /* PRIVILEGED_FUNCTION */
        {
            صف_Handle_t x_داخلی_صف_Handle = عدم;
            صف_Handle_t x_External_صف_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_داخلی_صف_Handle = x_صف_Create_Counting_Semaphore_Static( ux_Max_شمار, ux_Initial_شمار, px_Static_صف );

                إذا( x_داخلی_صف_Handle != عدم )
                {
                    MPU_Store_صف_Handle_At_شاخص( l_شاخص, x_داخلی_صف_Handle );
                    x_External_صف_Handle = ( صف_Handle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_صف_Handle;
        }

    #پایان_اگر /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_تخصیص == 1 )

        صف_Handle_t MPU_x_صف_Generic_Create( UBaseType_t ux_صف_درازی,
                                               UBaseType_t ux_قلم_اندازه,
                                               uint8_t uc_صف_Type ) /* PRIVILEGED_FUNCTION */
        {
            صف_Handle_t x_داخلی_صف_Handle = عدم;
            صف_Handle_t x_External_صف_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_داخلی_صف_Handle = x_صف_Generic_Create( ux_صف_درازی, ux_قلم_اندازه, uc_صف_Type );

                إذا( x_داخلی_صف_Handle != عدم )
                {
                    MPU_Store_صف_Handle_At_شاخص( l_شاخص, x_داخلی_صف_Handle );
                    x_External_صف_Handle = ( صف_Handle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_صف_Handle;
        }

    #پایان_اگر /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_تخصیص == 1 )

        صف_Handle_t MPU_x_صف_Generic_Create_Static( ثابت UBaseType_t ux_صف_درازی,
                                                     ثابت UBaseType_t ux_قلم_اندازه,
                                                     uint8_t * puc_صف_Storage,
                                                     Static_صف_t * px_Static_صف,
                                                     ثابت uint8_t uc_صف_Type ) /* PRIVILEGED_FUNCTION */
        {
            صف_Handle_t x_داخلی_صف_Handle = عدم;
            صف_Handle_t x_External_صف_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_داخلی_صف_Handle = x_صف_Generic_Create_Static( ux_صف_درازی, ux_قلم_اندازه, puc_صف_Storage, px_Static_صف, uc_صف_Type );

                إذا( x_داخلی_صف_Handle != عدم )
                {
                    MPU_Store_صف_Handle_At_شاخص( l_شاخص, x_داخلی_صف_Handle );
                    x_External_صف_Handle = ( صف_Handle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_صف_Handle;
        }

    #پایان_اگر /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Generic_Reset( صف_Handle_t x_صف,
                                       پایه_Type_t x_New_صف ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_شاخص;
        صف_Handle_t x_داخلی_صف_Handle = عدم;
        پایه_Type_t xReturn = pdFAIL;

        l_شاخص = ( int32_t ) x_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_داخلی_صف_Handle != عدم )
            {
                xReturn = x_صف_Generic_Reset( x_داخلی_صف_Handle, x_New_صف );
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_صف_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )

        صف_مجموعه_Handle_t MPU_x_صف_Create_مجموعه( UBaseType_t ux_Event_صف_درازی ) /* PRIVILEGED_FUNCTION */
        {
            صف_مجموعه_Handle_t x_داخلی_صف_مجموعه_Handle = عدم;
            صف_مجموعه_Handle_t x_External_صف_مجموعه_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_داخلی_صف_مجموعه_Handle = x_صف_Create_مجموعه( ux_Event_صف_درازی );

                إذا( x_داخلی_صف_مجموعه_Handle != عدم )
                {
                    MPU_Store_صف_مجموعه_Handle_At_شاخص( l_شاخص, x_داخلی_صف_مجموعه_Handle );
                    x_External_صف_مجموعه_Handle = ( صف_مجموعه_Handle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_صف_مجموعه_Handle;
        }

    #پایان_اگر /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_USE_صف_SETS == 1 ) && ( config_SUPPORT_STATIC_تخصیص == 1 ) )

        صف_مجموعه_Handle_t MPU_x_صف_Create_مجموعه_Static( ثابت UBaseType_t ux_Event_صف_درازی,
                                                    uint8_t * puc_صف_Storage,
                                                    Static_صف_t * px_Static_صف ) /* PRIVILEGED_FUNCTION */
        {
            صف_مجموعه_Handle_t x_داخلی_صف_مجموعه_Handle = عدم;
            صف_مجموعه_Handle_t x_External_صف_مجموعه_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_داخلی_صف_مجموعه_Handle = x_صف_Create_مجموعه_Static( ux_Event_صف_درازی, puc_صف_Storage, px_Static_صف );

                إذا( x_داخلی_صف_مجموعه_Handle != عدم )
                {
                    MPU_Store_صف_مجموعه_Handle_At_شاخص( l_شاخص, x_داخلی_صف_مجموعه_Handle );
                    x_External_صف_مجموعه_Handle = ( صف_مجموعه_Handle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_صف_مجموعه_Handle;
        }

    #پایان_اگر /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_صف_SETS == 1 )

        پایه_Type_t MPU_x_صف_Remove_From_مجموعه( صف_مجموعه_Member_Handle_t x_صف_Or_Semaphore,
                                            صف_مجموعه_Handle_t x_صف_مجموعه ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            صف_مجموعه_Member_Handle_t x_داخلی_صف_مجموعه_Member_Handle = عدم;
            صف_مجموعه_Handle_t x_داخلی_صف_مجموعه_Handle = عدم;
            int32_t l_شاخص_صف_مجموعه, l_شاخص_صف_مجموعه_Member;

            l_شاخص_صف_مجموعه = ( int32_t ) x_صف_مجموعه;
            l_شاخص_صف_مجموعه_Member = ( int32_t ) x_صف_Or_Semaphore;

            إذا( ( IS_EXTERNAL_شاخص_VALID( l_شاخص_صف_مجموعه ) != pdFALSE ) &&
                ( IS_EXTERNAL_شاخص_VALID( l_شاخص_صف_مجموعه_Member ) != pdFALSE ) )
            {
                x_داخلی_صف_مجموعه_Handle = MPU_Get_صف_مجموعه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص_صف_مجموعه ) );
                x_داخلی_صف_مجموعه_Member_Handle = MPU_Get_صف_مجموعه_Member_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص_صف_مجموعه_Member ) );

                إذا( ( x_داخلی_صف_مجموعه_Handle != عدم ) && ( x_داخلی_صف_مجموعه_Member_Handle != عدم ) )
                {
                    xReturn = x_صف_Remove_From_مجموعه( x_داخلی_صف_مجموعه_Member_Handle, x_داخلی_صف_مجموعه_Handle );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_تخصیص == 1 )

        پایه_Type_t MPU_x_صف_Generic_Get_Static_Buffers( صف_Handle_t x_صف,
                                                      uint8_t ** ppuc_صف_Storage,
                                                      Static_صف_t ** ppx_Static_صف ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_شاخص;
            صف_Handle_t x_داخلی_صف_Handle = عدم;
            پایه_Type_t xReturn = pdFALSE;

            l_شاخص = ( int32_t ) x_صف;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_صف_Handle != عدم )
                {
                    xReturn = x_صف_Generic_Get_Static_Buffers( x_داخلی_صف_Handle, ppuc_صف_Storage, ppx_Static_صف );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /*if ( configSUPPORT_STATIC_ALLOCATION == 1 )*/
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Generic_Send_From_ISR( صف_Handle_t x_صف,
                                             ثابت فراغ * ثابت pv_قلم_مقصد_صف,
                                             پایه_Type_t * ثابت px_Higher_اولویت_Task_Woken,
                                             ثابت پایه_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        پایه_Type_t xReturn = pdFAIL;
        int32_t l_شاخص;
        صف_Handle_t x_داخلی_صف_Handle = عدم;

        l_شاخص = ( int32_t ) x_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_داخلی_صف_Handle != عدم )
            {
                xReturn = x_صف_Generic_Send_From_ISR( x_داخلی_صف_Handle, pv_قلم_مقصد_صف, px_Higher_اولویت_Task_Woken, xCopyPosition );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Give_From_ISR( صف_Handle_t x_صف,
                                      پایه_Type_t * ثابت px_Higher_اولویت_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        پایه_Type_t xReturn = pdFAIL;
        int32_t l_شاخص;
        صف_Handle_t x_داخلی_صف_Handle = عدم;

        l_شاخص = ( int32_t ) x_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_داخلی_صف_Handle != عدم )
            {
                xReturn = x_صف_Give_From_ISR( x_داخلی_صف_Handle, px_Higher_اولویت_Task_Woken );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Peek_From_ISR( صف_Handle_t x_صف,
                                      فراغ * ثابت pv_میانگیر ) /* PRIVILEGED_FUNCTION */
    {
        پایه_Type_t xReturn = pdFAIL;
        int32_t l_شاخص;
        صف_Handle_t x_داخلی_صف_Handle = عدم;

        l_شاخص = ( int32_t ) x_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_داخلی_صف_Handle != عدم )
            {
                xReturn = x_صف_Peek_From_ISR( x_داخلی_صف_Handle, pv_میانگیر );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Receive_From_ISR( صف_Handle_t x_صف,
                                         فراغ * ثابت pv_میانگیر,
                                         پایه_Type_t * ثابت px_Higher_اولویت_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        پایه_Type_t xReturn = pdFAIL;
        int32_t l_شاخص;
        صف_Handle_t x_داخلی_صف_Handle = عدم;

        l_شاخص = ( int32_t ) x_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_داخلی_صف_Handle != عدم )
            {
                xReturn = x_صف_Receive_From_ISR( x_داخلی_صف_Handle, pv_میانگیر, px_Higher_اولویت_Task_Woken );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Is_صف_خالی_From_ISR( ثابت صف_Handle_t x_صف ) /* PRIVILEGED_FUNCTION */
    {
        پایه_Type_t xReturn = pdFAIL;
        int32_t l_شاخص;
        صف_Handle_t x_داخلی_صف_Handle = عدم;

        l_شاخص = ( int32_t ) x_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_داخلی_صف_Handle != عدم )
            {
                xReturn = x_صف_Is_صف_خالی_From_ISR( x_داخلی_صف_Handle );
            }
        }

        أرجع xReturn;
    }
/*-----------------------------------------------------------*/

    پایه_Type_t MPU_x_صف_Is_صف_پر_From_ISR( ثابت صف_Handle_t x_صف ) /* PRIVILEGED_FUNCTION */
    {
        پایه_Type_t xReturn = pdFAIL;
        int32_t l_شاخص;
        صف_Handle_t x_داخلی_صف_Handle = عدم;

        l_شاخص = ( int32_t ) x_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_داخلی_صف_Handle != عدم )
            {
                xReturn = x_صف_Is_صف_پر_From_ISR( x_داخلی_صف_Handle );
            }
        }

        أرجع xReturn;
    }

/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_صف_Messages_انتظار_From_ISR( ثابت صف_Handle_t x_صف ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn = 0;
        int32_t l_شاخص;
        صف_Handle_t x_داخلی_صف_Handle = عدم;

        l_شاخص = ( int32_t ) x_صف;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_داخلی_صف_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_داخلی_صف_Handle != عدم )
            {
                uxReturn = ux_صف_Messages_انتظار_From_ISR( x_داخلی_صف_Handle );
            }
        }

        أرجع uxReturn;
    }

/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_صف_Get_Mutex_Holder_From_ISR( صف_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_داخلی_Handle = عدم;
            TaskHandle_t xMutexHolderTaskExternalHandle = عدم;
            int32_t l_شاخص, l_Mutex_Holder_Task_شاخص;
            صف_Handle_t x_داخلی_Semaphore_Handle = عدم;

            l_شاخص = ( int32_t ) xSemaphore;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_Semaphore_Handle = MPU_Get_صف_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_Semaphore_Handle != عدم )
                {
                    x_Mutex_Holder_Task_داخلی_Handle = x_صف_Get_Mutex_Holder( x_داخلی_Semaphore_Handle );

                    إذا( x_Mutex_Holder_Task_داخلی_Handle != عدم )
                    {
                        l_Mutex_Holder_Task_شاخص = MPU_Get_شاخص_For_Task_Handle( x_Mutex_Holder_Task_داخلی_Handle );

                        إذا( l_Mutex_Holder_Task_شاخص != -1 )
                        {
                            xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_مقصد_EXTERNAL_شاخص( l_Mutex_Holder_Task_شاخص ) );
                        }
                    }
                }
            }

            أرجع xMutexHolderTaskExternalHandle;
        }

    #پایان_اگر /* #if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_صف_SETS == 1 )

        صف_مجموعه_Member_Handle_t MPU_x_صف_Select_From_مجموعه_From_ISR( صف_مجموعه_Handle_t x_صف_مجموعه ) /* PRIVILEGED_FUNCTION */
        {
            صف_مجموعه_Handle_t x_داخلی_صف_مجموعه_Handle = عدم;
            صف_مجموعه_Member_Handle_t x_Selected_Member_داخلی = عدم;
            صف_مجموعه_Member_Handle_t xSelectedMemberExternal = عدم;
            int32_t l_شاخص_صف_مجموعه, l_شاخص_Selected_Member;

            l_شاخص_صف_مجموعه = ( int32_t ) x_صف_مجموعه;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص_صف_مجموعه ) != pdFALSE )
            {
                x_داخلی_صف_مجموعه_Handle = MPU_Get_صف_مجموعه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص_صف_مجموعه ) );

                إذا( x_داخلی_صف_مجموعه_Handle != عدم )
                {
                    x_Selected_Member_داخلی = x_صف_Select_From_مجموعه_From_ISR( x_داخلی_صف_مجموعه_Handle );

                    إذا( x_Selected_Member_داخلی != عدم )
                    {
                        l_شاخص_Selected_Member = MPU_Get_شاخص_For_صف_مجموعه_Member_Handle( x_Selected_Member_داخلی );

                        إذا( l_شاخص_Selected_Member != -1 )
                        {
                            xSelectedMemberExternal = ( صف_مجموعه_Member_Handle_t ) ( CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص_Selected_Member ) );
                        }
                    }
                }
            }

            أرجع xSelectedMemberExternal;
        }

    #پایان_اگر /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for timers APIs.                  */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ * MPU_pvTimerGetTimerIDImpl( ثابت TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        فراغ * MPU_pvTimerGetTimerIDImpl( ثابت TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            فراغ * pvReturn = عدم;
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_داخلی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Timer_Handle != عدم )
                    {
                        pvReturn = pvTimerGetTimerID( x_داخلی_Timer_Handle );
                    }
                }
            }

            أرجع pvReturn;
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_مجموعه_Timer_IDImpl( TimerHandle_t xTimer,
                                       فراغ * pvNewID ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Timer_مجموعه_Timer_IDImpl( TimerHandle_t xTimer,
                                       فراغ * pvNewID ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_داخلی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Timer_Handle != عدم )
                    {
                        v_Timer_مجموعه_Timer_ID( x_داخلی_Timer_Handle, pvNewID );
                    }
                }
            }
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        پایه_Type_t MPU_x_Timer_Is_Timer_فعال_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_x_Timer_Is_Timer_فعال_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_داخلی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Timer_Handle != عدم )
                    {
                        xReturn = x_Timer_Is_Timer_فعال( x_داخلی_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( فراغ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xReturn;

            xReturn = xTimerGetTimerDaemonTaskHandle();

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        پایه_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ثابت پایه_Type_t xCommandID,
                                                     ثابت TickType_t x_Optional_مقدار,
                                                     پایه_Type_t * ثابت px_Higher_اولویت_Task_Woken,
                                                     ثابت TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            پایه_Type_t xReturn = pdFALSE;
            xTimerGenericCommandFromTaskParams_t xParams;

            xParams.xTimer = xTimer;
            xParams.xCommandID = xCommandID;
            xParams.x_Optional_مقدار = x_Optional_مقدار;
            xParams.px_Higher_اولویت_Task_Woken = px_Higher_اولویت_Task_Woken;
            xParams.x_Ticks_مقصد_Wait = x_Ticks_مقصد_Wait;

            xReturn = MPU_x_Timer_Generic_Command_From_Task_مدخل( &( xParams ) );

            أرجع xReturn;
        }

        پایه_Type_t MPU_xTimerGenericCommandFromTaskImpl( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_xTimerGenericCommandFromTaskImpl( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Is_Higher_اولویت_Task_Woken_Writeable = pdFALSE;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;
            پایه_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( pxParams,
                                                                      حجم( xTimerGenericCommandFromTaskParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( pxParams->xCommandID < tmr_اولی_FROM_ISR_COMMAND )
                {
                    إذا( pxParams->px_Higher_اولویت_Task_Woken != عدم )
                    {
                        x_Is_Higher_اولویت_Task_Woken_Writeable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( pxParams->px_Higher_اولویت_Task_Woken,
                                                                                               حجم( پایه_Type_t ),
                                                                                               tskMPU_WRITE_PERMISSION );
                    }

                    إذا( ( pxParams->px_Higher_اولویت_Task_Woken == عدم ) ||
                        ( x_Is_Higher_اولویت_Task_Woken_Writeable == pdTRUE ) )
                    {
                        l_شاخص = ( int32_t ) ( pxParams->xTimer );

                        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                            إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                            {
                                x_داخلی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                                إذا( x_داخلی_Timer_Handle != عدم )
                                {
                                    xReturn = xTimerGenericCommandFromTask( x_داخلی_Timer_Handle,
                                                                            pxParams->xCommandID,
                                                                            pxParams->x_Optional_مقدار,
                                                                            pxParams->px_Higher_اولویت_Task_Woken,
                                                                            pxParams->x_Ticks_مقصد_Wait );
                                }
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        ثابت حرف * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ثابت حرف * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ثابت حرف * pcReturn = عدم;
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_داخلی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Timer_Handle != عدم )
                    {
                        pcReturn = pcTimerGetName( x_داخلی_Timer_Handle );
                    }
                }
            }

            أرجع pcReturn;
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        فراغ MPU_v_Timer_مجموعه_Reload_نما_Impl( TimerHandle_t xTimer,
                                          ثابت پایه_Type_t xAutoReload ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Timer_مجموعه_Reload_نما_Impl( TimerHandle_t xTimer,
                                          ثابت پایه_Type_t xAutoReload ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_داخلی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Timer_Handle != عدم )
                    {
                        v_Timer_مجموعه_Reload_نما( x_داخلی_Timer_Handle, xAutoReload );
                    }
                }
            }
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        پایه_Type_t MPU_x_Timer_Get_Reload_نما_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_x_Timer_Get_Reload_نما_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_داخلی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Timer_Handle != عدم )
                    {
                        xReturn = x_Timer_Get_Reload_نما( x_داخلی_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_نما_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Timer_Get_Reload_نما_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_داخلی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Timer_Handle != عدم )
                    {
                        uxReturn = ux_Timer_Get_Reload_نما( x_داخلی_Timer_Handle );
                    }
                }
            }

            أرجع uxReturn;
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_داخلی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Timer_Handle != عدم )
                    {
                        xReturn = xTimerGetPeriod( x_داخلی_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_زمان_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_x_Timer_Get_Expiry_زمان_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_داخلی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Timer_Handle != عدم )
                    {
                        xReturn = x_Timer_Get_Expiry_زمان( x_داخلی_Timer_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Timer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreate( ثابت حرف * ثابت pcTimerName,
                                        ثابت TickType_t x_Timer_Period_درون_Ticks,
                                        ثابت پایه_Type_t xAutoReload,
                                        فراغ * ثابت pvTimerID,
                                        TimerCallbackFunction_t pxCallbackFunction ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            TimerHandle_t xExternalTimerHandle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_داخلی_Timer_Handle = xTimerCreate( pcTimerName, x_Timer_Period_درون_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback );

                إذا( x_داخلی_Timer_Handle != عدم )
                {
                    MPU_Store_Timer_Handle_At_شاخص( l_شاخص, x_داخلی_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع xExternalTimerHandle;
        }

    #پایان_اگر /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreateStatic( ثابت حرف * ثابت pcTimerName,
                                              ثابت TickType_t x_Timer_Period_درون_Ticks,
                                              ثابت پایه_Type_t xAutoReload,
                                              فراغ * ثابت pvTimerID,
                                              TimerCallbackFunction_t pxCallbackFunction,
                                              StaticTimer_t * px_Timer_میانگیر ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            TimerHandle_t xExternalTimerHandle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_داخلی_Timer_Handle = xTimerCreateStatic( pcTimerName, x_Timer_Period_درون_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback, px_Timer_میانگیر );

                إذا( x_داخلی_Timer_Handle != عدم )
                {
                    MPU_Store_Timer_Handle_At_شاخص( l_شاخص, x_داخلی_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع xExternalTimerHandle;
        }

    #پایان_اگر /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( configUSE_TIMERS == 1 )

        پایه_Type_t MPU_x_Timer_Get_Static_میانگیر( TimerHandle_t xTimer,
                                              StaticTimer_t ** ppx_Timer_میانگیر ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t xReturn = pdFALSE;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_Timer_Handle != عدم )
                {
                    xReturn = x_Timer_Get_Static_میانگیر( x_داخلی_Timer_Handle, ppx_Timer_میانگیر );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        پایه_Type_t MPU_xTimerGenericCommandFromISR( TimerHandle_t xTimer,
                                                    ثابت پایه_Type_t xCommandID,
                                                    ثابت TickType_t x_Optional_مقدار,
                                                    پایه_Type_t * ثابت px_Higher_اولویت_Task_Woken,
                                                    ثابت TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_Timer_Handle != عدم )
                {
                    xReturn = xTimerGenericCommandFromISR( x_داخلی_Timer_Handle, xCommandID, x_Optional_مقدار, px_Higher_اولویت_Task_Woken, x_Ticks_مقصد_Wait );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_TIMERS == 1 )

        پایه_Type_t MPU_xTimerDelete( TimerHandle_t xTimer, TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            TimerHandle_t x_داخلی_Timer_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) xTimer;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_Timer_Handle = MPU_Get_Timer_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_Timer_Handle != عدم )
                {
                    xReturn = xTimerGenericCommandFromTask( x_داخلی_Timer_Handle,
                                                            tmrCOMMAND_DELETE,
                                                            0U, /* xOptionalValue */
                                                            عدم, /* pxHigherPriorityTaskWoken */
                                                            x_Ticks_مقصد_Wait );
                    إذا( xReturn != pdFALSE )
                    {
                        MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for event group APIs.              */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بیتها_t MPU_x_Event_گروه_Wait_بیتها( Event_گروه_Handle_t x_Event_گروه,
                                             ثابت Event_بیتها_t ux_بیتها_مقصد_Wait_For,
                                             ثابت پایه_Type_t xClearOnExit,
                                             ثابت پایه_Type_t x_Wait_For_All_بیتها,
                                             TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بیتها_t xReturn = 0;
            x_Event_گروه_Wait_بیتها_Params_t xParams;

            xParams.x_Event_گروه = x_Event_گروه;
            xParams.ux_بیتها_مقصد_Wait_For = ux_بیتها_مقصد_Wait_For;
            xParams.xClearOnExit = xClearOnExit;
            xParams.x_Wait_For_All_بیتها = x_Wait_For_All_بیتها;
            xParams.x_Ticks_مقصد_Wait = x_Ticks_مقصد_Wait;

            xReturn = MPU_x_Event_گروه_Wait_بیتها_مدخل( &( xParams ) );

            أرجع xReturn;
        }

        Event_بیتها_t MPU_x_Event_گروه_Wait_بیتها_Impl( ثابت x_Event_گروه_Wait_بیتها_Params_t * pxParams ) PRIVILEGED_FUNCTION;

        Event_بیتها_t MPU_x_Event_گروه_Wait_بیتها_Impl( ثابت x_Event_گروه_Wait_بیتها_Params_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            Event_بیتها_t xReturn = 0;
            Event_گروه_Handle_t x_داخلی_Event_گروه_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه = pdFALSE;
            پایه_Type_t xAreParamsReadable = pdFALSE;

            إذا( pxParams != عدم )
            {
                xAreParamsReadable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( pxParams,
                                                                      حجم( x_Event_گروه_Wait_بیتها_Params_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            إذا( xAreParamsReadable == pdTRUE )
            {
                إذا( ( ( pxParams->ux_بیتها_مقصد_Wait_For & event_EVENT_بیتها_CONTROL_بایتها ) == 0U ) &&
                    ( pxParams->ux_بیتها_مقصد_Wait_For != 0U )
                    #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                        && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( pxParams->x_Ticks_مقصد_Wait != 0U ) ) )
                    #پایان_اگر
                    )
                {
                    l_شاخص = ( int32_t ) ( pxParams->x_Event_گروه );

                    إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه == pdTRUE )
                        {
                            x_داخلی_Event_گروه_Handle = MPU_Get_Event_گروه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                            إذا( x_داخلی_Event_گروه_Handle != عدم )
                            {
                                xReturn = x_Event_گروه_Wait_بیتها( x_داخلی_Event_گروه_Handle,
                                                               pxParams->ux_بیتها_مقصد_Wait_For,
                                                               pxParams->xClearOnExit,
                                                               pxParams->x_Wait_For_All_بیتها,
                                                               pxParams->x_Ticks_مقصد_Wait );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بیتها_t MPU_x_Event_گروه_Clear_بیتها_Impl( Event_گروه_Handle_t x_Event_گروه,
                                                  ثابت Event_بیتها_t ux_بیتها_مقصد_Clear ) PRIVILEGED_FUNCTION;

        Event_بیتها_t MPU_x_Event_گروه_Clear_بیتها_Impl( Event_گروه_Handle_t x_Event_گروه,
                                                  ثابت Event_بیتها_t ux_بیتها_مقصد_Clear ) /* PRIVILEGED_FUNCTION */
        {
            Event_بیتها_t xReturn = 0;
            Event_گروه_Handle_t x_داخلی_Event_گروه_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه = pdFALSE;

            إذا( ( ux_بیتها_مقصد_Clear & event_EVENT_بیتها_CONTROL_بایتها ) == 0U )
            {
                l_شاخص = ( int32_t ) x_Event_گروه;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه == pdTRUE )
                    {
                        x_داخلی_Event_گروه_Handle = MPU_Get_Event_گروه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_داخلی_Event_گروه_Handle != عدم )
                        {
                            xReturn = x_Event_گروه_Clear_بیتها( x_داخلی_Event_گروه_Handle, ux_بیتها_مقصد_Clear );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بیتها_t MPU_x_Event_گروه_مجموعه_بیتها_Impl( Event_گروه_Handle_t x_Event_گروه,
                                                ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه ) PRIVILEGED_FUNCTION;

        Event_بیتها_t MPU_x_Event_گروه_مجموعه_بیتها_Impl( Event_گروه_Handle_t x_Event_گروه,
                                                ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه ) /* PRIVILEGED_FUNCTION */
        {
            Event_بیتها_t xReturn = 0;
            Event_گروه_Handle_t x_داخلی_Event_گروه_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه = pdFALSE;

            إذا( ( ux_بیتها_مقصد_مجموعه & event_EVENT_بیتها_CONTROL_بایتها ) == 0U )
            {
                l_شاخص = ( int32_t ) x_Event_گروه;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه == pdTRUE )
                    {
                        x_داخلی_Event_گروه_Handle = MPU_Get_Event_گروه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_داخلی_Event_گروه_Handle != عدم )
                        {
                            xReturn = x_Event_گروه_مجموعه_بیتها( x_داخلی_Event_گروه_Handle, ux_بیتها_مقصد_مجموعه );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بیتها_t MPU_x_Event_گروه_Sync_Impl( Event_گروه_Handle_t x_Event_گروه,
                                             ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه,
                                             ثابت Event_بیتها_t ux_بیتها_مقصد_Wait_For,
                                             TickType_t x_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

        Event_بیتها_t MPU_x_Event_گروه_Sync_Impl( Event_گروه_Handle_t x_Event_گروه,
                                             ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه,
                                             ثابت Event_بیتها_t ux_بیتها_مقصد_Wait_For,
                                             TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
        {
            Event_بیتها_t xReturn = 0;
            Event_گروه_Handle_t x_داخلی_Event_گروه_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه = pdFALSE;

            إذا( ( ( ux_بیتها_مقصد_Wait_For & event_EVENT_بیتها_CONTROL_بایتها ) == 0U ) &&
                ( ux_بیتها_مقصد_Wait_For != 0U )
                #إذا ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                    && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_مقصد_Wait != 0U ) ) )
                #پایان_اگر
                )
            {
                l_شاخص = ( int32_t ) x_Event_گروه;

                إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه == pdTRUE )
                    {
                        x_داخلی_Event_گروه_Handle = MPU_Get_Event_گروه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_داخلی_Event_گروه_Handle != عدم )
                        {
                            xReturn = x_Event_گروه_Sync( x_داخلی_Event_گروه_Handle, ux_بیتها_مقصد_مجموعه, ux_بیتها_مقصد_Wait_For, x_Ticks_مقصد_Wait );
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_گروه_Get_عدد_Impl( فراغ * x_Event_گروه ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Event_گروه_Get_عدد_Impl( فراغ * x_Event_گروه ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t xReturn = 0;
            Event_گروه_Handle_t x_داخلی_Event_گروه_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه = pdFALSE;

            l_شاخص = ( int32_t ) x_Event_گروه;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه == pdTRUE )
                {
                    x_داخلی_Event_گروه_Handle = MPU_Get_Event_گروه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Event_گروه_Handle != عدم )
                    {
                        xReturn = ux_Event_گروه_Get_عدد( x_داخلی_Event_گروه_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        فراغ MPU_v_Event_گروه_مجموعه_عدد_Impl( فراغ * x_Event_گروه,
                                           UBaseType_t ux_Event_گروه_عدد ) PRIVILEGED_FUNCTION;

        فراغ MPU_v_Event_گروه_مجموعه_عدد_Impl( فراغ * x_Event_گروه,
                                           UBaseType_t ux_Event_گروه_عدد ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروه_Handle_t x_داخلی_Event_گروه_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه = pdFALSE;

            l_شاخص = ( int32_t ) x_Event_گروه;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروه == pdTRUE )
                {
                    x_داخلی_Event_گروه_Handle = MPU_Get_Event_گروه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_Event_گروه_Handle != عدم )
                    {
                        v_Event_گروه_مجموعه_عدد( x_داخلی_Event_گروه_Handle, ux_Event_گروه_عدد );
                    }
                }
            }
        }

    #پایان_اگر /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Event Group APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_گروه_Handle_t MPU_x_Event_گروه_Create( فراغ ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروه_Handle_t x_داخلی_Event_گروه_Handle = عدم;
            Event_گروه_Handle_t x_External_Event_گروه_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_داخلی_Event_گروه_Handle = x_Event_گروه_Create();

                إذا( x_داخلی_Event_گروه_Handle != عدم )
                {
                    MPU_Store_Event_گروه_Handle_At_شاخص( l_شاخص, x_داخلی_Event_گروه_Handle );
                    x_External_Event_گروه_Handle = ( Event_گروه_Handle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_Event_گروه_Handle;
        }

    #پایان_اگر /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_گروه_Handle_t MPU_x_Event_گروه_Create_Static( Static_Event_گروه_t * px_Event_گروه_میانگیر ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروه_Handle_t x_داخلی_Event_گروه_Handle = عدم;
            Event_گروه_Handle_t x_External_Event_گروه_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

            إذا( l_شاخص != -1 )
            {
                x_داخلی_Event_گروه_Handle = x_Event_گروه_Create_Static( px_Event_گروه_میانگیر );

                إذا( x_داخلی_Event_گروه_Handle != عدم )
                {
                    MPU_Store_Event_گروه_Handle_At_شاخص( l_شاخص, x_داخلی_Event_گروه_Handle );
                    x_External_Event_گروه_Handle = ( Event_گروه_Handle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                }
                وإلا
                {
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                }
            }

            أرجع x_External_Event_گروه_Handle;
        }

    #پایان_اگر /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        فراغ MPU_v_Event_گروه_Delete( Event_گروه_Handle_t x_Event_گروه ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروه_Handle_t x_داخلی_Event_گروه_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_Event_گروه;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_Event_گروه_Handle = MPU_Get_Event_گروه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_Event_گروه_Handle != عدم )
                {
                    v_Event_گروه_Delete( x_داخلی_Event_گروه_Handle );
                    MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );
                }
            }
        }

    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        پایه_Type_t MPU_x_Event_گروه_Get_Static_میانگیر( Event_گروه_Handle_t x_Event_گروه,
                                                   Static_Event_گروه_t ** ppx_Event_گروه_میانگیر ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            Event_گروه_Handle_t x_داخلی_Event_گروه_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_Event_گروه;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_Event_گروه_Handle = MPU_Get_Event_گروه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_Event_گروه_Handle != عدم )
                {
                    xReturn = x_Event_گروه_Get_Static_میانگیر( x_داخلی_Event_گروه_Handle, ppx_Event_گروه_میانگیر );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        پایه_Type_t MPU_x_Event_گروه_Clear_بیتها_From_ISR( Event_گروه_Handle_t x_Event_گروه,
                                                    ثابت Event_بیتها_t ux_بیتها_مقصد_Clear ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            Event_گروه_Handle_t x_داخلی_Event_گروه_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_Event_گروه;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_Event_گروه_Handle = MPU_Get_Event_گروه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_Event_گروه_Handle != عدم )
                {
                    xReturn = x_Event_گروه_Clear_بیتها_From_ISR( x_داخلی_Event_گروه_Handle, ux_بیتها_مقصد_Clear );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        پایه_Type_t MPU_x_Event_گروه_مجموعه_بیتها_From_ISR( Event_گروه_Handle_t x_Event_گروه,
                                                  ثابت Event_بیتها_t ux_بیتها_مقصد_مجموعه,
                                                  پایه_Type_t * px_Higher_اولویت_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            Event_گروه_Handle_t x_داخلی_Event_گروه_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_Event_گروه;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_Event_گروه_Handle = MPU_Get_Event_گروه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_Event_گروه_Handle != عدم )
                {
                    xReturn = x_Event_گروه_مجموعه_بیتها_From_ISR( x_داخلی_Event_گروه_Handle, ux_بیتها_مقصد_مجموعه, px_Higher_اولویت_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( configUSE_EVENT_GROUPS == 1 )

        Event_بیتها_t MPU_x_Event_گروه_Get_بیتها_From_ISR( Event_گروه_Handle_t x_Event_گروه ) /* PRIVILEGED_FUNCTION */
        {
            Event_بیتها_t xReturn = 0;
            Event_گروه_Handle_t x_داخلی_Event_گروه_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_Event_گروه;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_Event_گروه_Handle = MPU_Get_Event_گروه_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_Event_گروه_Handle != عدم )
                {
                    xReturn = x_Event_گروه_Get_بیتها_From_ISR( x_داخلی_Event_گروه_Handle );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for stream buffer APIs.            */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        size_t MPU_x_جریان_میانگیر_Send_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                          ثابت فراغ * pv_Tx_داده,
                                          size_t x_داده_درازی_بایتها,
                                          TickType_t x_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_جریان_میانگیر_Send_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                          ثابت فراغ * pv_Tx_داده,
                                          size_t x_داده_درازی_بایتها,
                                          TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Is_Tx_داده_میانگیر_Readable = pdFALSE;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = pdFALSE;

            إذا( pv_Tx_داده != عدم )
            {
                x_Is_Tx_داده_میانگیر_Readable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( pv_Tx_داده,
                                                                           x_داده_درازی_بایتها,
                                                                           tskMPU_READ_PERMISSION );

                إذا( x_Is_Tx_داده_میانگیر_Readable == pdTRUE )
                {
                    l_شاخص = ( int32_t ) x_جریان_میانگیر;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر == pdTRUE )
                        {
                            x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                            إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                            {
                                xReturn = x_جریان_میانگیر_Send( x_داخلی_جریان_میانگیر_Handle, pv_Tx_داده, x_داده_درازی_بایتها, x_Ticks_مقصد_Wait );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        size_t MPU_x_جریان_میانگیر_Receive_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                             فراغ * pv_Rx_داده,
                                             size_t x_میانگیر_درازی_بایتها,
                                             TickType_t x_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_جریان_میانگیر_Receive_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                             فراغ * pv_Rx_داده,
                                             size_t x_میانگیر_درازی_بایتها,
                                             TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Is_Rx_داده_میانگیر_Writeable = pdFALSE;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = pdFALSE;

            إذا( pv_Rx_داده != عدم )
            {
                x_Is_Rx_داده_میانگیر_Writeable = x_پورت_Is_Authorized_مقصد_Access_میانگیر( pv_Rx_داده,
                                                                            x_میانگیر_درازی_بایتها,
                                                                            tskMPU_WRITE_PERMISSION );

                إذا( x_Is_Rx_داده_میانگیر_Writeable == pdTRUE )
                {
                    l_شاخص = ( int32_t ) x_جریان_میانگیر;

                    إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                        إذا( x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر == pdTRUE )
                        {
                            x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                            إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                            {
                                xReturn = x_جریان_میانگیر_Receive( x_داخلی_جریان_میانگیر_Handle, pv_Rx_داده, x_میانگیر_درازی_بایتها, x_Ticks_مقصد_Wait );
                            }
                        }
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        پایه_Type_t MPU_x_جریان_میانگیر_Is_پر_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_x_جریان_میانگیر_Is_پر_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = pdFALSE;

            l_شاخص = ( int32_t ) x_جریان_میانگیر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر == pdTRUE )
                {
                    x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                    {
                        xReturn = x_جریان_میانگیر_Is_پر( x_داخلی_جریان_میانگیر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        پایه_Type_t MPU_x_جریان_میانگیر_Is_خالی_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_x_جریان_میانگیر_Is_خالی_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = pdFALSE;

            l_شاخص = ( int32_t ) x_جریان_میانگیر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر == pdTRUE )
                {
                    x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                    {
                        xReturn = x_جریان_میانگیر_Is_خالی( x_داخلی_جریان_میانگیر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        size_t MPU_x_جریان_میانگیر_Spaces_موجود_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_جریان_میانگیر_Spaces_موجود_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = pdFALSE;

            l_شاخص = ( int32_t ) x_جریان_میانگیر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر == pdTRUE )
                {
                    x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                    {
                        xReturn = x_جریان_میانگیر_Spaces_موجود( x_داخلی_جریان_میانگیر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        size_t MPU_x_جریان_میانگیر_بایتها_موجود_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_جریان_میانگیر_بایتها_موجود_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = pdFALSE;

            l_شاخص = ( int32_t ) x_جریان_میانگیر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر == pdTRUE )
                {
                    x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                    {
                        xReturn = x_جریان_میانگیر_بایتها_موجود( x_داخلی_جریان_میانگیر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        پایه_Type_t MPU_x_جریان_میانگیر_مجموعه_Trigger_Level_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                                         size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

        پایه_Type_t MPU_x_جریان_میانگیر_مجموعه_Trigger_Level_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                                         size_t xTriggerLevel ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = pdFALSE;

            l_شاخص = ( int32_t ) x_جریان_میانگیر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر == pdTRUE )
                {
                    x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                    {
                        xReturn = x_جریان_میانگیر_مجموعه_Trigger_Level( x_داخلی_جریان_میانگیر_Handle, xTriggerLevel );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        size_t MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها_Impl( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            int32_t l_شاخص;
            پایه_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = pdFALSE;

            l_شاخص = ( int32_t ) x_جریان_میانگیر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر = x_پورت_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_Calling_Task_Is_Authorized_مقصد_Access_جریان_میانگیر == pdTRUE )
                {
                    x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                    إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                    {
                        xReturn = x_جریان_میانگیر_بعدی_پیام_درازی_بایتها( x_داخلی_جریان_میانگیر_Handle );
                    }
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Stream Buffer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) && ( config_USE_جریان_BUFFERS == 1 ) )

        جریان_میانگیر_Handle_t MPU_x_جریان_میانگیر_Generic_Create( size_t x_میانگیر_اندازه_بایتها,
                                                             size_t x_Trigger_Level_بایتها,
                                                             پایه_Type_t x_جریان_میانگیر_Type,
                                                             جریان_میانگیر_Callback_Function_t pxSendCompletedCallback,
                                                             جریان_میانگیر_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            جریان_میانگیر_Handle_t x_External_جریان_میانگیر_Handle = عدم;
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
                l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

                إذا( l_شاخص != -1 )
                {
                    x_داخلی_جریان_میانگیر_Handle = x_جریان_میانگیر_Generic_Create( x_میانگیر_اندازه_بایتها,
                                                                              x_Trigger_Level_بایتها,
                                                                              x_جریان_میانگیر_Type,
                                                                              عدم,
                                                                              عدم );

                    إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                    {
                        MPU_Store_جریان_میانگیر_Handle_At_شاخص( l_شاخص, x_داخلی_جریان_میانگیر_Handle );
                        x_External_جریان_میانگیر_Handle = ( جریان_میانگیر_Handle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                    }
                    وإلا
                    {
                        MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                    }
                }
            }
            وإلا
            {
                trace_جریان_میانگیر_CREATE_FAILED( x_جریان_میانگیر_Type );
                x_External_جریان_میانگیر_Handle = عدم;
            }

            أرجع x_External_جریان_میانگیر_Handle;
        }

    #پایان_اگر /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( config_USE_جریان_BUFFERS == 1 ) )

        جریان_میانگیر_Handle_t MPU_x_جریان_میانگیر_Generic_Create_Static( size_t x_میانگیر_اندازه_بایتها,
                                                                   size_t x_Trigger_Level_بایتها,
                                                                   پایه_Type_t x_جریان_میانگیر_Type,
                                                                   uint8_t * ثابت puc_جریان_میانگیر_Storage_Area,
                                                                   Static_جریان_میانگیر_t * ثابت px_Static_جریان_میانگیر,
                                                                   جریان_میانگیر_Callback_Function_t pxSendCompletedCallback,
                                                                   جریان_میانگیر_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            جریان_میانگیر_Handle_t x_External_جریان_میانگیر_Handle = عدم;
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
                l_شاخص = MPU_Get_Free_شاخص_درون_Kernel_Object_Pool();

                إذا( l_شاخص != -1 )
                {
                    x_داخلی_جریان_میانگیر_Handle = x_جریان_میانگیر_Generic_Create_Static( x_میانگیر_اندازه_بایتها,
                                                                                    x_Trigger_Level_بایتها,
                                                                                    x_جریان_میانگیر_Type,
                                                                                    puc_جریان_میانگیر_Storage_Area,
                                                                                    px_Static_جریان_میانگیر,
                                                                                    عدم,
                                                                                    عدم );

                    إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                    {
                        MPU_Store_جریان_میانگیر_Handle_At_شاخص( l_شاخص, x_داخلی_جریان_میانگیر_Handle );
                        x_External_جریان_میانگیر_Handle = ( جریان_میانگیر_Handle_t ) CONVERT_مقصد_EXTERNAL_شاخص( l_شاخص );
                    }
                    وإلا
                    {
                        MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( l_شاخص );
                    }
                }
            }
            وإلا
            {
                trace_جریان_میانگیر_CREATE_STATIC_FAILED( xReturn, x_جریان_میانگیر_Type );
                x_External_جریان_میانگیر_Handle = عدم;
            }

            أرجع x_External_جریان_میانگیر_Handle;
        }

    #پایان_اگر /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        فراغ MPU_v_جریان_میانگیر_Delete( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* PRIVILEGED_FUNCTION */
        {
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_جریان_میانگیر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                {
                    v_جریان_میانگیر_Delete( x_داخلی_جریان_میانگیر_Handle );
                }

                MPU_مجموعه_شاخص_Free_درون_Kernel_Object_Pool( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );
            }
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        پایه_Type_t MPU_x_جریان_میانگیر_Reset( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_جریان_میانگیر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                {
                    xReturn = x_جریان_میانگیر_Reset( x_داخلی_جریان_میانگیر_Handle );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( config_USE_جریان_BUFFERS == 1 ) )

        پایه_Type_t MPU_x_جریان_میانگیر_Get_Static_Buffers( جریان_میانگیر_Handle_t x_جریان_Buffers,
                                                      uint8_t * ppuc_جریان_میانگیر_Storage_Area,
                                                      Static_جریان_میانگیر_t * ppx_Static_جریان_میانگیر ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_جریان_Buffers;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                {
                    xReturn = MPU_x_جریان_میانگیر_Get_Static_Buffers( x_داخلی_جریان_میانگیر_Handle, ppuc_جریان_میانگیر_Storage_Area, ppx_Static_جریان_میانگیر );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

    size_t MPU_x_جریان_میانگیر_Send_From_ISR( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                         ثابت فراغ * pv_Tx_داده,
                                         size_t x_داده_درازی_بایتها,
                                         پایه_Type_t * ثابت px_Higher_اولویت_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
        int32_t l_شاخص;

        l_شاخص = ( int32_t ) x_جریان_میانگیر;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
            {
                xReturn = x_جریان_میانگیر_Send_From_ISR( x_داخلی_جریان_میانگیر_Handle, pv_Tx_داده, x_داده_درازی_بایتها, px_Higher_اولویت_Task_Woken );
            }
        }

        أرجع xReturn;
    }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

    size_t MPU_x_جریان_میانگیر_Receive_From_ISR( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                            فراغ * pv_Rx_داده,
                                            size_t x_میانگیر_درازی_بایتها,
                                            پایه_Type_t * ثابت px_Higher_اولویت_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
        int32_t l_شاخص;

        l_شاخص = ( int32_t ) x_جریان_میانگیر;

        إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
        {
            x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

            إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
            {
                xReturn = x_جریان_میانگیر_Receive_From_ISR( x_داخلی_جریان_میانگیر_Handle, pv_Rx_داده, x_میانگیر_درازی_بایتها, px_Higher_اولویت_Task_Woken );
            }
        }

        أرجع xReturn;
    }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        پایه_Type_t MPU_x_جریان_میانگیر_Send_Completed_From_ISR( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                                          پایه_Type_t * px_Higher_اولویت_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_جریان_میانگیر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                {
                    xReturn = x_جریان_میانگیر_Send_Completed_From_ISR( x_داخلی_جریان_میانگیر_Handle, px_Higher_اولویت_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        پایه_Type_t MPU_x_جریان_میانگیر_Receive_Completed_From_ISR( جریان_میانگیر_Handle_t x_جریان_میانگیر,
                                                             پایه_Type_t * px_Higher_اولویت_Task_Woken ) /*PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFALSE;
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_جریان_میانگیر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                {
                    xReturn = x_جریان_میانگیر_Receive_Completed_From_ISR( x_داخلی_جریان_میانگیر_Handle, px_Higher_اولویت_Task_Woken );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

    #إذا ( config_USE_جریان_BUFFERS == 1 )

        پایه_Type_t MPU_x_جریان_میانگیر_Reset_From_ISR( جریان_میانگیر_Handle_t x_جریان_میانگیر ) /*PRIVILEGED_FUNCTION */
        {
            پایه_Type_t xReturn = pdFAIL;
            جریان_میانگیر_Handle_t x_داخلی_جریان_میانگیر_Handle = عدم;
            int32_t l_شاخص;

            l_شاخص = ( int32_t ) x_جریان_میانگیر;

            إذا( IS_EXTERNAL_شاخص_VALID( l_شاخص ) != pdFALSE )
            {
                x_داخلی_جریان_میانگیر_Handle = MPU_Get_جریان_میانگیر_Handle_At_شاخص( CONVERT_مقصد_داخلی_شاخص( l_شاخص ) );

                إذا( x_داخلی_جریان_میانگیر_Handle != عدم )
                {
                    xReturn = x_جریان_میانگیر_Reset_From_ISR( x_داخلی_جریان_میانگیر_Handle );
                }
            }

            أرجع xReturn;
        }

    #پایان_اگر /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h. */

    #إذا configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #ضمن "application_defined_privileged_functions.h"
    #پایان_اگر
/*-----------------------------------------------------------*/

/**
 * @brief Array of system call implementation functions.
 *
 * The index in the array MUST match the corresponding system call number
 * defined in mpu_wrappers.h.
 */
    PRIVILEGED_داده UBaseType_t uxSystemCallImplementations[ رقم_SYSTEM_CALLS ] =
    {
        #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_xTaskGenericNotifyImpl,                     /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyWaitImpl,                 /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #پایان_اگر

        #إذا ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_xTimerGenericCommandFromTaskImpl,           /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #پایان_اگر

        #إذا ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_گروه_Wait_بیتها_Impl,                    /* SYSTEM_CALL_xEventGroupWaitBits. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupWaitBits. */
        #پایان_اگر

        /* The system calls above this line take 5 parameters. */

        #إذا ( INCLUDE_xTaskDelayUntil == 1 )
            ( UBaseType_t ) MPU_xTaskDelayUntilImpl,                        /* SYSTEM_CALL_xTaskDelayUntil. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskDelayUntil. */
        #پایان_اگر

        #إذا ( INCLUDE_xTaskAbortDelay == 1 )
            ( UBaseType_t ) MPU_xTaskAbortDelayImpl,                        /* SYSTEM_CALL_xTaskAbortDelay. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskAbortDelay. */
        #پایان_اگر

        #إذا ( INCLUDE_vTaskDelay == 1 )
            ( UBaseType_t ) MPU_vTaskDelayImpl,                             /* SYSTEM_CALL_vTaskDelay. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskDelay. */
        #پایان_اگر

        #إذا ( INCLUDE_ux_Task_اولویت_Get == 1 )
            ( UBaseType_t ) MPU_ux_Task_اولویت_Get_Impl,                      /* SYSTEM_CALL_uxTaskPriorityGet. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskPriorityGet. */
        #پایان_اگر

        #إذا ( INCLUDE_eTaskGetState == 1 )
            ( UBaseType_t ) MPU_eTaskGetStateImpl,                          /* SYSTEM_CALL_eTaskGetState. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_eTaskGetState. */
        #پایان_اگر

        #إذا ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_vTaskGetInfoImpl,                           /* SYSTEM_CALL_vTaskGetInfo. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskGetInfo. */
        #پایان_اگر

        #إذا ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
            ( UBaseType_t ) MPU_xTaskGetIdleTaskHandleImpl,                 /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #پایان_اگر

        #إذا ( INCLUDE_vTaskSuspend == 1 )
            ( UBaseType_t ) MPU_vTaskSuspendImpl,                           /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) MPU_vTaskResumeImpl,                            /* SYSTEM_CALL_vTaskResume. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskResume. */
        #پایان_اگر

        ( UBaseType_t ) MPU_x_Task_Get_Tick_شمار_Impl,                          /* SYSTEM_CALL_xTaskGetTickCount. */
        ( UBaseType_t ) MPU_ux_Task_Get_عدد_از_Tasks_Impl,                     /* SYSTEM_CALL_uxTaskGetNumberOfTasks. */

        #إذا ( config_GENERATE_پیاپی_زمان_STATS == 1 )
            ( UBaseType_t ) MPU_ul_Task_Get_پیاپی_زمان_Counter_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) MPU_ul_Task_Get_پیاپی_زمان_Percent_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #پایان_اگر

        #إذا ( ( config_GENERATE_پیاپی_زمان_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_پیاپی_زمان_Percent_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_پیاپی_زمان_Counter_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #پایان_اگر

        #إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )
            ( UBaseType_t ) MPU_v_Task_مجموعه_Application_Task_برچسب_Impl,             /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) MPU_x_Task_Get_Application_Task_برچسب_Impl,             /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #پایان_اگر

        #إذا ( config_رقم_THREAD_LOCAL_STORAGE_اشارهگرها != 0 )
            ( UBaseType_t ) MPU_v_Task_مجموعه_Thread_Local_Storage_اشاره_گر_Impl,      /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) MPU_pv_Task_Get_Thread_Local_Storage_اشاره_گر_Impl,     /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #پایان_اگر

        #إذا ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_uxTaskGetSystemStateImpl,                   /* SYSTEM_CALL_uxTaskGetSystemState. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetSystemState. */
        #پایان_اگر

        #إذا ( INCLUDE_ux_Task_Get_پشته_بالا_Water_Mark == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_پشته_بالا_Water_Mark_Impl,            /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #پایان_اگر

        #إذا ( INCLUDE_ux_Task_Get_پشته_بالا_Water_Mark2 == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_پشته_بالا_Water_Mark2_Impl,           /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #پایان_اگر

        #إذا ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )
            ( UBaseType_t ) MPU_xTaskGetCurrentTaskHandleImpl,              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #پایان_اگر

        #إذا ( INCLUDE_xTaskGetSchedulerState == 1 )
            ( UBaseType_t ) MPU_xTaskGetSchedulerStateImpl,                 /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #پایان_اگر

        ( UBaseType_t ) MPU_v_Task_مجموعه_زمان_بیرون_State_Impl,                       /* SYSTEM_CALL_vTaskSetTimeOutState. */
        ( UBaseType_t ) MPU_x_Task_Check_For_زمان_بیرون_Impl,                       /* SYSTEM_CALL_xTaskCheckForTimeOut. */

        #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_ulTaskGenericNotifyTakeImpl,                /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyStateClearImpl,           /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) MPU_ul_Task_Generic_Notify_مقدار_Clear_Impl,          /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #پایان_اگر

        ( UBaseType_t ) MPU_x_صف_Generic_Send_Impl,                          /* SYSTEM_CALL_xQueueGenericSend. */
        ( UBaseType_t ) MPU_ux_صف_Messages_انتظار_Impl,                     /* SYSTEM_CALL_uxQueueMessagesWaiting. */
        ( UBaseType_t ) MPU_ux_صف_Spaces_موجود_Impl,                     /* SYSTEM_CALL_uxQueueSpacesAvailable. */
        ( UBaseType_t ) MPU_x_صف_Receive_Impl,                              /* SYSTEM_CALL_xQueueReceive. */
        ( UBaseType_t ) MPU_x_صف_Peek_Impl,                                 /* SYSTEM_CALL_xQueuePeek. */
        ( UBaseType_t ) MPU_x_صف_Semaphore_Take_Impl,                        /* SYSTEM_CALL_xQueueSemaphoreTake. */

        #إذا ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
            ( UBaseType_t ) MPU_x_صف_Get_Mutex_Holder_Impl,                   /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #پایان_اگر

        #إذا ( configUSE_RECURSIVE_MUTEXES == 1 )
            ( UBaseType_t ) MPU_x_صف_Take_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) MPU_x_صف_Give_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #پایان_اگر

        #إذا ( config_USE_صف_SETS == 1 )
            ( UBaseType_t ) MPU_x_صف_Select_From_مجموعه_Impl,                    /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) MPU_x_صف_جمع_کن_مقصد_مجموعه_Impl,                         /* SYSTEM_CALL_xQueueAddToSet. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueAddToSet. */
        #پایان_اگر

        #إذا config_صف_REGISTRY_اندازه > 0
            ( UBaseType_t ) MPU_v_صف_جمع_کن_مقصد_Registry_Impl,                    /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) MPU_v_صف_Unregister_صف_Impl,                  /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) MPU_pc_صف_Get_Name_Impl,                         /* SYSTEM_CALL_pcQueueGetName. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcQueueGetName. */
        #پایان_اگر

        #إذا ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_pvTimerGetTimerIDImpl,                      /* SYSTEM_CALL_pvTimerGetTimerID. */
            ( UBaseType_t ) MPU_v_Timer_مجموعه_Timer_IDImpl,                       /* SYSTEM_CALL_vTimerSetTimerID. */
            ( UBaseType_t ) MPU_x_Timer_Is_Timer_فعال_Impl,                    /* SYSTEM_CALL_xTimerIsTimerActive. */
            ( UBaseType_t ) MPU_xTimerGetTimerDaemonTaskHandleImpl,         /* SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle. */
            ( UBaseType_t ) MPU_pcTimerGetNameImpl,                         /* SYSTEM_CALL_pcTimerGetName. */
            ( UBaseType_t ) MPU_v_Timer_مجموعه_Reload_نما_Impl,                    /* SYSTEM_CALL_vTimerSetReloadMode. */
            ( UBaseType_t ) MPU_x_Timer_Get_Reload_نما_Impl,                    /* SYSTEM_CALL_xTimerGetReloadMode. */
            ( UBaseType_t ) MPU_ux_Timer_Get_Reload_نما_Impl,                   /* SYSTEM_CALL_uxTimerGetReloadMode. */
            ( UBaseType_t ) MPU_xTimerGetPeriodImpl,                        /* SYSTEM_CALL_xTimerGetPeriod. */
            ( UBaseType_t ) MPU_x_Timer_Get_Expiry_زمان_Impl,                    /* SYSTEM_CALL_xTimerGetExpiryTime. */
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
        #پایان_اگر

        #إذا ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_گروه_Clear_بیتها_Impl,                   /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) MPU_x_Event_گروه_مجموعه_بیتها_Impl,                     /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) MPU_x_Event_گروه_Sync_Impl,                        /* SYSTEM_CALL_xEventGroupSync. */

            #إذا ( configUSE_TRACE_FACILITY == 1 )
                ( UBaseType_t ) MPU_ux_Event_گروه_Get_عدد_Impl,              /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) MPU_v_Event_گروه_مجموعه_عدد_Impl,               /* SYSTEM_CALL_vEventGroupSetNumber. */
            #وإلا
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_vEventGroupSetNumber. */
            #پایان_اگر
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSync. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxEventGroupGetNumber. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vEventGroupSetNumber. */
        #پایان_اگر

        #إذا ( config_USE_جریان_BUFFERS == 1 )
            ( UBaseType_t ) MPU_x_جریان_میانگیر_Send_Impl,                      /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) MPU_x_جریان_میانگیر_Receive_Impl,                   /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) MPU_x_جریان_میانگیر_Is_پر_Impl,                    /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) MPU_x_جریان_میانگیر_Is_خالی_Impl,                   /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) MPU_x_جریان_میانگیر_Spaces_موجود_Impl,           /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) MPU_x_جریان_میانگیر_بایتها_موجود_Impl,            /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) MPU_x_جریان_میانگیر_مجموعه_Trigger_Level_Impl,           /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) MPU_x_جریان_میانگیر_بعدی_پیام_درازی_بایتها_Impl     /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #وإلا
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #پایان_اگر

    };
/*-----------------------------------------------------------*/

#پایان_اگر /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/
