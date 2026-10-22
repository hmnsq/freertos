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
#ضمن <stdlib.h>
#ضمن <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#وصف_ڪريو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ضمن "FreeRTOS.h"
#ضمن "task.h"

#وصف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#إذا ( config_SUPPORT_DYNAMIC_ورهاست == 0 )
    #غلطي This file must not be استعمال_ٿيل إذا config_SUPPORT_DYNAMIC_ورهاست is 0
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل config_ڍير_CLEAR_يادگيري_ON_FREE
    #وصف_ڪريو config_ڍير_CLEAR_يادگيري_ON_FREE    0
#جيڪڏهن_پورو

/* Block sizes must not get too small. */
#وصف_ڪريو ڍير_MINIMUM_بلاڪ_سائيز    ( ( size_t ) ( x_ڍير_Struct_سائيز << 1 ) )

/* Assumes 8bit bytes! */
#وصف_ڪريو ڍير_بٽ_في_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#وصف_ڪريو ڍير_سائيز_MAX              ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#وصف_ڪريو ڍير_MULTIPLY_WILL_حد_کان_مٿي( a, b )     ( ( ( a ) > 0 ) && ( ( b ) > ( ڍير_سائيز_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#وصف_ڪريو ڍير_جوڙيو_WILL_حد_کان_مٿي( a, b )          ( ( a ) > ( ڍير_سائيز_MAX - ( b ) ) )

/* Check if the subtraction operation ( a - b ) will result in underflow. */
#وصف_ڪريو ڍير_ڪٽيو_WILL_UNDERFLOW( a, b )    ( ( a ) < ( b ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#وصف_ڪريو ڍير_بلاڪ_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( حجم( size_t ) * ڍير_بٽ_في_BYTE ) - 1 ) )
#وصف_ڪريو ڍير_بلاڪ_سائيز_IS_VALID( x_بلاڪ_سائيز )    ( ( ( x_بلاڪ_سائيز ) & ڍير_بلاڪ_ALLOCATED_BITMASK ) == 0 )
#وصف_ڪريو ڍير_بلاڪ_IS_ALLOCATED( px_بلاڪ )        ( ( ( px_بلاڪ->x_بلاڪ_سائيز ) & ڍير_بلاڪ_ALLOCATED_BITMASK ) != 0 )
#وصف_ڪريو ڍير_ALLOCATE_بلاڪ( px_بلاڪ )            ( ( px_بلاڪ->x_بلاڪ_سائيز ) |= ڍير_بلاڪ_ALLOCATED_BITMASK )
#وصف_ڪريو ڍير_FREE_بلاڪ( px_بلاڪ )                ( ( px_بلاڪ->x_بلاڪ_سائيز ) &= ~ڍير_بلاڪ_ALLOCATED_BITMASK )

/* Setting configENABLE_HEAP_PROTECTOR to 1 enables heap block pointers
 * protection using an application supplied canary value to catch heap
 * corruption should a heap buffer overflow occur.
 */
#إذا ( config_ENABLE_ڍير_PROTECTOR == 1 )

/* Macro to load/store BlockLink_t pointers to memory. By XORing the
 * pointers with a random canary value, heap overflows will result
 * in randomly unpredictable pointer values which will be caught by
 * heapVALIDATE_BLOCK_POINTER assert. */
    #وصف_ڪريو ڍير_PROTECT_بلاڪ_اشارو( px_بلاڪ )    ( ( بلاڪ_Link_t * ) ( ( ( پورٽ_اشارو_سائيز_TYPE ) ( px_بلاڪ ) ) ^ x_ڍير_Canary ) )

/* Assert that a heap block pointer is within the heap bounds.
 * Setting configVALIDATE_HEAP_BLOCK_POINTER to 1 enables customized heap block pointers
 * protection on heap_5. */
    #جيڪڏهن_وصف_نه_ٿيل config_VALIDATE_ڍير_بلاڪ_اشارو
        #وصف_ڪريو ڍير_VALIDATE_بلاڪ_اشارو( px_بلاڪ )                           \
            configASSERT( ( puc_ڍير_مٿاهون_پتو != عدم ) &&                     \
                          ( puc_ڍير_هيٺيون_پتو != عدم ) &&                      \
                          ( ( uint8_t * ) ( px_بلاڪ ) >= puc_ڍير_هيٺيون_پتو ) && \
                          ( ( uint8_t * ) ( px_بلاڪ ) < puc_ڍير_مٿاهون_پتو ) )
    #وإلا /* ifndef configVALIDATE_HEAP_BLOCK_POINTER */
        #وصف_ڪريو ڍير_VALIDATE_بلاڪ_اشارو( px_بلاڪ )                           \
            config_VALIDATE_ڍير_بلاڪ_اشارو( px_بلاڪ )
    #جيڪڏهن_پورو /* configVALIDATE_HEAP_BLOCK_POINTER */

