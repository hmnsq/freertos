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
#నిర్వచించు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "queue.h"
#అన్తర్భావ "timers.h"
#అన్తర్భావ "event_groups.h"
#అన్తర్భావ "stream_buffer.h"
#అన్తర్భావ "mpu_prototypes.h"
#అన్తర్భావ "mpu_syscall_numbers.h"

#నిర్వచనం_రద్దు MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#ఒకవేళ ( ( పోర్టు_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #నిర్వచితం_కాకపోతే config_PROTECTED_KERNEL_OBJECT_POOL_కొలత
        #దోషం config_PROTECTED_KERNEL_OBJECT_POOL_కొలత must be defined గమ్యం గరిష్ఠ సంఖ్య యొక్క kernel objects లోపల the application.
    #అయితే_ముగింపు

/**
 * @brief Offset added to the index before returning to the user.
 *
 * If the actual handle is stored at index i, ( i + INDEX_OFFSET )
 * is returned to the user.
 */
    #నిర్వచించు సూచీ_స్థానభ్రంశం    1

/**
 * @brief Opaque type for a kernel object.
 */
    నిర్మాణం OpaqueObject;
    రకనిర్వచనం నిర్మాణం OpaqueObject * OpaqueObjectHandle_t;

/**
 * @brief Defines kernel object in the kernel object pool.
 */
    రకనిర్వచనం నిర్మాణం KernelObject
    {
        OpaqueObjectHandle_t x_అంతర్గత_Object_Handle;
        uint32_t ulKernelObjectType;
        శూన్య * pv_Kernel_Object_దత్తాంశం;
    } KernelObject_t;

/**
 * @brief Kernel object types.
 */
    #నిర్వచించు KERNEL_OBJECT_TYPE_INVALID          ( 0UL )
    #నిర్వచించు KERNEL_OBJECT_TYPE_వరుస            ( 1UL )
    #నిర్వచించు KERNEL_OBJECT_TYPE_TASK             ( 2UL )
    #నిర్వచించు KERNEL_OBJECT_TYPE_ప్రవాహం_బఫరు    ( 3UL )
    #నిర్వచించు KERNEL_OBJECT_TYPE_EVENT_సమూహం      ( 4UL )
    #నిర్వచించు KERNEL_OBJECT_TYPE_TIMER            ( 5UL )

