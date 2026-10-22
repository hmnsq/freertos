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
 * A sample implementation of pvPortMalloc() and vPortFree() that combines
 * (coalescences) adjacent memory blocks as they are freed, and in so doing
 * limits memory fragmentation.
 *
 * See heap_1.c, heap_2.c and heap_3.c for alternative implementations, and the
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

/* Block sizes must not get too small. */
#నిర్వచించు కుప్ప_MINIMUM_ఖండం_కొలత    ( ( size_t ) ( x_కుప్ప_Struct_కొలత << 1 ) )

/* Assumes 8bit bytes! */
#నిర్వచించు కుప్ప_బిట్లు_చొప్పున_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#నిర్వచించు కుప్ప_కొలత_MAX              ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#నిర్వచించు కుప్ప_MULTIPLY_WILL_అధికప్రవాహం( a, b )     ( ( ( a ) > 0 ) && ( ( b ) > ( కుప్ప_కొలత_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#నిర్వచించు కుప్ప_కూడు_WILL_అధికప్రవాహం( a, b )          ( ( a ) > ( కుప్ప_కొలత_MAX - ( b ) ) )

/* Check if the subtraction operation ( a - b ) will result in underflow. */
#నిర్వచించు కుప్ప_వ్యవకలనం_WILL_UNDERFLOW( a, b )    ( ( a ) < ( b ) )

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
 * of their memory address. */
రకనిర్వచనం నిర్మాణం A_ఖండం_LINK
{
    నిర్మాణం A_ఖండం_LINK * px_తదుపరి_Free_ఖండం; /**< The next free block in the list. */
    size_t x_ఖండం_కొలత;                     /**< The size of the free block. */
} ఖండం_Link_t;

/* Setting configENABLE_HEAP_PROTECTOR to 1 enables heap block pointers
 * protection using an application supplied canary value to catch heap
 * corruption should a heap buffer overflow occur.
 */
#ఒకవేళ ( config_ENABLE_కుప్ప_PROTECTOR == 1 )

/**
 * @brief Application provided function to get a random value to be used as canary.
 *
 * @param pxHeapCanary [out] Output parameter to return the canary value.
 */
    బాహ్య శూన్య v_Application_Get_Random_కుప్ప_Canary( పోర్టు_సూచిక_కొలత_TYPE * px_కుప్ప_Canary );

/* Canary value for protecting internal heap pointers. */
    PRIVILEGED_దత్తాంశం స్థిర పోర్టు_సూచిక_కొలత_TYPE x_కుప్ప_Canary;

/* Macro to load/store BlockLink_t pointers to memory. By XORing the
 * pointers with a random canary value, heap overflows will result
 * in randomly unpredictable pointer values which will be caught by
 * heapVALIDATE_BLOCK_POINTER assert. */
    #నిర్వచించు కుప్ప_PROTECT_ఖండం_సూచిక( px_ఖండం )    ( ( ఖండం_Link_t * ) ( ( ( పోర్టు_సూచిక_కొలత_TYPE ) ( px_ఖండం ) ) ^ x_కుప్ప_Canary ) )
#లేకపోతే

    #నిర్వచించు కుప్ప_PROTECT_ఖండం_సూచిక( px_ఖండం )    ( px_ఖండం )

#అయితే_ముగింపు /* configENABLE_HEAP_PROTECTOR */

/* Assert that a heap block pointer is within the heap bounds. */
#నిర్వచించు కుప్ప_VALIDATE_ఖండం_సూచిక( px_ఖండం )                          \
    configASSERT( ( ( uint8_t * ) ( px_ఖండం ) >= &( uc_కుప్ప[ 0 ] ) ) && \
                  ( ( uint8_t * ) ( px_ఖండం ) <= &( uc_కుప్ప[ config_మొత్తం_కుప్ప_కొలత - 1 ] ) ) )

