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

/* Block sizes must not get too small. */
#परिभाषय heap_MINIMUM_खण्डम्_आकार    ( ( size_t ) ( x_Heap_Struct_आकार << 1 ) )

/* Assumes 8bit bytes! */
#परिभाषय heap_द्वयङ्काः_प्रत्येकम्_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#परिभाषय heap_आकार_MAX              ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#परिभाषय heap_MULTIPLY_WILL_अतिप्रवाहः( a, b )     ( ( ( a ) > 0 ) && ( ( b ) > ( heap_आकार_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#परिभाषय heap_सङ्कलय_WILL_अतिप्रवाहः( a, b )          ( ( a ) > ( heap_आकार_MAX - ( b ) ) )

/* Check if the subtraction operation ( a - b ) will result in underflow. */
#परिभाषय heap_व्यवकलय_WILL_UNDERFLOW( a, b )    ( ( a ) < ( b ) )

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
 * of their memory address. */
प्रकारनिर्देश संरचना A_खण्डम्_LINK
{
    संरचना A_खण्डम्_LINK * px_अग्र_Free_खण्डम्; /**< The next free block in the list. */
    size_t x_खण्डम्_आकार;                     /**< The size of the free block. */
} खण्डम्_Link_t;

/* Setting configENABLE_HEAP_PROTECTOR to 1 enables heap block pointers
 * protection using an application supplied canary value to catch heap
 * corruption should a heap buffer overflow occur.
 */
#यदि ( configENABLE_HEAP_PROTECTOR == 1 )

/**
 * @brief Application provided function to get a random value to be used as canary.
 *
 * @param pxHeapCanary [out] Output parameter to return the canary value.
 */
    बाह्य शून्य vApplicationGetRandomHeapCanary( पत्तनम्_POINTER_आकार_TYPE * pxHeapCanary );

/* Canary value for protecting internal heap pointers. */
    PRIVILEGED_दत्त स्थिर पत्तनम्_POINTER_आकार_TYPE xHeapCanary;

/* Macro to load/store BlockLink_t pointers to memory. By XORing the
 * pointers with a random canary value, heap overflows will result
 * in randomly unpredictable pointer values which will be caught by
 * heapVALIDATE_BLOCK_POINTER assert. */
    #परिभाषय heap_PROTECT_खण्डम्_POINTER( px_खण्डम् )    ( ( खण्डम्_Link_t * ) ( ( ( पत्तनम्_POINTER_आकार_TYPE ) ( px_खण्डम् ) ) ^ xHeapCanary ) )
#अन्यथा

    #परिभाषय heap_PROTECT_खण्डम्_POINTER( px_खण्डम् )    ( px_खण्डम् )

#यदि_अन्तः /* configENABLE_HEAP_PROTECTOR */

/* Assert that a heap block pointer is within the heap bounds. */
#परिभाषय heap_VALIDATE_खण्डम्_POINTER( px_खण्डम् )                          \
    configASSERT( ( ( uint8_t * ) ( px_खण्डम् ) >= &( ucHeap[ 0 ] ) ) && \
                  ( ( uint8_t * ) ( px_खण्डम् ) <= &( ucHeap[ config_योग_HEAP_आकार - 1 ] ) ) )

/*-----------------------------------------------------------*/

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
स्थिर शून्य prv_निवेशय_खण्डम्_Into_Free_List( खण्डम्_Link_t * px_खण्डम्_गन्तव्यम्_निवेशय ) PRIVILEGED_FUNCTION;

/*
 * Called automatically to setup the required heap structures the first time
 * pvPortMalloc() is called.
 */
