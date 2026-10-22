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
#అన్తర్భావ <stdint.h>

/* Configuration includes. */
#అన్తర్భావ "FreeRTOSConfig.h"

/* Secure context heap includes. */
#అన్తర్భావ "secure_heap.h"

/* Secure port macros. */
#అన్తర్భావ "secure_port_macros.h"

/**
 * @brief Total heap size.
 */
#నిర్వచితం_కాకపోతే secureconfig_మొత్తం_కుప్ప_కొలత
    #నిర్వచించు secureconfig_మొత్తం_కుప్ప_కొలత    ( ( ( size_t ) ( 10 * 1024 ) ) )
#అయితే_ముగింపు

/* No test marker by default. */
#నిర్వచితం_కాకపోతే mtCOVERAGE_TEST_MARKER
    #నిర్వచించు mtCOVERAGE_TEST_MARKER()
#అయితే_ముగింపు

/* No tracing by default. */
#నిర్వచితం_కాకపోతే traceMALLOC
    #నిర్వచించు traceMALLOC( pvReturn, x_Wanted_కొలత )
#అయితే_ముగింపు

/* No tracing by default. */
#నిర్వచితం_కాకపోతే traceFREE
    #నిర్వచించు traceFREE( pv, x_ఖండం_కొలత )
#అయితే_ముగింపు

/* Block sizes must not get too small. */
#నిర్వచించు secureheap_MINIMUM_ఖండం_కొలత    ( ( size_t ) ( x_కుప్ప_Struct_కొలత << 1 ) )

/* Assumes 8bit bytes! */
#నిర్వచించు secureheap_బిట్లు_చొప్పున_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#నిర్వచించు secureheap_కొలత_MAX              ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#నిర్వచించు secureheap_కూడు_WILL_అధికప్రవాహం( a, b )    ( ( a ) > ( secureheap_కొలత_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#నిర్వచించు secureheap_ఖండం_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( పరిమాణం( size_t ) * secureheap_బిట్లు_చొప్పున_BYTE ) - 1 ) )
#నిర్వచించు secureheap_ఖండం_కొలత_IS_VALID( x_ఖండం_కొలత )    ( ( ( x_ఖండం_కొలత ) & secureheap_ఖండం_ALLOCATED_BITMASK ) == 0 )
#నిర్వచించు secureheap_ఖండం_IS_ALLOCATED( px_ఖండం )        ( ( ( px_ఖండం->x_ఖండం_కొలత ) & secureheap_ఖండం_ALLOCATED_BITMASK ) != 0 )
#నిర్వచించు secureheap_ALLOCATE_ఖండం( px_ఖండం )            ( ( px_ఖండం->x_ఖండం_కొలత ) |= secureheap_ఖండం_ALLOCATED_BITMASK )
#నిర్వచించు secureheap_FREE_ఖండం( px_ఖండం )                ( ( px_ఖండం->x_ఖండం_కొలత ) &= ~secureheap_ఖండం_ALLOCATED_BITMASK )
/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#ఒకవేళ ( config_APPLICATION_ALLOCATED_కుప్ప == 1 )

/* The application writer has already defined the array used for the RTOS
* heap - probably so it can be placed in a special segment or address. */
    బాహ్య uint8_t uc_కుప్ప[ secureconfig_మొత్తం_కుప్ప_కొలత ];
#లేకపోతే /* configAPPLICATION_ALLOCATED_HEAP */
    స్థిర uint8_t uc_కుప్ప[ secureconfig_మొత్తం_కుప్ప_కొలత ];
#అయితే_ముగింపు /* configAPPLICATION_ALLOCATED_HEAP */

/**
 * @brief The linked list structure.
 *
 * This is used to link free blocks in order of their memory address.
 */
రకనిర్వచనం నిర్మాణం A_ఖండం_LINK
{
    నిర్మాణం A_ఖండం_LINK * px_తదుపరి_Free_ఖండం; /**< The next free block in the list. */
    size_t x_ఖండం_కొలత;                     /**< The size of the free block. */
} ఖండం_Link_t;
/*-----------------------------------------------------------*/

/**
 * @brief Called automatically to setup the required heap structures the first
 * time pvPortMalloc() is called.
 */
స్థిర శూన్య prv_కుప్ప_Init( శూన్య );

/**
 * @brief Inserts a block of memory that is being freed into the correct
 * position in the list of free memory blocks.
 *
 * The block being freed will be merged with the block in front it and/or the
 * block behind it if the memory blocks are adjacent to each other.
 *
 * @param[in] pxBlockToInsert The block being freed.
 */
స్థిర శూన్య prv_చొప్పించు_ఖండం_Into_Free_List( ఖండం_Link_t * px_ఖండం_గమ్యం_చొప్పించు );
/*-----------------------------------------------------------*/

