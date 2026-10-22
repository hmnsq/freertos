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
#شامل <stdlib.h>
#شامل <string.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
 * all the API functions to use the MPU wrappers.  That should only be done when
 * task.h is included from an application file. */
#تعریف_کرو MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#شامل "FreeRTOS.h"
#شامل "task.h"

#تعریف_منسوخ MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#اگر ( config_SUPPORT_DYNAMIC_تخصیص == 0 )
    #غلطی This file must not be مستعمل اگر config_SUPPORT_DYNAMIC_تخصیص is 0
#اگر_ختم

#اگر_غیر_تعریف_شدہ config_ڈھیر_CLEAR_حافظہ_ON_FREE
    #تعریف_کرو config_ڈھیر_CLEAR_حافظہ_ON_FREE    0
#اگر_ختم

/* A few bytes might be lost to byte aligning the heap start address. */
#تعریف_کرو config_ADJUSTED_ڈھیر_سائز    ( config_کل_ڈھیر_سائز - پورٹ_BYTE_ALIGNMENT )

/* Assumes 8bit bytes! */
#تعریف_کرو ڈھیر_بٹ_فی_BYTE           ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#تعریف_کرو ڈھیر_سائز_MAX                ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#تعریف_کرو ڈھیر_MULTIPLY_WILL_حد_سے_تجاوز( a, b )    ( ( ( a ) > 0 ) && ( ( b ) > ( ڈھیر_سائز_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کرو ڈھیر_جوڑو_WILL_حد_سے_تجاوز( a, b )         ( ( a ) > ( ڈھیر_سائز_MAX - ( b ) ) )

/* MSB of the xBlockSize member of an BlockLink_t structure is used to track
 * the allocation status of a block.  When MSB of the xBlockSize member of
 * an BlockLink_t structure is set then the block belongs to the application.
 * When the bit is free the block is still part of the free heap space. */
#تعریف_کرو ڈھیر_بلاک_ALLOCATED_BITMASK    ( ( ( size_t ) 1 ) << ( ( حجم( size_t ) * ڈھیر_بٹ_فی_BYTE ) - 1 ) )
#تعریف_کرو ڈھیر_بلاک_سائز_IS_VALID( x_بلاک_سائز )    ( ( ( x_بلاک_سائز ) & ڈھیر_بلاک_ALLOCATED_BITMASK ) == 0 )
#تعریف_کرو ڈھیر_بلاک_IS_ALLOCATED( px_بلاک )        ( ( ( px_بلاک->x_بلاک_سائز ) & ڈھیر_بلاک_ALLOCATED_BITMASK ) != 0 )
#تعریف_کرو ڈھیر_ALLOCATE_بلاک( px_بلاک )            ( ( px_بلاک->x_بلاک_سائز ) |= ڈھیر_بلاک_ALLOCATED_BITMASK )
#تعریف_کرو ڈھیر_FREE_بلاک( px_بلاک )                ( ( px_بلاک->x_بلاک_سائز ) &= ~ڈھیر_بلاک_ALLOCATED_BITMASK )

/*-----------------------------------------------------------*/

/* Allocate the memory for the heap. */
#اگر ( config_APPLICATION_ALLOCATED_ڈھیر == 1 )

/* The application writer has already defined the array used for the RTOS
 * heap - probably so it can be placed in a special segment or address. */
    خارجی uint8_t uc_ڈھیر[ config_کل_ڈھیر_سائز ];
#ورنہ
    PRIVILEGED_ڈیٹا ساکن uint8_t uc_ڈھیر[ config_کل_ڈھیر_سائز ];
#اگر_ختم /* configAPPLICATION_ALLOCATED_HEAP */


/* Define the linked list structure.  This is used to link free blocks in order
 * of their size. */
قسمتعریف ساخت A_بلاک_LINK
{
    ساخت A_بلاک_LINK * px_اگلا_Free_بلاک; /*<< The next free block in the list. */
    size_t x_بلاک_سائز;                     /*<< The size of the free block. */
} بلاک_Link_t;


