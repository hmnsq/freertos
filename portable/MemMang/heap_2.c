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
 * A sample implementation of pvPortMalloc() and vPortFree() that permits
 * allocated blocks to be freed, but does not combine adjacent free blocks
 * into a single larger block (and so will fragment memory).  See heap_4.c for
 * an equivalent that does combine adjacent blocks into single larger blocks.
 *
 * See heap_1.c, heap_3.c and heap_4.c for alternative implementations, and the
 * memory management pages of https://www.FreeRTOS.org for more information.
 */
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ರಾಶಿ_CLEAR_ಸ್ಮರಣೆ_ON_FREE
    #ವ್ಯಾಖ್ಯಾನಿಸು config_ರಾಶಿ_CLEAR_ಸ್ಮರಣೆ_ON_FREE    0
#ಆದರೆ_ಅಂತ್ಯ

/* A few bytes might be lost to byte aligning the heap start address. */
#ವ್ಯಾಖ್ಯಾನಿಸು config_ADJUSTED_ರಾಶಿ_ಗಾತ್ರ    ( config_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ - ಪೋರ್ಟ್_BYTE_ALIGNMENT )

/* Assumes 8bit bytes! */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_BYTE           ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಗಾತ್ರ_MAX                ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_MULTIPLY_WILL_ಅತಿಪ್ರವಾಹ( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( ರಾಶಿ_ಗಾತ್ರ_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಕೂಡಿಸು_WILL_ಅತಿಪ್ರವಾಹ( a, b )         ( ( a ) > ( ರಾಶಿ_ಗಾತ್ರ_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಖಂಡ_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( ಗಾತ್ರ( size_t ) * ರಾಶಿ_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_BYTE ) - 1 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಖಂಡ_ಗಾತ್ರ_IS_VALID( x_ಖಂಡ_ಗಾತ್ರ )    ( ( ( x_ಖಂಡ_ಗಾತ್ರ ) & ರಾಶಿ_ಖಂಡ_ALLOCATED_BITMASK ) == 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಖಂಡ_IS_ALLOCATED( px_ಖಂಡ )        ( ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ ) & ರಾಶಿ_ಖಂಡ_ALLOCATED_BITMASK ) != 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ALLOCATE_ಖಂಡ( px_ಖಂಡ )            ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ ) |= ರಾಶಿ_ಖಂಡ_ALLOCATED_BITMASK )
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_FREE_ಖಂಡ( px_ಖಂಡ )                ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ ) &= ~ರಾಶಿ_ಖಂಡ_ALLOCATED_BITMASK )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#ಆದರೆ ( config_APPLICATION_ALLOCATED_ರಾಶಿ == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    ಬಾಹ್ಯ uint8_t uc_ರಾಶಿ[ config_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ ];
#ಇಲ್ಲದಿದ್ದರೆ
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ uint8_t uc_ರಾಶಿ[ config_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ ];
#ಆದರೆ_ಅಂತ್ಯ /* configAPPLICATION_ALLOCATED_HEAP */


/* Define the linked list structure.  This is used to link free blocks in order
 * of their size. */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ A_ಖಂಡ_LINK
{
    ರಚನೆ A_ಖಂಡ_LINK * px_ಮುಂದಿನ_Free_ಖಂಡ; /*<< The next free block in the list. */
    size_t x_ಖಂಡ_ಗಾತ್ರ;                     /*<< The size of the free block. */
} ಖಂಡ_Link_t;


ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ size_t x_ರಾಶಿ_Struct_ಗಾತ್ರ = ( ( ಗಾತ್ರ( ಖಂಡ_Link_t ) + ( size_t ) ( ಪೋರ್ಟ್_BYTE_ALIGNMENT - 1 ) ) & ~( ( size_t ) ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) );
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_MINIMUM_ಖಂಡ_ಗಾತ್ರ    ( ( size_t ) ( x_ರಾಶಿ_Struct_ಗಾತ್ರ * 2 ) )

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ ಖಂಡ_Link_t x_ಆರಂಭ, x_ಕೊನೆ;

/* Keeps track of the number of free bytes remaining, but says nothing about
 * fragmentation. */
PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ size_t x_Free_ಬೈಟುಗಳು_ಉಳಿದ = config_ADJUSTED_ರಾಶಿ_ಗಾತ್ರ;

/* Indicates whether the heap has been initialised or not. */
PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ ತಳ_Type_t x_ರಾಶಿ_Has_Been_Initialised = pdFALSE;

/*-----------------------------------------------------------*/

/*
 * Initialises the heap structures before their first use.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ರಾಶಿ_Init( ಶೂನ್ಯ ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* STATIC FUNCTIONS ARE DEFINED AS MACROS TO MINIMIZE THE FUNCTION CALL DEPTH. */

/*
 * Insert a block into the list of free blocks - which is ordered by size of
 * the block.  Small blocks at the start of the list and large blocks at the end
 * of the list.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು prv_ಸೇರಿಸು_ಖಂಡ_Into_Free_List( px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು )                                                                               \
    {                                                                                                                               \
        ಖಂಡ_Link_t * pxIterator;                                                                                                   \
        size_t x_ಖಂಡ_ಗಾತ್ರ;                                                                                                          \
                                                                                                                                    \
        x_ಖಂಡ_ಗಾತ್ರ = px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು->x_ಖಂಡ_ಗಾತ್ರ;                                                                                   \
                                                                                                                                    \
        /* Iterate through the list until a block is found that has a larger size */                                                \
        /* than the block we are inserting. */                                                                                      \
        ಗಾಗಿ( pxIterator = &x_ಆರಂಭ; pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ < x_ಖಂಡ_ಗಾತ್ರ; pxIterator = pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ ) \
        {                                                                                                                           \
            /* There is nothing to do here - just iterate to the correct position. */                                               \
        }                                                                                                                           \
                                                                                                                                    \
        /* Update the list to include the block being inserted in the correct */                                                    \
        /* position. */                                                                                                             \
        px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು->px_ಮುಂದಿನ_Free_ಖಂಡ = pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ;                                                             \
        pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ = px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು;                                                                              \
    }
/*-----------------------------------------------------------*/

