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
#که_نه_تعریف_شوی secureconfig_ټول_ډېرۍ_اندازه
    #تعریف_کړه secureconfig_ټول_ډېرۍ_اندازه    ( ( ( size_t ) ( 10 * 1024 ) ) )
#د_که_پای

/* No test marker by default. */
#که_نه_تعریف_شوی mtCOVERAGE_TEST_MARKER
    #تعریف_کړه mtCOVERAGE_TEST_MARKER()
#د_که_پای

/* No tracing by default. */
#که_نه_تعریف_شوی traceMALLOC
    #تعریف_کړه traceMALLOC( pvReturn, x_Wanted_اندازه )
#د_که_پای

/* No tracing by default. */
#که_نه_تعریف_شوی traceFREE
    #تعریف_کړه traceFREE( pv, x_بلاک_اندازه )
#د_که_پای

/* Block sizes must not get too small. */
#تعریف_کړه secureheap_MINIMUM_بلاک_اندازه    ( ( size_t ) ( x_ډېرۍ_Struct_اندازه << 1 ) )

/* Assumes 8bit bytes! */
#تعریف_کړه secureheap_بټونه_فی_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#تعریف_کړه secureheap_اندازه_MAX              ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کړه secureheap_جمع_کړه_WILL_ډکېدنه( a, b )    ( ( a ) > ( secureheap_اندازه_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#تعریف_کړه secureheap_بلاک_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( حجم( size_t ) * secureheap_بټونه_فی_BYTE ) - 1 ) )
#تعریف_کړه secureheap_بلاک_اندازه_IS_VALID( x_بلاک_اندازه )    ( ( ( x_بلاک_اندازه ) & secureheap_بلاک_ALLOCATED_BITMASK ) == 0 )
#تعریف_کړه secureheap_بلاک_IS_ALLOCATED( px_بلاک )        ( ( ( px_بلاک->x_بلاک_اندازه ) & secureheap_بلاک_ALLOCATED_BITMASK ) != 0 )
#تعریف_کړه secureheap_ALLOCATE_بلاک( px_بلاک )            ( ( px_بلاک->x_بلاک_اندازه ) |= secureheap_بلاک_ALLOCATED_BITMASK )
#تعریف_کړه secureheap_FREE_بلاک( px_بلاک )                ( ( px_بلاک->x_بلاک_اندازه ) &= ~secureheap_بلاک_ALLOCATED_BITMASK )
/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#إذا ( config_APPLICATION_ALLOCATED_ډېرۍ == 1 )

/* The application writer has already defined the array used for the RTOS
* heap - probably so it can be placed in a special segment or address. */
    خارجي uint8_t uc_ډېرۍ[ secureconfig_ټول_ډېرۍ_اندازه ];
#وإلا /* configAPPLICATION_ALLOCATED_HEAP */
    ساكن uint8_t uc_ډېرۍ[ secureconfig_ټول_ډېرۍ_اندازه ];
#د_که_پای /* configAPPLICATION_ALLOCATED_HEAP */

/**
 * @brief The linked list structure.
 *
 * This is used to link free blocks in order of their memory address.
 */
تعريفنوع بنية A_بلاک_LINK
{
    بنية A_بلاک_LINK * px_بل_Free_بلاک; /**< The next free block in the list. */
    size_t x_بلاک_اندازه;                     /**< The size of the free block. */
} بلاک_Link_t;
/*-----------------------------------------------------------*/

/**
 * @brief Called automatically to setup the required heap structures the first
 * time pvPortMalloc() is called.
 */
ساكن فراغ prv_ډېرۍ_Init( فراغ );

/**
 * @brief Inserts a block of memory that is being freed into the correct
 * position in the list of free memory blocks.
 *
 * The block being freed will be merged with the block in front it and/or the
 * block behind it if the memory blocks are adjacent to each other.
 *
 * @param[in] pxBlockToInsert The block being freed.
 */
ساكن فراغ prv_ورننباسه_بلاک_Into_Free_List( بلاک_Link_t * px_بلاک_منزل_ورننباسه );
/*-----------------------------------------------------------*/

