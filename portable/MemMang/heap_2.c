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
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#परिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

#अपरिभाषय MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#यदि ( config_SUPPORT_DYNAMIC_आवण्टनम् == 0 )
    #दोषः This file must not be प्रयुक्तम् यदि config_SUPPORT_DYNAMIC_आवण्टनम् is 0
#यदि_अन्तः

#यदि_अपरिभाषितम् config_HEAP_CLEAR_स्मृतिः_ON_FREE
    #परिभाषय config_HEAP_CLEAR_स्मृतिः_ON_FREE    0
#यदि_अन्तः

/* A few bytes might be lost to byte aligning the heap start address. */
#परिभाषय config_ADJUSTED_HEAP_आकार    ( config_योग_HEAP_आकार - पत्तनम्_BYTE_ALIGNMENT )

/* Assumes 8bit bytes! */
#परिभाषय heap_द्वयङ्काः_प्रत्येकम्_BYTE           ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#परिभाषय heap_आकार_MAX                ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#परिभाषय heap_MULTIPLY_WILL_अतिप्रवाहः( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( heap_आकार_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#परिभाषय heap_सङ्कलय_WILL_अतिप्रवाहः( a, b )         ( ( a ) > ( heap_आकार_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#परिभाषय heap_खण्डम्_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( परिमाण( size_t ) * heap_द्वयङ्काः_प्रत्येकम्_BYTE ) - 1 ) )
#परिभाषय heap_खण्डम्_आकार_IS_VALID( x_खण्डम्_आकार )    ( ( ( x_खण्डम्_आकार ) & heap_खण्डम्_ALLOCATED_BITMASK ) == 0 )
#परिभाषय heap_खण्डम्_IS_ALLOCATED( px_खण्डम् )        ( ( ( px_खण्डम्->x_खण्डम्_आकार ) & heap_खण्डम्_ALLOCATED_BITMASK ) != 0 )
#परिभाषय heap_ALLOCATE_खण्डम्( px_खण्डम् )            ( ( px_खण्डम्->x_खण्डम्_आकार ) |= heap_खण्डम्_ALLOCATED_BITMASK )
#परिभाषय heap_FREE_खण्डम्( px_खण्डम् )                ( ( px_खण्डम्->x_खण्डम्_आकार ) &= ~heap_खण्डम्_ALLOCATED_BITMASK )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#यदि ( configAPPLICATION_ALLOCATED_HEAP == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    बाह्य uint8_t ucHeap[ config_योग_HEAP_आकार ];
#अन्यथा
    PRIVILEGED_दत्त स्थिर uint8_t ucHeap[ config_योग_HEAP_आकार ];
#यदि_अन्तः /* configAPPLICATION_ALLOCATED_HEAP */


/* Define the linked list structure.  This is used to link free blocks in order
 * of their size. */
प्रकारनिर्देश संरचना A_खण्डम्_LINK
{
    संरचना A_खण्डम्_LINK * px_अग्र_Free_खण्डम्; /*<< The next free block in the list. */
    size_t x_खण्डम्_आकार;                     /*<< The size of the free block. */
} खण्डम्_Link_t;


स्थिर ध्रुव size_t x_Heap_Struct_आकार = ( ( परिमाण( खण्डम्_Link_t ) + ( size_t ) ( पत्तनम्_BYTE_ALIGNMENT - 1 ) ) & ~( ( size_t ) पत्तनम्_BYTE_ALIGNMENT_आवरणम् ) );
#परिभाषय heap_MINIMUM_खण्डम्_आकार    ( ( size_t ) ( x_Heap_Struct_आकार * 2 ) )

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_दत्त स्थिर खण्डम्_Link_t xStart, x_अन्तः;

/* Keeps track of the number of free bytes remaining, but says nothing about
 * fragmentation. */
PRIVILEGED_दत्त स्थिर size_t x_Free_अष्टकानि_Remaining = config_ADJUSTED_HEAP_आकार;

/* Indicates whether the heap has been initialised or not. */
PRIVILEGED_दत्त स्थिर आधारः_Type_t xHeapHasBeenInitialised = pdFALSE;

/*-----------------------------------------------------------*/

/*
 * Initialises the heap structures before their first use.
 */
