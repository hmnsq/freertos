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
#اگر_تعریف_نشده secureconfig_مجموع_انباشته_اندازه
    #تعریف_کن secureconfig_مجموع_انباشته_اندازه    ( ( ( size_t ) ( 10 * 1024 ) ) )
#پایان_اگر

/* No test marker by default. */
#اگر_تعریف_نشده mtCOVERAGE_TEST_MARKER
    #تعریف_کن mtCOVERAGE_TEST_MARKER()
#پایان_اگر

/* No tracing by default. */
#اگر_تعریف_نشده traceMALLOC
    #تعریف_کن traceMALLOC( pvReturn, x_Wanted_اندازه )
#پایان_اگر

/* No tracing by default. */
#اگر_تعریف_نشده traceFREE
    #تعریف_کن traceFREE( pv, x_بلوک_اندازه )
#پایان_اگر

/* Block sizes must not get too small. */
#تعریف_کن secureheap_MINIMUM_بلوک_اندازه    ( ( size_t ) ( x_انباشته_Struct_اندازه << 1 ) )

/* Assumes 8bit bytes! */
#تعریف_کن secureheap_بیتها_در_هر_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#تعریف_کن secureheap_اندازه_MAX              ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کن secureheap_جمع_کن_WILL_سرریز( a, b )    ( ( a ) > ( secureheap_اندازه_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#تعریف_کن secureheap_بلوک_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( حجم( size_t ) * secureheap_بیتها_در_هر_BYTE ) - 1 ) )
#تعریف_کن secureheap_بلوک_اندازه_IS_VALID( x_بلوک_اندازه )    ( ( ( x_بلوک_اندازه ) & secureheap_بلوک_ALLOCATED_BITMASK ) == 0 )
#تعریف_کن secureheap_بلوک_IS_ALLOCATED( px_بلوک )        ( ( ( px_بلوک->x_بلوک_اندازه ) & secureheap_بلوک_ALLOCATED_BITMASK ) != 0 )
#تعریف_کن secureheap_ALLOCATE_بلوک( px_بلوک )            ( ( px_بلوک->x_بلوک_اندازه ) |= secureheap_بلوک_ALLOCATED_BITMASK )
#تعریف_کن secureheap_FREE_بلوک( px_بلوک )                ( ( px_بلوک->x_بلوک_اندازه ) &= ~secureheap_بلوک_ALLOCATED_BITMASK )
/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#إذا ( config_APPLICATION_ALLOCATED_انباشته == 1 )

/* The application writer has already defined the array used for the RTOS
* heap - probably so it can be placed in a special segment or address. */
    خارجي uint8_t uc_انباشته[ secureconfig_مجموع_انباشته_اندازه ];
#وإلا /* configAPPLICATION_ALLOCATED_HEAP */
    ساكن uint8_t uc_انباشته[ secureconfig_مجموع_انباشته_اندازه ];
#پایان_اگر /* configAPPLICATION_ALLOCATED_HEAP */

/**
 * @brief The linked list structure.
 *
 * This is used to link free blocks in order of their memory address.
 */
تعريفنوع بنية A_بلوک_LINK
{
    بنية A_بلوک_LINK * px_بعدی_Free_بلوک; /**< The next free block in the list. */
    size_t x_بلوک_اندازه;                     /**< The size of the free block. */
} بلوک_Link_t;
/*-----------------------------------------------------------*/

/**
 * @brief Called automatically to setup the required heap structures the first
 * time pvPortMalloc() is called.
 */
ساكن فراغ prv_انباشته_Init( فراغ );

/**
 * @brief Inserts a block of memory that is being freed into the correct
 * position in the list of free memory blocks.
 *
 * The block being freed will be merged with the block in front it and/or the
 * block behind it if the memory blocks are adjacent to each other.
 *
 * @param[in] pxBlockToInsert The block being freed.
 */
ساكن فراغ prv_درج_بلوک_Into_Free_List( بلوک_Link_t * px_بلوک_مقصد_درج );
/*-----------------------------------------------------------*/

/**
 * @brief The size of the structure placed at the beginning of each allocated
 * memory block must by correctly byte aligned.
 */
