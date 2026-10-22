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
#समावेश <stdlib.h>
#समावेश <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#घोषणा MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#समावेश "FreeRTOS.h"
#समावेश "task.h"

#अघोषित MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#अगर ( configSUPPORT_DYNAMIC_ALLOCATION == 0 )
    #त्रुटि This file must not be used अगर configSUPPORT_DYNAMIC_ALLOCATION is 0
#पूर्ण_अगर

#अगर_अघोषित configHEAP_CLEAR_MEMORY_ON_FREE
    #घोषणा configHEAP_CLEAR_MEMORY_ON_FREE    0
#पूर्ण_अगर

/* A few bytes might be lost to byte aligning the heap start address. */
#घोषणा config_ADJUSTED_HEAP_आकार    ( config_योग_HEAP_आकार - portBYTE_ALIGNMENT )

/* Assumes 8bit bytes! */
#घोषणा heapBITS_PER_BYTE           ( ( माप_प्रकार ) 8 )

/* Max value that fits in a size_t type. */
#घोषणा heap_आकार_MAX                ( ~( ( माप_प्रकार ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#घोषणा heapMULTIPLY_WILL_OVERFLOW( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( heap_आकार_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#घोषणा heapADD_WILL_OVERFLOW( a, b )         ( ( a ) > ( heap_आकार_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#घोषणा heapBLOCK_ALLOCATED_BITMASK    ( ( ( माप_प्रकार ) 1 ) << ( ( माप( माप_प्रकार ) * heapBITS_PER_BYTE ) - 1 ) )
#घोषणा heap_BLOCK_आकार_IS_VALID( x_Block_आकार )    ( ( ( x_Block_आकार ) & heapBLOCK_ALLOCATED_BITMASK ) == 0 )
#घोषणा heapBLOCK_IS_ALLOCATED( pxBlock )        ( ( ( pxBlock->x_Block_आकार ) & heapBLOCK_ALLOCATED_BITMASK ) != 0 )
#घोषणा heapALLOCATE_BLOCK( pxBlock )            ( ( pxBlock->x_Block_आकार ) |= heapBLOCK_ALLOCATED_BITMASK )
#घोषणा heapFREE_BLOCK( pxBlock )                ( ( pxBlock->x_Block_आकार ) &= ~heapBLOCK_ALLOCATED_BITMASK )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#अगर ( configAPPLICATION_ALLOCATED_HEAP == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    बाह्य uint8_t ucHeap[ config_योग_HEAP_आकार ];
#अन्यथा
    PRIVILEGED_तथ्य अटल uint8_t ucHeap[ config_योग_HEAP_आकार ];
#पूर्ण_अगर /* configAPPLICATION_ALLOCATED_HEAP */


/* Define the linked list structure.  This is used to link free blocks in order
 * of their size. */
प्रकार काष्ठा A_BLOCK_LINK
{
    काष्ठा A_BLOCK_LINK * px_अग्र_Free_Block; /*<< The next free block in the list. */
    माप_प्रकार x_Block_आकार;                     /*<< The size of the free block. */
} BlockLink_t;


अटल स्थिर माप_प्रकार x_Heap_Struct_आकार = ( ( माप( BlockLink_t ) + ( माप_प्रकार ) ( portBYTE_ALIGNMENT - 1 ) ) & ~( ( माप_प्रकार ) portBYTE_ALIGNMENT_MASK ) );
#घोषणा heap_MINIMUM_BLOCK_आकार    ( ( माप_प्रकार ) ( x_Heap_Struct_आकार * 2 ) )

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_तथ्य अटल BlockLink_t xStart, xEnd;

/* Keeps track of the number of free bytes remaining, but says nothing about
 * fragmentation. */
PRIVILEGED_तथ्य अटल माप_प्रकार xFreeBytesRemaining = config_ADJUSTED_HEAP_आकार;

/* Indicates whether the heap has been initialised or not. */
PRIVILEGED_तथ्य अटल BaseType_t xHeapHasBeenInitialised = pdFALSE;

/*-----------------------------------------------------------*/

/*
 * Initialises the heap structures before their first use.
 */
