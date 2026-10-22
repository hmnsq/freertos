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
 * A sample implementation of pvPortMalloc() and vPortFree() that permits
 * allocated blocks to be freed, but does not combine adjacent free blocks
 * into a single larger block (and so will fragment memory).  See heap_4.c for
 * an equivalent that does combine adjacent blocks into single larger blocks.
 *
 * See heap_1.c, heap_3.c and heap_4.c for alternative implementations, and the
 * memory management pages of https://www.FreeRTOS.org for more information.
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

/* A few bytes might be lost to byte aligning the heap start address. */
#تعریف_کن config_ADJUSTED_انباشته_اندازه    ( config_مجموع_انباشته_اندازه - پورت_BYTE_ALIGNMENT )

/* Assumes 8bit bytes! */
#تعریف_کن انباشته_بیتها_در_هر_BYTE           ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#تعریف_کن انباشته_اندازه_MAX                ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#تعریف_کن انباشته_MULTIPLY_WILL_سرریز( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( انباشته_اندازه_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کن انباشته_جمع_کن_WILL_سرریز( a, b )         ( ( a ) > ( انباشته_اندازه_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#تعریف_کن انباشته_بلوک_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( حجم( size_t ) * انباشته_بیتها_در_هر_BYTE ) - 1 ) )
#تعریف_کن انباشته_بلوک_اندازه_IS_VALID( x_بلوک_اندازه )    ( ( ( x_بلوک_اندازه ) & انباشته_بلوک_ALLOCATED_BITMASK ) == 0 )
#تعریف_کن انباشته_بلوک_IS_ALLOCATED( px_بلوک )        ( ( ( px_بلوک->x_بلوک_اندازه ) & انباشته_بلوک_ALLOCATED_BITMASK ) != 0 )
#تعریف_کن انباشته_ALLOCATE_بلوک( px_بلوک )            ( ( px_بلوک->x_بلوک_اندازه ) |= انباشته_بلوک_ALLOCATED_BITMASK )
#تعریف_کن انباشته_FREE_بلوک( px_بلوک )                ( ( px_بلوک->x_بلوک_اندازه ) &= ~انباشته_بلوک_ALLOCATED_BITMASK )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#إذا ( config_APPLICATION_ALLOCATED_انباشته == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    خارجي uint8_t uc_انباشته[ config_مجموع_انباشته_اندازه ];
#وإلا
    PRIVILEGED_داده ساكن uint8_t uc_انباشته[ config_مجموع_انباشته_اندازه ];
#پایان_اگر /* configAPPLICATION_ALLOCATED_HEAP */


/* Define the linked list structure.  This is used to link free blocks in order
 * of their size. */
تعريفنوع بنية A_بلوک_LINK
{
    بنية A_بلوک_LINK * px_بعدی_Free_بلوک; /*<< The next free block in the list. */
    size_t x_بلوک_اندازه;                     /*<< The size of the free block. */
} بلوک_Link_t;


ساكن ثابت size_t x_انباشته_Struct_اندازه = ( ( حجم( بلوک_Link_t ) + ( size_t ) ( پورت_BYTE_ALIGNMENT - 1 ) ) & ~( ( size_t ) پورت_BYTE_ALIGNMENT_ماسک ) );
#تعریف_کن انباشته_MINIMUM_بلوک_اندازه    ( ( size_t ) ( x_انباشته_Struct_اندازه * 2 ) )

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_داده ساكن بلوک_Link_t x_شروع, x_انتها;

/* Keeps track of the number of free bytes remaining, but says nothing about
 * fragmentation. */
PRIVILEGED_داده ساكن size_t x_Free_بایتها_مانده = config_ADJUSTED_انباشته_اندازه;

/* Indicates whether the heap has been initialised or not. */
PRIVILEGED_داده ساكن پایه_Type_t x_انباشته_Has_Been_Initialised = pdFALSE;

/*-----------------------------------------------------------*/

/*
 * Initialises the heap structures before their first use.
 */