/**
 * @brief Checks whether an external index is valid or not.
 */
    #నిర్వచించు IS_EXTERNAL_సూచీ_VALID( l_సూచీ )   \
    ( ( ( ( l_సూచీ ) >= సూచీ_స్థానభ్రంశం ) &&       \
        ( ( l_సూచీ ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_కొలత + సూచీ_స్థానభ్రంశం ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Checks whether an internal index is valid or not.
 */
    #నిర్వచించు IS_అంతర్గత_సూచీ_VALID( l_సూచీ )   \
    ( ( ( ( l_సూచీ ) >= 0 ) &&                  \
        ( ( l_సూచీ ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_కొలత ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Converts an internal index into external.
 */
    #నిర్వచించు CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ )    ( ( l_సూచీ ) + సూచీ_స్థానభ్రంశం )

/**
 * @brief Converts an external index into internal.
 */
    #నిర్వచించు CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ )    ( ( l_సూచీ ) - సూచీ_స్థానభ్రంశం )

/**
 * @brief Max value that fits in a UBaseType_t type.
 */
    #నిర్వచించు mpuUBASETYPE_MAX    ( ~( ( UBaseType_t ) 0 ) )

/**
 * @brief Check if multiplying a and b will result in overflow.
 */
    #నిర్వచించు mpu_MULTIPLY_BASETYPE_WILL_అధికప్రవాహం( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( mpuUBASETYPE_MAX / ( a ) ) ) )

/**
 * @brief Get the index of a free slot in the kernel object pool.
 *
 * If a free slot is found, this function marks the slot as
 * "not free".
 *
 * @return Index of a free slot is returned, if a free slot is
 *         found. Otherwise -1 is returned.
 */
    స్థిర int32_t MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool( శూన్య ) PRIVILEGED_FUNCTION;

/**
 * @brief Set the given index as free in the kernel object pool.
 *
 * @param lIndex The index to set as free.
 */
    స్థిర శూన్య MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( int32_t l_సూచీ ) PRIVILEGED_FUNCTION;

/**
 * @brief Get the index at which a given kernel object is stored.
 *
 * @param xHandle The given kernel object handle.
 * @param ulKernelObjectType The kernel object type.
 *
 * @return Index at which the kernel object is stored if it is a valid
 *         handle, -1 otherwise.
 */
    స్థిర int32_t MPU_Get_సూచీ_For_Handle( OpaqueObjectHandle_t xHandle,
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
    స్థిర శూన్య MPU_Store_Handle_And_దత్తాంశం_At_సూచీ( int32_t l_సూచీ,
                                               OpaqueObjectHandle_t xHandle,
                                               శూన్య * pv_Kernel_Object_దత్తాంశం,
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
    స్థిర OpaqueObjectHandle_t MPU_Get_Handle_At_సూచీ( int32_t l_సూచీ,
                                                      uint32_t ulKernelObjectType ) PRIVILEGED_FUNCTION;

    #ఒకవేళ ( configUSE_TIMERS == 1 )

/**
 * @brief The function registered as callback for all the timers.
 *
 * We intercept all the timer callbacks so that we can call application
 * callbacks with opaque handle.
 *
 * @param xInternalHandle The internal timer handle.
 */
        స్థిర శూన్య MPU_TimerCallback( TimerHandle_t x_అంతర్గత_Handle ) PRIVILEGED_FUNCTION;

    #అయితే_ముగింపు /* #if ( configUSE_TIMERS == 1 ) */

/*
 * Wrappers to keep all the casting in one place.
 */
    #నిర్వచించు MPU_Store_వరుస_Handle_At_సూచీ( l_సూచీ, xHandle )                 MPU_Store_Handle_And_దత్తాంశం_At_సూచీ( ( l_సూచీ ), ( OpaqueObjectHandle_t ) ( xHandle ), ఖాళీ, KERNEL_OBJECT_TYPE_వరుస )
    #నిర్వచించు MPU_Get_వరుస_Handle_At_సూచీ( l_సూచీ )                            ( వరుస_Handle_t ) MPU_Get_Handle_At_సూచీ( ( l_సూచీ ), KERNEL_OBJECT_TYPE_వరుస )

    #ఒకవేళ ( config_USE_వరుస_SETS == 1 )
        #నిర్వచించు MPU_Store_వరుస_సమితి_Handle_At_సూచీ( l_సూచీ, xHandle )          MPU_Store_Handle_And_దత్తాంశం_At_సూచీ( ( l_సూచీ ), ( OpaqueObjectHandle_t ) ( xHandle ), ఖాళీ, KERNEL_OBJECT_TYPE_వరుస )
        #నిర్వచించు MPU_Get_వరుస_సమితి_Handle_At_సూచీ( l_సూచీ )                     ( వరుస_సమితి_Handle_t ) MPU_Get_Handle_At_సూచీ( ( l_సూచీ ), KERNEL_OBJECT_TYPE_వరుస )
        #నిర్వచించు MPU_Store_వరుస_సమితి_Member_Handle_At_సూచీ( l_సూచీ, xHandle )    MPU_Store_Handle_And_దత్తాంశం_At_సూచీ( ( l_సూచీ ), ( OpaqueObjectHandle_t ) ( xHandle ), ఖాళీ, KERNEL_OBJECT_TYPE_వరుస )
        #నిర్వచించు MPU_Get_వరుస_సమితి_Member_Handle_At_సూచీ( l_సూచీ )               ( వరుస_సమితి_Member_Handle_t ) MPU_Get_Handle_At_సూచీ( ( l_సూచీ ), KERNEL_OBJECT_TYPE_వరుస )
        #నిర్వచించు MPU_Get_సూచీ_For_వరుస_సమితి_Member_Handle( xHandle )             MPU_Get_సూచీ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_వరుస )
    #అయితే_ముగింపు

/*
 * Wrappers to keep all the casting in one place for Task APIs.
 */
    #నిర్వచించు MPU_Store_Task_Handle_At_సూచీ( l_సూచీ, xHandle )            MPU_Store_Handle_And_దత్తాంశం_At_సూచీ( ( l_సూచీ ), ( OpaqueObjectHandle_t ) ( xHandle ), ఖాళీ, KERNEL_OBJECT_TYPE_TASK )
    #నిర్వచించు MPU_Get_Task_Handle_At_సూచీ( l_సూచీ )                       ( TaskHandle_t ) MPU_Get_Handle_At_సూచీ( ( l_సూచీ ), KERNEL_OBJECT_TYPE_TASK )
    #నిర్వచించు MPU_Get_సూచీ_For_Task_Handle( xHandle )                     MPU_Get_సూచీ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TASK )

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )
/*
 * Wrappers to keep all the casting in one place for Event Group APIs.
 */
        #నిర్వచించు MPU_Store_Event_సమూహం_Handle_At_సూచీ( l_సూచీ, xHandle )      MPU_Store_Handle_And_దత్తాంశం_At_సూచీ( ( l_సూచీ ), ( OpaqueObjectHandle_t ) ( xHandle ), ఖాళీ, KERNEL_OBJECT_TYPE_EVENT_సమూహం )
        #నిర్వచించు MPU_Get_Event_సమూహం_Handle_At_సూచీ( l_సూచీ )                 ( Event_సమూహం_Handle_t ) MPU_Get_Handle_At_సూచీ( ( l_సూచీ ), KERNEL_OBJECT_TYPE_EVENT_సమూహం )
        #నిర్వచించు MPU_Get_సూచీ_For_Event_సమూహం_Handle( xHandle )               MPU_Get_సూచీ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_EVENT_సమూహం )

    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Stream Buffer APIs.
 */
        #నిర్వచించు MPU_Store_ప్రవాహం_బఫరు_Handle_At_సూచీ( l_సూచీ, xHandle )    MPU_Store_Handle_And_దత్తాంశం_At_సూచీ( ( l_సూచీ ), ( OpaqueObjectHandle_t ) ( xHandle), ఖాళీ, KERNEL_OBJECT_TYPE_ప్రవాహం_బఫరు )
        #నిర్వచించు MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( l_సూచీ )               ( ప్రవాహం_బఫరు_Handle_t ) MPU_Get_Handle_At_సూచీ( ( l_సూచీ ), KERNEL_OBJECT_TYPE_ప్రవాహం_బఫరు )
        #నిర్వచించు MPU_Get_సూచీ_For_ప్రవాహం_బఫరు_Handle( xHandle )             MPU_Get_సూచీ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_ప్రవాహం_బఫరు )

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

    #ఒకవేళ ( configUSE_TIMERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Timer APIs.
 */
        #నిర్వచించు MPU_Store_Timer_Handle_At_సూచీ( l_సూచీ, xHandle, pxApplicationCallback )    MPU_Store_Handle_And_దత్తాంశం_At_సూచీ( ( l_సూచీ ), ( OpaqueObjectHandle_t ) ( xHandle ), ( శూన్య * ) ( pxApplicationCallback ), KERNEL_OBJECT_TYPE_TIMER )
        #నిర్వచించు MPU_Get_Timer_Handle_At_సూచీ( l_సూచీ )                                      ( TimerHandle_t ) MPU_Get_Handle_At_సూచీ( ( l_సూచీ ), KERNEL_OBJECT_TYPE_TIMER )
        #నిర్వచించు MPU_Get_సూచీ_For_Timer_Handle( xHandle )                                    MPU_Get_సూచీ_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TIMER )

    #అయితే_ముగింపు /* #if ( configUSE_TIMERS == 1 ) */

/*-----------------------------------------------------------*/

/**
 * @brief Kernel object pool.
 */
    PRIVILEGED_దత్తాంశం స్థిర KernelObject_t xKernelObjectPool[ config_PROTECTED_KERNEL_OBJECT_POOL_కొలత ] = { 0 };
/*-----------------------------------------------------------*/

    స్థిర int32_t MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool( శూన్య ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_Free_సూచీ = -1;

        /* This function is called only from resource create APIs
         * which are not supposed to be called from ISRs. Therefore,
         * we only need to suspend the scheduler and do not require
         * critical section. */
        vTaskSuspendAll();
        {
            కొరకు( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_కొలత; i++ )
            {
                ఒకవేళ( xKernelObjectPool[ i ].x_అంతర్గత_Object_Handle == ఖాళీ )
                {
                    /* Mark this index as not free. */
                    xKernelObjectPool[ i ].x_అంతర్గత_Object_Handle = ( OpaqueObjectHandle_t ) ( ~0U );
                    l_Free_సూచీ = i;
                    ఆపు;
                }
            }
        }
        ( శూన్య ) xTaskResumeAll();

        తిరిగి l_Free_సూచీ;
    }
/*-----------------------------------------------------------*/

    స్థిర శూన్య MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( int32_t l_సూచీ ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_అంతర్గత_సూచీ_VALID( l_సూచీ ) != pdFALSE );

        taskENTER_CRITICAL();
        {
            xKernelObjectPool[ l_సూచీ ].x_అంతర్గత_Object_Handle = ఖాళీ;
            xKernelObjectPool[ l_సూచీ ].ulKernelObjectType = KERNEL_OBJECT_TYPE_INVALID;
            xKernelObjectPool[ l_సూచీ ].pv_Kernel_Object_దత్తాంశం = ఖాళీ;
        }
        taskEXIT_CRITICAL();
    }
/*-----------------------------------------------------------*/

    స్థిర int32_t MPU_Get_సూచీ_For_Handle( OpaqueObjectHandle_t xHandle,
                                          uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_సూచీ = -1;

        configASSERT( xHandle != ఖాళీ );

        కొరకు( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_కొలత; i++ )
        {
            ఒకవేళ( ( xKernelObjectPool[ i ].x_అంతర్గత_Object_Handle == xHandle ) &&
                ( xKernelObjectPool[ i ].ulKernelObjectType == ulKernelObjectType ) )
            {
                l_సూచీ = i;
                ఆపు;
            }
        }

        తిరిగి l_సూచీ;
    }
/*-----------------------------------------------------------*/

    స్థిర శూన్య MPU_Store_Handle_And_దత్తాంశం_At_సూచీ( int32_t l_సూచీ,
                                               OpaqueObjectHandle_t xHandle,
                                               శూన్య * pv_Kernel_Object_దత్తాంశం,
                                               uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_అంతర్గత_సూచీ_VALID( l_సూచీ ) != pdFALSE );
        xKernelObjectPool[ l_సూచీ ].x_అంతర్గత_Object_Handle = xHandle;
        xKernelObjectPool[ l_సూచీ ].ulKernelObjectType = ulKernelObjectType;
        xKernelObjectPool[ l_సూచీ ].pv_Kernel_Object_దత్తాంశం = pv_Kernel_Object_దత్తాంశం;
    }
/*-----------------------------------------------------------*/

    స్థిర OpaqueObjectHandle_t MPU_Get_Handle_At_సూచీ( int32_t l_సూచీ,
                                                      uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        OpaqueObjectHandle_t xObjectHandle = ఖాళీ;

        configASSERT( IS_అంతర్గత_సూచీ_VALID( l_సూచీ ) != pdFALSE );

        ఒకవేళ( xKernelObjectPool[ l_సూచీ ].ulKernelObjectType == ulKernelObjectType )
        {
            xObjectHandle = xKernelObjectPool[ l_సూచీ ].x_అంతర్గత_Object_Handle;
        }

        తిరిగి xObjectHandle;
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        శూన్య v_Grant_Access_గమ్యం_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                         int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                ఒకవేళ( xExternalTaskHandle == ఖాళీ )
                {
                    v_పోర్టు_Grant_Access_గమ్యం_Kernel_Object( xExternalTaskHandle, CONVERT_గమ్యం_అంతర్గత_సూచీ( lExternalKernelObjectHandle ) );
                }
                లేకపోతే
                {
                    l_External_Task_సూచీ = ( int32_t ) xExternalTaskHandle;

                    ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_External_Task_సూచీ ) != pdFALSE )
                    {
                        x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_External_Task_సూచీ ) );

                        ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                        {
                            v_పోర్టు_Grant_Access_గమ్యం_Kernel_Object( x_అంతర్గత_Task_Handle,
                                                            CONVERT_గమ్యం_అంతర్గత_సూచీ( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #అయితే_ముగింపు /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        శూన్య v_Revoke_Access_గమ్యం_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                          int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                ఒకవేళ( xExternalTaskHandle == ఖాళీ )
                {
                    v_పోర్టు_Revoke_Access_గమ్యం_Kernel_Object( xExternalTaskHandle, CONVERT_గమ్యం_అంతర్గత_సూచీ( lExternalKernelObjectHandle ) );
                }
                లేకపోతే
                {
                    l_External_Task_సూచీ = ( int32_t ) xExternalTaskHandle;

                    ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_External_Task_సూచీ ) != pdFALSE )
                    {
                        x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_External_Task_సూచీ ) );

                        ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                        {
                            v_పోర్టు_Revoke_Access_గమ్యం_Kernel_Object( x_అంతర్గత_Task_Handle,
                                                             CONVERT_గమ్యం_అంతర్గత_సూచీ( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #అయితే_ముగింపు /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        స్థిర శూన్య MPU_TimerCallback( TimerHandle_t x_అంతర్గత_Handle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t i, l_సూచీ = -1;
            TimerHandle_t xExternalHandle = ఖాళీ;
            TimerCallbackFunction_t px_Application_Call_వెనుక = ఖాళీ;

            /* Coming from the timer task and therefore, should be valid. */
            configASSERT( x_అంతర్గత_Handle != ఖాళీ );

            కొరకు( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_కొలత; i++ )
            {
                ఒకవేళ( ( ( TimerHandle_t ) xKernelObjectPool[ i ].x_అంతర్గత_Object_Handle == x_అంతర్గత_Handle ) &&
                    ( xKernelObjectPool[ i ].ulKernelObjectType == KERNEL_OBJECT_TYPE_TIMER ) )
                {
                    l_సూచీ = i;
                    ఆపు;
                }
            }

            configASSERT( l_సూచీ != -1 );
            xExternalHandle = ( TimerHandle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );

            px_Application_Call_వెనుక = ( TimerCallbackFunction_t ) xKernelObjectPool[ l_సూచీ ].pv_Kernel_Object_దత్తాంశం;
            px_Application_Call_వెనుక( xExternalHandle );
        }

    #అయితే_ముగింపు /* #if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for tasks APIs.                   */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskDelayUntil == 1 )

        పునాది_Type_t MPU_xTaskDelayUntilImpl( TickType_t * స్థిరరాశి px_మునుపటి_Wake_సమయం,
                                            TickType_t x_సమయం_Increment ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_xTaskDelayUntilImpl( TickType_t * స్థిరరాశి px_మునుపటి_Wake_సమయం,
                                            TickType_t x_సమయం_Increment ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            పునాది_Type_t x_Is_మునుపటి_Wake_సమయం_Accessible = pdFALSE;

            ఒకవేళ( ( px_మునుపటి_Wake_సమయం != ఖాళీ ) && ( x_సమయం_Increment > 0U ) )
            {
                x_Is_మునుపటి_Wake_సమయం_Accessible = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( px_మునుపటి_Wake_సమయం,
                                                                                 పరిమాణం( TickType_t ),
                                                                                 ( tskMPU_WRITE_PERMISSION | tskMPU_READ_PERMISSION ) );

                ఒకవేళ( x_Is_మునుపటి_Wake_సమయం_Accessible == pdTRUE )
                {
                    xReturn = xTaskDelayUntil( px_మునుపటి_Wake_సమయం, x_సమయం_Increment );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskAbortDelay == 1 )

        పునాది_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = ( int32_t ) xTask;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                {
                    x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                    {
                        xReturn = xTaskAbortDelay( x_అంతర్గత_Task_Handle );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_vTaskDelay == 1 )

        శూన్య MPU_vTaskDelayImpl( TickType_t x_Ticks_గమ్యం_Delay ) PRIVILEGED_FUNCTION;

        శూన్య MPU_vTaskDelayImpl( TickType_t x_Ticks_గమ్యం_Delay ) /* PRIVILEGED_FUNCTION */
        {
            vTaskDelay( x_Ticks_గమ్యం_Delay );
        }

    #అయితే_ముగింపు /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_ux_Task_ప్రాధాన్యత_Get == 1 )

        UBaseType_t MPU_ux_Task_ప్రాధాన్యత_Get_Impl( స్థిరరాశి TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_ప్రాధాన్యత_Get_Impl( స్థిరరాశి TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

            ఒకవేళ( pxTask == ఖాళీ )
            {
                uxReturn = ux_Task_ప్రాధాన్యత_Get( pxTask );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) pxTask;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                    {
                        x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                        {
                            uxReturn = ux_Task_ప్రాధాన్యత_Get( x_అంతర్గత_Task_Handle );
                        }
                    }
                }
            }

            తిరిగి uxReturn;
        }

    #అయితే_ముగింపు /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            eTaskState eReturn = eInvalid;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;

            l_సూచీ = ( int32_t ) pxTask;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                {
                    x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                    {
                        eReturn = eTaskGetState( x_అంతర్గత_Task_Handle );
                    }
                }
            }

            తిరిగి eReturn;
        }

    #అయితే_ముగింపు /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TRACE_FACILITY == 1 )

        శూన్య MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_స్థితి_t * px_Task_స్థితి,
                                   పునాది_Type_t x_Get_Free_దొంతర_Space,
                                   eTaskState eState ) PRIVILEGED_FUNCTION;

        శూన్య MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_స్థితి_t * px_Task_స్థితి,
                                   పునాది_Type_t x_Get_Free_దొంతర_Space,
                                   eTaskState eState ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            పునాది_Type_t x_Is_Task_స్థితి_Writeable = pdFALSE;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;

            x_Is_Task_స్థితి_Writeable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( px_Task_స్థితి,
                                                                      పరిమాణం( Task_స్థితి_t ),
                                                                      tskMPU_WRITE_PERMISSION );

            ఒకవేళ( x_Is_Task_స్థితి_Writeable == pdTRUE )
            {
                ఒకవేళ( xTask == ఖాళీ )
                {
                    vTaskGetInfo( xTask, px_Task_స్థితి, x_Get_Free_దొంతర_Space, eState );
                }
                లేకపోతే
                {
                    l_సూచీ = ( int32_t ) xTask;

                    ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                        {
                            x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                            ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                            {
                                vTaskGetInfo( x_అంతర్గత_Task_Handle, px_Task_స్థితి, x_Get_Free_దొంతర_Space, eState );
                            }
                        }
                    }
                }
            }
        }

    #అయితే_ముగింపు /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( శూన్య ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( శూన్య ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xIdleTaskHandle = ఖాళీ;

            xIdleTaskHandle = xTaskGetIdleTaskHandle();

            తిరిగి xIdleTaskHandle;
        }

    #అయితే_ముగింపు /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_vTaskSuspend == 1 )

        శూన్య MPU_vTaskSuspendImpl( TaskHandle_t px_Task_గమ్యం_Suspend ) PRIVILEGED_FUNCTION;

        శూన్య MPU_vTaskSuspendImpl( TaskHandle_t px_Task_గమ్యం_Suspend ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;

            ఒకవేళ( px_Task_గమ్యం_Suspend == ఖాళీ )
            {
                vTaskSuspend( px_Task_గమ్యం_Suspend );
            }
            లేకపోతే
            {
                /* After the scheduler starts, only privileged tasks are allowed
                 * to suspend other tasks. */
                #ఒకవేళ ( INCLUDE_xTaskGetSchedulerState == 1 )
                    ఒకవేళ( ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) || ( పోర్టు_IS_TASK_PRIVILEGED() == pdTRUE ) )
                #లేకపోతే
                    ఒకవేళ( పోర్టు_IS_TASK_PRIVILEGED() == pdTRUE )
                #అయితే_ముగింపు
                {
                    l_సూచీ = ( int32_t ) px_Task_గమ్యం_Suspend;

                    ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                        {
                            x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                            ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                            {
                                vTaskSuspend( x_అంతర్గత_Task_Handle );
                            }
                        }
                    }
                }
            }
        }

    #అయితే_ముగింపు /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_vTaskSuspend == 1 )

        శూన్య MPU_vTaskResumeImpl( TaskHandle_t px_Task_గమ్యం_Resume ) PRIVILEGED_FUNCTION;

        శూన్య MPU_vTaskResumeImpl( TaskHandle_t px_Task_గమ్యం_Resume ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;

            l_సూచీ = ( int32_t ) px_Task_గమ్యం_Resume;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                {
                    x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                    {
                        vTaskResume( x_అంతర్గత_Task_Handle );
                    }
                }
            }
        }

    #అయితే_ముగింపు /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_లెక్క_Impl( శూన్య ) PRIVILEGED_FUNCTION;

    TickType_t MPU_x_Task_Get_Tick_లెక్క_Impl( శూన్య ) /* PRIVILEGED_FUNCTION */
    {
        TickType_t xReturn;

        xReturn = x_Task_Get_Tick_లెక్క();

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks_Impl( శూన్య ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks_Impl( శూన్య ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn;

        uxReturn = ux_Task_Get_సంఖ్య_యొక్క_Tasks();

        తిరిగి uxReturn;
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 )

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Counter_Impl( స్థిరరాశి TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Counter_Impl( స్థిరరాశి TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_నిరంతరం_సమయం_COUNTER_TYPE xReturn = 0;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;

            ఒకవేళ( xTask == ఖాళీ )
            {
                xReturn = ul_Task_Get_నిరంతరం_సమయం_Counter( xTask );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) xTask;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                    {
                        x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                        {
                            xReturn = ul_Task_Get_నిరంతరం_సమయం_Counter( x_అంతర్గత_Task_Handle );
                        }
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 )

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Percent_Impl( స్థిరరాశి TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_నిరంతరం_సమయం_Percent_Impl( స్థిరరాశి TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_నిరంతరం_సమయం_COUNTER_TYPE xReturn = 0;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;

            ఒకవేళ( xTask == ఖాళీ )
            {
                xReturn = ul_Task_Get_నిరంతరం_సమయం_Percent( xTask );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) xTask;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                    {
                        x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                        {
                            xReturn = ul_Task_Get_నిరంతరం_సమయం_Percent( x_అంతర్గత_Task_Handle );
                        }
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent_Impl( శూన్య ) PRIVILEGED_FUNCTION;

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent_Impl( శూన్య ) /* PRIVILEGED_FUNCTION */
        {
            config_నిరంతరం_సమయం_COUNTER_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_నిరంతరం_సమయం_Percent();

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter_Impl( శూన్య ) PRIVILEGED_FUNCTION;

        config_నిరంతరం_సమయం_COUNTER_TYPE MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter_Impl( శూన్య ) /* PRIVILEGED_FUNCTION */
        {
            config_నిరంతరం_సమయం_COUNTER_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_నిరంతరం_సమయం_Counter();

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )

        శూన్య MPU_v_Task_సమితి_Application_Task_ట్యాగ్_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_ట్యాగ్_విలువ ) PRIVILEGED_FUNCTION;

        శూన్య MPU_v_Task_సమితి_Application_Task_ట్యాగ్_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_ట్యాగ్_విలువ ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;

            ఒకవేళ( xTask == ఖాళీ )
            {
                v_Task_సమితి_Application_Task_ట్యాగ్( xTask, px_ట్యాగ్_విలువ );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) xTask;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                    {
                        x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                        {
                            v_Task_సమితి_Application_Task_ట్యాగ్( x_అంతర్గత_Task_Handle, px_ట్యాగ్_విలువ );
                        }
                    }
                }
            }
        }

    #అయితే_ముగింపు /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ట్యాగ్_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ట్యాగ్_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = ఖాళీ;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;

            ఒకవేళ( xTask == ఖాళీ )
            {
                xReturn = x_Task_Get_Application_Task_ట్యాగ్( xTask );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) xTask;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                    {
                        x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                        {
                            xReturn = x_Task_Get_Application_Task_ట్యాగ్( x_అంతర్గత_Task_Handle );
                        }
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_అంకె_THREAD_LOCAL_STORAGE_సూచికలు != 0 )

        శూన్య MPU_v_Task_సమితి_Thread_Local_Storage_సూచిక_Impl( TaskHandle_t x_Task_గమ్యం_సమితి,
                                                        పునాది_Type_t x_సూచీ,
                                                        శూన్య * pv_విలువ ) PRIVILEGED_FUNCTION;

        శూన్య MPU_v_Task_సమితి_Thread_Local_Storage_సూచిక_Impl( TaskHandle_t x_Task_గమ్యం_సమితి,
                                                        పునాది_Type_t x_సూచీ,
                                                        శూన్య * pv_విలువ ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;

            ఒకవేళ( x_Task_గమ్యం_సమితి == ఖాళీ )
            {
                v_Task_సమితి_Thread_Local_Storage_సూచిక( x_Task_గమ్యం_సమితి, x_సూచీ, pv_విలువ );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) x_Task_గమ్యం_సమితి;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                    {
                        x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                        {
                            v_Task_సమితి_Thread_Local_Storage_సూచిక( x_అంతర్గత_Task_Handle, x_సూచీ, pv_విలువ );
                        }
                    }
                }
            }
        }

    #అయితే_ముగింపు /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_అంకె_THREAD_LOCAL_STORAGE_సూచికలు != 0 )

        శూన్య * MPU_pv_Task_Get_Thread_Local_Storage_సూచిక_Impl( TaskHandle_t x_Task_గమ్యం_Query,
                                                           పునాది_Type_t x_సూచీ ) PRIVILEGED_FUNCTION;

        శూన్య * MPU_pv_Task_Get_Thread_Local_Storage_సూచిక_Impl( TaskHandle_t x_Task_గమ్యం_Query,
                                                           పునాది_Type_t x_సూచీ ) /* PRIVILEGED_FUNCTION */
        {
            శూన్య * pvReturn = ఖాళీ;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;

            ఒకవేళ( x_Task_గమ్యం_Query == ఖాళీ )
            {
                pvReturn = pv_Task_Get_Thread_Local_Storage_సూచిక( x_Task_గమ్యం_Query, x_సూచీ );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) x_Task_గమ్యం_Query;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                    {
                        x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                        {
                            pvReturn = pv_Task_Get_Thread_Local_Storage_సూచిక( x_అంతర్గత_Task_Handle, x_సూచీ );
                        }
                    }
                }
            }

            తిరిగి pvReturn;
        }

    #అయితే_ముగింపు /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_స్థితి_t * px_Task_స్థితి_Array,
                                                  UBaseType_t ux_Array_కొలత,
                                                  config_నిరంతరం_సమయం_COUNTER_TYPE * pul_మొత్తం_నిరంతరం_సమయం ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_స్థితి_t * px_Task_స్థితి_Array,
                                                  UBaseType_t ux_Array_కొలత,
                                                  config_నిరంతరం_సమయం_COUNTER_TYPE * pul_మొత్తం_నిరంతరం_సమయం ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            పునాది_Type_t x_Is_Task_స్థితి_Array_Writeable = pdFALSE;
            పునాది_Type_t x_Is_మొత్తం_నిరంతరం_సమయం_Writeable = pdFALSE;

            ఒకవేళ( mpu_MULTIPLY_BASETYPE_WILL_అధికప్రవాహం( పరిమాణం( Task_స్థితి_t ), ux_Array_కొలత ) == 0 )
            {
                x_Is_Task_స్థితి_Array_Writeable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( px_Task_స్థితి_Array,
                                                                               పరిమాణం( Task_స్థితి_t ) * ( size_t ) ux_Array_కొలత,
                                                                               tskMPU_WRITE_PERMISSION );

                ఒకవేళ( pul_మొత్తం_నిరంతరం_సమయం != ఖాళీ )
                {
                    x_Is_మొత్తం_నిరంతరం_సమయం_Writeable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( pul_మొత్తం_నిరంతరం_సమయం,
                                                                                పరిమాణం( config_నిరంతరం_సమయం_COUNTER_TYPE ),
                                                                                tskMPU_WRITE_PERMISSION );
                }

                ఒకవేళ( ( x_Is_Task_స్థితి_Array_Writeable == pdTRUE ) &&
                    ( ( pul_మొత్తం_నిరంతరం_సమయం == ఖాళీ ) || ( x_Is_మొత్తం_నిరంతరం_సమయం_Writeable == pdTRUE ) ) )
                {
                    uxReturn = uxTaskGetSystemState( px_Task_స్థితి_Array, ux_Array_కొలత, pul_మొత్తం_నిరంతరం_సమయం );
                }
            }

            తిరిగి uxReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_ux_Task_Get_దొంతర_ఎగువ_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;

            ఒకవేళ( xTask == ఖాళీ )
            {
                uxReturn = ux_Task_Get_దొంతర_ఎగువ_Water_Mark( xTask );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) xTask;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                    {
                        x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                        {
                            uxReturn = ux_Task_Get_దొంతర_ఎగువ_Water_Mark( x_అంతర్గత_Task_Handle );
                        }
                    }
                }
            }

            తిరిగి uxReturn;
        }

    #అయితే_ముగింపు /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2 == 1 )

        config_దొంతర_లోతు_TYPE MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_దొంతర_లోతు_TYPE MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_దొంతర_లోతు_TYPE uxReturn = 0;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;

            ఒకవేళ( xTask == ఖాళీ )
            {
                uxReturn = ux_Task_Get_దొంతర_ఎగువ_Water_Mark2( xTask );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) xTask;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                    {
                        x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                        {
                            uxReturn = ux_Task_Get_దొంతర_ఎగువ_Water_Mark2( x_అంతర్గత_Task_Handle );
                        }
                    }
                }
            }

            తిరిగి uxReturn;
        }

    #అయితే_ముగింపు /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( శూన్య ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( శూన్య ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            TaskHandle_t xExternalTaskHandle = ఖాళీ;
            int32_t l_సూచీ;

            x_అంతర్గత_Task_Handle = xTaskGetCurrentTaskHandle();

            ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
            {
                l_సూచీ = MPU_Get_సూచీ_For_Task_Handle( x_అంతర్గత_Task_Handle );

                ఒకవేళ( l_సూచీ != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
            }

            తిరిగి xExternalTaskHandle;
        }

    #అయితే_ముగింపు /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskGetSchedulerState == 1 )

        పునాది_Type_t MPU_xTaskGetSchedulerStateImpl( శూన్య ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_xTaskGetSchedulerStateImpl( శూన్య ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = taskSCHEDULER_NOT_STARTED;

            xReturn = xTaskGetSchedulerState();

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    శూన్య MPU_v_Task_సమితి_సమయం_బహిర్గతం_State_Impl( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం ) PRIVILEGED_FUNCTION;

    శూన్య MPU_v_Task_సమితి_సమయం_బహిర్గతం_State_Impl( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం ) /* PRIVILEGED_FUNCTION */
    {
        పునాది_Type_t x_Is_సమయం_బహిర్గతం_Writeable = pdFALSE;

        ఒకవేళ( px_సమయం_బహిర్గతం != ఖాళీ )
        {
            x_Is_సమయం_బహిర్గతం_Writeable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( px_సమయం_బహిర్గతం,
                                                                   పరిమాణం( సమయం_బహిర్గతం_t ),
                                                                   tskMPU_WRITE_PERMISSION );

            ఒకవేళ( x_Is_సమయం_బహిర్గతం_Writeable == pdTRUE )
            {
                v_Task_సమితి_సమయం_బహిర్గతం_State( px_సమయం_బహిర్గతం );
            }
        }
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_Task_Check_For_సమయం_బహిర్గతం_Impl( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం,
                                             TickType_t * స్థిరరాశి px_Ticks_గమ్యం_Wait ) PRIVILEGED_FUNCTION;

    పునాది_Type_t MPU_x_Task_Check_For_సమయం_బహిర్గతం_Impl( సమయం_బహిర్గతం_t * స్థిరరాశి px_సమయం_బహిర్గతం,
                                             TickType_t * స్థిరరాశి px_Ticks_గమ్యం_Wait ) /* PRIVILEGED_FUNCTION */
    {
        పునాది_Type_t xReturn = pdFALSE;
        పునాది_Type_t x_Is_సమయం_బహిర్గతం_Writeable = pdFALSE;
        పునాది_Type_t x_Is_Ticks_గమ్యం_Wait_Writeable = pdFALSE;

        ఒకవేళ( ( px_సమయం_బహిర్గతం != ఖాళీ ) && ( px_Ticks_గమ్యం_Wait != ఖాళీ ) )
        {
            x_Is_సమయం_బహిర్గతం_Writeable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( px_సమయం_బహిర్గతం,
                                                                   పరిమాణం( సమయం_బహిర్గతం_t ),
                                                                   tskMPU_WRITE_PERMISSION );
            x_Is_Ticks_గమ్యం_Wait_Writeable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( px_Ticks_గమ్యం_Wait,
                                                                       పరిమాణం( TickType_t ),
                                                                       tskMPU_WRITE_PERMISSION );

            ఒకవేళ( ( x_Is_సమయం_బహిర్గతం_Writeable == pdTRUE ) && ( x_Is_Ticks_గమ్యం_Wait_Writeable == pdTRUE ) )
            {
                xReturn = x_Task_Check_For_సమయం_బహిర్గతం( px_సమయం_బహిర్గతం, px_Ticks_గమ్యం_Wait );
            }
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        పునాది_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_గమ్యం_Notify,
                                           UBaseType_t ux_సూచీ_గమ్యం_Notify,
                                           uint32_t ul_విలువ,
                                           eNotifyAction eAction,
                                           uint32_t * pul_మునుపటి_Notification_విలువ ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyParams_t xParams;

            xParams.x_Task_గమ్యం_Notify = x_Task_గమ్యం_Notify;
            xParams.ux_సూచీ_గమ్యం_Notify = ux_సూచీ_గమ్యం_Notify;
            xParams.ul_విలువ = ul_విలువ;
            xParams.eAction = eAction;
            xParams.pul_మునుపటి_Notification_విలువ = pul_మునుపటి_Notification_విలువ;

            xReturn = MPU_x_Task_Generic_Notify_నమోదు( &( xParams ) );

            తిరిగి xReturn;
        }

        పునాది_Type_t MPU_xTaskGenericNotifyImpl( స్థిరరాశి xTaskGenericNotifyParams_t * pxParams ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_xTaskGenericNotifyImpl( స్థిరరాశి xTaskGenericNotifyParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            పునాది_Type_t x_Is_మునుపటి_Notification_విలువ_Writeable = pdFALSE;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;
            పునాది_Type_t xAreParamsReadable = pdFALSE;

            ఒకవేళ( pxParams != ఖాళీ )
            {
                xAreParamsReadable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( pxParams,
                                                                      పరిమాణం( xTaskGenericNotifyParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ఒకవేళ( xAreParamsReadable == pdTRUE )
            {
                ఒకవేళ( ( pxParams->ux_సూచీ_గమ్యం_Notify < configTASK_NOTIFICATION_ARRAY_ENTRIES ) &&
                    ( ( pxParams->eAction == eNoAction ) ||
                      ( pxParams->eAction == e_సమితి_బిట్లు ) ||
                      ( pxParams->eAction == eIncrement ) ||
                      ( pxParams->eAction == e_సమితి_విలువ_With_Overwrite ) ||
                      ( pxParams->eAction == e_సమితి_విలువ_Without_Overwrite ) ) )
                {
                    ఒకవేళ( pxParams->pul_మునుపటి_Notification_విలువ != ఖాళీ )
                    {
                        x_Is_మునుపటి_Notification_విలువ_Writeable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( pxParams->pul_మునుపటి_Notification_విలువ,
                                                                                                 పరిమాణం( uint32_t ),
                                                                                                 tskMPU_WRITE_PERMISSION );
                    }

                    ఒకవేళ( ( pxParams->pul_మునుపటి_Notification_విలువ == ఖాళీ ) ||
                        ( x_Is_మునుపటి_Notification_విలువ_Writeable == pdTRUE ) )
                    {
                        l_సూచీ = ( int32_t ) ( pxParams->x_Task_గమ్యం_Notify );

                        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                            ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                            {
                                x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                                ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                                {
                                    xReturn = xTaskGenericNotify( x_అంతర్గత_Task_Handle,
                                                                  pxParams->ux_సూచీ_గమ్యం_Notify,
                                                                  pxParams->ul_విలువ,
                                                                  pxParams->eAction,
                                                                  pxParams->pul_మునుపటి_Notification_విలువ );
                                }
                            }
                        }
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        పునాది_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_సూచీ_గమ్యం_Wait_On,
                                               uint32_t ul_బిట్లు_గమ్యం_Clear_On_నమోదు,
                                               uint32_t ul_బిట్లు_గమ్యం_Clear_On_Exit,
                                               uint32_t * pul_Notification_విలువ,
                                               TickType_t x_Ticks_గమ్యం_Wait )
        {
            పునాది_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyWaitParams_t xParams;

            xParams.ux_సూచీ_గమ్యం_Wait_On = ux_సూచీ_గమ్యం_Wait_On;
            xParams.ul_బిట్లు_గమ్యం_Clear_On_నమోదు = ul_బిట్లు_గమ్యం_Clear_On_నమోదు;
            xParams.ul_బిట్లు_గమ్యం_Clear_On_Exit = ul_బిట్లు_గమ్యం_Clear_On_Exit;
            xParams.pul_Notification_విలువ = pul_Notification_విలువ;
            xParams.x_Ticks_గమ్యం_Wait = x_Ticks_గమ్యం_Wait;

            xReturn = MPU_x_Task_Generic_Notify_Wait_నమోదు( &( xParams ) );

            తిరిగి xReturn;
        }

        పునాది_Type_t MPU_xTaskGenericNotifyWaitImpl( స్థిరరాశి xTaskGenericNotifyWaitParams_t * pxParams ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_xTaskGenericNotifyWaitImpl( స్థిరరాశి xTaskGenericNotifyWaitParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            పునాది_Type_t x_Is_Notification_విలువ_Writable = pdFALSE;
            పునాది_Type_t xAreParamsReadable = pdFALSE;

            ఒకవేళ( pxParams != ఖాళీ )
            {
                xAreParamsReadable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( pxParams,
                                                                      పరిమాణం( xTaskGenericNotifyWaitParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ఒకవేళ( xAreParamsReadable == pdTRUE )
            {
                ఒకవేళ( pxParams->ux_సూచీ_గమ్యం_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
                {
                    ఒకవేళ( pxParams->pul_Notification_విలువ != ఖాళీ )
                    {
                        x_Is_Notification_విలువ_Writable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( pxParams->pul_Notification_విలువ,
                                                                                        పరిమాణం( uint32_t ),
                                                                                        tskMPU_WRITE_PERMISSION );
                    }

                    ఒకవేళ( ( pxParams->pul_Notification_విలువ == ఖాళీ ) ||
                        ( x_Is_Notification_విలువ_Writable == pdTRUE ) )
                    {
                        xReturn = xTaskGenericNotifyWait( pxParams->ux_సూచీ_గమ్యం_Wait_On,
                                                          pxParams->ul_బిట్లు_గమ్యం_Clear_On_నమోదు,
                                                          pxParams->ul_బిట్లు_గమ్యం_Clear_On_Exit,
                                                          pxParams->pul_Notification_విలువ,
                                                          pxParams->x_Ticks_గమ్యం_Wait );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_సూచీ_గమ్యం_Wait_On,
                                                  పునాది_Type_t x_Clear_లెక్క_On_Exit,
                                                  TickType_t x_Ticks_గమ్యం_Wait ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_సూచీ_గమ్యం_Wait_On,
                                                  పునాది_Type_t x_Clear_లెక్క_On_Exit,
                                                  TickType_t x_Ticks_గమ్యం_Wait ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;

            ఒకవేళ( ux_సూచీ_గమ్యం_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ulReturn = ulTaskGenericNotifyTake( ux_సూచీ_గమ్యం_Wait_On, x_Clear_లెక్క_On_Exit, x_Ticks_గమ్యం_Wait );
            }

            తిరిగి ulReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        పునాది_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_సూచీ_గమ్యం_Clear ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_సూచీ_గమ్యం_Clear ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;

            ఒకవేళ( ux_సూచీ_గమ్యం_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ఒకవేళ( xTask == ఖాళీ )
                {
                    xReturn = xTaskGenericNotifyStateClear( xTask, ux_సూచీ_గమ్యం_Clear );
                }
                లేకపోతే
                {
                    l_సూచీ = ( int32_t ) xTask;

                    ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                        {
                            x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                            ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                            {
                                xReturn = xTaskGenericNotifyStateClear( x_అంతర్గత_Task_Handle, ux_సూచీ_గమ్యం_Clear );
                            }
                        }
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_విలువ_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_సూచీ_గమ్యం_Clear,
                                                        uint32_t ul_బిట్లు_గమ్యం_Clear ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ul_Task_Generic_Notify_విలువ_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_సూచీ_గమ్యం_Clear,
                                                        uint32_t ul_బిట్లు_గమ్యం_Clear ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = pdFALSE;

            ఒకవేళ( ux_సూచీ_గమ్యం_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ఒకవేళ( xTask == ఖాళీ )
                {
                    ulReturn = ul_Task_Generic_Notify_విలువ_Clear( xTask, ux_సూచీ_గమ్యం_Clear, ul_బిట్లు_గమ్యం_Clear );
                }
                లేకపోతే
                {
                    l_సూచీ = ( int32_t ) xTask;

                    ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_గమ్యం_Access_Task = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Task == pdTRUE )
                        {
                            x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                            ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                            {
                                ulReturn = ul_Task_Generic_Notify_విలువ_Clear( x_అంతర్గత_Task_Handle, ux_సూచీ_గమ్యం_Clear, ul_బిట్లు_గమ్యం_Clear );
                            }
                        }
                    }
                }
            }

            తిరిగి ulReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Task APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 )

        పునాది_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_సంకేతం,
                                    స్థిరరాశి అక్షరం * స్థిరరాశి pcName,
                                    స్థిరరాశి config_దొంతర_లోతు_TYPE ux_దొంతర_లోతు,
                                    శూన్య * pvParameters,
                                    UBaseType_t ux_ప్రాధాన్యత,
                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                /* xTaskCreate() can only be used to create privileged tasks in MPU port. */
                ఒకవేళ( ( ux_ప్రాధాన్యత & పోర్టు_PRIVILEGE_బిట్టు ) != 0 )
                {
                    xReturn = xTaskCreate( pv_Task_సంకేతం, pcName, ux_దొంతర_లోతు, pvParameters, ux_ప్రాధాన్యత, &( x_అంతర్గత_Task_Handle ) );

                    ఒకవేళ( ( xReturn == pdPASS ) && ( x_అంతర్గత_Task_Handle != ఖాళీ ) )
                    {
                        MPU_Store_Task_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_Task_Handle );

                        ఒకవేళ( pxCreatedTask != ఖాళీ )
                        {
                            *pxCreatedTask = ( TaskHandle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                        }
                    }
                    లేకపోతే
                    {
                        MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_SUPPORT_STATIC_కేటాయింపు == 1 )

        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_సంకేతం,
                                            స్థిరరాశి అక్షరం * స్థిరరాశి pcName,
                                            స్థిరరాశి config_దొంతర_లోతు_TYPE ux_దొంతర_లోతు,
                                            శూన్య * స్థిరరాశి pvParameters,
                                            UBaseType_t ux_ప్రాధాన్యత,
                                            దొంతర_Type_t * స్థిరరాశి pux_దొంతర_బఫరు,
                                            StaticTask_t * స్థిరరాశి px_Task_బఫరు ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xExternalTaskHandle = ఖాళీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                x_అంతర్గత_Task_Handle = xTaskCreateStatic( px_Task_సంకేతం, pcName, ux_దొంతర_లోతు, pvParameters, ux_ప్రాధాన్యత, pux_దొంతర_బఫరు, px_Task_బఫరు );

                ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                {
                    MPU_Store_Task_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_Task_Handle );

                    #ఒకవేళ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ఒకవేళ( ( ux_ప్రాధాన్యత & పోర్టు_PRIVILEGE_బిట్టు ) == 0 )
                        {
                            v_పోర్టు_Grant_Access_గమ్యం_Kernel_Object( x_అంతర్గత_Task_Handle, l_సూచీ );
                        }
                    }
                    #అయితే_ముగింపు

                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి xExternalTaskHandle;
        }

    #అయితే_ముగింపు /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_vTaskDelete == 1 )

        శూన్య MPU_vTaskDelete( TaskHandle_t px_Task_గమ్యం_Delete ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            int32_t l_సూచీ;

            ఒకవేళ( px_Task_గమ్యం_Delete == ఖాళీ )
            {
                x_అంతర్గత_Task_Handle = xTaskGetCurrentTaskHandle();
                l_సూచీ = MPU_Get_సూచీ_For_Task_Handle( x_అంతర్గత_Task_Handle );

                ఒకవేళ( l_సూచీ != -1 )
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }

                vTaskDelete( x_అంతర్గత_Task_Handle );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) px_Task_గమ్యం_Delete;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                    {
                        MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );
                        vTaskDelete( x_అంతర్గత_Task_Handle );
                    }
                }
            }
        }

    #అయితే_ముగింపు /* #if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/


    #ఒకవేళ ( INCLUDE_v_Task_ప్రాధాన్యత_సమితి == 1 )

        శూన్య MPU_v_Task_ప్రాధాన్యత_సమితి( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_ప్రాధాన్యత ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            int32_t l_సూచీ;

            ఒకవేళ( pxTask == ఖాళీ )
            {
                v_Task_ప్రాధాన్యత_సమితి( pxTask, ux_New_ప్రాధాన్యత );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) pxTask;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                    {
                        v_Task_ప్రాధాన్యత_సమితి( x_అంతర్గత_Task_Handle, ux_New_ప్రాధాన్యత );
                    }
                }
            }
        }

    #అయితే_ముగింపు /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_xTaskGetHandle == 1 )

        TaskHandle_t MPU_xTaskGetHandle( స్థిరరాశి అక్షరం * pc_Name_గమ్యం_Query ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            TaskHandle_t xExternalTaskHandle = ఖాళీ;
            int32_t l_సూచీ;

            x_అంతర్గత_Task_Handle = xTaskGetHandle( pc_Name_గమ్యం_Query );

            ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
            {
                l_సూచీ = MPU_Get_సూచీ_For_Task_Handle( x_అంతర్గత_Task_Handle );

                ఒకవేళ( l_సూచీ != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
            }

            తిరిగి xExternalTaskHandle;
        }

    #అయితే_ముగింపు /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/


    #ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )

        పునాది_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     శూన్య * pvParameter ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

            ఒకవేళ( xTask == ఖాళీ )
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) xTask;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                    {
                        xReturn = xTaskCallApplicationTaskHook( x_అంతర్గత_Task_Handle, pvParameter );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 )

        పునాది_Type_t MPU_xTaskCreateRestricted( స్థిరరాశి TaskParameters_t * స్థిరరాశి pxTaskDefinition,
                                              TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                xReturn = xTaskCreateRestricted( pxTaskDefinition, &( x_అంతర్గత_Task_Handle ) );

                ఒకవేళ( ( xReturn == pdPASS ) && ( x_అంతర్గత_Task_Handle != ఖాళీ ) )
                {
                    MPU_Store_Task_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_Task_Handle );

                    #ఒకవేళ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ఒకవేళ( ( pxTaskDefinition->ux_ప్రాధాన్యత & పోర్టు_PRIVILEGE_బిట్టు ) == 0 )
                        {
                            v_పోర్టు_Grant_Access_గమ్యం_Kernel_Object( x_అంతర్గత_Task_Handle, l_సూచీ );
                        }
                    }
                    #అయితే_ముగింపు

                    ఒకవేళ( pxCreatedTask != ఖాళీ )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                    }
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_SUPPORT_STATIC_కేటాయింపు == 1 )

        పునాది_Type_t MPU_xTaskCreateRestrictedStatic( స్థిరరాశి TaskParameters_t * స్థిరరాశి pxTaskDefinition,
                                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                xReturn = xTaskCreateRestrictedStatic( pxTaskDefinition, &( x_అంతర్గత_Task_Handle ) );

                ఒకవేళ( ( xReturn == pdPASS ) && ( x_అంతర్గత_Task_Handle != ఖాళీ ) )
                {
                    MPU_Store_Task_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_Task_Handle );

                    #ఒకవేళ ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        ఒకవేళ( ( pxTaskDefinition->ux_ప్రాధాన్యత & పోర్టు_PRIVILEGE_బిట్టు ) == 0 )
                        {
                            v_పోర్టు_Grant_Access_గమ్యం_Kernel_Object( x_అంతర్గత_Task_Handle, l_సూచీ );
                        }
                    }
                    #అయితే_ముగింపు

                    ఒకవేళ( pxCreatedTask != ఖాళీ )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                    }
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    శూన్య MPU_vTaskAllocateMPURegions( TaskHandle_t x_Task_గమ్యం_Modify,
                                      స్థిరరాశి జ్ఞాపకం_Region_t * స్థిరరాశి xRegions ) /* PRIVILEGED_FUNCTION */
    {
        TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
        int32_t l_సూచీ;

        ఒకవేళ( x_Task_గమ్యం_Modify == ఖాళీ )
        {
            vTaskAllocateMPURegions( x_Task_గమ్యం_Modify, xRegions );
        }
        లేకపోతే
        {
            l_సూచీ = ( int32_t ) x_Task_గమ్యం_Modify;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                {
                    vTaskAllocateMPURegions( x_అంతర్గత_Task_Handle, xRegions );
                }
            }
        }
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_SUPPORT_STATIC_కేటాయింపు == 1 )

        పునాది_Type_t MPU_xTaskGetStaticBuffers( TaskHandle_t xTask,
                                              దొంతర_Type_t ** ppux_దొంతర_బఫరు,
                                              StaticTask_t ** ppx_Task_బఫరు ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t xReturn = pdFALSE;

            ఒకవేళ( xTask == ఖాళీ )
            {
                x_అంతర్గత_Task_Handle = xTaskGetCurrentTaskHandle();
                xReturn = xTaskGetStaticBuffers( x_అంతర్గత_Task_Handle, ppux_దొంతర_బఫరు, ppx_Task_బఫరు );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) xTask;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                    {
                        xReturn = xTaskGetStaticBuffers( x_అంతర్గత_Task_Handle, ppux_దొంతర_బఫరు, ppx_Task_బఫరు );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    అక్షరం * MPU_pcTaskGetName( TaskHandle_t x_Task_గమ్యం_Query ) /* PRIVILEGED_FUNCTION */
    {
        అక్షరం * pcReturn = ఖాళీ;
        int32_t l_సూచీ;
        TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

        ఒకవేళ( x_Task_గమ్యం_Query == ఖాళీ )
        {
            pcReturn = pcTaskGetName( x_Task_గమ్యం_Query );
        }
        లేకపోతే
        {
            l_సూచీ = ( int32_t ) x_Task_గమ్యం_Query;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                {
                    pcReturn = pcTaskGetName( x_అంతర్గత_Task_Handle );
                }
            }
        }

        తిరిగి pcReturn;
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( INCLUDE_ux_Task_ప్రాధాన్యత_Get == 1 )

        UBaseType_t MPU_ux_Task_ప్రాధాన్యత_Get_From_ISR( స్థిరరాశి TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

            ఒకవేళ( xTask == ఖాళీ )
            {
                uxReturn = ux_Task_ప్రాధాన్యత_Get_From_ISR( xTask );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) xTask;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                    {
                        uxReturn = ux_Task_ప్రాధాన్యత_Get_From_ISR( x_అంతర్గత_Task_Handle );
                    }
                }
            }

            తిరిగి uxReturn;
        }

    #అయితే_ముగింపు /* #if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( INCLUDE_ux_Task_ప్రాధాన్యత_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_పునాది_ప్రాధాన్యత_Get( స్థిరరాశి TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

            ఒకవేళ( xTask == ఖాళీ )
            {
                uxReturn = ux_Task_పునాది_ప్రాధాన్యత_Get( xTask );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) xTask;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                    {
                        uxReturn = ux_Task_పునాది_ప్రాధాన్యత_Get( x_అంతర్గత_Task_Handle );
                    }
                }
            }

            తిరిగి uxReturn;
        }

    #అయితే_ముగింపు /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( INCLUDE_ux_Task_ప్రాధాన్యత_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_పునాది_ప్రాధాన్యత_Get_From_ISR( స్థిరరాశి TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

            ఒకవేళ( xTask == ఖాళీ )
            {
                uxReturn = ux_Task_పునాది_ప్రాధాన్యత_Get_From_ISR( xTask );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) xTask;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                    {
                        uxReturn = ux_Task_పునాది_ప్రాధాన్యత_Get_From_ISR( x_అంతర్గత_Task_Handle );
                    }
                }
            }

            తిరిగి uxReturn;
        }

    #అయితే_ముగింపు /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

        పునాది_Type_t MPU_xTaskResumeFromISR( TaskHandle_t x_Task_గమ్యం_Resume ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

            l_సూచీ = ( int32_t ) x_Task_గమ్యం_Resume;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                {
                    xReturn = xTaskResumeFromISR( x_అంతర్గత_Task_Handle );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )*/
/*---------------------------------------------------------------------------------------*/

    #ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_ట్యాగ్_From_ISR( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = ఖాళీ;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

            ఒకవేళ( xTask == ఖాళీ )
            {
                xReturn = x_Task_Get_Application_Task_ట్యాగ్_From_ISR( xTask );
            }
            లేకపోతే
            {
                l_సూచీ = ( int32_t ) xTask;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                    {
                        xReturn = x_Task_Get_Application_Task_ట్యాగ్_From_ISR( x_అంతర్గత_Task_Handle );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        పునాది_Type_t MPU_xTaskGenericNotifyFromISR( TaskHandle_t x_Task_గమ్యం_Notify,
                                                  UBaseType_t ux_సూచీ_గమ్యం_Notify,
                                                  uint32_t ul_విలువ,
                                                  eNotifyAction eAction,
                                                  uint32_t * pul_మునుపటి_Notification_విలువ,
                                                  పునాది_Type_t * px_Higher_ప్రాధాన్యత_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

            l_సూచీ = ( int32_t ) x_Task_గమ్యం_Notify;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                {
                    xReturn = xTaskGenericNotifyFromISR( x_అంతర్గత_Task_Handle, ux_సూచీ_గమ్యం_Notify, ul_విలువ, eAction, pul_మునుపటి_Notification_విలువ, px_Higher_ప్రాధాన్యత_Task_Woken );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )

        శూన్య MPU_vTaskGenericNotifyGiveFromISR( TaskHandle_t x_Task_గమ్యం_Notify,
                                                UBaseType_t ux_సూచీ_గమ్యం_Notify,
                                                పునాది_Type_t * px_Higher_ప్రాధాన్యత_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_సూచీ;
            TaskHandle_t x_అంతర్గత_Task_Handle = ఖాళీ;

            l_సూచీ = ( int32_t ) x_Task_గమ్యం_Notify;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_Task_Handle = MPU_Get_Task_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_Task_Handle != ఖాళీ )
                {
                    vTaskGenericNotifyGiveFromISR( x_అంతర్గత_Task_Handle, ux_సూచీ_గమ్యం_Notify, px_Higher_ప్రాధాన్యత_Task_Woken );
                }
            }
        }
    #అయితే_ముగింపు /*#if ( configUSE_TASK_NOTIFICATIONS == 1 )*/
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for queue APIs.                   */
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Generic_Send_Impl( వరుస_Handle_t x_వరుస,
                                          స్థిరరాశి శూన్య * స్థిరరాశి pv_అంశం_గమ్యం_వరుస,
                                          TickType_t x_Ticks_గమ్యం_Wait,
                                          పునాది_Type_t xCopyPosition ) PRIVILEGED_FUNCTION;

    పునాది_Type_t MPU_x_వరుస_Generic_Send_Impl( వరుస_Handle_t x_వరుస,
                                          స్థిరరాశి శూన్య * స్థిరరాశి pv_అంశం_గమ్యం_వరుస,
                                          TickType_t x_Ticks_గమ్యం_Wait,
                                          పునాది_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_సూచీ;
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
        పునాది_Type_t xReturn = pdFAIL;
        పునాది_Type_t x_Is_అంశం_గమ్యం_వరుస_Readable = pdFALSE;
        పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = pdFALSE;
        UBaseType_t ux_వరుస_అంశం_కొలత, ux_వరుస_నిడివి;

        l_సూచీ = ( int32_t ) x_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస == pdTRUE )
            {
                x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                {
                    ux_వరుస_అంశం_కొలత = ux_వరుస_Get_వరుస_అంశం_కొలత( x_అంతర్గత_వరుస_Handle );
                    ux_వరుస_నిడివి = ux_వరుస_Get_వరుస_నిడివి( x_అంతర్గత_వరుస_Handle );

                    ఒకవేళ( ( !( ( pv_అంశం_గమ్యం_వరుస == ఖాళీ ) && ( ux_వరుస_అంశం_కొలత != ( UBaseType_t ) 0U ) ) ) &&
                        ( !( ( xCopyPosition == వరుస_OVERWRITE ) && ( ux_వరుస_నిడివి != ( UBaseType_t ) 1U ) ) )
                        #ఒకవేళ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_గమ్యం_Wait != 0U ) ) )
                        #అయితే_ముగింపు
                        )
                    {
                        ఒకవేళ( pv_అంశం_గమ్యం_వరుస != ఖాళీ )
                        {
                            x_Is_అంశం_గమ్యం_వరుస_Readable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( pv_అంశం_గమ్యం_వరుస,
                                                                                      ux_వరుస_అంశం_కొలత,
                                                                                      tskMPU_READ_PERMISSION );
                        }

                        ఒకవేళ( ( pv_అంశం_గమ్యం_వరుస == ఖాళీ ) || ( x_Is_అంశం_గమ్యం_వరుస_Readable == pdTRUE ) )
                        {
                            xReturn = x_వరుస_Generic_Send( x_అంతర్గత_వరుస_Handle, pv_అంశం_గమ్యం_వరుస, x_Ticks_గమ్యం_Wait, xCopyPosition );
                        }
                    }
                }
            }
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_వరుస_Messages_నిరీక్షణ_Impl( స్థిరరాశి వరుస_Handle_t px_వరుస ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_వరుస_Messages_నిరీక్షణ_Impl( స్థిరరాశి వరుస_Handle_t px_వరుస ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_సూచీ;
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
        UBaseType_t uxReturn = 0;
        పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = pdFALSE;

        l_సూచీ = ( int32_t ) px_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస == pdTRUE )
            {
                x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                {
                    uxReturn = ux_వరుస_Messages_నిరీక్షణ( x_అంతర్గత_వరుస_Handle );
                }
            }
        }

        తిరిగి uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_వరుస_Spaces_అందుబాటు_Impl( స్థిరరాశి వరుస_Handle_t x_వరుస ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_వరుస_Spaces_అందుబాటు_Impl( స్థిరరాశి వరుస_Handle_t x_వరుస ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_సూచీ;
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
        UBaseType_t uxReturn = 0;
        పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = pdFALSE;

        l_సూచీ = ( int32_t ) x_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస == pdTRUE )
            {
                x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                {
                    uxReturn = ux_వరుస_Spaces_అందుబాటు( x_అంతర్గత_వరుస_Handle );
                }
            }
        }

        తిరిగి uxReturn;
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Receive_Impl( వరుస_Handle_t px_వరుస,
                                      శూన్య * స్థిరరాశి pv_బఫరు,
                                      TickType_t x_Ticks_గమ్యం_Wait ) PRIVILEGED_FUNCTION;

    పునాది_Type_t MPU_x_వరుస_Receive_Impl( వరుస_Handle_t px_వరుస,
                                      శూన్య * స్థిరరాశి pv_బఫరు,
                                      TickType_t x_Ticks_గమ్యం_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_సూచీ;
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
        పునాది_Type_t xReturn = pdFAIL;
        పునాది_Type_t x_Is_Receive_బఫరు_Writable = pdFALSE;
        పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = pdFALSE;
        UBaseType_t ux_వరుస_అంశం_కొలత;

        l_సూచీ = ( int32_t ) px_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస == pdTRUE )
            {
                x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                {
                    ux_వరుస_అంశం_కొలత = ux_వరుస_Get_వరుస_అంశం_కొలత( x_అంతర్గత_వరుస_Handle );

                    ఒకవేళ( ( !( ( ( pv_బఫరు ) == ఖాళీ ) && ( ux_వరుస_అంశం_కొలత != ( UBaseType_t ) 0U ) ) )
                        #ఒకవేళ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_గమ్యం_Wait != 0U ) ) )
                        #అయితే_ముగింపు
                        )
                    {
                        x_Is_Receive_బఫరు_Writable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( pv_బఫరు,
                                                                                    ux_వరుస_అంశం_కొలత,
                                                                                    tskMPU_WRITE_PERMISSION );

                        ఒకవేళ( x_Is_Receive_బఫరు_Writable == pdTRUE )
                        {
                            xReturn = x_వరుస_Receive( x_అంతర్గత_వరుస_Handle, pv_బఫరు, x_Ticks_గమ్యం_Wait );
                        }
                    }
                }
            }
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Peek_Impl( వరుస_Handle_t x_వరుస,
                                   శూన్య * స్థిరరాశి pv_బఫరు,
                                   TickType_t x_Ticks_గమ్యం_Wait ) PRIVILEGED_FUNCTION;

    పునాది_Type_t MPU_x_వరుస_Peek_Impl( వరుస_Handle_t x_వరుస,
                                   శూన్య * స్థిరరాశి pv_బఫరు,
                                   TickType_t x_Ticks_గమ్యం_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_సూచీ;
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
        పునాది_Type_t xReturn = pdFAIL;
        పునాది_Type_t x_Is_Receive_బఫరు_Writable = pdFALSE;
        UBaseType_t ux_వరుస_అంశం_కొలత;
        పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = pdFALSE;

        l_సూచీ = ( int32_t ) x_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస == pdTRUE )
            {
                x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                {
                    ux_వరుస_అంశం_కొలత = ux_వరుస_Get_వరుస_అంశం_కొలత( x_అంతర్గత_వరుస_Handle );

                    ఒకవేళ( ( !( ( ( pv_బఫరు ) == ఖాళీ ) && ( ux_వరుస_అంశం_కొలత != ( UBaseType_t ) 0U ) ) )
                        #ఒకవేళ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_గమ్యం_Wait != 0U ) ) )
                        #అయితే_ముగింపు
                        )
                    {
                        x_Is_Receive_బఫరు_Writable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( pv_బఫరు,
                                                                                    ux_వరుస_అంశం_కొలత,
                                                                                    tskMPU_WRITE_PERMISSION );

                        ఒకవేళ( x_Is_Receive_బఫరు_Writable == pdTRUE )
                        {
                            xReturn = x_వరుస_Peek( x_అంతర్గత_వరుస_Handle, pv_బఫరు, x_Ticks_గమ్యం_Wait );
                        }
                    }
                }
            }
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Semaphore_Take_Impl( వరుస_Handle_t x_వరుస,
                                            TickType_t x_Ticks_గమ్యం_Wait ) PRIVILEGED_FUNCTION;

    పునాది_Type_t MPU_x_వరుస_Semaphore_Take_Impl( వరుస_Handle_t x_వరుస,
                                            TickType_t x_Ticks_గమ్యం_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_సూచీ;
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
        పునాది_Type_t xReturn = pdFAIL;
        UBaseType_t ux_వరుస_అంశం_కొలత;
        పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = pdFALSE;

        l_సూచీ = ( int32_t ) x_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస == pdTRUE )
            {
                x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                {
                    ux_వరుస_అంశం_కొలత = ux_వరుస_Get_వరుస_అంశం_కొలత( x_అంతర్గత_వరుస_Handle );

                    ఒకవేళ( ( ux_వరుస_అంశం_కొలత == 0U )
                        #ఒకవేళ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_గమ్యం_Wait != 0U ) ) )
                        #అయితే_ముగింపు
                        )
                    {
                        xReturn = x_వరుస_Semaphore_Take( x_అంతర్గత_వరుస_Handle, x_Ticks_గమ్యం_Wait );
                    }
                }
            }
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_వరుస_Get_Mutex_Holder_Impl( వరుస_Handle_t xSemaphore ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_x_వరుస_Get_Mutex_Holder_Impl( వరుస_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_అంతర్గత_Handle = ఖాళీ;
            TaskHandle_t xMutexHolderTaskExternalHandle = ఖాళీ;
            int32_t l_సూచీ, l_Mutex_Holder_Task_సూచీ;
            వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = pdFALSE;


            l_సూచీ = ( int32_t ) xSemaphore;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస == pdTRUE )
                {
                    x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                    {
                        x_Mutex_Holder_Task_అంతర్గత_Handle = x_వరుస_Get_Mutex_Holder( x_అంతర్గత_వరుస_Handle );

                        ఒకవేళ( x_Mutex_Holder_Task_అంతర్గత_Handle != ఖాళీ )
                        {
                            l_Mutex_Holder_Task_సూచీ = MPU_Get_సూచీ_For_Task_Handle( x_Mutex_Holder_Task_అంతర్గత_Handle );

                            ఒకవేళ( l_Mutex_Holder_Task_సూచీ != -1 )
                            {
                                xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_గమ్యం_EXTERNAL_సూచీ( l_Mutex_Holder_Task_సూచీ ) );
                            }
                        }
                    }
                }
            }

            తిరిగి xMutexHolderTaskExternalHandle;
        }

    #అయితే_ముగింపు /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_RECURSIVE_MUTEXES == 1 )

        పునాది_Type_t MPU_x_వరుస_Take_Mutex_Recursive_Impl( వరుస_Handle_t xMutex,
                                                     TickType_t x_ఖండం_సమయం ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_x_వరుస_Take_Mutex_Recursive_Impl( వరుస_Handle_t xMutex,
                                                     TickType_t x_ఖండం_సమయం ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = pdFALSE;
            int32_t l_సూచీ;
            వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
            UBaseType_t ux_వరుస_అంశం_కొలత;

            l_సూచీ = ( int32_t ) xMutex;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస == pdTRUE )
                {
                    x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                    {
                        ux_వరుస_అంశం_కొలత = ux_వరుస_Get_వరుస_అంశం_కొలత( x_అంతర్గత_వరుస_Handle );

                        ఒకవేళ( ux_వరుస_అంశం_కొలత == 0 )
                        {
                            xReturn = x_వరుస_Take_Mutex_Recursive( x_అంతర్గత_వరుస_Handle, x_ఖండం_సమయం );
                        }
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_RECURSIVE_MUTEXES == 1 )

        పునాది_Type_t MPU_x_వరుస_Give_Mutex_Recursive_Impl( వరుస_Handle_t xMutex ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_x_వరుస_Give_Mutex_Recursive_Impl( వరుస_Handle_t xMutex ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = pdFALSE;
            int32_t l_సూచీ;
            వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;

            l_సూచీ = ( int32_t ) xMutex;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస == pdTRUE )
                {
                    x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                    {
                        xReturn = x_వరుస_Give_Mutex_Recursive( x_అంతర్గత_వరుస_Handle );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_వరుస_SETS == 1 )

        వరుస_సమితి_Member_Handle_t MPU_x_వరుస_Select_From_సమితి_Impl( వరుస_సమితి_Handle_t x_వరుస_సమితి,
                                                            TickType_t x_ఖండం_సమయం_Ticks ) PRIVILEGED_FUNCTION;

        వరుస_సమితి_Member_Handle_t MPU_x_వరుస_Select_From_సమితి_Impl( వరుస_సమితి_Handle_t x_వరుస_సమితి,
                                                            TickType_t x_ఖండం_సమయం_Ticks ) /* PRIVILEGED_FUNCTION */
        {
            వరుస_సమితి_Handle_t x_అంతర్గత_వరుస_సమితి_Handle = ఖాళీ;
            వరుస_సమితి_Member_Handle_t x_Selected_Member_అంతర్గత = ఖాళీ;
            వరుస_సమితి_Member_Handle_t xSelectedMemberExternal = ఖాళీ;
            int32_t l_సూచీ_వరుస_సమితి, l_సూచీ_Selected_Member;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస_సమితి = pdFALSE;

            l_సూచీ_వరుస_సమితి = ( int32_t ) x_వరుస_సమితి;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ_వరుస_సమితి ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస_సమితి = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ_వరుస_సమితి ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస_సమితి == pdTRUE )
                {
                    x_అంతర్గత_వరుస_సమితి_Handle = MPU_Get_వరుస_సమితి_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ_వరుస_సమితి ) );

                    ఒకవేళ( x_అంతర్గత_వరుస_సమితి_Handle != ఖాళీ )
                    {
                        x_Selected_Member_అంతర్గత = x_వరుస_Select_From_సమితి( x_అంతర్గత_వరుస_సమితి_Handle, x_ఖండం_సమయం_Ticks );

                        ఒకవేళ( x_Selected_Member_అంతర్గత != ఖాళీ )
                        {
                            l_సూచీ_Selected_Member = MPU_Get_సూచీ_For_వరుస_సమితి_Member_Handle( x_Selected_Member_అంతర్గత );

                            ఒకవేళ( l_సూచీ_Selected_Member != -1 )
                            {
                                xSelectedMemberExternal = ( వరుస_సమితి_Member_Handle_t ) ( CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ_Selected_Member ) );
                            }
                        }
                    }
                }
            }

            తిరిగి xSelectedMemberExternal;
        }

    #అయితే_ముగింపు /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_వరుస_SETS == 1 )

        పునాది_Type_t MPU_x_వరుస_కూడు_గమ్యం_సమితి_Impl( వరుస_సమితి_Member_Handle_t x_వరుస_Or_Semaphore,
                                           వరుస_సమితి_Handle_t x_వరుస_సమితి ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_x_వరుస_కూడు_గమ్యం_సమితి_Impl( వరుస_సమితి_Member_Handle_t x_వరుస_Or_Semaphore,
                                           వరుస_సమితి_Handle_t x_వరుస_సమితి ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            వరుస_సమితి_Member_Handle_t x_అంతర్గత_వరుస_సమితి_Member_Handle = ఖాళీ;
            వరుస_సమితి_Handle_t x_అంతర్గత_వరుస_సమితి_Handle = ఖాళీ;
            int32_t l_సూచీ_వరుస_సమితి, l_సూచీ_వరుస_సమితి_Member;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస_సమితి = pdFALSE;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస_సమితి_Member = pdFALSE;

            l_సూచీ_వరుస_సమితి = ( int32_t ) x_వరుస_సమితి;
            l_సూచీ_వరుస_సమితి_Member = ( int32_t ) x_వరుస_Or_Semaphore;

            ఒకవేళ( ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ_వరుస_సమితి ) != pdFALSE ) &&
                ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ_వరుస_సమితి_Member ) != pdFALSE ) )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస_సమితి = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ_వరుస_సమితి ) );
                x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస_సమితి_Member = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ_వరుస_సమితి_Member ) );

                ఒకవేళ( ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస_సమితి == pdTRUE ) && ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస_సమితి_Member == pdTRUE ) )
                {
                    x_అంతర్గత_వరుస_సమితి_Handle = MPU_Get_వరుస_సమితి_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ_వరుస_సమితి ) );
                    x_అంతర్గత_వరుస_సమితి_Member_Handle = MPU_Get_వరుస_సమితి_Member_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ_వరుస_సమితి_Member ) );

                    ఒకవేళ( ( x_అంతర్గత_వరుస_సమితి_Handle != ఖాళీ ) && ( x_అంతర్గత_వరుస_సమితి_Member_Handle != ఖాళీ ) )
                    {
                        xReturn = x_వరుస_కూడు_గమ్యం_సమితి( x_అంతర్గత_వరుస_సమితి_Member_Handle, x_అంతర్గత_వరుస_సమితి_Handle );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ config_వరుస_REGISTRY_కొలత > 0

        శూన్య MPU_v_వరుస_కూడు_గమ్యం_Registry_Impl( వరుస_Handle_t x_వరుస,
                                          స్థిరరాశి అక్షరం * pcName ) PRIVILEGED_FUNCTION;

        శూన్య MPU_v_వరుస_కూడు_గమ్యం_Registry_Impl( వరుస_Handle_t x_వరుస,
                                          స్థిరరాశి అక్షరం * pcName ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_సూచీ;
            వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = pdFALSE;

            l_సూచీ = ( int32_t ) x_వరుస;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస == pdTRUE )
                {
                    x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                    {
                        v_వరుస_కూడు_గమ్యం_Registry( x_అంతర్గత_వరుస_Handle, pcName );
                    }
                }
            }
        }

    #అయితే_ముగింపు /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ఒకవేళ config_వరుస_REGISTRY_కొలత > 0

        శూన్య MPU_v_వరుస_Unregister_వరుస_Impl( వరుస_Handle_t x_వరుస ) PRIVILEGED_FUNCTION;

        శూన్య MPU_v_వరుస_Unregister_వరుస_Impl( వరుస_Handle_t x_వరుస ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_సూచీ;
            వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = pdFALSE;

            l_సూచీ = ( int32_t ) x_వరుస;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస == pdTRUE )
                {
                    x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                    {
                        v_వరుస_Unregister_వరుస( x_అంతర్గత_వరుస_Handle );
                    }
                }
            }
        }

    #అయితే_ముగింపు /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #ఒకవేళ config_వరుస_REGISTRY_కొలత > 0

        స్థిరరాశి అక్షరం * MPU_pc_వరుస_Get_Name_Impl( వరుస_Handle_t x_వరుస ) PRIVILEGED_FUNCTION;

        స్థిరరాశి అక్షరం * MPU_pc_వరుస_Get_Name_Impl( వరుస_Handle_t x_వరుస ) /* PRIVILEGED_FUNCTION */
        {
            స్థిరరాశి అక్షరం * pcReturn = ఖాళీ;
            వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = pdFALSE;

            l_సూచీ = ( int32_t ) x_వరుస;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_వరుస == pdTRUE )
                {
                    x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                    {
                        pcReturn = pc_వరుస_Get_Name( x_అంతర్గత_వరుస_Handle );
                    }
                }
            }

            తిరిగి pcReturn;
        }

    #అయితే_ముగింపు /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Queue APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    శూన్య MPU_v_వరుస_Delete( వరుస_Handle_t x_వరుస ) /* PRIVILEGED_FUNCTION */
    {
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
        int32_t l_సూచీ;

        l_సూచీ = ( int32_t ) x_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
            {
                v_వరుస_Delete( x_అంతర్గత_వరుస_Handle );
                MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );
            }
        }
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 ) )

        వరుస_Handle_t MPU_x_వరుస_Create_Mutex( స్థిరరాశి uint8_t uc_వరుస_Type ) /* PRIVILEGED_FUNCTION */
        {
            వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
            వరుస_Handle_t x_External_వరుస_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                x_అంతర్గత_వరుస_Handle = x_వరుస_Create_Mutex( uc_వరుస_Type );

                ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                {
                    MPU_Store_వరుస_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_వరుస_Handle );
                    x_External_వరుస_Handle = ( వరుస_Handle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి x_External_వరుస_Handle;
        }

    #అయితే_ముగింపు /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_కేటాయింపు == 1 ) )

        వరుస_Handle_t MPU_x_వరుస_Create_Mutex_Static( స్థిరరాశి uint8_t uc_వరుస_Type,
                                                   Static_వరుస_t * px_Static_వరుస ) /* PRIVILEGED_FUNCTION */
        {
            వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
            వరుస_Handle_t x_External_వరుస_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                x_అంతర్గత_వరుస_Handle = x_వరుస_Create_Mutex_Static( uc_వరుస_Type, px_Static_వరుస );

                ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                {
                    MPU_Store_వరుస_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_వరుస_Handle );
                    x_External_వరుస_Handle = ( వరుస_Handle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి x_External_వరుస_Handle;
        }

    #అయితే_ముగింపు /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 ) )

        వరుస_Handle_t MPU_x_వరుస_Create_Counting_Semaphore( UBaseType_t ux_లెక్క_విలువ,
                                                         UBaseType_t ux_Initial_లెక్క ) /* PRIVILEGED_FUNCTION */
        {
            వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
            వరుస_Handle_t x_External_వరుస_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                x_అంతర్గత_వరుస_Handle = x_వరుస_Create_Counting_Semaphore( ux_లెక్క_విలువ, ux_Initial_లెక్క );

                ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                {
                    MPU_Store_వరుస_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_వరుస_Handle );
                    x_External_వరుస_Handle = ( వరుస_Handle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి x_External_వరుస_Handle;
        }

    #అయితే_ముగింపు /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_కేటాయింపు == 1 ) )

        వరుస_Handle_t MPU_x_వరుస_Create_Counting_Semaphore_Static( స్థిరరాశి UBaseType_t ux_Max_లెక్క,
                                                               స్థిరరాశి UBaseType_t ux_Initial_లెక్క,
                                                               Static_వరుస_t * px_Static_వరుస ) /* PRIVILEGED_FUNCTION */
        {
            వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
            వరుస_Handle_t x_External_వరుస_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                x_అంతర్గత_వరుస_Handle = x_వరుస_Create_Counting_Semaphore_Static( ux_Max_లెక్క, ux_Initial_లెక్క, px_Static_వరుస );

                ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                {
                    MPU_Store_వరుస_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_వరుస_Handle );
                    x_External_వరుస_Handle = ( వరుస_Handle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి x_External_వరుస_Handle;
        }

    #అయితే_ముగింపు /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 )

        వరుస_Handle_t MPU_x_వరుస_Generic_Create( UBaseType_t ux_వరుస_నిడివి,
                                               UBaseType_t ux_అంశం_కొలత,
                                               uint8_t uc_వరుస_Type ) /* PRIVILEGED_FUNCTION */
        {
            వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
            వరుస_Handle_t x_External_వరుస_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                x_అంతర్గత_వరుస_Handle = x_వరుస_Generic_Create( ux_వరుస_నిడివి, ux_అంశం_కొలత, uc_వరుస_Type );

                ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                {
                    MPU_Store_వరుస_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_వరుస_Handle );
                    x_External_వరుస_Handle = ( వరుస_Handle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి x_External_వరుస_Handle;
        }

    #అయితే_ముగింపు /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_SUPPORT_STATIC_కేటాయింపు == 1 )

        వరుస_Handle_t MPU_x_వరుస_Generic_Create_Static( స్థిరరాశి UBaseType_t ux_వరుస_నిడివి,
                                                     స్థిరరాశి UBaseType_t ux_అంశం_కొలత,
                                                     uint8_t * puc_వరుస_Storage,
                                                     Static_వరుస_t * px_Static_వరుస,
                                                     స్థిరరాశి uint8_t uc_వరుస_Type ) /* PRIVILEGED_FUNCTION */
        {
            వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
            వరుస_Handle_t x_External_వరుస_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                x_అంతర్గత_వరుస_Handle = x_వరుస_Generic_Create_Static( ux_వరుస_నిడివి, ux_అంశం_కొలత, puc_వరుస_Storage, px_Static_వరుస, uc_వరుస_Type );

                ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                {
                    MPU_Store_వరుస_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_వరుస_Handle );
                    x_External_వరుస_Handle = ( వరుస_Handle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి x_External_వరుస_Handle;
        }

    #అయితే_ముగింపు /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Generic_Reset( వరుస_Handle_t x_వరుస,
                                       పునాది_Type_t x_New_వరుస ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_సూచీ;
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
        పునాది_Type_t xReturn = pdFAIL;

        l_సూచీ = ( int32_t ) x_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
            {
                xReturn = x_వరుస_Generic_Reset( x_అంతర్గత_వరుస_Handle, x_New_వరుస );
            }
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_USE_వరుస_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 ) )

        వరుస_సమితి_Handle_t MPU_x_వరుస_Create_సమితి( UBaseType_t ux_Event_వరుస_నిడివి ) /* PRIVILEGED_FUNCTION */
        {
            వరుస_సమితి_Handle_t x_అంతర్గత_వరుస_సమితి_Handle = ఖాళీ;
            వరుస_సమితి_Handle_t x_External_వరుస_సమితి_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                x_అంతర్గత_వరుస_సమితి_Handle = x_వరుస_Create_సమితి( ux_Event_వరుస_నిడివి );

                ఒకవేళ( x_అంతర్గత_వరుస_సమితి_Handle != ఖాళీ )
                {
                    MPU_Store_వరుస_సమితి_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_వరుస_సమితి_Handle );
                    x_External_వరుస_సమితి_Handle = ( వరుస_సమితి_Handle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి x_External_వరుస_సమితి_Handle;
        }

    #అయితే_ముగింపు /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_USE_వరుస_SETS == 1 ) && ( config_SUPPORT_STATIC_కేటాయింపు == 1 ) )

        వరుస_సమితి_Handle_t MPU_x_వరుస_Create_సమితి_Static( స్థిరరాశి UBaseType_t ux_Event_వరుస_నిడివి,
                                                    uint8_t * puc_వరుస_Storage,
                                                    Static_వరుస_t * px_Static_వరుస ) /* PRIVILEGED_FUNCTION */
        {
            వరుస_సమితి_Handle_t x_అంతర్గత_వరుస_సమితి_Handle = ఖాళీ;
            వరుస_సమితి_Handle_t x_External_వరుస_సమితి_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                x_అంతర్గత_వరుస_సమితి_Handle = x_వరుస_Create_సమితి_Static( ux_Event_వరుస_నిడివి, puc_వరుస_Storage, px_Static_వరుస );

                ఒకవేళ( x_అంతర్గత_వరుస_సమితి_Handle != ఖాళీ )
                {
                    MPU_Store_వరుస_సమితి_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_వరుస_సమితి_Handle );
                    x_External_వరుస_సమితి_Handle = ( వరుస_సమితి_Handle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి x_External_వరుస_సమితి_Handle;
        }

    #అయితే_ముగింపు /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_వరుస_SETS == 1 )

        పునాది_Type_t MPU_x_వరుస_Remove_From_సమితి( వరుస_సమితి_Member_Handle_t x_వరుస_Or_Semaphore,
                                            వరుస_సమితి_Handle_t x_వరుస_సమితి ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            వరుస_సమితి_Member_Handle_t x_అంతర్గత_వరుస_సమితి_Member_Handle = ఖాళీ;
            వరుస_సమితి_Handle_t x_అంతర్గత_వరుస_సమితి_Handle = ఖాళీ;
            int32_t l_సూచీ_వరుస_సమితి, l_సూచీ_వరుస_సమితి_Member;

            l_సూచీ_వరుస_సమితి = ( int32_t ) x_వరుస_సమితి;
            l_సూచీ_వరుస_సమితి_Member = ( int32_t ) x_వరుస_Or_Semaphore;

            ఒకవేళ( ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ_వరుస_సమితి ) != pdFALSE ) &&
                ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ_వరుస_సమితి_Member ) != pdFALSE ) )
            {
                x_అంతర్గత_వరుస_సమితి_Handle = MPU_Get_వరుస_సమితి_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ_వరుస_సమితి ) );
                x_అంతర్గత_వరుస_సమితి_Member_Handle = MPU_Get_వరుస_సమితి_Member_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ_వరుస_సమితి_Member ) );

                ఒకవేళ( ( x_అంతర్గత_వరుస_సమితి_Handle != ఖాళీ ) && ( x_అంతర్గత_వరుస_సమితి_Member_Handle != ఖాళీ ) )
                {
                    xReturn = x_వరుస_Remove_From_సమితి( x_అంతర్గత_వరుస_సమితి_Member_Handle, x_అంతర్గత_వరుస_సమితి_Handle );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_SUPPORT_STATIC_కేటాయింపు == 1 )

        పునాది_Type_t MPU_x_వరుస_Generic_Get_Static_Buffers( వరుస_Handle_t x_వరుస,
                                                      uint8_t ** ppuc_వరుస_Storage,
                                                      Static_వరుస_t ** ppx_Static_వరుస ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_సూచీ;
            వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;
            పునాది_Type_t xReturn = pdFALSE;

            l_సూచీ = ( int32_t ) x_వరుస;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
                {
                    xReturn = x_వరుస_Generic_Get_Static_Buffers( x_అంతర్గత_వరుస_Handle, ppuc_వరుస_Storage, ppx_Static_వరుస );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /*if ( configSUPPORT_STATIC_ALLOCATION == 1 )*/
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Generic_Send_From_ISR( వరుస_Handle_t x_వరుస,
                                             స్థిరరాశి శూన్య * స్థిరరాశి pv_అంశం_గమ్యం_వరుస,
                                             పునాది_Type_t * స్థిరరాశి px_Higher_ప్రాధాన్యత_Task_Woken,
                                             స్థిరరాశి పునాది_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        పునాది_Type_t xReturn = pdFAIL;
        int32_t l_సూచీ;
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;

        l_సూచీ = ( int32_t ) x_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
            {
                xReturn = x_వరుస_Generic_Send_From_ISR( x_అంతర్గత_వరుస_Handle, pv_అంశం_గమ్యం_వరుస, px_Higher_ప్రాధాన్యత_Task_Woken, xCopyPosition );
            }
        }

        తిరిగి xReturn;
    }

/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Give_From_ISR( వరుస_Handle_t x_వరుస,
                                      పునాది_Type_t * స్థిరరాశి px_Higher_ప్రాధాన్యత_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        పునాది_Type_t xReturn = pdFAIL;
        int32_t l_సూచీ;
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;

        l_సూచీ = ( int32_t ) x_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
            {
                xReturn = x_వరుస_Give_From_ISR( x_అంతర్గత_వరుస_Handle, px_Higher_ప్రాధాన్యత_Task_Woken );
            }
        }

        తిరిగి xReturn;
    }

