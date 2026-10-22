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
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "queue.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "timers.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "event_groups.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stream_buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mpu_prototypes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mpu_syscall_numbers.h"

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#ਜੇ ( ( ਪੋਰਟ_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_PROTECTED_KERNEL_OBJECT_POOL_ਮਾਪ
        #ਗਲਤੀ config_PROTECTED_KERNEL_OBJECT_POOL_ਮਾਪ must be defined ਮੰਜ਼ਿਲ ਵੱਧ_ਤੋਂ_ਵੱਧ ਸੰਖਿਆ ਦਾ kernel objects ਵਿੱਚ_2 the application.
    #ਜੇ_ਅੰਤ

/**
 * @brief Offset added to the index before returning to the user.
 *
 * If the actual handle is stored at index i, ( i + INDEX_OFFSET )
 * is returned to the user.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸੂਚਕਾਂਕ_ਵਿੱਥ    1

/**
 * @brief Opaque type for a kernel object.
 */
    ਬਣਤਰ OpaqueObject;
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ OpaqueObject * OpaqueObjectHandle_t;

/**
 * @brief Defines kernel object in the kernel object pool.
 */
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ KernelObject
    {
        OpaqueObjectHandle_t x_ਅੰਦਰੂਨੀ_Object_Handle;
        uint32_t ulKernelObjectType;
        ਖਾਲੀ * pv_Kernel_Object_ਅੰਕੜੇ;
    } KernelObject_t;

/**
 * @brief Kernel object types.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KERNEL_OBJECT_TYPE_INVALID          ( 0UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KERNEL_OBJECT_TYPE_ਕਤਾਰ            ( 1UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KERNEL_OBJECT_TYPE_TASK             ( 2UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KERNEL_OBJECT_TYPE_ਧਾਰਾ_ਬਫਰ    ( 3UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KERNEL_OBJECT_TYPE_EVENT_ਸਮੂਹ      ( 4UL )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KERNEL_OBJECT_TYPE_TIMER            ( 5UL )

/**
 * @brief Checks whether an external index is valid or not.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ )   \
    ( ( ( ( l_ਸੂਚਕਾਂਕ ) >= ਸੂਚਕਾਂਕ_ਵਿੱਥ ) &&       \
        ( ( l_ਸੂਚਕਾਂਕ ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_ਮਾਪ + ਸੂਚਕਾਂਕ_ਵਿੱਥ ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Checks whether an internal index is valid or not.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IS_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ )   \
    ( ( ( ( l_ਸੂਚਕਾਂਕ ) >= 0 ) &&                  \
        ( ( l_ਸੂਚਕਾਂਕ ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_ਮਾਪ ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Converts an internal index into external.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ )    ( ( l_ਸੂਚਕਾਂਕ ) + ਸੂਚਕਾਂਕ_ਵਿੱਥ )

/**
 * @brief Converts an external index into internal.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ )    ( ( l_ਸੂਚਕਾਂਕ ) - ਸੂਚਕਾਂਕ_ਵਿੱਥ )

/**
 * @brief Max value that fits in a UBaseType_t type.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ mpuUBASETYPE_MAX    ( ~( ( UBaseType_t ) 0 ) )

/**
 * @brief Check if multiplying a and b will result in overflow.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ mpu_MULTIPLY_BASETYPE_WILL_ਉਛਾਲ( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( mpuUBASETYPE_MAX / ( a ) ) ) )

/**
 * @brief Get the index of a free slot in the kernel object pool.
 *
 * If a free slot is found, this function marks the slot as
 * "not free".
 *
 * @return Index of a free slot is returned, if a free slot is
 *         found. Otherwise -1 is returned.
 */
    ਸਥਿਰ int32_t MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/**
 * @brief Set the given index as free in the kernel object pool.
 *
 * @param lIndex The index to set as free.
 */
    ਸਥਿਰ ਖਾਲੀ MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( int32_t l_ਸੂਚਕਾਂਕ ) PRIVILEGED_FUNCTION;

/**
 * @brief Get the index at which a given kernel object is stored.
 *
 * @param xHandle The given kernel object handle.
 * @param ulKernelObjectType The kernel object type.
 *
 * @return Index at which the kernel object is stored if it is a valid
 *         handle, -1 otherwise.
 */
    ਸਥਿਰ int32_t MPU_Get_ਸੂਚਕਾਂਕ_For_Handle( OpaqueObjectHandle_t xHandle,
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
    ਸਥਿਰ ਖਾਲੀ MPU_Store_Handle_And_ਅੰਕੜੇ_At_ਸੂਚਕਾਂਕ( int32_t l_ਸੂਚਕਾਂਕ,
                                               OpaqueObjectHandle_t xHandle,
                                               ਖਾਲੀ * pv_Kernel_Object_ਅੰਕੜੇ,
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
    ਸਥਿਰ OpaqueObjectHandle_t MPU_Get_Handle_At_ਸੂਚਕਾਂਕ( int32_t l_ਸੂਚਕਾਂਕ,
                                                      uint32_t ulKernelObjectType ) PRIVILEGED_FUNCTION;

    #ਜੇ ( configUSE_TIMERS == 1 )

/**
 * @brief The function registered as callback for all the timers.
 *
 * We intercept all the timer callbacks so that we can call application
 * callbacks with opaque handle.
 *
 * @param xInternalHandle The internal timer handle.
 */
        ਸਥਿਰ ਖਾਲੀ MPU_TimerCallback( TimerHandle_t x_ਅੰਦਰੂਨੀ_Handle ) PRIVILEGED_FUNCTION;

    #ਜੇ_ਅੰਤ /* #if ( configUSE_TIMERS == 1 ) */

/*
 * Wrappers to keep all the casting in one place.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Store_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, xHandle )                 MPU_Store_Handle_And_ਅੰਕੜੇ_At_ਸੂਚਕਾਂਕ( ( l_ਸੂਚਕਾਂਕ ), ( OpaqueObjectHandle_t ) ( xHandle ), ਨਿਰਾ, KERNEL_OBJECT_TYPE_ਕਤਾਰ )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ )                            ( ਕਤਾਰ_Handle_t ) MPU_Get_Handle_At_ਸੂਚਕਾਂਕ( ( l_ਸੂਚਕਾਂਕ ), KERNEL_OBJECT_TYPE_ਕਤਾਰ )

    #ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Store_ਕਤਾਰ_ਸੈੱਟ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, xHandle )          MPU_Store_Handle_And_ਅੰਕੜੇ_At_ਸੂਚਕਾਂਕ( ( l_ਸੂਚਕਾਂਕ ), ( OpaqueObjectHandle_t ) ( xHandle ), ਨਿਰਾ, KERNEL_OBJECT_TYPE_ਕਤਾਰ )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Get_ਕਤਾਰ_ਸੈੱਟ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ )                     ( ਕਤਾਰ_ਸੈੱਟ_Handle_t ) MPU_Get_Handle_At_ਸੂਚਕਾਂਕ( ( l_ਸੂਚਕਾਂਕ ), KERNEL_OBJECT_TYPE_ਕਤਾਰ )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Store_ਕਤਾਰ_ਸੈੱਟ_Member_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, xHandle )    MPU_Store_Handle_And_ਅੰਕੜੇ_At_ਸੂਚਕਾਂਕ( ( l_ਸੂਚਕਾਂਕ ), ( OpaqueObjectHandle_t ) ( xHandle ), ਨਿਰਾ, KERNEL_OBJECT_TYPE_ਕਤਾਰ )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Get_ਕਤਾਰ_ਸੈੱਟ_Member_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ )               ( ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t ) MPU_Get_Handle_At_ਸੂਚਕਾਂਕ( ( l_ਸੂਚਕਾਂਕ ), KERNEL_OBJECT_TYPE_ਕਤਾਰ )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Get_ਸੂਚਕਾਂਕ_For_ਕਤਾਰ_ਸੈੱਟ_Member_Handle( xHandle )             MPU_Get_ਸੂਚਕਾਂਕ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_ਕਤਾਰ )
    #ਜੇ_ਅੰਤ

/*
 * Wrappers to keep all the casting in one place for Task APIs.
 */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Store_Task_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, xHandle )            MPU_Store_Handle_And_ਅੰਕੜੇ_At_ਸੂਚਕਾਂਕ( ( l_ਸੂਚਕਾਂਕ ), ( OpaqueObjectHandle_t ) ( xHandle ), ਨਿਰਾ, KERNEL_OBJECT_TYPE_TASK )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ )                       ( TaskHandle_t ) MPU_Get_Handle_At_ਸੂਚਕਾਂਕ( ( l_ਸੂਚਕਾਂਕ ), KERNEL_OBJECT_TYPE_TASK )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Get_ਸੂਚਕਾਂਕ_For_Task_Handle( xHandle )                     MPU_Get_ਸੂਚਕਾਂਕ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TASK )

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )
/*
 * Wrappers to keep all the casting in one place for Event Group APIs.
 */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Store_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, xHandle )      MPU_Store_Handle_And_ਅੰਕੜੇ_At_ਸੂਚਕਾਂਕ( ( l_ਸੂਚਕਾਂਕ ), ( OpaqueObjectHandle_t ) ( xHandle ), ਨਿਰਾ, KERNEL_OBJECT_TYPE_EVENT_ਸਮੂਹ )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Get_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ )                 ( Event_ਸਮੂਹ_Handle_t ) MPU_Get_Handle_At_ਸੂਚਕਾਂਕ( ( l_ਸੂਚਕਾਂਕ ), KERNEL_OBJECT_TYPE_EVENT_ਸਮੂਹ )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Get_ਸੂਚਕਾਂਕ_For_Event_ਸਮੂਹ_Handle( xHandle )               MPU_Get_ਸੂਚਕਾਂਕ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_EVENT_ਸਮੂਹ )

    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Stream Buffer APIs.
 */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Store_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, xHandle )    MPU_Store_Handle_And_ਅੰਕੜੇ_At_ਸੂਚਕਾਂਕ( ( l_ਸੂਚਕਾਂਕ ), ( OpaqueObjectHandle_t ) ( xHandle), ਨਿਰਾ, KERNEL_OBJECT_TYPE_ਧਾਰਾ_ਬਫਰ )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ )               ( ਧਾਰਾ_ਬਫਰ_Handle_t ) MPU_Get_Handle_At_ਸੂਚਕਾਂਕ( ( l_ਸੂਚਕਾਂਕ ), KERNEL_OBJECT_TYPE_ਧਾਰਾ_ਬਫਰ )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Get_ਸੂਚਕਾਂਕ_For_ਧਾਰਾ_ਬਫਰ_Handle( xHandle )             MPU_Get_ਸੂਚਕਾਂਕ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_ਧਾਰਾ_ਬਫਰ )

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

    #ਜੇ ( configUSE_TIMERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Timer APIs.
 */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Store_Timer_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, xHandle, pxApplicationCallback )    MPU_Store_Handle_And_ਅੰਕੜੇ_At_ਸੂਚਕਾਂਕ( ( l_ਸੂਚਕਾਂਕ ), ( OpaqueObjectHandle_t ) ( xHandle ), ( ਖਾਲੀ * ) ( pxApplicationCallback ), KERNEL_OBJECT_TYPE_TIMER )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Get_Timer_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ )                                      ( TimerHandle_t ) MPU_Get_Handle_At_ਸੂਚਕਾਂਕ( ( l_ਸੂਚਕਾਂਕ ), KERNEL_OBJECT_TYPE_TIMER )
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_Get_ਸੂਚਕਾਂਕ_For_Timer_Handle( xHandle )                                    MPU_Get_ਸੂਚਕਾਂਕ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TIMER )

    #ਜੇ_ਅੰਤ /* #if ( configUSE_TIMERS == 1 ) */

/*-----------------------------------------------------------*/

/**
 * @brief Kernel object pool.
 */
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ KernelObject_t xKernelObjectPool[ config_PROTECTED_KERNEL_OBJECT_POOL_ਮਾਪ ] = { 0 };
/*-----------------------------------------------------------*/

    ਸਥਿਰ int32_t MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_Free_ਸੂਚਕਾਂਕ = -1;

        /* This function is called only from resource create APIs
         * which are not supposed to be called from ISRs. Therefore,
         * we only need to suspend the scheduler and do not require
         * critical section. */
        vTaskSuspendAll();
        {
            ਲਈ( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_ਮਾਪ; i++ )
            {
                ਜੇ( xKernelObjectPool[ i ].x_ਅੰਦਰੂਨੀ_Object_Handle == ਨਿਰਾ )
                {
                    /* Mark this index as not free. */
                    xKernelObjectPool[ i ].x_ਅੰਦਰੂਨੀ_Object_Handle = ( OpaqueObjectHandle_t ) ( ~0U );
                    l_Free_ਸੂਚਕਾਂਕ = i;
                    ਰੋਕੋ;
                }
            }
        }
        ( ਖਾਲੀ ) xTaskResumeAll();

        ਵਾਪਸ l_Free_ਸੂਚਕਾਂਕ;
    }
/*-----------------------------------------------------------*/

    ਸਥਿਰ ਖਾਲੀ MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( int32_t l_ਸੂਚਕਾਂਕ ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE );

        taskENTER_CRITICAL();
        {
            xKernelObjectPool[ l_ਸੂਚਕਾਂਕ ].x_ਅੰਦਰੂਨੀ_Object_Handle = ਨਿਰਾ;
            xKernelObjectPool[ l_ਸੂਚਕਾਂਕ ].ulKernelObjectType = KERNEL_OBJECT_TYPE_INVALID;
            xKernelObjectPool[ l_ਸੂਚਕਾਂਕ ].pv_Kernel_Object_ਅੰਕੜੇ = ਨਿਰਾ;
        }
        taskEXIT_CRITICAL();
    }
/*-----------------------------------------------------------*/

    ਸਥਿਰ int32_t MPU_Get_ਸੂਚਕਾਂਕ_For_Handle( OpaqueObjectHandle_t xHandle,
                                          uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_ਸੂਚਕਾਂਕ = -1;

        configASSERT( xHandle != ਨਿਰਾ );

        ਲਈ( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_ਮਾਪ; i++ )
        {
            ਜੇ( ( xKernelObjectPool[ i ].x_ਅੰਦਰੂਨੀ_Object_Handle == xHandle ) &&
                ( xKernelObjectPool[ i ].ulKernelObjectType == ulKernelObjectType ) )
            {
                l_ਸੂਚਕਾਂਕ = i;
                ਰੋਕੋ;
            }
        }

        ਵਾਪਸ l_ਸੂਚਕਾਂਕ;
    }
/*-----------------------------------------------------------*/

    ਸਥਿਰ ਖਾਲੀ MPU_Store_Handle_And_ਅੰਕੜੇ_At_ਸੂਚਕਾਂਕ( int32_t l_ਸੂਚਕਾਂਕ,
                                               OpaqueObjectHandle_t xHandle,
                                               ਖਾਲੀ * pv_Kernel_Object_ਅੰਕੜੇ,
                                               uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE );
        xKernelObjectPool[ l_ਸੂਚਕਾਂਕ ].x_ਅੰਦਰੂਨੀ_Object_Handle = xHandle;
        xKernelObjectPool[ l_ਸੂਚਕਾਂਕ ].ulKernelObjectType = ulKernelObjectType;
        xKernelObjectPool[ l_ਸੂਚਕਾਂਕ ].pv_Kernel_Object_ਅੰਕੜੇ = pv_Kernel_Object_ਅੰਕੜੇ;
    }
