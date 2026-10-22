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

/* Block sizes must not get too small. */
#تعریف_کرو ڈھیر_MINIMUM_بلاک_سائز    ( ( size_t ) ( x_ڈھیر_Struct_سائز << 1 ) )

/* Assumes 8bit bytes! */
#تعریف_کرو ڈھیر_بٹ_فی_BYTE         ( ( size_t ) 8 )

/* Max value that fits in a size_t type. */
#تعریف_کرو ڈھیر_سائز_MAX              ( ~( ( size_t ) 0 ) )

/* Check if multiplying a and b will result in overflow. */
#تعریف_کرو ڈھیر_MULTIPLY_WILL_حد_سے_تجاوز( a, b )     ( ( ( a ) > 0 ) && ( ( b ) > ( ڈھیر_سائز_MAX / ( a ) ) ) )

/* Check if adding a and b will result in overflow. */
#تعریف_کرو ڈھیر_جوڑو_WILL_حد_سے_تجاوز( a, b )          ( ( a ) > ( ڈھیر_سائز_MAX - ( b ) ) )

/* Check if the subtraction operation ( a - b ) will result in underflow. */
#تعریف_کرو ڈھیر_تفریق_WILL_UNDERFLOW( a, b )    ( ( a ) < ( b ) )

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
 * of their memory address. */
قسمتعریف ساخت A_بلاک_LINK
{
    ساخت A_بلاک_LINK * px_اگلا_Free_بلاک; /**< The next free block in the list. */
    size_t x_بلاک_سائز;                     /**< The size of the free block. */
} بلاک_Link_t;

/* Setting configENABLE_HEAP_PROTECTOR to 1 enables heap block pointers
 * protection using an application supplied canary value to catch heap
 * corruption should a heap buffer overflow occur.
 */
#اگر ( config_ENABLE_ڈھیر_PROTECTOR == 1 )

/**
 * @brief Application provided function to get a random value to be used as canary.
 *
 * @param pxHeapCanary [out] Output parameter to return the canary value.
 */
    خارجی خالی v_Application_Get_Random_ڈھیر_Canary( پورٹ_اشارہ_گر_سائز_TYPE * px_ڈھیر_Canary );

/* Canary value for protecting internal heap pointers. */
    PRIVILEGED_ڈیٹا ساکن پورٹ_اشارہ_گر_سائز_TYPE x_ڈھیر_Canary;

/* Macro to load/store BlockLink_t pointers to memory. By XORing the
 * pointers with a random canary value, heap overflows will result
 * in randomly unpredictable pointer values which will be caught by
 * heapVALIDATE_BLOCK_POINTER assert. */
    #تعریف_کرو ڈھیر_PROTECT_بلاک_اشارہ_گر( px_بلاک )    ( ( بلاک_Link_t * ) ( ( ( پورٹ_اشارہ_گر_سائز_TYPE ) ( px_بلاک ) ) ^ x_ڈھیر_Canary ) )
#ورنہ

    #تعریف_کرو ڈھیر_PROTECT_بلاک_اشارہ_گر( px_بلاک )    ( px_بلاک )

#اگر_ختم /* configENABLE_HEAP_PROTECTOR */

/* Assert that a heap block pointer is within the heap bounds. */
#تعریف_کرو ڈھیر_VALIDATE_بلاک_اشارہ_گر( px_بلاک )                          \
    configASSERT( ( ( uint8_t * ) ( px_بلاک ) >= &( uc_ڈھیر[ 0 ] ) ) && \
                  ( ( uint8_t * ) ( px_بلاک ) <= &( uc_ڈھیر[ config_کل_ڈھیر_سائز - 1 ] ) ) )

/*-----------------------------------------------------------*/

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
ساکن خالی prv_داخل_کرو_بلاک_Into_Free_List( بلاک_Link_t * px_بلاک_مقصد_داخل_کرو ) PRIVILEGED_FUNCTION;

