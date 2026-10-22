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
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਢੇਰ_CLEAR_ਸਮ੍ਰਿਤੀ_ON_FREE
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ਢੇਰ_CLEAR_ਸਮ੍ਰਿਤੀ_ON_FREE    0
#ਜੇ_ਅੰਤ

/* A few bytes might be lost to byte aligning the heap start address. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_ADJUSTED_ਢੇਰ_ਮਾਪ    ( config_ਕੁੱਲ_ਢੇਰ_ਮਾਪ - ਪੋਰਟ_BYTE_ALIGNMENT )

/* Assumes 8bit bytes! */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਬਿੱਟ_ਪ੍ਰਤੀ_BYTE           ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਮਾਪ_MAX                ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_MULTIPLY_WILL_ਉਛਾਲ( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( ਢੇਰ_ਮਾਪ_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਜੋੜੋ_WILL_ਉਛਾਲ( a, b )         ( ( a ) > ( ਢੇਰ_ਮਾਪ_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਖੰਡ_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( ਆਕਾਰ( size_t ) * ਢੇਰ_ਬਿੱਟ_ਪ੍ਰਤੀ_BYTE ) - 1 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਖੰਡ_ਮਾਪ_IS_VALID( x_ਖੰਡ_ਮਾਪ )    ( ( ( x_ਖੰਡ_ਮਾਪ ) & ਢੇਰ_ਖੰਡ_ALLOCATED_BITMASK ) == 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਖੰਡ_IS_ALLOCATED( px_ਖੰਡ )        ( ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ ) & ਢੇਰ_ਖੰਡ_ALLOCATED_BITMASK ) != 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ALLOCATE_ਖੰਡ( px_ਖੰਡ )            ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ ) |= ਢੇਰ_ਖੰਡ_ALLOCATED_BITMASK )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_FREE_ਖੰਡ( px_ਖੰਡ )                ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ ) &= ~ਢੇਰ_ਖੰਡ_ALLOCATED_BITMASK )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#ਜੇ ( config_APPLICATION_ALLOCATED_ਢੇਰ == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    ਬਾਹਰੀ uint8_t uc_ਢੇਰ[ config_ਕੁੱਲ_ਢੇਰ_ਮਾਪ ];
#ਨਹੀਂਤਾਂ
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ uint8_t uc_ਢੇਰ[ config_ਕੁੱਲ_ਢੇਰ_ਮਾਪ ];
#ਜੇ_ਅੰਤ /* configAPPLICATION_ALLOCATED_HEAP */


/* Define the linked list structure.  This is used to link free blocks in order
 * of their size. */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ A_ਖੰਡ_LINK
{
    ਬਣਤਰ A_ਖੰਡ_LINK * px_ਅਗਲਾ_Free_ਖੰਡ; /*<< The next free block in the list. */
    size_t x_ਖੰਡ_ਮਾਪ;                     /*<< The size of the free block. */
} ਖੰਡ_Link_t;


ਸਥਿਰ ਅਚਲ size_t x_ਢੇਰ_Struct_ਮਾਪ = ( ( ਆਕਾਰ( ਖੰਡ_Link_t ) + ( size_t ) ( ਪੋਰਟ_BYTE_ALIGNMENT - 1 ) ) & ~( ( size_t ) ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) );
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_MINIMUM_ਖੰਡ_ਮਾਪ    ( ( size_t ) ( x_ਢੇਰ_Struct_ਮਾਪ * 2 ) )

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ ਖੰਡ_Link_t x_ਸ਼ੁਰੂ, x_ਸਿਰਾ;

/* Keeps track of the number of free bytes remaining, but says nothing about
 * fragmentation. */
PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ size_t x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = config_ADJUSTED_ਢੇਰ_ਮਾਪ;

/* Indicates whether the heap has been initialised or not. */
PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ ਅਧਾਰ_Type_t x_ਢੇਰ_Has_Been_Initialised = pdFALSE;

/*-----------------------------------------------------------*/

/*
 * Initialises the heap structures before their first use.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਢੇਰ_Init( ਖਾਲੀ ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* STATIC FUNCTIONS ARE DEFINED AS MACROS TO MINIMIZE THE FUNCTION CALL DEPTH. */

/*
 * Insert a block into the list of free blocks - which is ordered by size of
 * the block.  Small blocks at the start of the list and large blocks at the end
 * of the list.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ prv_ਪਾਓ_ਖੰਡ_Into_Free_List( px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ )                                                                               \
    {                                                                                                                               \
        ਖੰਡ_Link_t * pxIterator;                                                                                                   \
        size_t x_ਖੰਡ_ਮਾਪ;                                                                                                          \
                                                                                                                                    \
        x_ਖੰਡ_ਮਾਪ = px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ->x_ਖੰਡ_ਮਾਪ;                                                                                   \
                                                                                                                                    \
        /* Iterate through the list until a block is found that has a larger size */                                                \
        /* than the block we are inserting. */                                                                                      \
        ਲਈ( pxIterator = &x_ਸ਼ੁਰੂ; pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ->x_ਖੰਡ_ਮਾਪ < x_ਖੰਡ_ਮਾਪ; pxIterator = pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ ) \
        {                                                                                                                           \
            /* There is nothing to do here - just iterate to the correct position. */                                               \
        }                                                                                                                           \
                                                                                                                                    \
        /* Update the list to include the block being inserted in the correct */                                                    \
        /* position. */                                                                                                             \
        px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ->px_ਅਗਲਾ_Free_ਖੰਡ = pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ;                                                             \
        pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ = px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ;                                                                              \
    }
