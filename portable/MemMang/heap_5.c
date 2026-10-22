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
#ضمن <stdlib.h>
#ضمن <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ضمن "FreeRTOS.h"
#ضمن "task.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#إذا ( configSUPPORT_DYNAMIC_ALLOCATION == 0 )
    #error This file must not be used إذا configSUPPORT_DYNAMIC_ALLOCATION is 0
#endif

#ifndef configHEAP_CLEAR_MEMORY_ON_FREE
    #define configHEAP_CLEAR_MEMORY_ON_FREE    0
#endif

/* Block sizes must not get too small. */
#define heapMINIMUM_BLOCK_SIZE    ( ( size_t ) ( xHeapStructSize << 1 ) )

/* Assumes 8bit bytes! */
#define heapBITS_PER_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#define heapSIZE_MAX              ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#define heapMULTIPLY_WILL_OVERFLOW( a, b )     ( ( ( a ) > 0 ) && ( ( b ) > ( heapSIZE_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#define heapADD_WILL_OVERFLOW( a, b )          ( ( a ) > ( heapSIZE_MAX - ( b ) ) )

/* Check if the subtraction operation ( a - b ) will result in underflow. */
#define heapSUBTRACT_WILL_UNDERFLOW( a, b )    ( ( a ) < ( b ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#define heapBLOCK_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( حجم( size_t ) * heapBITS_PER_BYTE ) - 1 ) )
#define heapBLOCK_SIZE_IS_VALID( xBlockSize )    ( ( ( xBlockSize ) & heapBLOCK_ALLOCATED_BITMASK ) == 0 )
#define heapBLOCK_IS_ALLOCATED( pxBlock )        ( ( ( pxBlock->xBlockSize ) & heapBLOCK_ALLOCATED_BITMASK ) != 0 )
#define heapALLOCATE_BLOCK( pxBlock )            ( ( pxBlock->xBlockSize ) |= heapBLOCK_ALLOCATED_BITMASK )
#define heapFREE_BLOCK( pxBlock )                ( ( pxBlock->xBlockSize ) &= ~heapBLOCK_ALLOCATED_BITMASK )

/* Setting configENABLE_HEAP_PROTECTOR to 1 enables heap block pointers
 * protection using an application supplied canary value to catch heap
 * corruption should a heap buffer overflow occur.
 */
#إذا ( configENABLE_HEAP_PROTECTOR == 1 )

/* Macro to load/store BlockLink_t pointers to memory. By XORing the
 * pointers with a random canary value, heap overflows will result
 * in randomly unpredictable pointer values which will be caught by
 * heapVALIDATE_BLOCK_POINTER assert. */
    #define heapPROTECT_BLOCK_POINTER( pxBlock )    ( ( BlockLink_t * ) ( ( ( portPOINTER_SIZE_TYPE ) ( pxBlock ) ) ^ xHeapCanary ) )

/* Assert that a heap block pointer is within the heap bounds.
 * Setting configVALIDATE_HEAP_BLOCK_POINTER to 1 enables customized heap block pointers
 * protection on heap_5. */
    #ifndef configVALIDATE_HEAP_BLOCK_POINTER
        #define heapVALIDATE_BLOCK_POINTER( pxBlock )                           \
            configASSERT( ( puc_Heap_سم_Address != عدم ) &&                     \
                          ( puc_Heap_كس_Address != عدم ) &&                      \
                          ( ( uint8_t * ) ( pxBlock ) >= puc_Heap_كس_Address ) && \
                          ( ( uint8_t * ) ( pxBlock ) < puc_Heap_سم_Address ) )
    #وإلا /* ifndef configVALIDATE_HEAP_BLOCK_POINTER */
        #define heapVALIDATE_BLOCK_POINTER( pxBlock )                           \
            configVALIDATE_HEAP_BLOCK_POINTER( pxBlock )
    #endif /* configVALIDATE_HEAP_BLOCK_POINTER */

#وإلا /* if ( configENABLE_HEAP_PROTECTOR == 1 ) */

    #define heapPROTECT_BLOCK_POINTER( pxBlock )    ( pxBlock )

    #define heapVALIDATE_BLOCK_POINTER( pxBlock )

#endif /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

/* Define the linked list structure.  This is used to link free blocks in order
 * of their memory address. */