/*
 * Called automatically to setup the required heap structures the first time
 * pvPortMalloc() is called.
 */
ساکن خالی prv_ڈھیر_Init( خالی ) PRIVILEGED_FUNCTION;

/*-----------------------------------------------------------*/

/* The size of the structure placed at the beginning of each allocated memory
 * block must by correctly byte aligned. */
ساکن ثابت size_t x_ڈھیر_Struct_سائز = ( حجم( بلاک_Link_t ) + ( ( size_t ) ( پورٹ_BYTE_ALIGNMENT - 1 ) ) ) & ~( ( size_t ) پورٹ_BYTE_ALIGNMENT_نقاب );

/* Create a couple of list links to mark the start and end of the list. */
PRIVILEGED_ڈیٹا ساکن بلاک_Link_t x_آغاز;
PRIVILEGED_ڈیٹا ساکن بلاک_Link_t * px_انتہا = تہی;

/* Keeps track of the number of calls to allocate and free memory as well as the
 * number of free bytes remaining, but says nothing about fragmentation. */
PRIVILEGED_ڈیٹا ساکن size_t x_Free_بائٹیں_بقایا = ( size_t ) 0U;
PRIVILEGED_ڈیٹا ساکن size_t x_Minimum_Ever_Free_بائٹیں_بقایا = ( size_t ) 0U;
PRIVILEGED_ڈیٹا ساکن size_t x_نمبر_کا_Successful_Allocations = ( size_t ) 0U;
PRIVILEGED_ڈیٹا ساکن size_t x_نمبر_کا_Successful_Frees = ( size_t ) 0U;

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
        اگر( px_انتہا == تہی )
        {
            prv_ڈھیر_Init();
        }
        ورنہ
        {
            mtCOVERAGE_TEST_MARKER();
        }

        /* Check the block size we are trying to allocate is not so large that the
         * top bit is set.  The top bit of the block size member of the BlockLink_t
         * structure is used to determine who owns the block - the application or
         * the kernel, so it must be free. */
        اگر( ڈھیر_بلاک_سائز_IS_VALID( x_Wanted_سائز ) != 0 )
        {
            اگر( ( x_Wanted_سائز > 0 ) && ( x_Wanted_سائز <= x_Free_بائٹیں_بقایا ) )
            {
                /* Traverse the list from the start (lowest address) block until
                 * one of adequate size is found. */
                px_پچھلا_بلاک = &x_آغاز;
                px_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( x_آغاز.px_اگلا_Free_بلاک );
                ڈھیر_VALIDATE_بلاک_اشارہ_گر( px_بلاک );

                جب( ( px_بلاک->x_بلاک_سائز < x_Wanted_سائز ) && ( px_بلاک->px_اگلا_Free_بلاک != ڈھیر_PROTECT_بلاک_اشارہ_گر( تہی ) ) )
                {
                    px_پچھلا_بلاک = px_بلاک;
                    px_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( px_بلاک->px_اگلا_Free_بلاک );
                    ڈھیر_VALIDATE_بلاک_اشارہ_گر( px_بلاک );
                }

                /* If the end marker was reached then a block of adequate size
                 * was not found. */
                اگر( px_بلاک != px_انتہا )
                {
                    /* Return the memory space pointed to - jumping over the
                     * BlockLink_t structure at its start. */
                    pvReturn = ( خالی * ) ( ( ( uint8_t * ) ڈھیر_PROTECT_بلاک_اشارہ_گر( px_پچھلا_بلاک->px_اگلا_Free_بلاک ) ) + x_ڈھیر_Struct_سائز );
                    ڈھیر_VALIDATE_بلاک_اشارہ_گر( pvReturn );

                    /* This block is being returned for use so must be taken out
                     * of the list of free blocks. */
                    px_پچھلا_بلاک->px_اگلا_Free_بلاک = px_بلاک->px_اگلا_Free_بلاک;

                    /* If the block is larger than required it can be split into
                     * two. */
                    configASSERT( ڈھیر_تفریق_WILL_UNDERFLOW( px_بلاک->x_بلاک_سائز, x_Wanted_سائز ) == 0 );

                    اگر( ( px_بلاک->x_بلاک_سائز - x_Wanted_سائز ) > ڈھیر_MINIMUM_بلاک_سائز )
                    {
                        /* This block is to be split into two.  Create a new
                         * block following the number of bytes requested. The void
                         * cast is used to prevent byte alignment warnings from the
                         * compiler. */
                        px_New_بلاک_Link = ( خالی * ) ( ( ( uint8_t * ) px_بلاک ) + x_Wanted_سائز );
                        configASSERT( ( ( ( size_t ) px_New_بلاک_Link ) & پورٹ_BYTE_ALIGNMENT_نقاب ) == 0 );

                        /* Calculate the sizes of two blocks split from the
                         * single block. */
                        px_New_بلاک_Link->x_بلاک_سائز = px_بلاک->x_بلاک_سائز - x_Wanted_سائز;
                        px_بلاک->x_بلاک_سائز = x_Wanted_سائز;

                        /* Insert the new block into the list of free blocks. */
                        px_New_بلاک_Link->px_اگلا_Free_بلاک = px_پچھلا_بلاک->px_اگلا_Free_بلاک;
                        px_پچھلا_بلاک->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( px_New_بلاک_Link );
                    }
                    ورنہ
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Free_بائٹیں_بقایا -= px_بلاک->x_بلاک_سائز;

                    اگر( x_Free_بائٹیں_بقایا < x_Minimum_Ever_Free_بائٹیں_بقایا )
                    {
                        x_Minimum_Ever_Free_بائٹیں_بقایا = x_Free_بائٹیں_بقایا;
                    }
                    ورنہ
                    {
                        mtCOVERAGE_TEST_MARKER();
                    }

                    x_Allocated_بلاک_سائز = px_بلاک->x_بلاک_سائز;

                    /* The block is being returned - it is allocated and owned
                     * by the application and has no "next" block. */
                    ڈھیر_ALLOCATE_بلاک( px_بلاک );
                    px_بلاک->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( تہی );
                    x_نمبر_کا_Successful_Allocations++;
                }
                ورنہ
                {
                    mtCOVERAGE_TEST_MARKER();
                }
            }
            ورنہ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ورنہ
        {
            mtCOVERAGE_TEST_MARKER();
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
        ورنہ
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
    #اگر_ختم /* if ( configUSE_MALLOC_FAILED_HOOK == 1 ) */

    configASSERT( ( ( ( size_t ) pvReturn ) & ( size_t ) پورٹ_BYTE_ALIGNMENT_نقاب ) == 0 );
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

        /* This casting is to keep the compiler from issuing warnings. */
        pxLink = ( خالی * ) puc;

        ڈھیر_VALIDATE_بلاک_اشارہ_گر( pxLink );
        configASSERT( ڈھیر_بلاک_IS_ALLOCATED( pxLink ) != 0 );
        configASSERT( pxLink->px_اگلا_Free_بلاک == ڈھیر_PROTECT_بلاک_اشارہ_گر( تہی ) );

        اگر( ڈھیر_بلاک_IS_ALLOCATED( pxLink ) != 0 )
        {
            اگر( pxLink->px_اگلا_Free_بلاک == ڈھیر_PROTECT_بلاک_اشارہ_گر( تہی ) )
            {
                /* The block is being returned to the heap - it is no longer
                 * allocated. */
                ڈھیر_FREE_بلاک( pxLink );
                #اگر ( config_ڈھیر_CLEAR_حافظہ_ON_FREE == 1 )
                {
                    /* Check for underflow as this can occur if xBlockSize is
                     * overwritten in a heap block. */
                    اگر( ڈھیر_تفریق_WILL_UNDERFLOW( pxLink->x_بلاک_سائز, x_ڈھیر_Struct_سائز ) == 0 )
                    {
                        ( خالی ) memset( puc + x_ڈھیر_Struct_سائز, 0, pxLink->x_بلاک_سائز - x_ڈھیر_Struct_سائز );
                    }
                }
                #اگر_ختم

                vTaskSuspendAll();
                {
                    /* Add this block to the list of free blocks. */
                    x_Free_بائٹیں_بقایا += pxLink->x_بلاک_سائز;
                    traceFREE( pv, pxLink->x_بلاک_سائز );
                    prv_داخل_کرو_بلاک_Into_Free_List( ( ( بلاک_Link_t * ) pxLink ) );
                    x_نمبر_کا_Successful_Frees++;
                }
                ( خالی ) xTaskResumeAll();
            }
            ورنہ
            {
                mtCOVERAGE_TEST_MARKER();
            }
        }
        ورنہ
        {
            mtCOVERAGE_TEST_MARKER();
        }
    }
}
/*-----------------------------------------------------------*/

