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
#تعریف_کن MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ضمن "FreeRTOS.h"
#ضمن "task.h"

#لغو_تعریف MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#إذا ( config_SUPPORT_DYNAMIC_تخصیص == 0 )
    #خطا This file must not be استفاده_شده إذا config_SUPPORT_DYNAMIC_تخصیص is 0
#پایان_اگر

#اگر_تعریف_نشده config_انباشته_CLEAR_حافظه_ON_FREE
    #تعریف_کن config_انباشته_CLEAR_حافظه_ON_FREE    0
#پایان_اگر

/* Block sizes must not get too small. */
#تعریف_کن انباشته_MINIMUM_بلوک_اندازه    ( ( size_t ) ( x_انباشته_Struct_اندازه << 1 ) )

/* Assumes 8bit bytes! */
#تعریف_کن انباشته_بیتها_در_هر_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#تعریف_کن انباشته_اندازه_MAX              ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#تعریف_کن انباشته_MULTIPLY_WILL_سرریز( a, b )     ( ( ( a ) > 0 ) && ( ( b ) > ( انباشته_اندازه_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کن انباشته_جمع_کن_WILL_سرریز( a, b )          ( ( a ) > ( انباشته_اندازه_MAX - ( b ) ) )

/* Check if the subtraction operation ( a - b ) will result in underflow. */
#تعریف_کن انباشته_تفریق_WILL_UNDERFLOW( a, b )    ( ( a ) < ( b ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#تعریف_کن انباشته_بلوک_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( حجم( size_t ) * انباشته_بیتها_در_هر_BYTE ) - 1 ) )
#تعریف_کن انباشته_بلوک_اندازه_IS_VALID( x_بلوک_اندازه )    ( ( ( x_بلوک_اندازه ) & انباشته_بلوک_ALLOCATED_BITMASK ) == 0 )
#تعریف_کن انباشته_بلوک_IS_ALLOCATED( px_بلوک )        ( ( ( px_بلوک->x_بلوک_اندازه ) & انباشته_بلوک_ALLOCATED_BITMASK ) != 0 )
#تعریف_کن انباشته_ALLOCATE_بلوک( px_بلوک )            ( ( px_بلوک->x_بلوک_اندازه ) |= انباشته_بلوک_ALLOCATED_BITMASK )
#تعریف_کن انباشته_FREE_بلوک( px_بلوک )                ( ( px_بلوک->x_بلوک_اندازه ) &= ~انباشته_بلوک_ALLOCATED_BITMASK )

/* Setting configENABLE_HEAP_PROTECTOR to 1 enables heap block pointers
 * protection using an application supplied canary value to catch heap
 * corruption should a heap buffer overflow occur.
 */
#إذا ( config_ENABLE_انباشته_PROTECTOR == 1 )

/* Macro to load/store BlockLink_t pointers to memory. By XORing the
 * pointers with a random canary value, heap overflows will result
 * in randomly unpredictable pointer values which will be caught by
 * heapVALIDATE_BLOCK_POINTER assert. */
    #تعریف_کن انباشته_PROTECT_بلوک_اشاره_گر( px_بلوک )    ( ( بلوک_Link_t * ) ( ( ( پورت_اشاره_گر_اندازه_TYPE ) ( px_بلوک ) ) ^ x_انباشته_Canary ) )

/* Assert that a heap block pointer is within the heap bounds.
 * Setting configVALIDATE_HEAP_BLOCK_POINTER to 1 enables customized heap block pointers
 * protection on heap_5. */
    #اگر_تعریف_نشده config_VALIDATE_انباشته_بلوک_اشاره_گر
        #تعریف_کن انباشته_VALIDATE_بلوک_اشاره_گر( px_بلوک )                           \
            configASSERT( ( puc_انباشته_بالا_آدرس != عدم ) &&                     \
                          ( puc_انباشته_کم_آدرس != عدم ) &&                      \
                          ( ( uint8_t * ) ( px_بلوک ) >= puc_انباشته_کم_آدرس ) && \
                          ( ( uint8_t * ) ( px_بلوک ) < puc_انباشته_بالا_آدرس ) )
    #وإلا /* ifndef configVALIDATE_HEAP_BLOCK_POINTER */
        #تعریف_کن انباشته_VALIDATE_بلوک_اشاره_گر( px_بلوک )                           \
            config_VALIDATE_انباشته_بلوک_اشاره_گر( px_بلوک )
    #پایان_اگر /* configVALIDATE_HEAP_BLOCK_POINTER */