/*-----------------------------------------------------------*/

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
స్థిర శూన్య prv_చొప్పించు_ఖండం_Into_Free_List( ఖండం_Link_t * px_ఖండం_గమ్యం_చొప్పించు ) PRIVILEGED_FUNCTION;

/*
 * Called automatically to setup the required heap structures the first time
 * pvPortMalloc() is called.
 */
స్థిర శూన్య prv_కుప్ప_Init( శూన్య ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* The size of the structure placed at the beginning of each allocated memory
 * block must by correctly byte aligned. */
స్థిర స్థిరరాశి size_t x_కుప్ప_Struct_కొలత = ( పరిమాణం( ఖండం_Link_t ) + ( ( size_t ) ( పోర్టు_BYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) పోర్టు_BYTE_ALIGNMENT_ముసుగు );

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_దత్తాంశం స్థిర ఖండం_Link_t x_ప్రారంభం;
PRIVILEGED_దత్తాంశం స్థిర ఖండం_Link_t * px_చివర = ఖాళీ;

/* Keeps track of the number of calls to allocate and free memory as well as the
 * number of free bytes remaining, but says nothing about fragmentation. */
PRIVILEGED_దత్తాంశం స్థిర size_t x_Free_బైట్లు_మిగిలిన = ( size_t ) 0U;
PRIVILEGED_దత్తాంశం స్థిర size_t x_Minimum_Ever_Free_బైట్లు_మిగిలిన = ( size_t ) 0U;
PRIVILEGED_దత్తాంశం స్థిర size_t x_సంఖ్య_యొక్క_Successful_Allocations = ( size_t ) 0U;
PRIVILEGED_దత్తాంశం స్థిర size_t x_సంఖ్య_యొక్క_Successful_Frees = ( size_t ) 0U;

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
        ఒకవేళ( px_చివర == ఖాళీ )
        {
            prv_కుప్ప_Init();
        }
        లేకపోతే
        {
            mtCOVERAGE_TEST_MARKER();
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        ఒకవేళ( కుప్ప_ఖండం_కొలత_IS_VALID( x_Wanted_కొలత ) != 0 )
        {
            ఒకవేళ( ( x_Wanted_కొలత > 0 ) && ( x_Wanted_కొలత <= x_Free_బైట్లు_మిగిలిన ) )
            {
                /* Traverse the list from the start (lowest address) block until
                 * one of adequate size is found. */
                px_మునుపటి_ఖండం = &x_ప్రారంభం;
                px_ఖండం = కుప్ప_PROTECT_ఖండం_సూచిక( x_ప్రారంభం.px_తదుపరి_Free_ఖండం );
                కుప్ప_VALIDATE_ఖండం_సూచిక( px_ఖండం );

                అయితే( ( px_ఖండం->x_ఖండం_కొలత < x_Wanted_కొలత ) && ( px_ఖండం->px_తదుపరి_Free_ఖండం != కుప్ప_PROTECT_ఖండం_సూచిక( ఖాళీ ) ) )
                {
                    px_మునుపటి_ఖండం = px_ఖండం;
                    px_ఖండం = కుప్ప_PROTECT_ఖండం_సూచిక( px_ఖండం->px_తదుపరి_Free_ఖండం );
                    కుప్ప_VALIDATE_ఖండం_సూచిక( px_ఖండం );
                }

                /* If the end marker was reached then a block of adequate size
                 * was not found. */
                ఒకవేళ( px_ఖండం != px_చివర )
                {
                    /* Return the memory space pointed to - jumping over the
                     * BlockLink_t structure at its start. */
                    pvReturn = ( శూన్య * ) ( ( ( uint8_t * ) కుప్ప_PROTECT_ఖండం_సూచిక( px_మునుపటి_ఖండం->px_తదుపరి_Free_ఖండం ) ) + x_కుప్ప_Struct_కొలత );
                    కుప్ప_VALIDATE_ఖండం_సూచిక( pvReturn );

                    /* This block is being returned for use so must be taken out
                     * of the list of free blocks. */
                    px_మునుపటి_ఖండం->px_తదుపరి_Free_ఖండం = px_ఖండం->px_తదుపరి_Free_ఖండం;

                    /* If the block is larger than required it can be split into
                     * two. */
                    configASSERT( కుప్ప_వ్యవకలనం_WILL_UNDERFLOW( px_ఖండం->x_ఖండం_కొలత, x_Wanted_కొలత ) == 0 );

                    ఒకవేళ( ( px_ఖండం->x_ఖండం_కొలత - x_Wanted_కొలత ) > కుప్ప_MINIMUM_ఖండం_కొలత )
                    {
                        /* This block is to be split into two.  Create a new
                         * block following the number of bytes requested. The void
                         * cast is used to prevent byte alignment warnings from the
                         * compiler. */
                        px_New_ఖండం_Link = ( శూన్య * ) ( ( ( uint8_t * ) px_ఖండం ) + x_Wanted_కొలత );
                        configASSERT( ( ( ( size_t ) px_New_ఖండం_Link ) & పోర్టు_BYTE_ALIGNMENT_ముసుగు ) == 0 );

                        /* Calculate the sizes of two blocks split from the
                         * single block. */
                        px_New_ఖండం_Link->x_ఖండం_కొలత = px_ఖండం->x_ఖండం_కొలత - x_Wanted_కొలత;
                        px_ఖండం->x_ఖండం_కొలత = x_Wanted_కొలత;

                        /* Insert the new block into the list of free blocks. */
                        px_New_ఖండం_Link->px_తదుపరి_Free_ఖండం = px_మునుపటి_ఖండం->px_తదుపరి_Free_ఖండం;
                        px_మునుపటి_ఖండం->px_తదుపరి_Free_ఖండం = కుప్ప_PROTECT_ఖండం_సూచిక( px_New_ఖండం_Link );
                    }
                    లేకపోతే
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Free_బైట్లు_మిగిలిన -= px_ఖండం->x_ఖండం_కొలత;

                    ఒకవేళ( x_Free_బైట్లు_మిగిలిన < x_Minimum_Ever_Free_బైట్లు_మిగిలిన )
                    {
                        x_Minimum_Ever_Free_బైట్లు_మిగిలిన = x_Free_బైట్లు_మిగిలిన;
                    }
                    లేకపోతే
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Allocated_ఖండం_కొలత = px_ఖండం->x_ఖండం_కొలత;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    కుప్ప_ALLOCATE_ఖండం( px_ఖండం );
                    px_ఖండం->px_తదుపరి_Free_ఖండం = కుప్ప_PROTECT_ఖండం_సూచిక( ఖాళీ );
                    x_సంఖ్య_యొక్క_Successful_Allocations++;
                }
                లేకపోతే
                {
                    mtCOVERAGE_TEST_MARKER();
                }
            }
            లేకపోతే
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        లేకపోతే
        {
            mtCOVERAGE_TEST_MARKER();
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
        లేకపోతే
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #అయితే_ముగింపు /* if ( configUSE_MALLOC_FAILED_HOOK == 1 ) */

    configASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) పోర్టు_BYTE_ALIGNMENT_ముసుగు ) == 0 );
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

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( శూన్య * ) puc;

        కుప్ప_VALIDATE_ఖండం_సూచిక( pxLink );
        configASSERT( కుప్ప_ఖండం_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_తదుపరి_Free_ఖండం == కుప్ప_PROTECT_ఖండం_సూచిక( ఖాళీ ) );

        ఒకవేళ( కుప్ప_ఖండం_IS_ALLOCATED( pxLink ) != 0 )
        {
            ఒకవేళ( pxLink->px_తదుపరి_Free_ఖండం == కుప్ప_PROTECT_ఖండం_సూచిక( ఖాళీ ) )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                కుప్ప_FREE_ఖండం( pxLink );
                #ఒకవేళ ( config_కుప్ప_CLEAR_జ్ఞాపకం_ON_FREE == 1 )
                {
                    /* Check for underflow as this can occur if xBlockSize is
                     * overwritten in a heap block. */
                    ఒకవేళ( కుప్ప_వ్యవకలనం_WILL_UNDERFLOW( pxLink->x_ఖండం_కొలత, x_కుప్ప_Struct_కొలత ) == 0 )
                    {
                        ( శూన్య ) memset( puc + x_కుప్ప_Struct_కొలత, 0, pxLink->x_ఖండం_కొలత - x_కుప్ప_Struct_కొలత );
                    }
                }
                #అయితే_ముగింపు

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_బైట్లు_మిగిలిన += pxLink->x_ఖండం_కొలత;
                    traceFREE( pv, pxLink->x_ఖండం_కొలత );
                    prv_చొప్పించు_ఖండం_Into_Free_List( ( ( ఖండం_Link_t * ) pxLink ) );
                    x_సంఖ్య_యొక్క_Successful_Frees++;
                }
                ( శూన్య ) xTaskResumeAll();
            }
            లేకపోతే
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        లేకపోతే
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_పోర్టు_Get_Free_కుప్ప_కొలత( శూన్య )
{
    తిరిగి x_Free_బైట్లు_మిగిలిన;
}
/*-----------------------------------------------------------*/

size_t x_పోర్టు_Get_Minimum_Ever_Free_కుప్ప_కొలత( శూన్య )
{
    తిరిగి x_Minimum_Ever_Free_బైట్లు_మిగిలిన;
}
/*-----------------------------------------------------------*/

శూన్య x_పోర్టు_Reset_కుప్ప_Minimum_Ever_Free_కుప్ప_కొలత( శూన్య )
{
    x_Minimum_Ever_Free_బైట్లు_మిగిలిన = x_Free_బైట్లు_మిగిలిన;
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
    పోర్టు_సూచిక_కొలత_TYPE ux_ప్రారంభం_చిరునామా, ux_చివర_చిరునామా;
    size_t x_మొత్తం_కుప్ప_కొలత = config_మొత్తం_కుప్ప_కొలత;

    /* Ensure the heap starts on a correctly aligned boundary. */
    ux_ప్రారంభం_చిరునామా = ( పోర్టు_సూచిక_కొలత_TYPE ) uc_కుప్ప;

    ఒకవేళ( ( ux_ప్రారంభం_చిరునామా & పోర్టు_BYTE_ALIGNMENT_ముసుగు ) != 0 )
    {
        ux_ప్రారంభం_చిరునామా += ( పోర్టు_BYTE_ALIGNMENT - 1 );
        ux_ప్రారంభం_చిరునామా &= ~( ( పోర్టు_సూచిక_కొలత_TYPE ) పోర్టు_BYTE_ALIGNMENT_ముసుగు );
        x_మొత్తం_కుప్ప_కొలత -= ( size_t ) ( ux_ప్రారంభం_చిరునామా - ( పోర్టు_సూచిక_కొలత_TYPE ) uc_కుప్ప );
    }

    #ఒకవేళ ( config_ENABLE_కుప్ప_PROTECTOR == 1 )
    {
        v_Application_Get_Random_కుప్ప_Canary( &( x_కుప్ప_Canary ) );
    }
    #అయితే_ముగింపు

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_ప్రారంభం.px_తదుపరి_Free_ఖండం = ( శూన్య * ) కుప్ప_PROTECT_ఖండం_సూచిక( ux_ప్రారంభం_చిరునామా );
    x_ప్రారంభం.x_ఖండం_కొలత = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    ux_చివర_చిరునామా = ux_ప్రారంభం_చిరునామా + ( పోర్టు_సూచిక_కొలత_TYPE ) x_మొత్తం_కుప్ప_కొలత;
    ux_చివర_చిరునామా -= ( పోర్టు_సూచిక_కొలత_TYPE ) x_కుప్ప_Struct_కొలత;
    ux_చివర_చిరునామా &= ~( ( పోర్టు_సూచిక_కొలత_TYPE ) పోర్టు_BYTE_ALIGNMENT_ముసుగు );
    px_చివర = ( ఖండం_Link_t * ) ux_చివర_చిరునామా;
    px_చివర->x_ఖండం_కొలత = 0;
    px_చివర->px_తదుపరి_Free_ఖండం = కుప్ప_PROTECT_ఖండం_సూచిక( ఖాళీ );

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    px_మొదటి_Free_ఖండం = ( ఖండం_Link_t * ) ux_ప్రారంభం_చిరునామా;
    px_మొదటి_Free_ఖండం->x_ఖండం_కొలత = ( size_t ) ( ux_చివర_చిరునామా - ( పోర్టు_సూచిక_కొలత_TYPE ) px_మొదటి_Free_ఖండం );
    px_మొదటి_Free_ఖండం->px_తదుపరి_Free_ఖండం = కుప్ప_PROTECT_ఖండం_సూచిక( px_చివర );

    /* Only one block exists - and it covers the entire usable heap space. */
    x_Minimum_Ever_Free_బైట్లు_మిగిలిన = px_మొదటి_Free_ఖండం->x_ఖండం_కొలత;
    x_Free_బైట్లు_మిగిలిన = px_మొదటి_Free_ఖండం->x_ఖండం_కొలత;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_చొప్పించు_ఖండం_Into_Free_List( ఖండం_Link_t * px_ఖండం_గమ్యం_చొప్పించు ) /* PRIVILEGED_FUNCTION */
{
    ఖండం_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    కొరకు( pxIterator = &x_ప్రారంభం; కుప్ప_PROTECT_ఖండం_సూచిక( pxIterator->px_తదుపరి_Free_ఖండం ) < px_ఖండం_గమ్యం_చొప్పించు; pxIterator = కుప్ప_PROTECT_ఖండం_సూచిక( pxIterator->px_తదుపరి_Free_ఖండం ) )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    ఒకవేళ( pxIterator != &x_ప్రారంభం )
    {
        కుప్ప_VALIDATE_ఖండం_సూచిక( pxIterator );
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    ఒకవేళ( ( puc + pxIterator->x_ఖండం_కొలత ) == ( uint8_t * ) px_ఖండం_గమ్యం_చొప్పించు )
    {
        pxIterator->x_ఖండం_కొలత += px_ఖండం_గమ్యం_చొప్పించు->x_ఖండం_కొలత;
        px_ఖండం_గమ్యం_చొప్పించు = pxIterator;
    }
    లేకపోతే
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_ఖండం_గమ్యం_చొప్పించు;

    ఒకవేళ( ( puc + px_ఖండం_గమ్యం_చొప్పించు->x_ఖండం_కొలత ) == ( uint8_t * ) కుప్ప_PROTECT_ఖండం_సూచిక( pxIterator->px_తదుపరి_Free_ఖండం ) )
    {
        ఒకవేళ( కుప్ప_PROTECT_ఖండం_సూచిక( pxIterator->px_తదుపరి_Free_ఖండం ) != px_చివర )
        {
            /* Form one big block from the two blocks. */
            px_ఖండం_గమ్యం_చొప్పించు->x_ఖండం_కొలత += కుప్ప_PROTECT_ఖండం_సూచిక( pxIterator->px_తదుపరి_Free_ఖండం )->x_ఖండం_కొలత;
            px_ఖండం_గమ్యం_చొప్పించు->px_తదుపరి_Free_ఖండం = కుప్ప_PROTECT_ఖండం_సూచిక( pxIterator->px_తదుపరి_Free_ఖండం )->px_తదుపరి_Free_ఖండం;
        }
        లేకపోతే
        {
            px_ఖండం_గమ్యం_చొప్పించు->px_తదుపరి_Free_ఖండం = కుప్ప_PROTECT_ఖండం_సూచిక( px_చివర );
        }
    }
    లేకపోతే
    {
        px_ఖండం_గమ్యం_చొప్పించు->px_తదుపరి_Free_ఖండం = pxIterator->px_తదుపరి_Free_ఖండం;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    ఒకవేళ( pxIterator != px_ఖండం_గమ్యం_చొప్పించు )
    {
        pxIterator->px_తదుపరి_Free_ఖండం = కుప్ప_PROTECT_ఖండం_సూచిక( px_ఖండం_గమ్యం_చొప్పించు );
    }
    లేకపోతే
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Get_కుప్ప_Stats( కుప్ప_Stats_t * px_కుప్ప_Stats )
{
    ఖండం_Link_t * px_ఖండం;
    size_t x_ఖండాలు = 0, x_Max_కొలత = 0, x_Min_కొలత = SIZE_MAX;

    vTaskSuspendAll();
    {
        px_ఖండం = కుప్ప_PROTECT_ఖండం_సూచిక( x_ప్రారంభం.px_తదుపరి_Free_ఖండం );

        /* pxBlock will be NULL if the heap has not been initialised.  The heap
         * is initialised automatically when the first allocation is made. */
        ఒకవేళ( px_ఖండం != ఖాళీ )
        {
            అయితే( px_ఖండం != px_చివర )
            {
                /* Increment the number of blocks and record the largest block seen
                 * so far. */
                x_ఖండాలు++;

                ఒకవేళ( px_ఖండం->x_ఖండం_కొలత > x_Max_కొలత )
                {
                    x_Max_కొలత = px_ఖండం->x_ఖండం_కొలత;
                }

                ఒకవేళ( px_ఖండం->x_ఖండం_కొలత < x_Min_కొలత )
                {
                    x_Min_కొలత = px_ఖండం->x_ఖండం_కొలత;
                }

                /* Move to the next block in the chain until the last block is
                 * reached. */
                px_ఖండం = కుప్ప_PROTECT_ఖండం_సూచిక( px_ఖండం->px_తదుపరి_Free_ఖండం );
            }
        }
    }
    ( శూన్య ) xTaskResumeAll();

    px_కుప్ప_Stats->x_కొలత_యొక్క_అతిపెద్ద_Free_ఖండం_లోపల_బైట్లు = x_Max_కొలత;
    px_కుప్ప_Stats->x_కొలత_యొక్క_అతిచిన్న_Free_ఖండం_లోపల_బైట్లు = x_Min_కొలత;
    px_కుప్ప_Stats->x_సంఖ్య_యొక్క_Free_ఖండాలు = x_ఖండాలు;

    taskENTER_CRITICAL();
    {
        px_కుప్ప_Stats->x_అందుబాటు_కుప్ప_Space_లోపల_బైట్లు = x_Free_బైట్లు_మిగిలిన;
        px_కుప్ప_Stats->x_సంఖ్య_యొక్క_Successful_Allocations = x_సంఖ్య_యొక్క_Successful_Allocations;
        px_కుప్ప_Stats->x_సంఖ్య_యొక్క_Successful_Frees = x_సంఖ్య_యొక్క_Successful_Frees;
        px_కుప్ప_Stats->x_Minimum_Ever_Free_బైట్లు_మిగిలిన = x_Minimum_Ever_Free_బైట్లు_మిగిలిన;
    }
    taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
శూన్య v_పోర్టు_కుప్ప_Reset_State( శూన్య )
{
    px_చివర = ఖాళీ;

    x_Free_బైట్లు_మిగిలిన = ( size_t ) 0U;
    x_Minimum_Ever_Free_బైట్లు_మిగిలిన = ( size_t ) 0U;
    x_సంఖ్య_యొక్క_Successful_Allocations = ( size_t ) 0U;
    x_సంఖ్య_యొక్క_Successful_Frees = ( size_t ) 0U;
}
/*-----------------------------------------------------------*/
