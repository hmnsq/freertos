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

#གལ་སྲིད defined( __MW__ )

    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>

    #include "FreeRTOS.h"

    #include "queue.h"
    #include "semphr.h"
    #include "task.h"

    #include "arc/arc_exception.h"
    #include "embARC_toolchain.h"
    #include "embARC_debug.h"

    #ifdef ENABLE_FREERTOS_TLS_DEBUG
        #define TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #དེ་མིན
        #define TLS_DEBUG( fmt, ... )
    #endif

/*
 * Runtime routines to execute constructors and
 * destructors for task local storage.
 */
    extern void __mw_run_tls_dtor();
    extern void __mw_run_tls_ctor();

    extern uint32_t exc_nest_count;

/*
 * Linker generated symbols to mark .tls section addresses
 * first byte .. last byte
 */
    extern var_na _ftls[], _etls[];
    #pragma weak _ftls
    #pragma weak _etls

    void executable_requires_tls_section( void )
    {
        #གལ་སྲིད _ARC
            དོན་ལུ( ; ; )
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

    static void * init_task_tls( void )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        void * tls = NULL;

        #གལ་སྲིད FREERTOS_HEAP_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #དེ་མིན
            tls = pvPortMalloc( len );
        #endif

        གལ་སྲིད( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            memcpy( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        ལོག tls;
    }

    static void free_task_tls( void * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        གལ་སྲིད( task2free != NULL )
        {
            void * tls = pvTaskGetThreadLocalStoragePointer( task2free, 0 );

            གལ་སྲིད( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                vPortFree( tls );
                vTaskSetThreadLocalStoragePointer( task2free, 0, NULL );
            }
        }
    }

    void task_end_hook( void * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    static void * get_isr_tls( void )
    {
        /* In an ISR */
        static ཧྲིལ first = 1;

        གལ་སྲིད( _Rarely( first ) )
        {
            first = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        ལོག ( void * ) _ftls;
    }
    #pragma off_inline(get_isr_tls)

    static void * get_task_tls( void )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        གལ་སྲིད( cur_task == NULL )
        {
            ལོག get_isr_tls();
        }

        void * tls = pvTaskGetThreadLocalStoragePointer( cur_task, 0 );

        གལ་སྲིད( tls == NULL )
        {
            tls = init_task_tls();

            གལ་སྲིད( tls )
            {
                vTaskSetThreadLocalStoragePointer( cur_task, 0, tls );
            }
            དེ་མིན
            {
                tls = get_isr_tls();
            }
        }

        ལོག tls;
    }
    #pragma off_inline(get_task_tls)

    #གལ་སྲིད _ARC /* for ARC XCALLs need to preserve flags */
        extern void * _Preserve_flags _mwget_tls( void );
    #endif

/*
 * Back end gens calls to find local data for this task
 */
    void * _mwget_tls( void )
    {
        གལ་སྲིད( _ftls == ( var_na * ) 0 )
        {
            executable_requires_tls_section();
        }

        གལ་སྲིད( exc_nest_count > 0 ) /* In ISR */
        {
            ལོག get_isr_tls();
        }
        དེ་མིན /* In Task */
        {
            ལོག get_task_tls();
        }
    }


/* simple interface of thread safe */
    typedef xSemaphoreHandle _lock_t;
    #གལ་སྲིད configUSE_RECURSIVE_MUTEXES != 1
        #error "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #endif

    void _mwmutex_create( _lock_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    void _mwmutex_delete( _lock_t * mutex_ptr )
    {
        གལ་སྲིད( ( *mutex_ptr ) != NULL )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    void _mwmutex_lock( _lock_t mutex )
    {
        གལ་སྲིད( ( mutex ) != NULL )
        {
            སྐབས( xSemaphoreTakeRecursive( mutex, portMAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    void _mwmutex_unlock( _lock_t mutex )
    {
        གལ་སྲིད( ( mutex ) != NULL )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#དེ་མིན /* if defined( __MW__ ) */

#endif /* __MW__ */
