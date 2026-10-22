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

#ಯದಿ defined( __MW__ )

    #ಅನ್ತರ್ಭಾವ <stdint.h>
    #ಅನ್ತರ್ಭಾವ <stdlib.h>
    #ಅನ್ತರ್ಭಾವ <string.h>

    #ಅನ್ತರ್ಭಾವ "FreeRTOS.h"

    #ಅನ್ತರ್ಭಾವ "queue.h"
    #ಅನ್ತರ್ಭಾವ "semphr.h"
    #ಅನ್ತರ್ಭಾವ "task.h"

    #ಅನ್ತರ್ಭಾವ "arc/arc_exception.h"
    #ಅನ್ತರ್ಭಾವ "embARC_toolchain.h"
    #ಅನ್ತರ್ಭಾವ "embARC_debug.h"

    #ifdef ENABLE_FREERTOS_TLS_DEBUG
        #define TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #ಅನ್ಯಥಾ
        #define TLS_DEBUG( fmt, ... )
    #endif

/*
 * Runtime routines to execute constructors and
 * destructors for task local storage.
 */
    ಬಾಹ್ಯ ಶೂನ್ಯ __mw_run_tls_dtor();
    ಬಾಹ್ಯ ಶೂನ್ಯ __mw_run_tls_ctor();

    ಬಾಹ್ಯ uint32_t exc_nest_ಎಣಿಕೆ;

/*
 * Linker generated symbols to mark .tls section addresses
 * first byte .. last byte
 */
    ಬಾಹ್ಯ ವರ್ಣ _ftls[], _etls[];
    #pragma weak _ftls
    #pragma weak _etls

    ಶೂನ್ಯ executable_requires_tls_section( ಶೂನ್ಯ )
    {
        #ಯದಿ _ARC
            ಪ್ರತಿ( ; ; )
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

    ಸ್ಥಿರ ಶೂನ್ಯ * init_task_tls( ಶೂನ್ಯ )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        ಶೂನ್ಯ * tls = ರಿಕ್ತ;

        #ಯದಿ FREERTOS_HEAP_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #ಅನ್ಯಥಾ
            tls = pvPortMalloc( len );
        #endif

        ಯದಿ( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            memcpy( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        ಪ್ರತ್ಯಾಗಮ tls;
    }

    ಸ್ಥಿರ ಶೂನ್ಯ free_task_tls( ಶೂನ್ಯ * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        ಯದಿ( task2free != ರಿಕ್ತ )
        {
            ಶೂನ್ಯ * tls = pvTaskGetThreadLocalStoragePointer( task2free, 0 );

            ಯದಿ( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                vPortFree( tls );
                vTaskSetThreadLocalStoragePointer( task2free, 0, ರಿಕ್ತ );
            }
        }
    }

    ಶೂನ್ಯ task_end_hook( ಶೂನ್ಯ * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    ಸ್ಥಿರ ಶೂನ್ಯ * get_isr_tls( ಶೂನ್ಯ )
    {
        /* In an ISR */
        ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ first = 1;

        ಯದಿ( _Rarely( first ) )
        {
            first = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        ಪ್ರತ್ಯಾಗಮ ( ಶೂನ್ಯ * ) _ftls;
    }
    #pragma off_inline(get_isr_tls)

    ಸ್ಥಿರ ಶೂನ್ಯ * get_task_tls( ಶೂನ್ಯ )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        ಯದಿ( cur_task == ರಿಕ್ತ )
        {
            ಪ್ರತ್ಯಾಗಮ get_isr_tls();
        }

        ಶೂನ್ಯ * tls = pvTaskGetThreadLocalStoragePointer( cur_task, 0 );

        ಯದಿ( tls == ರಿಕ್ತ )
        {
            tls = init_task_tls();

            ಯದಿ( tls )
            {
                vTaskSetThreadLocalStoragePointer( cur_task, 0, tls );
            }
            ಅನ್ಯಥಾ
            {
                tls = get_isr_tls();
            }
        }

        ಪ್ರತ್ಯಾಗಮ tls;
    }
    #pragma off_inline(get_task_tls)

    #ಯದಿ _ARC /* for ARC XCALLs need to preserve flags */
        ಬಾಹ್ಯ ಶೂನ್ಯ * _Preserve_flags _mwget_tls( ಶೂನ್ಯ );
    #endif

/*
 * Back end gens calls to find local data for this task
 */
    ಶೂನ್ಯ * _mwget_tls( ಶೂನ್ಯ )
    {
        ಯದಿ( _ftls == ( ವರ್ಣ * ) 0 )
        {
            executable_requires_tls_section();
        }

        ಯದಿ( exc_nest_ಎಣಿಕೆ > 0 ) /* In ISR */
        {
            ಪ್ರತ್ಯಾಗಮ get_isr_tls();
        }
        ಅನ್ಯಥಾ /* In Task */
        {
            ಪ್ರತ್ಯಾಗಮ get_task_tls();
        }
    }


/* simple interface of thread safe */
    ಪ್ರಕಾರನಿರ್ದೇಶ xSemaphoreHandle _lock_t;
    #ಯದಿ configUSE_RECURSIVE_MUTEXES != 1
        #error "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #endif

    ಶೂನ್ಯ _mwmutex_create( _lock_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    ಶೂನ್ಯ _mwmutex_delete( _lock_t * mutex_ptr )
    {
        ಯದಿ( ( *mutex_ptr ) != ರಿಕ್ತ )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    ಶೂನ್ಯ _mwmutex_lock( _lock_t mutex )
    {
        ಯದಿ( ( mutex ) != ರಿಕ್ತ )
        {
            ಯಾವತ್( xSemaphoreTakeRecursive( mutex, portMAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    ಶೂನ್ಯ _mwmutex_unlock( _lock_t mutex )
    {
        ಯದಿ( ( mutex ) != ರಿಕ್ತ )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#ಅನ್ಯಥಾ /* if defined( __MW__ ) */

#endif /* __MW__ */
