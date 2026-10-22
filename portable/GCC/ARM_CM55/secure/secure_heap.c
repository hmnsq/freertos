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
#समावेश <stdint.h>

/* Configuration includes. */
#समावेश "FreeRTOSConfig.h"

/* Secure context heap includes. */
#समावेश "secure_heap.h"

/* Secure port macros. */
#समावेश "secure_port_macros.h"

/**
 * @brief Total heap size.
 */
#अगर_अघोषित secureconfig_योग_HEAP_आकार
    #घोषणा secureconfig_योग_HEAP_आकार    ( ( ( माप_प्रकार ) ( 10 * 1024 ) ) )
#पूर्ण_अगर

/* No test marker by default. */
#अगर_अघोषित mtCOVERAGE_TEST_MARKER
    #घोषणा mtCOVERAGE_TEST_MARKER()
#पूर्ण_अगर

/* No tracing by default. */
#अगर_अघोषित traceMALLOC
    #घोषणा traceMALLOC( pvReturn, x_Wanted_आकार )
#पूर्ण_अगर

/* No tracing by default. */
#अगर_अघोषित traceFREE
    #घोषणा traceFREE( pv, x_Block_आकार )
#पूर्ण_अगर

/* Block sizes must not get too small. */
#घोषणा secureheap_MINIMUM_BLOCK_आकार    ( ( माप_प्रकार ) ( x_Heap_Struct_आकार << 1 ) )

/* Assumes 8bit bytes! */
#घोषणा secureheapBITS_PER_BYTE         ( ( माप_प्रकार ) 8 )

/* Max value that fits in a size_t type. */
#घोषणा secureheap_आकार_MAX              ( ~( ( माप_प्रकार ) 0 ) )

/* Check if adding a and b will result in overflow. */
#घोषणा secureheapADD_WILL_OVERFLOW( a, b )    ( ( a ) > ( secureheap_आकार_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#घोषणा secureheapBLOCK_ALLOCATED_BITMASK    ( ( ( माप_प्रकार ) 1 ) << ( ( माप( माप_प्रकार ) * secureheapBITS_PER_BYTE ) - 1 ) )
#घोषणा secureheap_BLOCK_आकार_IS_VALID( x_Block_आकार )    ( ( ( x_Block_आकार ) & secureheapBLOCK_ALLOCATED_BITMASK ) == 0 )
#घोषणा secureheapBLOCK_IS_ALLOCATED( pxBlock )        ( ( ( pxBlock->x_Block_आकार ) & secureheapBLOCK_ALLOCATED_BITMASK ) != 0 )
#घोषणा secureheapALLOCATE_BLOCK( pxBlock )            ( ( pxBlock->x_Block_आकार ) |= secureheapBLOCK_ALLOCATED_BITMASK )
#घोषणा secureheapFREE_BLOCK( pxBlock )                ( ( pxBlock->x_Block_आकार ) &= ~secureheapBLOCK_ALLOCATED_BITMASK )
/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#अगर ( configAPPLICATION_ALLOCATED_HEAP == 1 )

/* The application writer has already defined the array used for the RTOS
* heap - probably so it can be placed in a special segment or address. */
    बाह्य uint8_t ucHeap[ secureconfig_योग_HEAP_आकार ];
#अन्यथा /* configAPPLICATION_ALLOCATED_HEAP */
    अटल uint8_t ucHeap[ secureconfig_योग_HEAP_आकार ];
#पूर्ण_अगर /* configAPPLICATION_ALLOCATED_HEAP */

/**
 * @brief The linked list structure.
 *
 * This is used to link free blocks in order of their memory address.
 */
प्रकार काष्ठा A_BLOCK_LINK
{
    काष्ठा A_BLOCK_LINK * px_अग्र_Free_Block; /**< The next free block in the list. */
    माप_प्रकार x_Block_आकार;                     /**< The size of the free block. */
} BlockLink_t;
/*-----------------------------------------------------------*/

/**
 * @brief Called automatically to setup the required heap structures the first
 * time pvPortMalloc() is called.
 */
अटल व्योम prvHeapInit( व्योम );

