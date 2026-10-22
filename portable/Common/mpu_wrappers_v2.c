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
#شامل "FreeRTOS.h"
#شامل "task.h"
#شامل "queue.h"
#شامل "timers.h"
#شامل "event_groups.h"
#شامل "stream_buffer.h"
#شامل "mpu_prototypes.h"
#شامل "mpu_syscall_numbers.h"

#تعریف_منسوخ MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#اگر ( ( پورٹ_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #اگر_غیر_تعریف_شدہ config_PROTECTED_KERNEL_OBJECT_POOL_سائز
        #غلطی config_PROTECTED_KERNEL_OBJECT_POOL_سائز must be defined مقصد زیادہ_سے_زیادہ نمبر کا kernel objects اندر the application.
    #اگر_ختم

/**
 * @brief Offset added to the index before returning to the user.
 *
 * If the actual handle is stored at index i, ( i + INDEX_OFFSET )
 * is returned to the user.
 */
    #تعریف_کرو اشاریہ_انحراف    1

/**
 * @brief Opaque type for a kernel object.
 */
    ساخت OpaqueObject;
    قسمتعریف ساخت OpaqueObject * OpaqueObjectHandle_t;

/**
 * @brief Defines kernel object in the kernel object pool.
 */
    قسمتعریف ساخت KernelObject
    {
        OpaqueObjectHandle_t x_اندرونی_Object_Handle;
        uint32_t ulKernelObjectType;
        خالی * pv_Kernel_Object_ڈیٹا;
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
    ( ( ( ( l_اشاریہ ) >= اشاریہ_انحراف ) &&       \
        ( ( l_اشاریہ ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_سائز + اشاریہ_انحراف ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Checks whether an internal index is valid or not.
 */
    #تعریف_کرو IS_اندرونی_اشاریہ_VALID( l_اشاریہ )   \
    ( ( ( ( l_اشاریہ ) >= 0 ) &&                  \
        ( ( l_اشاریہ ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_سائز ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Converts an internal index into external.
 */
    #تعریف_کرو CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ )    ( ( l_اشاریہ ) + اشاریہ_انحراف )

/**
 * @brief Converts an external index into internal.
 */
    #تعریف_کرو CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ )    ( ( l_اشاریہ ) - اشاریہ_انحراف )

/**
 * @brief Max value that fits in a UBaseType_t type.
 */
    #تعریف_کرو mpuUBASETYPE_MAX    ( ~( ( UBaseType_t ) 0 ) )

/**
 * @brief Check if multiplying a and b will result in overflow.
 */
    #تعریف_کرو mpu_MULTIPLY_BASETYPE_WILL_حد_سے_تجاوز( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( mpuUBASETYPE_MAX / ( a ) ) ) )

/**
 * @brief Get the index of a free slot in the kernel object pool.
 *
 * If a free slot is found, this function marks the slot as
 * "not free".
 *
 * @return Index of a free slot is returned, if a free slot is
 *         found. Otherwise -1 is returned.
 */
    ساکن int32_t MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool( خالی ) PRIVILEGED_FUNCTION;

/**
 * @brief Set the given index as free in the kernel object pool.
 *
 * @param lIndex The index to set as free.
 */
    ساکن خالی MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( int32_t l_اشاریہ ) PRIVILEGED_FUNCTION;

/**
 * @brief Get the index at which a given kernel object is stored.
 *
 * @param xHandle The given kernel object handle.
 * @param ulKernelObjectType The kernel object type.
 *
 * @return Index at which the kernel object is stored if it is a valid
 *         handle, -1 otherwise.
 */
    ساکن int32_t MPU_Get_اشاریہ_For_Handle( OpaqueObjectHandle_t xHandle,
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
    ساکن خالی MPU_Store_Handle_And_ڈیٹا_At_اشاریہ( int32_t l_اشاریہ,
                                               OpaqueObjectHandle_t xHandle,
                                               خالی * pv_Kernel_Object_ڈیٹا,
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
    ساکن OpaqueObjectHandle_t MPU_Get_Handle_At_اشاریہ( int32_t l_اشاریہ,
                                                      uint32_t ulKernelObjectType ) PRIVILEGED_FUNCTION;

    #اگر ( configUSE_TIMERS == 1 )

/**
 * @brief The function registered as callback for all the timers.
 *
 * We intercept all the timer callbacks so that we can call application
 * callbacks with opaque handle.
 *
 * @param xInternalHandle The internal timer handle.
 */
        ساکن خالی MPU_TimerCallback( TimerHandle_t x_اندرونی_Handle ) PRIVILEGED_FUNCTION;

    #اگر_ختم /* #if ( configUSE_TIMERS == 1 ) */

/*
 * Wrappers to keep all the casting in one place.
 */
    #تعریف_کرو MPU_Store_قطار_Handle_At_اشاریہ( l_اشاریہ, xHandle )                 MPU_Store_Handle_And_ڈیٹا_At_اشاریہ( ( l_اشاریہ ), ( OpaqueObjectHandle_t ) ( xHandle ), تہی, KERNEL_OBJECT_TYPE_قطار )
    #تعریف_کرو MPU_Get_قطار_Handle_At_اشاریہ( l_اشاریہ )                            ( قطار_Handle_t ) MPU_Get_Handle_At_اشاریہ( ( l_اشاریہ ), KERNEL_OBJECT_TYPE_قطار )

    #اگر ( config_USE_قطار_SETS == 1 )
        #تعریف_کرو MPU_Store_قطار_سیٹ_Handle_At_اشاریہ( l_اشاریہ, xHandle )          MPU_Store_Handle_And_ڈیٹا_At_اشاریہ( ( l_اشاریہ ), ( OpaqueObjectHandle_t ) ( xHandle ), تہی, KERNEL_OBJECT_TYPE_قطار )
        #تعریف_کرو MPU_Get_قطار_سیٹ_Handle_At_اشاریہ( l_اشاریہ )                     ( قطار_سیٹ_Handle_t ) MPU_Get_Handle_At_اشاریہ( ( l_اشاریہ ), KERNEL_OBJECT_TYPE_قطار )
        #تعریف_کرو MPU_Store_قطار_سیٹ_Member_Handle_At_اشاریہ( l_اشاریہ, xHandle )    MPU_Store_Handle_And_ڈیٹا_At_اشاریہ( ( l_اشاریہ ), ( OpaqueObjectHandle_t ) ( xHandle ), تہی, KERNEL_OBJECT_TYPE_قطار )
        #تعریف_کرو MPU_Get_قطار_سیٹ_Member_Handle_At_اشاریہ( l_اشاریہ )               ( قطار_سیٹ_Member_Handle_t ) MPU_Get_Handle_At_اشاریہ( ( l_اشاریہ ), KERNEL_OBJECT_TYPE_قطار )
        #تعریف_کرو MPU_Get_اشاریہ_For_قطار_سیٹ_Member_Handle( xHandle )             MPU_Get_اشاریہ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_قطار )
    #اگر_ختم

/*
 * Wrappers to keep all the casting in one place for Task APIs.
 */
    #تعریف_کرو MPU_Store_Task_Handle_At_اشاریہ( l_اشاریہ, xHandle )            MPU_Store_Handle_And_ڈیٹا_At_اشاریہ( ( l_اشاریہ ), ( OpaqueObjectHandle_t ) ( xHandle ), تہی, KERNEL_OBJECT_TYPE_TASK )
    #تعریف_کرو MPU_Get_Task_Handle_At_اشاریہ( l_اشاریہ )                       ( TaskHandle_t ) MPU_Get_Handle_At_اشاریہ( ( l_اشاریہ ), KERNEL_OBJECT_TYPE_TASK )
    #تعریف_کرو MPU_Get_اشاریہ_For_Task_Handle( xHandle )                     MPU_Get_اشاریہ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TASK )

    #اگر ( configUSE_EVENT_GROUPS == 1 )
/*
 * Wrappers to keep all the casting in one place for Event Group APIs.
 */
        #تعریف_کرو MPU_Store_Event_گروہ_Handle_At_اشاریہ( l_اشاریہ, xHandle )      MPU_Store_Handle_And_ڈیٹا_At_اشاریہ( ( l_اشاریہ ), ( OpaqueObjectHandle_t ) ( xHandle ), تہی, KERNEL_OBJECT_TYPE_EVENT_گروہ )
        #تعریف_کرو MPU_Get_Event_گروہ_Handle_At_اشاریہ( l_اشاریہ )                 ( Event_گروہ_Handle_t ) MPU_Get_Handle_At_اشاریہ( ( l_اشاریہ ), KERNEL_OBJECT_TYPE_EVENT_گروہ )
        #تعریف_کرو MPU_Get_اشاریہ_For_Event_گروہ_Handle( xHandle )               MPU_Get_اشاریہ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_EVENT_گروہ )

    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */

    #اگر ( config_USE_دھارا_BUFFERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Stream Buffer APIs.
 */
        #تعریف_کرو MPU_Store_دھارا_بفر_Handle_At_اشاریہ( l_اشاریہ, xHandle )    MPU_Store_Handle_And_ڈیٹا_At_اشاریہ( ( l_اشاریہ ), ( OpaqueObjectHandle_t ) ( xHandle), تہی, KERNEL_OBJECT_TYPE_دھارا_بفر )
        #تعریف_کرو MPU_Get_دھارا_بفر_Handle_At_اشاریہ( l_اشاریہ )               ( دھارا_بفر_Handle_t ) MPU_Get_Handle_At_اشاریہ( ( l_اشاریہ ), KERNEL_OBJECT_TYPE_دھارا_بفر )
        #تعریف_کرو MPU_Get_اشاریہ_For_دھارا_بفر_Handle( xHandle )             MPU_Get_اشاریہ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_دھارا_بفر )

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

    #اگر ( configUSE_TIMERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Timer APIs.
 */
        #تعریف_کرو MPU_Store_Timer_Handle_At_اشاریہ( l_اشاریہ, xHandle, pxApplicationCallback )    MPU_Store_Handle_And_ڈیٹا_At_اشاریہ( ( l_اشاریہ ), ( OpaqueObjectHandle_t ) ( xHandle ), ( خالی * ) ( pxApplicationCallback ), KERNEL_OBJECT_TYPE_TIMER )
        #تعریف_کرو MPU_Get_Timer_Handle_At_اشاریہ( l_اشاریہ )                                      ( TimerHandle_t ) MPU_Get_Handle_At_اشاریہ( ( l_اشاریہ ), KERNEL_OBJECT_TYPE_TIMER )
        #تعریف_کرو MPU_Get_اشاریہ_For_Timer_Handle( xHandle )                                    MPU_Get_اشاریہ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TIMER )

    #اگر_ختم /* #if ( configUSE_TIMERS == 1 ) */

/*-----------------------------------------------------------*/

/**
 * @brief Kernel object pool.
 */
    PRIVILEGED_ڈیٹا ساکن KernelObject_t xKernelObjectPool[ config_PROTECTED_KERNEL_OBJECT_POOL_سائز ] = { 0 };
/*-----------------------------------------------------------*/

    ساکن int32_t MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool( خالی ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_Free_اشاریہ = -1;

        /* This function is called only from resource create APIs
         * which are not supposed to be called from ISRs. Therefore,
         * we only need to suspend the scheduler and do not require
         * critical section. */
        vTaskSuspendAll();
        {
            برائے( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_سائز; i++ )
            {
                اگر( xKernelObjectPool[ i ].x_اندرونی_Object_Handle == تہی )
                {
                    /* Mark this index as not free. */
                    xKernelObjectPool[ i ].x_اندرونی_Object_Handle = ( OpaqueObjectHandle_t ) ( ~0U );
                    l_Free_اشاریہ = i;
                    توڑو;
                }
            }
        }
        ( خالی ) xTaskResumeAll();

        واپس l_Free_اشاریہ;
    }
/*-----------------------------------------------------------*/

    ساکن خالی MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( int32_t l_اشاریہ ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_اندرونی_اشاریہ_VALID( l_اشاریہ ) != pdFALSE );

        taskENTER_CRITICAL();
        {
            xKernelObjectPool[ l_اشاریہ ].x_اندرونی_Object_Handle = تہی;
            xKernelObjectPool[ l_اشاریہ ].ulKernelObjectType = KERNEL_OBJECT_TYPE_INVALID;
            xKernelObjectPool[ l_اشاریہ ].pv_Kernel_Object_ڈیٹا = تہی;
        }
        taskEXIT_CRITICAL();
    }
/*-----------------------------------------------------------*/

    ساکن int32_t MPU_Get_اشاریہ_For_Handle( OpaqueObjectHandle_t xHandle,
                                          uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_اشاریہ = -1;

        configASSERT( xHandle != تہی );

        برائے( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_سائز; i++ )
        {
            اگر( ( xKernelObjectPool[ i ].x_اندرونی_Object_Handle == xHandle ) &&
                ( xKernelObjectPool[ i ].ulKernelObjectType == ulKernelObjectType ) )
            {
                l_اشاریہ = i;
                توڑو;
            }
        }

        واپس l_اشاریہ;
    }
/*-----------------------------------------------------------*/

    ساکن خالی MPU_Store_Handle_And_ڈیٹا_At_اشاریہ( int32_t l_اشاریہ,
                                               OpaqueObjectHandle_t xHandle,
                                               خالی * pv_Kernel_Object_ڈیٹا,
                                               uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_اندرونی_اشاریہ_VALID( l_اشاریہ ) != pdFALSE );
        xKernelObjectPool[ l_اشاریہ ].x_اندرونی_Object_Handle = xHandle;
        xKernelObjectPool[ l_اشاریہ ].ulKernelObjectType = ulKernelObjectType;
        xKernelObjectPool[ l_اشاریہ ].pv_Kernel_Object_ڈیٹا = pv_Kernel_Object_ڈیٹا;
    }
/*-----------------------------------------------------------*/

    ساکن OpaqueObjectHandle_t MPU_Get_Handle_At_اشاریہ( int32_t l_اشاریہ,
                                                      uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        OpaqueObjectHandle_t xObjectHandle = تہی;

        configASSERT( IS_اندرونی_اشاریہ_VALID( l_اشاریہ ) != pdFALSE );

        اگر( xKernelObjectPool[ l_اشاریہ ].ulKernelObjectType == ulKernelObjectType )
        {
            xObjectHandle = xKernelObjectPool[ l_اشاریہ ].x_اندرونی_Object_Handle;
        }

        واپس xObjectHandle;
    }
/*-----------------------------------------------------------*/

    #اگر ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        خالی v_Grant_Access_مقصد_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                         int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;

            اگر( IS_EXTERNAL_اشاریہ_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                اگر( xExternalTaskHandle == تہی )
                {
                    v_پورٹ_Grant_Access_مقصد_Kernel_Object( xExternalTaskHandle, CONVERT_مقصد_اندرونی_اشاریہ( lExternalKernelObjectHandle ) );
                }
                ورنہ
                {
                    l_External_Task_اشاریہ = ( int32_t ) xExternalTaskHandle;

                    اگر( IS_EXTERNAL_اشاریہ_VALID( l_External_Task_اشاریہ ) != pdFALSE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_External_Task_اشاریہ ) );

                        اگر( x_اندرونی_Task_Handle != تہی )
                        {
                            v_پورٹ_Grant_Access_مقصد_Kernel_Object( x_اندرونی_Task_Handle,
                                                            CONVERT_مقصد_اندرونی_اشاریہ( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #اگر_ختم /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        خالی v_Revoke_Access_مقصد_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                          int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;

            اگر( IS_EXTERNAL_اشاریہ_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                اگر( xExternalTaskHandle == تہی )
                {
                    v_پورٹ_Revoke_Access_مقصد_Kernel_Object( xExternalTaskHandle, CONVERT_مقصد_اندرونی_اشاریہ( lExternalKernelObjectHandle ) );
                }
                ورنہ
                {
                    l_External_Task_اشاریہ = ( int32_t ) xExternalTaskHandle;

                    اگر( IS_EXTERNAL_اشاریہ_VALID( l_External_Task_اشاریہ ) != pdFALSE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_External_Task_اشاریہ ) );

                        اگر( x_اندرونی_Task_Handle != تہی )
                        {
                            v_پورٹ_Revoke_Access_مقصد_Kernel_Object( x_اندرونی_Task_Handle,
                                                             CONVERT_مقصد_اندرونی_اشاریہ( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #اگر_ختم /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        ساکن خالی MPU_TimerCallback( TimerHandle_t x_اندرونی_Handle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t i, l_اشاریہ = -1;
            TimerHandle_t xExternalHandle = تہی;
            TimerCallbackFunction_t px_Application_Call_عقب = تہی;

            /* Coming from the timer task and therefore, should be valid. */
            configASSERT( x_اندرونی_Handle != تہی );

            برائے( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_سائز; i++ )
            {
                اگر( ( ( TimerHandle_t ) xKernelObjectPool[ i ].x_اندرونی_Object_Handle == x_اندرونی_Handle ) &&
                    ( xKernelObjectPool[ i ].ulKernelObjectType == KERNEL_OBJECT_TYPE_TIMER ) )
                {
                    l_اشاریہ = i;
                    توڑو;
                }
            }

            configASSERT( l_اشاریہ != -1 );
            xExternalHandle = ( TimerHandle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );

            px_Application_Call_عقب = ( TimerCallbackFunction_t ) xKernelObjectPool[ l_اشاریہ ].pv_Kernel_Object_ڈیٹا;
            px_Application_Call_عقب( xExternalHandle );
        }

    #اگر_ختم /* #if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for tasks APIs.                   */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskDelayUntil == 1 )

        بنیاد_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ثابت px_پچھلا_Wake_وقت,
                                            TickType_t x_وقت_Increment ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ثابت px_پچھلا_Wake_وقت,
                                            TickType_t x_وقت_Increment ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            بنیاد_Type_t x_Is_پچھلا_Wake_وقت_Accessible = pdFALSE;

            اگر( ( px_پچھلا_Wake_وقت != تہی ) && ( x_وقت_Increment > 0U ) )
            {
                x_Is_پچھلا_Wake_وقت_Accessible = x_پورٹ_Is_Authorized_مقصد_Access_بفر( px_پچھلا_Wake_وقت,
                                                                                 حجم( TickType_t ),
                                                                                 ( tskMPU_WRITE_PERMISSION | tskMPU_READ_PERMISSION ) );

                اگر( x_Is_پچھلا_Wake_وقت_Accessible == pdTRUE )
                {
                    xReturn = xTaskDelayUntil( px_پچھلا_Wake_وقت, x_وقت_Increment );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskAbortDelay == 1 )

        بنیاد_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) xTask;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Task_Handle != تہی )
                    {
                        xReturn = xTaskAbortDelay( x_اندرونی_Task_Handle );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_vTaskDelay == 1 )

        خالی MPU_vTaskDelayImpl( TickType_t x_Ticks_مقصد_Delay ) PRIVILEGED_FUNCTION;

        خالی MPU_vTaskDelayImpl( TickType_t x_Ticks_مقصد_Delay ) /* PRIVILEGED_FUNCTION */
        {
            vTaskDelay( x_Ticks_مقصد_Delay );
        }

    #اگر_ختم /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_ux_Task_ترجیح_Get == 1 )

        UBaseType_t MPU_ux_Task_ترجیح_Get_Impl( ثابت TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_ترجیح_Get_Impl( ثابت TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;

            اگر( pxTask == تہی )
            {
                uxReturn = ux_Task_ترجیح_Get( pxTask );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) pxTask;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_اندرونی_Task_Handle != تہی )
                        {
                            uxReturn = ux_Task_ترجیح_Get( x_اندرونی_Task_Handle );
                        }
                    }
                }
            }

            واپس uxReturn;
        }

    #اگر_ختم /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            eTaskState eReturn = eInvalid;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            l_اشاریہ = ( int32_t ) pxTask;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Task_Handle != تہی )
                    {
                        eReturn = eTaskGetState( x_اندرونی_Task_Handle );
                    }
                }
            }

            واپس eReturn;
        }

    #اگر_ختم /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TRACE_FACILITY == 1 )

        خالی MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_حالت_t * px_Task_حالت,
                                   بنیاد_Type_t x_Get_Free_ڈھیر_Space,
                                   eTaskState eState ) PRIVILEGED_FUNCTION;

        خالی MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_حالت_t * px_Task_حالت,
                                   بنیاد_Type_t x_Get_Free_ڈھیر_Space,
                                   eTaskState eState ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            بنیاد_Type_t x_Is_Task_حالت_Writeable = pdFALSE;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            x_Is_Task_حالت_Writeable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( px_Task_حالت,
                                                                      حجم( Task_حالت_t ),
                                                                      tskMPU_WRITE_PERMISSION );

            اگر( x_Is_Task_حالت_Writeable == pdTRUE )
            {
                اگر( xTask == تہی )
                {
                    vTaskGetInfo( xTask, px_Task_حالت, x_Get_Free_ڈھیر_Space, eState );
                }
                ورنہ
                {
                    l_اشاریہ = ( int32_t ) xTask;

                    اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                        {
                            x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                            اگر( x_اندرونی_Task_Handle != تہی )
                            {
                                vTaskGetInfo( x_اندرونی_Task_Handle, px_Task_حالت, x_Get_Free_ڈھیر_Space, eState );
                            }
                        }
                    }
                }
            }
        }

    #اگر_ختم /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( خالی ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( خالی ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xIdleTaskHandle = تہی;

            xIdleTaskHandle = xTaskGetIdleTaskHandle();

            واپس xIdleTaskHandle;
        }

    #اگر_ختم /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_vTaskSuspend == 1 )

        خالی MPU_vTaskSuspendImpl( TaskHandle_t px_Task_مقصد_Suspend ) PRIVILEGED_FUNCTION;

        خالی MPU_vTaskSuspendImpl( TaskHandle_t px_Task_مقصد_Suspend ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            اگر( px_Task_مقصد_Suspend == تہی )
            {
                vTaskSuspend( px_Task_مقصد_Suspend );
            }
            ورنہ
            {
                /* After the scheduler starts, only privileged tasks are allowed
                 * to suspend other tasks. */
                #اگر ( INCLUDE_xTaskGetSchedulerState == 1 )
                    اگر( ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) || ( پورٹ_IS_TASK_PRIVILEGED() == pdTRUE ) )
                #ورنہ
                    اگر( پورٹ_IS_TASK_PRIVILEGED() == pdTRUE )
                #اگر_ختم
                {
                    l_اشاریہ = ( int32_t ) px_Task_مقصد_Suspend;

                    اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                        {
                            x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                            اگر( x_اندرونی_Task_Handle != تہی )
                            {
                                vTaskSuspend( x_اندرونی_Task_Handle );
                            }
                        }
                    }
                }
            }
        }

    #اگر_ختم /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_vTaskSuspend == 1 )

        خالی MPU_vTaskResumeImpl( TaskHandle_t px_Task_مقصد_Resume ) PRIVILEGED_FUNCTION;

        خالی MPU_vTaskResumeImpl( TaskHandle_t px_Task_مقصد_Resume ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            l_اشاریہ = ( int32_t ) px_Task_مقصد_Resume;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Task_Handle != تہی )
                    {
                        vTaskResume( x_اندرونی_Task_Handle );
                    }
                }
            }
        }

    #اگر_ختم /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_گنتی_Impl( خالی ) PRIVILEGED_FUNCTION;

    TickType_t MPU_x_Task_Get_Tick_گنتی_Impl( خالی ) /* PRIVILEGED_FUNCTION */
    {
        TickType_t xReturn;

        xReturn = x_Task_Get_Tick_گنتی();

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_نمبر_کا_Tasks_Impl( خالی ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Task_Get_نمبر_کا_Tasks_Impl( خالی ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn;

        uxReturn = ux_Task_Get_نمبر_کا_Tasks();

        واپس uxReturn;
    }
/*-----------------------------------------------------------*/

    #اگر ( config_GENERATE_تسلسل_وقت_STATS == 1 )

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_شمار_Impl( ثابت TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_شمار_Impl( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_تسلسل_وقت_شمار_TYPE xReturn = 0;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            اگر( xTask == تہی )
            {
                xReturn = ul_Task_Get_تسلسل_وقت_شمار( xTask );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) xTask;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_اندرونی_Task_Handle != تہی )
                        {
                            xReturn = ul_Task_Get_تسلسل_وقت_شمار( x_اندرونی_Task_Handle );
                        }
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_GENERATE_تسلسل_وقت_STATS == 1 )

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_Percent_Impl( ثابت TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_تسلسل_وقت_Percent_Impl( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_تسلسل_وقت_شمار_TYPE xReturn = 0;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            اگر( xTask == تہی )
            {
                xReturn = ul_Task_Get_تسلسل_وقت_Percent( xTask );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) xTask;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_اندرونی_Task_Handle != تہی )
                        {
                            xReturn = ul_Task_Get_تسلسل_وقت_Percent( x_اندرونی_Task_Handle );
                        }
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_GENERATE_تسلسل_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent_Impl( خالی ) PRIVILEGED_FUNCTION;

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent_Impl( خالی ) /* PRIVILEGED_FUNCTION */
        {
            config_تسلسل_وقت_شمار_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_تسلسل_وقت_Percent();

            واپس xReturn;
        }

    #اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_GENERATE_تسلسل_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار_Impl( خالی ) PRIVILEGED_FUNCTION;

        config_تسلسل_وقت_شمار_TYPE MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار_Impl( خالی ) /* PRIVILEGED_FUNCTION */
        {
            config_تسلسل_وقت_شمار_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_تسلسل_وقت_شمار();

            واپس xReturn;
        }

    #اگر_ختم /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_APPLICATION_TASK_لیبل == 1 )

        خالی MPU_v_Task_سیٹ_Application_Task_لیبل_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_لیبل_قدر ) PRIVILEGED_FUNCTION;

        خالی MPU_v_Task_سیٹ_Application_Task_لیبل_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_لیبل_قدر ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            اگر( xTask == تہی )
            {
                v_Task_سیٹ_Application_Task_لیبل( xTask, px_لیبل_قدر );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) xTask;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_اندرونی_Task_Handle != تہی )
                        {
                            v_Task_سیٹ_Application_Task_لیبل( x_اندرونی_Task_Handle, px_لیبل_قدر );
                        }
                    }
                }
            }
        }

    #اگر_ختم /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_APPLICATION_TASK_لیبل == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_لیبل_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_لیبل_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = تہی;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            اگر( xTask == تہی )
            {
                xReturn = x_Task_Get_Application_Task_لیبل( xTask );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) xTask;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_اندرونی_Task_Handle != تہی )
                        {
                            xReturn = x_Task_Get_Application_Task_لیبل( x_اندرونی_Task_Handle );
                        }
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_عدد_THREAD_LOCAL_STORAGE_اشارے != 0 )

        خالی MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر_Impl( TaskHandle_t x_Task_مقصد_سیٹ,
                                                        بنیاد_Type_t x_اشاریہ,
                                                        خالی * pv_قدر ) PRIVILEGED_FUNCTION;

        خالی MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر_Impl( TaskHandle_t x_Task_مقصد_سیٹ,
                                                        بنیاد_Type_t x_اشاریہ,
                                                        خالی * pv_قدر ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            اگر( x_Task_مقصد_سیٹ == تہی )
            {
                v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( x_Task_مقصد_سیٹ, x_اشاریہ, pv_قدر );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) x_Task_مقصد_سیٹ;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_اندرونی_Task_Handle != تہی )
                        {
                            v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( x_اندرونی_Task_Handle, x_اشاریہ, pv_قدر );
                        }
                    }
                }
            }
        }

    #اگر_ختم /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_عدد_THREAD_LOCAL_STORAGE_اشارے != 0 )

        خالی * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر_Impl( TaskHandle_t x_Task_مقصد_Query,
                                                           بنیاد_Type_t x_اشاریہ ) PRIVILEGED_FUNCTION;

        خالی * MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر_Impl( TaskHandle_t x_Task_مقصد_Query,
                                                           بنیاد_Type_t x_اشاریہ ) /* PRIVILEGED_FUNCTION */
        {
            خالی * pvReturn = تہی;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            اگر( x_Task_مقصد_Query == تہی )
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_اشارہ_گر( x_Task_مقصد_Query, x_اشاریہ );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) x_Task_مقصد_Query;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_اندرونی_Task_Handle != تہی )
                        {
                            pvReturn = pv_Task_Get_Thread_Local_Storage_اشارہ_گر( x_اندرونی_Task_Handle, x_اشاریہ );
                        }
                    }
                }
            }

            واپس pvReturn;
        }

    #اگر_ختم /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_حالت_t * px_Task_حالت_Array,
                                                  UBaseType_t ux_Array_سائز,
                                                  config_تسلسل_وقت_شمار_TYPE * pul_کل_تسلسل_وقت ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_حالت_t * px_Task_حالت_Array,
                                                  UBaseType_t ux_Array_سائز,
                                                  config_تسلسل_وقت_شمار_TYPE * pul_کل_تسلسل_وقت ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            بنیاد_Type_t x_Is_Task_حالت_Array_Writeable = pdFALSE;
            بنیاد_Type_t x_Is_کل_تسلسل_وقت_Writeable = pdFALSE;

            اگر( mpu_MULTIPLY_BASETYPE_WILL_حد_سے_تجاوز( حجم( Task_حالت_t ), ux_Array_سائز ) == 0 )
            {
                x_Is_Task_حالت_Array_Writeable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( px_Task_حالت_Array,
                                                                               حجم( Task_حالت_t ) * ( size_t ) ux_Array_سائز,
                                                                               tskMPU_WRITE_PERMISSION );

                اگر( pul_کل_تسلسل_وقت != تہی )
                {
                    x_Is_کل_تسلسل_وقت_Writeable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( pul_کل_تسلسل_وقت,
                                                                                حجم( config_تسلسل_وقت_شمار_TYPE ),
                                                                                tskMPU_WRITE_PERMISSION );
                }

                اگر( ( x_Is_Task_حالت_Array_Writeable == pdTRUE ) &&
                    ( ( pul_کل_تسلسل_وقت == تہی ) || ( x_Is_کل_تسلسل_وقت_Writeable == pdTRUE ) ) )
                {
                    uxReturn = uxTaskGetSystemState( px_Task_حالت_Array, ux_Array_سائز, pul_کل_تسلسل_وقت );
                }
            }

            واپس uxReturn;
        }

    #اگر_ختم /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            اگر( xTask == تہی )
            {
                uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark( xTask );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) xTask;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_اندرونی_Task_Handle != تہی )
                        {
                            uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark( x_اندرونی_Task_Handle );
                        }
                    }
                }
            }

            واپس uxReturn;
        }

    #اگر_ختم /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark2 == 1 )

        config_ڈھیر_گہرائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_ڈھیر_گہرائی_TYPE MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_ڈھیر_گہرائی_TYPE uxReturn = 0;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            اگر( xTask == تہی )
            {
                uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark2( xTask );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) xTask;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                    {
                        x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_اندرونی_Task_Handle != تہی )
                        {
                            uxReturn = ux_Task_Get_ڈھیر_بلند_Water_Mark2( x_اندرونی_Task_Handle );
                        }
                    }
                }
            }

            واپس uxReturn;
        }

    #اگر_ختم /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( خالی ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( خالی ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            TaskHandle_t xExternalTaskHandle = تہی;
            int32_t l_اشاریہ;

            x_اندرونی_Task_Handle = xTaskGetCurrentTaskHandle();

            اگر( x_اندرونی_Task_Handle != تہی )
            {
                l_اشاریہ = MPU_Get_اشاریہ_For_Task_Handle( x_اندرونی_Task_Handle );

                اگر( l_اشاریہ != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
            }

            واپس xExternalTaskHandle;
        }

    #اگر_ختم /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskGetSchedulerState == 1 )

        بنیاد_Type_t MPU_xTaskGetSchedulerStateImpl( خالی ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_xTaskGetSchedulerStateImpl( خالی ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = taskSCHEDULER_NOT_STARTED;

            xReturn = xTaskGetSchedulerState();

            واپس xReturn;
        }

    #اگر_ختم /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    خالی MPU_v_Task_سیٹ_وقت_برآمد_State_Impl( وقت_برآمد_t * ثابت px_وقت_برآمد ) PRIVILEGED_FUNCTION;

    خالی MPU_v_Task_سیٹ_وقت_برآمد_State_Impl( وقت_برآمد_t * ثابت px_وقت_برآمد ) /* PRIVILEGED_FUNCTION */
    {
        بنیاد_Type_t x_Is_وقت_برآمد_Writeable = pdFALSE;

        اگر( px_وقت_برآمد != تہی )
        {
            x_Is_وقت_برآمد_Writeable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( px_وقت_برآمد,
                                                                   حجم( وقت_برآمد_t ),
                                                                   tskMPU_WRITE_PERMISSION );

            اگر( x_Is_وقت_برآمد_Writeable == pdTRUE )
            {
                v_Task_سیٹ_وقت_برآمد_State( px_وقت_برآمد );
            }
        }
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_Task_Check_For_وقت_برآمد_Impl( وقت_برآمد_t * ثابت px_وقت_برآمد,
                                             TickType_t * ثابت px_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

    بنیاد_Type_t MPU_x_Task_Check_For_وقت_برآمد_Impl( وقت_برآمد_t * ثابت px_وقت_برآمد,
                                             TickType_t * ثابت px_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
    {
        بنیاد_Type_t xReturn = pdFALSE;
        بنیاد_Type_t x_Is_وقت_برآمد_Writeable = pdFALSE;
        بنیاد_Type_t x_Is_Ticks_مقصد_Wait_Writeable = pdFALSE;

        اگر( ( px_وقت_برآمد != تہی ) && ( px_Ticks_مقصد_Wait != تہی ) )
        {
            x_Is_وقت_برآمد_Writeable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( px_وقت_برآمد,
                                                                   حجم( وقت_برآمد_t ),
                                                                   tskMPU_WRITE_PERMISSION );
            x_Is_Ticks_مقصد_Wait_Writeable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( px_Ticks_مقصد_Wait,
                                                                       حجم( TickType_t ),
                                                                       tskMPU_WRITE_PERMISSION );

            اگر( ( x_Is_وقت_برآمد_Writeable == pdTRUE ) && ( x_Is_Ticks_مقصد_Wait_Writeable == pdTRUE ) )
            {
                xReturn = x_Task_Check_For_وقت_برآمد( px_وقت_برآمد, px_Ticks_مقصد_Wait );
            }
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنیاد_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_مقصد_Notify,
                                           UBaseType_t ux_اشاریہ_مقصد_Notify,
                                           uint32_t ul_قدر,
                                           eNotifyAction eAction,
                                           uint32_t * pul_پچھلا_Notification_قدر ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyParams_t xParams;

            xParams.x_Task_مقصد_Notify = x_Task_مقصد_Notify;
            xParams.ux_اشاریہ_مقصد_Notify = ux_اشاریہ_مقصد_Notify;
            xParams.ul_قدر = ul_قدر;
            xParams.eAction = eAction;
            xParams.pul_پچھلا_Notification_قدر = pul_پچھلا_Notification_قدر;

            xReturn = MPU_x_Task_Generic_Notify_اندراج( &( xParams ) );

            واپس xReturn;
        }

        بنیاد_Type_t MPU_xTaskGenericNotifyImpl( ثابت xTaskGenericNotifyParams_t * pxParams ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_xTaskGenericNotifyImpl( ثابت xTaskGenericNotifyParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            بنیاد_Type_t x_Is_پچھلا_Notification_قدر_Writeable = pdFALSE;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;
            بنیاد_Type_t xAreParamsReadable = pdFALSE;

            اگر( pxParams != تہی )
            {
                xAreParamsReadable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( pxParams,
                                                                      حجم( xTaskGenericNotifyParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            اگر( xAreParamsReadable == pdTRUE )
            {
                اگر( ( pxParams->ux_اشاریہ_مقصد_Notify < configTASK_NOTIFICATION_ARRAY_ENTRIES ) &&
                    ( ( pxParams->eAction == eNoAction ) ||
                      ( pxParams->eAction == e_سیٹ_بٹ ) ||
                      ( pxParams->eAction == eIncrement ) ||
                      ( pxParams->eAction == e_سیٹ_قدر_With_Overwrite ) ||
                      ( pxParams->eAction == e_سیٹ_قدر_Without_Overwrite ) ) )
                {
                    اگر( pxParams->pul_پچھلا_Notification_قدر != تہی )
                    {
                        x_Is_پچھلا_Notification_قدر_Writeable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( pxParams->pul_پچھلا_Notification_قدر,
                                                                                                 حجم( uint32_t ),
                                                                                                 tskMPU_WRITE_PERMISSION );
                    }

                    اگر( ( pxParams->pul_پچھلا_Notification_قدر == تہی ) ||
                        ( x_Is_پچھلا_Notification_قدر_Writeable == pdTRUE ) )
                    {
                        l_اشاریہ = ( int32_t ) ( pxParams->x_Task_مقصد_Notify );

                        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                            اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                            {
                                x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                                اگر( x_اندرونی_Task_Handle != تہی )
                                {
                                    xReturn = xTaskGenericNotify( x_اندرونی_Task_Handle,
                                                                  pxParams->ux_اشاریہ_مقصد_Notify,
                                                                  pxParams->ul_قدر,
                                                                  pxParams->eAction,
                                                                  pxParams->pul_پچھلا_Notification_قدر );
                                }
                            }
                        }
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنیاد_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_اشاریہ_مقصد_Wait_On,
                                               uint32_t ul_بٹ_مقصد_Clear_On_اندراج,
                                               uint32_t ul_بٹ_مقصد_Clear_On_Exit,
                                               uint32_t * pul_Notification_قدر,
                                               TickType_t x_Ticks_مقصد_Wait )
        {
            بنیاد_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyWaitParams_t xParams;

            xParams.ux_اشاریہ_مقصد_Wait_On = ux_اشاریہ_مقصد_Wait_On;
            xParams.ul_بٹ_مقصد_Clear_On_اندراج = ul_بٹ_مقصد_Clear_On_اندراج;
            xParams.ul_بٹ_مقصد_Clear_On_Exit = ul_بٹ_مقصد_Clear_On_Exit;
            xParams.pul_Notification_قدر = pul_Notification_قدر;
            xParams.x_Ticks_مقصد_Wait = x_Ticks_مقصد_Wait;

            xReturn = MPU_x_Task_Generic_Notify_Wait_اندراج( &( xParams ) );

            واپس xReturn;
        }

        بنیاد_Type_t MPU_xTaskGenericNotifyWaitImpl( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_xTaskGenericNotifyWaitImpl( ثابت xTaskGenericNotifyWaitParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            بنیاد_Type_t x_Is_Notification_قدر_Writable = pdFALSE;
            بنیاد_Type_t xAreParamsReadable = pdFALSE;

            اگر( pxParams != تہی )
            {
                xAreParamsReadable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( pxParams,
                                                                      حجم( xTaskGenericNotifyWaitParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            اگر( xAreParamsReadable == pdTRUE )
            {
                اگر( pxParams->ux_اشاریہ_مقصد_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
                {
                    اگر( pxParams->pul_Notification_قدر != تہی )
                    {
                        x_Is_Notification_قدر_Writable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( pxParams->pul_Notification_قدر,
                                                                                        حجم( uint32_t ),
                                                                                        tskMPU_WRITE_PERMISSION );
                    }

                    اگر( ( pxParams->pul_Notification_قدر == تہی ) ||
                        ( x_Is_Notification_قدر_Writable == pdTRUE ) )
                    {
                        xReturn = xTaskGenericNotifyWait( pxParams->ux_اشاریہ_مقصد_Wait_On,
                                                          pxParams->ul_بٹ_مقصد_Clear_On_اندراج,
                                                          pxParams->ul_بٹ_مقصد_Clear_On_Exit,
                                                          pxParams->pul_Notification_قدر,
                                                          pxParams->x_Ticks_مقصد_Wait );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_اشاریہ_مقصد_Wait_On,
                                                  بنیاد_Type_t x_Clear_گنتی_On_Exit,
                                                  TickType_t x_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_اشاریہ_مقصد_Wait_On,
                                                  بنیاد_Type_t x_Clear_گنتی_On_Exit,
                                                  TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;

            اگر( ux_اشاریہ_مقصد_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ulReturn = ulTaskGenericNotifyTake( ux_اشاریہ_مقصد_Wait_On, x_Clear_گنتی_On_Exit, x_Ticks_مقصد_Wait );
            }

            واپس ulReturn;
        }

    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنیاد_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_اشاریہ_مقصد_Clear ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_اشاریہ_مقصد_Clear ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            اگر( ux_اشاریہ_مقصد_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                اگر( xTask == تہی )
                {
                    xReturn = xTaskGenericNotifyStateClear( xTask, ux_اشاریہ_مقصد_Clear );
                }
                ورنہ
                {
                    l_اشاریہ = ( int32_t ) xTask;

                    اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                        {
                            x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                            اگر( x_اندرونی_Task_Handle != تہی )
                            {
                                xReturn = xTaskGenericNotifyStateClear( x_اندرونی_Task_Handle, ux_اشاریہ_مقصد_Clear );
                            }
                        }
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_اشاریہ_مقصد_Clear,
                                                        uint32_t ul_بٹ_مقصد_Clear ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ul_Task_Generic_Notify_قدر_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_اشاریہ_مقصد_Clear,
                                                        uint32_t ul_بٹ_مقصد_Clear ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Task = pdFALSE;

            اگر( ux_اشاریہ_مقصد_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                اگر( xTask == تہی )
                {
                    ulReturn = ul_Task_Generic_Notify_قدر_Clear( xTask, ux_اشاریہ_مقصد_Clear, ul_بٹ_مقصد_Clear );
                }
                ورنہ
                {
                    l_اشاریہ = ( int32_t ) xTask;

                    اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_مقصد_Access_Task = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Task == pdTRUE )
                        {
                            x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                            اگر( x_اندرونی_Task_Handle != تہی )
                            {
                                ulReturn = ul_Task_Generic_Notify_قدر_Clear( x_اندرونی_Task_Handle, ux_اشاریہ_مقصد_Clear, ul_بٹ_مقصد_Clear );
                            }
                        }
                    }
                }
            }

            واپس ulReturn;
        }

    #اگر_ختم /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Task APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #اگر ( config_SUPPORT_DYNAMIC_تخصیص == 1 )

        بنیاد_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_رمز,
                                    ثابت حرف * ثابت pcName,
                                    ثابت config_ڈھیر_گہرائی_TYPE ux_ڈھیر_گہرائی,
                                    خالی * pvParameters,
                                    UBaseType_t ux_ترجیح,
                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                /* xTaskCreate() can only be used to create privileged tasks in MPU port. */
                اگر( ( ux_ترجیح & پورٹ_PRIVILEGE_ثنائی_ہندسہ ) != 0 )
                {
                    xReturn = xTaskCreate( pv_Task_رمز, pcName, ux_ڈھیر_گہرائی, pvParameters, ux_ترجیح, &( x_اندرونی_Task_Handle ) );

                    اگر( ( xReturn == pdPASS ) && ( x_اندرونی_Task_Handle != تہی ) )
                    {
                        MPU_Store_Task_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Task_Handle );

                        اگر( pxCreatedTask != تہی )
                        {
                            *pxCreatedTask = ( TaskHandle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                        }
                    }
                    ورنہ
                    {
                        MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #اگر ( config_SUPPORT_STATIC_تخصیص == 1 )

        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_رمز,
                                            ثابت حرف * ثابت pcName,
                                            ثابت config_ڈھیر_گہرائی_TYPE ux_ڈھیر_گہرائی,
                                            خالی * ثابت pvParameters,
                                            UBaseType_t ux_ترجیح,
                                            ڈھیر_Type_t * ثابت pux_ڈھیر_بفر,
                                            StaticTask_t * ثابت px_Task_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xExternalTaskHandle = تہی;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                x_اندرونی_Task_Handle = xTaskCreateStatic( px_Task_رمز, pcName, ux_ڈھیر_گہرائی, pvParameters, ux_ترجیح, pux_ڈھیر_بفر, px_Task_بفر );

                اگر( x_اندرونی_Task_Handle != تہی )
                {
                    MPU_Store_Task_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Task_Handle );

                    #اگر ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        اگر( ( ux_ترجیح & پورٹ_PRIVILEGE_ثنائی_ہندسہ ) == 0 )
                        {
                            v_پورٹ_Grant_Access_مقصد_Kernel_Object( x_اندرونی_Task_Handle, l_اشاریہ );
                        }
                    }
                    #اگر_ختم

                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس xExternalTaskHandle;
        }

    #اگر_ختم /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_vTaskDelete == 1 )

        خالی MPU_vTaskDelete( TaskHandle_t px_Task_مقصد_Delete ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            int32_t l_اشاریہ;

            اگر( px_Task_مقصد_Delete == تہی )
            {
                x_اندرونی_Task_Handle = xTaskGetCurrentTaskHandle();
                l_اشاریہ = MPU_Get_اشاریہ_For_Task_Handle( x_اندرونی_Task_Handle );

                اگر( l_اشاریہ != -1 )
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }

                vTaskDelete( x_اندرونی_Task_Handle );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) px_Task_مقصد_Delete;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Task_Handle != تہی )
                    {
                        MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );
                        vTaskDelete( x_اندرونی_Task_Handle );
                    }
                }
            }
        }

    #اگر_ختم /* #if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/


    #اگر ( INCLUDE_v_Task_ترجیح_سیٹ == 1 )

        خالی MPU_v_Task_ترجیح_سیٹ( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_ترجیح ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            int32_t l_اشاریہ;

            اگر( pxTask == تہی )
            {
                v_Task_ترجیح_سیٹ( pxTask, ux_New_ترجیح );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) pxTask;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Task_Handle != تہی )
                    {
                        v_Task_ترجیح_سیٹ( x_اندرونی_Task_Handle, ux_New_ترجیح );
                    }
                }
            }
        }

    #اگر_ختم /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_xTaskGetHandle == 1 )

        TaskHandle_t MPU_xTaskGetHandle( ثابت حرف * pc_Name_مقصد_Query ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            TaskHandle_t xExternalTaskHandle = تہی;
            int32_t l_اشاریہ;

            x_اندرونی_Task_Handle = xTaskGetHandle( pc_Name_مقصد_Query );

            اگر( x_اندرونی_Task_Handle != تہی )
            {
                l_اشاریہ = MPU_Get_اشاریہ_For_Task_Handle( x_اندرونی_Task_Handle );

                اگر( l_اشاریہ != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
            }

            واپس xExternalTaskHandle;
        }

    #اگر_ختم /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/


    #اگر ( config_USE_APPLICATION_TASK_لیبل == 1 )

        بنیاد_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     خالی * pvParameter ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;

            اگر( xTask == تہی )
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) xTask;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Task_Handle != تہی )
                    {
                        xReturn = xTaskCallApplicationTaskHook( x_اندرونی_Task_Handle, pvParameter );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_SUPPORT_DYNAMIC_تخصیص == 1 )

        بنیاد_Type_t MPU_xTaskCreateRestricted( ثابت TaskParameters_t * ثابت pxTaskDefinition,
                                              TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                xReturn = xTaskCreateRestricted( pxTaskDefinition, &( x_اندرونی_Task_Handle ) );

                اگر( ( xReturn == pdPASS ) && ( x_اندرونی_Task_Handle != تہی ) )
                {
                    MPU_Store_Task_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Task_Handle );

                    #اگر ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        اگر( ( pxTaskDefinition->ux_ترجیح & پورٹ_PRIVILEGE_ثنائی_ہندسہ ) == 0 )
                        {
                            v_پورٹ_Grant_Access_مقصد_Kernel_Object( x_اندرونی_Task_Handle, l_اشاریہ );
                        }
                    }
                    #اگر_ختم

                    اگر( pxCreatedTask != تہی )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                    }
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #اگر ( config_SUPPORT_STATIC_تخصیص == 1 )

        بنیاد_Type_t MPU_xTaskCreateRestrictedStatic( ثابت TaskParameters_t * ثابت pxTaskDefinition,
                                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                xReturn = xTaskCreateRestrictedStatic( pxTaskDefinition, &( x_اندرونی_Task_Handle ) );

                اگر( ( xReturn == pdPASS ) && ( x_اندرونی_Task_Handle != تہی ) )
                {
                    MPU_Store_Task_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Task_Handle );

                    #اگر ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        اگر( ( pxTaskDefinition->ux_ترجیح & پورٹ_PRIVILEGE_ثنائی_ہندسہ ) == 0 )
                        {
                            v_پورٹ_Grant_Access_مقصد_Kernel_Object( x_اندرونی_Task_Handle, l_اشاریہ );
                        }
                    }
                    #اگر_ختم

                    اگر( pxCreatedTask != تہی )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                    }
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    خالی MPU_vTaskAllocateMPURegions( TaskHandle_t x_Task_مقصد_Modify,
                                      ثابت حافظہ_Region_t * ثابت xRegions ) /* PRIVILEGED_FUNCTION */
    {
        TaskHandle_t x_اندرونی_Task_Handle = تہی;
        int32_t l_اشاریہ;

        اگر( x_Task_مقصد_Modify == تہی )
        {
            vTaskAllocateMPURegions( x_Task_مقصد_Modify, xRegions );
        }
        ورنہ
        {
            l_اشاریہ = ( int32_t ) x_Task_مقصد_Modify;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_Task_Handle != تہی )
                {
                    vTaskAllocateMPURegions( x_اندرونی_Task_Handle, xRegions );
                }
            }
        }
    }
/*-----------------------------------------------------------*/

    #اگر ( config_SUPPORT_STATIC_تخصیص == 1 )

        بنیاد_Type_t MPU_xTaskGetStaticBuffers( TaskHandle_t xTask,
                                              ڈھیر_Type_t ** ppux_ڈھیر_بفر,
                                              StaticTask_t ** ppx_Task_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_اندرونی_Task_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t xReturn = pdFALSE;

            اگر( xTask == تہی )
            {
                x_اندرونی_Task_Handle = xTaskGetCurrentTaskHandle();
                xReturn = xTaskGetStaticBuffers( x_اندرونی_Task_Handle, ppux_ڈھیر_بفر, ppx_Task_بفر );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) xTask;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Task_Handle != تہی )
                    {
                        xReturn = xTaskGetStaticBuffers( x_اندرونی_Task_Handle, ppux_ڈھیر_بفر, ppx_Task_بفر );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    حرف * MPU_pcTaskGetName( TaskHandle_t x_Task_مقصد_Query ) /* PRIVILEGED_FUNCTION */
    {
        حرف * pcReturn = تہی;
        int32_t l_اشاریہ;
        TaskHandle_t x_اندرونی_Task_Handle = تہی;

        اگر( x_Task_مقصد_Query == تہی )
        {
            pcReturn = pcTaskGetName( x_Task_مقصد_Query );
        }
        ورنہ
        {
            l_اشاریہ = ( int32_t ) x_Task_مقصد_Query;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_Task_Handle != تہی )
                {
                    pcReturn = pcTaskGetName( x_اندرونی_Task_Handle );
                }
            }
        }

        واپس pcReturn;
    }
/*-----------------------------------------------------------*/

    #اگر ( INCLUDE_ux_Task_ترجیح_Get == 1 )

        UBaseType_t MPU_ux_Task_ترجیح_Get_From_ISR( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;

            اگر( xTask == تہی )
            {
                uxReturn = ux_Task_ترجیح_Get_From_ISR( xTask );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) xTask;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Task_Handle != تہی )
                    {
                        uxReturn = ux_Task_ترجیح_Get_From_ISR( x_اندرونی_Task_Handle );
                    }
                }
            }

            واپس uxReturn;
        }

    #اگر_ختم /* #if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( INCLUDE_ux_Task_ترجیح_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_بنیاد_ترجیح_Get( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;

            اگر( xTask == تہی )
            {
                uxReturn = ux_Task_بنیاد_ترجیح_Get( xTask );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) xTask;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Task_Handle != تہی )
                    {
                        uxReturn = ux_Task_بنیاد_ترجیح_Get( x_اندرونی_Task_Handle );
                    }
                }
            }

            واپس uxReturn;
        }

    #اگر_ختم /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( INCLUDE_ux_Task_ترجیح_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_بنیاد_ترجیح_Get_From_ISR( ثابت TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;

            اگر( xTask == تہی )
            {
                uxReturn = ux_Task_بنیاد_ترجیح_Get_From_ISR( xTask );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) xTask;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Task_Handle != تہی )
                    {
                        uxReturn = ux_Task_بنیاد_ترجیح_Get_From_ISR( x_اندرونی_Task_Handle );
                    }
                }
            }

            واپس uxReturn;
        }

    #اگر_ختم /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

        بنیاد_Type_t MPU_xTaskResumeFromISR( TaskHandle_t x_Task_مقصد_Resume ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;

            l_اشاریہ = ( int32_t ) x_Task_مقصد_Resume;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_Task_Handle != تہی )
                {
                    xReturn = xTaskResumeFromISR( x_اندرونی_Task_Handle );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )*/
