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
#تعریف_کرو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ضمن "FreeRTOS.h"
#ضمن "task.h"

#تعریف_رد MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#إذا ( config_SUPPORT_DYNAMIC_ونڈ == 0 )
    #غلطی This file must not be ورتیا إذا config_SUPPORT_DYNAMIC_ونڈ is 0
#جے_انت

#جے_بنا_تعریف config_ڈھیر_CLEAR_حافظہ_ON_FREE
    #تعریف_کرو config_ڈھیر_CLEAR_حافظہ_ON_FREE    0
#جے_انت

/* Block sizes must not get too small. */
#تعریف_کرو ڈھیر_MINIMUM_بلاک_ناپ    ( ( size_t ) ( x_ڈھیر_Struct_ناپ << 1 ) )

/* Assumes 8bit bytes! */
#تعریف_کرو ڈھیر_بٹ_فی_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#تعریف_کرو ڈھیر_ناپ_MAX              ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#تعریف_کرو ڈھیر_MULTIPLY_WILL_حد_توں_ودھ( a, b )     ( ( ( a ) > 0 ) && ( ( b ) > ( ڈھیر_ناپ_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کرو ڈھیر_جوڑو_WILL_حد_توں_ودھ( a, b )          ( ( a ) > ( ڈھیر_ناپ_MAX - ( b ) ) )

/* Check if the subtraction operation ( a - b ) will result in underflow. */
#تعریف_کرو ڈھیر_گھٹاؤ_WILL_UNDERFLOW( a, b )    ( ( a ) < ( b ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#تعریف_کرو ڈھیر_بلاک_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( حجم( size_t ) * ڈھیر_بٹ_فی_BYTE ) - 1 ) )
#تعریف_کرو ڈھیر_بلاک_ناپ_IS_VALID( x_بلاک_ناپ )    ( ( ( x_بلاک_ناپ ) & ڈھیر_بلاک_ALLOCATED_BITMASK ) == 0 )
#تعریف_کرو ڈھیر_بلاک_IS_ALLOCATED( px_بلاک )        ( ( ( px_بلاک->x_بلاک_ناپ ) & ڈھیر_بلاک_ALLOCATED_BITMASK ) != 0 )
#تعریف_کرو ڈھیر_ALLOCATE_بلاک( px_بلاک )            ( ( px_بلاک->x_بلاک_ناپ ) |= ڈھیر_بلاک_ALLOCATED_BITMASK )
#تعریف_کرو ڈھیر_FREE_بلاک( px_بلاک )                ( ( px_بلاک->x_بلاک_ناپ ) &= ~ڈھیر_بلاک_ALLOCATED_BITMASK )

/* Setting configENABLE_HEAP_PROTECTOR to 1 enables heap block pointers
 * protection using an application supplied canary value to catch heap
 * corruption should a heap buffer overflow occur.
 */
#إذا ( config_ENABLE_ڈھیر_PROTECTOR == 1 )

/* Macro to load/store BlockLink_t pointers to memory. By XORing the
 * pointers with a random canary value, heap overflows will result
 * in randomly unpredictable pointer values which will be caught by
 * heapVALIDATE_BLOCK_POINTER assert. */
    #تعریف_کرو ڈھیر_PROTECT_بلاک_اشارہ_گر( px_بلاک )    ( ( بلاک_Link_t * ) ( ( ( پورٹ_اشارہ_گر_ناپ_TYPE ) ( px_بلاک ) ) ^ x_ڈھیر_Canary ) )

/* Assert that a heap block pointer is within the heap bounds.
 * Setting configVALIDATE_HEAP_BLOCK_POINTER to 1 enables customized heap block pointers
 * protection on heap_5. */
    #جے_بنا_تعریف config_VALIDATE_ڈھیر_بلاک_اشارہ_گر
        #تعریف_کرو ڈھیر_VALIDATE_بلاک_اشارہ_گر( px_بلاک )                           \
            configASSERT( ( puc_ڈھیر_بلند_پتہ != عدم ) &&                     \
                          ( puc_ڈھیر_کم_پتہ != عدم ) &&                      \
                          ( ( uint8_t * ) ( px_بلاک ) >= puc_ڈھیر_کم_پتہ ) && \
                          ( ( uint8_t * ) ( px_بلاک ) < puc_ڈھیر_بلند_پتہ ) )
    #وإلا /* ifndef configVALIDATE_HEAP_BLOCK_POINTER */
        #تعریف_کرو ڈھیر_VALIDATE_بلاک_اشارہ_گر( px_بلاک )                           \
            config_VALIDATE_ڈھیر_بلاک_اشارہ_گر( px_بلاک )
    #جے_انت /* configVALIDATE_HEAP_BLOCK_POINTER */