/**
 * @brief Inserts a block of memory that is being freed into the correct
 * position in the list of free memory blocks.
 *
 * The block being freed will be merged with the block in front it and/or the
 * block behind it if the memory blocks are adjacent to each other.
 *
 * @param[in] pxBlockToInsert The block being freed.
 */
अटल व्योम prv_जोड़ो_Block_Into_Free_List( BlockLink_t * px_Block_To_जोड़ो );
/*-----------------------------------------------------------*/

/**
 * @brief The size of the structure placed at the beginning of each allocated
 * memory block must by correctly byte aligned.
 */
अटल स्थिर माप_प्रकार x_Heap_Struct_आकार = ( माप( BlockLink_t ) + ( ( माप_प्रकार ) ( secureportBYTE_ALIGNMENT - 1 ) ) ) & ~( ( माप_प्रकार ) secureportBYTE_ALIGNMENT_MASK );

/**
 * @brief Create a couple of list links to mark the start and end of the list.
 */
अटल BlockLink_t xStart;
अटल BlockLink_t * pxEnd = शून्य;

/**
 * @brief Keeps track of the number of free bytes remaining, but says nothing
 * about fragmentation.
 */
अटल माप_प्रकार xFreeBytesRemaining = 0U;
अटल माप_प्रकार xMinimumEverFreeBytesRemaining = 0U;

/*-----------------------------------------------------------*/

