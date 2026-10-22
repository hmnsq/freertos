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

/* A few bytes might be lost to byte aligning the heap start address. */
#وصف_ڪريو config_ADJUSTED_ڍير_سائيز    ( config_ڪل_ڍير_سائيز - پورٽ_BYTE_ALIGNMENT )

/* Assumes 8bit bytes! */
#وصف_ڪريو ڍير_بٽ_في_BYTE           ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#وصف_ڪريو ڍير_سائيز_MAX                ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#وصف_ڪريو ڍير_MULTIPLY_WILL_حد_کان_مٿي( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( ڍير_سائيز_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#وصف_ڪريو ڍير_جوڙيو_WILL_حد_کان_مٿي( a, b )         ( ( a ) > ( ڍير_سائيز_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#وصف_ڪريو ڍير_بلاڪ_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( حجم( size_t ) * ڍير_بٽ_في_BYTE ) - 1 ) )
#وصف_ڪريو ڍير_بلاڪ_سائيز_IS_VALID( x_بلاڪ_سائيز )    ( ( ( x_بلاڪ_سائيز ) & ڍير_بلاڪ_ALLOCATED_BITMASK ) == 0 )
#وصف_ڪريو ڍير_بلاڪ_IS_ALLOCATED( px_بلاڪ )        ( ( ( px_بلاڪ->x_بلاڪ_سائيز ) & ڍير_بلاڪ_ALLOCATED_BITMASK ) != 0 )
#وصف_ڪريو ڍير_ALLOCATE_بلاڪ( px_بلاڪ )            ( ( px_بلاڪ->x_بلاڪ_سائيز ) |= ڍير_بلاڪ_ALLOCATED_BITMASK )
#وصف_ڪريو ڍير_FREE_بلاڪ( px_بلاڪ )                ( ( px_بلاڪ->x_بلاڪ_سائيز ) &= ~ڍير_بلاڪ_ALLOCATED_BITMASK )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#إذا ( config_APPLICATION_ALLOCATED_ڍير == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    خارجي uint8_t uc_ڍير[ config_ڪل_ڍير_سائيز ];
#وإلا
    PRIVILEGED_معلومات ساكن uint8_t uc_ڍير[ config_ڪل_ڍير_سائيز ];
#جيڪڏهن_پورو /* configAPPLICATION_ALLOCATED_HEAP */


/* Define the linked list structure.  This is used to link free blocks in order
 * of their size. */
تعريفنوع بنية A_بلاڪ_LINK
{
    بنية A_بلاڪ_LINK * px_ايندڙ_Free_بلاڪ; /*<< The next free block in the list. */
    size_t x_بلاڪ_سائيز;                     /*<< The size of the free block. */
} بلاڪ_Link_t;


ساكن ثابت size_t x_ڍير_Struct_سائيز = ( ( حجم( بلاڪ_Link_t ) + ( size_t ) ( پورٽ_BYTE_ALIGNMENT - 1 ) ) & ~( ( size_t ) پورٽ_BYTE_ALIGNMENT_نقاب ) );
#وصف_ڪريو ڍير_MINIMUM_بلاڪ_سائيز    ( ( size_t ) ( x_ڍير_Struct_سائيز * 2 ) )

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_معلومات ساكن بلاڪ_Link_t x_شروعات, x_پڇاڙي;

/* Keeps track of the number of free bytes remaining, but says nothing about
 * fragmentation. */
PRIVILEGED_معلومات ساكن size_t x_Free_بائيٽون_بچيل = config_ADJUSTED_ڍير_سائيز;

/* Indicates whether the heap has been initialised or not. */
PRIVILEGED_معلومات ساكن بنياد_Type_t x_ڍير_Has_Been_Initialised = pdFALSE;

/*-----------------------------------------------------------*/

/*
 * Initialises the heap structures before their first use.
 */
