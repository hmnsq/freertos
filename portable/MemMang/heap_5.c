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
 * A sample implementation of pvPortMalloc() that allows the heap to be defined
 * across multiple non-contiguous blocks and combines (coalescences) adjacent
 * memory blocks as they are freed.
 *
 * See heap_1.c, heap_2.c, heap_3.c and heap_4.c for alternative
 * implementations, and the memory management pages of https://www.FreeRTOS.org
 * for more information.
 *
 * Usage notes:
 *
 * vPortDefineHeapRegions() ***must*** be called before pvPortMalloc().
 * pvPortMalloc() will be called if any task objects (tasks, queues, event
 * groups, etc.) are created, therefore vPortDefineHeapRegions() ***must*** be
 * called before any other objects are defined.
 *
 * vPortDefineHeapRegions() takes a single parameter.  The parameter is an array
 * of HeapRegion_t structures.  HeapRegion_t is defined in portable.h as
 *
 * typedef struct HeapRegion
 * {
 *  uint8_t *pucStartAddress; << Start address of a block of memory that will be part of the heap.
 *  size_t xSizeInBytes;      << Size of the block of memory.
 * } HeapRegion_t;
 *
 * The array is terminated using a NULL zero sized region definition, and the
 * memory regions defined in the array ***must*** appear in address order from
 * low address to high address.  So the following is a valid example of how
 * to use the function.
 *
 * HeapRegion_t xHeapRegions[] =
 * {
 *  { ( uint8_t * ) 0x80000000UL, 0x10000 }, << Defines a block of 0x10000 bytes starting at address 0x80000000
 *  { ( uint8_t * ) 0x90000000UL, 0xa0000 }, << Defines a block of 0xa0000 bytes starting at address of 0x90000000
 *  { NULL, 0 }                << Terminates the array.
 * };
 *
 * vPortDefineHeapRegions( xHeapRegions ); << Pass the array into vPortDefineHeapRegions().
 *
 * Note 0x80000000 is the lower address so appears in the array first.
 *
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

