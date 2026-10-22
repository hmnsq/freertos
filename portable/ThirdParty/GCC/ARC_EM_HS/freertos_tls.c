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

#ಆದರೆ defined( __MW__ )

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

    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ ENABLE_FREERTOS_TLS_DEBUG
        #ವ್ಯಾಖ್ಯಾನಿಸು TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #ಇಲ್ಲದಿದ್ದರೆ
        #ವ್ಯಾಖ್ಯಾನಿಸು TLS_DEBUG( fmt, ... )
    #ಆದರೆ_ಅಂತ್ಯ

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
    ಬಾಹ್ಯ ಅಕ್ಷರ _ftls[], _etls[];
    #ಸೂಚನೆ weak _ftls
    #ಸೂಚನೆ weak _etls

    ಶೂನ್ಯ executable_requires_tls_section( ಶೂನ್ಯ )
    {
        #ಆದರೆ _ARC
            ಗಾಗಿ( ; ; )
            {
                _flag( 1 );
                _nop();
                _nop();
                _nop();
                _nop();
                _nop();
            }
        #ಆದರೆ_ಅಂತ್ಯ
    }
    #ಸೂಚನೆ off_inline(executable_requires_tls_section);
    #ಸೂಚನೆ alias(executable_requires_tls_section, "executable_requires_.tls_section");

    ಸ್ಥಿರ ಶೂನ್ಯ * init_task_tls( ಶೂನ್ಯ )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        ಶೂನ್ಯ * tls = ಖಾಲಿ;

        #ಆದರೆ FREERTOS_ರಾಶಿ_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #ಇಲ್ಲದಿದ್ದರೆ
            tls = pv_ಪೋರ್ಟ್_Malloc( len );
        #ಆದರೆ_ಅಂತ್ಯ

        ಆದರೆ( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            ಸ್ಮರಣೆ_ನಕಲು( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        ಹಿಂತಿರುಗಿ tls;
    }

    ಸ್ಥಿರ ಶೂನ್ಯ free_task_tls( ಶೂನ್ಯ * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        ಆದರೆ( task2free != ಖಾಲಿ )
        {
            ಶೂನ್ಯ * tls = pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ( task2free, 0 );

            ಆದರೆ( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                v_ಪೋರ್ಟ್_Free( tls );
                v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ( task2free, 0, ಖಾಲಿ );
            }
        }
    }

    ಶೂನ್ಯ task_ಕೊನೆ_hook( ಶೂನ್ಯ * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    ಸ್ಥಿರ ಶೂನ್ಯ * get_isr_tls( ಶೂನ್ಯ )
    {
        /* In an ISR */
        ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಮೊದಲ_2 = 1;

        ಆದರೆ( _Rarely( ಮೊದಲ_2 ) )
        {
            ಮೊದಲ_2 = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        ಹಿಂತಿರುಗಿ ( ಶೂನ್ಯ * ) _ftls;
    }
    #ಸೂಚನೆ off_inline(get_isr_tls)

    ಸ್ಥಿರ ಶೂನ್ಯ * get_task_tls( ಶೂನ್ಯ )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        ಆದರೆ( cur_task == ಖಾಲಿ )
        {
            ಹಿಂತಿರುಗಿ get_isr_tls();
        }

        ಶೂನ್ಯ * tls = pv_Task_Get_Thread_Local_Storage_ಸೂಚಕ( cur_task, 0 );

        ಆದರೆ( tls == ಖಾಲಿ )
        {
            tls = init_task_tls();

            ಆದರೆ( tls )
            {
                v_Task_ಗಣ_Thread_Local_Storage_ಸೂಚಕ( cur_task, 0, tls );
            }
            ಇಲ್ಲದಿದ್ದರೆ
            {
                tls = get_isr_tls();
            }
        }

        ಹಿಂತಿರುಗಿ tls;
    }
    #ಸೂಚನೆ off_inline(get_task_tls)

    #ಆದರೆ _ARC /* for ARC XCALLs need to preserve flags */
        ಬಾಹ್ಯ ಶೂನ್ಯ * _Preserve_flags _mwget_tls( ಶೂನ್ಯ );
    #ಆದರೆ_ಅಂತ್ಯ

/*
 * Back end gens calls to find local data for this task
 */
    ಶೂನ್ಯ * _mwget_tls( ಶೂನ್ಯ )
    {
        ಆದರೆ( _ftls == ( ಅಕ್ಷರ * ) 0 )
        {
            executable_requires_tls_section();
        }

        ಆದರೆ( exc_nest_ಎಣಿಕೆ > 0 ) /* In ISR */
        {
            ಹಿಂತಿರುಗಿ get_isr_tls();
        }
        ಇಲ್ಲದಿದ್ದರೆ /* In Task */
        {
            ಹಿಂತಿರುಗಿ get_task_tls();
        }
    }


/* simple interface of thread safe */
    ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ xSemaphoreHandle ಬೀಗ_t;
    #ಆದರೆ configUSE_RECURSIVE_MUTEXES != 1
        #ದೋಷ "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #ಆದರೆ_ಅಂತ್ಯ

    ಶೂನ್ಯ _mwmutex_create( ಬೀಗ_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    ಶೂನ್ಯ _mwmutex_delete( ಬೀಗ_t * mutex_ptr )
    {
        ಆದರೆ( ( *mutex_ptr ) != ಖಾಲಿ )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    ಶೂನ್ಯ mwmutex_ಬೀಗ( ಬೀಗ_t mutex )
    {
        ಆದರೆ( ( mutex ) != ಖಾಲಿ )
        {
            ಆಗ( xSemaphoreTakeRecursive( mutex, ಪೋರ್ಟ್_MAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    ಶೂನ್ಯ _mwmutex_unlock( ಬೀಗ_t mutex )
    {
        ಆದರೆ( ( mutex ) != ಖಾಲಿ )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#ಇಲ್ಲದಿದ್ದರೆ /* if defined( __MW__ ) */

#ಆದರೆ_ಅಂತ್ಯ /* __MW__ */