size_t x_پورٹ_Get_Free_ڈھیر_سائز( خالی )
{
    واپس x_Free_بائٹیں_بقایا;
}
/*-----------------------------------------------------------*/

size_t x_پورٹ_Get_Minimum_Ever_Free_ڈھیر_سائز( خالی )
{
    واپس x_Minimum_Ever_Free_بائٹیں_بقایا;
}
/*-----------------------------------------------------------*/

خالی x_پورٹ_Reset_ڈھیر_Minimum_Ever_Free_ڈھیر_سائز( خالی )
{
    x_Minimum_Ever_Free_بائٹیں_بقایا = x_Free_بائٹیں_بقایا;
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
    پورٹ_اشارہ_گر_سائز_TYPE ux_آغاز_پتہ, ux_انتہا_پتہ;
    size_t x_کل_ڈھیر_سائز = config_کل_ڈھیر_سائز;

    /* Ensure the heap starts on a correctly aligned boundary. */
    ux_آغاز_پتہ = ( پورٹ_اشارہ_گر_سائز_TYPE ) uc_ڈھیر;

    اگر( ( ux_آغاز_پتہ & پورٹ_BYTE_ALIGNMENT_نقاب ) != 0 )
    {
        ux_آغاز_پتہ += ( پورٹ_BYTE_ALIGNMENT - 1 );
        ux_آغاز_پتہ &= ~( ( پورٹ_اشارہ_گر_سائز_TYPE ) پورٹ_BYTE_ALIGNMENT_نقاب );
        x_کل_ڈھیر_سائز -= ( size_t ) ( ux_آغاز_پتہ - ( پورٹ_اشارہ_گر_سائز_TYPE ) uc_ڈھیر );
    }

    #اگر ( config_ENABLE_ڈھیر_PROTECTOR == 1 )
    {
        v_Application_Get_Random_ڈھیر_Canary( &( x_ڈھیر_Canary ) );
    }
    #اگر_ختم

    /* xStart is used to hold a pointer to the first item in the list of free
     * blocks.  The void cast is used to prevent compiler warnings. */
    x_آغاز.px_اگلا_Free_بلاک = ( خالی * ) ڈھیر_PROTECT_بلاک_اشارہ_گر( ux_آغاز_پتہ );
    x_آغاز.x_بلاک_سائز = ( size_t ) 0;

    /* pxEnd is used to mark the end of the list of free blocks and is inserted
     * at the end of the heap space. */
    ux_انتہا_پتہ = ux_آغاز_پتہ + ( پورٹ_اشارہ_گر_سائز_TYPE ) x_کل_ڈھیر_سائز;
    ux_انتہا_پتہ -= ( پورٹ_اشارہ_گر_سائز_TYPE ) x_ڈھیر_Struct_سائز;
    ux_انتہا_پتہ &= ~( ( پورٹ_اشارہ_گر_سائز_TYPE ) پورٹ_BYTE_ALIGNMENT_نقاب );
    px_انتہا = ( بلاک_Link_t * ) ux_انتہا_پتہ;
    px_انتہا->x_بلاک_سائز = 0;
    px_انتہا->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( تہی );

    /* To start with there is a single free block that is sized to take up the
     * entire heap space, minus the space taken by pxEnd. */
    px_پہلا_Free_بلاک = ( بلاک_Link_t * ) ux_آغاز_پتہ;
    px_پہلا_Free_بلاک->x_بلاک_سائز = ( size_t ) ( ux_انتہا_پتہ - ( پورٹ_اشارہ_گر_سائز_TYPE ) px_پہلا_Free_بلاک );
    px_پہلا_Free_بلاک->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( px_انتہا );

    /* Only one block exists - and it covers the entire usable heap space. */
    x_Minimum_Ever_Free_بائٹیں_بقایا = px_پہلا_Free_بلاک->x_بلاک_سائز;
    x_Free_بائٹیں_بقایا = px_پہلا_Free_بلاک->x_بلاک_سائز;
}
/*-----------------------------------------------------------*/