/*---------------------------------------------------------------------------------------*/

    #اگر ( config_USE_APPLICATION_TASK_لیبل == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_لیبل_From_ISR( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = تہی;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;

            اگر( xTask == تہی )
            {
                xReturn = x_Task_Get_Application_Task_لیبل_From_ISR( xTask );
            }
            ورنہ
            {
                l_اشاریہ = ( int32_t ) xTask;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Task_Handle != تہی )
                    {
                        xReturn = x_Task_Get_Application_Task_لیبل_From_ISR( x_اندرونی_Task_Handle );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        بنیاد_Type_t MPU_xTaskGenericNotifyFromISR( TaskHandle_t x_Task_مقصد_Notify,
                                                  UBaseType_t ux_اشاریہ_مقصد_Notify,
                                                  uint32_t ul_قدر,
                                                  eNotifyAction eAction,
                                                  uint32_t * pul_پچھلا_Notification_قدر,
                                                  بنیاد_Type_t * px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;

            l_اشاریہ = ( int32_t ) x_Task_مقصد_Notify;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_Task_Handle != تہی )
                {
                    xReturn = xTaskGenericNotifyFromISR( x_اندرونی_Task_Handle, ux_اشاریہ_مقصد_Notify, ul_قدر, eAction, pul_پچھلا_Notification_قدر, px_Higher_ترجیح_Task_Woken );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )

        خالی MPU_vTaskGenericNotifyGiveFromISR( TaskHandle_t x_Task_مقصد_Notify,
                                                UBaseType_t ux_اشاریہ_مقصد_Notify,
                                                بنیاد_Type_t * px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            TaskHandle_t x_اندرونی_Task_Handle = تہی;

            l_اشاریہ = ( int32_t ) x_Task_مقصد_Notify;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Task_Handle = MPU_Get_Task_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_Task_Handle != تہی )
                {
                    vTaskGenericNotifyGiveFromISR( x_اندرونی_Task_Handle, ux_اشاریہ_مقصد_Notify, px_Higher_ترجیح_Task_Woken );
                }
            }
        }
    #اگر_ختم /*#if ( configUSE_TASK_NOTIFICATIONS == 1 )*/
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for queue APIs.                   */
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Generic_Send_Impl( قطار_Handle_t x_قطار,
                                          ثابت خالی * ثابت pv_شے_مقصد_قطار,
                                          TickType_t x_Ticks_مقصد_Wait,
                                          بنیاد_Type_t xCopyPosition ) PRIVILEGED_FUNCTION;

    بنیاد_Type_t MPU_x_قطار_Generic_Send_Impl( قطار_Handle_t x_قطار,
                                          ثابت خالی * ثابت pv_شے_مقصد_قطار,
                                          TickType_t x_Ticks_مقصد_Wait,
                                          بنیاد_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
        بنیاد_Type_t xReturn = pdFAIL;
        بنیاد_Type_t x_Is_شے_مقصد_قطار_Readable = pdFALSE;
        بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار = pdFALSE;
        UBaseType_t ux_قطار_شے_سائز, ux_قطار_لمبائی;

        l_اشاریہ = ( int32_t ) x_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_مقصد_Access_قطار = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_Calling_Task_Is_Authorized_مقصد_Access_قطار == pdTRUE )
            {
                x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_قطار_Handle != تہی )
                {
                    ux_قطار_شے_سائز = ux_قطار_Get_قطار_شے_سائز( x_اندرونی_قطار_Handle );
                    ux_قطار_لمبائی = ux_قطار_Get_قطار_لمبائی( x_اندرونی_قطار_Handle );

                    اگر( ( !( ( pv_شے_مقصد_قطار == تہی ) && ( ux_قطار_شے_سائز != ( UBaseType_t ) 0U ) ) ) &&
                        ( !( ( xCopyPosition == قطار_OVERWRITE ) && ( ux_قطار_لمبائی != ( UBaseType_t ) 1U ) ) )
                        #اگر ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_مقصد_Wait != 0U ) ) )
                        #اگر_ختم
                        )
                    {
                        اگر( pv_شے_مقصد_قطار != تہی )
                        {
                            x_Is_شے_مقصد_قطار_Readable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( pv_شے_مقصد_قطار,
                                                                                      ux_قطار_شے_سائز,
                                                                                      tskMPU_READ_PERMISSION );
                        }

                        اگر( ( pv_شے_مقصد_قطار == تہی ) || ( x_Is_شے_مقصد_قطار_Readable == pdTRUE ) )
                        {
                            xReturn = x_قطار_Generic_Send( x_اندرونی_قطار_Handle, pv_شے_مقصد_قطار, x_Ticks_مقصد_Wait, xCopyPosition );
                        }
                    }
                }
            }
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Messages_انتظار_Impl( ثابت قطار_Handle_t px_قطار ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_قطار_Messages_انتظار_Impl( ثابت قطار_Handle_t px_قطار ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
        UBaseType_t uxReturn = 0;
        بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار = pdFALSE;

        l_اشاریہ = ( int32_t ) px_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_مقصد_Access_قطار = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_Calling_Task_Is_Authorized_مقصد_Access_قطار == pdTRUE )
            {
                x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_قطار_Handle != تہی )
                {
                    uxReturn = ux_قطار_Messages_انتظار( x_اندرونی_قطار_Handle );
                }
            }
        }

        واپس uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Spaces_دستیاب_Impl( ثابت قطار_Handle_t x_قطار ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_قطار_Spaces_دستیاب_Impl( ثابت قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
        UBaseType_t uxReturn = 0;
        بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار = pdFALSE;

        l_اشاریہ = ( int32_t ) x_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_مقصد_Access_قطار = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_Calling_Task_Is_Authorized_مقصد_Access_قطار == pdTRUE )
            {
                x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_قطار_Handle != تہی )
                {
                    uxReturn = ux_قطار_Spaces_دستیاب( x_اندرونی_قطار_Handle );
                }
            }
        }

        واپس uxReturn;
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Receive_Impl( قطار_Handle_t px_قطار,
                                      خالی * ثابت pv_بفر,
                                      TickType_t x_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

    بنیاد_Type_t MPU_x_قطار_Receive_Impl( قطار_Handle_t px_قطار,
                                      خالی * ثابت pv_بفر,
                                      TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
        بنیاد_Type_t xReturn = pdFAIL;
        بنیاد_Type_t x_Is_Receive_بفر_Writable = pdFALSE;
        بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار = pdFALSE;
        UBaseType_t ux_قطار_شے_سائز;

        l_اشاریہ = ( int32_t ) px_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_مقصد_Access_قطار = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_Calling_Task_Is_Authorized_مقصد_Access_قطار == pdTRUE )
            {
                x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_قطار_Handle != تہی )
                {
                    ux_قطار_شے_سائز = ux_قطار_Get_قطار_شے_سائز( x_اندرونی_قطار_Handle );

                    اگر( ( !( ( ( pv_بفر ) == تہی ) && ( ux_قطار_شے_سائز != ( UBaseType_t ) 0U ) ) )
                        #اگر ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_مقصد_Wait != 0U ) ) )
                        #اگر_ختم
                        )
                    {
                        x_Is_Receive_بفر_Writable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( pv_بفر,
                                                                                    ux_قطار_شے_سائز,
                                                                                    tskMPU_WRITE_PERMISSION );

                        اگر( x_Is_Receive_بفر_Writable == pdTRUE )
                        {
                            xReturn = x_قطار_Receive( x_اندرونی_قطار_Handle, pv_بفر, x_Ticks_مقصد_Wait );
                        }
                    }
                }
            }
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Peek_Impl( قطار_Handle_t x_قطار,
                                   خالی * ثابت pv_بفر,
                                   TickType_t x_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

    بنیاد_Type_t MPU_x_قطار_Peek_Impl( قطار_Handle_t x_قطار,
                                   خالی * ثابت pv_بفر,
                                   TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
        بنیاد_Type_t xReturn = pdFAIL;
        بنیاد_Type_t x_Is_Receive_بفر_Writable = pdFALSE;
        UBaseType_t ux_قطار_شے_سائز;
        بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار = pdFALSE;

        l_اشاریہ = ( int32_t ) x_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_مقصد_Access_قطار = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_Calling_Task_Is_Authorized_مقصد_Access_قطار == pdTRUE )
            {
                x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_قطار_Handle != تہی )
                {
                    ux_قطار_شے_سائز = ux_قطار_Get_قطار_شے_سائز( x_اندرونی_قطار_Handle );

                    اگر( ( !( ( ( pv_بفر ) == تہی ) && ( ux_قطار_شے_سائز != ( UBaseType_t ) 0U ) ) )
                        #اگر ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_مقصد_Wait != 0U ) ) )
                        #اگر_ختم
                        )
                    {
                        x_Is_Receive_بفر_Writable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( pv_بفر,
                                                                                    ux_قطار_شے_سائز,
                                                                                    tskMPU_WRITE_PERMISSION );

                        اگر( x_Is_Receive_بفر_Writable == pdTRUE )
                        {
                            xReturn = x_قطار_Peek( x_اندرونی_قطار_Handle, pv_بفر, x_Ticks_مقصد_Wait );
                        }
                    }
                }
            }
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Semaphore_Take_Impl( قطار_Handle_t x_قطار,
                                            TickType_t x_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

    بنیاد_Type_t MPU_x_قطار_Semaphore_Take_Impl( قطار_Handle_t x_قطار,
                                            TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
        بنیاد_Type_t xReturn = pdFAIL;
        UBaseType_t ux_قطار_شے_سائز;
        بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار = pdFALSE;

        l_اشاریہ = ( int32_t ) x_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_مقصد_Access_قطار = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_Calling_Task_Is_Authorized_مقصد_Access_قطار == pdTRUE )
            {
                x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_قطار_Handle != تہی )
                {
                    ux_قطار_شے_سائز = ux_قطار_Get_قطار_شے_سائز( x_اندرونی_قطار_Handle );

                    اگر( ( ux_قطار_شے_سائز == 0U )
                        #اگر ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_مقصد_Wait != 0U ) ) )
                        #اگر_ختم
                        )
                    {
                        xReturn = x_قطار_Semaphore_Take( x_اندرونی_قطار_Handle, x_Ticks_مقصد_Wait );
                    }
                }
            }
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder_Impl( قطار_Handle_t xSemaphore ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder_Impl( قطار_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_اندرونی_Handle = تہی;
            TaskHandle_t xMutexHolderTaskExternalHandle = تہی;
            int32_t l_اشاریہ, l_Mutex_Holder_Task_اشاریہ;
            قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار = pdFALSE;


            l_اشاریہ = ( int32_t ) xSemaphore;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_قطار = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_قطار == pdTRUE )
                {
                    x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_قطار_Handle != تہی )
                    {
                        x_Mutex_Holder_Task_اندرونی_Handle = x_قطار_Get_Mutex_Holder( x_اندرونی_قطار_Handle );

                        اگر( x_Mutex_Holder_Task_اندرونی_Handle != تہی )
                        {
                            l_Mutex_Holder_Task_اشاریہ = MPU_Get_اشاریہ_For_Task_Handle( x_Mutex_Holder_Task_اندرونی_Handle );

                            اگر( l_Mutex_Holder_Task_اشاریہ != -1 )
                            {
                                xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_مقصد_EXTERNAL_اشاریہ( l_Mutex_Holder_Task_اشاریہ ) );
                            }
                        }
                    }
                }
            }

            واپس xMutexHolderTaskExternalHandle;
        }

    #اگر_ختم /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_RECURSIVE_MUTEXES == 1 )

        بنیاد_Type_t MPU_x_قطار_Take_Mutex_Recursive_Impl( قطار_Handle_t xMutex,
                                                     TickType_t x_بلاک_وقت ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_x_قطار_Take_Mutex_Recursive_Impl( قطار_Handle_t xMutex,
                                                     TickType_t x_بلاک_وقت ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار = pdFALSE;
            int32_t l_اشاریہ;
            قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
            UBaseType_t ux_قطار_شے_سائز;

            l_اشاریہ = ( int32_t ) xMutex;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_قطار = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_قطار == pdTRUE )
                {
                    x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_قطار_Handle != تہی )
                    {
                        ux_قطار_شے_سائز = ux_قطار_Get_قطار_شے_سائز( x_اندرونی_قطار_Handle );

                        اگر( ux_قطار_شے_سائز == 0 )
                        {
                            xReturn = x_قطار_Take_Mutex_Recursive( x_اندرونی_قطار_Handle, x_بلاک_وقت );
                        }
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_RECURSIVE_MUTEXES == 1 )

        بنیاد_Type_t MPU_x_قطار_Give_Mutex_Recursive_Impl( قطار_Handle_t xMutex ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_x_قطار_Give_Mutex_Recursive_Impl( قطار_Handle_t xMutex ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار = pdFALSE;
            int32_t l_اشاریہ;
            قطار_Handle_t x_اندرونی_قطار_Handle = تہی;

            l_اشاریہ = ( int32_t ) xMutex;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_قطار = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_قطار == pdTRUE )
                {
                    x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_قطار_Handle != تہی )
                    {
                        xReturn = x_قطار_Give_Mutex_Recursive( x_اندرونی_قطار_Handle );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_قطار_SETS == 1 )

        قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ_Impl( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                            TickType_t x_بلاک_وقت_Ticks ) PRIVILEGED_FUNCTION;

        قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ_Impl( قطار_سیٹ_Handle_t x_قطار_سیٹ,
                                                            TickType_t x_بلاک_وقت_Ticks ) /* PRIVILEGED_FUNCTION */
        {
            قطار_سیٹ_Handle_t x_اندرونی_قطار_سیٹ_Handle = تہی;
            قطار_سیٹ_Member_Handle_t x_Selected_Member_اندرونی = تہی;
            قطار_سیٹ_Member_Handle_t xSelectedMemberExternal = تہی;
            int32_t l_اشاریہ_قطار_سیٹ, l_اشاریہ_Selected_Member;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار_سیٹ = pdFALSE;

            l_اشاریہ_قطار_سیٹ = ( int32_t ) x_قطار_سیٹ;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ_قطار_سیٹ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_قطار_سیٹ = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_قطار_سیٹ == pdTRUE )
                {
                    x_اندرونی_قطار_سیٹ_Handle = MPU_Get_قطار_سیٹ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ ) );

                    اگر( x_اندرونی_قطار_سیٹ_Handle != تہی )
                    {
                        x_Selected_Member_اندرونی = x_قطار_Select_From_سیٹ( x_اندرونی_قطار_سیٹ_Handle, x_بلاک_وقت_Ticks );

                        اگر( x_Selected_Member_اندرونی != تہی )
                        {
                            l_اشاریہ_Selected_Member = MPU_Get_اشاریہ_For_قطار_سیٹ_Member_Handle( x_Selected_Member_اندرونی );

                            اگر( l_اشاریہ_Selected_Member != -1 )
                            {
                                xSelectedMemberExternal = ( قطار_سیٹ_Member_Handle_t ) ( CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ_Selected_Member ) );
                            }
                        }
                    }
                }
            }

            واپس xSelectedMemberExternal;
        }

    #اگر_ختم /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_قطار_SETS == 1 )

        بنیاد_Type_t MPU_x_قطار_جوڑو_مقصد_سیٹ_Impl( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                           قطار_سیٹ_Handle_t x_قطار_سیٹ ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_x_قطار_جوڑو_مقصد_سیٹ_Impl( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                           قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            قطار_سیٹ_Member_Handle_t x_اندرونی_قطار_سیٹ_Member_Handle = تہی;
            قطار_سیٹ_Handle_t x_اندرونی_قطار_سیٹ_Handle = تہی;
            int32_t l_اشاریہ_قطار_سیٹ, l_اشاریہ_قطار_سیٹ_Member;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار_سیٹ = pdFALSE;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار_سیٹ_Member = pdFALSE;

            l_اشاریہ_قطار_سیٹ = ( int32_t ) x_قطار_سیٹ;
            l_اشاریہ_قطار_سیٹ_Member = ( int32_t ) x_قطار_Or_Semaphore;

            اگر( ( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ_قطار_سیٹ ) != pdFALSE ) &&
                ( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ_قطار_سیٹ_Member ) != pdFALSE ) )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_قطار_سیٹ = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ ) );
                x_Calling_Task_Is_Authorized_مقصد_Access_قطار_سیٹ_Member = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ_Member ) );

                اگر( ( x_Calling_Task_Is_Authorized_مقصد_Access_قطار_سیٹ == pdTRUE ) && ( x_Calling_Task_Is_Authorized_مقصد_Access_قطار_سیٹ_Member == pdTRUE ) )
                {
                    x_اندرونی_قطار_سیٹ_Handle = MPU_Get_قطار_سیٹ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ ) );
                    x_اندرونی_قطار_سیٹ_Member_Handle = MPU_Get_قطار_سیٹ_Member_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ_Member ) );

                    اگر( ( x_اندرونی_قطار_سیٹ_Handle != تہی ) && ( x_اندرونی_قطار_سیٹ_Member_Handle != تہی ) )
                    {
                        xReturn = x_قطار_جوڑو_مقصد_سیٹ( x_اندرونی_قطار_سیٹ_Member_Handle, x_اندرونی_قطار_سیٹ_Handle );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر config_قطار_REGISTRY_سائز > 0

        خالی MPU_v_قطار_جوڑو_مقصد_Registry_Impl( قطار_Handle_t x_قطار,
                                          ثابت حرف * pcName ) PRIVILEGED_FUNCTION;

        خالی MPU_v_قطار_جوڑو_مقصد_Registry_Impl( قطار_Handle_t x_قطار,
                                          ثابت حرف * pcName ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار = pdFALSE;

            l_اشاریہ = ( int32_t ) x_قطار;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_قطار = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_قطار == pdTRUE )
                {
                    x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_قطار_Handle != تہی )
                    {
                        v_قطار_جوڑو_مقصد_Registry( x_اندرونی_قطار_Handle, pcName );
                    }
                }
            }
        }

    #اگر_ختم /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #اگر config_قطار_REGISTRY_سائز > 0

        خالی MPU_v_قطار_Unregister_قطار_Impl( قطار_Handle_t x_قطار ) PRIVILEGED_FUNCTION;

        خالی MPU_v_قطار_Unregister_قطار_Impl( قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار = pdFALSE;

            l_اشاریہ = ( int32_t ) x_قطار;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_قطار = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_قطار == pdTRUE )
                {
                    x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_قطار_Handle != تہی )
                    {
                        v_قطار_Unregister_قطار( x_اندرونی_قطار_Handle );
                    }
                }
            }
        }

    #اگر_ختم /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #اگر config_قطار_REGISTRY_سائز > 0

        ثابت حرف * MPU_pc_قطار_Get_Name_Impl( قطار_Handle_t x_قطار ) PRIVILEGED_FUNCTION;

        ثابت حرف * MPU_pc_قطار_Get_Name_Impl( قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
        {
            ثابت حرف * pcReturn = تہی;
            قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_قطار = pdFALSE;

            l_اشاریہ = ( int32_t ) x_قطار;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_قطار = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_قطار == pdTRUE )
                {
                    x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_قطار_Handle != تہی )
                    {
                        pcReturn = pc_قطار_Get_Name( x_اندرونی_قطار_Handle );
                    }
                }
            }

            واپس pcReturn;
        }

    #اگر_ختم /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Queue APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    خالی MPU_v_قطار_Delete( قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
        int32_t l_اشاریہ;

        l_اشاریہ = ( int32_t ) x_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_اندرونی_قطار_Handle != تہی )
            {
                v_قطار_Delete( x_اندرونی_قطار_Handle );
                MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );
            }
        }
    }
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Mutex( ثابت uint8_t uc_قطار_Type ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
            قطار_Handle_t x_External_قطار_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_Handle = x_قطار_Create_Mutex( uc_قطار_Type );

                اگر( x_اندرونی_قطار_Handle != تہی )
                {
                    MPU_Store_قطار_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس x_External_قطار_Handle;
        }

    #اگر_ختم /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_تخصیص == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Mutex_Static( ثابت uint8_t uc_قطار_Type,
                                                   Static_قطار_t * px_Static_قطار ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
            قطار_Handle_t x_External_قطار_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_Handle = x_قطار_Create_Mutex_Static( uc_قطار_Type, px_Static_قطار );

                اگر( x_اندرونی_قطار_Handle != تہی )
                {
                    MPU_Store_قطار_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس x_External_قطار_Handle;
        }

    #اگر_ختم /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Counting_Semaphore( UBaseType_t ux_گنتی_قدر,
                                                         UBaseType_t ux_Initial_گنتی ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
            قطار_Handle_t x_External_قطار_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_Handle = x_قطار_Create_Counting_Semaphore( ux_گنتی_قدر, ux_Initial_گنتی );

                اگر( x_اندرونی_قطار_Handle != تہی )
                {
                    MPU_Store_قطار_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس x_External_قطار_Handle;
        }

    #اگر_ختم /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_تخصیص == 1 ) )

        قطار_Handle_t MPU_x_قطار_Create_Counting_Semaphore_Static( ثابت UBaseType_t ux_Max_گنتی,
                                                               ثابت UBaseType_t ux_Initial_گنتی,
                                                               Static_قطار_t * px_Static_قطار ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
            قطار_Handle_t x_External_قطار_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_Handle = x_قطار_Create_Counting_Semaphore_Static( ux_Max_گنتی, ux_Initial_گنتی, px_Static_قطار );

                اگر( x_اندرونی_قطار_Handle != تہی )
                {
                    MPU_Store_قطار_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس x_External_قطار_Handle;
        }

    #اگر_ختم /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( config_SUPPORT_DYNAMIC_تخصیص == 1 )

        قطار_Handle_t MPU_x_قطار_Generic_Create( UBaseType_t ux_قطار_لمبائی,
                                               UBaseType_t ux_شے_سائز,
                                               uint8_t uc_قطار_Type ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
            قطار_Handle_t x_External_قطار_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_Handle = x_قطار_Generic_Create( ux_قطار_لمبائی, ux_شے_سائز, uc_قطار_Type );

                اگر( x_اندرونی_قطار_Handle != تہی )
                {
                    MPU_Store_قطار_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس x_External_قطار_Handle;
        }

    #اگر_ختم /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_SUPPORT_STATIC_تخصیص == 1 )

        قطار_Handle_t MPU_x_قطار_Generic_Create_Static( ثابت UBaseType_t ux_قطار_لمبائی,
                                                     ثابت UBaseType_t ux_شے_سائز,
                                                     uint8_t * puc_قطار_Storage,
                                                     Static_قطار_t * px_Static_قطار,
                                                     ثابت uint8_t uc_قطار_Type ) /* PRIVILEGED_FUNCTION */
        {
            قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
            قطار_Handle_t x_External_قطار_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_Handle = x_قطار_Generic_Create_Static( ux_قطار_لمبائی, ux_شے_سائز, puc_قطار_Storage, px_Static_قطار, uc_قطار_Type );

                اگر( x_اندرونی_قطار_Handle != تہی )
                {
                    MPU_Store_قطار_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_Handle );
                    x_External_قطار_Handle = ( قطار_Handle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس x_External_قطار_Handle;
        }

    #اگر_ختم /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Generic_Reset( قطار_Handle_t x_قطار,
                                       بنیاد_Type_t x_New_قطار ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
        بنیاد_Type_t xReturn = pdFAIL;

        l_اشاریہ = ( int32_t ) x_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_اندرونی_قطار_Handle != تہی )
            {
                xReturn = x_قطار_Generic_Reset( x_اندرونی_قطار_Handle, x_New_قطار );
            }
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    #اگر ( ( config_USE_قطار_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) )

        قطار_سیٹ_Handle_t MPU_x_قطار_Create_سیٹ( UBaseType_t ux_Event_قطار_لمبائی ) /* PRIVILEGED_FUNCTION */
        {
            قطار_سیٹ_Handle_t x_اندرونی_قطار_سیٹ_Handle = تہی;
            قطار_سیٹ_Handle_t x_External_قطار_سیٹ_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_سیٹ_Handle = x_قطار_Create_سیٹ( ux_Event_قطار_لمبائی );

                اگر( x_اندرونی_قطار_سیٹ_Handle != تہی )
                {
                    MPU_Store_قطار_سیٹ_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_سیٹ_Handle );
                    x_External_قطار_سیٹ_Handle = ( قطار_سیٹ_Handle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس x_External_قطار_سیٹ_Handle;
        }

    #اگر_ختم /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_USE_قطار_SETS == 1 ) && ( config_SUPPORT_STATIC_تخصیص == 1 ) )

        قطار_سیٹ_Handle_t MPU_x_قطار_Create_سیٹ_Static( ثابت UBaseType_t ux_Event_قطار_لمبائی,
                                                    uint8_t * puc_قطار_Storage,
                                                    Static_قطار_t * px_Static_قطار ) /* PRIVILEGED_FUNCTION */
        {
            قطار_سیٹ_Handle_t x_اندرونی_قطار_سیٹ_Handle = تہی;
            قطار_سیٹ_Handle_t x_External_قطار_سیٹ_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                x_اندرونی_قطار_سیٹ_Handle = x_قطار_Create_سیٹ_Static( ux_Event_قطار_لمبائی, puc_قطار_Storage, px_Static_قطار );

                اگر( x_اندرونی_قطار_سیٹ_Handle != تہی )
                {
                    MPU_Store_قطار_سیٹ_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_قطار_سیٹ_Handle );
                    x_External_قطار_سیٹ_Handle = ( قطار_سیٹ_Handle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس x_External_قطار_سیٹ_Handle;
        }

    #اگر_ختم /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_قطار_SETS == 1 )

        بنیاد_Type_t MPU_x_قطار_Remove_From_سیٹ( قطار_سیٹ_Member_Handle_t x_قطار_Or_Semaphore,
                                            قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            قطار_سیٹ_Member_Handle_t x_اندرونی_قطار_سیٹ_Member_Handle = تہی;
            قطار_سیٹ_Handle_t x_اندرونی_قطار_سیٹ_Handle = تہی;
            int32_t l_اشاریہ_قطار_سیٹ, l_اشاریہ_قطار_سیٹ_Member;

            l_اشاریہ_قطار_سیٹ = ( int32_t ) x_قطار_سیٹ;
            l_اشاریہ_قطار_سیٹ_Member = ( int32_t ) x_قطار_Or_Semaphore;

            اگر( ( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ_قطار_سیٹ ) != pdFALSE ) &&
                ( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ_قطار_سیٹ_Member ) != pdFALSE ) )
            {
                x_اندرونی_قطار_سیٹ_Handle = MPU_Get_قطار_سیٹ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ ) );
                x_اندرونی_قطار_سیٹ_Member_Handle = MPU_Get_قطار_سیٹ_Member_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ_Member ) );

                اگر( ( x_اندرونی_قطار_سیٹ_Handle != تہی ) && ( x_اندرونی_قطار_سیٹ_Member_Handle != تہی ) )
                {
                    xReturn = x_قطار_Remove_From_سیٹ( x_اندرونی_قطار_سیٹ_Member_Handle, x_اندرونی_قطار_سیٹ_Handle );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_SUPPORT_STATIC_تخصیص == 1 )

        بنیاد_Type_t MPU_x_قطار_Generic_Get_Static_Buffers( قطار_Handle_t x_قطار,
                                                      uint8_t ** ppuc_قطار_Storage,
                                                      Static_قطار_t ** ppx_Static_قطار ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_اشاریہ;
            قطار_Handle_t x_اندرونی_قطار_Handle = تہی;
            بنیاد_Type_t xReturn = pdFALSE;

            l_اشاریہ = ( int32_t ) x_قطار;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_قطار_Handle != تہی )
                {
                    xReturn = x_قطار_Generic_Get_Static_Buffers( x_اندرونی_قطار_Handle, ppuc_قطار_Storage, ppx_Static_قطار );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /*if ( configSUPPORT_STATIC_ALLOCATION == 1 )*/
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Generic_Send_From_ISR( قطار_Handle_t x_قطار,
                                             ثابت خالی * ثابت pv_شے_مقصد_قطار,
                                             بنیاد_Type_t * ثابت px_Higher_ترجیح_Task_Woken,
                                             ثابت بنیاد_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        بنیاد_Type_t xReturn = pdFAIL;
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;

        l_اشاریہ = ( int32_t ) x_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_اندرونی_قطار_Handle != تہی )
            {
                xReturn = x_قطار_Generic_Send_From_ISR( x_اندرونی_قطار_Handle, pv_شے_مقصد_قطار, px_Higher_ترجیح_Task_Woken, xCopyPosition );
            }
        }

        واپس xReturn;
    }

