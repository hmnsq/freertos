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
 * A sample implementation of pvPortMalloc() and vPortFree() that combines
 * (coalescences) adjacent memory blocks as they are freed, and in so doing
 * limits memory fragmentation.
 *
 * See heap_1.c, heap_2.c and heap_3.c for alternative implementations, and the
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

/* Block sizes must not get too small. */
#घोषणा heap_MINIMUM_BLOCK_आकार    ( ( माप_प्रकार ) ( x_Heap_Struct_आकार << 1 ) )

/* Assumes 8bit bytes! */
#घोषणा heapBITS_PER_BYTE         ( ( माप_प्रकार ) 8 )

/* Max value that fits in a size_t type. */
#घोषणा heap_आकार_MAX              ( ~( ( माप_प्रकार ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#घोषणा heapMULTIPLY_WILL_OVERFLOW( a, b )     ( ( ( a ) > 0 ) && ( ( b ) > ( heap_आकार_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#घोषणा heapADD_WILL_OVERFLOW( a, b )          ( ( a ) > ( heap_आकार_MAX - ( b ) ) )

/* Check if the subtraction operation ( a - b ) will result in underflow. */
#घोषणा heapSUBTRACT_WILL_UNDERFLOW( a, b )    ( ( a ) < ( b ) )

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
 * of their memory address. */
प्रकार काष्ठा A_BLOCK_LINK
{
    काष्ठा A_BLOCK_LINK * px_अग्र_Free_Block; /**< The next free block in the list. */
    माप_प्रकार x_Block_आकार;                     /**< The size of the free block. */
} BlockLink_t;

/* Setting configENABLE_HEAP_PROTECTOR to 1 enables heap block pointers
 * protection using an application supplied canary value to catch heap
 * corruption should a heap buffer overflow occur.
 */
#अगर ( configENABLE_HEAP_PROTECTOR == 1 )

/**
 * @brief Application provided function to get a random value to be used as canary.
 *
 * @param pxHeapCanary [out] Output parameter to return the canary value.
 */
    बाह्य व्योम vApplicationGetRandomHeapCanary( port_POINTER_आकार_TYPE * pxHeapCanary );

/* Canary value for protecting internal heap pointers. */
    PRIVILEGED_तथ्य अटल port_POINTER_आकार_TYPE xHeapCanary;

/* Macro to load/store BlockLink_t pointers to memory. By XORing the
 * pointers with a random canary value, heap overflows will result
 * in randomly unpredictable pointer values which will be caught by
 * heapVALIDATE_BLOCK_POINTER assert. */
    #घोषणा heapPROTECT_BLOCK_POINTER( pxBlock )    ( ( BlockLink_t * ) ( ( ( port_POINTER_आकार_TYPE ) ( pxBlock ) ) ^ xHeapCanary ) )
#अन्यथा

    #घोषणा heapPROTECT_BLOCK_POINTER( pxBlock )    ( pxBlock )

#पूर्ण_अगर /* configENABLE_HEAP_PROTECTOR */

/* Assert that a heap block pointer is within the heap bounds. */
#घोषणा heapVALIDATE_BLOCK_POINTER( pxBlock )                          \
    configASSERT( ( ( uint8_t * ) ( pxBlock ) >= &( ucHeap[ 0 ] ) ) && \
                  ( ( uint8_t * ) ( pxBlock ) <= &( ucHeap[ config_योग_HEAP_आकार - 1 ] ) ) )

/*-----------------------------------------------------------*/

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
अटल व्योम prv_जोड़ो_Block_Into_Free_List( BlockLink_t * px_Block_To_जोड़ो ) PRIVILEGED_FUNCTION;

/*
 * Called automatically to setup the required heap structures the first time
 * pvPortMalloc() is called.
 */