ساکن خالی prv_داخل_کرو_بلاک_Into_Free_List( بلاک_Link_t * px_بلاک_مقصد_داخل_کرو ) /* PRIVILEGED_FUNCTION */
{
    بلاک_Link_t * pxIterator;
    uint8_t * puc;

    /* Iterate through the list until a block is found that has a higher address
     * than the block being inserted. */
    برائے( pxIterator = &x_آغاز; ڈھیر_PROTECT_بلاک_اشارہ_گر( pxIterator->px_اگلا_Free_بلاک ) < px_بلاک_مقصد_داخل_کرو; pxIterator = ڈھیر_PROTECT_بلاک_اشارہ_گر( pxIterator->px_اگلا_Free_بلاک ) )
    {
        /* Nothing to do here, just iterate to the right position. */
    }

    اگر( pxIterator != &x_آغاز )
    {
        ڈھیر_VALIDATE_بلاک_اشارہ_گر( pxIterator );
    }

    /* Do the block being inserted, and the block it is being inserted after
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) pxIterator;

    اگر( ( puc + pxIterator->x_بلاک_سائز ) == ( uint8_t * ) px_بلاک_مقصد_داخل_کرو )
    {
        pxIterator->x_بلاک_سائز += px_بلاک_مقصد_داخل_کرو->x_بلاک_سائز;
        px_بلاک_مقصد_داخل_کرو = pxIterator;
    }
    ورنہ
    {
        mtCOVERAGE_TEST_MARKER();
    }

    /* Do the block being inserted, and the block it is being inserted before
     * make a contiguous block of memory? */
    puc = ( uint8_t * ) px_بلاک_مقصد_داخل_کرو;

    اگر( ( puc + px_بلاک_مقصد_داخل_کرو->x_بلاک_سائز ) == ( uint8_t * ) ڈھیر_PROTECT_بلاک_اشارہ_گر( pxIterator->px_اگلا_Free_بلاک ) )
    {
        اگر( ڈھیر_PROTECT_بلاک_اشارہ_گر( pxIterator->px_اگلا_Free_بلاک ) != px_انتہا )
        {
            /* Form one big block from the two blocks. */
            px_بلاک_مقصد_داخل_کرو->x_بلاک_سائز += ڈھیر_PROTECT_بلاک_اشارہ_گر( pxIterator->px_اگلا_Free_بلاک )->x_بلاک_سائز;
            px_بلاک_مقصد_داخل_کرو->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( pxIterator->px_اگلا_Free_بلاک )->px_اگلا_Free_بلاک;
        }
        ورنہ
        {
            px_بلاک_مقصد_داخل_کرو->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( px_انتہا );
        }
    }
    ورنہ
    {
        px_بلاک_مقصد_داخل_کرو->px_اگلا_Free_بلاک = pxIterator->px_اگلا_Free_بلاک;
    }

    /* If the block being inserted plugged a gap, so was merged with the block
     * before and the block after, then it's pxNextFreeBlock pointer will have
     * already been set, and should not be set here as that would make it point
     * to itself. */
    اگر( pxIterator != px_بلاک_مقصد_داخل_کرو )
    {
        pxIterator->px_اگلا_Free_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( px_بلاک_مقصد_داخل_کرو );
    }
    ورنہ
    {
        mtCOVERAGE_TEST_MARKER();
    }
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Get_ڈھیر_Stats( ڈھیر_Stats_t * px_ڈھیر_Stats )
{
    بلاک_Link_t * px_بلاک;
    size_t x_بلاکیں = 0, x_Max_سائز = 0, x_Min_سائز = SIZE_MAX;

    vTaskSuspendAll();
    {
        px_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( x_آغاز.px_اگلا_Free_بلاک );

        /* pxBlock will be NULL if the heap has not been initialised.  The heap
         * is initialised automatically when the first allocation is made. */
        اگر( px_بلاک != تہی )
        {
            جب( px_بلاک != px_انتہا )
            {
                /* Increment the number of blocks and record the largest block seen
                 * so far. */
                x_بلاکیں++;

                اگر( px_بلاک->x_بلاک_سائز > x_Max_سائز )
                {
                    x_Max_سائز = px_بلاک->x_بلاک_سائز;
                }

                اگر( px_بلاک->x_بلاک_سائز < x_Min_سائز )
                {
                    x_Min_سائز = px_بلاک->x_بلاک_سائز;
                }

                /* Move to the next block in the chain until the last block is
                 * reached. */
                px_بلاک = ڈھیر_PROTECT_بلاک_اشارہ_گر( px_بلاک->px_اگلا_Free_بلاک );
            }
        }
    }
    ( خالی ) xTaskResumeAll();

    px_ڈھیر_Stats->x_سائز_کا_سب_سے_بڑا_Free_بلاک_اندر_بائٹیں = x_Max_سائز;
    px_ڈھیر_Stats->x_سائز_کا_سب_سے_چھوٹا_Free_بلاک_اندر_بائٹیں = x_Min_سائز;
    px_ڈھیر_Stats->x_نمبر_کا_Free_بلاکیں = x_بلاکیں;

    taskENTER_CRITICAL();
    {
        px_ڈھیر_Stats->x_دستیاب_ڈھیر_Space_اندر_بائٹیں = x_Free_بائٹیں_بقایا;
        px_ڈھیر_Stats->x_نمبر_کا_Successful_Allocations = x_نمبر_کا_Successful_Allocations;
        px_ڈھیر_Stats->x_نمبر_کا_Successful_Frees = x_نمبر_کا_Successful_Frees;
        px_ڈھیر_Stats->x_Minimum_Ever_Free_بائٹیں_بقایا = x_Minimum_Ever_Free_بائٹیں_بقایا;
    }
    taskEXIT_CRITICAL();
}
/*-----------------------------------------------------------*/

/*
 * Reset the state in this file. This state is normally initialized at start up.
 * This function must be called by the application before restarting the
 * scheduler.
 */
خالی v_پورٹ_ڈھیر_Reset_State( خالی )
{
    px_انتہا = تہی;

    x_Free_بائٹیں_بقایا = ( size_t ) 0U;
    x_Minimum_Ever_Free_بائٹیں_بقایا = ( size_t ) 0U;
    x_نمبر_کا_Successful_Allocations = ( size_t ) 0U;
    x_نمبر_کا_Successful_Frees = ( size_t ) 0U;
}
/*-----------------------------------------------------------*/