ساكن ثابت size_t x_انباشته_Struct_اندازه = ( حجم( بلوک_Link_t ) + ( ( size_t ) ( secureportBYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) secureport_BYTE_ALIGNMENT_ماسک );

/**
 * @brief Create a couple of list links to mark the start and end of the list.
 */
ساكن بلوک_Link_t x_شروع;
ساكن بلوک_Link_t * px_انتها = عدم;

/**
 * @brief Keeps track of the number of free bytes remaining, but says nothing
 * about fragmentation.
 */
ساكن size_t x_Free_بایتها_مانده = 0U;
ساكن size_t x_Minimum_Ever_Free_بایتها_مانده = 0U;

/*-----------------------------------------------------------*/

ساكن فراغ prv_انباشته_Init( فراغ )
{
    بلوک_Link_t * px_اولی_Free_بلوک;
    uint8_t * puc_Aligned_انباشته;
    size_t ux_آدرس;
    size_t x_مجموع_انباشته_اندازه = secureconfig_مجموع_انباشته_اندازه;

    /* Ensure the heap starts on a correctly aligned boundary. */
    ux_آدرس = ( size_t ) uc_انباشته;

    إذا( ( ux_آدرس & secureport_BYTE_ALIGNMENT_ماسک ) != 0 )
    {
        ux_آدرس += ( secureportBYTE_ALIGNMENT - 1 );
        ux_آدرس &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_ماسک );
        x_مجموع_انباشته_اندازه -= ux_آدرس - ( size_t ) uc_انباشته;
    }

    puc_Aligned_انباشته = ( uint8_t * ) ux_آدرس;

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_شروع.px_بعدی_Free_بلوک = ( فراغ * ) puc_Aligned_انباشته;
    x_شروع.x_بلوک_اندازه = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    ux_آدرس = ( ( size_t ) puc_Aligned_انباشته ) + x_مجموع_انباشته_اندازه;
    ux_آدرس -= x_انباشته_Struct_اندازه;
    ux_آدرس &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_ماسک );
    px_انتها = ( فراغ * ) ux_آدرس;
    px_انتها->x_بلوک_اندازه = 0;
    px_انتها->px_بعدی_Free_بلوک = عدم;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    px_اولی_Free_بلوک = ( فراغ * ) puc_Aligned_انباشته;
    px_اولی_Free_بلوک->x_بلوک_اندازه = ux_آدرس - ( size_t ) px_اولی_Free_بلوک;
    px_اولی_Free_بلوک->px_بعدی_Free_بلوک = px_انتها;

    /* Only one block exists - and it covers the entire usable heap space. */
    x_Minimum_Ever_Free_بایتها_مانده = px_اولی_Free_بلوک->x_بلوک_اندازه;
    x_Free_بایتها_مانده = px_اولی_Free_بلوک->x_بلوک_اندازه;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_درج_بلوک_Into_Free_List( بلوک_Link_t * px_بلوک_مقصد_درج )
{
    بلوک_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    لكل( pxIterator = &x_شروع; pxIterator->px_بعدی_Free_بلوک < px_بلوک_مقصد_درج; pxIterator = pxIterator->px_بعدی_Free_بلوک )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    إذا( ( puc + pxIterator->x_بلوک_اندازه ) == ( uint8_t * ) px_بلوک_مقصد_درج )
    {
        pxIterator->x_بلوک_اندازه += px_بلوک_مقصد_درج->x_بلوک_اندازه;
        px_بلوک_مقصد_درج = pxIterator;
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_بلوک_مقصد_درج;

    إذا( ( puc + px_بلوک_مقصد_درج->x_بلوک_اندازه ) == ( uint8_t * ) pxIterator->px_بعدی_Free_بلوک )
    {
        إذا( pxIterator->px_بعدی_Free_بلوک != px_انتها )
        {
            /* Form one big block from the two blocks. */
            px_بلوک_مقصد_درج->x_بلوک_اندازه += pxIterator->px_بعدی_Free_بلوک->x_بلوک_اندازه;
            px_بلوک_مقصد_درج->px_بعدی_Free_بلوک = pxIterator->px_بعدی_Free_بلوک->px_بعدی_Free_بلوک;
        }
        وإلا
        {
            px_بلوک_مقصد_درج->px_بعدی_Free_بلوک = px_انتها;
        }
    }
    وإلا
    {
        px_بلوک_مقصد_درج->px_بعدی_Free_بلوک = pxIterator->px_بعدی_Free_بلوک;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    إذا( pxIterator != px_بلوک_مقصد_درج )
    {
        pxIterator->px_بعدی_Free_بلوک = px_بلوک_مقصد_درج;
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

فراغ * pv_پورت_Malloc( size_t x_Wanted_اندازه )
{
    بلوک_Link_t * px_بلوک;
    بلوک_Link_t * px_قبلی_بلوک;
    بلوک_Link_t * px_New_بلوک_Link;
    فراغ * pvReturn = عدم;
    size_t x_Additional_Required_اندازه;
    size_t x_Allocated_بلوک_اندازه = 0;

    /* If this is the first call to malloc then the heap will require
     * initialisation to setup the list of free blocks. */
    إذا( px_انتها == عدم )
    {
        prv_انباشته_Init();
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }

    إذا( x_Wanted_اندازه > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        إذا( secureheap_جمع_کن_WILL_سرریز( x_Wanted_اندازه, x_انباشته_Struct_اندازه ) == 0 )
        {
            x_Wanted_اندازه += x_انباشته_Struct_اندازه;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            إذا( ( x_Wanted_اندازه & secureport_BYTE_ALIGNMENT_ماسک ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_اندازه = secureportBYTE_ALIGNMENT - ( x_Wanted_اندازه & secureport_BYTE_ALIGNMENT_ماسک );

                إذا( secureheap_جمع_کن_WILL_سرریز( x_Wanted_اندازه, x_Additional_Required_اندازه ) == 0 )
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
    إذا( secureheap_بلوک_اندازه_IS_VALID( x_Wanted_اندازه ) != 0 )
    {
        إذا( ( x_Wanted_اندازه > 0 ) && ( x_Wanted_اندازه <= x_Free_بایتها_مانده ) )
        {
            /* Traverse the list from the start (lowest address) block until
             * one of adequate size is found. */
            px_قبلی_بلوک = &x_شروع;
            px_بلوک = x_شروع.px_بعدی_Free_بلوک;

            طالما( ( px_بلوک->x_بلوک_اندازه < x_Wanted_اندازه ) && ( px_بلوک->px_بعدی_Free_بلوک != عدم ) )
            {
                px_قبلی_بلوک = px_بلوک;
                px_بلوک = px_بلوک->px_بعدی_Free_بلوک;
            }

            /* If the end marker was reached then a block of adequate size was
             * not found. */
            إذا( px_بلوک != px_انتها )
            {
                /* Return the memory space pointed to - jumping over the
                 * BlockLink_t structure at its start. */
                pvReturn = ( فراغ * ) ( ( ( uint8_t * ) px_قبلی_بلوک->px_بعدی_Free_بلوک ) + x_انباشته_Struct_اندازه );

                /* This block is being returned for use so must be taken out
                 * of the list of free blocks. */
                px_قبلی_بلوک->px_بعدی_Free_بلوک = px_بلوک->px_بعدی_Free_بلوک;

                /* If the block is larger than required it can be split into
                 * two. */
                إذا( ( px_بلوک->x_بلوک_اندازه - x_Wanted_اندازه ) > secureheap_MINIMUM_بلوک_اندازه )
                {
                    /* This block is to be split into two.  Create a new
                     * block following the number of bytes requested. The void
                     * cast is used to prevent byte alignment warnings from the
                     * compiler. */
                    px_New_بلوک_Link = ( فراغ * ) ( ( ( uint8_t * ) px_بلوک ) + x_Wanted_اندازه );
                    secureportASSERT( ( ( ( size_t ) px_New_بلوک_Link ) & secureport_BYTE_ALIGNMENT_ماسک ) == 0 );

                    /* Calculate the sizes of two blocks split from the single
                     * block. */
                    px_New_بلوک_Link->x_بلوک_اندازه = px_بلوک->x_بلوک_اندازه - x_Wanted_اندازه;
                    px_بلوک->x_بلوک_اندازه = x_Wanted_اندازه;

                    /* Insert the new block into the list of free blocks. */
                    px_New_بلوک_Link->px_بعدی_Free_بلوک = px_قبلی_بلوک->px_بعدی_Free_بلوک;
                    px_قبلی_بلوک->px_بعدی_Free_بلوک = px_New_بلوک_Link;
                }
                وإلا
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Free_بایتها_مانده -= px_بلوک->x_بلوک_اندازه;

                إذا( x_Free_بایتها_مانده < x_Minimum_Ever_Free_بایتها_مانده )
                {
                    x_Minimum_Ever_Free_بایتها_مانده = x_Free_بایتها_مانده;
                }
                وإلا
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Allocated_بلوک_اندازه = px_بلوک->x_بلوک_اندازه;

                /* The block is being returned - it is allocated and owned by
                 * the application and has no "next" block. */
                secureheap_ALLOCATE_بلوک( px_بلوک );
                px_بلوک->px_بعدی_Free_بلوک = عدم;
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

    traceMALLOC( pvReturn, x_Allocated_بلوک_اندازه );

    /* Prevent compiler warnings when trace macros are not used. */
    ( فراغ ) x_Allocated_بلوک_اندازه;

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
    #پایان_اگر /* if ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 ) */

    secureportASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) secureport_BYTE_ALIGNMENT_ماسک ) == 0 );
    أرجع pvReturn;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Free( فراغ * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    بلوک_Link_t * pxLink;

    إذا( pv != عدم )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_انباشته_Struct_اندازه;

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( فراغ * ) puc;

        /* Check the block is actually allocated. */
        secureportASSERT( secureheap_بلوک_IS_ALLOCATED( pxLink ) != 0 );
        secureportASSERT( pxLink->px_بعدی_Free_بلوک == عدم );

        إذا( secureheap_بلوک_IS_ALLOCATED( pxLink ) != 0 )
        {
            إذا( pxLink->px_بعدی_Free_بلوک == عدم )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                secureheap_FREE_بلوک( pxLink );

                secureportDISABLE_NON_SECURE_INTERRUPTS();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_بایتها_مانده += pxLink->x_بلوک_اندازه;
                    traceFREE( pv, pxLink->x_بلوک_اندازه );
                    prv_درج_بلوک_Into_Free_List( ( ( بلوک_Link_t * ) pxLink ) );
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

size_t x_پورت_Get_Free_انباشته_اندازه( فراغ )
{
    أرجع x_Free_بایتها_مانده;
}
/*-----------------------------------------------------------*/

size_t x_پورت_Get_Minimum_Ever_Free_انباشته_اندازه( فراغ )
{
    أرجع x_Minimum_Ever_Free_بایتها_مانده;
}
/*-----------------------------------------------------------*/
