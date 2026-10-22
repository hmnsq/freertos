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
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#నిర్వచించు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

#నిర్వచనం_రద్దు MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#ఒకవేళ ( config_SUPPORT_DYNAMIC_కేటాయింపు == 0 )
    #దోషం This file must not be వాడిన ఒకవేళ config_SUPPORT_DYNAMIC_కేటాయింపు is 0
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_కుప్ప_CLEAR_జ్ఞాపకం_ON_FREE
    #నిర్వచించు config_కుప్ప_CLEAR_జ్ఞాపకం_ON_FREE    0
#అయితే_ముగింపు

/* A few bytes might be lost to byte aligning the heap start address. */
#నిర్వచించు config_ADJUSTED_కుప్ప_కొలత    ( config_మొత్తం_కుప్ప_కొలత - పోర్టు_BYTE_ALIGNMENT )

/* Assumes 8bit bytes! */
#నిర్వచించు కుప్ప_బిట్లు_చొప్పున_BYTE           ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#నిర్వచించు కుప్ప_కొలత_MAX                ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#నిర్వచించు కుప్ప_MULTIPLY_WILL_అధికప్రవాహం( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( కుప్ప_కొలత_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#నిర్వచించు కుప్ప_కూడు_WILL_అధికప్రవాహం( a, b )         ( ( a ) > ( కుప్ప_కొలత_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#నిర్వచించు కుప్ప_ఖండం_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( పరిమాణం( size_t ) * కుప్ప_బిట్లు_చొప్పున_BYTE ) - 1 ) )
#నిర్వచించు కుప్ప_ఖండం_కొలత_IS_VALID( x_ఖండం_కొలత )    ( ( ( x_ఖండం_కొలత ) & కుప్ప_ఖండం_ALLOCATED_BITMASK ) == 0 )
#నిర్వచించు కుప్ప_ఖండం_IS_ALLOCATED( px_ఖండం )        ( ( ( px_ఖండం->x_ఖండం_కొలత ) & కుప్ప_ఖండం_ALLOCATED_BITMASK ) != 0 )
#నిర్వచించు కుప్ప_ALLOCATE_ఖండం( px_ఖండం )            ( ( px_ఖండం->x_ఖండం_కొలత ) |= కుప్ప_ఖండం_ALLOCATED_BITMASK )
#నిర్వచించు కుప్ప_FREE_ఖండం( px_ఖండం )                ( ( px_ఖండం->x_ఖండం_కొలత ) &= ~కుప్ప_ఖండం_ALLOCATED_BITMASK )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#ఒకవేళ ( config_APPLICATION_ALLOCATED_కుప్ప == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    బాహ్య uint8_t uc_కుప్ప[ config_మొత్తం_కుప్ప_కొలత ];
#లేకపోతే
    PRIVILEGED_దత్తాంశం స్థిర uint8_t uc_కుప్ప[ config_మొత్తం_కుప్ప_కొలత ];
#అయితే_ముగింపు /* configAPPLICATION_ALLOCATED_HEAP */


/* Define the linked list structure.  This is used to link free blocks in order
 * of their size. */
రకనిర్వచనం నిర్మాణం A_ఖండం_LINK
{
    నిర్మాణం A_ఖండం_LINK * px_తదుపరి_Free_ఖండం; /*<< The next free block in the list. */
    size_t x_ఖండం_కొలత;                     /*<< The size of the free block. */
} ఖండం_Link_t;


స్థిర స్థిరరాశి size_t x_కుప్ప_Struct_కొలత = ( ( పరిమాణం( ఖండం_Link_t ) + ( size_t ) ( పోర్టు_BYTE_ALIGNMENT - 1 ) ) & ~( ( size_t ) పోర్టు_BYTE_ALIGNMENT_ముసుగు ) );
#నిర్వచించు కుప్ప_MINIMUM_ఖండం_కొలత    ( ( size_t ) ( x_కుప్ప_Struct_కొలత * 2 ) )

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_దత్తాంశం స్థిర ఖండం_Link_t x_ప్రారంభం, x_చివర;

/* Keeps track of the number of free bytes remaining, but says nothing about
 * fragmentation. */