/*-----------------------------------------------------------*/

    ਸਥਿਰ OpaqueObjectHandle_t MPU_Get_Handle_At_ਸੂਚਕਾਂਕ( int32_t l_ਸੂਚਕਾਂਕ,
                                                      uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        OpaqueObjectHandle_t xObjectHandle = ਨਿਰਾ;

        configASSERT( IS_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE );

        ਜੇ( xKernelObjectPool[ l_ਸੂਚਕਾਂਕ ].ulKernelObjectType == ulKernelObjectType )
        {
            xObjectHandle = xKernelObjectPool[ l_ਸੂਚਕਾਂਕ ].x_ਅੰਦਰੂਨੀ_Object_Handle;
        }

        ਵਾਪਸ xObjectHandle;
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ਖਾਲੀ v_Grant_Access_ਮੰਜ਼ਿਲ_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                         int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                ਜੇ( xExternalTaskHandle == ਨਿਰਾ )
                {
                    v_ਪੋਰਟ_Grant_Access_ਮੰਜ਼ਿਲ_Kernel_Object( xExternalTaskHandle, CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( lExternalKernelObjectHandle ) );
                }
                ਨਹੀਂਤਾਂ
                {
                    l_External_Task_ਸੂਚਕਾਂਕ = ( int32_t ) xExternalTaskHandle;

                    ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_External_Task_ਸੂਚਕਾਂਕ ) != pdFALSE )
                    {
                        x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_External_Task_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                        {
                            v_ਪੋਰਟ_Grant_Access_ਮੰਜ਼ਿਲ_Kernel_Object( x_ਅੰਦਰੂਨੀ_Task_Handle,
                                                            CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #ਜੇ_ਅੰਤ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ਖਾਲੀ v_Revoke_Access_ਮੰਜ਼ਿਲ_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                          int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                ਜੇ( xExternalTaskHandle == ਨਿਰਾ )
                {
                    v_ਪੋਰਟ_Revoke_Access_ਮੰਜ਼ਿਲ_Kernel_Object( xExternalTaskHandle, CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( lExternalKernelObjectHandle ) );
                }
                ਨਹੀਂਤਾਂ
                {
                    l_External_Task_ਸੂਚਕਾਂਕ = ( int32_t ) xExternalTaskHandle;

                    ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_External_Task_ਸੂਚਕਾਂਕ ) != pdFALSE )
                    {
                        x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_External_Task_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                        {
                            v_ਪੋਰਟ_Revoke_Access_ਮੰਜ਼ਿਲ_Kernel_Object( x_ਅੰਦਰੂਨੀ_Task_Handle,
                                                             CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #ਜੇ_ਅੰਤ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਸਥਿਰ ਖਾਲੀ MPU_TimerCallback( TimerHandle_t x_ਅੰਦਰੂਨੀ_Handle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t i, l_ਸੂਚਕਾਂਕ = -1;
            TimerHandle_t xExternalHandle = ਨਿਰਾ;
            TimerCallbackFunction_t px_Application_Call_ਪਿੱਠ = ਨਿਰਾ;

            /* Coming from the timer task and therefore, should be valid. */
            configASSERT( x_ਅੰਦਰੂਨੀ_Handle != ਨਿਰਾ );

            ਲਈ( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_ਮਾਪ; i++ )
            {
                ਜੇ( ( ( TimerHandle_t ) xKernelObjectPool[ i ].x_ਅੰਦਰੂਨੀ_Object_Handle == x_ਅੰਦਰੂਨੀ_Handle ) &&
                    ( xKernelObjectPool[ i ].ulKernelObjectType == KERNEL_OBJECT_TYPE_TIMER ) )
                {
                    l_ਸੂਚਕਾਂਕ = i;
                    ਰੋਕੋ;
                }
            }

            configASSERT( l_ਸੂਚਕਾਂਕ != -1 );
            xExternalHandle = ( TimerHandle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );

            px_Application_Call_ਪਿੱਠ = ( TimerCallbackFunction_t ) xKernelObjectPool[ l_ਸੂਚਕਾਂਕ ].pv_Kernel_Object_ਅੰਕੜੇ;
            px_Application_Call_ਪਿੱਠ( xExternalHandle );
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for tasks APIs.                   */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskDelayUntil == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ਅਚਲ px_ਪਿਛਲਾ_Wake_ਸਮਾਂ,
                                            TickType_t x_ਸਮਾਂ_Increment ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ਅਚਲ px_ਪਿਛਲਾ_Wake_ਸਮਾਂ,
                                            TickType_t x_ਸਮਾਂ_Increment ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            ਅਧਾਰ_Type_t x_Is_ਪਿਛਲਾ_Wake_ਸਮਾਂ_Accessible = pdFALSE;

            ਜੇ( ( px_ਪਿਛਲਾ_Wake_ਸਮਾਂ != ਨਿਰਾ ) && ( x_ਸਮਾਂ_Increment > 0U ) )
            {
                x_Is_ਪਿਛਲਾ_Wake_ਸਮਾਂ_Accessible = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( px_ਪਿਛਲਾ_Wake_ਸਮਾਂ,
                                                                                 ਆਕਾਰ( TickType_t ),
                                                                                 ( tskMPU_WRITE_PERMISSION | tskMPU_READ_PERMISSION ) );

                ਜੇ( x_Is_ਪਿਛਲਾ_Wake_ਸਮਾਂ_Accessible == pdTRUE )
                {
                    xReturn = xTaskDelayUntil( px_ਪਿਛਲਾ_Wake_ਸਮਾਂ, x_ਸਮਾਂ_Increment );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskAbortDelay == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                    {
                        xReturn = xTaskAbortDelay( x_ਅੰਦਰੂਨੀ_Task_Handle );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_vTaskDelay == 1 )

        ਖਾਲੀ MPU_vTaskDelayImpl( TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Delay ) PRIVILEGED_FUNCTION;

        ਖਾਲੀ MPU_vTaskDelayImpl( TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Delay ) /* PRIVILEGED_FUNCTION */
        {
            vTaskDelay( x_Ticks_ਮੰਜ਼ਿਲ_Delay );
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_ux_Task_ਤਰਜੀਹ_Get == 1 )

        UBaseType_t MPU_ux_Task_ਤਰਜੀਹ_Get_Impl( ਅਚਲ TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_ਤਰਜੀਹ_Get_Impl( ਅਚਲ TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

            ਜੇ( pxTask == ਨਿਰਾ )
            {
                uxReturn = ux_Task_ਤਰਜੀਹ_Get( pxTask );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) pxTask;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                    {
                        x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                        {
                            uxReturn = ux_Task_ਤਰਜੀਹ_Get( x_ਅੰਦਰੂਨੀ_Task_Handle );
                        }
                    }
                }
            }

            ਵਾਪਸ uxReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            eTaskState eReturn = eInvalid;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) pxTask;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                    {
                        eReturn = eTaskGetState( x_ਅੰਦਰੂਨੀ_Task_Handle );
                    }
                }
            }

            ਵਾਪਸ eReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TRACE_FACILITY == 1 )

        ਖਾਲੀ MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_ਸਥਿਤੀ_t * px_Task_ਸਥਿਤੀ,
                                   ਅਧਾਰ_Type_t x_Get_Free_ਢੇਰ_Space,
                                   eTaskState eState ) PRIVILEGED_FUNCTION;

        ਖਾਲੀ MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_ਸਥਿਤੀ_t * px_Task_ਸਥਿਤੀ,
                                   ਅਧਾਰ_Type_t x_Get_Free_ਢੇਰ_Space,
                                   eTaskState eState ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Is_Task_ਸਥਿਤੀ_Writeable = pdFALSE;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;

            x_Is_Task_ਸਥਿਤੀ_Writeable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( px_Task_ਸਥਿਤੀ,
                                                                      ਆਕਾਰ( Task_ਸਥਿਤੀ_t ),
                                                                      tskMPU_WRITE_PERMISSION );

            ਜੇ( x_Is_Task_ਸਥਿਤੀ_Writeable == pdTRUE )
            {
                ਜੇ( xTask == ਨਿਰਾ )
                {
                    vTaskGetInfo( xTask, px_Task_ਸਥਿਤੀ, x_Get_Free_ਢੇਰ_Space, eState );
                }
                ਨਹੀਂਤਾਂ
                {
                    l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                    ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                        {
                            x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                            ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                            {
                                vTaskGetInfo( x_ਅੰਦਰੂਨੀ_Task_Handle, px_Task_ਸਥਿਤੀ, x_Get_Free_ਢੇਰ_Space, eState );
                            }
                        }
                    }
                }
            }
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xIdleTaskHandle = ਨਿਰਾ;

            xIdleTaskHandle = xTaskGetIdleTaskHandle();

            ਵਾਪਸ xIdleTaskHandle;
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_vTaskSuspend == 1 )

        ਖਾਲੀ MPU_vTaskSuspendImpl( TaskHandle_t px_Task_ਮੰਜ਼ਿਲ_Suspend ) PRIVILEGED_FUNCTION;

        ਖਾਲੀ MPU_vTaskSuspendImpl( TaskHandle_t px_Task_ਮੰਜ਼ਿਲ_Suspend ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;

            ਜੇ( px_Task_ਮੰਜ਼ਿਲ_Suspend == ਨਿਰਾ )
            {
                vTaskSuspend( px_Task_ਮੰਜ਼ਿਲ_Suspend );
            }
            ਨਹੀਂਤਾਂ
            {
                /* After the scheduler starts, only privileged tasks are allowed
                 * to suspend other tasks. */
                #ਜੇ ( INCLUDE_xTaskGetSchedulerState == 1 )
                    ਜੇ( ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) || ( ਪੋਰਟ_IS_TASK_PRIVILEGED() == pdTRUE ) )
                #ਨਹੀਂਤਾਂ
                    ਜੇ( ਪੋਰਟ_IS_TASK_PRIVILEGED() == pdTRUE )
                #ਜੇ_ਅੰਤ
                {
                    l_ਸੂਚਕਾਂਕ = ( int32_t ) px_Task_ਮੰਜ਼ਿਲ_Suspend;

                    ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                        {
                            x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                            ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                            {
                                vTaskSuspend( x_ਅੰਦਰੂਨੀ_Task_Handle );
                            }
                        }
                    }
                }
            }
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_vTaskSuspend == 1 )

        ਖਾਲੀ MPU_vTaskResumeImpl( TaskHandle_t px_Task_ਮੰਜ਼ਿਲ_Resume ) PRIVILEGED_FUNCTION;

        ਖਾਲੀ MPU_vTaskResumeImpl( TaskHandle_t px_Task_ਮੰਜ਼ਿਲ_Resume ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) px_Task_ਮੰਜ਼ਿਲ_Resume;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                    {
                        vTaskResume( x_ਅੰਦਰੂਨੀ_Task_Handle );
                    }
                }
            }
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_ਗਿਣਤੀ_Impl( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

    TickType_t MPU_x_Task_Get_Tick_ਗਿਣਤੀ_Impl( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
    {
        TickType_t xReturn;

        xReturn = x_Task_Get_Tick_ਗਿਣਤੀ();

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks_Impl( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks_Impl( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn;

        uxReturn = ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks();

        ਵਾਪਸ uxReturn;
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 )

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Impl( ਅਚਲ TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Impl( ਅਚਲ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE xReturn = 0;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;

            ਜੇ( xTask == ਨਿਰਾ )
            {
                xReturn = ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( xTask );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                    {
                        x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                        {
                            xReturn = ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter( x_ਅੰਦਰੂਨੀ_Task_Handle );
                        }
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 )

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Impl( ਅਚਲ TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Impl( ਅਚਲ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE xReturn = 0;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;

            ਜੇ( xTask == ਨਿਰਾ )
            {
                xReturn = ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( xTask );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                    {
                        x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                        {
                            xReturn = ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent( x_ਅੰਦਰੂਨੀ_Task_Handle );
                        }
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Impl( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Impl( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
        {
            config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent();

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Impl( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

        config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Impl( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
        {
            config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter();

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )

        ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_ਟੈਗ_ਮੁੱਲ ) PRIVILEGED_FUNCTION;

        ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_ਟੈਗ_ਮੁੱਲ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;

            ਜੇ( xTask == ਨਿਰਾ )
            {
                v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ( xTask, px_ਟੈਗ_ਮੁੱਲ );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                    {
                        x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                        {
                            v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ( x_ਅੰਦਰੂਨੀ_Task_Handle, px_ਟੈਗ_ਮੁੱਲ );
                        }
                    }
                }
            }
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ਟੈਗ_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ਟੈਗ_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;

            ਜੇ( xTask == ਨਿਰਾ )
            {
                xReturn = x_Task_Get_Application_Task_ਟੈਗ( xTask );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                    {
                        x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                        {
                            xReturn = x_Task_Get_Application_Task_ਟੈਗ( x_ਅੰਦਰੂਨੀ_Task_Handle );
                        }
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_ਅੰਕ_THREAD_LOCAL_STORAGE_ਸੂਚਕ_ਸਾਰੇ != 0 )

        ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ_Impl( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                                        ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ,
                                                        ਖਾਲੀ * pv_ਮੁੱਲ ) PRIVILEGED_FUNCTION;

        ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ_Impl( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                                        ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ,
                                                        ਖਾਲੀ * pv_ਮੁੱਲ ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;

            ਜੇ( x_Task_ਮੰਜ਼ਿਲ_ਸੈੱਟ == ਨਿਰਾ )
            {
                v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ( x_Task_ਮੰਜ਼ਿਲ_ਸੈੱਟ, x_ਸੂਚਕਾਂਕ, pv_ਮੁੱਲ );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Task_ਮੰਜ਼ਿਲ_ਸੈੱਟ;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                    {
                        x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                        {
                            v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ( x_ਅੰਦਰੂਨੀ_Task_Handle, x_ਸੂਚਕਾਂਕ, pv_ਮੁੱਲ );
                        }
                    }
                }
            }
        }

    #ਜੇ_ਅੰਤ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_ਅੰਕ_THREAD_LOCAL_STORAGE_ਸੂਚਕ_ਸਾਰੇ != 0 )

        ਖਾਲੀ * MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ_Impl( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Query,
                                                           ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ ) PRIVILEGED_FUNCTION;

        ਖਾਲੀ * MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ_Impl( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Query,
                                                           ਅਧਾਰ_Type_t x_ਸੂਚਕਾਂਕ ) /* PRIVILEGED_FUNCTION */
        {
            ਖਾਲੀ * pvReturn = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;

            ਜੇ( x_Task_ਮੰਜ਼ਿਲ_Query == ਨਿਰਾ )
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ( x_Task_ਮੰਜ਼ਿਲ_Query, x_ਸੂਚਕਾਂਕ );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Task_ਮੰਜ਼ਿਲ_Query;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                    {
                        x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                        {
                            pvReturn = pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ( x_ਅੰਦਰੂਨੀ_Task_Handle, x_ਸੂਚਕਾਂਕ );
                        }
                    }
                }
            }

            ਵਾਪਸ pvReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_ਸਥਿਤੀ_t * px_Task_ਸਥਿਤੀ_Array,
                                                  UBaseType_t ux_Array_ਮਾਪ,
                                                  config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE * pul_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_ਸਥਿਤੀ_t * px_Task_ਸਥਿਤੀ_Array,
                                                  UBaseType_t ux_Array_ਮਾਪ,
                                                  config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE * pul_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            ਅਧਾਰ_Type_t x_Is_Task_ਸਥਿਤੀ_Array_Writeable = pdFALSE;
            ਅਧਾਰ_Type_t x_Is_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ_Writeable = pdFALSE;

            ਜੇ( mpu_MULTIPLY_BASETYPE_WILL_ਉਛਾਲ( ਆਕਾਰ( Task_ਸਥਿਤੀ_t ), ux_Array_ਮਾਪ ) == 0 )
            {
                x_Is_Task_ਸਥਿਤੀ_Array_Writeable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( px_Task_ਸਥਿਤੀ_Array,
                                                                               ਆਕਾਰ( Task_ਸਥਿਤੀ_t ) * ( size_t ) ux_Array_ਮਾਪ,
                                                                               tskMPU_WRITE_PERMISSION );

                ਜੇ( pul_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ != ਨਿਰਾ )
                {
                    x_Is_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ_Writeable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( pul_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ,
                                                                                ਆਕਾਰ( config_ਲੜੀਵਾਰ_ਸਮਾਂ_COUNTER_TYPE ),
                                                                                tskMPU_WRITE_PERMISSION );
                }

                ਜੇ( ( x_Is_Task_ਸਥਿਤੀ_Array_Writeable == pdTRUE ) &&
                    ( ( pul_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ == ਨਿਰਾ ) || ( x_Is_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ_Writeable == pdTRUE ) ) )
                {
                    uxReturn = uxTaskGetSystemState( px_Task_ਸਥਿਤੀ_Array, ux_Array_ਮਾਪ, pul_ਕੁੱਲ_ਲੜੀਵਾਰ_ਸਮਾਂ );
                }
            }

            ਵਾਪਸ uxReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;

            ਜੇ( xTask == ਨਿਰਾ )
            {
                uxReturn = ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark( xTask );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                    {
                        x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                        {
                            uxReturn = ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark( x_ਅੰਦਰੂਨੀ_Task_Handle );
                        }
                    }
                }
            }

            ਵਾਪਸ uxReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2 == 1 )

        config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE uxReturn = 0;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;

            ਜੇ( xTask == ਨਿਰਾ )
            {
                uxReturn = ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2( xTask );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                    {
                        x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                        {
                            uxReturn = ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2( x_ਅੰਦਰੂਨੀ_Task_Handle );
                        }
                    }
                }
            }

            ਵਾਪਸ uxReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            TaskHandle_t xExternalTaskHandle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            x_ਅੰਦਰੂਨੀ_Task_Handle = xTaskGetCurrentTaskHandle();

            ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
            {
                l_ਸੂਚਕਾਂਕ = MPU_Get_ਸੂਚਕਾਂਕ_For_Task_Handle( x_ਅੰਦਰੂਨੀ_Task_Handle );

                ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ xExternalTaskHandle;
        }

    #ਜੇ_ਅੰਤ /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskGetSchedulerState == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskGetSchedulerStateImpl( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_xTaskGetSchedulerStateImpl( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = taskSCHEDULER_NOT_STARTED;

            xReturn = xTaskGetSchedulerState();

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State_Impl( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ ) PRIVILEGED_FUNCTION;

    ਖਾਲੀ MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State_Impl( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ ) /* PRIVILEGED_FUNCTION */
    {
        ਅਧਾਰ_Type_t x_Is_ਸਮਾਂ_ਬਾਹਰਲਾ_Writeable = pdFALSE;

        ਜੇ( px_ਸਮਾਂ_ਬਾਹਰਲਾ != ਨਿਰਾ )
        {
            x_Is_ਸਮਾਂ_ਬਾਹਰਲਾ_Writeable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( px_ਸਮਾਂ_ਬਾਹਰਲਾ,
                                                                   ਆਕਾਰ( ਸਮਾਂ_ਬਾਹਰਲਾ_t ),
                                                                   tskMPU_WRITE_PERMISSION );

            ਜੇ( x_Is_ਸਮਾਂ_ਬਾਹਰਲਾ_Writeable == pdTRUE )
            {
                v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State( px_ਸਮਾਂ_ਬਾਹਰਲਾ );
            }
        }
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ_Impl( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ,
                                             TickType_t * ਅਚਲ px_Ticks_ਮੰਜ਼ਿਲ_Wait ) PRIVILEGED_FUNCTION;

    ਅਧਾਰ_Type_t MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ_Impl( ਸਮਾਂ_ਬਾਹਰਲਾ_t * ਅਚਲ px_ਸਮਾਂ_ਬਾਹਰਲਾ,
                                             TickType_t * ਅਚਲ px_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* PRIVILEGED_FUNCTION */
    {
        ਅਧਾਰ_Type_t xReturn = pdFALSE;
        ਅਧਾਰ_Type_t x_Is_ਸਮਾਂ_ਬਾਹਰਲਾ_Writeable = pdFALSE;
        ਅਧਾਰ_Type_t x_Is_Ticks_ਮੰਜ਼ਿਲ_Wait_Writeable = pdFALSE;

        ਜੇ( ( px_ਸਮਾਂ_ਬਾਹਰਲਾ != ਨਿਰਾ ) && ( px_Ticks_ਮੰਜ਼ਿਲ_Wait != ਨਿਰਾ ) )
        {
            x_Is_ਸਮਾਂ_ਬਾਹਰਲਾ_Writeable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( px_ਸਮਾਂ_ਬਾਹਰਲਾ,
                                                                   ਆਕਾਰ( ਸਮਾਂ_ਬਾਹਰਲਾ_t ),
                                                                   tskMPU_WRITE_PERMISSION );
            x_Is_Ticks_ਮੰਜ਼ਿਲ_Wait_Writeable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( px_Ticks_ਮੰਜ਼ਿਲ_Wait,
                                                                       ਆਕਾਰ( TickType_t ),
                                                                       tskMPU_WRITE_PERMISSION );

            ਜੇ( ( x_Is_ਸਮਾਂ_ਬਾਹਰਲਾ_Writeable == pdTRUE ) && ( x_Is_Ticks_ਮੰਜ਼ਿਲ_Wait_Writeable == pdTRUE ) )
            {
                xReturn = x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ( px_ਸਮਾਂ_ਬਾਹਰਲਾ, px_Ticks_ਮੰਜ਼ਿਲ_Wait );
            }
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Notify,
                                           UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Notify,
                                           uint32_t ul_ਮੁੱਲ,
                                           eNotifyAction eAction,
                                           uint32_t * pul_ਪਿਛਲਾ_Notification_ਮੁੱਲ ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyParams_t xParams;

            xParams.x_Task_ਮੰਜ਼ਿਲ_Notify = x_Task_ਮੰਜ਼ਿਲ_Notify;
            xParams.ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Notify = ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Notify;
            xParams.ul_ਮੁੱਲ = ul_ਮੁੱਲ;
            xParams.eAction = eAction;
            xParams.pul_ਪਿਛਲਾ_Notification_ਮੁੱਲ = pul_ਪਿਛਲਾ_Notification_ਮੁੱਲ;

            xReturn = MPU_x_Task_Generic_Notify_ਇੰਦਰਾਜ( &( xParams ) );

            ਵਾਪਸ xReturn;
        }

        ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyImpl( ਅਚਲ xTaskGenericNotifyParams_t * pxParams ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyImpl( ਅਚਲ xTaskGenericNotifyParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Is_ਪਿਛਲਾ_Notification_ਮੁੱਲ_Writeable = pdFALSE;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;
            ਅਧਾਰ_Type_t xAreParamsReadable = pdFALSE;

            ਜੇ( pxParams != ਨਿਰਾ )
            {
                xAreParamsReadable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( pxParams,
                                                                      ਆਕਾਰ( xTaskGenericNotifyParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ਜੇ( xAreParamsReadable == pdTRUE )
            {
                ਜੇ( ( pxParams->ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Notify < configTASK_NOTIFICATION_ARRAY_ENTRIES ) &&
                    ( ( pxParams->eAction == eNoAction ) ||
                      ( pxParams->eAction == e_ਸੈੱਟ_ਬਿੱਟ ) ||
                      ( pxParams->eAction == eIncrement ) ||
                      ( pxParams->eAction == e_ਸੈੱਟ_ਮੁੱਲ_With_Overwrite ) ||
                      ( pxParams->eAction == e_ਸੈੱਟ_ਮੁੱਲ_Without_Overwrite ) ) )
                {
                    ਜੇ( pxParams->pul_ਪਿਛਲਾ_Notification_ਮੁੱਲ != ਨਿਰਾ )
                    {
                        x_Is_ਪਿਛਲਾ_Notification_ਮੁੱਲ_Writeable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( pxParams->pul_ਪਿਛਲਾ_Notification_ਮੁੱਲ,
                                                                                                 ਆਕਾਰ( uint32_t ),
                                                                                                 tskMPU_WRITE_PERMISSION );
                    }

                    ਜੇ( ( pxParams->pul_ਪਿਛਲਾ_Notification_ਮੁੱਲ == ਨਿਰਾ ) ||
                        ( x_Is_ਪਿਛਲਾ_Notification_ਮੁੱਲ_Writeable == pdTRUE ) )
                    {
                        l_ਸੂਚਕਾਂਕ = ( int32_t ) ( pxParams->x_Task_ਮੰਜ਼ਿਲ_Notify );

                        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                            ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                            {
                                x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                                ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                                {
                                    xReturn = xTaskGenericNotify( x_ਅੰਦਰੂਨੀ_Task_Handle,
                                                                  pxParams->ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Notify,
                                                                  pxParams->ul_ਮੁੱਲ,
                                                                  pxParams->eAction,
                                                                  pxParams->pul_ਪਿਛਲਾ_Notification_ਮੁੱਲ );
                                }
                            }
                        }
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On,
                                               uint32_t ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear_On_ਇੰਦਰਾਜ,
                                               uint32_t ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear_On_Exit,
                                               uint32_t * pul_Notification_ਮੁੱਲ,
                                               TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait )
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyWaitParams_t xParams;

            xParams.ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On = ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On;
            xParams.ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear_On_ਇੰਦਰਾਜ = ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear_On_ਇੰਦਰਾਜ;
            xParams.ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear_On_Exit = ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear_On_Exit;
            xParams.pul_Notification_ਮੁੱਲ = pul_Notification_ਮੁੱਲ;
            xParams.x_Ticks_ਮੰਜ਼ਿਲ_Wait = x_Ticks_ਮੰਜ਼ਿਲ_Wait;

            xReturn = MPU_x_Task_Generic_Notify_Wait_ਇੰਦਰਾਜ( &( xParams ) );

            ਵਾਪਸ xReturn;
        }

        ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyWaitImpl( ਅਚਲ xTaskGenericNotifyWaitParams_t * pxParams ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyWaitImpl( ਅਚਲ xTaskGenericNotifyWaitParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            ਅਧਾਰ_Type_t x_Is_Notification_ਮੁੱਲ_Writable = pdFALSE;
            ਅਧਾਰ_Type_t xAreParamsReadable = pdFALSE;

            ਜੇ( pxParams != ਨਿਰਾ )
            {
                xAreParamsReadable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( pxParams,
                                                                      ਆਕਾਰ( xTaskGenericNotifyWaitParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ਜੇ( xAreParamsReadable == pdTRUE )
            {
                ਜੇ( pxParams->ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
                {
                    ਜੇ( pxParams->pul_Notification_ਮੁੱਲ != ਨਿਰਾ )
                    {
                        x_Is_Notification_ਮੁੱਲ_Writable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( pxParams->pul_Notification_ਮੁੱਲ,
                                                                                        ਆਕਾਰ( uint32_t ),
                                                                                        tskMPU_WRITE_PERMISSION );
                    }

                    ਜੇ( ( pxParams->pul_Notification_ਮੁੱਲ == ਨਿਰਾ ) ||
                        ( x_Is_Notification_ਮੁੱਲ_Writable == pdTRUE ) )
                    {
                        xReturn = xTaskGenericNotifyWait( pxParams->ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On,
                                                          pxParams->ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear_On_ਇੰਦਰਾਜ,
                                                          pxParams->ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear_On_Exit,
                                                          pxParams->pul_Notification_ਮੁੱਲ,
                                                          pxParams->x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On,
                                                  ਅਧਾਰ_Type_t x_Clear_ਗਿਣਤੀ_On_Exit,
                                                  TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On,
                                                  ਅਧਾਰ_Type_t x_Clear_ਗਿਣਤੀ_On_Exit,
                                                  TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;

            ਜੇ( ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ulReturn = ulTaskGenericNotifyTake( ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Wait_On, x_Clear_ਗਿਣਤੀ_On_Exit, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
            }

            ਵਾਪਸ ulReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;

            ਜੇ( ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ਜੇ( xTask == ਨਿਰਾ )
                {
                    xReturn = xTaskGenericNotifyStateClear( xTask, ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear );
                }
                ਨਹੀਂਤਾਂ
                {
                    l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                    ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                        {
                            x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                            ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                            {
                                xReturn = xTaskGenericNotifyStateClear( x_ਅੰਦਰੂਨੀ_Task_Handle, ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear );
                            }
                        }
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_ਮੁੱਲ_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear,
                                                        uint32_t ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ul_Task_Generic_Notify_ਮੁੱਲ_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear,
                                                        uint32_t ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = pdFALSE;

            ਜੇ( ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ਜੇ( xTask == ਨਿਰਾ )
                {
                    ulReturn = ul_Task_Generic_Notify_ਮੁੱਲ_Clear( xTask, ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear, ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear );
                }
                ਨਹੀਂਤਾਂ
                {
                    l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                    ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Task == pdTRUE )
                        {
                            x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                            ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                            {
                                ulReturn = ul_Task_Generic_Notify_ਮੁੱਲ_Clear( x_ਅੰਦਰੂਨੀ_Task_Handle, ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Clear, ul_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear );
                            }
                        }
                    }
                }
            }

            ਵਾਪਸ ulReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Task APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_ਕੋਡ,
                                    ਅਚਲ ਅੱਖਰ * ਅਚਲ pcName,
                                    ਅਚਲ config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE ux_ਢੇਰ_ਡੂੰਘਾਈ,
                                    ਖਾਲੀ * pvParameters,
                                    UBaseType_t ux_ਤਰਜੀਹ,
                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                /* xTaskCreate() can only be used to create privileged tasks in MPU port. */
                ਜੇ( ( ux_ਤਰਜੀਹ & ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ ) != 0 )
                {
                    xReturn = xTaskCreate( pv_Task_ਕੋਡ, pcName, ux_ਢੇਰ_ਡੂੰਘਾਈ, pvParameters, ux_ਤਰਜੀਹ, &( x_ਅੰਦਰੂਨੀ_Task_Handle ) );

                    ਜੇ( ( xReturn == pdPASS ) && ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ ) )
                    {
                        MPU_Store_Task_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_Task_Handle );

                        ਜੇ( pxCreatedTask != ਨਿਰਾ )
                        {
                            *pxCreatedTask = ( TaskHandle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                        }
                    }
                    ਨਹੀਂਤਾਂ
                    {
                        MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_SUPPORT_STATIC_ਵੰਡ == 1 )

        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_ਕੋਡ,
                                            ਅਚਲ ਅੱਖਰ * ਅਚਲ pcName,
                                            ਅਚਲ config_ਢੇਰ_ਡੂੰਘਾਈ_TYPE ux_ਢੇਰ_ਡੂੰਘਾਈ,
                                            ਖਾਲੀ * ਅਚਲ pvParameters,
                                            UBaseType_t ux_ਤਰਜੀਹ,
                                            ਢੇਰ_Type_t * ਅਚਲ pux_ਢੇਰ_ਬਫਰ,
                                            StaticTask_t * ਅਚਲ px_Task_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xExternalTaskHandle = ਨਿਰਾ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                x_ਅੰਦਰੂਨੀ_Task_Handle = xTaskCreateStatic( px_Task_ਕੋਡ, pcName, ux_ਢੇਰ_ਡੂੰਘਾਈ, pvParameters, ux_ਤਰਜੀਹ, pux_ਢੇਰ_ਬਫਰ, px_Task_ਬਫਰ );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                {
                    MPU_Store_Task_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_Task_Handle );

                    #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ਜੇ( ( ux_ਤਰਜੀਹ & ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ ) == 0 )
                        {
                            v_ਪੋਰਟ_Grant_Access_ਮੰਜ਼ਿਲ_Kernel_Object( x_ਅੰਦਰੂਨੀ_Task_Handle, l_ਸੂਚਕਾਂਕ );
                        }
                    }
                    #ਜੇ_ਅੰਤ

                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ xExternalTaskHandle;
        }

    #ਜੇ_ਅੰਤ /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_vTaskDelete == 1 )

        ਖਾਲੀ MPU_vTaskDelete( TaskHandle_t px_Task_ਮੰਜ਼ਿਲ_Delete ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            ਜੇ( px_Task_ਮੰਜ਼ਿਲ_Delete == ਨਿਰਾ )
            {
                x_ਅੰਦਰੂਨੀ_Task_Handle = xTaskGetCurrentTaskHandle();
                l_ਸੂਚਕਾਂਕ = MPU_Get_ਸੂਚਕਾਂਕ_For_Task_Handle( x_ਅੰਦਰੂਨੀ_Task_Handle );

                ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }

                vTaskDelete( x_ਅੰਦਰੂਨੀ_Task_Handle );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) px_Task_ਮੰਜ਼ਿਲ_Delete;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                    {
                        MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );
                        vTaskDelete( x_ਅੰਦਰੂਨੀ_Task_Handle );
                    }
                }
            }
        }

    #ਜੇ_ਅੰਤ /* #if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/


    #ਜੇ ( INCLUDE_v_Task_ਤਰਜੀਹ_ਸੈੱਟ == 1 )

        ਖਾਲੀ MPU_v_Task_ਤਰਜੀਹ_ਸੈੱਟ( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_ਤਰਜੀਹ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            ਜੇ( pxTask == ਨਿਰਾ )
            {
                v_Task_ਤਰਜੀਹ_ਸੈੱਟ( pxTask, ux_New_ਤਰਜੀਹ );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) pxTask;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                    {
                        v_Task_ਤਰਜੀਹ_ਸੈੱਟ( x_ਅੰਦਰੂਨੀ_Task_Handle, ux_New_ਤਰਜੀਹ );
                    }
                }
            }
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_xTaskGetHandle == 1 )

        TaskHandle_t MPU_xTaskGetHandle( ਅਚਲ ਅੱਖਰ * pc_Name_ਮੰਜ਼ਿਲ_Query ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            TaskHandle_t xExternalTaskHandle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            x_ਅੰਦਰੂਨੀ_Task_Handle = xTaskGetHandle( pc_Name_ਮੰਜ਼ਿਲ_Query );

            ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
            {
                l_ਸੂਚਕਾਂਕ = MPU_Get_ਸੂਚਕਾਂਕ_For_Task_Handle( x_ਅੰਦਰੂਨੀ_Task_Handle );

                ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ xExternalTaskHandle;
        }

    #ਜੇ_ਅੰਤ /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/


    #ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     ਖਾਲੀ * pvParameter ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

            ਜੇ( xTask == ਨਿਰਾ )
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                    {
                        xReturn = xTaskCallApplicationTaskHook( x_ਅੰਦਰੂਨੀ_Task_Handle, pvParameter );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskCreateRestricted( ਅਚਲ TaskParameters_t * ਅਚਲ pxTaskDefinition,
                                              TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                xReturn = xTaskCreateRestricted( pxTaskDefinition, &( x_ਅੰਦਰੂਨੀ_Task_Handle ) );

                ਜੇ( ( xReturn == pdPASS ) && ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ ) )
                {
                    MPU_Store_Task_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_Task_Handle );

                    #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ਜੇ( ( pxTaskDefinition->ux_ਤਰਜੀਹ & ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ ) == 0 )
                        {
                            v_ਪੋਰਟ_Grant_Access_ਮੰਜ਼ਿਲ_Kernel_Object( x_ਅੰਦਰੂਨੀ_Task_Handle, l_ਸੂਚਕਾਂਕ );
                        }
                    }
                    #ਜੇ_ਅੰਤ

                    ਜੇ( pxCreatedTask != ਨਿਰਾ )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                    }
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_SUPPORT_STATIC_ਵੰਡ == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskCreateRestrictedStatic( ਅਚਲ TaskParameters_t * ਅਚਲ pxTaskDefinition,
                                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                xReturn = xTaskCreateRestrictedStatic( pxTaskDefinition, &( x_ਅੰਦਰੂਨੀ_Task_Handle ) );

                ਜੇ( ( xReturn == pdPASS ) && ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ ) )
                {
                    MPU_Store_Task_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_Task_Handle );

                    #ਜੇ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ਜੇ( ( pxTaskDefinition->ux_ਤਰਜੀਹ & ਪੋਰਟ_PRIVILEGE_ਦੋਆਧਾਰੀ_ਅੰਕ ) == 0 )
                        {
                            v_ਪੋਰਟ_Grant_Access_ਮੰਜ਼ਿਲ_Kernel_Object( x_ਅੰਦਰੂਨੀ_Task_Handle, l_ਸੂਚਕਾਂਕ );
                        }
                    }
                    #ਜੇ_ਅੰਤ

                    ਜੇ( pxCreatedTask != ਨਿਰਾ )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                    }
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    ਖਾਲੀ MPU_vTaskAllocateMPURegions( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Modify,
                                      ਅਚਲ ਸਮ੍ਰਿਤੀ_Region_t * ਅਚਲ xRegions ) /* PRIVILEGED_FUNCTION */
    {
        TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
        int32_t l_ਸੂਚਕਾਂਕ;

        ਜੇ( x_Task_ਮੰਜ਼ਿਲ_Modify == ਨਿਰਾ )
        {
            vTaskAllocateMPURegions( x_Task_ਮੰਜ਼ਿਲ_Modify, xRegions );
        }
        ਨਹੀਂਤਾਂ
        {
            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Task_ਮੰਜ਼ਿਲ_Modify;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                {
                    vTaskAllocateMPURegions( x_ਅੰਦਰੂਨੀ_Task_Handle, xRegions );
                }
            }
        }
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( config_SUPPORT_STATIC_ਵੰਡ == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskGetStaticBuffers( TaskHandle_t xTask,
                                              ਢੇਰ_Type_t ** ppux_ਢੇਰ_ਬਫਰ,
                                              StaticTask_t ** ppx_Task_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t xReturn = pdFALSE;

            ਜੇ( xTask == ਨਿਰਾ )
            {
                x_ਅੰਦਰੂਨੀ_Task_Handle = xTaskGetCurrentTaskHandle();
                xReturn = xTaskGetStaticBuffers( x_ਅੰਦਰੂਨੀ_Task_Handle, ppux_ਢੇਰ_ਬਫਰ, ppx_Task_ਬਫਰ );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                    {
                        xReturn = xTaskGetStaticBuffers( x_ਅੰਦਰੂਨੀ_Task_Handle, ppux_ਢੇਰ_ਬਫਰ, ppx_Task_ਬਫਰ );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    ਅੱਖਰ * MPU_pcTaskGetName( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Query ) /* PRIVILEGED_FUNCTION */
    {
        ਅੱਖਰ * pcReturn = ਨਿਰਾ;
        int32_t l_ਸੂਚਕਾਂਕ;
        TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

        ਜੇ( x_Task_ਮੰਜ਼ਿਲ_Query == ਨਿਰਾ )
        {
            pcReturn = pcTaskGetName( x_Task_ਮੰਜ਼ਿਲ_Query );
        }
        ਨਹੀਂਤਾਂ
        {
            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Task_ਮੰਜ਼ਿਲ_Query;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                {
                    pcReturn = pcTaskGetName( x_ਅੰਦਰੂਨੀ_Task_Handle );
                }
            }
        }

        ਵਾਪਸ pcReturn;
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( INCLUDE_ux_Task_ਤਰਜੀਹ_Get == 1 )

        UBaseType_t MPU_ux_Task_ਤਰਜੀਹ_Get_From_ISR( ਅਚਲ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

            ਜੇ( xTask == ਨਿਰਾ )
            {
                uxReturn = ux_Task_ਤਰਜੀਹ_Get_From_ISR( xTask );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                    {
                        uxReturn = ux_Task_ਤਰਜੀਹ_Get_From_ISR( x_ਅੰਦਰੂਨੀ_Task_Handle );
                    }
                }
            }

            ਵਾਪਸ uxReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( INCLUDE_ux_Task_ਤਰਜੀਹ_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_ਅਧਾਰ_ਤਰਜੀਹ_Get( ਅਚਲ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

            ਜੇ( xTask == ਨਿਰਾ )
            {
                uxReturn = ux_Task_ਅਧਾਰ_ਤਰਜੀਹ_Get( xTask );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                    {
                        uxReturn = ux_Task_ਅਧਾਰ_ਤਰਜੀਹ_Get( x_ਅੰਦਰੂਨੀ_Task_Handle );
                    }
                }
            }

            ਵਾਪਸ uxReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( INCLUDE_ux_Task_ਤਰਜੀਹ_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_ਅਧਾਰ_ਤਰਜੀਹ_Get_From_ISR( ਅਚਲ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

            ਜੇ( xTask == ਨਿਰਾ )
            {
                uxReturn = ux_Task_ਅਧਾਰ_ਤਰਜੀਹ_Get_From_ISR( xTask );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                    {
                        uxReturn = ux_Task_ਅਧਾਰ_ਤਰਜੀਹ_Get_From_ISR( x_ਅੰਦਰੂਨੀ_Task_Handle );
                    }
                }
            }

            ਵਾਪਸ uxReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

        ਅਧਾਰ_Type_t MPU_xTaskResumeFromISR( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Resume ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Task_ਮੰਜ਼ਿਲ_Resume;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                {
                    xReturn = xTaskResumeFromISR( x_ਅੰਦਰੂਨੀ_Task_Handle );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )*/
/*---------------------------------------------------------------------------------------*/

    #ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ਟੈਗ_From_ISR( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

            ਜੇ( xTask == ਨਿਰਾ )
            {
                xReturn = x_Task_Get_Application_Task_ਟੈਗ_From_ISR( xTask );
            }
            ਨਹੀਂਤਾਂ
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) xTask;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                    {
                        xReturn = x_Task_Get_Application_Task_ਟੈਗ_From_ISR( x_ਅੰਦਰੂਨੀ_Task_Handle );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ਅਧਾਰ_Type_t MPU_xTaskGenericNotifyFromISR( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Notify,
                                                  UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Notify,
                                                  uint32_t ul_ਮੁੱਲ,
                                                  eNotifyAction eAction,
                                                  uint32_t * pul_ਪਿਛਲਾ_Notification_ਮੁੱਲ,
                                                  ਅਧਾਰ_Type_t * px_Higher_ਤਰਜੀਹ_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Task_ਮੰਜ਼ਿਲ_Notify;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                {
                    xReturn = xTaskGenericNotifyFromISR( x_ਅੰਦਰੂਨੀ_Task_Handle, ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Notify, ul_ਮੁੱਲ, eAction, pul_ਪਿਛਲਾ_Notification_ਮੁੱਲ, px_Higher_ਤਰਜੀਹ_Task_Woken );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ਖਾਲੀ MPU_vTaskGenericNotifyGiveFromISR( TaskHandle_t x_Task_ਮੰਜ਼ਿਲ_Notify,
                                                UBaseType_t ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Notify,
                                                ਅਧਾਰ_Type_t * px_Higher_ਤਰਜੀਹ_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ਸੂਚਕਾਂਕ;
            TaskHandle_t x_ਅੰਦਰੂਨੀ_Task_Handle = ਨਿਰਾ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Task_ਮੰਜ਼ਿਲ_Notify;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_Task_Handle = MPU_Get_Task_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Task_Handle != ਨਿਰਾ )
                {
                    vTaskGenericNotifyGiveFromISR( x_ਅੰਦਰੂਨੀ_Task_Handle, ux_ਸੂਚਕਾਂਕ_ਮੰਜ਼ਿਲ_Notify, px_Higher_ਤਰਜੀਹ_Task_Woken );
                }
            }
        }
    #ਜੇ_ਅੰਤ /*#if ( configUSE_TASK_NOTIFICATIONS == 1 )*/
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for queue APIs.                   */
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Generic_Send_Impl( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                          ਅਚਲ ਖਾਲੀ * ਅਚਲ pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ,
                                          TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait,
                                          ਅਧਾਰ_Type_t xCopyPosition ) PRIVILEGED_FUNCTION;

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Generic_Send_Impl( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                          ਅਚਲ ਖਾਲੀ * ਅਚਲ pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ,
                                          TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait,
                                          ਅਧਾਰ_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_ਸੂਚਕਾਂਕ;
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
        ਅਧਾਰ_Type_t xReturn = pdFAIL;
        ਅਧਾਰ_Type_t x_Is_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ_Readable = pdFALSE;
        ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = pdFALSE;
        UBaseType_t ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ, ux_ਕਤਾਰ_ਲੰਮਾਈ;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ == pdTRUE )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                {
                    ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ = ux_ਕਤਾਰ_Get_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
                    ux_ਕਤਾਰ_ਲੰਮਾਈ = ux_ਕਤਾਰ_Get_ਕਤਾਰ_ਲੰਮਾਈ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );

                    ਜੇ( ( !( ( pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ == ਨਿਰਾ ) && ( ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ != ( UBaseType_t ) 0U ) ) ) &&
                        ( !( ( xCopyPosition == ਕਤਾਰ_OVERWRITE ) && ( ux_ਕਤਾਰ_ਲੰਮਾਈ != ( UBaseType_t ) 1U ) ) )
                        #ਜੇ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_ਮੰਜ਼ਿਲ_Wait != 0U ) ) )
                        #ਜੇ_ਅੰਤ
                        )
                    {
                        ਜੇ( pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ != ਨਿਰਾ )
                        {
                            x_Is_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ_Readable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ,
                                                                                      ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ,
                                                                                      tskMPU_READ_PERMISSION );
                        }

                        ਜੇ( ( pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ == ਨਿਰਾ ) || ( x_Is_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ_Readable == pdTRUE ) )
                        {
                            xReturn = x_ਕਤਾਰ_Generic_Send( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle, pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ, x_Ticks_ਮੰਜ਼ਿਲ_Wait, xCopyPosition );
                        }
                    }
                }
            }
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ_Impl( ਅਚਲ ਕਤਾਰ_Handle_t px_ਕਤਾਰ ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ_Impl( ਅਚਲ ਕਤਾਰ_Handle_t px_ਕਤਾਰ ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_ਸੂਚਕਾਂਕ;
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
        UBaseType_t uxReturn = 0;
        ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = pdFALSE;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) px_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ == pdTRUE )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                {
                    uxReturn = ux_ਕਤਾਰ_Messages_ਉਡੀਕ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
                }
            }
        }

        ਵਾਪਸ uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ_Impl( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ_Impl( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_ਸੂਚਕਾਂਕ;
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
        UBaseType_t uxReturn = 0;
        ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = pdFALSE;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ == pdTRUE )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                {
                    uxReturn = ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
                }
            }
        }

        ਵਾਪਸ uxReturn;
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Receive_Impl( ਕਤਾਰ_Handle_t px_ਕਤਾਰ,
                                      ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                                      TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) PRIVILEGED_FUNCTION;

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Receive_Impl( ਕਤਾਰ_Handle_t px_ਕਤਾਰ,
                                      ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                                      TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_ਸੂਚਕਾਂਕ;
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
        ਅਧਾਰ_Type_t xReturn = pdFAIL;
        ਅਧਾਰ_Type_t x_Is_Receive_ਬਫਰ_Writable = pdFALSE;
        ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = pdFALSE;
        UBaseType_t ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) px_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ == pdTRUE )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                {
                    ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ = ux_ਕਤਾਰ_Get_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );

                    ਜੇ( ( !( ( ( pv_ਬਫਰ ) == ਨਿਰਾ ) && ( ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ != ( UBaseType_t ) 0U ) ) )
                        #ਜੇ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_ਮੰਜ਼ਿਲ_Wait != 0U ) ) )
                        #ਜੇ_ਅੰਤ
                        )
                    {
                        x_Is_Receive_ਬਫਰ_Writable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( pv_ਬਫਰ,
                                                                                    ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ,
                                                                                    tskMPU_WRITE_PERMISSION );

                        ਜੇ( x_Is_Receive_ਬਫਰ_Writable == pdTRUE )
                        {
                            xReturn = x_ਕਤਾਰ_Receive( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle, pv_ਬਫਰ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                        }
                    }
                }
            }
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Peek_Impl( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                   ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                                   TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) PRIVILEGED_FUNCTION;

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Peek_Impl( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                   ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                                   TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_ਸੂਚਕਾਂਕ;
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
        ਅਧਾਰ_Type_t xReturn = pdFAIL;
        ਅਧਾਰ_Type_t x_Is_Receive_ਬਫਰ_Writable = pdFALSE;
        UBaseType_t ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ;
        ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = pdFALSE;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ == pdTRUE )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                {
                    ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ = ux_ਕਤਾਰ_Get_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );

                    ਜੇ( ( !( ( ( pv_ਬਫਰ ) == ਨਿਰਾ ) && ( ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ != ( UBaseType_t ) 0U ) ) )
                        #ਜੇ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_ਮੰਜ਼ਿਲ_Wait != 0U ) ) )
                        #ਜੇ_ਅੰਤ
                        )
                    {
                        x_Is_Receive_ਬਫਰ_Writable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( pv_ਬਫਰ,
                                                                                    ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ,
                                                                                    tskMPU_WRITE_PERMISSION );

                        ਜੇ( x_Is_Receive_ਬਫਰ_Writable == pdTRUE )
                        {
                            xReturn = x_ਕਤਾਰ_Peek( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle, pv_ਬਫਰ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                        }
                    }
                }
            }
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Semaphore_Take_Impl( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                            TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) PRIVILEGED_FUNCTION;

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Semaphore_Take_Impl( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                            TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_ਸੂਚਕਾਂਕ;
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
        ਅਧਾਰ_Type_t xReturn = pdFAIL;
        UBaseType_t ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ;
        ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = pdFALSE;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ == pdTRUE )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                {
                    ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ = ux_ਕਤਾਰ_Get_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );

                    ਜੇ( ( ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ == 0U )
                        #ਜੇ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_ਮੰਜ਼ਿਲ_Wait != 0U ) ) )
                        #ਜੇ_ਅੰਤ
                        )
                    {
                        xReturn = x_ਕਤਾਰ_Semaphore_Take( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                    }
                }
            }
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_ਕਤਾਰ_Get_Mutex_Holder_Impl( ਕਤਾਰ_Handle_t xSemaphore ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_x_ਕਤਾਰ_Get_Mutex_Holder_Impl( ਕਤਾਰ_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_ਅੰਦਰੂਨੀ_Handle = ਨਿਰਾ;
            TaskHandle_t xMutexHolderTaskExternalHandle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ, l_Mutex_Holder_Task_ਸੂਚਕਾਂਕ;
            ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = pdFALSE;


            l_ਸੂਚਕਾਂਕ = ( int32_t ) xSemaphore;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                    {
                        x_Mutex_Holder_Task_ਅੰਦਰੂਨੀ_Handle = x_ਕਤਾਰ_Get_Mutex_Holder( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );

                        ਜੇ( x_Mutex_Holder_Task_ਅੰਦਰੂਨੀ_Handle != ਨਿਰਾ )
                        {
                            l_Mutex_Holder_Task_ਸੂਚਕਾਂਕ = MPU_Get_ਸੂਚਕਾਂਕ_For_Task_Handle( x_Mutex_Holder_Task_ਅੰਦਰੂਨੀ_Handle );

                            ਜੇ( l_Mutex_Holder_Task_ਸੂਚਕਾਂਕ != -1 )
                            {
                                xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_Mutex_Holder_Task_ਸੂਚਕਾਂਕ ) );
                            }
                        }
                    }
                }
            }

            ਵਾਪਸ xMutexHolderTaskExternalHandle;
        }

    #ਜੇ_ਅੰਤ /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_RECURSIVE_MUTEXES == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Take_Mutex_Recursive_Impl( ਕਤਾਰ_Handle_t xMutex,
                                                     TickType_t x_ਖੰਡ_ਸਮਾਂ ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Take_Mutex_Recursive_Impl( ਕਤਾਰ_Handle_t xMutex,
                                                     TickType_t x_ਖੰਡ_ਸਮਾਂ ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = pdFALSE;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
            UBaseType_t ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xMutex;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                    {
                        ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ = ux_ਕਤਾਰ_Get_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );

                        ਜੇ( ux_ਕਤਾਰ_ਵਸਤੂ_ਮਾਪ == 0 )
                        {
                            xReturn = x_ਕਤਾਰ_Take_Mutex_Recursive( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle, x_ਖੰਡ_ਸਮਾਂ );
                        }
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_RECURSIVE_MUTEXES == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Give_Mutex_Recursive_Impl( ਕਤਾਰ_Handle_t xMutex ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Give_Mutex_Recursive_Impl( ਕਤਾਰ_Handle_t xMutex ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = pdFALSE;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xMutex;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                    {
                        xReturn = x_ਕਤਾਰ_Give_Mutex_Recursive( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )

        ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ_Impl( ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ,
                                                            TickType_t x_ਖੰਡ_ਸਮਾਂ_Ticks ) PRIVILEGED_FUNCTION;

        ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ_Impl( ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ,
                                                            TickType_t x_ਖੰਡ_ਸਮਾਂ_Ticks ) /* PRIVILEGED_FUNCTION */
        {
            ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle = ਨਿਰਾ;
            ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_Selected_Member_ਅੰਦਰੂਨੀ = ਨਿਰਾ;
            ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t xSelectedMemberExternal = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ, l_ਸੂਚਕਾਂਕ_Selected_Member;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ_ਸੈੱਟ = pdFALSE;

            l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ = ( int32_t ) x_ਕਤਾਰ_ਸੈੱਟ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ_ਸੈੱਟ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ_ਸੈੱਟ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle = MPU_Get_ਕਤਾਰ_ਸੈੱਟ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle != ਨਿਰਾ )
                    {
                        x_Selected_Member_ਅੰਦਰੂਨੀ = x_ਕਤਾਰ_Select_From_ਸੈੱਟ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle, x_ਖੰਡ_ਸਮਾਂ_Ticks );

                        ਜੇ( x_Selected_Member_ਅੰਦਰੂਨੀ != ਨਿਰਾ )
                        {
                            l_ਸੂਚਕਾਂਕ_Selected_Member = MPU_Get_ਸੂਚਕਾਂਕ_For_ਕਤਾਰ_ਸੈੱਟ_Member_Handle( x_Selected_Member_ਅੰਦਰੂਨੀ );

                            ਜੇ( l_ਸੂਚਕਾਂਕ_Selected_Member != -1 )
                            {
                                xSelectedMemberExternal = ( ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t ) ( CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ_Selected_Member ) );
                            }
                        }
                    }
                }
            }

            ਵਾਪਸ xSelectedMemberExternal;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ_Impl( ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_ਕਤਾਰ_Or_Semaphore,
                                           ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ_Impl( ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_ਕਤਾਰ_Or_Semaphore,
                                           ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Member_Handle = ਨਿਰਾ;
            ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ, l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ_Member;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ_ਸੈੱਟ = pdFALSE;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ_ਸੈੱਟ_Member = pdFALSE;

            l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ = ( int32_t ) x_ਕਤਾਰ_ਸੈੱਟ;
            l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ_Member = ( int32_t ) x_ਕਤਾਰ_Or_Semaphore;

            ਜੇ( ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ ) != pdFALSE ) &&
                ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ_Member ) != pdFALSE ) )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ_ਸੈੱਟ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ ) );
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ_ਸੈੱਟ_Member = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ_Member ) );

                ਜੇ( ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ_ਸੈੱਟ == pdTRUE ) && ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ_ਸੈੱਟ_Member == pdTRUE ) )
                {
                    x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle = MPU_Get_ਕਤਾਰ_ਸੈੱਟ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ ) );
                    x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Member_Handle = MPU_Get_ਕਤਾਰ_ਸੈੱਟ_Member_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ_Member ) );

                    ਜੇ( ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle != ਨਿਰਾ ) && ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Member_Handle != ਨਿਰਾ ) )
                    {
                        xReturn = x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Member_Handle, x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0

        ਖਾਲੀ MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry_Impl( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                          ਅਚਲ ਅੱਖਰ * pcName ) PRIVILEGED_FUNCTION;

        ਖਾਲੀ MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry_Impl( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                          ਅਚਲ ਅੱਖਰ * pcName ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ਸੂਚਕਾਂਕ;
            ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                    {
                        v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle, pcName );
                    }
                }
            }
        }

    #ਜੇ_ਅੰਤ /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ਜੇ config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0

        ਖਾਲੀ MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ_Impl( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) PRIVILEGED_FUNCTION;

        ਖਾਲੀ MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ_Impl( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ਸੂਚਕਾਂਕ;
            ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                    {
                        v_ਕਤਾਰ_Unregister_ਕਤਾਰ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
                    }
                }
            }
        }

    #ਜੇ_ਅੰਤ /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ਜੇ config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0

        ਅਚਲ ਅੱਖਰ * MPU_pc_ਕਤਾਰ_Get_Name_Impl( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) PRIVILEGED_FUNCTION;

        ਅਚਲ ਅੱਖਰ * MPU_pc_ਕਤਾਰ_Get_Name_Impl( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* PRIVILEGED_FUNCTION */
        {
            ਅਚਲ ਅੱਖਰ * pcReturn = ਨਿਰਾ;
            ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਕਤਾਰ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                    {
                        pcReturn = pc_ਕਤਾਰ_Get_Name( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
                    }
                }
            }

            ਵਾਪਸ pcReturn;
        }

    #ਜੇ_ਅੰਤ /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Queue APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    ਖਾਲੀ MPU_v_ਕਤਾਰ_Delete( ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* PRIVILEGED_FUNCTION */
    {
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
        int32_t l_ਸੂਚਕਾਂਕ;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
            {
                v_ਕਤਾਰ_Delete( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
                MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );
            }
        }
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 ) )

        ਕਤਾਰ_Handle_t MPU_x_ਕਤਾਰ_Create_Mutex( ਅਚਲ uint8_t uc_ਕਤਾਰ_Type ) /* PRIVILEGED_FUNCTION */
        {
            ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
            ਕਤਾਰ_Handle_t x_External_ਕਤਾਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = x_ਕਤਾਰ_Create_Mutex( uc_ਕਤਾਰ_Type );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                {
                    MPU_Store_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
                    x_External_ਕਤਾਰ_Handle = ( ਕਤਾਰ_Handle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ x_External_ਕਤਾਰ_Handle;
        }

    #ਜੇ_ਅੰਤ /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_ਵੰਡ == 1 ) )

        ਕਤਾਰ_Handle_t MPU_x_ਕਤਾਰ_Create_Mutex_Static( ਅਚਲ uint8_t uc_ਕਤਾਰ_Type,
                                                   Static_ਕਤਾਰ_t * px_Static_ਕਤਾਰ ) /* PRIVILEGED_FUNCTION */
        {
            ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
            ਕਤਾਰ_Handle_t x_External_ਕਤਾਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = x_ਕਤਾਰ_Create_Mutex_Static( uc_ਕਤਾਰ_Type, px_Static_ਕਤਾਰ );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                {
                    MPU_Store_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
                    x_External_ਕਤਾਰ_Handle = ( ਕਤਾਰ_Handle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ x_External_ਕਤਾਰ_Handle;
        }

    #ਜੇ_ਅੰਤ /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 ) )

        ਕਤਾਰ_Handle_t MPU_x_ਕਤਾਰ_Create_Counting_Semaphore( UBaseType_t ux_ਗਿਣਤੀ_ਮੁੱਲ,
                                                         UBaseType_t ux_Initial_ਗਿਣਤੀ ) /* PRIVILEGED_FUNCTION */
        {
            ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
            ਕਤਾਰ_Handle_t x_External_ਕਤਾਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = x_ਕਤਾਰ_Create_Counting_Semaphore( ux_ਗਿਣਤੀ_ਮੁੱਲ, ux_Initial_ਗਿਣਤੀ );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                {
                    MPU_Store_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
                    x_External_ਕਤਾਰ_Handle = ( ਕਤਾਰ_Handle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ x_External_ਕਤਾਰ_Handle;
        }

    #ਜੇ_ਅੰਤ /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_ਵੰਡ == 1 ) )

        ਕਤਾਰ_Handle_t MPU_x_ਕਤਾਰ_Create_Counting_Semaphore_Static( ਅਚਲ UBaseType_t ux_Max_ਗਿਣਤੀ,
                                                               ਅਚਲ UBaseType_t ux_Initial_ਗਿਣਤੀ,
                                                               Static_ਕਤਾਰ_t * px_Static_ਕਤਾਰ ) /* PRIVILEGED_FUNCTION */
        {
            ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
            ਕਤਾਰ_Handle_t x_External_ਕਤਾਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = x_ਕਤਾਰ_Create_Counting_Semaphore_Static( ux_Max_ਗਿਣਤੀ, ux_Initial_ਗਿਣਤੀ, px_Static_ਕਤਾਰ );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                {
                    MPU_Store_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
                    x_External_ਕਤਾਰ_Handle = ( ਕਤਾਰ_Handle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ x_External_ਕਤਾਰ_Handle;
        }

    #ਜੇ_ਅੰਤ /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 )

        ਕਤਾਰ_Handle_t MPU_x_ਕਤਾਰ_Generic_Create( UBaseType_t ux_ਕਤਾਰ_ਲੰਮਾਈ,
                                               UBaseType_t ux_ਵਸਤੂ_ਮਾਪ,
                                               uint8_t uc_ਕਤਾਰ_Type ) /* PRIVILEGED_FUNCTION */
        {
            ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
            ਕਤਾਰ_Handle_t x_External_ਕਤਾਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = x_ਕਤਾਰ_Generic_Create( ux_ਕਤਾਰ_ਲੰਮਾਈ, ux_ਵਸਤੂ_ਮਾਪ, uc_ਕਤਾਰ_Type );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                {
                    MPU_Store_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
                    x_External_ਕਤਾਰ_Handle = ( ਕਤਾਰ_Handle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ x_External_ਕਤਾਰ_Handle;
        }

    #ਜੇ_ਅੰਤ /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_SUPPORT_STATIC_ਵੰਡ == 1 )

        ਕਤਾਰ_Handle_t MPU_x_ਕਤਾਰ_Generic_Create_Static( ਅਚਲ UBaseType_t ux_ਕਤਾਰ_ਲੰਮਾਈ,
                                                     ਅਚਲ UBaseType_t ux_ਵਸਤੂ_ਮਾਪ,
                                                     uint8_t * puc_ਕਤਾਰ_Storage,
                                                     Static_ਕਤਾਰ_t * px_Static_ਕਤਾਰ,
                                                     ਅਚਲ uint8_t uc_ਕਤਾਰ_Type ) /* PRIVILEGED_FUNCTION */
        {
            ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
            ਕਤਾਰ_Handle_t x_External_ਕਤਾਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = x_ਕਤਾਰ_Generic_Create_Static( ux_ਕਤਾਰ_ਲੰਮਾਈ, ux_ਵਸਤੂ_ਮਾਪ, puc_ਕਤਾਰ_Storage, px_Static_ਕਤਾਰ, uc_ਕਤਾਰ_Type );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                {
                    MPU_Store_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
                    x_External_ਕਤਾਰ_Handle = ( ਕਤਾਰ_Handle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ x_External_ਕਤਾਰ_Handle;
        }

    #ਜੇ_ਅੰਤ /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Generic_Reset( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                       ਅਧਾਰ_Type_t x_New_ਕਤਾਰ ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_ਸੂਚਕਾਂਕ;
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
        ਅਧਾਰ_Type_t xReturn = pdFAIL;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
            {
                xReturn = x_ਕਤਾਰ_Generic_Reset( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle, x_New_ਕਤਾਰ );
            }
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_USE_ਕਤਾਰ_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 ) )

        ਕਤਾਰ_ਸੈੱਟ_Handle_t MPU_x_ਕਤਾਰ_Create_ਸੈੱਟ( UBaseType_t ux_Event_ਕਤਾਰ_ਲੰਮਾਈ ) /* PRIVILEGED_FUNCTION */
        {
            ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle = ਨਿਰਾ;
            ਕਤਾਰ_ਸੈੱਟ_Handle_t x_External_ਕਤਾਰ_ਸੈੱਟ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle = x_ਕਤਾਰ_Create_ਸੈੱਟ( ux_Event_ਕਤਾਰ_ਲੰਮਾਈ );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle != ਨਿਰਾ )
                {
                    MPU_Store_ਕਤਾਰ_ਸੈੱਟ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle );
                    x_External_ਕਤਾਰ_ਸੈੱਟ_Handle = ( ਕਤਾਰ_ਸੈੱਟ_Handle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ x_External_ਕਤਾਰ_ਸੈੱਟ_Handle;
        }

    #ਜੇ_ਅੰਤ /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_USE_ਕਤਾਰ_SETS == 1 ) && ( config_SUPPORT_STATIC_ਵੰਡ == 1 ) )

        ਕਤਾਰ_ਸੈੱਟ_Handle_t MPU_x_ਕਤਾਰ_Create_ਸੈੱਟ_Static( ਅਚਲ UBaseType_t ux_Event_ਕਤਾਰ_ਲੰਮਾਈ,
                                                    uint8_t * puc_ਕਤਾਰ_Storage,
                                                    Static_ਕਤਾਰ_t * px_Static_ਕਤਾਰ ) /* PRIVILEGED_FUNCTION */
        {
            ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle = ਨਿਰਾ;
            ਕਤਾਰ_ਸੈੱਟ_Handle_t x_External_ਕਤਾਰ_ਸੈੱਟ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle = x_ਕਤਾਰ_Create_ਸੈੱਟ_Static( ux_Event_ਕਤਾਰ_ਲੰਮਾਈ, puc_ਕਤਾਰ_Storage, px_Static_ਕਤਾਰ );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle != ਨਿਰਾ )
                {
                    MPU_Store_ਕਤਾਰ_ਸੈੱਟ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle );
                    x_External_ਕਤਾਰ_ਸੈੱਟ_Handle = ( ਕਤਾਰ_ਸੈੱਟ_Handle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ x_External_ਕਤਾਰ_ਸੈੱਟ_Handle;
        }

    #ਜੇ_ਅੰਤ /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Remove_From_ਸੈੱਟ( ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_ਕਤਾਰ_Or_Semaphore,
                                            ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Member_Handle = ਨਿਰਾ;
            ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ, l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ_Member;

            l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ = ( int32_t ) x_ਕਤਾਰ_ਸੈੱਟ;
            l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ_Member = ( int32_t ) x_ਕਤਾਰ_Or_Semaphore;

            ਜੇ( ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ ) != pdFALSE ) &&
                ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ_Member ) != pdFALSE ) )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle = MPU_Get_ਕਤਾਰ_ਸੈੱਟ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ ) );
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Member_Handle = MPU_Get_ਕਤਾਰ_ਸੈੱਟ_Member_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ_Member ) );

                ਜੇ( ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle != ਨਿਰਾ ) && ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Member_Handle != ਨਿਰਾ ) )
                {
                    xReturn = x_ਕਤਾਰ_Remove_From_ਸੈੱਟ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Member_Handle, x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_SUPPORT_STATIC_ਵੰਡ == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Generic_Get_Static_Buffers( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                                      uint8_t ** ppuc_ਕਤਾਰ_Storage,
                                                      Static_ਕਤਾਰ_t ** ppx_Static_ਕਤਾਰ ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ਸੂਚਕਾਂਕ;
            ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;
            ਅਧਾਰ_Type_t xReturn = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
                {
                    xReturn = x_ਕਤਾਰ_Generic_Get_Static_Buffers( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle, ppuc_ਕਤਾਰ_Storage, ppx_Static_ਕਤਾਰ );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /*if ( configSUPPORT_STATIC_ALLOCATION == 1 )*/
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Generic_Send_From_ISR( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                             ਅਚਲ ਖਾਲੀ * ਅਚਲ pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ,
                                             ਅਧਾਰ_Type_t * ਅਚਲ px_Higher_ਤਰਜੀਹ_Task_Woken,
                                             ਅਚਲ ਅਧਾਰ_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        ਅਧਾਰ_Type_t xReturn = pdFAIL;
        int32_t l_ਸੂਚਕਾਂਕ;
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
            {
                xReturn = x_ਕਤਾਰ_Generic_Send_From_ISR( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle, pv_ਵਸਤੂ_ਮੰਜ਼ਿਲ_ਕਤਾਰ, px_Higher_ਤਰਜੀਹ_Task_Woken, xCopyPosition );
            }
        }

        ਵਾਪਸ xReturn;
    }

/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Give_From_ISR( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                      ਅਧਾਰ_Type_t * ਅਚਲ px_Higher_ਤਰਜੀਹ_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        ਅਧਾਰ_Type_t xReturn = pdFAIL;
        int32_t l_ਸੂਚਕਾਂਕ;
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
            {
                xReturn = x_ਕਤਾਰ_Give_From_ISR( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle, px_Higher_ਤਰਜੀਹ_Task_Woken );
            }
        }

        ਵਾਪਸ xReturn;
    }

/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Peek_From_ISR( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                      ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
    {
        ਅਧਾਰ_Type_t xReturn = pdFAIL;
        int32_t l_ਸੂਚਕਾਂਕ;
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
            {
                xReturn = x_ਕਤਾਰ_Peek_From_ISR( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle, pv_ਬਫਰ );
            }
        }

        ਵਾਪਸ xReturn;
    }

/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Receive_From_ISR( ਕਤਾਰ_Handle_t x_ਕਤਾਰ,
                                         ਖਾਲੀ * ਅਚਲ pv_ਬਫਰ,
                                         ਅਧਾਰ_Type_t * ਅਚਲ px_Higher_ਤਰਜੀਹ_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        ਅਧਾਰ_Type_t xReturn = pdFAIL;
        int32_t l_ਸੂਚਕਾਂਕ;
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
            {
                xReturn = x_ਕਤਾਰ_Receive_From_ISR( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle, pv_ਬਫਰ, px_Higher_ਤਰਜੀਹ_Task_Woken );
            }
        }

        ਵਾਪਸ xReturn;
    }

