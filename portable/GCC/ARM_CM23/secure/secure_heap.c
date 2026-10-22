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
#অন্তর্ভাব <stdint.h>

/* Configuration includes. */
#অন্তর্ভাব "FreeRTOSConfig.h"

/* Secure context heap includes. */
#অন্তর্ভাব "secure_heap.h"

/* Secure port macros. */
#অন্তর্ভাব "secure_port_macros.h"

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
#define secureheapBLOCK_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( পরিমাণ( size_t ) * secureheapBITS_PER_BYTE ) - 1 ) )
#define secureheapBLOCK_SIZE_IS_VALID( xBlockSize )    ( ( ( xBlockSize ) & secureheapBLOCK_ALLOCATED_BITMASK ) == 0 )
#define secureheapBLOCK_IS_ALLOCATED( pxBlock )        ( ( ( pxBlock->xBlockSize ) & secureheapBLOCK_ALLOCATED_BITMASK ) != 0 )
#define secureheapALLOCATE_BLOCK( pxBlock )            ( ( pxBlock->xBlockSize ) |= secureheapBLOCK_ALLOCATED_BITMASK )
#define secureheapFREE_BLOCK( pxBlock )                ( ( pxBlock->xBlockSize ) &= ~secureheapBLOCK_ALLOCATED_BITMASK )
/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#যদি ( configAPPLICATION_ALLOCATED_HEAP == 1 )

/* The application writer has already defined the array used for the RTOS
* heap - probably so it can be placed in a special segment or address. */
    বাহ্য uint8_t ucHeap[ secureconfigTOTAL_HEAP_SIZE ];
#অন্যথা /* configAPPLICATION_ALLOCATED_HEAP */
    স্থির uint8_t ucHeap[ secureconfigTOTAL_HEAP_SIZE ];
#endif /* configAPPLICATION_ALLOCATED_HEAP */

/**
 * @brief The linked list structure.
 *
 * This is used to link free blocks in order of their memory address.
 */
প্রকারনির্দেশ সংরচনা A_BLOCK_LINK
{
    সংরচনা A_BLOCK_LINK * pxNextFreeBlock; /**< The next free block in the list. */
    size_t xBlockSize;                     /**< The size of the free block. */
} BlockLink_t;
/*-----------------------------------------------------------*/

/**
 * @brief Called automatically to setup the required heap structures the first
 * time pvPortMalloc() is called.
 */
স্থির শূন্য prvHeapInit( শূন্য );

/**
 * @brief Inserts a block of memory that is being freed into the correct
 * position in the list of free memory blocks.
 *
 * The block being freed will be merged with the block in front it and/or the
 * block behind it if the memory blocks are adjacent to each other.
 *
 * @param[in] pxBlockToInsert The block being freed.
 */
স্থির শূন্য prv_ঢোকাও_Block_Into_Free_List( BlockLink_t * px_Block_To_ঢোকাও );
/*-----------------------------------------------------------*/

/**
 * @brief The size of the structure placed at the beginning of each allocated
 * memory block must by correctly byte aligned.
 */
