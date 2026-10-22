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
#समावेश <stdlib.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#घोषणा MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#समावेश "FreeRTOS.h"
#समावेश "task.h"

#अघोषित MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#अगर ( configSUPPORT_DYNAMIC_ALLOCATION == 0 )
    #त्रुटि This file must not be used अगर configSUPPORT_DYNAMIC_ALLOCATION is 0
#पूर्ण_अगर

/* A few bytes might be lost to byte aligning the heap start address. */
#घोषणा config_ADJUSTED_HEAP_आकार        ( config_योग_HEAP_आकार - portBYTE_ALIGNMENT )

/* Max value that fits in a size_t type. */
#घोषणा heap_आकार_MAX                    ( ~( ( माप_प्रकार ) 0 ) )

/* Check if adding a and b will result in overflow. */
#घोषणा heapADD_WILL_OVERFLOW( a, b )   ( ( a ) > ( heap_आकार_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#अगर ( configAPPLICATION_ALLOCATED_HEAP == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    बाह्य uint8_t ucHeap[ config_योग_HEAP_आकार ];
#अन्यथा
    अटल uint8_t ucHeap[ config_योग_HEAP_आकार ];
#पूर्ण_अगर /* configAPPLICATION_ALLOCATED_HEAP */

/* Index into the ucHeap array. */
अटल माप_प्रकार x_अग्र_Free_Byte = ( माप_प्रकार ) 0U;

/*-----------------------------------------------------------*/

व्योम * pvPortMalloc( माप_प्रकार x_Wanted_आकार )
{
    व्योम * pvReturn = शून्य;
    अटल uint8_t * pucAlignedHeap = शून्य;

    /* Ensure that blocks are always aligned. */
    #अगर ( portBYTE_ALIGNMENT != 1 )
    {
        माप_प्रकार x_Additional_Required_आकार;

        अगर( ( x_Wanted_आकार & portBYTE_ALIGNMENT_MASK ) != 0x00 )
        {
            /* Byte alignment required. */
            x_Additional_Required_आकार = portBYTE_ALIGNMENT - ( x_Wanted_आकार & portBYTE_ALIGNMENT_MASK );

            अगर( heapADD_WILL_OVERFLOW( x_Wanted_आकार, x_Additional_Required_आकार ) == 0 )
            {
                x_Wanted_आकार += x_Additional_Required_आकार;
            }
            अन्यथा
            {
                x_Wanted_आकार = 0;
            }
        }
    }
    #पूर्ण_अगर /* if ( portBYTE_ALIGNMENT != 1 ) */

    vTaskSuspendAll();
    {
        अगर( pucAlignedHeap == शून्य )
        {
            /* Ensure the heap starts on a correctly aligned boundary. */
            pucAlignedHeap = ( uint8_t * ) ( ( ( port_POINTER_आकार_TYPE ) &( ucHeap[ portBYTE_ALIGNMENT - 1 ] ) ) &
                                             ( ~( ( port_POINTER_आकार_TYPE ) portBYTE_ALIGNMENT_MASK ) ) );
        }

        /* Check there is enough room left for the allocation. */
        अगर( ( x_Wanted_आकार > 0 ) &&
            ( heapADD_WILL_OVERFLOW( x_अग्र_Free_Byte, x_Wanted_आकार ) == 0 ) &&
            ( ( x_अग्र_Free_Byte + x_Wanted_आकार ) < config_ADJUSTED_HEAP_आकार ) )
        {
            /* Return the next free byte then increment the index past this
             * block. */
            pvReturn = pucAlignedHeap + x_अग्र_Free_Byte;
            x_अग्र_Free_Byte += x_Wanted_आकार;
        }

        traceMALLOC( pvReturn, x_Wanted_आकार );
    }
    ( व्योम ) xTaskResumeAll();

    #अगर ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        अगर( pvReturn == शून्य )
        {
            vApplicationMallocFailedHook();
        }
    }
    #पूर्ण_अगर

    वापस pvReturn;
}
/*-----------------------------------------------------------*/

व्योम vPortFree( व्योम * pv )
{
    /* Memory cannot be freed using this scheme.  See heap_2.c, heap_3.c and
     * heap_4.c for alternative implementations, and the memory management pages of
     * https://www.FreeRTOS.org for more information. */
    ( व्योम ) pv;

    /* Force an assert as it is invalid to call this function. */
    configASSERT( pv == शून्य );
}
/*-----------------------------------------------------------*/

व्योम vPortInitialiseBlocks( व्योम )
{
    /* Only required when static memory is not cleared. */
    x_अग्र_Free_Byte = ( माप_प्रकार ) 0;
}
/*-----------------------------------------------------------*/

माप_प्रकार x_Port_Get_Free_Heap_आकार( व्योम )
{
    वापस( config_ADJUSTED_HEAP_आकार - x_अग्र_Free_Byte );
}

/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
व्योम vPortHeapResetState( व्योम )
{
    x_अग्र_Free_Byte = ( माप_प्रकार ) 0U;
}
/*-----------------------------------------------------------*/