#وإلا /* if ( configENABLE_HEAP_PROTECTOR == 1 ) */

    #تعریف_کرو ڈھیر_PROTECT_بلاک_اشارہ_گر( px_بلاک )    ( px_بلاک )

    #تعریف_کرو ڈھیر_VALIDATE_بلاک_اشارہ_گر( px_بلاک )

#جے_انت /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

/* Define the linked list structure.  This is used to link free blocks in order
 * of their memory address. */
تعريفنوع بنية A_بلاک_LINK
{
    بنية A_بلاک_LINK * px_اگلا_Free_بلاک; /**< The next free block in the list. */
    size_t x_بلاک_ناپ;                     /**< The size of the free block. */
} بلاک_Link_t;

/*-----------------------------------------------------------*/

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
ساكن فراغ prv_داخل_کرو_بلاک_Into_Free_List( بلاک_Link_t * px_بلاک_منزل_داخل_کرو ) PRIVILEGED_FUNCTION;
فراغ v_پورٹ_Define_ڈھیر_Regions( ثابت ڈھیر_Region_t * ثابت px_ڈھیر_Regions ) PRIVILEGED_FUNCTION;

#إذا ( config_ENABLE_ڈھیر_PROTECTOR == 1 )

/**
 * @brief Application provided function to get a random value to be used as canary.
 *
 * @param pxHeapCanary [out] Output parameter to return the canary value.
 */
    خارجي فراغ v_Application_Get_Random_ڈھیر_Canary( پورٹ_اشارہ_گر_ناپ_TYPE * px_ڈھیر_Canary );
#جے_انت /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

/* The size of the structure placed at the beginning of each allocated memory
 * block must by correctly byte aligned. */