ساكن فراغ prv_انباشته_Init( فراغ ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* STATIC FUNCTIONS ARE DEFINED AS MACROS TO MINIMIZE THE FUNCTION CALL DEPTH. */

/*
 * Insert a block into the list of free blocks - which is ordered by size of
 * the block.  Small blocks at the start of the list and large blocks at the end
 * of the list.
 */
#تعریف_کن prv_درج_بلوک_Into_Free_List( px_بلوک_مقصد_درج )                                                                               \
    {                                                                                                                               \
        بلوک_Link_t * pxIterator;                                                                                                   \
        size_t x_بلوک_اندازه;                                                                                                          \
                                                                                                                                    \
        x_بلوک_اندازه = px_بلوک_مقصد_درج->x_بلوک_اندازه;                                                                                   \
                                                                                                                                    \
        /* Iterate through the list until a block is found that has a larger size */                                                \
        /* than the block we are inserting. */                                                                                      \
        لكل( pxIterator = &x_شروع; pxIterator->px_بعدی_Free_بلوک->x_بلوک_اندازه < x_بلوک_اندازه; pxIterator = pxIterator->px_بعدی_Free_بلوک ) \
        {                                                                                                                           \
            /* There is nothing to do here - just iterate to the correct position. */                                               \
        }                                                                                                                           \
                                                                                                                                    \
        /* Update the list to include the block being inserted in the correct */                                                    \
        /* position. */                                                                                                             \
        px_بلوک_مقصد_درج->px_بعدی_Free_بلوک = pxIterator->px_بعدی_Free_بلوک;                                                             \
        pxIterator->px_بعدی_Free_بلوک = px_بلوک_مقصد_درج;                                                                              \
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
        /* If this is the first call to malloc then the heap will require
         * initialisation to setup the list of free blocks. */
        إذا( x_انباشته_Has_Been_Initialised == pdFALSE )
        {
            prv_انباشته_Init();
            x_انباشته_Has_Been_Initialised = pdTRUE;
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        إذا( انباشته_بلوک_اندازه_IS_VALID( x_Wanted_اندازه ) != 0 )
        {
            إذا( ( x_Wanted_اندازه > 0 ) && ( x_Wanted_اندازه <= x_Free_بایتها_مانده ) )
            {
                /* Blocks are stored in byte order - traverse the list from the start
                 * (smallest) block until one of adequate size is found. */
                px_قبلی_بلوک = &x_شروع;
                px_بلوک = x_شروع.px_بعدی_Free_بلوک;

                طالما( ( px_بلوک->x_بلوک_اندازه < x_Wanted_اندازه ) && ( px_بلوک->px_بعدی_Free_بلوک != عدم ) )
                {
                    px_قبلی_بلوک = px_بلوک;
                    px_بلوک = px_بلوک->px_بعدی_Free_بلوک;
                }

                /* If we found the end marker then a block of adequate size was not found. */
                إذا( px_بلوک != &x_انتها )
                {
                    /* Return the memory space - jumping over the BlockLink_t structure
                     * at its start. */
                    pvReturn = ( فراغ * ) ( ( ( uint8_t * ) px_قبلی_بلوک->px_بعدی_Free_بلوک ) + x_انباشته_Struct_اندازه );

                    /* This block is being returned for use so must be taken out of the
                     * list of free blocks. */
                    px_قبلی_بلوک->px_بعدی_Free_بلوک = px_بلوک->px_بعدی_Free_بلوک;

                    /* If the block is larger than required it can be split into two. */
                    إذا( ( px_بلوک->x_بلوک_اندازه - x_Wanted_اندازه ) > انباشته_MINIMUM_بلوک_اندازه )
                    {
                        /* This block is to be split into two.  Create a new block
                         * following the number of bytes requested. The void cast is
                         * used to prevent byte alignment warnings from the compiler. */
                        px_New_بلوک_Link = ( فراغ * ) ( ( ( uint8_t * ) px_بلوک ) + x_Wanted_اندازه );

                        /* Calculate the sizes of two blocks split from the single
                         * block. */
                        px_New_بلوک_Link->x_بلوک_اندازه = px_بلوک->x_بلوک_اندازه - x_Wanted_اندازه;
                        px_بلوک->x_بلوک_اندازه = x_Wanted_اندازه;

                        /* Insert the new block into the list of free blocks.
                         * The list of free blocks is sorted by their size, we have to
                         * iterate to find the right place to insert new block. */
                        prv_درج_بلوک_Into_Free_List( ( px_New_بلوک_Link ) );
                    }

                    x_Free_بایتها_مانده -= px_بلوک->x_بلوک_اندازه;

                    x_Allocated_بلوک_اندازه = px_بلوک->x_بلوک_اندازه;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    انباشته_ALLOCATE_بلوک( px_بلوک );
                    px_بلوک->px_بعدی_Free_بلوک = عدم;
                }
            }
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
    }
    #پایان_اگر

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

        /* This unexpected casting is to keep some compilers from issuing
         * byte alignment warnings. */
        pxLink = ( فراغ * ) puc;

        configASSERT( انباشته_بلوک_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_بعدی_Free_بلوک == عدم );

        إذا( انباشته_بلوک_IS_ALLOCATED( pxLink ) != 0 )
        {
            إذا( pxLink->px_بعدی_Free_بلوک == عدم )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                انباشته_FREE_بلوک( pxLink );
                #إذا ( config_انباشته_CLEAR_حافظه_ON_FREE == 1 )
                {
                    ( فراغ ) memset( puc + x_انباشته_Struct_اندازه, 0, pxLink->x_بلوک_اندازه - x_انباشته_Struct_اندازه );
                }
                #پایان_اگر

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    prv_درج_بلوک_Into_Free_List( ( ( بلوک_Link_t * ) pxLink ) );
                    x_Free_بایتها_مانده += pxLink->x_بلوک_اندازه;
                    traceFREE( pv, pxLink->x_بلوک_اندازه );
                }
                ( فراغ ) xTaskResumeAll();
            }
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_پورت_Get_Free_انباشته_اندازه( فراغ )
{
    أرجع x_Free_بایتها_مانده;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Initialise_بلوکها( فراغ )
{
    /* This just exists to keep the linker quiet. */
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

ساكن فراغ prv_انباشته_Init( فراغ ) /* PRIVILEGED_FUNCTION */
{
    بلوک_Link_t * px_اولی_Free_بلوک;
    uint8_t * puc_Aligned_انباشته;

    /* Ensure the heap starts on a correctly aligned boundary. */
    puc_Aligned_انباشته = ( uint8_t * ) ( ( ( پورت_اشاره_گر_اندازه_TYPE ) & uc_انباشته[ پورت_BYTE_ALIGNMENT - 1 ] ) & ( ~( ( پورت_اشاره_گر_اندازه_TYPE ) پورت_BYTE_ALIGNMENT_ماسک ) ) );

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_شروع.px_بعدی_Free_بلوک = ( فراغ * ) puc_Aligned_انباشته;
    x_شروع.x_بلوک_اندازه = ( size_t ) 0;

    /* xEnd is used to mark the end of the list of free blocks. */
    x_انتها.x_بلوک_اندازه = config_ADJUSTED_انباشته_اندازه;
    x_انتها.px_بعدی_Free_بلوک = عدم;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space. */
    px_اولی_Free_بلوک = ( بلوک_Link_t * ) puc_Aligned_انباشته;
    px_اولی_Free_بلوک->x_بلوک_اندازه = config_ADJUSTED_انباشته_اندازه;
    px_اولی_Free_بلوک->px_بعدی_Free_بلوک = &x_انتها;
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
فراغ v_پورت_انباشته_Reset_State( فراغ )
{
    x_Free_بایتها_مانده = config_ADJUSTED_انباشته_اندازه;

    x_انباشته_Has_Been_Initialised = pdFALSE;
}
/*-----------------------------------------------------------*/