अटल व्योम prvHeapInit( व्योम ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* The size of the structure placed at the beginning of each allocated memory
 * block must by correctly byte aligned. */
अटल स्थिर माप_प्रकार x_Heap_Struct_आकार = ( माप( BlockLink_t ) + ( ( माप_प्रकार ) ( portBYTE_ALIGNMENT - 1 ) ) ) & ~( ( माप_प्रकार ) portBYTE_ALIGNMENT_MASK );

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_तथ्य अटल BlockLink_t xStart;
PRIVILEGED_तथ्य अटल BlockLink_t * pxEnd = शून्य;

/* Keeps track of the number of calls to allocate and free memory as well as the
 * number of free bytes remaining, but says nothing about fragmentation. */
PRIVILEGED_तथ्य अटल माप_प्रकार xFreeBytesRemaining = ( माप_प्रकार ) 0U;
PRIVILEGED_तथ्य अटल माप_प्रकार xMinimumEverFreeBytesRemaining = ( माप_प्रकार ) 0U;
PRIVILEGED_तथ्य अटल माप_प्रकार x_संख्या_Of_Successful_Allocations = ( माप_प्रकार ) 0U;
PRIVILEGED_तथ्य अटल माप_प्रकार x_संख्या_Of_Successful_Frees = ( माप_प्रकार ) 0U;

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
        अगर( pxEnd == शून्य )
        {
            prvHeapInit();
        }
        अन्यथा
        {
            mtCOVERAGE_TEST_MARKER();
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        अगर( heap_BLOCK_आकार_IS_VALID( x_Wanted_आकार ) != 0 )
        {
            अगर( ( x_Wanted_आकार > 0 ) && ( x_Wanted_आकार <= xFreeBytesRemaining ) )
            {
                /* Traverse the list from the start (lowest address) block until
                 * one of adequate size is found. */
                pxPreviousBlock = &xStart;
                pxBlock = heapPROTECT_BLOCK_POINTER( xStart.px_अग्र_Free_Block );
                heapVALIDATE_BLOCK_POINTER( pxBlock );

                जबतक( ( pxBlock->x_Block_आकार < x_Wanted_आकार ) && ( pxBlock->px_अग्र_Free_Block != heapPROTECT_BLOCK_POINTER( शून्य ) ) )
                {
                    pxPreviousBlock = pxBlock;
                    pxBlock = heapPROTECT_BLOCK_POINTER( pxBlock->px_अग्र_Free_Block );
                    heapVALIDATE_BLOCK_POINTER( pxBlock );
                }

                /* If the end marker was reached then a block of adequate size
                 * was not found. */
                अगर( pxBlock != pxEnd )
                {
                    /* Return the memory space pointed to - jumping over the
                     * BlockLink_t structure at its start. */
                    pvReturn = ( व्योम * ) ( ( ( uint8_t * ) heapPROTECT_BLOCK_POINTER( pxPreviousBlock->px_अग्र_Free_Block ) ) + x_Heap_Struct_आकार );
                    heapVALIDATE_BLOCK_POINTER( pvReturn );

                    /* This block is being returned for use so must be taken out
                     * of the list of free blocks. */
                    pxPreviousBlock->px_अग्र_Free_Block = pxBlock->px_अग्र_Free_Block;

                    /* If the block is larger than required it can be split into
                     * two. */
                    configASSERT( heapSUBTRACT_WILL_UNDERFLOW( pxBlock->x_Block_आकार, x_Wanted_आकार ) == 0 );

                    अगर( ( pxBlock->x_Block_आकार - x_Wanted_आकार ) > heap_MINIMUM_BLOCK_आकार )
                    {
                        /* This block is to be split into two.  Create a new
                         * block following the number of bytes requested. The void
                         * cast is used to prevent byte alignment warnings from the
                         * compiler. */
                        pxNewBlockLink = ( व्योम * ) ( ( ( uint8_t * ) pxBlock ) + x_Wanted_आकार );
                        configASSERT( ( ( ( माप_प्रकार ) pxNewBlockLink ) & portBYTE_ALIGNMENT_MASK ) == 0 );

                        /* Calculate the sizes of two blocks split from the
                         * single block. */
                        pxNewBlockLink->x_Block_आकार = pxBlock->x_Block_आकार - x_Wanted_आकार;
                        pxBlock->x_Block_आकार = x_Wanted_आकार;

                        /* Insert the new block into the list of free blocks. */
                        pxNewBlockLink->px_अग्र_Free_Block = pxPreviousBlock->px_अग्र_Free_Block;
                        pxPreviousBlock->px_अग्र_Free_Block = heapPROTECT_BLOCK_POINTER( pxNewBlockLink );
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

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    heapALLOCATE_BLOCK( pxBlock );
                    pxBlock->px_अग्र_Free_Block = heapPROTECT_BLOCK_POINTER( शून्य );
                    x_संख्या_Of_Successful_Allocations++;
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
    }
    ( व्योम ) xTaskResumeAll();

    #अगर ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        अगर( pvReturn == शून्य )
        {
            vApplicationMallocFailedHook();
        }
        अन्यथा
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #पूर्ण_अगर /* if ( configUSE_MALLOC_FAILED_HOOK == 1 ) */

    configASSERT( ( ( ( माप_प्रकार ) pvReturn ) & ( माप_प्रकार ) portBYTE_ALIGNMENT_MASK ) == 0 );
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

        heapVALIDATE_BLOCK_POINTER( pxLink );
        configASSERT( heapBLOCK_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_अग्र_Free_Block == heapPROTECT_BLOCK_POINTER( शून्य ) );

        अगर( heapBLOCK_IS_ALLOCATED( pxLink ) != 0 )
        {
            अगर( pxLink->px_अग्र_Free_Block == heapPROTECT_BLOCK_POINTER( शून्य ) )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                heapFREE_BLOCK( pxLink );
                #अगर ( configHEAP_CLEAR_MEMORY_ON_FREE == 1 )
                {
                    /* Check for underflow as this can occur if xBlockSize is
                     * overwritten in a heap block. */
                    अगर( heapSUBTRACT_WILL_UNDERFLOW( pxLink->x_Block_आकार, x_Heap_Struct_आकार ) == 0 )
                    {
                        ( व्योम ) स_रखो( puc + x_Heap_Struct_आकार, 0, pxLink->x_Block_आकार - x_Heap_Struct_आकार );
                    }
                }
                #पूर्ण_अगर

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    xFreeBytesRemaining += pxLink->x_Block_आकार;
                    traceFREE( pv, pxLink->x_Block_आकार );
                    prv_जोड़ो_Block_Into_Free_List( ( ( BlockLink_t * ) pxLink ) );
                    x_संख्या_Of_Successful_Frees++;
                }
                ( व्योम ) xTaskResumeAll();
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

व्योम x_Port_Reset_Heap_Minimum_Ever_Free_Heap_आकार( व्योम )
{
    xMinimumEverFreeBytesRemaining = xFreeBytesRemaining;
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
    port_POINTER_आकार_TYPE uxStartAddress, uxEndAddress;
    माप_प्रकार x_योग_Heap_आकार = config_योग_HEAP_आकार;

    /* Ensure the heap starts on a correctly aligned boundary. */
    uxStartAddress = ( port_POINTER_आकार_TYPE ) ucHeap;

    अगर( ( uxStartAddress & portBYTE_ALIGNMENT_MASK ) != 0 )
    {
        uxStartAddress += ( portBYTE_ALIGNMENT - 1 );
        uxStartAddress &= ~( ( port_POINTER_आकार_TYPE ) portBYTE_ALIGNMENT_MASK );
        x_योग_Heap_आकार -= ( माप_प्रकार ) ( uxStartAddress - ( port_POINTER_आकार_TYPE ) ucHeap );
    }

    #अगर ( configENABLE_HEAP_PROTECTOR == 1 )
    {
        vApplicationGetRandomHeapCanary( &( xHeapCanary ) );
    }
    #पूर्ण_अगर

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    xStart.px_अग्र_Free_Block = ( व्योम * ) heapPROTECT_BLOCK_POINTER( uxStartAddress );
    xStart.x_Block_आकार = ( माप_प्रकार ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    uxEndAddress = uxStartAddress + ( port_POINTER_आकार_TYPE ) x_योग_Heap_आकार;
    uxEndAddress -= ( port_POINTER_आकार_TYPE ) x_Heap_Struct_आकार;
    uxEndAddress &= ~( ( port_POINTER_आकार_TYPE ) portBYTE_ALIGNMENT_MASK );
    pxEnd = ( BlockLink_t * ) uxEndAddress;
    pxEnd->x_Block_आकार = 0;
    pxEnd->px_अग्र_Free_Block = heapPROTECT_BLOCK_POINTER( शून्य );

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    pxFirstFreeBlock = ( BlockLink_t * ) uxStartAddress;
    pxFirstFreeBlock->x_Block_आकार = ( माप_प्रकार ) ( uxEndAddress - ( port_POINTER_आकार_TYPE ) pxFirstFreeBlock );
    pxFirstFreeBlock->px_अग्र_Free_Block = heapPROTECT_BLOCK_POINTER( pxEnd );

    /* Only one block exists - and it covers the entire usable heap space. */
    xMinimumEverFreeBytesRemaining = pxFirstFreeBlock->x_Block_आकार;
    xFreeBytesRemaining = pxFirstFreeBlock->x_Block_आकार;
}
/*-----------------------------------------------------------*/

अटल व्योम prv_जोड़ो_Block_Into_Free_List( BlockLink_t * px_Block_To_जोड़ो ) /* PRIVILEGED_FUNCTION */
{
    BlockLink_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    क्रम( pxIterator = &xStart; heapPROTECT_BLOCK_POINTER( pxIterator->px_अग्र_Free_Block ) < px_Block_To_जोड़ो; pxIterator = heapPROTECT_BLOCK_POINTER( pxIterator->px_अग्र_Free_Block ) )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    अगर( pxIterator != &xStart )
    {
        heapVALIDATE_BLOCK_POINTER( pxIterator );
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

    अगर( ( puc + px_Block_To_जोड़ो->x_Block_आकार ) == ( uint8_t * ) heapPROTECT_BLOCK_POINTER( pxIterator->px_अग्र_Free_Block ) )
    {
        अगर( heapPROTECT_BLOCK_POINTER( pxIterator->px_अग्र_Free_Block ) != pxEnd )
        {
            /* Form one big block from the two blocks. */
            px_Block_To_जोड़ो->x_Block_आकार += heapPROTECT_BLOCK_POINTER( pxIterator->px_अग्र_Free_Block )->x_Block_आकार;
            px_Block_To_जोड़ो->px_अग्र_Free_Block = heapPROTECT_BLOCK_POINTER( pxIterator->px_अग्र_Free_Block )->px_अग्र_Free_Block;
        }
        अन्यथा
        {
            px_Block_To_जोड़ो->px_अग्र_Free_Block = heapPROTECT_BLOCK_POINTER( pxEnd );
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
        pxIterator->px_अग्र_Free_Block = heapPROTECT_BLOCK_POINTER( px_Block_To_जोड़ो );
    }
    अन्यथा
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

व्योम vPortGetHeapStats( HeapStats_t * pxHeapStats )
{
    BlockLink_t * pxBlock;
    माप_प्रकार xBlocks = 0, x_Max_आकार = 0, x_Min_आकार = SIZE_MAX;

    vTaskSuspendAll();
    {
        pxBlock = heapPROTECT_BLOCK_POINTER( xStart.px_अग्र_Free_Block );

        /* pxBlock will be NULL if the heap has not been initialised.  The heap
         * is initialised automatically when the first allocation is made. */
        अगर( pxBlock != शून्य )
        {
            जबतक( pxBlock != pxEnd )
            {
                /* Increment the number of blocks and record the largest block seen
                 * so far. */
                xBlocks++;

                अगर( pxBlock->x_Block_आकार > x_Max_आकार )
                {
                    x_Max_आकार = pxBlock->x_Block_आकार;
                }

                अगर( pxBlock->x_Block_आकार < x_Min_आकार )
                {
                    x_Min_आकार = pxBlock->x_Block_आकार;
                }

                /* Move to the next block in the chain until the last block is
                 * reached. */
                pxBlock = heapPROTECT_BLOCK_POINTER( pxBlock->px_अग्र_Free_Block );
            }
        }
    }
    ( व्योम ) xTaskResumeAll();

    pxHeapStats->x_आकार_Of_Largest_Free_Block_In_Bytes = x_Max_आकार;
    pxHeapStats->x_आकार_Of_Smallest_Free_Block_In_Bytes = x_Min_आकार;
    pxHeapStats->x_संख्या_Of_Free_Blocks = xBlocks;

    taskENTER_CRITICAL();
    {
        pxHeapStats->xAvailableHeapSpaceInBytes = xFreeBytesRemaining;
        pxHeapStats->x_संख्या_Of_Successful_Allocations = x_संख्या_Of_Successful_Allocations;
        pxHeapStats->x_संख्या_Of_Successful_Frees = x_संख्या_Of_Successful_Frees;
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
व्योम vPortHeapResetState( व्योम )
{
    pxEnd = शून्य;

    xFreeBytesRemaining = ( माप_प्रकार ) 0U;
    xMinimumEverFreeBytesRemaining = ( माप_प्रकार ) 0U;
    x_संख्या_Of_Successful_Allocations = ( माप_प्रकार ) 0U;
    x_संख्या_Of_Successful_Frees = ( माप_प्रकार ) 0U;
}
/*-----------------------------------------------------------*/