अटल व्योम prvHeapInit( व्योम )
{
    BlockLink_t * pxFirstFreeBlock;
    uint8_t * pucAlignedHeap;
    माप_प्रकार uxAddress;
    माप_प्रकार x_योग_Heap_आकार = secureconfig_योग_HEAP_आकार;

    /* Ensure the heap starts on a correctly aligned boundary. */
    uxAddress = ( माप_प्रकार ) ucHeap;

    अगर( ( uxAddress & secureportBYTE_ALIGNMENT_MASK ) != 0 )
    {
        uxAddress += ( secureportBYTE_ALIGNMENT - 1 );
        uxAddress &= ~( ( माप_प्रकार ) secureportBYTE_ALIGNMENT_MASK );
        x_योग_Heap_आकार -= uxAddress - ( माप_प्रकार ) ucHeap;
    }

    pucAlignedHeap = ( uint8_t * ) uxAddress;

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    xStart.px_अग्र_Free_Block = ( व्योम * ) pucAlignedHeap;
    xStart.x_Block_आकार = ( माप_प्रकार ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    uxAddress = ( ( माप_प्रकार ) pucAlignedHeap ) + x_योग_Heap_आकार;
    uxAddress -= x_Heap_Struct_आकार;
    uxAddress &= ~( ( माप_प्रकार ) secureportBYTE_ALIGNMENT_MASK );
    pxEnd = ( व्योम * ) uxAddress;
    pxEnd->x_Block_आकार = 0;
    pxEnd->px_अग्र_Free_Block = शून्य;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    pxFirstFreeBlock = ( व्योम * ) pucAlignedHeap;
    pxFirstFreeBlock->x_Block_आकार = uxAddress - ( माप_प्रकार ) pxFirstFreeBlock;
    pxFirstFreeBlock->px_अग्र_Free_Block = pxEnd;

    /* Only one block exists - and it covers the entire usable heap space. */
    xMinimumEverFreeBytesRemaining = pxFirstFreeBlock->x_Block_आकार;
    xFreeBytesRemaining = pxFirstFreeBlock->x_Block_आकार;
}
/*-----------------------------------------------------------*/

अटल व्योम prv_जोड़ो_Block_Into_Free_List( BlockLink_t * px_Block_To_जोड़ो )
{
    BlockLink_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    क्रम( pxIterator = &xStart; pxIterator->px_अग्र_Free_Block < px_Block_To_जोड़ो; pxIterator = pxIterator->px_अग्र_Free_Block )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    अगर( ( puc + pxIterator->x_Block_आकार ) == ( uint8_t * ) px_Block_To_जोड़ो )
    {
        pxIterator->x_Block_आकार += px_Block_To_जोड़ो->x_Block_आकार;
        px_Block_To_जोड़ो = pxIterator;
    }
    अन्यथा
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_Block_To_जोड़ो;

    अगर( ( puc + px_Block_To_जोड़ो->x_Block_आकार ) == ( uint8_t * ) pxIterator->px_अग्र_Free_Block )
    {
        अगर( pxIterator->px_अग्र_Free_Block != pxEnd )
        {
            /* Form one big block from the two blocks. */
            px_Block_To_जोड़ो->x_Block_आकार += pxIterator->px_अग्र_Free_Block->x_Block_आकार;
            px_Block_To_जोड़ो->px_अग्र_Free_Block = pxIterator->px_अग्र_Free_Block->px_अग्र_Free_Block;
        }
        अन्यथा
        {
            px_Block_To_जोड़ो->px_अग्र_Free_Block = pxEnd;
        }
    }
    अन्यथा
    {
        px_Block_To_जोड़ो->px_अग्र_Free_Block = pxIterator->px_अग्र_Free_Block;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    अगर( pxIterator != px_Block_To_जोड़ो )
    {
        pxIterator->px_अग्र_Free_Block = px_Block_To_जोड़ो;
    }
    अन्यथा
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

व्योम * pvPortMalloc( माप_प्रकार x_Wanted_आकार )
{
    BlockLink_t * pxBlock;
    BlockLink_t * pxPreviousBlock;
    BlockLink_t * pxNewBlockLink;
    व्योम * pvReturn = शून्य;
    माप_प्रकार x_Additional_Required_आकार;
    माप_प्रकार x_Allocated_Block_आकार = 0;

    /* If this is the first call to malloc then the heap will require
     * initialisation to setup the list of free blocks. */
    अगर( pxEnd == शून्य )
    {
        prvHeapInit();
    }
    अन्यथा
    {
        mtCOVERAGE_TEST_MARKER();
    }

    अगर( x_Wanted_आकार > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        अगर( secureheapADD_WILL_OVERFLOW( x_Wanted_आकार, x_Heap_Struct_आकार ) == 0 )
        {
            x_Wanted_आकार += x_Heap_Struct_आकार;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            अगर( ( x_Wanted_आकार & secureportBYTE_ALIGNMENT_MASK ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_आकार = secureportBYTE_ALIGNMENT - ( x_Wanted_आकार & secureportBYTE_ALIGNMENT_MASK );

                अगर( secureheapADD_WILL_OVERFLOW( x_Wanted_आकार, x_Additional_Required_आकार ) == 0 )
                {
                    x_Wanted_आकार += x_Additional_Required_आकार;
                }
                अन्यथा
                {
                    x_Wanted_आकार = 0;
                }
            }
            अन्यथा
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        अन्यथा
        {
            x_Wanted_आकार = 0;
        }
    }
    अन्यथा
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Check the requested block size is not so large that the top bit is set.
     * The top bit of the block size member of the BlockLink_t structure is used
     * to determine who owns the block - the application or the kernel, so it
     * must be free. */
    अगर( secureheap_BLOCK_आकार_IS_VALID( x_Wanted_आकार ) != 0 )
    {
        अगर( ( x_Wanted_आकार > 0 ) && ( x_Wanted_आकार <= xFreeBytesRemaining ) )
        {
            /* Traverse the list from the start (lowest address) block until
             * one of adequate size is found. */
            pxPreviousBlock = &xStart;
            pxBlock = xStart.px_अग्र_Free_Block;

            जबतक( ( pxBlock->x_Block_आकार < x_Wanted_आकार ) && ( pxBlock->px_अग्र_Free_Block != शून्य ) )
            {
                pxPreviousBlock = pxBlock;
                pxBlock = pxBlock->px_अग्र_Free_Block;
            }

            /* If the end marker was reached then a block of adequate size was
             * not found. */
            अगर( pxBlock != pxEnd )
            {
                /* Return the memory space pointed to - jumping over the
                 * BlockLink_t structure at its start. */
                pvReturn = ( व्योम * ) ( ( ( uint8_t * ) pxPreviousBlock->px_अग्र_Free_Block ) + x_Heap_Struct_आकार );

                /* This block is being returned for use so must be taken out
                 * of the list of free blocks. */
                pxPreviousBlock->px_अग्र_Free_Block = pxBlock->px_अग्र_Free_Block;

                /* If the block is larger than required it can be split into
                 * two. */
                अगर( ( pxBlock->x_Block_आकार - x_Wanted_आकार ) > secureheap_MINIMUM_BLOCK_आकार )
                {
                    /* This block is to be split into two.  Create a new
                     * block following the number of bytes requested. The void
                     * cast is used to prevent byte alignment warnings from the
                     * compiler. */
                    pxNewBlockLink = ( व्योम * ) ( ( ( uint8_t * ) pxBlock ) + x_Wanted_आकार );
                    secureportASSERT( ( ( ( माप_प्रकार ) pxNewBlockLink ) & secureportBYTE_ALIGNMENT_MASK ) == 0 );

                    /* Calculate the sizes of two blocks split from the single
                     * block. */
                    pxNewBlockLink->x_Block_आकार = pxBlock->x_Block_आकार - x_Wanted_आकार;
                    pxBlock->x_Block_आकार = x_Wanted_आकार;

                    /* Insert the new block into the list of free blocks. */
                    pxNewBlockLink->px_अग्र_Free_Block = pxPreviousBlock->px_अग्र_Free_Block;
                    pxPreviousBlock->px_अग्र_Free_Block = pxNewBlockLink;
                }
                अन्यथा
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                xFreeBytesRemaining -= pxBlock->x_Block_आकार;

                अगर( xFreeBytesRemaining < xMinimumEverFreeBytesRemaining )
                {
                    xMinimumEverFreeBytesRemaining = xFreeBytesRemaining;
                }
                अन्यथा
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Allocated_Block_आकार = pxBlock->x_Block_आकार;

                /* The block is being returned - it is allocated and owned by
                 * the application and has no "next" block. */
                secureheapALLOCATE_BLOCK( pxBlock );
                pxBlock->px_अग्र_Free_Block = शून्य;
            }
            अन्यथा
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        अन्यथा
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    अन्यथा
    {
        mtCOVERAGE_TEST_MARKER();
    }

    traceMALLOC( pvReturn, x_Allocated_Block_आकार );

    /* Prevent compiler warnings when trace macros are not used. */
    ( व्योम ) x_Allocated_Block_आकार;

    #अगर ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 )
    {
        अगर( pvReturn == शून्य )
        {
            बाह्य व्योम vApplicationMallocFailedHook( व्योम );
            vApplicationMallocFailedHook();
        }
        अन्यथा
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #पूर्ण_अगर /* if ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 ) */

    secureportASSERT( ( ( ( माप_प्रकार ) pvReturn ) & ( माप_प्रकार ) secureportBYTE_ALIGNMENT_MASK ) == 0 );
    वापस pvReturn;
}
/*-----------------------------------------------------------*/

व्योम vPortFree( व्योम * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    BlockLink_t * pxLink;

    अगर( pv != शून्य )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_Heap_Struct_आकार;

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( व्योम * ) puc;

        /* Check the block is actually allocated. */
        secureportASSERT( secureheapBLOCK_IS_ALLOCATED( pxLink ) != 0 );
        secureportASSERT( pxLink->px_अग्र_Free_Block == शून्य );

        अगर( secureheapBLOCK_IS_ALLOCATED( pxLink ) != 0 )
        {
            अगर( pxLink->px_अग्र_Free_Block == शून्य )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                secureheapFREE_BLOCK( pxLink );

                secureportDISABLE_NON_SECURE_INTERRUPTS();
                {
                    /* Add this block to the list of free blocks. */
                    xFreeBytesRemaining += pxLink->x_Block_आकार;
                    traceFREE( pv, pxLink->x_Block_आकार );
                    prv_जोड़ो_Block_Into_Free_List( ( ( BlockLink_t * ) pxLink ) );
                }
                secureportENABLE_NON_SECURE_INTERRUPTS();
            }
            अन्यथा
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        अन्यथा
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
}
/*-----------------------------------------------------------*/

माप_प्रकार x_Port_Get_Free_Heap_आकार( व्योम )
{
    वापस xFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

माप_प्रकार x_Port_Get_Minimum_Ever_Free_Heap_आकार( व्योम )
{
    वापस xMinimumEverFreeBytesRemaining;
}
/*-----------------------------------------------------------*/
