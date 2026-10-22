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
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

/* Configuration includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOSConfig.h"

/* Secure context heap includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "secure_heap.h"

/* Secure port macros. */
#ਅਨ੍ਤਰ੍ਭਾਵ "secure_port_macros.h"

/**
 * @brief Total heap size.
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ secureconfig_ਕੁੱਲ_ਢੇਰ_ਮਾਪ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureconfig_ਕੁੱਲ_ਢੇਰ_ਮਾਪ    ( ( ( size_t ) ( 10 * 1024 ) ) )
#ਜੇ_ਅੰਤ

/* No test marker by default. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ mtCOVERAGE_TEST_MARKER
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ mtCOVERAGE_TEST_MARKER()
#ਜੇ_ਅੰਤ

/* No tracing by default. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ traceMALLOC
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ traceMALLOC( pvReturn, x_Wanted_ਮਾਪ )
#ਜੇ_ਅੰਤ

/* No tracing by default. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ traceFREE
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ traceFREE( pv, x_ਖੰਡ_ਮਾਪ )
#ਜੇ_ਅੰਤ

/* Block sizes must not get too small. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureheap_MINIMUM_ਖੰਡ_ਮਾਪ    ( ( size_t ) ( x_ਢੇਰ_Struct_ਮਾਪ << 1 ) )

/* Assumes 8bit bytes! */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureheap_ਬਿੱਟ_ਪ੍ਰਤੀ_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureheap_ਮਾਪ_MAX              ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureheap_ਜੋੜੋ_WILL_ਉਛਾਲ( a, b )    ( ( a ) > ( secureheap_ਮਾਪ_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureheap_ਖੰਡ_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( ਆਕਾਰ( size_t ) * secureheap_ਬਿੱਟ_ਪ੍ਰਤੀ_BYTE ) - 1 ) )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureheap_ਖੰਡ_ਮਾਪ_IS_VALID( x_ਖੰਡ_ਮਾਪ )    ( ( ( x_ਖੰਡ_ਮਾਪ ) & secureheap_ਖੰਡ_ALLOCATED_BITMASK ) == 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureheap_ਖੰਡ_IS_ALLOCATED( px_ਖੰਡ )        ( ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ ) & secureheap_ਖੰਡ_ALLOCATED_BITMASK ) != 0 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureheap_ALLOCATE_ਖੰਡ( px_ਖੰਡ )            ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ ) |= secureheap_ਖੰਡ_ALLOCATED_BITMASK )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ secureheap_FREE_ਖੰਡ( px_ਖੰਡ )                ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ ) &= ~secureheap_ਖੰਡ_ALLOCATED_BITMASK )
/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#ਜੇ ( config_APPLICATION_ALLOCATED_ਢੇਰ == 1 )

/* The application writer has already defined the array used for the RTOS
* heap - probably so it can be placed in a special segment or address. */
    ਬਾਹਰੀ uint8_t uc_ਢੇਰ[ secureconfig_ਕੁੱਲ_ਢੇਰ_ਮਾਪ ];
#ਨਹੀਂਤਾਂ /* configAPPLICATION_ALLOCATED_HEAP */
    ਸਥਿਰ uint8_t uc_ਢੇਰ[ secureconfig_ਕੁੱਲ_ਢੇਰ_ਮਾਪ ];
#ਜੇ_ਅੰਤ /* configAPPLICATION_ALLOCATED_HEAP */

/**
 * @brief The linked list structure.
 *
 * This is used to link free blocks in order of their memory address.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ A_ਖੰਡ_LINK
{
    ਬਣਤਰ A_ਖੰਡ_LINK * px_ਅਗਲਾ_Free_ਖੰਡ; /**< The next free block in the list. */
    size_t x_ਖੰਡ_ਮਾਪ;                     /**< The size of the free block. */
} ਖੰਡ_Link_t;
/*-----------------------------------------------------------*/

