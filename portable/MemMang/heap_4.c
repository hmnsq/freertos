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

/* Block sizes must not get too small. */
#تعریف_کړه ډېرۍ_MINIMUM_بلاک_اندازه    ( ( size_t ) ( x_ډېرۍ_Struct_اندازه << 1 ) )

/* Assumes 8bit bytes! */
#تعریف_کړه ډېرۍ_بټونه_فی_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#تعریف_کړه ډېرۍ_اندازه_MAX              ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#تعریف_کړه ډېرۍ_MULTIPLY_WILL_ډکېدنه( a, b )     ( ( ( a ) > 0 ) && ( ( b ) > ( ډېرۍ_اندازه_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کړه ډېرۍ_جمع_کړه_WILL_ډکېدنه( a, b )          ( ( a ) > ( ډېرۍ_اندازه_MAX - ( b ) ) )

/* Check if the subtraction operation ( a - b ) will result in underflow. */
#تعریف_کړه ډېرۍ_کمول_WILL_UNDERFLOW( a, b )    ( ( a ) < ( b ) )

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
 * of their memory address. */
تعريفنوع بنية A_بلاک_LINK
{
    بنية A_بلاک_LINK * px_بل_Free_بلاک; /**< The next free block in the list. */
    size_t x_بلاک_اندازه;                     /**< The size of the free block. */
} بلاک_Link_t;

/* Setting configENABLE_HEAP_PROTECTOR to 1 enables heap block pointers
 * protection using an application supplied canary value to catch heap
 * corruption should a heap buffer overflow occur.
 */
#إذا ( config_ENABLE_ډېرۍ_PROTECTOR == 1 )

/**
 * @brief Application provided function to get a random value to be used as canary.
 *
 * @param pxHeapCanary [out] Output parameter to return the canary value.
 */
    خارجي فراغ v_Application_Get_Random_ډېرۍ_Canary( پورټ_اشاره_ګر_اندازه_TYPE * px_ډېرۍ_Canary );

/* Canary value for protecting internal heap pointers. */
    PRIVILEGED_معلومات ساكن پورټ_اشاره_ګر_اندازه_TYPE x_ډېرۍ_Canary;

/* Macro to load/store BlockLink_t pointers to memory. By XORing the
 * pointers with a random canary value, heap overflows will result
 * in randomly unpredictable pointer values which will be caught by
 * heapVALIDATE_BLOCK_POINTER assert. */
    #تعریف_کړه ډېرۍ_PROTECT_بلاک_اشاره_ګر( px_بلاک )    ( ( بلاک_Link_t * ) ( ( ( پورټ_اشاره_ګر_اندازه_TYPE ) ( px_بلاک ) ) ^ x_ډېرۍ_Canary ) )
#وإلا

    #تعریف_کړه ډېرۍ_PROTECT_بلاک_اشاره_ګر( px_بلاک )    ( px_بلاک )

#د_که_پای /* configENABLE_HEAP_PROTECTOR */

/* Assert that a heap block pointer is within the heap bounds. */
#تعریف_کړه ډېرۍ_VALIDATE_بلاک_اشاره_ګر( px_بلاک )                          \
    configASSERT( ( ( uint8_t * ) ( px_بلاک ) >= &( uc_ډېرۍ[ 0 ] ) ) && \
                  ( ( uint8_t * ) ( px_بلاک ) <= &( uc_ډېرۍ[ config_ټول_ډېرۍ_اندازه - 1 ] ) ) )

/*-----------------------------------------------------------*/

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
ساكن فراغ prv_ورننباسه_بلاک_Into_Free_List( بلاک_Link_t * px_بلاک_منزل_ورننباسه ) PRIVILEGED_FUNCTION;

/*
 * Called automatically to setup the required heap structures the first time
 * pvPortMalloc() is called.
 */
