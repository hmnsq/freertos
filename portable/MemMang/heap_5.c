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
 * A sample implementation of pvPortMalloc() that allows the heap to be defined
 * across multiple non-contiguous blocks and combines (coalescences) adjacent
 * memory blocks as they are freed.
 *
 * See heap_1.c, heap_2.c, heap_3.c and heap_4.c for alternative
 * implementations, and the memory management pages of https://www.FreeRTOS.org
 * for more information.
 *
 * Usage notes:
 *
 * vPortDefineHeapRegions() ***must*** be called before pvPortMalloc().
 * pvPortMalloc() will be called if any task objects (tasks, queues, event
 * groups, etc.) are created, therefore vPortDefineHeapRegions() ***must*** be
 * called before any other objects are defined.
 *
 * vPortDefineHeapRegions() takes a single parameter.  The parameter is an array
 * of HeapRegion_t structures.  HeapRegion_t is defined in portable.h as
 *
 * typedef struct HeapRegion
 * {
 *  uint8_t *pucStartAddress; << Start address of a block of memory that will be part of the heap.
 *  size_t xSizeInBytes;      << Size of the block of memory.
 * } HeapRegion_t;
 *
 * The array is terminated using a NULL zero sized region definition, and the
 * memory regions defined in the array ***must*** appear in address order from
 * low address to high address.  So the following is a valid example of how
 * to use the function.
 *
 * HeapRegion_t xHeapRegions[] =
 * {
 *  { ( uint8_t * ) 0x80000000UL, 0x10000 }, << Defines a block of 0x10000 bytes starting at address 0x80000000
 *  { ( uint8_t * ) 0x90000000UL, 0xa0000 }, << Defines a block of 0xa0000 bytes starting at address of 0x90000000
 *  { NULL, 0 }                << Terminates the array.
 * };
 *
 * vPortDefineHeapRegions( xHeapRegions ); << Pass the array into vPortDefineHeapRegions().
 *
 * Note 0x80000000 is the lower address so appears in the array first.
 *
 */
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#ವ್ಯಾಖ್ಯಾನಿಸು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ಆದರೆ ( config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ == 0 )
    #ದೋಷ This file must not be ಬಳಸಿದ ಆದರೆ config_SUPPORT_DYNAMIC_ಹಂಚಿಕೆ is 0
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ರಾಶಿ_CLEAR_ಸ್ಮರಣೆ_ON_FREE
    #ವ್ಯಾಖ್ಯಾನಿಸು config_ರಾಶಿ_CLEAR_ಸ್ಮರಣೆ_ON_FREE    0
#ಆದರೆ_ಅಂತ್ಯ

/* Block sizes must not get too small. */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_MINIMUM_ಖಂಡ_ಗಾತ್ರ    ( ( size_t ) ( x_ರಾಶಿ_Struct_ಗಾತ್ರ << 1 ) )