تعريفنوع بنية A_BLOCK_LINK
{
    بنية A_BLOCK_LINK * pxNextFreeBlock; /**< The next free block in the list. */
    size_t xBlockSize;                     /**< The size of the free block. */
} BlockLink_t;

/*-----------------------------------------------------------*/

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
ساكن فراغ prv_سك_Block_Into_Free_List( BlockLink_t * px_Block_To_سك ) PRIVILEGED_FUNCTION;
فراغ vPortDefineHeapRegions( ثابت HeapRegion_t * ثابت pxHeapRegions ) PRIVILEGED_FUNCTION;

#إذا ( configENABLE_HEAP_PROTECTOR == 1 )

/**
 * @brief Application provided function to get a random value to be used as canary.
 *
 * @param pxHeapCanary [out] Output parameter to return the canary value.
 */
    خارجي فراغ vApplicationGetRandomHeapCanary( portPOINTER_SIZE_TYPE * pxHeapCanary );
#endif /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

/* The size of the structure placed at the beginning of each allocated memory
 * block must by correctly byte aligned. */
ساكن ثابت size_t xHeapStructSize = ( حجم( BlockLink_t ) + ( ( size_t ) ( portBYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) portBYTE_ALIGNMENT_MASK );

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_DATA ساكن BlockLink_t xStart;
PRIVILEGED_DATA ساكن BlockLink_t * pxEnd = عدم;

/* Keeps track of the number of calls to allocate and free memory as well as the
 * number of free bytes remaining, but says nothing about fragmentation. */
PRIVILEGED_DATA ساكن size_t xFreeBytesRemaining = ( size_t ) 0U;
PRIVILEGED_DATA ساكن size_t xMinimumEverFreeBytesRemaining = ( size_t ) 0U;
PRIVILEGED_DATA ساكن size_t x_لمب_Of_Successful_Allocations = ( size_t ) 0U;
PRIVILEGED_DATA ساكن size_t x_لمب_Of_Successful_Frees = ( size_t ) 0U;

#إذا ( configENABLE_HEAP_PROTECTOR == 1 )

/* Canary value for protecting internal heap pointers. */
    PRIVILEGED_DATA ساكن portPOINTER_SIZE_TYPE xHeapCanary;

/* Highest and lowest heap addresses used for heap block bounds checking. */
    PRIVILEGED_DATA ساكن uint8_t * puc_Heap_سم_Address = عدم;
    PRIVILEGED_DATA ساكن uint8_t * puc_Heap_كس_Address = عدم;

#endif /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

فراغ * pvPortMalloc( size_t xWantedSize )
{
    BlockLink_t * pxBlock;
    BlockLink_t * pxPreviousBlock;
    BlockLink_t * pxNewBlockLink;
    فراغ * pvReturn = عدم;
    size_t xAdditionalRequiredSize;
    size_t xAllocatedBlockSize = 0;

    /* The heap must be initialised before the first call to
     * pvPortMalloc(). */
    configASSERT( pxEnd );

    إذا( xWantedSize > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        إذا( heapADD_WILL_OVERFLOW( xWantedSize, xHeapStructSize ) == 0 )
        {
            xWantedSize += xHeapStructSize;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            إذا( ( xWantedSize & portBYTE_ALIGNMENT_MASK ) != 0x00 )
            {
                /* Byte alignment required. */
                xAdditionalRequiredSize = portBYTE_ALIGNMENT - ( xWantedSize & portBYTE_ALIGNMENT_MASK );

                إذا( heapADD_WILL_OVERFLOW( xWantedSize, xAdditionalRequiredSize ) == 0 )
                {
                    xWantedSize += xAdditionalRequiredSize;
                }
                وإلا
                {
                    xWantedSize = 0;
                }
            }
            وإلا
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        وإلا
        {
            xWantedSize = 0;
        }
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }

    vTaskSuspendAll();
    {
        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        إذا( heapBLOCK_SIZE_IS_VALID( xWantedSize ) != 0 )
        {
            إذا( ( xWantedSize > 0 ) && ( xWantedSize <= xFreeBytesRemaining ) )
            {
                /* Traverse the list from the start (lowest address) block until
                 * one of adequate size is found. */
                pxPreviousBlock = &xStart;
                pxBlock = heapPROTECT_BLOCK_POINTER( xStart.pxNextFreeBlock );
                heapVALIDATE_BLOCK_POINTER( pxBlock );

                طالما( ( pxBlock->xBlockSize < xWantedSize ) && ( pxBlock->pxNextFreeBlock != heapPROTECT_BLOCK_POINTER( عدم ) ) )
                {
                    pxPreviousBlock = pxBlock;
                    pxBlock = heapPROTECT_BLOCK_POINTER( pxBlock->pxNextFreeBlock );

                    /* pxEnd is the end marker of the free list. It is located at
                     * pucHeapHighAddress and is not part of the usable heap, so it
                     * must be excluded from the heap block pointer validation. */
                    إذا( pxBlock != pxEnd )
                    {
                        heapVALIDATE_BLOCK_POINTER( pxBlock );
                    }
                }

                /* If the end marker was reached then a block of adequate size
                 * was not found. */
                إذا( pxBlock != pxEnd )
                {
                    /* Return the memory space pointed to - jumping over the
                     * BlockLink_t structure at its start. */
                    pvReturn = ( فراغ * ) ( ( ( uint8_t * ) heapPROTECT_BLOCK_POINTER( pxPreviousBlock->pxNextFreeBlock ) ) + xHeapStructSize );
                    heapVALIDATE_BLOCK_POINTER( pvReturn );

                    /* This block is being returned for use so must be taken out
                     * of the list of free blocks. */
                    pxPreviousBlock->pxNextFreeBlock = pxBlock->pxNextFreeBlock;

                    /* If the block is larger than required it can be split into
                     * two. */
                    configASSERT( heapSUBTRACT_WILL_UNDERFLOW( pxBlock->xBlockSize, xWantedSize ) == 0 );

                    إذا( ( pxBlock->xBlockSize - xWantedSize ) > heapMINIMUM_BLOCK_SIZE )
                    {
                        /* This block is to be split into two.  Create a new
                         * block following the number of bytes requested. The void
                         * cast is used to prevent byte alignment warnings from the
                         * compiler. */
                        pxNewBlockLink = ( فراغ * ) ( ( ( uint8_t * ) pxBlock ) + xWantedSize );
                        configASSERT( ( ( ( size_t ) pxNewBlockLink ) & portBYTE_ALIGNMENT_MASK ) == 0 );

                        /* Calculate the sizes of two blocks split from the
                         * single block. */
                        pxNewBlockLink->xBlockSize = pxBlock->xBlockSize - xWantedSize;
                        pxBlock->xBlockSize = xWantedSize;

                        /* Insert the new block into the list of free blocks. */
                        pxNewBlockLink->pxNextFreeBlock = pxPreviousBlock->pxNextFreeBlock;
                        pxPreviousBlock->pxNextFreeBlock = heapPROTECT_BLOCK_POINTER( pxNewBlockLink );
                    }
                    وإلا
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    xFreeBytesRemaining -= pxBlock->xBlockSize;

                    إذا( xFreeBytesRemaining < xMinimumEverFreeBytesRemaining )
                    {
                        xMinimumEverFreeBytesRemaining = xFreeBytesRemaining;
                    }
                    وإلا
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    xAllocatedBlockSize = pxBlock->xBlockSize;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    heapALLOCATE_BLOCK( pxBlock );
                    pxBlock->pxNextFreeBlock = heapPROTECT_BLOCK_POINTER( عدم );
                    x_لمب_Of_Successful_Allocations++;
                }
                وإلا
                {
                    mtCOVERAGE_TEST_MARKER();
                }
            }
            وإلا
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        وإلا
        {
            mtCOVERAGE_TEST_MARKER();
        }

        traceMALLOC( pvReturn, xAllocatedBlockSize );

        /* Prevent compiler warnings when trace macros are not used. */
        ( فراغ ) xAllocatedBlockSize;
    }
    ( فراغ ) xTaskResumeAll();

    #إذا ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        إذا( pvReturn == عدم )
        {
            vApplicationMallocFailedHook();
        }
        وإلا
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #endif /* if ( configUSE_MALLOC_FAILED_HOOK == 1 ) */

    configASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) portBYTE_ALIGNMENT_MASK ) == 0 );
    أرجع pvReturn;
}
/*-----------------------------------------------------------*/

