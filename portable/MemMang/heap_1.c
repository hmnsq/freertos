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
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ਜੇ ( config_SUPPORT_DYNAMIC_ਵੰਡ == 0 )
    #ਗਲਤੀ This file must not be ਵਰਤਿਆ ਜੇ config_SUPPORT_DYNAMIC_ਵੰਡ is 0
#ਜੇ_ਅੰਤ

/* A few bytes might be lost to byte aligning the heap start address. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ADJUSTED_ਢੇਰ_ਮਾਪ        ( config_ਕੁੱਲ_ਢੇਰ_ਮਾਪ - ਪੋਰਟ_BYTE_ALIGNMENT )

/* Max value that fits in a size_t type. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਮਾਪ_MAX                    ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਜੋੜੋ_WILL_ਉਛਾਲ( a, b )   ( ( a ) > ( ਢੇਰ_ਮਾਪ_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#ਜੇ ( config_APPLICATION_ALLOCATED_ਢੇਰ == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    ਬਾਹਰੀ uint8_t uc_ਢੇਰ[ config_ਕੁੱਲ_ਢੇਰ_ਮਾਪ ];
#ਨਹੀਂਤਾਂ
    ਸਥਿਰ uint8_t uc_ਢੇਰ[ config_ਕੁੱਲ_ਢੇਰ_ਮਾਪ ];
#ਜੇ_ਅੰਤ /* configAPPLICATION_ALLOCATED_HEAP */

/* Index into the ucHeap array. */
ਸਥਿਰ size_t x_ਅਗਲਾ_Free_Byte = ( size_t ) 0U;

/*-----------------------------------------------------------*/

ਖਾਲੀ * pv_ਪੋਰਟ_Malloc( size_t x_Wanted_ਮਾਪ )
{
    ਖਾਲੀ * pvReturn = ਨਿਰਾ;
    ਸਥਿਰ uint8_t * puc_Aligned_ਢੇਰ = ਨਿਰਾ;

    /* Ensure that blocks are always aligned. */
    #ਜੇ ( ਪੋਰਟ_BYTE_ALIGNMENT != 1 )
    {
        size_t x_Additional_Required_ਮਾਪ;

        ਜੇ( ( x_Wanted_ਮਾਪ & ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) != 0x00 )
        {
            /* Byte alignment required. */
            x_Additional_Required_ਮਾਪ = ਪੋਰਟ_BYTE_ALIGNMENT - ( x_Wanted_ਮਾਪ & ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ );

            ਜੇ( ਢੇਰ_ਜੋੜੋ_WILL_ਉਛਾਲ( x_Wanted_ਮਾਪ, x_Additional_Required_ਮਾਪ ) == 0 )
            {
                x_Wanted_ਮਾਪ += x_Additional_Required_ਮਾਪ;
            }
            ਨਹੀਂਤਾਂ
            {
                x_Wanted_ਮਾਪ = 0;
            }
        }
    }
    #ਜੇ_ਅੰਤ /* if ( portBYTE_ALIGNMENT != 1 ) */

    vTaskSuspendAll();
    {
        ਜੇ( puc_Aligned_ਢੇਰ == ਨਿਰਾ )
        {
            /* Ensure the heap starts on a correctly aligned boundary. */
            puc_Aligned_ਢੇਰ = ( uint8_t * ) ( ( ( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE ) &( uc_ਢੇਰ[ ਪੋਰਟ_BYTE_ALIGNMENT - 1 ] ) ) &
                                             ( ~( ( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE ) ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) ) );
        }

        /* Check there is enough room left for the allocation. */
        ਜੇ( ( x_Wanted_ਮਾਪ > 0 ) &&
            ( ਢੇਰ_ਜੋੜੋ_WILL_ਉਛਾਲ( x_ਅਗਲਾ_Free_Byte, x_Wanted_ਮਾਪ ) == 0 ) &&
            ( ( x_ਅਗਲਾ_Free_Byte + x_Wanted_ਮਾਪ ) < config_ADJUSTED_ਢੇਰ_ਮਾਪ ) )
        {
            /* Return the next free byte then increment the index past this
             * block. */
            pvReturn = puc_Aligned_ਢੇਰ + x_ਅਗਲਾ_Free_Byte;
            x_ਅਗਲਾ_Free_Byte += x_Wanted_ਮਾਪ;
        }

        traceMALLOC( pvReturn, x_Wanted_ਮਾਪ );
    }
    ( ਖਾਲੀ ) xTaskResumeAll();

    #ਜੇ ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        ਜੇ( pvReturn == ਨਿਰਾ )
        {
            vApplicationMallocFailedHook();
        }
    }
    #ਜੇ_ਅੰਤ

    ਵਾਪਸ pvReturn;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Free( ਖਾਲੀ * pv )
{
    /* Memory cannot be freed using this scheme.  See heap_2.c, heap_3.c and
     * heap_4.c for alternative implementations, and the memory management pages of
     * https://www.FreeRTOS.org for more information. */
    ( ਖਾਲੀ ) pv;

    /* Force an assert as it is invalid to call this function. */
    configASSERT( pv == ਨਿਰਾ );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Initialise_ਖੰਡਾਂ( ਖਾਲੀ )
{
    /* Only required when static memory is not cleared. */
    x_ਅਗਲਾ_Free_Byte = ( size_t ) 0;
}
/*-----------------------------------------------------------*/

size_t x_ਪੋਰਟ_Get_Free_ਢੇਰ_ਮਾਪ( ਖਾਲੀ )
{
    ਵਾਪਸ( config_ADJUSTED_ਢੇਰ_ਮਾਪ - x_ਅਗਲਾ_Free_Byte );
}

/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
ਖਾਲੀ v_ਪੋਰਟ_ਢੇਰ_Reset_State( ਖਾਲੀ )
{
    x_ਅਗਲਾ_Free_Byte = ( size_t ) 0U;
}
/*-----------------------------------------------------------*/
