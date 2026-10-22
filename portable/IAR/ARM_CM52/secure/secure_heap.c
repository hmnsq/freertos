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
#شامل <stdint.h>

/* Configuration includes. */
#شامل "FreeRTOSConfig.h"

/* Secure context heap includes. */
#شامل "secure_heap.h"

/* Secure port macros. */
#شامل "secure_port_macros.h"

/**
 * @brief Total heap size.
 */
#اگر_غیر_تعریف_شدہ secureconfig_کل_ڈھیر_سائز
    #تعریف_کرو secureconfig_کل_ڈھیر_سائز    ( ( ( size_t ) ( 10 * 1024 ) ) )
#اگر_ختم

/* No test marker by default. */
#اگر_غیر_تعریف_شدہ mtCOVERAGE_TEST_MARKER
    #تعریف_کرو mtCOVERAGE_TEST_MARKER()
#اگر_ختم

/* No tracing by default. */
#اگر_غیر_تعریف_شدہ traceMALLOC
    #تعریف_کرو traceMALLOC( pvReturn, x_Wanted_سائز )
#اگر_ختم

/* No tracing by default. */
#اگر_غیر_تعریف_شدہ traceFREE
    #تعریف_کرو traceFREE( pv, x_بلاک_سائز )
#اگر_ختم

/* Block sizes must not get too small. */
#تعریف_کرو secureheap_MINIMUM_بلاک_سائز    ( ( size_t ) ( x_ڈھیر_Struct_سائز << 1 ) )

/* Assumes 8bit bytes! */
#تعریف_کرو secureheap_بٹ_فی_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#تعریف_کرو secureheap_سائز_MAX              ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کرو secureheap_جوڑو_WILL_حد_سے_تجاوز( a, b )    ( ( a ) > ( secureheap_سائز_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#تعریف_کرو secureheap_بلاک_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( حجم( size_t ) * secureheap_بٹ_فی_BYTE ) - 1 ) )
#تعریف_کرو secureheap_بلاک_سائز_IS_VALID( x_بلاک_سائز )    ( ( ( x_بلاک_سائز ) & secureheap_بلاک_ALLOCATED_BITMASK ) == 0 )
#تعریف_کرو secureheap_بلاک_IS_ALLOCATED( px_بلاک )        ( ( ( px_بلاک->x_بلاک_سائز ) & secureheap_بلاک_ALLOCATED_BITMASK ) != 0 )
#تعریف_کرو secureheap_ALLOCATE_بلاک( px_بلاک )            ( ( px_بلاک->x_بلاک_سائز ) |= secureheap_بلاک_ALLOCATED_BITMASK )
#تعریف_کرو secureheap_FREE_بلاک( px_بلاک )                ( ( px_بلاک->x_بلاک_سائز ) &= ~secureheap_بلاک_ALLOCATED_BITMASK )
/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#اگر ( config_APPLICATION_ALLOCATED_ڈھیر == 1 )

/* The application writer has already defined the array used for the RTOS
* heap - probably so it can be placed in a special segment or address. */
    خارجی uint8_t uc_ڈھیر[ secureconfig_کل_ڈھیر_سائز ];
#ورنہ /* configAPPLICATION_ALLOCATED_HEAP */
    ساکن uint8_t uc_ڈھیر[ secureconfig_کل_ڈھیر_سائز ];
#اگر_ختم /* configAPPLICATION_ALLOCATED_HEAP */

/**
 * @brief The linked list structure.
 *
 * This is used to link free blocks in order of their memory address.
 */
قسمتعریف ساخت A_بلاک_LINK
{
    ساخت A_بلاک_LINK * px_اگلا_Free_بلاک; /**< The next free block in the list. */
    size_t x_بلاک_سائز;                     /**< The size of the free block. */
} بلاک_Link_t;
/*-----------------------------------------------------------*/

/**
 * @brief Called automatically to setup the required heap structures the first
 * time pvPortMalloc() is called.
 */
ساکن خالی prv_ڈھیر_Init( خالی );

/**
 * @brief Inserts a block of memory that is being freed into the correct
 * position in the list of free memory blocks.
 *
 * The block being freed will be merged with the block in front it and/or the
 * block behind it if the memory blocks are adjacent to each other.
 *
 * @param[in] pxBlockToInsert The block being freed.
 */
