/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2020 Synopsys, Inc. or its affiliates.  All Rights Reserved.
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

#যদি defined( __MW__ )

    #অন্তর্ভাব <stdint.h>
    #অন্তর্ভাব <stdlib.h>
    #অন্তর্ভাব <string.h>

    #অন্তর্ভাব "FreeRTOS.h"

    #অন্তর্ভাব "queue.h"
    #অন্তর্ভাব "semphr.h"
    #অন্তর্ভাব "task.h"

    #অন্তর্ভাব "arc/arc_exception.h"
    #অন্তর্ভাব "embARC_toolchain.h"
    #অন্তর্ভাব "embARC_debug.h"

    #ifdef ENABLE_FREERTOS_TLS_DEBUG
        #define TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #অন্যথা
        #define TLS_DEBUG( fmt, ... )
    #endif

/*
 * Runtime routines to execute constructors and
 * destructors for task local storage.
 */
    বাহ্যিক শূন্য __mw_run_tls_dtor();
    বাহ্যিক শূন্য __mw_run_tls_ctor();

    বাহ্যিক uint32_t exc_nest_গুনতি;

/*
 * Linker generated symbols to mark .tls section addresses
 * first byte .. last byte
 */
    বাহ্যিক অক্ষর _ftls[], _etls[];
    #pragma weak _ftls
    #pragma weak _etls

    শূন্য executable_requires_tls_section( শূন্য )
    {
        #যদি _ARC
            জন্য( ; ; )
            {
                _flag( 1 );
                _nop();
                _nop();
                _nop();
                _nop();
                _nop();
            }
        #endif
    }
    #pragma off_inline(executable_requires_tls_section);
    #pragma alias(executable_requires_tls_section, "executable_requires_.tls_section");

    স্থির শূন্য * init_task_tls( শূন্য )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        শূন্য * tls = ফাঁকা;

        #যদি FREERTOS_HEAP_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #অন্যথা
            tls = pvPortMalloc( len );
        #endif

        যদি( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            memcpy( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        ফেরত tls;
    }

    স্থির শূন্য free_task_tls( শূন্য * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        যদি( task2free != ফাঁকা )
        {
            শূন্য * tls = pvTaskGetThreadLocalStoragePointer( task2free, 0 );

            যদি( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                vPortFree( tls );
                vTaskSetThreadLocalStoragePointer( task2free, 0, ফাঁকা );
            }
        }
    }

    শূন্য task_end_hook( শূন্য * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    স্থির শূন্য * get_isr_tls( শূন্য )
    {
        /* In an ISR */
        স্থির পূর্ণসংখ্যা first = 1;

        যদি( _Rarely( first ) )
        {
            first = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        ফেরত ( শূন্য * ) _ftls;
    }
    #pragma off_inline(get_isr_tls)

    স্থির শূন্য * get_task_tls( শূন্য )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        যদি( cur_task == ফাঁকা )
        {
            ফেরত get_isr_tls();
        }

        শূন্য * tls = pvTaskGetThreadLocalStoragePointer( cur_task, 0 );

        যদি( tls == ফাঁকা )
        {
            tls = init_task_tls();

            যদি( tls )
            {
                vTaskSetThreadLocalStoragePointer( cur_task, 0, tls );
            }
            অন্যথা
            {
                tls = get_isr_tls();
            }
        }

        ফেরত tls;
    }
    #pragma off_inline(get_task_tls)

    #যদি _ARC /* for ARC XCALLs need to preserve flags */
        বাহ্যিক শূন্য * _Preserve_flags _mwget_tls( শূন্য );
    #endif

/*
 * Back end gens calls to find local data for this task
 */
    শূন্য * _mwget_tls( শূন্য )
    {
        যদি( _ftls == ( অক্ষর * ) 0 )
        {
            executable_requires_tls_section();
        }

        যদি( exc_nest_গুনতি > 0 ) /* In ISR */
        {
            ফেরত get_isr_tls();
        }
        অন্যথা /* In Task */
        {
            ফেরত get_task_tls();
        }
    }


/* simple interface of thread safe */
    প্রকারলেখ xSemaphoreHandle _lock_t;
    #যদি configUSE_RECURSIVE_MUTEXES != 1
        #error "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #endif

    শূন্য _mwmutex_create( _lock_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    শূন্য _mwmutex_delete( _lock_t * mutex_ptr )
    {
        যদি( ( *mutex_ptr ) != ফাঁকা )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    শূন্য _mwmutex_lock( _lock_t mutex )
    {
        যদি( ( mutex ) != ফাঁকা )
        {
            যখন( xSemaphoreTakeRecursive( mutex, portMAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    শূন্য _mwmutex_unlock( _lock_t mutex )
    {
        যদি( ( mutex ) != ফাঁকা )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#অন্যথা /* if defined( __MW__ ) */

#endif /* __MW__ */