فراغ vPortFree( فراغ * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    BlockLink_t * pxLink;

    إذا( pv != عدم )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= xHeapStructSize;

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( فراغ * ) puc;

        heapVALIDATE_BLOCK_POINTER( pxLink );
        configASSERT( heapBLOCK_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->pxNextFreeBlock == heapPROTECT_BLOCK_POINTER( عدم ) );

        إذا( heapBLOCK_IS_ALLOCATED( pxLink ) != 0 )
        {
            إذا( pxLink->pxNextFreeBlock == heapPROTECT_BLOCK_POINTER( عدم ) )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                heapFREE_BLOCK( pxLink );
                #إذا ( configHEAP_CLEAR_MEMORY_ON_FREE == 1 )
                {
                    /* Check for underflow as this can occur if xBlockSize is
                     * overwritten in a heap block. */
                    إذا( heapSUBTRACT_WILL_UNDERFLOW( pxLink->xBlockSize, xHeapStructSize ) == 0 )
                    {
                        ( فراغ ) memset( puc + xHeapStructSize, 0, pxLink->xBlockSize - xHeapStructSize );
                    }
                }
                #endif

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    xFreeBytesRemaining += pxLink->xBlockSize;
                    traceFREE( pv, pxLink->xBlockSize );
                    prv_سك_Block_Into_Free_List( ( ( BlockLink_t * ) pxLink ) );
                    x_لمب_Of_Successful_Frees++;
                }
                ( فراغ ) xTaskResumeAll();
            }
            وإلا
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        وإلا
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
}
/*-----------------------------------------------------------*/