/**
 * @brief Called automatically to setup the required heap structures the first
 * time pvPortMalloc() is called.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਢੇਰ_Init( ਖਾਲੀ );

/**
 * @brief Inserts a block of memory that is being freed into the correct
 * position in the list of free memory blocks.
 *
 * The block being freed will be merged with the block in front it and/or the
 * block behind it if the memory blocks are adjacent to each other.
 *
 * @param[in] pxBlockToInsert The block being freed.
 */
ਸਥਿਰ ਖਾਲੀ prv_ਪਾਓ_ਖੰਡ_Into_Free_List( ਖੰਡ_Link_t * px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ );
/*-----------------------------------------------------------*/

/**
 * @brief The size of the structure placed at the beginning of each allocated
 * memory block must by correctly byte aligned.
 */
ਸਥਿਰ ਅਚਲ size_t x_ਢੇਰ_Struct_ਮਾਪ = ( ਆਕਾਰ( ਖੰਡ_Link_t ) + ( ( size_t ) ( secureportBYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) secureport_BYTE_ALIGNMENT_ਨਕਾਬ );

/**
 * @brief Create a couple of list links to mark the start and end of the list.
 */
ਸਥਿਰ ਖੰਡ_Link_t x_ਸ਼ੁਰੂ;
ਸਥਿਰ ਖੰਡ_Link_t * px_ਸਿਰਾ = ਨਿਰਾ;

/**
 * @brief Keeps track of the number of free bytes remaining, but says nothing
 * about fragmentation.
 */
ਸਥਿਰ size_t x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = 0U;
ਸਥਿਰ size_t x_Minimum_Ever_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = 0U;

/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਢੇਰ_Init( ਖਾਲੀ )
{
    ਖੰਡ_Link_t * px_ਪਹਿਲਾ_Free_ਖੰਡ;
    uint8_t * puc_Aligned_ਢੇਰ;
    size_t ux_ਪਤਾ;
    size_t x_ਕੁੱਲ_ਢੇਰ_ਮਾਪ = secureconfig_ਕੁੱਲ_ਢੇਰ_ਮਾਪ;

    /* Ensure the heap starts on a correctly aligned boundary. */
    ux_ਪਤਾ = ( size_t ) uc_ਢੇਰ;

    ਜੇ( ( ux_ਪਤਾ & secureport_BYTE_ALIGNMENT_ਨਕਾਬ ) != 0 )
    {
        ux_ਪਤਾ += ( secureportBYTE_ALIGNMENT - 1 );
        ux_ਪਤਾ &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_ਨਕਾਬ );
        x_ਕੁੱਲ_ਢੇਰ_ਮਾਪ -= ux_ਪਤਾ - ( size_t ) uc_ਢੇਰ;
    }

    puc_Aligned_ਢੇਰ = ( uint8_t * ) ux_ਪਤਾ;

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_ਸ਼ੁਰੂ.px_ਅਗਲਾ_Free_ਖੰਡ = ( ਖਾਲੀ * ) puc_Aligned_ਢੇਰ;
    x_ਸ਼ੁਰੂ.x_ਖੰਡ_ਮਾਪ = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    ux_ਪਤਾ = ( ( size_t ) puc_Aligned_ਢੇਰ ) + x_ਕੁੱਲ_ਢੇਰ_ਮਾਪ;
    ux_ਪਤਾ -= x_ਢੇਰ_Struct_ਮਾਪ;
    ux_ਪਤਾ &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_ਨਕਾਬ );
    px_ਸਿਰਾ = ( ਖਾਲੀ * ) ux_ਪਤਾ;
    px_ਸਿਰਾ->x_ਖੰਡ_ਮਾਪ = 0;
    px_ਸਿਰਾ->px_ਅਗਲਾ_Free_ਖੰਡ = ਨਿਰਾ;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    px_ਪਹਿਲਾ_Free_ਖੰਡ = ( ਖਾਲੀ * ) puc_Aligned_ਢੇਰ;
    px_ਪਹਿਲਾ_Free_ਖੰਡ->x_ਖੰਡ_ਮਾਪ = ux_ਪਤਾ - ( size_t ) px_ਪਹਿਲਾ_Free_ਖੰਡ;
    px_ਪਹਿਲਾ_Free_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ = px_ਸਿਰਾ;

    /* Only one block exists - and it covers the entire usable heap space. */
    x_Minimum_Ever_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = px_ਪਹਿਲਾ_Free_ਖੰਡ->x_ਖੰਡ_ਮਾਪ;
    x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = px_ਪਹਿਲਾ_Free_ਖੰਡ->x_ਖੰਡ_ਮਾਪ;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਪਾਓ_ਖੰਡ_Into_Free_List( ਖੰਡ_Link_t * px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ )
{
    ਖੰਡ_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    ਲਈ( pxIterator = &x_ਸ਼ੁਰੂ; pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ < px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ; pxIterator = pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    ਜੇ( ( puc + pxIterator->x_ਖੰਡ_ਮਾਪ ) == ( uint8_t * ) px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ )
    {
        pxIterator->x_ਖੰਡ_ਮਾਪ += px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ->x_ਖੰਡ_ਮਾਪ;
        px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ = pxIterator;
    }
    ਨਹੀਂਤਾਂ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ;

    ਜੇ( ( puc + px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ->x_ਖੰਡ_ਮਾਪ ) == ( uint8_t * ) pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ )
    {
        ਜੇ( pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ != px_ਸਿਰਾ )
        {
            /* Form one big block from the two blocks. */
            px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ->x_ਖੰਡ_ਮਾਪ += pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ->x_ਖੰਡ_ਮਾਪ;
            px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ->px_ਅਗਲਾ_Free_ਖੰਡ = pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ;
        }
        ਨਹੀਂਤਾਂ
        {
            px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ->px_ਅਗਲਾ_Free_ਖੰਡ = px_ਸਿਰਾ;
        }
    }
    ਨਹੀਂਤਾਂ
    {
        px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ->px_ਅਗਲਾ_Free_ਖੰਡ = pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    ਜੇ( pxIterator != px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ )
    {
        pxIterator->px_ਅਗਲਾ_Free_ਖੰਡ = px_ਖੰਡ_ਮੰਜ਼ਿਲ_ਪਾਓ;
    }
    ਨਹੀਂਤਾਂ
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ * pv_ਪੋਰਟ_Malloc( size_t x_Wanted_ਮਾਪ )
{
    ਖੰਡ_Link_t * px_ਖੰਡ;
    ਖੰਡ_Link_t * px_ਪਿਛਲਾ_ਖੰਡ;
    ਖੰਡ_Link_t * px_New_ਖੰਡ_Link;
    ਖਾਲੀ * pvReturn = ਨਿਰਾ;
    size_t x_Additional_Required_ਮਾਪ;
    size_t x_Allocated_ਖੰਡ_ਮਾਪ = 0;

    /* If this is the first call to malloc then the heap will require
     * initialisation to setup the list of free blocks. */
    ਜੇ( px_ਸਿਰਾ == ਨਿਰਾ )
    {
        prv_ਢੇਰ_Init();
    }
    ਨਹੀਂਤਾਂ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    ਜੇ( x_Wanted_ਮਾਪ > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        ਜੇ( secureheap_ਜੋੜੋ_WILL_ਉਛਾਲ( x_Wanted_ਮਾਪ, x_ਢੇਰ_Struct_ਮਾਪ ) == 0 )
        {
            x_Wanted_ਮਾਪ += x_ਢੇਰ_Struct_ਮਾਪ;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            ਜੇ( ( x_Wanted_ਮਾਪ & secureport_BYTE_ALIGNMENT_ਨਕਾਬ ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_ਮਾਪ = secureportBYTE_ALIGNMENT - ( x_Wanted_ਮਾਪ & secureport_BYTE_ALIGNMENT_ਨਕਾਬ );

                ਜੇ( secureheap_ਜੋੜੋ_WILL_ਉਛਾਲ( x_Wanted_ਮਾਪ, x_Additional_Required_ਮਾਪ ) == 0 )
                {
                    x_Wanted_ਮਾਪ += x_Additional_Required_ਮਾਪ;
                }
                ਨਹੀਂਤਾਂ
                {
                    x_Wanted_ਮਾਪ = 0;
                }
            }
            ਨਹੀਂਤਾਂ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ਨਹੀਂਤਾਂ
        {
            x_Wanted_ਮਾਪ = 0;
        }
    }
    ਨਹੀਂਤਾਂ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Check the requested block size is not so large that the top bit is set.
     * The top bit of the block size member of the BlockLink_t structure is used
     * to determine who owns the block - the application or the kernel, so it
     * must be free. */
    ਜੇ( secureheap_ਖੰਡ_ਮਾਪ_IS_VALID( x_Wanted_ਮਾਪ ) != 0 )
    {
        ਜੇ( ( x_Wanted_ਮਾਪ > 0 ) && ( x_Wanted_ਮਾਪ <= x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ ) )
        {
            /* Traverse the list from the start (lowest address) block until
             * one of adequate size is found. */
            px_ਪਿਛਲਾ_ਖੰਡ = &x_ਸ਼ੁਰੂ;
            px_ਖੰਡ = x_ਸ਼ੁਰੂ.px_ਅਗਲਾ_Free_ਖੰਡ;

            ਜਦੋਂ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ < x_Wanted_ਮਾਪ ) && ( px_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ != ਨਿਰਾ ) )
            {
                px_ਪਿਛਲਾ_ਖੰਡ = px_ਖੰਡ;
                px_ਖੰਡ = px_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ;
            }

            /* If the end marker was reached then a block of adequate size was
             * not found. */
            ਜੇ( px_ਖੰਡ != px_ਸਿਰਾ )
            {
                /* Return the memory space pointed to - jumping over the
                 * BlockLink_t structure at its start. */
                pvReturn = ( ਖਾਲੀ * ) ( ( ( uint8_t * ) px_ਪਿਛਲਾ_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ ) + x_ਢੇਰ_Struct_ਮਾਪ );

                /* This block is being returned for use so must be taken out
                 * of the list of free blocks. */
                px_ਪਿਛਲਾ_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ = px_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ;

                /* If the block is larger than required it can be split into
                 * two. */
                ਜੇ( ( px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ - x_Wanted_ਮਾਪ ) > secureheap_MINIMUM_ਖੰਡ_ਮਾਪ )
                {
                    /* This block is to be split into two.  Create a new
                     * block following the number of bytes requested. The void
                     * cast is used to prevent byte alignment warnings from the
                     * compiler. */
                    px_New_ਖੰਡ_Link = ( ਖਾਲੀ * ) ( ( ( uint8_t * ) px_ਖੰਡ ) + x_Wanted_ਮਾਪ );
                    secureportASSERT( ( ( ( size_t ) px_New_ਖੰਡ_Link ) & secureport_BYTE_ALIGNMENT_ਨਕਾਬ ) == 0 );

                    /* Calculate the sizes of two blocks split from the single
                     * block. */
                    px_New_ਖੰਡ_Link->x_ਖੰਡ_ਮਾਪ = px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ - x_Wanted_ਮਾਪ;
                    px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ = x_Wanted_ਮਾਪ;

                    /* Insert the new block into the list of free blocks. */
                    px_New_ਖੰਡ_Link->px_ਅਗਲਾ_Free_ਖੰਡ = px_ਪਿਛਲਾ_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ;
                    px_ਪਿਛਲਾ_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ = px_New_ਖੰਡ_Link;
                }
                ਨਹੀਂਤਾਂ
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ -= px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ;

                ਜੇ( x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ < x_Minimum_Ever_Free_ਬਾਈਟਾਂ_ਬਚਿਆ )
                {
                    x_Minimum_Ever_Free_ਬਾਈਟਾਂ_ਬਚਿਆ = x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ;
                }
                ਨਹੀਂਤਾਂ
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Allocated_ਖੰਡ_ਮਾਪ = px_ਖੰਡ->x_ਖੰਡ_ਮਾਪ;

                /* The block is being returned - it is allocated and owned by
                 * the application and has no "next" block. */
                secureheap_ALLOCATE_ਖੰਡ( px_ਖੰਡ );
                px_ਖੰਡ->px_ਅਗਲਾ_Free_ਖੰਡ = ਨਿਰਾ;
            }
            ਨਹੀਂਤਾਂ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ਨਹੀਂਤਾਂ
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    ਨਹੀਂਤਾਂ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    traceMALLOC( pvReturn, x_Allocated_ਖੰਡ_ਮਾਪ );

    /* Prevent compiler warnings when trace macros are not used. */
    ( ਖਾਲੀ ) x_Allocated_ਖੰਡ_ਮਾਪ;

    #ਜੇ ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 )
    {
        ਜੇ( pvReturn == ਨਿਰਾ )
        {
            ਬਾਹਰੀ ਖਾਲੀ vApplicationMallocFailedHook( ਖਾਲੀ );
            vApplicationMallocFailedHook();
        }
        ਨਹੀਂਤਾਂ
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #ਜੇ_ਅੰਤ /* if ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 ) */

    secureportASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) secureport_BYTE_ALIGNMENT_ਨਕਾਬ ) == 0 );
    ਵਾਪਸ pvReturn;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Free( ਖਾਲੀ * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    ਖੰਡ_Link_t * pxLink;

    ਜੇ( pv != ਨਿਰਾ )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_ਢੇਰ_Struct_ਮਾਪ;

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( ਖਾਲੀ * ) puc;

        /* Check the block is actually allocated. */
        secureportASSERT( secureheap_ਖੰਡ_IS_ALLOCATED( pxLink ) != 0 );
        secureportASSERT( pxLink->px_ਅਗਲਾ_Free_ਖੰਡ == ਨਿਰਾ );

        ਜੇ( secureheap_ਖੰਡ_IS_ALLOCATED( pxLink ) != 0 )
        {
            ਜੇ( pxLink->px_ਅਗਲਾ_Free_ਖੰਡ == ਨਿਰਾ )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                secureheap_FREE_ਖੰਡ( pxLink );

                secureportDISABLE_NON_SECURE_INTERRUPTS();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ += pxLink->x_ਖੰਡ_ਮਾਪ;
                    traceFREE( pv, pxLink->x_ਖੰਡ_ਮਾਪ );
                    prv_ਪਾਓ_ਖੰਡ_Into_Free_List( ( ( ਖੰਡ_Link_t * ) pxLink ) );
                }
                secureportENABLE_NON_SECURE_INTERRUPTS();
            }
            ਨਹੀਂਤਾਂ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ਨਹੀਂਤਾਂ
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_ਪੋਰਟ_Get_Free_ਢੇਰ_ਮਾਪ( ਖਾਲੀ )
{
    ਵਾਪਸ x_Free_ਬਾਈਟਾਂ_ਬਚਿਆ;
}
/*-----------------------------------------------------------*/

size_t x_ਪੋਰਟ_Get_Minimum_Ever_Free_ਢੇਰ_ਮਾਪ( ਖਾਲੀ )
{
    ਵਾਪਸ x_Minimum_Ever_Free_ਬਾਈਟਾਂ_ਬਚਿਆ;
}
/*-----------------------------------------------------------*/
