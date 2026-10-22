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

#إذا defined( __MW__ )

    #ضمن <stdint.h>
    #ضمن <stdlib.h>
    #ضمن <string.h>

    #ضمن "FreeRTOS.h"

    #ضمن "queue.h"
    #ضمن "semphr.h"
    #ضمن "task.h"

    #ضمن "arc/arc_exception.h"
    #ضمن "embARC_toolchain.h"
    #ضمن "embARC_debug.h"

    #ifdef ENABLE_FREERTOS_TLS_DEBUG
        #define TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #وإلا
        #define TLS_DEBUG( fmt, ... )
    #endif

/*
 * Runtime routines to execute constructors and
 * destructors for task local storage.
 */
    خارجي فراغ __mw_run_tls_dtor();
    خارجي فراغ __mw_run_tls_ctor();

    خارجي uint32_t exc_nest_كدي;

/*
 * Linker generated symbols to mark .tls section addresses
 * first byte .. last byte
 */
    خارجي حرف _ftls[], _etls[];
    #pragma weak _ftls
    #pragma weak _etls

    فراغ executable_requires_tls_section( فراغ )
    {
        #إذا _ARC
            لكل( ; ; )
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

    ساكن فراغ * init_task_tls( فراغ )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        فراغ * tls = عدم;

        #إذا FREERTOS_HEAP_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #وإلا
            tls = pvPortMalloc( len );
        #endif

        إذا( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            memcpy( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        أرجع tls;
    }

    ساكن فراغ free_task_tls( فراغ * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        إذا( task2free != عدم )
        {
            فراغ * tls = pvTaskGetThreadLocalStoragePointer( task2free, 0 );

            إذا( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                vPortFree( tls );
                vTaskSetThreadLocalStoragePointer( task2free, 0, عدم );
            }
        }
    }

    فراغ task_end_hook( فراغ * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    ساكن فراغ * get_isr_tls( فراغ )
    {
        /* In an ISR */
        ساكن صحيح first = 1;

        إذا( _Rarely( first ) )
        {
            first = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        أرجع ( فراغ * ) _ftls;
    }
    #pragma off_inline(get_isr_tls)

    ساكن فراغ * get_task_tls( فراغ )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        إذا( cur_task == عدم )
        {
            أرجع get_isr_tls();
        }

        فراغ * tls = pvTaskGetThreadLocalStoragePointer( cur_task, 0 );

        إذا( tls == عدم )
        {
            tls = init_task_tls();

            إذا( tls )
            {
                vTaskSetThreadLocalStoragePointer( cur_task, 0, tls );
            }
            وإلا
            {
                tls = get_isr_tls();
            }
        }

        أرجع tls;
    }
    #pragma off_inline(get_task_tls)

    #إذا _ARC /* for ARC XCALLs need to preserve flags */
        خارجي فراغ * _Preserve_flags _mwget_tls( فراغ );
    #endif

/*
 * Back end gens calls to find local data for this task
 */
    فراغ * _mwget_tls( فراغ )
    {
        إذا( _ftls == ( حرف * ) 0 )
        {
            executable_requires_tls_section();
        }

        إذا( exc_nest_كدي > 0 ) /* In ISR */
        {
            أرجع get_isr_tls();
        }
        وإلا /* In Task */
        {
            أرجع get_task_tls();
        }
    }


/* simple interface of thread safe */
    تعريفنوع xSemaphoreHandle _lock_t;
    #إذا configUSE_RECURSIVE_MUTEXES != 1
        #error "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #endif

    فراغ _mwmutex_create( _lock_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    فراغ _mwmutex_delete( _lock_t * mutex_ptr )
    {
        إذا( ( *mutex_ptr ) != عدم )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    فراغ _mwmutex_lock( _lock_t mutex )
    {
        إذا( ( mutex ) != عدم )
        {
            طالما( xSemaphoreTakeRecursive( mutex, portMAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    فراغ _mwmutex_unlock( _lock_t mutex )
    {
        إذا( ( mutex ) != عدم )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#وإلا /* if defined( __MW__ ) */

#endif /* __MW__ */
