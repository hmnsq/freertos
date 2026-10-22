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

#अगर defined( __MW__ )

    #समावेश <stdint.h>
    #समावेश <stdlib.h>
    #समावेश <string.h>

    #समावेश "FreeRTOS.h"

    #समावेश "queue.h"
    #समावेश "semphr.h"
    #समावेश "task.h"

    #समावेश "arc/arc_exception.h"
    #समावेश "embARC_toolchain.h"
    #समावेश "embARC_debug.h"

    #अगर_घोषित ENABLE_FREERTOS_TLS_DEBUG
        #घोषणा TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #अन्यथा
        #घोषणा TLS_DEBUG( fmt, ... )
    #पूर्ण_अगर

/*
 * Runtime routines to execute constructors and
 * destructors for task local storage.
 */
    बाह्य व्योम __mw_run_tls_dtor();
    बाह्य व्योम __mw_run_tls_ctor();

    बाह्य uint32_t exc_nest_गिनती;

/*
 * Linker generated symbols to mark .tls section addresses
 * first byte .. last byte
 */
    बाह्य अक्षर _ftls[], _etls[];
    #आशय weak _ftls
    #आशय weak _etls

    व्योम executable_requires_tls_section( व्योम )
    {
        #अगर _ARC
            क्रम( ; ; )
            {
                _flag( 1 );
                _nop();
                _nop();
                _nop();
                _nop();
                _nop();
            }
        #पूर्ण_अगर
    }
    #आशय off_inline(executable_requires_tls_section);
    #आशय alias(executable_requires_tls_section, "executable_requires_.tls_section");

    अटल व्योम * init_task_tls( व्योम )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        व्योम * tls = शून्य;

        #अगर FREERTOS_HEAP_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #अन्यथा
            tls = pvPortMalloc( len );
        #पूर्ण_अगर

        अगर( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            स_नकल( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        वापस tls;
    }

    अटल व्योम free_task_tls( व्योम * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        अगर( task2free != शून्य )
        {
            व्योम * tls = pvTaskGetThreadLocalStoragePointer( task2free, 0 );

            अगर( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                vPortFree( tls );
                vTaskSetThreadLocalStoragePointer( task2free, 0, शून्य );
            }
        }
    }

    व्योम task_end_hook( व्योम * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    अटल व्योम * get_isr_tls( व्योम )
    {
        /* In an ISR */
        अटल पूर्णांक first = 1;

        अगर( _Rarely( first ) )
        {
            first = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        वापस ( व्योम * ) _ftls;
    }
    #आशय off_inline(get_isr_tls)

    अटल व्योम * get_task_tls( व्योम )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        अगर( cur_task == शून्य )
        {
            वापस get_isr_tls();
        }

        व्योम * tls = pvTaskGetThreadLocalStoragePointer( cur_task, 0 );

        अगर( tls == शून्य )
        {
            tls = init_task_tls();

            अगर( tls )
            {
                vTaskSetThreadLocalStoragePointer( cur_task, 0, tls );
            }
            अन्यथा
            {
                tls = get_isr_tls();
            }
        }

        वापस tls;
    }
    #आशय off_inline(get_task_tls)

    #अगर _ARC /* for ARC XCALLs need to preserve flags */
        बाह्य व्योम * _Preserve_flags _mwget_tls( व्योम );
    #पूर्ण_अगर

/*
 * Back end gens calls to find local data for this task
 */
    व्योम * _mwget_tls( व्योम )
    {
        अगर( _ftls == ( अक्षर * ) 0 )
        {
            executable_requires_tls_section();
        }

        अगर( exc_nest_गिनती > 0 ) /* In ISR */
        {
            वापस get_isr_tls();
        }
        अन्यथा /* In Task */
        {
            वापस get_task_tls();
        }
    }


/* simple interface of thread safe */
    प्रकार xSemaphoreHandle _lock_t;
    #अगर configUSE_RECURSIVE_MUTEXES != 1
        #त्रुटि "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #पूर्ण_अगर

    व्योम _mwmutex_create( _lock_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    व्योम _mwmutex_delete( _lock_t * mutex_ptr )
    {
        अगर( ( *mutex_ptr ) != शून्य )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    व्योम _mwmutex_lock( _lock_t mutex )
    {
        अगर( ( mutex ) != शून्य )
        {
            जबतक( xSemaphoreTakeRecursive( mutex, portMAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    व्योम _mwmutex_unlock( _lock_t mutex )
    {
        अगर( ( mutex ) != शून्य )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#अन्यथा /* if defined( __MW__ ) */

#पूर्ण_अगर /* __MW__ */
