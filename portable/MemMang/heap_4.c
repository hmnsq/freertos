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

/* Block sizes must not get too small. */
#تعریف_کن انباشته_MINIMUM_بلوک_اندازه    ( ( size_t ) ( x_انباشته_Struct_اندازه << 1 ) )

/* Assumes 8bit bytes! */
#تعریف_کن انباشته_بیتها_در_هر_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#تعریف_کن انباشته_اندازه_MAX              ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#تعریف_کن انباشته_MULTIPLY_WILL_سرریز( a, b )     ( ( ( a ) > 0 ) && ( ( b ) > ( انباشته_اندازه_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کن انباشته_جمع_کن_WILL_سرریز( a, b )          ( ( a ) > ( انباشته_اندازه_MAX - ( b ) ) )

/* Check if the subtraction operation ( a - b ) will result in underflow. */
#تعریف_کن انباشته_تفریق_WILL_UNDERFLOW( a, b )    ( ( a ) < ( b ) )

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
 * of their memory address. */
تعريفنوع بنية A_بلوک_LINK
{
    بنية A_بلوک_LINK * px_بعدی_Free_بلوک; /**< The next free block in the list. */
    size_t x_بلوک_اندازه;                     /**< The size of the free block. */
} بلوک_Link_t;

/* Setting configENABLE_HEAP_PROTECTOR to 1 enables heap block pointers
 * protection using an application supplied canary value to catch heap
 * corruption should a heap buffer overflow occur.
 */
#إذا ( config_ENABLE_انباشته_PROTECTOR == 1 )

/**
 * @brief Application provided function to get a random value to be used as canary.
 *
 * @param pxHeapCanary [out] Output parameter to return the canary value.
 */
    خارجي فراغ v_Application_Get_Random_انباشته_Canary( پورت_اشاره_گر_اندازه_TYPE * px_انباشته_Canary );

/* Canary value for protecting internal heap pointers. */
    PRIVILEGED_داده ساكن پورت_اشاره_گر_اندازه_TYPE x_انباشته_Canary;

/* Macro to load/store BlockLink_t pointers to memory. By XORing the
 * pointers with a random canary value, heap overflows will result
 * in randomly unpredictable pointer values which will be caught by
 * heapVALIDATE_BLOCK_POINTER assert. */
    #تعریف_کن انباشته_PROTECT_بلوک_اشاره_گر( px_بلوک )    ( ( بلوک_Link_t * ) ( ( ( پورت_اشاره_گر_اندازه_TYPE ) ( px_بلوک ) ) ^ x_انباشته_Canary ) )
#وإلا

    #تعریف_کن انباشته_PROTECT_بلوک_اشاره_گر( px_بلوک )    ( px_بلوک )

#پایان_اگر /* configENABLE_HEAP_PROTECTOR */

/* Assert that a heap block pointer is within the heap bounds. */
#تعریف_کن انباشته_VALIDATE_بلوک_اشاره_گر( px_بلوک )                          \
    configASSERT( ( ( uint8_t * ) ( px_بلوک ) >= &( uc_انباشته[ 0 ] ) ) && \
                  ( ( uint8_t * ) ( px_بلوک ) <= &( uc_انباشته[ config_مجموع_انباشته_اندازه - 1 ] ) ) )

/*-----------------------------------------------------------*/

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
ساكن فراغ prv_درج_بلوک_Into_Free_List( بلوک_Link_t * px_بلوک_مقصد_درج ) PRIVILEGED_FUNCTION;

/*
 * Called automatically to setup the required heap structures the first time
 * pvPortMalloc() is called.
 */
