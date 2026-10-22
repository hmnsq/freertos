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
#شامل <stdlib.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#تعریف_کرو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#شامل "FreeRTOS.h"
#شامل "task.h"

#تعریف_منسوخ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#اگر ( config_SUPPORT_DYNAMIC_تخصیص == 0 )
    #غلطی This file must not be مستعمل اگر config_SUPPORT_DYNAMIC_تخصیص is 0
#اگر_ختم

/* A few bytes might be lost to byte aligning the heap start address. */
#تعریف_کرو config_ADJUSTED_ڈھیر_سائز        ( config_کل_ڈھیر_سائز - پورٹ_BYTE_ALIGNMENT )

/* Max value that fits in a size_t type. */
#تعریف_کرو ڈھیر_سائز_MAX                    ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کرو ڈھیر_جوڑو_WILL_حد_سے_تجاوز( a, b )   ( ( a ) > ( ڈھیر_سائز_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#اگر ( config_APPLICATION_ALLOCATED_ڈھیر == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    خارجی uint8_t uc_ڈھیر[ config_کل_ڈھیر_سائز ];
#ورنہ
    ساکن uint8_t uc_ڈھیر[ config_کل_ڈھیر_سائز ];
#اگر_ختم /* configAPPLICATION_ALLOCATED_HEAP */

/* Index into the ucHeap array. */
ساکن size_t x_اگلا_Free_Byte = ( size_t ) 0U;

/*-----------------------------------------------------------*/

خالی * pv_پورٹ_Malloc( size_t x_Wanted_سائز )
{
    خالی * pvReturn = تہی;
    ساکن uint8_t * puc_Aligned_ڈھیر = تہی;

    /* Ensure that blocks are always aligned. */
    #اگر ( پورٹ_BYTE_ALIGNMENT != 1 )
    {
        size_t x_Additional_Required_سائز;

        اگر( ( x_Wanted_سائز & پورٹ_BYTE_ALIGNMENT_نقاب ) != 0x00 )
        {
            /* Byte alignment required. */
            x_Additional_Required_سائز = پورٹ_BYTE_ALIGNMENT - ( x_Wanted_سائز & پورٹ_BYTE_ALIGNMENT_نقاب );

            اگر( ڈھیر_جوڑو_WILL_حد_سے_تجاوز( x_Wanted_سائز, x_Additional_Required_سائز ) == 0 )
            {
                x_Wanted_سائز += x_Additional_Required_سائز;
            }
            ورنہ
            {
                x_Wanted_سائز = 0;
            }
        }
    }
    #اگر_ختم /* if ( portBYTE_ALIGNMENT != 1 ) */

    vTaskSuspendAll();
    {
        اگر( puc_Aligned_ڈھیر == تہی )
        {
            /* Ensure the heap starts on a correctly aligned boundary. */
            puc_Aligned_ڈھیر = ( uint8_t * ) ( ( ( پورٹ_اشارہ_گر_سائز_TYPE ) &( uc_ڈھیر[ پورٹ_BYTE_ALIGNMENT - 1 ] ) ) &
                                             ( ~( ( پورٹ_اشارہ_گر_سائز_TYPE ) پورٹ_BYTE_ALIGNMENT_نقاب ) ) );
        }

        /* Check there is enough room left for the allocation. */
        اگر( ( x_Wanted_سائز > 0 ) &&
            ( ڈھیر_جوڑو_WILL_حد_سے_تجاوز( x_اگلا_Free_Byte, x_Wanted_سائز ) == 0 ) &&
            ( ( x_اگلا_Free_Byte + x_Wanted_سائز ) < config_ADJUSTED_ڈھیر_سائز ) )
        {
            /* Return the next free byte then increment the index past this
             * block. */
            pvReturn = puc_Aligned_ڈھیر + x_اگلا_Free_Byte;
            x_اگلا_Free_Byte += x_Wanted_سائز;
        }

        traceMALLOC( pvReturn, x_Wanted_سائز );
    }
    ( خالی ) xTaskResumeAll();

    #اگر ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        اگر( pvReturn == تہی )
        {
            vApplicationMallocFailedHook();
        }
    }
    #اگر_ختم

    واپس pvReturn;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Free( خالی * pv )
{
    /* Memory cannot be freed using this scheme.  See heap_2.c, heap_3.c and
     * heap_4.c for alternative implementations, and the memory management pages of
     * https://www.FreeRTOS.org for more information. */
    ( خالی ) pv;

    /* Force an assert as it is invalid to call this function. */
    configASSERT( pv == تہی );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Initialise_بلاکیں( خالی )
{
    /* Only required when static memory is not cleared. */
    x_اگلا_Free_Byte = ( size_t ) 0;
}
/*-----------------------------------------------------------*/

size_t x_پورٹ_Get_Free_ڈھیر_سائز( خالی )
{
    واپس( config_ADJUSTED_ڈھیر_سائز - x_اگلا_Free_Byte );
}

/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
خالی v_پورٹ_ڈھیر_Reset_State( خالی )
{
    x_اگلا_Free_Byte = ( size_t ) 0U;
}
/*-----------------------------------------------------------*/
