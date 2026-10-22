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
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#যদি ( configSUPPORT_DYNAMIC_ALLOCATION == 0 )
    #error This file must not be used যদি configSUPPORT_DYNAMIC_ALLOCATION is 0
#endif

#ifndef configHEAP_CLEAR_MEMORY_ON_FREE
    #define configHEAP_CLEAR_MEMORY_ON_FREE    0
#endif

/* Block sizes must not get too small. */
#define heap_MINIMUM_BLOCK_আকার    ( ( size_t ) ( x_Heap_Struct_আকার << 1 ) )

/* Assumes 8bit bytes! */
#define heapBITS_PER_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#define heap_আকার_MAX              ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#define heapMULTIPLY_WILL_OVERFLOW( a, b )     ( ( ( a ) > 0 ) && ( ( b ) > ( heap_আকার_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#define heapADD_WILL_OVERFLOW( a, b )          ( ( a ) > ( heap_আকার_MAX - ( b ) ) )

/* Check if the subtraction operation ( a - b ) will result in underflow. */
#define heapSUBTRACT_WILL_UNDERFLOW( a, b )    ( ( a ) < ( b ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#define heapBLOCK_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( আকার( size_t ) * heapBITS_PER_BYTE ) - 1 ) )
#define heap_BLOCK_আকার_IS_VALID( x_Block_আকার )    ( ( ( x_Block_আকার ) & heapBLOCK_ALLOCATED_BITMASK ) == 0 )
#define heapBLOCK_IS_ALLOCATED( pxBlock )        ( ( ( pxBlock->x_Block_আকার ) & heapBLOCK_ALLOCATED_BITMASK ) != 0 )
#define heapALLOCATE_BLOCK( pxBlock )            ( ( pxBlock->x_Block_আকার ) |= heapBLOCK_ALLOCATED_BITMASK )
#define heapFREE_BLOCK( pxBlock )                ( ( pxBlock->x_Block_আকার ) &= ~heapBLOCK_ALLOCATED_BITMASK )

/* Setting configENABLE_HEAP_PROTECTOR to 1 enables heap block pointers
 * protection using an application supplied canary value to catch heap
 * corruption should a heap buffer overflow occur.
 */
#যদি ( configENABLE_HEAP_PROTECTOR == 1 )

/* Macro to load/store BlockLink_t pointers to memory. By XORing the
 * pointers with a random canary value, heap overflows will result
 * in randomly unpredictable pointer values which will be caught by
 * heapVALIDATE_BLOCK_POINTER assert. */
    #define heapPROTECT_BLOCK_POINTER( pxBlock )    ( ( BlockLink_t * ) ( ( ( port_POINTER_আকার_TYPE ) ( pxBlock ) ) ^ xHeapCanary ) )

/* Assert that a heap block pointer is within the heap bounds.
 * Setting configVALIDATE_HEAP_BLOCK_POINTER to 1 enables customized heap block pointers
 * protection on heap_5. */
    #ifndef configVALIDATE_HEAP_BLOCK_POINTER
        #define heapVALIDATE_BLOCK_POINTER( pxBlock )                           \
            configASSERT( ( puc_Heap_উপরের_Address != ফাঁকা ) &&                     \
                          ( puc_Heap_নিচের_Address != ফাঁকা ) &&                      \
                          ( ( uint8_t * ) ( pxBlock ) >= puc_Heap_নিচের_Address ) && \
                          ( ( uint8_t * ) ( pxBlock ) < puc_Heap_উপরের_Address ) )
    #অন্যথা /* ifndef configVALIDATE_HEAP_BLOCK_POINTER */
        #define heapVALIDATE_BLOCK_POINTER( pxBlock )                           \
            configVALIDATE_HEAP_BLOCK_POINTER( pxBlock )
    #endif /* configVALIDATE_HEAP_BLOCK_POINTER */

