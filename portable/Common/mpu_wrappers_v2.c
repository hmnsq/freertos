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
#ವ್ಯಾಖ್ಯಾನಿಸು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "queue.h"
#ಅನ್ತರ್ಭಾವ "timers.h"
#ಅನ್ತರ್ಭಾವ "event_groups.h"
#ಅನ್ತರ್ಭಾವ "stream_buffer.h"
#ಅನ್ತರ್ಭಾವ "mpu_prototypes.h"
#ಅನ್ತರ್ಭಾವ "mpu_syscall_numbers.h"

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#ಆದರೆ ( ( ಪೋರ್ಟ್_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_PROTECTED_KERNEL_OBJECT_POOL_ಗಾತ್ರ
        #ದೋಷ config_PROTECTED_KERNEL_OBJECT_POOL_ಗಾತ್ರ must be defined ಗಮ್ಯ ಗರಿಷ್ಠ ಸಂಖ್ಯೆ ದ kernel objects ಒಳ the application.
    #ಆದರೆ_ಅಂತ್ಯ

/**
 * @brief Offset added to the index before returning to the user.
 *
 * If the actual handle is stored at index i, ( i + INDEX_OFFSET )
 * is returned to the user.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಸೂಚ್ಯಂಕ_ಸ್ಥಾನಾಂತರ    1

/**
 * @brief Opaque type for a kernel object.
 */
    ರಚನೆ OpaqueObject;
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ OpaqueObject * OpaqueObjectHandle_t;

/**
 * @brief Defines kernel object in the kernel object pool.
 */
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ KernelObject
    {
        OpaqueObjectHandle_t x_ಆಂತರಿಕ_Object_Handle;
        uint32_t ulKernelObjectType;
        ಶೂನ್ಯ * pv_Kernel_Object_ದತ್ತಾಂಶ;
    } KernelObject_t;

/**
 * @brief Kernel object types.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು KERNEL_OBJECT_TYPE_INVALID          ( 0UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು KERNEL_OBJECT_TYPE_ಸರತಿ            ( 1UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು KERNEL_OBJECT_TYPE_TASK             ( 2UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು KERNEL_OBJECT_TYPE_ಹರಿವು_ಬಫರ್    ( 3UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು KERNEL_OBJECT_TYPE_EVENT_ಗುಂಪು      ( 4UL )
    #ವ್ಯಾಖ್ಯಾನಿಸು KERNEL_OBJECT_TYPE_TIMER            ( 5UL )

/**
 * @brief Checks whether an external index is valid or not.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ )   \
    ( ( ( ( l_ಸೂಚ್ಯಂಕ ) >= ಸೂಚ್ಯಂಕ_ಸ್ಥಾನಾಂತರ ) &&       \
        ( ( l_ಸೂಚ್ಯಂಕ ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_ಗಾತ್ರ + ಸೂಚ್ಯಂಕ_ಸ್ಥಾನಾಂತರ ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Checks whether an internal index is valid or not.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು IS_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ )   \
    ( ( ( ( l_ಸೂಚ್ಯಂಕ ) >= 0 ) &&                  \
        ( ( l_ಸೂಚ್ಯಂಕ ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_ಗಾತ್ರ ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Converts an internal index into external.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ )    ( ( l_ಸೂಚ್ಯಂಕ ) + ಸೂಚ್ಯಂಕ_ಸ್ಥಾನಾಂತರ )

/**
 * @brief Converts an external index into internal.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ )    ( ( l_ಸೂಚ್ಯಂಕ ) - ಸೂಚ್ಯಂಕ_ಸ್ಥಾನಾಂತರ )

/**
 * @brief Max value that fits in a UBaseType_t type.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು mpuUBASETYPE_MAX    ( ~( ( UBaseType_t ) 0 ) )

/**
 * @brief Check if multiplying a and b will result in overflow.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು mpu_MULTIPLY_BASETYPE_WILL_ಅತಿಪ್ರವಾಹ( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( mpuUBASETYPE_MAX / ( a ) ) ) )

/**
 * @brief Get the index of a free slot in the kernel object pool.
 *
 * If a free slot is found, this function marks the slot as
 * "not free".
 *
 * @return Index of a free slot is returned, if a free slot is
 *         found. Otherwise -1 is returned.
 */
    ಸ್ಥಿರ int32_t MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/**
 * @brief Set the given index as free in the kernel object pool.
 *
 * @param lIndex The index to set as free.
 */
    ಸ್ಥಿರ ಶೂನ್ಯ MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( int32_t l_ಸೂಚ್ಯಂಕ ) PRIVILEGED_FUNCTION;

/**
 * @brief Get the index at which a given kernel object is stored.
 *
 * @param xHandle The given kernel object handle.
 * @param ulKernelObjectType The kernel object type.
 *
 * @return Index at which the kernel object is stored if it is a valid
 *         handle, -1 otherwise.
 */
    ಸ್ಥಿರ int32_t MPU_Get_ಸೂಚ್ಯಂಕ_For_Handle( OpaqueObjectHandle_t xHandle,
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
    ಸ್ಥಿರ ಶೂನ್ಯ MPU_Store_Handle_And_ದತ್ತಾಂಶ_At_ಸೂಚ್ಯಂಕ( int32_t l_ಸೂಚ್ಯಂಕ,
                                               OpaqueObjectHandle_t xHandle,
                                               ಶೂನ್ಯ * pv_Kernel_Object_ದತ್ತಾಂಶ,
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
    ಸ್ಥಿರ OpaqueObjectHandle_t MPU_Get_Handle_At_ಸೂಚ್ಯಂಕ( int32_t l_ಸೂಚ್ಯಂಕ,
                                                      uint32_t ulKernelObjectType ) PRIVILEGED_FUNCTION;

    #ಆದರೆ ( configUSE_TIMERS == 1 )

/**
 * @brief The function registered as callback for all the timers.
 *
 * We intercept all the timer callbacks so that we can call application
 * callbacks with opaque handle.
 *
 * @param xInternalHandle The internal timer handle.
 */
        ಸ್ಥಿರ ಶೂನ್ಯ MPU_TimerCallback( TimerHandle_t x_ಆಂತರಿಕ_Handle ) PRIVILEGED_FUNCTION;

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_TIMERS == 1 ) */

/*
 * Wrappers to keep all the casting in one place.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Store_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, xHandle )                 MPU_Store_Handle_And_ದತ್ತಾಂಶ_At_ಸೂಚ್ಯಂಕ( ( l_ಸೂಚ್ಯಂಕ ), ( OpaqueObjectHandle_t ) ( xHandle ), ಖಾಲಿ, KERNEL_OBJECT_TYPE_ಸರತಿ )
    #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ )                            ( ಸರತಿ_Handle_t ) MPU_Get_Handle_At_ಸೂಚ್ಯಂಕ( ( l_ಸೂಚ್ಯಂಕ ), KERNEL_OBJECT_TYPE_ಸರತಿ )

    #ಆದರೆ ( config_USE_ಸರತಿ_SETS == 1 )
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Store_ಸರತಿ_ಗಣ_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, xHandle )          MPU_Store_Handle_And_ದತ್ತಾಂಶ_At_ಸೂಚ್ಯಂಕ( ( l_ಸೂಚ್ಯಂಕ ), ( OpaqueObjectHandle_t ) ( xHandle ), ಖಾಲಿ, KERNEL_OBJECT_TYPE_ಸರತಿ )
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Get_ಸರತಿ_ಗಣ_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ )                     ( ಸರತಿ_ಗಣ_Handle_t ) MPU_Get_Handle_At_ಸೂಚ್ಯಂಕ( ( l_ಸೂಚ್ಯಂಕ ), KERNEL_OBJECT_TYPE_ಸರತಿ )
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Store_ಸರತಿ_ಗಣ_Member_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, xHandle )    MPU_Store_Handle_And_ದತ್ತಾಂಶ_At_ಸೂಚ್ಯಂಕ( ( l_ಸೂಚ್ಯಂಕ ), ( OpaqueObjectHandle_t ) ( xHandle ), ಖಾಲಿ, KERNEL_OBJECT_TYPE_ಸರತಿ )
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Get_ಸರತಿ_ಗಣ_Member_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ )               ( ಸರತಿ_ಗಣ_Member_Handle_t ) MPU_Get_Handle_At_ಸೂಚ್ಯಂಕ( ( l_ಸೂಚ್ಯಂಕ ), KERNEL_OBJECT_TYPE_ಸರತಿ )
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Get_ಸೂಚ್ಯಂಕ_For_ಸರತಿ_ಗಣ_Member_Handle( xHandle )             MPU_Get_ಸೂಚ್ಯಂಕ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_ಸರತಿ )
    #ಆದರೆ_ಅಂತ್ಯ

/*
 * Wrappers to keep all the casting in one place for Task APIs.
 */
    #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Store_Task_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, xHandle )            MPU_Store_Handle_And_ದತ್ತಾಂಶ_At_ಸೂಚ್ಯಂಕ( ( l_ಸೂಚ್ಯಂಕ ), ( OpaqueObjectHandle_t ) ( xHandle ), ಖಾಲಿ, KERNEL_OBJECT_TYPE_TASK )
    #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ )                       ( TaskHandle_t ) MPU_Get_Handle_At_ಸೂಚ್ಯಂಕ( ( l_ಸೂಚ್ಯಂಕ ), KERNEL_OBJECT_TYPE_TASK )
    #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Get_ಸೂಚ್ಯಂಕ_For_Task_Handle( xHandle )                     MPU_Get_ಸೂಚ್ಯಂಕ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TASK )

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )
/*
 * Wrappers to keep all the casting in one place for Event Group APIs.
 */
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Store_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, xHandle )      MPU_Store_Handle_And_ದತ್ತಾಂಶ_At_ಸೂಚ್ಯಂಕ( ( l_ಸೂಚ್ಯಂಕ ), ( OpaqueObjectHandle_t ) ( xHandle ), ಖಾಲಿ, KERNEL_OBJECT_TYPE_EVENT_ಗುಂಪು )
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Get_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ )                 ( Event_ಗುಂಪು_Handle_t ) MPU_Get_Handle_At_ಸೂಚ್ಯಂಕ( ( l_ಸೂಚ್ಯಂಕ ), KERNEL_OBJECT_TYPE_EVENT_ಗುಂಪು )
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Get_ಸೂಚ್ಯಂಕ_For_Event_ಗುಂಪು_Handle( xHandle )               MPU_Get_ಸೂಚ್ಯಂಕ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_EVENT_ಗುಂಪು )

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Stream Buffer APIs.
 */
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Store_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, xHandle )    MPU_Store_Handle_And_ದತ್ತಾಂಶ_At_ಸೂಚ್ಯಂಕ( ( l_ಸೂಚ್ಯಂಕ ), ( OpaqueObjectHandle_t ) ( xHandle), ಖಾಲಿ, KERNEL_OBJECT_TYPE_ಹರಿವು_ಬಫರ್ )
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ )               ( ಹರಿವು_ಬಫರ್_Handle_t ) MPU_Get_Handle_At_ಸೂಚ್ಯಂಕ( ( l_ಸೂಚ್ಯಂಕ ), KERNEL_OBJECT_TYPE_ಹರಿವು_ಬಫರ್ )
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Get_ಸೂಚ್ಯಂಕ_For_ಹರಿವು_ಬಫರ್_Handle( xHandle )             MPU_Get_ಸೂಚ್ಯಂಕ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_ಹರಿವು_ಬಫರ್ )

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

    #ಆದರೆ ( configUSE_TIMERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Timer APIs.
 */
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Store_Timer_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, xHandle, pxApplicationCallback )    MPU_Store_Handle_And_ದತ್ತಾಂಶ_At_ಸೂಚ್ಯಂಕ( ( l_ಸೂಚ್ಯಂಕ ), ( OpaqueObjectHandle_t ) ( xHandle ), ( ಶೂನ್ಯ * ) ( pxApplicationCallback ), KERNEL_OBJECT_TYPE_TIMER )
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Get_Timer_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ )                                      ( TimerHandle_t ) MPU_Get_Handle_At_ಸೂಚ್ಯಂಕ( ( l_ಸೂಚ್ಯಂಕ ), KERNEL_OBJECT_TYPE_TIMER )
        #ವ್ಯಾಖ್ಯಾನಿಸು MPU_Get_ಸೂಚ್ಯಂಕ_For_Timer_Handle( xHandle )                                    MPU_Get_ಸೂಚ್ಯಂಕ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TIMER )

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_TIMERS == 1 ) */

/*-----------------------------------------------------------*/

/**
 * @brief Kernel object pool.
 */
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ KernelObject_t xKernelObjectPool[ config_PROTECTED_KERNEL_OBJECT_POOL_ಗಾತ್ರ ] = { 0 };
/*-----------------------------------------------------------*/

    ಸ್ಥಿರ int32_t MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_Free_ಸೂಚ್ಯಂಕ = -1;

        /* This function is called only from resource create APIs
         * which are not supposed to be called from ISRs. Therefore,
         * we only need to suspend the scheduler and do not require
         * critical section. */
        vTaskSuspendAll();
        {
            ಗಾಗಿ( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_ಗಾತ್ರ; i++ )
            {
                ಆದರೆ( xKernelObjectPool[ i ].x_ಆಂತರಿಕ_Object_Handle == ಖಾಲಿ )
                {
                    /* Mark this index as not free. */
                    xKernelObjectPool[ i ].x_ಆಂತರಿಕ_Object_Handle = ( OpaqueObjectHandle_t ) ( ~0U );
                    l_Free_ಸೂಚ್ಯಂಕ = i;
                    ನಿಲ್ಲಿಸು;
                }
            }
        }
        ( ಶೂನ್ಯ ) xTaskResumeAll();

        ಹಿಂತಿರುಗಿ l_Free_ಸೂಚ್ಯಂಕ;
    }
/*-----------------------------------------------------------*/

    ಸ್ಥಿರ ಶೂನ್ಯ MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( int32_t l_ಸೂಚ್ಯಂಕ ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE );

        taskENTER_CRITICAL();
        {
            xKernelObjectPool[ l_ಸೂಚ್ಯಂಕ ].x_ಆಂತರಿಕ_Object_Handle = ಖಾಲಿ;
            xKernelObjectPool[ l_ಸೂಚ್ಯಂಕ ].ulKernelObjectType = KERNEL_OBJECT_TYPE_INVALID;
            xKernelObjectPool[ l_ಸೂಚ್ಯಂಕ ].pv_Kernel_Object_ದತ್ತಾಂಶ = ಖಾಲಿ;
        }
        taskEXIT_CRITICAL();
    }
/*-----------------------------------------------------------*/

    ಸ್ಥಿರ int32_t MPU_Get_ಸೂಚ್ಯಂಕ_For_Handle( OpaqueObjectHandle_t xHandle,
                                          uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_ಸೂಚ್ಯಂಕ = -1;

        configASSERT( xHandle != ಖಾಲಿ );

        ಗಾಗಿ( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_ಗಾತ್ರ; i++ )
        {
            ಆದರೆ( ( xKernelObjectPool[ i ].x_ಆಂತರಿಕ_Object_Handle == xHandle ) &&
                ( xKernelObjectPool[ i ].ulKernelObjectType == ulKernelObjectType ) )
            {
                l_ಸೂಚ್ಯಂಕ = i;
                ನಿಲ್ಲಿಸು;
            }
        }

        ಹಿಂತಿರುಗಿ l_ಸೂಚ್ಯಂಕ;
    }
/*-----------------------------------------------------------*/

    ಸ್ಥಿರ ಶೂನ್ಯ MPU_Store_Handle_And_ದತ್ತಾಂಶ_At_ಸೂಚ್ಯಂಕ( int32_t l_ಸೂಚ್ಯಂಕ,
                                               OpaqueObjectHandle_t xHandle,
                                               ಶೂನ್ಯ * pv_Kernel_Object_ದತ್ತಾಂಶ,
                                               uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE );
        xKernelObjectPool[ l_ಸೂಚ್ಯಂಕ ].x_ಆಂತರಿಕ_Object_Handle = xHandle;
        xKernelObjectPool[ l_ಸೂಚ್ಯಂಕ ].ulKernelObjectType = ulKernelObjectType;
        xKernelObjectPool[ l_ಸೂಚ್ಯಂಕ ].pv_Kernel_Object_ದತ್ತಾಂಶ = pv_Kernel_Object_ದತ್ತಾಂಶ;
    }
