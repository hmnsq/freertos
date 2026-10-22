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
#ಅನ್ತರ್ಭಾವ <stdint.h>

/* Configuration includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOSConfig.h"

/* Secure context heap includes. */
#ಅನ್ತರ್ಭಾವ "secure_heap.h"

/* Secure port macros. */
#ಅನ್ತರ್ಭಾವ "secure_port_macros.h"

/**
 * @brief Total heap size.
 */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ secureconfig_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ
    #ವ್ಯಾಖ್ಯಾನಿಸು secureconfig_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ    ( ( ( size_t ) ( 10 * 1024 ) ) )
#ಆದರೆ_ಅಂತ್ಯ

/* No test marker by default. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ mtCOVERAGE_TEST_MARKER
    #ವ್ಯಾಖ್ಯಾನಿಸು mtCOVERAGE_TEST_MARKER()
#ಆದರೆ_ಅಂತ್ಯ

/* No tracing by default. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ traceMALLOC
    #ವ್ಯಾಖ್ಯಾನಿಸು traceMALLOC( pvReturn, x_Wanted_ಗಾತ್ರ )
#ಆದರೆ_ಅಂತ್ಯ

/* No tracing by default. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ traceFREE
    #ವ್ಯಾಖ್ಯಾನಿಸು traceFREE( pv, x_ಖಂಡ_ಗಾತ್ರ )
#ಆದರೆ_ಅಂತ್ಯ

/* Block sizes must not get too small. */
#ವ್ಯಾಖ್ಯಾನಿಸು secureheap_MINIMUM_ಖಂಡ_ಗಾತ್ರ    ( ( size_t ) ( x_ರಾಶಿ_Struct_ಗಾತ್ರ << 1 ) )

/* Assumes 8bit bytes! */
#ವ್ಯಾಖ್ಯಾನಿಸು secureheap_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#ವ್ಯಾಖ್ಯಾನಿಸು secureheap_ಗಾತ್ರ_MAX              ( ~( ( size_t ) 0 ) )

/* Check if adding a and b will result in overflow. */
#ವ್ಯಾಖ್ಯಾನಿಸು secureheap_ಕೂಡಿಸು_WILL_ಅತಿಪ್ರವಾಹ( a, b )    ( ( a ) > ( secureheap_ಗಾತ್ರ_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#ವ್ಯಾಖ್ಯಾನಿಸು secureheap_ಖಂಡ_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( ಗಾತ್ರ( size_t ) * secureheap_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_BYTE ) - 1 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು secureheap_ಖಂಡ_ಗಾತ್ರ_IS_VALID( x_ಖಂಡ_ಗಾತ್ರ )    ( ( ( x_ಖಂಡ_ಗಾತ್ರ ) & secureheap_ಖಂಡ_ALLOCATED_BITMASK ) == 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು secureheap_ಖಂಡ_IS_ALLOCATED( px_ಖಂಡ )        ( ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ ) & secureheap_ಖಂಡ_ALLOCATED_BITMASK ) != 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು secureheap_ALLOCATE_ಖಂಡ( px_ಖಂಡ )            ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ ) |= secureheap_ಖಂಡ_ALLOCATED_BITMASK )
#ವ್ಯಾಖ್ಯಾನಿಸು secureheap_FREE_ಖಂಡ( px_ಖಂಡ )                ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ ) &= ~secureheap_ಖಂಡ_ALLOCATED_BITMASK )
/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#ಆದರೆ ( config_APPLICATION_ALLOCATED_ರಾಶಿ == 1 )

/* The application writer has already defined the array used for the RTOS
* heap - probably so it can be placed in a special segment or address. */
    ಬಾಹ್ಯ uint8_t uc_ರಾಶಿ[ secureconfig_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ ];
#ಇಲ್ಲದಿದ್ದರೆ /* configAPPLICATION_ALLOCATED_HEAP */
    ಸ್ಥಿರ uint8_t uc_ರಾಶಿ[ secureconfig_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ ];
