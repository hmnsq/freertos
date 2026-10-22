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

#જો defined( __MW__ )

    #અન્તર્ભાવ <stdint.h>
    #અન્તર્ભાવ <stdlib.h>
    #અન્તર્ભાવ <string.h>

    #અન્તર્ભાવ "FreeRTOS.h"

    #અન્તર્ભાવ "queue.h"
    #અન્તર્ભાવ "semphr.h"
    #અન્તર્ભાવ "task.h"

    #અન્તર્ભાવ "arc/arc_exception.h"
    #અન્તર્ભાવ "embARC_toolchain.h"
    #અન્તર્ભાવ "embARC_debug.h"

    #ifdef ENABLE_FREERTOS_TLS_DEBUG
        #define TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #નહીંતર
        #define TLS_DEBUG( fmt, ... )
    #endif

/*
 * Runtime routines to execute constructors and
 * destructors for task local storage.
 */
    બાહ્ય શૂન્ય __mw_run_tls_dtor();
    બાહ્ય શૂન્ય __mw_run_tls_ctor();

    બાહ્ય uint32_t exc_nest_ગણતરી;

/*
 * Linker generated symbols to mark .tls section addresses
 * first byte .. last byte
 */
    બાહ્ય અક્ષર _ftls[], _etls[];
    #pragma weak _ftls
    #pragma weak _etls

    શૂન્ય executable_requires_tls_section( શૂન્ય )
    {
        #જો _ARC
            માટે( ; ; )
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

    સ્થિર શૂન્ય * init_task_tls( શૂન્ય )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        શૂન્ય * tls = ખાલી;

        #જો FREERTOS_HEAP_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #નહીંતર
            tls = pvPortMalloc( len );
        #endif

        જો( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            memcpy( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        પાછા tls;
    }

    સ્થિર શૂન્ય free_task_tls( શૂન્ય * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        જો( task2free != ખાલી )
        {
            શૂન્ય * tls = pvTaskGetThreadLocalStoragePointer( task2free, 0 );

            જો( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                vPortFree( tls );
                vTaskSetThreadLocalStoragePointer( task2free, 0, ખાલી );
            }
        }
    }

    શૂન્ય task_end_hook( શૂન્ય * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    સ્થિર શૂન્ય * get_isr_tls( શૂન્ય )
    {
        /* In an ISR */
        સ્થિર પૂર્ણાંક first = 1;

        જો( _Rarely( first ) )
        {
            first = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        પાછા ( શૂન્ય * ) _ftls;
    }
    #pragma off_inline(get_isr_tls)

    સ્થિર શૂન્ય * get_task_tls( શૂન્ય )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        જો( cur_task == ખાલી )
        {
            પાછા get_isr_tls();
        }

        શૂન્ય * tls = pvTaskGetThreadLocalStoragePointer( cur_task, 0 );

        જો( tls == ખાલી )
        {
            tls = init_task_tls();

            જો( tls )
            {
                vTaskSetThreadLocalStoragePointer( cur_task, 0, tls );
            }
            નહીંતર
            {
                tls = get_isr_tls();
            }
        }

        પાછા tls;
    }
    #pragma off_inline(get_task_tls)

    #જો _ARC /* for ARC XCALLs need to preserve flags */
        બાહ્ય શૂન્ય * _Preserve_flags _mwget_tls( શૂન્ય );
    #endif

/*
 * Back end gens calls to find local data for this task
 */
    શૂન્ય * _mwget_tls( શૂન્ય )
    {
        જો( _ftls == ( અક્ષર * ) 0 )
        {
            executable_requires_tls_section();
        }

        જો( exc_nest_ગણતરી > 0 ) /* In ISR */
        {
            પાછા get_isr_tls();
        }
        નહીંતર /* In Task */
        {
            પાછા get_task_tls();
        }
    }


/* simple interface of thread safe */
    પ્રકારવ્યાખ્યા xSemaphoreHandle _lock_t;
    #જો configUSE_RECURSIVE_MUTEXES != 1
        #error "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #endif

    શૂન્ય _mwmutex_create( _lock_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    શૂન્ય _mwmutex_delete( _lock_t * mutex_ptr )
    {
        જો( ( *mutex_ptr ) != ખાલી )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    શૂન્ય _mwmutex_lock( _lock_t mutex )
    {
        જો( ( mutex ) != ખાલી )
        {
            જ્યારે( xSemaphoreTakeRecursive( mutex, portMAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    શૂન્ય _mwmutex_unlock( _lock_t mutex )
    {
        જો( ( mutex ) != ખાલી )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#નહીંતર /* if defined( __MW__ ) */

#endif /* __MW__ */
