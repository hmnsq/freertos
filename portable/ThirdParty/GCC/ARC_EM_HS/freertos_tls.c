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

#ਜੇ defined( __MW__ )

    #ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
    #ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
    #ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

    #ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"

    #ਅਨ੍ਤਰ੍ਭਾਵ "queue.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "semphr.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

    #ਅਨ੍ਤਰ੍ਭਾਵ "arc/arc_exception.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "embARC_toolchain.h"
    #ਅਨ੍ਤਰ੍ਭਾਵ "embARC_debug.h"

    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ ENABLE_FREERTOS_TLS_DEBUG
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #ਨਹੀਂਤਾਂ
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TLS_DEBUG( fmt, ... )
    #ਜੇ_ਅੰਤ

/*
 * Runtime routines to execute constructors and
 * destructors for task local storage.
 */
    ਬਾਹਰੀ ਖਾਲੀ __mw_run_tls_dtor();
    ਬਾਹਰੀ ਖਾਲੀ __mw_run_tls_ctor();

    ਬਾਹਰੀ uint32_t exc_nest_ਗਿਣਤੀ;

/*
 * Linker generated symbols to mark .tls section addresses
 * first byte .. last byte
 */
    ਬਾਹਰੀ ਅੱਖਰ _ftls[], _etls[];
    #ਹਦਾਇਤ weak _ftls
    #ਹਦਾਇਤ weak _etls

    ਖਾਲੀ executable_requires_tls_section( ਖਾਲੀ )
    {
        #ਜੇ _ARC
            ਲਈ( ; ; )
            {
                _flag( 1 );
                _nop();
                _nop();
                _nop();
                _nop();
                _nop();
            }
        #ਜੇ_ਅੰਤ
    }
    #ਹਦਾਇਤ off_inline(executable_requires_tls_section);
    #ਹਦਾਇਤ alias(executable_requires_tls_section, "executable_requires_.tls_section");

    ਸਥਿਰ ਖਾਲੀ * init_task_tls( ਖਾਲੀ )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        ਖਾਲੀ * tls = ਨਿਰਾ;

        #ਜੇ FREERTOS_ਢੇਰ_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #ਨਹੀਂਤਾਂ
            tls = pv_ਪੋਰਟ_Malloc( len );
        #ਜੇ_ਅੰਤ

        ਜੇ( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            ਸਮ੍ਰਿਤੀ_ਨਕਲ( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        ਵਾਪਸ tls;
    }

    ਸਥਿਰ ਖਾਲੀ free_task_tls( ਖਾਲੀ * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        ਜੇ( task2free != ਨਿਰਾ )
        {
            ਖਾਲੀ * tls = pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ( task2free, 0 );

            ਜੇ( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                v_ਪੋਰਟ_Free( tls );
                v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ( task2free, 0, ਨਿਰਾ );
            }
        }
    }

    ਖਾਲੀ task_ਸਿਰਾ_hook( ਖਾਲੀ * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    ਸਥਿਰ ਖਾਲੀ * get_isr_tls( ਖਾਲੀ )
    {
        /* In an ISR */
        ਸਥਿਰ ਪੂਰਨ ਪਹਿਲਾ_2 = 1;

        ਜੇ( _Rarely( ਪਹਿਲਾ_2 ) )
        {
            ਪਹਿਲਾ_2 = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        ਵਾਪਸ ( ਖਾਲੀ * ) _ftls;
    }
    #ਹਦਾਇਤ off_inline(get_isr_tls)

    ਸਥਿਰ ਖਾਲੀ * get_task_tls( ਖਾਲੀ )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        ਜੇ( cur_task == ਨਿਰਾ )
        {
            ਵਾਪਸ get_isr_tls();
        }

        ਖਾਲੀ * tls = pv_Task_Get_Thread_Local_Storage_ਸੂਚਕ( cur_task, 0 );

        ਜੇ( tls == ਨਿਰਾ )
        {
            tls = init_task_tls();

            ਜੇ( tls )
            {
                v_Task_ਸੈੱਟ_Thread_Local_Storage_ਸੂਚਕ( cur_task, 0, tls );
            }
            ਨਹੀਂਤਾਂ
            {
                tls = get_isr_tls();
            }
        }

        ਵਾਪਸ tls;
    }
    #ਹਦਾਇਤ off_inline(get_task_tls)

    #ਜੇ _ARC /* for ARC XCALLs need to preserve flags */
        ਬਾਹਰੀ ਖਾਲੀ * _Preserve_flags _mwget_tls( ਖਾਲੀ );
    #ਜੇ_ਅੰਤ

/*
 * Back end gens calls to find local data for this task
 */
    ਖਾਲੀ * _mwget_tls( ਖਾਲੀ )
    {
        ਜੇ( _ftls == ( ਅੱਖਰ * ) 0 )
        {
            executable_requires_tls_section();
        }

        ਜੇ( exc_nest_ਗਿਣਤੀ > 0 ) /* In ISR */
        {
            ਵਾਪਸ get_isr_tls();
        }
        ਨਹੀਂਤਾਂ /* In Task */
        {
            ਵਾਪਸ get_task_tls();
        }
    }


/* simple interface of thread safe */
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ xSemaphoreHandle ਤਾਲਾ_t;
    #ਜੇ configUSE_RECURSIVE_MUTEXES != 1
        #ਗਲਤੀ "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #ਜੇ_ਅੰਤ

    ਖਾਲੀ _mwmutex_create( ਤਾਲਾ_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    ਖਾਲੀ _mwmutex_delete( ਤਾਲਾ_t * mutex_ptr )
    {
        ਜੇ( ( *mutex_ptr ) != ਨਿਰਾ )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    ਖਾਲੀ mwmutex_ਤਾਲਾ( ਤਾਲਾ_t mutex )
    {
        ਜੇ( ( mutex ) != ਨਿਰਾ )
        {
            ਜਦੋਂ( xSemaphoreTakeRecursive( mutex, ਪੋਰਟ_MAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    ਖਾਲੀ _mwmutex_unlock( ਤਾਲਾ_t mutex )
    {
        ਜੇ( ( mutex ) != ਨਿਰਾ )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#ਨਹੀਂਤਾਂ /* if defined( __MW__ ) */

#ਜੇ_ਅੰਤ /* __MW__ */
