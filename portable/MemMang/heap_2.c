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
#تعریف_کړه MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ضمن "FreeRTOS.h"
#ضمن "task.h"

#تعریف_لغوه MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#إذا ( config_SUPPORT_DYNAMIC_ویش == 0 )
    #تېروتنه This file must not be کارول_شوی إذا config_SUPPORT_DYNAMIC_ویش is 0
#د_که_پای

#که_نه_تعریف_شوی config_ډېرۍ_CLEAR_حافظه_ON_FREE
    #تعریف_کړه config_ډېرۍ_CLEAR_حافظه_ON_FREE    0
#د_که_پای

/* A few bytes might be lost to byte aligning the heap start address. */
#تعریف_کړه config_ADJUSTED_ډېرۍ_اندازه    ( config_ټول_ډېرۍ_اندازه - پورټ_BYTE_ALIGNMENT )

/* Assumes 8bit bytes! */
#تعریف_کړه ډېرۍ_بټونه_فی_BYTE           ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#تعریف_کړه ډېرۍ_اندازه_MAX                ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#تعریف_کړه ډېرۍ_MULTIPLY_WILL_ډکېدنه( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( ډېرۍ_اندازه_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کړه ډېرۍ_جمع_کړه_WILL_ډکېدنه( a, b )         ( ( a ) > ( ډېرۍ_اندازه_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#تعریف_کړه ډېرۍ_بلاک_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( حجم( size_t ) * ډېرۍ_بټونه_فی_BYTE ) - 1 ) )
#تعریف_کړه ډېرۍ_بلاک_اندازه_IS_VALID( x_بلاک_اندازه )    ( ( ( x_بلاک_اندازه ) & ډېرۍ_بلاک_ALLOCATED_BITMASK ) == 0 )
#تعریف_کړه ډېرۍ_بلاک_IS_ALLOCATED( px_بلاک )        ( ( ( px_بلاک->x_بلاک_اندازه ) & ډېرۍ_بلاک_ALLOCATED_BITMASK ) != 0 )
#تعریف_کړه ډېرۍ_ALLOCATE_بلاک( px_بلاک )            ( ( px_بلاک->x_بلاک_اندازه ) |= ډېرۍ_بلاک_ALLOCATED_BITMASK )
#تعریف_کړه ډېرۍ_FREE_بلاک( px_بلاک )                ( ( px_بلاک->x_بلاک_اندازه ) &= ~ډېرۍ_بلاک_ALLOCATED_BITMASK )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#إذا ( config_APPLICATION_ALLOCATED_ډېرۍ == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    خارجي uint8_t uc_ډېرۍ[ config_ټول_ډېرۍ_اندازه ];
#وإلا
    PRIVILEGED_معلومات ساكن uint8_t uc_ډېرۍ[ config_ټول_ډېرۍ_اندازه ];
#د_که_پای /* configAPPLICATION_ALLOCATED_HEAP */


/* Define the linked list structure.  This is used to link free blocks in order
 * of their size. */
تعريفنوع بنية A_بلاک_LINK
{
    بنية A_بلاک_LINK * px_بل_Free_بلاک; /*<< The next free block in the list. */
    size_t x_بلاک_اندازه;                     /*<< The size of the free block. */
} بلاک_Link_t;


ساكن ثابت size_t x_ډېرۍ_Struct_اندازه = ( ( حجم( بلاک_Link_t ) + ( size_t ) ( پورټ_BYTE_ALIGNMENT - 1 ) ) & ~( ( size_t ) پورټ_BYTE_ALIGNMENT_ماسک ) );
#تعریف_کړه ډېرۍ_MINIMUM_بلاک_اندازه    ( ( size_t ) ( x_ډېرۍ_Struct_اندازه * 2 ) )

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_معلومات ساكن بلاک_Link_t x_پیل, x_پای_ټکی;

/* Keeps track of the number of free bytes remaining, but says nothing about
 * fragmentation. */
PRIVILEGED_معلومات ساكن size_t x_Free_بایټونه_پاتې_شوی = config_ADJUSTED_ډېرۍ_اندازه;

/* Indicates whether the heap has been initialised or not. */
PRIVILEGED_معلومات ساكن بنسټ_Type_t x_ډېرۍ_Has_Been_Initialised = pdFALSE;

/*-----------------------------------------------------------*/

/*
 * Initialises the heap structures before their first use.
 */