/* Assumes 8bit bytes! */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಗಾತ್ರ_MAX              ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_MULTIPLY_WILL_ಅತಿಪ್ರವಾಹ( a, b )     ( ( ( a ) > 0 ) && ( ( b ) > ( ರಾಶಿ_ಗಾತ್ರ_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಕೂಡಿಸು_WILL_ಅತಿಪ್ರವಾಹ( a, b )          ( ( a ) > ( ರಾಶಿ_ಗಾತ್ರ_MAX - ( b ) ) )

/* Check if the subtraction operation ( a - b ) will result in underflow. */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಕಳೆ_WILL_UNDERFLOW( a, b )    ( ( a ) < ( b ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಖಂಡ_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( ಗಾತ್ರ( size_t ) * ರಾಶಿ_ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_BYTE ) - 1 ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಖಂಡ_ಗಾತ್ರ_IS_VALID( x_ಖಂಡ_ಗಾತ್ರ )    ( ( ( x_ಖಂಡ_ಗಾತ್ರ ) & ರಾಶಿ_ಖಂಡ_ALLOCATED_BITMASK ) == 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ಖಂಡ_IS_ALLOCATED( px_ಖಂಡ )        ( ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ ) & ರಾಶಿ_ಖಂಡ_ALLOCATED_BITMASK ) != 0 )
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_ALLOCATE_ಖಂಡ( px_ಖಂಡ )            ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ ) |= ರಾಶಿ_ಖಂಡ_ALLOCATED_BITMASK )
#ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_FREE_ಖಂಡ( px_ಖಂಡ )                ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ ) &= ~ರಾಶಿ_ಖಂಡ_ALLOCATED_BITMASK )

/* Setting configENABLE_HEAP_PROTECTOR to 1 enables heap block pointers
 * protection using an application supplied canary value to catch heap
 * corruption should a heap buffer overflow occur.
 */
#ಆದರೆ ( config_ENABLE_ರಾಶಿ_PROTECTOR == 1 )

/* Macro to load/store BlockLink_t pointers to memory. By XORing the
 * pointers with a random canary value, heap overflows will result
 * in randomly unpredictable pointer values which will be caught by
 * heapVALIDATE_BLOCK_POINTER assert. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( px_ಖಂಡ )    ( ( ಖಂಡ_Link_t * ) ( ( ( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE ) ( px_ಖಂಡ ) ) ^ x_ರಾಶಿ_Canary ) )

/* Assert that a heap block pointer is within the heap bounds.
 * Setting configVALIDATE_HEAP_BLOCK_POINTER to 1 enables customized heap block pointers
 * protection on heap_5. */
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_VALIDATE_ರಾಶಿ_ಖಂಡ_ಸೂಚಕ
        #ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_VALIDATE_ಖಂಡ_ಸೂಚಕ( px_ಖಂಡ )                           \
            configASSERT( ( puc_ರಾಶಿ_ಮೇಲಿನ_ವಿಳಾಸ != ಖಾಲಿ ) &&                     \
                          ( puc_ರಾಶಿ_ಕೆಳಗಿನ_ವಿಳಾಸ != ಖಾಲಿ ) &&                      \
                          ( ( uint8_t * ) ( px_ಖಂಡ ) >= puc_ರಾಶಿ_ಕೆಳಗಿನ_ವಿಳಾಸ ) && \
                          ( ( uint8_t * ) ( px_ಖಂಡ ) < puc_ರಾಶಿ_ಮೇಲಿನ_ವಿಳಾಸ ) )
    #ಇಲ್ಲದಿದ್ದರೆ /* ifndef configVALIDATE_HEAP_BLOCK_POINTER */
        #ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_VALIDATE_ಖಂಡ_ಸೂಚಕ( px_ಖಂಡ )                           \
            config_VALIDATE_ರಾಶಿ_ಖಂಡ_ಸೂಚಕ( px_ಖಂಡ )
    #ಆದರೆ_ಅಂತ್ಯ /* configVALIDATE_HEAP_BLOCK_POINTER */

#ಇಲ್ಲದಿದ್ದರೆ /* if ( configENABLE_HEAP_PROTECTOR == 1 ) */

    #ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( px_ಖಂಡ )    ( px_ಖಂಡ )

    #ವ್ಯಾಖ್ಯಾನಿಸು ರಾಶಿ_VALIDATE_ಖಂಡ_ಸೂಚಕ( px_ಖಂಡ )

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

/* Define the linked list structure.  This is used to link free blocks in order
 * of their memory address. */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ A_ಖಂಡ_LINK
{
    ರಚನೆ A_ಖಂಡ_LINK * px_ಮುಂದಿನ_Free_ಖಂಡ; /**< The next free block in the list. */
    size_t x_ಖಂಡ_ಗಾತ್ರ;                     /**< The size of the free block. */
} ಖಂಡ_Link_t;

/*-----------------------------------------------------------*/

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸೇರಿಸು_ಖಂಡ_Into_Free_List( ಖಂಡ_Link_t * px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು ) PRIVILEGED_FUNCTION;
ಶೂನ್ಯ v_ಪೋರ್ಟ್_Define_ರಾಶಿ_Regions( ಸ್ಥಿರಾಂಕ ರಾಶಿ_Region_t * ಸ್ಥಿರಾಂಕ px_ರಾಶಿ_Regions ) PRIVILEGED_FUNCTION;

#ಆದರೆ ( config_ENABLE_ರಾಶಿ_PROTECTOR == 1 )

/**
 * @brief Application provided function to get a random value to be used as canary.
 *
 * @param pxHeapCanary [out] Output parameter to return the canary value.
 */
    ಬಾಹ್ಯ ಶೂನ್ಯ v_Application_Get_Random_ರಾಶಿ_Canary( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE * px_ರಾಶಿ_Canary );
#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

/* The size of the structure placed at the beginning of each allocated memory
 * block must by correctly byte aligned. */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ size_t x_ರಾಶಿ_Struct_ಗಾತ್ರ = ( ಗಾತ್ರ( ಖಂಡ_Link_t ) + ( ( size_t ) ( ಪೋರ್ಟ್_BYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ );

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ ಖಂಡ_Link_t x_ಆರಂಭ;
PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ ಖಂಡ_Link_t * px_ಕೊನೆ = ಖಾಲಿ;

/* Keeps track of the number of calls to allocate and free memory as well as the
 * number of free bytes remaining, but says nothing about fragmentation. */
PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ size_t x_Free_ಬೈಟುಗಳು_ಉಳಿದ = ( size_t ) 0U;
PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ size_t x_Minimum_Ever_Free_ಬೈಟುಗಳು_ಉಳಿದ = ( size_t ) 0U;
PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ size_t x_ಸಂಖ್ಯೆ_ದ_Successful_Allocations = ( size_t ) 0U;
PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ size_t x_ಸಂಖ್ಯೆ_ದ_Successful_Frees = ( size_t ) 0U;

#ಆದರೆ ( config_ENABLE_ರಾಶಿ_PROTECTOR == 1 )

/* Canary value for protecting internal heap pointers. */
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE x_ರಾಶಿ_Canary;

/* Highest and lowest heap addresses used for heap block bounds checking. */
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ uint8_t * puc_ರಾಶಿ_ಮೇಲಿನ_ವಿಳಾಸ = ಖಾಲಿ;
    PRIVILEGED_ದತ್ತಾಂಶ ಸ್ಥಿರ uint8_t * puc_ರಾಶಿ_ಕೆಳಗಿನ_ವಿಳಾಸ = ಖಾಲಿ;

#ಆದರೆ_ಅಂತ್ಯ /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

ಶೂನ್ಯ * pv_ಪೋರ್ಟ್_Malloc( size_t x_Wanted_ಗಾತ್ರ )
{
    ಖಂಡ_Link_t * px_ಖಂಡ;
    ಖಂಡ_Link_t * px_ಹಿಂದಿನ_ಖಂಡ;
    ಖಂಡ_Link_t * px_New_ಖಂಡ_Link;
    ಶೂನ್ಯ * pvReturn = ಖಾಲಿ;
    size_t x_Additional_Required_ಗಾತ್ರ;
    size_t x_Allocated_ಖಂಡ_ಗಾತ್ರ = 0;

    /* The heap must be initialised before the first call to
     * pvPortMalloc(). */
    configASSERT( px_ಕೊನೆ );

    ಆದರೆ( x_Wanted_ಗಾತ್ರ > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        ಆದರೆ( ರಾಶಿ_ಕೂಡಿಸು_WILL_ಅತಿಪ್ರವಾಹ( x_Wanted_ಗಾತ್ರ, x_ರಾಶಿ_Struct_ಗಾತ್ರ ) == 0 )
        {
            x_Wanted_ಗಾತ್ರ += x_ರಾಶಿ_Struct_ಗಾತ್ರ;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            ಆದರೆ( ( x_Wanted_ಗಾತ್ರ & ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_ಗಾತ್ರ = ಪೋರ್ಟ್_BYTE_ALIGNMENT - ( x_Wanted_ಗಾತ್ರ & ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ );

                ಆದರೆ( ರಾಶಿ_ಕೂಡಿಸು_WILL_ಅತಿಪ್ರವಾಹ( x_Wanted_ಗಾತ್ರ, x_Additional_Required_ಗಾತ್ರ ) == 0 )
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

    vTaskSuspendAll();
    {
        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        ಆದರೆ( ರಾಶಿ_ಖಂಡ_ಗಾತ್ರ_IS_VALID( x_Wanted_ಗಾತ್ರ ) != 0 )
        {
            ಆದರೆ( ( x_Wanted_ಗಾತ್ರ > 0 ) && ( x_Wanted_ಗಾತ್ರ <= x_Free_ಬೈಟುಗಳು_ಉಳಿದ ) )
            {
                /* Traverse the list from the start (lowest address) block until
                 * one of adequate size is found. */
                px_ಹಿಂದಿನ_ಖಂಡ = &x_ಆರಂಭ;
                px_ಖಂಡ = ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( x_ಆರಂಭ.px_ಮುಂದಿನ_Free_ಖಂಡ );
                ರಾಶಿ_VALIDATE_ಖಂಡ_ಸೂಚಕ( px_ಖಂಡ );

                ಆಗ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ < x_Wanted_ಗಾತ್ರ ) && ( px_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ != ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( ಖಾಲಿ ) ) )
                {
                    px_ಹಿಂದಿನ_ಖಂಡ = px_ಖಂಡ;
                    px_ಖಂಡ = ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( px_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ );

                    /* pxEnd is the end marker of the free list. It is located at
                     * pucHeapHighAddress and is not part of the usable heap, so it
                     * must be excluded from the heap block pointer validation. */
                    ಆದರೆ( px_ಖಂಡ != px_ಕೊನೆ )
                    {
                        ರಾಶಿ_VALIDATE_ಖಂಡ_ಸೂಚಕ( px_ಖಂಡ );
                    }
                }

                /* If the end marker was reached then a block of adequate size
                 * was not found. */
                ಆದರೆ( px_ಖಂಡ != px_ಕೊನೆ )
                {
                    /* Return the memory space pointed to - jumping over the
                     * BlockLink_t structure at its start. */
                    pvReturn = ( ಶೂನ್ಯ * ) ( ( ( uint8_t * ) ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( px_ಹಿಂದಿನ_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ ) ) + x_ರಾಶಿ_Struct_ಗಾತ್ರ );
                    ರಾಶಿ_VALIDATE_ಖಂಡ_ಸೂಚಕ( pvReturn );

                    /* This block is being returned for use so must be taken out
                     * of the list of free blocks. */
                    px_ಹಿಂದಿನ_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ = px_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ;

                    /* If the block is larger than required it can be split into
                     * two. */
                    configASSERT( ರಾಶಿ_ಕಳೆ_WILL_UNDERFLOW( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ, x_Wanted_ಗಾತ್ರ ) == 0 );

                    ಆದರೆ( ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ - x_Wanted_ಗಾತ್ರ ) > ರಾಶಿ_MINIMUM_ಖಂಡ_ಗಾತ್ರ )
                    {
                        /* This block is to be split into two.  Create a new
                         * block following the number of bytes requested. The void
                         * cast is used to prevent byte alignment warnings from the
                         * compiler. */
                        px_New_ಖಂಡ_Link = ( ಶೂನ್ಯ * ) ( ( ( uint8_t * ) px_ಖಂಡ ) + x_Wanted_ಗಾತ್ರ );
                        configASSERT( ( ( ( size_t ) px_New_ಖಂಡ_Link ) & ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) == 0 );

                        /* Calculate the sizes of two blocks split from the
                         * single block. */
                        px_New_ಖಂಡ_Link->x_ಖಂಡ_ಗಾತ್ರ = px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ - x_Wanted_ಗಾತ್ರ;
                        px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ = x_Wanted_ಗಾತ್ರ;

                        /* Insert the new block into the list of free blocks. */
                        px_New_ಖಂಡ_Link->px_ಮುಂದಿನ_Free_ಖಂಡ = px_ಹಿಂದಿನ_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ;
                        px_ಹಿಂದಿನ_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ = ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( px_New_ಖಂಡ_Link );
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

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    ರಾಶಿ_ALLOCATE_ಖಂಡ( px_ಖಂಡ );
                    px_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ = ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( ಖಾಲಿ );
                    x_ಸಂಖ್ಯೆ_ದ_Successful_Allocations++;
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
    }
    ( ಶೂನ್ಯ ) xTaskResumeAll();

    #ಆದರೆ ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        ಆದರೆ( pvReturn == ಖಾಲಿ )
        {
            vApplicationMallocFailedHook();
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_MALLOC_FAILED_HOOK == 1 ) */

    configASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) == 0 );
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

        ರಾಶಿ_VALIDATE_ಖಂಡ_ಸೂಚಕ( pxLink );
        configASSERT( ರಾಶಿ_ಖಂಡ_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_ಮುಂದಿನ_Free_ಖಂಡ == ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( ಖಾಲಿ ) );

        ಆದರೆ( ರಾಶಿ_ಖಂಡ_IS_ALLOCATED( pxLink ) != 0 )
        {
            ಆದರೆ( pxLink->px_ಮುಂದಿನ_Free_ಖಂಡ == ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( ಖಾಲಿ ) )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                ರಾಶಿ_FREE_ಖಂಡ( pxLink );
                #ಆದರೆ ( config_ರಾಶಿ_CLEAR_ಸ್ಮರಣೆ_ON_FREE == 1 )
                {
                    /* Check for underflow as this can occur if xBlockSize is
                     * overwritten in a heap block. */
                    ಆದರೆ( ರಾಶಿ_ಕಳೆ_WILL_UNDERFLOW( pxLink->x_ಖಂಡ_ಗಾತ್ರ, x_ರಾಶಿ_Struct_ಗಾತ್ರ ) == 0 )
                    {
                        ( ಶೂನ್ಯ ) memset( puc + x_ರಾಶಿ_Struct_ಗಾತ್ರ, 0, pxLink->x_ಖಂಡ_ಗಾತ್ರ - x_ರಾಶಿ_Struct_ಗಾತ್ರ );
                    }
                }
                #ಆದರೆ_ಅಂತ್ಯ

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_ಬೈಟುಗಳು_ಉಳಿದ += pxLink->x_ಖಂಡ_ಗಾತ್ರ;
                    traceFREE( pv, pxLink->x_ಖಂಡ_ಗಾತ್ರ );
                    prv_ಸೇರಿಸು_ಖಂಡ_Into_Free_List( ( ( ಖಂಡ_Link_t * ) pxLink ) );
                    x_ಸಂಖ್ಯೆ_ದ_Successful_Frees++;
                }
                ( ಶೂನ್ಯ ) xTaskResumeAll();
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

ಶೂನ್ಯ x_ಪೋರ್ಟ್_Reset_ರಾಶಿ_Minimum_Ever_Free_ರಾಶಿ_ಗಾತ್ರ( ಶೂನ್ಯ )
{
    x_Minimum_Ever_Free_ಬೈಟುಗಳು_ಉಳಿದ = x_Free_ಬೈಟುಗಳು_ಉಳಿದ;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ * pv_ಪೋರ್ಟ್_Calloc( size_t x_ಅಂಕೆ,
                     size_t x_ಗಾತ್ರ )
{
    ಶೂನ್ಯ * pv = ಖಾಲಿ;

    ಆದರೆ( ರಾಶಿ_MULTIPLY_WILL_ಅತಿಪ್ರವಾಹ( x_ಅಂಕೆ, x_ಗಾತ್ರ ) == 0 )
    {
        pv = pv_ಪೋರ್ಟ್_Malloc( x_ಅಂಕೆ * x_ಗಾತ್ರ );

        ಆದರೆ( pv != ಖಾಲಿ )
        {
            ( ಶೂನ್ಯ ) memset( pv, 0, x_ಅಂಕೆ * x_ಗಾತ್ರ );
        }
    }

    ಹಿಂತಿರುಗಿ pv;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸೇರಿಸು_ಖಂಡ_Into_Free_List( ಖಂಡ_Link_t * px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು ) /* PRIVILEGED_FUNCTION */
{
    ಖಂಡ_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    ಗಾಗಿ( pxIterator = &x_ಆರಂಭ; ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ ) < px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು; pxIterator = ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ ) )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    ಆದರೆ( pxIterator != &x_ಆರಂಭ )
    {
        ರಾಶಿ_VALIDATE_ಖಂಡ_ಸೂಚಕ( pxIterator );
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

    ಆದರೆ( ( puc + px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು->x_ಖಂಡ_ಗಾತ್ರ ) == ( uint8_t * ) ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ ) )
    {
        ಆದರೆ( ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ ) != px_ಕೊನೆ )
        {
            /* Form one big block from the two blocks. */
            px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು->x_ಖಂಡ_ಗಾತ್ರ += ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ )->x_ಖಂಡ_ಗಾತ್ರ;
            px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು->px_ಮುಂದಿನ_Free_ಖಂಡ = ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ )->px_ಮುಂದಿನ_Free_ಖಂಡ;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು->px_ಮುಂದಿನ_Free_ಖಂಡ = ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( px_ಕೊನೆ );
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
        pxIterator->px_ಮುಂದಿನ_Free_ಖಂಡ = ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( px_ಖಂಡ_ಗಮ್ಯ_ಸೇರಿಸು );
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Define_ರಾಶಿ_Regions( ಸ್ಥಿರಾಂಕ ರಾಶಿ_Region_t * ಸ್ಥಿರಾಂಕ px_ರಾಶಿ_Regions ) /* PRIVILEGED_FUNCTION */
{
    ಖಂಡ_Link_t * px_ಮೊದಲ_Free_ಖಂಡ_ಒಳ_Region = ಖಾಲಿ;
    ಖಂಡ_Link_t * px_ಹಿಂದಿನ_Free_ಖಂಡ;
    ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE x_Aligned_ರಾಶಿ;
    size_t x_ಒಟ್ಟು_Region_ಗಾತ್ರ, x_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ = 0;
    ತಳ_Type_t xDefinedRegions = 0;
    ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE x_ವಿಳಾಸ;
    ಸ್ಥಿರಾಂಕ ರಾಶಿ_Region_t * px_ರಾಶಿ_Region;

    /* Can only call once! */
    configASSERT( px_ಕೊನೆ == ಖಾಲಿ );

    #ಆದರೆ ( config_ENABLE_ರಾಶಿ_PROTECTOR == 1 )
    {
        v_Application_Get_Random_ರಾಶಿ_Canary( &( x_ರಾಶಿ_Canary ) );
    }
    #ಆದರೆ_ಅಂತ್ಯ

    px_ರಾಶಿ_Region = &( px_ರಾಶಿ_Regions[ xDefinedRegions ] );

    ಆಗ( px_ರಾಶಿ_Region->x_ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು > 0 )
    {
        x_ಒಟ್ಟು_Region_ಗಾತ್ರ = px_ರಾಶಿ_Region->x_ಗಾತ್ರ_ಒಳ_ಬೈಟುಗಳು;

        /* Ensure the heap region starts on a correctly aligned boundary. */
        x_ವಿಳಾಸ = ( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE ) px_ರಾಶಿ_Region->puc_ಆರಂಭ_ವಿಳಾಸ;

        ಆದರೆ( ( x_ವಿಳಾಸ & ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ ) != 0 )
        {
            x_ವಿಳಾಸ += ( ಪೋರ್ಟ್_BYTE_ALIGNMENT - 1 );
            x_ವಿಳಾಸ &= ~( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE ) ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ;

            /* Adjust the size for the bytes lost to alignment. */
            x_ಒಟ್ಟು_Region_ಗಾತ್ರ -= ( size_t ) ( x_ವಿಳಾಸ - ( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE ) px_ರಾಶಿ_Region->puc_ಆರಂಭ_ವಿಳಾಸ );
        }

        x_Aligned_ರಾಶಿ = x_ವಿಳಾಸ;

        /* Set xStart if it has not already been set. */
        ಆದರೆ( xDefinedRegions == 0 )
        {
            /* xStart is used to hold a pointer to the first item in the list of
             *  free blocks.  The void cast is used to prevent compiler warnings. */
            x_ಆರಂಭ.px_ಮುಂದಿನ_Free_ಖಂಡ = ( ಖಂಡ_Link_t * ) ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( x_Aligned_ರಾಶಿ );
            x_ಆರಂಭ.x_ಖಂಡ_ಗಾತ್ರ = ( size_t ) 0;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            /* Should only get here if one region has already been added to the
             * heap. */
            configASSERT( px_ಕೊನೆ != ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( ಖಾಲಿ ) );

            /* Check blocks are passed in with increasing start addresses. */
            configASSERT( ( size_t ) x_ವಿಳಾಸ > ( size_t ) px_ಕೊನೆ );
        }

        #ಆದರೆ ( config_ENABLE_ರಾಶಿ_PROTECTOR == 1 )
        {
            ಆದರೆ( ( puc_ರಾಶಿ_ಕೆಳಗಿನ_ವಿಳಾಸ == ಖಾಲಿ ) ||
                ( ( uint8_t * ) x_Aligned_ರಾಶಿ < puc_ರಾಶಿ_ಕೆಳಗಿನ_ವಿಳಾಸ ) )
            {
                puc_ರಾಶಿ_ಕೆಳಗಿನ_ವಿಳಾಸ = ( uint8_t * ) x_Aligned_ರಾಶಿ;
            }
        }
        #ಆದರೆ_ಅಂತ್ಯ /* configENABLE_HEAP_PROTECTOR */

        /* Remember the location of the end marker in the previous region, if
         * any. */
        px_ಹಿಂದಿನ_Free_ಖಂಡ = px_ಕೊನೆ;

        /* pxEnd is used to mark the end of the list of free blocks and is
         * inserted at the end of the region space. */
        x_ವಿಳಾಸ = x_Aligned_ರಾಶಿ + ( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE ) x_ಒಟ್ಟು_Region_ಗಾತ್ರ;
        x_ವಿಳಾಸ -= ( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE ) x_ರಾಶಿ_Struct_ಗಾತ್ರ;
        x_ವಿಳಾಸ &= ~( ( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE ) ಪೋರ್ಟ್_BYTE_ALIGNMENT_ಮುಖವಾಡ );
        px_ಕೊನೆ = ( ಖಂಡ_Link_t * ) x_ವಿಳಾಸ;
        px_ಕೊನೆ->x_ಖಂಡ_ಗಾತ್ರ = 0;
        px_ಕೊನೆ->px_ಮುಂದಿನ_Free_ಖಂಡ = ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( ಖಾಲಿ );

        /* To start with there is a single free block in this region that is
         * sized to take up the entire heap region minus the space taken by the
         * free block structure. */
        px_ಮೊದಲ_Free_ಖಂಡ_ಒಳ_Region = ( ಖಂಡ_Link_t * ) x_Aligned_ರಾಶಿ;
        px_ಮೊದಲ_Free_ಖಂಡ_ಒಳ_Region->x_ಖಂಡ_ಗಾತ್ರ = ( size_t ) ( x_ವಿಳಾಸ - ( ಪೋರ್ಟ್_ಸೂಚಕ_ಗಾತ್ರ_TYPE ) px_ಮೊದಲ_Free_ಖಂಡ_ಒಳ_Region );
        px_ಮೊದಲ_Free_ಖಂಡ_ಒಳ_Region->px_ಮುಂದಿನ_Free_ಖಂಡ = ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( px_ಕೊನೆ );

        /* If this is not the first region that makes up the entire heap space
         * then link the previous region to this region. */
        ಆದರೆ( px_ಹಿಂದಿನ_Free_ಖಂಡ != ಖಾಲಿ )
        {
            px_ಹಿಂದಿನ_Free_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ = ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( px_ಮೊದಲ_Free_ಖಂಡ_ಒಳ_Region );
        }

        x_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ += px_ಮೊದಲ_Free_ಖಂಡ_ಒಳ_Region->x_ಖಂಡ_ಗಾತ್ರ;

        #ಆದರೆ ( config_ENABLE_ರಾಶಿ_PROTECTOR == 1 )
        {
            ಆದರೆ( ( puc_ರಾಶಿ_ಮೇಲಿನ_ವಿಳಾಸ == ಖಾಲಿ ) ||
                ( ( ( ( uint8_t * ) px_ಮೊದಲ_Free_ಖಂಡ_ಒಳ_Region ) + px_ಮೊದಲ_Free_ಖಂಡ_ಒಳ_Region->x_ಖಂಡ_ಗಾತ್ರ ) > puc_ರಾಶಿ_ಮೇಲಿನ_ವಿಳಾಸ ) )
            {
                puc_ರಾಶಿ_ಮೇಲಿನ_ವಿಳಾಸ = ( ( uint8_t * ) px_ಮೊದಲ_Free_ಖಂಡ_ಒಳ_Region ) + px_ಮೊದಲ_Free_ಖಂಡ_ಒಳ_Region->x_ಖಂಡ_ಗಾತ್ರ;
            }
        }
        #ಆದರೆ_ಅಂತ್ಯ

        /* Move onto the next HeapRegion_t structure. */
        xDefinedRegions++;
        px_ರಾಶಿ_Region = &( px_ರಾಶಿ_Regions[ xDefinedRegions ] );
    }

    x_Minimum_Ever_Free_ಬೈಟುಗಳು_ಉಳಿದ = x_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ;
    x_Free_ಬೈಟುಗಳು_ಉಳಿದ = x_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ;

    /* Check something was actually defined before it is accessed. */
    configASSERT( x_ಒಟ್ಟು_ರಾಶಿ_ಗಾತ್ರ );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Get_ರಾಶಿ_Stats( ರಾಶಿ_Stats_t * px_ರಾಶಿ_Stats )
{
    ಖಂಡ_Link_t * px_ಖಂಡ;
    size_t x_ಖಂಡಗಳು = 0, x_Max_ಗಾತ್ರ = 0, x_Min_ಗಾತ್ರ = SIZE_MAX;

    vTaskSuspendAll();
    {
        px_ಖಂಡ = ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( x_ಆರಂಭ.px_ಮುಂದಿನ_Free_ಖಂಡ );

        /* pxBlock will be NULL if the heap has not been initialised.  The heap
         * is initialised automatically when the first allocation is made. */
        ಆದರೆ( px_ಖಂಡ != ಖಾಲಿ )
        {
            ಆಗ( px_ಖಂಡ != px_ಕೊನೆ )
            {
                /* Increment the number of blocks and record the largest block seen
                 * so far. */
                x_ಖಂಡಗಳು++;

                ಆದರೆ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ > x_Max_ಗಾತ್ರ )
                {
                    x_Max_ಗಾತ್ರ = px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ;
                }

                /* Heap five will have a zero sized block at the end of each
                 * each region - the block is only used to link to the next
                 * heap region so it not a real block. */
                ಆದರೆ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ != 0 )
                {
                    ಆದರೆ( px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ < x_Min_ಗಾತ್ರ )
                    {
                        x_Min_ಗಾತ್ರ = px_ಖಂಡ->x_ಖಂಡ_ಗಾತ್ರ;
                    }
                }

                /* Move to the next block in the chain until the last block is
                 * reached. */
                px_ಖಂಡ = ರಾಶಿ_PROTECT_ಖಂಡ_ಸೂಚಕ( px_ಖಂಡ->px_ಮುಂದಿನ_Free_ಖಂಡ );
            }
        }
    }
    ( ಶೂನ್ಯ ) xTaskResumeAll();

    px_ರಾಶಿ_Stats->x_ಗಾತ್ರ_ದ_ಅತಿದೊಡ್ಡ_Free_ಖಂಡ_ಒಳ_ಬೈಟುಗಳು = x_Max_ಗಾತ್ರ;
    px_ರಾಶಿ_Stats->x_ಗಾತ್ರ_ದ_ಅತಿಚಿಕ್ಕ_Free_ಖಂಡ_ಒಳ_ಬೈಟುಗಳು = x_Min_ಗಾತ್ರ;
    px_ರಾಶಿ_Stats->x_ಸಂಖ್ಯೆ_ದ_Free_ಖಂಡಗಳು = x_ಖಂಡಗಳು;

    taskENTER_CRITICAL();
    {
        px_ರಾಶಿ_Stats->x_ಲಭ್ಯ_ರಾಶಿ_Space_ಒಳ_ಬೈಟುಗಳು = x_Free_ಬೈಟುಗಳು_ಉಳಿದ;
        px_ರಾಶಿ_Stats->x_ಸಂಖ್ಯೆ_ದ_Successful_Allocations = x_ಸಂಖ್ಯೆ_ದ_Successful_Allocations;
        px_ರಾಶಿ_Stats->x_ಸಂಖ್ಯೆ_ದ_Successful_Frees = x_ಸಂಖ್ಯೆ_ದ_Successful_Frees;
        px_ರಾಶಿ_Stats->x_Minimum_Ever_Free_ಬೈಟುಗಳು_ಉಳಿದ = x_Minimum_Ever_Free_ಬೈಟುಗಳು_ಉಳಿದ;
    }
    taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
ಶೂನ್ಯ v_ಪೋರ್ಟ್_ರಾಶಿ_Reset_State( ಶೂನ್ಯ )
{
    px_ಕೊನೆ = ಖಾಲಿ;

    x_Free_ಬೈಟುಗಳು_ಉಳಿದ = ( size_t ) 0U;
    x_Minimum_Ever_Free_ಬೈಟುಗಳು_ಉಳಿದ = ( size_t ) 0U;
    x_ಸಂಖ್ಯೆ_ದ_Successful_Allocations = ( size_t ) 0U;
    x_ಸಂಖ್ಯೆ_ದ_Successful_Frees = ( size_t ) 0U;

    #ಆದರೆ ( config_ENABLE_ರಾಶಿ_PROTECTOR == 1 )
        puc_ರಾಶಿ_ಮೇಲಿನ_ವಿಳಾಸ = ಖಾಲಿ;
        puc_ರಾಶಿ_ಕೆಳಗಿನ_ವಿಳಾಸ = ಖಾಲಿ;
    #ಆದರೆ_ಅಂತ್ಯ /* #if ( configENABLE_HEAP_PROTECTOR == 1 ) */
}
/*-----------------------------------------------------------*/