ساكن فراغ prv_ڍير_Init( فراغ ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* STATIC FUNCTIONS ARE DEFINED AS MACROS TO MINIMIZE THE FUNCTION CALL DEPTH. */

/*
 * Insert a block into the list of free blocks - which is ordered by size of
 * the block.  Small blocks at the start of the list and large blocks at the end
 * of the list.
 */
#وصف_ڪريو prv_وجهو_بلاڪ_Into_Free_List( px_بلاڪ_منزل_وجهو )                                                                               \
    {                                                                                                                               \
        بلاڪ_Link_t * pxIterator;                                                                                                   \
        size_t x_بلاڪ_سائيز;                                                                                                          \
                                                                                                                                    \
        x_بلاڪ_سائيز = px_بلاڪ_منزل_وجهو->x_بلاڪ_سائيز;                                                                                   \
                                                                                                                                    \
        /* Iterate through the list until a block is found that has a larger size */                                                \
        /* than the block we are inserting. */                                                                                      \
        لكل( pxIterator = &x_شروعات; pxIterator->px_ايندڙ_Free_بلاڪ->x_بلاڪ_سائيز < x_بلاڪ_سائيز; pxIterator = pxIterator->px_ايندڙ_Free_بلاڪ ) \
        {                                                                                                                           \
            /* There is nothing to do here - just iterate to the correct position. */                                               \
        }                                                                                                                           \
                                                                                                                                    \
        /* Update the list to include the block being inserted in the correct */                                                    \
        /* position. */                                                                                                             \
        px_بلاڪ_منزل_وجهو->px_ايندڙ_Free_بلاڪ = pxIterator->px_ايندڙ_Free_بلاڪ;                                                             \
        pxIterator->px_ايندڙ_Free_بلاڪ = px_بلاڪ_منزل_وجهو;                                                                              \
    }
/*-----------------------------------------------------------*/

فراغ * pv_پورٽ_Malloc( size_t x_Wanted_سائيز )
{
    بلاڪ_Link_t * px_بلاڪ;
    بلاڪ_Link_t * px_اڳيون_بلاڪ;
    بلاڪ_Link_t * px_New_بلاڪ_Link;
    فراغ * pvReturn = عدم;
    size_t x_Additional_Required_سائيز;
    size_t x_Allocated_بلاڪ_سائيز = 0;

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
        /* If this is the first call to malloc then the heap will require
         * initialisation to setup the list of free blocks. */
        إذا( x_ڍير_Has_Been_Initialised == pdFALSE )
        {
            prv_ڍير_Init();
            x_ڍير_Has_Been_Initialised = pdTRUE;
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        إذا( ڍير_بلاڪ_سائيز_IS_VALID( x_Wanted_سائيز ) != 0 )
        {
            إذا( ( x_Wanted_سائيز > 0 ) && ( x_Wanted_سائيز <= x_Free_بائيٽون_بچيل ) )
            {
                /* Blocks are stored in byte order - traverse the list from the start
                 * (smallest) block until one of adequate size is found. */
                px_اڳيون_بلاڪ = &x_شروعات;
                px_بلاڪ = x_شروعات.px_ايندڙ_Free_بلاڪ;

                طالما( ( px_بلاڪ->x_بلاڪ_سائيز < x_Wanted_سائيز ) && ( px_بلاڪ->px_ايندڙ_Free_بلاڪ != عدم ) )
                {
                    px_اڳيون_بلاڪ = px_بلاڪ;
                    px_بلاڪ = px_بلاڪ->px_ايندڙ_Free_بلاڪ;
                }

                /* If we found the end marker then a block of adequate size was not found. */
                إذا( px_بلاڪ != &x_پڇاڙي )
                {
                    /* Return the memory space - jumping over the BlockLink_t structure
                     * at its start. */
                    pvReturn = ( فراغ * ) ( ( ( uint8_t * ) px_اڳيون_بلاڪ->px_ايندڙ_Free_بلاڪ ) + x_ڍير_Struct_سائيز );

                    /* This block is being returned for use so must be taken out of the
                     * list of free blocks. */
                    px_اڳيون_بلاڪ->px_ايندڙ_Free_بلاڪ = px_بلاڪ->px_ايندڙ_Free_بلاڪ;

                    /* If the block is larger than required it can be split into two. */
                    إذا( ( px_بلاڪ->x_بلاڪ_سائيز - x_Wanted_سائيز ) > ڍير_MINIMUM_بلاڪ_سائيز )
                    {
                        /* This block is to be split into two.  Create a new block
                         * following the number of bytes requested. The void cast is
                         * used to prevent byte alignment warnings from the compiler. */
                        px_New_بلاڪ_Link = ( فراغ * ) ( ( ( uint8_t * ) px_بلاڪ ) + x_Wanted_سائيز );

                        /* Calculate the sizes of two blocks split from the single
                         * block. */
                        px_New_بلاڪ_Link->x_بلاڪ_سائيز = px_بلاڪ->x_بلاڪ_سائيز - x_Wanted_سائيز;
                        px_بلاڪ->x_بلاڪ_سائيز = x_Wanted_سائيز;

                        /* Insert the new block into the list of free blocks.
                         * The list of free blocks is sorted by their size, we have to
                         * iterate to find the right place to insert new block. */
                        prv_وجهو_بلاڪ_Into_Free_List( ( px_New_بلاڪ_Link ) );
                    }

                    x_Free_بائيٽون_بچيل -= px_بلاڪ->x_بلاڪ_سائيز;

                    x_Allocated_بلاڪ_سائيز = px_بلاڪ->x_بلاڪ_سائيز;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    ڍير_ALLOCATE_بلاڪ( px_بلاڪ );
                    px_بلاڪ->px_ايندڙ_Free_بلاڪ = عدم;
                }
            }
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
    }
    #جيڪڏهن_پورو

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

        /* This unexpected casting is to keep some compilers from issuing
         * byte alignment warnings. */
        pxLink = ( فراغ * ) puc;

        configASSERT( ڍير_بلاڪ_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_ايندڙ_Free_بلاڪ == عدم );

        إذا( ڍير_بلاڪ_IS_ALLOCATED( pxLink ) != 0 )
        {
            إذا( pxLink->px_ايندڙ_Free_بلاڪ == عدم )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                ڍير_FREE_بلاڪ( pxLink );
                #إذا ( config_ڍير_CLEAR_يادگيري_ON_FREE == 1 )
                {
                    ( فراغ ) memset( puc + x_ڍير_Struct_سائيز, 0, pxLink->x_بلاڪ_سائيز - x_ڍير_Struct_سائيز );
                }
                #جيڪڏهن_پورو

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    prv_وجهو_بلاڪ_Into_Free_List( ( ( بلاڪ_Link_t * ) pxLink ) );
                    x_Free_بائيٽون_بچيل += pxLink->x_بلاڪ_سائيز;
                    traceFREE( pv, pxLink->x_بلاڪ_سائيز );
                }
                ( فراغ ) xTaskResumeAll();
            }
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_پورٽ_Get_Free_ڍير_سائيز( فراغ )
{
    أرجع x_Free_بائيٽون_بچيل;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Initialise_بلاڪون( فراغ )
{
    /* This just exists to keep the linker quiet. */
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

ساكن فراغ prv_ڍير_Init( فراغ ) /* PRIVILEGED_FUNCTION */
{
    بلاڪ_Link_t * px_پهريون_Free_بلاڪ;
    uint8_t * puc_Aligned_ڍير;

    /* Ensure the heap starts on a correctly aligned boundary. */
    puc_Aligned_ڍير = ( uint8_t * ) ( ( ( پورٽ_اشارو_سائيز_TYPE ) & uc_ڍير[ پورٽ_BYTE_ALIGNMENT - 1 ] ) & ( ~( ( پورٽ_اشارو_سائيز_TYPE ) پورٽ_BYTE_ALIGNMENT_نقاب ) ) );

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_شروعات.px_ايندڙ_Free_بلاڪ = ( فراغ * ) puc_Aligned_ڍير;
    x_شروعات.x_بلاڪ_سائيز = ( size_t ) 0;

    /* xEnd is used to mark the end of the list of free blocks. */
    x_پڇاڙي.x_بلاڪ_سائيز = config_ADJUSTED_ڍير_سائيز;
    x_پڇاڙي.px_ايندڙ_Free_بلاڪ = عدم;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space. */
    px_پهريون_Free_بلاڪ = ( بلاڪ_Link_t * ) puc_Aligned_ڍير;
    px_پهريون_Free_بلاڪ->x_بلاڪ_سائيز = config_ADJUSTED_ڍير_سائيز;
    px_پهريون_Free_بلاڪ->px_ايندڙ_Free_بلاڪ = &x_پڇاڙي;
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
فراغ v_پورٽ_ڍير_Reset_State( فراغ )
{
    x_Free_بائيٽون_بچيل = config_ADJUSTED_ڍير_سائيز;

    x_ڍير_Has_Been_Initialised = pdFALSE;
}
/*-----------------------------------------------------------*/