/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Peek_From_ISR( వరుస_Handle_t x_వరుస,
                                      శూన్య * స్థిరరాశి pv_బఫరు ) /* PRIVILEGED_FUNCTION */
    {
        పునాది_Type_t xReturn = pdFAIL;
        int32_t l_సూచీ;
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;

        l_సూచీ = ( int32_t ) x_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
            {
                xReturn = x_వరుస_Peek_From_ISR( x_అంతర్గత_వరుస_Handle, pv_బఫరు );
            }
        }

        తిరిగి xReturn;
    }

/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Receive_From_ISR( వరుస_Handle_t x_వరుస,
                                         శూన్య * స్థిరరాశి pv_బఫరు,
                                         పునాది_Type_t * స్థిరరాశి px_Higher_ప్రాధాన్యత_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        పునాది_Type_t xReturn = pdFAIL;
        int32_t l_సూచీ;
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;

        l_సూచీ = ( int32_t ) x_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
            {
                xReturn = x_వరుస_Receive_From_ISR( x_అంతర్గత_వరుస_Handle, pv_బఫరు, px_Higher_ప్రాధాన్యత_Task_Woken );
            }
        }

        తిరిగి xReturn;
    }

/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Is_వరుస_ఖాళీలు_From_ISR( స్థిరరాశి వరుస_Handle_t x_వరుస ) /* PRIVILEGED_FUNCTION */
    {
        పునాది_Type_t xReturn = pdFAIL;
        int32_t l_సూచీ;
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;

        l_సూచీ = ( int32_t ) x_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
            {
                xReturn = x_వరుస_Is_వరుస_ఖాళీలు_From_ISR( x_అంతర్గత_వరుస_Handle );
            }
        }

        తిరిగి xReturn;
    }
