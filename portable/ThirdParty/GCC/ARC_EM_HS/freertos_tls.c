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

#ఒకవేళ defined( __MW__ )

    #అన్తర్భావ <stdint.h>
    #అన్తర్భావ <stdlib.h>
    #అన్తర్భావ <string.h>

    #అన్తర్భావ "FreeRTOS.h"

    #అన్తర్భావ "queue.h"
    #అన్తర్భావ "semphr.h"
    #అన్తర్భావ "task.h"

    #అన్తర్భావ "arc/arc_exception.h"
    #అన్తర్భావ "embARC_toolchain.h"
    #అన్తర్భావ "embARC_debug.h"

    #నిర్వచితమైతే ENABLE_FREERTOS_TLS_DEBUG
        #నిర్వచించు TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #లేకపోతే
        #నిర్వచించు TLS_DEBUG( fmt, ... )
    #అయితే_ముగింపు

/*
 * Runtime routines to execute constructors and
 * destructors for task local storage.
 */
    బాహ్య శూన్య __mw_run_tls_dtor();
    బాహ్య శూన్య __mw_run_tls_ctor();

    బాహ్య uint32_t exc_nest_లెక్క;

/*
 * Linker generated symbols to mark .tls section addresses
 * first byte .. last byte
 */
    బాహ్య అక్షరం _ftls[], _etls[];
    #సూచన weak _ftls
    #సూచన weak _etls

    శూన్య executable_requires_tls_section( శూన్య )
    {
        #ఒకవేళ _ARC
            కొరకు( ; ; )
            {
                _flag( 1 );
                _nop();
                _nop();
                _nop();
                _nop();
                _nop();
            }
        #అయితే_ముగింపు
    }
    #సూచన off_inline(executable_requires_tls_section);
    #సూచన alias(executable_requires_tls_section, "executable_requires_.tls_section");

    స్థిర శూన్య * init_task_tls( శూన్య )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        శూన్య * tls = ఖాళీ;

        #ఒకవేళ FREERTOS_కుప్ప_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #లేకపోతే
            tls = pv_పోర్టు_Malloc( len );
        #అయితే_ముగింపు

        ఒకవేళ( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            జ్ఞాపకం_నకలు( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        తిరిగి tls;
    }

    స్థిర శూన్య free_task_tls( శూన్య * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        ఒకవేళ( task2free != ఖాళీ )
        {
            శూన్య * tls = pv_Task_Get_Thread_Local_Storage_సూచిక( task2free, 0 );

            ఒకవేళ( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                v_పోర్టు_Free( tls );
                v_Task_సమితి_Thread_Local_Storage_సూచిక( task2free, 0, ఖాళీ );
            }
        }
    }

    శూన్య task_చివర_hook( శూన్య * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    స్థిర శూన్య * get_isr_tls( శూన్య )
    {
        /* In an ISR */
        స్థిర పూర్ణాంకం మొదటి_2 = 1;

        ఒకవేళ( _Rarely( మొదటి_2 ) )
        {
            మొదటి_2 = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        తిరిగి ( శూన్య * ) _ftls;
    }
    #సూచన off_inline(get_isr_tls)

    స్థిర శూన్య * get_task_tls( శూన్య )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        ఒకవేళ( cur_task == ఖాళీ )
        {
            తిరిగి get_isr_tls();
        }

        శూన్య * tls = pv_Task_Get_Thread_Local_Storage_సూచిక( cur_task, 0 );

        ఒకవేళ( tls == ఖాళీ )
        {
            tls = init_task_tls();

            ఒకవేళ( tls )
            {
                v_Task_సమితి_Thread_Local_Storage_సూచిక( cur_task, 0, tls );
            }
            లేకపోతే
            {
                tls = get_isr_tls();
            }
        }

        తిరిగి tls;
    }
    #సూచన off_inline(get_task_tls)

    #ఒకవేళ _ARC /* for ARC XCALLs need to preserve flags */
        బాహ్య శూన్య * _Preserve_flags _mwget_tls( శూన్య );
    #అయితే_ముగింపు

/*
 * Back end gens calls to find local data for this task
 */
    శూన్య * _mwget_tls( శూన్య )
    {
        ఒకవేళ( _ftls == ( అక్షరం * ) 0 )
        {
            executable_requires_tls_section();
        }

        ఒకవేళ( exc_nest_లెక్క > 0 ) /* In ISR */
        {
            తిరిగి get_isr_tls();
        }
        లేకపోతే /* In Task */
        {
            తిరిగి get_task_tls();
        }
    }


/* simple interface of thread safe */
    రకనిర్వచనం xSemaphoreHandle తాళం_t;
    #ఒకవేళ configUSE_RECURSIVE_MUTEXES != 1
        #దోషం "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #అయితే_ముగింపు

    శూన్య _mwmutex_create( తాళం_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    శూన్య _mwmutex_delete( తాళం_t * mutex_ptr )
    {
        ఒకవేళ( ( *mutex_ptr ) != ఖాళీ )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    శూన్య mwmutex_తాళం( తాళం_t mutex )
    {
        ఒకవేళ( ( mutex ) != ఖాళీ )
        {
            అయితే( xSemaphoreTakeRecursive( mutex, పోర్టు_MAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    శూన్య _mwmutex_unlock( తాళం_t mutex )
    {
        ఒకవేళ( ( mutex ) != ఖాళీ )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#లేకపోతే /* if defined( __MW__ ) */

#అయితే_ముగింపు /* __MW__ */
