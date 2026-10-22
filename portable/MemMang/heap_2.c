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

/* A few bytes might be lost to byte aligning the heap start address. */
#define config_ADJUSTED_HEAP_আকার    ( config_যোগ_HEAP_আকার - portBYTE_ALIGNMENT )

/* Assumes 8bit bytes! */
#define heapBITS_PER_BYTE           ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#define heap_আকার_MAX                ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#define heapMULTIPLY_WILL_OVERFLOW( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( heap_আকার_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#define heapADD_WILL_OVERFLOW( a, b )         ( ( a ) > ( heap_আকার_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#define heapBLOCK_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( আকার( size_t ) * heapBITS_PER_BYTE ) - 1 ) )
#define heap_BLOCK_আকার_IS_VALID( x_Block_আকার )    ( ( ( x_Block_আকার ) & heapBLOCK_ALLOCATED_BITMASK ) == 0 )
#define heapBLOCK_IS_ALLOCATED( pxBlock )        ( ( ( pxBlock->x_Block_আকার ) & heapBLOCK_ALLOCATED_BITMASK ) != 0 )
#define heapALLOCATE_BLOCK( pxBlock )            ( ( pxBlock->x_Block_আকার ) |= heapBLOCK_ALLOCATED_BITMASK )
#define heapFREE_BLOCK( pxBlock )                ( ( pxBlock->x_Block_আকার ) &= ~heapBLOCK_ALLOCATED_BITMASK )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#যদি ( configAPPLICATION_ALLOCATED_HEAP == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    বাহ্যিক uint8_t ucHeap[ config_যোগ_HEAP_আকার ];
#অন্যথা
    PRIVILEGED_তথ্য স্থির uint8_t ucHeap[ config_যোগ_HEAP_আকার ];
#endif /* configAPPLICATION_ALLOCATED_HEAP */


/* Define the linked list structure.  This is used to link free blocks in order
 * of their size. */
প্রকারলেখ কাঠামো A_BLOCK_LINK
{
    কাঠামো A_BLOCK_LINK * px_পরবর্তী_Free_Block; /*<< The next free block in the list. */
    size_t x_Block_আকার;                     /*<< The size of the free block. */
} BlockLink_t;


স্থির ধ্রুবক size_t x_Heap_Struct_আকার = ( ( আকার( BlockLink_t ) + ( size_t ) ( portBYTE_ALIGNMENT - 1 ) ) & ~( ( size_t ) portBYTE_ALIGNMENT_MASK ) );
#define heap_MINIMUM_BLOCK_আকার    ( ( size_t ) ( x_Heap_Struct_আকার * 2 ) )

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_তথ্য স্থির BlockLink_t xStart, xEnd;

/* Keeps track of the number of free bytes remaining, but says nothing about
 * fragmentation. */
PRIVILEGED_তথ্য স্থির size_t xFreeBytesRemaining = config_ADJUSTED_HEAP_আকার;

/* Indicates whether the heap has been initialised or not. */
PRIVILEGED_তথ্য স্থির BaseType_t xHeapHasBeenInitialised = pdFALSE;

/*-----------------------------------------------------------*/

/*
 * Initialises the heap structures before their first use.
 */
