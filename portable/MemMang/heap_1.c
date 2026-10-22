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
#ಅನ್ತರ್ಭಾವ <stdlib.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#ವ್ಯಾಖ್ಯಾನಿಸು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ಆದರೆ ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 0 )
    #ದೋಷ This file must not be ಬಳಸಿದ ಆದರೆ config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ is 0
#ಆದರೆ_ಅಂತ್ಯ

/* A few bytes might be lost to byte aligning the heap start address. */
#ವ್ಯಾಖ್ಯಾನಿಸು config_ADJUSTED_ರಾಶಿ_ಗಾತ್ರ        ( config_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ - ಪೋರ್ಟ್_BYTE_ALIGNMENT )

/* Max value that fits in a size_t type. */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಗಾತ್ರ_MAX                    ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಕೂಡಿಸು_WILL_ಅತಿಪ್ರವಾಹ( a, b )   ( ( a ) > ( ರಾಶಿ_ಗಾತ್ರ_MAX - ( b ) ) )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#ಆದರೆ ( config_APPLICATION_ALLOCATED_ರಾಶಿ == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    ಬಾಹ್ಯ uint8_t uc_ರಾಶಿ[ config_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ ];
#ಇಲ್ಲದಿದ್ದರೆ
    ಸ್ಥಿರ uint8_t uc_ರಾಶಿ[ config_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ ];
#ಆದರೆ_ಅಂತ್ಯ /* configAPPLICATION_ALLOCATED_HEAP */

/* Index into the ucHeap array. */
ಸ್ಥಿರ size_t x_ಮುಂದಿನ_Free_Byte = ( size_t ) 0U;

/*-----------------------------------------------------------*/

ಶೂನ್ಯ * pv_ಪೋರ್ಟ್_Malloc( size_t x_Wanted_ಗಾತ್ರ )
{
    ಶೂನ್ಯ * pvReturn = ಖಾಲಿ;
    ಸ್ಥಿರ uint8_t * puc_Aligned_ರಾಶಿ = ಖಾಲಿ;

    /* Ensure that blocks are always aligned. */
    #ಆದರೆ ( ಪೋರ್ಟ್_BYTE_ALIGNMENT != 1 )
    {
        size_t x_Additional_Required_ಗಾತ್ರ;

        ಆದರೆ( ( x_Wanted_ಗಾತ್ರ & ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) != 0x00 )
        {
            /* Byte alignment required. */
            x_Additional_Required_ಗಾತ್ರ = ಪೋರ್ಟ್_BYTE_ALIGNMENT - ( x_Wanted_ಗಾತ್ರ & ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ );

            ಆದರೆ( ರಾಶಿ_ಕೂಡಿಸು_WILL_ಅತಿಪ್ರವಾಹ( x_Wanted_ಗಾತ್ರ, x_Additional_Required_ಗಾತ್ರ ) == 0 )
            {
                x_Wanted_ಗಾತ್ರ += x_Additional_Required_ಗಾತ್ರ;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                x_Wanted_ಗಾತ್ರ = 0;
            }
        }
    }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( portBYTE_ALIGNMENT != 1 ) */

    vTaskSuspendAll();
    {
        ಆದರೆ( puc_Aligned_ರಾಶಿ == ಖಾಲಿ )
        {
            /* Ensure the heap starts on a correctly aligned boundary. */
            puc_Aligned_ರಾಶಿ = ( uint8_t * ) ( ( ( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE ) &( uc_ರಾಶಿ[ ಪೋರ್ಟ್_BYTE_ALIGNMENT - 1 ] ) ) &
                                             ( ~( ( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE ) ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) ) );
        }

        /* Check there is enough room left for the allocation. */
        ಆದರೆ( ( x_Wanted_ಗಾತ್ರ > 0 ) &&
            ( ರಾಶಿ_ಕೂಡಿಸು_WILL_ಅತಿಪ್ರವಾಹ( x_ಮುಂದಿನ_Free_Byte, x_Wanted_ಗಾತ್ರ ) == 0 ) &&
            ( ( x_ಮುಂದಿನ_Free_Byte + x_Wanted_ಗಾತ್ರ ) < config_ADJUSTED_ರಾಶಿ_ಗಾತ್ರ ) )
        {
            /* Return the next free byte then increment the index past this
             * block. */
            pvReturn = puc_Aligned_ರಾಶಿ + x_ಮುಂದಿನ_Free_Byte;
            x_ಮುಂದಿನ_Free_Byte += x_Wanted_ಗಾತ್ರ;
        }

        traceMALLOC( pvReturn, x_Wanted_ಗಾತ್ರ );
    }
    ( ಶೂನ್ಯ ) xTaskResumeAll();

    #ಆದರೆ ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        ಆದರೆ( pvReturn == ಖಾಲಿ )
        {
            vApplicationMallocFailedHook();
        }
    }
    #ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ pvReturn;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Free( ಶೂನ್ಯ * pv )
{
    /* Memory cannot be freed using this scheme.  See heap_2.c, heap_3.c and
     * heap_4.c for alternative implementations, and the memory management pages of
     * https://www.FreeRTOS.org for more information. */
    ( ಶೂನ್ಯ ) pv;

    /* Force an assert as it is invalid to call this function. */
    configASSERT( pv == ಖಾಲಿ );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Initialise_ಖಂಡಗಳು( ಶೂನ್ಯ )
{
    /* Only required when static memory is not cleared. */
    x_ಮುಂದಿನ_Free_Byte = ( size_t ) 0;
}
/*-----------------------------------------------------------*/

size_t x_ಪೋರ್ಟ್_Get_Free_ರಾಶಿ_ಗಾತ್ರ( ಶೂನ್ಯ )
{
    ಹಿಂತಿರುಗಿ( config_ADJUSTED_ರಾಶಿ_ಗಾತ್ರ - x_ಮುಂದಿನ_Free_Byte );
}

/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ರಾಶಿ_Reset_State( ಶೂನ್ಯ )
{
    x_ಮುಂದಿನ_Free_Byte = ( size_t ) 0U;
}
/*-----------------------------------------------------------*/
