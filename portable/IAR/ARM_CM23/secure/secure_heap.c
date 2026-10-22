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

/* Standard includes. */
#அந்தர்பாவ <stdint.h>

/* Configuration includes. */
#அந்தர்பாவ "FreeRTOSConfig.h"

/* Secure context heap includes. */
#அந்தர்பாவ "secure_heap.h"

/* Secure port macros. */
#அந்தர்பாவ "secure_port_macros.h"

/**
 * @brief Total heap size.
 */
#ifndef secureconfigTOTAL_HEAP_SIZE
    #define secureconfigTOTAL_HEAP_SIZE    ( ( ( size_t ) ( 10 * 1024 ) ) )
#endif

/* No test marker by default. */
#ifndef mtCOVERAGE_TEST_MARKER
    #define mtCOVERAGE_TEST_MARKER()
#endif

/* No tracing by default. */
#ifndef traceMALLOC
    #define traceMALLOC( pvReturn, xWantedSize )
#endif

/* No tracing by default. */
#ifndef traceFREE
    #define traceFREE( pv, xBlockSize )
#endif

/* Block sizes must not get too small. */
#define secureheapMINIMUM_BLOCK_SIZE    ( ( size_t ) ( xHeapStructSize << 1 ) )

/* Assumes 8bit bytes! */
#define secureheapBITS_PER_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#define secureheapSIZE_MAX              ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#define secureheapADD_WILL_OVERFLOW( a, b )    ( ( a ) > ( secureheapSIZE_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#define secureheapBLOCK_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( அளவு( size_t ) * secureheapBITS_PER_BYTE ) - 1 ) )
#define secureheapBLOCK_SIZE_IS_VALID( xBlockSize )    ( ( ( xBlockSize ) & secureheapBLOCK_ALLOCATED_BITMASK ) == 0 )
#define secureheapBLOCK_IS_ALLOCATED( pxBlock )        ( ( ( pxBlock->xBlockSize ) & secureheapBLOCK_ALLOCATED_BITMASK ) != 0 )
#define secureheapALLOCATE_BLOCK( pxBlock )            ( ( pxBlock->xBlockSize ) |= secureheapBLOCK_ALLOCATED_BITMASK )
#define secureheapFREE_BLOCK( pxBlock )                ( ( pxBlock->xBlockSize ) &= ~secureheapBLOCK_ALLOCATED_BITMASK )
/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#எனில் ( configAPPLICATION_ALLOCATED_HEAP == 1 )

/* The application writer has already defined the array used for the RTOS
* heap - probably so it can be placed in a special segment or address. */
    வெளி uint8_t ucHeap[ secureconfigTOTAL_HEAP_SIZE ];
#இல்லையெனில் /* configAPPLICATION_ALLOCATED_HEAP */
    நிலையான uint8_t ucHeap[ secureconfigTOTAL_HEAP_SIZE ];
#endif /* configAPPLICATION_ALLOCATED_HEAP */

/**
 * @brief The linked list structure.
 *
 * This is used to link free blocks in order of their memory address.
 */
வகைவரை கட்டமைப்பு A_BLOCK_LINK
{
    கட்டமைப்பு A_BLOCK_LINK * pxNextFreeBlock; /**< The next free block in the list. */
    size_t xBlockSize;                     /**< The size of the free block. */
} BlockLink_t;
/*-----------------------------------------------------------*/

/**
 * @brief Called automatically to setup the required heap structures the first
 * time pvPortMalloc() is called.
 */
நிலையான வெறுமை prvHeapInit( வெறுமை );

/**
 * @brief Inserts a block of memory that is being freed into the correct
 * position in the list of free memory blocks.
 *
 * The block being freed will be merged with the block in front it and/or the
 * block behind it if the memory blocks are adjacent to each other.
 *
 * @param[in] pxBlockToInsert The block being freed.
 */
