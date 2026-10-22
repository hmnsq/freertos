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

/* A few bytes might be lost to byte aligning the heap start address. */
#تعریف_کرو config_ADJUSTED_ڈھیر_ناپ    ( config_کل_ڈھیر_ناپ - پورٹ_BYTE_ALIGNMENT )

/* Assumes 8bit bytes! */
#تعریف_کرو ڈھیر_بٹ_فی_BYTE           ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#تعریف_کرو ڈھیر_ناپ_MAX                ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#تعریف_کرو ڈھیر_MULTIPLY_WILL_حد_توں_ودھ( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( ڈھیر_ناپ_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کرو ڈھیر_جوڑو_WILL_حد_توں_ودھ( a, b )         ( ( a ) > ( ڈھیر_ناپ_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#تعریف_کرو ڈھیر_بلاک_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( حجم( size_t ) * ڈھیر_بٹ_فی_BYTE ) - 1 ) )
#تعریف_کرو ڈھیر_بلاک_ناپ_IS_VALID( x_بلاک_ناپ )    ( ( ( x_بلاک_ناپ ) & ڈھیر_بلاک_ALLOCATED_BITMASK ) == 0 )
#تعریف_کرو ڈھیر_بلاک_IS_ALLOCATED( px_بلاک )        ( ( ( px_بلاک->x_بلاک_ناپ ) & ڈھیر_بلاک_ALLOCATED_BITMASK ) != 0 )
#تعریف_کرو ڈھیر_ALLOCATE_بلاک( px_بلاک )            ( ( px_بلاک->x_بلاک_ناپ ) |= ڈھیر_بلاک_ALLOCATED_BITMASK )
#تعریف_کرو ڈھیر_FREE_بلاک( px_بلاک )                ( ( px_بلاک->x_بلاک_ناپ ) &= ~ڈھیر_بلاک_ALLOCATED_BITMASK )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#إذا ( config_APPLICATION_ALLOCATED_ڈھیر == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    خارجي uint8_t uc_ڈھیر[ config_کل_ڈھیر_ناپ ];
#وإلا
    PRIVILEGED_انکڑے ساكن uint8_t uc_ڈھیر[ config_کل_ڈھیر_ناپ ];
#جے_انت /* configAPPLICATION_ALLOCATED_HEAP */


/* Define the linked list structure.  This is used to link free blocks in order
 * of their size. */
تعريفنوع بنية A_بلاک_LINK
{
    بنية A_بلاک_LINK * px_اگلا_Free_بلاک; /*<< The next free block in the list. */
    size_t x_بلاک_ناپ;                     /*<< The size of the free block. */
} بلاک_Link_t;


ساكن ثابت size_t x_ڈھیر_Struct_ناپ = ( ( حجم( بلاک_Link_t ) + ( size_t ) ( پورٹ_BYTE_ALIGNMENT - 1 ) ) & ~( ( size_t ) پورٹ_BYTE_ALIGNMENT_نقاب ) );
#تعریف_کرو ڈھیر_MINIMUM_بلاک_ناپ    ( ( size_t ) ( x_ڈھیر_Struct_ناپ * 2 ) )

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_انکڑے ساكن بلاک_Link_t x_شروع, x_سرا;

/* Keeps track of the number of free bytes remaining, but says nothing about
 * fragmentation. */
PRIVILEGED_انکڑے ساكن size_t x_Free_بائٹاں_بچیا = config_ADJUSTED_ڈھیر_ناپ;

/* Indicates whether the heap has been initialised or not. */
PRIVILEGED_انکڑے ساكن ادھار_Type_t x_ڈھیر_Has_Been_Initialised = pdFALSE;

/*-----------------------------------------------------------*/

/*
 * Initialises the heap structures before their first use.
 */