#وإلا /* if ( configENABLE_HEAP_PROTECTOR == 1 ) */

    #وصف_ڪريو ڍير_PROTECT_بلاڪ_اشارو( px_بلاڪ )    ( px_بلاڪ )

    #وصف_ڪريو ڍير_VALIDATE_بلاڪ_اشارو( px_بلاڪ )

#جيڪڏهن_پورو /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

/* Define the linked list structure.  This is used to link free blocks in order
 * of their memory address. */
تعريفنوع بنية A_بلاڪ_LINK
{
    بنية A_بلاڪ_LINK * px_ايندڙ_Free_بلاڪ; /**< The next free block in the list. */
    size_t x_بلاڪ_سائيز;                     /**< The size of the free block. */
} بلاڪ_Link_t;

/*-----------------------------------------------------------*/

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
ساكن فراغ prv_وجهو_بلاڪ_Into_Free_List( بلاڪ_Link_t * px_بلاڪ_منزل_وجهو ) PRIVILEGED_FUNCTION;
فراغ v_پورٽ_Define_ڍير_Regions( ثابت ڍير_Region_t * ثابت px_ڍير_Regions ) PRIVILEGED_FUNCTION;

#إذا ( config_ENABLE_ڍير_PROTECTOR == 1 )

/**
 * @brief Application provided function to get a random value to be used as canary.
 *
 * @param pxHeapCanary [out] Output parameter to return the canary value.
 */
    خارجي فراغ v_Application_Get_Random_ڍير_Canary( پورٽ_اشارو_سائيز_TYPE * px_ڍير_Canary );
#جيڪڏهن_پورو /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

/* The size of the structure placed at the beginning of each allocated memory
 * block must by correctly byte aligned. */
