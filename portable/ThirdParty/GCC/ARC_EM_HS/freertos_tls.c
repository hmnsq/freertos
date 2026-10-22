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

#ଯଦି defined( __MW__ )

    #ଅନ୍ତର୍ଭାଵ <stdint.h>
    #ଅନ୍ତର୍ଭାଵ <stdlib.h>
    #ଅନ୍ତର୍ଭାଵ <string.h>

    #ଅନ୍ତର୍ଭାଵ "FreeRTOS.h"

    #ଅନ୍ତର୍ଭାଵ "queue.h"
    #ଅନ୍ତର୍ଭାଵ "semphr.h"
    #ଅନ୍ତର୍ଭାଵ "task.h"

    #ଅନ୍ତର୍ଭାଵ "arc/arc_exception.h"
    #ଅନ୍ତର୍ଭାଵ "embARC_toolchain.h"
    #ଅନ୍ତର୍ଭାଵ "embARC_debug.h"

    #ifdef ENABLE_FREERTOS_TLS_DEBUG
        #define TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #ଅନ୍ୟଥା
        #define TLS_DEBUG( fmt, ... )
    #endif

/*
 * Runtime routines to execute constructors and
 * destructors for task local storage.
 */
    ବାହ୍ୟ ଶୂନ୍ୟ __mw_run_tls_dtor();
    ବାହ୍ୟ ଶୂନ୍ୟ __mw_run_tls_ctor();

    ବାହ୍ୟ uint32_t exc_nest_ଗଣନା;

/*
 * Linker generated symbols to mark .tls section addresses
 * first byte .. last byte
 */
    ବାହ୍ୟ ଅକ୍ଷର _ftls[], _etls[];
    #pragma weak _ftls
    #pragma weak _etls

    ଶୂନ୍ୟ executable_requires_tls_section( ଶୂନ୍ୟ )
    {
        #ଯଦି _ARC
            ପାଇଁ( ; ; )
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

    ସ୍ଥିର ଶୂନ୍ୟ * init_task_tls( ଶୂନ୍ୟ )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        ଶୂନ୍ୟ * tls = ଖାଲି;

        #ଯଦି FREERTOS_HEAP_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #ଅନ୍ୟଥା
            tls = pvPortMalloc( len );
        #endif

        ଯଦି( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            memcpy( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        ଫେରନ୍ତୁ tls;
    }

    ସ୍ଥିର ଶୂନ୍ୟ free_task_tls( ଶୂନ୍ୟ * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        ଯଦି( task2free != ଖାଲି )
        {
            ଶୂନ୍ୟ * tls = pvTaskGetThreadLocalStoragePointer( task2free, 0 );

            ଯଦି( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                vPortFree( tls );
                vTaskSetThreadLocalStoragePointer( task2free, 0, ଖାଲି );
            }
        }
    }

    ଶୂନ୍ୟ task_end_hook( ଶୂନ୍ୟ * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    ସ୍ଥିର ଶୂନ୍ୟ * get_isr_tls( ଶୂନ୍ୟ )
    {
        /* In an ISR */
        ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା first = 1;

        ଯଦି( _Rarely( first ) )
        {
            first = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        ଫେରନ୍ତୁ ( ଶୂନ୍ୟ * ) _ftls;
    }
    #pragma off_inline(get_isr_tls)

    ସ୍ଥିର ଶୂନ୍ୟ * get_task_tls( ଶୂନ୍ୟ )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        ଯଦି( cur_task == ଖାଲି )
        {
            ଫେରନ୍ତୁ get_isr_tls();
        }

        ଶୂନ୍ୟ * tls = pvTaskGetThreadLocalStoragePointer( cur_task, 0 );

        ଯଦି( tls == ଖାଲି )
        {
            tls = init_task_tls();

            ଯଦି( tls )
            {
                vTaskSetThreadLocalStoragePointer( cur_task, 0, tls );
            }
            ଅନ୍ୟଥା
            {
                tls = get_isr_tls();
            }
        }

        ଫେରନ୍ତୁ tls;
    }
    #pragma off_inline(get_task_tls)

    #ଯଦି _ARC /* for ARC XCALLs need to preserve flags */
        ବାହ୍ୟ ଶୂନ୍ୟ * _Preserve_flags _mwget_tls( ଶୂନ୍ୟ );
    #endif

/*
 * Back end gens calls to find local data for this task
 */
    ଶୂନ୍ୟ * _mwget_tls( ଶୂନ୍ୟ )
    {
        ଯଦି( _ftls == ( ଅକ୍ଷର * ) 0 )
        {
            executable_requires_tls_section();
        }

        ଯଦି( exc_nest_ଗଣନା > 0 ) /* In ISR */
        {
            ଫେରନ୍ତୁ get_isr_tls();
        }
        ଅନ୍ୟଥା /* In Task */
        {
            ଫେରନ୍ତୁ get_task_tls();
        }
    }


/* simple interface of thread safe */
    ପ୍ରକାରବ୍ୟାଖ୍ୟା xSemaphoreHandle _lock_t;
    #ଯଦି configUSE_RECURSIVE_MUTEXES != 1
        #error "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #endif

    ଶୂନ୍ୟ _mwmutex_create( _lock_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    ଶୂନ୍ୟ _mwmutex_delete( _lock_t * mutex_ptr )
    {
        ଯଦି( ( *mutex_ptr ) != ଖାଲି )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    ଶୂନ୍ୟ _mwmutex_lock( _lock_t mutex )
    {
        ଯଦି( ( mutex ) != ଖାଲି )
        {
            ଯେତେବେଳେ( xSemaphoreTakeRecursive( mutex, portMAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    ଶୂନ୍ୟ _mwmutex_unlock( _lock_t mutex )
    {
        ଯଦି( ( mutex ) != ଖାଲି )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#ଅନ୍ୟଥା /* if defined( __MW__ ) */

#endif /* __MW__ */
