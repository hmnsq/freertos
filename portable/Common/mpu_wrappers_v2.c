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
#परिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "queue.h"
#अन्तर्भाव "timers.h"
#अन्तर्भाव "event_groups.h"
#अन्तर्भाव "stream_buffer.h"
#अन्तर्भाव "mpu_prototypes.h"
#अन्तर्भाव "mpu_syscall_numbers.h"

#अपरिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE
/*-----------------------------------------------------------*/

#यदि ( ( पत्तनम्_USING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) )

    #यदि_अपरिभाषितम् config_PROTECTED_KERNEL_OBJECT_POOL_आकार
        #दोषः config_PROTECTED_KERNEL_OBJECT_POOL_आकार must be defined गन्तव्यम् अधिकतमम् सङ्ख्या सम्बन्धि kernel objects अन्तर् the application.
    #यदि_अन्तः

/**
 * @brief Offset added to the index before returning to the user.
 *
 * If the actual handle is stored at index i, ( i + INDEX_OFFSET )
 * is returned to the user.
 */
    #परिभाषय सूचकांक_विस्थापनम्    1

/**
 * @brief Opaque type for a kernel object.
 */
    संरचना OpaqueObject;
    प्रकारनिर्देश संरचना OpaqueObject * OpaqueObjectHandle_t;

/**
 * @brief Defines kernel object in the kernel object pool.
 */
    प्रकारनिर्देश संरचना KernelObject
    {
        OpaqueObjectHandle_t x_आन्तरिकम्_Object_Handle;
        uint32_t ulKernelObjectType;
        शून्य * pv_Kernel_Object_दत्त;
    } KernelObject_t;

/**
 * @brief Kernel object types.
 */
    #परिभाषय KERNEL_OBJECT_TYPE_INVALID          ( 0UL )
    #परिभाषय KERNEL_OBJECT_TYPE_QUEUE            ( 1UL )
    #परिभाषय KERNEL_OBJECT_TYPE_TASK             ( 2UL )
    #परिभाषय KERNEL_OBJECT_TYPE_प्रवाहः_बफर    ( 3UL )
    #परिभाषय KERNEL_OBJECT_TYPE_EVENT_गणः      ( 4UL )
    #परिभाषय KERNEL_OBJECT_TYPE_TIMER            ( 5UL )