ساكن ثابت size_t x_ڍير_Struct_سائيز = ( حجم( بلاڪ_Link_t ) + ( ( size_t ) ( پورٽ_BYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) پورٽ_BYTE_ALIGNMENT_نقاب );

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_معلومات ساكن بلاڪ_Link_t x_شروعات;
PRIVILEGED_معلومات ساكن بلاڪ_Link_t * px_پڇاڙي = عدم;

/* Keeps track of the number of calls to allocate and free memory as well as the
 * number of free bytes remaining, but says nothing about fragmentation. */
PRIVILEGED_معلومات ساكن size_t x_Free_بائيٽون_بچيل = ( size_t ) 0U;
PRIVILEGED_معلومات ساكن size_t x_Minimum_Ever_Free_بائيٽون_بچيل = ( size_t ) 0U;
PRIVILEGED_معلومات ساكن size_t x_عدد_جو_Successful_Allocations = ( size_t ) 0U;
PRIVILEGED_معلومات ساكن size_t x_عدد_جو_Successful_Frees = ( size_t ) 0U;

#إذا ( config_ENABLE_ڍير_PROTECTOR == 1 )

/* Canary value for protecting internal heap pointers. */
    PRIVILEGED_معلومات ساكن پورٽ_اشارو_سائيز_TYPE x_ڍير_Canary;

/* Highest and lowest heap addresses used for heap block bounds checking. */
    PRIVILEGED_معلومات ساكن uint8_t * puc_ڍير_مٿاهون_پتو = عدم;
    PRIVILEGED_معلومات ساكن uint8_t * puc_ڍير_هيٺيون_پتو = عدم;

#جيڪڏهن_پورو /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

فراغ * pv_پورٽ_Malloc( size_t x_Wanted_سائيز )
{
    بلاڪ_Link_t * px_بلاڪ;
    بلاڪ_Link_t * px_اڳيون_بلاڪ;
    بلاڪ_Link_t * px_New_بلاڪ_Link;
    فراغ * pvReturn = عدم;
    size_t x_Additional_Required_سائيز;
    size_t x_Allocated_بلاڪ_سائيز = 0;

    /* The heap must be initialised before the first call to
     * pvPortMalloc(). */
    configASSERT( px_پڇاڙي );

    إذا( x_Wanted_سائيز > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        إذا( ڍير_جوڙيو_WILL_حد_کان_مٿي( x_Wanted_سائيز, x_ڍير_Struct_سائيز ) == 0 )
        {
            x_Wanted_سائيز += x_ڍير_Struct_سائيز;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            إذا( ( x_Wanted_سائيز & پورٽ_BYTE_ALIGNMENT_نقاب ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_سائيز = پورٽ_BYTE_ALIGNMENT - ( x_Wanted_سائيز & پورٽ_BYTE_ALIGNMENT_نقاب );

                إذا( ڍير_جوڙيو_WILL_حد_کان_مٿي( x_Wanted_سائيز, x_Additional_Required_سائيز ) == 0 )
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

    vTaskSuspendAll();
    {
        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        إذا( ڍير_بلاڪ_سائيز_IS_VALID( x_Wanted_سائيز ) != 0 )
        {
            إذا( ( x_Wanted_سائيز > 0 ) && ( x_Wanted_سائيز <= x_Free_بائيٽون_بچيل ) )
            {
                /* Traverse the list from the start (lowest address) block until
                 * one of adequate size is found. */
                px_اڳيون_بلاڪ = &x_شروعات;
                px_بلاڪ = ڍير_PROTECT_بلاڪ_اشارو( x_شروعات.px_ايندڙ_Free_بلاڪ );
                ڍير_VALIDATE_بلاڪ_اشارو( px_بلاڪ );

                طالما( ( px_بلاڪ->x_بلاڪ_سائيز < x_Wanted_سائيز ) && ( px_بلاڪ->px_ايندڙ_Free_بلاڪ != ڍير_PROTECT_بلاڪ_اشارو( عدم ) ) )
                {
                    px_اڳيون_بلاڪ = px_بلاڪ;
                    px_بلاڪ = ڍير_PROTECT_بلاڪ_اشارو( px_بلاڪ->px_ايندڙ_Free_بلاڪ );

                    /* pxEnd is the end marker of the free list. It is located at
                     * pucHeapHighAddress and is not part of the usable heap, so it
                     * must be excluded from the heap block pointer validation. */
                    إذا( px_بلاڪ != px_پڇاڙي )
                    {
                        ڍير_VALIDATE_بلاڪ_اشارو( px_بلاڪ );
                    }
                }

                /* If the end marker was reached then a block of adequate size
                 * was not found. */
                إذا( px_بلاڪ != px_پڇاڙي )
                {
                    /* Return the memory space pointed to - jumping over the
                     * BlockLink_t structure at its start. */
                    pvReturn = ( فراغ * ) ( ( ( uint8_t * ) ڍير_PROTECT_بلاڪ_اشارو( px_اڳيون_بلاڪ->px_ايندڙ_Free_بلاڪ ) ) + x_ڍير_Struct_سائيز );
                    ڍير_VALIDATE_بلاڪ_اشارو( pvReturn );

                    /* This block is being returned for use so must be taken out
                     * of the list of free blocks. */
                    px_اڳيون_بلاڪ->px_ايندڙ_Free_بلاڪ = px_بلاڪ->px_ايندڙ_Free_بلاڪ;

                    /* If the block is larger than required it can be split into
                     * two. */
                    configASSERT( ڍير_ڪٽيو_WILL_UNDERFLOW( px_بلاڪ->x_بلاڪ_سائيز, x_Wanted_سائيز ) == 0 );

                    إذا( ( px_بلاڪ->x_بلاڪ_سائيز - x_Wanted_سائيز ) > ڍير_MINIMUM_بلاڪ_سائيز )
                    {
                        /* This block is to be split into two.  Create a new
                         * block following the number of bytes requested. The void
                         * cast is used to prevent byte alignment warnings from the
                         * compiler. */
                        px_New_بلاڪ_Link = ( فراغ * ) ( ( ( uint8_t * ) px_بلاڪ ) + x_Wanted_سائيز );
                        configASSERT( ( ( ( size_t ) px_New_بلاڪ_Link ) & پورٽ_BYTE_ALIGNMENT_نقاب ) == 0 );

                        /* Calculate the sizes of two blocks split from the
                         * single block. */
                        px_New_بلاڪ_Link->x_بلاڪ_سائيز = px_بلاڪ->x_بلاڪ_سائيز - x_Wanted_سائيز;
                        px_بلاڪ->x_بلاڪ_سائيز = x_Wanted_سائيز;

                        /* Insert the new block into the list of free blocks. */
                        px_New_بلاڪ_Link->px_ايندڙ_Free_بلاڪ = px_اڳيون_بلاڪ->px_ايندڙ_Free_بلاڪ;
                        px_اڳيون_بلاڪ->px_ايندڙ_Free_بلاڪ = ڍير_PROTECT_بلاڪ_اشارو( px_New_بلاڪ_Link );
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

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    ڍير_ALLOCATE_بلاڪ( px_بلاڪ );
                    px_بلاڪ->px_ايندڙ_Free_بلاڪ = ڍير_PROTECT_بلاڪ_اشارو( عدم );
                    x_عدد_جو_Successful_Allocations++;
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
    }
    ( فراغ ) xTaskResumeAll();

    #إذا ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        إذا( pvReturn == عدم )
        {
            vApplicationMallocFailedHook();
        }
        وإلا
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #جيڪڏهن_پورو /* if ( configUSE_MALLOC_FAILED_HOOK == 1 ) */

    configASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) پورٽ_BYTE_ALIGNMENT_نقاب ) == 0 );
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

        ڍير_VALIDATE_بلاڪ_اشارو( pxLink );
        configASSERT( ڍير_بلاڪ_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_ايندڙ_Free_بلاڪ == ڍير_PROTECT_بلاڪ_اشارو( عدم ) );

        إذا( ڍير_بلاڪ_IS_ALLOCATED( pxLink ) != 0 )
        {
            إذا( pxLink->px_ايندڙ_Free_بلاڪ == ڍير_PROTECT_بلاڪ_اشارو( عدم ) )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                ڍير_FREE_بلاڪ( pxLink );
                #إذا ( config_ڍير_CLEAR_يادگيري_ON_FREE == 1 )
                {
                    /* Check for underflow as this can occur if xBlockSize is
                     * overwritten in a heap block. */
                    إذا( ڍير_ڪٽيو_WILL_UNDERFLOW( pxLink->x_بلاڪ_سائيز, x_ڍير_Struct_سائيز ) == 0 )
                    {
                        ( فراغ ) memset( puc + x_ڍير_Struct_سائيز, 0, pxLink->x_بلاڪ_سائيز - x_ڍير_Struct_سائيز );
                    }
                }
                #جيڪڏهن_پورو

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_بائيٽون_بچيل += pxLink->x_بلاڪ_سائيز;
                    traceFREE( pv, pxLink->x_بلاڪ_سائيز );
                    prv_وجهو_بلاڪ_Into_Free_List( ( ( بلاڪ_Link_t * ) pxLink ) );
                    x_عدد_جو_Successful_Frees++;
                }
                ( فراغ ) xTaskResumeAll();
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

فراغ x_پورٽ_Reset_ڍير_Minimum_Ever_Free_ڍير_سائيز( فراغ )
{
    x_Minimum_Ever_Free_بائيٽون_بچيل = x_Free_بائيٽون_بچيل;
}
/*-----------------------------------------------------------*/

فراغ * pv_پورٽ_Calloc( size_t x_انگ,
                     size_t x_سائيز )
{
    فراغ * pv = عدم;

    إذا( ڍير_MULTIPLY_WILL_حد_کان_مٿي( x_انگ, x_سائيز ) == 0 )
    {
        pv = pv_پورٽ_Malloc( x_انگ * x_سائيز );

        إذا( pv != عدم )
        {
            ( فراغ ) memset( pv, 0, x_انگ * x_سائيز );
        }
    }

    أرجع pv;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_وجهو_بلاڪ_Into_Free_List( بلاڪ_Link_t * px_بلاڪ_منزل_وجهو ) /* PRIVILEGED_FUNCTION */
{
    بلاڪ_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    لكل( pxIterator = &x_شروعات; ڍير_PROTECT_بلاڪ_اشارو( pxIterator->px_ايندڙ_Free_بلاڪ ) < px_بلاڪ_منزل_وجهو; pxIterator = ڍير_PROTECT_بلاڪ_اشارو( pxIterator->px_ايندڙ_Free_بلاڪ ) )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    إذا( pxIterator != &x_شروعات )
    {
        ڍير_VALIDATE_بلاڪ_اشارو( pxIterator );
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

    إذا( ( puc + px_بلاڪ_منزل_وجهو->x_بلاڪ_سائيز ) == ( uint8_t * ) ڍير_PROTECT_بلاڪ_اشارو( pxIterator->px_ايندڙ_Free_بلاڪ ) )
    {
        إذا( ڍير_PROTECT_بلاڪ_اشارو( pxIterator->px_ايندڙ_Free_بلاڪ ) != px_پڇاڙي )
        {
            /* Form one big block from the two blocks. */
            px_بلاڪ_منزل_وجهو->x_بلاڪ_سائيز += ڍير_PROTECT_بلاڪ_اشارو( pxIterator->px_ايندڙ_Free_بلاڪ )->x_بلاڪ_سائيز;
            px_بلاڪ_منزل_وجهو->px_ايندڙ_Free_بلاڪ = ڍير_PROTECT_بلاڪ_اشارو( pxIterator->px_ايندڙ_Free_بلاڪ )->px_ايندڙ_Free_بلاڪ;
        }
        وإلا
        {
            px_بلاڪ_منزل_وجهو->px_ايندڙ_Free_بلاڪ = ڍير_PROTECT_بلاڪ_اشارو( px_پڇاڙي );
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
        pxIterator->px_ايندڙ_Free_بلاڪ = ڍير_PROTECT_بلاڪ_اشارو( px_بلاڪ_منزل_وجهو );
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Define_ڍير_Regions( ثابت ڍير_Region_t * ثابت px_ڍير_Regions ) /* PRIVILEGED_FUNCTION */
{
    بلاڪ_Link_t * px_پهريون_Free_بلاڪ_اندريون_Region = عدم;
    بلاڪ_Link_t * px_اڳيون_Free_بلاڪ;
    پورٽ_اشارو_سائيز_TYPE x_Aligned_ڍير;
    size_t x_ڪل_Region_سائيز, x_ڪل_ڍير_سائيز = 0;
    بنياد_Type_t xDefinedRegions = 0;
    پورٽ_اشارو_سائيز_TYPE x_پتو;
    ثابت ڍير_Region_t * px_ڍير_Region;

    /* Can only call once! */
    configASSERT( px_پڇاڙي == عدم );

    #إذا ( config_ENABLE_ڍير_PROTECTOR == 1 )
    {
        v_Application_Get_Random_ڍير_Canary( &( x_ڍير_Canary ) );
    }
    #جيڪڏهن_پورو

    px_ڍير_Region = &( px_ڍير_Regions[ xDefinedRegions ] );

    طالما( px_ڍير_Region->x_سائيز_اندريون_بائيٽون > 0 )
    {
        x_ڪل_Region_سائيز = px_ڍير_Region->x_سائيز_اندريون_بائيٽون;

        /* Ensure the heap region starts on a correctly aligned boundary. */
        x_پتو = ( پورٽ_اشارو_سائيز_TYPE ) px_ڍير_Region->puc_شروعات_پتو;

        إذا( ( x_پتو & پورٽ_BYTE_ALIGNMENT_نقاب ) != 0 )
        {
            x_پتو += ( پورٽ_BYTE_ALIGNMENT - 1 );
            x_پتو &= ~( پورٽ_اشارو_سائيز_TYPE ) پورٽ_BYTE_ALIGNMENT_نقاب;

            /* Adjust the size for the bytes lost to alignment. */
            x_ڪل_Region_سائيز -= ( size_t ) ( x_پتو - ( پورٽ_اشارو_سائيز_TYPE ) px_ڍير_Region->puc_شروعات_پتو );
        }

        x_Aligned_ڍير = x_پتو;

        /* Set xStart if it has not already been set. */
        إذا( xDefinedRegions == 0 )
        {
            /* xStart is used to hold a pointer to the first item in the list of
             *  free blocks.  The void cast is used to prevent compiler warnings. */
            x_شروعات.px_ايندڙ_Free_بلاڪ = ( بلاڪ_Link_t * ) ڍير_PROTECT_بلاڪ_اشارو( x_Aligned_ڍير );
            x_شروعات.x_بلاڪ_سائيز = ( size_t ) 0;
        }
        وإلا
        {
            /* Should only get here if one region has already been added to the
             * heap. */
            configASSERT( px_پڇاڙي != ڍير_PROTECT_بلاڪ_اشارو( عدم ) );

            /* Check blocks are passed in with increasing start addresses. */
            configASSERT( ( size_t ) x_پتو > ( size_t ) px_پڇاڙي );
        }

        #إذا ( config_ENABLE_ڍير_PROTECTOR == 1 )
        {
            إذا( ( puc_ڍير_هيٺيون_پتو == عدم ) ||
                ( ( uint8_t * ) x_Aligned_ڍير < puc_ڍير_هيٺيون_پتو ) )
            {
                puc_ڍير_هيٺيون_پتو = ( uint8_t * ) x_Aligned_ڍير;
            }
        }
        #جيڪڏهن_پورو /* configENABLE_HEAP_PROTECTOR */

        /* Remember the location of the end marker in the previous region, if
         * any. */
        px_اڳيون_Free_بلاڪ = px_پڇاڙي;

        /* pxEnd is used to mark the end of the list of free blocks and is
         * inserted at the end of the region space. */
        x_پتو = x_Aligned_ڍير + ( پورٽ_اشارو_سائيز_TYPE ) x_ڪل_Region_سائيز;
        x_پتو -= ( پورٽ_اشارو_سائيز_TYPE ) x_ڍير_Struct_سائيز;
        x_پتو &= ~( ( پورٽ_اشارو_سائيز_TYPE ) پورٽ_BYTE_ALIGNMENT_نقاب );
        px_پڇاڙي = ( بلاڪ_Link_t * ) x_پتو;
        px_پڇاڙي->x_بلاڪ_سائيز = 0;
        px_پڇاڙي->px_ايندڙ_Free_بلاڪ = ڍير_PROTECT_بلاڪ_اشارو( عدم );

        /* To start with there is a single free block in this region that is
         * sized to take up the entire heap region minus the space taken by the
         * free block structure. */
        px_پهريون_Free_بلاڪ_اندريون_Region = ( بلاڪ_Link_t * ) x_Aligned_ڍير;
        px_پهريون_Free_بلاڪ_اندريون_Region->x_بلاڪ_سائيز = ( size_t ) ( x_پتو - ( پورٽ_اشارو_سائيز_TYPE ) px_پهريون_Free_بلاڪ_اندريون_Region );
        px_پهريون_Free_بلاڪ_اندريون_Region->px_ايندڙ_Free_بلاڪ = ڍير_PROTECT_بلاڪ_اشارو( px_پڇاڙي );

        /* If this is not the first region that makes up the entire heap space
         * then link the previous region to this region. */
        إذا( px_اڳيون_Free_بلاڪ != عدم )
        {
            px_اڳيون_Free_بلاڪ->px_ايندڙ_Free_بلاڪ = ڍير_PROTECT_بلاڪ_اشارو( px_پهريون_Free_بلاڪ_اندريون_Region );
        }

        x_ڪل_ڍير_سائيز += px_پهريون_Free_بلاڪ_اندريون_Region->x_بلاڪ_سائيز;

        #إذا ( config_ENABLE_ڍير_PROTECTOR == 1 )
        {
            إذا( ( puc_ڍير_مٿاهون_پتو == عدم ) ||
                ( ( ( ( uint8_t * ) px_پهريون_Free_بلاڪ_اندريون_Region ) + px_پهريون_Free_بلاڪ_اندريون_Region->x_بلاڪ_سائيز ) > puc_ڍير_مٿاهون_پتو ) )
            {
                puc_ڍير_مٿاهون_پتو = ( ( uint8_t * ) px_پهريون_Free_بلاڪ_اندريون_Region ) + px_پهريون_Free_بلاڪ_اندريون_Region->x_بلاڪ_سائيز;
            }
        }
        #جيڪڏهن_پورو

        /* Move onto the next HeapRegion_t structure. */
        xDefinedRegions++;
        px_ڍير_Region = &( px_ڍير_Regions[ xDefinedRegions ] );
    }

    x_Minimum_Ever_Free_بائيٽون_بچيل = x_ڪل_ڍير_سائيز;
    x_Free_بائيٽون_بچيل = x_ڪل_ڍير_سائيز;

    /* Check something was actually defined before it is accessed. */
    configASSERT( x_ڪل_ڍير_سائيز );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Get_ڍير_Stats( ڍير_Stats_t * px_ڍير_Stats )
{
    بلاڪ_Link_t * px_بلاڪ;
    size_t x_بلاڪون = 0, x_Max_سائيز = 0, x_Min_سائيز = SIZE_MAX;

    vTaskSuspendAll();
    {
        px_بلاڪ = ڍير_PROTECT_بلاڪ_اشارو( x_شروعات.px_ايندڙ_Free_بلاڪ );

        /* pxBlock will be NULL if the heap has not been initialised.  The heap
         * is initialised automatically when the first allocation is made. */
        إذا( px_بلاڪ != عدم )
        {
            طالما( px_بلاڪ != px_پڇاڙي )
            {
                /* Increment the number of blocks and record the largest block seen
                 * so far. */
                x_بلاڪون++;

                إذا( px_بلاڪ->x_بلاڪ_سائيز > x_Max_سائيز )
                {
                    x_Max_سائيز = px_بلاڪ->x_بلاڪ_سائيز;
                }

                /* Heap five will have a zero sized block at the end of each
                 * each region - the block is only used to link to the next
                 * heap region so it not a real block. */
                إذا( px_بلاڪ->x_بلاڪ_سائيز != 0 )
                {
                    إذا( px_بلاڪ->x_بلاڪ_سائيز < x_Min_سائيز )
                    {
                        x_Min_سائيز = px_بلاڪ->x_بلاڪ_سائيز;
                    }
                }

                /* Move to the next block in the chain until the last block is
                 * reached. */
                px_بلاڪ = ڍير_PROTECT_بلاڪ_اشارو( px_بلاڪ->px_ايندڙ_Free_بلاڪ );
            }
        }
    }
    ( فراغ ) xTaskResumeAll();

    px_ڍير_Stats->x_سائيز_جو_سڀ_کان_وڏو_Free_بلاڪ_اندريون_بائيٽون = x_Max_سائيز;
    px_ڍير_Stats->x_سائيز_جو_سڀ_کان_ننڍو_Free_بلاڪ_اندريون_بائيٽون = x_Min_سائيز;
    px_ڍير_Stats->x_عدد_جو_Free_بلاڪون = x_بلاڪون;

    taskENTER_CRITICAL();
    {
        px_ڍير_Stats->x_موجود_ڍير_Space_اندريون_بائيٽون = x_Free_بائيٽون_بچيل;
        px_ڍير_Stats->x_عدد_جو_Successful_Allocations = x_عدد_جو_Successful_Allocations;
        px_ڍير_Stats->x_عدد_جو_Successful_Frees = x_عدد_جو_Successful_Frees;
        px_ڍير_Stats->x_Minimum_Ever_Free_بائيٽون_بچيل = x_Minimum_Ever_Free_بائيٽون_بچيل;
    }
    taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
فراغ v_پورٽ_ڍير_Reset_State( فراغ )
{
    px_پڇاڙي = عدم;

    x_Free_بائيٽون_بچيل = ( size_t ) 0U;
    x_Minimum_Ever_Free_بائيٽون_بچيل = ( size_t ) 0U;
    x_عدد_جو_Successful_Allocations = ( size_t ) 0U;
    x_عدد_جو_Successful_Frees = ( size_t ) 0U;

    #إذا ( config_ENABLE_ڍير_PROTECTOR == 1 )
        puc_ڍير_مٿاهون_پتو = عدم;
        puc_ڍير_هيٺيون_پتو = عدم;
    #جيڪڏهن_پورو /* #if ( configENABLE_HEAP_PROTECTOR == 1 ) */
}
/*-----------------------------------------------------------*/