স্থির শূন্য prvHeapInit( শূন্য ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* STATIC FUNCTIONS ARE DEFINED AS MACROS TO MINIMIZE THE FUNCTION CALL DEPTH. */

/*
 * Insert a block into the list of free blocks - which is ordered by size of
 * the block.  Small blocks at the start of the list and large blocks at the end
 * of the list.
 */
#define prv_ঢোকাও_Block_Into_Free_List( px_Block_To_ঢোকাও )                                                                               \
    {                                                                                                                               \
        BlockLink_t * pxIterator;                                                                                                   \
        size_t x_Block_আকার;                                                                                                          \
                                                                                                                                    \
        x_Block_আকার = px_Block_To_ঢোকাও->x_Block_আকার;                                                                                   \
                                                                                                                                    \
        /* Iterate through the list until a block is found that has a larger size */                                                \
        /* than the block we are inserting. */                                                                                      \
        জন্য( pxIterator = &xStart; pxIterator->px_পরবর্তী_Free_Block->x_Block_আকার < x_Block_আকার; pxIterator = pxIterator->px_পরবর্তী_Free_Block ) \
        {                                                                                                                           \
            /* There is nothing to do here - just iterate to the correct position. */                                               \
        }                                                                                                                           \
                                                                                                                                    \
        /* Update the list to include the block being inserted in the correct */                                                    \
        /* position. */                                                                                                             \
        px_Block_To_ঢোকাও->px_পরবর্তী_Free_Block = pxIterator->px_পরবর্তী_Free_Block;                                                             \
        pxIterator->px_পরবর্তী_Free_Block = px_Block_To_ঢোকাও;                                                                              \
    }
/*-----------------------------------------------------------*/

শূন্য * pvPortMalloc( size_t x_Wanted_আকার )
{
    BlockLink_t * pxBlock;
    BlockLink_t * pxPreviousBlock;
    BlockLink_t * pxNewBlockLink;
    শূন্য * pvReturn = ফাঁকা;
    size_t x_Additional_Required_আকার;
    size_t x_Allocated_Block_আকার = 0;

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
        /* If this is the first call to malloc then the heap will require
         * initialisation to setup the list of free blocks. */
        যদি( xHeapHasBeenInitialised == pdFALSE )
        {
            prvHeapInit();
            xHeapHasBeenInitialised = pdTRUE;
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        যদি( heap_BLOCK_আকার_IS_VALID( x_Wanted_আকার ) != 0 )
        {
            যদি( ( x_Wanted_আকার > 0 ) && ( x_Wanted_আকার <= xFreeBytesRemaining ) )
            {
                /* Blocks are stored in byte order - traverse the list from the start
                 * (smallest) block until one of adequate size is found. */
                pxPreviousBlock = &xStart;
                pxBlock = xStart.px_পরবর্তী_Free_Block;

                যখন( ( pxBlock->x_Block_আকার < x_Wanted_আকার ) && ( pxBlock->px_পরবর্তী_Free_Block != ফাঁকা ) )
                {
                    pxPreviousBlock = pxBlock;
                    pxBlock = pxBlock->px_পরবর্তী_Free_Block;
                }

                /* If we found the end marker then a block of adequate size was not found. */
                যদি( pxBlock != &xEnd )
                {
                    /* Return the memory space - jumping over the BlockLink_t structure
                     * at its start. */
                    pvReturn = ( শূন্য * ) ( ( ( uint8_t * ) pxPreviousBlock->px_পরবর্তী_Free_Block ) + x_Heap_Struct_আকার );

                    /* This block is being returned for use so must be taken out of the
                     * list of free blocks. */
                    pxPreviousBlock->px_পরবর্তী_Free_Block = pxBlock->px_পরবর্তী_Free_Block;

                    /* If the block is larger than required it can be split into two. */
                    যদি( ( pxBlock->x_Block_আকার - x_Wanted_আকার ) > heap_MINIMUM_BLOCK_আকার )
                    {
                        /* This block is to be split into two.  Create a new block
                         * following the number of bytes requested. The void cast is
                         * used to prevent byte alignment warnings from the compiler. */
                        pxNewBlockLink = ( শূন্য * ) ( ( ( uint8_t * ) pxBlock ) + x_Wanted_আকার );

                        /* Calculate the sizes of two blocks split from the single
                         * block. */
                        pxNewBlockLink->x_Block_আকার = pxBlock->x_Block_আকার - x_Wanted_আকার;
                        pxBlock->x_Block_আকার = x_Wanted_আকার;

                        /* Insert the new block into the list of free blocks.
                         * The list of free blocks is sorted by their size, we have to
                         * iterate to find the right place to insert new block. */
                        prv_ঢোকাও_Block_Into_Free_List( ( pxNewBlockLink ) );
                    }

                    xFreeBytesRemaining -= pxBlock->x_Block_আকার;

                    x_Allocated_Block_আকার = pxBlock->x_Block_আকার;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    heapALLOCATE_BLOCK( pxBlock );
                    pxBlock->px_পরবর্তী_Free_Block = ফাঁকা;
                }
            }
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
    }
    #endif

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

        /* This unexpected casting is to keep some compilers from issuing
         * byte alignment warnings. */
        pxLink = ( শূন্য * ) puc;

        configASSERT( heapBLOCK_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_পরবর্তী_Free_Block == ফাঁকা );

        যদি( heapBLOCK_IS_ALLOCATED( pxLink ) != 0 )
        {
            যদি( pxLink->px_পরবর্তী_Free_Block == ফাঁকা )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                heapFREE_BLOCK( pxLink );
                #যদি ( configHEAP_CLEAR_MEMORY_ON_FREE == 1 )
                {
                    ( শূন্য ) memset( puc + x_Heap_Struct_আকার, 0, pxLink->x_Block_আকার - x_Heap_Struct_আকার );
                }
                #endif

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    prv_ঢোকাও_Block_Into_Free_List( ( ( BlockLink_t * ) pxLink ) );
                    xFreeBytesRemaining += pxLink->x_Block_আকার;
                    traceFREE( pv, pxLink->x_Block_আকার );
                }
                ( শূন্য ) xTaskResumeAll();
            }
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_Port_Get_Free_Heap_আকার( শূন্য )
{
    ফেরত xFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

শূন্য vPortInitialiseBlocks( শূন্য )
{
    /* This just exists to keep the linker quiet. */
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

স্থির শূন্য prvHeapInit( শূন্য ) /* PRIVILEGED_FUNCTION */
{
    BlockLink_t * pxFirstFreeBlock;
    uint8_t * pucAlignedHeap;

    /* Ensure the heap starts on a correctly aligned boundary. */
    pucAlignedHeap = ( uint8_t * ) ( ( ( port_POINTER_আকার_TYPE ) & ucHeap[ portBYTE_ALIGNMENT - 1 ] ) & ( ~( ( port_POINTER_আকার_TYPE ) portBYTE_ALIGNMENT_MASK ) ) );

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    xStart.px_পরবর্তী_Free_Block = ( শূন্য * ) pucAlignedHeap;
    xStart.x_Block_আকার = ( size_t ) 0;

    /* xEnd is used to mark the end of the list of free blocks. */
    xEnd.x_Block_আকার = config_ADJUSTED_HEAP_আকার;
    xEnd.px_পরবর্তী_Free_Block = ফাঁকা;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space. */
    pxFirstFreeBlock = ( BlockLink_t * ) pucAlignedHeap;
    pxFirstFreeBlock->x_Block_আকার = config_ADJUSTED_HEAP_আকার;
    pxFirstFreeBlock->px_পরবর্তী_Free_Block = &xEnd;
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
শূন্য vPortHeapResetState( শূন্য )
{
    xFreeBytesRemaining = config_ADJUSTED_HEAP_আকার;

    xHeapHasBeenInitialised = pdFALSE;
}
/*-----------------------------------------------------------*/
