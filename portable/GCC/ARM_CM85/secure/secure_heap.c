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
#अन्तर्भाव <stdint.h>

/* Configuration includes. */
#अन्तर्भाव "FreeRTOSConfig.h"

/* Secure context heap includes. */
#अन्तर्भाव "secure_heap.h"

/* Secure port macros. */
#अन्तर्भाव "secure_port_macros.h"

/**
 * @brief Total heap size.
 */
#यदि_अपरिभाषितम् secureconfig_योग_HEAP_आकार
    #परिभाषय secureconfig_योग_HEAP_आकार    ( ( ( size_t ) ( 10 * 1024 ) ) )
#यदि_अन्तः

/* No test marker by default. */
#यदि_अपरिभाषितम् mtCOVERAGE_TEST_MARKER
    #परिभाषय mtCOVERAGE_TEST_MARKER()
#यदि_अन्तः

/* No tracing by default. */
#यदि_अपरिभाषितम् traceMALLOC
    #परिभाषय traceMALLOC( pvReturn, x_Wanted_आकार )
#यदि_अन्तः

/* No tracing by default. */
#यदि_अपरिभाषितम् traceFREE
    #परिभाषय traceFREE( pv, x_खण्डम्_आकार )
#यदि_अन्तः

/* Block sizes must not get too small. */
#परिभाषय secureheap_MINIMUM_खण्डम्_आकार    ( ( size_t ) ( x_Heap_Struct_आकार << 1 ) )

/* Assumes 8bit bytes! */
#परिभाषय secureheap_द्वयङ्काः_प्रत्येकम्_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#परिभाषय secureheap_आकार_MAX              ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#परिभाषय secureheap_सङ्कलय_WILL_अतिप्रवाहः( a, b )    ( ( a ) > ( secureheap_आकार_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#परिभाषय secureheap_खण्डम्_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( परिमाण( size_t ) * secureheap_द्वयङ्काः_प्रत्येकम्_BYTE ) - 1 ) )
#परिभाषय secureheap_खण्डम्_आकार_IS_VALID( x_खण्डम्_आकार )    ( ( ( x_खण्डम्_आकार ) & secureheap_खण्डम्_ALLOCATED_BITMASK ) == 0 )
#परिभाषय secureheap_खण्डम्_IS_ALLOCATED( px_खण्डम् )        ( ( ( px_खण्डम्->x_खण्डम्_आकार ) & secureheap_खण्डम्_ALLOCATED_BITMASK ) != 0 )
#परिभाषय secureheap_ALLOCATE_खण्डम्( px_खण्डम् )            ( ( px_खण्डम्->x_खण्डम्_आकार ) |= secureheap_खण्डम्_ALLOCATED_BITMASK )
#परिभाषय secureheap_FREE_खण्डम्( px_खण्डम् )                ( ( px_खण्डम्->x_खण्डम्_आकार ) &= ~secureheap_खण्डम्_ALLOCATED_BITMASK )
/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#यदि ( configAPPLICATION_ALLOCATED_HEAP == 1 )

/* The application writer has already defined the array used for the RTOS
* heap - probably so it can be placed in a special segment or address. */
    बाह्य uint8_t ucHeap[ secureconfig_योग_HEAP_आकार ];
#अन्यथा /* configAPPLICATION_ALLOCATED_HEAP */
    स्थिर uint8_t ucHeap[ secureconfig_योग_HEAP_आकार ];
#यदि_अन्तः /* configAPPLICATION_ALLOCATED_HEAP */

/**
 * @brief The linked list structure.
 *
 * This is used to link free blocks in order of their memory address.
 */
प्रकारनिर्देश संरचना A_खण्डम्_LINK
{
    संरचना A_खण्डम्_LINK * px_अग्र_Free_खण्डम्; /**< The next free block in the list. */
    size_t x_खण्डम्_आकार;                     /**< The size of the free block. */
} खण्डम्_Link_t;
/*-----------------------------------------------------------*/

/**
 * @brief Called automatically to setup the required heap structures the first
 * time pvPortMalloc() is called.
 */
स्थिर शून्य prvHeapInit( शून्य );

/**
 * @brief Inserts a block of memory that is being freed into the correct
 * position in the list of free memory blocks.
 *
 * The block being freed will be merged with the block in front it and/or the
 * block behind it if the memory blocks are adjacent to each other.
 *
 * @param[in] pxBlockToInsert The block being freed.
 */