/**
 * @brief Checks whether an external index is valid or not.
 */
    #परिभाषय IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक )   \
    ( ( ( ( l_सूचकांक ) >= सूचकांक_विस्थापनम् ) &&       \
        ( ( l_सूचकांक ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_आकार + सूचकांक_विस्थापनम् ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Checks whether an internal index is valid or not.
 */
    #परिभाषय IS_आन्तरिकम्_सूचकांक_VALID( l_सूचकांक )   \
    ( ( ( ( l_सूचकांक ) >= 0 ) &&                  \
        ( ( l_सूचकांक ) < ( config_PROTECTED_KERNEL_OBJECT_POOL_आकार ) ) ) ? pdTRUE : pdFALSE )

/**
 * @brief Converts an internal index into external.
 */
    #परिभाषय CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक )    ( ( l_सूचकांक ) + सूचकांक_विस्थापनम् )

/**
 * @brief Converts an external index into internal.
 */
    #परिभाषय CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक )    ( ( l_सूचकांक ) - सूचकांक_विस्थापनम् )

/**
 * @brief Max value that fits in a UBaseType_t type.
 */
    #परिभाषय mpuUBASETYPE_MAX    ( ~( ( UBaseType_t ) 0 ) )

/**
 * @brief Check if multiplying a and b will result in overflow.
 */
    #परिभाषय mpu_MULTIPLY_BASETYPE_WILL_अतिप्रवाहः( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( mpuUBASETYPE_MAX / ( a ) ) ) )

/**
 * @brief Get the index of a free slot in the kernel object pool.
 *
 * If a free slot is found, this function marks the slot as
 * "not free".
 *
 * @return Index of a free slot is returned, if a free slot is
 *         found. Otherwise -1 is returned.
 */
    स्थिर int32_t MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool( शून्य ) PRIVILEGED_FUNCTION;

/**
 * @brief Set the given index as free in the kernel object pool.
 *
 * @param lIndex The index to set as free.
 */
    स्थिर शून्य MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( int32_t l_सूचकांक ) PRIVILEGED_FUNCTION;

/**
 * @brief Get the index at which a given kernel object is stored.
 *
 * @param xHandle The given kernel object handle.
 * @param ulKernelObjectType The kernel object type.
 *
 * @return Index at which the kernel object is stored if it is a valid
 *         handle, -1 otherwise.
 */
    स्थिर int32_t MPU_Get_सूचकांक_For_Handle( OpaqueObjectHandle_t xHandle,
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
    स्थिर शून्य MPU_Store_Handle_And_दत्त_At_सूचकांक( int32_t l_सूचकांक,
                                               OpaqueObjectHandle_t xHandle,
                                               शून्य * pv_Kernel_Object_दत्त,
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
    स्थिर OpaqueObjectHandle_t MPU_Get_Handle_At_सूचकांक( int32_t l_सूचकांक,
                                                      uint32_t ulKernelObjectType ) PRIVILEGED_FUNCTION;

    #यदि ( configUSE_TIMERS == 1 )

/**
 * @brief The function registered as callback for all the timers.
 *
 * We intercept all the timer callbacks so that we can call application
 * callbacks with opaque handle.
 *
 * @param xInternalHandle The internal timer handle.
 */
        स्थिर शून्य MPU_TimerCallback( TimerHandle_t x_आन्तरिकम्_Handle ) PRIVILEGED_FUNCTION;

    #यदि_अन्तः /* #if ( configUSE_TIMERS == 1 ) */

/*
 * Wrappers to keep all the casting in one place.
 */
    #परिभाषय MPU_Store_Queue_Handle_At_सूचकांक( l_सूचकांक, xHandle )                 MPU_Store_Handle_And_दत्त_At_सूचकांक( ( l_सूचकांक ), ( OpaqueObjectHandle_t ) ( xHandle ), रिक्त, KERNEL_OBJECT_TYPE_QUEUE )
    #परिभाषय MPU_Get_Queue_Handle_At_सूचकांक( l_सूचकांक )                            ( QueueHandle_t ) MPU_Get_Handle_At_सूचकांक( ( l_सूचकांक ), KERNEL_OBJECT_TYPE_QUEUE )

    #यदि ( configUSE_QUEUE_SETS == 1 )
        #परिभाषय MPU_Store_Queue_समुच्चयः_Handle_At_सूचकांक( l_सूचकांक, xHandle )          MPU_Store_Handle_And_दत्त_At_सूचकांक( ( l_सूचकांक ), ( OpaqueObjectHandle_t ) ( xHandle ), रिक्त, KERNEL_OBJECT_TYPE_QUEUE )
        #परिभाषय MPU_Get_Queue_समुच्चयः_Handle_At_सूचकांक( l_सूचकांक )                     ( Queue_समुच्चयः_Handle_t ) MPU_Get_Handle_At_सूचकांक( ( l_सूचकांक ), KERNEL_OBJECT_TYPE_QUEUE )
        #परिभाषय MPU_Store_Queue_समुच्चयः_Member_Handle_At_सूचकांक( l_सूचकांक, xHandle )    MPU_Store_Handle_And_दत्त_At_सूचकांक( ( l_सूचकांक ), ( OpaqueObjectHandle_t ) ( xHandle ), रिक्त, KERNEL_OBJECT_TYPE_QUEUE )
        #परिभाषय MPU_Get_Queue_समुच्चयः_Member_Handle_At_सूचकांक( l_सूचकांक )               ( Queue_समुच्चयः_Member_Handle_t ) MPU_Get_Handle_At_सूचकांक( ( l_सूचकांक ), KERNEL_OBJECT_TYPE_QUEUE )
        #परिभाषय MPU_Get_सूचकांक_For_Queue_समुच्चयः_Member_Handle( xHandle )             MPU_Get_सूचकांक_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_QUEUE )
    #यदि_अन्तः

/*
 * Wrappers to keep all the casting in one place for Task APIs.
 */
    #परिभाषय MPU_Store_Task_Handle_At_सूचकांक( l_सूचकांक, xHandle )            MPU_Store_Handle_And_दत्त_At_सूचकांक( ( l_सूचकांक ), ( OpaqueObjectHandle_t ) ( xHandle ), रिक्त, KERNEL_OBJECT_TYPE_TASK )
    #परिभाषय MPU_Get_Task_Handle_At_सूचकांक( l_सूचकांक )                       ( TaskHandle_t ) MPU_Get_Handle_At_सूचकांक( ( l_सूचकांक ), KERNEL_OBJECT_TYPE_TASK )
    #परिभाषय MPU_Get_सूचकांक_For_Task_Handle( xHandle )                     MPU_Get_सूचकांक_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TASK )

    #यदि ( configUSE_EVENT_GROUPS == 1 )
/*
 * Wrappers to keep all the casting in one place for Event Group APIs.
 */
        #परिभाषय MPU_Store_Event_गणः_Handle_At_सूचकांक( l_सूचकांक, xHandle )      MPU_Store_Handle_And_दत्त_At_सूचकांक( ( l_सूचकांक ), ( OpaqueObjectHandle_t ) ( xHandle ), रिक्त, KERNEL_OBJECT_TYPE_EVENT_गणः )
        #परिभाषय MPU_Get_Event_गणः_Handle_At_सूचकांक( l_सूचकांक )                 ( Event_गणः_Handle_t ) MPU_Get_Handle_At_सूचकांक( ( l_सूचकांक ), KERNEL_OBJECT_TYPE_EVENT_गणः )
        #परिभाषय MPU_Get_सूचकांक_For_Event_गणः_Handle( xHandle )               MPU_Get_सूचकांक_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_EVENT_गणः )

    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Stream Buffer APIs.
 */
        #परिभाषय MPU_Store_प्रवाहः_बफर_Handle_At_सूचकांक( l_सूचकांक, xHandle )    MPU_Store_Handle_And_दत्त_At_सूचकांक( ( l_सूचकांक ), ( OpaqueObjectHandle_t ) ( xHandle), रिक्त, KERNEL_OBJECT_TYPE_प्रवाहः_बफर )
        #परिभाषय MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( l_सूचकांक )               ( प्रवाहः_बफर_Handle_t ) MPU_Get_Handle_At_सूचकांक( ( l_सूचकांक ), KERNEL_OBJECT_TYPE_प्रवाहः_बफर )
        #परिभाषय MPU_Get_सूचकांक_For_प्रवाहः_बफर_Handle( xHandle )             MPU_Get_सूचकांक_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_प्रवाहः_बफर )

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

    #यदि ( configUSE_TIMERS == 1 )
/*
 * Wrappers to keep all the casting in one place for Timer APIs.
 */
        #परिभाषय MPU_Store_Timer_Handle_At_सूचकांक( l_सूचकांक, xHandle, pxApplicationCallback )    MPU_Store_Handle_And_दत्त_At_सूचकांक( ( l_सूचकांक ), ( OpaqueObjectHandle_t ) ( xHandle ), ( शून्य * ) ( pxApplicationCallback ), KERNEL_OBJECT_TYPE_TIMER )
        #परिभाषय MPU_Get_Timer_Handle_At_सूचकांक( l_सूचकांक )                                      ( TimerHandle_t ) MPU_Get_Handle_At_सूचकांक( ( l_सूचकांक ), KERNEL_OBJECT_TYPE_TIMER )
        #परिभाषय MPU_Get_सूचकांक_For_Timer_Handle( xHandle )                                    MPU_Get_सूचकांक_For_Handle( ( OpaqueObjectHandle_t ) ( xHandle ), KERNEL_OBJECT_TYPE_TIMER )

    #यदि_अन्तः /* #if ( configUSE_TIMERS == 1 ) */

/*-----------------------------------------------------------*/

/**
 * @brief Kernel object pool.
 */
    PRIVILEGED_दत्त स्थिर KernelObject_t xKernelObjectPool[ config_PROTECTED_KERNEL_OBJECT_POOL_आकार ] = { 0 };
/*-----------------------------------------------------------*/

    स्थिर int32_t MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool( शून्य ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_Free_सूचकांक = -1;

        /* This function is called only from resource create APIs
         * which are not supposed to be called from ISRs. Therefore,
         * we only need to suspend the scheduler and do not require
         * critical section. */
        vTaskSuspendAll();
        {
            प्रति( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_आकार; i++ )
            {
                यदि( xKernelObjectPool[ i ].x_आन्तरिकम्_Object_Handle == रिक्त )
                {
                    /* Mark this index as not free. */
                    xKernelObjectPool[ i ].x_आन्तरिकम्_Object_Handle = ( OpaqueObjectHandle_t ) ( ~0U );
                    l_Free_सूचकांक = i;
                    भङ्ग;
                }
            }
        }
        ( शून्य ) xTaskResumeAll();

        प्रत्यागम l_Free_सूचकांक;
    }
/*-----------------------------------------------------------*/

    स्थिर शून्य MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( int32_t l_सूचकांक ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_आन्तरिकम्_सूचकांक_VALID( l_सूचकांक ) != pdFALSE );

        taskENTER_CRITICAL();
        {
            xKernelObjectPool[ l_सूचकांक ].x_आन्तरिकम्_Object_Handle = रिक्त;
            xKernelObjectPool[ l_सूचकांक ].ulKernelObjectType = KERNEL_OBJECT_TYPE_INVALID;
            xKernelObjectPool[ l_सूचकांक ].pv_Kernel_Object_दत्त = रिक्त;
        }
        taskEXIT_CRITICAL();
    }
/*-----------------------------------------------------------*/

    स्थिर int32_t MPU_Get_सूचकांक_For_Handle( OpaqueObjectHandle_t xHandle,
                                          uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        int32_t i, l_सूचकांक = -1;

        configASSERT( xHandle != रिक्त );

        प्रति( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_आकार; i++ )
        {
            यदि( ( xKernelObjectPool[ i ].x_आन्तरिकम्_Object_Handle == xHandle ) &&
                ( xKernelObjectPool[ i ].ulKernelObjectType == ulKernelObjectType ) )
            {
                l_सूचकांक = i;
                भङ्ग;
            }
        }

        प्रत्यागम l_सूचकांक;
    }
/*-----------------------------------------------------------*/

    स्थिर शून्य MPU_Store_Handle_And_दत्त_At_सूचकांक( int32_t l_सूचकांक,
                                               OpaqueObjectHandle_t xHandle,
                                               शून्य * pv_Kernel_Object_दत्त,
                                               uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        configASSERT( IS_आन्तरिकम्_सूचकांक_VALID( l_सूचकांक ) != pdFALSE );
        xKernelObjectPool[ l_सूचकांक ].x_आन्तरिकम्_Object_Handle = xHandle;
        xKernelObjectPool[ l_सूचकांक ].ulKernelObjectType = ulKernelObjectType;
        xKernelObjectPool[ l_सूचकांक ].pv_Kernel_Object_दत्त = pv_Kernel_Object_दत्त;
    }
/*-----------------------------------------------------------*/

    स्थिर OpaqueObjectHandle_t MPU_Get_Handle_At_सूचकांक( int32_t l_सूचकांक,
                                                      uint32_t ulKernelObjectType ) /* PRIVILEGED_FUNCTION */
    {
        OpaqueObjectHandle_t xObjectHandle = रिक्त;

        configASSERT( IS_आन्तरिकम्_सूचकांक_VALID( l_सूचकांक ) != pdFALSE );

        यदि( xKernelObjectPool[ l_सूचकांक ].ulKernelObjectType == ulKernelObjectType )
        {
            xObjectHandle = xKernelObjectPool[ l_सूचकांक ].x_आन्तरिकम्_Object_Handle;
        }

        प्रत्यागम xObjectHandle;
    }
/*-----------------------------------------------------------*/

    #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        शून्य v_Grant_Access_गन्तव्यम्_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                         int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

            यदि( IS_EXTERNAL_सूचकांक_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                यदि( xExternalTaskHandle == रिक्त )
                {
                    v_पत्तनम्_Grant_Access_गन्तव्यम्_Kernel_Object( xExternalTaskHandle, CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( lExternalKernelObjectHandle ) );
                }
                अन्यथा
                {
                    l_External_Task_सूचकांक = ( int32_t ) xExternalTaskHandle;

                    यदि( IS_EXTERNAL_सूचकांक_VALID( l_External_Task_सूचकांक ) != pdFALSE )
                    {
                        x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_External_Task_सूचकांक ) );

                        यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                        {
                            v_पत्तनम्_Grant_Access_गन्तव्यम्_Kernel_Object( x_आन्तरिकम्_Task_Handle,
                                                            CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #यदि_अन्तः /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )

        शून्य v_Revoke_Access_गन्तव्यम्_Kernel_Object( TaskHandle_t xExternalTaskHandle,
                                          int32_t lExternalKernelObjectHandle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_External_Task_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

            यदि( IS_EXTERNAL_सूचकांक_VALID( lExternalKernelObjectHandle ) != pdFALSE )
            {
                यदि( xExternalTaskHandle == रिक्त )
                {
                    v_पत्तनम्_Revoke_Access_गन्तव्यम्_Kernel_Object( xExternalTaskHandle, CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( lExternalKernelObjectHandle ) );
                }
                अन्यथा
                {
                    l_External_Task_सूचकांक = ( int32_t ) xExternalTaskHandle;

                    यदि( IS_EXTERNAL_सूचकांक_VALID( l_External_Task_सूचकांक ) != pdFALSE )
                    {
                        x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_External_Task_सूचकांक ) );

                        यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                        {
                            v_पत्तनम्_Revoke_Access_गन्तव्यम्_Kernel_Object( x_आन्तरिकम्_Task_Handle,
                                                             CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( lExternalKernelObjectHandle ) );
                        }
                    }
                }
            }
        }

    #यदि_अन्तः /* #if ( configENABLE_ACCESS_CONTROL_LIST == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        स्थिर शून्य MPU_TimerCallback( TimerHandle_t x_आन्तरिकम्_Handle ) /* PRIVILEGED_FUNCTION */
        {
            int32_t i, l_सूचकांक = -1;
            TimerHandle_t xExternalHandle = रिक्त;
            TimerCallbackFunction_t px_Application_Call_पृष्ठभागः = रिक्त;

            /* Coming from the timer task and therefore, should be valid. */
            configASSERT( x_आन्तरिकम्_Handle != रिक्त );

            प्रति( i = 0; i < config_PROTECTED_KERNEL_OBJECT_POOL_आकार; i++ )
            {
                यदि( ( ( TimerHandle_t ) xKernelObjectPool[ i ].x_आन्तरिकम्_Object_Handle == x_आन्तरिकम्_Handle ) &&
                    ( xKernelObjectPool[ i ].ulKernelObjectType == KERNEL_OBJECT_TYPE_TIMER ) )
                {
                    l_सूचकांक = i;
                    भङ्ग;
                }
            }

            configASSERT( l_सूचकांक != -1 );
            xExternalHandle = ( TimerHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );

            px_Application_Call_पृष्ठभागः = ( TimerCallbackFunction_t ) xKernelObjectPool[ l_सूचकांक ].pv_Kernel_Object_दत्त;
            px_Application_Call_पृष्ठभागः( xExternalHandle );
        }

    #यदि_अन्तः /* #if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for tasks APIs.                   */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskDelayUntil == 1 )

        आधारः_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ध्रुव pxPreviousWakeTime,
                                            TickType_t xTimeIncrement ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_xTaskDelayUntilImpl( TickType_t * ध्रुव pxPreviousWakeTime,
                                            TickType_t xTimeIncrement ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            आधारः_Type_t xIsPreviousWakeTimeAccessible = pdFALSE;

            यदि( ( pxPreviousWakeTime != रिक्त ) && ( xTimeIncrement > 0U ) )
            {
                xIsPreviousWakeTimeAccessible = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( pxPreviousWakeTime,
                                                                                 परिमाण( TickType_t ),
                                                                                 ( tskMPU_WRITE_PERMISSION | tskMPU_READ_PERMISSION ) );

                यदि( xIsPreviousWakeTimeAccessible == pdTRUE )
                {
                    xReturn = xTaskDelayUntil( pxPreviousWakeTime, xTimeIncrement );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( INCLUDE_xTaskDelayUntil == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskAbortDelay == 1 )

        आधारः_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_xTaskAbortDelayImpl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) xTask;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                {
                    x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                    {
                        xReturn = xTaskAbortDelay( x_आन्तरिकम्_Task_Handle );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( INCLUDE_xTaskAbortDelay == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskDelay == 1 )

        शून्य MPU_vTaskDelayImpl( TickType_t x_Ticks_गन्तव्यम्_Delay ) PRIVILEGED_FUNCTION;

        शून्य MPU_vTaskDelayImpl( TickType_t x_Ticks_गन्तव्यम्_Delay ) /* PRIVILEGED_FUNCTION */
        {
            vTaskDelay( x_Ticks_गन्तव्यम्_Delay );
        }

    #यदि_अन्तः /* if ( INCLUDE_vTaskDelay == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_प्राथमिकता_Get == 1 )

        UBaseType_t MPU_ux_Task_प्राथमिकता_Get_Impl( ध्रुव TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_प्राथमिकता_Get_Impl( ध्रुव TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

            यदि( pxTask == रिक्त )
            {
                uxReturn = ux_Task_प्राथमिकता_Get( pxTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) pxTask;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                    {
                        x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                        {
                            uxReturn = ux_Task_प्राथमिकता_Get( x_आन्तरिकम्_Task_Handle );
                        }
                    }
                }
            }

            प्रत्यागम uxReturn;
        }

    #यदि_अन्तः /* if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_eTaskGetState == 1 )

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) PRIVILEGED_FUNCTION;

        eTaskState MPU_eTaskGetStateImpl( TaskHandle_t pxTask ) /* PRIVILEGED_FUNCTION */
        {
            eTaskState eReturn = eInvalid;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;

            l_सूचकांक = ( int32_t ) pxTask;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                {
                    x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                    {
                        eReturn = eTaskGetState( x_आन्तरिकम्_Task_Handle );
                    }
                }
            }

            प्रत्यागम eReturn;
        }

    #यदि_अन्तः /* if ( INCLUDE_eTaskGetState == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TRACE_FACILITY == 1 )

        शून्य MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_स्थितिः_t * px_Task_स्थितिः,
                                   आधारः_Type_t x_Get_Free_राशिः_Space,
                                   eTaskState eState ) PRIVILEGED_FUNCTION;

        शून्य MPU_vTaskGetInfoImpl( TaskHandle_t xTask,
                                   Task_स्थितिः_t * px_Task_स्थितिः,
                                   आधारः_Type_t x_Get_Free_राशिः_Space,
                                   eTaskState eState ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            आधारः_Type_t x_Is_Task_स्थितिः_Writeable = pdFALSE;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;

            x_Is_Task_स्थितिः_Writeable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( px_Task_स्थितिः,
                                                                      परिमाण( Task_स्थितिः_t ),
                                                                      tskMPU_WRITE_PERMISSION );

            यदि( x_Is_Task_स्थितिः_Writeable == pdTRUE )
            {
                यदि( xTask == रिक्त )
                {
                    vTaskGetInfo( xTask, px_Task_स्थितिः, x_Get_Free_राशिः_Space, eState );
                }
                अन्यथा
                {
                    l_सूचकांक = ( int32_t ) xTask;

                    यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                        {
                            x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                            यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                            {
                                vTaskGetInfo( x_आन्तरिकम्_Task_Handle, px_Task_स्थितिः, x_Get_Free_राशिः_Space, eState );
                            }
                        }
                    }
                }
            }
        }

    #यदि_अन्तः /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskGetIdleTaskHandle == 1 )

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( शून्य ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetIdleTaskHandleImpl( शून्य ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xIdleTaskHandle = रिक्त;

            xIdleTaskHandle = xTaskGetIdleTaskHandle();

            प्रत्यागम xIdleTaskHandle;
        }

    #यदि_अन्तः /* if ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskSuspend == 1 )

        शून्य MPU_vTaskSuspendImpl( TaskHandle_t px_Task_गन्तव्यम्_Suspend ) PRIVILEGED_FUNCTION;

        शून्य MPU_vTaskSuspendImpl( TaskHandle_t px_Task_गन्तव्यम्_Suspend ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;

            यदि( px_Task_गन्तव्यम्_Suspend == रिक्त )
            {
                vTaskSuspend( px_Task_गन्तव्यम्_Suspend );
            }
            अन्यथा
            {
                /* After the scheduler starts, only privileged tasks are allowed
                 * to suspend other tasks. */
                #यदि ( INCLUDE_xTaskGetSchedulerState == 1 )
                    यदि( ( xTaskGetSchedulerState() == taskSCHEDULER_NOT_STARTED ) || ( पत्तनम्_IS_TASK_PRIVILEGED() == pdTRUE ) )
                #अन्यथा
                    यदि( पत्तनम्_IS_TASK_PRIVILEGED() == pdTRUE )
                #यदि_अन्तः
                {
                    l_सूचकांक = ( int32_t ) px_Task_गन्तव्यम्_Suspend;

                    यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                        {
                            x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                            यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                            {
                                vTaskSuspend( x_आन्तरिकम्_Task_Handle );
                            }
                        }
                    }
                }
            }
        }

    #यदि_अन्तः /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskSuspend == 1 )

        शून्य MPU_vTaskResumeImpl( TaskHandle_t px_Task_गन्तव्यम्_Resume ) PRIVILEGED_FUNCTION;

        शून्य MPU_vTaskResumeImpl( TaskHandle_t px_Task_गन्तव्यम्_Resume ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;

            l_सूचकांक = ( int32_t ) px_Task_गन्तव्यम्_Resume;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                {
                    x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                    {
                        vTaskResume( x_आन्तरिकम्_Task_Handle );
                    }
                }
            }
        }

    #यदि_अन्तः /* if ( INCLUDE_vTaskSuspend == 1 ) */
/*-----------------------------------------------------------*/

    TickType_t MPU_x_Task_Get_Tick_गणनम्_Impl( शून्य ) PRIVILEGED_FUNCTION;

    TickType_t MPU_x_Task_Get_Tick_गणनम्_Impl( शून्य ) /* PRIVILEGED_FUNCTION */
    {
        TickType_t xReturn;

        xReturn = x_Task_Get_Tick_गणनम्();

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks_Impl( शून्य ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks_Impl( शून्य ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn;

        uxReturn = ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks();

        प्रत्यागम uxReturn;
    }
/*-----------------------------------------------------------*/

    #यदि ( config_GENERATE_सततम्_TIME_STATS == 1 )

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_गणक_Impl( ध्रुव TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_गणक_Impl( ध्रुव TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_सततम्_TIME_गणक_TYPE xReturn = 0;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;

            यदि( xTask == रिक्त )
            {
                xReturn = ul_Task_Get_सततम्_Time_गणक( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                    {
                        x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                        {
                            xReturn = ul_Task_Get_सततम्_Time_गणक( x_आन्तरिकम्_Task_Handle );
                        }
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_GENERATE_सततम्_TIME_STATS == 1 )

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_Percent_Impl( ध्रुव TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_सततम्_Time_Percent_Impl( ध्रुव TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_सततम्_TIME_गणक_TYPE xReturn = 0;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;

            यदि( xTask == रिक्त )
            {
                xReturn = ul_Task_Get_सततम्_Time_Percent( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                    {
                        x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                        {
                            xReturn = ul_Task_Get_सततम्_Time_Percent( x_आन्तरिकम्_Task_Handle );
                        }
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_GENERATE_सततम्_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_Percent_Impl( शून्य ) PRIVILEGED_FUNCTION;

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_Percent_Impl( शून्य ) /* PRIVILEGED_FUNCTION */
        {
            config_सततम्_TIME_गणक_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_सततम्_Time_Percent();

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_GENERATE_सततम्_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_गणक_Impl( शून्य ) PRIVILEGED_FUNCTION;

        config_सततम्_TIME_गणक_TYPE MPU_ul_Task_Get_Idle_सततम्_Time_गणक_Impl( शून्य ) /* PRIVILEGED_FUNCTION */
        {
            config_सततम्_TIME_गणक_TYPE xReturn;

            xReturn = ul_Task_Get_Idle_सततम्_Time_गणक();

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( ( configGENERATE_RUN_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_APPLICATION_TASK_चिह्नकम् == 1 )

        शून्य MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_चिह्नकम्_मानम् ) PRIVILEGED_FUNCTION;

        शून्य MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्_Impl( TaskHandle_t xTask,
                                                 TaskHookFunction_t px_चिह्नकम्_मानम् ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;

            यदि( xTask == रिक्त )
            {
                v_Task_समुच्चयः_Application_Task_चिह्नकम्( xTask, px_चिह्नकम्_मानम् );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                    {
                        x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                        {
                            v_Task_समुच्चयः_Application_Task_चिह्नकम्( x_आन्तरिकम्_Task_Handle, px_चिह्नकम्_मानम् );
                        }
                    }
                }
            }
        }

    #यदि_अन्तः /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_APPLICATION_TASK_चिह्नकम् == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_चिह्नकम्_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_चिह्नकम्_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = रिक्त;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;

            यदि( xTask == रिक्त )
            {
                xReturn = x_Task_Get_Application_Task_चिह्नकम्( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                    {
                        x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                        {
                            xReturn = x_Task_Get_Application_Task_चिह्नकम्( x_आन्तरिकम्_Task_Handle );
                        }
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_अङ्कः_THREAD_LOCAL_STORAGE_सूचकाः != 0 )

        शून्य MPU_v_Task_समुच्चयः_Thread_Local_Storage_Pointer_Impl( TaskHandle_t x_Task_गन्तव्यम्_समुच्चयः,
                                                        आधारः_Type_t x_सूचकांक,
                                                        शून्य * pv_मानम् ) PRIVILEGED_FUNCTION;

        शून्य MPU_v_Task_समुच्चयः_Thread_Local_Storage_Pointer_Impl( TaskHandle_t x_Task_गन्तव्यम्_समुच्चयः,
                                                        आधारः_Type_t x_सूचकांक,
                                                        शून्य * pv_मानम् ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;

            यदि( x_Task_गन्तव्यम्_समुच्चयः == रिक्त )
            {
                v_Task_समुच्चयः_Thread_Local_Storage_Pointer( x_Task_गन्तव्यम्_समुच्चयः, x_सूचकांक, pv_मानम् );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) x_Task_गन्तव्यम्_समुच्चयः;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                    {
                        x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                        {
                            v_Task_समुच्चयः_Thread_Local_Storage_Pointer( x_आन्तरिकम्_Task_Handle, x_सूचकांक, pv_मानम् );
                        }
                    }
                }
            }
        }

    #यदि_अन्तः /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_अङ्कः_THREAD_LOCAL_STORAGE_सूचकाः != 0 )

        शून्य * MPU_pvTaskGetThreadLocalStoragePointerImpl( TaskHandle_t x_Task_गन्तव्यम्_Query,
                                                           आधारः_Type_t x_सूचकांक ) PRIVILEGED_FUNCTION;

        शून्य * MPU_pvTaskGetThreadLocalStoragePointerImpl( TaskHandle_t x_Task_गन्तव्यम्_Query,
                                                           आधारः_Type_t x_सूचकांक ) /* PRIVILEGED_FUNCTION */
        {
            शून्य * pvReturn = रिक्त;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;

            यदि( x_Task_गन्तव्यम्_Query == रिक्त )
            {
                pvReturn = pvTaskGetThreadLocalStoragePointer( x_Task_गन्तव्यम्_Query, x_सूचकांक );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) x_Task_गन्तव्यम्_Query;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                    {
                        x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                        {
                            pvReturn = pvTaskGetThreadLocalStoragePointer( x_आन्तरिकम्_Task_Handle, x_सूचकांक );
                        }
                    }
                }
            }

            प्रत्यागम pvReturn;
        }

    #यदि_अन्तः /* if ( configNUM_THREAD_LOCAL_STORAGE_POINTERS != 0 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TRACE_FACILITY == 1 )

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_स्थितिः_t * px_Task_स्थितिः_Array,
                                                  UBaseType_t ux_Array_आकार,
                                                  config_सततम्_TIME_गणक_TYPE * pul_योग_सततम्_Time ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_uxTaskGetSystemStateImpl( Task_स्थितिः_t * px_Task_स्थितिः_Array,
                                                  UBaseType_t ux_Array_आकार,
                                                  config_सततम्_TIME_गणक_TYPE * pul_योग_सततम्_Time ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            आधारः_Type_t x_Is_Task_स्थितिः_Array_Writeable = pdFALSE;
            आधारः_Type_t x_Is_योग_सततम्_Time_Writeable = pdFALSE;

            यदि( mpu_MULTIPLY_BASETYPE_WILL_अतिप्रवाहः( परिमाण( Task_स्थितिः_t ), ux_Array_आकार ) == 0 )
            {
                x_Is_Task_स्थितिः_Array_Writeable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( px_Task_स्थितिः_Array,
                                                                               परिमाण( Task_स्थितिः_t ) * ( size_t ) ux_Array_आकार,
                                                                               tskMPU_WRITE_PERMISSION );

                यदि( pul_योग_सततम्_Time != रिक्त )
                {
                    x_Is_योग_सततम्_Time_Writeable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( pul_योग_सततम्_Time,
                                                                                परिमाण( config_सततम्_TIME_गणक_TYPE ),
                                                                                tskMPU_WRITE_PERMISSION );
                }

                यदि( ( x_Is_Task_स्थितिः_Array_Writeable == pdTRUE ) &&
                    ( ( pul_योग_सततम्_Time == रिक्त ) || ( x_Is_योग_सततम्_Time_Writeable == pdTRUE ) ) )
                {
                    uxReturn = uxTaskGetSystemState( px_Task_स्थितिः_Array, ux_Array_आकार, pul_योग_सततम्_Time );
                }
            }

            प्रत्यागम uxReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TRACE_FACILITY == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_Get_राशिः_उच्चः_Water_Mark == 1 )

        UBaseType_t MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;

            यदि( xTask == रिक्त )
            {
                uxReturn = ux_Task_Get_राशिः_उच्चः_Water_Mark( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                    {
                        x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                        {
                            uxReturn = ux_Task_Get_राशिः_उच्चः_Water_Mark( x_आन्तरिकम्_Task_Handle );
                        }
                    }
                }
            }

            प्रत्यागम uxReturn;
        }

    #यदि_अन्तः /* if ( INCLUDE_uxTaskGetStackHighWaterMark == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_Get_राशिः_उच्चः_Water_Mark2 == 1 )

        config_राशिः_गभीरता_TYPE MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2_Impl( TaskHandle_t xTask ) PRIVILEGED_FUNCTION;

        config_राशिः_गभीरता_TYPE MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2_Impl( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            config_राशिः_गभीरता_TYPE uxReturn = 0;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;

            यदि( xTask == रिक्त )
            {
                uxReturn = ux_Task_Get_राशिः_उच्चः_Water_Mark2( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                    {
                        x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                        {
                            uxReturn = ux_Task_Get_राशिः_उच्चः_Water_Mark2( x_आन्तरिकम्_Task_Handle );
                        }
                    }
                }
            }

            प्रत्यागम uxReturn;
        }

    #यदि_अन्तः /* if ( INCLUDE_uxTaskGetStackHighWaterMark2 == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) )

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( शून्य ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTaskGetCurrentTaskHandleImpl( शून्य ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            TaskHandle_t xExternalTaskHandle = रिक्त;
            int32_t l_सूचकांक;

            x_आन्तरिकम्_Task_Handle = xTaskGetCurrentTaskHandle();

            यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
            {
                l_सूचकांक = MPU_Get_सूचकांक_For_Task_Handle( x_आन्तरिकम्_Task_Handle );

                यदि( l_सूचकांक != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
            }

            प्रत्यागम xExternalTaskHandle;
        }

    #यदि_अन्तः /* if ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_RECURSIVE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskGetSchedulerState == 1 )

        आधारः_Type_t MPU_xTaskGetSchedulerStateImpl( शून्य ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_xTaskGetSchedulerStateImpl( शून्य ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = taskSCHEDULER_NOT_STARTED;

            xReturn = xTaskGetSchedulerState();

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( INCLUDE_xTaskGetSchedulerState == 1 ) */
/*-----------------------------------------------------------*/

    शून्य MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State_Impl( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम् ) PRIVILEGED_FUNCTION;

    शून्य MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State_Impl( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम् ) /* PRIVILEGED_FUNCTION */
    {
        आधारः_Type_t x_Is_Time_बहिर्गमनम्_Writeable = pdFALSE;

        यदि( px_Time_बहिर्गमनम् != रिक्त )
        {
            x_Is_Time_बहिर्गमनम्_Writeable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( px_Time_बहिर्गमनम्,
                                                                   परिमाण( Time_बहिर्गमनम्_t ),
                                                                   tskMPU_WRITE_PERMISSION );

            यदि( x_Is_Time_बहिर्गमनम्_Writeable == pdTRUE )
            {
                v_Task_समुच्चयः_Time_बहिर्गमनम्_State( px_Time_बहिर्गमनम् );
            }
        }
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_x_Task_Check_For_Time_बहिर्गमनम्_Impl( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम्,
                                             TickType_t * ध्रुव px_Ticks_गन्तव्यम्_Wait ) PRIVILEGED_FUNCTION;

    आधारः_Type_t MPU_x_Task_Check_For_Time_बहिर्गमनम्_Impl( Time_बहिर्गमनम्_t * ध्रुव px_Time_बहिर्गमनम्,
                                             TickType_t * ध्रुव px_Ticks_गन्तव्यम्_Wait ) /* PRIVILEGED_FUNCTION */
    {
        आधारः_Type_t xReturn = pdFALSE;
        आधारः_Type_t x_Is_Time_बहिर्गमनम्_Writeable = pdFALSE;
        आधारः_Type_t x_Is_Ticks_गन्तव्यम्_Wait_Writeable = pdFALSE;

        यदि( ( px_Time_बहिर्गमनम् != रिक्त ) && ( px_Ticks_गन्तव्यम्_Wait != रिक्त ) )
        {
            x_Is_Time_बहिर्गमनम्_Writeable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( px_Time_बहिर्गमनम्,
                                                                   परिमाण( Time_बहिर्गमनम्_t ),
                                                                   tskMPU_WRITE_PERMISSION );
            x_Is_Ticks_गन्तव्यम्_Wait_Writeable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( px_Ticks_गन्तव्यम्_Wait,
                                                                       परिमाण( TickType_t ),
                                                                       tskMPU_WRITE_PERMISSION );

            यदि( ( x_Is_Time_बहिर्गमनम्_Writeable == pdTRUE ) && ( x_Is_Ticks_गन्तव्यम्_Wait_Writeable == pdTRUE ) )
            {
                xReturn = x_Task_Check_For_Time_बहिर्गमनम्( px_Time_बहिर्गमनम्, px_Ticks_गन्तव्यम्_Wait );
            }
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        आधारः_Type_t MPU_xTaskGenericNotify( TaskHandle_t x_Task_गन्तव्यम्_Notify,
                                           UBaseType_t ux_सूचकांक_गन्तव्यम्_Notify,
                                           uint32_t ul_मानम्,
                                           eNotifyAction eAction,
                                           uint32_t * pul_Previous_Notification_मानम् ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyParams_t xParams;

            xParams.x_Task_गन्तव्यम्_Notify = x_Task_गन्तव्यम्_Notify;
            xParams.ux_सूचकांक_गन्तव्यम्_Notify = ux_सूचकांक_गन्तव्यम्_Notify;
            xParams.ul_मानम् = ul_मानम्;
            xParams.eAction = eAction;
            xParams.pul_Previous_Notification_मानम् = pul_Previous_Notification_मानम्;

            xReturn = MPU_x_Task_Generic_Notify_प्रविष्टिः( &( xParams ) );

            प्रत्यागम xReturn;
        }

        आधारः_Type_t MPU_xTaskGenericNotifyImpl( ध्रुव xTaskGenericNotifyParams_t * pxParams ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_xTaskGenericNotifyImpl( ध्रुव xTaskGenericNotifyParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            आधारः_Type_t x_Is_Previous_Notification_मानम्_Writeable = pdFALSE;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;
            आधारः_Type_t xAreParamsReadable = pdFALSE;

            यदि( pxParams != रिक्त )
            {
                xAreParamsReadable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( pxParams,
                                                                      परिमाण( xTaskGenericNotifyParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            यदि( xAreParamsReadable == pdTRUE )
            {
                यदि( ( pxParams->ux_सूचकांक_गन्तव्यम्_Notify < configTASK_NOTIFICATION_ARRAY_ENTRIES ) &&
                    ( ( pxParams->eAction == eNoAction ) ||
                      ( pxParams->eAction == e_समुच्चयः_द्वयङ्काः ) ||
                      ( pxParams->eAction == eIncrement ) ||
                      ( pxParams->eAction == e_समुच्चयः_मानम्_With_Overwrite ) ||
                      ( pxParams->eAction == e_समुच्चयः_मानम्_Without_Overwrite ) ) )
                {
                    यदि( pxParams->pul_Previous_Notification_मानम् != रिक्त )
                    {
                        x_Is_Previous_Notification_मानम्_Writeable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( pxParams->pul_Previous_Notification_मानम्,
                                                                                                 परिमाण( uint32_t ),
                                                                                                 tskMPU_WRITE_PERMISSION );
                    }

                    यदि( ( pxParams->pul_Previous_Notification_मानम् == रिक्त ) ||
                        ( x_Is_Previous_Notification_मानम्_Writeable == pdTRUE ) )
                    {
                        l_सूचकांक = ( int32_t ) ( pxParams->x_Task_गन्तव्यम्_Notify );

                        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                            यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                            {
                                x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                                यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                                {
                                    xReturn = xTaskGenericNotify( x_आन्तरिकम्_Task_Handle,
                                                                  pxParams->ux_सूचकांक_गन्तव्यम्_Notify,
                                                                  pxParams->ul_मानम्,
                                                                  pxParams->eAction,
                                                                  pxParams->pul_Previous_Notification_मानम् );
                                }
                            }
                        }
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        आधारः_Type_t MPU_xTaskGenericNotifyWait( UBaseType_t ux_सूचकांक_गन्तव्यम्_Wait_On,
                                               uint32_t ul_द्वयङ्काः_गन्तव्यम्_Clear_On_प्रविष्टिः,
                                               uint32_t ul_द्वयङ्काः_गन्तव्यम्_Clear_On_Exit,
                                               uint32_t * pul_Notification_मानम्,
                                               TickType_t x_Ticks_गन्तव्यम्_Wait )
        {
            आधारः_Type_t xReturn = pdFAIL;
            xTaskGenericNotifyWaitParams_t xParams;

            xParams.ux_सूचकांक_गन्तव्यम्_Wait_On = ux_सूचकांक_गन्तव्यम्_Wait_On;
            xParams.ul_द्वयङ्काः_गन्तव्यम्_Clear_On_प्रविष्टिः = ul_द्वयङ्काः_गन्तव्यम्_Clear_On_प्रविष्टिः;
            xParams.ul_द्वयङ्काः_गन्तव्यम्_Clear_On_Exit = ul_द्वयङ्काः_गन्तव्यम्_Clear_On_Exit;
            xParams.pul_Notification_मानम् = pul_Notification_मानम्;
            xParams.x_Ticks_गन्तव्यम्_Wait = x_Ticks_गन्तव्यम्_Wait;

            xReturn = MPU_x_Task_Generic_Notify_Wait_प्रविष्टिः( &( xParams ) );

            प्रत्यागम xReturn;
        }

        आधारः_Type_t MPU_xTaskGenericNotifyWaitImpl( ध्रुव xTaskGenericNotifyWaitParams_t * pxParams ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_xTaskGenericNotifyWaitImpl( ध्रुव xTaskGenericNotifyWaitParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            आधारः_Type_t x_Is_Notification_मानम्_Writable = pdFALSE;
            आधारः_Type_t xAreParamsReadable = pdFALSE;

            यदि( pxParams != रिक्त )
            {
                xAreParamsReadable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( pxParams,
                                                                      परिमाण( xTaskGenericNotifyWaitParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            यदि( xAreParamsReadable == pdTRUE )
            {
                यदि( pxParams->ux_सूचकांक_गन्तव्यम्_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
                {
                    यदि( pxParams->pul_Notification_मानम् != रिक्त )
                    {
                        x_Is_Notification_मानम्_Writable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( pxParams->pul_Notification_मानम्,
                                                                                        परिमाण( uint32_t ),
                                                                                        tskMPU_WRITE_PERMISSION );
                    }

                    यदि( ( pxParams->pul_Notification_मानम् == रिक्त ) ||
                        ( x_Is_Notification_मानम्_Writable == pdTRUE ) )
                    {
                        xReturn = xTaskGenericNotifyWait( pxParams->ux_सूचकांक_गन्तव्यम्_Wait_On,
                                                          pxParams->ul_द्वयङ्काः_गन्तव्यम्_Clear_On_प्रविष्टिः,
                                                          pxParams->ul_द्वयङ्काः_गन्तव्यम्_Clear_On_Exit,
                                                          pxParams->pul_Notification_मानम्,
                                                          pxParams->x_Ticks_गन्तव्यम्_Wait );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_सूचकांक_गन्तव्यम्_Wait_On,
                                                  आधारः_Type_t x_Clear_गणनम्_On_Exit,
                                                  TickType_t x_Ticks_गन्तव्यम्_Wait ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ulTaskGenericNotifyTakeImpl( UBaseType_t ux_सूचकांक_गन्तव्यम्_Wait_On,
                                                  आधारः_Type_t x_Clear_गणनम्_On_Exit,
                                                  TickType_t x_Ticks_गन्तव्यम्_Wait ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;

            यदि( ux_सूचकांक_गन्तव्यम्_Wait_On < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                ulReturn = ulTaskGenericNotifyTake( ux_सूचकांक_गन्तव्यम्_Wait_On, x_Clear_गणनम्_On_Exit, x_Ticks_गन्तव्यम्_Wait );
            }

            प्रत्यागम ulReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        आधारः_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_xTaskGenericNotifyStateClearImpl( TaskHandle_t xTask,
                                                         UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;

            यदि( ux_सूचकांक_गन्तव्यम्_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                यदि( xTask == रिक्त )
                {
                    xReturn = xTaskGenericNotifyStateClear( xTask, ux_सूचकांक_गन्तव्यम्_Clear );
                }
                अन्यथा
                {
                    l_सूचकांक = ( int32_t ) xTask;

                    यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                        {
                            x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                            यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                            {
                                xReturn = xTaskGenericNotifyStateClear( x_आन्तरिकम्_Task_Handle, ux_सूचकांक_गन्तव्यम्_Clear );
                            }
                        }
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        uint32_t MPU_ul_Task_Generic_Notify_मानम्_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear,
                                                        uint32_t ul_द्वयङ्काः_गन्तव्यम्_Clear ) PRIVILEGED_FUNCTION;

        uint32_t MPU_ul_Task_Generic_Notify_मानम्_Clear_Impl( TaskHandle_t xTask,
                                                        UBaseType_t ux_सूचकांक_गन्तव्यम्_Clear,
                                                        uint32_t ul_द्वयङ्काः_गन्तव्यम्_Clear ) /* PRIVILEGED_FUNCTION */
        {
            uint32_t ulReturn = 0;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = pdFALSE;

            यदि( ux_सूचकांक_गन्तव्यम्_Clear < configTASK_NOTIFICATION_ARRAY_ENTRIES )
            {
                यदि( xTask == रिक्त )
                {
                    ulReturn = ul_Task_Generic_Notify_मानम्_Clear( xTask, ux_सूचकांक_गन्तव्यम्_Clear, ul_द्वयङ्काः_गन्तव्यम्_Clear );
                }
                अन्यथा
                {
                    l_सूचकांक = ( int32_t ) xTask;

                    यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Task == pdTRUE )
                        {
                            x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                            यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                            {
                                ulReturn = ul_Task_Generic_Notify_मानम्_Clear( x_आन्तरिकम्_Task_Handle, ux_सूचकांक_गन्तव्यम्_Clear, ul_द्वयङ्काः_गन्तव्यम्_Clear );
                            }
                        }
                    }
                }
            }

            प्रत्यागम ulReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Task APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #यदि ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 )

        आधारः_Type_t MPU_xTaskCreate( TaskFunction_t pv_Task_संहिता,
                                    ध्रुव वर्ण * ध्रुव pcName,
                                    ध्रुव config_राशिः_गभीरता_TYPE ux_राशिः_गभीरता,
                                    शून्य * pvParameters,
                                    UBaseType_t ux_प्राथमिकता,
                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                /* xTaskCreate() can only be used to create privileged tasks in MPU port. */
                यदि( ( ux_प्राथमिकता & पत्तनम्_PRIVILEGE_BIT ) != 0 )
                {
                    xReturn = xTaskCreate( pv_Task_संहिता, pcName, ux_राशिः_गभीरता, pvParameters, ux_प्राथमिकता, &( x_आन्तरिकम्_Task_Handle ) );

                    यदि( ( xReturn == pdPASS ) && ( x_आन्तरिकम्_Task_Handle != रिक्त ) )
                    {
                        MPU_Store_Task_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Task_Handle );

                        यदि( pxCreatedTask != रिक्त )
                        {
                            *pxCreatedTask = ( TaskHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                        }
                    }
                    अन्यथा
                    {
                        MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #यदि ( config_SUPPORT_STATIC_आवण्टनम् == 1 )

        TaskHandle_t MPU_xTaskCreateStatic( TaskFunction_t px_Task_संहिता,
                                            ध्रुव वर्ण * ध्रुव pcName,
                                            ध्रुव config_राशिः_गभीरता_TYPE ux_राशिः_गभीरता,
                                            शून्य * ध्रुव pvParameters,
                                            UBaseType_t ux_प्राथमिकता,
                                            राशिः_Type_t * ध्रुव pux_राशिः_बफर,
                                            StaticTask_t * ध्रुव px_Task_बफर ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xExternalTaskHandle = रिक्त;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                x_आन्तरिकम्_Task_Handle = xTaskCreateStatic( px_Task_संहिता, pcName, ux_राशिः_गभीरता, pvParameters, ux_प्राथमिकता, pux_राशिः_बफर, px_Task_बफर );

                यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                {
                    MPU_Store_Task_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Task_Handle );

                    #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        यदि( ( ux_प्राथमिकता & पत्तनम्_PRIVILEGE_BIT ) == 0 )
                        {
                            v_पत्तनम्_Grant_Access_गन्तव्यम्_Kernel_Object( x_आन्तरिकम्_Task_Handle, l_सूचकांक );
                        }
                    }
                    #यदि_अन्तः

                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम xExternalTaskHandle;
        }

    #यदि_अन्तः /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_vTaskDelete == 1 )

        शून्य MPU_vTaskDelete( TaskHandle_t px_Task_गन्तव्यम्_Delete ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            int32_t l_सूचकांक;

            यदि( px_Task_गन्तव्यम्_Delete == रिक्त )
            {
                x_आन्तरिकम्_Task_Handle = xTaskGetCurrentTaskHandle();
                l_सूचकांक = MPU_Get_सूचकांक_For_Task_Handle( x_आन्तरिकम्_Task_Handle );

                यदि( l_सूचकांक != -1 )
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }

                vTaskDelete( x_आन्तरिकम्_Task_Handle );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) px_Task_गन्तव्यम्_Delete;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                    {
                        MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );
                        vTaskDelete( x_आन्तरिकम्_Task_Handle );
                    }
                }
            }
        }

    #यदि_अन्तः /* #if ( INCLUDE_vTaskDelete == 1 ) */
/*-----------------------------------------------------------*/


    #यदि ( INCLUDE_v_Task_प्राथमिकता_समुच्चयः == 1 )

        शून्य MPU_v_Task_प्राथमिकता_समुच्चयः( TaskHandle_t pxTask,
                                   UBaseType_t ux_New_प्राथमिकता ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            int32_t l_सूचकांक;

            यदि( pxTask == रिक्त )
            {
                v_Task_प्राथमिकता_समुच्चयः( pxTask, ux_New_प्राथमिकता );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) pxTask;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                    {
                        v_Task_प्राथमिकता_समुच्चयः( x_आन्तरिकम्_Task_Handle, ux_New_प्राथमिकता );
                    }
                }
            }
        }

    #यदि_अन्तः /* if ( INCLUDE_vTaskPrioritySet == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_xTaskGetHandle == 1 )

        TaskHandle_t MPU_xTaskGetHandle( ध्रुव वर्ण * pc_Name_गन्तव्यम्_Query ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            TaskHandle_t xExternalTaskHandle = रिक्त;
            int32_t l_सूचकांक;

            x_आन्तरिकम्_Task_Handle = xTaskGetHandle( pc_Name_गन्तव्यम्_Query );

            यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
            {
                l_सूचकांक = MPU_Get_सूचकांक_For_Task_Handle( x_आन्तरिकम्_Task_Handle );

                यदि( l_सूचकांक != -1 )
                {
                    xExternalTaskHandle = ( TaskHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
            }

            प्रत्यागम xExternalTaskHandle;
        }

    #यदि_अन्तः /* if ( INCLUDE_xTaskGetHandle == 1 ) */
/*-----------------------------------------------------------*/


    #यदि ( config_USE_APPLICATION_TASK_चिह्नकम् == 1 )

        आधारः_Type_t MPU_xTaskCallApplicationTaskHook( TaskHandle_t xTask,
                                                     शून्य * pvParameter ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

            यदि( xTask == रिक्त )
            {
                xReturn = xTaskCallApplicationTaskHook( xTask, pvParameter );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                    {
                        xReturn = xTaskCallApplicationTaskHook( x_आन्तरिकम्_Task_Handle, pvParameter );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 )

        आधारः_Type_t MPU_xTaskCreateRestricted( ध्रुव TaskParameters_t * ध्रुव pxTaskDefinition,
                                              TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                xReturn = xTaskCreateRestricted( pxTaskDefinition, &( x_आन्तरिकम्_Task_Handle ) );

                यदि( ( xReturn == pdPASS ) && ( x_आन्तरिकम्_Task_Handle != रिक्त ) )
                {
                    MPU_Store_Task_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Task_Handle );

                    #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        यदि( ( pxTaskDefinition->ux_प्राथमिकता & पत्तनम्_PRIVILEGE_BIT ) == 0 )
                        {
                            v_पत्तनम्_Grant_Access_गन्तव्यम्_Kernel_Object( x_आन्तरिकम्_Task_Handle, l_सूचकांक );
                        }
                    }
                    #यदि_अन्तः

                    यदि( pxCreatedTask != रिक्त )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                    }
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* configSUPPORT_DYNAMIC_ALLOCATION */
/*-----------------------------------------------------------*/

    #यदि ( config_SUPPORT_STATIC_आवण्टनम् == 1 )

        आधारः_Type_t MPU_xTaskCreateRestrictedStatic( ध्रुव TaskParameters_t * ध्रुव pxTaskDefinition,
                                                    TaskHandle_t * pxCreatedTask ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                xReturn = xTaskCreateRestrictedStatic( pxTaskDefinition, &( x_आन्तरिकम्_Task_Handle ) );

                यदि( ( xReturn == pdPASS ) && ( x_आन्तरिकम्_Task_Handle != रिक्त ) )
                {
                    MPU_Store_Task_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Task_Handle );

                    #यदि ( configENABLE_ACCESS_CONTROL_LIST == 1 )
                    {
                        /* By default, an unprivileged task has access to itself. */
                        यदि( ( pxTaskDefinition->ux_प्राथमिकता & पत्तनम्_PRIVILEGE_BIT ) == 0 )
                        {
                            v_पत्तनम्_Grant_Access_गन्तव्यम्_Kernel_Object( x_आन्तरिकम्_Task_Handle, l_सूचकांक );
                        }
                    }
                    #यदि_अन्तः

                    यदि( pxCreatedTask != रिक्त )
                    {
                        *pxCreatedTask = ( TaskHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                    }
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* configSUPPORT_STATIC_ALLOCATION */
/*-----------------------------------------------------------*/

    शून्य MPU_vTaskAllocateMPURegions( TaskHandle_t x_Task_गन्तव्यम्_Modify,
                                      ध्रुव स्मृतिः_Region_t * ध्रुव xRegions ) /* PRIVILEGED_FUNCTION */
    {
        TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
        int32_t l_सूचकांक;

        यदि( x_Task_गन्तव्यम्_Modify == रिक्त )
        {
            vTaskAllocateMPURegions( x_Task_गन्तव्यम्_Modify, xRegions );
        }
        अन्यथा
        {
            l_सूचकांक = ( int32_t ) x_Task_गन्तव्यम्_Modify;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                {
                    vTaskAllocateMPURegions( x_आन्तरिकम्_Task_Handle, xRegions );
                }
            }
        }
    }
/*-----------------------------------------------------------*/

    #यदि ( config_SUPPORT_STATIC_आवण्टनम् == 1 )

        आधारः_Type_t MPU_xTaskGetStaticBuffers( TaskHandle_t xTask,
                                              राशिः_Type_t ** ppux_राशिः_बफर,
                                              StaticTask_t ** ppx_Task_बफर ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t xReturn = pdFALSE;

            यदि( xTask == रिक्त )
            {
                x_आन्तरिकम्_Task_Handle = xTaskGetCurrentTaskHandle();
                xReturn = xTaskGetStaticBuffers( x_आन्तरिकम्_Task_Handle, ppux_राशिः_बफर, ppx_Task_बफर );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                    {
                        xReturn = xTaskGetStaticBuffers( x_आन्तरिकम्_Task_Handle, ppux_राशिः_बफर, ppx_Task_बफर );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    वर्ण * MPU_pcTaskGetName( TaskHandle_t x_Task_गन्तव्यम्_Query ) /* PRIVILEGED_FUNCTION */
    {
        वर्ण * pcReturn = रिक्त;
        int32_t l_सूचकांक;
        TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

        यदि( x_Task_गन्तव्यम्_Query == रिक्त )
        {
            pcReturn = pcTaskGetName( x_Task_गन्तव्यम्_Query );
        }
        अन्यथा
        {
            l_सूचकांक = ( int32_t ) x_Task_गन्तव्यम्_Query;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                {
                    pcReturn = pcTaskGetName( x_आन्तरिकम्_Task_Handle );
                }
            }
        }

        प्रत्यागम pcReturn;
    }
/*-----------------------------------------------------------*/

    #यदि ( INCLUDE_ux_Task_प्राथमिकता_Get == 1 )

        UBaseType_t MPU_ux_Task_प्राथमिकता_Get_From_ISR( ध्रुव TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

            यदि( xTask == रिक्त )
            {
                uxReturn = ux_Task_प्राथमिकता_Get_From_ISR( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                    {
                        uxReturn = ux_Task_प्राथमिकता_Get_From_ISR( x_आन्तरिकम्_Task_Handle );
                    }
                }
            }

            प्रत्यागम uxReturn;
        }

    #यदि_अन्तः /* #if ( INCLUDE_uxTaskPriorityGet == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( INCLUDE_ux_Task_प्राथमिकता_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_आधारः_प्राथमिकता_Get( ध्रुव TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

            यदि( xTask == रिक्त )
            {
                uxReturn = ux_Task_आधारः_प्राथमिकता_Get( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                    {
                        uxReturn = ux_Task_आधारः_प्राथमिकता_Get( x_आन्तरिकम्_Task_Handle );
                    }
                }
            }

            प्रत्यागम uxReturn;
        }

    #यदि_अन्तः /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( INCLUDE_ux_Task_प्राथमिकता_Get == 1 ) && ( configUSE_MUTEXES == 1 ) )

        UBaseType_t MPU_ux_Task_आधारः_प्राथमिकता_Get_From_ISR( ध्रुव TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = configMAX_PRIORITIES;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

            यदि( xTask == रिक्त )
            {
                uxReturn = ux_Task_आधारः_प्राथमिकता_Get_From_ISR( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                    {
                        uxReturn = ux_Task_आधारः_प्राथमिकता_Get_From_ISR( x_आन्तरिकम्_Task_Handle );
                    }
                }
            }

            प्रत्यागम uxReturn;
        }

    #यदि_अन्तः /* #if ( ( INCLUDE_uxTaskPriorityGet == 1 ) && ( configUSE_MUTEXES == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )

        आधारः_Type_t MPU_xTaskResumeFromISR( TaskHandle_t x_Task_गन्तव्यम्_Resume ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

            l_सूचकांक = ( int32_t ) x_Task_गन्तव्यम्_Resume;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                {
                    xReturn = xTaskResumeFromISR( x_आन्तरिकम्_Task_Handle );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( ( INCLUDE_xTaskResumeFromISR == 1 ) && ( INCLUDE_vTaskSuspend == 1 ) )*/
/*---------------------------------------------------------------------------------------*/

    #यदि ( config_USE_APPLICATION_TASK_चिह्नकम् == 1 )

        TaskHookFunction_t MPU_x_Task_Get_Application_Task_चिह्नकम्_From_ISR( TaskHandle_t xTask ) /* PRIVILEGED_FUNCTION */
        {
            TaskHookFunction_t xReturn = रिक्त;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

            यदि( xTask == रिक्त )
            {
                xReturn = x_Task_Get_Application_Task_चिह्नकम्_From_ISR( xTask );
            }
            अन्यथा
            {
                l_सूचकांक = ( int32_t ) xTask;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                    {
                        xReturn = x_Task_Get_Application_Task_चिह्नकम्_From_ISR( x_आन्तरिकम्_Task_Handle );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_APPLICATION_TASK_TAG == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        आधारः_Type_t MPU_xTaskGenericNotifyFromISR( TaskHandle_t x_Task_गन्तव्यम्_Notify,
                                                  UBaseType_t ux_सूचकांक_गन्तव्यम्_Notify,
                                                  uint32_t ul_मानम्,
                                                  eNotifyAction eAction,
                                                  uint32_t * pul_Previous_Notification_मानम्,
                                                  आधारः_Type_t * px_Higher_प्राथमिकता_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

            l_सूचकांक = ( int32_t ) x_Task_गन्तव्यम्_Notify;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                {
                    xReturn = xTaskGenericNotifyFromISR( x_आन्तरिकम्_Task_Handle, ux_सूचकांक_गन्तव्यम्_Notify, ul_मानम्, eAction, pul_Previous_Notification_मानम्, px_Higher_प्राथमिकता_Task_Woken );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_TASK_NOTIFICATIONS == 1 ) */
/*---------------------------------------------------------------------------------------*/

    #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )

        शून्य MPU_vTaskGenericNotifyGiveFromISR( TaskHandle_t x_Task_गन्तव्यम्_Notify,
                                                UBaseType_t ux_सूचकांक_गन्तव्यम्_Notify,
                                                आधारः_Type_t * px_Higher_प्राथमिकता_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            TaskHandle_t x_आन्तरिकम्_Task_Handle = रिक्त;

            l_सूचकांक = ( int32_t ) x_Task_गन्तव्यम्_Notify;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Task_Handle = MPU_Get_Task_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Task_Handle != रिक्त )
                {
                    vTaskGenericNotifyGiveFromISR( x_आन्तरिकम्_Task_Handle, ux_सूचकांक_गन्तव्यम्_Notify, px_Higher_प्राथमिकता_Task_Woken );
                }
            }
        }
    #यदि_अन्तः /*#if ( configUSE_TASK_NOTIFICATIONS == 1 )*/
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for queue APIs.                   */
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueGenericSendImpl( QueueHandle_t xQueue,
                                          ध्रुव शून्य * ध्रुव pv_Item_गन्तव्यम्_Queue,
                                          TickType_t x_Ticks_गन्तव्यम्_Wait,
                                          आधारः_Type_t xCopyPosition ) PRIVILEGED_FUNCTION;

    आधारः_Type_t MPU_xQueueGenericSendImpl( QueueHandle_t xQueue,
                                          ध्रुव शून्य * ध्रुव pv_Item_गन्तव्यम्_Queue,
                                          TickType_t x_Ticks_गन्तव्यम्_Wait,
                                          आधारः_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_सूचकांक;
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
        आधारः_Type_t xReturn = pdFAIL;
        आधारः_Type_t x_Is_Item_गन्तव्यम्_Queue_Readable = pdFALSE;
        आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = pdFALSE;
        UBaseType_t ux_Queue_Item_आकार, ux_Queue_दीर्घता;

        l_सूचकांक = ( int32_t ) xQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue == pdTRUE )
            {
                x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                {
                    ux_Queue_Item_आकार = ux_Queue_Get_Queue_Item_आकार( x_आन्तरिकम्_Queue_Handle );
                    ux_Queue_दीर्घता = ux_Queue_Get_Queue_दीर्घता( x_आन्तरिकम्_Queue_Handle );

                    यदि( ( !( ( pv_Item_गन्तव्यम्_Queue == रिक्त ) && ( ux_Queue_Item_आकार != ( UBaseType_t ) 0U ) ) ) &&
                        ( !( ( xCopyPosition == queueOVERWRITE ) && ( ux_Queue_दीर्घता != ( UBaseType_t ) 1U ) ) )
                        #यदि ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_गन्तव्यम्_Wait != 0U ) ) )
                        #यदि_अन्तः
                        )
                    {
                        यदि( pv_Item_गन्तव्यम्_Queue != रिक्त )
                        {
                            x_Is_Item_गन्तव्यम्_Queue_Readable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( pv_Item_गन्तव्यम्_Queue,
                                                                                      ux_Queue_Item_आकार,
                                                                                      tskMPU_READ_PERMISSION );
                        }

                        यदि( ( pv_Item_गन्तव्यम्_Queue == रिक्त ) || ( x_Is_Item_गन्तव्यम्_Queue_Readable == pdTRUE ) )
                        {
                            xReturn = xQueueGenericSend( x_आन्तरिकम्_Queue_Handle, pv_Item_गन्तव्यम्_Queue, x_Ticks_गन्तव्यम्_Wait, xCopyPosition );
                        }
                    }
                }
            }
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Queue_Messages_प्रतीक्षा_Impl( ध्रुव QueueHandle_t pxQueue ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Queue_Messages_प्रतीक्षा_Impl( ध्रुव QueueHandle_t pxQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_सूचकांक;
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
        UBaseType_t uxReturn = 0;
        आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = pdFALSE;

        l_सूचकांक = ( int32_t ) pxQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue == pdTRUE )
            {
                x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                {
                    uxReturn = ux_Queue_Messages_प्रतीक्षा( x_आन्तरिकम्_Queue_Handle );
                }
            }
        }

        प्रत्यागम uxReturn;
    }
/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Queue_Spaces_उपलब्धम्_Impl( ध्रुव QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

    UBaseType_t MPU_ux_Queue_Spaces_उपलब्धम्_Impl( ध्रुव QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_सूचकांक;
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
        UBaseType_t uxReturn = 0;
        आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = pdFALSE;

        l_सूचकांक = ( int32_t ) xQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue == pdTRUE )
            {
                x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                {
                    uxReturn = ux_Queue_Spaces_उपलब्धम्( x_आन्तरिकम्_Queue_Handle );
                }
            }
        }

        प्रत्यागम uxReturn;
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueReceiveImpl( QueueHandle_t pxQueue,
                                      शून्य * ध्रुव pv_बफर,
                                      TickType_t x_Ticks_गन्तव्यम्_Wait ) PRIVILEGED_FUNCTION;

    आधारः_Type_t MPU_xQueueReceiveImpl( QueueHandle_t pxQueue,
                                      शून्य * ध्रुव pv_बफर,
                                      TickType_t x_Ticks_गन्तव्यम्_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_सूचकांक;
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
        आधारः_Type_t xReturn = pdFAIL;
        आधारः_Type_t x_Is_Receive_बफर_Writable = pdFALSE;
        आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = pdFALSE;
        UBaseType_t ux_Queue_Item_आकार;

        l_सूचकांक = ( int32_t ) pxQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue == pdTRUE )
            {
                x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                {
                    ux_Queue_Item_आकार = ux_Queue_Get_Queue_Item_आकार( x_आन्तरिकम्_Queue_Handle );

                    यदि( ( !( ( ( pv_बफर ) == रिक्त ) && ( ux_Queue_Item_आकार != ( UBaseType_t ) 0U ) ) )
                        #यदि ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_गन्तव्यम्_Wait != 0U ) ) )
                        #यदि_अन्तः
                        )
                    {
                        x_Is_Receive_बफर_Writable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( pv_बफर,
                                                                                    ux_Queue_Item_आकार,
                                                                                    tskMPU_WRITE_PERMISSION );

                        यदि( x_Is_Receive_बफर_Writable == pdTRUE )
                        {
                            xReturn = xQueueReceive( x_आन्तरिकम्_Queue_Handle, pv_बफर, x_Ticks_गन्तव्यम्_Wait );
                        }
                    }
                }
            }
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueuePeekImpl( QueueHandle_t xQueue,
                                   शून्य * ध्रुव pv_बफर,
                                   TickType_t x_Ticks_गन्तव्यम्_Wait ) PRIVILEGED_FUNCTION;

    आधारः_Type_t MPU_xQueuePeekImpl( QueueHandle_t xQueue,
                                   शून्य * ध्रुव pv_बफर,
                                   TickType_t x_Ticks_गन्तव्यम्_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_सूचकांक;
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
        आधारः_Type_t xReturn = pdFAIL;
        आधारः_Type_t x_Is_Receive_बफर_Writable = pdFALSE;
        UBaseType_t ux_Queue_Item_आकार;
        आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = pdFALSE;

        l_सूचकांक = ( int32_t ) xQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue == pdTRUE )
            {
                x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                {
                    ux_Queue_Item_आकार = ux_Queue_Get_Queue_Item_आकार( x_आन्तरिकम्_Queue_Handle );

                    यदि( ( !( ( ( pv_बफर ) == रिक्त ) && ( ux_Queue_Item_आकार != ( UBaseType_t ) 0U ) ) )
                        #यदि ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_गन्तव्यम्_Wait != 0U ) ) )
                        #यदि_अन्तः
                        )
                    {
                        x_Is_Receive_बफर_Writable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( pv_बफर,
                                                                                    ux_Queue_Item_आकार,
                                                                                    tskMPU_WRITE_PERMISSION );

                        यदि( x_Is_Receive_बफर_Writable == pdTRUE )
                        {
                            xReturn = xQueuePeek( x_आन्तरिकम्_Queue_Handle, pv_बफर, x_Ticks_गन्तव्यम्_Wait );
                        }
                    }
                }
            }
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueSemaphoreTakeImpl( QueueHandle_t xQueue,
                                            TickType_t x_Ticks_गन्तव्यम्_Wait ) PRIVILEGED_FUNCTION;

    आधारः_Type_t MPU_xQueueSemaphoreTakeImpl( QueueHandle_t xQueue,
                                            TickType_t x_Ticks_गन्तव्यम्_Wait ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_सूचकांक;
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
        आधारः_Type_t xReturn = pdFAIL;
        UBaseType_t ux_Queue_Item_आकार;
        आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = pdFALSE;

        l_सूचकांक = ( int32_t ) xQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue == pdTRUE )
            {
                x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                {
                    ux_Queue_Item_आकार = ux_Queue_Get_Queue_Item_आकार( x_आन्तरिकम्_Queue_Handle );

                    यदि( ( ux_Queue_Item_आकार == 0U )
                        #यदि ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                            && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_गन्तव्यम्_Wait != 0U ) ) )
                        #यदि_अन्तः
                        )
                    {
                        xReturn = xQueueSemaphoreTake( x_आन्तरिकम्_Queue_Handle, x_Ticks_गन्तव्यम्_Wait );
                    }
                }
            }
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolderImpl( QueueHandle_t xSemaphore ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xQueueGetMutexHolderImpl( QueueHandle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_आन्तरिकम्_Handle = रिक्त;
            TaskHandle_t xMutexHolderTaskExternalHandle = रिक्त;
            int32_t l_सूचकांक, l_Mutex_Holder_Task_सूचकांक;
            QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = pdFALSE;


            l_सूचकांक = ( int32_t ) xSemaphore;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue == pdTRUE )
                {
                    x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                    {
                        x_Mutex_Holder_Task_आन्तरिकम्_Handle = xQueueGetMutexHolder( x_आन्तरिकम्_Queue_Handle );

                        यदि( x_Mutex_Holder_Task_आन्तरिकम्_Handle != रिक्त )
                        {
                            l_Mutex_Holder_Task_सूचकांक = MPU_Get_सूचकांक_For_Task_Handle( x_Mutex_Holder_Task_आन्तरिकम्_Handle );

                            यदि( l_Mutex_Holder_Task_सूचकांक != -1 )
                            {
                                xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_Mutex_Holder_Task_सूचकांक ) );
                            }
                        }
                    }
                }
            }

            प्रत्यागम xMutexHolderTaskExternalHandle;
        }

    #यदि_अन्तः /* if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_RECURSIVE_MUTEXES == 1 )

        आधारः_Type_t MPU_xQueueTakeMutexRecursiveImpl( QueueHandle_t xMutex,
                                                     TickType_t x_खण्डम्_Time ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_xQueueTakeMutexRecursiveImpl( QueueHandle_t xMutex,
                                                     TickType_t x_खण्डम्_Time ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = pdFALSE;
            int32_t l_सूचकांक;
            QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
            UBaseType_t ux_Queue_Item_आकार;

            l_सूचकांक = ( int32_t ) xMutex;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue == pdTRUE )
                {
                    x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                    {
                        ux_Queue_Item_आकार = ux_Queue_Get_Queue_Item_आकार( x_आन्तरिकम्_Queue_Handle );

                        यदि( ux_Queue_Item_आकार == 0 )
                        {
                            xReturn = xQueueTakeMutexRecursive( x_आन्तरिकम्_Queue_Handle, x_खण्डम्_Time );
                        }
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_RECURSIVE_MUTEXES == 1 )

        आधारः_Type_t MPU_xQueueGiveMutexRecursiveImpl( QueueHandle_t xMutex ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_xQueueGiveMutexRecursiveImpl( QueueHandle_t xMutex ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = pdFALSE;
            int32_t l_सूचकांक;
            QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;

            l_सूचकांक = ( int32_t ) xMutex;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue == pdTRUE )
                {
                    x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                    {
                        xReturn = xQueueGiveMutexRecursive( x_आन्तरिकम्_Queue_Handle );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_RECURSIVE_MUTEXES == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_QUEUE_SETS == 1 )

        Queue_समुच्चयः_Member_Handle_t MPU_x_Queue_Select_From_समुच्चयः_Impl( Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः,
                                                            TickType_t x_खण्डम्_Time_Ticks ) PRIVILEGED_FUNCTION;

        Queue_समुच्चयः_Member_Handle_t MPU_x_Queue_Select_From_समुच्चयः_Impl( Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः,
                                                            TickType_t x_खण्डम्_Time_Ticks ) /* PRIVILEGED_FUNCTION */
        {
            Queue_समुच्चयः_Handle_t x_आन्तरिकम्_Queue_समुच्चयः_Handle = रिक्त;
            Queue_समुच्चयः_Member_Handle_t x_Selected_Member_आन्तरिकम् = रिक्त;
            Queue_समुच्चयः_Member_Handle_t xSelectedMemberExternal = रिक्त;
            int32_t l_सूचकांक_Queue_समुच्चयः, l_सूचकांक_Selected_Member;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue_समुच्चयः = pdFALSE;

            l_सूचकांक_Queue_समुच्चयः = ( int32_t ) x_Queue_समुच्चयः;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक_Queue_समुच्चयः ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue_समुच्चयः = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक_Queue_समुच्चयः ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue_समुच्चयः == pdTRUE )
                {
                    x_आन्तरिकम्_Queue_समुच्चयः_Handle = MPU_Get_Queue_समुच्चयः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक_Queue_समुच्चयः ) );

                    यदि( x_आन्तरिकम्_Queue_समुच्चयः_Handle != रिक्त )
                    {
                        x_Selected_Member_आन्तरिकम् = x_Queue_Select_From_समुच्चयः( x_आन्तरिकम्_Queue_समुच्चयः_Handle, x_खण्डम्_Time_Ticks );

                        यदि( x_Selected_Member_आन्तरिकम् != रिक्त )
                        {
                            l_सूचकांक_Selected_Member = MPU_Get_सूचकांक_For_Queue_समुच्चयः_Member_Handle( x_Selected_Member_आन्तरिकम् );

                            यदि( l_सूचकांक_Selected_Member != -1 )
                            {
                                xSelectedMemberExternal = ( Queue_समुच्चयः_Member_Handle_t ) ( CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक_Selected_Member ) );
                            }
                        }
                    }
                }
            }

            प्रत्यागम xSelectedMemberExternal;
        }

    #यदि_अन्तः /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_QUEUE_SETS == 1 )

        आधारः_Type_t MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः_Impl( Queue_समुच्चयः_Member_Handle_t xQueueOrSemaphore,
                                           Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः_Impl( Queue_समुच्चयः_Member_Handle_t xQueueOrSemaphore,
                                           Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            Queue_समुच्चयः_Member_Handle_t x_आन्तरिकम्_Queue_समुच्चयः_Member_Handle = रिक्त;
            Queue_समुच्चयः_Handle_t x_आन्तरिकम्_Queue_समुच्चयः_Handle = रिक्त;
            int32_t l_सूचकांक_Queue_समुच्चयः, l_सूचकांक_Queue_समुच्चयः_Member;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue_समुच्चयः = pdFALSE;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue_समुच्चयः_Member = pdFALSE;

            l_सूचकांक_Queue_समुच्चयः = ( int32_t ) x_Queue_समुच्चयः;
            l_सूचकांक_Queue_समुच्चयः_Member = ( int32_t ) xQueueOrSemaphore;

            यदि( ( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक_Queue_समुच्चयः ) != pdFALSE ) &&
                ( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक_Queue_समुच्चयः_Member ) != pdFALSE ) )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue_समुच्चयः = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक_Queue_समुच्चयः ) );
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue_समुच्चयः_Member = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक_Queue_समुच्चयः_Member ) );

                यदि( ( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue_समुच्चयः == pdTRUE ) && ( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue_समुच्चयः_Member == pdTRUE ) )
                {
                    x_आन्तरिकम्_Queue_समुच्चयः_Handle = MPU_Get_Queue_समुच्चयः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक_Queue_समुच्चयः ) );
                    x_आन्तरिकम्_Queue_समुच्चयः_Member_Handle = MPU_Get_Queue_समुच्चयः_Member_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक_Queue_समुच्चयः_Member ) );

                    यदि( ( x_आन्तरिकम्_Queue_समुच्चयः_Handle != रिक्त ) && ( x_आन्तरिकम्_Queue_समुच्चयः_Member_Handle != रिक्त ) )
                    {
                        xReturn = x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः( x_आन्तरिकम्_Queue_समुच्चयः_Member_Handle, x_आन्तरिकम्_Queue_समुच्चयः_Handle );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि config_QUEUE_REGISTRY_आकार > 0

        शून्य MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry_Impl( QueueHandle_t xQueue,
                                          ध्रुव वर्ण * pcName ) PRIVILEGED_FUNCTION;

        शून्य MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry_Impl( QueueHandle_t xQueue,
                                          ध्रुव वर्ण * pcName ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = pdFALSE;

            l_सूचकांक = ( int32_t ) xQueue;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue == pdTRUE )
                {
                    x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                    {
                        v_Queue_सङ्कलय_गन्तव्यम्_Registry( x_आन्तरिकम्_Queue_Handle, pcName );
                    }
                }
            }
        }

    #यदि_अन्तः /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #यदि config_QUEUE_REGISTRY_आकार > 0

        शून्य MPU_vQueueUnregisterQueueImpl( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

        शून्य MPU_vQueueUnregisterQueueImpl( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = pdFALSE;

            l_सूचकांक = ( int32_t ) xQueue;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue == pdTRUE )
                {
                    x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                    {
                        vQueueUnregisterQueue( x_आन्तरिकम्_Queue_Handle );
                    }
                }
            }
        }

    #यदि_अन्तः /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

    #यदि config_QUEUE_REGISTRY_आकार > 0

        ध्रुव वर्ण * MPU_pcQueueGetNameImpl( QueueHandle_t xQueue ) PRIVILEGED_FUNCTION;

        ध्रुव वर्ण * MPU_pcQueueGetNameImpl( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
        {
            ध्रुव वर्ण * pcReturn = रिक्त;
            QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = pdFALSE;

            l_सूचकांक = ( int32_t ) xQueue;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Queue == pdTRUE )
                {
                    x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                    {
                        pcReturn = pcQueueGetName( x_आन्तरिकम्_Queue_Handle );
                    }
                }
            }

            प्रत्यागम pcReturn;
        }

    #यदि_अन्तः /* if configQUEUE_REGISTRY_SIZE > 0 */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Queue APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    शून्य MPU_vQueueDelete( QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
        int32_t l_सूचकांक;

        l_सूचकांक = ( int32_t ) xQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
            {
                vQueueDelete( x_आन्तरिकम्_Queue_Handle );
                MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );
            }
        }
    }
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 ) )

        QueueHandle_t MPU_xQueueCreateMutex( ध्रुव uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
            QueueHandle_t xExternalQueueHandle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                x_आन्तरिकम्_Queue_Handle = xQueueCreateMutex( ucQueueType );

                यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                {
                    MPU_Store_Queue_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Queue_Handle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम xExternalQueueHandle;
        }

    #यदि_अन्तः /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_MUTEXES == 1 ) && ( config_SUPPORT_STATIC_आवण्टनम् == 1 ) )

        QueueHandle_t MPU_xQueueCreateMutexStatic( ध्रुव uint8_t ucQueueType,
                                                   StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
            QueueHandle_t xExternalQueueHandle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                x_आन्तरिकम्_Queue_Handle = xQueueCreateMutexStatic( ucQueueType, pxStaticQueue );

                यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                {
                    MPU_Store_Queue_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Queue_Handle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम xExternalQueueHandle;
        }

    #यदि_अन्तः /* if ( ( configUSE_MUTEXES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphore( UBaseType_t ux_गणनम्_मानम्,
                                                         UBaseType_t ux_Initial_गणनम् ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
            QueueHandle_t xExternalQueueHandle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                x_आन्तरिकम्_Queue_Handle = xQueueCreateCountingSemaphore( ux_गणनम्_मानम्, ux_Initial_गणनम् );

                यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                {
                    MPU_Store_Queue_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Queue_Handle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम xExternalQueueHandle;
        }

    #यदि_अन्तः /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( config_SUPPORT_STATIC_आवण्टनम् == 1 ) )

        QueueHandle_t MPU_xQueueCreateCountingSemaphoreStatic( ध्रुव UBaseType_t ux_Max_गणनम्,
                                                               ध्रुव UBaseType_t ux_Initial_गणनम्,
                                                               StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
            QueueHandle_t xExternalQueueHandle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                x_आन्तरिकम्_Queue_Handle = xQueueCreateCountingSemaphoreStatic( ux_Max_गणनम्, ux_Initial_गणनम्, pxStaticQueue );

                यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                {
                    MPU_Store_Queue_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Queue_Handle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम xExternalQueueHandle;
        }

    #यदि_अन्तः /* if ( ( configUSE_COUNTING_SEMAPHORES == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 )

        QueueHandle_t MPU_xQueueGenericCreate( UBaseType_t ux_Queue_दीर्घता,
                                               UBaseType_t ux_Item_आकार,
                                               uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
            QueueHandle_t xExternalQueueHandle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                x_आन्तरिकम्_Queue_Handle = xQueueGenericCreate( ux_Queue_दीर्घता, ux_Item_आकार, ucQueueType );

                यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                {
                    MPU_Store_Queue_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Queue_Handle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम xExternalQueueHandle;
        }

    #यदि_अन्तः /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_SUPPORT_STATIC_आवण्टनम् == 1 )

        QueueHandle_t MPU_xQueueGenericCreateStatic( ध्रुव UBaseType_t ux_Queue_दीर्घता,
                                                     ध्रुव UBaseType_t ux_Item_आकार,
                                                     uint8_t * pucQueueStorage,
                                                     StaticQueue_t * pxStaticQueue,
                                                     ध्रुव uint8_t ucQueueType ) /* PRIVILEGED_FUNCTION */
        {
            QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
            QueueHandle_t xExternalQueueHandle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                x_आन्तरिकम्_Queue_Handle = xQueueGenericCreateStatic( ux_Queue_दीर्घता, ux_Item_आकार, pucQueueStorage, pxStaticQueue, ucQueueType );

                यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                {
                    MPU_Store_Queue_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Queue_Handle );
                    xExternalQueueHandle = ( QueueHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम xExternalQueueHandle;
        }

    #यदि_अन्तः /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) */
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueGenericReset( QueueHandle_t xQueue,
                                       आधारः_Type_t xNewQueue ) /* PRIVILEGED_FUNCTION */
    {
        int32_t l_सूचकांक;
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
        आधारः_Type_t xReturn = pdFAIL;

        l_सूचकांक = ( int32_t ) xQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
            {
                xReturn = xQueueGenericReset( x_आन्तरिकम्_Queue_Handle, xNewQueue );
            }
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_QUEUE_SETS == 1 ) && ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 ) )

        Queue_समुच्चयः_Handle_t MPU_x_Queue_Create_समुच्चयः( UBaseType_t ux_Event_Queue_दीर्घता ) /* PRIVILEGED_FUNCTION */
        {
            Queue_समुच्चयः_Handle_t x_आन्तरिकम्_Queue_समुच्चयः_Handle = रिक्त;
            Queue_समुच्चयः_Handle_t x_External_Queue_समुच्चयः_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                x_आन्तरिकम्_Queue_समुच्चयः_Handle = x_Queue_Create_समुच्चयः( ux_Event_Queue_दीर्घता );

                यदि( x_आन्तरिकम्_Queue_समुच्चयः_Handle != रिक्त )
                {
                    MPU_Store_Queue_समुच्चयः_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Queue_समुच्चयः_Handle );
                    x_External_Queue_समुच्चयः_Handle = ( Queue_समुच्चयः_Handle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम x_External_Queue_समुच्चयः_Handle;
        }

    #यदि_अन्तः /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_QUEUE_SETS == 1 ) && ( config_SUPPORT_STATIC_आवण्टनम् == 1 ) )

        Queue_समुच्चयः_Handle_t MPU_x_Queue_Create_समुच्चयः_Static( ध्रुव UBaseType_t ux_Event_Queue_दीर्घता,
                                                    uint8_t * pucQueueStorage,
                                                    StaticQueue_t * pxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            Queue_समुच्चयः_Handle_t x_आन्तरिकम्_Queue_समुच्चयः_Handle = रिक्त;
            Queue_समुच्चयः_Handle_t x_External_Queue_समुच्चयः_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                x_आन्तरिकम्_Queue_समुच्चयः_Handle = x_Queue_Create_समुच्चयः_Static( ux_Event_Queue_दीर्घता, pucQueueStorage, pxStaticQueue );

                यदि( x_आन्तरिकम्_Queue_समुच्चयः_Handle != रिक्त )
                {
                    MPU_Store_Queue_समुच्चयः_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Queue_समुच्चयः_Handle );
                    x_External_Queue_समुच्चयः_Handle = ( Queue_समुच्चयः_Handle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम x_External_Queue_समुच्चयः_Handle;
        }

    #यदि_अन्तः /* if ( ( configUSE_QUEUE_SETS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_QUEUE_SETS == 1 )

        आधारः_Type_t MPU_x_Queue_Remove_From_समुच्चयः( Queue_समुच्चयः_Member_Handle_t xQueueOrSemaphore,
                                            Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            Queue_समुच्चयः_Member_Handle_t x_आन्तरिकम्_Queue_समुच्चयः_Member_Handle = रिक्त;
            Queue_समुच्चयः_Handle_t x_आन्तरिकम्_Queue_समुच्चयः_Handle = रिक्त;
            int32_t l_सूचकांक_Queue_समुच्चयः, l_सूचकांक_Queue_समुच्चयः_Member;

            l_सूचकांक_Queue_समुच्चयः = ( int32_t ) x_Queue_समुच्चयः;
            l_सूचकांक_Queue_समुच्चयः_Member = ( int32_t ) xQueueOrSemaphore;

            यदि( ( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक_Queue_समुच्चयः ) != pdFALSE ) &&
                ( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक_Queue_समुच्चयः_Member ) != pdFALSE ) )
            {
                x_आन्तरिकम्_Queue_समुच्चयः_Handle = MPU_Get_Queue_समुच्चयः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक_Queue_समुच्चयः ) );
                x_आन्तरिकम्_Queue_समुच्चयः_Member_Handle = MPU_Get_Queue_समुच्चयः_Member_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक_Queue_समुच्चयः_Member ) );

                यदि( ( x_आन्तरिकम्_Queue_समुच्चयः_Handle != रिक्त ) && ( x_आन्तरिकम्_Queue_समुच्चयः_Member_Handle != रिक्त ) )
                {
                    xReturn = x_Queue_Remove_From_समुच्चयः( x_आन्तरिकम्_Queue_समुच्चयः_Member_Handle, x_आन्तरिकम्_Queue_समुच्चयः_Handle );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_SUPPORT_STATIC_आवण्टनम् == 1 )

        आधारः_Type_t MPU_xQueueGenericGetStaticBuffers( QueueHandle_t xQueue,
                                                      uint8_t ** ppucQueueStorage,
                                                      StaticQueue_t ** ppxStaticQueue ) /* PRIVILEGED_FUNCTION */
        {
            int32_t l_सूचकांक;
            QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;
            आधारः_Type_t xReturn = pdFALSE;

            l_सूचकांक = ( int32_t ) xQueue;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
                {
                    xReturn = xQueueGenericGetStaticBuffers( x_आन्तरिकम्_Queue_Handle, ppucQueueStorage, ppxStaticQueue );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /*if ( configSUPPORT_STATIC_ALLOCATION == 1 )*/
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueGenericSendFromISR( QueueHandle_t xQueue,
                                             ध्रुव शून्य * ध्रुव pv_Item_गन्तव्यम्_Queue,
                                             आधारः_Type_t * ध्रुव px_Higher_प्राथमिकता_Task_Woken,
                                             ध्रुव आधारः_Type_t xCopyPosition ) /* PRIVILEGED_FUNCTION */
    {
        आधारः_Type_t xReturn = pdFAIL;
        int32_t l_सूचकांक;
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;

        l_सूचकांक = ( int32_t ) xQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
            {
                xReturn = xQueueGenericSendFromISR( x_आन्तरिकम्_Queue_Handle, pv_Item_गन्तव्यम्_Queue, px_Higher_प्राथमिकता_Task_Woken, xCopyPosition );
            }
        }

        प्रत्यागम xReturn;
    }

/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueGiveFromISR( QueueHandle_t xQueue,
                                      आधारः_Type_t * ध्रुव px_Higher_प्राथमिकता_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        आधारः_Type_t xReturn = pdFAIL;
        int32_t l_सूचकांक;
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;

        l_सूचकांक = ( int32_t ) xQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
            {
                xReturn = xQueueGiveFromISR( x_आन्तरिकम्_Queue_Handle, px_Higher_प्राथमिकता_Task_Woken );
            }
        }

        प्रत्यागम xReturn;
    }

/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueuePeekFromISR( QueueHandle_t xQueue,
                                      शून्य * ध्रुव pv_बफर ) /* PRIVILEGED_FUNCTION */
    {
        आधारः_Type_t xReturn = pdFAIL;
        int32_t l_सूचकांक;
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;

        l_सूचकांक = ( int32_t ) xQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
            {
                xReturn = xQueuePeekFromISR( x_आन्तरिकम्_Queue_Handle, pv_बफर );
            }
        }

        प्रत्यागम xReturn;
    }

/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_xQueueReceiveFromISR( QueueHandle_t xQueue,
                                         शून्य * ध्रुव pv_बफर,
                                         आधारः_Type_t * ध्रुव px_Higher_प्राथमिकता_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        आधारः_Type_t xReturn = pdFAIL;
        int32_t l_सूचकांक;
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;

        l_सूचकांक = ( int32_t ) xQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
            {
                xReturn = xQueueReceiveFromISR( x_आन्तरिकम्_Queue_Handle, pv_बफर, px_Higher_प्राथमिकता_Task_Woken );
            }
        }

        प्रत्यागम xReturn;
    }

/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_x_Queue_Is_Queue_रिक्तानि_From_ISR( ध्रुव QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        आधारः_Type_t xReturn = pdFAIL;
        int32_t l_सूचकांक;
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;

        l_सूचकांक = ( int32_t ) xQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
            {
                xReturn = x_Queue_Is_Queue_रिक्तानि_From_ISR( x_आन्तरिकम्_Queue_Handle );
            }
        }

        प्रत्यागम xReturn;
    }
/*-----------------------------------------------------------*/

    आधारः_Type_t MPU_x_Queue_Is_Queue_पूर्णम्_From_ISR( ध्रुव QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        आधारः_Type_t xReturn = pdFAIL;
        int32_t l_सूचकांक;
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;

        l_सूचकांक = ( int32_t ) xQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
            {
                xReturn = x_Queue_Is_Queue_पूर्णम्_From_ISR( x_आन्तरिकम्_Queue_Handle );
            }
        }

        प्रत्यागम xReturn;
    }

/*-----------------------------------------------------------*/

    UBaseType_t MPU_ux_Queue_Messages_प्रतीक्षा_From_ISR( ध्रुव QueueHandle_t xQueue ) /* PRIVILEGED_FUNCTION */
    {
        UBaseType_t uxReturn = 0;
        int32_t l_सूचकांक;
        QueueHandle_t x_आन्तरिकम्_Queue_Handle = रिक्त;

        l_सूचकांक = ( int32_t ) xQueue;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_आन्तरिकम्_Queue_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_आन्तरिकम्_Queue_Handle != रिक्त )
            {
                uxReturn = ux_Queue_Messages_प्रतीक्षा_From_ISR( x_आन्तरिकम्_Queue_Handle );
            }
        }

        प्रत्यागम uxReturn;
    }

/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )

        TaskHandle_t MPU_xQueueGetMutexHolderFromISR( QueueHandle_t xSemaphore ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t x_Mutex_Holder_Task_आन्तरिकम्_Handle = रिक्त;
            TaskHandle_t xMutexHolderTaskExternalHandle = रिक्त;
            int32_t l_सूचकांक, l_Mutex_Holder_Task_सूचकांक;
            QueueHandle_t x_आन्तरिकम्_Semaphore_Handle = रिक्त;

            l_सूचकांक = ( int32_t ) xSemaphore;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Semaphore_Handle = MPU_Get_Queue_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Semaphore_Handle != रिक्त )
                {
                    x_Mutex_Holder_Task_आन्तरिकम्_Handle = xQueueGetMutexHolder( x_आन्तरिकम्_Semaphore_Handle );

                    यदि( x_Mutex_Holder_Task_आन्तरिकम्_Handle != रिक्त )
                    {
                        l_Mutex_Holder_Task_सूचकांक = MPU_Get_सूचकांक_For_Task_Handle( x_Mutex_Holder_Task_आन्तरिकम्_Handle );

                        यदि( l_Mutex_Holder_Task_सूचकांक != -1 )
                        {
                            xMutexHolderTaskExternalHandle = ( TaskHandle_t ) ( CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_Mutex_Holder_Task_सूचकांक ) );
                        }
                    }
                }
            }

            प्रत्यागम xMutexHolderTaskExternalHandle;
        }

    #यदि_अन्तः /* #if ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_QUEUE_SETS == 1 )

        Queue_समुच्चयः_Member_Handle_t MPU_x_Queue_Select_From_समुच्चयः_From_ISR( Queue_समुच्चयः_Handle_t x_Queue_समुच्चयः ) /* PRIVILEGED_FUNCTION */
        {
            Queue_समुच्चयः_Handle_t x_आन्तरिकम्_Queue_समुच्चयः_Handle = रिक्त;
            Queue_समुच्चयः_Member_Handle_t x_Selected_Member_आन्तरिकम् = रिक्त;
            Queue_समुच्चयः_Member_Handle_t xSelectedMemberExternal = रिक्त;
            int32_t l_सूचकांक_Queue_समुच्चयः, l_सूचकांक_Selected_Member;

            l_सूचकांक_Queue_समुच्चयः = ( int32_t ) x_Queue_समुच्चयः;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक_Queue_समुच्चयः ) != pdFALSE )
            {
                x_आन्तरिकम्_Queue_समुच्चयः_Handle = MPU_Get_Queue_समुच्चयः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक_Queue_समुच्चयः ) );

                यदि( x_आन्तरिकम्_Queue_समुच्चयः_Handle != रिक्त )
                {
                    x_Selected_Member_आन्तरिकम् = x_Queue_Select_From_समुच्चयः_From_ISR( x_आन्तरिकम्_Queue_समुच्चयः_Handle );

                    यदि( x_Selected_Member_आन्तरिकम् != रिक्त )
                    {
                        l_सूचकांक_Selected_Member = MPU_Get_सूचकांक_For_Queue_समुच्चयः_Member_Handle( x_Selected_Member_आन्तरिकम् );

                        यदि( l_सूचकांक_Selected_Member != -1 )
                        {
                            xSelectedMemberExternal = ( Queue_समुच्चयः_Member_Handle_t ) ( CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक_Selected_Member ) );
                        }
                    }
                }
            }

            प्रत्यागम xSelectedMemberExternal;
        }

    #यदि_अन्तः /* if ( configUSE_QUEUE_SETS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*            MPU wrappers for timers APIs.                  */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        शून्य * MPU_pvTimerGetTimerIDImpl( ध्रुव TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        शून्य * MPU_pvTimerGetTimerIDImpl( ध्रुव TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            शून्य * pvReturn = रिक्त;
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer == pdTRUE )
                {
                    x_आन्तरिकम्_Timer_Handle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                    {
                        pvReturn = pvTimerGetTimerID( x_आन्तरिकम्_Timer_Handle );
                    }
                }
            }

            प्रत्यागम pvReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        शून्य MPU_v_Timer_समुच्चयः_Timer_IDImpl( TimerHandle_t xTimer,
                                       शून्य * pvNewID ) PRIVILEGED_FUNCTION;

        शून्य MPU_v_Timer_समुच्चयः_Timer_IDImpl( TimerHandle_t xTimer,
                                       शून्य * pvNewID ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer == pdTRUE )
                {
                    x_आन्तरिकम्_Timer_Handle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                    {
                        v_Timer_समुच्चयः_Timer_ID( x_आन्तरिकम्_Timer_Handle, pvNewID );
                    }
                }
            }
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        आधारः_Type_t MPU_x_Timer_Is_Timer_सक्रिय_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_x_Timer_Is_Timer_सक्रिय_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer == pdTRUE )
                {
                    x_आन्तरिकम्_Timer_Handle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                    {
                        xReturn = x_Timer_Is_Timer_सक्रिय( x_आन्तरिकम्_Timer_Handle );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( शून्य ) PRIVILEGED_FUNCTION;

        TaskHandle_t MPU_xTimerGetTimerDaemonTaskHandleImpl( शून्य ) /* PRIVILEGED_FUNCTION */
        {
            TaskHandle_t xReturn;

            xReturn = xTimerGetTimerDaemonTaskHandle();

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        आधारः_Type_t MPU_xTimerGenericCommandFromTask( TimerHandle_t xTimer,
                                                     ध्रुव आधारः_Type_t xCommandID,
                                                     ध्रुव TickType_t x_Optional_मानम्,
                                                     आधारः_Type_t * ध्रुव px_Higher_प्राथमिकता_Task_Woken,
                                                     ध्रुव TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            आधारः_Type_t xReturn = pdFALSE;
            xTimerGenericCommandFromTaskParams_t xParams;

            xParams.xTimer = xTimer;
            xParams.xCommandID = xCommandID;
            xParams.x_Optional_मानम् = x_Optional_मानम्;
            xParams.px_Higher_प्राथमिकता_Task_Woken = px_Higher_प्राथमिकता_Task_Woken;
            xParams.x_Ticks_गन्तव्यम्_Wait = x_Ticks_गन्तव्यम्_Wait;

            xReturn = MPU_x_Timer_Generic_Command_From_Task_प्रविष्टिः( &( xParams ) );

            प्रत्यागम xReturn;
        }

        आधारः_Type_t MPU_xTimerGenericCommandFromTaskImpl( ध्रुव xTimerGenericCommandFromTaskParams_t * pxParams ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_xTimerGenericCommandFromTaskImpl( ध्रुव xTimerGenericCommandFromTaskParams_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Is_Higher_प्राथमिकता_Task_Woken_Writeable = pdFALSE;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = pdFALSE;
            आधारः_Type_t xAreParamsReadable = pdFALSE;

            यदि( pxParams != रिक्त )
            {
                xAreParamsReadable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( pxParams,
                                                                      परिमाण( xTimerGenericCommandFromTaskParams_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            यदि( xAreParamsReadable == pdTRUE )
            {
                यदि( pxParams->xCommandID < tmrFIRST_FROM_ISR_COMMAND )
                {
                    यदि( pxParams->px_Higher_प्राथमिकता_Task_Woken != रिक्त )
                    {
                        x_Is_Higher_प्राथमिकता_Task_Woken_Writeable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( pxParams->px_Higher_प्राथमिकता_Task_Woken,
                                                                                               परिमाण( आधारः_Type_t ),
                                                                                               tskMPU_WRITE_PERMISSION );
                    }

                    यदि( ( pxParams->px_Higher_प्राथमिकता_Task_Woken == रिक्त ) ||
                        ( x_Is_Higher_प्राथमिकता_Task_Woken_Writeable == pdTRUE ) )
                    {
                        l_सूचकांक = ( int32_t ) ( pxParams->xTimer );

                        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                        {
                            x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                            यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer == pdTRUE )
                            {
                                x_आन्तरिकम्_Timer_Handle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                                यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                                {
                                    xReturn = xTimerGenericCommandFromTask( x_आन्तरिकम्_Timer_Handle,
                                                                            pxParams->xCommandID,
                                                                            pxParams->x_Optional_मानम्,
                                                                            pxParams->px_Higher_प्राथमिकता_Task_Woken,
                                                                            pxParams->x_Ticks_गन्तव्यम्_Wait );
                                }
                            }
                        }
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        ध्रुव वर्ण * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        ध्रुव वर्ण * MPU_pcTimerGetNameImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            ध्रुव वर्ण * pcReturn = रिक्त;
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer == pdTRUE )
                {
                    x_आन्तरिकम्_Timer_Handle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                    {
                        pcReturn = pcTimerGetName( x_आन्तरिकम्_Timer_Handle );
                    }
                }
            }

            प्रत्यागम pcReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        शून्य MPU_v_Timer_समुच्चयः_Reload_बहुलकम्_Impl( TimerHandle_t xTimer,
                                          ध्रुव आधारः_Type_t xAutoReload ) PRIVILEGED_FUNCTION;

        शून्य MPU_v_Timer_समुच्चयः_Reload_बहुलकम्_Impl( TimerHandle_t xTimer,
                                          ध्रुव आधारः_Type_t xAutoReload ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer == pdTRUE )
                {
                    x_आन्तरिकम्_Timer_Handle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                    {
                        v_Timer_समुच्चयः_Reload_बहुलकम्( x_आन्तरिकम्_Timer_Handle, xAutoReload );
                    }
                }
            }
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        आधारः_Type_t MPU_x_Timer_Get_Reload_बहुलकम्_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_x_Timer_Get_Reload_बहुलकम्_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer == pdTRUE )
                {
                    x_आन्तरिकम्_Timer_Handle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                    {
                        xReturn = x_Timer_Get_Reload_बहुलकम्( x_आन्तरिकम्_Timer_Handle );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        UBaseType_t MPU_ux_Timer_Get_Reload_बहुलकम्_Impl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Timer_Get_Reload_बहुलकम्_Impl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t uxReturn = 0;
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer == pdTRUE )
                {
                    x_आन्तरिकम्_Timer_Handle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                    {
                        uxReturn = ux_Timer_Get_Reload_बहुलकम्( x_आन्तरिकम्_Timer_Handle );
                    }
                }
            }

            प्रत्यागम uxReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetPeriodImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer == pdTRUE )
                {
                    x_आन्तरिकम्_Timer_Handle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                    {
                        xReturn = xTimerGetPeriod( x_आन्तरिकम्_Timer_Handle );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        TickType_t MPU_xTimerGetExpiryTimeImpl( TimerHandle_t xTimer ) PRIVILEGED_FUNCTION;

        TickType_t MPU_xTimerGetExpiryTimeImpl( TimerHandle_t xTimer ) /* PRIVILEGED_FUNCTION */
        {
            TickType_t xReturn = 0;
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Timer == pdTRUE )
                {
                    x_आन्तरिकम्_Timer_Handle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                    {
                        xReturn = xTimerGetExpiryTime( x_आन्तरिकम्_Timer_Handle );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Timer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #यदि ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreate( ध्रुव वर्ण * ध्रुव pcTimerName,
                                        ध्रुव TickType_t x_Timer_Period_अन्तर्_Ticks,
                                        ध्रुव आधारः_Type_t xAutoReload,
                                        शून्य * ध्रुव pvTimerID,
                                        TimerCallbackFunction_t pxCallbackFunction ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            TimerHandle_t xExternalTimerHandle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                x_आन्तरिकम्_Timer_Handle = xTimerCreate( pcTimerName, x_Timer_Period_अन्तर्_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback );

                यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                {
                    MPU_Store_Timer_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम xExternalTimerHandle;
        }

    #यदि_अन्तः /* if ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_SUPPORT_STATIC_आवण्टनम् == 1 ) && ( configUSE_TIMERS == 1 )

        TimerHandle_t MPU_xTimerCreateStatic( ध्रुव वर्ण * ध्रुव pcTimerName,
                                              ध्रुव TickType_t x_Timer_Period_अन्तर्_Ticks,
                                              ध्रुव आधारः_Type_t xAutoReload,
                                              शून्य * ध्रुव pvTimerID,
                                              TimerCallbackFunction_t pxCallbackFunction,
                                              StaticTimer_t * px_Timer_बफर ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            TimerHandle_t xExternalTimerHandle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                x_आन्तरिकम्_Timer_Handle = xTimerCreateStatic( pcTimerName, x_Timer_Period_अन्तर्_Ticks, xAutoReload, pvTimerID, MPU_TimerCallback, px_Timer_बफर );

                यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                {
                    MPU_Store_Timer_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Timer_Handle, pxCallbackFunction );
                    xExternalTimerHandle = ( TimerHandle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम xExternalTimerHandle;
        }

    #यदि_अन्तः /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_SUPPORT_STATIC_आवण्टनम् == 1 ) && ( configUSE_TIMERS == 1 )

        आधारः_Type_t MPU_x_Timer_Get_Static_बफर( TimerHandle_t xTimer,
                                              StaticTimer_t ** ppx_Timer_बफर ) /* PRIVILEGED_FUNCTION */
        {
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t xReturn = pdFALSE;

            l_सूचकांक = ( int32_t ) xTimer;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Timer_Handle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                {
                    xReturn = x_Timer_Get_Static_बफर( x_आन्तरिकम्_Timer_Handle, ppx_Timer_बफर );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        आधारः_Type_t MPU_xTimerGenericCommandFromISR( TimerHandle_t xTimer,
                                                    ध्रुव आधारः_Type_t xCommandID,
                                                    ध्रुव TickType_t x_Optional_मानम्,
                                                    आधारः_Type_t * ध्रुव px_Higher_प्राथमिकता_Task_Woken,
                                                    ध्रुव TickType_t x_Ticks_गन्तव्यम्_Wait ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) xTimer;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Timer_Handle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                {
                    xReturn = xTimerGenericCommandFromISR( x_आन्तरिकम्_Timer_Handle, xCommandID, x_Optional_मानम्, px_Higher_प्राथमिकता_Task_Woken, x_Ticks_गन्तव्यम्_Wait );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_TIMERS == 1 )

        आधारः_Type_t MPU_xTimerDelete( TimerHandle_t xTimer, TickType_t x_Ticks_गन्तव्यम्_Wait ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            TimerHandle_t x_आन्तरिकम्_Timer_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) xTimer;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Timer_Handle = MPU_Get_Timer_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Timer_Handle != रिक्त )
                {
                    xReturn = xTimerGenericCommandFromTask( x_आन्तरिकम्_Timer_Handle,
                                                            tmrCOMMAND_DELETE,
                                                            0U, /* xOptionalValue */
                                                            रिक्त, /* pxHigherPriorityTaskWoken */
                                                            x_Ticks_गन्तव्यम्_Wait );
                    यदि( xReturn != pdFALSE )
                    {
                        MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* if ( configUSE_TIMERS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for event group APIs.              */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Wait_द्वयङ्काः( Event_गणः_Handle_t x_Event_गणः,
                                             ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Wait_For,
                                             ध्रुव आधारः_Type_t xClearOnExit,
                                             ध्रुव आधारः_Type_t x_Wait_For_All_द्वयङ्काः,
                                             TickType_t x_Ticks_गन्तव्यम्_Wait ) /* FREERTOS_SYSTEM_CALL */
        {
            Event_द्वयङ्काः_t xReturn = 0;
            x_Event_गणः_Wait_द्वयङ्काः_Params_t xParams;

            xParams.x_Event_गणः = x_Event_गणः;
            xParams.ux_द्वयङ्काः_गन्तव्यम्_Wait_For = ux_द्वयङ्काः_गन्तव्यम्_Wait_For;
            xParams.xClearOnExit = xClearOnExit;
            xParams.x_Wait_For_All_द्वयङ्काः = x_Wait_For_All_द्वयङ्काः;
            xParams.x_Ticks_गन्तव्यम्_Wait = x_Ticks_गन्तव्यम्_Wait;

            xReturn = MPU_x_Event_गणः_Wait_द्वयङ्काः_प्रविष्टिः( &( xParams ) );

            प्रत्यागम xReturn;
        }

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Wait_द्वयङ्काः_Impl( ध्रुव x_Event_गणः_Wait_द्वयङ्काः_Params_t * pxParams ) PRIVILEGED_FUNCTION;

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Wait_द्वयङ्काः_Impl( ध्रुव x_Event_गणः_Wait_द्वयङ्काः_Params_t * pxParams ) /* PRIVILEGED_FUNCTION */
        {
            Event_द्वयङ्काः_t xReturn = 0;
            Event_गणः_Handle_t x_आन्तरिकम्_Event_गणः_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः = pdFALSE;
            आधारः_Type_t xAreParamsReadable = pdFALSE;

            यदि( pxParams != रिक्त )
            {
                xAreParamsReadable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( pxParams,
                                                                      परिमाण( x_Event_गणः_Wait_द्वयङ्काः_Params_t ),
                                                                      tskMPU_READ_PERMISSION );
            }

            यदि( xAreParamsReadable == pdTRUE )
            {
                यदि( ( ( pxParams->ux_द्वयङ्काः_गन्तव्यम्_Wait_For & event_EVENT_द्वयङ्काः_CONTROL_अष्टकानि ) == 0U ) &&
                    ( pxParams->ux_द्वयङ्काः_गन्तव्यम्_Wait_For != 0U )
                    #यदि ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                        && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( pxParams->x_Ticks_गन्तव्यम्_Wait != 0U ) ) )
                    #यदि_अन्तः
                    )
                {
                    l_सूचकांक = ( int32_t ) ( pxParams->x_Event_गणः );

                    यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः == pdTRUE )
                        {
                            x_आन्तरिकम्_Event_गणः_Handle = MPU_Get_Event_गणः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                            यदि( x_आन्तरिकम्_Event_गणः_Handle != रिक्त )
                            {
                                xReturn = x_Event_गणः_Wait_द्वयङ्काः( x_आन्तरिकम्_Event_गणः_Handle,
                                                               pxParams->ux_द्वयङ्काः_गन्तव्यम्_Wait_For,
                                                               pxParams->xClearOnExit,
                                                               pxParams->x_Wait_For_All_द्वयङ्काः,
                                                               pxParams->x_Ticks_गन्तव्यम्_Wait );
                            }
                        }
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Clear_द्वयङ्काः_Impl( Event_गणः_Handle_t x_Event_गणः,
                                                  ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Clear ) PRIVILEGED_FUNCTION;

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Clear_द्वयङ्काः_Impl( Event_गणः_Handle_t x_Event_गणः,
                                                  ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Clear ) /* PRIVILEGED_FUNCTION */
        {
            Event_द्वयङ्काः_t xReturn = 0;
            Event_गणः_Handle_t x_आन्तरिकम्_Event_गणः_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः = pdFALSE;

            यदि( ( ux_द्वयङ्काः_गन्तव्यम्_Clear & event_EVENT_द्वयङ्काः_CONTROL_अष्टकानि ) == 0U )
            {
                l_सूचकांक = ( int32_t ) x_Event_गणः;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः == pdTRUE )
                    {
                        x_आन्तरिकम्_Event_गणः_Handle = MPU_Get_Event_गणः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_आन्तरिकम्_Event_गणः_Handle != रिक्त )
                        {
                            xReturn = x_Event_गणः_Clear_द्वयङ्काः( x_आन्तरिकम्_Event_गणः_Handle, ux_द्वयङ्काः_गन्तव्यम्_Clear );
                        }
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )

        Event_द्वयङ्काः_t MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः_Impl( Event_गणः_Handle_t x_Event_गणः,
                                                ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः ) PRIVILEGED_FUNCTION;

        Event_द्वयङ्काः_t MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः_Impl( Event_गणः_Handle_t x_Event_गणः,
                                                ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः ) /* PRIVILEGED_FUNCTION */
        {
            Event_द्वयङ्काः_t xReturn = 0;
            Event_गणः_Handle_t x_आन्तरिकम्_Event_गणः_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः = pdFALSE;

            यदि( ( ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः & event_EVENT_द्वयङ्काः_CONTROL_अष्टकानि ) == 0U )
            {
                l_सूचकांक = ( int32_t ) x_Event_गणः;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः == pdTRUE )
                    {
                        x_आन्तरिकम्_Event_गणः_Handle = MPU_Get_Event_गणः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_आन्तरिकम्_Event_गणः_Handle != रिक्त )
                        {
                            xReturn = x_Event_गणः_समुच्चयः_द्वयङ्काः( x_आन्तरिकम्_Event_गणः_Handle, ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः );
                        }
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Sync_Impl( Event_गणः_Handle_t x_Event_गणः,
                                             ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः,
                                             ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Wait_For,
                                             TickType_t x_Ticks_गन्तव्यम्_Wait ) PRIVILEGED_FUNCTION;

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Sync_Impl( Event_गणः_Handle_t x_Event_गणः,
                                             ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः,
                                             ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Wait_For,
                                             TickType_t x_Ticks_गन्तव्यम्_Wait ) /* PRIVILEGED_FUNCTION */
        {
            Event_द्वयङ्काः_t xReturn = 0;
            Event_गणः_Handle_t x_आन्तरिकम्_Event_गणः_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः = pdFALSE;

            यदि( ( ( ux_द्वयङ्काः_गन्तव्यम्_Wait_For & event_EVENT_द्वयङ्काः_CONTROL_अष्टकानि ) == 0U ) &&
                ( ux_द्वयङ्काः_गन्तव्यम्_Wait_For != 0U )
                #यदि ( ( INCLUDE_xTaskGetSchedulerState == 1 ) || ( configUSE_TIMERS == 1 ) )
                    && ( !( ( xTaskGetSchedulerState() == taskSCHEDULER_SUSPENDED ) && ( x_Ticks_गन्तव्यम्_Wait != 0U ) ) )
                #यदि_अन्तः
                )
            {
                l_सूचकांक = ( int32_t ) x_Event_गणः;

                यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                {
                    x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः == pdTRUE )
                    {
                        x_आन्तरिकम्_Event_गणः_Handle = MPU_Get_Event_गणः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_आन्तरिकम्_Event_गणः_Handle != रिक्त )
                        {
                            xReturn = x_Event_गणः_Sync( x_आन्तरिकम्_Event_गणः_Handle, ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः, ux_द्वयङ्काः_गन्तव्यम्_Wait_For, x_Ticks_गन्तव्यम्_Wait );
                        }
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        UBaseType_t MPU_ux_Event_गणः_Get_सङ्ख्या_Impl( शून्य * x_Event_गणः ) PRIVILEGED_FUNCTION;

        UBaseType_t MPU_ux_Event_गणः_Get_सङ्ख्या_Impl( शून्य * x_Event_गणः ) /* PRIVILEGED_FUNCTION */
        {
            UBaseType_t xReturn = 0;
            Event_गणः_Handle_t x_आन्तरिकम्_Event_गणः_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः = pdFALSE;

            l_सूचकांक = ( int32_t ) x_Event_गणः;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः == pdTRUE )
                {
                    x_आन्तरिकम्_Event_गणः_Handle = MPU_Get_Event_गणः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Event_गणः_Handle != रिक्त )
                    {
                        xReturn = ux_Event_गणः_Get_सङ्ख्या( x_आन्तरिकम्_Event_गणः_Handle );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) )

        शून्य MPU_v_Event_गणः_समुच्चयः_सङ्ख्या_Impl( शून्य * x_Event_गणः,
                                           UBaseType_t ux_Event_गणः_सङ्ख्या ) PRIVILEGED_FUNCTION;

        शून्य MPU_v_Event_गणः_समुच्चयः_सङ्ख्या_Impl( शून्य * x_Event_गणः,
                                           UBaseType_t ux_Event_गणः_सङ्ख्या ) /* PRIVILEGED_FUNCTION */
        {
            Event_गणः_Handle_t x_आन्तरिकम्_Event_गणः_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः = pdFALSE;

            l_सूचकांक = ( int32_t ) x_Event_गणः;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_Event_गणः == pdTRUE )
                {
                    x_आन्तरिकम्_Event_गणः_Handle = MPU_Get_Event_गणः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_Event_गणः_Handle != रिक्त )
                    {
                        v_Event_गणः_समुच्चयः_सङ्ख्या( x_आन्तरिकम्_Event_गणः_Handle, ux_Event_गणः_सङ्ख्या );
                    }
                }
            }
        }

    #यदि_अन्तः /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( configUSE_TRACE_FACILITY == 1 ) ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Event Group APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #यदि ( ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_गणः_Handle_t MPU_x_Event_गणः_Create( शून्य ) /* PRIVILEGED_FUNCTION */
        {
            Event_गणः_Handle_t x_आन्तरिकम्_Event_गणः_Handle = रिक्त;
            Event_गणः_Handle_t x_External_Event_गणः_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                x_आन्तरिकम्_Event_गणः_Handle = x_Event_गणः_Create();

                यदि( x_आन्तरिकम्_Event_गणः_Handle != रिक्त )
                {
                    MPU_Store_Event_गणः_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Event_गणः_Handle );
                    x_External_Event_गणः_Handle = ( Event_गणः_Handle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम x_External_Event_गणः_Handle;
        }

    #यदि_अन्तः /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_SUPPORT_STATIC_आवण्टनम् == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        Event_गणः_Handle_t MPU_x_Event_गणः_Create_Static( Static_Event_गणः_t * px_Event_गणः_बफर ) /* PRIVILEGED_FUNCTION */
        {
            Event_गणः_Handle_t x_आन्तरिकम्_Event_गणः_Handle = रिक्त;
            Event_गणः_Handle_t x_External_Event_गणः_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

            यदि( l_सूचकांक != -1 )
            {
                x_आन्तरिकम्_Event_गणः_Handle = x_Event_गणः_Create_Static( px_Event_गणः_बफर );

                यदि( x_आन्तरिकम्_Event_गणः_Handle != रिक्त )
                {
                    MPU_Store_Event_गणः_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_Event_गणः_Handle );
                    x_External_Event_गणः_Handle = ( Event_गणः_Handle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                }
                अन्यथा
                {
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                }
            }

            प्रत्यागम x_External_Event_गणः_Handle;
        }

    #यदि_अन्तः /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )

        शून्य MPU_v_Event_गणः_Delete( Event_गणः_Handle_t x_Event_गणः ) /* PRIVILEGED_FUNCTION */
        {
            Event_गणः_Handle_t x_आन्तरिकम्_Event_गणः_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_Event_गणः;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Event_गणः_Handle = MPU_Get_Event_गणः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Event_गणः_Handle != रिक्त )
                {
                    v_Event_गणः_Delete( x_आन्तरिकम्_Event_गणः_Handle );
                    MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );
                }
            }
        }

    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_SUPPORT_STATIC_आवण्टनम् == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) )

        आधारः_Type_t MPU_x_Event_गणः_Get_Static_बफर( Event_गणः_Handle_t x_Event_गणः,
                                                   Static_Event_गणः_t ** ppx_Event_गणः_बफर ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            Event_गणः_Handle_t x_आन्तरिकम्_Event_गणः_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_Event_गणः;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Event_गणः_Handle = MPU_Get_Event_गणः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Event_गणः_Handle != रिक्त )
                {
                    xReturn = x_Event_गणः_Get_Static_बफर( x_आन्तरिकम्_Event_गणः_Handle, ppx_Event_गणः_बफर );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_EVENT_GROUPS == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        आधारः_Type_t MPU_x_Event_गणः_Clear_द्वयङ्काः_From_ISR( Event_गणः_Handle_t x_Event_गणः,
                                                    ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_Clear ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            Event_गणः_Handle_t x_आन्तरिकम्_Event_गणः_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_Event_गणः;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Event_गणः_Handle = MPU_Get_Event_गणः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Event_गणः_Handle != रिक्त )
                {
                    xReturn = x_Event_गणः_Clear_द्वयङ्काः_From_ISR( x_आन्तरिकम्_Event_गणः_Handle, ux_द्वयङ्काः_गन्तव्यम्_Clear );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) )

        आधारः_Type_t MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः_From_ISR( Event_गणः_Handle_t x_Event_गणः,
                                                  ध्रुव Event_द्वयङ्काः_t ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः,
                                                  आधारः_Type_t * px_Higher_प्राथमिकता_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            Event_गणः_Handle_t x_आन्तरिकम्_Event_गणः_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_Event_गणः;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Event_गणः_Handle = MPU_Get_Event_गणः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Event_गणः_Handle != रिक्त )
                {
                    xReturn = x_Event_गणः_समुच्चयः_द्वयङ्काः_From_ISR( x_आन्तरिकम्_Event_गणः_Handle, ux_द्वयङ्काः_गन्तव्यम्_समुच्चयः, px_Higher_प्राथमिकता_Task_Woken );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( ( configUSE_EVENT_GROUPS == 1 ) && ( INCLUDE_xTimerPendFunctionCall == 1 ) && ( configUSE_TIMERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( configUSE_EVENT_GROUPS == 1 )

        Event_द्वयङ्काः_t MPU_x_Event_गणः_Get_द्वयङ्काः_From_ISR( Event_गणः_Handle_t x_Event_गणः ) /* PRIVILEGED_FUNCTION */
        {
            Event_द्वयङ्काः_t xReturn = 0;
            Event_गणः_Handle_t x_आन्तरिकम्_Event_गणः_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_Event_गणः;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_Event_गणः_Handle = MPU_Get_Event_गणः_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_Event_गणः_Handle != रिक्त )
                {
                    xReturn = x_Event_गणः_Get_द्वयङ्काः_From_ISR( x_आन्तरिकम्_Event_गणः_Handle );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_EVENT_GROUPS == 1 ) */
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*           MPU wrappers for stream buffer APIs.            */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        size_t MPU_x_प्रवाहः_बफर_Send_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                          ध्रुव शून्य * pv_Tx_दत्त,
                                          size_t x_दत्त_दीर्घता_अष्टकानि,
                                          TickType_t x_Ticks_गन्तव्यम्_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_प्रवाहः_बफर_Send_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                          ध्रुव शून्य * pv_Tx_दत्त,
                                          size_t x_दत्त_दीर्घता_अष्टकानि,
                                          TickType_t x_Ticks_गन्तव्यम्_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Is_Tx_दत्त_बफर_Readable = pdFALSE;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = pdFALSE;

            यदि( pv_Tx_दत्त != रिक्त )
            {
                x_Is_Tx_दत्त_बफर_Readable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( pv_Tx_दत्त,
                                                                           x_दत्त_दीर्घता_अष्टकानि,
                                                                           tskMPU_READ_PERMISSION );

                यदि( x_Is_Tx_दत्त_बफर_Readable == pdTRUE )
                {
                    l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

                    यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर == pdTRUE )
                        {
                            x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                            यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                            {
                                xReturn = x_प्रवाहः_बफर_Send( x_आन्तरिकम्_प्रवाहः_बफर_Handle, pv_Tx_दत्त, x_दत्त_दीर्घता_अष्टकानि, x_Ticks_गन्तव्यम्_Wait );
                            }
                        }
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        size_t MPU_x_प्रवाहः_बफर_Receive_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                             शून्य * pv_Rx_दत्त,
                                             size_t x_बफर_दीर्घता_अष्टकानि,
                                             TickType_t x_Ticks_गन्तव्यम्_Wait ) PRIVILEGED_FUNCTION;

        size_t MPU_x_प्रवाहः_बफर_Receive_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                             शून्य * pv_Rx_दत्त,
                                             size_t x_बफर_दीर्घता_अष्टकानि,
                                             TickType_t x_Ticks_गन्तव्यम्_Wait ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Is_Rx_दत्त_बफर_Writeable = pdFALSE;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = pdFALSE;

            यदि( pv_Rx_दत्त != रिक्त )
            {
                x_Is_Rx_दत्त_बफर_Writeable = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_बफर( pv_Rx_दत्त,
                                                                            x_बफर_दीर्घता_अष्टकानि,
                                                                            tskMPU_WRITE_PERMISSION );

                यदि( x_Is_Rx_दत्त_बफर_Writeable == pdTRUE )
                {
                    l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

                    यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
                    {
                        x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                        यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर == pdTRUE )
                        {
                            x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                            यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                            {
                                xReturn = x_प्रवाहः_बफर_Receive( x_आन्तरिकम्_प्रवाहः_बफर_Handle, pv_Rx_दत्त, x_बफर_दीर्घता_अष्टकानि, x_Ticks_गन्तव्यम्_Wait );
                            }
                        }
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_पूर्णम्_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_पूर्णम्_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = pdFALSE;

            l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर == pdTRUE )
                {
                    x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                    {
                        xReturn = x_प्रवाहः_बफर_Is_पूर्णम्( x_आन्तरिकम्_प्रवाहः_बफर_Handle );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_रिक्तानि_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Is_रिक्तानि_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = pdFALSE;

            l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर == pdTRUE )
                {
                    x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                    {
                        xReturn = x_प्रवाहः_बफर_Is_रिक्तानि( x_आन्तरिकम्_प्रवाहः_बफर_Handle );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        size_t MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) PRIVILEGED_FUNCTION;

        size_t MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = pdFALSE;

            l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर == pdTRUE )
                {
                    x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                    {
                        xReturn = x_प्रवाहः_बफर_Spaces_उपलब्धम्( x_आन्तरिकम्_प्रवाहः_बफर_Handle );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        size_t MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) PRIVILEGED_FUNCTION;

        size_t MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = pdFALSE;

            l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर == pdTRUE )
                {
                    x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                    {
                        xReturn = x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्( x_आन्तरिकम्_प्रवाहः_बफर_Handle );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        आधारः_Type_t MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                                         size_t xTriggerLevel ) PRIVILEGED_FUNCTION;

        आधारः_Type_t MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                                         size_t xTriggerLevel ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = pdFALSE;

            l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर == pdTRUE )
                {
                    x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                    {
                        xReturn = x_प्रवाहः_बफर_समुच्चयः_Trigger_Level( x_आन्तरिकम्_प्रवाहः_बफर_Handle, xTriggerLevel );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        size_t MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) PRIVILEGED_FUNCTION;

        size_t MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि_Impl( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* PRIVILEGED_FUNCTION */
        {
            size_t xReturn = 0;
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;
            आधारः_Type_t x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = pdFALSE;

            l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर = x_पत्तनम्_Is_Authorized_गन्तव्यम्_Access_Kernel_Object( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_Calling_Task_Is_Authorized_गन्तव्यम्_Access_प्रवाहः_बफर == pdTRUE )
                {
                    x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                    यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                    {
                        xReturn = x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि( x_आन्तरिकम्_प्रवाहः_बफर_Handle );
                    }
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

/* Privileged only wrappers for Stream Buffer APIs. These are needed so that
 * the application can use opaque handles maintained in mpu_wrappers.c
 * with all the APIs. */
/*-----------------------------------------------------------*/

    #यदि ( ( config_SUPPORT_DYNAMIC_आवण्टनम् == 1 ) && ( config_USE_प्रवाहः_BUFFERS == 1 ) )

        प्रवाहः_बफर_Handle_t MPU_x_प्रवाहः_बफर_Generic_Create( size_t x_बफर_आकार_अष्टकानि,
                                                             size_t x_Trigger_Level_अष्टकानि,
                                                             आधारः_Type_t x_प्रवाहः_बफर_Type,
                                                             प्रवाहः_बफर_Callback_Function_t pxSendCompletedCallback,
                                                             प्रवाहः_बफर_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            प्रवाहः_बफर_Handle_t x_External_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == रिक्त ) &&
                          ( pxReceiveCompletedCallback == रिक्त ) );

            यदि( ( pxSendCompletedCallback == रिक्त ) &&
                ( pxReceiveCompletedCallback == रिक्त ) )
            {
                l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

                यदि( l_सूचकांक != -1 )
                {
                    x_आन्तरिकम्_प्रवाहः_बफर_Handle = x_प्रवाहः_बफर_Generic_Create( x_बफर_आकार_अष्टकानि,
                                                                              x_Trigger_Level_अष्टकानि,
                                                                              x_प्रवाहः_बफर_Type,
                                                                              रिक्त,
                                                                              रिक्त );

                    यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                    {
                        MPU_Store_प्रवाहः_बफर_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_प्रवाहः_बफर_Handle );
                        x_External_प्रवाहः_बफर_Handle = ( प्रवाहः_बफर_Handle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                    }
                    अन्यथा
                    {
                        MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                    }
                }
            }
            अन्यथा
            {
                trace_प्रवाहः_बफर_CREATE_FAILED( x_प्रवाहः_बफर_Type );
                x_External_प्रवाहः_बफर_Handle = रिक्त;
            }

            प्रत्यागम x_External_प्रवाहः_बफर_Handle;
        }

    #यदि_अन्तः /* #if ( ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_SUPPORT_STATIC_आवण्टनम् == 1 ) && ( config_USE_प्रवाहः_BUFFERS == 1 ) )

        प्रवाहः_बफर_Handle_t MPU_x_प्रवाहः_बफर_Generic_Create_Static( size_t x_बफर_आकार_अष्टकानि,
                                                                   size_t x_Trigger_Level_अष्टकानि,
                                                                   आधारः_Type_t x_प्रवाहः_बफर_Type,
                                                                   uint8_t * ध्रुव puc_प्रवाहः_बफर_Storage_Area,
                                                                   Static_प्रवाहः_बफर_t * ध्रुव px_Static_प्रवाहः_बफर,
                                                                   प्रवाहः_बफर_Callback_Function_t pxSendCompletedCallback,
                                                                   प्रवाहः_बफर_Callback_Function_t pxReceiveCompletedCallback ) /* PRIVILEGED_FUNCTION */
        {
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            प्रवाहः_बफर_Handle_t x_External_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;

            /**
             * Stream buffer application level callback functionality is disabled for MPU
             * enabled ports.
             */
            configASSERT( ( pxSendCompletedCallback == रिक्त ) &&
                          ( pxReceiveCompletedCallback == रिक्त ) );

            यदि( ( pxSendCompletedCallback == रिक्त ) &&
                ( pxReceiveCompletedCallback == रिक्त ) )
            {
                l_सूचकांक = MPU_Get_Free_सूचकांक_अन्तर्_Kernel_Object_Pool();

                यदि( l_सूचकांक != -1 )
                {
                    x_आन्तरिकम्_प्रवाहः_बफर_Handle = x_प्रवाहः_बफर_Generic_Create_Static( x_बफर_आकार_अष्टकानि,
                                                                                    x_Trigger_Level_अष्टकानि,
                                                                                    x_प्रवाहः_बफर_Type,
                                                                                    puc_प्रवाहः_बफर_Storage_Area,
                                                                                    px_Static_प्रवाहः_बफर,
                                                                                    रिक्त,
                                                                                    रिक्त );

                    यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                    {
                        MPU_Store_प्रवाहः_बफर_Handle_At_सूचकांक( l_सूचकांक, x_आन्तरिकम्_प्रवाहः_बफर_Handle );
                        x_External_प्रवाहः_बफर_Handle = ( प्रवाहः_बफर_Handle_t ) CONVERT_गन्तव्यम्_EXTERNAL_सूचकांक( l_सूचकांक );
                    }
                    अन्यथा
                    {
                        MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( l_सूचकांक );
                    }
                }
            }
            अन्यथा
            {
                trace_प्रवाहः_बफर_CREATE_STATIC_FAILED( xReturn, x_प्रवाहः_बफर_Type );
                x_External_प्रवाहः_बफर_Handle = रिक्त;
            }

            प्रत्यागम x_External_प्रवाहः_बफर_Handle;
        }

    #यदि_अन्तः /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        शून्य MPU_v_प्रवाहः_बफर_Delete( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* PRIVILEGED_FUNCTION */
        {
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                {
                    v_प्रवाहः_बफर_Delete( x_आन्तरिकम्_प्रवाहः_बफर_Handle );
                }

                MPU_समुच्चयः_सूचकांक_Free_अन्तर्_Kernel_Object_Pool( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );
            }
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Reset( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                {
                    xReturn = x_प्रवाहः_बफर_Reset( x_आन्तरिकम्_प्रवाहः_बफर_Handle );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( ( config_SUPPORT_STATIC_आवण्टनम् == 1 ) && ( config_USE_प्रवाहः_BUFFERS == 1 ) )

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Get_Static_Buffers( प्रवाहः_बफर_Handle_t x_प्रवाहः_Buffers,
                                                      uint8_t * ppuc_प्रवाहः_बफर_Storage_Area,
                                                      Static_प्रवाहः_बफर_t * ppx_Static_प्रवाहः_बफर ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_प्रवाहः_Buffers;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                {
                    xReturn = MPU_x_प्रवाहः_बफर_Get_Static_Buffers( x_आन्तरिकम्_प्रवाहः_बफर_Handle, ppuc_प्रवाहः_बफर_Storage_Area, ppx_Static_प्रवाहः_बफर );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configUSE_STREAM_BUFFERS == 1 ) ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

    size_t MPU_x_प्रवाहः_बफर_Send_From_ISR( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                         ध्रुव शून्य * pv_Tx_दत्त,
                                         size_t x_दत्त_दीर्घता_अष्टकानि,
                                         आधारः_Type_t * ध्रुव px_Higher_प्राथमिकता_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
        int32_t l_सूचकांक;

        l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
            {
                xReturn = x_प्रवाहः_बफर_Send_From_ISR( x_आन्तरिकम्_प्रवाहः_बफर_Handle, pv_Tx_दत्त, x_दत्त_दीर्घता_अष्टकानि, px_Higher_प्राथमिकता_Task_Woken );
            }
        }

        प्रत्यागम xReturn;
    }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

    size_t MPU_x_प्रवाहः_बफर_Receive_From_ISR( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                            शून्य * pv_Rx_दत्त,
                                            size_t x_बफर_दीर्घता_अष्टकानि,
                                            आधारः_Type_t * ध्रुव px_Higher_प्राथमिकता_Task_Woken ) /* PRIVILEGED_FUNCTION */
    {
        size_t xReturn = 0;
        प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
        int32_t l_सूचकांक;

        l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

        यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
        {
            x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

            यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
            {
                xReturn = x_प्रवाहः_बफर_Receive_From_ISR( x_आन्तरिकम्_प्रवाहः_बफर_Handle, pv_Rx_दत्त, x_बफर_दीर्घता_अष्टकानि, px_Higher_प्राथमिकता_Task_Woken );
            }
        }

        प्रत्यागम xReturn;
    }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Send_Completed_From_ISR( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                                          आधारः_Type_t * px_Higher_प्राथमिकता_Task_Woken ) /* PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                {
                    xReturn = x_प्रवाहः_बफर_Send_Completed_From_ISR( x_आन्तरिकम्_प्रवाहः_बफर_Handle, px_Higher_प्राथमिकता_Task_Woken );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */
/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Receive_Completed_From_ISR( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर,
                                                             आधारः_Type_t * px_Higher_प्राथमिकता_Task_Woken ) /*PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFALSE;
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                {
                    xReturn = x_प्रवाहः_बफर_Receive_Completed_From_ISR( x_आन्तरिकम्_प्रवाहः_बफर_Handle, px_Higher_प्राथमिकता_Task_Woken );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

    #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )

        आधारः_Type_t MPU_x_प्रवाहः_बफर_Reset_From_ISR( प्रवाहः_बफर_Handle_t x_प्रवाहः_बफर ) /*PRIVILEGED_FUNCTION */
        {
            आधारः_Type_t xReturn = pdFAIL;
            प्रवाहः_बफर_Handle_t x_आन्तरिकम्_प्रवाहः_बफर_Handle = रिक्त;
            int32_t l_सूचकांक;

            l_सूचकांक = ( int32_t ) x_प्रवाहः_बफर;

            यदि( IS_EXTERNAL_सूचकांक_VALID( l_सूचकांक ) != pdFALSE )
            {
                x_आन्तरिकम्_प्रवाहः_बफर_Handle = MPU_Get_प्रवाहः_बफर_Handle_At_सूचकांक( CONVERT_गन्तव्यम्_आन्तरिकम्_सूचकांक( l_सूचकांक ) );

                यदि( x_आन्तरिकम्_प्रवाहः_बफर_Handle != रिक्त )
                {
                    xReturn = x_प्रवाहः_बफर_Reset_From_ISR( x_आन्तरिकम्_प्रवाहः_बफर_Handle );
                }
            }

            प्रत्यागम xReturn;
        }

    #यदि_अन्तः /* #if ( configUSE_STREAM_BUFFERS == 1 ) */

/*-----------------------------------------------------------*/

/* Functions that the application writer wants to execute in privileged mode
 * can be defined in application_defined_privileged_functions.h. */

    #यदि configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS == 1
        #अन्तर्भाव "application_defined_privileged_functions.h"
    #यदि_अन्तः
/*-----------------------------------------------------------*/

/**
 * @brief Array of system call implementation functions.
 *
 * The index in the array MUST match the corresponding system call number
 * defined in mpu_wrappers.h.
 */
    PRIVILEGED_दत्त UBaseType_t uxSystemCallImplementations[ अङ्कः_SYSTEM_CALLS ] =
    {
        #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_xTaskGenericNotifyImpl,                     /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyWaitImpl,                 /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotify. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyWait. */
        #यदि_अन्तः

        #यदि ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_xTimerGenericCommandFromTaskImpl,           /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTimerGenericCommandFromTask. */
        #यदि_अन्तः

        #यदि ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_गणः_Wait_द्वयङ्काः_Impl,                    /* SYSTEM_CALL_xEventGroupWaitBits. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupWaitBits. */
        #यदि_अन्तः

        /* The system calls above this line take 5 parameters. */

        #यदि ( INCLUDE_xTaskDelayUntil == 1 )
            ( UBaseType_t ) MPU_xTaskDelayUntilImpl,                        /* SYSTEM_CALL_xTaskDelayUntil. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskDelayUntil. */
        #यदि_अन्तः

        #यदि ( INCLUDE_xTaskAbortDelay == 1 )
            ( UBaseType_t ) MPU_xTaskAbortDelayImpl,                        /* SYSTEM_CALL_xTaskAbortDelay. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskAbortDelay. */
        #यदि_अन्तः

        #यदि ( INCLUDE_vTaskDelay == 1 )
            ( UBaseType_t ) MPU_vTaskDelayImpl,                             /* SYSTEM_CALL_vTaskDelay. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskDelay. */
        #यदि_अन्तः

        #यदि ( INCLUDE_ux_Task_प्राथमिकता_Get == 1 )
            ( UBaseType_t ) MPU_ux_Task_प्राथमिकता_Get_Impl,                      /* SYSTEM_CALL_uxTaskPriorityGet. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskPriorityGet. */
        #यदि_अन्तः

        #यदि ( INCLUDE_eTaskGetState == 1 )
            ( UBaseType_t ) MPU_eTaskGetStateImpl,                          /* SYSTEM_CALL_eTaskGetState. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_eTaskGetState. */
        #यदि_अन्तः

        #यदि ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_vTaskGetInfoImpl,                           /* SYSTEM_CALL_vTaskGetInfo. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskGetInfo. */
        #यदि_अन्तः

        #यदि ( INCLUDE_xTaskGetIdleTaskHandle == 1 )
            ( UBaseType_t ) MPU_xTaskGetIdleTaskHandleImpl,                 /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetIdleTaskHandle. */
        #यदि_अन्तः

        #यदि ( INCLUDE_vTaskSuspend == 1 )
            ( UBaseType_t ) MPU_vTaskSuspendImpl,                           /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) MPU_vTaskResumeImpl,                            /* SYSTEM_CALL_vTaskResume. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSuspend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskResume. */
        #यदि_अन्तः

        ( UBaseType_t ) MPU_x_Task_Get_Tick_गणनम्_Impl,                          /* SYSTEM_CALL_xTaskGetTickCount. */
        ( UBaseType_t ) MPU_ux_Task_Get_सङ्ख्या_सम्बन्धि_Tasks_Impl,                     /* SYSTEM_CALL_uxTaskGetNumberOfTasks. */

        #यदि ( config_GENERATE_सततम्_TIME_STATS == 1 )
            ( UBaseType_t ) MPU_ul_Task_Get_सततम्_Time_गणक_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) MPU_ul_Task_Get_सततम्_Time_Percent_Impl,                /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimeCounter. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetRunTimePercent. */
        #यदि_अन्तः

        #यदि ( ( config_GENERATE_सततम्_TIME_STATS == 1 ) && ( INCLUDE_xTaskGetIdleTaskHandle == 1 ) )
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_सततम्_Time_Percent_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) MPU_ul_Task_Get_Idle_सततम्_Time_गणक_Impl,            /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimePercent. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGetIdleRunTimeCounter. */
        #यदि_अन्तः

        #यदि ( config_USE_APPLICATION_TASK_चिह्नकम् == 1 )
            ( UBaseType_t ) MPU_v_Task_समुच्चयः_Application_Task_चिह्नकम्_Impl,             /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) MPU_x_Task_Get_Application_Task_चिह्नकम्_Impl,             /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetApplicationTaskTag. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetApplicationTaskTag. */
        #यदि_अन्तः

        #यदि ( config_अङ्कः_THREAD_LOCAL_STORAGE_सूचकाः != 0 )
            ( UBaseType_t ) MPU_v_Task_समुच्चयः_Thread_Local_Storage_Pointer_Impl,      /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) MPU_pvTaskGetThreadLocalStoragePointerImpl,     /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vTaskSetThreadLocalStoragePointer. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pvTaskGetThreadLocalStoragePointer. */
        #यदि_अन्तः

        #यदि ( configUSE_TRACE_FACILITY == 1 )
            ( UBaseType_t ) MPU_uxTaskGetSystemStateImpl,                   /* SYSTEM_CALL_uxTaskGetSystemState. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetSystemState. */
        #यदि_अन्तः

        #यदि ( INCLUDE_ux_Task_Get_राशिः_उच्चः_Water_Mark == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark_Impl,            /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark. */
        #यदि_अन्तः

        #यदि ( INCLUDE_ux_Task_Get_राशिः_उच्चः_Water_Mark2 == 1 )
            ( UBaseType_t ) MPU_ux_Task_Get_राशिः_उच्चः_Water_Mark2_Impl,           /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxTaskGetStackHighWaterMark2. */
        #यदि_अन्तः

        #यदि ( ( INCLUDE_xTaskGetCurrentTaskHandle == 1 ) || ( configUSE_MUTEXES == 1 ) )
            ( UBaseType_t ) MPU_xTaskGetCurrentTaskHandleImpl,              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetCurrentTaskHandle. */
        #यदि_अन्तः

        #यदि ( INCLUDE_xTaskGetSchedulerState == 1 )
            ( UBaseType_t ) MPU_xTaskGetSchedulerStateImpl,                 /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGetSchedulerState. */
        #यदि_अन्तः

        ( UBaseType_t ) MPU_v_Task_समुच्चयः_Time_बहिर्गमनम्_State_Impl,                       /* SYSTEM_CALL_vTaskSetTimeOutState. */
        ( UBaseType_t ) MPU_x_Task_Check_For_Time_बहिर्गमनम्_Impl,                       /* SYSTEM_CALL_xTaskCheckForTimeOut. */

        #यदि ( configUSE_TASK_NOTIFICATIONS == 1 )
            ( UBaseType_t ) MPU_ulTaskGenericNotifyTakeImpl,                /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) MPU_xTaskGenericNotifyStateClearImpl,           /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) MPU_ul_Task_Generic_Notify_मानम्_Clear_Impl,          /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyTake. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xTaskGenericNotifyStateClear. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_ulTaskGenericNotifyValueClear. */
        #यदि_अन्तः

        ( UBaseType_t ) MPU_xQueueGenericSendImpl,                          /* SYSTEM_CALL_xQueueGenericSend. */
        ( UBaseType_t ) MPU_ux_Queue_Messages_प्रतीक्षा_Impl,                     /* SYSTEM_CALL_uxQueueMessagesWaiting. */
        ( UBaseType_t ) MPU_ux_Queue_Spaces_उपलब्धम्_Impl,                     /* SYSTEM_CALL_uxQueueSpacesAvailable. */
        ( UBaseType_t ) MPU_xQueueReceiveImpl,                              /* SYSTEM_CALL_xQueueReceive. */
        ( UBaseType_t ) MPU_xQueuePeekImpl,                                 /* SYSTEM_CALL_xQueuePeek. */
        ( UBaseType_t ) MPU_xQueueSemaphoreTakeImpl,                        /* SYSTEM_CALL_xQueueSemaphoreTake. */

        #यदि ( ( configUSE_MUTEXES == 1 ) && ( INCLUDE_xSemaphoreGetMutexHolder == 1 ) )
            ( UBaseType_t ) MPU_xQueueGetMutexHolderImpl,                   /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGetMutexHolder. */
        #यदि_अन्तः

        #यदि ( configUSE_RECURSIVE_MUTEXES == 1 )
            ( UBaseType_t ) MPU_xQueueTakeMutexRecursiveImpl,               /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) MPU_xQueueGiveMutexRecursiveImpl,               /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueTakeMutexRecursive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueGiveMutexRecursive. */
        #यदि_अन्तः

        #यदि ( configUSE_QUEUE_SETS == 1 )
            ( UBaseType_t ) MPU_x_Queue_Select_From_समुच्चयः_Impl,                    /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) MPU_x_Queue_सङ्कलय_गन्तव्यम्_समुच्चयः_Impl,                         /* SYSTEM_CALL_xQueueAddToSet. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueSelectFromSet. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xQueueAddToSet. */
        #यदि_अन्तः

        #यदि config_QUEUE_REGISTRY_आकार > 0
            ( UBaseType_t ) MPU_v_Queue_सङ्कलय_गन्तव्यम्_Registry_Impl,                    /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) MPU_vQueueUnregisterQueueImpl,                  /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) MPU_pcQueueGetNameImpl,                         /* SYSTEM_CALL_pcQueueGetName. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueAddToRegistry. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vQueueUnregisterQueue. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_pcQueueGetName. */
        #यदि_अन्तः

        #यदि ( configUSE_TIMERS == 1 )
            ( UBaseType_t ) MPU_pvTimerGetTimerIDImpl,                      /* SYSTEM_CALL_pvTimerGetTimerID. */
            ( UBaseType_t ) MPU_v_Timer_समुच्चयः_Timer_IDImpl,                       /* SYSTEM_CALL_vTimerSetTimerID. */
            ( UBaseType_t ) MPU_x_Timer_Is_Timer_सक्रिय_Impl,                    /* SYSTEM_CALL_xTimerIsTimerActive. */
            ( UBaseType_t ) MPU_xTimerGetTimerDaemonTaskHandleImpl,         /* SYSTEM_CALL_xTimerGetTimerDaemonTaskHandle. */
            ( UBaseType_t ) MPU_pcTimerGetNameImpl,                         /* SYSTEM_CALL_pcTimerGetName. */
            ( UBaseType_t ) MPU_v_Timer_समुच्चयः_Reload_बहुलकम्_Impl,                    /* SYSTEM_CALL_vTimerSetReloadMode. */
            ( UBaseType_t ) MPU_x_Timer_Get_Reload_बहुलकम्_Impl,                    /* SYSTEM_CALL_xTimerGetReloadMode. */
            ( UBaseType_t ) MPU_ux_Timer_Get_Reload_बहुलकम्_Impl,                   /* SYSTEM_CALL_uxTimerGetReloadMode. */
            ( UBaseType_t ) MPU_xTimerGetPeriodImpl,                        /* SYSTEM_CALL_xTimerGetPeriod. */
            ( UBaseType_t ) MPU_xTimerGetExpiryTimeImpl,                    /* SYSTEM_CALL_xTimerGetExpiryTime. */
        #अन्यथा
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
        #यदि_अन्तः

        #यदि ( configUSE_EVENT_GROUPS == 1 )
            ( UBaseType_t ) MPU_x_Event_गणः_Clear_द्वयङ्काः_Impl,                   /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) MPU_x_Event_गणः_समुच्चयः_द्वयङ्काः_Impl,                     /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) MPU_x_Event_गणः_Sync_Impl,                        /* SYSTEM_CALL_xEventGroupSync. */

            #यदि ( configUSE_TRACE_FACILITY == 1 )
                ( UBaseType_t ) MPU_ux_Event_गणः_Get_सङ्ख्या_Impl,              /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) MPU_v_Event_गणः_समुच्चयः_सङ्ख्या_Impl,               /* SYSTEM_CALL_vEventGroupSetNumber. */
            #अन्यथा
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_uxEventGroupGetNumber. */
                ( UBaseType_t ) 0,                                          /* SYSTEM_CALL_vEventGroupSetNumber. */
            #यदि_अन्तः
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupClearBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSetBits. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xEventGroupSync. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_uxEventGroupGetNumber. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_vEventGroupSetNumber. */
        #यदि_अन्तः

        #यदि ( config_USE_प्रवाहः_BUFFERS == 1 )
            ( UBaseType_t ) MPU_x_प्रवाहः_बफर_Send_Impl,                      /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) MPU_x_प्रवाहः_बफर_Receive_Impl,                   /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) MPU_x_प्रवाहः_बफर_Is_पूर्णम्_Impl,                    /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) MPU_x_प्रवाहः_बफर_Is_रिक्तानि_Impl,                   /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) MPU_x_प्रवाहः_बफर_Spaces_उपलब्धम्_Impl,           /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) MPU_x_प्रवाहः_बफर_अष्टकानि_उपलब्धम्_Impl,            /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) MPU_x_प्रवाहः_बफर_समुच्चयः_Trigger_Level_Impl,           /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) MPU_x_प्रवाहः_बफर_अग्र_सन्देशः_दीर्घता_अष्टकानि_Impl     /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #अन्यथा
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSend. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferReceive. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsFull. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferIsEmpty. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSpacesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferBytesAvailable. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferSetTriggerLevel. */
            ( UBaseType_t ) 0,                                              /* SYSTEM_CALL_xStreamBufferNextMessageLengthBytes. */
        #यदि_अन्तः

    };
/*-----------------------------------------------------------*/

#यदि_अन्तः /* #if ( ( portUSING_MPU_WRAPPERS == 1 ) && ( configUSE_MPU_WRAPPERS_V1 == 0 ) ) */
/*-----------------------------------------------------------*/