/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Is_ਕਤਾਰ_ਖਾਲੀ_ਥਾਵਾਂ_From_ISR( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* PRIVILEGED_FUNCTION */
    {
        ਅਧਾਰ_Type_t xReturn = pdFAIL;
        int32_t l_ਸੂਚਕਾਂਕ;
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
            {
                xReturn = x_ਕਤਾਰ_Is_ਕਤਾਰ_ਖਾਲੀ_ਥਾਵਾਂ_From_ISR( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
            }
        }

        ਵਾਪਸ xReturn;
    }
/*-----------------------------------------------------------*/

    ਅਧਾਰ_Type_t MPU_x_ਕਤਾਰ_Is_ਕਤਾਰ_ਭਰਿਆ_From_ISR( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* PRIVILEGED_FUNCTION */
    {
        ਅਧਾਰ_Type_t xReturn = pdFAIL;
        int32_t l_ਸੂਚਕਾਂਕ;
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
            {
                xReturn = x_ਕਤਾਰ_Is_ਕਤਾਰ_ਭਰਿਆ_From_ISR( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
            }
        }

        ਵਾਪਸ xReturn;
    }

/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ_From_ISR( ਅਚਲ ਕਤਾਰ_Handle_t x_ਕਤਾਰ ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn = 0;
        int32_t l_ਸੂਚਕਾਂਕ;
        ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = ਨਿਰਾ;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਕਤਾਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle != ਨਿਰਾ )
            {
                uxReturn = ux_ਕਤਾਰ_Messages_ਉਡੀਕ_From_ISR( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_Handle );
            }
        }

        ਵਾਪਸ uxReturn;
    }