#ಆದರೆ_ಅಂತ್ಯ /* configAPPLICATION_ALLOCATED_HEAP */

/**
 * @brief The linked list structure.
 *
 * This is used to link free blocks in order of their memory address.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ A_ಖಂಡ_LINK
{
    ರಚನೆ A_ಖಂಡ_LINK * px_ಮುಂದಿನ_Free_ಖಂಡ; /**< The next free block in the list. */
    size_t x_ಖಂಡ_ಗಾತ್ರ;                     /**< The size of the free block. */
} ಖಂಡ_Link_t;
/*-----------------------------------------------------------*/

/**
 * @brief Called automatically to setup the required heap structures the first
 * time pvPortMalloc() is called.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ರಾಶಿ_Init( ಶೂನ್ಯ );

/**
 * @brief Inserts a block of memory that is being freed into the correct
 * position in the list of free memory blocks.
 *
 * The block being freed will be merged with the block in front it and/or the
 * block behind it if the memory blocks are adjacent to each other.
 *
 * @param[in] pxBlockToInsert The block being freed.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸೇರಿಸು_ಖಂಡ_Into_Free_List( ಖಂಡ_Link_t * px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು );
/*-----------------------------------------------------------*/

/**
 * @brief The size of the structure placed at the beginning of each allocated
 * memory block must by correctly byte aligned.
 */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ size_t x_ರಾಶಿ_Struct_ಗಾತ್ರ = ( ಗಾತ್ರ( ಖಂಡ_Link_t ) + ( ( size_t ) ( secureportBYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) secureport_BYTE_ALIGNMENT_ಮುಖವಾಡ );

/**
 * @brief Create a couple of list links to mark the start and end of the list.
 */
ಸ್ಥಿರ ಖಂಡ_Link_t x_ಆರಂಭ;
ಸ್ಥಿರ ಖಂಡ_Link_t * px_ಕೊನೆ = ಖಾಲಿ;

/**
 * @brief Keeps track of the number of free bytes remaining, but says nothing
 * about fragmentation.
 */
ಸ್ಥಿರ size_t x_Free_ಬೈಟುಗಳು_ಉಳಿದ = 0U;
ಸ್ಥಿರ size_t x_Minimum_Ever_Free_ಬೈಟುಗಳು_ಉಳಿದ = 0U;

/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ರಾಶಿ_Init( ಶೂನ್ಯ )
{
    ಖಂಡ_Link_t * px_ಮೊದಲ_Free_ಖಂಡ;
    uint8_t * puc_Aligned_ರಾಶಿ;
    size_t ux_ವಿಳಾಸ;
    size_t x_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ = secureconfig_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ;

    /* Ensure the heap starts on a correctly aligned boundary. */
    ux_ವಿಳಾಸ = ( size_t ) uc_ರಾಶಿ;

    ಆದರೆ( ( ux_ವಿಳಾಸ & secureport_BYTE_ALIGNMENT_ಮುಖವಾಡ ) != 0 )
    {
        ux_ವಿಳಾಸ += ( secureportBYTE_ALIGNMENT - 1 );
        ux_ವಿಳಾಸ &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_ಮುಖವಾಡ );
        x_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ -= ux_ವಿಳಾಸ - ( size_t ) uc_ರಾಶಿ;
    }

    puc_Aligned_ರಾಶಿ = ( uint8_t * ) ux_ವಿಳಾಸ;

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_ಆರಂಭ.px_ಮುಂದಿನ_Free_ಖಂಡ = ( ಶೂನ್ಯ * ) puc_Aligned_ರಾಶಿ;
    x_ಆರಂಭ.x_ಖಂಡ_ಗಾತ್ರ = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    ux_ವಿಳಾಸ = ( ( size_t ) puc_Aligned_ರಾಶಿ ) + x_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ;
    ux_ವಿಳಾಸ -= x_ರಾಶಿ_Struct_ಗಾತ್ರ;
    ux_ವಿಳಾಸ &= ~( ( size_t ) secureport_BYTE_ALIGNMENT_ಮುಖವಾಡ );
    px_ಕೊನೆ = ( ಶೂನ್ಯ * ) ux_ವಿಳಾಸ;
    px_ಕೊನೆ->x_ಖಂಡ_ಗಾತ್ರ = 0;
    px_ಕೊನೆ->px_ಮುಂದಿನ_Free_ಖಂಡ = ಖಾಲಿ;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    px_ಮೊದಲ_Free_ಖಂಡ = ( ಶೂನ್ಯ * ) puc_Aligned_ರಾಶಿ;
    px_ಮೊದಲ_Free_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ = ux_ವಿಳಾಸ - ( size_t ) px_ಮೊದಲ_Free_ಖಂಡ;
    px_ಮೊದಲ_Free_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ = px_ಕೊನೆ;

    /* Only one block exists - and it covers the entire usable heap space. */
    x_Minimum_Ever_Free_ಬೈಟುಗಳು_ಉಳಿದ = px_ಮೊದಲ_Free_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ;
    x_Free_ಬೈಟುಗಳು_ಉಳಿದ = px_ಮೊದಲ_Free_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸೇರಿಸು_ಖಂಡ_Into_Free_List( ಖಂಡ_Link_t * px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು )
{
    ಖಂಡ_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    ಗಾಗಿ( pxIterator = &x_ಆರಂಭ; pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ < px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು; pxIterator = pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    ಆದರೆ( ( puc + pxIterator->x_ಖಂಡ_ಗಾತ್ರ ) == ( uint8_t * ) px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು )
    {
        pxIterator->x_ಖಂಡ_ಗಾತ್ರ += px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು->x_ಖಂಡ_ಗಾತ್ರ;
        px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು = pxIterator;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು;

    ಆದರೆ( ( puc + px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು->x_ಖಂಡ_ಗಾತ್ರ ) == ( uint8_t * ) pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ )
    {
        ಆದರೆ( pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ != px_ಕೊನೆ )
        {
            /* Form one big block from the two blocks. */
            px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು->x_ಖಂಡ_ಗಾತ್ರ += pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ;
            px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು->px_ಮುಂದಿನ_Free_ಖಂಡ = pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು->px_ಮುಂದಿನ_Free_ಖಂಡ = px_ಕೊನೆ;
        }
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು->px_ಮುಂದಿನ_Free_ಖಂಡ = pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    ಆದರೆ( pxIterator != px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು )
    {
        pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ = px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ * pv_ಪೋರ್ಟ್_Malloc( size_t x_Wanted_ಗಾತ್ರ )
{
    ಖಂಡ_Link_t * px_ಖಂಡ;
    ಖಂಡ_Link_t * px_ಹಿಂದಿನ_ಖಂಡ;
    ಖಂಡ_Link_t * px_New_ಖಂಡ_Link;
    ಶೂನ್ಯ * pvReturn = ಖಾಲಿ;
    size_t x_Additional_Required_ಗಾತ್ರ;
    size_t x_Allocated_ಖಂಡ_ಗಾತ್ರ = 0;

    /* If this is the first call to malloc then the heap will require
     * initialisation to setup the list of free blocks. */
    ಆದರೆ( px_ಕೊನೆ == ಖಾಲಿ )
    {
        prv_ರಾಶಿ_Init();
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    ಆದರೆ( x_Wanted_ಗಾತ್ರ > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        ಆದರೆ( secureheap_ಕೂಡಿಸು_WILL_ಅತಿಪ್ರವಾಹ( x_Wanted_ಗಾತ್ರ, x_ರಾಶಿ_Struct_ಗಾತ್ರ ) == 0 )
        {
            x_Wanted_ಗಾತ್ರ += x_ರಾಶಿ_Struct_ಗಾತ್ರ;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            ಆದರೆ( ( x_Wanted_ಗಾತ್ರ & secureport_BYTE_ALIGNMENT_ಮುಖವಾಡ ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_ಗಾತ್ರ = secureportBYTE_ALIGNMENT - ( x_Wanted_ಗಾತ್ರ & secureport_BYTE_ALIGNMENT_ಮುಖವಾಡ );

                ಆದರೆ( secureheap_ಕೂಡಿಸು_WILL_ಅತಿಪ್ರವಾಹ( x_Wanted_ಗಾತ್ರ, x_Additional_Required_ಗಾತ್ರ ) == 0 )
                {
                    x_Wanted_ಗಾತ್ರ += x_Additional_Required_ಗಾತ್ರ;
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    x_Wanted_ಗಾತ್ರ = 0;
                }
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            x_Wanted_ಗಾತ್ರ = 0;
        }
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Check the requested block size is not so large that the top bit is set.
     * The top bit of the block size member of the BlockLink_t structure is used
     * to determine who owns the block - the application or the kernel, so it
     * must be free. */
    ಆದರೆ( secureheap_ಖಂಡ_ಗಾತ್ರ_IS_VALID( x_Wanted_ಗಾತ್ರ ) != 0 )
    {
        ಆದರೆ( ( x_Wanted_ಗಾತ್ರ > 0 ) && ( x_Wanted_ಗಾತ್ರ <= x_Free_ಬೈಟುಗಳು_ಉಳಿದ ) )
        {
            /* Traverse the list from the start (lowest address) block until
             * one of adequate size is found. */
            px_ಹಿಂದಿನ_ಖಂಡ = &x_ಆರಂಭ;
            px_ಖಂಡ = x_ಆರಂಭ.px_ಮುಂದಿನ_Free_ಖಂಡ;

            ಆಗ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ < x_Wanted_ಗಾತ್ರ ) && ( px_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ != ಖಾಲಿ ) )
            {
                px_ಹಿಂದಿನ_ಖಂಡ = px_ಖಂಡ;
                px_ಖಂಡ = px_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ;
            }

            /* If the end marker was reached then a block of adequate size was
             * not found. */
            ಆದರೆ( px_ಖಂಡ != px_ಕೊನೆ )
            {
                /* Return the memory space pointed to - jumping over the
                 * BlockLink_t structure at its start. */
                pvReturn = ( ಶೂನ್ಯ * ) ( ( ( uint8_t * ) px_ಹಿಂದಿನ_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ ) + x_ರಾಶಿ_Struct_ಗಾತ್ರ );

                /* This block is being returned for use so must be taken out
                 * of the list of free blocks. */
                px_ಹಿಂದಿನ_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ = px_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ;

                /* If the block is larger than required it can be split into
                 * two. */
                ಆದರೆ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ - x_Wanted_ಗಾತ್ರ ) > secureheap_MINIMUM_ಖಂಡ_ಗಾತ್ರ )
                {
                    /* This block is to be split into two.  Create a new
                     * block following the number of bytes requested. The void
                     * cast is used to prevent byte alignment warnings from the
                     * compiler. */
                    px_New_ಖಂಡ_Link = ( ಶೂನ್ಯ * ) ( ( ( uint8_t * ) px_ಖಂಡ ) + x_Wanted_ಗಾತ್ರ );
                    secureportASSERT( ( ( ( size_t ) px_New_ಖಂಡ_Link ) & secureport_BYTE_ALIGNMENT_ಮುಖವಾಡ ) == 0 );

                    /* Calculate the sizes of two blocks split from the single
                     * block. */
                    px_New_ಖಂಡ_Link->x_ಖಂಡ_ಗಾತ್ರ = px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ - x_Wanted_ಗಾತ್ರ;
                    px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ = x_Wanted_ಗಾತ್ರ;

                    /* Insert the new block into the list of free blocks. */
                    px_New_ಖಂಡ_Link->px_ಮುಂದಿನ_Free_ಖಂಡ = px_ಹಿಂದಿನ_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ;
                    px_ಹಿಂದಿನ_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ = px_New_ಖಂಡ_Link;
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Free_ಬೈಟುಗಳು_ಉಳಿದ -= px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ;

                ಆದರೆ( x_Free_ಬೈಟುಗಳು_ಉಳಿದ < x_Minimum_Ever_Free_ಬೈಟುಗಳು_ಉಳಿದ )
                {
                    x_Minimum_Ever_Free_ಬೈಟುಗಳು_ಉಳಿದ = x_Free_ಬೈಟುಗಳು_ಉಳಿದ;
                }
                ಇಲ್ಲದಿದ್ದರೆ
                {
                    mtCOVERAGE_TEST_MARKER();
                }

                x_Allocated_ಖಂಡ_ಗಾತ್ರ = px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ;

                /* The block is being returned - it is allocated and owned by
                 * the application and has no "next" block. */
                secureheap_ALLOCATE_ಖಂಡ( px_ಖಂಡ );
                px_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ = ಖಾಲಿ;
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    traceMALLOC( pvReturn, x_Allocated_ಖಂಡ_ಗಾತ್ರ );

    /* Prevent compiler warnings when trace macros are not used. */
    ( ಶೂನ್ಯ ) x_Allocated_ಖಂಡ_ಗಾತ್ರ;

    #ಆದರೆ ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 )
    {
        ಆದರೆ( pvReturn == ಖಾಲಿ )
        {
            ಬಾಹ್ಯ ಶೂನ್ಯ vApplicationMallocFailedHook( ಶೂನ್ಯ );
            vApplicationMallocFailedHook();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( secureconfigUSE_MALLOC_FAILED_HOOK == 1 ) */

    secureportASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) secureport_BYTE_ALIGNMENT_ಮುಖವಾಡ ) == 0 );
    ಹಿಂತಿರುಗಿ pvReturn;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Free( ಶೂನ್ಯ * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    ಖಂಡ_Link_t * pxLink;

    ಆದರೆ( pv != ಖಾಲಿ )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_ರಾಶಿ_Struct_ಗಾತ್ರ;

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( ಶೂನ್ಯ * ) puc;

        /* Check the block is actually allocated. */
        secureportASSERT( secureheap_ಖಂಡ_IS_ALLOCATED( pxLink ) != 0 );
        secureportASSERT( pxLink->px_ಮುಂದಿನ_Free_ಖಂಡ == ಖಾಲಿ );

        ಆದರೆ( secureheap_ಖಂಡ_IS_ALLOCATED( pxLink ) != 0 )
        {
            ಆದರೆ( pxLink->px_ಮುಂದಿನ_Free_ಖಂಡ == ಖಾಲಿ )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                secureheap_FREE_ಖಂಡ( pxLink );

                secureportDISABLE_NON_SECURE_INTERRUPTS();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_ಬೈಟುಗಳು_ಉಳಿದ += pxLink->x_ಖಂಡ_ಗಾತ್ರ;
                    traceFREE( pv, pxLink->x_ಖಂಡ_ಗಾತ್ರ );
                    prv_ಸೇರಿಸು_ಖಂಡ_Into_Free_List( ( ( ಖಂಡ_Link_t * ) pxLink ) );
                }
                secureportENABLE_NON_SECURE_INTERRUPTS();
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_ಪೋರ್ಟ್_Get_Free_ರಾಶಿ_ಗಾತ್ರ( ಶೂನ್ಯ )
{
    ಹಿಂತಿರುಗಿ x_Free_ಬೈಟುಗಳು_ಉಳಿದ;
}
/*-----------------------------------------------------------*/

size_t x_ಪೋರ್ಟ್_Get_Minimum_Ever_Free_ರಾಶಿ_ಗಾತ್ರ( ಶೂನ್ಯ )
{
    ಹಿಂತಿರುಗಿ x_Minimum_Ever_Free_ಬೈಟುಗಳು_ಉಳಿದ;
}
/*-----------------------------------------------------------*/