/* Block sizes must not get too small. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_MINIMUM_ਖੰਡ_ਮਾਪ    ( ( size_t ) ( x_ਢੇਰ_Struct_ਮਾਪ << 1 ) )

/* Assumes 8bit bytes! */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਬਿੱਟ_ਪ੍ਰਤੀ_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਮਾਪ_MAX              ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_MULTIPLY_WILL_ਉਛਾਲ( a, b )     ( ( ( a ) > 0 ) && ( ( b ) > ( ਢੇਰ_ਮਾਪ_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਜੋੜੋ_WILL_ਉਛਾਲ( a, b )          ( ( a ) > ( ਢੇਰ_ਮਾਪ_MAX - ( b ) ) )

/* Check if the subtraction operation ( a - b ) will result in underflow. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਘਟਾਓ_WILL_UNDERFLOW( a, b )    ( ( a ) < ( b ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਖੰਡ_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( ਆਕਾਰ( size_t ) * ਢੇਰ_ਬਿੱਟ_ਪ੍ਰਤੀ_BYTE ) - 1 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਖੰਡ_ਮਾਪ_IS_VALID( x_ਖੰਡ_ਮਾਪ )    ( ( ( x_ਖੰਡ_ਮਾਪ ) & ਢੇਰ_ਖੰਡ_ALLOCATED_BITMASK ) == 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ਖੰਡ_IS_ALLOCATED( px_ਖੰਡ )        ( ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ ) & ਢੇਰ_ਖੰਡ_ALLOCATED_BITMASK ) != 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_ALLOCATE_ਖੰਡ( px_ਖੰਡ )            ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ ) |= ਢੇਰ_ਖੰਡ_ALLOCATED_BITMASK )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_FREE_ਖੰਡ( px_ਖੰਡ )                ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ ) &= ~ਢੇਰ_ਖੰਡ_ALLOCATED_BITMASK )

/* Setting configENABLE_HEAP_PROTECTOR to 1 enables heap block pointers
 * protection using an application supplied canary value to catch heap
 * corruption should a heap buffer overflow occur.
 */
#ਜੇ ( config_ENABLE_ਢੇਰ_PROTECTOR == 1 )

/* Macro to load/store BlockLink_t pointers to memory. By XORing the
 * pointers with a random canary value, heap overflows will result
 * in randomly unpredictable pointer values which will be caught by
 * heapVALIDATE_BLOCK_POINTER assert. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( px_ਖੰਡ )    ( ( ਖੰਡ_Link_t * ) ( ( ( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE ) ( px_ਖੰਡ ) ) ^ x_ਢੇਰ_Canary ) )

/* Assert that a heap block pointer is within the heap bounds.
 * Setting configVALIDATE_HEAP_BLOCK_POINTER to 1 enables customized heap block pointers
 * protection on heap_5. */
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_VALIDATE_ਢੇਰ_ਖੰਡ_ਸੂਚਕ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_VALIDATE_ਖੰਡ_ਸੂਚਕ( px_ਖੰਡ )                           \
            configASSERT( ( puc_ਢੇਰ_ਉੱਚਾ_ਪਤਾ != ਨਿਰਾ ) &&                     \
                          ( puc_ਢੇਰ_ਨੀਵਾਂ_ਪਤਾ != ਨਿਰਾ ) &&                      \
                          ( ( uint8_t * ) ( px_ਖੰਡ ) >= puc_ਢੇਰ_ਨੀਵਾਂ_ਪਤਾ ) && \
                          ( ( uint8_t * ) ( px_ਖੰਡ ) < puc_ਢੇਰ_ਉੱਚਾ_ਪਤਾ ) )
    #ਨਹੀਂਤਾਂ /* ifndef configVALIDATE_HEAP_BLOCK_POINTER */
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_VALIDATE_ਖੰਡ_ਸੂਚਕ( px_ਖੰਡ )                           \
            config_VALIDATE_ਢੇਰ_ਖੰਡ_ਸੂਚਕ( px_ਖੰਡ )
    #ਜੇ_ਅੰਤ /* configVALIDATE_HEAP_BLOCK_POINTER */

#ਨਹੀਂਤਾਂ /* if ( configENABLE_HEAP_PROTECTOR == 1 ) */

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( px_ਖੰਡ )    ( px_ਖੰਡ )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਢੇਰ_VALIDATE_ਖੰਡ_ਸੂਚਕ( px_ਖੰਡ )

#ਜੇ_ਅੰਤ /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

/* Define the linked list structure.  This is used to link free blocks in order
 * of their memory address. */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ A_ਖੰਡ_LINK
{
    ਬਣਤਰ A_ਖੰਡ_LINK * px_ਅਗਲਾ_Free_ਖੰਡ; /**< The next free block in the list. */
    size_t x_ਖੰਡ_ਮਾਪ;                     /**< The size of the free block. */
} ਖੰਡ_Link_t;

/*-----------------------------------------------------------*/

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਪਾਓ_ਖੰਡ_Into_Free_List( ਖੰਡ_Link_t * px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ ) PRIVILEGED_FUNCTION;
ਖਾਲੀ v_ਪੋਰਟ_Define_ਢੇਰ_Regions( ਅਚਲ ਢੇਰ_Region_t * ਅਚਲ px_ਢੇਰ_Regions ) PRIVILEGED_FUNCTION;

#ਜੇ ( config_ENABLE_ਢੇਰ_PROTECTOR == 1 )

/**
 * @brief Application provided function to get a random value to be used as canary.
 *
 * @param pxHeapCanary [out] Output parameter to return the canary value.
 */
    ਬਾਹਰੀ ਖਾਲੀ v_Application_Get_Random_ਢੇਰ_Canary( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE * px_ਢੇਰ_Canary );
#ਜੇ_ਅੰਤ /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

/* The size of the structure placed at the beginning of each allocated memory
 * block must by correctly byte aligned. */
ਸਥਿਰ ਅਚਲ size_t x_ਢੇਰ_Struct_ਮਾਪ = ( ਆਕਾਰ( ਖੰਡ_Link_t ) + ( ( size_t ) ( ਪੋਰਟ_BYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ );

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ ਖੰਡ_Link_t x_ਸ਼ੁਰੂ;
PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ ਖੰਡ_Link_t * px_ਸਿਰਾ = ਨਿਰਾ;

/* Keeps track of the number of calls to allocate and free memory as well as the
 * number of free bytes remaining, but says nothing about fragmentation. */
PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ size_t x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = ( size_t ) 0U;
PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ size_t x_Minimum_Ever_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = ( size_t ) 0U;
PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ size_t x_ਸੰਖਿਆ_ਦਾ_Successful_Allocations = ( size_t ) 0U;
PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ size_t x_ਸੰਖਿਆ_ਦਾ_Successful_Frees = ( size_t ) 0U;

#ਜੇ ( config_ENABLE_ਢੇਰ_PROTECTOR == 1 )

/* Canary value for protecting internal heap pointers. */
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE x_ਢੇਰ_Canary;

/* Highest and lowest heap addresses used for heap block bounds checking. */
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ uint8_t * puc_ਢੇਰ_ਉੱਚਾ_ਪਤਾ = ਨਿਰਾ;
    PRIVILEGED_ਅੰਕੜੇ ਸਥਿਰ uint8_t * puc_ਢੇਰ_ਨੀਵਾਂ_ਪਤਾ = ਨਿਰਾ;

#ਜੇ_ਅੰਤ /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

ਖਾਲੀ * pv_ਪੋਰਟ_Malloc( size_t x_Wanted_ਮਾਪ )
{
    ਖੰਡ_Link_t * px_ਖੰਡ;
    ਖੰਡ_Link_t * px_ਪਿਛਲਾ_ਖੰਡ;
    ਖੰਡ_Link_t * px_New_ਖੰਡ_Link;
    ਖਾਲੀ * pvReturn = ਨਿਰਾ;
    size_t x_Additional_Required_ਮਾਪ;
    size_t x_Allocated_ਖੰਡ_ਮਾਪ = 0;

    /* The heap must be initialised before the first call to
     * pvPortMalloc(). */
    configASSERT( px_ਸਿਰਾ );

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
        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        ਜੇ( ਢੇਰ_ਖੰਡ_ਮਾਪ_IS_VALID( x_Wanted_ਮਾਪ ) != 0 )
        {
            ਜੇ( ( x_Wanted_ਮਾਪ > 0 ) && ( x_Wanted_ਮਾਪ <= x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ ) )
            {
                /* Traverse the list from the start (lowest address) block until
                 * one of adequate size is found. */
                px_ਪਿਛਲਾ_ਖੰਡ = &x_ਸ਼ੁਰੂ;
                px_ਖੰਡ = ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( x_ਸ਼ੁਰੂ.px_ਅਗਲਾ_Free_ਖੰਡ );
                ਢੇਰ_VALIDATE_ਖੰਡ_ਸੂਚਕ( px_ਖੰਡ );

                ਜਦੋਂ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ < x_Wanted_ਮਾਪ ) && ( px_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ != ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( ਨਿਰਾ ) ) )
                {
                    px_ਪਿਛਲਾ_ਖੰਡ = px_ਖੰਡ;
                    px_ਖੰਡ = ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( px_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ );

                    /* pxEnd is the end marker of the free list. It is located at
                     * pucHeapHighAddress and is not part of the usable heap, so it
                     * must be excluded from the heap block pointer validation. */
                    ਜੇ( px_ਖੰਡ != px_ਸਿਰਾ )
                    {
                        ਢੇਰ_VALIDATE_ਖੰਡ_ਸੂਚਕ( px_ਖੰਡ );
                    }
                }

                /* If the end marker was reached then a block of adequate size
                 * was not found. */
                ਜੇ( px_ਖੰਡ != px_ਸਿਰਾ )
                {
                    /* Return the memory space pointed to - jumping over the
                     * BlockLink_t structure at its start. */
                    pvReturn = ( ਖਾਲੀ * ) ( ( ( uint8_t * ) ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( px_ਪਿਛਲਾ_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ ) ) + x_ਢੇਰ_Struct_ਮਾਪ );
                    ਢੇਰ_VALIDATE_ਖੰਡ_ਸੂਚਕ( pvReturn );

                    /* This block is being returned for use so must be taken out
                     * of the list of free blocks. */
                    px_ਪਿਛਲਾ_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ = px_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ;

                    /* If the block is larger than required it can be split into
                     * two. */
                    configASSERT( ਢੇਰ_ਘਟਾਓ_WILL_UNDERFLOW( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ, x_Wanted_ਮਾਪ ) == 0 );

                    ਜੇ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ - x_Wanted_ਮਾਪ ) > ਢੇਰ_MINIMUM_ਖੰਡ_ਮਾਪ )
                    {
                        /* This block is to be split into two.  Create a new
                         * block following the number of bytes requested. The void
                         * cast is used to prevent byte alignment warnings from the
                         * compiler. */
                        px_New_ਖੰਡ_Link = ( ਖਾਲੀ * ) ( ( ( uint8_t * ) px_ਖੰਡ ) + x_Wanted_ਮਾਪ );
                        configASSERT( ( ( ( size_t ) px_New_ਖੰਡ_Link ) & ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) == 0 );

                        /* Calculate the sizes of two blocks split from the
                         * single block. */
                        px_New_ਖੰਡ_Link->x_ਖੰਡ_ਮਾਪ = px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ - x_Wanted_ਮਾਪ;
                        px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ = x_Wanted_ਮਾਪ;

                        /* Insert the new block into the list of free blocks. */
                        px_New_ਖੰਡ_Link->px_ਅਗਲਾ_Free_ਖੰਡ = px_ਪਿਛਲਾ_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ;
                        px_ਪਿਛਲਾ_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ = ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( px_New_ਖੰਡ_Link );
                    }
                    ਨਹੀਂਤਾਂ
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ -= px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ;

                    ਜੇ( x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ < x_Minimum_Ever_Free_ਬਾਈਟਾਂ_ਬਚਿਆ )
                    {
                        x_Minimum_Ever_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ;
                    }
                    ਨਹੀਂਤਾਂ
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Allocated_ਖੰਡ_ਮਾਪ = px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    ਢੇਰ_ALLOCATE_ਖੰਡ( px_ਖੰਡ );
                    px_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ = ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( ਨਿਰਾ );
                    x_ਸੰਖਿਆ_ਦਾ_Successful_Allocations++;
                }
                ਨਹੀਂਤਾਂ
                {
                    mtCOVERAGE_TEST_MARKER();
                }
            }
            ਨਹੀਂਤਾਂ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ਨਹੀਂਤਾਂ
        {
            mtCOVERAGE_TEST_MARKER();
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
        ਨਹੀਂਤਾਂ
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #ਜੇ_ਅੰਤ /* if ( configUSE_MALLOC_FAILED_HOOK == 1 ) */

    configASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) == 0 );
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

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( ਖਾਲੀ * ) puc;

        ਢੇਰ_VALIDATE_ਖੰਡ_ਸੂਚਕ( pxLink );
        configASSERT( ਢੇਰ_ਖੰਡ_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_ਅਗਲਾ_Free_ਖੰਡ == ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( ਨਿਰਾ ) );

        ਜੇ( ਢੇਰ_ਖੰਡ_IS_ALLOCATED( pxLink ) != 0 )
        {
            ਜੇ( pxLink->px_ਅਗਲਾ_Free_ਖੰਡ == ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( ਨਿਰਾ ) )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                ਢੇਰ_FREE_ਖੰਡ( pxLink );
                #ਜੇ ( config_ਢੇਰ_CLEAR_ਸਮ੍ਰਿਤੀ_ON_FREE == 1 )
                {
                    /* Check for underflow as this can occur if xBlockSize is
                     * overwritten in a heap block. */
                    ਜੇ( ਢੇਰ_ਘਟਾਓ_WILL_UNDERFLOW( pxLink->x_ਖੰਡ_ਮਾਪ, x_ਢੇਰ_Struct_ਮਾਪ ) == 0 )
                    {
                        ( ਖਾਲੀ ) memset( puc + x_ਢੇਰ_Struct_ਮਾਪ, 0, pxLink->x_ਖੰਡ_ਮਾਪ - x_ਢੇਰ_Struct_ਮਾਪ );
                    }
                }
                #ਜੇ_ਅੰਤ

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ += pxLink->x_ਖੰਡ_ਮਾਪ;
                    traceFREE( pv, pxLink->x_ਖੰਡ_ਮਾਪ );
                    prv_ਪਾਓ_ਖੰਡ_Into_Free_List( ( ( ਖੰਡ_Link_t * ) pxLink ) );
                    x_ਸੰਖਿਆ_ਦਾ_Successful_Frees++;
                }
                ( ਖਾਲੀ ) xTaskResumeAll();
            }
            ਨਹੀਂਤਾਂ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ਨਹੀਂਤਾਂ
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_ਪੋਰਟ_Get_Free_ਢੇਰ_ਮਾਪ( ਖਾਲੀ )
{
    ਵਾਪਸ x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ;
}
/*-----------------------------------------------------------*/

size_t x_ਪੋਰਟ_Get_Minimum_Ever_Free_ਢੇਰ_ਮਾਪ( ਖਾਲੀ )
{
    ਵਾਪਸ x_Minimum_Ever_Free_ਬਾਈਟਾਂ_ਬਚਿਆ;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ x_ਪੋਰਟ_Reset_ਢੇਰ_Minimum_Ever_Free_ਢੇਰ_ਮਾਪ( ਖਾਲੀ )
{
    x_Minimum_Ever_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ;
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

ਸਥਿਰ ਖਾਲੀ prv_ਪਾਓ_ਖੰਡ_Into_Free_List( ਖੰਡ_Link_t * px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ ) /* PRIVILEGED_FUNCTION */
{
    ਖੰਡ_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    ਲਈ( pxIterator = &x_ਸ਼ੁਰੂ; ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ ) < px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ; pxIterator = ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ ) )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    ਜੇ( pxIterator != &x_ਸ਼ੁਰੂ )
    {
        ਢੇਰ_VALIDATE_ਖੰਡ_ਸੂਚਕ( pxIterator );
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    ਜੇ( ( puc + pxIterator->x_ਖੰਡ_ਮਾਪ ) == ( uint8_t * ) px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ )
    {
        pxIterator->x_ਖੰਡ_ਮਾਪ += px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ->x_ਖੰਡ_ਮਾਪ;
        px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ = pxIterator;
    }
    ਨਹੀਂਤਾਂ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ;

    ਜੇ( ( puc + px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ->x_ਖੰਡ_ਮਾਪ ) == ( uint8_t * ) ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ ) )
    {
        ਜੇ( ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ ) != px_ਸਿਰਾ )
        {
            /* Form one big block from the two blocks. */
            px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ->x_ਖੰਡ_ਮਾਪ += ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ )->x_ਖੰਡ_ਮਾਪ;
            px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ->px_ਅਗਲਾ_Free_ਖੰਡ = ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ )->px_ਅਗਲਾ_Free_ਖੰਡ;
        }
        ਨਹੀਂਤਾਂ
        {
            px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ->px_ਅਗਲਾ_Free_ਖੰਡ = ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( px_ਸਿਰਾ );
        }
    }
    ਨਹੀਂਤਾਂ
    {
        px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ->px_ਅਗਲਾ_Free_ਖੰਡ = pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    ਜੇ( pxIterator != px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ )
    {
        pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ = ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ );
    }
    ਨਹੀਂਤਾਂ
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Define_ਢੇਰ_Regions( ਅਚਲ ਢੇਰ_Region_t * ਅਚਲ px_ਢੇਰ_Regions ) /* PRIVILEGED_FUNCTION */
{
    ਖੰਡ_Link_t * px_ਪਹਿਲਾ_Free_ਖੰਡ_ਵਿੱਚ_Region = ਨਿਰਾ;
    ਖੰਡ_Link_t * px_ਪਿਛਲਾ_Free_ਖੰਡ;
    ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE x_Aligned_ਢੇਰ;
    size_t x_ਕੁੱਲ_Region_ਮਾਪ, x_ਕੁੱਲ_ਢੇਰ_ਮਾਪ = 0;
    ਅਧਾਰ_Type_t xDefinedRegions = 0;
    ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE x_ਪਤਾ;
    ਅਚਲ ਢੇਰ_Region_t * px_ਢੇਰ_Region;

    /* Can only call once! */
    configASSERT( px_ਸਿਰਾ == ਨਿਰਾ );

    #ਜੇ ( config_ENABLE_ਢੇਰ_PROTECTOR == 1 )
    {
        v_Application_Get_Random_ਢੇਰ_Canary( &( x_ਢੇਰ_Canary ) );
    }
    #ਜੇ_ਅੰਤ

    px_ਢੇਰ_Region = &( px_ਢੇਰ_Regions[ xDefinedRegions ] );

    ਜਦੋਂ( px_ਢੇਰ_Region->x_ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ > 0 )
    {
        x_ਕੁੱਲ_Region_ਮਾਪ = px_ਢੇਰ_Region->x_ਮਾਪ_ਵਿੱਚ_ਬਾਈਟਾਂ;

        /* Ensure the heap region starts on a correctly aligned boundary. */
        x_ਪਤਾ = ( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE ) px_ਢੇਰ_Region->puc_ਸ਼ੁਰੂ_ਪਤਾ;

        ਜੇ( ( x_ਪਤਾ & ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ ) != 0 )
        {
            x_ਪਤਾ += ( ਪੋਰਟ_BYTE_ALIGNMENT - 1 );
            x_ਪਤਾ &= ~( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE ) ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ;

            /* Adjust the size for the bytes lost to alignment. */
            x_ਕੁੱਲ_Region_ਮਾਪ -= ( size_t ) ( x_ਪਤਾ - ( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE ) px_ਢੇਰ_Region->puc_ਸ਼ੁਰੂ_ਪਤਾ );
        }

        x_Aligned_ਢੇਰ = x_ਪਤਾ;

        /* Set xStart if it has not already been set. */
        ਜੇ( xDefinedRegions == 0 )
        {
            /* xStart is used to hold a pointer to the first item in the list of
             *  free blocks.  The void cast is used to prevent compiler warnings. */
            x_ਸ਼ੁਰੂ.px_ਅਗਲਾ_Free_ਖੰਡ = ( ਖੰਡ_Link_t * ) ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( x_Aligned_ਢੇਰ );
            x_ਸ਼ੁਰੂ.x_ਖੰਡ_ਮਾਪ = ( size_t ) 0;
        }
        ਨਹੀਂਤਾਂ
        {
            /* Should only get here if one region has already been added to the
             * heap. */
            configASSERT( px_ਸਿਰਾ != ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( ਨਿਰਾ ) );

            /* Check blocks are passed in with increasing start addresses. */
            configASSERT( ( size_t ) x_ਪਤਾ > ( size_t ) px_ਸਿਰਾ );
        }

        #ਜੇ ( config_ENABLE_ਢੇਰ_PROTECTOR == 1 )
        {
            ਜੇ( ( puc_ਢੇਰ_ਨੀਵਾਂ_ਪਤਾ == ਨਿਰਾ ) ||
                ( ( uint8_t * ) x_Aligned_ਢੇਰ < puc_ਢੇਰ_ਨੀਵਾਂ_ਪਤਾ ) )
            {
                puc_ਢੇਰ_ਨੀਵਾਂ_ਪਤਾ = ( uint8_t * ) x_Aligned_ਢੇਰ;
            }
        }
        #ਜੇ_ਅੰਤ /* configENABLE_HEAP_PROTECTOR */

        /* Remember the location of the end marker in the previous region, if
         * any. */
        px_ਪਿਛਲਾ_Free_ਖੰਡ = px_ਸਿਰਾ;

        /* pxEnd is used to mark the end of the list of free blocks and is
         * inserted at the end of the region space. */
        x_ਪਤਾ = x_Aligned_ਢੇਰ + ( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE ) x_ਕੁੱਲ_Region_ਮਾਪ;
        x_ਪਤਾ -= ( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE ) x_ਢੇਰ_Struct_ਮਾਪ;
        x_ਪਤਾ &= ~( ( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE ) ਪੋਰਟ_BYTE_ALIGNMENT_ਨਕਾਬ );
        px_ਸਿਰਾ = ( ਖੰਡ_Link_t * ) x_ਪਤਾ;
        px_ਸਿਰਾ->x_ਖੰਡ_ਮਾਪ = 0;
        px_ਸਿਰਾ->px_ਅਗਲਾ_Free_ਖੰਡ = ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( ਨਿਰਾ );

        /* To start with there is a single free block in this region that is
         * sized to take up the entire heap region minus the space taken by the
         * free block structure. */
        px_ਪਹਿਲਾ_Free_ਖੰਡ_ਵਿੱਚ_Region = ( ਖੰਡ_Link_t * ) x_Aligned_ਢੇਰ;
        px_ਪਹਿਲਾ_Free_ਖੰਡ_ਵਿੱਚ_Region->x_ਖੰਡ_ਮਾਪ = ( size_t ) ( x_ਪਤਾ - ( ਪੋਰਟ_ਸੂਚਕ_ਮਾਪ_TYPE ) px_ਪਹਿਲਾ_Free_ਖੰਡ_ਵਿੱਚ_Region );
        px_ਪਹਿਲਾ_Free_ਖੰਡ_ਵਿੱਚ_Region->px_ਅਗਲਾ_Free_ਖੰਡ = ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( px_ਸਿਰਾ );

        /* If this is not the first region that makes up the entire heap space
         * then link the previous region to this region. */
        ਜੇ( px_ਪਿਛਲਾ_Free_ਖੰਡ != ਨਿਰਾ )
        {
            px_ਪਿਛਲਾ_Free_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ = ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( px_ਪਹਿਲਾ_Free_ਖੰਡ_ਵਿੱਚ_Region );
        }

        x_ਕੁੱਲ_ਢੇਰ_ਮਾਪ += px_ਪਹਿਲਾ_Free_ਖੰਡ_ਵਿੱਚ_Region->x_ਖੰਡ_ਮਾਪ;

        #ਜੇ ( config_ENABLE_ਢੇਰ_PROTECTOR == 1 )
        {
            ਜੇ( ( puc_ਢੇਰ_ਉੱਚਾ_ਪਤਾ == ਨਿਰਾ ) ||
                ( ( ( ( uint8_t * ) px_ਪਹਿਲਾ_Free_ਖੰਡ_ਵਿੱਚ_Region ) + px_ਪਹਿਲਾ_Free_ਖੰਡ_ਵਿੱਚ_Region->x_ਖੰਡ_ਮਾਪ ) > puc_ਢੇਰ_ਉੱਚਾ_ਪਤਾ ) )
            {
                puc_ਢੇਰ_ਉੱਚਾ_ਪਤਾ = ( ( uint8_t * ) px_ਪਹਿਲਾ_Free_ਖੰਡ_ਵਿੱਚ_Region ) + px_ਪਹਿਲਾ_Free_ਖੰਡ_ਵਿੱਚ_Region->x_ਖੰਡ_ਮਾਪ;
            }
        }
        #ਜੇ_ਅੰਤ

        /* Move onto the next HeapRegion_t structure. */
        xDefinedRegions++;
        px_ਢੇਰ_Region = &( px_ਢੇਰ_Regions[ xDefinedRegions ] );
    }

    x_Minimum_Ever_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = x_ਕੁੱਲ_ਢੇਰ_ਮਾਪ;
    x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = x_ਕੁੱਲ_ਢੇਰ_ਮਾਪ;

    /* Check something was actually defined before it is accessed. */
    configASSERT( x_ਕੁੱਲ_ਢੇਰ_ਮਾਪ );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Get_ਢੇਰ_Stats( ਢੇਰ_Stats_t * px_ਢੇਰ_Stats )
{
    ਖੰਡ_Link_t * px_ਖੰਡ;
    size_t x_ਖੰਡਾਂ = 0, x_Max_ਮਾਪ = 0, x_Min_ਮਾਪ = SIZE_MAX;

    vTaskSuspendAll();
    {
        px_ਖੰਡ = ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( x_ਸ਼ੁਰੂ.px_ਅਗਲਾ_Free_ਖੰਡ );

        /* pxBlock will be NULL if the heap has not been initialised.  The heap
         * is initialised automatically when the first allocation is made. */
        ਜੇ( px_ਖੰਡ != ਨਿਰਾ )
        {
            ਜਦੋਂ( px_ਖੰਡ != px_ਸਿਰਾ )
            {
                /* Increment the number of blocks and record the largest block seen
                 * so far. */
                x_ਖੰਡਾਂ++;

                ਜੇ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ > x_Max_ਮਾਪ )
                {
                    x_Max_ਮਾਪ = px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ;
                }

                /* Heap five will have a zero sized block at the end of each
                 * each region - the block is only used to link to the next
                 * heap region so it not a real block. */
                ਜੇ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ != 0 )
                {
                    ਜੇ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ < x_Min_ਮਾਪ )
                    {
                        x_Min_ਮਾਪ = px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ;
                    }
                }

                /* Move to the next block in the chain until the last block is
                 * reached. */
                px_ਖੰਡ = ਢੇਰ_PROTECT_ਖੰਡ_ਸੂਚਕ( px_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ );
            }
        }
    }
    ( ਖਾਲੀ ) xTaskResumeAll();

    px_ਢੇਰ_Stats->x_ਮਾਪ_ਦਾ_ਸਭ_ਤੋਂ_ਵੱਡਾ_Free_ਖੰਡ_ਵਿੱਚ_ਬਾਈਟਾਂ = x_Max_ਮਾਪ;
    px_ਢੇਰ_Stats->x_ਮਾਪ_ਦਾ_ਸਭ_ਤੋਂ_ਛੋਟਾ_Free_ਖੰਡ_ਵਿੱਚ_ਬਾਈਟਾਂ = x_Min_ਮਾਪ;
    px_ਢੇਰ_Stats->x_ਸੰਖਿਆ_ਦਾ_Free_ਖੰਡਾਂ = x_ਖੰਡਾਂ;

    taskENTER_CRITICAL();
    {
        px_ਢੇਰ_Stats->x_ਉਪਲਬਧ_ਢੇਰ_Space_ਵਿੱਚ_ਬਾਈਟਾਂ = x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ;
        px_ਢੇਰ_Stats->x_ਸੰਖਿਆ_ਦਾ_Successful_Allocations = x_ਸੰਖਿਆ_ਦਾ_Successful_Allocations;
        px_ਢੇਰ_Stats->x_ਸੰਖਿਆ_ਦਾ_Successful_Frees = x_ਸੰਖਿਆ_ਦਾ_Successful_Frees;
        px_ਢੇਰ_Stats->x_Minimum_Ever_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = x_Minimum_Ever_Free_ਬਾਈਟਾਂ_ਬਚਿਆ;
    }
    taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
ਖਾਲੀ v_ਪੋਰਟ_ਢੇਰ_Reset_State( ਖਾਲੀ )
{
    px_ਸਿਰਾ = ਨਿਰਾ;

    x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = ( size_t ) 0U;
    x_Minimum_Ever_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = ( size_t ) 0U;
    x_ਸੰਖਿਆ_ਦਾ_Successful_Allocations = ( size_t ) 0U;
    x_ਸੰਖਿਆ_ਦਾ_Successful_Frees = ( size_t ) 0U;

    #ਜੇ ( config_ENABLE_ਢੇਰ_PROTECTOR == 1 )
        puc_ਢੇਰ_ਉੱਚਾ_ਪਤਾ = ਨਿਰਾ;
        puc_ਢੇਰ_ਨੀਵਾਂ_ਪਤਾ = ਨਿਰਾ;
    #ਜੇ_ਅੰਤ /* #if ( configENABLE_HEAP_PROTECTOR == 1 ) */
}
/*-----------------------------------------------------------*/