#অন্যথা /* if ( configENABLE_HEAP_PROTECTOR == 1 ) */

    #define heapPROTECT_BLOCK_POINTER( pxBlock )    ( pxBlock )

    #define heapVALIDATE_BLOCK_POINTER( pxBlock )

#endif /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

/* Define the linked list structure.  This is used to link free blocks in order
 * of their memory address. */
প্রকারলেখ কাঠামো A_BLOCK_LINK
{
    কাঠামো A_BLOCK_LINK * px_পরবর্তী_Free_Block; /**< The next free block in the list. */
    size_t x_Block_আকার;                     /**< The size of the free block. */
} BlockLink_t;

/*-----------------------------------------------------------*/

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
স্থির শূন্য prv_ঢোকাও_Block_Into_Free_List( BlockLink_t * px_Block_To_ঢোকাও ) PRIVILEGED_FUNCTION;
শূন্য vPortDefineHeapRegions( ধ্রুবক HeapRegion_t * ধ্রুবক pxHeapRegions ) PRIVILEGED_FUNCTION;

#যদি ( configENABLE_HEAP_PROTECTOR == 1 )

/**
 * @brief Application provided function to get a random value to be used as canary.
 *
 * @param pxHeapCanary [out] Output parameter to return the canary value.
 */
    বাহ্যিক শূন্য vApplicationGetRandomHeapCanary( port_POINTER_আকার_TYPE * pxHeapCanary );
#endif /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

/* The size of the structure placed at the beginning of each allocated memory
 * block must by correctly byte aligned. */