ساکن ثابت size_t x_ڈھیر_Struct_سائز = ( ( حجم( بلاک_Link_t ) + ( size_t ) ( پورٹ_BYTE_ALIGNMENT - 1 ) ) & ~( ( size_t ) پورٹ_BYTE_ALIGNMENT_نقاب ) );
#تعریف_کرو ڈھیر_MINIMUM_بلاک_سائز    ( ( size_t ) ( x_ڈھیر_Struct_سائز * 2 ) )

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_ڈیٹا ساکن بلاک_Link_t x_آغاز, x_انتہا;

/* Keeps track of the number of free bytes remaining, but says nothing about
 * fragmentation. */
PRIVILEGED_ڈیٹا ساکن size_t x_Free_بائٹیں_بقایا = config_ADJUSTED_ڈھیر_سائز;

/* Indicates whether the heap has been initialised or not. */
PRIVILEGED_ڈیٹا ساکن بنیاد_Type_t x_ڈھیر_Has_Been_Initialised = pdFALSE;

/*-----------------------------------------------------------*/

/*
 * Initialises the heap structures before their first use.
 */
ساکن خالی prv_ڈھیر_Init( خالی ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* STATIC FUNCTIONS ARE DEFINED AS MACROS TO MINIMIZE THE FUNCTION CALL DEPTH. */

/*
 * Insert a block into the list of free blocks - which is ordered by size of
 * the block.  Small blocks at the start of the list and large blocks at the end
 * of the list.
 */
#تعریف_کرو prv_داخل_کرو_بلاک_Into_Free_List( px_بلاک_مقصد_داخل_کرو )                                                                               \
    {                                                                                                                               \
        بلاک_Link_t * pxIterator;                                                                                                   \
        size_t x_بلاک_سائز;                                                                                                          \
                                                                                                                                    \
        x_بلاک_سائز = px_بلاک_مقصد_داخل_کرو->x_بلاک_سائز;                                                                                   \
                                                                                                                                    \
        /* Iterate through the list until a block is found that has a larger size */                                                \
        /* than the block we are inserting. */                                                                                      \
        برائے( pxIterator = &x_آغاز; pxIterator->px_اگلا_Free_بلاک->x_بلاک_سائز < x_بلاک_سائز; pxIterator = pxIterator->px_اگلا_Free_بلاک ) \
        {                                                                                                                           \
            /* There is nothing to do here - just iterate to the correct position. */                                               \
        }                                                                                                                           \
                                                                                                                                    \
        /* Update the list to include the block being inserted in the correct */                                                    \
        /* position. */                                                                                                             \
        px_بلاک_مقصد_داخل_کرو->px_اگلا_Free_بلاک = pxIterator->px_اگلا_Free_بلاک;                                                             \
        pxIterator->px_اگلا_Free_بلاک = px_بلاک_مقصد_داخل_کرو;                                                                              \
    }
/*-----------------------------------------------------------*/

خالی * pv_پورٹ_Malloc( size_t x_Wanted_سائز )
{
    بلاک_Link_t * px_بلاک;
    بلاک_Link_t * px_پچھلا_بلاک;
    بلاک_Link_t * px_New_بلاک_Link;
    خالی * pvReturn = تہی;
    size_t x_Additional_Required_سائز;
    size_t x_Allocated_بلاک_سائز = 0;

    اگر( x_Wanted_سائز > 0 )
    {
        /* The wanted size must be increased so it can contain a BlockLink_t
         * structure in addition to the requested amount of bytes. */
        اگر( ڈھیر_جوڑو_WILL_حد_سے_تجاوز( x_Wanted_سائز, x_ڈھیر_Struct_سائز ) == 0 )
        {
            x_Wanted_سائز += x_ڈھیر_Struct_سائز;

            /* Ensure that blocks are always aligned to the required number
             * of bytes. */
            اگر( ( x_Wanted_سائز & پورٹ_BYTE_ALIGNMENT_نقاب ) != 0x00 )
            {
                /* Byte alignment required. */
                x_Additional_Required_سائز = پورٹ_BYTE_ALIGNMENT - ( x_Wanted_سائز & پورٹ_BYTE_ALIGNMENT_نقاب );

                اگر( ڈھیر_جوڑو_WILL_حد_سے_تجاوز( x_Wanted_سائز, x_Additional_Required_سائز ) == 0 )
                {
                    x_Wanted_سائز += x_Additional_Required_سائز;
                }
                ورنہ
                {
                    x_Wanted_سائز = 0;
                }
            }
            ورنہ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ورنہ
        {
            x_Wanted_سائز = 0;
        }
    }
    ورنہ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    vTaskSuspendAll();
    {
        /* If this is the first call to malloc then the heap will require
         * initialisation to setup the list of free blocks. */
        اگر( x_ڈھیر_Has_Been_Initialised == pdFALSE )
        {
            prv_ڈھیر_Init();
            x_ڈھیر_Has_Been_Initialised = pdTRUE;
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        اگر( ڈھیر_بلاک_سائز_IS_VALID( x_Wanted_سائز ) != 0 )
        {
            اگر( ( x_Wanted_سائز > 0 ) && ( x_Wanted_سائز <= x_Free_بائٹیں_بقایا ) )
            {
                /* Blocks are stored in byte order - traverse the list from the start
                 * (smallest) block until one of adequate size is found. */
                px_پچھلا_بلاک = &x_آغاز;
                px_بلاک = x_آغاز.px_اگلا_Free_بلاک;

                جب( ( px_بلاک->x_بلاک_سائز < x_Wanted_سائز ) && ( px_بلاک->px_اگلا_Free_بلاک != تہی ) )
                {
                    px_پچھلا_بلاک = px_بلاک;
                    px_بلاک = px_بلاک->px_اگلا_Free_بلاک;
                }

                /* If we found the end marker then a block of adequate size was not found. */
                اگر( px_بلاک != &x_انتہا )
                {
                    /* Return the memory space - jumping over the BlockLink_t structure
                     * at its start. */
                    pvReturn = ( خالی * ) ( ( ( uint8_t * ) px_پچھلا_بلاک->px_اگلا_Free_بلاک ) + x_ڈھیر_Struct_سائز );

                    /* This block is being returned for use so must be taken out of the
                     * list of free blocks. */
                    px_پچھلا_بلاک->px_اگلا_Free_بلاک = px_بلاک->px_اگلا_Free_بلاک;

                    /* If the block is larger than required it can be split into two. */
                    اگر( ( px_بلاک->x_بلاک_سائز - x_Wanted_سائز ) > ڈھیر_MINIMUM_بلاک_سائز )
                    {
                        /* This block is to be split into two.  Create a new block
                         * following the number of bytes requested. The void cast is
                         * used to prevent byte alignment warnings from the compiler. */
                        px_New_بلاک_Link = ( خالی * ) ( ( ( uint8_t * ) px_بلاک ) + x_Wanted_سائز );

                        /* Calculate the sizes of two blocks split from the single
                         * block. */
                        px_New_بلاک_Link->x_بلاک_سائز = px_بلاک->x_بلاک_سائز - x_Wanted_سائز;
                        px_بلاک->x_بلاک_سائز = x_Wanted_سائز;

                        /* Insert the new block into the list of free blocks.
                         * The list of free blocks is sorted by their size, we have to
                         * iterate to find the right place to insert new block. */
                        prv_داخل_کرو_بلاک_Into_Free_List( ( px_New_بلاک_Link ) );
                    }

                    x_Free_بائٹیں_بقایا -= px_بلاک->x_بلاک_سائز;

                    x_Allocated_بلاک_سائز = px_بلاک->x_بلاک_سائز;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    ڈھیر_ALLOCATE_بلاک( px_بلاک );
                    px_بلاک->px_اگلا_Free_بلاک = تہی;
                }
            }
        }

        traceMALLOC( pvReturn, x_Allocated_بلاک_سائز );

        /* Prevent compiler warnings when trace macros are not used. */
        ( خالی ) x_Allocated_بلاک_سائز;
    }
    ( خالی ) xTaskResumeAll();

    #اگر ( configUSE_MALLOC_FAILED_HOOK == 1 )
    {
        اگر( pvReturn == تہی )
        {
            vApplicationMallocFailedHook();
        }
    }
    #اگر_ختم

    واپس pvReturn;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Free( خالی * pv )
{
    uint8_t * puc = ( uint8_t * ) pv;
    بلاک_Link_t * pxLink;

    اگر( pv != تہی )
    {
        /* The memory being freed will have an BlockLink_t structure immediately
         * before it. */
        puc -= x_ڈھیر_Struct_سائز;

        /* This unexpected casting is to keep some compilers from issuing
         * byte alignment warnings. */
        pxLink = ( خالی * ) puc;

        configASSERT( ڈھیر_بلاک_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_اگلا_Free_بلاک == تہی );

        اگر( ڈھیر_بلاک_IS_ALLOCATED( pxLink ) != 0 )
        {
            اگر( pxLink->px_اگلا_Free_بلاک == تہی )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                ڈھیر_FREE_بلاک( pxLink );
                #اگر ( config_ڈھیر_CLEAR_حافظہ_ON_FREE == 1 )
                {
                    ( خالی ) memset( puc + x_ڈھیر_Struct_سائز, 0, pxLink->x_بلاک_سائز - x_ڈھیر_Struct_سائز );
                }
                #اگر_ختم

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    prv_داخل_کرو_بلاک_Into_Free_List( ( ( بلاک_Link_t * ) pxLink ) );
                    x_Free_بائٹیں_بقایا += pxLink->x_بلاک_سائز;
                    traceFREE( pv, pxLink->x_بلاک_سائز );
                }
                ( خالی ) xTaskResumeAll();
            }
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_پورٹ_Get_Free_ڈھیر_سائز( خالی )
{
    واپس x_Free_بائٹیں_بقایا;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Initialise_بلاکیں( خالی )
{
    /* This just exists to keep the linker quiet. */
}
/*-----------------------------------------------------------*/

خالی * pv_پورٹ_Calloc( size_t x_عدد,
                     size_t x_سائز )
{
    خالی * pv = تہی;

    اگر( ڈھیر_MULTIPLY_WILL_حد_سے_تجاوز( x_عدد, x_سائز ) == 0 )
    {
        pv = pv_پورٹ_Malloc( x_عدد * x_سائز );

        اگر( pv != تہی )
        {
            ( خالی ) memset( pv, 0, x_عدد * x_سائز );
        }
    }

    واپس pv;
}
/*-----------------------------------------------------------*/

ساکن خالی prv_ڈھیر_Init( خالی ) /* PRIVILEGED_FUNCTION */
{
    بلاک_Link_t * px_پہلا_Free_بلاک;
    uint8_t * puc_Aligned_ڈھیر;

    /* Ensure the heap starts on a correctly aligned boundary. */
    puc_Aligned_ڈھیر = ( uint8_t * ) ( ( ( پورٹ_اشارہ_گر_سائز_TYPE ) & uc_ڈھیر[ پورٹ_BYTE_ALIGNMENT - 1 ] ) & ( ~( ( پورٹ_اشارہ_گر_سائز_TYPE ) پورٹ_BYTE_ALIGNMENT_نقاب ) ) );

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_آغاز.px_اگلا_Free_بلاک = ( خالی * ) puc_Aligned_ڈھیر;
    x_آغاز.x_بلاک_سائز = ( size_t ) 0;

    /* xEnd is used to mark the end of the list of free blocks. */
    x_انتہا.x_بلاک_سائز = config_ADJUSTED_ڈھیر_سائز;
    x_انتہا.px_اگلا_Free_بلاک = تہی;

    /* To start with there is a single free block that is sized to take up the
     * entire heap space. */
    px_پہلا_Free_بلاک = ( بلاک_Link_t * ) puc_Aligned_ڈھیر;
    px_پہلا_Free_بلاک->x_بلاک_سائز = config_ADJUSTED_ڈھیر_سائز;
    px_پہلا_Free_بلاک->px_اگلا_Free_بلاک = &x_انتہا;
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
خالی v_پورٹ_ڈھیر_Reset_State( خالی )
{
    x_Free_بائٹیں_بقایا = config_ADJUSTED_ڈھیر_سائز;

    x_ڈھیر_Has_Been_Initialised = pdFALSE;
}
/*-----------------------------------------------------------*/
