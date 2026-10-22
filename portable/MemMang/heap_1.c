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
#ضمن <stdlib.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#تعریف_کړه MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ضمن "FreeRTOS.h"
#ضمن "task.h"

#تعریف_لغوه MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#إذا ( config_SUPPORT_DYNAMIC_ویش == 0 )
    #تېروتنه This file must not be کارول_شوی إذا config_SUPPORT_DYNAMIC_ویش is 0
#د_که_پای

/* A few bytes might be lost to byte aligning the heap start address. */
#تعریف_کړه config_ADJUSTED_ډېرۍ_اندازه        ( config_ټول_ډېرۍ_اندازه - پورټ_BYTE_ALIGNMENT )

/* Max value that fits in a size_t type. */
#تعریف_کړه ډېرۍ_اندازه_MAX                    ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کړه ډېرۍ_جمع_کړه_WILL_ډکېدنه( a, b )   ( ( a ) > ( ډېرۍ_اندازه_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#إذا ( config_APPLICATION_ALLOCATED_ډېرۍ == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    خارجي uint8_t uc_ډېرۍ[ config_ټول_ډېرۍ_اندازه ];
#وإلا
    ساكن uint8_t uc_ډېرۍ[ config_ټول_ډېرۍ_اندازه ];
#د_که_پای /* configAPPLICATION_ALLOCATED_HEAP */

/* Index into the ucHeap array. */
ساكن size_t x_بل_Free_Byte = ( size_t ) 0U;

/*-----------------------------------------------------------*/

فراغ * pv_پورټ_Malloc( size_t x_Wanted_اندازه )
{
    فراغ * pvReturn = عدم;
    ساكن uint8_t * puc_Aligned_ډېرۍ = عدم;

    /* Ensure that blocks are always aligned. */
    #إذا ( پورټ_BYTE_ALIGNMENT != 1 )
    {
        size_t x_Additional_Required_اندازه;

        إذا( ( x_Wanted_اندازه & پورټ_BYTE_ALIGNMENT_ماسک ) != 0x00 )
        {
            /* Byte alignment required. */
            x_Additional_Required_اندازه = پورټ_BYTE_ALIGNMENT - ( x_Wanted_اندازه & پورټ_BYTE_ALIGNMENT_ماسک );

            إذا( ډېرۍ_جمع_کړه_WILL_ډکېدنه( x_Wanted_اندازه, x_Additional_Required_اندازه ) == 0 )
            {
                x_Wanted_اندازه += x_Additional_Required_اندازه;
            }
            وإلا
            {
                x_Wanted_اندازه = 0;
            }
        }
    }
    #د_که_پای /* if ( portBYTE_ALIGNMENT != 1 ) */

    vTaskSuspendAll();
    {
        إذا( puc_Aligned_ډېرۍ == عدم )
        {
            /* Ensure the heap starts on a correctly aligned boundary. */
            puc_Aligned_ډېرۍ = ( uint8_t * ) ( ( ( پورټ_اشاره_ګر_اندازه_TYPE ) &( uc_ډېرۍ[ پورټ_BYTE_ALIGNMENT - 1 ] ) ) &
                                             ( ~( ( پورټ_اشاره_ګر_اندازه_TYPE ) پورټ_BYTE_ALIGNMENT_ماسک ) ) );
        }

        /* Check there is enough room left for the allocation. */
        إذا( ( x_Wanted_اندازه > 0 ) &&
            ( ډېرۍ_جمع_کړه_WILL_ډکېدنه( x_بل_Free_Byte, x_Wanted_اندازه ) == 0 ) &&
            ( ( x_بل_Free_Byte + x_Wanted_اندازه ) < config_ADJUSTED_ډېرۍ_اندازه ) )
        {
            /* Return the next free byte then increment the index past this
             * block. */
            pvReturn = puc_Aligned_ډېرۍ + x_بل_Free_Byte;
            x_بل_Free_Byte += x_Wanted_اندازه;
        }

        traceMALLOC( pvReturn, x_Wanted_اندازه );
    }
    ( فراغ ) xTaskResumeAll();

    #إذا ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        إذا( pvReturn == عدم )
        {
            vApplicationMallocFailedHook();
        }
    }
    #د_که_پای

    أرجع pvReturn;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Free( فراغ * pv )
{
    /* Memory cannot be freed using this scheme.  See heap_2.c, heap_3.c and
     * heap_4.c for alternative implementations, and the memory management pages of
     * https://www.FreeRTOS.org for more information. */
    ( فراغ ) pv;

    /* Force an assert as it is invalid to call this function. */
    configASSERT( pv == عدم );
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Initialise_بلاکونه( فراغ )
{
    /* Only required when static memory is not cleared. */
    x_بل_Free_Byte = ( size_t ) 0;
}
/*-----------------------------------------------------------*/

size_t x_پورټ_Get_Free_ډېرۍ_اندازه( فراغ )
{
    أرجع( config_ADJUSTED_ډېرۍ_اندازه - x_بل_Free_Byte );
}

/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
فراغ v_پورټ_ډېرۍ_Reset_State( فراغ )
{
    x_بل_Free_Byte = ( size_t ) 0U;
}
/*-----------------------------------------------------------*/