#وإلا /* if ( configENABLE_HEAP_PROTECTOR == 1 ) */

    #تعریف_کن انباشته_PROTECT_بلوک_اشاره_گر( px_بلوک )    ( px_بلوک )

    #تعریف_کن انباشته_VALIDATE_بلوک_اشاره_گر( px_بلوک )

#پایان_اگر /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

/* Define the linked list structure.  This is used to link free blocks in order
 * of their memory address. */
تعريفنوع بنية A_بلوک_LINK
{
    بنية A_بلوک_LINK * px_بعدی_Free_بلوک; /**< The next free block in the list. */
    size_t x_بلوک_اندازه;                     /**< The size of the free block. */
} بلوک_Link_t;

/*-----------------------------------------------------------*/

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
ساكن فراغ prv_درج_بلوک_Into_Free_List( بلوک_Link_t * px_بلوک_مقصد_درج ) PRIVILEGED_FUNCTION;
فراغ v_پورت_Define_انباشته_Regions( ثابت انباشته_Region_t * ثابت px_انباشته_Regions ) PRIVILEGED_FUNCTION;

#إذا ( config_ENABLE_انباشته_PROTECTOR == 1 )

/**
 * @brief Application provided function to get a random value to be used as canary.
 *
 * @param pxHeapCanary [out] Output parameter to return the canary value.
 */
    خارجي فراغ v_Application_Get_Random_انباشته_Canary( پورت_اشاره_گر_اندازه_TYPE * px_انباشته_Canary );
#پایان_اگر /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

/* The size of the structure placed at the beginning of each allocated memory
 * block must by correctly byte aligned. */