स्थिर शून्य prvHeapInit( शून्य ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* STATIC FUNCTIONS ARE DEFINED AS MACROS TO MINIMIZE THE FUNCTION CALL DEPTH. */

/*
 * Insert a block into the list of free blocks - which is ordered by size of
 * the block.  Small blocks at the start of the list and large blocks at the end
 * of the list.
 */
#परिभाषय prv_निवेशय_खण्डम्_Into_Free_List( px_खण्डम्_गन्तव्यम्_निवेशय )                                                                               \
    {                                                                                                                               \
        खण्डम्_Link_t * pxIterator;                                                                                                   \
        size_t x_खण्डम्_आकार;                                                                                                          \
                                                                                                                                    \
        x_खण्डम्_आकार = px_खण्डम्_गन्तव्यम्_निवेशय->x_खण्डम्_आकार;                                                                                   \
                                                                                                                                    \
        /* Iterate through the list until a block is found that has a larger size */                                                \
        /* than the block we are inserting. */                                                                                      \
        प्रति( pxIterator = &xStart; pxIterator->px_अग्र_Free_खण्डम्->x_खण्डम्_आकार < x_खण्डम्_आकार; pxIterator = pxIterator->px_अग्र_Free_खण्डम् ) \
        {                                                                                                                           \
            /* There is nothing to do here - just iterate to the correct position. */                                               \
        }                                                                                                                           \
                                                                                                                                    \
        /* Update the list to include the block being inserted in the correct */                                                    \
        /* position. */                                                                                                             \
        px_खण्डम्_गन्तव्यम्_निवेशय->px_अग्र_Free_खण्डम् = pxIterator->px_अग्र_Free_खण्डम्;                                                             \
        pxIterator->px_अग्र_Free_खण्डम् = px_खण्डम्_गन्तव्यम्_निवेशय;                                                                              \
    }
/*-----------------------------------------------------------*/

शून्य * pv_पत्तनम्_Malloc( size_t x_Wanted_आकार )
{
    खण्डम्_Link_t * px_खण्डम्;
    खण्डम्_Link_t * px_Previous_खण्डम्;
    खण्डम्_Link_t * px_New_खण्डम्_Link;
    शून्य * pvReturn = रिक्त;
    size_t x_Additional_Required_आकार;
    size_t x_Allocated_खण्डम्_आकार = 0;

    यदि( x_Wanted_आकार > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        यदि( heap_सङ्कलय_WILL_अतिप्रवाहः( x_Wanted_आकार, x_Heap_Struct_आकार ) == 0 )
        {
            x_Wanted_आकार += x_Heap_Struct_आकार;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            यदि( ( x_Wanted_आकार & पत्तनम्_BYTE_ALIGNMENT_आवरणम् ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_आकार = पत्तनम्_BYTE_ALIGNMENT - ( x_Wanted_आकार & पत्तनम्_BYTE_ALIGNMENT_आवरणम् );

                यदि( heap_सङ्कलय_WILL_अतिप्रवाहः( x_Wanted_आकार, x_Additional_Required_आकार ) == 0 )
                {
                    x_Wanted_आकार += x_Additional_Required_आकार;
                }
                अन्यथा
                {
                    x_Wanted_आकार = 0;
                }
            }
            अन्यथा
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        अन्यथा
        {
            x_Wanted_आकार = 0;
        }
    }
    अन्यथा
    {
        mtCOVERAGE_TEST_MARKER();
    }

    vTaskSuspendAll();
    {
        /* If this is the first call to malloc then the heap will require
         * initialisation to setup the list of free blocks. */
        यदि( xHeapHasBeenInitialised == pdFALSE )
        {
            prvHeapInit();
            xHeapHasBeenInitialised = pdTRUE;
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        यदि( heap_खण्डम्_आकार_IS_VALID( x_Wanted_आकार ) != 0 )
        {
            यदि( ( x_Wanted_आकार > 0 ) && ( x_Wanted_आकार <= x_Free_अष्टकानि_Remaining ) )
            {
                /* Blocks are stored in byte order - traverse the list from the start
                 * (smallest) block until one of adequate size is found. */
                px_Previous_खण्डम् = &xStart;
                px_खण्डम् = xStart.px_अग्र_Free_खण्डम्;

                यावत्( ( px_खण्डम्->x_खण्डम्_आकार < x_Wanted_आकार ) && ( px_खण्डम्->px_अग्र_Free_खण्डम् != रिक्त ) )
                {
                    px_Previous_खण्डम् = px_खण्डम्;
                    px_खण्डम् = px_खण्डम्->px_अग्र_Free_खण्डम्;
                }

                /* If we found the end marker then a block of adequate size was not found. */
                यदि( px_खण्डम् != &x_अन्तः )
                {
                    /* Return the memory space - jumping over the BlockLink_t structure
                     * at its start. */
                    pvReturn = ( शून्य * ) ( ( ( uint8_t * ) px_Previous_खण्डम्->px_अग्र_Free_खण्डम् ) + x_Heap_Struct_आकार );

                    /* This block is being returned for use so must be taken out of the
                     * list of free blocks. */
                    px_Previous_खण्डम्->px_अग्र_Free_खण्डम् = px_खण्डम्->px_अग्र_Free_खण्डम्;

                    /* If the block is larger than required it can be split into two. */
                    यदि( ( px_खण्डम्->x_खण्डम्_आकार - x_Wanted_आकार ) > heap_MINIMUM_खण्डम्_आकार )
                    {
                        /* This block is to be split into two.  Create a new block
                         * following the number of bytes requested. The void cast is
                         * used to prevent byte alignment warnings from the compiler. */
                        px_New_खण्डम्_Link = ( शून्य * ) ( ( ( uint8_t * ) px_खण्डम् ) + x_Wanted_आकार );

                        /* Calculate the sizes of two blocks split from the single
                         * block. */
                        px_New_खण्डम्_Link->x_खण्डम्_आकार = px_खण्डम्->x_खण्डम्_आकार - x_Wanted_आकार;
                        px_खण्डम्->x_खण्डम्_आकार = x_Wanted_आकार;

                        /* Insert the new block into the list of free blocks.
                         * The list of free blocks is sorted by their size, we have to
                         * iterate to find the right place to insert new block. */
                        prv_निवेशय_खण्डम्_Into_Free_List( ( px_New_खण्डम्_Link ) );
                    }

                    x_Free_अष्टकानि_Remaining -= px_खण्डम्->x_खण्डम्_आकार;

                    x_Allocated_खण्डम्_आकार = px_खण्डम्->x_खण्डम्_आकार;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    heap_ALLOCATE_खण्डम्( px_खण्डम् );
                    px_खण्डम्->px_अग्र_Free_खण्डम् = रिक्त;
                }
            }
        }

        traceMALLOC( pvReturn, x_Allocated_खण्डम्_आकार );

        /* Prevent compiler warnings when trace macros are not used. */
        ( शून्य ) x_Allocated_खण्डम्_आकार;
    }
    ( शून्य ) xTaskResumeAll();

    #यदि ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        यदि( pvReturn == रिक्त )
        {
            vApplicationMallocFailedHook();
        }
    }
    #यदि_अन्तः

    प्रत्यागम pvReturn;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Free( शून्य * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    खण्डम्_Link_t * pxLink;

    यदि( pv != रिक्त )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_Heap_Struct_आकार;

        /* This unexpected casting is to keep some compilers from issuing
         * byte alignment warnings. */
        pxLink = ( शून्य * ) puc;

        configASSERT( heap_खण्डम्_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_अग्र_Free_खण्डम् == रिक्त );

        यदि( heap_खण्डम्_IS_ALLOCATED( pxLink ) != 0 )
        {
            यदि( pxLink->px_अग्र_Free_खण्डम् == रिक्त )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                heap_FREE_खण्डम्( pxLink );
                #यदि ( config_HEAP_CLEAR_स्मृतिः_ON_FREE == 1 )
                {
                    ( शून्य ) स्मृतिं_पूरय( puc + x_Heap_Struct_आकार, 0, pxLink->x_खण्डम्_आकार - x_Heap_Struct_आकार );
                }
                #यदि_अन्तः

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    prv_निवेशय_खण्डम्_Into_Free_List( ( ( खण्डम्_Link_t * ) pxLink ) );
                    x_Free_अष्टकानि_Remaining += pxLink->x_खण्डम्_आकार;
                    traceFREE( pv, pxLink->x_खण्डम्_आकार );
                }
                ( शून्य ) xTaskResumeAll();
            }
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_पत्तनम्_Get_Free_Heap_आकार( शून्य )
{
    प्रत्यागम x_Free_अष्टकानि_Remaining;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Initialise_खण्डानि( शून्य )
{
    /* This just exists to keep the linker quiet. */
}
/*-----------------------------------------------------------*/

शून्य * pv_पत्तनम्_Calloc( size_t x_अङ्कः,
                     size_t x_आकार )
{
    शून्य * pv = रिक्त;

    यदि( heap_MULTIPLY_WILL_अतिप्रवाहः( x_अङ्कः, x_आकार ) == 0 )
    {
        pv = pv_पत्तनम्_Malloc( x_अङ्कः * x_आकार );

        यदि( pv != रिक्त )
        {
            ( शून्य ) स्मृतिं_पूरय( pv, 0, x_अङ्कः * x_आकार );
        }
    }

    प्रत्यागम pv;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvHeapInit( शून्य ) /* PRIVILEGED_FUNCTION */
{
    खण्डम्_Link_t * px_First_Free_खण्डम्;
    uint8_t * pucAlignedHeap;

    /* Ensure the heap starts on a correctly aligned boundary. */
    pucAlignedHeap = ( uint8_t * ) ( ( ( पत्तनम्_POINTER_आकार_TYPE ) & ucHeap[ पत्तनम्_BYTE_ALIGNMENT - 1 ] ) & ( ~( ( पत्तनम्_POINTER_आकार_TYPE ) पत्तनम्_BYTE_ALIGNMENT_आवरणम् ) ) );

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    xStart.px_अग्र_Free_खण्डम् = ( शून्य * ) pucAlignedHeap;
    xStart.x_खण्डम्_आकार = ( size_t ) 0;

    /* xEnd is used to mark the end of the list of free blocks. */
    x_अन्तः.x_खण्डम्_आकार = config_ADJUSTED_HEAP_आकार;
    x_अन्तः.px_अग्र_Free_खण्डम् = रिक्त;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space. */
    px_First_Free_खण्डम् = ( खण्डम्_Link_t * ) pucAlignedHeap;
    px_First_Free_खण्डम्->x_खण्डम्_आकार = config_ADJUSTED_HEAP_आकार;
    px_First_Free_खण्डम्->px_अग्र_Free_खण्डम् = &x_अन्तः;
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
शून्य v_पत्तनम्_Heap_Reset_State( शून्य )
{
    x_Free_अष्टकानि_Remaining = config_ADJUSTED_HEAP_आकार;

    xHeapHasBeenInitialised = pdFALSE;
}
/*-----------------------------------------------------------*/