ساكن فراغ prv_ڈھیر_Init( فراغ ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* STATIC FUNCTIONS ARE DEFINED AS MACROS TO MINIMIZE THE FUNCTION CALL DEPTH. */

/*
 * Insert a block into the list of free blocks - which is ordered by size of
 * the block.  Small blocks at the start of the list and large blocks at the end
 * of the list.
 */
#تعریف_کرو prv_داخل_کرو_بلاک_Into_Free_List( px_بلاک_منزل_داخل_کرو )                                                                               \
    {                                                                                                                               \
        بلاک_Link_t * pxIterator;                                                                                                   \
        size_t x_بلاک_ناپ;                                                                                                          \
                                                                                                                                    \
        x_بلاک_ناپ = px_بلاک_منزل_داخل_کرو->x_بلاک_ناپ;                                                                                   \
                                                                                                                                    \
        /* Iterate through the list until a block is found that has a larger size */                                                \
        /* than the block we are inserting. */                                                                                      \
        لكل( pxIterator = &x_شروع; pxIterator->px_اگلا_Free_بلاک->x_بلاک_ناپ < x_بلاک_ناپ; pxIterator = pxIterator->px_اگلا_Free_بلاک ) \
        {                                                                                                                           \
            /* There is nothing to do here - just iterate to the correct position. */                                               \
        }                                                                                                                           \
                                                                                                                                    \
        /* Update the list to include the block being inserted in the correct */                                                    \
        /* position. */                                                                                                             \
        px_بلاک_منزل_داخل_کرو->px_اگلا_Free_بلاک = pxIterator->px_اگلا_Free_بلاک;                                                             \
        pxIterator->px_اگلا_Free_بلاک = px_بلاک_منزل_داخل_کرو;                                                                              \
    }
/*-----------------------------------------------------------*/

فراغ * pv_پورٹ_Malloc( size_t x_Wanted_ناپ )
{
    بلاک_Link_t * px_بلاک;
    بلاک_Link_t * px_پچھلا_بلاک;
    بلاک_Link_t * px_New_بلاک_Link;
    فراغ * pvReturn = عدم;
    size_t x_Additional_Required_ناپ;
    size_t x_Allocated_بلاک_ناپ = 0;

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
        /* If this is the first call to malloc then the heap will require
         * initialisation to setup the list of free blocks. */
        إذا( x_ڈھیر_Has_Been_Initialised == pdFALSE )
        {
            prv_ڈھیر_Init();
            x_ڈھیر_Has_Been_Initialised = pdTRUE;
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        إذا( ڈھیر_بلاک_ناپ_IS_VALID( x_Wanted_ناپ ) != 0 )
        {
            إذا( ( x_Wanted_ناپ > 0 ) && ( x_Wanted_ناپ <= x_Free_بائٹاں_بچیا ) )
            {
                /* Blocks are stored in byte order - traverse the list from the start
                 * (smallest) block until one of adequate size is found. */
                px_پچھلا_بلاک = &x_شروع;
                px_بلاک = x_شروع.px_اگلا_Free_بلاک;

                طالما( ( px_بلاک->x_بلاک_ناپ < x_Wanted_ناپ ) && ( px_بلاک->px_اگلا_Free_بلاک != عدم ) )
                {
                    px_پچھلا_بلاک = px_بلاک;
                    px_بلاک = px_بلاک->px_اگلا_Free_بلاک;
                }

                /* If we found the end marker then a block of adequate size was not found. */
                إذا( px_بلاک != &x_سرا )
                {
                    /* Return the memory space - jumping over the BlockLink_t structure
                     * at its start. */
                    pvReturn = ( فراغ * ) ( ( ( uint8_t * ) px_پچھلا_بلاک->px_اگلا_Free_بلاک ) + x_ڈھیر_Struct_ناپ );

                    /* This block is being returned for use so must be taken out of the
                     * list of free blocks. */
                    px_پچھلا_بلاک->px_اگلا_Free_بلاک = px_بلاک->px_اگلا_Free_بلاک;

                    /* If the block is larger than required it can be split into two. */
                    إذا( ( px_بلاک->x_بلاک_ناپ - x_Wanted_ناپ ) > ڈھیر_MINIMUM_بلاک_ناپ )
                    {
                        /* This block is to be split into two.  Create a new block
                         * following the number of bytes requested. The void cast is
                         * used to prevent byte alignment warnings from the compiler. */
                        px_New_بلاک_Link = ( فراغ * ) ( ( ( uint8_t * ) px_بلاک ) + x_Wanted_ناپ );

                        /* Calculate the sizes of two blocks split from the single
                         * block. */
                        px_New_بلاک_Link->x_بلاک_ناپ = px_بلاک->x_بلاک_ناپ - x_Wanted_ناپ;
                        px_بلاک->x_بلاک_ناپ = x_Wanted_ناپ;

                        /* Insert the new block into the list of free blocks.
                         * The list of free blocks is sorted by their size, we have to
                         * iterate to find the right place to insert new block. */
                        prv_داخل_کرو_بلاک_Into_Free_List( ( px_New_بلاک_Link ) );
                    }

                    x_Free_بائٹاں_بچیا -= px_بلاک->x_بلاک_ناپ;

                    x_Allocated_بلاک_ناپ = px_بلاک->x_بلاک_ناپ;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    ڈھیر_ALLOCATE_بلاک( px_بلاک );
                    px_بلاک->px_اگلا_Free_بلاک = عدم;
                }
            }
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
    }
    #جے_انت

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

        /* This unexpected casting is to keep some compilers from issuing
         * byte alignment warnings. */
        pxLink = ( فراغ * ) puc;

        configASSERT( ڈھیر_بلاک_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_اگلا_Free_بلاک == عدم );

        إذا( ڈھیر_بلاک_IS_ALLOCATED( pxLink ) != 0 )
        {
            إذا( pxLink->px_اگلا_Free_بلاک == عدم )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                ڈھیر_FREE_بلاک( pxLink );
                #إذا ( config_ڈھیر_CLEAR_حافظہ_ON_FREE == 1 )
                {
                    ( فراغ ) memset( puc + x_ڈھیر_Struct_ناپ, 0, pxLink->x_بلاک_ناپ - x_ڈھیر_Struct_ناپ );
                }
                #جے_انت

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    prv_داخل_کرو_بلاک_Into_Free_List( ( ( بلاک_Link_t * ) pxLink ) );
                    x_Free_بائٹاں_بچیا += pxLink->x_بلاک_ناپ;
                    traceFREE( pv, pxLink->x_بلاک_ناپ );
                }
                ( فراغ ) xTaskResumeAll();
            }
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_پورٹ_Get_Free_ڈھیر_ناپ( فراغ )
{
    أرجع x_Free_بائٹاں_بچیا;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Initialise_بلاکاں( فراغ )
{
    /* This just exists to keep the linker quiet. */
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

ساكن فراغ prv_ڈھیر_Init( فراغ ) /* PRIVILEGED_FUNCTION */
{
    بلاک_Link_t * px_پہلا_Free_بلاک;
    uint8_t * puc_Aligned_ڈھیر;

    /* Ensure the heap starts on a correctly aligned boundary. */
    puc_Aligned_ڈھیر = ( uint8_t * ) ( ( ( پورٹ_اشارہ_گر_ناپ_TYPE ) & uc_ڈھیر[ پورٹ_BYTE_ALIGNMENT - 1 ] ) & ( ~( ( پورٹ_اشارہ_گر_ناپ_TYPE ) پورٹ_BYTE_ALIGNMENT_نقاب ) ) );

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_شروع.px_اگلا_Free_بلاک = ( فراغ * ) puc_Aligned_ڈھیر;
    x_شروع.x_بلاک_ناپ = ( size_t ) 0;

    /* xEnd is used to mark the end of the list of free blocks. */
    x_سرا.x_بلاک_ناپ = config_ADJUSTED_ڈھیر_ناپ;
    x_سرا.px_اگلا_Free_بلاک = عدم;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space. */
    px_پہلا_Free_بلاک = ( بلاک_Link_t * ) puc_Aligned_ڈھیر;
    px_پہلا_Free_بلاک->x_بلاک_ناپ = config_ADJUSTED_ڈھیر_ناپ;
    px_پہلا_Free_بلاک->px_اگلا_Free_بلاک = &x_سرا;
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
فراغ v_پورٹ_ڈھیر_Reset_State( فراغ )
{
    x_Free_بائٹاں_بچیا = config_ADJUSTED_ڈھیر_ناپ;

    x_ڈھیر_Has_Been_Initialised = pdFALSE;
}
/*-----------------------------------------------------------*/