ساكن ثابت size_t x_انباشته_Struct_اندازه = ( حجم( بلوک_Link_t ) + ( ( size_t ) ( پورت_BYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) پورت_BYTE_ALIGNMENT_ماسک );

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_داده ساكن بلوک_Link_t x_شروع;
PRIVILEGED_داده ساكن بلوک_Link_t * px_انتها = عدم;

/* Keeps track of the number of calls to allocate and free memory as well as the
 * number of free bytes remaining, but says nothing about fragmentation. */
PRIVILEGED_داده ساكن size_t x_Free_بایتها_مانده = ( size_t ) 0U;
PRIVILEGED_داده ساكن size_t x_Minimum_Ever_Free_بایتها_مانده = ( size_t ) 0U;
PRIVILEGED_داده ساكن size_t x_عدد_از_Successful_Allocations = ( size_t ) 0U;
PRIVILEGED_داده ساكن size_t x_عدد_از_Successful_Frees = ( size_t ) 0U;

#إذا ( config_ENABLE_انباشته_PROTECTOR == 1 )

/* Canary value for protecting internal heap pointers. */
    PRIVILEGED_داده ساكن پورت_اشاره_گر_اندازه_TYPE x_انباشته_Canary;

/* Highest and lowest heap addresses used for heap block bounds checking. */
    PRIVILEGED_داده ساكن uint8_t * puc_انباشته_بالا_آدرس = عدم;
    PRIVILEGED_داده ساكن uint8_t * puc_انباشته_کم_آدرس = عدم;

#پایان_اگر /* configENABLE_HEAP_PROTECTOR */

/*-----------------------------------------------------------*/

فراغ * pv_پورت_Malloc( size_t x_Wanted_اندازه )
{
    بلوک_Link_t * px_بلوک;
    بلوک_Link_t * px_قبلی_بلوک;
    بلوک_Link_t * px_New_بلوک_Link;
    فراغ * pvReturn = عدم;
    size_t x_Additional_Required_اندازه;
    size_t x_Allocated_بلوک_اندازه = 0;

    /* The heap must be initialised before the first call to
     * pvPortMalloc(). */
    configASSERT( px_انتها );

    إذا( x_Wanted_اندازه > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        إذا( انباشته_جمع_کن_WILL_سرریز( x_Wanted_اندازه, x_انباشته_Struct_اندازه ) == 0 )
        {
            x_Wanted_اندازه += x_انباشته_Struct_اندازه;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            إذا( ( x_Wanted_اندازه & پورت_BYTE_ALIGNMENT_ماسک ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_اندازه = پورت_BYTE_ALIGNMENT - ( x_Wanted_اندازه & پورت_BYTE_ALIGNMENT_ماسک );

                إذا( انباشته_جمع_کن_WILL_سرریز( x_Wanted_اندازه, x_Additional_Required_اندازه ) == 0 )
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

    vTaskSuspendAll();
    {
        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        إذا( انباشته_بلوک_اندازه_IS_VALID( x_Wanted_اندازه ) != 0 )
        {
            إذا( ( x_Wanted_اندازه > 0 ) && ( x_Wanted_اندازه <= x_Free_بایتها_مانده ) )
            {
                /* Traverse the list from the start (lowest address) block until
                 * one of adequate size is found. */
                px_قبلی_بلوک = &x_شروع;
                px_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( x_شروع.px_بعدی_Free_بلوک );
                انباشته_VALIDATE_بلوک_اشاره_گر( px_بلوک );

                طالما( ( px_بلوک->x_بلوک_اندازه < x_Wanted_اندازه ) && ( px_بلوک->px_بعدی_Free_بلوک != انباشته_PROTECT_بلوک_اشاره_گر( عدم ) ) )
                {
                    px_قبلی_بلوک = px_بلوک;
                    px_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( px_بلوک->px_بعدی_Free_بلوک );

                    /* pxEnd is the end marker of the free list. It is located at
                     * pucHeapHighAddress and is not part of the usable heap, so it
                     * must be excluded from the heap block pointer validation. */
                    إذا( px_بلوک != px_انتها )
                    {
                        انباشته_VALIDATE_بلوک_اشاره_گر( px_بلوک );
                    }
                }

                /* If the end marker was reached then a block of adequate size
                 * was not found. */
                إذا( px_بلوک != px_انتها )
                {
                    /* Return the memory space pointed to - jumping over the
                     * BlockLink_t structure at its start. */
                    pvReturn = ( فراغ * ) ( ( ( uint8_t * ) انباشته_PROTECT_بلوک_اشاره_گر( px_قبلی_بلوک->px_بعدی_Free_بلوک ) ) + x_انباشته_Struct_اندازه );
                    انباشته_VALIDATE_بلوک_اشاره_گر( pvReturn );

                    /* This block is being returned for use so must be taken out
                     * of the list of free blocks. */
                    px_قبلی_بلوک->px_بعدی_Free_بلوک = px_بلوک->px_بعدی_Free_بلوک;

                    /* If the block is larger than required it can be split into
                     * two. */
                    configASSERT( انباشته_تفریق_WILL_UNDERFLOW( px_بلوک->x_بلوک_اندازه, x_Wanted_اندازه ) == 0 );

                    إذا( ( px_بلوک->x_بلوک_اندازه - x_Wanted_اندازه ) > انباشته_MINIMUM_بلوک_اندازه )
                    {
                        /* This block is to be split into two.  Create a new
                         * block following the number of bytes requested. The void
                         * cast is used to prevent byte alignment warnings from the
                         * compiler. */
                        px_New_بلوک_Link = ( فراغ * ) ( ( ( uint8_t * ) px_بلوک ) + x_Wanted_اندازه );
                        configASSERT( ( ( ( size_t ) px_New_بلوک_Link ) & پورت_BYTE_ALIGNMENT_ماسک ) == 0 );

                        /* Calculate the sizes of two blocks split from the
                         * single block. */
                        px_New_بلوک_Link->x_بلوک_اندازه = px_بلوک->x_بلوک_اندازه - x_Wanted_اندازه;
                        px_بلوک->x_بلوک_اندازه = x_Wanted_اندازه;

                        /* Insert the new block into the list of free blocks. */
                        px_New_بلوک_Link->px_بعدی_Free_بلوک = px_قبلی_بلوک->px_بعدی_Free_بلوک;
                        px_قبلی_بلوک->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( px_New_بلوک_Link );
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

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    انباشته_ALLOCATE_بلوک( px_بلوک );
                    px_بلوک->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( عدم );
                    x_عدد_از_Successful_Allocations++;
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
    #پایان_اگر /* if ( configUSE_MALLOC_FAILED_HOOK == 1 ) */

    configASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) پورت_BYTE_ALIGNMENT_ماسک ) == 0 );
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

        انباشته_VALIDATE_بلوک_اشاره_گر( pxLink );
        configASSERT( انباشته_بلوک_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_بعدی_Free_بلوک == انباشته_PROTECT_بلوک_اشاره_گر( عدم ) );

        إذا( انباشته_بلوک_IS_ALLOCATED( pxLink ) != 0 )
        {
            إذا( pxLink->px_بعدی_Free_بلوک == انباشته_PROTECT_بلوک_اشاره_گر( عدم ) )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                انباشته_FREE_بلوک( pxLink );
                #إذا ( config_انباشته_CLEAR_حافظه_ON_FREE == 1 )
                {
                    /* Check for underflow as this can occur if xBlockSize is
                     * overwritten in a heap block. */
                    إذا( انباشته_تفریق_WILL_UNDERFLOW( pxLink->x_بلوک_اندازه, x_انباشته_Struct_اندازه ) == 0 )
                    {
                        ( فراغ ) memset( puc + x_انباشته_Struct_اندازه, 0, pxLink->x_بلوک_اندازه - x_انباشته_Struct_اندازه );
                    }
                }
                #پایان_اگر

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_بایتها_مانده += pxLink->x_بلوک_اندازه;
                    traceFREE( pv, pxLink->x_بلوک_اندازه );
                    prv_درج_بلوک_Into_Free_List( ( ( بلوک_Link_t * ) pxLink ) );
                    x_عدد_از_Successful_Frees++;
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

فراغ x_پورت_Reset_انباشته_Minimum_Ever_Free_انباشته_اندازه( فراغ )
{
    x_Minimum_Ever_Free_بایتها_مانده = x_Free_بایتها_مانده;
}
/*-----------------------------------------------------------*/

فراغ * pv_پورت_Calloc( size_t x_رقم,
                     size_t x_اندازه )
{
    فراغ * pv = عدم;

    إذا( انباشته_MULTIPLY_WILL_سرریز( x_رقم, x_اندازه ) == 0 )
    {
        pv = pv_پورت_Malloc( x_رقم * x_اندازه );

        إذا( pv != عدم )
        {
            ( فراغ ) memset( pv, 0, x_رقم * x_اندازه );
        }
    }

    أرجع pv;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_درج_بلوک_Into_Free_List( بلوک_Link_t * px_بلوک_مقصد_درج ) /* PRIVILEGED_FUNCTION */
{
    بلوک_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    لكل( pxIterator = &x_شروع; انباشته_PROTECT_بلوک_اشاره_گر( pxIterator->px_بعدی_Free_بلوک ) < px_بلوک_مقصد_درج; pxIterator = انباشته_PROTECT_بلوک_اشاره_گر( pxIterator->px_بعدی_Free_بلوک ) )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    إذا( pxIterator != &x_شروع )
    {
        انباشته_VALIDATE_بلوک_اشاره_گر( pxIterator );
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

    إذا( ( puc + px_بلوک_مقصد_درج->x_بلوک_اندازه ) == ( uint8_t * ) انباشته_PROTECT_بلوک_اشاره_گر( pxIterator->px_بعدی_Free_بلوک ) )
    {
        إذا( انباشته_PROTECT_بلوک_اشاره_گر( pxIterator->px_بعدی_Free_بلوک ) != px_انتها )
        {
            /* Form one big block from the two blocks. */
            px_بلوک_مقصد_درج->x_بلوک_اندازه += انباشته_PROTECT_بلوک_اشاره_گر( pxIterator->px_بعدی_Free_بلوک )->x_بلوک_اندازه;
            px_بلوک_مقصد_درج->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( pxIterator->px_بعدی_Free_بلوک )->px_بعدی_Free_بلوک;
        }
        وإلا
        {
            px_بلوک_مقصد_درج->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( px_انتها );
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
        pxIterator->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( px_بلوک_مقصد_درج );
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Define_انباشته_Regions( ثابت انباشته_Region_t * ثابت px_انباشته_Regions ) /* PRIVILEGED_FUNCTION */
{
    بلوک_Link_t * px_اولی_Free_بلوک_درون_Region = عدم;
    بلوک_Link_t * px_قبلی_Free_بلوک;
    پورت_اشاره_گر_اندازه_TYPE x_Aligned_انباشته;
    size_t x_مجموع_Region_اندازه, x_مجموع_انباشته_اندازه = 0;
    پایه_Type_t xDefinedRegions = 0;
    پورت_اشاره_گر_اندازه_TYPE x_آدرس;
    ثابت انباشته_Region_t * px_انباشته_Region;

    /* Can only call once! */
    configASSERT( px_انتها == عدم );

    #إذا ( config_ENABLE_انباشته_PROTECTOR == 1 )
    {
        v_Application_Get_Random_انباشته_Canary( &( x_انباشته_Canary ) );
    }
    #پایان_اگر

    px_انباشته_Region = &( px_انباشته_Regions[ xDefinedRegions ] );

    طالما( px_انباشته_Region->x_اندازه_درون_بایتها > 0 )
    {
        x_مجموع_Region_اندازه = px_انباشته_Region->x_اندازه_درون_بایتها;

        /* Ensure the heap region starts on a correctly aligned boundary. */
        x_آدرس = ( پورت_اشاره_گر_اندازه_TYPE ) px_انباشته_Region->puc_شروع_آدرس;

        إذا( ( x_آدرس & پورت_BYTE_ALIGNMENT_ماسک ) != 0 )
        {
            x_آدرس += ( پورت_BYTE_ALIGNMENT - 1 );
            x_آدرس &= ~( پورت_اشاره_گر_اندازه_TYPE ) پورت_BYTE_ALIGNMENT_ماسک;

            /* Adjust the size for the bytes lost to alignment. */
            x_مجموع_Region_اندازه -= ( size_t ) ( x_آدرس - ( پورت_اشاره_گر_اندازه_TYPE ) px_انباشته_Region->puc_شروع_آدرس );
        }

        x_Aligned_انباشته = x_آدرس;

        /* Set xStart if it has not already been set. */
        إذا( xDefinedRegions == 0 )
        {
            /* xStart is used to hold a pointer to the first item in the list of
             *  free blocks.  The void cast is used to prevent compiler warnings. */
            x_شروع.px_بعدی_Free_بلوک = ( بلوک_Link_t * ) انباشته_PROTECT_بلوک_اشاره_گر( x_Aligned_انباشته );
            x_شروع.x_بلوک_اندازه = ( size_t ) 0;
        }
        وإلا
        {
            /* Should only get here if one region has already been added to the
             * heap. */
            configASSERT( px_انتها != انباشته_PROTECT_بلوک_اشاره_گر( عدم ) );

            /* Check blocks are passed in with increasing start addresses. */
            configASSERT( ( size_t ) x_آدرس > ( size_t ) px_انتها );
        }

        #إذا ( config_ENABLE_انباشته_PROTECTOR == 1 )
        {
            إذا( ( puc_انباشته_کم_آدرس == عدم ) ||
                ( ( uint8_t * ) x_Aligned_انباشته < puc_انباشته_کم_آدرس ) )
            {
                puc_انباشته_کم_آدرس = ( uint8_t * ) x_Aligned_انباشته;
            }
        }
        #پایان_اگر /* configENABLE_HEAP_PROTECTOR */

        /* Remember the location of the end marker in the previous region, if
         * any. */
        px_قبلی_Free_بلوک = px_انتها;

        /* pxEnd is used to mark the end of the list of free blocks and is
         * inserted at the end of the region space. */
        x_آدرس = x_Aligned_انباشته + ( پورت_اشاره_گر_اندازه_TYPE ) x_مجموع_Region_اندازه;
        x_آدرس -= ( پورت_اشاره_گر_اندازه_TYPE ) x_انباشته_Struct_اندازه;
        x_آدرس &= ~( ( پورت_اشاره_گر_اندازه_TYPE ) پورت_BYTE_ALIGNMENT_ماسک );
        px_انتها = ( بلوک_Link_t * ) x_آدرس;
        px_انتها->x_بلوک_اندازه = 0;
        px_انتها->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( عدم );

        /* To start with there is a single free block in this region that is
         * sized to take up the entire heap region minus the space taken by the
         * free block structure. */
        px_اولی_Free_بلوک_درون_Region = ( بلوک_Link_t * ) x_Aligned_انباشته;
        px_اولی_Free_بلوک_درون_Region->x_بلوک_اندازه = ( size_t ) ( x_آدرس - ( پورت_اشاره_گر_اندازه_TYPE ) px_اولی_Free_بلوک_درون_Region );
        px_اولی_Free_بلوک_درون_Region->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( px_انتها );

        /* If this is not the first region that makes up the entire heap space
         * then link the previous region to this region. */
        إذا( px_قبلی_Free_بلوک != عدم )
        {
            px_قبلی_Free_بلوک->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( px_اولی_Free_بلوک_درون_Region );
        }

        x_مجموع_انباشته_اندازه += px_اولی_Free_بلوک_درون_Region->x_بلوک_اندازه;

        #إذا ( config_ENABLE_انباشته_PROTECTOR == 1 )
        {
            إذا( ( puc_انباشته_بالا_آدرس == عدم ) ||
                ( ( ( ( uint8_t * ) px_اولی_Free_بلوک_درون_Region ) + px_اولی_Free_بلوک_درون_Region->x_بلوک_اندازه ) > puc_انباشته_بالا_آدرس ) )
            {
                puc_انباشته_بالا_آدرس = ( ( uint8_t * ) px_اولی_Free_بلوک_درون_Region ) + px_اولی_Free_بلوک_درون_Region->x_بلوک_اندازه;
            }
        }
        #پایان_اگر

        /* Move onto the next HeapRegion_t structure. */
        xDefinedRegions++;
        px_انباشته_Region = &( px_انباشته_Regions[ xDefinedRegions ] );
    }

    x_Minimum_Ever_Free_بایتها_مانده = x_مجموع_انباشته_اندازه;
    x_Free_بایتها_مانده = x_مجموع_انباشته_اندازه;

    /* Check something was actually defined before it is accessed. */
    configASSERT( x_مجموع_انباشته_اندازه );
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Get_انباشته_Stats( انباشته_Stats_t * px_انباشته_Stats )
{
    بلوک_Link_t * px_بلوک;
    size_t x_بلوکها = 0, x_Max_اندازه = 0, x_Min_اندازه = SIZE_MAX;

    vTaskSuspendAll();
    {
        px_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( x_شروع.px_بعدی_Free_بلوک );

        /* pxBlock will be NULL if the heap has not been initialised.  The heap
         * is initialised automatically when the first allocation is made. */
        إذا( px_بلوک != عدم )
        {
            طالما( px_بلوک != px_انتها )
            {
                /* Increment the number of blocks and record the largest block seen
                 * so far. */
                x_بلوکها++;

                إذا( px_بلوک->x_بلوک_اندازه > x_Max_اندازه )
                {
                    x_Max_اندازه = px_بلوک->x_بلوک_اندازه;
                }

                /* Heap five will have a zero sized block at the end of each
                 * each region - the block is only used to link to the next
                 * heap region so it not a real block. */
                إذا( px_بلوک->x_بلوک_اندازه != 0 )
                {
                    إذا( px_بلوک->x_بلوک_اندازه < x_Min_اندازه )
                    {
                        x_Min_اندازه = px_بلوک->x_بلوک_اندازه;
                    }
                }

                /* Move to the next block in the chain until the last block is
                 * reached. */
                px_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( px_بلوک->px_بعدی_Free_بلوک );
            }
        }
    }
    ( فراغ ) xTaskResumeAll();

    px_انباشته_Stats->x_اندازه_از_بزرگترین_Free_بلوک_درون_بایتها = x_Max_اندازه;
    px_انباشته_Stats->x_اندازه_از_کوچکترین_Free_بلوک_درون_بایتها = x_Min_اندازه;
    px_انباشته_Stats->x_عدد_از_Free_بلوکها = x_بلوکها;

    taskENTER_CRITICAL();
    {
        px_انباشته_Stats->x_موجود_انباشته_Space_درون_بایتها = x_Free_بایتها_مانده;
        px_انباشته_Stats->x_عدد_از_Successful_Allocations = x_عدد_از_Successful_Allocations;
        px_انباشته_Stats->x_عدد_از_Successful_Frees = x_عدد_از_Successful_Frees;
        px_انباشته_Stats->x_Minimum_Ever_Free_بایتها_مانده = x_Minimum_Ever_Free_بایتها_مانده;
    }
    taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
فراغ v_پورت_انباشته_Reset_State( فراغ )
{
    px_انتها = عدم;

    x_Free_بایتها_مانده = ( size_t ) 0U;
    x_Minimum_Ever_Free_بایتها_مانده = ( size_t ) 0U;
    x_عدد_از_Successful_Allocations = ( size_t ) 0U;
    x_عدد_از_Successful_Frees = ( size_t ) 0U;

    #إذا ( config_ENABLE_انباشته_PROTECTOR == 1 )
        puc_انباشته_بالا_آدرس = عدم;
        puc_انباشته_کم_آدرس = عدم;
    #پایان_اگر /* #if ( configENABLE_HEAP_PROTECTOR == 1 ) */
}
/*-----------------------------------------------------------*/