ಶೂನ್ಯ * pv_ಪೋರ್ಟ್_Malloc( size_t x_Wanted_ಗಾತ್ರ )
{
    ಖಂಡ_Link_t * px_ಖಂಡ;
    ಖಂಡ_Link_t * px_ಹಿಂದಿನ_ಖಂಡ;
    ಖಂಡ_Link_t * px_New_ಖಂಡ_Link;
    ಶೂನ್ಯ * pvReturn = ಖಾಲಿ;
    size_t x_Additional_Required_ಗಾತ್ರ;
    size_t x_Allocated_ಖಂಡ_ಗಾತ್ರ = 0;

    ಆದರೆ( x_Wanted_ಗಾತ್ರ > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        ಆದರೆ( ರಾಶಿ_ಕೂಡಿಸು_WILL_ಅತಿಪ್ರವಾಹ( x_Wanted_ಗಾತ್ರ, x_ರಾಶಿ_Struct_ಗಾತ್ರ ) == 0 )
        {
            x_Wanted_ಗಾತ್ರ += x_ರಾಶಿ_Struct_ಗಾತ್ರ;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
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
            ಇಲ್ಲದಿದ್ದರೆ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            x_Wanted_ಗಾತ್ರ = 0;
        }
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    vTaskSuspendAll();
    {
        /* If this is the first call to malloc then the heap will require
         * initialisation to setup the list of free blocks. */
        ಆದರೆ( x_ರಾಶಿ_Has_Been_Initialised == pdFALSE )
        {
            prv_ರಾಶಿ_Init();
            x_ರಾಶಿ_Has_Been_Initialised = pdTRUE;
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        ಆದರೆ( ರಾಶಿ_ಖಂಡ_ಗಾತ್ರ_IS_VALID( x_Wanted_ಗಾತ್ರ ) != 0 )
        {
            ಆದರೆ( ( x_Wanted_ಗಾತ್ರ > 0 ) && ( x_Wanted_ಗಾತ್ರ <= x_Free_ಬೈಟುಗಳು_ಉಳಿದ ) )
            {
                /* Blocks are stored in byte order - traverse the list from the start
                 * (smallest) block until one of adequate size is found. */
                px_ಹಿಂದಿನ_ಖಂಡ = &x_ಆರಂಭ;
                px_ಖಂಡ = x_ಆರಂಭ.px_ಮುಂದಿನ_Free_ಖಂಡ;

                ಆಗ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ < x_Wanted_ಗಾತ್ರ ) && ( px_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ != ಖಾಲಿ ) )
                {
                    px_ಹಿಂದಿನ_ಖಂಡ = px_ಖಂಡ;
                    px_ಖಂಡ = px_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ;
                }

                /* If we found the end marker then a block of adequate size was not found. */
                ಆದರೆ( px_ಖಂಡ != &x_ಕೊನೆ )
                {
                    /* Return the memory space - jumping over the BlockLink_t structure
                     * at its start. */
                    pvReturn = ( ಶೂನ್ಯ * ) ( ( ( uint8_t * ) px_ಹಿಂದಿನ_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ ) + x_ರಾಶಿ_Struct_ಗಾತ್ರ );

                    /* This block is being returned for use so must be taken out of the
                     * list of free blocks. */
                    px_ಹಿಂದಿನ_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ = px_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ;

                    /* If the block is larger than required it can be split into two. */
                    ಆದರೆ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ - x_Wanted_ಗಾತ್ರ ) > ರಾಶಿ_MINIMUM_ಖಂಡ_ಗಾತ್ರ )
                    {
                        /* This block is to be split into two.  Create a new block
                         * following the number of bytes requested. The void cast is
                         * used to prevent byte alignment warnings from the compiler. */
                        px_New_ಖಂಡ_Link = ( ಶೂನ್ಯ * ) ( ( ( uint8_t * ) px_ಖಂಡ ) + x_Wanted_ಗಾತ್ರ );

                        /* Calculate the sizes of two blocks split from the single
                         * block. */
                        px_New_ಖಂಡ_Link->x_ಖಂಡ_ಗಾತ್ರ = px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ - x_Wanted_ಗಾತ್ರ;
                        px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ = x_Wanted_ಗಾತ್ರ;

                        /* Insert the new block into the list of free blocks.
                         * The list of free blocks is sorted by their size, we have to
                         * iterate to find the right place to insert new block. */
                        prv_ಸೇರಿಸು_ಖಂಡ_Into_Free_List( ( px_New_ಖಂಡ_Link ) );
                    }

                    x_Free_ಬೈಟುಗಳು_ಉಳಿದ -= px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ;

                    x_Allocated_ಖಂಡ_ಗಾತ್ರ = px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    ರಾಶಿ_ALLOCATE_ಖಂಡ( px_ಖಂಡ );
                    px_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ = ಖಾಲಿ;
                }
            }
        }

        traceMALLOC( pvReturn, x_Allocated_ಖಂಡ_ಗಾತ್ರ );

        /* Prevent compiler warnings when trace macros are not used. */
        ( ಶೂನ್ಯ ) x_Allocated_ಖಂಡ_ಗಾತ್ರ;
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
    uint8_t * puc = ( uint8_t * ) pv;
    ಖಂಡ_Link_t * pxLink;

    ಆದರೆ( pv != ಖಾಲಿ )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_ರಾಶಿ_Struct_ಗಾತ್ರ;

        /* This unexpected casting is to keep some compilers from issuing
         * byte alignment warnings. */
        pxLink = ( ಶೂನ್ಯ * ) puc;

        configASSERT( ರಾಶಿ_ಖಂಡ_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_ಮುಂದಿನ_Free_ಖಂಡ == ಖಾಲಿ );

        ಆದರೆ( ರಾಶಿ_ಖಂಡ_IS_ALLOCATED( pxLink ) != 0 )
        {
            ಆದರೆ( pxLink->px_ಮುಂದಿನ_Free_ಖಂಡ == ಖಾಲಿ )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                ರಾಶಿ_FREE_ಖಂಡ( pxLink );
                #ಆದರೆ ( config_ರಾಶಿ_CLEAR_ಸ್ಮರಣೆ_ON_FREE == 1 )
                {
                    ( ಶೂನ್ಯ ) memset( puc + x_ರಾಶಿ_Struct_ಗಾತ್ರ, 0, pxLink->x_ಖಂಡ_ಗಾತ್ರ - x_ರಾಶಿ_Struct_ಗಾತ್ರ );
                }
                #ಆದರೆ_ಅಂತ್ಯ

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    prv_ಸೇರಿಸು_ಖಂಡ_Into_Free_List( ( ( ಖಂಡ_Link_t * ) pxLink ) );
                    x_Free_ಬೈಟುಗಳು_ಉಳಿದ += pxLink->x_ಖಂಡ_ಗಾತ್ರ;
                    traceFREE( pv, pxLink->x_ಖಂಡ_ಗಾತ್ರ );
                }
                ( ಶೂನ್ಯ ) xTaskResumeAll();
            }
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_ಪೋರ್ಟ್_Get_Free_ರಾಶಿ_ಗಾತ್ರ( ಶೂನ್ಯ )
{
    ಹಿಂತಿರುಗಿ x_Free_ಬೈಟುಗಳು_ಉಳಿದ;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Initialise_ಖಂಡಗಳು( ಶೂನ್ಯ )
{
    /* This just exists to keep the linker quiet. */
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ * pv_ಪೋರ್ಟ್_Calloc( size_t x_ಅಂಕೆ,
                     size_t x_ಗಾತ್ರ )
{
    ಶೂನ್ಯ * pv = ಖಾಲಿ;

    ಆದರೆ( ರಾಶಿ_MULTIPLY_WILL_ಅತಿಪ್ರವಾಹ( x_ಅಂಕೆ, x_ಗಾತ್ರ ) == 0 )
    {
        pv = pv_ಪೋರ್ಟ್_Malloc( x_ಅಂಕೆ * x_ಗಾತ್ರ );

        ಆದರೆ( pv != ಖಾಲಿ )
        {
            ( ಶೂನ್ಯ ) memset( pv, 0, x_ಅಂಕೆ * x_ಗಾತ್ರ );
        }
    }

    ಹಿಂತಿರುಗಿ pv;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ರಾಶಿ_Init( ಶೂನ್ಯ ) /* PRIVILEGED_FUNCTION */
{
    ಖಂಡ_Link_t * px_ಮೊದಲ_Free_ಖಂಡ;
    uint8_t * puc_Aligned_ರಾಶಿ;

    /* Ensure the heap starts on a correctly aligned boundary. */
    puc_Aligned_ರಾಶಿ = ( uint8_t * ) ( ( ( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE ) & uc_ರಾಶಿ[ ಪೋರ್ಟ್_BYTE_ALIGNMENT - 1 ] ) & ( ~( ( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE ) ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) ) );

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_ಆರಂಭ.px_ಮುಂದಿನ_Free_ಖಂಡ = ( ಶೂನ್ಯ * ) puc_Aligned_ರಾಶಿ;
    x_ಆರಂಭ.x_ಖಂಡ_ಗಾತ್ರ = ( size_t ) 0;

    /* xEnd is used to mark the end of the list of free blocks. */
    x_ಕೊನೆ.x_ಖಂಡ_ಗಾತ್ರ = config_ADJUSTED_ರಾಶಿ_ಗಾತ್ರ;
    x_ಕೊನೆ.px_ಮುಂದಿನ_Free_ಖಂಡ = ಖಾಲಿ;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space. */
    px_ಮೊದಲ_Free_ಖಂಡ = ( ಖಂಡ_Link_t * ) puc_Aligned_ರಾಶಿ;
    px_ಮೊದಲ_Free_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ = config_ADJUSTED_ರಾಶಿ_ಗಾತ್ರ;
    px_ಮೊದಲ_Free_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ = &x_ಕೊನೆ;
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ರಾಶಿ_Reset_State( ಶೂನ್ಯ )
{
    x_Free_ಬೈಟುಗಳು_ಉಳಿದ = config_ADJUSTED_ರಾಶಿ_ಗಾತ್ರ;

    x_ರಾಶಿ_Has_Been_Initialised = pdFALSE;
}
/*-----------------------------------------------------------*/
