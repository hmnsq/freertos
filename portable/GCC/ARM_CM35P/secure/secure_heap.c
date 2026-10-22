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
#ضمن <stdint.h>

/* Configuration includes. */
#ضمن "FreeRTOSConfig.h"

/* Secure context heap includes. */
#ضمن "secure_heap.h"

/* Secure port macros. */
#ضمن "secure_port_macros.h"

/**
 * @brief Total heap size.
 */
#جيڪڏهن_وصف_نه_ٿيل secureconfig_ڪل_ڍير_سائيز
    #وصف_ڪريو secureconfig_ڪل_ڍير_سائيز    ( ( ( size_t ) ( 10 * 1024 ) ) )
#جيڪڏهن_پورو

/* No test marker by default. */
#جيڪڏهن_وصف_نه_ٿيل mtCOVERAGE_TEST_MARKER
    #وصف_ڪريو mtCOVERAGE_TEST_MARKER()
#جيڪڏهن_پورو

/* No tracing by default. */
#جيڪڏهن_وصف_نه_ٿيل traceMALLOC
    #وصف_ڪريو traceMALLOC( pvReturn, x_Wanted_سائيز )
#جيڪڏهن_پورو

/* No tracing by default. */
#جيڪڏهن_وصف_نه_ٿيل traceFREE
    #وصف_ڪريو traceFREE( pv, x_بلاڪ_سائيز )
#جيڪڏهن_پورو

/* Block sizes must not get too small. */
#وصف_ڪريو secureheap_MINIMUM_بلاڪ_سائيز    ( ( size_t ) ( x_ڍير_Struct_سائيز << 1 ) )

/* Assumes 8bit bytes! */
#وصف_ڪريو secureheap_بٽ_في_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#وصف_ڪريو secureheap_سائيز_MAX              ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#وصف_ڪريو secureheap_جوڙيو_WILL_حد_کان_مٿي( a, b )    ( ( a ) > ( secureheap_سائيز_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#وصف_ڪريو secureheap_بلاڪ_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( حجم( size_t ) * secureheap_بٽ_في_BYTE ) - 1 ) )
#وصف_ڪريو secureheap_بلاڪ_سائيز_IS_VALID( x_بلاڪ_سائيز )    ( ( ( x_بلاڪ_سائيز ) & secureheap_بلاڪ_ALLOCATED_BITMASK ) == 0 )
#وصف_ڪريو secureheap_بلاڪ_IS_ALLOCATED( px_بلاڪ )        ( ( ( px_بلاڪ->x_بلاڪ_سائيز ) & secureheap_بلاڪ_ALLOCATED_BITMASK ) != 0 )
#وصف_ڪريو secureheap_ALLOCATE_بلاڪ( px_بلاڪ )            ( ( px_بلاڪ->x_بلاڪ_سائيز ) |= secureheap_بلاڪ_ALLOCATED_BITMASK )
#وصف_ڪريو secureheap_FREE_بلاڪ( px_بلاڪ )                ( ( px_بلاڪ->x_بلاڪ_سائيز ) &= ~secureheap_بلاڪ_ALLOCATED_BITMASK )
/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#إذا ( config_APPLICATION_ALLOCATED_ڍير == 1 )

/* The application writer has already defined the array used for the RTOS
* heap - probably so it can be placed in a special segment or address. */
    خارجي uint8_t uc_ڍير[ secureconfig_ڪل_ڍير_سائيز ];
#وإلا /* configAPPLICATION_ALLOCATED_HEAP */
    ساكن uint8_t uc_ڍير[ secureconfig_ڪل_ڍير_سائيز ];
#جيڪڏهن_پورو /* configAPPLICATION_ALLOCATED_HEAP */

/**
 * @brief The linked list structure.
 *
 * This is used to link free blocks in order of their memory address.
 */
تعريفنوع بنية A_بلاڪ_LINK
{
    بنية A_بلاڪ_LINK * px_ايندڙ_Free_بلاڪ; /**< The next free block in the list. */
    size_t x_بلاڪ_سائيز;                     /**< The size of the free block. */
} بلاڪ_Link_t;
/*-----------------------------------------------------------*/

/**
 * @brief Called automatically to setup the required heap structures the first
 * time pvPortMalloc() is called.
 */
ساكن فراغ prv_ڍير_Init( فراغ );