/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Give_From_ISR( قطار_Handle_t x_قطار,
                                      بنیاد_Type_t * ثابت px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        بنیاد_Type_t xReturn = pdFAIL;
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;

        l_اشاریہ = ( int32_t ) x_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_اندرونی_قطار_Handle != تہی )
            {
                xReturn = x_قطار_Give_From_ISR( x_اندرونی_قطار_Handle, px_Higher_ترجیح_Task_Woken );
            }
        }

        واپس xReturn;
    }

/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Peek_From_ISR( قطار_Handle_t x_قطار,
                                      خالی * ثابت pv_بفر ) /* PRIVILEGED_FUNCTION */
    {
        بنیاد_Type_t xReturn = pdFAIL;
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;

        l_اشاریہ = ( int32_t ) x_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_اندرونی_قطار_Handle != تہی )
            {
                xReturn = x_قطار_Peek_From_ISR( x_اندرونی_قطار_Handle, pv_بفر );
            }
        }

        واپس xReturn;
    }

/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Receive_From_ISR( قطار_Handle_t x_قطار,
                                         خالی * ثابت pv_بفر,
                                         بنیاد_Type_t * ثابت px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        بنیاد_Type_t xReturn = pdFAIL;
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;

        l_اشاریہ = ( int32_t ) x_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_اندرونی_قطار_Handle != تہی )
            {
                xReturn = x_قطار_Receive_From_ISR( x_اندرونی_قطار_Handle, pv_بفر, px_Higher_ترجیح_Task_Woken );
            }
        }

        واپس xReturn;
    }