/*-----------------------------------------------------------*/

    ಸ್ಥಿರ OpaqueObjectHandle_t MPU_Get_Handle_At_ಸೂಚ್ಯಂಕ( int32_t l_ಸೂಚ್ಯಂಕ,
                                                      uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        OpaqueObjectHandle_t xObjectHandle = ಖಾಲಿ;

        configASSERT( IS_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE );

        ಆದರೆ( xKernelObjectPool[ l_ಸೂಚ್ಯಂಕ ].ulKernelObjectType == ulKernelObjectType )
        {
            xObjectHandle = xKernelObjectPool[ l_ಸೂಚ್ಯಂಕ ].x_ಆಂತರಿಕ_Object_Handle;
        }

        ಹಿಂತಿರುಗಿ xObjectHandle;
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ಶೂನ್ಯ v_Grant_Access_ಗಮ್ಯ_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                         int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                ಆದರೆ( xExternalTaskHandle == ಖಾಲಿ )
                {
                    v_ಪೋರ್ಟ್_Grant_Access_ಗಮ್ಯ_Kernel_Object( xExternalTaskHandle, CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( lExternalKernelObjectHandle ) );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    l_External_Task_ಸೂಚ್ಯಂಕ = ( int32_t ) xExternalTaskHandle;

                    ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_External_Task_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                    {
                        x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_External_Task_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                        {
                            v_ಪೋರ್ಟ್_Grant_Access_ಗಮ್ಯ_Kernel_Object( x_ಆಂತರಿಕ_Task_Handle,
                                                            CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        ಶೂನ್ಯ v_Revoke_Access_ಗಮ್ಯ_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                          int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                ಆದರೆ( xExternalTaskHandle == ಖಾಲಿ )
                {
                    v_ಪೋರ್ಟ್_Revoke_Access_ಗಮ್ಯ_Kernel_Object( xExternalTaskHandle, CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( lExternalKernelObjectHandle ) );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    l_External_Task_ಸೂಚ್ಯಂಕ = ( int32_t ) xExternalTaskHandle;

                    ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_External_Task_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                    {
                        x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_External_Task_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                        {
                            v_ಪೋರ್ಟ್_Revoke_Access_ಗಮ್ಯ_Kernel_Object( x_ಆಂತರಿಕ_Task_Handle,
                                                             CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ಸ್ಥಿರ ಶೂನ್ಯ MPU_TimerCallback( TimerHandle_t x_ಆಂತರಿಕ_Handle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t i, l_ಸೂಚ್ಯಂಕ = -1;
            TimerHandle_t xExternalHandle = ಖಾಲಿ;
            TimerCallbackFunction_t px_Application_Call_ಹಿಂಭಾಗ = ಖಾಲಿ;

            /* Coming from the timer task and therefore, should be valid. */
            configASSERT( x_ಆಂತರಿಕ_Handle != ಖಾಲಿ );

            ಗಾಗಿ( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_ಗಾತ್ರ; i++ )
            {
                ಆದರೆ( ( ( TimerHandle_t ) xKernelObjectPool[ i ].x_ಆಂತರಿಕ_Object_Handle == x_ಆಂತರಿಕ_Handle ) &&
                    ( xKernelObjectPool[ i ].ulKernelObjectType == KERNEL_OBJECT_TYPE_TIMER ) )
                {
                    l_ಸೂಚ್ಯಂಕ = i;
                    ನಿಲ್ಲಿಸು;
                }
            }

            configASSERT( l_ಸೂಚ್ಯಂಕ != -1 );
            xExternalHandle = ( TimerHandle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );

            px_Application_Call_ಹಿಂಭಾಗ = ( TimerCallbackFunction_t ) xKernelObjectPool[ l_ಸೂಚ್ಯಂಕ ].pv_Kernel_Object_ದತ್ತಾಂಶ;
            px_Application_Call_ಹಿಂಭಾಗ( xExternalHandle );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for tasks APIs.                   */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_xTaskDelayUntil == 1 )

        ತಳ_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ಸ್ಥಿರಾಂಕ px_ಹಿಂದಿನ_Wake_ಸಮಯ,
                                            TickType_t x_ಸಮಯ_Increment ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ಸ್ಥಿರಾಂಕ px_ಹಿಂದಿನ_Wake_ಸಮಯ,
                                            TickType_t x_ಸಮಯ_Increment ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            ತಳ_Type_t x_Is_ಹಿಂದಿನ_Wake_ಸಮಯ_Accessible = pdFALSE;

            ಆದರೆ( ( px_ಹಿಂದಿನ_Wake_ಸಮಯ != ಖಾಲಿ ) && ( x_ಸಮಯ_Increment > 0U ) )
            {
                x_Is_ಹಿಂದಿನ_Wake_ಸಮಯ_Accessible = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( px_ಹಿಂದಿನ_Wake_ಸಮಯ,
                                                                                 ಗಾತ್ರ( TickType_t ),
                                                                                 ( tskMPU_WRITE_PERMISSION | tskMPU_READ_PERMISSION ) );

                ಆದರೆ( x_Is_ಹಿಂದಿನ_Wake_ಸಮಯ_Accessible == pdTRUE )
                {
                    xReturn = xTaskDelayUntil( px_ಹಿಂದಿನ_Wake_ಸಮಯ, x_ಸಮಯ_Increment );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_xTaskAbortDelay == 1 )

        ತಳ_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                {
                    x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                    {
                        xReturn = xTaskAbortDelay( x_ಆಂತರಿಕ_Task_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_vTaskDelay == 1 )

        ಶೂನ್ಯ MPU_vTaskDelayImpl( TickType_t x_Ticks_ಗಮ್ಯ_Delay ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_vTaskDelayImpl( TickType_t x_Ticks_ಗಮ್ಯ_Delay ) /* PRIVILEGED_FUNCTION */
        {
            vTaskDelay( x_Ticks_ಗಮ್ಯ_Delay );
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_ux_Task_ಆದ್ಯತೆ_Get == 1 )

        UBaseType_t MPU_ux_Task_ಆದ್ಯತೆ_Get_Impl( ಸ್ಥಿರಾಂಕ TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_ಆದ್ಯತೆ_Get_Impl( ಸ್ಥಿರಾಂಕ TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

            ಆದರೆ( pxTask == ಖಾಲಿ )
            {
                uxReturn = ux_Task_ಆದ್ಯತೆ_Get( pxTask );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) pxTask;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                    {
                        x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                        {
                            uxReturn = ux_Task_ಆದ್ಯತೆ_Get( x_ಆಂತರಿಕ_Task_Handle );
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ uxReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            eTaskState eReturn = eInvalid;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) pxTask;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                {
                    x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                    {
                        eReturn = eTaskGetState( x_ಆಂತರಿಕ_Task_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ eReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TRACE_FACILITY == 1 )

        ಶೂನ್ಯ MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_ಸ್ಥಿತಿ_t * px_Task_ಸ್ಥಿತಿ,
                                   ತಳ_Type_t x_Get_Free_ರಾಶಿ_Space,
                                   eTaskState eState ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_ಸ್ಥಿತಿ_t * px_Task_ಸ್ಥಿತಿ,
                                   ತಳ_Type_t x_Get_Free_ರಾಶಿ_Space,
                                   eTaskState eState ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Is_Task_ಸ್ಥಿತಿ_Writeable = pdFALSE;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;

            x_Is_Task_ಸ್ಥಿತಿ_Writeable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( px_Task_ಸ್ಥಿತಿ,
                                                                      ಗಾತ್ರ( Task_ಸ್ಥಿತಿ_t ),
                                                                      tskMPU_WRITE_PERMISSION );

            ಆದರೆ( x_Is_Task_ಸ್ಥಿತಿ_Writeable == pdTRUE )
            {
                ಆದರೆ( xTask == ಖಾಲಿ )
                {
                    vTaskGetInfo( xTask, px_Task_ಸ್ಥಿತಿ, x_Get_Free_ರಾಶಿ_Space, eState );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                    ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                        {
                            x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                            ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                            {
                                vTaskGetInfo( x_ಆಂತರಿಕ_Task_Handle, px_Task_ಸ್ಥಿತಿ, x_Get_Free_ರಾಶಿ_Space, eState );
                            }
                        }
                    }
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xIdleTaskHandle = ಖಾಲಿ;

            xIdleTaskHandle = xTaskGetIdleTaskHandle();

            ಹಿಂತಿರುಗಿ xIdleTaskHandle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_vTaskSuspend == 1 )

        ಶೂನ್ಯ MPU_vTaskSuspendImpl( TaskHandle_t px_Task_ಗಮ್ಯ_Suspend ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_vTaskSuspendImpl( TaskHandle_t px_Task_ಗಮ್ಯ_Suspend ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;

            ಆದರೆ( px_Task_ಗಮ್ಯ_Suspend == ಖಾಲಿ )
            {
                vTaskSuspend( px_Task_ಗಮ್ಯ_Suspend );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                /* After the scheduler starts, only privileged tasks are allowed
                 * to suspend other tasks. */
                #ಆದರೆ ( INCLUDE_xTaskGetSchedulerState == 1 )
                    ಆದರೆ( ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) || ( ಪೋರ್ಟ್_IS_TASK_PRIVILEGED() == pdTRUE ) )
                #ಇಲ್ಲದಿದ್ದರೆ
                    ಆದರೆ( ಪೋರ್ಟ್_IS_TASK_PRIVILEGED() == pdTRUE )
                #ಆದರೆ_ಅಂತ್ಯ
                {
                    l_ಸೂಚ್ಯಂಕ = ( int32_t ) px_Task_ಗಮ್ಯ_Suspend;

                    ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                        {
                            x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                            ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                            {
                                vTaskSuspend( x_ಆಂತರಿಕ_Task_Handle );
                            }
                        }
                    }
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_vTaskSuspend == 1 )

        ಶೂನ್ಯ MPU_vTaskResumeImpl( TaskHandle_t px_Task_ಗಮ್ಯ_Resume ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_vTaskResumeImpl( TaskHandle_t px_Task_ಗಮ್ಯ_Resume ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) px_Task_ಗಮ್ಯ_Resume;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                {
                    x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                    {
                        vTaskResume( x_ಆಂತರಿಕ_Task_Handle );
                    }
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_ಎಣಿಕೆ_Impl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

    TickType_t MPU_x_Task_Get_Tick_ಎಣಿಕೆ_Impl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        TickType_t xReturn;

        xReturn = x_Task_Get_Tick_ಎಣಿಕೆ();

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks_Impl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks_Impl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn;

        uxReturn = ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks();

        ಹಿಂತಿರುಗಿ uxReturn;
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 )

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Counter_Impl( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Counter_Impl( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_ಸತತ_ಸಮಯ_COUNTER_TYPE xReturn = 0;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;

            ಆದರೆ( xTask == ಖಾಲಿ )
            {
                xReturn = ul_Task_Get_ಸತತ_ಸಮಯ_Counter( xTask );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                    {
                        x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                        {
                            xReturn = ul_Task_Get_ಸತತ_ಸಮಯ_Counter( x_ಆಂತರಿಕ_Task_Handle );
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 )

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Percent_Impl( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Percent_Impl( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_ಸತತ_ಸಮಯ_COUNTER_TYPE xReturn = 0;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;

            ಆದರೆ( xTask == ಖಾಲಿ )
            {
                xReturn = ul_Task_Get_ಸತತ_ಸಮಯ_Percent( xTask );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                    {
                        x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                        {
                            xReturn = ul_Task_Get_ಸತತ_ಸಮಯ_Percent( x_ಆಂತರಿಕ_Task_Handle );
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent_Impl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent_Impl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            config_ಸತತ_ಸಮಯ_COUNTER_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent();

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter_Impl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

        config_ಸತತ_ಸಮಯ_COUNTER_TYPE MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter_Impl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            config_ಸತತ_ಸಮಯ_COUNTER_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter();

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_APPLICATION_TASK_ಟ್ಯಾಗ್ == 1 )

        ಶೂನ್ಯ MPU_v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_ಟ್ಯಾಗ್_ಮೌಲ್ಯ ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_ಟ್ಯಾಗ್_ಮೌಲ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;

            ಆದರೆ( xTask == ಖಾಲಿ )
            {
                v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್( xTask, px_ಟ್ಯಾಗ್_ಮೌಲ್ಯ );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                    {
                        x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                        {
                            v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್( x_ಆಂತರಿಕ_Task_Handle, px_ಟ್ಯಾಗ್_ಮೌಲ್ಯ );
                        }
                    }
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_APPLICATION_TASK_ಟ್ಯಾಗ್ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ಟ್ಯಾಗ್_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ಟ್ಯಾಗ್_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;

            ಆದರೆ( xTask == ಖಾಲಿ )
            {
                xReturn = x_Task_Get_Application_Task_ಟ್ಯಾಗ್( xTask );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                    {
                        x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                        {
                            xReturn = x_Task_Get_Application_Task_ಟ್ಯಾಗ್( x_ಆಂತರಿಕ_Task_Handle );
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_ಸೂಚಕಗಳು != 0 )

        ಶೂನ್ಯ MPU_v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ_Impl( TaskHandle_t x_Task_ಗಮ್ಯ_ಗಣ,
                                                        ತಳ_Type_t x_ಸೂಚ್ಯಂಕ,
                                                        ಶೂನ್ಯ * pv_ಮೌಲ್ಯ ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ_Impl( TaskHandle_t x_Task_ಗಮ್ಯ_ಗಣ,
                                                        ತಳ_Type_t x_ಸೂಚ್ಯಂಕ,
                                                        ಶೂನ್ಯ * pv_ಮೌಲ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;

            ಆದರೆ( x_Task_ಗಮ್ಯ_ಗಣ == ಖಾಲಿ )
            {
                v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ( x_Task_ಗಮ್ಯ_ಗಣ, x_ಸೂಚ್ಯಂಕ, pv_ಮೌಲ್ಯ );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Task_ಗಮ್ಯ_ಗಣ;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                    {
                        x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                        {
                            v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ( x_ಆಂತರಿಕ_Task_Handle, x_ಸೂಚ್ಯಂಕ, pv_ಮೌಲ್ಯ );
                        }
                    }
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_ಸೂಚಕಗಳು != 0 )

        ಶೂನ್ಯ * MPU_pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ_Impl( TaskHandle_t x_Task_ಗಮ್ಯ_Query,
                                                           ತಳ_Type_t x_ಸೂಚ್ಯಂಕ ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ * MPU_pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ_Impl( TaskHandle_t x_Task_ಗಮ್ಯ_Query,
                                                           ತಳ_Type_t x_ಸೂಚ್ಯಂಕ ) /* PRIVILEGED_FUNCTION */
        {
            ಶೂನ್ಯ * pvReturn = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;

            ಆದರೆ( x_Task_ಗಮ್ಯ_Query == ಖಾಲಿ )
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ( x_Task_ಗಮ್ಯ_Query, x_ಸೂಚ್ಯಂಕ );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Task_ಗಮ್ಯ_Query;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                    {
                        x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                        {
                            pvReturn = pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ( x_ಆಂತರಿಕ_Task_Handle, x_ಸೂಚ್ಯಂಕ );
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ pvReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_ಸ್ಥಿತಿ_t * px_Task_ಸ್ಥಿತಿ_Array,
                                                  UBaseType_t ux_Array_ಗಾತ್ರ,
                                                  config_ಸತತ_ಸಮಯ_COUNTER_TYPE * pul_ಒಟ್ಟು_ಸತತ_ಸಮಯ ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_ಸ್ಥಿತಿ_t * px_Task_ಸ್ಥಿತಿ_Array,
                                                  UBaseType_t ux_Array_ಗಾತ್ರ,
                                                  config_ಸತತ_ಸಮಯ_COUNTER_TYPE * pul_ಒಟ್ಟು_ಸತತ_ಸಮಯ ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            ತಳ_Type_t x_Is_Task_ಸ್ಥಿತಿ_Array_Writeable = pdFALSE;
            ತಳ_Type_t x_Is_ಒಟ್ಟು_ಸತತ_ಸಮಯ_Writeable = pdFALSE;

            ಆದರೆ( mpu_MULTIPLY_BASETYPE_WILL_ಅತಿಪ್ರವಾಹ( ಗಾತ್ರ( Task_ಸ್ಥಿತಿ_t ), ux_Array_ಗಾತ್ರ ) == 0 )
            {
                x_Is_Task_ಸ್ಥಿತಿ_Array_Writeable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( px_Task_ಸ್ಥಿತಿ_Array,
                                                                               ಗಾತ್ರ( Task_ಸ್ಥಿತಿ_t ) * ( size_t ) ux_Array_ಗಾತ್ರ,
                                                                               tskMPU_WRITE_PERMISSION );

                ಆದರೆ( pul_ಒಟ್ಟು_ಸತತ_ಸಮಯ != ಖಾಲಿ )
                {
                    x_Is_ಒಟ್ಟು_ಸತತ_ಸಮಯ_Writeable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( pul_ಒಟ್ಟು_ಸತತ_ಸಮಯ,
                                                                                ಗಾತ್ರ( config_ಸತತ_ಸಮಯ_COUNTER_TYPE ),
                                                                                tskMPU_WRITE_PERMISSION );
                }

                ಆದರೆ( ( x_Is_Task_ಸ್ಥಿತಿ_Array_Writeable == pdTRUE ) &&
                    ( ( pul_ಒಟ್ಟು_ಸತತ_ಸಮಯ == ಖಾಲಿ ) || ( x_Is_ಒಟ್ಟು_ಸತತ_ಸಮಯ_Writeable == pdTRUE ) ) )
                {
                    uxReturn = uxTaskGetSystemState( px_Task_ಸ್ಥಿತಿ_Array, ux_Array_ಗಾತ್ರ, pul_ಒಟ್ಟು_ಸತತ_ಸಮಯ );
                }
            }

            ಹಿಂತಿರುಗಿ uxReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;

            ಆದರೆ( xTask == ಖಾಲಿ )
            {
                uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( xTask );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                    {
                        x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                        {
                            uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark( x_ಆಂತರಿಕ_Task_Handle );
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ uxReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2 == 1 )

        config_ರಾಶಿ_ಆಳ_TYPE MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_ರಾಶಿ_ಆಳ_TYPE MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_ರಾಶಿ_ಆಳ_TYPE uxReturn = 0;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;

            ಆದರೆ( xTask == ಖಾಲಿ )
            {
                uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( xTask );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                    {
                        x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                        {
                            uxReturn = ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2( x_ಆಂತರಿಕ_Task_Handle );
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ uxReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            TaskHandle_t xExternalTaskHandle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            x_ಆಂತರಿಕ_Task_Handle = xTaskGetCurrentTaskHandle();

            ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
            {
                l_ಸೂಚ್ಯಂಕ = MPU_Get_ಸೂಚ್ಯಂಕ_For_Task_Handle( x_ಆಂತರಿಕ_Task_Handle );

                ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ xExternalTaskHandle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_xTaskGetSchedulerState == 1 )

        ತಳ_Type_t MPU_xTaskGetSchedulerStateImpl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_xTaskGetSchedulerStateImpl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = taskSCHEDULER_NOT_STARTED;

            xReturn = xTaskGetSchedulerState();

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ MPU_v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State_Impl( ಸಮಯ_ಹೊರಹೋಗು_t * ಸ್ಥಿರಾಂಕ px_ಸಮಯ_ಹೊರಹೋಗು ) PRIVILEGED_FUNCTION;

    ಶೂನ್ಯ MPU_v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State_Impl( ಸಮಯ_ಹೊರಹೋಗು_t * ಸ್ಥಿರಾಂಕ px_ಸಮಯ_ಹೊರಹೋಗು ) /* PRIVILEGED_FUNCTION */
    {
        ತಳ_Type_t x_Is_ಸಮಯ_ಹೊರಹೋಗು_Writeable = pdFALSE;

        ಆದರೆ( px_ಸಮಯ_ಹೊರಹೋಗು != ಖಾಲಿ )
        {
            x_Is_ಸಮಯ_ಹೊರಹೋಗು_Writeable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( px_ಸಮಯ_ಹೊರಹೋಗು,
                                                                   ಗಾತ್ರ( ಸಮಯ_ಹೊರಹೋಗು_t ),
                                                                   tskMPU_WRITE_PERMISSION );

            ಆದರೆ( x_Is_ಸಮಯ_ಹೊರಹೋಗು_Writeable == pdTRUE )
            {
                v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State( px_ಸಮಯ_ಹೊರಹೋಗು );
            }
        }
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು_Impl( ಸಮಯ_ಹೊರಹೋಗು_t * ಸ್ಥಿರಾಂಕ px_ಸಮಯ_ಹೊರಹೋಗು,
                                             TickType_t * ಸ್ಥಿರಾಂಕ px_Ticks_ಗಮ್ಯ_Wait ) PRIVILEGED_FUNCTION;

    ತಳ_Type_t MPU_x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು_Impl( ಸಮಯ_ಹೊರಹೋಗು_t * ಸ್ಥಿರಾಂಕ px_ಸಮಯ_ಹೊರಹೋಗು,
                                             TickType_t * ಸ್ಥಿರಾಂಕ px_Ticks_ಗಮ್ಯ_Wait ) /* PRIVILEGED_FUNCTION */
    {
        ತಳ_Type_t xReturn = pdFALSE;
        ತಳ_Type_t x_Is_ಸಮಯ_ಹೊರಹೋಗು_Writeable = pdFALSE;
        ತಳ_Type_t x_Is_Ticks_ಗಮ್ಯ_Wait_Writeable = pdFALSE;

        ಆದರೆ( ( px_ಸಮಯ_ಹೊರಹೋಗು != ಖಾಲಿ ) && ( px_Ticks_ಗಮ್ಯ_Wait != ಖಾಲಿ ) )
        {
            x_Is_ಸಮಯ_ಹೊರಹೋಗು_Writeable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( px_ಸಮಯ_ಹೊರಹೋಗು,
                                                                   ಗಾತ್ರ( ಸಮಯ_ಹೊರಹೋಗು_t ),
                                                                   tskMPU_WRITE_PERMISSION );
            x_Is_Ticks_ಗಮ್ಯ_Wait_Writeable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( px_Ticks_ಗಮ್ಯ_Wait,
                                                                       ಗಾತ್ರ( TickType_t ),
                                                                       tskMPU_WRITE_PERMISSION );

            ಆದರೆ( ( x_Is_ಸಮಯ_ಹೊರಹೋಗು_Writeable == pdTRUE ) && ( x_Is_Ticks_ಗಮ್ಯ_Wait_Writeable == pdTRUE ) )
            {
                xReturn = x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು( px_ಸಮಯ_ಹೊರಹೋಗು, px_Ticks_ಗಮ್ಯ_Wait );
            }
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ತಳ_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_ಗಮ್ಯ_Notify,
                                           UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Notify,
                                           uint32_t ul_ಮೌಲ್ಯ,
                                           eNotifyAction eAction,
                                           uint32_t * pul_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyParams_t xParams;

            xParams.x_Task_ಗಮ್ಯ_Notify = x_Task_ಗಮ್ಯ_Notify;
            xParams.ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Notify = ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Notify;
            xParams.ul_ಮೌಲ್ಯ = ul_ಮೌಲ್ಯ;
            xParams.eAction = eAction;
            xParams.pul_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ = pul_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ;

            xReturn = MPU_x_Task_Generic_Notify_ನಮೂದು( &( xParams ) );

            ಹಿಂತಿರುಗಿ xReturn;
        }

        ತಳ_Type_t MPU_xTaskGenericNotifyImpl( ಸ್ಥಿರಾಂಕ xTaskGenericNotifyParams_t * pxParams ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_xTaskGenericNotifyImpl( ಸ್ಥಿರಾಂಕ xTaskGenericNotifyParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Is_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ_Writeable = pdFALSE;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;
            ತಳ_Type_t xAreParamsReadable = pdFALSE;

            ಆದರೆ( pxParams != ಖಾಲಿ )
            {
                xAreParamsReadable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( pxParams,
                                                                      ಗಾತ್ರ( xTaskGenericNotifyParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ಆದರೆ( xAreParamsReadable == pdTRUE )
            {
                ಆದರೆ( ( pxParams->ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Notify < configTASK_NOTIFICATION_ARRAY_ENTRIES ) &&
                    ( ( pxParams->eAction == eNoAction ) ||
                      ( pxParams->eAction == e_ಗಣ_ಬಿಟ್ಟುಗಳು ) ||
                      ( pxParams->eAction == eIncrement ) ||
                      ( pxParams->eAction == e_ಗಣ_ಮೌಲ್ಯ_With_Overwrite ) ||
                      ( pxParams->eAction == e_ಗಣ_ಮೌಲ್ಯ_Without_Overwrite ) ) )
                {
                    ಆದರೆ( pxParams->pul_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ != ಖಾಲಿ )
                    {
                        x_Is_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ_Writeable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( pxParams->pul_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ,
                                                                                                 ಗಾತ್ರ( uint32_t ),
                                                                                                 tskMPU_WRITE_PERMISSION );
                    }

                    ಆದರೆ( ( pxParams->pul_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ == ಖಾಲಿ ) ||
                        ( x_Is_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ_Writeable == pdTRUE ) )
                    {
                        l_ಸೂಚ್ಯಂಕ = ( int32_t ) ( pxParams->x_Task_ಗಮ್ಯ_Notify );

                        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                            ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                            {
                                x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                                ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                                {
                                    xReturn = xTaskGenericNotify( x_ಆಂತರಿಕ_Task_Handle,
                                                                  pxParams->ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Notify,
                                                                  pxParams->ul_ಮೌಲ್ಯ,
                                                                  pxParams->eAction,
                                                                  pxParams->pul_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ );
                                }
                            }
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ತಳ_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On,
                                               uint32_t ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear_On_ನಮೂದು,
                                               uint32_t ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear_On_Exit,
                                               uint32_t * pul_Notification_ಮೌಲ್ಯ,
                                               TickType_t x_Ticks_ಗಮ್ಯ_Wait )
        {
            ತಳ_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyWaitParams_t xParams;

            xParams.ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On = ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On;
            xParams.ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear_On_ನಮೂದು = ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear_On_ನಮೂದು;
            xParams.ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear_On_Exit = ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear_On_Exit;
            xParams.pul_Notification_ಮೌಲ್ಯ = pul_Notification_ಮೌಲ್ಯ;
            xParams.x_Ticks_ಗಮ್ಯ_Wait = x_Ticks_ಗಮ್ಯ_Wait;

            xReturn = MPU_x_Task_Generic_Notify_Wait_ನಮೂದು( &( xParams ) );

            ಹಿಂತಿರುಗಿ xReturn;
        }

        ತಳ_Type_t MPU_xTaskGenericNotifyWaitImpl( ಸ್ಥಿರಾಂಕ xTaskGenericNotifyWaitParams_t * pxParams ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_xTaskGenericNotifyWaitImpl( ಸ್ಥಿರಾಂಕ xTaskGenericNotifyWaitParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            ತಳ_Type_t x_Is_Notification_ಮೌಲ್ಯ_Writable = pdFALSE;
            ತಳ_Type_t xAreParamsReadable = pdFALSE;

            ಆದರೆ( pxParams != ಖಾಲಿ )
            {
                xAreParamsReadable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( pxParams,
                                                                      ಗಾತ್ರ( xTaskGenericNotifyWaitParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ಆದರೆ( xAreParamsReadable == pdTRUE )
            {
                ಆದರೆ( pxParams->ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
                {
                    ಆದರೆ( pxParams->pul_Notification_ಮೌಲ್ಯ != ಖಾಲಿ )
                    {
                        x_Is_Notification_ಮೌಲ್ಯ_Writable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( pxParams->pul_Notification_ಮೌಲ್ಯ,
                                                                                        ಗಾತ್ರ( uint32_t ),
                                                                                        tskMPU_WRITE_PERMISSION );
                    }

                    ಆದರೆ( ( pxParams->pul_Notification_ಮೌಲ್ಯ == ಖಾಲಿ ) ||
                        ( x_Is_Notification_ಮೌಲ್ಯ_Writable == pdTRUE ) )
                    {
                        xReturn = xTaskGenericNotifyWait( pxParams->ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On,
                                                          pxParams->ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear_On_ನಮೂದು,
                                                          pxParams->ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear_On_Exit,
                                                          pxParams->pul_Notification_ಮೌಲ್ಯ,
                                                          pxParams->x_Ticks_ಗಮ್ಯ_Wait );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On,
                                                  ತಳ_Type_t x_Clear_ಎಣಿಕೆ_On_Exit,
                                                  TickType_t x_Ticks_ಗಮ್ಯ_Wait ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On,
                                                  ತಳ_Type_t x_Clear_ಎಣಿಕೆ_On_Exit,
                                                  TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;

            ಆದರೆ( ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ulReturn = ulTaskGenericNotifyTake( ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Wait_On, x_Clear_ಎಣಿಕೆ_On_Exit, x_Ticks_ಗಮ್ಯ_Wait );
            }

            ಹಿಂತಿರುಗಿ ulReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ತಳ_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;

            ಆದರೆ( ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ಆದರೆ( xTask == ಖಾಲಿ )
                {
                    xReturn = xTaskGenericNotifyStateClear( xTask, ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                    ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                        {
                            x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                            ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                            {
                                xReturn = xTaskGenericNotifyStateClear( x_ಆಂತರಿಕ_Task_Handle, ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear );
                            }
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear,
                                                        uint32_t ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear,
                                                        uint32_t ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = pdFALSE;

            ಆದರೆ( ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ಆದರೆ( xTask == ಖಾಲಿ )
                {
                    ulReturn = ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( xTask, ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear, ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                    ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Task == pdTRUE )
                        {
                            x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                            ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                            {
                                ulReturn = ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear( x_ಆಂತರಿಕ_Task_Handle, ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Clear, ul_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear );
                            }
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ ulReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Task APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 )

        ತಳ_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_ಸಂಕೇತ,
                                    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ pcName,
                                    ಸ್ಥಿರಾಂಕ config_ರಾಶಿ_ಆಳ_TYPE ux_ರಾಶಿ_ಆಳ,
                                    ಶೂನ್ಯ * pvParameters,
                                    UBaseType_t ux_ಆದ್ಯತೆ,
                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                /* xTaskCreate() can only be used to create privileged tasks in MPU port. */
                ಆದರೆ( ( ux_ಆದ್ಯತೆ & ಪೋರ್ಟ್_PRIVILEGE_ಬಿಟ್ ) != 0 )
                {
                    xReturn = xTaskCreate( pv_Task_ಸಂಕೇತ, pcName, ux_ರಾಶಿ_ಆಳ, pvParameters, ux_ಆದ್ಯತೆ, &( x_ಆಂತರಿಕ_Task_Handle ) );

                    ಆದರೆ( ( xReturn == pdPASS ) && ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ ) )
                    {
                        MPU_Store_Task_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_Task_Handle );

                        ಆದರೆ( pxCreatedTask != ಖಾಲಿ )
                        {
                            *pxCreatedTask = ( TaskHandle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                        }
                    }
                    ಇಲ್ಲದಿದ್ದರೆ
                    {
                        MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 )

        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_ಸಂಕೇತ,
                                            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ pcName,
                                            ಸ್ಥಿರಾಂಕ config_ರಾಶಿ_ಆಳ_TYPE ux_ರಾಶಿ_ಆಳ,
                                            ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pvParameters,
                                            UBaseType_t ux_ಆದ್ಯತೆ,
                                            ರಾಶಿ_Type_t * ಸ್ಥಿರಾಂಕ pux_ರಾಶಿ_ಬಫರ್,
                                            StaticTask_t * ಸ್ಥಿರಾಂಕ px_Task_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xExternalTaskHandle = ಖಾಲಿ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                x_ಆಂತರಿಕ_Task_Handle = xTaskCreateStatic( px_Task_ಸಂಕೇತ, pcName, ux_ರಾಶಿ_ಆಳ, pvParameters, ux_ಆದ್ಯತೆ, pux_ರಾಶಿ_ಬಫರ್, px_Task_ಬಫರ್ );

                ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                {
                    MPU_Store_Task_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_Task_Handle );

                    #ಆದರೆ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ಆದರೆ( ( ux_ಆದ್ಯತೆ & ಪೋರ್ಟ್_PRIVILEGE_ಬಿಟ್ ) == 0 )
                        {
                            v_ಪೋರ್ಟ್_Grant_Access_ಗಮ್ಯ_Kernel_Object( x_ಆಂತರಿಕ_Task_Handle, l_ಸೂಚ್ಯಂಕ );
                        }
                    }
                    #ಆದರೆ_ಅಂತ್ಯ

                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ xExternalTaskHandle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_vTaskDelete == 1 )

        ಶೂನ್ಯ MPU_vTaskDelete( TaskHandle_t px_Task_ಗಮ್ಯ_Delete ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            ಆದರೆ( px_Task_ಗಮ್ಯ_Delete == ಖಾಲಿ )
            {
                x_ಆಂತರಿಕ_Task_Handle = xTaskGetCurrentTaskHandle();
                l_ಸೂಚ್ಯಂಕ = MPU_Get_ಸೂಚ್ಯಂಕ_For_Task_Handle( x_ಆಂತರಿಕ_Task_Handle );

                ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }

                vTaskDelete( x_ಆಂತರಿಕ_Task_Handle );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) px_Task_ಗಮ್ಯ_Delete;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                    {
                        MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );
                        vTaskDelete( x_ಆಂತರಿಕ_Task_Handle );
                    }
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/


    #ಆದರೆ ( INCLUDE_v_Task_ಆದ್ಯತೆ_ಗಣ == 1 )

        ಶೂನ್ಯ MPU_v_Task_ಆದ್ಯತೆ_ಗಣ( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_ಆದ್ಯತೆ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            ಆದರೆ( pxTask == ಖಾಲಿ )
            {
                v_Task_ಆದ್ಯತೆ_ಗಣ( pxTask, ux_New_ಆದ್ಯತೆ );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) pxTask;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                    {
                        v_Task_ಆದ್ಯತೆ_ಗಣ( x_ಆಂತರಿಕ_Task_Handle, ux_New_ಆದ್ಯತೆ );
                    }
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_xTaskGetHandle == 1 )

        TaskHandle_t MPU_xTaskGetHandle( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pc_Name_ಗಮ್ಯ_Query ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            TaskHandle_t xExternalTaskHandle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            x_ಆಂತರಿಕ_Task_Handle = xTaskGetHandle( pc_Name_ಗಮ್ಯ_Query );

            ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
            {
                l_ಸೂಚ್ಯಂಕ = MPU_Get_ಸೂಚ್ಯಂಕ_For_Task_Handle( x_ಆಂತರಿಕ_Task_Handle );

                ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ xExternalTaskHandle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/


    #ಆದರೆ ( config_USE_APPLICATION_TASK_ಟ್ಯಾಗ್ == 1 )

        ತಳ_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     ಶೂನ್ಯ * pvParameter ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

            ಆದರೆ( xTask == ಖಾಲಿ )
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                    {
                        xReturn = xTaskCallApplicationTaskHook( x_ಆಂತರಿಕ_Task_Handle, pvParameter );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 )

        ತಳ_Type_t MPU_xTaskCreateRestricted( ಸ್ಥಿರಾಂಕ TaskParameters_t * ಸ್ಥಿರಾಂಕ pxTaskDefinition,
                                              TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                xReturn = xTaskCreateRestricted( pxTaskDefinition, &( x_ಆಂತರಿಕ_Task_Handle ) );

                ಆದರೆ( ( xReturn == pdPASS ) && ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ ) )
                {
                    MPU_Store_Task_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_Task_Handle );

                    #ಆದರೆ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ಆದರೆ( ( pxTaskDefinition->ux_ಆದ್ಯತೆ & ಪೋರ್ಟ್_PRIVILEGE_ಬಿಟ್ ) == 0 )
                        {
                            v_ಪೋರ್ಟ್_Grant_Access_ಗಮ್ಯ_Kernel_Object( x_ಆಂತರಿಕ_Task_Handle, l_ಸೂಚ್ಯಂಕ );
                        }
                    }
                    #ಆದರೆ_ಅಂತ್ಯ

                    ಆದರೆ( pxCreatedTask != ಖಾಲಿ )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                    }
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 )

        ತಳ_Type_t MPU_xTaskCreateRestrictedStatic( ಸ್ಥಿರಾಂಕ TaskParameters_t * ಸ್ಥಿರಾಂಕ pxTaskDefinition,
                                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                xReturn = xTaskCreateRestrictedStatic( pxTaskDefinition, &( x_ಆಂತರಿಕ_Task_Handle ) );

                ಆದರೆ( ( xReturn == pdPASS ) && ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ ) )
                {
                    MPU_Store_Task_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_Task_Handle );

                    #ಆದರೆ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ಆದರೆ( ( pxTaskDefinition->ux_ಆದ್ಯತೆ & ಪೋರ್ಟ್_PRIVILEGE_ಬಿಟ್ ) == 0 )
                        {
                            v_ಪೋರ್ಟ್_Grant_Access_ಗಮ್ಯ_Kernel_Object( x_ಆಂತರಿಕ_Task_Handle, l_ಸೂಚ್ಯಂಕ );
                        }
                    }
                    #ಆದರೆ_ಅಂತ್ಯ

                    ಆದರೆ( pxCreatedTask != ಖಾಲಿ )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                    }
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ MPU_vTaskAllocateMPURegions( TaskHandle_t x_Task_ಗಮ್ಯ_Modify,
                                      ಸ್ಥಿರಾಂಕ ಸ್ಮರಣೆ_Region_t * ಸ್ಥಿರಾಂಕ xRegions ) /* PRIVILEGED_FUNCTION */
    {
        TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
        int32_t l_ಸೂಚ್ಯಂಕ;

        ಆದರೆ( x_Task_ಗಮ್ಯ_Modify == ಖಾಲಿ )
        {
            vTaskAllocateMPURegions( x_Task_ಗಮ್ಯ_Modify, xRegions );
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Task_ಗಮ್ಯ_Modify;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                {
                    vTaskAllocateMPURegions( x_ಆಂತರಿಕ_Task_Handle, xRegions );
                }
            }
        }
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 )

        ತಳ_Type_t MPU_xTaskGetStaticBuffers( TaskHandle_t xTask,
                                              ರಾಶಿ_Type_t ** ppux_ರಾಶಿ_ಬಫರ್,
                                              StaticTask_t ** ppx_Task_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t xReturn = pdFALSE;

            ಆದರೆ( xTask == ಖಾಲಿ )
            {
                x_ಆಂತರಿಕ_Task_Handle = xTaskGetCurrentTaskHandle();
                xReturn = xTaskGetStaticBuffers( x_ಆಂತರಿಕ_Task_Handle, ppux_ರಾಶಿ_ಬಫರ್, ppx_Task_ಬಫರ್ );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                    {
                        xReturn = xTaskGetStaticBuffers( x_ಆಂತರಿಕ_Task_Handle, ppux_ರಾಶಿ_ಬಫರ್, ppx_Task_ಬಫರ್ );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    ಅಕ್ಷರ * MPU_pcTaskGetName( TaskHandle_t x_Task_ಗಮ್ಯ_Query ) /* PRIVILEGED_FUNCTION */
    {
        ಅಕ್ಷರ * pcReturn = ಖಾಲಿ;
        int32_t l_ಸೂಚ್ಯಂಕ;
        TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

        ಆದರೆ( x_Task_ಗಮ್ಯ_Query == ಖಾಲಿ )
        {
            pcReturn = pcTaskGetName( x_Task_ಗಮ್ಯ_Query );
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Task_ಗಮ್ಯ_Query;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                {
                    pcReturn = pcTaskGetName( x_ಆಂತರಿಕ_Task_Handle );
                }
            }
        }

        ಹಿಂತಿರುಗಿ pcReturn;
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( INCLUDE_ux_Task_ಆದ್ಯತೆ_Get == 1 )

        UBaseType_t MPU_ux_Task_ಆದ್ಯತೆ_Get_From_ISR( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

            ಆದರೆ( xTask == ಖಾಲಿ )
            {
                uxReturn = ux_Task_ಆದ್ಯತೆ_Get_From_ISR( xTask );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                    {
                        uxReturn = ux_Task_ಆದ್ಯತೆ_Get_From_ISR( x_ಆಂತರಿಕ_Task_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ uxReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( INCLUDE_ux_Task_ಆದ್ಯತೆ_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_ತಳ_ಆದ್ಯತೆ_Get( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

            ಆದರೆ( xTask == ಖಾಲಿ )
            {
                uxReturn = ux_Task_ತಳ_ಆದ್ಯತೆ_Get( xTask );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                    {
                        uxReturn = ux_Task_ತಳ_ಆದ್ಯತೆ_Get( x_ಆಂತರಿಕ_Task_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ uxReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( INCLUDE_ux_Task_ಆದ್ಯತೆ_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_ತಳ_ಆದ್ಯತೆ_Get_From_ISR( ಸ್ಥಿರಾಂಕ TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

            ಆದರೆ( xTask == ಖಾಲಿ )
            {
                uxReturn = ux_Task_ತಳ_ಆದ್ಯತೆ_Get_From_ISR( xTask );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                    {
                        uxReturn = ux_Task_ತಳ_ಆದ್ಯತೆ_Get_From_ISR( x_ಆಂತರಿಕ_Task_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ uxReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

        ತಳ_Type_t MPU_xTaskResumeFromISR( TaskHandle_t x_Task_ಗಮ್ಯ_Resume ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Task_ಗಮ್ಯ_Resume;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                {
                    xReturn = xTaskResumeFromISR( x_ಆಂತರಿಕ_Task_Handle );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )*/
/*---------------------------------------------------------------------------------------*/

    #ಆದರೆ ( config_USE_APPLICATION_TASK_ಟ್ಯಾಗ್ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ಟ್ಯಾಗ್_From_ISR( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

            ಆದರೆ( xTask == ಖಾಲಿ )
            {
                xReturn = x_Task_Get_Application_Task_ಟ್ಯಾಗ್_From_ISR( xTask );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTask;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                    {
                        xReturn = x_Task_Get_Application_Task_ಟ್ಯಾಗ್_From_ISR( x_ಆಂತರಿಕ_Task_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ತಳ_Type_t MPU_xTaskGenericNotifyFromISR( TaskHandle_t x_Task_ಗಮ್ಯ_Notify,
                                                  UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Notify,
                                                  uint32_t ul_ಮೌಲ್ಯ,
                                                  eNotifyAction eAction,
                                                  uint32_t * pul_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ,
                                                  ತಳ_Type_t * px_Higher_ಆದ್ಯತೆ_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Task_ಗಮ್ಯ_Notify;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                {
                    xReturn = xTaskGenericNotifyFromISR( x_ಆಂತರಿಕ_Task_Handle, ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Notify, ul_ಮೌಲ್ಯ, eAction, pul_ಹಿಂದಿನ_Notification_ಮೌಲ್ಯ, px_Higher_ಆದ್ಯತೆ_Task_Woken );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )

        ಶೂನ್ಯ MPU_vTaskGenericNotifyGiveFromISR( TaskHandle_t x_Task_ಗಮ್ಯ_Notify,
                                                UBaseType_t ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Notify,
                                                ತಳ_Type_t * px_Higher_ಆದ್ಯತೆ_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ಸೂಚ್ಯಂಕ;
            TaskHandle_t x_ಆಂತರಿಕ_Task_Handle = ಖಾಲಿ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Task_ಗಮ್ಯ_Notify;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_Task_Handle = MPU_Get_Task_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_Task_Handle != ಖಾಲಿ )
                {
                    vTaskGenericNotifyGiveFromISR( x_ಆಂತರಿಕ_Task_Handle, ux_ಸೂಚ್ಯಂಕ_ಗಮ್ಯ_Notify, px_Higher_ಆದ್ಯತೆ_Task_Woken );
                }
            }
        }
    #ಆದರೆ_ಅಂತ್ಯ /*#if ( configUSE_TASK_NOTIFICATIONS == 1 )*/
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for queue APIs.                   */
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Generic_Send_Impl( ಸರತಿ_Handle_t x_ಸರತಿ,
                                          ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ,
                                          TickType_t x_Ticks_ಗಮ್ಯ_Wait,
                                          ತಳ_Type_t xCopyPosition ) PRIVILEGED_FUNCTION;

    ತಳ_Type_t MPU_x_ಸರತಿ_Generic_Send_Impl( ಸರತಿ_Handle_t x_ಸರತಿ,
                                          ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ,
                                          TickType_t x_Ticks_ಗಮ್ಯ_Wait,
                                          ತಳ_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_ಸೂಚ್ಯಂಕ;
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
        ತಳ_Type_t xReturn = pdFAIL;
        ತಳ_Type_t x_Is_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ_Readable = pdFALSE;
        ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = pdFALSE;
        UBaseType_t ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ, ux_ಸರತಿ_ಉದ್ದಳತೆ;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ == pdTRUE )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                {
                    ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ = ux_ಸರತಿ_Get_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ( x_ಆಂತರಿಕ_ಸರತಿ_Handle );
                    ux_ಸರತಿ_ಉದ್ದಳತೆ = ux_ಸರತಿ_Get_ಸರತಿ_ಉದ್ದಳತೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle );

                    ಆದರೆ( ( !( ( pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ == ಖಾಲಿ ) && ( ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ != ( UBaseType_t ) 0U ) ) ) &&
                        ( !( ( xCopyPosition == ಸರತಿ_OVERWRITE ) && ( ux_ಸರತಿ_ಉದ್ದಳತೆ != ( UBaseType_t ) 1U ) ) )
                        #ಆದರೆ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_ಗಮ್ಯ_Wait != 0U ) ) )
                        #ಆದರೆ_ಅಂತ್ಯ
                        )
                    {
                        ಆದರೆ( pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ != ಖಾಲಿ )
                        {
                            x_Is_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ_Readable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ,
                                                                                      ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ,
                                                                                      tskMPU_READ_PERMISSION );
                        }

                        ಆದರೆ( ( pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ == ಖಾಲಿ ) || ( x_Is_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ_Readable == pdTRUE ) )
                        {
                            xReturn = x_ಸರತಿ_Generic_Send( x_ಆಂತರಿಕ_ಸರತಿ_Handle, pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ, x_Ticks_ಗಮ್ಯ_Wait, xCopyPosition );
                        }
                    }
                }
            }
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ_Impl( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t px_ಸರತಿ ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ_Impl( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t px_ಸರತಿ ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_ಸೂಚ್ಯಂಕ;
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
        UBaseType_t uxReturn = 0;
        ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = pdFALSE;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) px_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ == pdTRUE )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                {
                    uxReturn = ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle );
                }
            }
        }

        ಹಿಂತಿರುಗಿ uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ಸರತಿ_Spaces_ಲಭ್ಯ_Impl( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t x_ಸರತಿ ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_ಸರತಿ_Spaces_ಲಭ್ಯ_Impl( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t x_ಸರತಿ ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_ಸೂಚ್ಯಂಕ;
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
        UBaseType_t uxReturn = 0;
        ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = pdFALSE;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ == pdTRUE )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                {
                    uxReturn = ux_ಸರತಿ_Spaces_ಲಭ್ಯ( x_ಆಂತರಿಕ_ಸರತಿ_Handle );
                }
            }
        }

        ಹಿಂತಿರುಗಿ uxReturn;
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Receive_Impl( ಸರತಿ_Handle_t px_ಸರತಿ,
                                      ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                                      TickType_t x_Ticks_ಗಮ್ಯ_Wait ) PRIVILEGED_FUNCTION;

    ತಳ_Type_t MPU_x_ಸರತಿ_Receive_Impl( ಸರತಿ_Handle_t px_ಸರತಿ,
                                      ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                                      TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_ಸೂಚ್ಯಂಕ;
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
        ತಳ_Type_t xReturn = pdFAIL;
        ತಳ_Type_t x_Is_Receive_ಬಫರ್_Writable = pdFALSE;
        ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = pdFALSE;
        UBaseType_t ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) px_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ == pdTRUE )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                {
                    ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ = ux_ಸರತಿ_Get_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ( x_ಆಂತರಿಕ_ಸರತಿ_Handle );

                    ಆದರೆ( ( !( ( ( pv_ಬಫರ್ ) == ಖಾಲಿ ) && ( ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ != ( UBaseType_t ) 0U ) ) )
                        #ಆದರೆ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_ಗಮ್ಯ_Wait != 0U ) ) )
                        #ಆದರೆ_ಅಂತ್ಯ
                        )
                    {
                        x_Is_Receive_ಬಫರ್_Writable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( pv_ಬಫರ್,
                                                                                    ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ,
                                                                                    tskMPU_WRITE_PERMISSION );

                        ಆದರೆ( x_Is_Receive_ಬಫರ್_Writable == pdTRUE )
                        {
                            xReturn = x_ಸರತಿ_Receive( x_ಆಂತರಿಕ_ಸರತಿ_Handle, pv_ಬಫರ್, x_Ticks_ಗಮ್ಯ_Wait );
                        }
                    }
                }
            }
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Peek_Impl( ಸರತಿ_Handle_t x_ಸರತಿ,
                                   ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                                   TickType_t x_Ticks_ಗಮ್ಯ_Wait ) PRIVILEGED_FUNCTION;

    ತಳ_Type_t MPU_x_ಸರತಿ_Peek_Impl( ಸರತಿ_Handle_t x_ಸರತಿ,
                                   ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                                   TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_ಸೂಚ್ಯಂಕ;
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
        ತಳ_Type_t xReturn = pdFAIL;
        ತಳ_Type_t x_Is_Receive_ಬಫರ್_Writable = pdFALSE;
        UBaseType_t ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ;
        ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = pdFALSE;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ == pdTRUE )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                {
                    ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ = ux_ಸರತಿ_Get_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ( x_ಆಂತರಿಕ_ಸರತಿ_Handle );

                    ಆದರೆ( ( !( ( ( pv_ಬಫರ್ ) == ಖಾಲಿ ) && ( ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ != ( UBaseType_t ) 0U ) ) )
                        #ಆದರೆ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_ಗಮ್ಯ_Wait != 0U ) ) )
                        #ಆದರೆ_ಅಂತ್ಯ
                        )
                    {
                        x_Is_Receive_ಬಫರ್_Writable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( pv_ಬಫರ್,
                                                                                    ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ,
                                                                                    tskMPU_WRITE_PERMISSION );

                        ಆದರೆ( x_Is_Receive_ಬಫರ್_Writable == pdTRUE )
                        {
                            xReturn = x_ಸರತಿ_Peek( x_ಆಂತರಿಕ_ಸರತಿ_Handle, pv_ಬಫರ್, x_Ticks_ಗಮ್ಯ_Wait );
                        }
                    }
                }
            }
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Semaphore_Take_Impl( ಸರತಿ_Handle_t x_ಸರತಿ,
                                            TickType_t x_Ticks_ಗಮ್ಯ_Wait ) PRIVILEGED_FUNCTION;

    ತಳ_Type_t MPU_x_ಸರತಿ_Semaphore_Take_Impl( ಸರತಿ_Handle_t x_ಸರತಿ,
                                            TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_ಸೂಚ್ಯಂಕ;
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
        ತಳ_Type_t xReturn = pdFAIL;
        UBaseType_t ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ;
        ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = pdFALSE;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ == pdTRUE )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                {
                    ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ = ux_ಸರತಿ_Get_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ( x_ಆಂತರಿಕ_ಸರತಿ_Handle );

                    ಆದರೆ( ( ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ == 0U )
                        #ಆದರೆ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_ಗಮ್ಯ_Wait != 0U ) ) )
                        #ಆದರೆ_ಅಂತ್ಯ
                        )
                    {
                        xReturn = x_ಸರತಿ_Semaphore_Take( x_ಆಂತರಿಕ_ಸರತಿ_Handle, x_Ticks_ಗಮ್ಯ_Wait );
                    }
                }
            }
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_ಸರತಿ_Get_Mutex_Holder_Impl( ಸರತಿ_Handle_t xSemaphore ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_x_ಸರತಿ_Get_Mutex_Holder_Impl( ಸರತಿ_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_ಆಂತರಿಕ_Handle = ಖಾಲಿ;
            TaskHandle_t xMutexHolderTaskExternalHandle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ, l_Mutex_Holder_Task_ಸೂಚ್ಯಂಕ;
            ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = pdFALSE;


            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xSemaphore;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ == pdTRUE )
                {
                    x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                    {
                        x_Mutex_Holder_Task_ಆಂತರಿಕ_Handle = x_ಸರತಿ_Get_Mutex_Holder( x_ಆಂತರಿಕ_ಸರತಿ_Handle );

                        ಆದರೆ( x_Mutex_Holder_Task_ಆಂತರಿಕ_Handle != ಖಾಲಿ )
                        {
                            l_Mutex_Holder_Task_ಸೂಚ್ಯಂಕ = MPU_Get_ಸೂಚ್ಯಂಕ_For_Task_Handle( x_Mutex_Holder_Task_ಆಂತರಿಕ_Handle );

                            ಆದರೆ( l_Mutex_Holder_Task_ಸೂಚ್ಯಂಕ != -1 )
                            {
                                xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_Mutex_Holder_Task_ಸೂಚ್ಯಂಕ ) );
                            }
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xMutexHolderTaskExternalHandle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_RECURSIVE_MUTEXES == 1 )

        ತಳ_Type_t MPU_x_ಸರತಿ_Take_Mutex_Recursive_Impl( ಸರತಿ_Handle_t xMutex,
                                                     TickType_t x_ಖಂಡ_ಸಮಯ ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_x_ಸರತಿ_Take_Mutex_Recursive_Impl( ಸರತಿ_Handle_t xMutex,
                                                     TickType_t x_ಖಂಡ_ಸಮಯ ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = pdFALSE;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
            UBaseType_t ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xMutex;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ == pdTRUE )
                {
                    x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                    {
                        ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ = ux_ಸರತಿ_Get_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ( x_ಆಂತರಿಕ_ಸರತಿ_Handle );

                        ಆದರೆ( ux_ಸರತಿ_ಅಂಶ_ಗಾತ್ರ == 0 )
                        {
                            xReturn = x_ಸರತಿ_Take_Mutex_Recursive( x_ಆಂತರಿಕ_ಸರತಿ_Handle, x_ಖಂಡ_ಸಮಯ );
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_RECURSIVE_MUTEXES == 1 )

        ತಳ_Type_t MPU_x_ಸರತಿ_Give_Mutex_Recursive_Impl( ಸರತಿ_Handle_t xMutex ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_x_ಸರತಿ_Give_Mutex_Recursive_Impl( ಸರತಿ_Handle_t xMutex ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = pdFALSE;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xMutex;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ == pdTRUE )
                {
                    x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                    {
                        xReturn = x_ಸರತಿ_Give_Mutex_Recursive( x_ಆಂತರಿಕ_ಸರತಿ_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಸರತಿ_SETS == 1 )

        ಸರತಿ_ಗಣ_Member_Handle_t MPU_x_ಸರತಿ_Select_From_ಗಣ_Impl( ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ,
                                                            TickType_t x_ಖಂಡ_ಸಮಯ_Ticks ) PRIVILEGED_FUNCTION;

        ಸರತಿ_ಗಣ_Member_Handle_t MPU_x_ಸರತಿ_Select_From_ಗಣ_Impl( ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ,
                                                            TickType_t x_ಖಂಡ_ಸಮಯ_Ticks ) /* PRIVILEGED_FUNCTION */
        {
            ಸರತಿ_ಗಣ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle = ಖಾಲಿ;
            ಸರತಿ_ಗಣ_Member_Handle_t x_Selected_Member_ಆಂತರಿಕ = ಖಾಲಿ;
            ಸರತಿ_ಗಣ_Member_Handle_t xSelectedMemberExternal = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ, l_ಸೂಚ್ಯಂಕ_Selected_Member;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ_ಗಣ = pdFALSE;

            l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ = ( int32_t ) x_ಸರತಿ_ಗಣ;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ_ಗಣ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ_ಗಣ == pdTRUE )
                {
                    x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle = MPU_Get_ಸರತಿ_ಗಣ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle != ಖಾಲಿ )
                    {
                        x_Selected_Member_ಆಂತರಿಕ = x_ಸರತಿ_Select_From_ಗಣ( x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle, x_ಖಂಡ_ಸಮಯ_Ticks );

                        ಆದರೆ( x_Selected_Member_ಆಂತರಿಕ != ಖಾಲಿ )
                        {
                            l_ಸೂಚ್ಯಂಕ_Selected_Member = MPU_Get_ಸೂಚ್ಯಂಕ_For_ಸರತಿ_ಗಣ_Member_Handle( x_Selected_Member_ಆಂತರಿಕ );

                            ಆದರೆ( l_ಸೂಚ್ಯಂಕ_Selected_Member != -1 )
                            {
                                xSelectedMemberExternal = ( ಸರತಿ_ಗಣ_Member_Handle_t ) ( CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ_Selected_Member ) );
                            }
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xSelectedMemberExternal;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಸರತಿ_SETS == 1 )

        ತಳ_Type_t MPU_x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ_Impl( ಸರತಿ_ಗಣ_Member_Handle_t x_ಸರತಿ_Or_Semaphore,
                                           ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ_Impl( ಸರತಿ_ಗಣ_Member_Handle_t x_ಸರತಿ_Or_Semaphore,
                                           ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            ಸರತಿ_ಗಣ_Member_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Member_Handle = ಖಾಲಿ;
            ಸರತಿ_ಗಣ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ, l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ_Member;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ_ಗಣ = pdFALSE;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ_ಗಣ_Member = pdFALSE;

            l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ = ( int32_t ) x_ಸರತಿ_ಗಣ;
            l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ_Member = ( int32_t ) x_ಸರತಿ_Or_Semaphore;

            ಆದರೆ( ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ ) != pdFALSE ) &&
                ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ_Member ) != pdFALSE ) )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ_ಗಣ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ ) );
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ_ಗಣ_Member = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ_Member ) );

                ಆದರೆ( ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ_ಗಣ == pdTRUE ) && ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ_ಗಣ_Member == pdTRUE ) )
                {
                    x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle = MPU_Get_ಸರತಿ_ಗಣ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ ) );
                    x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Member_Handle = MPU_Get_ಸರತಿ_ಗಣ_Member_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ_Member ) );

                    ಆದರೆ( ( x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle != ಖಾಲಿ ) && ( x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Member_Handle != ಖಾಲಿ ) )
                    {
                        xReturn = x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ( x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Member_Handle, x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ config_ಸರತಿ_REGISTRY_ಗಾತ್ರ > 0

        ಶೂನ್ಯ MPU_v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry_Impl( ಸರತಿ_Handle_t x_ಸರತಿ,
                                          ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pcName ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry_Impl( ಸರತಿ_Handle_t x_ಸರತಿ,
                                          ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pcName ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ಸೂಚ್ಯಂಕ;
            ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ == pdTRUE )
                {
                    x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                    {
                        v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry( x_ಆಂತರಿಕ_ಸರತಿ_Handle, pcName );
                    }
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ಆದರೆ config_ಸರತಿ_REGISTRY_ಗಾತ್ರ > 0

        ಶೂನ್ಯ MPU_v_ಸರತಿ_Unregister_ಸರತಿ_Impl( ಸರತಿ_Handle_t x_ಸರತಿ ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_v_ಸರತಿ_Unregister_ಸರತಿ_Impl( ಸರತಿ_Handle_t x_ಸರತಿ ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ಸೂಚ್ಯಂಕ;
            ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ == pdTRUE )
                {
                    x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                    {
                        v_ಸರತಿ_Unregister_ಸರತಿ( x_ಆಂತರಿಕ_ಸರತಿ_Handle );
                    }
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ಆದರೆ config_ಸರತಿ_REGISTRY_ಗಾತ್ರ > 0

        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * MPU_pc_ಸರತಿ_Get_Name_Impl( ಸರತಿ_Handle_t x_ಸರತಿ ) PRIVILEGED_FUNCTION;

        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * MPU_pc_ಸರತಿ_Get_Name_Impl( ಸರತಿ_Handle_t x_ಸರತಿ ) /* PRIVILEGED_FUNCTION */
        {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pcReturn = ಖಾಲಿ;
            ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಸರತಿ == pdTRUE )
                {
                    x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                    {
                        pcReturn = pc_ಸರತಿ_Get_Name( x_ಆಂತರಿಕ_ಸರತಿ_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ pcReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Queue APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    ಶೂನ್ಯ MPU_v_ಸರತಿ_Delete( ಸರತಿ_Handle_t x_ಸರತಿ ) /* PRIVILEGED_FUNCTION */
    {
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
        int32_t l_ಸೂಚ್ಯಂಕ;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
            {
                v_ಸರತಿ_Delete( x_ಆಂತರಿಕ_ಸರತಿ_Handle );
                MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );
            }
        }
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 ) )

        ಸರತಿ_Handle_t MPU_x_ಸರತಿ_Create_Mutex( ಸ್ಥಿರಾಂಕ uint8_t uc_ಸರತಿ_Type ) /* PRIVILEGED_FUNCTION */
        {
            ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
            ಸರತಿ_Handle_t x_External_ಸರತಿ_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_Handle = x_ಸರತಿ_Create_Mutex( uc_ಸರತಿ_Type );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                {
                    MPU_Store_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_ಸರತಿ_Handle );
                    x_External_ಸರತಿ_Handle = ( ಸರತಿ_Handle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ x_External_ಸರತಿ_Handle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 ) )

        ಸರತಿ_Handle_t MPU_x_ಸರತಿ_Create_Mutex_Static( ಸ್ಥಿರಾಂಕ uint8_t uc_ಸರತಿ_Type,
                                                   Static_ಸರತಿ_t * px_Static_ಸರತಿ ) /* PRIVILEGED_FUNCTION */
        {
            ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
            ಸರತಿ_Handle_t x_External_ಸರತಿ_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_Handle = x_ಸರತಿ_Create_Mutex_Static( uc_ಸರತಿ_Type, px_Static_ಸರತಿ );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                {
                    MPU_Store_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_ಸರತಿ_Handle );
                    x_External_ಸರತಿ_Handle = ( ಸರತಿ_Handle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ x_External_ಸರತಿ_Handle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 ) )

        ಸರತಿ_Handle_t MPU_x_ಸರತಿ_Create_Counting_Semaphore( UBaseType_t ux_ಎಣಿಕೆ_ಮೌಲ್ಯ,
                                                         UBaseType_t ux_Initial_ಎಣಿಕೆ ) /* PRIVILEGED_FUNCTION */
        {
            ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
            ಸರತಿ_Handle_t x_External_ಸರತಿ_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_Handle = x_ಸರತಿ_Create_Counting_Semaphore( ux_ಎಣಿಕೆ_ಮೌಲ್ಯ, ux_Initial_ಎಣಿಕೆ );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                {
                    MPU_Store_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_ಸರತಿ_Handle );
                    x_External_ಸರತಿ_Handle = ( ಸರತಿ_Handle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ x_External_ಸರತಿ_Handle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 ) )

        ಸರತಿ_Handle_t MPU_x_ಸರತಿ_Create_Counting_Semaphore_Static( ಸ್ಥಿರಾಂಕ UBaseType_t ux_Max_ಎಣಿಕೆ,
                                                               ಸ್ಥಿರಾಂಕ UBaseType_t ux_Initial_ಎಣಿಕೆ,
                                                               Static_ಸರತಿ_t * px_Static_ಸರತಿ ) /* PRIVILEGED_FUNCTION */
        {
            ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
            ಸರತಿ_Handle_t x_External_ಸರತಿ_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_Handle = x_ಸರತಿ_Create_Counting_Semaphore_Static( ux_Max_ಎಣಿಕೆ, ux_Initial_ಎಣಿಕೆ, px_Static_ಸರತಿ );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                {
                    MPU_Store_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_ಸರತಿ_Handle );
                    x_External_ಸರತಿ_Handle = ( ಸರತಿ_Handle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ x_External_ಸರತಿ_Handle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 )

        ಸರತಿ_Handle_t MPU_x_ಸರತಿ_Generic_Create( UBaseType_t ux_ಸರತಿ_ಉದ್ದಳತೆ,
                                               UBaseType_t ux_ಅಂಶ_ಗಾತ್ರ,
                                               uint8_t uc_ಸರತಿ_Type ) /* PRIVILEGED_FUNCTION */
        {
            ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
            ಸರತಿ_Handle_t x_External_ಸರತಿ_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_Handle = x_ಸರತಿ_Generic_Create( ux_ಸರತಿ_ಉದ್ದಳತೆ, ux_ಅಂಶ_ಗಾತ್ರ, uc_ಸರತಿ_Type );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                {
                    MPU_Store_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_ಸರತಿ_Handle );
                    x_External_ಸರತಿ_Handle = ( ಸರತಿ_Handle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ x_External_ಸರತಿ_Handle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 )

        ಸರತಿ_Handle_t MPU_x_ಸರತಿ_Generic_Create_Static( ಸ್ಥಿರಾಂಕ UBaseType_t ux_ಸರತಿ_ಉದ್ದಳತೆ,
                                                     ಸ್ಥಿರಾಂಕ UBaseType_t ux_ಅಂಶ_ಗಾತ್ರ,
                                                     uint8_t * puc_ಸರತಿ_Storage,
                                                     Static_ಸರತಿ_t * px_Static_ಸರತಿ,
                                                     ಸ್ಥಿರಾಂಕ uint8_t uc_ಸರತಿ_Type ) /* PRIVILEGED_FUNCTION */
        {
            ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
            ಸರತಿ_Handle_t x_External_ಸರತಿ_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_Handle = x_ಸರತಿ_Generic_Create_Static( ux_ಸರತಿ_ಉದ್ದಳತೆ, ux_ಅಂಶ_ಗಾತ್ರ, puc_ಸರತಿ_Storage, px_Static_ಸರತಿ, uc_ಸರತಿ_Type );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                {
                    MPU_Store_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_ಸರತಿ_Handle );
                    x_External_ಸರತಿ_Handle = ( ಸರತಿ_Handle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ x_External_ಸರತಿ_Handle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Generic_Reset( ಸರತಿ_Handle_t x_ಸರತಿ,
                                       ತಳ_Type_t x_New_ಸರತಿ ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_ಸೂಚ್ಯಂಕ;
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
        ತಳ_Type_t xReturn = pdFAIL;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
            {
                xReturn = x_ಸರತಿ_Generic_Reset( x_ಆಂತರಿಕ_ಸರತಿ_Handle, x_New_ಸರತಿ );
            }
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_USE_ಸರತಿ_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 ) )

        ಸರತಿ_ಗಣ_Handle_t MPU_x_ಸರತಿ_Create_ಗಣ( UBaseType_t ux_Event_ಸರತಿ_ಉದ್ದಳತೆ ) /* PRIVILEGED_FUNCTION */
        {
            ಸರತಿ_ಗಣ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle = ಖಾಲಿ;
            ಸರತಿ_ಗಣ_Handle_t x_External_ಸರತಿ_ಗಣ_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle = x_ಸರತಿ_Create_ಗಣ( ux_Event_ಸರತಿ_ಉದ್ದಳತೆ );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle != ಖಾಲಿ )
                {
                    MPU_Store_ಸರತಿ_ಗಣ_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle );
                    x_External_ಸರತಿ_ಗಣ_Handle = ( ಸರತಿ_ಗಣ_Handle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ x_External_ಸರತಿ_ಗಣ_Handle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_USE_ಸರತಿ_SETS == 1 ) && ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 ) )

        ಸರತಿ_ಗಣ_Handle_t MPU_x_ಸರತಿ_Create_ಗಣ_Static( ಸ್ಥಿರಾಂಕ UBaseType_t ux_Event_ಸರತಿ_ಉದ್ದಳತೆ,
                                                    uint8_t * puc_ಸರತಿ_Storage,
                                                    Static_ಸರತಿ_t * px_Static_ಸರತಿ ) /* PRIVILEGED_FUNCTION */
        {
            ಸರತಿ_ಗಣ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle = ಖಾಲಿ;
            ಸರತಿ_ಗಣ_Handle_t x_External_ಸರತಿ_ಗಣ_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle = x_ಸರತಿ_Create_ಗಣ_Static( ux_Event_ಸರತಿ_ಉದ್ದಳತೆ, puc_ಸರತಿ_Storage, px_Static_ಸರತಿ );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle != ಖಾಲಿ )
                {
                    MPU_Store_ಸರತಿ_ಗಣ_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle );
                    x_External_ಸರತಿ_ಗಣ_Handle = ( ಸರತಿ_ಗಣ_Handle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ x_External_ಸರತಿ_ಗಣ_Handle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಸರತಿ_SETS == 1 )

        ತಳ_Type_t MPU_x_ಸರತಿ_Remove_From_ಗಣ( ಸರತಿ_ಗಣ_Member_Handle_t x_ಸರತಿ_Or_Semaphore,
                                            ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            ಸರತಿ_ಗಣ_Member_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Member_Handle = ಖಾಲಿ;
            ಸರತಿ_ಗಣ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ, l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ_Member;

            l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ = ( int32_t ) x_ಸರತಿ_ಗಣ;
            l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ_Member = ( int32_t ) x_ಸರತಿ_Or_Semaphore;

            ಆದರೆ( ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ ) != pdFALSE ) &&
                ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ_Member ) != pdFALSE ) )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle = MPU_Get_ಸರತಿ_ಗಣ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ ) );
                x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Member_Handle = MPU_Get_ಸರತಿ_ಗಣ_Member_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ_Member ) );

                ಆದರೆ( ( x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle != ಖಾಲಿ ) && ( x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Member_Handle != ಖಾಲಿ ) )
                {
                    xReturn = x_ಸರತಿ_Remove_From_ಗಣ( x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Member_Handle, x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 )

        ತಳ_Type_t MPU_x_ಸರತಿ_Generic_Get_Static_Buffers( ಸರತಿ_Handle_t x_ಸರತಿ,
                                                      uint8_t ** ppuc_ಸರತಿ_Storage,
                                                      Static_ಸರತಿ_t ** ppx_Static_ಸರತಿ ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_ಸೂಚ್ಯಂಕ;
            ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;
            ತಳ_Type_t xReturn = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
                {
                    xReturn = x_ಸರತಿ_Generic_Get_Static_Buffers( x_ಆಂತರಿಕ_ಸರತಿ_Handle, ppuc_ಸರತಿ_Storage, ppx_Static_ಸರತಿ );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /*if ( configSUPPORT_STATIC_ALLOCATION == 1 )*/
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Generic_Send_From_ISR( ಸರತಿ_Handle_t x_ಸರತಿ,
                                             ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ,
                                             ತಳ_Type_t * ಸ್ಥಿರಾಂಕ px_Higher_ಆದ್ಯತೆ_Task_Woken,
                                             ಸ್ಥಿರಾಂಕ ತಳ_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        ತಳ_Type_t xReturn = pdFAIL;
        int32_t l_ಸೂಚ್ಯಂಕ;
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
            {
                xReturn = x_ಸರತಿ_Generic_Send_From_ISR( x_ಆಂತರಿಕ_ಸರತಿ_Handle, pv_ಅಂಶ_ಗಮ್ಯ_ಸರತಿ, px_Higher_ಆದ್ಯತೆ_Task_Woken, xCopyPosition );
            }
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }

/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Give_From_ISR( ಸರತಿ_Handle_t x_ಸರತಿ,
                                      ತಳ_Type_t * ಸ್ಥಿರಾಂಕ px_Higher_ಆದ್ಯತೆ_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        ತಳ_Type_t xReturn = pdFAIL;
        int32_t l_ಸೂಚ್ಯಂಕ;
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
            {
                xReturn = x_ಸರತಿ_Give_From_ISR( x_ಆಂತರಿಕ_ಸರತಿ_Handle, px_Higher_ಆದ್ಯತೆ_Task_Woken );
            }
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }

/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Peek_From_ISR( ಸರತಿ_Handle_t x_ಸರತಿ,
                                      ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
    {
        ತಳ_Type_t xReturn = pdFAIL;
        int32_t l_ಸೂಚ್ಯಂಕ;
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
            {
                xReturn = x_ಸರತಿ_Peek_From_ISR( x_ಆಂತರಿಕ_ಸರತಿ_Handle, pv_ಬಫರ್ );
            }
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }

/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Receive_From_ISR( ಸರತಿ_Handle_t x_ಸರತಿ,
                                         ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pv_ಬಫರ್,
                                         ತಳ_Type_t * ಸ್ಥಿರಾಂಕ px_Higher_ಆದ್ಯತೆ_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        ತಳ_Type_t xReturn = pdFAIL;
        int32_t l_ಸೂಚ್ಯಂಕ;
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
            {
                xReturn = x_ಸರತಿ_Receive_From_ISR( x_ಆಂತರಿಕ_ಸರತಿ_Handle, pv_ಬಫರ್, px_Higher_ಆದ್ಯತೆ_Task_Woken );
            }
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }

/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Is_ಸರತಿ_ಖಾಲಿಗಳು_From_ISR( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t x_ಸರತಿ ) /* PRIVILEGED_FUNCTION */
    {
        ತಳ_Type_t xReturn = pdFAIL;
        int32_t l_ಸೂಚ್ಯಂಕ;
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
            {
                xReturn = x_ಸರತಿ_Is_ಸರತಿ_ಖಾಲಿಗಳು_From_ISR( x_ಆಂತರಿಕ_ಸರತಿ_Handle );
            }
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }
/*-----------------------------------------------------------*/

    ತಳ_Type_t MPU_x_ಸರತಿ_Is_ಸರತಿ_ತುಂಬಿದ_From_ISR( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t x_ಸರತಿ ) /* PRIVILEGED_FUNCTION */
    {
        ತಳ_Type_t xReturn = pdFAIL;
        int32_t l_ಸೂಚ್ಯಂಕ;
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
            {
                xReturn = x_ಸರತಿ_Is_ಸರತಿ_ತುಂಬಿದ_From_ISR( x_ಆಂತರಿಕ_ಸರತಿ_Handle );
            }
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }

/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ_From_ISR( ಸ್ಥಿರಾಂಕ ಸರತಿ_Handle_t x_ಸರತಿ ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn = 0;
        int32_t l_ಸೂಚ್ಯಂಕ;
        ಸರತಿ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_Handle = ಖಾಲಿ;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಸರತಿ;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_ಆಂತರಿಕ_ಸರತಿ_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_Handle != ಖಾಲಿ )
            {
                uxReturn = ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ_From_ISR( x_ಆಂತರಿಕ_ಸರತಿ_Handle );
            }
        }

        ಹಿಂತಿರುಗಿ uxReturn;
    }

/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_ಸರತಿ_Get_Mutex_Holder_From_ISR( ಸರತಿ_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_ಆಂತರಿಕ_Handle = ಖಾಲಿ;
            TaskHandle_t xMutexHolderTaskExternalHandle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ, l_Mutex_Holder_Task_ಸೂಚ್ಯಂಕ;
            ಸರತಿ_Handle_t x_ಆಂತರಿಕ_Semaphore_Handle = ಖಾಲಿ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xSemaphore;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_Semaphore_Handle = MPU_Get_ಸರತಿ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_Semaphore_Handle != ಖಾಲಿ )
                {
                    x_Mutex_Holder_Task_ಆಂತರಿಕ_Handle = x_ಸರತಿ_Get_Mutex_Holder( x_ಆಂತರಿಕ_Semaphore_Handle );

                    ಆದರೆ( x_Mutex_Holder_Task_ಆಂತರಿಕ_Handle != ಖಾಲಿ )
                    {
                        l_Mutex_Holder_Task_ಸೂಚ್ಯಂಕ = MPU_Get_ಸೂಚ್ಯಂಕ_For_Task_Handle( x_Mutex_Holder_Task_ಆಂತರಿಕ_Handle );

                        ಆದರೆ( l_Mutex_Holder_Task_ಸೂಚ್ಯಂಕ != -1 )
                        {
                            xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_Mutex_Holder_Task_ಸೂಚ್ಯಂಕ ) );
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xMutexHolderTaskExternalHandle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಸರತಿ_SETS == 1 )

        ಸರತಿ_ಗಣ_Member_Handle_t MPU_x_ಸರತಿ_Select_From_ಗಣ_From_ISR( ಸರತಿ_ಗಣ_Handle_t x_ಸರತಿ_ಗಣ ) /* PRIVILEGED_FUNCTION */
        {
            ಸರತಿ_ಗಣ_Handle_t x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle = ಖಾಲಿ;
            ಸರತಿ_ಗಣ_Member_Handle_t x_Selected_Member_ಆಂತರಿಕ = ಖಾಲಿ;
            ಸರತಿ_ಗಣ_Member_Handle_t xSelectedMemberExternal = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ, l_ಸೂಚ್ಯಂಕ_Selected_Member;

            l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ = ( int32_t ) x_ಸರತಿ_ಗಣ;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle = MPU_Get_ಸರತಿ_ಗಣ_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ_ಸರತಿ_ಗಣ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle != ಖಾಲಿ )
                {
                    x_Selected_Member_ಆಂತರಿಕ = x_ಸರತಿ_Select_From_ಗಣ_From_ISR( x_ಆಂತರಿಕ_ಸರತಿ_ಗಣ_Handle );

                    ಆದರೆ( x_Selected_Member_ಆಂತರಿಕ != ಖಾಲಿ )
                    {
                        l_ಸೂಚ್ಯಂಕ_Selected_Member = MPU_Get_ಸೂಚ್ಯಂಕ_For_ಸರತಿ_ಗಣ_Member_Handle( x_Selected_Member_ಆಂತರಿಕ );

                        ಆದರೆ( l_ಸೂಚ್ಯಂಕ_Selected_Member != -1 )
                        {
                            xSelectedMemberExternal = ( ಸರತಿ_ಗಣ_Member_Handle_t ) ( CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ_Selected_Member ) );
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xSelectedMemberExternal;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for timers APIs.                  */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ಶೂನ್ಯ * MPU_pvTimerGetTimerIDImpl( ಸ್ಥಿರಾಂಕ TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ * MPU_pvTimerGetTimerIDImpl( ಸ್ಥಿರಾಂಕ TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ಶೂನ್ಯ * pvReturn = ಖಾಲಿ;
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTimer;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer == pdTRUE )
                {
                    x_ಆಂತರಿಕ_Timer_Handle = MPU_Get_Timer_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                    {
                        pvReturn = pvTimerGetTimerID( x_ಆಂತರಿಕ_Timer_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ pvReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ಶೂನ್ಯ MPU_v_Timer_ಗಣ_Timer_IDImpl( TimerHandle_t xTimer,
                                       ಶೂನ್ಯ * pvNewID ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_v_Timer_ಗಣ_Timer_IDImpl( TimerHandle_t xTimer,
                                       ಶೂನ್ಯ * pvNewID ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTimer;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer == pdTRUE )
                {
                    x_ಆಂತರಿಕ_Timer_Handle = MPU_Get_Timer_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                    {
                        v_Timer_ಗಣ_Timer_ID( x_ಆಂತರಿಕ_Timer_Handle, pvNewID );
                    }
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ತಳ_Type_t MPU_x_Timer_Is_Timer_ಸಕ್ರಿಯ_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_x_Timer_Is_Timer_ಸಕ್ರಿಯ_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTimer;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer == pdTRUE )
                {
                    x_ಆಂತರಿಕ_Timer_Handle = MPU_Get_Timer_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                    {
                        xReturn = x_Timer_Is_Timer_ಸಕ್ರಿಯ( x_ಆಂತರಿಕ_Timer_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xReturn;

            xReturn = xTimerGetTimerDaemonTaskHandle();

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ತಳ_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ಸ್ಥಿರಾಂಕ ತಳ_Type_t xCommandID,
                                                     ಸ್ಥಿರಾಂಕ TickType_t x_Optional_ಮೌಲ್ಯ,
                                                     ತಳ_Type_t * ಸ್ಥಿರಾಂಕ px_Higher_ಆದ್ಯತೆ_Task_Woken,
                                                     ಸ್ಥಿರಾಂಕ TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            xTimerGenericCommandFromTaskParams_t xParams;

            xParams.xTimer = xTimer;
            xParams.xCommandID = xCommandID;
            xParams.x_Optional_ಮೌಲ್ಯ = x_Optional_ಮೌಲ್ಯ;
            xParams.px_Higher_ಆದ್ಯತೆ_Task_Woken = px_Higher_ಆದ್ಯತೆ_Task_Woken;
            xParams.x_Ticks_ಗಮ್ಯ_Wait = x_Ticks_ಗಮ್ಯ_Wait;

            xReturn = MPU_x_Timer_Generic_Command_From_Task_ನಮೂದು( &( xParams ) );

            ಹಿಂತಿರುಗಿ xReturn;
        }

        ತಳ_Type_t MPU_xTimerGenericCommandFromTaskImpl( ಸ್ಥಿರಾಂಕ xTimerGenericCommandFromTaskParams_t * pxParams ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_xTimerGenericCommandFromTaskImpl( ಸ್ಥಿರಾಂಕ xTimerGenericCommandFromTaskParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Is_Higher_ಆದ್ಯತೆ_Task_Woken_Writeable = pdFALSE;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = pdFALSE;
            ತಳ_Type_t xAreParamsReadable = pdFALSE;

            ಆದರೆ( pxParams != ಖಾಲಿ )
            {
                xAreParamsReadable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( pxParams,
                                                                      ಗಾತ್ರ( xTimerGenericCommandFromTaskParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ಆದರೆ( xAreParamsReadable == pdTRUE )
            {
                ಆದರೆ( pxParams->xCommandID < tmr_ಮೊದಲ_FROM_ISR_COMMAND )
                {
                    ಆದರೆ( pxParams->px_Higher_ಆದ್ಯತೆ_Task_Woken != ಖಾಲಿ )
                    {
                        x_Is_Higher_ಆದ್ಯತೆ_Task_Woken_Writeable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( pxParams->px_Higher_ಆದ್ಯತೆ_Task_Woken,
                                                                                               ಗಾತ್ರ( ತಳ_Type_t ),
                                                                                               tskMPU_WRITE_PERMISSION );
                    }

                    ಆದರೆ( ( pxParams->px_Higher_ಆದ್ಯತೆ_Task_Woken == ಖಾಲಿ ) ||
                        ( x_Is_Higher_ಆದ್ಯತೆ_Task_Woken_Writeable == pdTRUE ) )
                    {
                        l_ಸೂಚ್ಯಂಕ = ( int32_t ) ( pxParams->xTimer );

                        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                            ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer == pdTRUE )
                            {
                                x_ಆಂತರಿಕ_Timer_Handle = MPU_Get_Timer_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                                ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                                {
                                    xReturn = xTimerGenericCommandFromTask( x_ಆಂತರಿಕ_Timer_Handle,
                                                                            pxParams->xCommandID,
                                                                            pxParams->x_Optional_ಮೌಲ್ಯ,
                                                                            pxParams->px_Higher_ಆದ್ಯತೆ_Task_Woken,
                                                                            pxParams->x_Ticks_ಗಮ್ಯ_Wait );
                                }
                            }
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pcReturn = ಖಾಲಿ;
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTimer;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer == pdTRUE )
                {
                    x_ಆಂತರಿಕ_Timer_Handle = MPU_Get_Timer_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                    {
                        pcReturn = pcTimerGetName( x_ಆಂತರಿಕ_Timer_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ pcReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ಶೂನ್ಯ MPU_v_Timer_ಗಣ_Reload_ಬಹುಲಕ_Impl( TimerHandle_t xTimer,
                                          ಸ್ಥಿರಾಂಕ ತಳ_Type_t xAutoReload ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_v_Timer_ಗಣ_Reload_ಬಹುಲಕ_Impl( TimerHandle_t xTimer,
                                          ಸ್ಥಿರಾಂಕ ತಳ_Type_t xAutoReload ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTimer;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer == pdTRUE )
                {
                    x_ಆಂತರಿಕ_Timer_Handle = MPU_Get_Timer_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                    {
                        v_Timer_ಗಣ_Reload_ಬಹುಲಕ( x_ಆಂತರಿಕ_Timer_Handle, xAutoReload );
                    }
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ತಳ_Type_t MPU_x_Timer_Get_Reload_ಬಹುಲಕ_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_x_Timer_Get_Reload_ಬಹುಲಕ_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTimer;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer == pdTRUE )
                {
                    x_ಆಂತರಿಕ_Timer_Handle = MPU_Get_Timer_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                    {
                        xReturn = x_Timer_Get_Reload_ಬಹುಲಕ( x_ಆಂತರಿಕ_Timer_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_ಬಹುಲಕ_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Timer_Get_Reload_ಬಹುಲಕ_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTimer;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer == pdTRUE )
                {
                    x_ಆಂತರಿಕ_Timer_Handle = MPU_Get_Timer_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                    {
                        uxReturn = ux_Timer_Get_Reload_ಬಹುಲಕ( x_ಆಂತರಿಕ_Timer_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ uxReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTimer;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer == pdTRUE )
                {
                    x_ಆಂತರಿಕ_Timer_Handle = MPU_Get_Timer_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                    {
                        xReturn = xTimerGetPeriod( x_ಆಂತರಿಕ_Timer_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_ಸಮಯ_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_x_Timer_Get_Expiry_ಸಮಯ_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTimer;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Timer == pdTRUE )
                {
                    x_ಆಂತರಿಕ_Timer_Handle = MPU_Get_Timer_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                    {
                        xReturn = x_Timer_Get_Expiry_ಸಮಯ( x_ಆಂತರಿಕ_Timer_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Timer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreate( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ pcTimerName,
                                        ಸ್ಥಿರಾಂಕ TickType_t x_Timer_Period_ಒಳ_Ticks,
                                        ಸ್ಥಿರಾಂಕ ತಳ_Type_t xAutoReload,
                                        ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pvTimerID,
                                        TimerCallbackFunction_t pxCallbackFunction ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            TimerHandle_t xExternalTimerHandle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                x_ಆಂತರಿಕ_Timer_Handle = xTimerCreate( pcTimerName, x_Timer_Period_ಒಳ_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback );

                ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                {
                    MPU_Store_Timer_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ xExternalTimerHandle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreateStatic( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ pcTimerName,
                                              ಸ್ಥಿರಾಂಕ TickType_t x_Timer_Period_ಒಳ_Ticks,
                                              ಸ್ಥಿರಾಂಕ ತಳ_Type_t xAutoReload,
                                              ಶೂನ್ಯ * ಸ್ಥಿರಾಂಕ pvTimerID,
                                              TimerCallbackFunction_t pxCallbackFunction,
                                              StaticTimer_t * px_Timer_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            TimerHandle_t xExternalTimerHandle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                x_ಆಂತರಿಕ_Timer_Handle = xTimerCreateStatic( pcTimerName, x_Timer_Period_ಒಳ_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback, px_Timer_ಬಫರ್ );

                ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                {
                    MPU_Store_Timer_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ xExternalTimerHandle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 ) && ( configUSE_TIMERS == 1 )

        ತಳ_Type_t MPU_x_Timer_Get_Static_ಬಫರ್( TimerHandle_t xTimer,
                                              StaticTimer_t ** ppx_Timer_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t xReturn = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTimer;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_Timer_Handle = MPU_Get_Timer_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                {
                    xReturn = x_Timer_Get_Static_ಬಫರ್( x_ಆಂತರಿಕ_Timer_Handle, ppx_Timer_ಬಫರ್ );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ತಳ_Type_t MPU_xTimerGenericCommandFromISR( TimerHandle_t xTimer,
                                                    ಸ್ಥಿರಾಂಕ ತಳ_Type_t xCommandID,
                                                    ಸ್ಥಿರಾಂಕ TickType_t x_Optional_ಮೌಲ್ಯ,
                                                    ತಳ_Type_t * ಸ್ಥಿರಾಂಕ px_Higher_ಆದ್ಯತೆ_Task_Woken,
                                                    ಸ್ಥಿರಾಂಕ TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTimer;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_Timer_Handle = MPU_Get_Timer_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                {
                    xReturn = xTimerGenericCommandFromISR( x_ಆಂತರಿಕ_Timer_Handle, xCommandID, x_Optional_ಮೌಲ್ಯ, px_Higher_ಆದ್ಯತೆ_Task_Woken, x_Ticks_ಗಮ್ಯ_Wait );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_TIMERS == 1 )

        ತಳ_Type_t MPU_xTimerDelete( TimerHandle_t xTimer, TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            TimerHandle_t x_ಆಂತರಿಕ_Timer_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) xTimer;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_Timer_Handle = MPU_Get_Timer_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_Timer_Handle != ಖಾಲಿ )
                {
                    xReturn = xTimerGenericCommandFromTask( x_ಆಂತರಿಕ_Timer_Handle,
                                                            tmrCOMMAND_DELETE,
                                                            0U, /* xOptionalValue */
                                                            ಖಾಲಿ, /* pxHigherPriorityTaskWoken */
                                                            x_Ticks_ಗಮ್ಯ_Wait );
                    ಆದರೆ( xReturn != pdFALSE )
                    {
                        MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for event group APIs.              */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                             ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For,
                                             ಸ್ಥಿರಾಂಕ ತಳ_Type_t xClearOnExit,
                                             ಸ್ಥಿರಾಂಕ ತಳ_Type_t x_Wait_For_All_ಬಿಟ್ಟುಗಳು,
                                             TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_ಬಿಟ್ಟುಗಳು_t xReturn = 0;
            x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Params_t xParams;

            xParams.x_Event_ಗುಂಪು = x_Event_ಗುಂಪು;
            xParams.ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For = ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For;
            xParams.xClearOnExit = xClearOnExit;
            xParams.x_Wait_For_All_ಬಿಟ್ಟುಗಳು = x_Wait_For_All_ಬಿಟ್ಟುಗಳು;
            xParams.x_Ticks_ಗಮ್ಯ_Wait = x_Ticks_ಗಮ್ಯ_Wait;

            xReturn = MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_ನಮೂದು( &( xParams ) );

            ಹಿಂತಿರುಗಿ xReturn;
        }

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Impl( ಸ್ಥಿರಾಂಕ x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Params_t * pxParams ) PRIVILEGED_FUNCTION;

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Impl( ಸ್ಥಿರಾಂಕ x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Params_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            Event_ಬಿಟ್ಟುಗಳು_t xReturn = 0;
            Event_ಗುಂಪು_Handle_t x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು = pdFALSE;
            ತಳ_Type_t xAreParamsReadable = pdFALSE;

            ಆದರೆ( pxParams != ಖಾಲಿ )
            {
                xAreParamsReadable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( pxParams,
                                                                      ಗಾತ್ರ( x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Params_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ಆದರೆ( xAreParamsReadable == pdTRUE )
            {
                ಆದರೆ( ( ( pxParams->ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For & event_EVENT_ಬಿಟ್ಟುಗಳು_CONTROL_ಬೈಟುಗಳು ) == 0U ) &&
                    ( pxParams->ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For != 0U )
                    #ಆದರೆ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                        && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( pxParams->x_Ticks_ಗಮ್ಯ_Wait != 0U ) ) )
                    #ಆದರೆ_ಅಂತ್ಯ
                    )
                {
                    l_ಸೂಚ್ಯಂಕ = ( int32_t ) ( pxParams->x_Event_ಗುಂಪು );

                    ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು == pdTRUE )
                        {
                            x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = MPU_Get_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                            ಆದರೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle != ಖಾಲಿ )
                            {
                                xReturn = x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle,
                                                               pxParams->ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For,
                                                               pxParams->xClearOnExit,
                                                               pxParams->x_Wait_For_All_ಬಿಟ್ಟುಗಳು,
                                                               pxParams->x_Ticks_ಗಮ್ಯ_Wait );
                            }
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು_Impl( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                                  ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) PRIVILEGED_FUNCTION;

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು_Impl( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                                  ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) /* PRIVILEGED_FUNCTION */
        {
            Event_ಬಿಟ್ಟುಗಳು_t xReturn = 0;
            Event_ಗುಂಪು_Handle_t x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು = pdFALSE;

            ಆದರೆ( ( ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear & event_EVENT_ಬಿಟ್ಟುಗಳು_CONTROL_ಬೈಟುಗಳು ) == 0U )
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Event_ಗುಂಪು;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು == pdTRUE )
                    {
                        x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = MPU_Get_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle != ಖಾಲಿ )
                        {
                            xReturn = x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear );
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು_Impl( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                                ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ ) PRIVILEGED_FUNCTION;

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು_Impl( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                                ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ ) /* PRIVILEGED_FUNCTION */
        {
            Event_ಬಿಟ್ಟುಗಳು_t xReturn = 0;
            Event_ಗುಂಪು_Handle_t x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು = pdFALSE;

            ಆದರೆ( ( ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ & event_EVENT_ಬಿಟ್ಟುಗಳು_CONTROL_ಬೈಟುಗಳು ) == 0U )
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Event_ಗುಂಪು;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು == pdTRUE )
                    {
                        x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = MPU_Get_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle != ಖಾಲಿ )
                        {
                            xReturn = x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ );
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Sync_Impl( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                             ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ,
                                             ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For,
                                             TickType_t x_Ticks_ಗಮ್ಯ_Wait ) PRIVILEGED_FUNCTION;

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Sync_Impl( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                             ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ,
                                             ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For,
                                             TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* PRIVILEGED_FUNCTION */
        {
            Event_ಬಿಟ್ಟುಗಳು_t xReturn = 0;
            Event_ಗುಂಪು_Handle_t x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು = pdFALSE;

            ಆದರೆ( ( ( ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For & event_EVENT_ಬಿಟ್ಟುಗಳು_CONTROL_ಬೈಟುಗಳು ) == 0U ) &&
                ( ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For != 0U )
                #ಆದರೆ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                    && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_ಗಮ್ಯ_Wait != 0U ) ) )
                #ಆದರೆ_ಅಂತ್ಯ
                )
            {
                l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Event_ಗುಂಪು;

                ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು == pdTRUE )
                    {
                        x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = MPU_Get_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle != ಖಾಲಿ )
                        {
                            xReturn = x_Event_ಗುಂಪು_Sync( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Wait_For, x_Ticks_ಗಮ್ಯ_Wait );
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_ಗುಂಪು_Get_ಸಂಖ್ಯೆ_Impl( ಶೂನ್ಯ * x_Event_ಗುಂಪು ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Event_ಗುಂಪು_Get_ಸಂಖ್ಯೆ_Impl( ಶೂನ್ಯ * x_Event_ಗುಂಪು ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t xReturn = 0;
            Event_ಗುಂಪು_Handle_t x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Event_ಗುಂಪು;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು == pdTRUE )
                {
                    x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = MPU_Get_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle != ಖಾಲಿ )
                    {
                        xReturn = ux_Event_ಗುಂಪು_Get_ಸಂಖ್ಯೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        ಶೂನ್ಯ MPU_v_Event_ಗುಂಪು_ಗಣ_ಸಂಖ್ಯೆ_Impl( ಶೂನ್ಯ * x_Event_ಗುಂಪು,
                                           UBaseType_t ux_Event_ಗುಂಪು_ಸಂಖ್ಯೆ ) PRIVILEGED_FUNCTION;

        ಶೂನ್ಯ MPU_v_Event_ಗುಂಪು_ಗಣ_ಸಂಖ್ಯೆ_Impl( ಶೂನ್ಯ * x_Event_ಗುಂಪು,
                                           UBaseType_t ux_Event_ಗುಂಪು_ಸಂಖ್ಯೆ ) /* PRIVILEGED_FUNCTION */
        {
            Event_ಗುಂಪು_Handle_t x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Event_ಗುಂಪು;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_Event_ಗುಂಪು == pdTRUE )
                {
                    x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = MPU_Get_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle != ಖಾಲಿ )
                    {
                        v_Event_ಗುಂಪು_ಗಣ_ಸಂಖ್ಯೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle, ux_Event_ಗುಂಪು_ಸಂಖ್ಯೆ );
                    }
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Event Group APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_ಗುಂಪು_Handle_t MPU_x_Event_ಗುಂಪು_Create( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
        {
            Event_ಗುಂಪು_Handle_t x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            Event_ಗುಂಪು_Handle_t x_External_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = x_Event_ಗುಂಪು_Create();

                ಆದರೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle != ಖಾಲಿ )
                {
                    MPU_Store_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle );
                    x_External_Event_ಗುಂಪು_Handle = ( Event_ಗುಂಪು_Handle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ x_External_Event_ಗುಂಪು_Handle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_ಗುಂಪು_Handle_t MPU_x_Event_ಗುಂಪು_Create_Static( Static_Event_ಗುಂಪು_t * px_Event_ಗುಂಪು_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
        {
            Event_ಗುಂಪು_Handle_t x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            Event_ಗುಂಪು_Handle_t x_External_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

            ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
            {
                x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = x_Event_ಗುಂಪು_Create_Static( px_Event_ಗುಂಪು_ಬಫರ್ );

                ಆದರೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle != ಖಾಲಿ )
                {
                    MPU_Store_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle );
                    x_External_Event_ಗುಂಪು_Handle = ( Event_ಗುಂಪು_Handle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                }
            }

            ಹಿಂತಿರುಗಿ x_External_Event_ಗುಂಪು_Handle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )

        ಶೂನ್ಯ MPU_v_Event_ಗುಂಪು_Delete( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು ) /* PRIVILEGED_FUNCTION */
        {
            Event_ಗುಂಪು_Handle_t x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Event_ಗುಂಪು;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = MPU_Get_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle != ಖಾಲಿ )
                {
                    v_Event_ಗುಂಪು_Delete( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle );
                    MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );
                }
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        ತಳ_Type_t MPU_x_Event_ಗುಂಪು_Get_Static_ಬಫರ್( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                                   Static_Event_ಗುಂಪು_t ** ppx_Event_ಗುಂಪು_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            Event_ಗುಂಪು_Handle_t x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Event_ಗುಂಪು;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = MPU_Get_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle != ಖಾಲಿ )
                {
                    xReturn = x_Event_ಗುಂಪು_Get_Static_ಬಫರ್( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle, ppx_Event_ಗುಂಪು_ಬಫರ್ );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        ತಳ_Type_t MPU_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು_From_ISR( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                                    ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            Event_ಗುಂಪು_Handle_t x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Event_ಗುಂಪು;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = MPU_Get_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle != ಖಾಲಿ )
                {
                    xReturn = x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು_From_ISR( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_Clear );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        ತಳ_Type_t MPU_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು_From_ISR( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು,
                                                  ಸ್ಥಿರಾಂಕ Event_ಬಿಟ್ಟುಗಳು_t ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ,
                                                  ತಳ_Type_t * px_Higher_ಆದ್ಯತೆ_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            Event_ಗುಂಪು_Handle_t x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Event_ಗುಂಪು;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = MPU_Get_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle != ಖಾಲಿ )
                {
                    xReturn = x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು_From_ISR( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle, ux_ಬಿಟ್ಟುಗಳು_ಗಮ್ಯ_ಗಣ, px_Higher_ಆದ್ಯತೆ_Task_Woken );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )

        Event_ಬಿಟ್ಟುಗಳು_t MPU_x_Event_ಗುಂಪು_Get_ಬಿಟ್ಟುಗಳು_From_ISR( Event_ಗುಂಪು_Handle_t x_Event_ಗುಂಪು ) /* PRIVILEGED_FUNCTION */
        {
            Event_ಬಿಟ್ಟುಗಳು_t xReturn = 0;
            Event_ಗುಂಪು_Handle_t x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_Event_ಗುಂಪು;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle = MPU_Get_Event_ಗುಂಪು_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle != ಖಾಲಿ )
                {
                    xReturn = x_Event_ಗುಂಪು_Get_ಬಿಟ್ಟುಗಳು_From_ISR( x_ಆಂತರಿಕ_Event_ಗುಂಪು_Handle );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for stream buffer APIs.            */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        size_t MPU_x_ಹರಿವು_ಬಫರ್_Send_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                          ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * pv_Tx_ದತ್ತಾಂಶ,
                                          size_t x_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                          TickType_t x_Ticks_ಗಮ್ಯ_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ಹರಿವು_ಬಫರ್_Send_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                          ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * pv_Tx_ದತ್ತಾಂಶ,
                                          size_t x_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                          TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Is_Tx_ದತ್ತಾಂಶ_ಬಫರ್_Readable = pdFALSE;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = pdFALSE;

            ಆದರೆ( pv_Tx_ದತ್ತಾಂಶ != ಖಾಲಿ )
            {
                x_Is_Tx_ದತ್ತಾಂಶ_ಬಫರ್_Readable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( pv_Tx_ದತ್ತಾಂಶ,
                                                                           x_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                                                           tskMPU_READ_PERMISSION );

                ಆದರೆ( x_Is_Tx_ದತ್ತಾಂಶ_ಬಫರ್_Readable == pdTRUE )
                {
                    l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

                    ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ == pdTRUE )
                        {
                            x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                            ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                            {
                                xReturn = x_ಹರಿವು_ಬಫರ್_Send( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle, pv_Tx_ದತ್ತಾಂಶ, x_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು, x_Ticks_ಗಮ್ಯ_Wait );
                            }
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        size_t MPU_x_ಹರಿವು_ಬಫರ್_Receive_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                             ಶೂನ್ಯ * pv_Rx_ದತ್ತಾಂಶ,
                                             size_t x_ಬಫರ್_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                             TickType_t x_Ticks_ಗಮ್ಯ_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ಹರಿವು_ಬಫರ್_Receive_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                             ಶೂನ್ಯ * pv_Rx_ದತ್ತಾಂಶ,
                                             size_t x_ಬಫರ್_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                             TickType_t x_Ticks_ಗಮ್ಯ_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Is_Rx_ದತ್ತಾಂಶ_ಬಫರ್_Writeable = pdFALSE;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = pdFALSE;

            ಆದರೆ( pv_Rx_ದತ್ತಾಂಶ != ಖಾಲಿ )
            {
                x_Is_Rx_ದತ್ತಾಂಶ_ಬಫರ್_Writeable = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_ಬಫರ್( pv_Rx_ದತ್ತಾಂಶ,
                                                                            x_ಬಫರ್_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                                                            tskMPU_WRITE_PERMISSION );

                ಆದರೆ( x_Is_Rx_ದತ್ತಾಂಶ_ಬಫರ್_Writeable == pdTRUE )
                {
                    l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

                    ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                        ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ == pdTRUE )
                        {
                            x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                            ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                            {
                                xReturn = x_ಹರಿವು_ಬಫರ್_Receive( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle, pv_Rx_ದತ್ತಾಂಶ, x_ಬಫರ್_ಉದ್ದಳತೆ_ಬೈಟುಗಳು, x_Ticks_ಗಮ್ಯ_Wait );
                            }
                        }
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ == pdTRUE )
                {
                    x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                    {
                        xReturn = x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ == pdTRUE )
                {
                    x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                    {
                        xReturn = x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        size_t MPU_x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ == pdTRUE )
                {
                    x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                    {
                        xReturn = x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        size_t MPU_x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ == pdTRUE )
                {
                    x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                    {
                        xReturn = x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                                         size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                                         size_t xTriggerLevel ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ == pdTRUE )
                {
                    x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                    {
                        xReturn = x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle, xTriggerLevel );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        size_t MPU_x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು_Impl( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;
            ತಳ_Type_t x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = pdFALSE;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ = x_ಪೋರ್ಟ್_Is_Authorized_ಗಮ್ಯ_Access_Kernel_Object( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_Calling_Task_Is_Authorized_ಗಮ್ಯ_Access_ಹರಿವು_ಬಫರ್ == pdTRUE )
                {
                    x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                    {
                        xReturn = x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle );
                    }
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Stream Buffer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 1 ) && ( config_USE_ಹರಿವು_BUFFERS == 1 ) )

        ಹರಿವು_ಬಫರ್_Handle_t MPU_x_ಹರಿವು_ಬಫರ್_Generic_Create( size_t x_ಬಫರ್_ಗಾತ್ರ_ಬೈಟುಗಳು,
                                                             size_t x_Trigger_Level_ಬೈಟುಗಳು,
                                                             ತಳ_Type_t x_ಹರಿವು_ಬಫರ್_Type,
                                                             ಹರಿವು_ಬಫರ್_Callback_Function_t pxSendCompletedCallback,
                                                             ಹರಿವು_ಬಫರ್_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            ಹರಿವು_ಬಫರ್_Handle_t x_External_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ಖಾಲಿ ) &&
                          ( pxReceiveCompletedCallback == ಖಾಲಿ ) );

            ಆದರೆ( ( pxSendCompletedCallback == ಖಾಲಿ ) &&
                ( pxReceiveCompletedCallback == ಖಾಲಿ ) )
            {
                l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

                ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
                {
                    x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = x_ಹರಿವು_ಬಫರ್_Generic_Create( x_ಬಫರ್_ಗಾತ್ರ_ಬೈಟುಗಳು,
                                                                              x_Trigger_Level_ಬೈಟುಗಳು,
                                                                              x_ಹರಿವು_ಬಫರ್_Type,
                                                                              ಖಾಲಿ,
                                                                              ಖಾಲಿ );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                    {
                        MPU_Store_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle );
                        x_External_ಹರಿವು_ಬಫರ್_Handle = ( ಹರಿವು_ಬಫರ್_Handle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                    }
                    ಇಲ್ಲದಿದ್ದರೆ
                    {
                        MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                    }
                }
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                trace_ಹರಿವು_ಬಫರ್_CREATE_FAILED( x_ಹರಿವು_ಬಫರ್_Type );
                x_External_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            }

            ಹಿಂತಿರುಗಿ x_External_ಹರಿವು_ಬಫರ್_Handle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 ) && ( config_USE_ಹರಿವು_BUFFERS == 1 ) )

        ಹರಿವು_ಬಫರ್_Handle_t MPU_x_ಹರಿವು_ಬಫರ್_Generic_Create_Static( size_t x_ಬಫರ್_ಗಾತ್ರ_ಬೈಟುಗಳು,
                                                                   size_t x_Trigger_Level_ಬೈಟುಗಳು,
                                                                   ತಳ_Type_t x_ಹರಿವು_ಬಫರ್_Type,
                                                                   uint8_t * ಸ್ಥಿರಾಂಕ puc_ಹರಿವು_ಬಫರ್_Storage_Area,
                                                                   Static_ಹರಿವು_ಬಫರ್_t * ಸ್ಥಿರಾಂಕ px_Static_ಹರಿವು_ಬಫರ್,
                                                                   ಹರಿವು_ಬಫರ್_Callback_Function_t pxSendCompletedCallback,
                                                                   ಹರಿವು_ಬಫರ್_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            ಹರಿವು_ಬಫರ್_Handle_t x_External_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ಖಾಲಿ ) &&
                          ( pxReceiveCompletedCallback == ಖಾಲಿ ) );

            ಆದರೆ( ( pxSendCompletedCallback == ಖಾಲಿ ) &&
                ( pxReceiveCompletedCallback == ಖಾಲಿ ) )
            {
                l_ಸೂಚ್ಯಂಕ = MPU_Get_Free_ಸೂಚ್ಯಂಕ_ಒಳ_Kernel_Object_Pool();

                ಆದರೆ( l_ಸೂಚ್ಯಂಕ != -1 )
                {
                    x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = x_ಹರಿವು_ಬಫರ್_Generic_Create_Static( x_ಬಫರ್_ಗಾತ್ರ_ಬೈಟುಗಳು,
                                                                                    x_Trigger_Level_ಬೈಟುಗಳು,
                                                                                    x_ಹರಿವು_ಬಫರ್_Type,
                                                                                    puc_ಹರಿವು_ಬಫರ್_Storage_Area,
                                                                                    px_Static_ಹರಿವು_ಬಫರ್,
                                                                                    ಖಾಲಿ,
                                                                                    ಖಾಲಿ );

                    ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                    {
                        MPU_Store_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ, x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle );
                        x_External_ಹರಿವು_ಬಫರ್_Handle = ( ಹರಿವು_ಬಫರ್_Handle_t ) CONVERT_ಗಮ್ಯ_EXTERNAL_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ );
                    }
                    ಇಲ್ಲದಿದ್ದರೆ
                    {
                        MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( l_ಸೂಚ್ಯಂಕ );
                    }
                }
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                trace_ಹರಿವು_ಬಫರ್_CREATE_STATIC_FAILED( xReturn, x_ಹರಿವು_ಬಫರ್_Type );
                x_External_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            }

            ಹಿಂತಿರುಗಿ x_External_ಹರಿವು_ಬಫರ್_Handle;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        ಶೂನ್ಯ MPU_v_ಹರಿವು_ಬಫರ್_Delete( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
        {
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                {
                    v_ಹರಿವು_ಬಫರ್_Delete( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle );
                }

                MPU_ಗಣ_ಸೂಚ್ಯಂಕ_Free_ಒಳ_Kernel_Object_Pool( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );
            }
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Reset( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                {
                    xReturn = x_ಹರಿವು_ಬಫರ್_Reset( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( ( config_SUPPORT_STATIC_ಹಂಚಿಕೆ == 1 ) && ( config_USE_ಹರಿವು_BUFFERS == 1 ) )

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Get_Static_Buffers( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_Buffers,
                                                      uint8_t * ppuc_ಹರಿವು_ಬಫರ್_Storage_Area,
                                                      Static_ಹರಿವು_ಬಫರ್_t * ppx_Static_ಹರಿವು_ಬಫರ್ ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_Buffers;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                {
                    xReturn = MPU_x_ಹರಿವು_ಬಫರ್_Get_Static_Buffers( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle, ppuc_ಹರಿವು_ಬಫರ್_Storage_Area, ppx_Static_ಹರಿವು_ಬಫರ್ );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

    size_t MPU_x_ಹರಿವು_ಬಫರ್_Send_From_ISR( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                         ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ * pv_Tx_ದತ್ತಾಂಶ,
                                         size_t x_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                         ತಳ_Type_t * ಸ್ಥಿರಾಂಕ px_Higher_ಆದ್ಯತೆ_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
        int32_t l_ಸೂಚ್ಯಂಕ;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
            {
                xReturn = x_ಹರಿವು_ಬಫರ್_Send_From_ISR( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle, pv_Tx_ದತ್ತಾಂಶ, x_ದತ್ತಾಂಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು, px_Higher_ಆದ್ಯತೆ_Task_Woken );
            }
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

    size_t MPU_x_ಹರಿವು_ಬಫರ್_Receive_From_ISR( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                            ಶೂನ್ಯ * pv_Rx_ದತ್ತಾಂಶ,
                                            size_t x_ಬಫರ್_ಉದ್ದಳತೆ_ಬೈಟುಗಳು,
                                            ತಳ_Type_t * ಸ್ಥಿರಾಂಕ px_Higher_ಆದ್ಯತೆ_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
        int32_t l_ಸೂಚ್ಯಂಕ;

        l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

        ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
        {
            x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

            ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
            {
                xReturn = x_ಹರಿವು_ಬಫರ್_Receive_From_ISR( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle, pv_Rx_ದತ್ತಾಂಶ, x_ಬಫರ್_ಉದ್ದಳತೆ_ಬೈಟುಗಳು, px_Higher_ಆದ್ಯತೆ_Task_Woken );
            }
        }

        ಹಿಂತಿರುಗಿ xReturn;
    }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Send_Completed_From_ISR( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                                          ತಳ_Type_t * px_Higher_ಆದ್ಯತೆ_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                {
                    xReturn = x_ಹರಿವು_ಬಫರ್_Send_Completed_From_ISR( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle, px_Higher_ಆದ್ಯತೆ_Task_Woken );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Receive_Completed_From_ISR( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್,
                                                             ತಳ_Type_t * px_Higher_ಆದ್ಯತೆ_Task_Woken ) /*PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFALSE;
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                {
                    xReturn = x_ಹರಿವು_ಬಫರ್_Receive_Completed_From_ISR( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle, px_Higher_ಆದ್ಯತೆ_Task_Woken );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

    #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )

        ತಳ_Type_t MPU_x_ಹರಿವು_ಬಫರ್_Reset_From_ISR( ಹರಿವು_ಬಫರ್_Handle_t x_ಹರಿವು_ಬಫರ್ ) /*PRIVILEGED_FUNCTION */
        {
            ತಳ_Type_t xReturn = pdFAIL;
            ಹರಿವು_ಬಫರ್_Handle_t x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = ಖಾಲಿ;
            int32_t l_ಸೂಚ್ಯಂಕ;

            l_ಸೂಚ್ಯಂಕ = ( int32_t ) x_ಹರಿವು_ಬಫರ್;

            ಆದರೆ( IS_EXTERNAL_ಸೂಚ್ಯಂಕ_VALID( l_ಸೂಚ್ಯಂಕ ) != pdFALSE )
            {
                x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle = MPU_Get_ಹರಿವು_ಬಫರ್_Handle_At_ಸೂಚ್ಯಂಕ( CONVERT_ಗಮ್ಯ_ಆಂತರಿಕ_ಸೂಚ್ಯಂಕ( l_ಸೂಚ್ಯಂಕ ) );

                ಆದರೆ( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle != ಖಾಲಿ )
                {
                    xReturn = x_ಹರಿವು_ಬಫರ್_Reset_From_ISR( x_ಆಂತರಿಕ_ಹರಿವು_ಬಫರ್_Handle );
                }
            }

            ಹಿಂತಿರುಗಿ xReturn;
        }

    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h. */

    #ಆದರೆ configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #ಅನ್ತರ್ಭಾವ "application_defined_privileged_functions.h"
    #ಆದರೆ_ಅಂತ್ಯ
/*-----------------------------------------------------------*/

/**
 * @brief Array of system call implementation functions.
 *
 * The index in the array MUST match the corresponding system call number
 * defined in mpu_wrappers.h.
 */
    PRIVILEGED_ದತ್ತಾಂಶ UBaseType_t uxSystemCallImplementations[ ಅಂಕೆ_SYSTEM_CALLS ] =
    {
        #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_xTaskGenericNotifyImpl,                     /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyWaitImpl,                 /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_xTimerGenericCommandFromTaskImpl,           /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_ಗುಂಪು_Wait_ಬಿಟ್ಟುಗಳು_Impl,                    /* SYSTEM_CALL_xEventGroupWaitBits. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupWaitBits. */
        #ಆದರೆ_ಅಂತ್ಯ

        /* The system calls above this line take 5 parameters. */

        #ಆದರೆ ( INCLUDE_xTaskDelayUntil == 1 )
            ( UBaseType_t ) MPU_xTaskDelayUntilImpl,                        /* SYSTEM_CALL_xTaskDelayUntil. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskDelayUntil. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( INCLUDE_xTaskAbortDelay == 1 )
            ( UBaseType_t ) MPU_xTaskAbortDelayImpl,                        /* SYSTEM_CALL_xTaskAbortDelay. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskAbortDelay. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( INCLUDE_vTaskDelay == 1 )
            ( UBaseType_t ) MPU_vTaskDelayImpl,                             /* SYSTEM_CALL_vTaskDelay. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskDelay. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( INCLUDE_ux_Task_ಆದ್ಯತೆ_Get == 1 )
            ( UBaseType_t ) MPU_ux_Task_ಆದ್ಯತೆ_Get_Impl,                      /* SYSTEM_CALL_uxTaskPriorityGet. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskPriorityGet. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( INCLUDE_eTaskGetState == 1 )
            ( UBaseType_t ) MPU_eTaskGetStateImpl,                          /* SYSTEM_CALL_eTaskGetState. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_eTaskGetState. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_vTaskGetInfoImpl,                           /* SYSTEM_CALL_vTaskGetInfo. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskGetInfo. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
            ( UBaseType_t ) MPU_xTaskGetIdleTaskHandleImpl,                 /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( INCLUDE_vTaskSuspend == 1 )
            ( UBaseType_t ) MPU_vTaskSuspendImpl,                           /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) MPU_vTaskResumeImpl,                            /* SYSTEM_CALL_vTaskResume. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskResume. */
        #ಆದರೆ_ಅಂತ್ಯ

        ( UBaseType_t ) MPU_x_Task_Get_Tick_ಎಣಿಕೆ_Impl,                          /* SYSTEM_CALL_xTaskGetTickCount. */
        ( UBaseType_t ) MPU_ux_Task_Get_ಸಂಖ್ಯೆ_ದ_Tasks_Impl,                     /* SYSTEM_CALL_uxTaskGetNumberOfTasks. */

        #ಆದರೆ ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 )
            ( UBaseType_t ) MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Counter_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) MPU_ul_Task_Get_ಸತತ_ಸಮಯ_Percent_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( ( config_GENERATE_ಸತತ_ಸಮಯ_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Percent_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_ಸತತ_ಸಮಯ_Counter_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( config_USE_APPLICATION_TASK_ಟ್ಯಾಗ್ == 1 )
            ( UBaseType_t ) MPU_v_Task_ಗಣ_Application_Task_ಟ್ಯಾಗ್_Impl,             /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) MPU_x_Task_Get_Application_Task_ಟ್ಯಾಗ್_Impl,             /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_ಸೂಚಕಗಳು != 0 )
            ( UBaseType_t ) MPU_v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ_Impl,      /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) MPU_pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ_Impl,     /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_uxTaskGetSystemStateImpl,                   /* SYSTEM_CALL_uxTaskGetSystemState. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetSystemState. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark_Impl,            /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( INCLUDE_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2 == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_ರಾಶಿ_ಮೇಲಿನ_Water_Mark2_Impl,           /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )
            ( UBaseType_t ) MPU_xTaskGetCurrentTaskHandleImpl,              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( INCLUDE_xTaskGetSchedulerState == 1 )
            ( UBaseType_t ) MPU_xTaskGetSchedulerStateImpl,                 /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #ಆದರೆ_ಅಂತ್ಯ

        ( UBaseType_t ) MPU_v_Task_ಗಣ_ಸಮಯ_ಹೊರಹೋಗು_State_Impl,                       /* SYSTEM_CALL_vTaskSetTimeOutState. */
        ( UBaseType_t ) MPU_x_Task_Check_For_ಸಮಯ_ಹೊರಹೋಗು_Impl,                       /* SYSTEM_CALL_xTaskCheckForTimeOut. */

        #ಆದರೆ ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_ulTaskGenericNotifyTakeImpl,                /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyStateClearImpl,           /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) MPU_ul_Task_Generic_Notify_ಮೌಲ್ಯ_Clear_Impl,          /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #ಆದರೆ_ಅಂತ್ಯ

        ( UBaseType_t ) MPU_x_ಸರತಿ_Generic_Send_Impl,                          /* SYSTEM_CALL_xQueueGenericSend. */
        ( UBaseType_t ) MPU_ux_ಸರತಿ_Messages_ಕಾಯುವಿಕೆ_Impl,                     /* SYSTEM_CALL_uxQueueMessagesWaiting. */
        ( UBaseType_t ) MPU_ux_ಸರತಿ_Spaces_ಲಭ್ಯ_Impl,                     /* SYSTEM_CALL_uxQueueSpacesAvailable. */
        ( UBaseType_t ) MPU_x_ಸರತಿ_Receive_Impl,                              /* SYSTEM_CALL_xQueueReceive. */
        ( UBaseType_t ) MPU_x_ಸರತಿ_Peek_Impl,                                 /* SYSTEM_CALL_xQueuePeek. */
        ( UBaseType_t ) MPU_x_ಸರತಿ_Semaphore_Take_Impl,                        /* SYSTEM_CALL_xQueueSemaphoreTake. */

        #ಆದರೆ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
            ( UBaseType_t ) MPU_x_ಸರತಿ_Get_Mutex_Holder_Impl,                   /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( configUSE_RECURSIVE_MUTEXES == 1 )
            ( UBaseType_t ) MPU_x_ಸರತಿ_Take_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) MPU_x_ಸರತಿ_Give_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( config_USE_ಸರತಿ_SETS == 1 )
            ( UBaseType_t ) MPU_x_ಸರತಿ_Select_From_ಗಣ_Impl,                    /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) MPU_x_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_ಗಣ_Impl,                         /* SYSTEM_CALL_xQueueAddToSet. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueAddToSet. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ config_ಸರತಿ_REGISTRY_ಗಾತ್ರ > 0
            ( UBaseType_t ) MPU_v_ಸರತಿ_ಕೂಡಿಸು_ಗಮ್ಯ_Registry_Impl,                    /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) MPU_v_ಸರತಿ_Unregister_ಸರತಿ_Impl,                  /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) MPU_pc_ಸರತಿ_Get_Name_Impl,                         /* SYSTEM_CALL_pcQueueGetName. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcQueueGetName. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_pvTimerGetTimerIDImpl,                      /* SYSTEM_CALL_pvTimerGetTimerID. */
            ( UBaseType_t ) MPU_v_Timer_ಗಣ_Timer_IDImpl,                       /* SYSTEM_CALL_vTimerSetTimerID. */
            ( UBaseType_t ) MPU_x_Timer_Is_Timer_ಸಕ್ರಿಯ_Impl,                    /* SYSTEM_CALL_xTimerIsTimerActive. */
            ( UBaseType_t ) MPU_xTimerGetTimerDaemonTaskHandleImpl,         /* SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle. */
            ( UBaseType_t ) MPU_pcTimerGetNameImpl,                         /* SYSTEM_CALL_pcTimerGetName. */
            ( UBaseType_t ) MPU_v_Timer_ಗಣ_Reload_ಬಹುಲಕ_Impl,                    /* SYSTEM_CALL_vTimerSetReloadMode. */
            ( UBaseType_t ) MPU_x_Timer_Get_Reload_ಬಹುಲಕ_Impl,                    /* SYSTEM_CALL_xTimerGetReloadMode. */
            ( UBaseType_t ) MPU_ux_Timer_Get_Reload_ಬಹುಲಕ_Impl,                   /* SYSTEM_CALL_uxTimerGetReloadMode. */
            ( UBaseType_t ) MPU_xTimerGetPeriodImpl,                        /* SYSTEM_CALL_xTimerGetPeriod. */
            ( UBaseType_t ) MPU_x_Timer_Get_Expiry_ಸಮಯ_Impl,                    /* SYSTEM_CALL_xTimerGetExpiryTime. */
        #ಇಲ್ಲದಿದ್ದರೆ
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
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_ಗುಂಪು_Clear_ಬಿಟ್ಟುಗಳು_Impl,                   /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) MPU_x_Event_ಗುಂಪು_ಗಣ_ಬಿಟ್ಟುಗಳು_Impl,                     /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) MPU_x_Event_ಗುಂಪು_Sync_Impl,                        /* SYSTEM_CALL_xEventGroupSync. */

            #ಆದರೆ ( configUSE_TRACE_FACILITY == 1 )
                ( UBaseType_t ) MPU_ux_Event_ಗುಂಪು_Get_ಸಂಖ್ಯೆ_Impl,              /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) MPU_v_Event_ಗುಂಪು_ಗಣ_ಸಂಖ್ಯೆ_Impl,               /* SYSTEM_CALL_vEventGroupSetNumber. */
            #ಇಲ್ಲದಿದ್ದರೆ
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_vEventGroupSetNumber. */
            #ಆದರೆ_ಅಂತ್ಯ
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSync. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxEventGroupGetNumber. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vEventGroupSetNumber. */
        #ಆದರೆ_ಅಂತ್ಯ

        #ಆದರೆ ( config_USE_ಹರಿವು_BUFFERS == 1 )
            ( UBaseType_t ) MPU_x_ಹರಿವು_ಬಫರ್_Send_Impl,                      /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) MPU_x_ಹರಿವು_ಬಫರ್_Receive_Impl,                   /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) MPU_x_ಹರಿವು_ಬಫರ್_Is_ತುಂಬಿದ_Impl,                    /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) MPU_x_ಹರಿವು_ಬಫರ್_Is_ಖಾಲಿಗಳು_Impl,                   /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) MPU_x_ಹರಿವು_ಬಫರ್_Spaces_ಲಭ್ಯ_Impl,           /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) MPU_x_ಹರಿವು_ಬಫರ್_ಬೈಟುಗಳು_ಲಭ್ಯ_Impl,            /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) MPU_x_ಹರಿವು_ಬಫರ್_ಗಣ_Trigger_Level_Impl,           /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) MPU_x_ಹರಿವು_ಬಫರ್_ಮುಂದಿನ_ಸಂದೇಶ_ಉದ್ದಳತೆ_ಬೈಟುಗಳು_Impl     /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #ಇಲ್ಲದಿದ್ದರೆ
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #ಆದರೆ_ಅಂತ್ಯ

    };
/*-----------------------------------------------------------*/

#ಆದರೆ_ಅಂತ್ಯ /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/