ساکن خالی prv_داخل_کرو_بلاک_Into_Free_List( بلاک_Link_t * px_بلاک_مقصد_داخل_کرو );
/*-----------------------------------------------------------*/

/**
 * @brief The size of the structure placed at the beginning of each allocated
 * memory block must by correctly byte aligned.
 */
ساکن ثابت size_t x_ڈھیر_Struct_سائز = ( حجم( بلاک_Link_t ) + ( ( size_t ) ( secureportBYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) secureport_BYTE_ALIGNMENT_نقاب );

/**
 * @brief Create a couple of list links to mark the start and end of the list.
 */
ساکن بلاک_Link_t x_آغاز;
ساکن بلاک_Link_t * px_انتہا = تہی;

/**
 * @brief Keeps track of the number of free bytes remaining, but says nothing
 * about fragmentation.
 */
ساکن size_t x_Free_بائٹیں_بقایا = 0U;
ساکن size_t x_Minimum_Ever_Free_بائٹیں_بقایا = 0U;

/*-----------------------------------------------------------*/

ساکن خالی prv_ڈھیر_Init( خالی )
{
    بلاک_Link_t * px_پہلا_Free_بلاک;
    uint8_t * puc_Aligned_ڈھیر;
    size_t ux_پتہ;
    size_t x_کل_ڈھیر_سائز = secureconfig_کل_ڈھیر_سائز;

    /* Ensure the heap starts on a correctly aligned boundary. */
    ux_پتہ = ( size_t ) uc_ڈھیر;

    اگر( ( ux_پتہ & secureport_BYTE_ALIGNMENT_نقاب ) != 0 )
    {
        ux_پتہ += ( secureportBYTE_ALIGNMENT - 1 );
        ux_پتہ &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_نقاب );
        x_کل_ڈھیر_سائز -= ux_پتہ - ( size_t ) uc_ڈھیر;
    }

    puc_Aligned_ڈھیر = ( uint8_t * ) ux_پتہ;

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_آغاز.px_اگلا_Free_بلاک = ( خالی * ) puc_Aligned_ڈھیر;
    x_آغاز.x_بلاک_سائز = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    ux_پتہ = ( ( size_t ) puc_Aligned_ڈھیر ) + x_کل_ڈھیر_سائز;
    ux_پتہ -= x_ڈھیر_Struct_سائز;
    ux_پتہ &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_نقاب );
    px_انتہا = ( خالی * ) ux_پتہ;
    px_انتہا->x_بلاک_سائز = 0;
    px_انتہا->px_اگلا_Free_بلاک = تہی;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    px_پہلا_Free_بلاک = ( خالی * ) puc_Aligned_ڈھیر;
    px_پہلا_Free_بلاک->x_بلاک_سائز = ux_پتہ - ( size_t ) px_پہلا_Free_بلاک;
    px_پہلا_Free_بلاک->px_اگلا_Free_بلاک = px_انتہا;

    /* Only one block exists - and it covers the entire usable heap space. */
    x_Minimum_Ever_Free_بائٹیں_بقایا = px_پہلا_Free_بلاک->x_بلاک_سائز;
    x_Free_بائٹیں_بقایا = px_پہلا_Free_بلاک->x_بلاک_سائز;
}
/*-----------------------------------------------------------*/