स्थिर शून्य prvHeapInit( शून्य ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* The size of the structure placed at the beginning of each allocated memory
 * block must by correctly byte aligned. */
स्थिर ध्रुव size_t x_Heap_Struct_आकार = ( परिमाण( खण्डम्_Link_t ) + ( ( size_t ) ( पत्तनम्_BYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) पत्तनम्_BYTE_ALIGNMENT_आवरणम् );

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_दत्त स्थिर खण्डम्_Link_t xStart;
PRIVILEGED_दत्त स्थिर खण्डम्_Link_t * px_अन्तः = रिक्त;

/* Keeps track of the number of calls to allocate and free memory as well as the
 * number of free bytes remaining, but says nothing about fragmentation. */
PRIVILEGED_दत्त स्थिर size_t x_Free_अष्टकानि_Remaining = ( size_t ) 0U;
PRIVILEGED_दत्त स्थिर size_t x_Minimum_Ever_Free_अष्टकानि_Remaining = ( size_t ) 0U;
PRIVILEGED_दत्त स्थिर size_t x_सङ्ख्या_सम्बन्धि_Successful_Allocations = ( size_t ) 0U;
PRIVILEGED_दत्त स्थिर size_t x_सङ्ख्या_सम्बन्धि_Successful_Frees = ( size_t ) 0U;

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
        यदि( px_अन्तः == रिक्त )
        {
            prvHeapInit();
        }
        अन्यथा
        {
            mtCOVERAGE_TEST_MARKER();
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        यदि( heap_खण्डम्_आकार_IS_VALID( x_Wanted_आकार ) != 0 )
        {
            यदि( ( x_Wanted_आकार > 0 ) && ( x_Wanted_आकार <= x_Free_अष्टकानि_Remaining ) )
            {
                /* Traverse the list from the start (lowest address) block until
                 * one of adequate size is found. */
                px_Previous_खण्डम् = &xStart;
                px_खण्डम् = heap_PROTECT_खण्डम्_POINTER( xStart.px_अग्र_Free_खण्डम् );
                heap_VALIDATE_खण्डम्_POINTER( px_खण्डम् );

                यावत्( ( px_खण्डम्->x_खण्डम्_आकार < x_Wanted_आकार ) && ( px_खण्डम्->px_अग्र_Free_खण्डम् != heap_PROTECT_खण्डम्_POINTER( रिक्त ) ) )
                {
                    px_Previous_खण्डम् = px_खण्डम्;
                    px_खण्डम् = heap_PROTECT_खण्डम्_POINTER( px_खण्डम्->px_अग्र_Free_खण्डम् );
                    heap_VALIDATE_खण्डम्_POINTER( px_खण्डम् );
                }

                /* If the end marker was reached then a block of adequate size
                 * was not found. */
                यदि( px_खण्डम् != px_अन्तः )
                {
                    /* Return the memory space pointed to - jumping over the
                     * BlockLink_t structure at its start. */
                    pvReturn = ( शून्य * ) ( ( ( uint8_t * ) heap_PROTECT_खण्डम्_POINTER( px_Previous_खण्डम्->px_अग्र_Free_खण्डम् ) ) + x_Heap_Struct_आकार );
                    heap_VALIDATE_खण्डम्_POINTER( pvReturn );

                    /* This block is being returned for use so must be taken out
                     * of the list of free blocks. */
                    px_Previous_खण्डम्->px_अग्र_Free_खण्डम् = px_खण्डम्->px_अग्र_Free_खण्डम्;

                    /* If the block is larger than required it can be split into
                     * two. */
                    configASSERT( heap_व्यवकलय_WILL_UNDERFLOW( px_खण्डम्->x_खण्डम्_आकार, x_Wanted_आकार ) == 0 );

                    यदि( ( px_खण्डम्->x_खण्डम्_आकार - x_Wanted_आकार ) > heap_MINIMUM_खण्डम्_आकार )
                    {
                        /* This block is to be split into two.  Create a new
                         * block following the number of bytes requested. The void
                         * cast is used to prevent byte alignment warnings from the
                         * compiler. */
                        px_New_खण्डम्_Link = ( शून्य * ) ( ( ( uint8_t * ) px_खण्डम् ) + x_Wanted_आकार );
                        configASSERT( ( ( ( size_t ) px_New_खण्डम्_Link ) & पत्तनम्_BYTE_ALIGNMENT_आवरणम् ) == 0 );

                        /* Calculate the sizes of two blocks split from the
                         * single block. */
                        px_New_खण्डम्_Link->x_खण्डम्_आकार = px_खण्डम्->x_खण्डम्_आकार - x_Wanted_आकार;
                        px_खण्डम्->x_खण्डम्_आकार = x_Wanted_आकार;

                        /* Insert the new block into the list of free blocks. */
                        px_New_खण्डम्_Link->px_अग्र_Free_खण्डम् = px_Previous_खण्डम्->px_अग्र_Free_खण्डम्;
                        px_Previous_खण्डम्->px_अग्र_Free_खण्डम् = heap_PROTECT_खण्डम्_POINTER( px_New_खण्डम्_Link );
                    }
                    अन्यथा
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Free_अष्टकानि_Remaining -= px_खण्डम्->x_खण्डम्_आकार;

                    यदि( x_Free_अष्टकानि_Remaining < x_Minimum_Ever_Free_अष्टकानि_Remaining )
                    {
                        x_Minimum_Ever_Free_अष्टकानि_Remaining = x_Free_अष्टकानि_Remaining;
                    }
                    अन्यथा
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Allocated_खण्डम्_आकार = px_खण्डम्->x_खण्डम्_आकार;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    heap_ALLOCATE_खण्डम्( px_खण्डम् );
                    px_खण्डम्->px_अग्र_Free_खण्डम् = heap_PROTECT_खण्डम्_POINTER( रिक्त );
                    x_सङ्ख्या_सम्बन्धि_Successful_Allocations++;
                }
                अन्यथा
                {
                    mtCOVERAGE_TEST_MARKER();
                }
            }
            अन्यथा
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        अन्यथा
        {
            mtCOVERAGE_TEST_MARKER();
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
        अन्यथा
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #यदि_अन्तः /* if ( configUSE_MALLOC_FAILED_HOOK == 1 ) */

    configASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) पत्तनम्_BYTE_ALIGNMENT_आवरणम् ) == 0 );
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

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( शून्य * ) puc;

        heap_VALIDATE_खण्डम्_POINTER( pxLink );
        configASSERT( heap_खण्डम्_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_अग्र_Free_खण्डम् == heap_PROTECT_खण्डम्_POINTER( रिक्त ) );

        यदि( heap_खण्डम्_IS_ALLOCATED( pxLink ) != 0 )
        {
            यदि( pxLink->px_अग्र_Free_खण्डम् == heap_PROTECT_खण्डम्_POINTER( रिक्त ) )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                heap_FREE_खण्डम्( pxLink );
                #यदि ( config_HEAP_CLEAR_स्मृतिः_ON_FREE == 1 )
                {
                    /* Check for underflow as this can occur if xBlockSize is
                     * overwritten in a heap block. */
                    यदि( heap_व्यवकलय_WILL_UNDERFLOW( pxLink->x_खण्डम्_आकार, x_Heap_Struct_आकार ) == 0 )
                    {
                        ( शून्य ) स्मृतिं_पूरय( puc + x_Heap_Struct_आकार, 0, pxLink->x_खण्डम्_आकार - x_Heap_Struct_आकार );
                    }
                }
                #यदि_अन्तः

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_अष्टकानि_Remaining += pxLink->x_खण्डम्_आकार;
                    traceFREE( pv, pxLink->x_खण्डम्_आकार );
                    prv_निवेशय_खण्डम्_Into_Free_List( ( ( खण्डम्_Link_t * ) pxLink ) );
                    x_सङ्ख्या_सम्बन्धि_Successful_Frees++;
                }
                ( शून्य ) xTaskResumeAll();
            }
            अन्यथा
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        अन्यथा
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_पत्तनम्_Get_Free_Heap_आकार( शून्य )
{
    प्रत्यागम x_Free_अष्टकानि_Remaining;
}
/*-----------------------------------------------------------*/

size_t x_पत्तनम्_Get_Minimum_Ever_Free_Heap_आकार( शून्य )
{
    प्रत्यागम x_Minimum_Ever_Free_अष्टकानि_Remaining;
}
/*-----------------------------------------------------------*/

शून्य x_पत्तनम्_Reset_Heap_Minimum_Ever_Free_Heap_आकार( शून्य )
{
    x_Minimum_Ever_Free_अष्टकानि_Remaining = x_Free_अष्टकानि_Remaining;
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
    पत्तनम्_POINTER_आकार_TYPE ux_Start_स्थानाङ्कः, ux_अन्तः_स्थानाङ्कः;
    size_t x_योग_Heap_आकार = config_योग_HEAP_आकार;

    /* Ensure the heap starts on a correctly aligned boundary. */
    ux_Start_स्थानाङ्कः = ( पत्तनम्_POINTER_आकार_TYPE ) ucHeap;

    यदि( ( ux_Start_स्थानाङ्कः & पत्तनम्_BYTE_ALIGNMENT_आवरणम् ) != 0 )
    {
        ux_Start_स्थानाङ्कः += ( पत्तनम्_BYTE_ALIGNMENT - 1 );
        ux_Start_स्थानाङ्कः &= ~( ( पत्तनम्_POINTER_आकार_TYPE ) पत्तनम्_BYTE_ALIGNMENT_आवरणम् );
        x_योग_Heap_आकार -= ( size_t ) ( ux_Start_स्थानाङ्कः - ( पत्तनम्_POINTER_आकार_TYPE ) ucHeap );
    }

    #यदि ( configENABLE_HEAP_PROTECTOR == 1 )
    {
        vApplicationGetRandomHeapCanary( &( xHeapCanary ) );
    }
    #यदि_अन्तः

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    xStart.px_अग्र_Free_खण्डम् = ( शून्य * ) heap_PROTECT_खण्डम्_POINTER( ux_Start_स्थानाङ्कः );
    xStart.x_खण्डम्_आकार = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    ux_अन्तः_स्थानाङ्कः = ux_Start_स्थानाङ्कः + ( पत्तनम्_POINTER_आकार_TYPE ) x_योग_Heap_आकार;
    ux_अन्तः_स्थानाङ्कः -= ( पत्तनम्_POINTER_आकार_TYPE ) x_Heap_Struct_आकार;
    ux_अन्तः_स्थानाङ्कः &= ~( ( पत्तनम्_POINTER_आकार_TYPE ) पत्तनम्_BYTE_ALIGNMENT_आवरणम् );
    px_अन्तः = ( खण्डम्_Link_t * ) ux_अन्तः_स्थानाङ्कः;
    px_अन्तः->x_खण्डम्_आकार = 0;
    px_अन्तः->px_अग्र_Free_खण्डम् = heap_PROTECT_खण्डम्_POINTER( रिक्त );

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    px_First_Free_खण्डम् = ( खण्डम्_Link_t * ) ux_Start_स्थानाङ्कः;
    px_First_Free_खण्डम्->x_खण्डम्_आकार = ( size_t ) ( ux_अन्तः_स्थानाङ्कः - ( पत्तनम्_POINTER_आकार_TYPE ) px_First_Free_खण्डम् );
    px_First_Free_खण्डम्->px_अग्र_Free_खण्डम् = heap_PROTECT_खण्डम्_POINTER( px_अन्तः );

    /* Only one block exists - and it covers the entire usable heap space. */
    x_Minimum_Ever_Free_अष्टकानि_Remaining = px_First_Free_खण्डम्->x_खण्डम्_आकार;
    x_Free_अष्टकानि_Remaining = px_First_Free_खण्डम्->x_खण्डम्_आकार;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_निवेशय_खण्डम्_Into_Free_List( खण्डम्_Link_t * px_खण्डम्_गन्तव्यम्_निवेशय ) /* PRIVILEGED_FUNCTION */
{
    खण्डम्_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    प्रति( pxIterator = &xStart; heap_PROTECT_खण्डम्_POINTER( pxIterator->px_अग्र_Free_खण्डम् ) < px_खण्डम्_गन्तव्यम्_निवेशय; pxIterator = heap_PROTECT_खण्डम्_POINTER( pxIterator->px_अग्र_Free_खण्डम् ) )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    यदि( pxIterator != &xStart )
    {
        heap_VALIDATE_खण्डम्_POINTER( pxIterator );
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    यदि( ( puc + pxIterator->x_खण्डम्_आकार ) == ( uint8_t * ) px_खण्डम्_गन्तव्यम्_निवेशय )
    {
        pxIterator->x_खण्डम्_आकार += px_खण्डम्_गन्तव्यम्_निवेशय->x_खण्डम्_आकार;
        px_खण्डम्_गन्तव्यम्_निवेशय = pxIterator;
    }
    अन्यथा
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_खण्डम्_गन्तव्यम्_निवेशय;

    यदि( ( puc + px_खण्डम्_गन्तव्यम्_निवेशय->x_खण्डम्_आकार ) == ( uint8_t * ) heap_PROTECT_खण्डम्_POINTER( pxIterator->px_अग्र_Free_खण्डम् ) )
    {
        यदि( heap_PROTECT_खण्डम्_POINTER( pxIterator->px_अग्र_Free_खण्डम् ) != px_अन्तः )
        {
            /* Form one big block from the two blocks. */
            px_खण्डम्_गन्तव्यम्_निवेशय->x_खण्डम्_आकार += heap_PROTECT_खण्डम्_POINTER( pxIterator->px_अग्र_Free_खण्डम् )->x_खण्डम्_आकार;
            px_खण्डम्_गन्तव्यम्_निवेशय->px_अग्र_Free_खण्डम् = heap_PROTECT_खण्डम्_POINTER( pxIterator->px_अग्र_Free_खण्डम् )->px_अग्र_Free_खण्डम्;
        }
        अन्यथा
        {
            px_खण्डम्_गन्तव्यम्_निवेशय->px_अग्र_Free_खण्डम् = heap_PROTECT_खण्डम्_POINTER( px_अन्तः );
        }
    }
    अन्यथा
    {
        px_खण्डम्_गन्तव्यम्_निवेशय->px_अग्र_Free_खण्डम् = pxIterator->px_अग्र_Free_खण्डम्;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    यदि( pxIterator != px_खण्डम्_गन्तव्यम्_निवेशय )
    {
        pxIterator->px_अग्र_Free_खण्डम् = heap_PROTECT_खण्डम्_POINTER( px_खण्डम्_गन्तव्यम्_निवेशय );
    }
    अन्यथा
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Get_Heap_Stats( HeapStats_t * pxHeapStats )
{
    खण्डम्_Link_t * px_खण्डम्;
    size_t x_खण्डानि = 0, x_Max_आकार = 0, x_Min_आकार = SIZE_MAX;

    vTaskSuspendAll();
    {
        px_खण्डम् = heap_PROTECT_खण्डम्_POINTER( xStart.px_अग्र_Free_खण्डम् );

        /* pxBlock will be NULL if the heap has not been initialised.  The heap
         * is initialised automatically when the first allocation is made. */
        यदि( px_खण्डम् != रिक्त )
        {
            यावत्( px_खण्डम् != px_अन्तः )
            {
                /* Increment the number of blocks and record the largest block seen
                 * so far. */
                x_खण्डानि++;

                यदि( px_खण्डम्->x_खण्डम्_आकार > x_Max_आकार )
                {
                    x_Max_आकार = px_खण्डम्->x_खण्डम्_आकार;
                }

                यदि( px_खण्डम्->x_खण्डम्_आकार < x_Min_आकार )
                {
                    x_Min_आकार = px_खण्डम्->x_खण्डम्_आकार;
                }

                /* Move to the next block in the chain until the last block is
                 * reached. */
                px_खण्डम् = heap_PROTECT_खण्डम्_POINTER( px_खण्डम्->px_अग्र_Free_खण्डम् );
            }
        }
    }
    ( शून्य ) xTaskResumeAll();

    pxHeapStats->x_आकार_सम्बन्धि_Largest_Free_खण्डम्_अन्तर्_अष्टकानि = x_Max_आकार;
    pxHeapStats->x_आकार_सम्बन्धि_Smallest_Free_खण्डम्_अन्तर्_अष्टकानि = x_Min_आकार;
    pxHeapStats->x_सङ्ख्या_सम्बन्धि_Free_खण्डानि = x_खण्डानि;

    taskENTER_CRITICAL();
    {
        pxHeapStats->x_उपलब्धम्_Heap_Space_अन्तर्_अष्टकानि = x_Free_अष्टकानि_Remaining;
        pxHeapStats->x_सङ्ख्या_सम्बन्धि_Successful_Allocations = x_सङ्ख्या_सम्बन्धि_Successful_Allocations;
        pxHeapStats->x_सङ्ख्या_सम्बन्धि_Successful_Frees = x_सङ्ख्या_सम्बन्धि_Successful_Frees;
        pxHeapStats->x_Minimum_Ever_Free_अष्टकानि_Remaining = x_Minimum_Ever_Free_अष्टकानि_Remaining;
    }
    taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
शून्य v_पत्तनम्_Heap_Reset_State( शून्य )
{
    px_अन्तः = रिक्त;

    x_Free_अष्टकानि_Remaining = ( size_t ) 0U;
    x_Minimum_Ever_Free_अष्टकानि_Remaining = ( size_t ) 0U;
    x_सङ्ख्या_सम्बन्धि_Successful_Allocations = ( size_t ) 0U;
    x_सङ्ख्या_सम्बन्धि_Successful_Frees = ( size_t ) 0U;
}
/*-----------------------------------------------------------*/