अटल व्योम prvHeapInit( व्योम ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* STATIC FUNCTIONS ARE DEFINED AS MACROS TO MINIMIZE THE FUNCTION CALL DEPTH. */

/*
 * Insert a block into the list of free blocks - which is ordered by size of
 * the block.  Small blocks at the start of the list and large blocks at the end
 * of the list.
 */
#घोषणा prv_जोड़ो_Block_Into_Free_List( px_Block_To_जोड़ो )                                                                               \
    {                                                                                                                               \
        BlockLink_t * pxIterator;                                                                                                   \
        माप_प्रकार x_Block_आकार;                                                                                                          \
                                                                                                                                    \
        x_Block_आकार = px_Block_To_जोड़ो->x_Block_आकार;                                                                                   \
                                                                                                                                    \
        /* Iterate through the list until a block is found that has a larger size */                                                \
        /* than the block we are inserting. */                                                                                      \
        क्रम( pxIterator = &xStart; pxIterator->px_अग्र_Free_Block->x_Block_आकार < x_Block_आकार; pxIterator = pxIterator->px_अग्र_Free_Block ) \
        {                                                                                                                           \
            /* There is nothing to do here - just iterate to the correct position. */                                               \
        }                                                                                                                           \
                                                                                                                                    \
        /* Update the list to include the block being inserted in the correct */                                                    \
        /* position. */                                                                                                             \
        px_Block_To_जोड़ो->px_अग्र_Free_Block = pxIterator->px_अग्र_Free_Block;                                                             \
        pxIterator->px_अग्र_Free_Block = px_Block_To_जोड़ो;                                                                              \
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

    अगर( x_Wanted_आकार > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        अगर( heapADD_WILL_OVERFLOW( x_Wanted_आकार, x_Heap_Struct_आकार ) == 0 )
        {
            x_Wanted_आकार += x_Heap_Struct_आकार;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            अगर( ( x_Wanted_आकार & portBYTE_ALIGNMENT_MASK ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_आकार = portBYTE_ALIGNMENT - ( x_Wanted_आकार & portBYTE_ALIGNMENT_MASK );

                अगर( heapADD_WILL_OVERFLOW( x_Wanted_आकार, x_Additional_Required_आकार ) == 0 )
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

    vTaskSuspendAll();
    {
        /* If this is the first call to malloc then the heap will require
         * initialisation to setup the list of free blocks. */
        अगर( xHeapHasBeenInitialised == pdFALSE )
        {
            prvHeapInit();
            xHeapHasBeenInitialised = pdTRUE;
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        अगर( heap_BLOCK_आकार_IS_VALID( x_Wanted_आकार ) != 0 )
        {
            अगर( ( x_Wanted_आकार > 0 ) && ( x_Wanted_आकार <= xFreeBytesRemaining ) )
            {
                /* Blocks are stored in byte order - traverse the list from the start
                 * (smallest) block until one of adequate size is found. */
                pxPreviousBlock = &xStart;
                pxBlock = xStart.px_अग्र_Free_Block;

                जबतक( ( pxBlock->x_Block_आकार < x_Wanted_आकार ) && ( pxBlock->px_अग्र_Free_Block != शून्य ) )
                {
                    pxPreviousBlock = pxBlock;
                    pxBlock = pxBlock->px_अग्र_Free_Block;
                }

                /* If we found the end marker then a block of adequate size was not found. */
                अगर( pxBlock != &xEnd )
                {
                    /* Return the memory space - jumping over the BlockLink_t structure
                     * at its start. */
                    pvReturn = ( व्योम * ) ( ( ( uint8_t * ) pxPreviousBlock->px_अग्र_Free_Block ) + x_Heap_Struct_आकार );

                    /* This block is being returned for use so must be taken out of the
                     * list of free blocks. */
                    pxPreviousBlock->px_अग्र_Free_Block = pxBlock->px_अग्र_Free_Block;

                    /* If the block is larger than required it can be split into two. */
                    अगर( ( pxBlock->x_Block_आकार - x_Wanted_आकार ) > heap_MINIMUM_BLOCK_आकार )
                    {
                        /* This block is to be split into two.  Create a new block
                         * following the number of bytes requested. The void cast is
                         * used to prevent byte alignment warnings from the compiler. */
                        pxNewBlockLink = ( व्योम * ) ( ( ( uint8_t * ) pxBlock ) + x_Wanted_आकार );

                        /* Calculate the sizes of two blocks split from the single
                         * block. */
                        pxNewBlockLink->x_Block_आकार = pxBlock->x_Block_आकार - x_Wanted_आकार;
                        pxBlock->x_Block_आकार = x_Wanted_आकार;

                        /* Insert the new block into the list of free blocks.
                         * The list of free blocks is sorted by their size, we have to
                         * iterate to find the right place to insert new block. */
                        prv_जोड़ो_Block_Into_Free_List( ( pxNewBlockLink ) );
                    }

                    xFreeBytesRemaining -= pxBlock->x_Block_आकार;

                    x_Allocated_Block_आकार = pxBlock->x_Block_आकार;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    heapALLOCATE_BLOCK( pxBlock );
                    pxBlock->px_अग्र_Free_Block = शून्य;
                }
            }
        }

        traceMALLOC( pvReturn, x_Allocated_Block_आकार );

        /* Prevent compiler warnings when trace macros are not used. */
        ( व्योम ) x_Allocated_Block_आकार;
    }
    ( व्योम ) xTaskResumeAll();

    #अगर ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        अगर( pvReturn == शून्य )
        {
            vApplicationMallocFailedHook();
        }
    }
    #पूर्ण_अगर

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

        /* This unexpected casting is to keep some compilers from issuing
         * byte alignment warnings. */
        pxLink = ( व्योम * ) puc;

        configASSERT( heapBLOCK_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_अग्र_Free_Block == शून्य );

        अगर( heapBLOCK_IS_ALLOCATED( pxLink ) != 0 )
        {
            अगर( pxLink->px_अग्र_Free_Block == शून्य )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                heapFREE_BLOCK( pxLink );
                #अगर ( configHEAP_CLEAR_MEMORY_ON_FREE == 1 )
                {
                    ( व्योम ) स_रखो( puc + x_Heap_Struct_आकार, 0, pxLink->x_Block_आकार - x_Heap_Struct_आकार );
                }
                #पूर्ण_अगर

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    prv_जोड़ो_Block_Into_Free_List( ( ( BlockLink_t * ) pxLink ) );
                    xFreeBytesRemaining += pxLink->x_Block_आकार;
                    traceFREE( pv, pxLink->x_Block_आकार );
                }
                ( व्योम ) xTaskResumeAll();
            }
        }
    }
}
/*-----------------------------------------------------------*/

माप_प्रकार x_Port_Get_Free_Heap_आकार( व्योम )
{
    वापस xFreeBytesRemaining;
}
/*-----------------------------------------------------------*/

व्योम vPortInitialiseBlocks( व्योम )
{
    /* This just exists to keep the linker quiet. */
}
/*-----------------------------------------------------------*/

व्योम * pvPortCalloc( माप_प्रकार x_अंक,
                     माप_प्रकार x_आकार )
{
    व्योम * pv = शून्य;

    अगर( heapMULTIPLY_WILL_OVERFLOW( x_अंक, x_आकार ) == 0 )
    {
        pv = pvPortMalloc( x_अंक * x_आकार );

        अगर( pv != शून्य )
        {
            ( व्योम ) स_रखो( pv, 0, x_अंक * x_आकार );
        }
    }

    वापस pv;
}
/*-----------------------------------------------------------*/

अटल व्योम prvHeapInit( व्योम ) /* PRIVILEGED_FUNCTION */
{
    BlockLink_t * pxFirstFreeBlock;
    uint8_t * pucAlignedHeap;

    /* Ensure the heap starts on a correctly aligned boundary. */
    pucAlignedHeap = ( uint8_t * ) ( ( ( port_POINTER_आकार_TYPE ) & ucHeap[ portBYTE_ALIGNMENT - 1 ] ) & ( ~( ( port_POINTER_आकार_TYPE ) portBYTE_ALIGNMENT_MASK ) ) );

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    xStart.px_अग्र_Free_Block = ( व्योम * ) pucAlignedHeap;
    xStart.x_Block_आकार = ( माप_प्रकार ) 0;

    /* xEnd is used to mark the end of the list of free blocks. */
    xEnd.x_Block_आकार = config_ADJUSTED_HEAP_आकार;
    xEnd.px_अग्र_Free_Block = शून्य;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space. */
    pxFirstFreeBlock = ( BlockLink_t * ) pucAlignedHeap;
    pxFirstFreeBlock->x_Block_आकार = config_ADJUSTED_HEAP_आकार;
    pxFirstFreeBlock->px_अग्र_Free_Block = &xEnd;
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
व्योम vPortHeapResetState( व्योम )
{
    xFreeBytesRemaining = config_ADJUSTED_HEAP_आकार;

    xHeapHasBeenInitialised = pdFALSE;
}
/*-----------------------------------------------------------*/