स्थिर शून्य prv_निवेशय_खण्डम्_Into_Free_List( खण्डम्_Link_t * px_खण्डम्_गन्तव्यम्_निवेशय );
/*-----------------------------------------------------------*/

/**
 * @brief The size of the structure placed at the beginning of each allocated
 * memory block must by correctly byte aligned.
 */
स्थिर ध्रुव size_t x_Heap_Struct_आकार = ( परिमाण( खण्डम्_Link_t ) + ( ( size_t ) ( secureportBYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) secureport_BYTE_ALIGNMENT_आवरणम् );

/**
 * @brief Create a couple of list links to mark the start and end of the list.
 */
स्थिर खण्डम्_Link_t xStart;
स्थिर खण्डम्_Link_t * px_अन्तः = रिक्त;

/**
 * @brief Keeps track of the number of free bytes remaining, but says nothing
 * about fragmentation.
 */
स्थिर size_t x_Free_अष्टकानि_Remaining = 0U;
स्थिर size_t x_Minimum_Ever_Free_अष्टकानि_Remaining = 0U;

/*-----------------------------------------------------------*/

स्थिर शून्य prvHeapInit( शून्य )
{
    खण्डम्_Link_t * px_First_Free_खण्डम्;
    uint8_t * pucAlignedHeap;
    size_t ux_स्थानाङ्कः;
    size_t x_योग_Heap_आकार = secureconfig_योग_HEAP_आकार;

    /* Ensure the heap starts on a correctly aligned boundary. */
    ux_स्थानाङ्कः = ( size_t ) ucHeap;

    यदि( ( ux_स्थानाङ्कः & secureport_BYTE_ALIGNMENT_आवरणम् ) != 0 )
    {
        ux_स्थानाङ्कः += ( secureportBYTE_ALIGNMENT - 1 );
        ux_स्थानाङ्कः &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_आवरणम् );
        x_योग_Heap_आकार -= ux_स्थानाङ्कः - ( size_t ) ucHeap;
    }

    pucAlignedHeap = ( uint8_t * ) ux_स्थानाङ्कः;

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    xStart.px_अग्र_Free_खण्डम् = ( शून्य * ) pucAlignedHeap;
    xStart.x_खण्डम्_आकार = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    ux_स्थानाङ्कः = ( ( size_t ) pucAlignedHeap ) + x_योग_Heap_आकार;
    ux_स्थानाङ्कः -= x_Heap_Struct_आकार;
    ux_स्थानाङ्कः &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_आवरणम् );
    px_अन्तः = ( शून्य * ) ux_स्थानाङ्कः;
    px_अन्तः->x_खण्डम्_आकार = 0;
    px_अन्तः->px_अग्र_Free_खण्डम् = रिक्त;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    px_First_Free_खण्डम् = ( शून्य * ) pucAlignedHeap;
    px_First_Free_खण्डम्->x_खण्डम्_आकार = ux_स्थानाङ्कः - ( size_t ) px_First_Free_खण्डम्;
    px_First_Free_खण्डम्->px_अग्र_Free_खण्डम् = px_अन्तः;

    /* Only one block exists - and it covers the entire usable heap space. */
    x_Minimum_Ever_Free_अष्टकानि_Remaining = px_First_Free_खण्डम्->x_खण्डम्_आकार;
    x_Free_अष्टकानि_Remaining = px_First_Free_खण्डम्->x_खण्डम्_आकार;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_निवेशय_खण्डम्_Into_Free_List( खण्डम्_Link_t * px_खण्डम्_गन्तव्यम्_निवेशय )
{
    खण्डम्_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    प्रति( pxIterator = &xStart; pxIterator->px_अग्र_Free_खण्डम् < px_खण्डम्_गन्तव्यम्_निवेशय; pxIterator = pxIterator->px_अग्र_Free_खण्डम् )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    यदि( ( puc + pxIterator->x_खण्डम्_आकार ) == ( uint8_t * ) px_खण्डम्_गन्तव्यम्_निवेशय )
    {
        pxIterator->x_खण्डम्_आकार += px_खण्डम्_गन्तव्यम्_निवेशय->x_खण्डम्_आकार;
        px_खण्डम्_गन्तव्यम्_निवेशय = pxIterator;
    }
    अन्यथा
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_खण्डम्_गन्तव्यम्_निवेशय;

    यदि( ( puc + px_खण्डम्_गन्तव्यम्_निवेशय->x_खण्डम्_आकार ) == ( uint8_t * ) pxIterator->px_अग्र_Free_खण्डम् )
    {
        यदि( pxIterator->px_अग्र_Free_खण्डम् != px_अन्तः )
        {
            /* Form one big block from the two blocks. */
            px_खण्डम्_गन्तव्यम्_निवेशय->x_खण्डम्_आकार += pxIterator->px_अग्र_Free_खण्डम्->x_खण्डम्_आकार;
            px_खण्डम्_गन्तव्यम्_निवेशय->px_अग्र_Free_खण्डम् = pxIterator->px_अग्र_Free_खण्डम्->px_अग्र_Free_खण्डम्;
        }
        अन्यथा
        {
            px_खण्डम्_गन्तव्यम्_निवेशय->px_अग्र_Free_खण्डम् = px_अन्तः;
        }
    }
    अन्यथा
    {
        px_खण्डम्_गन्तव्यम्_निवेशय->px_अग्र_Free_खण्डम् = pxIterator->px_अग्र_Free_खण्डम्;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    यदि( pxIterator != px_खण्डम्_गन्तव्यम्_निवेशय )
    {
        pxIterator->px_अग्र_Free_खण्डम् = px_खण्डम्_गन्तव्यम्_निवेशय;
    }
    अन्यथा
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

शून्य * pv_पत्तनम्_Malloc( size_t x_Wanted_आकार )
{
    खण्डम्_Link_t * px_खण्डम्;
    खण्डम्_Link_t * px_Previous_खण्डम्;
    खण्डम्_Link_t * px_New_खण्डम्_Link;
    शून्य * pvReturn = रिक्त;
    size_t x_Additional_Required_आकार;
    size_t x_Allocated_खण्डम्_आकार = 0;

    /* If this is the first call to malloc then the heap will require
     * initialisation to setup the list of free blocks. */
    यदि( px_अन्तः == रिक्त )
    {
        prvHeapInit();
    }
    अन्यथा
    {
        mtCOVERAGE_TEST_MARKER();
    }

    यदि( x_Wanted_आकार > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        यदि( secureheap_सङ्कलय_WILL_अतिप्रवाहः( x_Wanted_आकार, x_Heap_Struct_आकार ) == 0 )
        {
            x_Wanted_आकार += x_Heap_Struct_आकार;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            यदि( ( x_Wanted_आकार & secureport_BYTE_ALIGNMENT_आवरणम् ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_आकार = secureportBYTE_ALIGNMENT - ( x_Wanted_आकार & secureport_BYTE_ALIGNMENT_आवरणम् );

                यदि( secureheap_सङ्कलय_WILL_अतिप्रवाहः( x_Wanted_आकार, x_Additional_Required_आकार ) == 0 )
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
    यदि( secureheap_खण्डम्_आकार_IS_VALID( x_Wanted_आकार ) != 0 )
    {
        यदि( ( x_Wanted_आकार > 0 ) && ( x_Wanted_आकार <= x_Free_अष्टकानि_Remaining ) )
        {
            /* Traverse the list from the start (lowest address) block until
             * one of adequate size is found. */
            px_Previous_खण्डम् = &xStart;
            px_खण्डम् = xStart.px_अग्र_Free_खण्डम्;

            यावत्( ( px_खण्डम्->x_खण्डम्_आकार < x_Wanted_आकार ) && ( px_खण्डम्->px_अग्र_Free_खण्डम् != रिक्त ) )
            {
                px_Previous_खण्डम् = px_खण्डम्;
                px_खण्डम् = px_खण्डम्->px_अग्र_Free_खण्डम्;
            }

            /* If the end marker was reached then a block of adequate size was
             * not found. */
            यदि( px_खण्डम् != px_अन्तः )
            {
                /* Return the memory space pointed to - jumping over the
                 * BlockLink_t structure at its start. */
                pvReturn = ( शून्य * ) ( ( ( uint8_t * ) px_Previous_खण्डम्->px_अग्र_Free_खण्डम् ) + x_Heap_Struct_आकार );

                /* This block is being returned for use so must be taken out
                 * of the list of free blocks. */
                px_Previous_खण्डम्->px_अग्र_Free_खण्डम् = px_खण्डम्->px_अग्र_Free_खण्डम्;

                /* If the block is larger than required it can be split into
                 * two. */
                यदि( ( px_खण्डम्->x_खण्डम्_आकार - x_Wanted_आकार ) > secureheap_MINIMUM_खण्डम्_आकार )
                {
                    /* This block is to be split into two.  Create a new
                     * block following the number of bytes requested. The void
                     * cast is used to prevent byte alignment warnings from the
                     * compiler. */
                    px_New_खण्डम्_Link = ( शून्य * ) ( ( ( uint8_t * ) px_खण्डम् ) + x_Wanted_आकार );
                    secureportASSERT( ( ( ( size_t ) px_New_खण्डम्_Link ) & secureport_BYTE_ALIGNMENT_आवरणम् ) == 0 );

                    /* Calculate the sizes of two blocks split from the single
                     * block. */
                    px_New_खण्डम्_Link->x_खण्डम्_आकार = px_खण्डम्->x_खण्डम्_आकार - x_Wanted_आकार;
                    px_खण्डम्->x_खण्डम्_आकार = x_Wanted_आकार;

                    /* Insert the new block into the list of free blocks. */
                    px_New_खण्डम्_Link->px_अग्र_Free_खण्डम् = px_Previous_खण्डम्->px_अग्र_Free_खण्डम्;
                    px_Previous_खण्डम्->px_अग्र_Free_खण्डम् = px_New_खण्डम्_Link;
                }
                अन्यथा
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Free_अष्टकानि_Remaining -= px_खण्डम्->x_खण्डम्_आकार;

                यदि( x_Free_अष्टकानि_Remaining < x_Minimum_Ever_Free_अष्टकानि_Remaining )
                {
                    x_Minimum_Ever_Free_अष्टकानि_Remaining = x_Free_अष्टकानि_Remaining;
                }
                अन्यथा
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Allocated_खण्डम्_आकार = px_खण्डम्->x_खण्डम्_आकार;

                /* The block is being returned - it is allocated and owned by
                 * the application and has no "next" block. */
                secureheap_ALLOCATE_खण्डम्( px_खण्डम् );
                px_खण्डम्->px_अग्र_Free_खण्डम् = रिक्त;
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

    traceMALLOC( pvReturn, x_Allocated_खण्डम्_आकार );

    /* Prevent compiler warnings when trace macros are not used. */
    ( शून्य ) x_Allocated_खण्डम्_आकार;

    #यदि ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 )
    {
        यदि( pvReturn == रिक्त )
        {
            बाह्य शून्य vApplicationMallocFailedHook( शून्य );
            vApplicationMallocFailedHook();
        }
        अन्यथा
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #यदि_अन्तः /* if ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 ) */

    secureportASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) secureport_BYTE_ALIGNMENT_आवरणम् ) == 0 );
    प्रत्यागम pvReturn;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Free( शून्य * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    खण्डम्_Link_t * pxLink;

    यदि( pv != रिक्त )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_Heap_Struct_आकार;

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( शून्य * ) puc;

        /* Check the block is actually allocated. */
        secureportASSERT( secureheap_खण्डम्_IS_ALLOCATED( pxLink ) != 0 );
        secureportASSERT( pxLink->px_अग्र_Free_खण्डम् == रिक्त );

        यदि( secureheap_खण्डम्_IS_ALLOCATED( pxLink ) != 0 )
        {
            यदि( pxLink->px_अग्र_Free_खण्डम् == रिक्त )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                secureheap_FREE_खण्डम्( pxLink );

                secureportDISABLE_NON_SECURE_INTERRUPTS();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_अष्टकानि_Remaining += pxLink->x_खण्डम्_आकार;
                    traceFREE( pv, pxLink->x_खण्डम्_आकार );
                    prv_निवेशय_खण्डम्_Into_Free_List( ( ( खण्डम्_Link_t * ) pxLink ) );
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

size_t x_पत्तनम्_Get_Free_Heap_आकार( शून्य )
{
    प्रत्यागम x_Free_अष्टकानि_Remaining;
}
/*-----------------------------------------------------------*/

size_t x_पत्तनम्_Get_Minimum_Ever_Free_Heap_आकार( शून्य )
{
    प्रत्यागम x_Minimum_Ever_Free_अष्टकानि_Remaining;
}
/*-----------------------------------------------------------*/