PRIVILEGED_దత్తాంశం స్థిర size_t x_Free_బైట్లు_మిగిలిన = config_ADJUSTED_కుప్ప_కొలత;

/* Indicates whether the heap has been initialised or not. */
PRIVILEGED_దత్తాంశం స్థిర పునాది_Type_t x_కుప్ప_Has_Been_Initialised = pdFALSE;

/*-----------------------------------------------------------*/

/*
 * Initialises the heap structures before their first use.
 */
స్థిర శూన్య prv_కుప్ప_Init( శూన్య ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* STATIC FUNCTIONS ARE DEFINED AS MACROS TO MINIMIZE THE FUNCTION CALL DEPTH. */

/*
 * Insert a block into the list of free blocks - which is ordered by size of
 * the block.  Small blocks at the start of the list and large blocks at the end
 * of the list.
 */
#నిర్వచించు prv_చొప్పించు_ఖండం_Into_Free_List( px_ఖండం_గమ్యం_చొప్పించు )                                                                               \
    {                                                                                                                               \
        ఖండం_Link_t * pxIterator;                                                                                                   \
        size_t x_ఖండం_కొలత;                                                                                                          \
                                                                                                                                    \
        x_ఖండం_కొలత = px_ఖండం_గమ్యం_చొప్పించు->x_ఖండం_కొలత;                                                                                   \
                                                                                                                                    \
        /* Iterate through the list until a block is found that has a larger size */                                                \
        /* than the block we are inserting. */                                                                                      \
        కొరకు( pxIterator = &x_ప్రారంభం; pxIterator->px_తదుపరి_Free_ఖండం->x_ఖండం_కొలత < x_ఖండం_కొలత; pxIterator = pxIterator->px_తదుపరి_Free_ఖండం ) \
        {                                                                                                                           \
            /* There is nothing to do here - just iterate to the correct position. */                                               \
        }                                                                                                                           \
                                                                                                                                    \
        /* Update the list to include the block being inserted in the correct */                                                    \
        /* position. */                                                                                                             \
        px_ఖండం_గమ్యం_చొప్పించు->px_తదుపరి_Free_ఖండం = pxIterator->px_తదుపరి_Free_ఖండం;                                                             \
        pxIterator->px_తదుపరి_Free_ఖండం = px_ఖండం_గమ్యం_చొప్పించు;                                                                              \
    }
/*-----------------------------------------------------------*/

శూన్య * pv_పోర్టు_Malloc( size_t x_Wanted_కొలత )
{
    ఖండం_Link_t * px_ఖండం;
    ఖండం_Link_t * px_మునుపటి_ఖండం;
    ఖండం_Link_t * px_New_ఖండం_Link;
    శూన్య * pvReturn = ఖాళీ;
    size_t x_Additional_Required_కొలత;
    size_t x_Allocated_ఖండం_కొలత = 0;

    ఒకవేళ( x_Wanted_కొలత > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        ఒకవేళ( కుప్ప_కూడు_WILL_అధికప్రవాహం( x_Wanted_కొలత, x_కుప్ప_Struct_కొలత ) == 0 )
        {
            x_Wanted_కొలత += x_కుప్ప_Struct_కొలత;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            ఒకవేళ( ( x_Wanted_కొలత & పోర్టు_BYTE_ALIGNMENT_ముసుగు ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_కొలత = పోర్టు_BYTE_ALIGNMENT - ( x_Wanted_కొలత & పోర్టు_BYTE_ALIGNMENT_ముసుగు );

                ఒకవేళ( కుప్ప_కూడు_WILL_అధికప్రవాహం( x_Wanted_కొలత, x_Additional_Required_కొలత ) == 0 )
                {
                    x_Wanted_కొలత += x_Additional_Required_కొలత;
                }
                లేకపోతే
                {
                    x_Wanted_కొలత = 0;
                }
            }
            లేకపోతే
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        లేకపోతే
        {
            x_Wanted_కొలత = 0;
        }
    }
    లేకపోతే
    {
        mtCOVERAGE_TEST_MARKER();
    }

    vTaskSuspendAll();
    {
        /* If this is the first call to malloc then the heap will require
         * initialisation to setup the list of free blocks. */
        ఒకవేళ( x_కుప్ప_Has_Been_Initialised == pdFALSE )
        {
            prv_కుప్ప_Init();
            x_కుప్ప_Has_Been_Initialised = pdTRUE;
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        ఒకవేళ( కుప్ప_ఖండం_కొలత_IS_VALID( x_Wanted_కొలత ) != 0 )
        {
            ఒకవేళ( ( x_Wanted_కొలత > 0 ) && ( x_Wanted_కొలత <= x_Free_బైట్లు_మిగిలిన ) )
            {
                /* Blocks are stored in byte order - traverse the list from the start
                 * (smallest) block until one of adequate size is found. */
                px_మునుపటి_ఖండం = &x_ప్రారంభం;
                px_ఖండం = x_ప్రారంభం.px_తదుపరి_Free_ఖండం;

                అయితే( ( px_ఖండం->x_ఖండం_కొలత < x_Wanted_కొలత ) && ( px_ఖండం->px_తదుపరి_Free_ఖండం != ఖాళీ ) )
                {
                    px_మునుపటి_ఖండం = px_ఖండం;
                    px_ఖండం = px_ఖండం->px_తదుపరి_Free_ఖండం;
                }

                /* If we found the end marker then a block of adequate size was not found. */
                ఒకవేళ( px_ఖండం != &x_చివర )
                {
                    /* Return the memory space - jumping over the BlockLink_t structure
                     * at its start. */
                    pvReturn = ( శూన్య * ) ( ( ( uint8_t * ) px_మునుపటి_ఖండం->px_తదుపరి_Free_ఖండం ) + x_కుప్ప_Struct_కొలత );

                    /* This block is being returned for use so must be taken out of the
                     * list of free blocks. */
                    px_మునుపటి_ఖండం->px_తదుపరి_Free_ఖండం = px_ఖండం->px_తదుపరి_Free_ఖండం;

                    /* If the block is larger than required it can be split into two. */
                    ఒకవేళ( ( px_ఖండం->x_ఖండం_కొలత - x_Wanted_కొలత ) > కుప్ప_MINIMUM_ఖండం_కొలత )
                    {
                        /* This block is to be split into two.  Create a new block
                         * following the number of bytes requested. The void cast is
                         * used to prevent byte alignment warnings from the compiler. */
                        px_New_ఖండం_Link = ( శూన్య * ) ( ( ( uint8_t * ) px_ఖండం ) + x_Wanted_కొలత );

                        /* Calculate the sizes of two blocks split from the single
                         * block. */
                        px_New_ఖండం_Link->x_ఖండం_కొలత = px_ఖండం->x_ఖండం_కొలత - x_Wanted_కొలత;
                        px_ఖండం->x_ఖండం_కొలత = x_Wanted_కొలత;

                        /* Insert the new block into the list of free blocks.
                         * The list of free blocks is sorted by their size, we have to
                         * iterate to find the right place to insert new block. */
                        prv_చొప్పించు_ఖండం_Into_Free_List( ( px_New_ఖండం_Link ) );
                    }

                    x_Free_బైట్లు_మిగిలిన -= px_ఖండం->x_ఖండం_కొలత;

                    x_Allocated_ఖండం_కొలత = px_ఖండం->x_ఖండం_కొలత;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    కుప్ప_ALLOCATE_ఖండం( px_ఖండం );
                    px_ఖండం->px_తదుపరి_Free_ఖండం = ఖాళీ;
                }
            }
        }

        traceMALLOC( pvReturn, x_Allocated_ఖండం_కొలత );

        /* Prevent compiler warnings when trace macros are not used. */
        ( శూన్య ) x_Allocated_ఖండం_కొలత;
    }
    ( శూన్య ) xTaskResumeAll();

    #ఒకవేళ ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        ఒకవేళ( pvReturn == ఖాళీ )
        {
            vApplicationMallocFailedHook();
        }
    }
    #అయితే_ముగింపు

    తిరిగి pvReturn;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Free( శూన్య * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    ఖండం_Link_t * pxLink;

    ఒకవేళ( pv != ఖాళీ )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_కుప్ప_Struct_కొలత;

        /* This unexpected casting is to keep some compilers from issuing
         * byte alignment warnings. */
        pxLink = ( శూన్య * ) puc;

        configASSERT( కుప్ప_ఖండం_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_తదుపరి_Free_ఖండం == ఖాళీ );

        ఒకవేళ( కుప్ప_ఖండం_IS_ALLOCATED( pxLink ) != 0 )
        {
            ఒకవేళ( pxLink->px_తదుపరి_Free_ఖండం == ఖాళీ )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                కుప్ప_FREE_ఖండం( pxLink );
                #ఒకవేళ ( config_కుప్ప_CLEAR_జ్ఞాపకం_ON_FREE == 1 )
                {
                    ( శూన్య ) memset( puc + x_కుప్ప_Struct_కొలత, 0, pxLink->x_ఖండం_కొలత - x_కుప్ప_Struct_కొలత );
                }
                #అయితే_ముగింపు

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    prv_చొప్పించు_ఖండం_Into_Free_List( ( ( ఖండం_Link_t * ) pxLink ) );
                    x_Free_బైట్లు_మిగిలిన += pxLink->x_ఖండం_కొలత;
                    traceFREE( pv, pxLink->x_ఖండం_కొలత );
                }
                ( శూన్య ) xTaskResumeAll();
            }
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_పోర్టు_Get_Free_కుప్ప_కొలత( శూన్య )
{
    తిరిగి x_Free_బైట్లు_మిగిలిన;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Initialise_ఖండాలు( శూన్య )
{
    /* This just exists to keep the linker quiet. */
}
/*-----------------------------------------------------------*/

శూన్య * pv_పోర్టు_Calloc( size_t x_అంకె,
                     size_t x_కొలత )
{
    శూన్య * pv = ఖాళీ;

    ఒకవేళ( కుప్ప_MULTIPLY_WILL_అధికప్రవాహం( x_అంకె, x_కొలత ) == 0 )
    {
        pv = pv_పోర్టు_Malloc( x_అంకె * x_కొలత );

        ఒకవేళ( pv != ఖాళీ )
        {
            ( శూన్య ) memset( pv, 0, x_అంకె * x_కొలత );
        }
    }

    తిరిగి pv;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_కుప్ప_Init( శూన్య ) /* PRIVILEGED_FUNCTION */
{
    ఖండం_Link_t * px_మొదటి_Free_ఖండం;
    uint8_t * puc_Aligned_కుప్ప;

    /* Ensure the heap starts on a correctly aligned boundary. */
    puc_Aligned_కుప్ప = ( uint8_t * ) ( ( ( పోర్టు_సూచిక_కొలత_TYPE ) & uc_కుప్ప[ పోర్టు_BYTE_ALIGNMENT - 1 ] ) & ( ~( ( పోర్టు_సూచిక_కొలత_TYPE ) పోర్టు_BYTE_ALIGNMENT_ముసుగు ) ) );

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_ప్రారంభం.px_తదుపరి_Free_ఖండం = ( శూన్య * ) puc_Aligned_కుప్ప;
    x_ప్రారంభం.x_ఖండం_కొలత = ( size_t ) 0;

    /* xEnd is used to mark the end of the list of free blocks. */
    x_చివర.x_ఖండం_కొలత = config_ADJUSTED_కుప్ప_కొలత;
    x_చివర.px_తదుపరి_Free_ఖండం = ఖాళీ;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space. */
    px_మొదటి_Free_ఖండం = ( ఖండం_Link_t * ) puc_Aligned_కుప్ప;
    px_మొదటి_Free_ఖండం->x_ఖండం_కొలత = config_ADJUSTED_కుప్ప_కొలత;
    px_మొదటి_Free_ఖండం->px_తదుపరి_Free_ఖండం = &x_చివర;
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
శూన్య v_పోర్టు_కుప్ప_Reset_State( శూన్య )
{
    x_Free_బైట్లు_మిగిలిన = config_ADJUSTED_కుప్ప_కొలత;

    x_కుప్ప_Has_Been_Initialised = pdFALSE;
}
/*-----------------------------------------------------------*/
