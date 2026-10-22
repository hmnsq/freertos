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
#وصف_ڪريو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ضمن "FreeRTOS.h"
#ضمن "task.h"

#وصف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#إذا ( config_SUPPORT_DYNAMIC_ورهاست == 0 )
    #غلطي This file must not be استعمال_ٿيل إذا config_SUPPORT_DYNAMIC_ورهاست is 0
#جيڪڏهن_پورو

/* A few bytes might be lost to byte aligning the heap start address. */
#وصف_ڪريو config_ADJUSTED_ڍير_سائيز        ( config_ڪل_ڍير_سائيز - پورٽ_BYTE_ALIGNMENT )

/* Max value that fits in a size_t type. */
#وصف_ڪريو ڍير_سائيز_MAX                    ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#وصف_ڪريو ڍير_جوڙيو_WILL_حد_کان_مٿي( a, b )   ( ( a ) > ( ڍير_سائيز_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#إذا ( config_APPLICATION_ALLOCATED_ڍير == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    خارجي uint8_t uc_ڍير[ config_ڪل_ڍير_سائيز ];
#وإلا
    ساكن uint8_t uc_ڍير[ config_ڪل_ڍير_سائيز ];
#جيڪڏهن_پورو /* configAPPLICATION_ALLOCATED_HEAP */

/* Index into the ucHeap array. */
ساكن size_t x_ايندڙ_Free_Byte = ( size_t ) 0U;

/*-----------------------------------------------------------*/

فراغ * pv_پورٽ_Malloc( size_t x_Wanted_سائيز )
{
    فراغ * pvReturn = عدم;
    ساكن uint8_t * puc_Aligned_ڍير = عدم;

    /* Ensure that blocks are always aligned. */
    #إذا ( پورٽ_BYTE_ALIGNMENT != 1 )
    {
        size_t x_Additional_Required_سائيز;

        إذا( ( x_Wanted_سائيز & پورٽ_BYTE_ALIGNMENT_نقاب ) != 0x00 )
        {
            /* Byte alignment required. */
            x_Additional_Required_سائيز = پورٽ_BYTE_ALIGNMENT - ( x_Wanted_سائيز & پورٽ_BYTE_ALIGNMENT_نقاب );

            إذا( ڍير_جوڙيو_WILL_حد_کان_مٿي( x_Wanted_سائيز, x_Additional_Required_سائيز ) == 0 )
            {
                x_Wanted_سائيز += x_Additional_Required_سائيز;
            }
            وإلا
            {
                x_Wanted_سائيز = 0;
            }
        }
    }
    #جيڪڏهن_پورو /* if ( portBYTE_ALIGNMENT != 1 ) */

    vTaskSuspendAll();
    {
        إذا( puc_Aligned_ڍير == عدم )
        {
            /* Ensure the heap starts on a correctly aligned boundary. */
            puc_Aligned_ڍير = ( uint8_t * ) ( ( ( پورٽ_اشارو_سائيز_TYPE ) &( uc_ڍير[ پورٽ_BYTE_ALIGNMENT - 1 ] ) ) &
                                             ( ~( ( پورٽ_اشارو_سائيز_TYPE ) پورٽ_BYTE_ALIGNMENT_نقاب ) ) );
        }

        /* Check there is enough room left for the allocation. */
        إذا( ( x_Wanted_سائيز > 0 ) &&
            ( ڍير_جوڙيو_WILL_حد_کان_مٿي( x_ايندڙ_Free_Byte, x_Wanted_سائيز ) == 0 ) &&
            ( ( x_ايندڙ_Free_Byte + x_Wanted_سائيز ) < config_ADJUSTED_ڍير_سائيز ) )
        {
            /* Return the next free byte then increment the index past this
             * block. */
            pvReturn = puc_Aligned_ڍير + x_ايندڙ_Free_Byte;
            x_ايندڙ_Free_Byte += x_Wanted_سائيز;
        }

        traceMALLOC( pvReturn, x_Wanted_سائيز );
    }
    ( فراغ ) xTaskResumeAll();

    #إذا ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        إذا( pvReturn == عدم )
        {
            vApplicationMallocFailedHook();
        }
    }
    #جيڪڏهن_پورو

    أرجع pvReturn;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Free( فراغ * pv )
{
    /* Memory cannot be freed using this scheme.  See heap_2.c, heap_3.c and
     * heap_4.c for alternative implementations, and the memory management pages of
     * https://www.FreeRTOS.org for more information. */
    ( فراغ ) pv;

    /* Force an assert as it is invalid to call this function. */
    configASSERT( pv == عدم );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Initialise_بلاڪون( فراغ )
{
    /* Only required when static memory is not cleared. */
    x_ايندڙ_Free_Byte = ( size_t ) 0;
}
/*-----------------------------------------------------------*/

size_t x_پورٽ_Get_Free_ڍير_سائيز( فراغ )
{
    أرجع( config_ADJUSTED_ڍير_سائيز - x_ايندڙ_Free_Byte );
}

/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
فراغ v_پورٽ_ڍير_Reset_State( فراغ )
{
    x_ايندڙ_Free_Byte = ( size_t ) 0U;
}
/*-----------------------------------------------------------*/