/**
 * @brief The size of the structure placed at the beginning of each allocated
 * memory block must by correctly byte aligned.
 */
స్థిర స్థిరరాశి size_t x_కుప్ప_Struct_కొలత = ( పరిమాణం( ఖండం_Link_t ) + ( ( size_t ) ( secureportBYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) secureport_BYTE_ALIGNMENT_ముసుగు );

/**
 * @brief Create a couple of list links to mark the start and end of the list.
 */
స్థిర ఖండం_Link_t x_ప్రారంభం;
స్థిర ఖండం_Link_t * px_చివర = ఖాళీ;

/**
 * @brief Keeps track of the number of free bytes remaining, but says nothing
 * about fragmentation.
 */
స్థిర size_t x_Free_బైట్లు_మిగిలిన = 0U;
స్థిర size_t x_Minimum_Ever_Free_బైట్లు_మిగిలిన = 0U;

/*-----------------------------------------------------------*/

స్థిర శూన్య prv_కుప్ప_Init( శూన్య )
{
    ఖండం_Link_t * px_మొదటి_Free_ఖండం;
    uint8_t * puc_Aligned_కుప్ప;
    size_t ux_చిరునామా;
    size_t x_మొత్తం_కుప్ప_కొలత = secureconfig_మొత్తం_కుప్ప_కొలత;

    /* Ensure the heap starts on a correctly aligned boundary. */
    ux_చిరునామా = ( size_t ) uc_కుప్ప;

    ఒకవేళ( ( ux_చిరునామా & secureport_BYTE_ALIGNMENT_ముసుగు ) != 0 )
    {
        ux_చిరునామా += ( secureportBYTE_ALIGNMENT - 1 );
        ux_చిరునామా &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_ముసుగు );
        x_మొత్తం_కుప్ప_కొలత -= ux_చిరునామా - ( size_t ) uc_కుప్ప;
    }

    puc_Aligned_కుప్ప = ( uint8_t * ) ux_చిరునామా;

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_ప్రారంభం.px_తదుపరి_Free_ఖండం = ( శూన్య * ) puc_Aligned_కుప్ప;
    x_ప్రారంభం.x_ఖండం_కొలత = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    ux_చిరునామా = ( ( size_t ) puc_Aligned_కుప్ప ) + x_మొత్తం_కుప్ప_కొలత;
    ux_చిరునామా -= x_కుప్ప_Struct_కొలత;
    ux_చిరునామా &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_ముసుగు );
    px_చివర = ( శూన్య * ) ux_చిరునామా;
    px_చివర->x_ఖండం_కొలత = 0;
    px_చివర->px_తదుపరి_Free_ఖండం = ఖాళీ;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    px_మొదటి_Free_ఖండం = ( శూన్య * ) puc_Aligned_కుప్ప;
    px_మొదటి_Free_ఖండం->x_ఖండం_కొలత = ux_చిరునామా - ( size_t ) px_మొదటి_Free_ఖండం;
    px_మొదటి_Free_ఖండం->px_తదుపరి_Free_ఖండం = px_చివర;

    /* Only one block exists - and it covers the entire usable heap space. */
    x_Minimum_Ever_Free_బైట్లు_మిగిలిన = px_మొదటి_Free_ఖండం->x_ఖండం_కొలత;
    x_Free_బైట్లు_మిగిలిన = px_మొదటి_Free_ఖండం->x_ఖండం_కొలత;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_చొప్పించు_ఖండం_Into_Free_List( ఖండం_Link_t * px_ఖండం_గమ్యం_చొప్పించు )
{
    ఖండం_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    కొరకు( pxIterator = &x_ప్రారంభం; pxIterator->px_తదుపరి_Free_ఖండం < px_ఖండం_గమ్యం_చొప్పించు; pxIterator = pxIterator->px_తదుపరి_Free_ఖండం )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    ఒకవేళ( ( puc + pxIterator->x_ఖండం_కొలత ) == ( uint8_t * ) px_ఖండం_గమ్యం_చొప్పించు )
    {
        pxIterator->x_ఖండం_కొలత += px_ఖండం_గమ్యం_చొప్పించు->x_ఖండం_కొలత;
        px_ఖండం_గమ్యం_చొప్పించు = pxIterator;
    }
    లేకపోతే
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_ఖండం_గమ్యం_చొప్పించు;

    ఒకవేళ( ( puc + px_ఖండం_గమ్యం_చొప్పించు->x_ఖండం_కొలత ) == ( uint8_t * ) pxIterator->px_తదుపరి_Free_ఖండం )
    {
        ఒకవేళ( pxIterator->px_తదుపరి_Free_ఖండం != px_చివర )
        {
            /* Form one big block from the two blocks. */
            px_ఖండం_గమ్యం_చొప్పించు->x_ఖండం_కొలత += pxIterator->px_తదుపరి_Free_ఖండం->x_ఖండం_కొలత;
            px_ఖండం_గమ్యం_చొప్పించు->px_తదుపరి_Free_ఖండం = pxIterator->px_తదుపరి_Free_ఖండం->px_తదుపరి_Free_ఖండం;
        }
        లేకపోతే
        {
            px_ఖండం_గమ్యం_చొప్పించు->px_తదుపరి_Free_ఖండం = px_చివర;
        }
    }
    లేకపోతే
    {
        px_ఖండం_గమ్యం_చొప్పించు->px_తదుపరి_Free_ఖండం = pxIterator->px_తదుపరి_Free_ఖండం;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    ఒకవేళ( pxIterator != px_ఖండం_గమ్యం_చొప్పించు )
    {
        pxIterator->px_తదుపరి_Free_ఖండం = px_ఖండం_గమ్యం_చొప్పించు;
    }
    లేకపోతే
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

శూన్య * pv_పోర్టు_Malloc( size_t x_Wanted_కొలత )
{
    ఖండం_Link_t * px_ఖండం;
    ఖండం_Link_t * px_మునుపటి_ఖండం;
    ఖండం_Link_t * px_New_ఖండం_Link;
    శూన్య * pvReturn = ఖాళీ;
    size_t x_Additional_Required_కొలత;
    size_t x_Allocated_ఖండం_కొలత = 0;

    /* If this is the first call to malloc then the heap will require
     * initialisation to setup the list of free blocks. */
    ఒకవేళ( px_చివర == ఖాళీ )
    {
        prv_కుప్ప_Init();
    }
    లేకపోతే
    {
        mtCOVERAGE_TEST_MARKER();
    }

    ఒకవేళ( x_Wanted_కొలత > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        ఒకవేళ( secureheap_కూడు_WILL_అధికప్రవాహం( x_Wanted_కొలత, x_కుప్ప_Struct_కొలత ) == 0 )
        {
            x_Wanted_కొలత += x_కుప్ప_Struct_కొలత;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            ఒకవేళ( ( x_Wanted_కొలత & secureport_BYTE_ALIGNMENT_ముసుగు ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_కొలత = secureportBYTE_ALIGNMENT - ( x_Wanted_కొలత & secureport_BYTE_ALIGNMENT_ముసుగు );

                ఒకవేళ( secureheap_కూడు_WILL_అధికప్రవాహం( x_Wanted_కొలత, x_Additional_Required_కొలత ) == 0 )
                {
                    x_Wanted_కొలత += x_Additional_Required_కొలత;
                }
                లేకపోతే
                {
                    x_Wanted_కొలత = 0;
                }
            }
            లేకపోతే
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        లేకపోతే
        {
            x_Wanted_కొలత = 0;
        }
    }
    లేకపోతే
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Check the requested block size is not so large that the top bit is set.
     * The top bit of the block size member of the BlockLink_t structure is used
     * to determine who owns the block - the application or the kernel, so it
     * must be free. */
    ఒకవేళ( secureheap_ఖండం_కొలత_IS_VALID( x_Wanted_కొలత ) != 0 )
    {
        ఒకవేళ( ( x_Wanted_కొలత > 0 ) && ( x_Wanted_కొలత <= x_Free_బైట్లు_మిగిలిన ) )
        {
            /* Traverse the list from the start (lowest address) block until
             * one of adequate size is found. */
            px_మునుపటి_ఖండం = &x_ప్రారంభం;
            px_ఖండం = x_ప్రారంభం.px_తదుపరి_Free_ఖండం;

            అయితే( ( px_ఖండం->x_ఖండం_కొలత < x_Wanted_కొలత ) && ( px_ఖండం->px_తదుపరి_Free_ఖండం != ఖాళీ ) )
            {
                px_మునుపటి_ఖండం = px_ఖండం;
                px_ఖండం = px_ఖండం->px_తదుపరి_Free_ఖండం;
            }

            /* If the end marker was reached then a block of adequate size was
             * not found. */
            ఒకవేళ( px_ఖండం != px_చివర )
            {
                /* Return the memory space pointed to - jumping over the
                 * BlockLink_t structure at its start. */
                pvReturn = ( శూన్య * ) ( ( ( uint8_t * ) px_మునుపటి_ఖండం->px_తదుపరి_Free_ఖండం ) + x_కుప్ప_Struct_కొలత );

                /* This block is being returned for use so must be taken out
                 * of the list of free blocks. */
                px_మునుపటి_ఖండం->px_తదుపరి_Free_ఖండం = px_ఖండం->px_తదుపరి_Free_ఖండం;

                /* If the block is larger than required it can be split into
                 * two. */
                ఒకవేళ( ( px_ఖండం->x_ఖండం_కొలత - x_Wanted_కొలత ) > secureheap_MINIMUM_ఖండం_కొలత )
                {
                    /* This block is to be split into two.  Create a new
                     * block following the number of bytes requested. The void
                     * cast is used to prevent byte alignment warnings from the
                     * compiler. */
                    px_New_ఖండం_Link = ( శూన్య * ) ( ( ( uint8_t * ) px_ఖండం ) + x_Wanted_కొలత );
                    secureportASSERT( ( ( ( size_t ) px_New_ఖండం_Link ) & secureport_BYTE_ALIGNMENT_ముసుగు ) == 0 );

                    /* Calculate the sizes of two blocks split from the single
                     * block. */
                    px_New_ఖండం_Link->x_ఖండం_కొలత = px_ఖండం->x_ఖండం_కొలత - x_Wanted_కొలత;
                    px_ఖండం->x_ఖండం_కొలత = x_Wanted_కొలత;

                    /* Insert the new block into the list of free blocks. */
                    px_New_ఖండం_Link->px_తదుపరి_Free_ఖండం = px_మునుపటి_ఖండం->px_తదుపరి_Free_ఖండం;
                    px_మునుపటి_ఖండం->px_తదుపరి_Free_ఖండం = px_New_ఖండం_Link;
                }
                లేకపోతే
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Free_బైట్లు_మిగిలిన -= px_ఖండం->x_ఖండం_కొలత;

                ఒకవేళ( x_Free_బైట్లు_మిగిలిన < x_Minimum_Ever_Free_బైట్లు_మిగిలిన )
                {
                    x_Minimum_Ever_Free_బైట్లు_మిగిలిన = x_Free_బైట్లు_మిగిలిన;
                }
                లేకపోతే
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Allocated_ఖండం_కొలత = px_ఖండం->x_ఖండం_కొలత;

                /* The block is being returned - it is allocated and owned by
                 * the application and has no "next" block. */
                secureheap_ALLOCATE_ఖండం( px_ఖండం );
                px_ఖండం->px_తదుపరి_Free_ఖండం = ఖాళీ;
            }
            లేకపోతే
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        లేకపోతే
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    లేకపోతే
    {
        mtCOVERAGE_TEST_MARKER();
    }

    traceMALLOC( pvReturn, x_Allocated_ఖండం_కొలత );

    /* Prevent compiler warnings when trace macros are not used. */
    ( శూన్య ) x_Allocated_ఖండం_కొలత;

    #ఒకవేళ ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 )
    {
        ఒకవేళ( pvReturn == ఖాళీ )
        {
            బాహ్య శూన్య vApplicationMallocFailedHook( శూన్య );
            vApplicationMallocFailedHook();
        }
        లేకపోతే
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #అయితే_ముగింపు /* if ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 ) */

    secureportASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) secureport_BYTE_ALIGNMENT_ముసుగు ) == 0 );
    తిరిగి pvReturn;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Free( శూన్య * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    ఖండం_Link_t * pxLink;

    ఒకవేళ( pv != ఖాళీ )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_కుప్ప_Struct_కొలత;

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( శూన్య * ) puc;

        /* Check the block is actually allocated. */
        secureportASSERT( secureheap_ఖండం_IS_ALLOCATED( pxLink ) != 0 );
        secureportASSERT( pxLink->px_తదుపరి_Free_ఖండం == ఖాళీ );

        ఒకవేళ( secureheap_ఖండం_IS_ALLOCATED( pxLink ) != 0 )
        {
            ఒకవేళ( pxLink->px_తదుపరి_Free_ఖండం == ఖాళీ )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                secureheap_FREE_ఖండం( pxLink );

                secureportDISABLE_NON_SECURE_INTERRUPTS();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_బైట్లు_మిగిలిన += pxLink->x_ఖండం_కొలత;
                    traceFREE( pv, pxLink->x_ఖండం_కొలత );
                    prv_చొప్పించు_ఖండం_Into_Free_List( ( ( ఖండం_Link_t * ) pxLink ) );
                }
                secureportENABLE_NON_SECURE_INTERRUPTS();
            }
            లేకపోతే
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        లేకపోతే
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_పోర్టు_Get_Free_కుప్ప_కొలత( శూన్య )
{
    తిరిగి x_Free_బైట్లు_మిగిలిన;
}
/*-----------------------------------------------------------*/

size_t x_పోర్టు_Get_Minimum_Ever_Free_కుప్ప_కొలత( శూన్య )
{
    తిరిగి x_Minimum_Ever_Free_బైట్లు_మిగిలిన;
}
/*-----------------------------------------------------------*/