/*-----------------------------------------------------------*/

    పునాది_Type_t MPU_x_వరుస_Is_వరుస_నిండిన_From_ISR( స్థిరరాశి వరుస_Handle_t x_వరుస ) /* PRIVILEGED_FUNCTION */
    {
        పునాది_Type_t xReturn = pdFAIL;
        int32_t l_సూచీ;
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;

        l_సూచీ = ( int32_t ) x_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
            {
                xReturn = x_వరుస_Is_వరుస_నిండిన_From_ISR( x_అంతర్గత_వరుస_Handle );
            }
        }

        తిరిగి xReturn;
    }

/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_వరుస_Messages_నిరీక్షణ_From_ISR( స్థిరరాశి వరుస_Handle_t x_వరుస ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn = 0;
        int32_t l_సూచీ;
        వరుస_Handle_t x_అంతర్గత_వరుస_Handle = ఖాళీ;

        l_సూచీ = ( int32_t ) x_వరుస;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_అంతర్గత_వరుస_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_అంతర్గత_వరుస_Handle != ఖాళీ )
            {
                uxReturn = ux_వరుస_Messages_నిరీక్షణ_From_ISR( x_అంతర్గత_వరుస_Handle );
            }
        }

        తిరిగి uxReturn;
    }

/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_x_వరుస_Get_Mutex_Holder_From_ISR( వరుస_Handle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_అంతర్గత_Handle = ఖాళీ;
            TaskHandle_t xMutexHolderTaskExternalHandle = ఖాళీ;
            int32_t l_సూచీ, l_Mutex_Holder_Task_సూచీ;
            వరుస_Handle_t x_అంతర్గత_Semaphore_Handle = ఖాళీ;

            l_సూచీ = ( int32_t ) xSemaphore;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_Semaphore_Handle = MPU_Get_వరుస_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_Semaphore_Handle != ఖాళీ )
                {
                    x_Mutex_Holder_Task_అంతర్గత_Handle = x_వరుస_Get_Mutex_Holder( x_అంతర్గత_Semaphore_Handle );

                    ఒకవేళ( x_Mutex_Holder_Task_అంతర్గత_Handle != ఖాళీ )
                    {
                        l_Mutex_Holder_Task_సూచీ = MPU_Get_సూచీ_For_Task_Handle( x_Mutex_Holder_Task_అంతర్గత_Handle );

                        ఒకవేళ( l_Mutex_Holder_Task_సూచీ != -1 )
                        {
                            xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_గమ్యం_EXTERNAL_సూచీ( l_Mutex_Holder_Task_సూచీ ) );
                        }
                    }
                }
            }

            తిరిగి xMutexHolderTaskExternalHandle;
        }

    #అయితే_ముగింపు /* #if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_వరుస_SETS == 1 )

        వరుస_సమితి_Member_Handle_t MPU_x_వరుస_Select_From_సమితి_From_ISR( వరుస_సమితి_Handle_t x_వరుస_సమితి ) /* PRIVILEGED_FUNCTION */
        {
            వరుస_సమితి_Handle_t x_అంతర్గత_వరుస_సమితి_Handle = ఖాళీ;
            వరుస_సమితి_Member_Handle_t x_Selected_Member_అంతర్గత = ఖాళీ;
            వరుస_సమితి_Member_Handle_t xSelectedMemberExternal = ఖాళీ;
            int32_t l_సూచీ_వరుస_సమితి, l_సూచీ_Selected_Member;

            l_సూచీ_వరుస_సమితి = ( int32_t ) x_వరుస_సమితి;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ_వరుస_సమితి ) != pdFALSE )
            {
                x_అంతర్గత_వరుస_సమితి_Handle = MPU_Get_వరుస_సమితి_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ_వరుస_సమితి ) );

                ఒకవేళ( x_అంతర్గత_వరుస_సమితి_Handle != ఖాళీ )
                {
                    x_Selected_Member_అంతర్గత = x_వరుస_Select_From_సమితి_From_ISR( x_అంతర్గత_వరుస_సమితి_Handle );

                    ఒకవేళ( x_Selected_Member_అంతర్గత != ఖాళీ )
                    {
                        l_సూచీ_Selected_Member = MPU_Get_సూచీ_For_వరుస_సమితి_Member_Handle( x_Selected_Member_అంతర్గత );

                        ఒకవేళ( l_సూచీ_Selected_Member != -1 )
                        {
                            xSelectedMemberExternal = ( వరుస_సమితి_Member_Handle_t ) ( CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ_Selected_Member ) );
                        }
                    }
                }
            }

            తిరిగి xSelectedMemberExternal;
        }

    #అయితే_ముగింపు /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for timers APIs.                  */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        శూన్య * MPU_pvTimerGetTimerIDImpl( స్థిరరాశి TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        శూన్య * MPU_pvTimerGetTimerIDImpl( స్థిరరాశి TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            శూన్య * pvReturn = ఖాళీ;
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = pdFALSE;

            l_సూచీ = ( int32_t ) xTimer;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer == pdTRUE )
                {
                    x_అంతర్గత_Timer_Handle = MPU_Get_Timer_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                    {
                        pvReturn = pvTimerGetTimerID( x_అంతర్గత_Timer_Handle );
                    }
                }
            }

            తిరిగి pvReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        శూన్య MPU_v_Timer_సమితి_Timer_IDImpl( TimerHandle_t xTimer,
                                       శూన్య * pvNewID ) PRIVILEGED_FUNCTION;

        శూన్య MPU_v_Timer_సమితి_Timer_IDImpl( TimerHandle_t xTimer,
                                       శూన్య * pvNewID ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = pdFALSE;

            l_సూచీ = ( int32_t ) xTimer;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer == pdTRUE )
                {
                    x_అంతర్గత_Timer_Handle = MPU_Get_Timer_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                    {
                        v_Timer_సమితి_Timer_ID( x_అంతర్గత_Timer_Handle, pvNewID );
                    }
                }
            }
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        పునాది_Type_t MPU_x_Timer_Is_Timer_చురుకైన_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_x_Timer_Is_Timer_చురుకైన_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = pdFALSE;

            l_సూచీ = ( int32_t ) xTimer;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer == pdTRUE )
                {
                    x_అంతర్గత_Timer_Handle = MPU_Get_Timer_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                    {
                        xReturn = x_Timer_Is_Timer_చురుకైన( x_అంతర్గత_Timer_Handle );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( శూన్య ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( శూన్య ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xReturn;

            xReturn = xTimerGetTimerDaemonTaskHandle();

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        పునాది_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     స్థిరరాశి పునాది_Type_t xCommandID,
                                                     స్థిరరాశి TickType_t x_Optional_విలువ,
                                                     పునాది_Type_t * స్థిరరాశి px_Higher_ప్రాధాన్యత_Task_Woken,
                                                     స్థిరరాశి TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            పునాది_Type_t xReturn = pdFALSE;
            xTimerGenericCommandFromTaskParams_t xParams;

            xParams.xTimer = xTimer;
            xParams.xCommandID = xCommandID;
            xParams.x_Optional_విలువ = x_Optional_విలువ;
            xParams.px_Higher_ప్రాధాన్యత_Task_Woken = px_Higher_ప్రాధాన్యత_Task_Woken;
            xParams.x_Ticks_గమ్యం_Wait = x_Ticks_గమ్యం_Wait;

            xReturn = MPU_x_Timer_Generic_Command_From_Task_నమోదు( &( xParams ) );

            తిరిగి xReturn;
        }

        పునాది_Type_t MPU_xTimerGenericCommandFromTaskImpl( స్థిరరాశి xTimerGenericCommandFromTaskParams_t * pxParams ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_xTimerGenericCommandFromTaskImpl( స్థిరరాశి xTimerGenericCommandFromTaskParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Is_Higher_ప్రాధాన్యత_Task_Woken_Writeable = pdFALSE;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = pdFALSE;
            పునాది_Type_t xAreParamsReadable = pdFALSE;

            ఒకవేళ( pxParams != ఖాళీ )
            {
                xAreParamsReadable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( pxParams,
                                                                      పరిమాణం( xTimerGenericCommandFromTaskParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ఒకవేళ( xAreParamsReadable == pdTRUE )
            {
                ఒకవేళ( pxParams->xCommandID < tmr_మొదటి_FROM_ISR_COMMAND )
                {
                    ఒకవేళ( pxParams->px_Higher_ప్రాధాన్యత_Task_Woken != ఖాళీ )
                    {
                        x_Is_Higher_ప్రాధాన్యత_Task_Woken_Writeable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( pxParams->px_Higher_ప్రాధాన్యత_Task_Woken,
                                                                                               పరిమాణం( పునాది_Type_t ),
                                                                                               tskMPU_WRITE_PERMISSION );
                    }

                    ఒకవేళ( ( pxParams->px_Higher_ప్రాధాన్యత_Task_Woken == ఖాళీ ) ||
                        ( x_Is_Higher_ప్రాధాన్యత_Task_Woken_Writeable == pdTRUE ) )
                    {
                        l_సూచీ = ( int32_t ) ( pxParams->xTimer );

                        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                            ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer == pdTRUE )
                            {
                                x_అంతర్గత_Timer_Handle = MPU_Get_Timer_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                                ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                                {
                                    xReturn = xTimerGenericCommandFromTask( x_అంతర్గత_Timer_Handle,
                                                                            pxParams->xCommandID,
                                                                            pxParams->x_Optional_విలువ,
                                                                            pxParams->px_Higher_ప్రాధాన్యత_Task_Woken,
                                                                            pxParams->x_Ticks_గమ్యం_Wait );
                                }
                            }
                        }
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        స్థిరరాశి అక్షరం * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        స్థిరరాశి అక్షరం * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            స్థిరరాశి అక్షరం * pcReturn = ఖాళీ;
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = pdFALSE;

            l_సూచీ = ( int32_t ) xTimer;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer == pdTRUE )
                {
                    x_అంతర్గత_Timer_Handle = MPU_Get_Timer_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                    {
                        pcReturn = pcTimerGetName( x_అంతర్గత_Timer_Handle );
                    }
                }
            }

            తిరిగి pcReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        శూన్య MPU_v_Timer_సమితి_Reload_బహుళకం_Impl( TimerHandle_t xTimer,
                                          స్థిరరాశి పునాది_Type_t xAutoReload ) PRIVILEGED_FUNCTION;

        శూన్య MPU_v_Timer_సమితి_Reload_బహుళకం_Impl( TimerHandle_t xTimer,
                                          స్థిరరాశి పునాది_Type_t xAutoReload ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = pdFALSE;

            l_సూచీ = ( int32_t ) xTimer;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer == pdTRUE )
                {
                    x_అంతర్గత_Timer_Handle = MPU_Get_Timer_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                    {
                        v_Timer_సమితి_Reload_బహుళకం( x_అంతర్గత_Timer_Handle, xAutoReload );
                    }
                }
            }
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        పునాది_Type_t MPU_x_Timer_Get_Reload_బహుళకం_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_x_Timer_Get_Reload_బహుళకం_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = pdFALSE;

            l_సూచీ = ( int32_t ) xTimer;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer == pdTRUE )
                {
                    x_అంతర్గత_Timer_Handle = MPU_Get_Timer_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                    {
                        xReturn = x_Timer_Get_Reload_బహుళకం( x_అంతర్గత_Timer_Handle );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_బహుళకం_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Timer_Get_Reload_బహుళకం_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = pdFALSE;

            l_సూచీ = ( int32_t ) xTimer;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer == pdTRUE )
                {
                    x_అంతర్గత_Timer_Handle = MPU_Get_Timer_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                    {
                        uxReturn = ux_Timer_Get_Reload_బహుళకం( x_అంతర్గత_Timer_Handle );
                    }
                }
            }

            తిరిగి uxReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = pdFALSE;

            l_సూచీ = ( int32_t ) xTimer;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer == pdTRUE )
                {
                    x_అంతర్గత_Timer_Handle = MPU_Get_Timer_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                    {
                        xReturn = xTimerGetPeriod( x_అంతర్గత_Timer_Handle );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        TickType_t MPU_x_Timer_Get_Expiry_సమయం_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_x_Timer_Get_Expiry_సమయం_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = pdFALSE;

            l_సూచీ = ( int32_t ) xTimer;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Timer == pdTRUE )
                {
                    x_అంతర్గత_Timer_Handle = MPU_Get_Timer_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                    {
                        xReturn = x_Timer_Get_Expiry_సమయం( x_అంతర్గత_Timer_Handle );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Timer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreate( స్థిరరాశి అక్షరం * స్థిరరాశి pcTimerName,
                                        స్థిరరాశి TickType_t x_Timer_Period_లోపల_Ticks,
                                        స్థిరరాశి పునాది_Type_t xAutoReload,
                                        శూన్య * స్థిరరాశి pvTimerID,
                                        TimerCallbackFunction_t pxCallbackFunction ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            TimerHandle_t xExternalTimerHandle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                x_అంతర్గత_Timer_Handle = xTimerCreate( pcTimerName, x_Timer_Period_లోపల_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback );

                ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                {
                    MPU_Store_Timer_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి xExternalTimerHandle;
        }

    #అయితే_ముగింపు /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_SUPPORT_STATIC_కేటాయింపు == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreateStatic( స్థిరరాశి అక్షరం * స్థిరరాశి pcTimerName,
                                              స్థిరరాశి TickType_t x_Timer_Period_లోపల_Ticks,
                                              స్థిరరాశి పునాది_Type_t xAutoReload,
                                              శూన్య * స్థిరరాశి pvTimerID,
                                              TimerCallbackFunction_t pxCallbackFunction,
                                              StaticTimer_t * px_Timer_బఫరు ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            TimerHandle_t xExternalTimerHandle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                x_అంతర్గత_Timer_Handle = xTimerCreateStatic( pcTimerName, x_Timer_Period_లోపల_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback, px_Timer_బఫరు );

                ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                {
                    MPU_Store_Timer_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి xExternalTimerHandle;
        }

    #అయితే_ముగింపు /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_SUPPORT_STATIC_కేటాయింపు == 1 ) && ( configUSE_TIMERS == 1 )

        పునాది_Type_t MPU_x_Timer_Get_Static_బఫరు( TimerHandle_t xTimer,
                                              StaticTimer_t ** ppx_Timer_బఫరు ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t xReturn = pdFALSE;

            l_సూచీ = ( int32_t ) xTimer;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_Timer_Handle = MPU_Get_Timer_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                {
                    xReturn = x_Timer_Get_Static_బఫరు( x_అంతర్గత_Timer_Handle, ppx_Timer_బఫరు );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        పునాది_Type_t MPU_xTimerGenericCommandFromISR( TimerHandle_t xTimer,
                                                    స్థిరరాశి పునాది_Type_t xCommandID,
                                                    స్థిరరాశి TickType_t x_Optional_విలువ,
                                                    పునాది_Type_t * స్థిరరాశి px_Higher_ప్రాధాన్యత_Task_Woken,
                                                    స్థిరరాశి TickType_t x_Ticks_గమ్యం_Wait ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = ( int32_t ) xTimer;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_Timer_Handle = MPU_Get_Timer_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                {
                    xReturn = xTimerGenericCommandFromISR( x_అంతర్గత_Timer_Handle, xCommandID, x_Optional_విలువ, px_Higher_ప్రాధాన్యత_Task_Woken, x_Ticks_గమ్యం_Wait );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_TIMERS == 1 )

        పునాది_Type_t MPU_xTimerDelete( TimerHandle_t xTimer, TickType_t x_Ticks_గమ్యం_Wait ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            TimerHandle_t x_అంతర్గత_Timer_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = ( int32_t ) xTimer;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_Timer_Handle = MPU_Get_Timer_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_Timer_Handle != ఖాళీ )
                {
                    xReturn = xTimerGenericCommandFromTask( x_అంతర్గత_Timer_Handle,
                                                            tmrCOMMAND_DELETE,
                                                            0U, /* xOptionalValue */
                                                            ఖాళీ, /* pxHigherPriorityTaskWoken */
                                                            x_Ticks_గమ్యం_Wait );
                    ఒకవేళ( xReturn != pdFALSE )
                    {
                        MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for event group APIs.              */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

        Event_బిట్లు_t MPU_x_Event_సమూహం_Wait_బిట్లు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                             స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Wait_For,
                                             స్థిరరాశి పునాది_Type_t xClearOnExit,
                                             స్థిరరాశి పునాది_Type_t x_Wait_For_All_బిట్లు,
                                             TickType_t x_Ticks_గమ్యం_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_బిట్లు_t xReturn = 0;
            x_Event_సమూహం_Wait_బిట్లు_Params_t xParams;

            xParams.x_Event_సమూహం = x_Event_సమూహం;
            xParams.ux_బిట్లు_గమ్యం_Wait_For = ux_బిట్లు_గమ్యం_Wait_For;
            xParams.xClearOnExit = xClearOnExit;
            xParams.x_Wait_For_All_బిట్లు = x_Wait_For_All_బిట్లు;
            xParams.x_Ticks_గమ్యం_Wait = x_Ticks_గమ్యం_Wait;

            xReturn = MPU_x_Event_సమూహం_Wait_బిట్లు_నమోదు( &( xParams ) );

            తిరిగి xReturn;
        }

        Event_బిట్లు_t MPU_x_Event_సమూహం_Wait_బిట్లు_Impl( స్థిరరాశి x_Event_సమూహం_Wait_బిట్లు_Params_t * pxParams ) PRIVILEGED_FUNCTION;

        Event_బిట్లు_t MPU_x_Event_సమూహం_Wait_బిట్లు_Impl( స్థిరరాశి x_Event_సమూహం_Wait_బిట్లు_Params_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            Event_బిట్లు_t xReturn = 0;
            Event_సమూహం_Handle_t x_అంతర్గత_Event_సమూహం_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం = pdFALSE;
            పునాది_Type_t xAreParamsReadable = pdFALSE;

            ఒకవేళ( pxParams != ఖాళీ )
            {
                xAreParamsReadable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( pxParams,
                                                                      పరిమాణం( x_Event_సమూహం_Wait_బిట్లు_Params_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            ఒకవేళ( xAreParamsReadable == pdTRUE )
            {
                ఒకవేళ( ( ( pxParams->ux_బిట్లు_గమ్యం_Wait_For & event_EVENT_బిట్లు_CONTROL_బైట్లు ) == 0U ) &&
                    ( pxParams->ux_బిట్లు_గమ్యం_Wait_For != 0U )
                    #ఒకవేళ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                        && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( pxParams->x_Ticks_గమ్యం_Wait != 0U ) ) )
                    #అయితే_ముగింపు
                    )
                {
                    l_సూచీ = ( int32_t ) ( pxParams->x_Event_సమూహం );

                    ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం == pdTRUE )
                        {
                            x_అంతర్గత_Event_సమూహం_Handle = MPU_Get_Event_సమూహం_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                            ఒకవేళ( x_అంతర్గత_Event_సమూహం_Handle != ఖాళీ )
                            {
                                xReturn = x_Event_సమూహం_Wait_బిట్లు( x_అంతర్గత_Event_సమూహం_Handle,
                                                               pxParams->ux_బిట్లు_గమ్యం_Wait_For,
                                                               pxParams->xClearOnExit,
                                                               pxParams->x_Wait_For_All_బిట్లు,
                                                               pxParams->x_Ticks_గమ్యం_Wait );
                            }
                        }
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

        Event_బిట్లు_t MPU_x_Event_సమూహం_Clear_బిట్లు_Impl( Event_సమూహం_Handle_t x_Event_సమూహం,
                                                  స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Clear ) PRIVILEGED_FUNCTION;

        Event_బిట్లు_t MPU_x_Event_సమూహం_Clear_బిట్లు_Impl( Event_సమూహం_Handle_t x_Event_సమూహం,
                                                  స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Clear ) /* PRIVILEGED_FUNCTION */
        {
            Event_బిట్లు_t xReturn = 0;
            Event_సమూహం_Handle_t x_అంతర్గత_Event_సమూహం_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం = pdFALSE;

            ఒకవేళ( ( ux_బిట్లు_గమ్యం_Clear & event_EVENT_బిట్లు_CONTROL_బైట్లు ) == 0U )
            {
                l_సూచీ = ( int32_t ) x_Event_సమూహం;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం == pdTRUE )
                    {
                        x_అంతర్గత_Event_సమూహం_Handle = MPU_Get_Event_సమూహం_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_అంతర్గత_Event_సమూహం_Handle != ఖాళీ )
                        {
                            xReturn = x_Event_సమూహం_Clear_బిట్లు( x_అంతర్గత_Event_సమూహం_Handle, ux_బిట్లు_గమ్యం_Clear );
                        }
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

        Event_బిట్లు_t MPU_x_Event_సమూహం_సమితి_బిట్లు_Impl( Event_సమూహం_Handle_t x_Event_సమూహం,
                                                స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి ) PRIVILEGED_FUNCTION;

        Event_బిట్లు_t MPU_x_Event_సమూహం_సమితి_బిట్లు_Impl( Event_సమూహం_Handle_t x_Event_సమూహం,
                                                స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి ) /* PRIVILEGED_FUNCTION */
        {
            Event_బిట్లు_t xReturn = 0;
            Event_సమూహం_Handle_t x_అంతర్గత_Event_సమూహం_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం = pdFALSE;

            ఒకవేళ( ( ux_బిట్లు_గమ్యం_సమితి & event_EVENT_బిట్లు_CONTROL_బైట్లు ) == 0U )
            {
                l_సూచీ = ( int32_t ) x_Event_సమూహం;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం == pdTRUE )
                    {
                        x_అంతర్గత_Event_సమూహం_Handle = MPU_Get_Event_సమూహం_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_అంతర్గత_Event_సమూహం_Handle != ఖాళీ )
                        {
                            xReturn = x_Event_సమూహం_సమితి_బిట్లు( x_అంతర్గత_Event_సమూహం_Handle, ux_బిట్లు_గమ్యం_సమితి );
                        }
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

        Event_బిట్లు_t MPU_x_Event_సమూహం_Sync_Impl( Event_సమూహం_Handle_t x_Event_సమూహం,
                                             స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి,
                                             స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Wait_For,
                                             TickType_t x_Ticks_గమ్యం_Wait ) PRIVILEGED_FUNCTION;

        Event_బిట్లు_t MPU_x_Event_సమూహం_Sync_Impl( Event_సమూహం_Handle_t x_Event_సమూహం,
                                             స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి,
                                             స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Wait_For,
                                             TickType_t x_Ticks_గమ్యం_Wait ) /* PRIVILEGED_FUNCTION */
        {
            Event_బిట్లు_t xReturn = 0;
            Event_సమూహం_Handle_t x_అంతర్గత_Event_సమూహం_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం = pdFALSE;

            ఒకవేళ( ( ( ux_బిట్లు_గమ్యం_Wait_For & event_EVENT_బిట్లు_CONTROL_బైట్లు ) == 0U ) &&
                ( ux_బిట్లు_గమ్యం_Wait_For != 0U )
                #ఒకవేళ ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                    && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_గమ్యం_Wait != 0U ) ) )
                #అయితే_ముగింపు
                )
            {
                l_సూచీ = ( int32_t ) x_Event_సమూహం;

                ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం == pdTRUE )
                    {
                        x_అంతర్గత_Event_సమూహం_Handle = MPU_Get_Event_సమూహం_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_అంతర్గత_Event_సమూహం_Handle != ఖాళీ )
                        {
                            xReturn = x_Event_సమూహం_Sync( x_అంతర్గత_Event_సమూహం_Handle, ux_బిట్లు_గమ్యం_సమితి, ux_బిట్లు_గమ్యం_Wait_For, x_Ticks_గమ్యం_Wait );
                        }
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_సమూహం_Get_సంఖ్య_Impl( శూన్య * x_Event_సమూహం ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Event_సమూహం_Get_సంఖ్య_Impl( శూన్య * x_Event_సమూహం ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t xReturn = 0;
            Event_సమూహం_Handle_t x_అంతర్గత_Event_సమూహం_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం = pdFALSE;

            l_సూచీ = ( int32_t ) x_Event_సమూహం;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం == pdTRUE )
                {
                    x_అంతర్గత_Event_సమూహం_Handle = MPU_Get_Event_సమూహం_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Event_సమూహం_Handle != ఖాళీ )
                    {
                        xReturn = ux_Event_సమూహం_Get_సంఖ్య( x_అంతర్గత_Event_సమూహం_Handle );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        శూన్య MPU_v_Event_సమూహం_సమితి_సంఖ్య_Impl( శూన్య * x_Event_సమూహం,
                                           UBaseType_t ux_Event_సమూహం_సంఖ్య ) PRIVILEGED_FUNCTION;

        శూన్య MPU_v_Event_సమూహం_సమితి_సంఖ్య_Impl( శూన్య * x_Event_సమూహం,
                                           UBaseType_t ux_Event_సమూహం_సంఖ్య ) /* PRIVILEGED_FUNCTION */
        {
            Event_సమూహం_Handle_t x_అంతర్గత_Event_సమూహం_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం = pdFALSE;

            l_సూచీ = ( int32_t ) x_Event_సమూహం;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_Event_సమూహం == pdTRUE )
                {
                    x_అంతర్గత_Event_సమూహం_Handle = MPU_Get_Event_సమూహం_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_Event_సమూహం_Handle != ఖాళీ )
                    {
                        v_Event_సమూహం_సమితి_సంఖ్య( x_అంతర్గత_Event_సమూహం_Handle, ux_Event_సమూహం_సంఖ్య );
                    }
                }
            }
        }

    #అయితే_ముగింపు /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Event Group APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_సమూహం_Handle_t MPU_x_Event_సమూహం_Create( శూన్య ) /* PRIVILEGED_FUNCTION */
        {
            Event_సమూహం_Handle_t x_అంతర్గత_Event_సమూహం_Handle = ఖాళీ;
            Event_సమూహం_Handle_t x_External_Event_సమూహం_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                x_అంతర్గత_Event_సమూహం_Handle = x_Event_సమూహం_Create();

                ఒకవేళ( x_అంతర్గత_Event_సమూహం_Handle != ఖాళీ )
                {
                    MPU_Store_Event_సమూహం_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_Event_సమూహం_Handle );
                    x_External_Event_సమూహం_Handle = ( Event_సమూహం_Handle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి x_External_Event_సమూహం_Handle;
        }

    #అయితే_ముగింపు /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_SUPPORT_STATIC_కేటాయింపు == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_సమూహం_Handle_t MPU_x_Event_సమూహం_Create_Static( Static_Event_సమూహం_t * px_Event_సమూహం_బఫరు ) /* PRIVILEGED_FUNCTION */
        {
            Event_సమూహం_Handle_t x_అంతర్గత_Event_సమూహం_Handle = ఖాళీ;
            Event_సమూహం_Handle_t x_External_Event_సమూహం_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

            ఒకవేళ( l_సూచీ != -1 )
            {
                x_అంతర్గత_Event_సమూహం_Handle = x_Event_సమూహం_Create_Static( px_Event_సమూహం_బఫరు );

                ఒకవేళ( x_అంతర్గత_Event_సమూహం_Handle != ఖాళీ )
                {
                    MPU_Store_Event_సమూహం_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_Event_సమూహం_Handle );
                    x_External_Event_సమూహం_Handle = ( Event_సమూహం_Handle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                }
                లేకపోతే
                {
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                }
            }

            తిరిగి x_External_Event_సమూహం_Handle;
        }

    #అయితే_ముగింపు /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

        శూన్య MPU_v_Event_సమూహం_Delete( Event_సమూహం_Handle_t x_Event_సమూహం ) /* PRIVILEGED_FUNCTION */
        {
            Event_సమూహం_Handle_t x_అంతర్గత_Event_సమూహం_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = ( int32_t ) x_Event_సమూహం;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_Event_సమూహం_Handle = MPU_Get_Event_సమూహం_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_Event_సమూహం_Handle != ఖాళీ )
                {
                    v_Event_సమూహం_Delete( x_అంతర్గత_Event_సమూహం_Handle );
                    MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );
                }
            }
        }

    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_SUPPORT_STATIC_కేటాయింపు == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        పునాది_Type_t MPU_x_Event_సమూహం_Get_Static_బఫరు( Event_సమూహం_Handle_t x_Event_సమూహం,
                                                   Static_Event_సమూహం_t ** ppx_Event_సమూహం_బఫరు ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            Event_సమూహం_Handle_t x_అంతర్గత_Event_సమూహం_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = ( int32_t ) x_Event_సమూహం;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_Event_సమూహం_Handle = MPU_Get_Event_సమూహం_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_Event_సమూహం_Handle != ఖాళీ )
                {
                    xReturn = x_Event_సమూహం_Get_Static_బఫరు( x_అంతర్గత_Event_సమూహం_Handle, ppx_Event_సమూహం_బఫరు );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        పునాది_Type_t MPU_x_Event_సమూహం_Clear_బిట్లు_From_ISR( Event_సమూహం_Handle_t x_Event_సమూహం,
                                                    స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_Clear ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            Event_సమూహం_Handle_t x_అంతర్గత_Event_సమూహం_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = ( int32_t ) x_Event_సమూహం;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_Event_సమూహం_Handle = MPU_Get_Event_సమూహం_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_Event_సమూహం_Handle != ఖాళీ )
                {
                    xReturn = x_Event_సమూహం_Clear_బిట్లు_From_ISR( x_అంతర్గత_Event_సమూహం_Handle, ux_బిట్లు_గమ్యం_Clear );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        పునాది_Type_t MPU_x_Event_సమూహం_సమితి_బిట్లు_From_ISR( Event_సమూహం_Handle_t x_Event_సమూహం,
                                                  స్థిరరాశి Event_బిట్లు_t ux_బిట్లు_గమ్యం_సమితి,
                                                  పునాది_Type_t * px_Higher_ప్రాధాన్యత_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            Event_సమూహం_Handle_t x_అంతర్గత_Event_సమూహం_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = ( int32_t ) x_Event_సమూహం;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_Event_సమూహం_Handle = MPU_Get_Event_సమూహం_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_Event_సమూహం_Handle != ఖాళీ )
                {
                    xReturn = x_Event_సమూహం_సమితి_బిట్లు_From_ISR( x_అంతర్గత_Event_సమూహం_Handle, ux_బిట్లు_గమ్యం_సమితి, px_Higher_ప్రాధాన్యత_Task_Woken );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )

        Event_బిట్లు_t MPU_x_Event_సమూహం_Get_బిట్లు_From_ISR( Event_సమూహం_Handle_t x_Event_సమూహం ) /* PRIVILEGED_FUNCTION */
        {
            Event_బిట్లు_t xReturn = 0;
            Event_సమూహం_Handle_t x_అంతర్గత_Event_సమూహం_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = ( int32_t ) x_Event_సమూహం;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_Event_సమూహం_Handle = MPU_Get_Event_సమూహం_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_Event_సమూహం_Handle != ఖాళీ )
                {
                    xReturn = x_Event_సమూహం_Get_బిట్లు_From_ISR( x_అంతర్గత_Event_సమూహం_Handle );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for stream buffer APIs.            */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        size_t MPU_x_ప్రవాహం_బఫరు_Send_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                          స్థిరరాశి శూన్య * pv_Tx_దత్తాంశం,
                                          size_t x_దత్తాంశం_నిడివి_బైట్లు,
                                          TickType_t x_Ticks_గమ్యం_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ప్రవాహం_బఫరు_Send_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                          స్థిరరాశి శూన్య * pv_Tx_దత్తాంశం,
                                          size_t x_దత్తాంశం_నిడివి_బైట్లు,
                                          TickType_t x_Ticks_గమ్యం_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Is_Tx_దత్తాంశం_బఫరు_Readable = pdFALSE;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = pdFALSE;

            ఒకవేళ( pv_Tx_దత్తాంశం != ఖాళీ )
            {
                x_Is_Tx_దత్తాంశం_బఫరు_Readable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( pv_Tx_దత్తాంశం,
                                                                           x_దత్తాంశం_నిడివి_బైట్లు,
                                                                           tskMPU_READ_PERMISSION );

                ఒకవేళ( x_Is_Tx_దత్తాంశం_బఫరు_Readable == pdTRUE )
                {
                    l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

                    ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు == pdTRUE )
                        {
                            x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                            ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                            {
                                xReturn = x_ప్రవాహం_బఫరు_Send( x_అంతర్గత_ప్రవాహం_బఫరు_Handle, pv_Tx_దత్తాంశం, x_దత్తాంశం_నిడివి_బైట్లు, x_Ticks_గమ్యం_Wait );
                            }
                        }
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        size_t MPU_x_ప్రవాహం_బఫరు_Receive_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                             శూన్య * pv_Rx_దత్తాంశం,
                                             size_t x_బఫరు_నిడివి_బైట్లు,
                                             TickType_t x_Ticks_గమ్యం_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ప్రవాహం_బఫరు_Receive_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                             శూన్య * pv_Rx_దత్తాంశం,
                                             size_t x_బఫరు_నిడివి_బైట్లు,
                                             TickType_t x_Ticks_గమ్యం_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Is_Rx_దత్తాంశం_బఫరు_Writeable = pdFALSE;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = pdFALSE;

            ఒకవేళ( pv_Rx_దత్తాంశం != ఖాళీ )
            {
                x_Is_Rx_దత్తాంశం_బఫరు_Writeable = x_పోర్టు_Is_Authorized_గమ్యం_Access_బఫరు( pv_Rx_దత్తాంశం,
                                                                            x_బఫరు_నిడివి_బైట్లు,
                                                                            tskMPU_WRITE_PERMISSION );

                ఒకవేళ( x_Is_Rx_దత్తాంశం_బఫరు_Writeable == pdTRUE )
                {
                    l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

                    ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                        ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు == pdTRUE )
                        {
                            x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                            ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                            {
                                xReturn = x_ప్రవాహం_బఫరు_Receive( x_అంతర్గత_ప్రవాహం_బఫరు_Handle, pv_Rx_దత్తాంశం, x_బఫరు_నిడివి_బైట్లు, x_Ticks_గమ్యం_Wait );
                            }
                        }
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_నిండిన_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_నిండిన_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = pdFALSE;

            l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు == pdTRUE )
                {
                    x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                    {
                        xReturn = x_ప్రవాహం_బఫరు_Is_నిండిన( x_అంతర్గత_ప్రవాహం_బఫరు_Handle );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = pdFALSE;

            l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు == pdTRUE )
                {
                    x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                    {
                        xReturn = x_ప్రవాహం_బఫరు_Is_ఖాళీలు( x_అంతర్గత_ప్రవాహం_బఫరు_Handle );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        size_t MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = pdFALSE;

            l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు == pdTRUE )
                {
                    x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                    {
                        xReturn = x_ప్రవాహం_బఫరు_Spaces_అందుబాటు( x_అంతర్గత_ప్రవాహం_బఫరు_Handle );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        size_t MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = pdFALSE;

            l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు == pdTRUE )
                {
                    x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                    {
                        xReturn = x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు( x_అంతర్గత_ప్రవాహం_బఫరు_Handle );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                                         size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                                         size_t xTriggerLevel ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = pdFALSE;

            l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు == pdTRUE )
                {
                    x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                    {
                        xReturn = x_ప్రవాహం_బఫరు_సమితి_Trigger_Level( x_అంతర్గత_ప్రవాహం_బఫరు_Handle, xTriggerLevel );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        size_t MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) PRIVILEGED_FUNCTION;

        size_t MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు_Impl( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;
            పునాది_Type_t x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = pdFALSE;

            l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు = x_పోర్టు_Is_Authorized_గమ్యం_Access_Kernel_Object( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_Calling_Task_Is_Authorized_గమ్యం_Access_ప్రవాహం_బఫరు == pdTRUE )
                {
                    x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                    ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                    {
                        xReturn = x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు( x_అంతర్గత_ప్రవాహం_బఫరు_Handle );
                    }
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Stream Buffer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_SUPPORT_DYNAMIC_కేటాయింపు == 1 ) && ( config_USE_ప్రవాహం_BUFFERS == 1 ) )

        ప్రవాహం_బఫరు_Handle_t MPU_x_ప్రవాహం_బఫరు_Generic_Create( size_t x_బఫరు_కొలత_బైట్లు,
                                                             size_t x_Trigger_Level_బైట్లు,
                                                             పునాది_Type_t x_ప్రవాహం_బఫరు_Type,
                                                             ప్రవాహం_బఫరు_Callback_Function_t pxSendCompletedCallback,
                                                             ప్రవాహం_బఫరు_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            ప్రవాహం_బఫరు_Handle_t x_External_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ఖాళీ ) &&
                          ( pxReceiveCompletedCallback == ఖాళీ ) );

            ఒకవేళ( ( pxSendCompletedCallback == ఖాళీ ) &&
                ( pxReceiveCompletedCallback == ఖాళీ ) )
            {
                l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

                ఒకవేళ( l_సూచీ != -1 )
                {
                    x_అంతర్గత_ప్రవాహం_బఫరు_Handle = x_ప్రవాహం_బఫరు_Generic_Create( x_బఫరు_కొలత_బైట్లు,
                                                                              x_Trigger_Level_బైట్లు,
                                                                              x_ప్రవాహం_బఫరు_Type,
                                                                              ఖాళీ,
                                                                              ఖాళీ );

                    ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                    {
                        MPU_Store_ప్రవాహం_బఫరు_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_ప్రవాహం_బఫరు_Handle );
                        x_External_ప్రవాహం_బఫరు_Handle = ( ప్రవాహం_బఫరు_Handle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                    }
                    లేకపోతే
                    {
                        MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                    }
                }
            }
            లేకపోతే
            {
                trace_ప్రవాహం_బఫరు_CREATE_FAILED( x_ప్రవాహం_బఫరు_Type );
                x_External_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            }

            తిరిగి x_External_ప్రవాహం_బఫరు_Handle;
        }

    #అయితే_ముగింపు /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_SUPPORT_STATIC_కేటాయింపు == 1 ) && ( config_USE_ప్రవాహం_BUFFERS == 1 ) )

        ప్రవాహం_బఫరు_Handle_t MPU_x_ప్రవాహం_బఫరు_Generic_Create_Static( size_t x_బఫరు_కొలత_బైట్లు,
                                                                   size_t x_Trigger_Level_బైట్లు,
                                                                   పునాది_Type_t x_ప్రవాహం_బఫరు_Type,
                                                                   uint8_t * స్థిరరాశి puc_ప్రవాహం_బఫరు_Storage_Area,
                                                                   Static_ప్రవాహం_బఫరు_t * స్థిరరాశి px_Static_ప్రవాహం_బఫరు,
                                                                   ప్రవాహం_బఫరు_Callback_Function_t pxSendCompletedCallback,
                                                                   ప్రవాహం_బఫరు_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            ప్రవాహం_బఫరు_Handle_t x_External_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == ఖాళీ ) &&
                          ( pxReceiveCompletedCallback == ఖాళీ ) );

            ఒకవేళ( ( pxSendCompletedCallback == ఖాళీ ) &&
                ( pxReceiveCompletedCallback == ఖాళీ ) )
            {
                l_సూచీ = MPU_Get_Free_సూచీ_లోపల_Kernel_Object_Pool();

                ఒకవేళ( l_సూచీ != -1 )
                {
                    x_అంతర్గత_ప్రవాహం_బఫరు_Handle = x_ప్రవాహం_బఫరు_Generic_Create_Static( x_బఫరు_కొలత_బైట్లు,
                                                                                    x_Trigger_Level_బైట్లు,
                                                                                    x_ప్రవాహం_బఫరు_Type,
                                                                                    puc_ప్రవాహం_బఫరు_Storage_Area,
                                                                                    px_Static_ప్రవాహం_బఫరు,
                                                                                    ఖాళీ,
                                                                                    ఖాళీ );

                    ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                    {
                        MPU_Store_ప్రవాహం_బఫరు_Handle_At_సూచీ( l_సూచీ, x_అంతర్గత_ప్రవాహం_బఫరు_Handle );
                        x_External_ప్రవాహం_బఫరు_Handle = ( ప్రవాహం_బఫరు_Handle_t ) CONVERT_గమ్యం_EXTERNAL_సూచీ( l_సూచీ );
                    }
                    లేకపోతే
                    {
                        MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( l_సూచీ );
                    }
                }
            }
            లేకపోతే
            {
                trace_ప్రవాహం_బఫరు_CREATE_STATIC_FAILED( xReturn, x_ప్రవాహం_బఫరు_Type );
                x_External_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            }

            తిరిగి x_External_ప్రవాహం_బఫరు_Handle;
        }

    #అయితే_ముగింపు /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        శూన్య MPU_v_ప్రవాహం_బఫరు_Delete( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* PRIVILEGED_FUNCTION */
        {
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                {
                    v_ప్రవాహం_బఫరు_Delete( x_అంతర్గత_ప్రవాహం_బఫరు_Handle );
                }

                MPU_సమితి_సూచీ_Free_లోపల_Kernel_Object_Pool( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );
            }
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Reset( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                {
                    xReturn = x_ప్రవాహం_బఫరు_Reset( x_అంతర్గత_ప్రవాహం_బఫరు_Handle );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( ( config_SUPPORT_STATIC_కేటాయింపు == 1 ) && ( config_USE_ప్రవాహం_BUFFERS == 1 ) )

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Get_Static_Buffers( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_Buffers,
                                                      uint8_t * ppuc_ప్రవాహం_బఫరు_Storage_Area,
                                                      Static_ప్రవాహం_బఫరు_t * ppx_Static_ప్రవాహం_బఫరు ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = ( int32_t ) x_ప్రవాహం_Buffers;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                {
                    xReturn = MPU_x_ప్రవాహం_బఫరు_Get_Static_Buffers( x_అంతర్గత_ప్రవాహం_బఫరు_Handle, ppuc_ప్రవాహం_బఫరు_Storage_Area, ppx_Static_ప్రవాహం_బఫరు );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

    size_t MPU_x_ప్రవాహం_బఫరు_Send_From_ISR( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                         స్థిరరాశి శూన్య * pv_Tx_దత్తాంశం,
                                         size_t x_దత్తాంశం_నిడివి_బైట్లు,
                                         పునాది_Type_t * స్థిరరాశి px_Higher_ప్రాధాన్యత_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
        int32_t l_సూచీ;

        l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
            {
                xReturn = x_ప్రవాహం_బఫరు_Send_From_ISR( x_అంతర్గత_ప్రవాహం_బఫరు_Handle, pv_Tx_దత్తాంశం, x_దత్తాంశం_నిడివి_బైట్లు, px_Higher_ప్రాధాన్యత_Task_Woken );
            }
        }

        తిరిగి xReturn;
    }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

    size_t MPU_x_ప్రవాహం_బఫరు_Receive_From_ISR( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                            శూన్య * pv_Rx_దత్తాంశం,
                                            size_t x_బఫరు_నిడివి_బైట్లు,
                                            పునాది_Type_t * స్థిరరాశి px_Higher_ప్రాధాన్యత_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
        int32_t l_సూచీ;

        l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

        ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
        {
            x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

            ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
            {
                xReturn = x_ప్రవాహం_బఫరు_Receive_From_ISR( x_అంతర్గత_ప్రవాహం_బఫరు_Handle, pv_Rx_దత్తాంశం, x_బఫరు_నిడివి_బైట్లు, px_Higher_ప్రాధాన్యత_Task_Woken );
            }
        }

        తిరిగి xReturn;
    }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Send_Completed_From_ISR( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                                          పునాది_Type_t * px_Higher_ప్రాధాన్యత_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                {
                    xReturn = x_ప్రవాహం_బఫరు_Send_Completed_From_ISR( x_అంతర్గత_ప్రవాహం_బఫరు_Handle, px_Higher_ప్రాధాన్యత_Task_Woken );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Receive_Completed_From_ISR( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు,
                                                             పునాది_Type_t * px_Higher_ప్రాధాన్యత_Task_Woken ) /*PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFALSE;
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                {
                    xReturn = x_ప్రవాహం_బఫరు_Receive_Completed_From_ISR( x_అంతర్గత_ప్రవాహం_బఫరు_Handle, px_Higher_ప్రాధాన్యత_Task_Woken );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

    #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )

        పునాది_Type_t MPU_x_ప్రవాహం_బఫరు_Reset_From_ISR( ప్రవాహం_బఫరు_Handle_t x_ప్రవాహం_బఫరు ) /*PRIVILEGED_FUNCTION */
        {
            పునాది_Type_t xReturn = pdFAIL;
            ప్రవాహం_బఫరు_Handle_t x_అంతర్గత_ప్రవాహం_బఫరు_Handle = ఖాళీ;
            int32_t l_సూచీ;

            l_సూచీ = ( int32_t ) x_ప్రవాహం_బఫరు;

            ఒకవేళ( IS_EXTERNAL_సూచీ_VALID( l_సూచీ ) != pdFALSE )
            {
                x_అంతర్గత_ప్రవాహం_బఫరు_Handle = MPU_Get_ప్రవాహం_బఫరు_Handle_At_సూచీ( CONVERT_గమ్యం_అంతర్గత_సూచీ( l_సూచీ ) );

                ఒకవేళ( x_అంతర్గత_ప్రవాహం_బఫరు_Handle != ఖాళీ )
                {
                    xReturn = x_ప్రవాహం_బఫరు_Reset_From_ISR( x_అంతర్గత_ప్రవాహం_బఫరు_Handle );
                }
            }

            తిరిగి xReturn;
        }

    #అయితే_ముగింపు /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h. */

    #ఒకవేళ configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #అన్తర్భావ "application_defined_privileged_functions.h"
    #అయితే_ముగింపు
/*-----------------------------------------------------------*/

/**
 * @brief Array of system call implementation functions.
 *
 * The index in the array MUST match the corresponding system call number
 * defined in mpu_wrappers.h.
 */
    PRIVILEGED_దత్తాంశం UBaseType_t uxSystemCallImplementations[ అంకె_SYSTEM_CALLS ] =
    {
        #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_xTaskGenericNotifyImpl,                     /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyWaitImpl,                 /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #అయితే_ముగింపు

        #ఒకవేళ ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_xTimerGenericCommandFromTaskImpl,           /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #అయితే_ముగింపు

        #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_సమూహం_Wait_బిట్లు_Impl,                    /* SYSTEM_CALL_xEventGroupWaitBits. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupWaitBits. */
        #అయితే_ముగింపు

        /* The system calls above this line take 5 parameters. */

        #ఒకవేళ ( INCLUDE_xTaskDelayUntil == 1 )
            ( UBaseType_t ) MPU_xTaskDelayUntilImpl,                        /* SYSTEM_CALL_xTaskDelayUntil. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskDelayUntil. */
        #అయితే_ముగింపు

        #ఒకవేళ ( INCLUDE_xTaskAbortDelay == 1 )
            ( UBaseType_t ) MPU_xTaskAbortDelayImpl,                        /* SYSTEM_CALL_xTaskAbortDelay. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskAbortDelay. */
        #అయితే_ముగింపు

        #ఒకవేళ ( INCLUDE_vTaskDelay == 1 )
            ( UBaseType_t ) MPU_vTaskDelayImpl,                             /* SYSTEM_CALL_vTaskDelay. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskDelay. */
        #అయితే_ముగింపు

        #ఒకవేళ ( INCLUDE_ux_Task_ప్రాధాన్యత_Get == 1 )
            ( UBaseType_t ) MPU_ux_Task_ప్రాధాన్యత_Get_Impl,                      /* SYSTEM_CALL_uxTaskPriorityGet. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskPriorityGet. */
        #అయితే_ముగింపు

        #ఒకవేళ ( INCLUDE_eTaskGetState == 1 )
            ( UBaseType_t ) MPU_eTaskGetStateImpl,                          /* SYSTEM_CALL_eTaskGetState. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_eTaskGetState. */
        #అయితే_ముగింపు

        #ఒకవేళ ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_vTaskGetInfoImpl,                           /* SYSTEM_CALL_vTaskGetInfo. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskGetInfo. */
        #అయితే_ముగింపు

        #ఒకవేళ ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
            ( UBaseType_t ) MPU_xTaskGetIdleTaskHandleImpl,                 /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #అయితే_ముగింపు

        #ఒకవేళ ( INCLUDE_vTaskSuspend == 1 )
            ( UBaseType_t ) MPU_vTaskSuspendImpl,                           /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) MPU_vTaskResumeImpl,                            /* SYSTEM_CALL_vTaskResume. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskResume. */
        #అయితే_ముగింపు

        ( UBaseType_t ) MPU_x_Task_Get_Tick_లెక్క_Impl,                          /* SYSTEM_CALL_xTaskGetTickCount. */
        ( UBaseType_t ) MPU_ux_Task_Get_సంఖ్య_యొక్క_Tasks_Impl,                     /* SYSTEM_CALL_uxTaskGetNumberOfTasks. */

        #ఒకవేళ ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 )
            ( UBaseType_t ) MPU_ul_Task_Get_నిరంతరం_సమయం_Counter_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) MPU_ul_Task_Get_నిరంతరం_సమయం_Percent_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #అయితే_ముగింపు

        #ఒకవేళ ( ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Percent_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_నిరంతరం_సమయం_Counter_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #అయితే_ముగింపు

        #ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )
            ( UBaseType_t ) MPU_v_Task_సమితి_Application_Task_ట్యాగ్_Impl,             /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) MPU_x_Task_Get_Application_Task_ట్యాగ్_Impl,             /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #అయితే_ముగింపు

        #ఒకవేళ ( config_అంకె_THREAD_LOCAL_STORAGE_సూచికలు != 0 )
            ( UBaseType_t ) MPU_v_Task_సమితి_Thread_Local_Storage_సూచిక_Impl,      /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) MPU_pv_Task_Get_Thread_Local_Storage_సూచిక_Impl,     /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #అయితే_ముగింపు

        #ఒకవేళ ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_uxTaskGetSystemStateImpl,                   /* SYSTEM_CALL_uxTaskGetSystemState. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetSystemState. */
        #అయితే_ముగింపు

        #ఒకవేళ ( INCLUDE_ux_Task_Get_దొంతర_ఎగువ_Water_Mark == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark_Impl,            /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #అయితే_ముగింపు

        #ఒకవేళ ( INCLUDE_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2 == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_దొంతర_ఎగువ_Water_Mark2_Impl,           /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #అయితే_ముగింపు

        #ఒకవేళ ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )
            ( UBaseType_t ) MPU_xTaskGetCurrentTaskHandleImpl,              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #అయితే_ముగింపు

        #ఒకవేళ ( INCLUDE_xTaskGetSchedulerState == 1 )
            ( UBaseType_t ) MPU_xTaskGetSchedulerStateImpl,                 /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #అయితే_ముగింపు

        ( UBaseType_t ) MPU_v_Task_సమితి_సమయం_బహిర్గతం_State_Impl,                       /* SYSTEM_CALL_vTaskSetTimeOutState. */
        ( UBaseType_t ) MPU_x_Task_Check_For_సమయం_బహిర్గతం_Impl,                       /* SYSTEM_CALL_xTaskCheckForTimeOut. */

        #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_ulTaskGenericNotifyTakeImpl,                /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyStateClearImpl,           /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) MPU_ul_Task_Generic_Notify_విలువ_Clear_Impl,          /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #అయితే_ముగింపు

        ( UBaseType_t ) MPU_x_వరుస_Generic_Send_Impl,                          /* SYSTEM_CALL_xQueueGenericSend. */
        ( UBaseType_t ) MPU_ux_వరుస_Messages_నిరీక్షణ_Impl,                     /* SYSTEM_CALL_uxQueueMessagesWaiting. */
        ( UBaseType_t ) MPU_ux_వరుస_Spaces_అందుబాటు_Impl,                     /* SYSTEM_CALL_uxQueueSpacesAvailable. */
        ( UBaseType_t ) MPU_x_వరుస_Receive_Impl,                              /* SYSTEM_CALL_xQueueReceive. */
        ( UBaseType_t ) MPU_x_వరుస_Peek_Impl,                                 /* SYSTEM_CALL_xQueuePeek. */
        ( UBaseType_t ) MPU_x_వరుస_Semaphore_Take_Impl,                        /* SYSTEM_CALL_xQueueSemaphoreTake. */

        #ఒకవేళ ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
            ( UBaseType_t ) MPU_x_వరుస_Get_Mutex_Holder_Impl,                   /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #అయితే_ముగింపు

        #ఒకవేళ ( configUSE_RECURSIVE_MUTEXES == 1 )
            ( UBaseType_t ) MPU_x_వరుస_Take_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) MPU_x_వరుస_Give_Mutex_Recursive_Impl,               /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #అయితే_ముగింపు

        #ఒకవేళ ( config_USE_వరుస_SETS == 1 )
            ( UBaseType_t ) MPU_x_వరుస_Select_From_సమితి_Impl,                    /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) MPU_x_వరుస_కూడు_గమ్యం_సమితి_Impl,                         /* SYSTEM_CALL_xQueueAddToSet. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueAddToSet. */
        #అయితే_ముగింపు

        #ఒకవేళ config_వరుస_REGISTRY_కొలత > 0
            ( UBaseType_t ) MPU_v_వరుస_కూడు_గమ్యం_Registry_Impl,                    /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) MPU_v_వరుస_Unregister_వరుస_Impl,                  /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) MPU_pc_వరుస_Get_Name_Impl,                         /* SYSTEM_CALL_pcQueueGetName. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcQueueGetName. */
        #అయితే_ముగింపు

        #ఒకవేళ ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_pvTimerGetTimerIDImpl,                      /* SYSTEM_CALL_pvTimerGetTimerID. */
            ( UBaseType_t ) MPU_v_Timer_సమితి_Timer_IDImpl,                       /* SYSTEM_CALL_vTimerSetTimerID. */
            ( UBaseType_t ) MPU_x_Timer_Is_Timer_చురుకైన_Impl,                    /* SYSTEM_CALL_xTimerIsTimerActive. */
            ( UBaseType_t ) MPU_xTimerGetTimerDaemonTaskHandleImpl,         /* SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle. */
            ( UBaseType_t ) MPU_pcTimerGetNameImpl,                         /* SYSTEM_CALL_pcTimerGetName. */
            ( UBaseType_t ) MPU_v_Timer_సమితి_Reload_బహుళకం_Impl,                    /* SYSTEM_CALL_vTimerSetReloadMode. */
            ( UBaseType_t ) MPU_x_Timer_Get_Reload_బహుళకం_Impl,                    /* SYSTEM_CALL_xTimerGetReloadMode. */
            ( UBaseType_t ) MPU_ux_Timer_Get_Reload_బహుళకం_Impl,                   /* SYSTEM_CALL_uxTimerGetReloadMode. */
            ( UBaseType_t ) MPU_xTimerGetPeriodImpl,                        /* SYSTEM_CALL_xTimerGetPeriod. */
            ( UBaseType_t ) MPU_x_Timer_Get_Expiry_సమయం_Impl,                    /* SYSTEM_CALL_xTimerGetExpiryTime. */
        #లేకపోతే
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
        #అయితే_ముగింపు

        #ఒకవేళ ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_సమూహం_Clear_బిట్లు_Impl,                   /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) MPU_x_Event_సమూహం_సమితి_బిట్లు_Impl,                     /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) MPU_x_Event_సమూహం_Sync_Impl,                        /* SYSTEM_CALL_xEventGroupSync. */

            #ఒకవేళ ( configUSE_TRACE_FACILITY == 1 )
                ( UBaseType_t ) MPU_ux_Event_సమూహం_Get_సంఖ్య_Impl,              /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) MPU_v_Event_సమూహం_సమితి_సంఖ్య_Impl,               /* SYSTEM_CALL_vEventGroupSetNumber. */
            #లేకపోతే
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_vEventGroupSetNumber. */
            #అయితే_ముగింపు
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSync. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxEventGroupGetNumber. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vEventGroupSetNumber. */
        #అయితే_ముగింపు

        #ఒకవేళ ( config_USE_ప్రవాహం_BUFFERS == 1 )
            ( UBaseType_t ) MPU_x_ప్రవాహం_బఫరు_Send_Impl,                      /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) MPU_x_ప్రవాహం_బఫరు_Receive_Impl,                   /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) MPU_x_ప్రవాహం_బఫరు_Is_నిండిన_Impl,                    /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) MPU_x_ప్రవాహం_బఫరు_Is_ఖాళీలు_Impl,                   /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) MPU_x_ప్రవాహం_బఫరు_Spaces_అందుబాటు_Impl,           /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) MPU_x_ప్రవాహం_బఫరు_బైట్లు_అందుబాటు_Impl,            /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) MPU_x_ప్రవాహం_బఫరు_సమితి_Trigger_Level_Impl,           /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) MPU_x_ప్రవాహం_బఫరు_తదుపరి_సందేశం_నిడివి_బైట్లు_Impl     /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #లేకపోతే
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #అయితే_ముగింపు

    };
/*-----------------------------------------------------------*/

#అయితే_ముగింపు /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/
