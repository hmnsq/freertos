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

    #اگر_تعریف_شدہ ENABLE_FREERTOS_TLS_DEBUG
        #تعریف_کرو TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #ورنہ
        #تعریف_کرو TLS_DEBUG( fmt, ... )
    #اگر_ختم

/*
 * Runtime routines to execute constructors and
 * destructors for task local storage.
 */
    خارجی خالی __mw_run_tls_dtor();
    خارجی خالی __mw_run_tls_ctor();

    خارجی uint32_t exc_nest_گنتی;

/*
 * Linker generated symbols to mark .tls section addresses
 * first byte .. last byte
 */
    خارجی حرف _ftls[], _etls[];
    #ہدایت weak _ftls
    #ہدایت weak _etls

    خالی executable_requires_tls_section( خالی )
    {
        #اگر _ARC
            برائے( ; ; )
            {
                _flag( 1 );
                _nop();
                _nop();
                _nop();
                _nop();
                _nop();
            }
        #اگر_ختم
    }
    #ہدایت off_inline(executable_requires_tls_section);
    #ہدایت alias(executable_requires_tls_section, "executable_requires_.tls_section");

    ساکن خالی * init_task_tls( خالی )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        خالی * tls = تہی;

        #اگر FREERTOS_ڈھیر_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #ورنہ
            tls = pv_پورٹ_Malloc( len );
        #اگر_ختم

        اگر( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            حافظہ_نقل( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        واپس tls;
    }

    ساکن خالی free_task_tls( خالی * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        اگر( task2free != تہی )
        {
            خالی * tls = pv_Task_Get_Thread_Local_Storage_اشارہ_گر( task2free, 0 );

            اگر( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                v_پورٹ_Free( tls );
                v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( task2free, 0, تہی );
            }
        }
    }

    خالی task_انتہا_hook( خالی * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    ساکن خالی * get_isr_tls( خالی )
    {
        /* In an ISR */
        ساکن صحیح پہلا_2 = 1;

        اگر( _Rarely( پہلا_2 ) )
        {
            پہلا_2 = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        واپس ( خالی * ) _ftls;
    }
    #ہدایت off_inline(get_isr_tls)

    ساکن خالی * get_task_tls( خالی )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        اگر( cur_task == تہی )
        {
            واپس get_isr_tls();
        }

        خالی * tls = pv_Task_Get_Thread_Local_Storage_اشارہ_گر( cur_task, 0 );

        اگر( tls == تہی )
        {
            tls = init_task_tls();

            اگر( tls )
            {
                v_Task_سیٹ_Thread_Local_Storage_اشارہ_گر( cur_task, 0, tls );
            }
            ورنہ
            {
                tls = get_isr_tls();
            }
        }

        واپس tls;
    }
    #ہدایت off_inline(get_task_tls)

    #اگر _ARC /* for ARC XCALLs need to preserve flags */
        خارجی خالی * _Preserve_flags _mwget_tls( خالی );
    #اگر_ختم

/*
 * Back end gens calls to find local data for this task
 */
    خالی * _mwget_tls( خالی )
    {
        اگر( _ftls == ( حرف * ) 0 )
        {
            executable_requires_tls_section();
        }

        اگر( exc_nest_گنتی > 0 ) /* In ISR */
        {
            واپس get_isr_tls();
        }
        ورنہ /* In Task */
        {
            واپس get_task_tls();
        }
    }


/* simple interface of thread safe */
    قسمتعریف xSemaphoreHandle تالا_t;
    #اگر configUSE_RECURSIVE_MUTEXES != 1
        #غلطی "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #اگر_ختم

    خالی _mwmutex_create( تالا_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    خالی _mwmutex_delete( تالا_t * mutex_ptr )
    {
        اگر( ( *mutex_ptr ) != تہی )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    خالی mwmutex_تالا( تالا_t mutex )
    {
        اگر( ( mutex ) != تہی )
        {
            جب( xSemaphoreTakeRecursive( mutex, پورٹ_MAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    خالی _mwmutex_unlock( تالا_t mutex )
    {
        اگر( ( mutex ) != تہی )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#ورنہ /* if defined( __MW__ ) */

#اگر_ختم /* __MW__ */
