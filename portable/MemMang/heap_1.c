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
#అన్తర్భావ <stdlib.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#నిర్వచించు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

#నిర్వచనం_రద్దు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ఒకవేళ ( config_SUPPORT_DYNAMIC_కేటాయింపు == 0 )
    #దోషం This file must not be వాడిన ఒకవేళ config_SUPPORT_DYNAMIC_కేటాయింపు is 0
#అయితే_ముగింపు

/* A few bytes might be lost to byte aligning the heap start address. */
#నిర్వచించు config_ADJUSTED_కుప్ప_కొలత        ( config_మొత్తం_కుప్ప_కొలత - పోర్టు_BYTE_ALIGNMENT )

/* Max value that fits in a size_t type. */
#నిర్వచించు కుప్ప_కొలత_MAX                    ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#నిర్వచించు కుప్ప_కూడు_WILL_అధికప్రవాహం( a, b )   ( ( a ) > ( కుప్ప_కొలత_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#ఒకవేళ ( config_APPLICATION_ALLOCATED_కుప్ప == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    బాహ్య uint8_t uc_కుప్ప[ config_మొత్తం_కుప్ప_కొలత ];
#లేకపోతే
    స్థిర uint8_t uc_కుప్ప[ config_మొత్తం_కుప్ప_కొలత ];
#అయితే_ముగింపు /* configAPPLICATION_ALLOCATED_HEAP */

/* Index into the ucHeap array. */
స్థిర size_t x_తదుపరి_Free_Byte = ( size_t ) 0U;

/*-----------------------------------------------------------*/

శూన్య * pv_పోర్టు_Malloc( size_t x_Wanted_కొలత )
{
    శూన్య * pvReturn = ఖాళీ;
    స్థిర uint8_t * puc_Aligned_కుప్ప = ఖాళీ;

    /* Ensure that blocks are always aligned. */
    #ఒకవేళ ( పోర్టు_BYTE_ALIGNMENT != 1 )
    {
        size_t x_Additional_Required_కొలత;

        ఒకవేళ( ( x_Wanted_కొలత & పోర్టు_BYTE_ALIGNMENT_ముసుగు ) != 0x00 )
        {
            /* Byte alignment required. */
            x_Additional_Required_కొలత = పోర్టు_BYTE_ALIGNMENT - ( x_Wanted_కొలత & పోర్టు_BYTE_ALIGNMENT_ముసుగు );

            ఒకవేళ( కుప్ప_కూడు_WILL_అధికప్రవాహం( x_Wanted_కొలత, x_Additional_Required_కొలత ) == 0 )
            {
                x_Wanted_కొలత += x_Additional_Required_కొలత;
            }
            లేకపోతే
            {
                x_Wanted_కొలత = 0;
            }
        }
    }
    #అయితే_ముగింపు /* if ( portBYTE_ALIGNMENT != 1 ) */

    vTaskSuspendAll();
    {
        ఒకవేళ( puc_Aligned_కుప్ప == ఖాళీ )
        {
            /* Ensure the heap starts on a correctly aligned boundary. */
            puc_Aligned_కుప్ప = ( uint8_t * ) ( ( ( పోర్టు_సూచిక_కొలత_TYPE ) &( uc_కుప్ప[ పోర్టు_BYTE_ALIGNMENT - 1 ] ) ) &
                                             ( ~( ( పోర్టు_సూచిక_కొలత_TYPE ) పోర్టు_BYTE_ALIGNMENT_ముసుగు ) ) );
        }

        /* Check there is enough room left for the allocation. */
        ఒకవేళ( ( x_Wanted_కొలత > 0 ) &&
            ( కుప్ప_కూడు_WILL_అధికప్రవాహం( x_తదుపరి_Free_Byte, x_Wanted_కొలత ) == 0 ) &&
            ( ( x_తదుపరి_Free_Byte + x_Wanted_కొలత ) < config_ADJUSTED_కుప్ప_కొలత ) )
        {
            /* Return the next free byte then increment the index past this
             * block. */
            pvReturn = puc_Aligned_కుప్ప + x_తదుపరి_Free_Byte;
            x_తదుపరి_Free_Byte += x_Wanted_కొలత;
        }

        traceMALLOC( pvReturn, x_Wanted_కొలత );
    }
    ( శూన్య ) xTaskResumeAll();

    #ఒకవేళ ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        ఒకవేళ( pvReturn == ఖాళీ )
        {
            vApplicationMallocFailedHook();
        }
    }
    #అయితే_ముగింపు

    తిరిగి pvReturn;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Free( శూన్య * pv )
{
    /* Memory cannot be freed using this scheme.  See heap_2.c, heap_3.c and
     * heap_4.c for alternative implementations, and the memory management pages of
     * https://www.FreeRTOS.org for more information. */
    ( శూన్య ) pv;

    /* Force an assert as it is invalid to call this function. */
    configASSERT( pv == ఖాళీ );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Initialise_ఖండాలు( శూన్య )
{
    /* Only required when static memory is not cleared. */
    x_తదుపరి_Free_Byte = ( size_t ) 0;
}
/*-----------------------------------------------------------*/

size_t x_పోర్టు_Get_Free_కుప్ప_కొలత( శూన్య )
{
    తిరిగి( config_ADJUSTED_కుప్ప_కొలత - x_తదుపరి_Free_Byte );
}

/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
శూన్య v_పోర్టు_కుప్ప_Reset_State( శూన్య )
{
    x_తదుపరి_Free_Byte = ( size_t ) 0U;
}
/*-----------------------------------------------------------*/