ساکن خالی prv_داخل_کرو_بلاک_Into_Free_List( بلاک_Link_t * px_بلاک_مقصد_داخل_کرو )
{
    بلاک_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    برائے( pxIterator = &x_آغاز; pxIterator->px_اگلا_Free_بلاک < px_بلاک_مقصد_داخل_کرو; pxIterator = pxIterator->px_اگلا_Free_بلاک )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    اگر( ( puc + pxIterator->x_بلاک_سائز ) == ( uint8_t * ) px_بلاک_مقصد_داخل_کرو )
    {
        pxIterator->x_بلاک_سائز += px_بلاک_مقصد_داخل_کرو->x_بلاک_سائز;
        px_بلاک_مقصد_داخل_کرو = pxIterator;
    }
    ورنہ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_بلاک_مقصد_داخل_کرو;

    اگر( ( puc + px_بلاک_مقصد_داخل_کرو->x_بلاک_سائز ) == ( uint8_t * ) pxIterator->px_اگلا_Free_بلاک )
    {
        اگر( pxIterator->px_اگلا_Free_بلاک != px_انتہا )
        {
            /* Form one big block from the two blocks. */
            px_بلاک_مقصد_داخل_کرو->x_بلاک_سائز += pxIterator->px_اگلا_Free_بلاک->x_بلاک_سائز;
            px_بلاک_مقصد_داخل_کرو->px_اگلا_Free_بلاک = pxIterator->px_اگلا_Free_بلاک->px_اگلا_Free_بلاک;
        }
        ورنہ
        {
            px_بلاک_مقصد_داخل_کرو->px_اگلا_Free_بلاک = px_انتہا;
        }
    }
    ورنہ
    {
        px_بلاک_مقصد_داخل_کرو->px_اگلا_Free_بلاک = pxIterator->px_اگلا_Free_بلاک;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    اگر( pxIterator != px_بلاک_مقصد_داخل_کرو )
    {
        pxIterator->px_اگلا_Free_بلاک = px_بلاک_مقصد_داخل_کرو;
    }
    ورنہ
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

خالی * pv_پورٹ_Malloc( size_t x_Wanted_سائز )
{
    بلاک_Link_t * px_بلاک;
    بلاک_Link_t * px_پچھلا_بلاک;
    بلاک_Link_t * px_New_بلاک_Link;
    خالی * pvReturn = تہی;
    size_t x_Additional_Required_سائز;
    size_t x_Allocated_بلاک_سائز = 0;

    /* If this is the first call to malloc then the heap will require
     * initialisation to setup the list of free blocks. */
    اگر( px_انتہا == تہی )
    {
        prv_ڈھیر_Init();
    }
    ورنہ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    اگر( x_Wanted_سائز > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        اگر( secureheap_جوڑو_WILL_حد_سے_تجاوز( x_Wanted_سائز, x_ڈھیر_Struct_سائز ) == 0 )
        {
            x_Wanted_سائز += x_ڈھیر_Struct_سائز;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            اگر( ( x_Wanted_سائز & secureport_BYTE_ALIGNMENT_نقاب ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_سائز = secureportBYTE_ALIGNMENT - ( x_Wanted_سائز & secureport_BYTE_ALIGNMENT_نقاب );

                اگر( secureheap_جوڑو_WILL_حد_سے_تجاوز( x_Wanted_سائز, x_Additional_Required_سائز ) == 0 )
                {
                    x_Wanted_سائز += x_Additional_Required_سائز;
                }
                ورنہ
                {
                    x_Wanted_سائز = 0;
                }
            }
            ورنہ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ورنہ
        {
            x_Wanted_سائز = 0;
        }
    }
    ورنہ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Check the requested block size is not so large that the top bit is set.
     * The top bit of the block size member of the BlockLink_t structure is used
     * to determine who owns the block - the application or the kernel, so it
     * must be free. */
    اگر( secureheap_بلاک_سائز_IS_VALID( x_Wanted_سائز ) != 0 )
    {
        اگر( ( x_Wanted_سائز > 0 ) && ( x_Wanted_سائز <= x_Free_بائٹیں_بقایا ) )
        {
            /* Traverse the list from the start (lowest address) block until
             * one of adequate size is found. */
            px_پچھلا_بلاک = &x_آغاز;
            px_بلاک = x_آغاز.px_اگلا_Free_بلاک;

            جب( ( px_بلاک->x_بلاک_سائز < x_Wanted_سائز ) && ( px_بلاک->px_اگلا_Free_بلاک != تہی ) )
            {
                px_پچھلا_بلاک = px_بلاک;
                px_بلاک = px_بلاک->px_اگلا_Free_بلاک;
            }

            /* If the end marker was reached then a block of adequate size was
             * not found. */
            اگر( px_بلاک != px_انتہا )
            {
                /* Return the memory space pointed to - jumping over the
                 * BlockLink_t structure at its start. */
                pvReturn = ( خالی * ) ( ( ( uint8_t * ) px_پچھلا_بلاک->px_اگلا_Free_بلاک ) + x_ڈھیر_Struct_سائز );

                /* This block is being returned for use so must be taken out
                 * of the list of free blocks. */
                px_پچھلا_بلاک->px_اگلا_Free_بلاک = px_بلاک->px_اگلا_Free_بلاک;

                /* If the block is larger than required it can be split into
                 * two. */
                اگر( ( px_بلاک->x_بلاک_سائز - x_Wanted_سائز ) > secureheap_MINIMUM_بلاک_سائز )
                {
                    /* This block is to be split into two.  Create a new
                     * block following the number of bytes requested. The void
                     * cast is used to prevent byte alignment warnings from the
                     * compiler. */
                    px_New_بلاک_Link = ( خالی * ) ( ( ( uint8_t * ) px_بلاک ) + x_Wanted_سائز );
                    secureportASSERT( ( ( ( size_t ) px_New_بلاک_Link ) & secureport_BYTE_ALIGNMENT_نقاب ) == 0 );

                    /* Calculate the sizes of two blocks split from the single
                     * block. */
                    px_New_بلاک_Link->x_بلاک_سائز = px_بلاک->x_بلاک_سائز - x_Wanted_سائز;
                    px_بلاک->x_بلاک_سائز = x_Wanted_سائز;

                    /* Insert the new block into the list of free blocks. */
                    px_New_بلاک_Link->px_اگلا_Free_بلاک = px_پچھلا_بلاک->px_اگلا_Free_بلاک;
                    px_پچھلا_بلاک->px_اگلا_Free_بلاک = px_New_بلاک_Link;
                }
                ورنہ
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Free_بائٹیں_بقایا -= px_بلاک->x_بلاک_سائز;

                اگر( x_Free_بائٹیں_بقایا < x_Minimum_Ever_Free_بائٹیں_بقایا )
                {
                    x_Minimum_Ever_Free_بائٹیں_بقایا = x_Free_بائٹیں_بقایا;
                }
                ورنہ
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Allocated_بلاک_سائز = px_بلاک->x_بلاک_سائز;

                /* The block is being returned - it is allocated and owned by
                 * the application and has no "next" block. */
                secureheap_ALLOCATE_بلاک( px_بلاک );
                px_بلاک->px_اگلا_Free_بلاک = تہی;
            }
            ورنہ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ورنہ
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    ورنہ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    traceMALLOC( pvReturn, x_Allocated_بلاک_سائز );

    /* Prevent compiler warnings when trace macros are not used. */
    ( خالی ) x_Allocated_بلاک_سائز;

    #اگر ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 )
    {
        اگر( pvReturn == تہی )
        {
            خارجی خالی vApplicationMallocFailedHook( خالی );
            vApplicationMallocFailedHook();
        }
        ورنہ
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #اگر_ختم /* if ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 ) */

    secureportASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) secureport_BYTE_ALIGNMENT_نقاب ) == 0 );
    واپس pvReturn;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Free( خالی * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    بلاک_Link_t * pxLink;

    اگر( pv != تہی )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_ڈھیر_Struct_سائز;

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( خالی * ) puc;

        /* Check the block is actually allocated. */
        secureportASSERT( secureheap_بلاک_IS_ALLOCATED( pxLink ) != 0 );
        secureportASSERT( pxLink->px_اگلا_Free_بلاک == تہی );

        اگر( secureheap_بلاک_IS_ALLOCATED( pxLink ) != 0 )
        {
            اگر( pxLink->px_اگلا_Free_بلاک == تہی )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                secureheap_FREE_بلاک( pxLink );

                secureportDISABLE_NON_SECURE_INTERRUPTS();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_بائٹیں_بقایا += pxLink->x_بلاک_سائز;
                    traceFREE( pv, pxLink->x_بلاک_سائز );
                    prv_داخل_کرو_بلاک_Into_Free_List( ( ( بلاک_Link_t * ) pxLink ) );
                }
                secureportENABLE_NON_SECURE_INTERRUPTS();
            }
            ورنہ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ورنہ
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_پورٹ_Get_Free_ڈھیر_سائز( خالی )
{
    واپس x_Free_بائٹیں_بقایا;
}
/*-----------------------------------------------------------*/

size_t x_پورٹ_Get_Minimum_Ever_Free_ڈھیر_سائز( خالی )
{
    واپس x_Minimum_Ever_Free_بائٹیں_بقایا;
}
/*-----------------------------------------------------------*/