size_t xPortGetFreeHeapSize( فراغ )
{
    أرجع xFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

size_t xPortGetMinimumEverFreeHeapSize( فراغ )
{
    أرجع xMinimumEverFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

فراغ xPortResetHeapMinimumEverFreeHeapSize( فراغ )
{
    xMinimumEverFreeBytesRemaining = xFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

فراغ * pvPortCalloc( size_t x_لمب,
                     size_t xSize )
{
    فراغ * pv = عدم;

    إذا( heapMULTIPLY_WILL_OVERFLOW( x_لمب, xSize ) == 0 )
    {
        pv = pvPortMalloc( x_لمب * xSize );

        إذا( pv != عدم )
        {
            ( فراغ ) memset( pv, 0, x_لمب * xSize );
        }
    }

    أرجع pv;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_سك_Block_Into_Free_List( BlockLink_t * px_Block_To_سك ) /* PRIVILEGED_FUNCTION */
{
    BlockLink_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    لكل( pxIterator = &xStart; heapPROTECT_BLOCK_POINTER( pxIterator->pxNextFreeBlock ) < px_Block_To_سك; pxIterator = heapPROTECT_BLOCK_POINTER( pxIterator->pxNextFreeBlock ) )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    إذا( pxIterator != &xStart )
    {
        heapVALIDATE_BLOCK_POINTER( pxIterator );
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    إذا( ( puc + pxIterator->xBlockSize ) == ( uint8_t * ) px_Block_To_سك )
    {
        pxIterator->xBlockSize += px_Block_To_سك->xBlockSize;
        px_Block_To_سك = pxIterator;
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_Block_To_سك;

    إذا( ( puc + px_Block_To_سك->xBlockSize ) == ( uint8_t * ) heapPROTECT_BLOCK_POINTER( pxIterator->pxNextFreeBlock ) )
    {
        إذا( heapPROTECT_BLOCK_POINTER( pxIterator->pxNextFreeBlock ) != pxEnd )
        {
            /* Form one big block from the two blocks. */
            px_Block_To_سك->xBlockSize += heapPROTECT_BLOCK_POINTER( pxIterator->pxNextFreeBlock )->xBlockSize;
            px_Block_To_سك->pxNextFreeBlock = heapPROTECT_BLOCK_POINTER( pxIterator->pxNextFreeBlock )->pxNextFreeBlock;
        }
        وإلا
        {
            px_Block_To_سك->pxNextFreeBlock = heapPROTECT_BLOCK_POINTER( pxEnd );
        }
    }
    وإلا
    {
        px_Block_To_سك->pxNextFreeBlock = pxIterator->pxNextFreeBlock;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    إذا( pxIterator != px_Block_To_سك )
    {
        pxIterator->pxNextFreeBlock = heapPROTECT_BLOCK_POINTER( px_Block_To_سك );
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

فراغ vPortDefineHeapRegions( ثابت HeapRegion_t * ثابت pxHeapRegions ) /* PRIVILEGED_FUNCTION */
{
    BlockLink_t * pxFirstFreeBlockInRegion = عدم;
    BlockLink_t * pxPreviousFreeBlock;
    portPOINTER_SIZE_TYPE xAlignedHeap;
    size_t xTotalRegionSize, xTotalHeapSize = 0;
    BaseType_t xDefinedRegions = 0;
    portPOINTER_SIZE_TYPE xAddress;
    ثابت HeapRegion_t * pxHeapRegion;

    /* Can only call once! */
    configASSERT( pxEnd == عدم );

    #إذا ( configENABLE_HEAP_PROTECTOR == 1 )
    {
        vApplicationGetRandomHeapCanary( &( xHeapCanary ) );
    }
    #endif

    pxHeapRegion = &( pxHeapRegions[ xDefinedRegions ] );

    طالما( pxHeapRegion->xSizeInBytes > 0 )
    {
        xTotalRegionSize = pxHeapRegion->xSizeInBytes;

        /* Ensure the heap region starts on a correctly aligned boundary. */
        xAddress = ( portPOINTER_SIZE_TYPE ) pxHeapRegion->pucStartAddress;

        إذا( ( xAddress & portBYTE_ALIGNMENT_MASK ) != 0 )
        {
            xAddress += ( portBYTE_ALIGNMENT - 1 );
            xAddress &= ~( portPOINTER_SIZE_TYPE ) portBYTE_ALIGNMENT_MASK;

            /* Adjust the size for the bytes lost to alignment. */
            xTotalRegionSize -= ( size_t ) ( xAddress - ( portPOINTER_SIZE_TYPE ) pxHeapRegion->pucStartAddress );
        }

        xAlignedHeap = xAddress;

        /* Set xStart if it has not already been set. */
        إذا( xDefinedRegions == 0 )
        {
            /* xStart is used to hold a pointer to the first item in the list of
             *  free blocks.  The void cast is used to prevent compiler warnings. */
            xStart.pxNextFreeBlock = ( BlockLink_t * ) heapPROTECT_BLOCK_POINTER( xAlignedHeap );
            xStart.xBlockSize = ( size_t ) 0;
        }
        وإلا
        {
            /* Should only get here if one region has already been added to the
             * heap. */
            configASSERT( pxEnd != heapPROTECT_BLOCK_POINTER( عدم ) );

            /* Check blocks are passed in with increasing start addresses. */
            configASSERT( ( size_t ) xAddress > ( size_t ) pxEnd );
        }

        #إذا ( configENABLE_HEAP_PROTECTOR == 1 )
        {
            إذا( ( puc_Heap_كس_Address == عدم ) ||
                ( ( uint8_t * ) xAlignedHeap < puc_Heap_كس_Address ) )
            {
                puc_Heap_كس_Address = ( uint8_t * ) xAlignedHeap;
            }
        }
        #endif /* configENABLE_HEAP_PROTECTOR */

        /* Remember the location of the end marker in the previous region, if
         * any. */
        pxPreviousFreeBlock = pxEnd;

        /* pxEnd is used to mark the end of the list of free blocks and is
         * inserted at the end of the region space. */
        xAddress = xAlignedHeap + ( portPOINTER_SIZE_TYPE ) xTotalRegionSize;
        xAddress -= ( portPOINTER_SIZE_TYPE ) xHeapStructSize;
        xAddress &= ~( ( portPOINTER_SIZE_TYPE ) portBYTE_ALIGNMENT_MASK );
        pxEnd = ( BlockLink_t * ) xAddress;
        pxEnd->xBlockSize = 0;
        pxEnd->pxNextFreeBlock = heapPROTECT_BLOCK_POINTER( عدم );

        /* To start with there is a single free block in this region that is
         * sized to take up the entire heap region minus the space taken by the
         * free block structure. */
        pxFirstFreeBlockInRegion = ( BlockLink_t * ) xAlignedHeap;
        pxFirstFreeBlockInRegion->xBlockSize = ( size_t ) ( xAddress - ( portPOINTER_SIZE_TYPE ) pxFirstFreeBlockInRegion );
        pxFirstFreeBlockInRegion->pxNextFreeBlock = heapPROTECT_BLOCK_POINTER( pxEnd );

        /* If this is not the first region that makes up the entire heap space
         * then link the previous region to this region. */
        إذا( pxPreviousFreeBlock != عدم )
        {
            pxPreviousFreeBlock->pxNextFreeBlock = heapPROTECT_BLOCK_POINTER( pxFirstFreeBlockInRegion );
        }

        xTotalHeapSize += pxFirstFreeBlockInRegion->xBlockSize;

        #إذا ( configENABLE_HEAP_PROTECTOR == 1 )
        {
            إذا( ( puc_Heap_سم_Address == عدم ) ||
                ( ( ( ( uint8_t * ) pxFirstFreeBlockInRegion ) + pxFirstFreeBlockInRegion->xBlockSize ) > puc_Heap_سم_Address ) )
            {
                puc_Heap_سم_Address = ( ( uint8_t * ) pxFirstFreeBlockInRegion ) + pxFirstFreeBlockInRegion->xBlockSize;
            }
        }
        #endif

        /* Move onto the next HeapRegion_t structure. */
        xDefinedRegions++;
        pxHeapRegion = &( pxHeapRegions[ xDefinedRegions ] );
    }

    xMinimumEverFreeBytesRemaining = xTotalHeapSize;
    xFreeBytesRemaining = xTotalHeapSize;

    /* Check something was actually defined before it is accessed. */
    configASSERT( xTotalHeapSize );
}
/*-----------------------------------------------------------*/

فراغ vPortGetHeapStats( HeapStats_t * pxHeapStats )
{
    BlockLink_t * pxBlock;
    size_t xBlocks = 0, xMaxSize = 0, xMinSize = SIZE_MAX;

    vTaskSuspendAll();
    {
        pxBlock = heapPROTECT_BLOCK_POINTER( xStart.pxNextFreeBlock );

        /* pxBlock will be NULL if the heap has not been initialised.  The heap
         * is initialised automatically when the first allocation is made. */
        إذا( pxBlock != عدم )
        {
            طالما( pxBlock != pxEnd )
            {
                /* Increment the number of blocks and record the largest block seen
                 * so far. */
                xBlocks++;

                إذا( pxBlock->xBlockSize > xMaxSize )
                {
                    xMaxSize = pxBlock->xBlockSize;
                }

                /* Heap five will have a zero sized block at the end of each
                 * each region - the block is only used to link to the next
                 * heap region so it not a real block. */
                إذا( pxBlock->xBlockSize != 0 )
                {
                    إذا( pxBlock->xBlockSize < xMinSize )
                    {
                        xMinSize = pxBlock->xBlockSize;
                    }
                }

                /* Move to the next block in the chain until the last block is
                 * reached. */
                pxBlock = heapPROTECT_BLOCK_POINTER( pxBlock->pxNextFreeBlock );
            }
        }
    }
    ( فراغ ) xTaskResumeAll();

    pxHeapStats->xSizeOfLargestFreeBlockInBytes = xMaxSize;
    pxHeapStats->xSizeOfSmallestFreeBlockInBytes = xMinSize;
    pxHeapStats->x_لمب_Of_Free_Blocks = xBlocks;

    taskENTER_CRITICAL();
    {
        pxHeapStats->xAvailableHeapSpaceInBytes = xFreeBytesRemaining;
        pxHeapStats->x_لمب_Of_Successful_Allocations = x_لمب_Of_Successful_Allocations;
        pxHeapStats->x_لمب_Of_Successful_Frees = x_لمب_Of_Successful_Frees;
        pxHeapStats->xMinimumEverFreeBytesRemaining = xMinimumEverFreeBytesRemaining;
    }
    taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
فراغ vPortHeapResetState( فراغ )
{
    pxEnd = عدم;

    xFreeBytesRemaining = ( size_t ) 0U;
    xMinimumEverFreeBytesRemaining = ( size_t ) 0U;
    x_لمب_Of_Successful_Allocations = ( size_t ) 0U;
    x_لمب_Of_Successful_Frees = ( size_t ) 0U;

    #إذا ( configENABLE_HEAP_PROTECTOR == 1 )
        puc_Heap_سم_Address = عدم;
        puc_Heap_كس_Address = عدم;
    #endif /* #if ( configENABLE_HEAP_PROTECTOR == 1 ) */
}
/*-----------------------------------------------------------*/