ساكن فراغ prv_ډېرۍ_Init( فراغ ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* STATIC FUNCTIONS ARE DEFINED AS MACROS TO MINIMIZE THE FUNCTION CALL DEPTH. */

/*
 * Insert a block into the list of free blocks - which is ordered by size of
 * the block.  Small blocks at the start of the list and large blocks at the end
 * of the list.
 */
#تعریف_کړه prv_ورننباسه_بلاک_Into_Free_List( px_بلاک_منزل_ورننباسه )                                                                               \
    {                                                                                                                               \
        بلاک_Link_t * pxIterator;                                                                                                   \
        size_t x_بلاک_اندازه;                                                                                                          \
                                                                                                                                    \
        x_بلاک_اندازه = px_بلاک_منزل_ورننباسه->x_بلاک_اندازه;                                                                                   \
                                                                                                                                    \
        /* Iterate through the list until a block is found that has a larger size */                                                \
        /* than the block we are inserting. */                                                                                      \
        لكل( pxIterator = &x_پیل; pxIterator->px_بل_Free_بلاک->x_بلاک_اندازه < x_بلاک_اندازه; pxIterator = pxIterator->px_بل_Free_بلاک ) \
        {                                                                                                                           \
            /* There is nothing to do here - just iterate to the correct position. */                                               \
        }                                                                                                                           \
                                                                                                                                    \
        /* Update the list to include the block being inserted in the correct */                                                    \
        /* position. */                                                                                                             \
        px_بلاک_منزل_ورننباسه->px_بل_Free_بلاک = pxIterator->px_بل_Free_بلاک;                                                             \
        pxIterator->px_بل_Free_بلاک = px_بلاک_منزل_ورننباسه;                                                                              \
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

    إذا( x_Wanted_اندازه > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        إذا( ډېرۍ_جمع_کړه_WILL_ډکېدنه( x_Wanted_اندازه, x_ډېرۍ_Struct_اندازه ) == 0 )
        {
            x_Wanted_اندازه += x_ډېرۍ_Struct_اندازه;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            إذا( ( x_Wanted_اندازه & پورټ_BYTE_ALIGNMENT_ماسک ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_اندازه = پورټ_BYTE_ALIGNMENT - ( x_Wanted_اندازه & پورټ_BYTE_ALIGNMENT_ماسک );

                إذا( ډېرۍ_جمع_کړه_WILL_ډکېدنه( x_Wanted_اندازه, x_Additional_Required_اندازه ) == 0 )
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
        إذا( x_ډېرۍ_Has_Been_Initialised == pdFALSE )
        {
            prv_ډېرۍ_Init();
            x_ډېرۍ_Has_Been_Initialised = pdTRUE;
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        إذا( ډېرۍ_بلاک_اندازه_IS_VALID( x_Wanted_اندازه ) != 0 )
        {
            إذا( ( x_Wanted_اندازه > 0 ) && ( x_Wanted_اندازه <= x_Free_بایټونه_پاتې_شوی ) )
            {
                /* Blocks are stored in byte order - traverse the list from the start
                 * (smallest) block until one of adequate size is found. */
                px_پخوانی_بلاک = &x_پیل;
                px_بلاک = x_پیل.px_بل_Free_بلاک;

                طالما( ( px_بلاک->x_بلاک_اندازه < x_Wanted_اندازه ) && ( px_بلاک->px_بل_Free_بلاک != عدم ) )
                {
                    px_پخوانی_بلاک = px_بلاک;
                    px_بلاک = px_بلاک->px_بل_Free_بلاک;
                }

                /* If we found the end marker then a block of adequate size was not found. */
                إذا( px_بلاک != &x_پای_ټکی )
                {
                    /* Return the memory space - jumping over the BlockLink_t structure
                     * at its start. */
                    pvReturn = ( فراغ * ) ( ( ( uint8_t * ) px_پخوانی_بلاک->px_بل_Free_بلاک ) + x_ډېرۍ_Struct_اندازه );

                    /* This block is being returned for use so must be taken out of the
                     * list of free blocks. */
                    px_پخوانی_بلاک->px_بل_Free_بلاک = px_بلاک->px_بل_Free_بلاک;

                    /* If the block is larger than required it can be split into two. */
                    إذا( ( px_بلاک->x_بلاک_اندازه - x_Wanted_اندازه ) > ډېرۍ_MINIMUM_بلاک_اندازه )
                    {
                        /* This block is to be split into two.  Create a new block
                         * following the number of bytes requested. The void cast is
                         * used to prevent byte alignment warnings from the compiler. */
                        px_New_بلاک_Link = ( فراغ * ) ( ( ( uint8_t * ) px_بلاک ) + x_Wanted_اندازه );

                        /* Calculate the sizes of two blocks split from the single
                         * block. */
                        px_New_بلاک_Link->x_بلاک_اندازه = px_بلاک->x_بلاک_اندازه - x_Wanted_اندازه;
                        px_بلاک->x_بلاک_اندازه = x_Wanted_اندازه;

                        /* Insert the new block into the list of free blocks.
                         * The list of free blocks is sorted by their size, we have to
                         * iterate to find the right place to insert new block. */
                        prv_ورننباسه_بلاک_Into_Free_List( ( px_New_بلاک_Link ) );
                    }

                    x_Free_بایټونه_پاتې_شوی -= px_بلاک->x_بلاک_اندازه;

                    x_Allocated_بلاک_اندازه = px_بلاک->x_بلاک_اندازه;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    ډېرۍ_ALLOCATE_بلاک( px_بلاک );
                    px_بلاک->px_بل_Free_بلاک = عدم;
                }
            }
        }

        traceMALLOC( pvReturn, x_Allocated_بلاک_اندازه );

        /* Prevent compiler warnings when trace macros are not used. */
        ( فراغ ) x_Allocated_بلاک_اندازه;
    }
    ( فراغ ) xTaskResumeAll();

    #إذا ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        إذا( pvReturn == عدم )
        {
            vApplicationMallocFailedHook();
        }
    }
    #د_که_پای

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

        /* This unexpected casting is to keep some compilers from issuing
         * byte alignment warnings. */
        pxLink = ( فراغ * ) puc;

        configASSERT( ډېرۍ_بلاک_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_بل_Free_بلاک == عدم );

        إذا( ډېرۍ_بلاک_IS_ALLOCATED( pxLink ) != 0 )
        {
            إذا( pxLink->px_بل_Free_بلاک == عدم )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                ډېرۍ_FREE_بلاک( pxLink );
                #إذا ( config_ډېرۍ_CLEAR_حافظه_ON_FREE == 1 )
                {
                    ( فراغ ) memset( puc + x_ډېرۍ_Struct_اندازه, 0, pxLink->x_بلاک_اندازه - x_ډېرۍ_Struct_اندازه );
                }
                #د_که_پای

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    prv_ورننباسه_بلاک_Into_Free_List( ( ( بلاک_Link_t * ) pxLink ) );
                    x_Free_بایټونه_پاتې_شوی += pxLink->x_بلاک_اندازه;
                    traceFREE( pv, pxLink->x_بلاک_اندازه );
                }
                ( فراغ ) xTaskResumeAll();
            }
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_پورټ_Get_Free_ډېرۍ_اندازه( فراغ )
{
    أرجع x_Free_بایټونه_پاتې_شوی;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Initialise_بلاکونه( فراغ )
{
    /* This just exists to keep the linker quiet. */
}
/*-----------------------------------------------------------*/

فراغ * pv_پورټ_Calloc( size_t x_عدد,
                     size_t x_اندازه )
{
    فراغ * pv = عدم;

    إذا( ډېرۍ_MULTIPLY_WILL_ډکېدنه( x_عدد, x_اندازه ) == 0 )
    {
        pv = pv_پورټ_Malloc( x_عدد * x_اندازه );

        إذا( pv != عدم )
        {
            ( فراغ ) memset( pv, 0, x_عدد * x_اندازه );
        }
    }

    أرجع pv;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_ډېرۍ_Init( فراغ ) /* PRIVILEGED_FUNCTION */
{
    بلاک_Link_t * px_لومړی_Free_بلاک;
    uint8_t * puc_Aligned_ډېرۍ;

    /* Ensure the heap starts on a correctly aligned boundary. */
    puc_Aligned_ډېرۍ = ( uint8_t * ) ( ( ( پورټ_اشاره_ګر_اندازه_TYPE ) & uc_ډېرۍ[ پورټ_BYTE_ALIGNMENT - 1 ] ) & ( ~( ( پورټ_اشاره_ګر_اندازه_TYPE ) پورټ_BYTE_ALIGNMENT_ماسک ) ) );

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_پیل.px_بل_Free_بلاک = ( فراغ * ) puc_Aligned_ډېرۍ;
    x_پیل.x_بلاک_اندازه = ( size_t ) 0;

    /* xEnd is used to mark the end of the list of free blocks. */
    x_پای_ټکی.x_بلاک_اندازه = config_ADJUSTED_ډېرۍ_اندازه;
    x_پای_ټکی.px_بل_Free_بلاک = عدم;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space. */
    px_لومړی_Free_بلاک = ( بلاک_Link_t * ) puc_Aligned_ډېرۍ;
    px_لومړی_Free_بلاک->x_بلاک_اندازه = config_ADJUSTED_ډېرۍ_اندازه;
    px_لومړی_Free_بلاک->px_بل_Free_بلاک = &x_پای_ټکی;
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
فراغ v_پورټ_ډېرۍ_Reset_State( فراغ )
{
    x_Free_بایټونه_پاتې_شوی = config_ADJUSTED_ډېرۍ_اندازه;

    x_ډېرۍ_Has_Been_Initialised = pdFALSE;
}
/*-----------------------------------------------------------*/
