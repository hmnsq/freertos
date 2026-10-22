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
 * The simplest possible implementation of pvPortMalloc().  Note that this
 * implementation does NOT allow allocated memory to be freed again.
 *
 * See heap_2.c, heap_3.c and heap_4.c for alternative implementations, and the
 * memory management pages of https://www.FreeRTOS.org for more information.
 */
#अन्तर्भाव <stdlib.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#परिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

#अपरिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#यदि ( config_SUPPORT_DYNAMIC_आवण्टनम् == 0 )
    #दोषः This file must not be प्रयुक्तम् यदि config_SUPPORT_DYNAMIC_आवण्टनम् is 0
#यदि_अन्तः

/* A few bytes might be lost to byte aligning the heap start address. */
#परिभाषय config_ADJUSTED_HEAP_आकार        ( config_योग_HEAP_आकार - पत्तनम्_BYTE_ALIGNMENT )

/* Max value that fits in a size_t type. */
#परिभाषय heap_आकार_MAX                    ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#परिभाषय heap_सङ्कलय_WILL_अतिप्रवाहः( a, b )   ( ( a ) > ( heap_आकार_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#यदि ( configAPPLICATION_ALLOCATED_HEAP == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    बाह्य uint8_t ucHeap[ config_योग_HEAP_आकार ];
#अन्यथा
    स्थिर uint8_t ucHeap[ config_योग_HEAP_आकार ];
#यदि_अन्तः /* configAPPLICATION_ALLOCATED_HEAP */

/* Index into the ucHeap array. */
स्थिर size_t x_अग्र_Free_Byte = ( size_t ) 0U;

/*-----------------------------------------------------------*/

शून्य * pv_पत्तनम्_Malloc( size_t x_Wanted_आकार )
{
    शून्य * pvReturn = रिक्त;
    स्थिर uint8_t * pucAlignedHeap = रिक्त;

    /* Ensure that blocks are always aligned. */
    #यदि ( पत्तनम्_BYTE_ALIGNMENT != 1 )
    {
        size_t x_Additional_Required_आकार;

        यदि( ( x_Wanted_आकार & पत्तनम्_BYTE_ALIGNMENT_आवरणम् ) != 0x00 )
        {
            /* Byte alignment required. */
            x_Additional_Required_आकार = पत्तनम्_BYTE_ALIGNMENT - ( x_Wanted_आकार & पत्तनम्_BYTE_ALIGNMENT_आवरणम् );

            यदि( heap_सङ्कलय_WILL_अतिप्रवाहः( x_Wanted_आकार, x_Additional_Required_आकार ) == 0 )
            {
                x_Wanted_आकार += x_Additional_Required_आकार;
            }
            अन्यथा
            {
                x_Wanted_आकार = 0;
            }
        }
    }
    #यदि_अन्तः /* if ( portBYTE_ALIGNMENT != 1 ) */

    vTaskSuspendAll();
    {
        यदि( pucAlignedHeap == रिक्त )
        {
            /* Ensure the heap starts on a correctly aligned boundary. */
            pucAlignedHeap = ( uint8_t * ) ( ( ( पत्तनम्_POINTER_आकार_TYPE ) &( ucHeap[ पत्तनम्_BYTE_ALIGNMENT - 1 ] ) ) &
                                             ( ~( ( पत्तनम्_POINTER_आकार_TYPE ) पत्तनम्_BYTE_ALIGNMENT_आवरणम् ) ) );
        }

        /* Check there is enough room left for the allocation. */
        यदि( ( x_Wanted_आकार > 0 ) &&
            ( heap_सङ्कलय_WILL_अतिप्रवाहः( x_अग्र_Free_Byte, x_Wanted_आकार ) == 0 ) &&
            ( ( x_अग्र_Free_Byte + x_Wanted_आकार ) < config_ADJUSTED_HEAP_आकार ) )
        {
            /* Return the next free byte then increment the index past this
             * block. */
            pvReturn = pucAlignedHeap + x_अग्र_Free_Byte;
            x_अग्र_Free_Byte += x_Wanted_आकार;
        }

        traceMALLOC( pvReturn, x_Wanted_आकार );
    }
    ( शून्य ) xTaskResumeAll();

    #यदि ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        यदि( pvReturn == रिक्त )
        {
            vApplicationMallocFailedHook();
        }
    }
    #यदि_अन्तः

    प्रत्यागम pvReturn;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Free( शून्य * pv )
{
    /* Memory cannot be freed using this scheme.  See heap_2.c, heap_3.c and
     * heap_4.c for alternative implementations, and the memory management pages of
     * https://www.FreeRTOS.org for more information. */
    ( शून्य ) pv;

    /* Force an assert as it is invalid to call this function. */
    configASSERT( pv == रिक्त );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Initialise_खण्डानि( शून्य )
{
    /* Only required when static memory is not cleared. */
    x_अग्र_Free_Byte = ( size_t ) 0;
}
/*-----------------------------------------------------------*/

size_t x_पत्तनम्_Get_Free_Heap_आकार( शून्य )
{
    प्रत्यागम( config_ADJUSTED_HEAP_आकार - x_अग्र_Free_Byte );
}

/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
शून्य v_पत्तनम्_Heap_Reset_State( शून्य )
{
    x_अग्र_Free_Byte = ( size_t ) 0U;
}
/*-----------------------------------------------------------*/
