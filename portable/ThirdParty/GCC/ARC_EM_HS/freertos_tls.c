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

#എങ്കിൽ defined( __MW__ )

    #അന്തര്ഭാവ <stdint.h>
    #അന്തര്ഭാവ <stdlib.h>
    #അന്തര്ഭാവ <string.h>

    #അന്തര്ഭാവ "FreeRTOS.h"

    #അന്തര്ഭാവ "queue.h"
    #അന്തര്ഭാവ "semphr.h"
    #അന്തര്ഭാവ "task.h"

    #അന്തര്ഭാവ "arc/arc_exception.h"
    #അന്തര്ഭാവ "embARC_toolchain.h"
    #അന്തര്ഭാവ "embARC_debug.h"

    #ifdef ENABLE_FREERTOS_TLS_DEBUG
        #define TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #അല്ലെങ്കിൽ
        #define TLS_DEBUG( fmt, ... )
    #endif

/*
 * Runtime routines to execute constructors and
 * destructors for task local storage.
 */
    ബാഹ്യ ശൂന്യം __mw_run_tls_dtor();
    ബാഹ്യ ശൂന്യം __mw_run_tls_ctor();

    ബാഹ്യ uint32_t exc_nest_എണ്ണം;

/*
 * Linker generated symbols to mark .tls section addresses
 * first byte .. last byte
 */
    ബാഹ്യ അക്ഷരം _ftls[], _etls[];
    #pragma weak _ftls
    #pragma weak _etls

    ശൂന്യം executable_requires_tls_section( ശൂന്യം )
    {
        #എങ്കിൽ _ARC
            വേണ്ടി( ; ; )
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

    സ്ഥിതം ശൂന്യം * init_task_tls( ശൂന്യം )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        ശൂന്യം * tls = ശൂന്യ;

        #എങ്കിൽ FREERTOS_HEAP_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #അല്ലെങ്കിൽ
            tls = pvPortMalloc( len );
        #endif

        എങ്കിൽ( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            memcpy( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        തിരികെ tls;
    }

    സ്ഥിതം ശൂന്യം free_task_tls( ശൂന്യം * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        എങ്കിൽ( task2free != ശൂന്യ )
        {
            ശൂന്യം * tls = pvTaskGetThreadLocalStoragePointer( task2free, 0 );

            എങ്കിൽ( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                vPortFree( tls );
                vTaskSetThreadLocalStoragePointer( task2free, 0, ശൂന്യ );
            }
        }
    }

    ശൂന്യം task_end_hook( ശൂന്യം * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    സ്ഥിതം ശൂന്യം * get_isr_tls( ശൂന്യം )
    {
        /* In an ISR */
        സ്ഥിതം പൂർണ്ണസംഖ്യ first = 1;

        എങ്കിൽ( _Rarely( first ) )
        {
            first = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        തിരികെ ( ശൂന്യം * ) _ftls;
    }
    #pragma off_inline(get_isr_tls)

    സ്ഥിതം ശൂന്യം * get_task_tls( ശൂന്യം )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        എങ്കിൽ( cur_task == ശൂന്യ )
        {
            തിരികെ get_isr_tls();
        }

        ശൂന്യം * tls = pvTaskGetThreadLocalStoragePointer( cur_task, 0 );

        എങ്കിൽ( tls == ശൂന്യ )
        {
            tls = init_task_tls();

            എങ്കിൽ( tls )
            {
                vTaskSetThreadLocalStoragePointer( cur_task, 0, tls );
            }
            അല്ലെങ്കിൽ
            {
                tls = get_isr_tls();
            }
        }

        തിരികെ tls;
    }
    #pragma off_inline(get_task_tls)

    #എങ്കിൽ _ARC /* for ARC XCALLs need to preserve flags */
        ബാഹ്യ ശൂന്യം * _Preserve_flags _mwget_tls( ശൂന്യം );
    #endif

/*
 * Back end gens calls to find local data for this task
 */
    ശൂന്യം * _mwget_tls( ശൂന്യം )
    {
        എങ്കിൽ( _ftls == ( അക്ഷരം * ) 0 )
        {
            executable_requires_tls_section();
        }

        എങ്കിൽ( exc_nest_എണ്ണം > 0 ) /* In ISR */
        {
            തിരികെ get_isr_tls();
        }
        അല്ലെങ്കിൽ /* In Task */
        {
            തിരികെ get_task_tls();
        }
    }


/* simple interface of thread safe */
    തരനിർവചനം xSemaphoreHandle _lock_t;
    #എങ്കിൽ configUSE_RECURSIVE_MUTEXES != 1
        #error "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #endif

    ശൂന്യം _mwmutex_create( _lock_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    ശൂന്യം _mwmutex_delete( _lock_t * mutex_ptr )
    {
        എങ്കിൽ( ( *mutex_ptr ) != ശൂന്യ )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    ശൂന്യം _mwmutex_lock( _lock_t mutex )
    {
        എങ്കിൽ( ( mutex ) != ശൂന്യ )
        {
            ആകുമ്പോൾ( xSemaphoreTakeRecursive( mutex, portMAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    ശൂന്യം _mwmutex_unlock( _lock_t mutex )
    {
        എങ്കിൽ( ( mutex ) != ശൂന്യ )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#അല്ലെങ്കിൽ /* if defined( __MW__ ) */

#endif /* __MW__ */