/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_ਕਤਾਰ_Get_Mutex_Holder_From_ISR( ਕਤਾਰ_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_ਅੰਦਰੂਨੀ_Handle = ਨਿਰਾ;
            TaskHandle_t xMutexHolderTaskExternalHandle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ, l_Mutex_Holder_Task_ਸੂਚਕਾਂਕ;
            ਕਤਾਰ_Handle_t x_ਅੰਦਰੂਨੀ_Semaphore_Handle = ਨਿਰਾ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xSemaphore;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_Semaphore_Handle = MPU_Get_ਕਤਾਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Semaphore_Handle != ਨਿਰਾ )
                {
                    x_Mutex_Holder_Task_ਅੰਦਰੂਨੀ_Handle = x_ਕਤਾਰ_Get_Mutex_Holder( x_ਅੰਦਰੂਨੀ_Semaphore_Handle );

                    ਜੇ( x_Mutex_Holder_Task_ਅੰਦਰੂਨੀ_Handle != ਨਿਰਾ )
                    {
                        l_Mutex_Holder_Task_ਸੂਚਕਾਂਕ = MPU_Get_ਸੂਚਕਾਂਕ_For_Task_Handle( x_Mutex_Holder_Task_ਅੰਦਰੂਨੀ_Handle );

                        ਜੇ( l_Mutex_Holder_Task_ਸੂਚਕਾਂਕ != -1 )
                        {
                            xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_Mutex_Holder_Task_ਸੂਚਕਾਂਕ ) );
                        }
                    }
                }
            }

            ਵਾਪਸ xMutexHolderTaskExternalHandle;
        }

    #ਜੇ_ਅੰਤ /* #if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )

        ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ_From_ISR( ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਕਤਾਰ_ਸੈੱਟ ) /* PRIVILEGED_FUNCTION */
        {
            ਕਤਾਰ_ਸੈੱਟ_Handle_t x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle = ਨਿਰਾ;
            ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t x_Selected_Member_ਅੰਦਰੂਨੀ = ਨਿਰਾ;
            ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t xSelectedMemberExternal = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ, l_ਸੂਚਕਾਂਕ_Selected_Member;

            l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ = ( int32_t ) x_ਕਤਾਰ_ਸੈੱਟ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle = MPU_Get_ਕਤਾਰ_ਸੈੱਟ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ_ਕਤਾਰ_ਸੈੱਟ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle != ਨਿਰਾ )
                {
                    x_Selected_Member_ਅੰਦਰੂਨੀ = x_ਕਤਾਰ_Select_From_ਸੈੱਟ_From_ISR( x_ਅੰਦਰੂਨੀ_ਕਤਾਰ_ਸੈੱਟ_Handle );

                    ਜੇ( x_Selected_Member_ਅੰਦਰੂਨੀ != ਨਿਰਾ )
                    {
                        l_ਸੂਚਕਾਂਕ_Selected_Member = MPU_Get_ਸੂਚਕਾਂਕ_For_ਕਤਾਰ_ਸੈੱਟ_Member_Handle( x_Selected_Member_ਅੰਦਰੂਨੀ );

                        ਜੇ( l_ਸੂਚਕਾਂਕ_Selected_Member != -1 )
                        {
                            xSelectedMemberExternal = ( ਕਤਾਰ_ਸੈੱਟ_Member_Handle_t ) ( CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ_Selected_Member ) );
                        }
                    }
                }
            }

            ਵਾਪਸ xSelectedMemberExternal;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for timers APIs.                  */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਖਾਲੀ * MPU_pvTimerGetTimerIDImpl( ਅਚਲ TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ਖਾਲੀ * MPU_pvTimerGetTimerIDImpl( ਅਚਲ TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ਖਾਲੀ * pvReturn = ਨਿਰਾ;
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xTimer;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_Timer_Handle = MPU_Get_Timer_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                    {
                        pvReturn = pvTimerGetTimerID( x_ਅੰਦਰੂਨੀ_Timer_Handle );
                    }
                }
            }

            ਵਾਪਸ pvReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Timer_IDImpl( TimerHandle_t xTimer,
                                       ਖਾਲੀ * pvNewID ) PRIVILEGED_FUNCTION;

        ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Timer_IDImpl( TimerHandle_t xTimer,
                                       ਖਾਲੀ * pvNewID ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xTimer;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_Timer_Handle = MPU_Get_Timer_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                    {
                        v_Timer_ਸੈੱਟ_Timer_ID( x_ਅੰਦਰੂਨੀ_Timer_Handle, pvNewID );
                    }
                }
            }
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_Timer_Is_Timer_ਸਰਗਰਮ_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_x_Timer_Is_Timer_ਸਰਗਰਮ_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xTimer;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_Timer_Handle = MPU_Get_Timer_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                    {
                        xReturn = x_Timer_Is_Timer_ਸਰਗਰਮ( x_ਅੰਦਰੂਨੀ_Timer_Handle );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xReturn;

            xReturn = xTimerGetTimerDaemonTaskHandle();

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਅਧਾਰ_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ਅਚਲ ਅਧਾਰ_Type_t xCommandID,
                                                     ਅਚਲ TickType_t x_Optional_ਮੁੱਲ,
                                                     ਅਧਾਰ_Type_t * ਅਚਲ px_Higher_ਤਰਜੀਹ_Task_Woken,
                                                     ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            xTimerGenericCommandFromTaskParams_t xParams;

            xParams.xTimer = xTimer;
            xParams.xCommandID = xCommandID;
            xParams.x_Optional_ਮੁੱਲ = x_Optional_ਮੁੱਲ;
            xParams.px_Higher_ਤਰਜੀਹ_Task_Woken = px_Higher_ਤਰਜੀਹ_Task_Woken;
            xParams.x_Ticks_ਮੰਜ਼ਿਲ_Wait = x_Ticks_ਮੰਜ਼ਿਲ_Wait;

            xReturn = MPU_x_Timer_Generic_Command_From_Task_ਇੰਦਰਾਜ( &( xParams ) );

            ਵਾਪਸ xReturn;
        }

        ਅਧਾਰ_Type_t MPU_xTimerGenericCommandFromTaskImpl( ਅਚਲ xTimerGenericCommandFromTaskParams_t * pxParams ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_xTimerGenericCommandFromTaskImpl( ਅਚਲ xTimerGenericCommandFromTaskParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Is_Higher_ਤਰਜੀਹ_Task_Woken_Writeable = pdFALSE;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = pdFALSE;
            ਅਧਾਰ_Type_t xAreParamsReadable = pdFALSE;

            ਜੇ( pxParams != ਨਿਰਾ )
            {
                xAreParamsReadable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( pxParams,
                                                                      ਆਕਾਰ( xTimerGenericCommandFromTaskParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ਜੇ( xAreParamsReadable == pdTRUE )
            {
                ਜੇ( pxParams->xCommandID < tmr_ਪਹਿਲਾ_FROM_ISR_COMMAND )
                {
                    ਜੇ( pxParams->px_Higher_ਤਰਜੀਹ_Task_Woken != ਨਿਰਾ )
                    {
                        x_Is_Higher_ਤਰਜੀਹ_Task_Woken_Writeable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( pxParams->px_Higher_ਤਰਜੀਹ_Task_Woken,
                                                                                               ਆਕਾਰ( ਅਧਾਰ_Type_t ),
                                                                                               tskMPU_WRITE_PERMISSION );
                    }

                    ਜੇ( ( pxParams->px_Higher_ਤਰਜੀਹ_Task_Woken == ਨਿਰਾ ) ||
                        ( x_Is_Higher_ਤਰਜੀਹ_Task_Woken_Writeable == pdTRUE ) )
                    {
                        l_ਸੂਚਕਾਂਕ = ( int32_t ) ( pxParams->xTimer );

                        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                            ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer == pdTRUE )
                            {
                                x_ਅੰਦਰੂਨੀ_Timer_Handle = MPU_Get_Timer_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                                ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                                {
                                    xReturn = xTimerGenericCommandFromTask( x_ਅੰਦਰੂਨੀ_Timer_Handle,
                                                                            pxParams->xCommandID,
                                                                            pxParams->x_Optional_ਮੁੱਲ,
                                                                            pxParams->px_Higher_ਤਰਜੀਹ_Task_Woken,
                                                                            pxParams->x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                                }
                            }
                        }
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਅਚਲ ਅੱਖਰ * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ਅਚਲ ਅੱਖਰ * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ਅਚਲ ਅੱਖਰ * pcReturn = ਨਿਰਾ;
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xTimer;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_Timer_Handle = MPU_Get_Timer_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                    {
                        pcReturn = pcTimerGetName( x_ਅੰਦਰੂਨੀ_Timer_Handle );
                    }
                }
            }

            ਵਾਪਸ pcReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ_Impl( TimerHandle_t xTimer,
                                          ਅਚਲ ਅਧਾਰ_Type_t xAutoReload ) PRIVILEGED_FUNCTION;

        ਖਾਲੀ MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ_Impl( TimerHandle_t xTimer,
                                          ਅਚਲ ਅਧਾਰ_Type_t xAutoReload ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xTimer;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_Timer_Handle = MPU_Get_Timer_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                    {
                        v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ( x_ਅੰਦਰੂਨੀ_Timer_Handle, xAutoReload );
                    }
                }
            }
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_Timer_Get_Reload_ਬਹੁਲਕ_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_x_Timer_Get_Reload_ਬਹੁਲਕ_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xTimer;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_Timer_Handle = MPU_Get_Timer_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                    {
                        xReturn = x_Timer_Get_Reload_ਬਹੁਲਕ( x_ਅੰਦਰੂਨੀ_Timer_Handle );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xTimer;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_Timer_Handle = MPU_Get_Timer_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                    {
                        uxReturn = ux_Timer_Get_Reload_ਬਹੁਲਕ( x_ਅੰਦਰੂਨੀ_Timer_Handle );
                    }
                }
            }

            ਵਾਪਸ uxReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xTimer;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_Timer_Handle = MPU_Get_Timer_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                    {
                        xReturn = xTimerGetPeriod( x_ਅੰਦਰੂਨੀ_Timer_Handle );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_ਸਮਾਂ_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_x_Timer_Get_Expiry_ਸਮਾਂ_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xTimer;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Timer == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_Timer_Handle = MPU_Get_Timer_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                    {
                        xReturn = x_Timer_Get_Expiry_ਸਮਾਂ( x_ਅੰਦਰੂਨੀ_Timer_Handle );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Timer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreate( ਅਚਲ ਅੱਖਰ * ਅਚਲ pcTimerName,
                                        ਅਚਲ TickType_t x_Timer_Period_ਵਿੱਚ_Ticks,
                                        ਅਚਲ ਅਧਾਰ_Type_t xAutoReload,
                                        ਖਾਲੀ * ਅਚਲ pvTimerID,
                                        TimerCallbackFunction_t pxCallbackFunction ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            TimerHandle_t xExternalTimerHandle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                x_ਅੰਦਰੂਨੀ_Timer_Handle = xTimerCreate( pcTimerName, x_Timer_Period_ਵਿੱਚ_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                {
                    MPU_Store_Timer_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ xExternalTimerHandle;
        }

    #ਜੇ_ਅੰਤ /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_SUPPORT_STATIC_ਵੰਡ == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreateStatic( ਅਚਲ ਅੱਖਰ * ਅਚਲ pcTimerName,
                                              ਅਚਲ TickType_t x_Timer_Period_ਵਿੱਚ_Ticks,
                                              ਅਚਲ ਅਧਾਰ_Type_t xAutoReload,
                                              ਖਾਲੀ * ਅਚਲ pvTimerID,
                                              TimerCallbackFunction_t pxCallbackFunction,
                                              StaticTimer_t * px_Timer_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            TimerHandle_t xExternalTimerHandle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                x_ਅੰਦਰੂਨੀ_Timer_Handle = xTimerCreateStatic( pcTimerName, x_Timer_Period_ਵਿੱਚ_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback, px_Timer_ਬਫਰ );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                {
                    MPU_Store_Timer_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ xExternalTimerHandle;
        }

    #ਜੇ_ਅੰਤ /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_SUPPORT_STATIC_ਵੰਡ == 1 ) && ( configUSE_TIMERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_Timer_Get_Static_ਬਫਰ( TimerHandle_t xTimer,
                                              StaticTimer_t ** ppx_Timer_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t xReturn = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xTimer;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_Timer_Handle = MPU_Get_Timer_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                {
                    xReturn = x_Timer_Get_Static_ਬਫਰ( x_ਅੰਦਰੂਨੀ_Timer_Handle, ppx_Timer_ਬਫਰ );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਅਧਾਰ_Type_t MPU_xTimerGenericCommandFromISR( TimerHandle_t xTimer,
                                                    ਅਚਲ ਅਧਾਰ_Type_t xCommandID,
                                                    ਅਚਲ TickType_t x_Optional_ਮੁੱਲ,
                                                    ਅਧਾਰ_Type_t * ਅਚਲ px_Higher_ਤਰਜੀਹ_Task_Woken,
                                                    ਅਚਲ TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xTimer;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_Timer_Handle = MPU_Get_Timer_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                {
                    xReturn = xTimerGenericCommandFromISR( x_ਅੰਦਰੂਨੀ_Timer_Handle, xCommandID, x_Optional_ਮੁੱਲ, px_Higher_ਤਰਜੀਹ_Task_Woken, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_TIMERS == 1 )

        ਅਧਾਰ_Type_t MPU_xTimerDelete( TimerHandle_t xTimer, TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_ਅੰਦਰੂਨੀ_Timer_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) xTimer;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_Timer_Handle = MPU_Get_Timer_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Timer_Handle != ਨਿਰਾ )
                {
                    xReturn = xTimerGenericCommandFromTask( x_ਅੰਦਰੂਨੀ_Timer_Handle,
                                                            tmrCOMMAND_DELETE,
                                                            0U, /* xOptionalValue */
                                                            ਨਿਰਾ, /* pxHigherPriorityTaskWoken */
                                                            x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                    ਜੇ( xReturn != pdFALSE )
                    {
                        MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for event group APIs.              */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                             ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For,
                                             ਅਚਲ ਅਧਾਰ_Type_t xClearOnExit,
                                             ਅਚਲ ਅਧਾਰ_Type_t x_Wait_For_All_ਬਿੱਟ,
                                             TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ਬਿੱਟ_t xReturn = 0;
            x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Params_t xParams;

            xParams.x_Event_ਸਮੂਹ = x_Event_ਸਮੂਹ;
            xParams.ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For = ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For;
            xParams.xClearOnExit = xClearOnExit;
            xParams.x_Wait_For_All_ਬਿੱਟ = x_Wait_For_All_ਬਿੱਟ;
            xParams.x_Ticks_ਮੰਜ਼ਿਲ_Wait = x_Ticks_ਮੰਜ਼ਿਲ_Wait;

            xReturn = MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_ਇੰਦਰਾਜ( &( xParams ) );

            ਵਾਪਸ xReturn;
        }

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Impl( ਅਚਲ x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Params_t * pxParams ) PRIVILEGED_FUNCTION;

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Impl( ਅਚਲ x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Params_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            Event_ਬਿੱਟ_t xReturn = 0;
            Event_ਸਮੂਹ_Handle_t x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ = pdFALSE;
            ਅਧਾਰ_Type_t xAreParamsReadable = pdFALSE;

            ਜੇ( pxParams != ਨਿਰਾ )
            {
                xAreParamsReadable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( pxParams,
                                                                      ਆਕਾਰ( x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Params_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ਜੇ( xAreParamsReadable == pdTRUE )
            {
                ਜੇ( ( ( pxParams->ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For & event_EVENT_ਬਿੱਟ_CONTROL_ਬਾਈਟਾਂ ) == 0U ) &&
                    ( pxParams->ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For != 0U )
                    #ਜੇ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                        && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( pxParams->x_Ticks_ਮੰਜ਼ਿਲ_Wait != 0U ) ) )
                    #ਜੇ_ਅੰਤ
                    )
                {
                    l_ਸੂਚਕਾਂਕ = ( int32_t ) ( pxParams->x_Event_ਸਮੂਹ );

                    ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ == pdTRUE )
                        {
                            x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = MPU_Get_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                            ਜੇ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle != ਨਿਰਾ )
                            {
                                xReturn = x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle,
                                                               pxParams->ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For,
                                                               pxParams->xClearOnExit,
                                                               pxParams->x_Wait_For_All_ਬਿੱਟ,
                                                               pxParams->x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                            }
                        }
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ_Impl( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                                  ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) PRIVILEGED_FUNCTION;

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ_Impl( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                                  ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) /* PRIVILEGED_FUNCTION */
        {
            Event_ਬਿੱਟ_t xReturn = 0;
            Event_ਸਮੂਹ_Handle_t x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ = pdFALSE;

            ਜੇ( ( ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear & event_EVENT_ਬਿੱਟ_CONTROL_ਬਾਈਟਾਂ ) == 0U )
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Event_ਸਮੂਹ;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ == pdTRUE )
                    {
                        x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = MPU_Get_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle != ਨਿਰਾ )
                        {
                            xReturn = x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear );
                        }
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ_Impl( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                                ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ ) PRIVILEGED_FUNCTION;

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ_Impl( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                                ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ ) /* PRIVILEGED_FUNCTION */
        {
            Event_ਬਿੱਟ_t xReturn = 0;
            Event_ਸਮੂਹ_Handle_t x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ = pdFALSE;

            ਜੇ( ( ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ & event_EVENT_ਬਿੱਟ_CONTROL_ਬਾਈਟਾਂ ) == 0U )
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Event_ਸਮੂਹ;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ == pdTRUE )
                    {
                        x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = MPU_Get_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle != ਨਿਰਾ )
                        {
                            xReturn = x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ );
                        }
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Sync_Impl( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                             ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                             ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For,
                                             TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) PRIVILEGED_FUNCTION;

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Sync_Impl( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                             ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                             ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For,
                                             TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* PRIVILEGED_FUNCTION */
        {
            Event_ਬਿੱਟ_t xReturn = 0;
            Event_ਸਮੂਹ_Handle_t x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ = pdFALSE;

            ਜੇ( ( ( ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For & event_EVENT_ਬਿੱਟ_CONTROL_ਬਾਈਟਾਂ ) == 0U ) &&
                ( ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For != 0U )
                #ਜੇ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                    && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_ਮੰਜ਼ਿਲ_Wait != 0U ) ) )
                #ਜੇ_ਅੰਤ
                )
            {
                l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Event_ਸਮੂਹ;

                ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ == pdTRUE )
                    {
                        x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = MPU_Get_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle != ਨਿਰਾ )
                        {
                            xReturn = x_Event_ਸਮੂਹ_Sync( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Wait_For, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                        }
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ_Impl( ਖਾਲੀ * x_Event_ਸਮੂਹ ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ_Impl( ਖਾਲੀ * x_Event_ਸਮੂਹ ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t xReturn = 0;
            Event_ਸਮੂਹ_Handle_t x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Event_ਸਮੂਹ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = MPU_Get_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle != ਨਿਰਾ )
                    {
                        xReturn = ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        ਖਾਲੀ MPU_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ_Impl( ਖਾਲੀ * x_Event_ਸਮੂਹ,
                                           UBaseType_t ux_Event_ਸਮੂਹ_ਸੰਖਿਆ ) PRIVILEGED_FUNCTION;

        ਖਾਲੀ MPU_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ_Impl( ਖਾਲੀ * x_Event_ਸਮੂਹ,
                                           UBaseType_t ux_Event_ਸਮੂਹ_ਸੰਖਿਆ ) /* PRIVILEGED_FUNCTION */
        {
            Event_ਸਮੂਹ_Handle_t x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Event_ਸਮੂਹ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Event_ਸਮੂਹ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = MPU_Get_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle != ਨਿਰਾ )
                    {
                        v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle, ux_Event_ਸਮੂਹ_ਸੰਖਿਆ );
                    }
                }
            }
        }

    #ਜੇ_ਅੰਤ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Event Group APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_ਸਮੂਹ_Handle_t MPU_x_Event_ਸਮੂਹ_Create( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
        {
            Event_ਸਮੂਹ_Handle_t x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            Event_ਸਮੂਹ_Handle_t x_External_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = x_Event_ਸਮੂਹ_Create();

                ਜੇ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle != ਨਿਰਾ )
                {
                    MPU_Store_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle );
                    x_External_Event_ਸਮੂਹ_Handle = ( Event_ਸਮੂਹ_Handle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ x_External_Event_ਸਮੂਹ_Handle;
        }

    #ਜੇ_ਅੰਤ /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_SUPPORT_STATIC_ਵੰਡ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_ਸਮੂਹ_Handle_t MPU_x_Event_ਸਮੂਹ_Create_Static( Static_Event_ਸਮੂਹ_t * px_Event_ਸਮੂਹ_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
        {
            Event_ਸਮੂਹ_Handle_t x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            Event_ਸਮੂਹ_Handle_t x_External_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

            ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
            {
                x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = x_Event_ਸਮੂਹ_Create_Static( px_Event_ਸਮੂਹ_ਬਫਰ );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle != ਨਿਰਾ )
                {
                    MPU_Store_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle );
                    x_External_Event_ਸਮੂਹ_Handle = ( Event_ਸਮੂਹ_Handle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                }
                ਨਹੀਂਤਾਂ
                {
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                }
            }

            ਵਾਪਸ x_External_Event_ਸਮੂਹ_Handle;
        }

    #ਜੇ_ਅੰਤ /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )

        ਖਾਲੀ MPU_v_Event_ਸਮੂਹ_Delete( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ ) /* PRIVILEGED_FUNCTION */
        {
            Event_ਸਮੂਹ_Handle_t x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Event_ਸਮੂਹ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = MPU_Get_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle != ਨਿਰਾ )
                {
                    v_Event_ਸਮੂਹ_Delete( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle );
                    MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );
                }
            }
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_SUPPORT_STATIC_ਵੰਡ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        ਅਧਾਰ_Type_t MPU_x_Event_ਸਮੂਹ_Get_Static_ਬਫਰ( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                                   Static_Event_ਸਮੂਹ_t ** ppx_Event_ਸਮੂਹ_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            Event_ਸਮੂਹ_Handle_t x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Event_ਸਮੂਹ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = MPU_Get_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle != ਨਿਰਾ )
                {
                    xReturn = x_Event_ਸਮੂਹ_Get_Static_ਬਫਰ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle, ppx_Event_ਸਮੂਹ_ਬਫਰ );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        ਅਧਾਰ_Type_t MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ_From_ISR( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                                    ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            Event_ਸਮੂਹ_Handle_t x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Event_ਸਮੂਹ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = MPU_Get_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle != ਨਿਰਾ )
                {
                    xReturn = x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ_From_ISR( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_Clear );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        ਅਧਾਰ_Type_t MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ_From_ISR( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ,
                                                  ਅਚਲ Event_ਬਿੱਟ_t ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ,
                                                  ਅਧਾਰ_Type_t * px_Higher_ਤਰਜੀਹ_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            Event_ਸਮੂਹ_Handle_t x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Event_ਸਮੂਹ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = MPU_Get_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle != ਨਿਰਾ )
                {
                    xReturn = x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ_From_ISR( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle, ux_ਬਿੱਟ_ਮੰਜ਼ਿਲ_ਸੈੱਟ, px_Higher_ਤਰਜੀਹ_Task_Woken );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( configUSE_EVENT_GROUPS == 1 )

        Event_ਬਿੱਟ_t MPU_x_Event_ਸਮੂਹ_Get_ਬਿੱਟ_From_ISR( Event_ਸਮੂਹ_Handle_t x_Event_ਸਮੂਹ ) /* PRIVILEGED_FUNCTION */
        {
            Event_ਬਿੱਟ_t xReturn = 0;
            Event_ਸਮੂਹ_Handle_t x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_Event_ਸਮੂਹ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle = MPU_Get_Event_ਸਮੂਹ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle != ਨਿਰਾ )
                {
                    xReturn = x_Event_ਸਮੂਹ_Get_ਬਿੱਟ_From_ISR( x_ਅੰਦਰੂਨੀ_Event_ਸਮੂਹ_Handle );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for stream buffer APIs.            */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Send_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                          ਅਚਲ ਖਾਲੀ * pv_Tx_ਅੰਕੜੇ,
                                          size_t x_ਅੰਕੜੇ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                          TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Send_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                          ਅਚਲ ਖਾਲੀ * pv_Tx_ਅੰਕੜੇ,
                                          size_t x_ਅੰਕੜੇ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                          TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Is_Tx_ਅੰਕੜੇ_ਬਫਰ_Readable = pdFALSE;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = pdFALSE;

            ਜੇ( pv_Tx_ਅੰਕੜੇ != ਨਿਰਾ )
            {
                x_Is_Tx_ਅੰਕੜੇ_ਬਫਰ_Readable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( pv_Tx_ਅੰਕੜੇ,
                                                                           x_ਅੰਕੜੇ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                                                           tskMPU_READ_PERMISSION );

                ਜੇ( x_Is_Tx_ਅੰਕੜੇ_ਬਫਰ_Readable == pdTRUE )
                {
                    l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

                    ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ == pdTRUE )
                        {
                            x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                            ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                            {
                                xReturn = x_ਧਾਰਾ_ਬਫਰ_Send( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle, pv_Tx_ਅੰਕੜੇ, x_ਅੰਕੜੇ_ਲੰਮਾਈ_ਬਾਈਟਾਂ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                            }
                        }
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Receive_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                             ਖਾਲੀ * pv_Rx_ਅੰਕੜੇ,
                                             size_t x_ਬਫਰ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                             TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Receive_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                             ਖਾਲੀ * pv_Rx_ਅੰਕੜੇ,
                                             size_t x_ਬਫਰ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                             TickType_t x_Ticks_ਮੰਜ਼ਿਲ_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Is_Rx_ਅੰਕੜੇ_ਬਫਰ_Writeable = pdFALSE;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = pdFALSE;

            ਜੇ( pv_Rx_ਅੰਕੜੇ != ਨਿਰਾ )
            {
                x_Is_Rx_ਅੰਕੜੇ_ਬਫਰ_Writeable = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਬਫਰ( pv_Rx_ਅੰਕੜੇ,
                                                                            x_ਬਫਰ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                                                            tskMPU_WRITE_PERMISSION );

                ਜੇ( x_Is_Rx_ਅੰਕੜੇ_ਬਫਰ_Writeable == pdTRUE )
                {
                    l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

                    ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                        ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ == pdTRUE )
                        {
                            x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                            ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                            {
                                xReturn = x_ਧਾਰਾ_ਬਫਰ_Receive( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle, pv_Rx_ਅੰਕੜੇ, x_ਬਫਰ_ਲੰਮਾਈ_ਬਾਈਟਾਂ, x_Ticks_ਮੰਜ਼ਿਲ_Wait );
                            }
                        }
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                    {
                        xReturn = x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                    {
                        xReturn = x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                    {
                        xReturn = x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                    {
                        xReturn = x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                                         size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                                         size_t xTriggerLevel ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                    {
                        xReturn = x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle, xTriggerLevel );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ_Impl( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;
            ਅਧਾਰ_Type_t x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = pdFALSE;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ = x_ਪੋਰਟ_Is_Authorized_ਮੰਜ਼ਿਲ_Access_Kernel_Object( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_Calling_Task_Is_Authorized_ਮੰਜ਼ਿਲ_Access_ਧਾਰਾ_ਬਫਰ == pdTRUE )
                {
                    x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                    {
                        xReturn = x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle );
                    }
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Stream Buffer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_SUPPORT_DYNAMIC_ਵੰਡ == 1 ) && ( config_USE_ਧਾਰਾ_BUFFERS == 1 ) )

        ਧਾਰਾ_ਬਫਰ_Handle_t MPU_x_ਧਾਰਾ_ਬਫਰ_Generic_Create( size_t x_ਬਫਰ_ਮਾਪ_ਬਾਈਟਾਂ,
                                                             size_t x_Trigger_Level_ਬਾਈਟਾਂ,
                                                             ਅਧਾਰ_Type_t x_ਧਾਰਾ_ਬਫਰ_Type,
                                                             ਧਾਰਾ_ਬਫਰ_Callback_Function_t pxSendCompletedCallback,
                                                             ਧਾਰਾ_ਬਫਰ_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_External_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ਨਿਰਾ ) &&
                          ( pxReceiveCompletedCallback == ਨਿਰਾ ) );

            ਜੇ( ( pxSendCompletedCallback == ਨਿਰਾ ) &&
                ( pxReceiveCompletedCallback == ਨਿਰਾ ) )
            {
                l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

                ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
                {
                    x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = x_ਧਾਰਾ_ਬਫਰ_Generic_Create( x_ਬਫਰ_ਮਾਪ_ਬਾਈਟਾਂ,
                                                                              x_Trigger_Level_ਬਾਈਟਾਂ,
                                                                              x_ਧਾਰਾ_ਬਫਰ_Type,
                                                                              ਨਿਰਾ,
                                                                              ਨਿਰਾ );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                    {
                        MPU_Store_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle );
                        x_External_ਧਾਰਾ_ਬਫਰ_Handle = ( ਧਾਰਾ_ਬਫਰ_Handle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                    }
                    ਨਹੀਂਤਾਂ
                    {
                        MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                    }
                }
            }
            ਨਹੀਂਤਾਂ
            {
                trace_ਧਾਰਾ_ਬਫਰ_CREATE_FAILED( x_ਧਾਰਾ_ਬਫਰ_Type );
                x_External_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            }

            ਵਾਪਸ x_External_ਧਾਰਾ_ਬਫਰ_Handle;
        }

    #ਜੇ_ਅੰਤ /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_SUPPORT_STATIC_ਵੰਡ == 1 ) && ( config_USE_ਧਾਰਾ_BUFFERS == 1 ) )

        ਧਾਰਾ_ਬਫਰ_Handle_t MPU_x_ਧਾਰਾ_ਬਫਰ_Generic_Create_Static( size_t x_ਬਫਰ_ਮਾਪ_ਬਾਈਟਾਂ,
                                                                   size_t x_Trigger_Level_ਬਾਈਟਾਂ,
                                                                   ਅਧਾਰ_Type_t x_ਧਾਰਾ_ਬਫਰ_Type,
                                                                   uint8_t * ਅਚਲ puc_ਧਾਰਾ_ਬਫਰ_Storage_Area,
                                                                   Static_ਧਾਰਾ_ਬਫਰ_t * ਅਚਲ px_Static_ਧਾਰਾ_ਬਫਰ,
                                                                   ਧਾਰਾ_ਬਫਰ_Callback_Function_t pxSendCompletedCallback,
                                                                   ਧਾਰਾ_ਬਫਰ_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_External_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ਨਿਰਾ ) &&
                          ( pxReceiveCompletedCallback == ਨਿਰਾ ) );

            ਜੇ( ( pxSendCompletedCallback == ਨਿਰਾ ) &&
                ( pxReceiveCompletedCallback == ਨਿਰਾ ) )
            {
                l_ਸੂਚਕਾਂਕ = MPU_Get_Free_ਸੂਚਕਾਂਕ_ਵਿੱਚ_Kernel_Object_Pool();

                ਜੇ( l_ਸੂਚਕਾਂਕ != -1 )
                {
                    x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = x_ਧਾਰਾ_ਬਫਰ_Generic_Create_Static( x_ਬਫਰ_ਮਾਪ_ਬਾਈਟਾਂ,
                                                                                    x_Trigger_Level_ਬਾਈਟਾਂ,
                                                                                    x_ਧਾਰਾ_ਬਫਰ_Type,
                                                                                    puc_ਧਾਰਾ_ਬਫਰ_Storage_Area,
                                                                                    px_Static_ਧਾਰਾ_ਬਫਰ,
                                                                                    ਨਿਰਾ,
                                                                                    ਨਿਰਾ );

                    ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                    {
                        MPU_Store_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ, x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle );
                        x_External_ਧਾਰਾ_ਬਫਰ_Handle = ( ਧਾਰਾ_ਬਫਰ_Handle_t ) CONVERT_ਮੰਜ਼ਿਲ_EXTERNAL_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ );
                    }
                    ਨਹੀਂਤਾਂ
                    {
                        MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( l_ਸੂਚਕਾਂਕ );
                    }
                }
            }
            ਨਹੀਂਤਾਂ
            {
                trace_ਧਾਰਾ_ਬਫਰ_CREATE_STATIC_FAILED( xReturn, x_ਧਾਰਾ_ਬਫਰ_Type );
                x_External_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            }

            ਵਾਪਸ x_External_ਧਾਰਾ_ਬਫਰ_Handle;
        }

    #ਜੇ_ਅੰਤ /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        ਖਾਲੀ MPU_v_ਧਾਰਾ_ਬਫਰ_Delete( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
        {
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                {
                    v_ਧਾਰਾ_ਬਫਰ_Delete( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle );
                }

                MPU_ਸੈੱਟ_ਸੂਚਕਾਂਕ_Free_ਵਿੱਚ_Kernel_Object_Pool( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );
            }
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Reset( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                {
                    xReturn = x_ਧਾਰਾ_ਬਫਰ_Reset( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( ( config_SUPPORT_STATIC_ਵੰਡ == 1 ) && ( config_USE_ਧਾਰਾ_BUFFERS == 1 ) )

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Get_Static_Buffers( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_Buffers,
                                                      uint8_t * ppuc_ਧਾਰਾ_ਬਫਰ_Storage_Area,
                                                      Static_ਧਾਰਾ_ਬਫਰ_t * ppx_Static_ਧਾਰਾ_ਬਫਰ ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_Buffers;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                {
                    xReturn = MPU_x_ਧਾਰਾ_ਬਫਰ_Get_Static_Buffers( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle, ppuc_ਧਾਰਾ_ਬਫਰ_Storage_Area, ppx_Static_ਧਾਰਾ_ਬਫਰ );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

    size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Send_From_ISR( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                         ਅਚਲ ਖਾਲੀ * pv_Tx_ਅੰਕੜੇ,
                                         size_t x_ਅੰਕੜੇ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                         ਅਧਾਰ_Type_t * ਅਚਲ px_Higher_ਤਰਜੀਹ_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
        int32_t l_ਸੂਚਕਾਂਕ;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
            {
                xReturn = x_ਧਾਰਾ_ਬਫਰ_Send_From_ISR( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle, pv_Tx_ਅੰਕੜੇ, x_ਅੰਕੜੇ_ਲੰਮਾਈ_ਬਾਈਟਾਂ, px_Higher_ਤਰਜੀਹ_Task_Woken );
            }
        }

        ਵਾਪਸ xReturn;
    }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

    size_t MPU_x_ਧਾਰਾ_ਬਫਰ_Receive_From_ISR( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                            ਖਾਲੀ * pv_Rx_ਅੰਕੜੇ,
                                            size_t x_ਬਫਰ_ਲੰਮਾਈ_ਬਾਈਟਾਂ,
                                            ਅਧਾਰ_Type_t * ਅਚਲ px_Higher_ਤਰਜੀਹ_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
        int32_t l_ਸੂਚਕਾਂਕ;

        l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

        ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
        {
            x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

            ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
            {
                xReturn = x_ਧਾਰਾ_ਬਫਰ_Receive_From_ISR( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle, pv_Rx_ਅੰਕੜੇ, x_ਬਫਰ_ਲੰਮਾਈ_ਬਾਈਟਾਂ, px_Higher_ਤਰਜੀਹ_Task_Woken );
            }
        }

        ਵਾਪਸ xReturn;
    }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Send_Completed_From_ISR( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                                          ਅਧਾਰ_Type_t * px_Higher_ਤਰਜੀਹ_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                {
                    xReturn = x_ਧਾਰਾ_ਬਫਰ_Send_Completed_From_ISR( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle, px_Higher_ਤਰਜੀਹ_Task_Woken );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Receive_Completed_From_ISR( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ,
                                                             ਅਧਾਰ_Type_t * px_Higher_ਤਰਜੀਹ_Task_Woken ) /*PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFALSE;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                {
                    xReturn = x_ਧਾਰਾ_ਬਫਰ_Receive_Completed_From_ISR( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle, px_Higher_ਤਰਜੀਹ_Task_Woken );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

    #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )

        ਅਧਾਰ_Type_t MPU_x_ਧਾਰਾ_ਬਫਰ_Reset_From_ISR( ਧਾਰਾ_ਬਫਰ_Handle_t x_ਧਾਰਾ_ਬਫਰ ) /*PRIVILEGED_FUNCTION */
        {
            ਅਧਾਰ_Type_t xReturn = pdFAIL;
            ਧਾਰਾ_ਬਫਰ_Handle_t x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = ਨਿਰਾ;
            int32_t l_ਸੂਚਕਾਂਕ;

            l_ਸੂਚਕਾਂਕ = ( int32_t ) x_ਧਾਰਾ_ਬਫਰ;

            ਜੇ( IS_EXTERNAL_ਸੂਚਕਾਂਕ_VALID( l_ਸੂਚਕਾਂਕ ) != pdFALSE )
            {
                x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle = MPU_Get_ਧਾਰਾ_ਬਫਰ_Handle_At_ਸੂਚਕਾਂਕ( CONVERT_ਮੰਜ਼ਿਲ_ਅੰਦਰੂਨੀ_ਸੂਚਕਾਂਕ( l_ਸੂਚਕਾਂਕ ) );

                ਜੇ( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle != ਨਿਰਾ )
                {
                    xReturn = x_ਧਾਰਾ_ਬਫਰ_Reset_From_ISR( x_ਅੰਦਰੂਨੀ_ਧਾਰਾ_ਬਫਰ_Handle );
                }
            }

            ਵਾਪਸ xReturn;
        }

    #ਜੇ_ਅੰਤ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h. */

    #ਜੇ configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #ਅਨ੍ਤਰ੍ਭਾਵ "application_defined_privileged_functions.h"
    #ਜੇ_ਅੰਤ
/*-----------------------------------------------------------*/

/**
 * @brief Array of system call implementation functions.
 *
 * The index in the array MUST match the corresponding system call number
 * defined in mpu_wrappers.h.
 */
    PRIVILEGED_ਅੰਕੜੇ UBaseType_t uxSystemCallImplementations[ ਅੰਕ_SYSTEM_CALLS ] =
    {
        #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_xTaskGenericNotifyImpl,                     /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyWaitImpl,                 /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_xTimerGenericCommandFromTaskImpl,           /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_ਸਮੂਹ_Wait_ਬਿੱਟ_Impl,                    /* SYSTEM_CALL_xEventGroupWaitBits. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupWaitBits. */
        #ਜੇ_ਅੰਤ

        /* The system calls above this line take 5 parameters. */

        #ਜੇ ( INCLUDE_xTaskDelayUntil == 1 )
            ( UBaseType_t ) MPU_xTaskDelayUntilImpl,                        /* SYSTEM_CALL_xTaskDelayUntil. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskDelayUntil. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( INCLUDE_xTaskAbortDelay == 1 )
            ( UBaseType_t ) MPU_xTaskAbortDelayImpl,                        /* SYSTEM_CALL_xTaskAbortDelay. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskAbortDelay. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( INCLUDE_vTaskDelay == 1 )
            ( UBaseType_t ) MPU_vTaskDelayImpl,                             /* SYSTEM_CALL_vTaskDelay. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskDelay. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( INCLUDE_ux_Task_ਤਰਜੀਹ_Get == 1 )
            ( UBaseType_t ) MPU_ux_Task_ਤਰਜੀਹ_Get_Impl,                      /* SYSTEM_CALL_uxTaskPriorityGet. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskPriorityGet. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( INCLUDE_eTaskGetState == 1 )
            ( UBaseType_t ) MPU_eTaskGetStateImpl,                          /* SYSTEM_CALL_eTaskGetState. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_eTaskGetState. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_vTaskGetInfoImpl,                           /* SYSTEM_CALL_vTaskGetInfo. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskGetInfo. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
            ( UBaseType_t ) MPU_xTaskGetIdleTaskHandleImpl,                 /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( INCLUDE_vTaskSuspend == 1 )
            ( UBaseType_t ) MPU_vTaskSuspendImpl,                           /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) MPU_vTaskResumeImpl,                            /* SYSTEM_CALL_vTaskResume. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskResume. */
        #ਜੇ_ਅੰਤ

        ( UBaseType_t ) MPU_x_Task_Get_Tick_ਗਿਣਤੀ_Impl,                          /* SYSTEM_CALL_xTaskGetTickCount. */
        ( UBaseType_t ) MPU_ux_Task_Get_ਸੰਖਿਆ_ਦਾ_Tasks_Impl,                     /* SYSTEM_CALL_uxTaskGetNumberOfTasks. */

        #ਜੇ ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 )
            ( UBaseType_t ) MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) MPU_ul_Task_Get_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Percent_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )
            ( UBaseType_t ) MPU_v_Task_ਸੈੱਟ_Application_Task_ਟੈਗ_Impl,             /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) MPU_x_Task_Get_Application_Task_ਟੈਗ_Impl,             /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( config_ਅੰਕ_THREAD_LOCAL_STORAGE_ਸੂਚਕ_ਸਾਰੇ != 0 )
            ( UBaseType_t ) MPU_v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ_Impl,      /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) MPU_pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ_Impl,     /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_uxTaskGetSystemStateImpl,                   /* SYSTEM_CALL_uxTaskGetSystemState. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetSystemState. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( INCLUDE_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark_Impl,            /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( INCLUDE_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2 == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ਢੇਰ_ਉੱਚਾ_Water_Mark2_Impl,           /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )
            ( UBaseType_t ) MPU_xTaskGetCurrentTaskHandleImpl,              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( INCLUDE_xTaskGetSchedulerState == 1 )
            ( UBaseType_t ) MPU_xTaskGetSchedulerStateImpl,                 /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #ਜੇ_ਅੰਤ

        ( UBaseType_t ) MPU_v_Task_ਸੈੱਟ_ਸਮਾਂ_ਬਾਹਰਲਾ_State_Impl,                       /* SYSTEM_CALL_vTaskSetTimeOutState. */
        ( UBaseType_t ) MPU_x_Task_Check_For_ਸਮਾਂ_ਬਾਹਰਲਾ_Impl,                       /* SYSTEM_CALL_xTaskCheckForTimeOut. */

        #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_ulTaskGenericNotifyTakeImpl,                /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyStateClearImpl,           /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) MPU_ul_Task_Generic_Notify_ਮੁੱਲ_Clear_Impl,          /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #ਜੇ_ਅੰਤ

        ( UBaseType_t ) MPU_x_ਕਤਾਰ_Generic_Send_Impl,                          /* SYSTEM_CALL_xQueueGenericSend. */
        ( UBaseType_t ) MPU_ux_ਕਤਾਰ_Messages_ਉਡੀਕ_Impl,                     /* SYSTEM_CALL_uxQueueMessagesWaiting. */
        ( UBaseType_t ) MPU_ux_ਕਤਾਰ_Spaces_ਉਪਲਬਧ_Impl,                     /* SYSTEM_CALL_uxQueueSpacesAvailable. */
        ( UBaseType_t ) MPU_x_ਕਤਾਰ_Receive_Impl,                              /* SYSTEM_CALL_xQueueReceive. */
        ( UBaseType_t ) MPU_x_ਕਤਾਰ_Peek_Impl,                                 /* SYSTEM_CALL_xQueuePeek. */
        ( UBaseType_t ) MPU_x_ਕਤਾਰ_Semaphore_Take_Impl,                        /* SYSTEM_CALL_xQueueSemaphoreTake. */

        #ਜੇ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
            ( UBaseType_t ) MPU_x_ਕਤਾਰ_Get_Mutex_Holder_Impl,                   /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( configUSE_RECURSIVE_MUTEXES == 1 )
            ( UBaseType_t ) MPU_x_ਕਤਾਰ_Take_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) MPU_x_ਕਤਾਰ_Give_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( config_USE_ਕਤਾਰ_SETS == 1 )
            ( UBaseType_t ) MPU_x_ਕਤਾਰ_Select_From_ਸੈੱਟ_Impl,                    /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) MPU_x_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_ਸੈੱਟ_Impl,                         /* SYSTEM_CALL_xQueueAddToSet. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueAddToSet. */
        #ਜੇ_ਅੰਤ

        #ਜੇ config_ਕਤਾਰ_REGISTRY_ਮਾਪ > 0
            ( UBaseType_t ) MPU_v_ਕਤਾਰ_ਜੋੜੋ_ਮੰਜ਼ਿਲ_Registry_Impl,                    /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) MPU_v_ਕਤਾਰ_Unregister_ਕਤਾਰ_Impl,                  /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) MPU_pc_ਕਤਾਰ_Get_Name_Impl,                         /* SYSTEM_CALL_pcQueueGetName. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcQueueGetName. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_pvTimerGetTimerIDImpl,                      /* SYSTEM_CALL_pvTimerGetTimerID. */
            ( UBaseType_t ) MPU_v_Timer_ਸੈੱਟ_Timer_IDImpl,                       /* SYSTEM_CALL_vTimerSetTimerID. */
            ( UBaseType_t ) MPU_x_Timer_Is_Timer_ਸਰਗਰਮ_Impl,                    /* SYSTEM_CALL_xTimerIsTimerActive. */
            ( UBaseType_t ) MPU_xTimerGetTimerDaemonTaskHandleImpl,         /* SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle. */
            ( UBaseType_t ) MPU_pcTimerGetNameImpl,                         /* SYSTEM_CALL_pcTimerGetName. */
            ( UBaseType_t ) MPU_v_Timer_ਸੈੱਟ_Reload_ਬਹੁਲਕ_Impl,                    /* SYSTEM_CALL_vTimerSetReloadMode. */
            ( UBaseType_t ) MPU_x_Timer_Get_Reload_ਬਹੁਲਕ_Impl,                    /* SYSTEM_CALL_xTimerGetReloadMode. */
            ( UBaseType_t ) MPU_ux_Timer_Get_Reload_ਬਹੁਲਕ_Impl,                   /* SYSTEM_CALL_uxTimerGetReloadMode. */
            ( UBaseType_t ) MPU_xTimerGetPeriodImpl,                        /* SYSTEM_CALL_xTimerGetPeriod. */
            ( UBaseType_t ) MPU_x_Timer_Get_Expiry_ਸਮਾਂ_Impl,                    /* SYSTEM_CALL_xTimerGetExpiryTime. */
        #ਨਹੀਂਤਾਂ
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
        #ਜੇ_ਅੰਤ

        #ਜੇ ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_ਸਮੂਹ_Clear_ਬਿੱਟ_Impl,                   /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) MPU_x_Event_ਸਮੂਹ_ਸੈੱਟ_ਬਿੱਟ_Impl,                     /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) MPU_x_Event_ਸਮੂਹ_Sync_Impl,                        /* SYSTEM_CALL_xEventGroupSync. */

            #ਜੇ ( configUSE_TRACE_FACILITY == 1 )
                ( UBaseType_t ) MPU_ux_Event_ਸਮੂਹ_Get_ਸੰਖਿਆ_Impl,              /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) MPU_v_Event_ਸਮੂਹ_ਸੈੱਟ_ਸੰਖਿਆ_Impl,               /* SYSTEM_CALL_vEventGroupSetNumber. */
            #ਨਹੀਂਤਾਂ
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_vEventGroupSetNumber. */
            #ਜੇ_ਅੰਤ
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSync. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxEventGroupGetNumber. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vEventGroupSetNumber. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( config_USE_ਧਾਰਾ_BUFFERS == 1 )
            ( UBaseType_t ) MPU_x_ਧਾਰਾ_ਬਫਰ_Send_Impl,                      /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) MPU_x_ਧਾਰਾ_ਬਫਰ_Receive_Impl,                   /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਭਰਿਆ_Impl,                    /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) MPU_x_ਧਾਰਾ_ਬਫਰ_Is_ਖਾਲੀ_ਥਾਵਾਂ_Impl,                   /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) MPU_x_ਧਾਰਾ_ਬਫਰ_Spaces_ਉਪਲਬਧ_Impl,           /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) MPU_x_ਧਾਰਾ_ਬਫਰ_ਬਾਈਟਾਂ_ਉਪਲਬਧ_Impl,            /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) MPU_x_ਧਾਰਾ_ਬਫਰ_ਸੈੱਟ_Trigger_Level_Impl,           /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) MPU_x_ਧਾਰਾ_ਬਫਰ_ਅਗਲਾ_ਸੁਨੇਹਾ_ਲੰਮਾਈ_ਬਾਈਟਾਂ_Impl     /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #ਨਹੀਂਤਾਂ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #ਜੇ_ਅੰਤ

    };
/*-----------------------------------------------------------*/

#ਜੇ_ਅੰਤ /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/