স্থির ধ্রুব size_t xHeapStructSize = ( পরিমাণ( BlockLink_t ) + ( ( size_t ) ( secureportBYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) secureportBYTE_ALIGNMENT_MASK );

/**
 * @brief Create a couple of list links to mark the start and end of the list.
 */
স্থির BlockLink_t xStart;
স্থির BlockLink_t * pxEnd = রিক্ত;

/**
 * @brief Keeps track of the number of free bytes remaining, but says nothing
 * about fragmentation.
 */
স্থির size_t xFreeBytesRemaining = 0U;
স্থির size_t xMinimumEverFreeBytesRemaining = 0U;

/*-----------------------------------------------------------*/

স্থির শূন্য prvHeapInit( শূন্য )
{
    BlockLink_t * pxFirstFreeBlock;
    uint8_t * pucAlignedHeap;
    size_t uxAddress;
    size_t xTotalHeapSize = secureconfigTOTAL_HEAP_SIZE;

    /* Ensure the heap starts on a correctly aligned boundary. */
    uxAddress = ( size_t ) ucHeap;

    যদি( ( uxAddress & secureportBYTE_ALIGNMENT_MASK ) != 0 )
    {
        uxAddress += ( secureportBYTE_ALIGNMENT - 1 );
        uxAddress &= ~( ( size_t ) secureportBYTE_ALIGNMENT_MASK );
        xTotalHeapSize -= uxAddress - ( size_t ) ucHeap;
    }

    pucAlignedHeap = ( uint8_t * ) uxAddress;

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    xStart.pxNextFreeBlock = ( শূন্য * ) pucAlignedHeap;
    xStart.xBlockSize = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    uxAddress = ( ( size_t ) pucAlignedHeap ) + xTotalHeapSize;
    uxAddress -= xHeapStructSize;
    uxAddress &= ~( ( size_t ) secureportBYTE_ALIGNMENT_MASK );
    pxEnd = ( শূন্য * ) uxAddress;
    pxEnd->xBlockSize = 0;
    pxEnd->pxNextFreeBlock = রিক্ত;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    pxFirstFreeBlock = ( শূন্য * ) pucAlignedHeap;
    pxFirstFreeBlock->xBlockSize = uxAddress - ( size_t ) pxFirstFreeBlock;
    pxFirstFreeBlock->pxNextFreeBlock = pxEnd;

    /* Only one block exists - and it covers the entire usable heap space. */
    xMinimumEverFreeBytesRemaining = pxFirstFreeBlock->xBlockSize;
    xFreeBytesRemaining = pxFirstFreeBlock->xBlockSize;
}
/*-----------------------------------------------------------*/

স্থির শূন্য prv_ঢোকাও_Block_Into_Free_List( BlockLink_t * px_Block_To_ঢোকাও )
{
    BlockLink_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    প্রতি( pxIterator = &xStart; pxIterator->pxNextFreeBlock < px_Block_To_ঢোকাও; pxIterator = pxIterator->pxNextFreeBlock )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    যদি( ( puc + pxIterator->xBlockSize ) == ( uint8_t * ) px_Block_To_ঢোকাও )
    {
        pxIterator->xBlockSize += px_Block_To_ঢোকাও->xBlockSize;
        px_Block_To_ঢোকাও = pxIterator;
    }
    অন্যথা
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_Block_To_ঢোকাও;

    যদি( ( puc + px_Block_To_ঢোকাও->xBlockSize ) == ( uint8_t * ) pxIterator->pxNextFreeBlock )
    {
        যদি( pxIterator->pxNextFreeBlock != pxEnd )
        {
            /* Form one big block from the two blocks. */
            px_Block_To_ঢোকাও->xBlockSize += pxIterator->pxNextFreeBlock->xBlockSize;
            px_Block_To_ঢোকাও->pxNextFreeBlock = pxIterator->pxNextFreeBlock->pxNextFreeBlock;
        }
        অন্যথা
        {
            px_Block_To_ঢোকাও->pxNextFreeBlock = pxEnd;
        }
    }
    অন্যথা
    {
        px_Block_To_ঢোকাও->pxNextFreeBlock = pxIterator->pxNextFreeBlock;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    যদি( pxIterator != px_Block_To_ঢোকাও )
    {
        pxIterator->pxNextFreeBlock = px_Block_To_ঢোকাও;
    }
    অন্যথা
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

শূন্য * pvPortMalloc( size_t xWantedSize )
{
    BlockLink_t * pxBlock;
    BlockLink_t * pxPreviousBlock;
    BlockLink_t * pxNewBlockLink;
    শূন্য * pvReturn = রিক্ত;
    size_t xAdditionalRequiredSize;
    size_t xAllocatedBlockSize = 0;

    /* If this is the first call to malloc then the heap will require
     * initialisation to setup the list of free blocks. */
    যদি( pxEnd == রিক্ত )
    {
        prvHeapInit();
    }
    অন্যথা
    {
        mtCOVERAGE_TEST_MARKER();
    }

    যদি( xWantedSize > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        যদি( secureheapADD_WILL_OVERFLOW( xWantedSize, xHeapStructSize ) == 0 )
        {
            xWantedSize += xHeapStructSize;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            যদি( ( xWantedSize & secureportBYTE_ALIGNMENT_MASK ) != 0x00 )
            {
                /* Byte alignment required. */
                xAdditionalRequiredSize = secureportBYTE_ALIGNMENT - ( xWantedSize & secureportBYTE_ALIGNMENT_MASK );

                যদি( secureheapADD_WILL_OVERFLOW( xWantedSize, xAdditionalRequiredSize ) == 0 )
                {
                    xWantedSize += xAdditionalRequiredSize;
                }
                অন্যথা
                {
                    xWantedSize = 0;
                }
            }
            অন্যথা
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        অন্যথা
        {
            xWantedSize = 0;
        }
    }
    অন্যথা
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Check the requested block size is not so large that the top bit is set.
     * The top bit of the block size member of the BlockLink_t structure is used
     * to determine who owns the block - the application or the kernel, so it
     * must be free. */
    যদি( secureheapBLOCK_SIZE_IS_VALID( xWantedSize ) != 0 )
    {
        যদি( ( xWantedSize > 0 ) && ( xWantedSize <= xFreeBytesRemaining ) )
        {
            /* Traverse the list from the start (lowest address) block until
             * one of adequate size is found. */
            pxPreviousBlock = &xStart;
            pxBlock = xStart.pxNextFreeBlock;

            যাবত্( ( pxBlock->xBlockSize < xWantedSize ) && ( pxBlock->pxNextFreeBlock != রিক্ত ) )
            {
                pxPreviousBlock = pxBlock;
                pxBlock = pxBlock->pxNextFreeBlock;
            }

            /* If the end marker was reached then a block of adequate size was
             * not found. */
            যদি( pxBlock != pxEnd )
            {
                /* Return the memory space pointed to - jumping over the
                 * BlockLink_t structure at its start. */
                pvReturn = ( শূন্য * ) ( ( ( uint8_t * ) pxPreviousBlock->pxNextFreeBlock ) + xHeapStructSize );

                /* This block is being returned for use so must be taken out
                 * of the list of free blocks. */
                pxPreviousBlock->pxNextFreeBlock = pxBlock->pxNextFreeBlock;

                /* If the block is larger than required it can be split into
                 * two. */
                যদি( ( pxBlock->xBlockSize - xWantedSize ) > secureheapMINIMUM_BLOCK_SIZE )
                {
                    /* This block is to be split into two.  Create a new
                     * block following the number of bytes requested. The void
                     * cast is used to prevent byte alignment warnings from the
                     * compiler. */
                    pxNewBlockLink = ( শূন্য * ) ( ( ( uint8_t * ) pxBlock ) + xWantedSize );
                    secureportASSERT( ( ( ( size_t ) pxNewBlockLink ) & secureportBYTE_ALIGNMENT_MASK ) == 0 );

                    /* Calculate the sizes of two blocks split from the single
                     * block. */
                    pxNewBlockLink->xBlockSize = pxBlock->xBlockSize - xWantedSize;
                    pxBlock->xBlockSize = xWantedSize;

                    /* Insert the new block into the list of free blocks. */
                    pxNewBlockLink->pxNextFreeBlock = pxPreviousBlock->pxNextFreeBlock;
                    pxPreviousBlock->pxNextFreeBlock = pxNewBlockLink;
                }
                অন্যথা
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                xFreeBytesRemaining -= pxBlock->xBlockSize;

                যদি( xFreeBytesRemaining < xMinimumEverFreeBytesRemaining )
                {
                    xMinimumEverFreeBytesRemaining = xFreeBytesRemaining;
                }
                অন্যথা
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                xAllocatedBlockSize = pxBlock->xBlockSize;

                /* The block is being returned - it is allocated and owned by
                 * the application and has no "next" block. */
                secureheapALLOCATE_BLOCK( pxBlock );
                pxBlock->pxNextFreeBlock = রিক্ত;
            }
            অন্যথা
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        অন্যথা
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    অন্যথা
    {
        mtCOVERAGE_TEST_MARKER();
    }

    traceMALLOC( pvReturn, xAllocatedBlockSize );

    /* Prevent compiler warnings when trace macros are not used. */
    ( শূন্য ) xAllocatedBlockSize;

    #যদি ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 )
    {
        যদি( pvReturn == রিক্ত )
        {
            বাহ্য শূন্য vApplicationMallocFailedHook( শূন্য );
            vApplicationMallocFailedHook();
        }
        অন্যথা
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #endif /* if ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 ) */

    secureportASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) secureportBYTE_ALIGNMENT_MASK ) == 0 );
    প্রত্যাগম pvReturn;
}
/*-----------------------------------------------------------*/

শূন্য vPortFree( শূন্য * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    BlockLink_t * pxLink;

    যদি( pv != রিক্ত )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= xHeapStructSize;

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( শূন্য * ) puc;

        /* Check the block is actually allocated. */
        secureportASSERT( secureheapBLOCK_IS_ALLOCATED( pxLink ) != 0 );
        secureportASSERT( pxLink->pxNextFreeBlock == রিক্ত );

        যদি( secureheapBLOCK_IS_ALLOCATED( pxLink ) != 0 )
        {
            যদি( pxLink->pxNextFreeBlock == রিক্ত )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                secureheapFREE_BLOCK( pxLink );

                secureportDISABLE_NON_SECURE_INTERRUPTS();
                {
                    /* Add this block to the list of free blocks. */
                    xFreeBytesRemaining += pxLink->xBlockSize;
                    traceFREE( pv, pxLink->xBlockSize );
                    prv_ঢোকাও_Block_Into_Free_List( ( ( BlockLink_t * ) pxLink ) );
                }
                secureportENABLE_NON_SECURE_INTERRUPTS();
            }
            অন্যথা
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        অন্যথা
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
}
/*-----------------------------------------------------------*/

size_t xPortGetFreeHeapSize( শূন্য )
{
    প্রত্যাগম xFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

size_t xPortGetMinimumEverFreeHeapSize( শূন্য )
{
    প্রত্যাগম xMinimumEverFreeBytesRemaining;
}
/*-----------------------------------------------------------*/