ساكن فراغ prv_ډېرۍ_Init( فراغ ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* The size of the structure placed at the beginning of each allocated memory
 * block must by correctly byte aligned. */
ساكن ثابت size_t x_ډېرۍ_Struct_اندازه = ( حجم( بلاک_Link_t ) + ( ( size_t ) ( پورټ_BYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) پورټ_BYTE_ALIGNMENT_ماسک );

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_معلومات ساكن بلاک_Link_t x_پیل;
PRIVILEGED_معلومات ساكن بلاک_Link_t * px_پای_ټکی = عدم;

/* Keeps track of the number of calls to allocate and free memory as well as the
 * number of free bytes remaining, but says nothing about fragmentation. */
PRIVILEGED_معلومات ساكن size_t x_Free_بایټونه_پاتې_شوی = ( size_t ) 0U;
PRIVILEGED_معلومات ساكن size_t x_Minimum_Ever_Free_بایټونه_پاتې_شوی = ( size_t ) 0U;
PRIVILEGED_معلومات ساكن size_t x_شمېره_د_Successful_Allocations = ( size_t ) 0U;
PRIVILEGED_معلومات ساكن size_t x_شمېره_د_Successful_Frees = ( size_t ) 0U;

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
        إذا( px_پای_ټکی == عدم )
        {
            prv_ډېرۍ_Init();
        }
        وإلا
        {
            mtCOVERAGE_TEST_MARKER();
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        إذا( ډېرۍ_بلاک_اندازه_IS_VALID( x_Wanted_اندازه ) != 0 )
        {
            إذا( ( x_Wanted_اندازه > 0 ) && ( x_Wanted_اندازه <= x_Free_بایټونه_پاتې_شوی ) )
            {
                /* Traverse the list from the start (lowest address) block until
                 * one of adequate size is found. */
                px_پخوانی_بلاک = &x_پیل;
                px_بلاک = ډېرۍ_PROTECT_بلاک_اشاره_ګر( x_پیل.px_بل_Free_بلاک );
                ډېرۍ_VALIDATE_بلاک_اشاره_ګر( px_بلاک );

                طالما( ( px_بلاک->x_بلاک_اندازه < x_Wanted_اندازه ) && ( px_بلاک->px_بل_Free_بلاک != ډېرۍ_PROTECT_بلاک_اشاره_ګر( عدم ) ) )
                {
                    px_پخوانی_بلاک = px_بلاک;
                    px_بلاک = ډېرۍ_PROTECT_بلاک_اشاره_ګر( px_بلاک->px_بل_Free_بلاک );
                    ډېرۍ_VALIDATE_بلاک_اشاره_ګر( px_بلاک );
                }

                /* If the end marker was reached then a block of adequate size
                 * was not found. */
                إذا( px_بلاک != px_پای_ټکی )
                {
                    /* Return the memory space pointed to - jumping over the
                     * BlockLink_t structure at its start. */
                    pvReturn = ( فراغ * ) ( ( ( uint8_t * ) ډېرۍ_PROTECT_بلاک_اشاره_ګر( px_پخوانی_بلاک->px_بل_Free_بلاک ) ) + x_ډېرۍ_Struct_اندازه );
                    ډېرۍ_VALIDATE_بلاک_اشاره_ګر( pvReturn );

                    /* This block is being returned for use so must be taken out
                     * of the list of free blocks. */
                    px_پخوانی_بلاک->px_بل_Free_بلاک = px_بلاک->px_بل_Free_بلاک;

                    /* If the block is larger than required it can be split into
                     * two. */
                    configASSERT( ډېرۍ_کمول_WILL_UNDERFLOW( px_بلاک->x_بلاک_اندازه, x_Wanted_اندازه ) == 0 );

                    إذا( ( px_بلاک->x_بلاک_اندازه - x_Wanted_اندازه ) > ډېرۍ_MINIMUM_بلاک_اندازه )
                    {
                        /* This block is to be split into two.  Create a new
                         * block following the number of bytes requested. The void
                         * cast is used to prevent byte alignment warnings from the
                         * compiler. */
                        px_New_بلاک_Link = ( فراغ * ) ( ( ( uint8_t * ) px_بلاک ) + x_Wanted_اندازه );
                        configASSERT( ( ( ( size_t ) px_New_بلاک_Link ) & پورټ_BYTE_ALIGNMENT_ماسک ) == 0 );

                        /* Calculate the sizes of two blocks split from the
                         * single block. */
                        px_New_بلاک_Link->x_بلاک_اندازه = px_بلاک->x_بلاک_اندازه - x_Wanted_اندازه;
                        px_بلاک->x_بلاک_اندازه = x_Wanted_اندازه;

                        /* Insert the new block into the list of free blocks. */
                        px_New_بلاک_Link->px_بل_Free_بلاک = px_پخوانی_بلاک->px_بل_Free_بلاک;
                        px_پخوانی_بلاک->px_بل_Free_بلاک = ډېرۍ_PROTECT_بلاک_اشاره_ګر( px_New_بلاک_Link );
                    }
                    وإلا
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Free_بایټونه_پاتې_شوی -= px_بلاک->x_بلاک_اندازه;

                    إذا( x_Free_بایټونه_پاتې_شوی < x_Minimum_Ever_Free_بایټونه_پاتې_شوی )
                    {
                        x_Minimum_Ever_Free_بایټونه_پاتې_شوی = x_Free_بایټونه_پاتې_شوی;
                    }
                    وإلا
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Allocated_بلاک_اندازه = px_بلاک->x_بلاک_اندازه;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    ډېرۍ_ALLOCATE_بلاک( px_بلاک );
                    px_بلاک->px_بل_Free_بلاک = ډېرۍ_PROTECT_بلاک_اشاره_ګر( عدم );
                    x_شمېره_د_Successful_Allocations++;
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
        وإلا
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #د_که_پای /* if ( configUSE_MALLOC_FAILED_HOOK == 1 ) */

    configASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) پورټ_BYTE_ALIGNMENT_ماسک ) == 0 );
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

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( فراغ * ) puc;

        ډېرۍ_VALIDATE_بلاک_اشاره_ګر( pxLink );
        configASSERT( ډېرۍ_بلاک_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_بل_Free_بلاک == ډېرۍ_PROTECT_بلاک_اشاره_ګر( عدم ) );

        إذا( ډېرۍ_بلاک_IS_ALLOCATED( pxLink ) != 0 )
        {
            إذا( pxLink->px_بل_Free_بلاک == ډېرۍ_PROTECT_بلاک_اشاره_ګر( عدم ) )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                ډېرۍ_FREE_بلاک( pxLink );
                #إذا ( config_ډېرۍ_CLEAR_حافظه_ON_FREE == 1 )
                {
                    /* Check for underflow as this can occur if xBlockSize is
                     * overwritten in a heap block. */
                    إذا( ډېرۍ_کمول_WILL_UNDERFLOW( pxLink->x_بلاک_اندازه, x_ډېرۍ_Struct_اندازه ) == 0 )
                    {
                        ( فراغ ) memset( puc + x_ډېرۍ_Struct_اندازه, 0, pxLink->x_بلاک_اندازه - x_ډېرۍ_Struct_اندازه );
                    }
                }
                #د_که_پای

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_بایټونه_پاتې_شوی += pxLink->x_بلاک_اندازه;
                    traceFREE( pv, pxLink->x_بلاک_اندازه );
                    prv_ورننباسه_بلاک_Into_Free_List( ( ( بلاک_Link_t * ) pxLink ) );
                    x_شمېره_د_Successful_Frees++;
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

size_t x_پورټ_Get_Free_ډېرۍ_اندازه( فراغ )
{
    أرجع x_Free_بایټونه_پاتې_شوی;
}
/*-----------------------------------------------------------*/

size_t x_پورټ_Get_Minimum_Ever_Free_ډېرۍ_اندازه( فراغ )
{
    أرجع x_Minimum_Ever_Free_بایټونه_پاتې_شوی;
}
/*-----------------------------------------------------------*/

فراغ x_پورټ_Reset_ډېرۍ_Minimum_Ever_Free_ډېرۍ_اندازه( فراغ )
{
    x_Minimum_Ever_Free_بایټونه_پاتې_شوی = x_Free_بایټونه_پاتې_شوی;
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
    پورټ_اشاره_ګر_اندازه_TYPE ux_پیل_پته, ux_پای_ټکی_پته;
    size_t x_ټول_ډېرۍ_اندازه = config_ټول_ډېرۍ_اندازه;

    /* Ensure the heap starts on a correctly aligned boundary. */
    ux_پیل_پته = ( پورټ_اشاره_ګر_اندازه_TYPE ) uc_ډېرۍ;

    إذا( ( ux_پیل_پته & پورټ_BYTE_ALIGNMENT_ماسک ) != 0 )
    {
        ux_پیل_پته += ( پورټ_BYTE_ALIGNMENT - 1 );
        ux_پیل_پته &= ~( ( پورټ_اشاره_ګر_اندازه_TYPE ) پورټ_BYTE_ALIGNMENT_ماسک );
        x_ټول_ډېرۍ_اندازه -= ( size_t ) ( ux_پیل_پته - ( پورټ_اشاره_ګر_اندازه_TYPE ) uc_ډېرۍ );
    }

    #إذا ( config_ENABLE_ډېرۍ_PROTECTOR == 1 )
    {
        v_Application_Get_Random_ډېرۍ_Canary( &( x_ډېرۍ_Canary ) );
    }
    #د_که_پای

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_پیل.px_بل_Free_بلاک = ( فراغ * ) ډېرۍ_PROTECT_بلاک_اشاره_ګر( ux_پیل_پته );
    x_پیل.x_بلاک_اندازه = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    ux_پای_ټکی_پته = ux_پیل_پته + ( پورټ_اشاره_ګر_اندازه_TYPE ) x_ټول_ډېرۍ_اندازه;
    ux_پای_ټکی_پته -= ( پورټ_اشاره_ګر_اندازه_TYPE ) x_ډېرۍ_Struct_اندازه;
    ux_پای_ټکی_پته &= ~( ( پورټ_اشاره_ګر_اندازه_TYPE ) پورټ_BYTE_ALIGNMENT_ماسک );
    px_پای_ټکی = ( بلاک_Link_t * ) ux_پای_ټکی_پته;
    px_پای_ټکی->x_بلاک_اندازه = 0;
    px_پای_ټکی->px_بل_Free_بلاک = ډېرۍ_PROTECT_بلاک_اشاره_ګر( عدم );

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    px_لومړی_Free_بلاک = ( بلاک_Link_t * ) ux_پیل_پته;
    px_لومړی_Free_بلاک->x_بلاک_اندازه = ( size_t ) ( ux_پای_ټکی_پته - ( پورټ_اشاره_ګر_اندازه_TYPE ) px_لومړی_Free_بلاک );
    px_لومړی_Free_بلاک->px_بل_Free_بلاک = ډېرۍ_PROTECT_بلاک_اشاره_ګر( px_پای_ټکی );

    /* Only one block exists - and it covers the entire usable heap space. */
    x_Minimum_Ever_Free_بایټونه_پاتې_شوی = px_لومړی_Free_بلاک->x_بلاک_اندازه;
    x_Free_بایټونه_پاتې_شوی = px_لومړی_Free_بلاک->x_بلاک_اندازه;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_ورننباسه_بلاک_Into_Free_List( بلاک_Link_t * px_بلاک_منزل_ورننباسه ) /* PRIVILEGED_FUNCTION */
{
    بلاک_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    لكل( pxIterator = &x_پیل; ډېرۍ_PROTECT_بلاک_اشاره_ګر( pxIterator->px_بل_Free_بلاک ) < px_بلاک_منزل_ورننباسه; pxIterator = ډېرۍ_PROTECT_بلاک_اشاره_ګر( pxIterator->px_بل_Free_بلاک ) )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    إذا( pxIterator != &x_پیل )
    {
        ډېرۍ_VALIDATE_بلاک_اشاره_ګر( pxIterator );
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    إذا( ( puc + pxIterator->x_بلاک_اندازه ) == ( uint8_t * ) px_بلاک_منزل_ورننباسه )
    {
        pxIterator->x_بلاک_اندازه += px_بلاک_منزل_ورننباسه->x_بلاک_اندازه;
        px_بلاک_منزل_ورننباسه = pxIterator;
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_بلاک_منزل_ورننباسه;

    إذا( ( puc + px_بلاک_منزل_ورننباسه->x_بلاک_اندازه ) == ( uint8_t * ) ډېرۍ_PROTECT_بلاک_اشاره_ګر( pxIterator->px_بل_Free_بلاک ) )
    {
        إذا( ډېرۍ_PROTECT_بلاک_اشاره_ګر( pxIterator->px_بل_Free_بلاک ) != px_پای_ټکی )
        {
            /* Form one big block from the two blocks. */
            px_بلاک_منزل_ورننباسه->x_بلاک_اندازه += ډېرۍ_PROTECT_بلاک_اشاره_ګر( pxIterator->px_بل_Free_بلاک )->x_بلاک_اندازه;
            px_بلاک_منزل_ورننباسه->px_بل_Free_بلاک = ډېرۍ_PROTECT_بلاک_اشاره_ګر( pxIterator->px_بل_Free_بلاک )->px_بل_Free_بلاک;
        }
        وإلا
        {
            px_بلاک_منزل_ورننباسه->px_بل_Free_بلاک = ډېرۍ_PROTECT_بلاک_اشاره_ګر( px_پای_ټکی );
        }
    }
    وإلا
    {
        px_بلاک_منزل_ورننباسه->px_بل_Free_بلاک = pxIterator->px_بل_Free_بلاک;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    إذا( pxIterator != px_بلاک_منزل_ورننباسه )
    {
        pxIterator->px_بل_Free_بلاک = ډېرۍ_PROTECT_بلاک_اشاره_ګر( px_بلاک_منزل_ورننباسه );
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Get_ډېرۍ_Stats( ډېرۍ_Stats_t * px_ډېرۍ_Stats )
{
    بلاک_Link_t * px_بلاک;
    size_t x_بلاکونه = 0, x_Max_اندازه = 0, x_Min_اندازه = SIZE_MAX;

    vTaskSuspendAll();
    {
        px_بلاک = ډېرۍ_PROTECT_بلاک_اشاره_ګر( x_پیل.px_بل_Free_بلاک );

        /* pxBlock will be NULL if the heap has not been initialised.  The heap
         * is initialised automatically when the first allocation is made. */
        إذا( px_بلاک != عدم )
        {
            طالما( px_بلاک != px_پای_ټکی )
            {
                /* Increment the number of blocks and record the largest block seen
                 * so far. */
                x_بلاکونه++;

                إذا( px_بلاک->x_بلاک_اندازه > x_Max_اندازه )
                {
                    x_Max_اندازه = px_بلاک->x_بلاک_اندازه;
                }

                إذا( px_بلاک->x_بلاک_اندازه < x_Min_اندازه )
                {
                    x_Min_اندازه = px_بلاک->x_بلاک_اندازه;
                }

                /* Move to the next block in the chain until the last block is
                 * reached. */
                px_بلاک = ډېرۍ_PROTECT_بلاک_اشاره_ګر( px_بلاک->px_بل_Free_بلاک );
            }
        }
    }
    ( فراغ ) xTaskResumeAll();

    px_ډېرۍ_Stats->x_اندازه_د_تر_ټولو_لوی_Free_بلاک_دننه_بایټونه = x_Max_اندازه;
    px_ډېرۍ_Stats->x_اندازه_د_تر_ټولو_کوچنی_Free_بلاک_دننه_بایټونه = x_Min_اندازه;
    px_ډېرۍ_Stats->x_شمېره_د_Free_بلاکونه = x_بلاکونه;

    taskENTER_CRITICAL();
    {
        px_ډېرۍ_Stats->x_شته_ډېرۍ_Space_دننه_بایټونه = x_Free_بایټونه_پاتې_شوی;
        px_ډېرۍ_Stats->x_شمېره_د_Successful_Allocations = x_شمېره_د_Successful_Allocations;
        px_ډېرۍ_Stats->x_شمېره_د_Successful_Frees = x_شمېره_د_Successful_Frees;
        px_ډېرۍ_Stats->x_Minimum_Ever_Free_بایټونه_پاتې_شوی = x_Minimum_Ever_Free_بایټونه_پاتې_شوی;
    }
    taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
فراغ v_پورټ_ډېرۍ_Reset_State( فراغ )
{
    px_پای_ټکی = عدم;

    x_Free_بایټونه_پاتې_شوی = ( size_t ) 0U;
    x_Minimum_Ever_Free_بایټونه_پاتې_شوی = ( size_t ) 0U;
    x_شمېره_د_Successful_Allocations = ( size_t ) 0U;
    x_شمېره_د_Successful_Frees = ( size_t ) 0U;
}
/*-----------------------------------------------------------*/