ساكن ثابت size_t x_ڈھیر_Struct_ناپ = ( حجم( بلاک_Link_t ) + ( ( size_t ) ( پورٹ_BYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) پورٹ_BYTE_ALIGNMENT_نقاب );

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_انکڑے ساكن بلاک_Link_t x_شروع;
PRIVILEGED_انکڑے ساكن بلاک_Link_t * px_سرا = عدم;

/* Keeps track of the number of calls to allocate and free memory as well as the
 * number of free bytes remaining, but says nothing about fragmentation. */
PRIVILEGED_انکڑے ساكن size_t x_Free_بائٹاں_بچیا = ( size_t ) 0U;
PRIVILEGED_انکڑے ساكن size_t x_Minimum_Ever_Free_بائٹاں_بچیا = ( size_t ) 0U;
PRIVILEGED_انکڑے ساكن size_t x_نمبر_دا_Successful_Allocations = ( size_t ) 0U;
PRIVILEGED_انکڑے ساكن size_t x_نمبر_دا_Successful_Frees = ( size_t ) 0U;

#إذا ( config_ENABLE_ڈھیر_PROTECTOR == 1 )

/* Canary value for protecting internal heap pointers. */
    PRIVILEGED_انکڑے ساكن پورٹ_اشارہ_گر_ناپ_TYPE x_ڈھیر_Canary;

/* Highest and lowest heap addresses used for heap block bounds checking. */
    PRIVILEGED_انکڑے ساكن uint8_t * puc_ڈھیر_بلند_پتہ = عدم;
    PRIVILEGED_انکڑے ساكن uint8_t * puc_ڈھیر_کم_پتہ = عدم;

#جے_انت /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

فراغ * pv_پورٹ_Malloc( size_t x_Wanted_ناپ )
{
    بلاک_Link_t * px_بلاک;
    بلاک_Link_t * px_پچھلا_بلاک;
    بلاک_Link_t * px_New_بلاک_Link;
    فراغ * pvReturn = عدم;
    size_t x_Additional_Required_ناپ;
    size_t x_Allocated_بلاک_ناپ = 0;

    /* The heap must be initialised before the first call to
     * pvPortMalloc(). */
    configASSERT( px_سرا );

    إذا( x_Wanted_ناپ > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        إذا( ڈھیر_جوڑو_WILL_حد_توں_ودھ( x_Wanted_ناپ, x_ڈھیر_Struct_ناپ ) == 0 )
        {
            x_Wanted_ناپ += x_ڈھیر_Struct_ناپ;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            إذا( ( x_Wanted_ناپ & پورٹ_BYTE_ALIGNMENT_نقاب ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_ناپ = پورٹ_BYTE_ALIGNMENT - ( x_Wanted_ناپ & پورٹ_BYTE_ALIGNMENT_نقاب );

                إذا( ڈھیر_جوڑو_WILL_حد_توں_ودھ( x_Wanted_ناپ, x_Additional_Required_ناپ ) == 0 )
                {
                    x_Wanted_ناپ += x_Additional_Required_ناپ;
                }
                وإلا
                {
                    x_Wanted_ناپ = 0;
                }
            }
            وإلا
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        وإلا
        {
            x_Wanted_ناپ = 0;
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
        إذا( ڈھیر_بلاک_ناپ_IS_VALID( x_Wanted_ناپ ) != 0 )
        {
            إذا( ( x_Wanted_ناپ > 0 ) && ( x_Wanted_ناپ <= x_Free_بائٹاں_بچیا ) )
            {
                /* Traverse the list from the start (lowest address) block until
                 * one of adequate size is found. */
                px_پچھلا_بلاک = &x_شروع;
                px_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( x_شروع.px_اگلا_Free_بلاک );
                ڈھیر_VALIDATE_بلاک_اشارہ_گر( px_بلاک );

                طالما( ( px_بلاک->x_بلاک_ناپ < x_Wanted_ناپ ) && ( px_بلاک->px_اگلا_Free_بلاک != ڈھیر_PROTECT_بلاک_اشارہ_گر( عدم ) ) )
                {
                    px_پچھلا_بلاک = px_بلاک;
                    px_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( px_بلاک->px_اگلا_Free_بلاک );

                    /* pxEnd is the end marker of the free list. It is located at
                     * pucHeapHighAddress and is not part of the usable heap, so it
                     * must be excluded from the heap block pointer validation. */
                    إذا( px_بلاک != px_سرا )
                    {
                        ڈھیر_VALIDATE_بلاک_اشارہ_گر( px_بلاک );
                    }
                }

                /* If the end marker was reached then a block of adequate size
                 * was not found. */
                إذا( px_بلاک != px_سرا )
                {
                    /* Return the memory space pointed to - jumping over the
                     * BlockLink_t structure at its start. */
                    pvReturn = ( فراغ * ) ( ( ( uint8_t * ) ڈھیر_PROTECT_بلاک_اشارہ_گر( px_پچھلا_بلاک->px_اگلا_Free_بلاک ) ) + x_ڈھیر_Struct_ناپ );
                    ڈھیر_VALIDATE_بلاک_اشارہ_گر( pvReturn );

                    /* This block is being returned for use so must be taken out
                     * of the list of free blocks. */
                    px_پچھلا_بلاک->px_اگلا_Free_بلاک = px_بلاک->px_اگلا_Free_بلاک;

                    /* If the block is larger than required it can be split into
                     * two. */
                    configASSERT( ڈھیر_گھٹاؤ_WILL_UNDERFLOW( px_بلاک->x_بلاک_ناپ, x_Wanted_ناپ ) == 0 );

                    إذا( ( px_بلاک->x_بلاک_ناپ - x_Wanted_ناپ ) > ڈھیر_MINIMUM_بلاک_ناپ )
                    {
                        /* This block is to be split into two.  Create a new
                         * block following the number of bytes requested. The void
                         * cast is used to prevent byte alignment warnings from the
                         * compiler. */
                        px_New_بلاک_Link = ( فراغ * ) ( ( ( uint8_t * ) px_بلاک ) + x_Wanted_ناپ );
                        configASSERT( ( ( ( size_t ) px_New_بلاک_Link ) & پورٹ_BYTE_ALIGNMENT_نقاب ) == 0 );

                        /* Calculate the sizes of two blocks split from the
                         * single block. */
                        px_New_بلاک_Link->x_بلاک_ناپ = px_بلاک->x_بلاک_ناپ - x_Wanted_ناپ;
                        px_بلاک->x_بلاک_ناپ = x_Wanted_ناپ;

                        /* Insert the new block into the list of free blocks. */
                        px_New_بلاک_Link->px_اگلا_Free_بلاک = px_پچھلا_بلاک->px_اگلا_Free_بلاک;
                        px_پچھلا_بلاک->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( px_New_بلاک_Link );
                    }
                    وإلا
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Free_بائٹاں_بچیا -= px_بلاک->x_بلاک_ناپ;

                    إذا( x_Free_بائٹاں_بچیا < x_Minimum_Ever_Free_بائٹاں_بچیا )
                    {
                        x_Minimum_Ever_Free_بائٹاں_بچیا = x_Free_بائٹاں_بچیا;
                    }
                    وإلا
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Allocated_بلاک_ناپ = px_بلاک->x_بلاک_ناپ;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    ڈھیر_ALLOCATE_بلاک( px_بلاک );
                    px_بلاک->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( عدم );
                    x_نمبر_دا_Successful_Allocations++;
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

        traceMALLOC( pvReturn, x_Allocated_بلاک_ناپ );

        /* Prevent compiler warnings when trace macros are not used. */
        ( فراغ ) x_Allocated_بلاک_ناپ;
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
    #جے_انت /* if ( configUSE_MALLOC_FAILED_HOOK == 1 ) */

    configASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) پورٹ_BYTE_ALIGNMENT_نقاب ) == 0 );
    أرجع pvReturn;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Free( فراغ * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    بلاک_Link_t * pxLink;

    إذا( pv != عدم )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_ڈھیر_Struct_ناپ;

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( فراغ * ) puc;

        ڈھیر_VALIDATE_بلاک_اشارہ_گر( pxLink );
        configASSERT( ڈھیر_بلاک_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_اگلا_Free_بلاک == ڈھیر_PROTECT_بلاک_اشارہ_گر( عدم ) );

        إذا( ڈھیر_بلاک_IS_ALLOCATED( pxLink ) != 0 )
        {
            إذا( pxLink->px_اگلا_Free_بلاک == ڈھیر_PROTECT_بلاک_اشارہ_گر( عدم ) )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                ڈھیر_FREE_بلاک( pxLink );
                #إذا ( config_ڈھیر_CLEAR_حافظہ_ON_FREE == 1 )
                {
                    /* Check for underflow as this can occur if xBlockSize is
                     * overwritten in a heap block. */
                    إذا( ڈھیر_گھٹاؤ_WILL_UNDERFLOW( pxLink->x_بلاک_ناپ, x_ڈھیر_Struct_ناپ ) == 0 )
                    {
                        ( فراغ ) memset( puc + x_ڈھیر_Struct_ناپ, 0, pxLink->x_بلاک_ناپ - x_ڈھیر_Struct_ناپ );
                    }
                }
                #جے_انت

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_بائٹاں_بچیا += pxLink->x_بلاک_ناپ;
                    traceFREE( pv, pxLink->x_بلاک_ناپ );
                    prv_داخل_کرو_بلاک_Into_Free_List( ( ( بلاک_Link_t * ) pxLink ) );
                    x_نمبر_دا_Successful_Frees++;
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

size_t x_پورٹ_Get_Free_ڈھیر_ناپ( فراغ )
{
    أرجع x_Free_بائٹاں_بچیا;
}
/*-----------------------------------------------------------*/

size_t x_پورٹ_Get_Minimum_Ever_Free_ڈھیر_ناپ( فراغ )
{
    أرجع x_Minimum_Ever_Free_بائٹاں_بچیا;
}
/*-----------------------------------------------------------*/

فراغ x_پورٹ_Reset_ڈھیر_Minimum_Ever_Free_ڈھیر_ناپ( فراغ )
{
    x_Minimum_Ever_Free_بائٹاں_بچیا = x_Free_بائٹاں_بچیا;
}
/*-----------------------------------------------------------*/

فراغ * pv_پورٹ_Calloc( size_t x_عدد,
                     size_t x_ناپ )
{
    فراغ * pv = عدم;

    إذا( ڈھیر_MULTIPLY_WILL_حد_توں_ودھ( x_عدد, x_ناپ ) == 0 )
    {
        pv = pv_پورٹ_Malloc( x_عدد * x_ناپ );

        إذا( pv != عدم )
        {
            ( فراغ ) memset( pv, 0, x_عدد * x_ناپ );
        }
    }

    أرجع pv;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_داخل_کرو_بلاک_Into_Free_List( بلاک_Link_t * px_بلاک_منزل_داخل_کرو ) /* PRIVILEGED_FUNCTION */
{
    بلاک_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    لكل( pxIterator = &x_شروع; ڈھیر_PROTECT_بلاک_اشارہ_گر( pxIterator->px_اگلا_Free_بلاک ) < px_بلاک_منزل_داخل_کرو; pxIterator = ڈھیر_PROTECT_بلاک_اشارہ_گر( pxIterator->px_اگلا_Free_بلاک ) )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    إذا( pxIterator != &x_شروع )
    {
        ڈھیر_VALIDATE_بلاک_اشارہ_گر( pxIterator );
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    إذا( ( puc + pxIterator->x_بلاک_ناپ ) == ( uint8_t * ) px_بلاک_منزل_داخل_کرو )
    {
        pxIterator->x_بلاک_ناپ += px_بلاک_منزل_داخل_کرو->x_بلاک_ناپ;
        px_بلاک_منزل_داخل_کرو = pxIterator;
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_بلاک_منزل_داخل_کرو;

    إذا( ( puc + px_بلاک_منزل_داخل_کرو->x_بلاک_ناپ ) == ( uint8_t * ) ڈھیر_PROTECT_بلاک_اشارہ_گر( pxIterator->px_اگلا_Free_بلاک ) )
    {
        إذا( ڈھیر_PROTECT_بلاک_اشارہ_گر( pxIterator->px_اگلا_Free_بلاک ) != px_سرا )
        {
            /* Form one big block from the two blocks. */
            px_بلاک_منزل_داخل_کرو->x_بلاک_ناپ += ڈھیر_PROTECT_بلاک_اشارہ_گر( pxIterator->px_اگلا_Free_بلاک )->x_بلاک_ناپ;
            px_بلاک_منزل_داخل_کرو->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( pxIterator->px_اگلا_Free_بلاک )->px_اگلا_Free_بلاک;
        }
        وإلا
        {
            px_بلاک_منزل_داخل_کرو->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( px_سرا );
        }
    }
    وإلا
    {
        px_بلاک_منزل_داخل_کرو->px_اگلا_Free_بلاک = pxIterator->px_اگلا_Free_بلاک;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    إذا( pxIterator != px_بلاک_منزل_داخل_کرو )
    {
        pxIterator->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( px_بلاک_منزل_داخل_کرو );
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Define_ڈھیر_Regions( ثابت ڈھیر_Region_t * ثابت px_ڈھیر_Regions ) /* PRIVILEGED_FUNCTION */
{
    بلاک_Link_t * px_پہلا_Free_بلاک_وچ_Region = عدم;
    بلاک_Link_t * px_پچھلا_Free_بلاک;
    پورٹ_اشارہ_گر_ناپ_TYPE x_Aligned_ڈھیر;
    size_t x_کل_Region_ناپ, x_کل_ڈھیر_ناپ = 0;
    ادھار_Type_t xDefinedRegions = 0;
    پورٹ_اشارہ_گر_ناپ_TYPE x_پتہ;
    ثابت ڈھیر_Region_t * px_ڈھیر_Region;

    /* Can only call once! */
    configASSERT( px_سرا == عدم );

    #إذا ( config_ENABLE_ڈھیر_PROTECTOR == 1 )
    {
        v_Application_Get_Random_ڈھیر_Canary( &( x_ڈھیر_Canary ) );
    }
    #جے_انت

    px_ڈھیر_Region = &( px_ڈھیر_Regions[ xDefinedRegions ] );

    طالما( px_ڈھیر_Region->x_ناپ_وچ_بائٹاں > 0 )
    {
        x_کل_Region_ناپ = px_ڈھیر_Region->x_ناپ_وچ_بائٹاں;

        /* Ensure the heap region starts on a correctly aligned boundary. */
        x_پتہ = ( پورٹ_اشارہ_گر_ناپ_TYPE ) px_ڈھیر_Region->puc_شروع_پتہ;

        إذا( ( x_پتہ & پورٹ_BYTE_ALIGNMENT_نقاب ) != 0 )
        {
            x_پتہ += ( پورٹ_BYTE_ALIGNMENT - 1 );
            x_پتہ &= ~( پورٹ_اشارہ_گر_ناپ_TYPE ) پورٹ_BYTE_ALIGNMENT_نقاب;

            /* Adjust the size for the bytes lost to alignment. */
            x_کل_Region_ناپ -= ( size_t ) ( x_پتہ - ( پورٹ_اشارہ_گر_ناپ_TYPE ) px_ڈھیر_Region->puc_شروع_پتہ );
        }

        x_Aligned_ڈھیر = x_پتہ;

        /* Set xStart if it has not already been set. */
        إذا( xDefinedRegions == 0 )
        {
            /* xStart is used to hold a pointer to the first item in the list of
             *  free blocks.  The void cast is used to prevent compiler warnings. */
            x_شروع.px_اگلا_Free_بلاک = ( بلاک_Link_t * ) ڈھیر_PROTECT_بلاک_اشارہ_گر( x_Aligned_ڈھیر );
            x_شروع.x_بلاک_ناپ = ( size_t ) 0;
        }
        وإلا
        {
            /* Should only get here if one region has already been added to the
             * heap. */
            configASSERT( px_سرا != ڈھیر_PROTECT_بلاک_اشارہ_گر( عدم ) );

            /* Check blocks are passed in with increasing start addresses. */
            configASSERT( ( size_t ) x_پتہ > ( size_t ) px_سرا );
        }

        #إذا ( config_ENABLE_ڈھیر_PROTECTOR == 1 )
        {
            إذا( ( puc_ڈھیر_کم_پتہ == عدم ) ||
                ( ( uint8_t * ) x_Aligned_ڈھیر < puc_ڈھیر_کم_پتہ ) )
            {
                puc_ڈھیر_کم_پتہ = ( uint8_t * ) x_Aligned_ڈھیر;
            }
        }
        #جے_انت /* configENABLE_HEAP_PROTECTOR */

        /* Remember the location of the end marker in the previous region, if
         * any. */
        px_پچھلا_Free_بلاک = px_سرا;

        /* pxEnd is used to mark the end of the list of free blocks and is
         * inserted at the end of the region space. */
        x_پتہ = x_Aligned_ڈھیر + ( پورٹ_اشارہ_گر_ناپ_TYPE ) x_کل_Region_ناپ;
        x_پتہ -= ( پورٹ_اشارہ_گر_ناپ_TYPE ) x_ڈھیر_Struct_ناپ;
        x_پتہ &= ~( ( پورٹ_اشارہ_گر_ناپ_TYPE ) پورٹ_BYTE_ALIGNMENT_نقاب );
        px_سرا = ( بلاک_Link_t * ) x_پتہ;
        px_سرا->x_بلاک_ناپ = 0;
        px_سرا->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( عدم );

        /* To start with there is a single free block in this region that is
         * sized to take up the entire heap region minus the space taken by the
         * free block structure. */
        px_پہلا_Free_بلاک_وچ_Region = ( بلاک_Link_t * ) x_Aligned_ڈھیر;
        px_پہلا_Free_بلاک_وچ_Region->x_بلاک_ناپ = ( size_t ) ( x_پتہ - ( پورٹ_اشارہ_گر_ناپ_TYPE ) px_پہلا_Free_بلاک_وچ_Region );
        px_پہلا_Free_بلاک_وچ_Region->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( px_سرا );

        /* If this is not the first region that makes up the entire heap space
         * then link the previous region to this region. */
        إذا( px_پچھلا_Free_بلاک != عدم )
        {
            px_پچھلا_Free_بلاک->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( px_پہلا_Free_بلاک_وچ_Region );
        }

        x_کل_ڈھیر_ناپ += px_پہلا_Free_بلاک_وچ_Region->x_بلاک_ناپ;

        #إذا ( config_ENABLE_ڈھیر_PROTECTOR == 1 )
        {
            إذا( ( puc_ڈھیر_بلند_پتہ == عدم ) ||
                ( ( ( ( uint8_t * ) px_پہلا_Free_بلاک_وچ_Region ) + px_پہلا_Free_بلاک_وچ_Region->x_بلاک_ناپ ) > puc_ڈھیر_بلند_پتہ ) )
            {
                puc_ڈھیر_بلند_پتہ = ( ( uint8_t * ) px_پہلا_Free_بلاک_وچ_Region ) + px_پہلا_Free_بلاک_وچ_Region->x_بلاک_ناپ;
            }
        }
        #جے_انت

        /* Move onto the next HeapRegion_t structure. */
        xDefinedRegions++;
        px_ڈھیر_Region = &( px_ڈھیر_Regions[ xDefinedRegions ] );
    }

    x_Minimum_Ever_Free_بائٹاں_بچیا = x_کل_ڈھیر_ناپ;
    x_Free_بائٹاں_بچیا = x_کل_ڈھیر_ناپ;

    /* Check something was actually defined before it is accessed. */
    configASSERT( x_کل_ڈھیر_ناپ );
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Get_ڈھیر_Stats( ڈھیر_Stats_t * px_ڈھیر_Stats )
{
    بلاک_Link_t * px_بلاک;
    size_t x_بلاکاں = 0, x_Max_ناپ = 0, x_Min_ناپ = SIZE_MAX;

    vTaskSuspendAll();
    {
        px_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( x_شروع.px_اگلا_Free_بلاک );

        /* pxBlock will be NULL if the heap has not been initialised.  The heap
         * is initialised automatically when the first allocation is made. */
        إذا( px_بلاک != عدم )
        {
            طالما( px_بلاک != px_سرا )
            {
                /* Increment the number of blocks and record the largest block seen
                 * so far. */
                x_بلاکاں++;

                إذا( px_بلاک->x_بلاک_ناپ > x_Max_ناپ )
                {
                    x_Max_ناپ = px_بلاک->x_بلاک_ناپ;
                }

                /* Heap five will have a zero sized block at the end of each
                 * each region - the block is only used to link to the next
                 * heap region so it not a real block. */
                إذا( px_بلاک->x_بلاک_ناپ != 0 )
                {
                    إذا( px_بلاک->x_بلاک_ناپ < x_Min_ناپ )
                    {
                        x_Min_ناپ = px_بلاک->x_بلاک_ناپ;
                    }
                }

                /* Move to the next block in the chain until the last block is
                 * reached. */
                px_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( px_بلاک->px_اگلا_Free_بلاک );
            }
        }
    }
    ( فراغ ) xTaskResumeAll();

    px_ڈھیر_Stats->x_ناپ_دا_سبھ_توں_وڈا_Free_بلاک_وچ_بائٹاں = x_Max_ناپ;
    px_ڈھیر_Stats->x_ناپ_دا_سبھ_توں_چھوٹا_Free_بلاک_وچ_بائٹاں = x_Min_ناپ;
    px_ڈھیر_Stats->x_نمبر_دا_Free_بلاکاں = x_بلاکاں;

    taskENTER_CRITICAL();
    {
        px_ڈھیر_Stats->x_دستیاب_ڈھیر_Space_وچ_بائٹاں = x_Free_بائٹاں_بچیا;
        px_ڈھیر_Stats->x_نمبر_دا_Successful_Allocations = x_نمبر_دا_Successful_Allocations;
        px_ڈھیر_Stats->x_نمبر_دا_Successful_Frees = x_نمبر_دا_Successful_Frees;
        px_ڈھیر_Stats->x_Minimum_Ever_Free_بائٹاں_بچیا = x_Minimum_Ever_Free_بائٹاں_بچیا;
    }
    taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
فراغ v_پورٹ_ڈھیر_Reset_State( فراغ )
{
    px_سرا = عدم;

    x_Free_بائٹاں_بچیا = ( size_t ) 0U;
    x_Minimum_Ever_Free_بائٹاں_بچیا = ( size_t ) 0U;
    x_نمبر_دا_Successful_Allocations = ( size_t ) 0U;
    x_نمبر_دا_Successful_Frees = ( size_t ) 0U;

    #إذا ( config_ENABLE_ڈھیر_PROTECTOR == 1 )
        puc_ڈھیر_بلند_پتہ = عدم;
        puc_ڈھیر_کم_پتہ = عدم;
    #جے_انت /* #if ( configENABLE_HEAP_PROTECTOR == 1 ) */
}
/*-----------------------------------------------------------*/