/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Is_قطار_خالی_خانے_From_ISR( ثابت قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        بنیاد_Type_t xReturn = pdFAIL;
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;

        l_اشاریہ = ( int32_t ) x_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_اندرونی_قطار_Handle != تہی )
            {
                xReturn = x_قطار_Is_قطار_خالی_خانے_From_ISR( x_اندرونی_قطار_Handle );
            }
        }

        واپس xReturn;
    }
/*-----------------------------------------------------------*/

    بنیاد_Type_t MPU_x_قطار_Is_قطار_بھرا_From_ISR( ثابت قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        بنیاد_Type_t xReturn = pdFAIL;
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;

        l_اشاریہ = ( int32_t ) x_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_اندرونی_قطار_Handle != تہی )
            {
                xReturn = x_قطار_Is_قطار_بھرا_From_ISR( x_اندرونی_قطار_Handle );
            }
        }

        واپس xReturn;
    }

/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_قطار_Messages_انتظار_From_ISR( ثابت قطار_Handle_t x_قطار ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn = 0;
        int32_t l_اشاریہ;
        قطار_Handle_t x_اندرونی_قطار_Handle = تہی;

        l_اشاریہ = ( int32_t ) x_قطار;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_قطار_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_اندرونی_قطار_Handle != تہی )
            {
                uxReturn = ux_قطار_Messages_انتظار_From_ISR( x_اندرونی_قطار_Handle );
            }
        }

        واپس uxReturn;
    }

