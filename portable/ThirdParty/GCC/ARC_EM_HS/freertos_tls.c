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

#எனில் defined( __MW__ )

    #அந்தர்பாவ <stdint.h>
    #அந்தர்பாவ <stdlib.h>
    #அந்தர்பாவ <string.h>

    #அந்தர்பாவ "FreeRTOS.h"

    #அந்தர்பாவ "queue.h"
    #அந்தர்பாவ "semphr.h"
    #அந்தர்பாவ "task.h"

    #அந்தர்பாவ "arc/arc_exception.h"
    #அந்தர்பாவ "embARC_toolchain.h"
    #அந்தர்பாவ "embARC_debug.h"

    #ifdef ENABLE_FREERTOS_TLS_DEBUG
        #define TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #இல்லையெனில்
        #define TLS_DEBUG( fmt, ... )
    #endif

/*
 * Runtime routines to execute constructors and
 * destructors for task local storage.
 */
    வெளி வெறுமை __mw_run_tls_dtor();
    வெளி வெறுமை __mw_run_tls_ctor();

    வெளி uint32_t exc_nest_மொத்தம்;

/*
 * Linker generated symbols to mark .tls section addresses
 * first byte .. last byte
 */
    வெளி எழுத்து _ftls[], _etls[];
    #pragma weak _ftls
    #pragma weak _etls

    வெறுமை executable_requires_tls_section( வெறுமை )
    {
        #எனில் _ARC
            க்கு( ; ; )
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

    நிலையான வெறுமை * init_task_tls( வெறுமை )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        வெறுமை * tls = வெற்று;

        #எனில் FREERTOS_HEAP_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #இல்லையெனில்
            tls = pvPortMalloc( len );
        #endif

        எனில்( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            memcpy( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        திரும்பு tls;
    }

    நிலையான வெறுமை free_task_tls( வெறுமை * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        எனில்( task2free != வெற்று )
        {
            வெறுமை * tls = pvTaskGetThreadLocalStoragePointer( task2free, 0 );

            எனில்( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                vPortFree( tls );
                vTaskSetThreadLocalStoragePointer( task2free, 0, வெற்று );
            }
        }
    }

    வெறுமை task_end_hook( வெறுமை * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    நிலையான வெறுமை * get_isr_tls( வெறுமை )
    {
        /* In an ISR */
        நிலையான முழு first = 1;

        எனில்( _Rarely( first ) )
        {
            first = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        திரும்பு ( வெறுமை * ) _ftls;
    }
    #pragma off_inline(get_isr_tls)

    நிலையான வெறுமை * get_task_tls( வெறுமை )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        எனில்( cur_task == வெற்று )
        {
            திரும்பு get_isr_tls();
        }

        வெறுமை * tls = pvTaskGetThreadLocalStoragePointer( cur_task, 0 );

        எனில்( tls == வெற்று )
        {
            tls = init_task_tls();

            எனில்( tls )
            {
                vTaskSetThreadLocalStoragePointer( cur_task, 0, tls );
            }
            இல்லையெனில்
            {
                tls = get_isr_tls();
            }
        }

        திரும்பு tls;
    }
    #pragma off_inline(get_task_tls)

    #எனில் _ARC /* for ARC XCALLs need to preserve flags */
        வெளி வெறுமை * _Preserve_flags _mwget_tls( வெறுமை );
    #endif

/*
 * Back end gens calls to find local data for this task
 */
    வெறுமை * _mwget_tls( வெறுமை )
    {
        எனில்( _ftls == ( எழுத்து * ) 0 )
        {
            executable_requires_tls_section();
        }

        எனில்( exc_nest_மொத்தம் > 0 ) /* In ISR */
        {
            திரும்பு get_isr_tls();
        }
        இல்லையெனில் /* In Task */
        {
            திரும்பு get_task_tls();
        }
    }


/* simple interface of thread safe */
    வகைவரை xSemaphoreHandle _lock_t;
    #எனில் configUSE_RECURSIVE_MUTEXES != 1
        #error "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #endif

    வெறுமை _mwmutex_create( _lock_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    வெறுமை _mwmutex_delete( _lock_t * mutex_ptr )
    {
        எனில்( ( *mutex_ptr ) != வெற்று )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    வெறுமை _mwmutex_lock( _lock_t mutex )
    {
        எனில்( ( mutex ) != வெற்று )
        {
            போது( xSemaphoreTakeRecursive( mutex, portMAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    வெறுமை _mwmutex_unlock( _lock_t mutex )
    {
        எனில்( ( mutex ) != வெற்று )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#இல்லையெனில் /* if defined( __MW__ ) */

#endif /* __MW__ */