/**
 * @brief Inserts a block of memory that is being freed into the correct
 * position in the list of free memory blocks.
 *
 * The block being freed will be merged with the block in front it and/or the
 * block behind it if the memory blocks are adjacent to each other.
 *
 * @param[in] pxBlockToInsert The block being freed.
 */
ساكن فراغ prv_وجهو_بلاڪ_Into_Free_List( بلاڪ_Link_t * px_بلاڪ_منزل_وجهو );
/*-----------------------------------------------------------*/

/**
 * @brief The size of the structure placed at the beginning of each allocated
 * memory block must by correctly byte aligned.
 */
ساكن ثابت size_t x_ڍير_Struct_سائيز = ( حجم( بلاڪ_Link_t ) + ( ( size_t ) ( secureportBYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) secureport_BYTE_ALIGNMENT_نقاب );

/**
 * @brief Create a couple of list links to mark the start and end of the list.
 */
ساكن بلاڪ_Link_t x_شروعات;
ساكن بلاڪ_Link_t * px_پڇاڙي = عدم;

/**
 * @brief Keeps track of the number of free bytes remaining, but says nothing
 * about fragmentation.
 */
ساكن size_t x_Free_بائيٽون_بچيل = 0U;
ساكن size_t x_Minimum_Ever_Free_بائيٽون_بچيل = 0U;

/*-----------------------------------------------------------*/

ساكن فراغ prv_ڍير_Init( فراغ )
{
    بلاڪ_Link_t * px_پهريون_Free_بلاڪ;
    uint8_t * puc_Aligned_ڍير;
    size_t ux_پتو;
    size_t x_ڪل_ڍير_سائيز = secureconfig_ڪل_ڍير_سائيز;

    /* Ensure the heap starts on a correctly aligned boundary. */
    ux_پتو = ( size_t ) uc_ڍير;

    إذا( ( ux_پتو & secureport_BYTE_ALIGNMENT_نقاب ) != 0 )
    {
        ux_پتو += ( secureportBYTE_ALIGNMENT - 1 );
        ux_پتو &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_نقاب );
        x_ڪل_ڍير_سائيز -= ux_پتو - ( size_t ) uc_ڍير;
    }

    puc_Aligned_ڍير = ( uint8_t * ) ux_پتو;

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_شروعات.px_ايندڙ_Free_بلاڪ = ( فراغ * ) puc_Aligned_ڍير;
    x_شروعات.x_بلاڪ_سائيز = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    ux_پتو = ( ( size_t ) puc_Aligned_ڍير ) + x_ڪل_ڍير_سائيز;
    ux_پتو -= x_ڍير_Struct_سائيز;
    ux_پتو &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_نقاب );
    px_پڇاڙي = ( فراغ * ) ux_پتو;
    px_پڇاڙي->x_بلاڪ_سائيز = 0;
    px_پڇاڙي->px_ايندڙ_Free_بلاڪ = عدم;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    px_پهريون_Free_بلاڪ = ( فراغ * ) puc_Aligned_ڍير;
    px_پهريون_Free_بلاڪ->x_بلاڪ_سائيز = ux_پتو - ( size_t ) px_پهريون_Free_بلاڪ;
    px_پهريون_Free_بلاڪ->px_ايندڙ_Free_بلاڪ = px_پڇاڙي;

    /* Only one block exists - and it covers the entire usable heap space. */
    x_Minimum_Ever_Free_بائيٽون_بچيل = px_پهريون_Free_بلاڪ->x_بلاڪ_سائيز;
    x_Free_بائيٽون_بچيل = px_پهريون_Free_بلاڪ->x_بلاڪ_سائيز;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_وجهو_بلاڪ_Into_Free_List( بلاڪ_Link_t * px_بلاڪ_منزل_وجهو )
{
    بلاڪ_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    لكل( pxIterator = &x_شروعات; pxIterator->px_ايندڙ_Free_بلاڪ < px_بلاڪ_منزل_وجهو; pxIterator = pxIterator->px_ايندڙ_Free_بلاڪ )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    إذا( ( puc + pxIterator->x_بلاڪ_سائيز ) == ( uint8_t * ) px_بلاڪ_منزل_وجهو )
    {
        pxIterator->x_بلاڪ_سائيز += px_بلاڪ_منزل_وجهو->x_بلاڪ_سائيز;
        px_بلاڪ_منزل_وجهو = pxIterator;
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_بلاڪ_منزل_وجهو;

    إذا( ( puc + px_بلاڪ_منزل_وجهو->x_بلاڪ_سائيز ) == ( uint8_t * ) pxIterator->px_ايندڙ_Free_بلاڪ )
    {
        إذا( pxIterator->px_ايندڙ_Free_بلاڪ != px_پڇاڙي )
        {
            /* Form one big block from the two blocks. */
            px_بلاڪ_منزل_وجهو->x_بلاڪ_سائيز += pxIterator->px_ايندڙ_Free_بلاڪ->x_بلاڪ_سائيز;
            px_بلاڪ_منزل_وجهو->px_ايندڙ_Free_بلاڪ = pxIterator->px_ايندڙ_Free_بلاڪ->px_ايندڙ_Free_بلاڪ;
        }
        وإلا
        {
            px_بلاڪ_منزل_وجهو->px_ايندڙ_Free_بلاڪ = px_پڇاڙي;
        }
    }
    وإلا
    {
        px_بلاڪ_منزل_وجهو->px_ايندڙ_Free_بلاڪ = pxIterator->px_ايندڙ_Free_بلاڪ;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    إذا( pxIterator != px_بلاڪ_منزل_وجهو )
    {
        pxIterator->px_ايندڙ_Free_بلاڪ = px_بلاڪ_منزل_وجهو;
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

فراغ * pv_پورٽ_Malloc( size_t x_Wanted_سائيز )
{
    بلاڪ_Link_t * px_بلاڪ;
    بلاڪ_Link_t * px_اڳيون_بلاڪ;
    بلاڪ_Link_t * px_New_بلاڪ_Link;
    فراغ * pvReturn = عدم;
    size_t x_Additional_Required_سائيز;
    size_t x_Allocated_بلاڪ_سائيز = 0;

    /* If this is the first call to malloc then the heap will require
     * initialisation to setup the list of free blocks. */
    إذا( px_پڇاڙي == عدم )
    {
        prv_ڍير_Init();
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }

    إذا( x_Wanted_سائيز > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        إذا( secureheap_جوڙيو_WILL_حد_کان_مٿي( x_Wanted_سائيز, x_ڍير_Struct_سائيز ) == 0 )
        {
            x_Wanted_سائيز += x_ڍير_Struct_سائيز;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            إذا( ( x_Wanted_سائيز & secureport_BYTE_ALIGNMENT_نقاب ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_سائيز = secureportBYTE_ALIGNMENT - ( x_Wanted_سائيز & secureport_BYTE_ALIGNMENT_نقاب );

                إذا( secureheap_جوڙيو_WILL_حد_کان_مٿي( x_Wanted_سائيز, x_Additional_Required_سائيز ) == 0 )
                {
                    x_Wanted_سائيز += x_Additional_Required_سائيز;
                }
                وإلا
                {
                    x_Wanted_سائيز = 0;
                }
            }
            وإلا
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        وإلا
        {
            x_Wanted_سائيز = 0;
        }
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Check the requested block size is not so large that the top bit is set.
     * The top bit of the block size member of the BlockLink_t structure is used
     * to determine who owns the block - the application or the kernel, so it
     * must be free. */
    إذا( secureheap_بلاڪ_سائيز_IS_VALID( x_Wanted_سائيز ) != 0 )
    {
        إذا( ( x_Wanted_سائيز > 0 ) && ( x_Wanted_سائيز <= x_Free_بائيٽون_بچيل ) )
        {
            /* Traverse the list from the start (lowest address) block until
             * one of adequate size is found. */
            px_اڳيون_بلاڪ = &x_شروعات;
            px_بلاڪ = x_شروعات.px_ايندڙ_Free_بلاڪ;

            طالما( ( px_بلاڪ->x_بلاڪ_سائيز < x_Wanted_سائيز ) && ( px_بلاڪ->px_ايندڙ_Free_بلاڪ != عدم ) )
            {
                px_اڳيون_بلاڪ = px_بلاڪ;
                px_بلاڪ = px_بلاڪ->px_ايندڙ_Free_بلاڪ;
            }

            /* If the end marker was reached then a block of adequate size was
             * not found. */
            إذا( px_بلاڪ != px_پڇاڙي )
            {
                /* Return the memory space pointed to - jumping over the
                 * BlockLink_t structure at its start. */
                pvReturn = ( فراغ * ) ( ( ( uint8_t * ) px_اڳيون_بلاڪ->px_ايندڙ_Free_بلاڪ ) + x_ڍير_Struct_سائيز );

                /* This block is being returned for use so must be taken out
                 * of the list of free blocks. */
                px_اڳيون_بلاڪ->px_ايندڙ_Free_بلاڪ = px_بلاڪ->px_ايندڙ_Free_بلاڪ;

                /* If the block is larger than required it can be split into
                 * two. */
                إذا( ( px_بلاڪ->x_بلاڪ_سائيز - x_Wanted_سائيز ) > secureheap_MINIMUM_بلاڪ_سائيز )
                {
                    /* This block is to be split into two.  Create a new
                     * block following the number of bytes requested. The void
                     * cast is used to prevent byte alignment warnings from the
                     * compiler. */
                    px_New_بلاڪ_Link = ( فراغ * ) ( ( ( uint8_t * ) px_بلاڪ ) + x_Wanted_سائيز );
                    secureportASSERT( ( ( ( size_t ) px_New_بلاڪ_Link ) & secureport_BYTE_ALIGNMENT_نقاب ) == 0 );

                    /* Calculate the sizes of two blocks split from the single
                     * block. */
                    px_New_بلاڪ_Link->x_بلاڪ_سائيز = px_بلاڪ->x_بلاڪ_سائيز - x_Wanted_سائيز;
                    px_بلاڪ->x_بلاڪ_سائيز = x_Wanted_سائيز;

                    /* Insert the new block into the list of free blocks. */
                    px_New_بلاڪ_Link->px_ايندڙ_Free_بلاڪ = px_اڳيون_بلاڪ->px_ايندڙ_Free_بلاڪ;
                    px_اڳيون_بلاڪ->px_ايندڙ_Free_بلاڪ = px_New_بلاڪ_Link;
                }
                وإلا
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Free_بائيٽون_بچيل -= px_بلاڪ->x_بلاڪ_سائيز;

                إذا( x_Free_بائيٽون_بچيل < x_Minimum_Ever_Free_بائيٽون_بچيل )
                {
                    x_Minimum_Ever_Free_بائيٽون_بچيل = x_Free_بائيٽون_بچيل;
                }
                وإلا
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Allocated_بلاڪ_سائيز = px_بلاڪ->x_بلاڪ_سائيز;

                /* The block is being returned - it is allocated and owned by
                 * the application and has no "next" block. */
                secureheap_ALLOCATE_بلاڪ( px_بلاڪ );
                px_بلاڪ->px_ايندڙ_Free_بلاڪ = عدم;
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

    traceMALLOC( pvReturn, x_Allocated_بلاڪ_سائيز );

    /* Prevent compiler warnings when trace macros are not used. */
    ( فراغ ) x_Allocated_بلاڪ_سائيز;

    #إذا ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 )
    {
        إذا( pvReturn == عدم )
        {
            خارجي فراغ vApplicationMallocFailedHook( فراغ );
            vApplicationMallocFailedHook();
        }
        وإلا
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #جيڪڏهن_پورو /* if ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 ) */

    secureportASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) secureport_BYTE_ALIGNMENT_نقاب ) == 0 );
    أرجع pvReturn;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Free( فراغ * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    بلاڪ_Link_t * pxLink;

    إذا( pv != عدم )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_ڍير_Struct_سائيز;

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( فراغ * ) puc;

        /* Check the block is actually allocated. */
        secureportASSERT( secureheap_بلاڪ_IS_ALLOCATED( pxLink ) != 0 );
        secureportASSERT( pxLink->px_ايندڙ_Free_بلاڪ == عدم );

        إذا( secureheap_بلاڪ_IS_ALLOCATED( pxLink ) != 0 )
        {
            إذا( pxLink->px_ايندڙ_Free_بلاڪ == عدم )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                secureheap_FREE_بلاڪ( pxLink );

                secureportDISABLE_NON_SECURE_INTERRUPTS();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_بائيٽون_بچيل += pxLink->x_بلاڪ_سائيز;
                    traceFREE( pv, pxLink->x_بلاڪ_سائيز );
                    prv_وجهو_بلاڪ_Into_Free_List( ( ( بلاڪ_Link_t * ) pxLink ) );
                }
                secureportENABLE_NON_SECURE_INTERRUPTS();
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

size_t x_پورٽ_Get_Free_ڍير_سائيز( فراغ )
{
    أرجع x_Free_بائيٽون_بچيل;
}
/*-----------------------------------------------------------*/

size_t x_پورٽ_Get_Minimum_Ever_Free_ڍير_سائيز( فراغ )
{
    أرجع x_Minimum_Ever_Free_بائيٽون_بچيل;
}
/*-----------------------------------------------------------*/