ساكن فراغ prv_انباشته_Init( فراغ ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* The size of the structure placed at the beginning of each allocated memory
 * block must by correctly byte aligned. */
ساكن ثابت size_t x_انباشته_Struct_اندازه = ( حجم( بلوک_Link_t ) + ( ( size_t ) ( پورت_BYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) پورت_BYTE_ALIGNMENT_ماسک );

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_داده ساكن بلوک_Link_t x_شروع;
PRIVILEGED_داده ساكن بلوک_Link_t * px_انتها = عدم;

/* Keeps track of the number of calls to allocate and free memory as well as the
 * number of free bytes remaining, but says nothing about fragmentation. */
PRIVILEGED_داده ساكن size_t x_Free_بایتها_مانده = ( size_t ) 0U;
PRIVILEGED_داده ساكن size_t x_Minimum_Ever_Free_بایتها_مانده = ( size_t ) 0U;
PRIVILEGED_داده ساكن size_t x_عدد_از_Successful_Allocations = ( size_t ) 0U;
PRIVILEGED_داده ساكن size_t x_عدد_از_Successful_Frees = ( size_t ) 0U;

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
        إذا( px_انتها == عدم )
        {
            prv_انباشته_Init();
        }
        وإلا
        {
            mtCOVERAGE_TEST_MARKER();
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        إذا( انباشته_بلوک_اندازه_IS_VALID( x_Wanted_اندازه ) != 0 )
        {
            إذا( ( x_Wanted_اندازه > 0 ) && ( x_Wanted_اندازه <= x_Free_بایتها_مانده ) )
            {
                /* Traverse the list from the start (lowest address) block until
                 * one of adequate size is found. */
                px_قبلی_بلوک = &x_شروع;
                px_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( x_شروع.px_بعدی_Free_بلوک );
                انباشته_VALIDATE_بلوک_اشاره_گر( px_بلوک );

                طالما( ( px_بلوک->x_بلوک_اندازه < x_Wanted_اندازه ) && ( px_بلوک->px_بعدی_Free_بلوک != انباشته_PROTECT_بلوک_اشاره_گر( عدم ) ) )
                {
                    px_قبلی_بلوک = px_بلوک;
                    px_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( px_بلوک->px_بعدی_Free_بلوک );
                    انباشته_VALIDATE_بلوک_اشاره_گر( px_بلوک );
                }

                /* If the end marker was reached then a block of adequate size
                 * was not found. */
                إذا( px_بلوک != px_انتها )
                {
                    /* Return the memory space pointed to - jumping over the
                     * BlockLink_t structure at its start. */
                    pvReturn = ( فراغ * ) ( ( ( uint8_t * ) انباشته_PROTECT_بلوک_اشاره_گر( px_قبلی_بلوک->px_بعدی_Free_بلوک ) ) + x_انباشته_Struct_اندازه );
                    انباشته_VALIDATE_بلوک_اشاره_گر( pvReturn );

                    /* This block is being returned for use so must be taken out
                     * of the list of free blocks. */
                    px_قبلی_بلوک->px_بعدی_Free_بلوک = px_بلوک->px_بعدی_Free_بلوک;

                    /* If the block is larger than required it can be split into
                     * two. */
                    configASSERT( انباشته_تفریق_WILL_UNDERFLOW( px_بلوک->x_بلوک_اندازه, x_Wanted_اندازه ) == 0 );

                    إذا( ( px_بلوک->x_بلوک_اندازه - x_Wanted_اندازه ) > انباشته_MINIMUM_بلوک_اندازه )
                    {
                        /* This block is to be split into two.  Create a new
                         * block following the number of bytes requested. The void
                         * cast is used to prevent byte alignment warnings from the
                         * compiler. */
                        px_New_بلوک_Link = ( فراغ * ) ( ( ( uint8_t * ) px_بلوک ) + x_Wanted_اندازه );
                        configASSERT( ( ( ( size_t ) px_New_بلوک_Link ) & پورت_BYTE_ALIGNMENT_ماسک ) == 0 );

                        /* Calculate the sizes of two blocks split from the
                         * single block. */
                        px_New_بلوک_Link->x_بلوک_اندازه = px_بلوک->x_بلوک_اندازه - x_Wanted_اندازه;
                        px_بلوک->x_بلوک_اندازه = x_Wanted_اندازه;

                        /* Insert the new block into the list of free blocks. */
                        px_New_بلوک_Link->px_بعدی_Free_بلوک = px_قبلی_بلوک->px_بعدی_Free_بلوک;
                        px_قبلی_بلوک->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( px_New_بلوک_Link );
                    }
                    وإلا
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Free_بایتها_مانده -= px_بلوک->x_بلوک_اندازه;

                    إذا( x_Free_بایتها_مانده < x_Minimum_Ever_Free_بایتها_مانده )
                    {
                        x_Minimum_Ever_Free_بایتها_مانده = x_Free_بایتها_مانده;
                    }
                    وإلا
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Allocated_بلوک_اندازه = px_بلوک->x_بلوک_اندازه;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    انباشته_ALLOCATE_بلوک( px_بلوک );
                    px_بلوک->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( عدم );
                    x_عدد_از_Successful_Allocations++;
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
        وإلا
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #پایان_اگر /* if ( configUSE_MALLOC_FAILED_HOOK == 1 ) */

    configASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) پورت_BYTE_ALIGNMENT_ماسک ) == 0 );
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

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( فراغ * ) puc;

        انباشته_VALIDATE_بلوک_اشاره_گر( pxLink );
        configASSERT( انباشته_بلوک_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_بعدی_Free_بلوک == انباشته_PROTECT_بلوک_اشاره_گر( عدم ) );

        إذا( انباشته_بلوک_IS_ALLOCATED( pxLink ) != 0 )
        {
            إذا( pxLink->px_بعدی_Free_بلوک == انباشته_PROTECT_بلوک_اشاره_گر( عدم ) )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                انباشته_FREE_بلوک( pxLink );
                #إذا ( config_انباشته_CLEAR_حافظه_ON_FREE == 1 )
                {
                    /* Check for underflow as this can occur if xBlockSize is
                     * overwritten in a heap block. */
                    إذا( انباشته_تفریق_WILL_UNDERFLOW( pxLink->x_بلوک_اندازه, x_انباشته_Struct_اندازه ) == 0 )
                    {
                        ( فراغ ) memset( puc + x_انباشته_Struct_اندازه, 0, pxLink->x_بلوک_اندازه - x_انباشته_Struct_اندازه );
                    }
                }
                #پایان_اگر

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_بایتها_مانده += pxLink->x_بلوک_اندازه;
                    traceFREE( pv, pxLink->x_بلوک_اندازه );
                    prv_درج_بلوک_Into_Free_List( ( ( بلوک_Link_t * ) pxLink ) );
                    x_عدد_از_Successful_Frees++;
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

size_t x_پورت_Get_Free_انباشته_اندازه( فراغ )
{
    أرجع x_Free_بایتها_مانده;
}
/*-----------------------------------------------------------*/

size_t x_پورت_Get_Minimum_Ever_Free_انباشته_اندازه( فراغ )
{
    أرجع x_Minimum_Ever_Free_بایتها_مانده;
}
/*-----------------------------------------------------------*/

فراغ x_پورت_Reset_انباشته_Minimum_Ever_Free_انباشته_اندازه( فراغ )
{
    x_Minimum_Ever_Free_بایتها_مانده = x_Free_بایتها_مانده;
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
    پورت_اشاره_گر_اندازه_TYPE ux_شروع_آدرس, ux_انتها_آدرس;
    size_t x_مجموع_انباشته_اندازه = config_مجموع_انباشته_اندازه;

    /* Ensure the heap starts on a correctly aligned boundary. */
    ux_شروع_آدرس = ( پورت_اشاره_گر_اندازه_TYPE ) uc_انباشته;

    إذا( ( ux_شروع_آدرس & پورت_BYTE_ALIGNMENT_ماسک ) != 0 )
    {
        ux_شروع_آدرس += ( پورت_BYTE_ALIGNMENT - 1 );
        ux_شروع_آدرس &= ~( ( پورت_اشاره_گر_اندازه_TYPE ) پورت_BYTE_ALIGNMENT_ماسک );
        x_مجموع_انباشته_اندازه -= ( size_t ) ( ux_شروع_آدرس - ( پورت_اشاره_گر_اندازه_TYPE ) uc_انباشته );
    }

    #إذا ( config_ENABLE_انباشته_PROTECTOR == 1 )
    {
        v_Application_Get_Random_انباشته_Canary( &( x_انباشته_Canary ) );
    }
    #پایان_اگر

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_شروع.px_بعدی_Free_بلوک = ( فراغ * ) انباشته_PROTECT_بلوک_اشاره_گر( ux_شروع_آدرس );
    x_شروع.x_بلوک_اندازه = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    ux_انتها_آدرس = ux_شروع_آدرس + ( پورت_اشاره_گر_اندازه_TYPE ) x_مجموع_انباشته_اندازه;
    ux_انتها_آدرس -= ( پورت_اشاره_گر_اندازه_TYPE ) x_انباشته_Struct_اندازه;
    ux_انتها_آدرس &= ~( ( پورت_اشاره_گر_اندازه_TYPE ) پورت_BYTE_ALIGNMENT_ماسک );
    px_انتها = ( بلوک_Link_t * ) ux_انتها_آدرس;
    px_انتها->x_بلوک_اندازه = 0;
    px_انتها->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( عدم );

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    px_اولی_Free_بلوک = ( بلوک_Link_t * ) ux_شروع_آدرس;
    px_اولی_Free_بلوک->x_بلوک_اندازه = ( size_t ) ( ux_انتها_آدرس - ( پورت_اشاره_گر_اندازه_TYPE ) px_اولی_Free_بلوک );
    px_اولی_Free_بلوک->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( px_انتها );

    /* Only one block exists - and it covers the entire usable heap space. */
    x_Minimum_Ever_Free_بایتها_مانده = px_اولی_Free_بلوک->x_بلوک_اندازه;
    x_Free_بایتها_مانده = px_اولی_Free_بلوک->x_بلوک_اندازه;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_درج_بلوک_Into_Free_List( بلوک_Link_t * px_بلوک_مقصد_درج ) /* PRIVILEGED_FUNCTION */
{
    بلوک_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    لكل( pxIterator = &x_شروع; انباشته_PROTECT_بلوک_اشاره_گر( pxIterator->px_بعدی_Free_بلوک ) < px_بلوک_مقصد_درج; pxIterator = انباشته_PROTECT_بلوک_اشاره_گر( pxIterator->px_بعدی_Free_بلوک ) )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    إذا( pxIterator != &x_شروع )
    {
        انباشته_VALIDATE_بلوک_اشاره_گر( pxIterator );
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    إذا( ( puc + pxIterator->x_بلوک_اندازه ) == ( uint8_t * ) px_بلوک_مقصد_درج )
    {
        pxIterator->x_بلوک_اندازه += px_بلوک_مقصد_درج->x_بلوک_اندازه;
        px_بلوک_مقصد_درج = pxIterator;
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_بلوک_مقصد_درج;

    إذا( ( puc + px_بلوک_مقصد_درج->x_بلوک_اندازه ) == ( uint8_t * ) انباشته_PROTECT_بلوک_اشاره_گر( pxIterator->px_بعدی_Free_بلوک ) )
    {
        إذا( انباشته_PROTECT_بلوک_اشاره_گر( pxIterator->px_بعدی_Free_بلوک ) != px_انتها )
        {
            /* Form one big block from the two blocks. */
            px_بلوک_مقصد_درج->x_بلوک_اندازه += انباشته_PROTECT_بلوک_اشاره_گر( pxIterator->px_بعدی_Free_بلوک )->x_بلوک_اندازه;
            px_بلوک_مقصد_درج->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( pxIterator->px_بعدی_Free_بلوک )->px_بعدی_Free_بلوک;
        }
        وإلا
        {
            px_بلوک_مقصد_درج->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( px_انتها );
        }
    }
    وإلا
    {
        px_بلوک_مقصد_درج->px_بعدی_Free_بلوک = pxIterator->px_بعدی_Free_بلوک;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    إذا( pxIterator != px_بلوک_مقصد_درج )
    {
        pxIterator->px_بعدی_Free_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( px_بلوک_مقصد_درج );
    }
    وإلا
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Get_انباشته_Stats( انباشته_Stats_t * px_انباشته_Stats )
{
    بلوک_Link_t * px_بلوک;
    size_t x_بلوکها = 0, x_Max_اندازه = 0, x_Min_اندازه = SIZE_MAX;

    vTaskSuspendAll();
    {
        px_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( x_شروع.px_بعدی_Free_بلوک );

        /* pxBlock will be NULL if the heap has not been initialised.  The heap
         * is initialised automatically when the first allocation is made. */
        إذا( px_بلوک != عدم )
        {
            طالما( px_بلوک != px_انتها )
            {
                /* Increment the number of blocks and record the largest block seen
                 * so far. */
                x_بلوکها++;

                إذا( px_بلوک->x_بلوک_اندازه > x_Max_اندازه )
                {
                    x_Max_اندازه = px_بلوک->x_بلوک_اندازه;
                }

                إذا( px_بلوک->x_بلوک_اندازه < x_Min_اندازه )
                {
                    x_Min_اندازه = px_بلوک->x_بلوک_اندازه;
                }

                /* Move to the next block in the chain until the last block is
                 * reached. */
                px_بلوک = انباشته_PROTECT_بلوک_اشاره_گر( px_بلوک->px_بعدی_Free_بلوک );
            }
        }
    }
    ( فراغ ) xTaskResumeAll();

    px_انباشته_Stats->x_اندازه_از_بزرگترین_Free_بلوک_درون_بایتها = x_Max_اندازه;
    px_انباشته_Stats->x_اندازه_از_کوچکترین_Free_بلوک_درون_بایتها = x_Min_اندازه;
    px_انباشته_Stats->x_عدد_از_Free_بلوکها = x_بلوکها;

    taskENTER_CRITICAL();
    {
        px_انباشته_Stats->x_موجود_انباشته_Space_درون_بایتها = x_Free_بایتها_مانده;
        px_انباشته_Stats->x_عدد_از_Successful_Allocations = x_عدد_از_Successful_Allocations;
        px_انباشته_Stats->x_عدد_از_Successful_Frees = x_عدد_از_Successful_Frees;
        px_انباشته_Stats->x_Minimum_Ever_Free_بایتها_مانده = x_Minimum_Ever_Free_بایتها_مانده;
    }
    taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
فراغ v_پورت_انباشته_Reset_State( فراغ )
{
    px_انتها = عدم;

    x_Free_بایتها_مانده = ( size_t ) 0U;
    x_Minimum_Ever_Free_بایتها_مانده = ( size_t ) 0U;
    x_عدد_از_Successful_Allocations = ( size_t ) 0U;
    x_عدد_از_Successful_Frees = ( size_t ) 0U;
}
/*-----------------------------------------------------------*/