/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_قطار_Get_Mutex_Holder_From_ISR( قطار_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_اندرونی_Handle = تہی;
            TaskHandle_t xMutexHolderTaskExternalHandle = تہی;
            int32_t l_اشاریہ, l_Mutex_Holder_Task_اشاریہ;
            قطار_Handle_t x_اندرونی_Semaphore_Handle = تہی;

            l_اشاریہ = ( int32_t ) xSemaphore;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Semaphore_Handle = MPU_Get_قطار_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_Semaphore_Handle != تہی )
                {
                    x_Mutex_Holder_Task_اندرونی_Handle = x_قطار_Get_Mutex_Holder( x_اندرونی_Semaphore_Handle );

                    اگر( x_Mutex_Holder_Task_اندرونی_Handle != تہی )
                    {
                        l_Mutex_Holder_Task_اشاریہ = MPU_Get_اشاریہ_For_Task_Handle( x_Mutex_Holder_Task_اندرونی_Handle );

                        اگر( l_Mutex_Holder_Task_اشاریہ != -1 )
                        {
                            xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_مقصد_EXTERNAL_اشاریہ( l_Mutex_Holder_Task_اشاریہ ) );
                        }
                    }
                }
            }

            واپس xMutexHolderTaskExternalHandle;
        }

    #اگر_ختم /* #if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_قطار_SETS == 1 )

        قطار_سیٹ_Member_Handle_t MPU_x_قطار_Select_From_سیٹ_From_ISR( قطار_سیٹ_Handle_t x_قطار_سیٹ ) /* PRIVILEGED_FUNCTION */
        {
            قطار_سیٹ_Handle_t x_اندرونی_قطار_سیٹ_Handle = تہی;
            قطار_سیٹ_Member_Handle_t x_Selected_Member_اندرونی = تہی;
            قطار_سیٹ_Member_Handle_t xSelectedMemberExternal = تہی;
            int32_t l_اشاریہ_قطار_سیٹ, l_اشاریہ_Selected_Member;

            l_اشاریہ_قطار_سیٹ = ( int32_t ) x_قطار_سیٹ;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ_قطار_سیٹ ) != pdFALSE )
            {
                x_اندرونی_قطار_سیٹ_Handle = MPU_Get_قطار_سیٹ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ_قطار_سیٹ ) );

                اگر( x_اندرونی_قطار_سیٹ_Handle != تہی )
                {
                    x_Selected_Member_اندرونی = x_قطار_Select_From_سیٹ_From_ISR( x_اندرونی_قطار_سیٹ_Handle );

                    اگر( x_Selected_Member_اندرونی != تہی )
                    {
                        l_اشاریہ_Selected_Member = MPU_Get_اشاریہ_For_قطار_سیٹ_Member_Handle( x_Selected_Member_اندرونی );

                        اگر( l_اشاریہ_Selected_Member != -1 )
                        {
                            xSelectedMemberExternal = ( قطار_سیٹ_Member_Handle_t ) ( CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ_Selected_Member ) );
                        }
                    }
                }
            }

            واپس xSelectedMemberExternal;
        }

    #اگر_ختم /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for timers APIs.                  */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        خالی * MPU_pvTimerGetTimerIDImpl( ثابت TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        خالی * MPU_pvTimerGetTimerIDImpl( ثابت TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            خالی * pvReturn = تہی;
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Timer_Handle != تہی )
                    {
                        pvReturn = pvTimerGetTimerID( x_اندرونی_Timer_Handle );
                    }
                }
            }

            واپس pvReturn;
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        خالی MPU_v_Timer_سیٹ_Timer_IDImpl( TimerHandle_t xTimer,
                                       خالی * pvNewID ) PRIVILEGED_FUNCTION;

        خالی MPU_v_Timer_سیٹ_Timer_IDImpl( TimerHandle_t xTimer,
                                       خالی * pvNewID ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Timer_Handle != تہی )
                    {
                        v_Timer_سیٹ_Timer_ID( x_اندرونی_Timer_Handle, pvNewID );
                    }
                }
            }
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        بنیاد_Type_t MPU_x_Timer_Is_Timer_فعال_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_x_Timer_Is_Timer_فعال_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Timer_Handle != تہی )
                    {
                        xReturn = x_Timer_Is_Timer_فعال( x_اندرونی_Timer_Handle );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( خالی ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( خالی ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xReturn;

            xReturn = xTimerGetTimerDaemonTaskHandle();

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        بنیاد_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ثابت بنیاد_Type_t xCommandID,
                                                     ثابت TickType_t x_Optional_قدر,
                                                     بنیاد_Type_t * ثابت px_Higher_ترجیح_Task_Woken,
                                                     ثابت TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            xTimerGenericCommandFromTaskParams_t xParams;

            xParams.xTimer = xTimer;
            xParams.xCommandID = xCommandID;
            xParams.x_Optional_قدر = x_Optional_قدر;
            xParams.px_Higher_ترجیح_Task_Woken = px_Higher_ترجیح_Task_Woken;
            xParams.x_Ticks_مقصد_Wait = x_Ticks_مقصد_Wait;

            xReturn = MPU_x_Timer_Generic_Command_From_Task_اندراج( &( xParams ) );

            واپس xReturn;
        }

        بنیاد_Type_t MPU_xTimerGenericCommandFromTaskImpl( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_xTimerGenericCommandFromTaskImpl( ثابت xTimerGenericCommandFromTaskParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Is_Higher_ترجیح_Task_Woken_Writeable = pdFALSE;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;
            بنیاد_Type_t xAreParamsReadable = pdFALSE;

            اگر( pxParams != تہی )
            {
                xAreParamsReadable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( pxParams,
                                                                      حجم( xTimerGenericCommandFromTaskParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            اگر( xAreParamsReadable == pdTRUE )
            {
                اگر( pxParams->xCommandID < tmr_پہلا_FROM_ISR_COMMAND )
                {
                    اگر( pxParams->px_Higher_ترجیح_Task_Woken != تہی )
                    {
                        x_Is_Higher_ترجیح_Task_Woken_Writeable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( pxParams->px_Higher_ترجیح_Task_Woken,
                                                                                               حجم( بنیاد_Type_t ),
                                                                                               tskMPU_WRITE_PERMISSION );
                    }

                    اگر( ( pxParams->px_Higher_ترجیح_Task_Woken == تہی ) ||
                        ( x_Is_Higher_ترجیح_Task_Woken_Writeable == pdTRUE ) )
                    {
                        l_اشاریہ = ( int32_t ) ( pxParams->xTimer );

                        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                            اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                            {
                                x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                                اگر( x_اندرونی_Timer_Handle != تہی )
                                {
                                    xReturn = xTimerGenericCommandFromTask( x_اندرونی_Timer_Handle,
                                                                            pxParams->xCommandID,
                                                                            pxParams->x_Optional_قدر,
                                                                            pxParams->px_Higher_ترجیح_Task_Woken,
                                                                            pxParams->x_Ticks_مقصد_Wait );
                                }
                            }
                        }
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        ثابت حرف * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ثابت حرف * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ثابت حرف * pcReturn = تہی;
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Timer_Handle != تہی )
                    {
                        pcReturn = pcTimerGetName( x_اندرونی_Timer_Handle );
                    }
                }
            }

            واپس pcReturn;
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        خالی MPU_v_Timer_سیٹ_Reload_منوال_Impl( TimerHandle_t xTimer,
                                          ثابت بنیاد_Type_t xAutoReload ) PRIVILEGED_FUNCTION;

        خالی MPU_v_Timer_سیٹ_Reload_منوال_Impl( TimerHandle_t xTimer,
                                          ثابت بنیاد_Type_t xAutoReload ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Timer_Handle != تہی )
                    {
                        v_Timer_سیٹ_Reload_منوال( x_اندرونی_Timer_Handle, xAutoReload );
                    }
                }
            }
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        بنیاد_Type_t MPU_x_Timer_Get_Reload_منوال_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_x_Timer_Get_Reload_منوال_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Timer_Handle != تہی )
                    {
                        xReturn = x_Timer_Get_Reload_منوال( x_اندرونی_Timer_Handle );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_منوال_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Timer_Get_Reload_منوال_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Timer_Handle != تہی )
                    {
                        uxReturn = ux_Timer_Get_Reload_منوال( x_اندرونی_Timer_Handle );
                    }
                }
            }

            واپس uxReturn;
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Timer_Handle != تہی )
                    {
                        xReturn = xTimerGetPeriod( x_اندرونی_Timer_Handle );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_وقت_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_x_Timer_Get_Expiry_وقت_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Timer = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Timer = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Timer == pdTRUE )
                {
                    x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Timer_Handle != تہی )
                    {
                        xReturn = x_Timer_Get_Expiry_وقت( x_اندرونی_Timer_Handle );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Timer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #اگر ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreate( ثابت حرف * ثابت pcTimerName,
                                        ثابت TickType_t x_Timer_Period_اندر_Ticks,
                                        ثابت بنیاد_Type_t xAutoReload,
                                        خالی * ثابت pvTimerID,
                                        TimerCallbackFunction_t pxCallbackFunction ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            TimerHandle_t xExternalTimerHandle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                x_اندرونی_Timer_Handle = xTimerCreate( pcTimerName, x_Timer_Period_اندر_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback );

                اگر( x_اندرونی_Timer_Handle != تہی )
                {
                    MPU_Store_Timer_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس xExternalTimerHandle;
        }

    #اگر_ختم /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreateStatic( ثابت حرف * ثابت pcTimerName,
                                              ثابت TickType_t x_Timer_Period_اندر_Ticks,
                                              ثابت بنیاد_Type_t xAutoReload,
                                              خالی * ثابت pvTimerID,
                                              TimerCallbackFunction_t pxCallbackFunction,
                                              StaticTimer_t * px_Timer_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            TimerHandle_t xExternalTimerHandle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                x_اندرونی_Timer_Handle = xTimerCreateStatic( pcTimerName, x_Timer_Period_اندر_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback, px_Timer_بفر );

                اگر( x_اندرونی_Timer_Handle != تہی )
                {
                    MPU_Store_Timer_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس xExternalTimerHandle;
        }

    #اگر_ختم /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( configUSE_TIMERS == 1 )

        بنیاد_Type_t MPU_x_Timer_Get_Static_بفر( TimerHandle_t xTimer,
                                              StaticTimer_t ** ppx_Timer_بفر ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t xReturn = pdFALSE;

            l_اشاریہ = ( int32_t ) xTimer;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_Timer_Handle != تہی )
                {
                    xReturn = x_Timer_Get_Static_بفر( x_اندرونی_Timer_Handle, ppx_Timer_بفر );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        بنیاد_Type_t MPU_xTimerGenericCommandFromISR( TimerHandle_t xTimer,
                                                    ثابت بنیاد_Type_t xCommandID,
                                                    ثابت TickType_t x_Optional_قدر,
                                                    بنیاد_Type_t * ثابت px_Higher_ترجیح_Task_Woken,
                                                    ثابت TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) xTimer;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_Timer_Handle != تہی )
                {
                    xReturn = xTimerGenericCommandFromISR( x_اندرونی_Timer_Handle, xCommandID, x_Optional_قدر, px_Higher_ترجیح_Task_Woken, x_Ticks_مقصد_Wait );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_TIMERS == 1 )

        بنیاد_Type_t MPU_xTimerDelete( TimerHandle_t xTimer, TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            TimerHandle_t x_اندرونی_Timer_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) xTimer;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Timer_Handle = MPU_Get_Timer_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_Timer_Handle != تہی )
                {
                    xReturn = xTimerGenericCommandFromTask( x_اندرونی_Timer_Handle,
                                                            tmrCOMMAND_DELETE,
                                                            0U, /* xOptionalValue */
                                                            تہی, /* pxHigherPriorityTaskWoken */
                                                            x_Ticks_مقصد_Wait );
                    اگر( xReturn != pdFALSE )
                    {
                        MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for event group APIs.              */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ( Event_گروہ_Handle_t x_Event_گروہ,
                                             ثابت Event_بٹ_t ux_بٹ_مقصد_Wait_For,
                                             ثابت بنیاد_Type_t xClearOnExit,
                                             ثابت بنیاد_Type_t x_Wait_For_All_بٹ,
                                             TickType_t x_Ticks_مقصد_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_بٹ_t xReturn = 0;
            x_Event_گروہ_Wait_بٹ_Params_t xParams;

            xParams.x_Event_گروہ = x_Event_گروہ;
            xParams.ux_بٹ_مقصد_Wait_For = ux_بٹ_مقصد_Wait_For;
            xParams.xClearOnExit = xClearOnExit;
            xParams.x_Wait_For_All_بٹ = x_Wait_For_All_بٹ;
            xParams.x_Ticks_مقصد_Wait = x_Ticks_مقصد_Wait;

            xReturn = MPU_x_Event_گروہ_Wait_بٹ_اندراج( &( xParams ) );

            واپس xReturn;
        }

        Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ_Impl( ثابت x_Event_گروہ_Wait_بٹ_Params_t * pxParams ) PRIVILEGED_FUNCTION;

        Event_بٹ_t MPU_x_Event_گروہ_Wait_بٹ_Impl( ثابت x_Event_گروہ_Wait_بٹ_Params_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٹ_t xReturn = 0;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ = pdFALSE;
            بنیاد_Type_t xAreParamsReadable = pdFALSE;

            اگر( pxParams != تہی )
            {
                xAreParamsReadable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( pxParams,
                                                                      حجم( x_Event_گروہ_Wait_بٹ_Params_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            اگر( xAreParamsReadable == pdTRUE )
            {
                اگر( ( ( pxParams->ux_بٹ_مقصد_Wait_For & event_EVENT_بٹ_CONTROL_بائٹیں ) == 0U ) &&
                    ( pxParams->ux_بٹ_مقصد_Wait_For != 0U )
                    #اگر ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                        && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( pxParams->x_Ticks_مقصد_Wait != 0U ) ) )
                    #اگر_ختم
                    )
                {
                    l_اشاریہ = ( int32_t ) ( pxParams->x_Event_گروہ );

                    اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ == pdTRUE )
                        {
                            x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                            اگر( x_اندرونی_Event_گروہ_Handle != تہی )
                            {
                                xReturn = x_Event_گروہ_Wait_بٹ( x_اندرونی_Event_گروہ_Handle,
                                                               pxParams->ux_بٹ_مقصد_Wait_For,
                                                               pxParams->xClearOnExit,
                                                               pxParams->x_Wait_For_All_بٹ,
                                                               pxParams->x_Ticks_مقصد_Wait );
                            }
                        }
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ_Impl( Event_گروہ_Handle_t x_Event_گروہ,
                                                  ثابت Event_بٹ_t ux_بٹ_مقصد_Clear ) PRIVILEGED_FUNCTION;

        Event_بٹ_t MPU_x_Event_گروہ_Clear_بٹ_Impl( Event_گروہ_Handle_t x_Event_گروہ,
                                                  ثابت Event_بٹ_t ux_بٹ_مقصد_Clear ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٹ_t xReturn = 0;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ = pdFALSE;

            اگر( ( ux_بٹ_مقصد_Clear & event_EVENT_بٹ_CONTROL_بائٹیں ) == 0U )
            {
                l_اشاریہ = ( int32_t ) x_Event_گروہ;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ == pdTRUE )
                    {
                        x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_اندرونی_Event_گروہ_Handle != تہی )
                        {
                            xReturn = x_Event_گروہ_Clear_بٹ( x_اندرونی_Event_گروہ_Handle, ux_بٹ_مقصد_Clear );
                        }
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ_Impl( Event_گروہ_Handle_t x_Event_گروہ,
                                                ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ ) PRIVILEGED_FUNCTION;

        Event_بٹ_t MPU_x_Event_گروہ_سیٹ_بٹ_Impl( Event_گروہ_Handle_t x_Event_گروہ,
                                                ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٹ_t xReturn = 0;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ = pdFALSE;

            اگر( ( ux_بٹ_مقصد_سیٹ & event_EVENT_بٹ_CONTROL_بائٹیں ) == 0U )
            {
                l_اشاریہ = ( int32_t ) x_Event_گروہ;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ == pdTRUE )
                    {
                        x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_اندرونی_Event_گروہ_Handle != تہی )
                        {
                            xReturn = x_Event_گروہ_سیٹ_بٹ( x_اندرونی_Event_گروہ_Handle, ux_بٹ_مقصد_سیٹ );
                        }
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Sync_Impl( Event_گروہ_Handle_t x_Event_گروہ,
                                             ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ,
                                             ثابت Event_بٹ_t ux_بٹ_مقصد_Wait_For,
                                             TickType_t x_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

        Event_بٹ_t MPU_x_Event_گروہ_Sync_Impl( Event_گروہ_Handle_t x_Event_گروہ,
                                             ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ,
                                             ثابت Event_بٹ_t ux_بٹ_مقصد_Wait_For,
                                             TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٹ_t xReturn = 0;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ = pdFALSE;

            اگر( ( ( ux_بٹ_مقصد_Wait_For & event_EVENT_بٹ_CONTROL_بائٹیں ) == 0U ) &&
                ( ux_بٹ_مقصد_Wait_For != 0U )
                #اگر ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                    && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_مقصد_Wait != 0U ) ) )
                #اگر_ختم
                )
            {
                l_اشاریہ = ( int32_t ) x_Event_گروہ;

                اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ == pdTRUE )
                    {
                        x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_اندرونی_Event_گروہ_Handle != تہی )
                        {
                            xReturn = x_Event_گروہ_Sync( x_اندرونی_Event_گروہ_Handle, ux_بٹ_مقصد_سیٹ, ux_بٹ_مقصد_Wait_For, x_Ticks_مقصد_Wait );
                        }
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_گروہ_Get_نمبر_Impl( خالی * x_Event_گروہ ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Event_گروہ_Get_نمبر_Impl( خالی * x_Event_گروہ ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t xReturn = 0;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ = pdFALSE;

            l_اشاریہ = ( int32_t ) x_Event_گروہ;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ == pdTRUE )
                {
                    x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Event_گروہ_Handle != تہی )
                    {
                        xReturn = ux_Event_گروہ_Get_نمبر( x_اندرونی_Event_گروہ_Handle );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        خالی MPU_v_Event_گروہ_سیٹ_نمبر_Impl( خالی * x_Event_گروہ,
                                           UBaseType_t ux_Event_گروہ_نمبر ) PRIVILEGED_FUNCTION;

        خالی MPU_v_Event_گروہ_سیٹ_نمبر_Impl( خالی * x_Event_گروہ,
                                           UBaseType_t ux_Event_گروہ_نمبر ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ = pdFALSE;

            l_اشاریہ = ( int32_t ) x_Event_گروہ;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_Event_گروہ == pdTRUE )
                {
                    x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_Event_گروہ_Handle != تہی )
                    {
                        v_Event_گروہ_سیٹ_نمبر( x_اندرونی_Event_گروہ_Handle, ux_Event_گروہ_نمبر );
                    }
                }
            }
        }

    #اگر_ختم /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Event Group APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #اگر ( ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_گروہ_Handle_t MPU_x_Event_گروہ_Create( خالی ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = تہی;
            Event_گروہ_Handle_t x_External_Event_گروہ_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                x_اندرونی_Event_گروہ_Handle = x_Event_گروہ_Create();

                اگر( x_اندرونی_Event_گروہ_Handle != تہی )
                {
                    MPU_Store_Event_گروہ_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Event_گروہ_Handle );
                    x_External_Event_گروہ_Handle = ( Event_گروہ_Handle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس x_External_Event_گروہ_Handle;
        }

    #اگر_ختم /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_گروہ_Handle_t MPU_x_Event_گروہ_Create_Static( Static_Event_گروہ_t * px_Event_گروہ_بفر ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = تہی;
            Event_گروہ_Handle_t x_External_Event_گروہ_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

            اگر( l_اشاریہ != -1 )
            {
                x_اندرونی_Event_گروہ_Handle = x_Event_گروہ_Create_Static( px_Event_گروہ_بفر );

                اگر( x_اندرونی_Event_گروہ_Handle != تہی )
                {
                    MPU_Store_Event_گروہ_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_Event_گروہ_Handle );
                    x_External_Event_گروہ_Handle = ( Event_گروہ_Handle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                }
                ورنہ
                {
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                }
            }

            واپس x_External_Event_گروہ_Handle;
        }

    #اگر_ختم /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )

        خالی MPU_v_Event_گروہ_Delete( Event_گروہ_Handle_t x_Event_گروہ ) /* PRIVILEGED_FUNCTION */
        {
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_Event_گروہ;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_Event_گروہ_Handle != تہی )
                {
                    v_Event_گروہ_Delete( x_اندرونی_Event_گروہ_Handle );
                    MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );
                }
            }
        }

    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        بنیاد_Type_t MPU_x_Event_گروہ_Get_Static_بفر( Event_گروہ_Handle_t x_Event_گروہ,
                                                   Static_Event_گروہ_t ** ppx_Event_گروہ_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_Event_گروہ;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_Event_گروہ_Handle != تہی )
                {
                    xReturn = x_Event_گروہ_Get_Static_بفر( x_اندرونی_Event_گروہ_Handle, ppx_Event_گروہ_بفر );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        بنیاد_Type_t MPU_x_Event_گروہ_Clear_بٹ_From_ISR( Event_گروہ_Handle_t x_Event_گروہ,
                                                    ثابت Event_بٹ_t ux_بٹ_مقصد_Clear ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_Event_گروہ;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_Event_گروہ_Handle != تہی )
                {
                    xReturn = x_Event_گروہ_Clear_بٹ_From_ISR( x_اندرونی_Event_گروہ_Handle, ux_بٹ_مقصد_Clear );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        بنیاد_Type_t MPU_x_Event_گروہ_سیٹ_بٹ_From_ISR( Event_گروہ_Handle_t x_Event_گروہ,
                                                  ثابت Event_بٹ_t ux_بٹ_مقصد_سیٹ,
                                                  بنیاد_Type_t * px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_Event_گروہ;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_Event_گروہ_Handle != تہی )
                {
                    xReturn = x_Event_گروہ_سیٹ_بٹ_From_ISR( x_اندرونی_Event_گروہ_Handle, ux_بٹ_مقصد_سیٹ, px_Higher_ترجیح_Task_Woken );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( configUSE_EVENT_GROUPS == 1 )

        Event_بٹ_t MPU_x_Event_گروہ_Get_بٹ_From_ISR( Event_گروہ_Handle_t x_Event_گروہ ) /* PRIVILEGED_FUNCTION */
        {
            Event_بٹ_t xReturn = 0;
            Event_گروہ_Handle_t x_اندرونی_Event_گروہ_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_Event_گروہ;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_Event_گروہ_Handle = MPU_Get_Event_گروہ_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_Event_گروہ_Handle != تہی )
                {
                    xReturn = x_Event_گروہ_Get_بٹ_From_ISR( x_اندرونی_Event_گروہ_Handle );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for stream buffer APIs.            */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_Send_Impl( دھارا_بفر_Handle_t x_دھارا_بفر,
                                          ثابت خالی * pv_Tx_ڈیٹا,
                                          size_t x_ڈیٹا_لمبائی_بائٹیں,
                                          TickType_t x_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_دھارا_بفر_Send_Impl( دھارا_بفر_Handle_t x_دھارا_بفر,
                                          ثابت خالی * pv_Tx_ڈیٹا,
                                          size_t x_ڈیٹا_لمبائی_بائٹیں,
                                          TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Is_Tx_ڈیٹا_بفر_Readable = pdFALSE;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = pdFALSE;

            اگر( pv_Tx_ڈیٹا != تہی )
            {
                x_Is_Tx_ڈیٹا_بفر_Readable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( pv_Tx_ڈیٹا,
                                                                           x_ڈیٹا_لمبائی_بائٹیں,
                                                                           tskMPU_READ_PERMISSION );

                اگر( x_Is_Tx_ڈیٹا_بفر_Readable == pdTRUE )
                {
                    l_اشاریہ = ( int32_t ) x_دھارا_بفر;

                    اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر == pdTRUE )
                        {
                            x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                            اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                            {
                                xReturn = x_دھارا_بفر_Send( x_اندرونی_دھارا_بفر_Handle, pv_Tx_ڈیٹا, x_ڈیٹا_لمبائی_بائٹیں, x_Ticks_مقصد_Wait );
                            }
                        }
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_Receive_Impl( دھارا_بفر_Handle_t x_دھارا_بفر,
                                             خالی * pv_Rx_ڈیٹا,
                                             size_t x_بفر_لمبائی_بائٹیں,
                                             TickType_t x_Ticks_مقصد_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_دھارا_بفر_Receive_Impl( دھارا_بفر_Handle_t x_دھارا_بفر,
                                             خالی * pv_Rx_ڈیٹا,
                                             size_t x_بفر_لمبائی_بائٹیں,
                                             TickType_t x_Ticks_مقصد_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Is_Rx_ڈیٹا_بفر_Writeable = pdFALSE;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = pdFALSE;

            اگر( pv_Rx_ڈیٹا != تہی )
            {
                x_Is_Rx_ڈیٹا_بفر_Writeable = x_پورٹ_Is_Authorized_مقصد_Access_بفر( pv_Rx_ڈیٹا,
                                                                            x_بفر_لمبائی_بائٹیں,
                                                                            tskMPU_WRITE_PERMISSION );

                اگر( x_Is_Rx_ڈیٹا_بفر_Writeable == pdTRUE )
                {
                    l_اشاریہ = ( int32_t ) x_دھارا_بفر;

                    اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                        اگر( x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر == pdTRUE )
                        {
                            x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                            اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                            {
                                xReturn = x_دھارا_بفر_Receive( x_اندرونی_دھارا_بفر_Handle, pv_Rx_ڈیٹا, x_بفر_لمبائی_بائٹیں, x_Ticks_مقصد_Wait );
                            }
                        }
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        بنیاد_Type_t MPU_x_دھارا_بفر_Is_بھرا_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_x_دھارا_بفر_Is_بھرا_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = pdFALSE;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر == pdTRUE )
                {
                    x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                    {
                        xReturn = x_دھارا_بفر_Is_بھرا( x_اندرونی_دھارا_بفر_Handle );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        بنیاد_Type_t MPU_x_دھارا_بفر_Is_خالی_خانے_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_x_دھارا_بفر_Is_خالی_خانے_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = pdFALSE;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر == pdTRUE )
                {
                    x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                    {
                        xReturn = x_دھارا_بفر_Is_خالی_خانے( x_اندرونی_دھارا_بفر_Handle );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_Spaces_دستیاب_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_دھارا_بفر_Spaces_دستیاب_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = pdFALSE;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر == pdTRUE )
                {
                    x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                    {
                        xReturn = x_دھارا_بفر_Spaces_دستیاب( x_اندرونی_دھارا_بفر_Handle );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_بائٹیں_دستیاب_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_دھارا_بفر_بائٹیں_دستیاب_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = pdFALSE;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر == pdTRUE )
                {
                    x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                    {
                        xReturn = x_دھارا_بفر_بائٹیں_دستیاب( x_اندرونی_دھارا_بفر_Handle );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        بنیاد_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level_Impl( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                         size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

        بنیاد_Type_t MPU_x_دھارا_بفر_سیٹ_Trigger_Level_Impl( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                         size_t xTriggerLevel ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = pdFALSE;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر == pdTRUE )
                {
                    x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                    {
                        xReturn = x_دھارا_بفر_سیٹ_Trigger_Level( x_اندرونی_دھارا_بفر_Handle, xTriggerLevel );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        size_t MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) PRIVILEGED_FUNCTION;

        size_t MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں_Impl( دھارا_بفر_Handle_t x_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;
            بنیاد_Type_t x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = pdFALSE;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر = x_پورٹ_Is_Authorized_مقصد_Access_Kernel_Object( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_Calling_Task_Is_Authorized_مقصد_Access_دھارا_بفر == pdTRUE )
                {
                    x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                    اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                    {
                        xReturn = x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں( x_اندرونی_دھارا_بفر_Handle );
                    }
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Stream Buffer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #اگر ( ( config_SUPPORT_DYNAMIC_تخصیص == 1 ) && ( config_USE_دھارا_BUFFERS == 1 ) )

        دھارا_بفر_Handle_t MPU_x_دھارا_بفر_Generic_Create( size_t x_بفر_سائز_بائٹیں,
                                                             size_t x_Trigger_Level_بائٹیں,
                                                             بنیاد_Type_t x_دھارا_بفر_Type,
                                                             دھارا_بفر_Callback_Function_t pxSendCompletedCallback,
                                                             دھارا_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            دھارا_بفر_Handle_t x_External_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == تہی ) &&
                          ( pxReceiveCompletedCallback == تہی ) );

            اگر( ( pxSendCompletedCallback == تہی ) &&
                ( pxReceiveCompletedCallback == تہی ) )
            {
                l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

                اگر( l_اشاریہ != -1 )
                {
                    x_اندرونی_دھارا_بفر_Handle = x_دھارا_بفر_Generic_Create( x_بفر_سائز_بائٹیں,
                                                                              x_Trigger_Level_بائٹیں,
                                                                              x_دھارا_بفر_Type,
                                                                              تہی,
                                                                              تہی );

                    اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                    {
                        MPU_Store_دھارا_بفر_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_دھارا_بفر_Handle );
                        x_External_دھارا_بفر_Handle = ( دھارا_بفر_Handle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                    }
                    ورنہ
                    {
                        MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                    }
                }
            }
            ورنہ
            {
                trace_دھارا_بفر_CREATE_FAILED( x_دھارا_بفر_Type );
                x_External_دھارا_بفر_Handle = تہی;
            }

            واپس x_External_دھارا_بفر_Handle;
        }

    #اگر_ختم /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( config_USE_دھارا_BUFFERS == 1 ) )

        دھارا_بفر_Handle_t MPU_x_دھارا_بفر_Generic_Create_Static( size_t x_بفر_سائز_بائٹیں,
                                                                   size_t x_Trigger_Level_بائٹیں,
                                                                   بنیاد_Type_t x_دھارا_بفر_Type,
                                                                   uint8_t * ثابت puc_دھارا_بفر_Storage_Area,
                                                                   Static_دھارا_بفر_t * ثابت px_Static_دھارا_بفر,
                                                                   دھارا_بفر_Callback_Function_t pxSendCompletedCallback,
                                                                   دھارا_بفر_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            دھارا_بفر_Handle_t x_External_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == تہی ) &&
                          ( pxReceiveCompletedCallback == تہی ) );

            اگر( ( pxSendCompletedCallback == تہی ) &&
                ( pxReceiveCompletedCallback == تہی ) )
            {
                l_اشاریہ = MPU_Get_Free_اشاریہ_اندر_Kernel_Object_Pool();

                اگر( l_اشاریہ != -1 )
                {
                    x_اندرونی_دھارا_بفر_Handle = x_دھارا_بفر_Generic_Create_Static( x_بفر_سائز_بائٹیں,
                                                                                    x_Trigger_Level_بائٹیں,
                                                                                    x_دھارا_بفر_Type,
                                                                                    puc_دھارا_بفر_Storage_Area,
                                                                                    px_Static_دھارا_بفر,
                                                                                    تہی,
                                                                                    تہی );

                    اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                    {
                        MPU_Store_دھارا_بفر_Handle_At_اشاریہ( l_اشاریہ, x_اندرونی_دھارا_بفر_Handle );
                        x_External_دھارا_بفر_Handle = ( دھارا_بفر_Handle_t ) CONVERT_مقصد_EXTERNAL_اشاریہ( l_اشاریہ );
                    }
                    ورنہ
                    {
                        MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( l_اشاریہ );
                    }
                }
            }
            ورنہ
            {
                trace_دھارا_بفر_CREATE_STATIC_FAILED( xReturn, x_دھارا_بفر_Type );
                x_External_دھارا_بفر_Handle = تہی;
            }

            واپس x_External_دھارا_بفر_Handle;
        }

    #اگر_ختم /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        خالی MPU_v_دھارا_بفر_Delete( دھارا_بفر_Handle_t x_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                {
                    v_دھارا_بفر_Delete( x_اندرونی_دھارا_بفر_Handle );
                }

                MPU_سیٹ_اشاریہ_Free_اندر_Kernel_Object_Pool( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );
            }
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        بنیاد_Type_t MPU_x_دھارا_بفر_Reset( دھارا_بفر_Handle_t x_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                {
                    xReturn = x_دھارا_بفر_Reset( x_اندرونی_دھارا_بفر_Handle );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( ( config_SUPPORT_STATIC_تخصیص == 1 ) && ( config_USE_دھارا_BUFFERS == 1 ) )

        بنیاد_Type_t MPU_x_دھارا_بفر_Get_Static_Buffers( دھارا_بفر_Handle_t x_دھارا_Buffers,
                                                      uint8_t * ppuc_دھارا_بفر_Storage_Area,
                                                      Static_دھارا_بفر_t * ppx_Static_دھارا_بفر ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_دھارا_Buffers;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                {
                    xReturn = MPU_x_دھارا_بفر_Get_Static_Buffers( x_اندرونی_دھارا_بفر_Handle, ppuc_دھارا_بفر_Storage_Area, ppx_Static_دھارا_بفر );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

    size_t MPU_x_دھارا_بفر_Send_From_ISR( دھارا_بفر_Handle_t x_دھارا_بفر,
                                         ثابت خالی * pv_Tx_ڈیٹا,
                                         size_t x_ڈیٹا_لمبائی_بائٹیں,
                                         بنیاد_Type_t * ثابت px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
        int32_t l_اشاریہ;

        l_اشاریہ = ( int32_t ) x_دھارا_بفر;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
            {
                xReturn = x_دھارا_بفر_Send_From_ISR( x_اندرونی_دھارا_بفر_Handle, pv_Tx_ڈیٹا, x_ڈیٹا_لمبائی_بائٹیں, px_Higher_ترجیح_Task_Woken );
            }
        }

        واپس xReturn;
    }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

    size_t MPU_x_دھارا_بفر_Receive_From_ISR( دھارا_بفر_Handle_t x_دھارا_بفر,
                                            خالی * pv_Rx_ڈیٹا,
                                            size_t x_بفر_لمبائی_بائٹیں,
                                            بنیاد_Type_t * ثابت px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
        int32_t l_اشاریہ;

        l_اشاریہ = ( int32_t ) x_دھارا_بفر;

        اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
        {
            x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

            اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
            {
                xReturn = x_دھارا_بفر_Receive_From_ISR( x_اندرونی_دھارا_بفر_Handle, pv_Rx_ڈیٹا, x_بفر_لمبائی_بائٹیں, px_Higher_ترجیح_Task_Woken );
            }
        }

        واپس xReturn;
    }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        بنیاد_Type_t MPU_x_دھارا_بفر_Send_Completed_From_ISR( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                          بنیاد_Type_t * px_Higher_ترجیح_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                {
                    xReturn = x_دھارا_بفر_Send_Completed_From_ISR( x_اندرونی_دھارا_بفر_Handle, px_Higher_ترجیح_Task_Woken );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        بنیاد_Type_t MPU_x_دھارا_بفر_Receive_Completed_From_ISR( دھارا_بفر_Handle_t x_دھارا_بفر,
                                                             بنیاد_Type_t * px_Higher_ترجیح_Task_Woken ) /*PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFALSE;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                {
                    xReturn = x_دھارا_بفر_Receive_Completed_From_ISR( x_اندرونی_دھارا_بفر_Handle, px_Higher_ترجیح_Task_Woken );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

    #اگر ( config_USE_دھارا_BUFFERS == 1 )

        بنیاد_Type_t MPU_x_دھارا_بفر_Reset_From_ISR( دھارا_بفر_Handle_t x_دھارا_بفر ) /*PRIVILEGED_FUNCTION */
        {
            بنیاد_Type_t xReturn = pdFAIL;
            دھارا_بفر_Handle_t x_اندرونی_دھارا_بفر_Handle = تہی;
            int32_t l_اشاریہ;

            l_اشاریہ = ( int32_t ) x_دھارا_بفر;

            اگر( IS_EXTERNAL_اشاریہ_VALID( l_اشاریہ ) != pdFALSE )
            {
                x_اندرونی_دھارا_بفر_Handle = MPU_Get_دھارا_بفر_Handle_At_اشاریہ( CONVERT_مقصد_اندرونی_اشاریہ( l_اشاریہ ) );

                اگر( x_اندرونی_دھارا_بفر_Handle != تہی )
                {
                    xReturn = x_دھارا_بفر_Reset_From_ISR( x_اندرونی_دھارا_بفر_Handle );
                }
            }

            واپس xReturn;
        }

    #اگر_ختم /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h. */

    #اگر configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #شامل "application_defined_privileged_functions.h"
    #اگر_ختم
/*-----------------------------------------------------------*/

/**
 * @brief Array of system call implementation functions.
 *
 * The index in the array MUST match the corresponding system call number
 * defined in mpu_wrappers.h.
 */
    PRIVILEGED_ڈیٹا UBaseType_t uxSystemCallImplementations[ عدد_SYSTEM_CALLS ] =
    {
        #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_xTaskGenericNotifyImpl,                     /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyWaitImpl,                 /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #اگر_ختم

        #اگر ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_xTimerGenericCommandFromTaskImpl,           /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #اگر_ختم

        #اگر ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_گروہ_Wait_بٹ_Impl,                    /* SYSTEM_CALL_xEventGroupWaitBits. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupWaitBits. */
        #اگر_ختم

        /* The system calls above this line take 5 parameters. */

        #اگر ( INCLUDE_xTaskDelayUntil == 1 )
            ( UBaseType_t ) MPU_xTaskDelayUntilImpl,                        /* SYSTEM_CALL_xTaskDelayUntil. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskDelayUntil. */
        #اگر_ختم

        #اگر ( INCLUDE_xTaskAbortDelay == 1 )
            ( UBaseType_t ) MPU_xTaskAbortDelayImpl,                        /* SYSTEM_CALL_xTaskAbortDelay. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskAbortDelay. */
        #اگر_ختم

        #اگر ( INCLUDE_vTaskDelay == 1 )
            ( UBaseType_t ) MPU_vTaskDelayImpl,                             /* SYSTEM_CALL_vTaskDelay. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskDelay. */
        #اگر_ختم

        #اگر ( INCLUDE_ux_Task_ترجیح_Get == 1 )
            ( UBaseType_t ) MPU_ux_Task_ترجیح_Get_Impl,                      /* SYSTEM_CALL_uxTaskPriorityGet. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskPriorityGet. */
        #اگر_ختم

        #اگر ( INCLUDE_eTaskGetState == 1 )
            ( UBaseType_t ) MPU_eTaskGetStateImpl,                          /* SYSTEM_CALL_eTaskGetState. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_eTaskGetState. */
        #اگر_ختم

        #اگر ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_vTaskGetInfoImpl,                           /* SYSTEM_CALL_vTaskGetInfo. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskGetInfo. */
        #اگر_ختم

        #اگر ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
            ( UBaseType_t ) MPU_xTaskGetIdleTaskHandleImpl,                 /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #اگر_ختم

        #اگر ( INCLUDE_vTaskSuspend == 1 )
            ( UBaseType_t ) MPU_vTaskSuspendImpl,                           /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) MPU_vTaskResumeImpl,                            /* SYSTEM_CALL_vTaskResume. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskResume. */
        #اگر_ختم

        ( UBaseType_t ) MPU_x_Task_Get_Tick_گنتی_Impl,                          /* SYSTEM_CALL_xTaskGetTickCount. */
        ( UBaseType_t ) MPU_ux_Task_Get_نمبر_کا_Tasks_Impl,                     /* SYSTEM_CALL_uxTaskGetNumberOfTasks. */

        #اگر ( config_GENERATE_تسلسل_وقت_STATS == 1 )
            ( UBaseType_t ) MPU_ul_Task_Get_تسلسل_وقت_شمار_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) MPU_ul_Task_Get_تسلسل_وقت_Percent_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #اگر_ختم

        #اگر ( ( config_GENERATE_تسلسل_وقت_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_تسلسل_وقت_Percent_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_تسلسل_وقت_شمار_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #اگر_ختم

        #اگر ( config_USE_APPLICATION_TASK_لیبل == 1 )
            ( UBaseType_t ) MPU_v_Task_سیٹ_Application_Task_لیبل_Impl,             /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) MPU_x_Task_Get_Application_Task_لیبل_Impl,             /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #اگر_ختم

        #اگر ( config_عدد_THREAD_LOCAL_STORAGE_اشارے != 0 )
            ( UBaseType_t ) MPU_v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر_Impl,      /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) MPU_pv_Task_Get_Thread_Local_Storage_اشارہ_گر_Impl,     /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #اگر_ختم

        #اگر ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_uxTaskGetSystemStateImpl,                   /* SYSTEM_CALL_uxTaskGetSystemState. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetSystemState. */
        #اگر_ختم

        #اگر ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark_Impl,            /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #اگر_ختم

        #اگر ( INCLUDE_ux_Task_Get_ڈھیر_بلند_Water_Mark2 == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ڈھیر_بلند_Water_Mark2_Impl,           /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #اگر_ختم

        #اگر ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )
            ( UBaseType_t ) MPU_xTaskGetCurrentTaskHandleImpl,              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #اگر_ختم

        #اگر ( INCLUDE_xTaskGetSchedulerState == 1 )
            ( UBaseType_t ) MPU_xTaskGetSchedulerStateImpl,                 /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #اگر_ختم

        ( UBaseType_t ) MPU_v_Task_سیٹ_وقت_برآمد_State_Impl,                       /* SYSTEM_CALL_vTaskSetTimeOutState. */
        ( UBaseType_t ) MPU_x_Task_Check_For_وقت_برآمد_Impl,                       /* SYSTEM_CALL_xTaskCheckForTimeOut. */

        #اگر ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_ulTaskGenericNotifyTakeImpl,                /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyStateClearImpl,           /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) MPU_ul_Task_Generic_Notify_قدر_Clear_Impl,          /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #اگر_ختم

        ( UBaseType_t ) MPU_x_قطار_Generic_Send_Impl,                          /* SYSTEM_CALL_xQueueGenericSend. */
        ( UBaseType_t ) MPU_ux_قطار_Messages_انتظار_Impl,                     /* SYSTEM_CALL_uxQueueMessagesWaiting. */
        ( UBaseType_t ) MPU_ux_قطار_Spaces_دستیاب_Impl,                     /* SYSTEM_CALL_uxQueueSpacesAvailable. */
        ( UBaseType_t ) MPU_x_قطار_Receive_Impl,                              /* SYSTEM_CALL_xQueueReceive. */
        ( UBaseType_t ) MPU_x_قطار_Peek_Impl,                                 /* SYSTEM_CALL_xQueuePeek. */
        ( UBaseType_t ) MPU_x_قطار_Semaphore_Take_Impl,                        /* SYSTEM_CALL_xQueueSemaphoreTake. */

        #اگر ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
            ( UBaseType_t ) MPU_x_قطار_Get_Mutex_Holder_Impl,                   /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #اگر_ختم

        #اگر ( configUSE_RECURSIVE_MUTEXES == 1 )
            ( UBaseType_t ) MPU_x_قطار_Take_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) MPU_x_قطار_Give_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #اگر_ختم

        #اگر ( config_USE_قطار_SETS == 1 )
            ( UBaseType_t ) MPU_x_قطار_Select_From_سیٹ_Impl,                    /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) MPU_x_قطار_جوڑو_مقصد_سیٹ_Impl,                         /* SYSTEM_CALL_xQueueAddToSet. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueAddToSet. */
        #اگر_ختم

        #اگر config_قطار_REGISTRY_سائز > 0
            ( UBaseType_t ) MPU_v_قطار_جوڑو_مقصد_Registry_Impl,                    /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) MPU_v_قطار_Unregister_قطار_Impl,                  /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) MPU_pc_قطار_Get_Name_Impl,                         /* SYSTEM_CALL_pcQueueGetName. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcQueueGetName. */
        #اگر_ختم

        #اگر ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_pvTimerGetTimerIDImpl,                      /* SYSTEM_CALL_pvTimerGetTimerID. */
            ( UBaseType_t ) MPU_v_Timer_سیٹ_Timer_IDImpl,                       /* SYSTEM_CALL_vTimerSetTimerID. */
            ( UBaseType_t ) MPU_x_Timer_Is_Timer_فعال_Impl,                    /* SYSTEM_CALL_xTimerIsTimerActive. */
            ( UBaseType_t ) MPU_xTimerGetTimerDaemonTaskHandleImpl,         /* SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle. */
            ( UBaseType_t ) MPU_pcTimerGetNameImpl,                         /* SYSTEM_CALL_pcTimerGetName. */
            ( UBaseType_t ) MPU_v_Timer_سیٹ_Reload_منوال_Impl,                    /* SYSTEM_CALL_vTimerSetReloadMode. */
            ( UBaseType_t ) MPU_x_Timer_Get_Reload_منوال_Impl,                    /* SYSTEM_CALL_xTimerGetReloadMode. */
            ( UBaseType_t ) MPU_ux_Timer_Get_Reload_منوال_Impl,                   /* SYSTEM_CALL_uxTimerGetReloadMode. */
            ( UBaseType_t ) MPU_xTimerGetPeriodImpl,                        /* SYSTEM_CALL_xTimerGetPeriod. */
            ( UBaseType_t ) MPU_x_Timer_Get_Expiry_وقت_Impl,                    /* SYSTEM_CALL_xTimerGetExpiryTime. */
        #ورنہ
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
        #اگر_ختم

        #اگر ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_گروہ_Clear_بٹ_Impl,                   /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) MPU_x_Event_گروہ_سیٹ_بٹ_Impl,                     /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) MPU_x_Event_گروہ_Sync_Impl,                        /* SYSTEM_CALL_xEventGroupSync. */

            #اگر ( configUSE_TRACE_FACILITY == 1 )
                ( UBaseType_t ) MPU_ux_Event_گروہ_Get_نمبر_Impl,              /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) MPU_v_Event_گروہ_سیٹ_نمبر_Impl,               /* SYSTEM_CALL_vEventGroupSetNumber. */
            #ورنہ
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_vEventGroupSetNumber. */
            #اگر_ختم
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSync. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxEventGroupGetNumber. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vEventGroupSetNumber. */
        #اگر_ختم

        #اگر ( config_USE_دھارا_BUFFERS == 1 )
            ( UBaseType_t ) MPU_x_دھارا_بفر_Send_Impl,                      /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) MPU_x_دھارا_بفر_Receive_Impl,                   /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) MPU_x_دھارا_بفر_Is_بھرا_Impl,                    /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) MPU_x_دھارا_بفر_Is_خالی_خانے_Impl,                   /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) MPU_x_دھارا_بفر_Spaces_دستیاب_Impl,           /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) MPU_x_دھارا_بفر_بائٹیں_دستیاب_Impl,            /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) MPU_x_دھارا_بفر_سیٹ_Trigger_Level_Impl,           /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) MPU_x_دھارا_بفر_اگلا_پیغام_لمبائی_بائٹیں_Impl     /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #ورنہ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #اگر_ختم

    };
/*-----------------------------------------------------------*/

#اگر_ختم /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/