স্থির ধ্রুবক size_t x_Heap_Struct_আকার = ( আকার( BlockLink_t ) + ( ( size_t ) ( portBYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) portBYTE_ALIGNMENT_MASK );

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_তথ্য স্থির BlockLink_t xStart;
PRIVILEGED_তথ্য স্থির BlockLink_t * pxEnd = ফাঁকা;

/* Keeps track of the number of calls to allocate and free memory as well as the
 * number of free bytes remaining, but says nothing about fragmentation. */
PRIVILEGED_তথ্য স্থির size_t xFreeBytesRemaining = ( size_t ) 0U;
PRIVILEGED_তথ্য স্থির size_t xMinimumEverFreeBytesRemaining = ( size_t ) 0U;
PRIVILEGED_তথ্য স্থির size_t x_সংখ্যা_Of_Successful_Allocations = ( size_t ) 0U;
PRIVILEGED_তথ্য স্থির size_t x_সংখ্যা_Of_Successful_Frees = ( size_t ) 0U;

#যদি ( configENABLE_HEAP_PROTECTOR == 1 )

/* Canary value for protecting internal heap pointers. */
    PRIVILEGED_তথ্য স্থির port_POINTER_আকার_TYPE xHeapCanary;

/* Highest and lowest heap addresses used for heap block bounds checking. */
    PRIVILEGED_তথ্য স্থির uint8_t * puc_Heap_উপরের_Address = ফাঁকা;
    PRIVILEGED_তথ্য স্থির uint8_t * puc_Heap_নিচের_Address = ফাঁকা;

#endif /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

শূন্য * pvPortMalloc( size_t x_Wanted_আকার )
{
    BlockLink_t * pxBlock;
    BlockLink_t * pxPreviousBlock;
    BlockLink_t * pxNewBlockLink;
    শূন্য * pvReturn = ফাঁকা;
    size_t x_Additional_Required_আকার;
    size_t x_Allocated_Block_আকার = 0;

    /* The heap must be initialised before the first call to
     * pvPortMalloc(). */
    configASSERT( pxEnd );

    যদি( x_Wanted_আকার > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        যদি( heapADD_WILL_OVERFLOW( x_Wanted_আকার, x_Heap_Struct_আকার ) == 0 )
        {
            x_Wanted_আকার += x_Heap_Struct_আকার;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            যদি( ( x_Wanted_আকার & portBYTE_ALIGNMENT_MASK ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_আকার = portBYTE_ALIGNMENT - ( x_Wanted_আকার & portBYTE_ALIGNMENT_MASK );

                যদি( heapADD_WILL_OVERFLOW( x_Wanted_আকার, x_Additional_Required_আকার ) == 0 )
                {
                    x_Wanted_আকার += x_Additional_Required_আকার;
                }
                অন্যথা
                {
                    x_Wanted_আকার = 0;
                }
            }
            অন্যথা
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        অন্যথা
        {
            x_Wanted_আকার = 0;
        }
    }
    অন্যথা
    {
        mtCOVERAGE_TEST_MARKER();
    }

    vTaskSuspendAll();
    {
        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        যদি( heap_BLOCK_আকার_IS_VALID( x_Wanted_আকার ) != 0 )
        {
            যদি( ( x_Wanted_আকার > 0 ) && ( x_Wanted_আকার <= xFreeBytesRemaining ) )
            {
                /* Traverse the list from the start (lowest address) block until
                 * one of adequate size is found. */
                pxPreviousBlock = &xStart;
                pxBlock = heapPROTECT_BLOCK_POINTER( xStart.px_পরবর্তী_Free_Block );
                heapVALIDATE_BLOCK_POINTER( pxBlock );

                যখন( ( pxBlock->x_Block_আকার < x_Wanted_আকার ) && ( pxBlock->px_পরবর্তী_Free_Block != heapPROTECT_BLOCK_POINTER( ফাঁকা ) ) )
                {
                    pxPreviousBlock = pxBlock;
                    pxBlock = heapPROTECT_BLOCK_POINTER( pxBlock->px_পরবর্তী_Free_Block );

                    /* pxEnd is the end marker of the free list. It is located at
                     * pucHeapHighAddress and is not part of the usable heap, so it
                     * must be excluded from the heap block pointer validation. */
                    যদি( pxBlock != pxEnd )
                    {
                        heapVALIDATE_BLOCK_POINTER( pxBlock );
                    }
                }

                /* If the end marker was reached then a block of adequate size
                 * was not found. */
                যদি( pxBlock != pxEnd )
                {
                    /* Return the memory space pointed to - jumping over the
                     * BlockLink_t structure at its start. */
                    pvReturn = ( শূন্য * ) ( ( ( uint8_t * ) heapPROTECT_BLOCK_POINTER( pxPreviousBlock->px_পরবর্তী_Free_Block ) ) + x_Heap_Struct_আকার );
                    heapVALIDATE_BLOCK_POINTER( pvReturn );

                    /* This block is being returned for use so must be taken out
                     * of the list of free blocks. */
                    pxPreviousBlock->px_পরবর্তী_Free_Block = pxBlock->px_পরবর্তী_Free_Block;

                    /* If the block is larger than required it can be split into
                     * two. */
                    configASSERT( heapSUBTRACT_WILL_UNDERFLOW( pxBlock->x_Block_আকার, x_Wanted_আকার ) == 0 );

                    যদি( ( pxBlock->x_Block_আকার - x_Wanted_আকার ) > heap_MINIMUM_BLOCK_আকার )
                    {
                        /* This block is to be split into two.  Create a new
                         * block following the number of bytes requested. The void
                         * cast is used to prevent byte alignment warnings from the
                         * compiler. */
                        pxNewBlockLink = ( শূন্য * ) ( ( ( uint8_t * ) pxBlock ) + x_Wanted_আকার );
                        configASSERT( ( ( ( size_t ) pxNewBlockLink ) & portBYTE_ALIGNMENT_MASK ) == 0 );

                        /* Calculate the sizes of two blocks split from the
                         * single block. */
                        pxNewBlockLink->x_Block_আকার = pxBlock->x_Block_আকার - x_Wanted_আকার;
                        pxBlock->x_Block_আকার = x_Wanted_আকার;

                        /* Insert the new block into the list of free blocks. */
                        pxNewBlockLink->px_পরবর্তী_Free_Block = pxPreviousBlock->px_পরবর্তী_Free_Block;
                        pxPreviousBlock->px_পরবর্তী_Free_Block = heapPROTECT_BLOCK_POINTER( pxNewBlockLink );
                    }
                    অন্যথা
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    xFreeBytesRemaining -= pxBlock->x_Block_আকার;

                    যদি( xFreeBytesRemaining < xMinimumEverFreeBytesRemaining )
                    {
                        xMinimumEverFreeBytesRemaining = xFreeBytesRemaining;
                    }
                    অন্যথা
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Allocated_Block_আকার = pxBlock->x_Block_আকার;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    heapALLOCATE_BLOCK( pxBlock );
                    pxBlock->px_পরবর্তী_Free_Block = heapPROTECT_BLOCK_POINTER( ফাঁকা );
                    x_সংখ্যা_Of_Successful_Allocations++;
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

        traceMALLOC( pvReturn, x_Allocated_Block_আকার );

        /* Prevent compiler warnings when trace macros are not used. */
        ( শূন্য ) x_Allocated_Block_আকার;
    }
    ( শূন্য ) xTaskResumeAll();

    #যদি ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        যদি( pvReturn == ফাঁকা )
        {
            vApplicationMallocFailedHook();
        }
        অন্যথা
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #endif /* if ( configUSE_MALLOC_FAILED_HOOK == 1 ) */

    configASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) portBYTE_ALIGNMENT_MASK ) == 0 );
    ফেরত pvReturn;
}
/*-----------------------------------------------------------*/

শূন্য vPortFree( শূন্য * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    BlockLink_t * pxLink;

    যদি( pv != ফাঁকা )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_Heap_Struct_আকার;

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( শূন্য * ) puc;

        heapVALIDATE_BLOCK_POINTER( pxLink );
        configASSERT( heapBLOCK_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_পরবর্তী_Free_Block == heapPROTECT_BLOCK_POINTER( ফাঁকা ) );

        যদি( heapBLOCK_IS_ALLOCATED( pxLink ) != 0 )
        {
            যদি( pxLink->px_পরবর্তী_Free_Block == heapPROTECT_BLOCK_POINTER( ফাঁকা ) )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                heapFREE_BLOCK( pxLink );
                #যদি ( configHEAP_CLEAR_MEMORY_ON_FREE == 1 )
                {
                    /* Check for underflow as this can occur if xBlockSize is
                     * overwritten in a heap block. */
                    যদি( heapSUBTRACT_WILL_UNDERFLOW( pxLink->x_Block_আকার, x_Heap_Struct_আকার ) == 0 )
                    {
                        ( শূন্য ) memset( puc + x_Heap_Struct_আকার, 0, pxLink->x_Block_আকার - x_Heap_Struct_আকার );
                    }
                }
                #endif

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    xFreeBytesRemaining += pxLink->x_Block_আকার;
                    traceFREE( pv, pxLink->x_Block_আকার );
                    prv_ঢোকাও_Block_Into_Free_List( ( ( BlockLink_t * ) pxLink ) );
                    x_সংখ্যা_Of_Successful_Frees++;
                }
                ( শূন্য ) xTaskResumeAll();
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

size_t x_Port_Get_Free_Heap_আকার( শূন্য )
{
    ফেরত xFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

size_t x_Port_Get_Minimum_Ever_Free_Heap_আকার( শূন্য )
{
    ফেরত xMinimumEverFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

শূন্য x_Port_Reset_Heap_Minimum_Ever_Free_Heap_আকার( শূন্য )
{
    xMinimumEverFreeBytesRemaining = xFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

শূন্য * pvPortCalloc( size_t x_অঙ্ক,
                     size_t x_আকার )
{
    শূন্য * pv = ফাঁকা;

    যদি( heapMULTIPLY_WILL_OVERFLOW( x_অঙ্ক, x_আকার ) == 0 )
    {
        pv = pvPortMalloc( x_অঙ্ক * x_আকার );

        যদি( pv != ফাঁকা )
        {
            ( শূন্য ) memset( pv, 0, x_অঙ্ক * x_আকার );
        }
    }

    ফেরত pv;
}
/*-----------------------------------------------------------*/

স্থির শূন্য prv_ঢোকাও_Block_Into_Free_List( BlockLink_t * px_Block_To_ঢোকাও ) /* PRIVILEGED_FUNCTION */
{
    BlockLink_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    জন্য( pxIterator = &xStart; heapPROTECT_BLOCK_POINTER( pxIterator->px_পরবর্তী_Free_Block ) < px_Block_To_ঢোকাও; pxIterator = heapPROTECT_BLOCK_POINTER( pxIterator->px_পরবর্তী_Free_Block ) )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    যদি( pxIterator != &xStart )
    {
        heapVALIDATE_BLOCK_POINTER( pxIterator );
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    যদি( ( puc + pxIterator->x_Block_আকার ) == ( uint8_t * ) px_Block_To_ঢোকাও )
    {
        pxIterator->x_Block_আকার += px_Block_To_ঢোকাও->x_Block_আকার;
        px_Block_To_ঢোকাও = pxIterator;
    }
    অন্যথা
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_Block_To_ঢোকাও;

    যদি( ( puc + px_Block_To_ঢোকাও->x_Block_আকার ) == ( uint8_t * ) heapPROTECT_BLOCK_POINTER( pxIterator->px_পরবর্তী_Free_Block ) )
    {
        যদি( heapPROTECT_BLOCK_POINTER( pxIterator->px_পরবর্তী_Free_Block ) != pxEnd )
        {
            /* Form one big block from the two blocks. */
            px_Block_To_ঢোকাও->x_Block_আকার += heapPROTECT_BLOCK_POINTER( pxIterator->px_পরবর্তী_Free_Block )->x_Block_আকার;
            px_Block_To_ঢোকাও->px_পরবর্তী_Free_Block = heapPROTECT_BLOCK_POINTER( pxIterator->px_পরবর্তী_Free_Block )->px_পরবর্তী_Free_Block;
        }
        অন্যথা
        {
            px_Block_To_ঢোকাও->px_পরবর্তী_Free_Block = heapPROTECT_BLOCK_POINTER( pxEnd );
        }
    }
    অন্যথা
    {
        px_Block_To_ঢোকাও->px_পরবর্তী_Free_Block = pxIterator->px_পরবর্তী_Free_Block;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    যদি( pxIterator != px_Block_To_ঢোকাও )
    {
        pxIterator->px_পরবর্তী_Free_Block = heapPROTECT_BLOCK_POINTER( px_Block_To_ঢোকাও );
    }
    অন্যথা
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

শূন্য vPortDefineHeapRegions( ধ্রুবক HeapRegion_t * ধ্রুবক pxHeapRegions ) /* PRIVILEGED_FUNCTION */
{
    BlockLink_t * pxFirstFreeBlockInRegion = ফাঁকা;
    BlockLink_t * pxPreviousFreeBlock;
    port_POINTER_আকার_TYPE xAlignedHeap;
    size_t x_যোগ_Region_আকার, x_যোগ_Heap_আকার = 0;
    BaseType_t xDefinedRegions = 0;
    port_POINTER_আকার_TYPE xAddress;
    ধ্রুবক HeapRegion_t * pxHeapRegion;

    /* Can only call once! */
    configASSERT( pxEnd == ফাঁকা );

    #যদি ( configENABLE_HEAP_PROTECTOR == 1 )
    {
        vApplicationGetRandomHeapCanary( &( xHeapCanary ) );
    }
    #endif

    pxHeapRegion = &( pxHeapRegions[ xDefinedRegions ] );

    যখন( pxHeapRegion->x_আকার_In_Bytes > 0 )
    {
        x_যোগ_Region_আকার = pxHeapRegion->x_আকার_In_Bytes;

        /* Ensure the heap region starts on a correctly aligned boundary. */
        xAddress = ( port_POINTER_আকার_TYPE ) pxHeapRegion->pucStartAddress;

        যদি( ( xAddress & portBYTE_ALIGNMENT_MASK ) != 0 )
        {
            xAddress += ( portBYTE_ALIGNMENT - 1 );
            xAddress &= ~( port_POINTER_আকার_TYPE ) portBYTE_ALIGNMENT_MASK;

            /* Adjust the size for the bytes lost to alignment. */
            x_যোগ_Region_আকার -= ( size_t ) ( xAddress - ( port_POINTER_আকার_TYPE ) pxHeapRegion->pucStartAddress );
        }

        xAlignedHeap = xAddress;

        /* Set xStart if it has not already been set. */
        যদি( xDefinedRegions == 0 )
        {
            /* xStart is used to hold a pointer to the first item in the list of
             *  free blocks.  The void cast is used to prevent compiler warnings. */
            xStart.px_পরবর্তী_Free_Block = ( BlockLink_t * ) heapPROTECT_BLOCK_POINTER( xAlignedHeap );
            xStart.x_Block_আকার = ( size_t ) 0;
        }
        অন্যথা
        {
            /* Should only get here if one region has already been added to the
             * heap. */
            configASSERT( pxEnd != heapPROTECT_BLOCK_POINTER( ফাঁকা ) );

            /* Check blocks are passed in with increasing start addresses. */
            configASSERT( ( size_t ) xAddress > ( size_t ) pxEnd );
        }

        #যদি ( configENABLE_HEAP_PROTECTOR == 1 )
        {
            যদি( ( puc_Heap_নিচের_Address == ফাঁকা ) ||
                ( ( uint8_t * ) xAlignedHeap < puc_Heap_নিচের_Address ) )
            {
                puc_Heap_নিচের_Address = ( uint8_t * ) xAlignedHeap;
            }
        }
        #endif /* configENABLE_HEAP_PROTECTOR */

        /* Remember the location of the end marker in the previous region, if
         * any. */
        pxPreviousFreeBlock = pxEnd;

        /* pxEnd is used to mark the end of the list of free blocks and is
         * inserted at the end of the region space. */
        xAddress = xAlignedHeap + ( port_POINTER_আকার_TYPE ) x_যোগ_Region_আকার;
        xAddress -= ( port_POINTER_আকার_TYPE ) x_Heap_Struct_আকার;
        xAddress &= ~( ( port_POINTER_আকার_TYPE ) portBYTE_ALIGNMENT_MASK );
        pxEnd = ( BlockLink_t * ) xAddress;
        pxEnd->x_Block_আকার = 0;
        pxEnd->px_পরবর্তী_Free_Block = heapPROTECT_BLOCK_POINTER( ফাঁকা );

        /* To start with there is a single free block in this region that is
         * sized to take up the entire heap region minus the space taken by the
         * free block structure. */
        pxFirstFreeBlockInRegion = ( BlockLink_t * ) xAlignedHeap;
        pxFirstFreeBlockInRegion->x_Block_আকার = ( size_t ) ( xAddress - ( port_POINTER_আকার_TYPE ) pxFirstFreeBlockInRegion );
        pxFirstFreeBlockInRegion->px_পরবর্তী_Free_Block = heapPROTECT_BLOCK_POINTER( pxEnd );

        /* If this is not the first region that makes up the entire heap space
         * then link the previous region to this region. */
        যদি( pxPreviousFreeBlock != ফাঁকা )
        {
            pxPreviousFreeBlock->px_পরবর্তী_Free_Block = heapPROTECT_BLOCK_POINTER( pxFirstFreeBlockInRegion );
        }

        x_যোগ_Heap_আকার += pxFirstFreeBlockInRegion->x_Block_আকার;

        #যদি ( configENABLE_HEAP_PROTECTOR == 1 )
        {
            যদি( ( puc_Heap_উপরের_Address == ফাঁকা ) ||
                ( ( ( ( uint8_t * ) pxFirstFreeBlockInRegion ) + pxFirstFreeBlockInRegion->x_Block_আকার ) > puc_Heap_উপরের_Address ) )
            {
                puc_Heap_উপরের_Address = ( ( uint8_t * ) pxFirstFreeBlockInRegion ) + pxFirstFreeBlockInRegion->x_Block_আকার;
            }
        }
        #endif

        /* Move onto the next HeapRegion_t structure. */
        xDefinedRegions++;
        pxHeapRegion = &( pxHeapRegions[ xDefinedRegions ] );
    }

    xMinimumEverFreeBytesRemaining = x_যোগ_Heap_আকার;
    xFreeBytesRemaining = x_যোগ_Heap_আকার;

    /* Check something was actually defined before it is accessed. */
    configASSERT( x_যোগ_Heap_আকার );
}
/*-----------------------------------------------------------*/

শূন্য vPortGetHeapStats( HeapStats_t * pxHeapStats )
{
    BlockLink_t * pxBlock;
    size_t xBlocks = 0, x_Max_আকার = 0, x_Min_আকার = SIZE_MAX;

    vTaskSuspendAll();
    {
        pxBlock = heapPROTECT_BLOCK_POINTER( xStart.px_পরবর্তী_Free_Block );

        /* pxBlock will be NULL if the heap has not been initialised.  The heap
         * is initialised automatically when the first allocation is made. */
        যদি( pxBlock != ফাঁকা )
        {
            যখন( pxBlock != pxEnd )
            {
                /* Increment the number of blocks and record the largest block seen
                 * so far. */
                xBlocks++;

                যদি( pxBlock->x_Block_আকার > x_Max_আকার )
                {
                    x_Max_আকার = pxBlock->x_Block_আকার;
                }

                /* Heap five will have a zero sized block at the end of each
                 * each region - the block is only used to link to the next
                 * heap region so it not a real block. */
                যদি( pxBlock->x_Block_আকার != 0 )
                {
                    যদি( pxBlock->x_Block_আকার < x_Min_আকার )
                    {
                        x_Min_আকার = pxBlock->x_Block_আকার;
                    }
                }

                /* Move to the next block in the chain until the last block is
                 * reached. */
                pxBlock = heapPROTECT_BLOCK_POINTER( pxBlock->px_পরবর্তী_Free_Block );
            }
        }
    }
    ( শূন্য ) xTaskResumeAll();

    pxHeapStats->x_আকার_Of_Largest_Free_Block_In_Bytes = x_Max_আকার;
    pxHeapStats->x_আকার_Of_Smallest_Free_Block_In_Bytes = x_Min_আকার;
    pxHeapStats->x_সংখ্যা_Of_Free_Blocks = xBlocks;

    taskENTER_CRITICAL();
    {
        pxHeapStats->xAvailableHeapSpaceInBytes = xFreeBytesRemaining;
        pxHeapStats->x_সংখ্যা_Of_Successful_Allocations = x_সংখ্যা_Of_Successful_Allocations;
        pxHeapStats->x_সংখ্যা_Of_Successful_Frees = x_সংখ্যা_Of_Successful_Frees;
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
শূন্য vPortHeapResetState( শূন্য )
{
    pxEnd = ফাঁকা;

    xFreeBytesRemaining = ( size_t ) 0U;
    xMinimumEverFreeBytesRemaining = ( size_t ) 0U;
    x_সংখ্যা_Of_Successful_Allocations = ( size_t ) 0U;
    x_সংখ্যা_Of_Successful_Frees = ( size_t ) 0U;

    #যদি ( configENABLE_HEAP_PROTECTOR == 1 )
        puc_Heap_উপরের_Address = ফাঁকা;
        puc_Heap_নিচের_Address = ফাঁকা;
    #endif /* #if ( configENABLE_HEAP_PROTECTOR == 1 ) */
}
/*-----------------------------------------------------------*/