/**
 * @brief The size of the structure placed at the beginning of each allocated
 * memory block must by correctly byte aligned.
 */
ساكن ثابت size_t x_ډېرۍ_Struct_اندازه = ( حجم( بلاک_Link_t ) + ( ( size_t ) ( secureportBYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) secureport_BYTE_ALIGNMENT_ماسک );

/**
 * @brief Create a couple of list links to mark the start and end of the list.
 */
ساكن بلاک_Link_t x_پیل;
ساكن بلاک_Link_t * px_پای_ټکی = عدم;

/**
 * @brief Keeps track of the number of free bytes remaining, but says nothing
 * about fragmentation.
 */
ساكن size_t x_Free_بایټونه_پاتې_شوی = 0U;
ساكن size_t x_Minimum_Ever_Free_بایټونه_پاتې_شوی = 0U;

/*-----------------------------------------------------------*/

ساكن فراغ prv_ډېرۍ_Init( فراغ )
{
    بلاک_Link_t * px_لومړی_Free_بلاک;
    uint8_t * puc_Aligned_ډېرۍ;
    size_t ux_پته;
    size_t x_ټول_ډېرۍ_اندازه = secureconfig_ټول_ډېرۍ_اندازه;

    /* Ensure the heap starts on a correctly aligned boundary. */
    ux_پته = ( size_t ) uc_ډېرۍ;

    إذا( ( ux_پته & secureport_BYTE_ALIGNMENT_ماسک ) != 0 )
    {
        ux_پته += ( secureportBYTE_ALIGNMENT - 1 );
        ux_پته &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_ماسک );
        x_ټول_ډېرۍ_اندازه -= ux_پته - ( size_t ) uc_ډېرۍ;
    }

    puc_Aligned_ډېرۍ = ( uint8_t * ) ux_پته;

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_پیل.px_بل_Free_بلاک = ( فراغ * ) puc_Aligned_ډېرۍ;
    x_پیل.x_بلاک_اندازه = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    ux_پته = ( ( size_t ) puc_Aligned_ډېرۍ ) + x_ټول_ډېرۍ_اندازه;
    ux_پته -= x_ډېرۍ_Struct_اندازه;
    ux_پته &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_ماسک );
    px_پای_ټکی = ( فراغ * ) ux_پته;
    px_پای_ټکی->x_بلاک_اندازه = 0;
    px_پای_ټکی->px_بل_Free_بلاک = عدم;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    px_لومړی_Free_بلاک = ( فراغ * ) puc_Aligned_ډېرۍ;
    px_لومړی_Free_بلاک->x_بلاک_اندازه = ux_پته - ( size_t ) px_لومړی_Free_بلاک;
    px_لومړی_Free_بلاک->px_بل_Free_بلاک = px_پای_ټکی;

    /* Only one block exists - and it covers the entire usable heap space. */
    x_Minimum_Ever_Free_بایټونه_پاتې_شوی = px_لومړی_Free_بلاک->x_بلاک_اندازه;
    x_Free_بایټونه_پاتې_شوی = px_لومړی_Free_بلاک->x_بلاک_اندازه;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_ورننباسه_بلاک_Into_Free_List( بلاک_Link_t * px_بلاک_منزل_ورننباسه )
{
    بلاک_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    لكل( pxIterator = &x_پیل; pxIterator->px_بل_Free_بلاک < px_بلاک_منزل_ورننباسه; pxIterator = pxIterator->px_بل_Free_بلاک )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    إذا( ( puc + pxIterator->x_بلاک_اندازه ) == ( uint8_t * ) px_بلاک_منزل_ورننباسه )
    {
        pxIterator->x_بلاک_اندازه += px_بلاک_منزل_ورننباسه->x_بلاک_اندازه;
        px_بلاک_منزل_ورننباسه = pxIterator;
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_بلاک_منزل_ورننباسه;

    إذا( ( puc + px_بلاک_منزل_ورننباسه->x_بلاک_اندازه ) == ( uint8_t * ) pxIterator->px_بل_Free_بلاک )
    {
        إذا( pxIterator->px_بل_Free_بلاک != px_پای_ټکی )
        {
            /* Form one big block from the two blocks. */
            px_بلاک_منزل_ورننباسه->x_بلاک_اندازه += pxIterator->px_بل_Free_بلاک->x_بلاک_اندازه;
            px_بلاک_منزل_ورننباسه->px_بل_Free_بلاک = pxIterator->px_بل_Free_بلاک->px_بل_Free_بلاک;
        }
        وإلا
        {
            px_بلاک_منزل_ورننباسه->px_بل_Free_بلاک = px_پای_ټکی;
        }
    }
    وإلا
    {
        px_بلاک_منزل_ورننباسه->px_بل_Free_بلاک = pxIterator->px_بل_Free_بلاک;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    إذا( pxIterator != px_بلاک_منزل_ورننباسه )
    {
        pxIterator->px_بل_Free_بلاک = px_بلاک_منزل_ورننباسه;
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

فراغ * pv_پورټ_Malloc( size_t x_Wanted_اندازه )
{
    بلاک_Link_t * px_بلاک;
    بلاک_Link_t * px_پخوانی_بلاک;
    بلاک_Link_t * px_New_بلاک_Link;
    فراغ * pvReturn = عدم;
    size_t x_Additional_Required_اندازه;
    size_t x_Allocated_بلاک_اندازه = 0;

    /* If this is the first call to malloc then the heap will require
     * initialisation to setup the list of free blocks. */
    إذا( px_پای_ټکی == عدم )
    {
        prv_ډېرۍ_Init();
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }

    إذا( x_Wanted_اندازه > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        إذا( secureheap_جمع_کړه_WILL_ډکېدنه( x_Wanted_اندازه, x_ډېرۍ_Struct_اندازه ) == 0 )
        {
            x_Wanted_اندازه += x_ډېرۍ_Struct_اندازه;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            إذا( ( x_Wanted_اندازه & secureport_BYTE_ALIGNMENT_ماسک ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_اندازه = secureportBYTE_ALIGNMENT - ( x_Wanted_اندازه & secureport_BYTE_ALIGNMENT_ماسک );

                إذا( secureheap_جمع_کړه_WILL_ډکېدنه( x_Wanted_اندازه, x_Additional_Required_اندازه ) == 0 )
                {
                    x_Wanted_اندازه += x_Additional_Required_اندازه;
                }
                وإلا
                {
                    x_Wanted_اندازه = 0;
                }
            }
            وإلا
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        وإلا
        {
            x_Wanted_اندازه = 0;
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
    إذا( secureheap_بلاک_اندازه_IS_VALID( x_Wanted_اندازه ) != 0 )
    {
        إذا( ( x_Wanted_اندازه > 0 ) && ( x_Wanted_اندازه <= x_Free_بایټونه_پاتې_شوی ) )
        {
            /* Traverse the list from the start (lowest address) block until
             * one of adequate size is found. */
            px_پخوانی_بلاک = &x_پیل;
            px_بلاک = x_پیل.px_بل_Free_بلاک;

            طالما( ( px_بلاک->x_بلاک_اندازه < x_Wanted_اندازه ) && ( px_بلاک->px_بل_Free_بلاک != عدم ) )
            {
                px_پخوانی_بلاک = px_بلاک;
                px_بلاک = px_بلاک->px_بل_Free_بلاک;
            }

            /* If the end marker was reached then a block of adequate size was
             * not found. */
            إذا( px_بلاک != px_پای_ټکی )
            {
                /* Return the memory space pointed to - jumping over the
                 * BlockLink_t structure at its start. */
                pvReturn = ( فراغ * ) ( ( ( uint8_t * ) px_پخوانی_بلاک->px_بل_Free_بلاک ) + x_ډېرۍ_Struct_اندازه );

                /* This block is being returned for use so must be taken out
                 * of the list of free blocks. */
                px_پخوانی_بلاک->px_بل_Free_بلاک = px_بلاک->px_بل_Free_بلاک;

                /* If the block is larger than required it can be split into
                 * two. */
                إذا( ( px_بلاک->x_بلاک_اندازه - x_Wanted_اندازه ) > secureheap_MINIMUM_بلاک_اندازه )
                {
                    /* This block is to be split into two.  Create a new
                     * block following the number of bytes requested. The void
                     * cast is used to prevent byte alignment warnings from the
                     * compiler. */
                    px_New_بلاک_Link = ( فراغ * ) ( ( ( uint8_t * ) px_بلاک ) + x_Wanted_اندازه );
                    secureportASSERT( ( ( ( size_t ) px_New_بلاک_Link ) & secureport_BYTE_ALIGNMENT_ماسک ) == 0 );

                    /* Calculate the sizes of two blocks split from the single
                     * block. */
                    px_New_بلاک_Link->x_بلاک_اندازه = px_بلاک->x_بلاک_اندازه - x_Wanted_اندازه;
                    px_بلاک->x_بلاک_اندازه = x_Wanted_اندازه;

                    /* Insert the new block into the list of free blocks. */
                    px_New_بلاک_Link->px_بل_Free_بلاک = px_پخوانی_بلاک->px_بل_Free_بلاک;
                    px_پخوانی_بلاک->px_بل_Free_بلاک = px_New_بلاک_Link;
                }
                وإلا
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Free_بایټونه_پاتې_شوی -= px_بلاک->x_بلاک_اندازه;

                إذا( x_Free_بایټونه_پاتې_شوی < x_Minimum_Ever_Free_بایټونه_پاتې_شوی )
                {
                    x_Minimum_Ever_Free_بایټونه_پاتې_شوی = x_Free_بایټونه_پاتې_شوی;
                }
                وإلا
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Allocated_بلاک_اندازه = px_بلاک->x_بلاک_اندازه;

                /* The block is being returned - it is allocated and owned by
                 * the application and has no "next" block. */
                secureheap_ALLOCATE_بلاک( px_بلاک );
                px_بلاک->px_بل_Free_بلاک = عدم;
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

    traceMALLOC( pvReturn, x_Allocated_بلاک_اندازه );

    /* Prevent compiler warnings when trace macros are not used. */
    ( فراغ ) x_Allocated_بلاک_اندازه;

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
    #د_که_پای /* if ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 ) */

    secureportASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) secureport_BYTE_ALIGNMENT_ماسک ) == 0 );
    أرجع pvReturn;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Free( فراغ * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    بلاک_Link_t * pxLink;

    إذا( pv != عدم )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_ډېرۍ_Struct_اندازه;

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( فراغ * ) puc;

        /* Check the block is actually allocated. */
        secureportASSERT( secureheap_بلاک_IS_ALLOCATED( pxLink ) != 0 );
        secureportASSERT( pxLink->px_بل_Free_بلاک == عدم );

        إذا( secureheap_بلاک_IS_ALLOCATED( pxLink ) != 0 )
        {
            إذا( pxLink->px_بل_Free_بلاک == عدم )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                secureheap_FREE_بلاک( pxLink );

                secureportDISABLE_NON_SECURE_INTERRUPTS();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_بایټونه_پاتې_شوی += pxLink->x_بلاک_اندازه;
                    traceFREE( pv, pxLink->x_بلاک_اندازه );
                    prv_ورننباسه_بلاک_Into_Free_List( ( ( بلاک_Link_t * ) pxLink ) );
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

size_t x_پورټ_Get_Free_ډېرۍ_اندازه( فراغ )
{
    أرجع x_Free_بایټونه_پاتې_شوی;
}
/*-----------------------------------------------------------*/

size_t x_پورټ_Get_Minimum_Ever_Free_ډېرۍ_اندازه( فراغ )
{
    أرجع x_Minimum_Ever_Free_بایټونه_پاتې_شوی;
}
/*-----------------------------------------------------------*/
