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

#اگر defined( __MW__ )

    #شامل <stdint.h>
    #شامل <stdlib.h>
    #شامل <string.h>

    #شامل "FreeRTOS.h"

    #شامل "queue.h"
    #شامل "semphr.h"
    #شامل "task.h"

    #شامل "arc/arc_exception.h"
    #شامل "embARC_toolchain.h"
    #شامل "embARC_debug.h"

    #ifdef ENABLE_FREERTOS_TLS_DEBUG
        #define TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #وگرنه
        #define TLS_DEBUG( fmt, ... )
    #endif

/*
 * Runtime routines to execute constructors and
 * destructors for task local storage.
 */
    بیرونی تهی __mw_run_tls_dtor();
    بیرونی تهی __mw_run_tls_ctor();

    بیرونی uint32_t exc_nest_شمار;

/*
 * Linker generated symbols to mark .tls section addresses
 * first byte .. last byte
 */
    بیرونی نویسه _ftls[], _etls[];
    #pragma weak _ftls
    #pragma weak _etls

    تهی executable_requires_tls_section( تهی )
    {
        #اگر _ARC
            برای( ; ; )
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

    ایستا تهی * init_task_tls( تهی )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        تهی * tls = پوچ;

        #اگر FREERTOS_HEAP_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #وگرنه
            tls = pvPortMalloc( len );
        #endif

        اگر( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            memcpy( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        بازگشت tls;
    }

    ایستا تهی free_task_tls( تهی * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        اگر( task2free != پوچ )
        {
            تهی * tls = pvTaskGetThreadLocalStoragePointer( task2free, 0 );

            اگر( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                vPortFree( tls );
                vTaskSetThreadLocalStoragePointer( task2free, 0, پوچ );
            }
        }
    }

    تهی task_end_hook( تهی * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    ایستا تهی * get_isr_tls( تهی )
    {
        /* In an ISR */
        ایستا صحیح first = 1;

        اگر( _Rarely( first ) )
        {
            first = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        بازگشت ( تهی * ) _ftls;
    }
    #pragma off_inline(get_isr_tls)

    ایستا تهی * get_task_tls( تهی )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        اگر( cur_task == پوچ )
        {
            بازگشت get_isr_tls();
        }

        تهی * tls = pvTaskGetThreadLocalStoragePointer( cur_task, 0 );

        اگر( tls == پوچ )
        {
            tls = init_task_tls();

            اگر( tls )
            {
                vTaskSetThreadLocalStoragePointer( cur_task, 0, tls );
            }
            وگرنه
            {
                tls = get_isr_tls();
            }
        }

        بازگشت tls;
    }
    #pragma off_inline(get_task_tls)

    #اگر _ARC /* for ARC XCALLs need to preserve flags */
        بیرونی تهی * _Preserve_flags _mwget_tls( تهی );
    #endif

/*
 * Back end gens calls to find local data for this task
 */
    تهی * _mwget_tls( تهی )
    {
        اگر( _ftls == ( نویسه * ) 0 )
        {
            executable_requires_tls_section();
        }

        اگر( exc_nest_شمار > 0 ) /* In ISR */
        {
            بازگشت get_isr_tls();
        }
        وگرنه /* In Task */
        {
            بازگشت get_task_tls();
        }
    }


/* simple interface of thread safe */
    تعریفنوع xSemaphoreHandle _lock_t;
    #اگر configUSE_RECURSIVE_MUTEXES != 1
        #error "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #endif

    تهی _mwmutex_create( _lock_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    تهی _mwmutex_delete( _lock_t * mutex_ptr )
    {
        اگر( ( *mutex_ptr ) != پوچ )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    تهی _mwmutex_lock( _lock_t mutex )
    {
        اگر( ( mutex ) != پوچ )
        {
            وقتی( xSemaphoreTakeRecursive( mutex, portMAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    تهی _mwmutex_unlock( _lock_t mutex )
    {
        اگر( ( mutex ) != پوچ )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#وگرنه /* if defined( __MW__ ) */

#endif /* __MW__ */