/*-----------------------------------------------------------*/

ਖਾਲੀ * pv_ਪੋਰਟ_Malloc( size_t x_Wanted_ਮਾਪ )
{
    ਖੰਡ_Link_t * px_ਖੰਡ;
    ਖੰਡ_Link_t * px_ਪਿਛਲਾ_ਖੰਡ;
    ਖੰਡ_Link_t * px_New_ਖੰਡ_Link;
    ਖਾਲੀ * pvReturn = ਨਿਰਾ;
    size_t x_Additional_Required_ਮਾਪ;
    size_t x_Allocated_ਖੰਡ_ਮਾਪ = 0;

    ਜੇ( x_Wanted_ਮਾਪ > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        ਜੇ( ਢੇਰ_ਜੋੜੋ_WILL_ਉਛਾਲ( x_Wanted_ਮਾਪ, x_ਢੇਰ_Struct_ਮਾਪ ) == 0 )
        {
            x_Wanted_ਮਾਪ += x_ਢੇਰ_Struct_ਮਾਪ;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
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
            ਨਹੀਂਤਾਂ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ਨਹੀਂਤਾਂ
        {
            x_Wanted_ਮਾਪ = 0;
        }
    }
    ਨਹੀਂਤਾਂ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    vTaskSuspendAll();
    {
        /* If this is the first call to malloc then the heap will require
         * initialisation to setup the list of free blocks. */
        ਜੇ( x_ਢੇਰ_Has_Been_Initialised == pdFALSE )
        {
            prv_ਢੇਰ_Init();
            x_ਢੇਰ_Has_Been_Initialised = pdTRUE;
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        ਜੇ( ਢੇਰ_ਖੰਡ_ਮਾਪ_IS_VALID( x_Wanted_ਮਾਪ ) != 0 )
        {
            ਜੇ( ( x_Wanted_ਮਾਪ > 0 ) && ( x_Wanted_ਮਾਪ <= x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ ) )
            {
                /* Blocks are stored in byte order - traverse the list from the start
                 * (smallest) block until one of adequate size is found. */
                px_ਪਿਛਲਾ_ਖੰਡ = &x_ਸ਼ੁਰੂ;
                px_ਖੰਡ = x_ਸ਼ੁਰੂ.px_ਅਗਲਾ_Free_ਖੰਡ;

                ਜਦੋਂ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ < x_Wanted_ਮਾਪ ) && ( px_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ != ਨਿਰਾ ) )
                {
                    px_ਪਿਛਲਾ_ਖੰਡ = px_ਖੰਡ;
                    px_ਖੰਡ = px_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ;
                }

                /* If we found the end marker then a block of adequate size was not found. */
                ਜੇ( px_ਖੰਡ != &x_ਸਿਰਾ )
                {
                    /* Return the memory space - jumping over the BlockLink_t structure
                     * at its start. */
                    pvReturn = ( ਖਾਲੀ * ) ( ( ( uint8_t * ) px_ਪਿਛਲਾ_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ ) + x_ਢੇਰ_Struct_ਮਾਪ );

                    /* This block is being returned for use so must be taken out of the
                     * list of free blocks. */
                    px_ਪਿਛਲਾ_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ = px_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ;

                    /* If the block is larger than required it can be split into two. */
                    ਜੇ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ - x_Wanted_ਮਾਪ ) > ਢੇਰ_MINIMUM_ਖੰਡ_ਮਾਪ )
                    {
                        /* This block is to be split into two.  Create a new block
                         * following the number of bytes requested. The void cast is
                         * used to prevent byte alignment warnings from the compiler. */
                        px_New_ਖੰਡ_Link = ( ਖਾਲੀ * ) ( ( ( uint8_t * ) px_ਖੰਡ ) + x_Wanted_ਮਾਪ );

                        /* Calculate the sizes of two blocks split from the single
                         * block. */
                        px_New_ਖੰਡ_Link->x_ਖੰਡ_ਮਾਪ = px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ - x_Wanted_ਮਾਪ;
                        px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ = x_Wanted_ਮਾਪ;

                        /* Insert the new block into the list of free blocks.
                         * The list of free blocks is sorted by their size, we have to
                         * iterate to find the right place to insert new block. */
                        prv_ਪਾਓ_ਖੰਡ_Into_Free_List( ( px_New_ਖੰਡ_Link ) );
                    }

                    x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ -= px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ;

                    x_Allocated_ਖੰਡ_ਮਾਪ = px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    ਢੇਰ_ALLOCATE_ਖੰਡ( px_ਖੰਡ );
                    px_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ = ਨਿਰਾ;
                }
            }
        }

        traceMALLOC( pvReturn, x_Allocated_ਖੰਡ_ਮਾਪ );

        /* Prevent compiler warnings when trace macros are not used. */
        ( ਖਾਲੀ ) x_Allocated_ਖੰਡ_ਮਾਪ;
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
    uint8_t * puc = ( uint8_t * ) pv;
    ਖੰਡ_Link_t * pxLink;

    ਜੇ( pv != ਨਿਰਾ )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_ਢੇਰ_Struct_ਮਾਪ;

        /* This unexpected casting is to keep some compilers from issuing
         * byte alignment warnings. */
        pxLink = ( ਖਾਲੀ * ) puc;

        configASSERT( ਢੇਰ_ਖੰਡ_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_ਅਗਲਾ_Free_ਖੰਡ == ਨਿਰਾ );

        ਜੇ( ਢੇਰ_ਖੰਡ_IS_ALLOCATED( pxLink ) != 0 )
        {
            ਜੇ( pxLink->px_ਅਗਲਾ_Free_ਖੰਡ == ਨਿਰਾ )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                ਢੇਰ_FREE_ਖੰਡ( pxLink );
                #ਜੇ ( config_ਢੇਰ_CLEAR_ਸਮ੍ਰਿਤੀ_ON_FREE == 1 )
                {
                    ( ਖਾਲੀ ) memset( puc + x_ਢੇਰ_Struct_ਮਾਪ, 0, pxLink->x_ਖੰਡ_ਮਾਪ - x_ਢੇਰ_Struct_ਮਾਪ );
                }
                #ਜੇ_ਅੰਤ

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    prv_ਪਾਓ_ਖੰਡ_Into_Free_List( ( ( ਖੰਡ_Link_t * ) pxLink ) );
                    x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ += pxLink->x_ਖੰਡ_ਮਾਪ;
                    traceFREE( pv, pxLink->x_ਖੰਡ_ਮਾਪ );
                }
                ( ਖਾਲੀ ) xTaskResumeAll();
            }
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_ਪੋਰਟ_Get_Free_ਢੇਰ_ਮਾਪ( ਖਾਲੀ )
{
    ਵਾਪਸ x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Initialise_ਖੰਡਾਂ( ਖਾਲੀ )
{
    /* This just exists to keep the linker quiet. */
}
/*-----------------------------------------------------------*/

ਖਾਲੀ * pv_ਪੋਰਟ_Calloc( size_t x_ਅੰਕ,
                     size_t x_ਮਾਪ )
{
    ਖਾਲੀ * pv = ਨਿਰਾ;

    ਜੇ( ਢੇਰ_MULTIPLY_WILL_ਉਛਾਲ( x_ਅੰਕ, x_ਮਾਪ ) == 0 )
    {
        pv = pv_ਪੋਰਟ_Malloc( x_ਅੰਕ * x_ਮਾਪ );

        ਜੇ( pv != ਨਿਰਾ )
        {
            ( ਖਾਲੀ ) memset( pv, 0, x_ਅੰਕ * x_ਮਾਪ );
        }
    }

    ਵਾਪਸ pv;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਢੇਰ_Init( ਖਾਲੀ ) /* PRIVILEGED_FUNCTION */
{
    ਖੰਡ_Link_t * px_ਪਹਿਲਾ_Free_ਖੰਡ;
    uint8_t * puc_Aligned_ਢੇਰ;

    /* Ensure the heap starts on a correctly aligned boundary. */
    puc_Aligned_ਢੇਰ = ( uint8_t * ) ( ( ( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE ) & uc_ਢੇਰ[ ਪੋਰਟ_BYTE_ALIGNMENT - 1 ] ) & ( ~( ( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE ) ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) ) );

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_ਸ਼ੁਰੂ.px_ਅਗਲਾ_Free_ਖੰਡ = ( ਖਾਲੀ * ) puc_Aligned_ਢੇਰ;
    x_ਸ਼ੁਰੂ.x_ਖੰਡ_ਮਾਪ = ( size_t ) 0;

    /* xEnd is used to mark the end of the list of free blocks. */
    x_ਸਿਰਾ.x_ਖੰਡ_ਮਾਪ = config_ADJUSTED_ਢੇਰ_ਮਾਪ;
    x_ਸਿਰਾ.px_ਅਗਲਾ_Free_ਖੰਡ = ਨਿਰਾ;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space. */
    px_ਪਹਿਲਾ_Free_ਖੰਡ = ( ਖੰਡ_Link_t * ) puc_Aligned_ਢੇਰ;
    px_ਪਹਿਲਾ_Free_ਖੰਡ->x_ਖੰਡ_ਮਾਪ = config_ADJUSTED_ਢੇਰ_ਮਾਪ;
    px_ਪਹਿਲਾ_Free_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ = &x_ਸਿਰਾ;
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
ਖਾਲੀ v_ਪੋਰਟ_ਢੇਰ_Reset_State( ਖਾਲੀ )
{
    x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = config_ADJUSTED_ਢੇਰ_ਮਾਪ;

    x_ਢੇਰ_Has_Been_Initialised = pdFALSE;
}
/*-----------------------------------------------------------*/