நிலையான வெறுமை prv_செருகு_Block_Into_Free_List( BlockLink_t * px_Block_To_செருகு );
/*-----------------------------------------------------------*/

/**
 * @brief The size of the structure placed at the beginning of each allocated
 * memory block must by correctly byte aligned.
 */
நிலையான மாறிலி size_t xHeapStructSize = ( அளவு( BlockLink_t ) + ( ( size_t ) ( secureportBYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) secureportBYTE_ALIGNMENT_MASK );

/**
 * @brief Create a couple of list links to mark the start and end of the list.
 */
நிலையான BlockLink_t xStart;
நிலையான BlockLink_t * pxEnd = வெற்று;

/**
 * @brief Keeps track of the number of free bytes remaining, but says nothing
 * about fragmentation.
 */
நிலையான size_t xFreeBytesRemaining = 0U;
நிலையான size_t xMinimumEverFreeBytesRemaining = 0U;

/*-----------------------------------------------------------*/

நிலையான வெறுமை prvHeapInit( வெறுமை )
{
    BlockLink_t * pxFirstFreeBlock;
    uint8_t * pucAlignedHeap;
    size_t uxAddress;
    size_t xTotalHeapSize = secureconfigTOTAL_HEAP_SIZE;

    /* Ensure the heap starts on a correctly aligned boundary. */
    uxAddress = ( size_t ) ucHeap;

    எனில்( ( uxAddress & secureportBYTE_ALIGNMENT_MASK ) != 0 )
    {
        uxAddress += ( secureportBYTE_ALIGNMENT - 1 );
        uxAddress &= ~( ( size_t ) secureportBYTE_ALIGNMENT_MASK );
        xTotalHeapSize -= uxAddress - ( size_t ) ucHeap;
    }

    pucAlignedHeap = ( uint8_t * ) uxAddress;

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    xStart.pxNextFreeBlock = ( வெறுமை * ) pucAlignedHeap;
    xStart.xBlockSize = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    uxAddress = ( ( size_t ) pucAlignedHeap ) + xTotalHeapSize;
    uxAddress -= xHeapStructSize;
    uxAddress &= ~( ( size_t ) secureportBYTE_ALIGNMENT_MASK );
    pxEnd = ( வெறுமை * ) uxAddress;
    pxEnd->xBlockSize = 0;
    pxEnd->pxNextFreeBlock = வெற்று;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    pxFirstFreeBlock = ( வெறுமை * ) pucAlignedHeap;
    pxFirstFreeBlock->xBlockSize = uxAddress - ( size_t ) pxFirstFreeBlock;
    pxFirstFreeBlock->pxNextFreeBlock = pxEnd;

    /* Only one block exists - and it covers the entire usable heap space. */
    xMinimumEverFreeBytesRemaining = pxFirstFreeBlock->xBlockSize;
    xFreeBytesRemaining = pxFirstFreeBlock->xBlockSize;
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prv_செருகு_Block_Into_Free_List( BlockLink_t * px_Block_To_செருகு )
{
    BlockLink_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    க்கு( pxIterator = &xStart; pxIterator->pxNextFreeBlock < px_Block_To_செருகு; pxIterator = pxIterator->pxNextFreeBlock )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    எனில்( ( puc + pxIterator->xBlockSize ) == ( uint8_t * ) px_Block_To_செருகு )
    {
        pxIterator->xBlockSize += px_Block_To_செருகு->xBlockSize;
        px_Block_To_செருகு = pxIterator;
    }
    இல்லையெனில்
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_Block_To_செருகு;

    எனில்( ( puc + px_Block_To_செருகு->xBlockSize ) == ( uint8_t * ) pxIterator->pxNextFreeBlock )
    {
        எனில்( pxIterator->pxNextFreeBlock != pxEnd )
        {
            /* Form one big block from the two blocks. */
            px_Block_To_செருகு->xBlockSize += pxIterator->pxNextFreeBlock->xBlockSize;
            px_Block_To_செருகு->pxNextFreeBlock = pxIterator->pxNextFreeBlock->pxNextFreeBlock;
        }
        இல்லையெனில்
        {
            px_Block_To_செருகு->pxNextFreeBlock = pxEnd;
        }
    }
    இல்லையெனில்
    {
        px_Block_To_செருகு->pxNextFreeBlock = pxIterator->pxNextFreeBlock;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    எனில்( pxIterator != px_Block_To_செருகு )
    {
        pxIterator->pxNextFreeBlock = px_Block_To_செருகு;
    }
    இல்லையெனில்
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

வெறுமை * pvPortMalloc( size_t xWantedSize )
{
    BlockLink_t * pxBlock;
    BlockLink_t * pxPreviousBlock;
    BlockLink_t * pxNewBlockLink;
    வெறுமை * pvReturn = வெற்று;
    size_t xAdditionalRequiredSize;
    size_t xAllocatedBlockSize = 0;

    /* If this is the first call to malloc then the heap will require
     * initialisation to setup the list of free blocks. */
    எனில்( pxEnd == வெற்று )
    {
        prvHeapInit();
    }
    இல்லையெனில்
    {
        mtCOVERAGE_TEST_MARKER();
    }

    எனில்( xWantedSize > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        எனில்( secureheapADD_WILL_OVERFLOW( xWantedSize, xHeapStructSize ) == 0 )
        {
            xWantedSize += xHeapStructSize;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            எனில்( ( xWantedSize & secureportBYTE_ALIGNMENT_MASK ) != 0x00 )
            {
                /* Byte alignment required. */
                xAdditionalRequiredSize = secureportBYTE_ALIGNMENT - ( xWantedSize & secureportBYTE_ALIGNMENT_MASK );

                எனில்( secureheapADD_WILL_OVERFLOW( xWantedSize, xAdditionalRequiredSize ) == 0 )
                {
                    xWantedSize += xAdditionalRequiredSize;
                }
                இல்லையெனில்
                {
                    xWantedSize = 0;
                }
            }
            இல்லையெனில்
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        இல்லையெனில்
        {
            xWantedSize = 0;
        }
    }
    இல்லையெனில்
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Check the requested block size is not so large that the top bit is set.
     * The top bit of the block size member of the BlockLink_t structure is used
     * to determine who owns the block - the application or the kernel, so it
     * must be free. */
    எனில்( secureheapBLOCK_SIZE_IS_VALID( xWantedSize ) != 0 )
    {
        எனில்( ( xWantedSize > 0 ) && ( xWantedSize <= xFreeBytesRemaining ) )
        {
            /* Traverse the list from the start (lowest address) block until
             * one of adequate size is found. */
            pxPreviousBlock = &xStart;
            pxBlock = xStart.pxNextFreeBlock;

            போது( ( pxBlock->xBlockSize < xWantedSize ) && ( pxBlock->pxNextFreeBlock != வெற்று ) )
            {
                pxPreviousBlock = pxBlock;
                pxBlock = pxBlock->pxNextFreeBlock;
            }

            /* If the end marker was reached then a block of adequate size was
             * not found. */
            எனில்( pxBlock != pxEnd )
            {
                /* Return the memory space pointed to - jumping over the
                 * BlockLink_t structure at its start. */
                pvReturn = ( வெறுமை * ) ( ( ( uint8_t * ) pxPreviousBlock->pxNextFreeBlock ) + xHeapStructSize );

                /* This block is being returned for use so must be taken out
                 * of the list of free blocks. */
                pxPreviousBlock->pxNextFreeBlock = pxBlock->pxNextFreeBlock;

                /* If the block is larger than required it can be split into
                 * two. */
                எனில்( ( pxBlock->xBlockSize - xWantedSize ) > secureheapMINIMUM_BLOCK_SIZE )
                {
                    /* This block is to be split into two.  Create a new
                     * block following the number of bytes requested. The void
                     * cast is used to prevent byte alignment warnings from the
                     * compiler. */
                    pxNewBlockLink = ( வெறுமை * ) ( ( ( uint8_t * ) pxBlock ) + xWantedSize );
                    secureportASSERT( ( ( ( size_t ) pxNewBlockLink ) & secureportBYTE_ALIGNMENT_MASK ) == 0 );

                    /* Calculate the sizes of two blocks split from the single
                     * block. */
                    pxNewBlockLink->xBlockSize = pxBlock->xBlockSize - xWantedSize;
                    pxBlock->xBlockSize = xWantedSize;

                    /* Insert the new block into the list of free blocks. */
                    pxNewBlockLink->pxNextFreeBlock = pxPreviousBlock->pxNextFreeBlock;
                    pxPreviousBlock->pxNextFreeBlock = pxNewBlockLink;
                }
                இல்லையெனில்
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                xFreeBytesRemaining -= pxBlock->xBlockSize;

                எனில்( xFreeBytesRemaining < xMinimumEverFreeBytesRemaining )
                {
                    xMinimumEverFreeBytesRemaining = xFreeBytesRemaining;
                }
                இல்லையெனில்
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                xAllocatedBlockSize = pxBlock->xBlockSize;

                /* The block is being returned - it is allocated and owned by
                 * the application and has no "next" block. */
                secureheapALLOCATE_BLOCK( pxBlock );
                pxBlock->pxNextFreeBlock = வெற்று;
            }
            இல்லையெனில்
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        இல்லையெனில்
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    இல்லையெனில்
    {
        mtCOVERAGE_TEST_MARKER();
    }

    traceMALLOC( pvReturn, xAllocatedBlockSize );

    /* Prevent compiler warnings when trace macros are not used. */
    ( வெறுமை ) xAllocatedBlockSize;

    #எனில் ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 )
    {
        எனில்( pvReturn == வெற்று )
        {
            வெளி வெறுமை vApplicationMallocFailedHook( வெறுமை );
            vApplicationMallocFailedHook();
        }
        இல்லையெனில்
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #endif /* if ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 ) */

    secureportASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) secureportBYTE_ALIGNMENT_MASK ) == 0 );
    திரும்பு pvReturn;
}
/*-----------------------------------------------------------*/

வெறுமை vPortFree( வெறுமை * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    BlockLink_t * pxLink;

    எனில்( pv != வெற்று )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= xHeapStructSize;

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( வெறுமை * ) puc;

        /* Check the block is actually allocated. */
        secureportASSERT( secureheapBLOCK_IS_ALLOCATED( pxLink ) != 0 );
        secureportASSERT( pxLink->pxNextFreeBlock == வெற்று );

        எனில்( secureheapBLOCK_IS_ALLOCATED( pxLink ) != 0 )
        {
            எனில்( pxLink->pxNextFreeBlock == வெற்று )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                secureheapFREE_BLOCK( pxLink );

                secureportDISABLE_NON_SECURE_INTERRUPTS();
                {
                    /* Add this block to the list of free blocks. */
                    xFreeBytesRemaining += pxLink->xBlockSize;
                    traceFREE( pv, pxLink->xBlockSize );
                    prv_செருகு_Block_Into_Free_List( ( ( BlockLink_t * ) pxLink ) );
                }
                secureportENABLE_NON_SECURE_INTERRUPTS();
            }
            இல்லையெனில்
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        இல்லையெனில்
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
}
/*-----------------------------------------------------------*/

size_t xPortGetFreeHeapSize( வெறுமை )
{
    திரும்பு xFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

size_t xPortGetMinimumEverFreeHeapSize( வெறுமை )
{
    திரும்பு xMinimumEverFreeBytesRemaining;
}
/*-----------------------------------------------------------*/
