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

#यदि defined( __MW__ )

    #अन्तर्भाव <stdint.h>
    #अन्तर्भाव <stdlib.h>
    #अन्तर्भाव <string.h>

    #अन्तर्भाव "FreeRTOS.h"

    #अन्तर्भाव "queue.h"
    #अन्तर्भाव "semphr.h"
    #अन्तर्भाव "task.h"

    #अन्तर्भाव "arc/arc_exception.h"
    #अन्तर्भाव "embARC_toolchain.h"
    #अन्तर्भाव "embARC_debug.h"

    #यदि_परिभाषितम् ENABLE_FREERTOS_TLS_DEBUG
        #परिभाषय TLS_DEBUG( fmt, ... )    EMBARC_PRINTF( fmt, ## __VA_ARGS__ )
    #अन्यथा
        #परिभाषय TLS_DEBUG( fmt, ... )
    #यदि_अन्तः

/*
 * Runtime routines to execute constructors and
 * destructors for task local storage.
 */
    बाह्य शून्य __mw_run_tls_dtor();
    बाह्य शून्य __mw_run_tls_ctor();

    बाह्य uint32_t exc_nest_गणनम्;

/*
 * Linker generated symbols to mark .tls section addresses
 * first byte .. last byte
 */
    बाह्य वर्ण _ftls[], _etls[];
    #निर्देशः weak _ftls
    #निर्देशः weak _etls

    शून्य executable_requires_tls_section( शून्य )
    {
        #यदि _ARC
            प्रति( ; ; )
            {
                _flag( 1 );
                _nop();
                _nop();
                _nop();
                _nop();
                _nop();
            }
        #यदि_अन्तः
    }
    #निर्देशः off_inline(executable_requires_tls_section);
    #निर्देशः alias(executable_requires_tls_section, "executable_requires_.tls_section");

    स्थिर शून्य * init_task_tls( शून्य )
    {
        uint32_t len = ( uint32_t ) ( _etls - _ftls );
        शून्य * tls = रिक्त;

        #यदि FREERTOS_HEAP_SEL == 3
        #warning "FreeRTOS TLS support is not compatible with heap 3 solution(FREERTOS_HEAP_SEL=3)!"
        #warning "You can change FREERTOS_HEAP_SEL in freertos.mk to select other heap solution."
        #अन्यथा
            tls = pv_पत्तनम्_Malloc( len );
        #यदि_अन्तः

        यदि( tls )
        {
            TLS_DEBUG( "Malloc task tls:%dbytes\r\n", len );
            स्मृतिं_प्रतिलिख( tls, _ftls, len );
            __mw_run_tls_ctor(); /* Run constructors */
        }

        प्रत्यागम tls;
    }

    स्थिर शून्य free_task_tls( शून्य * pxTCB )
    {
        TaskHandle_t task2free = ( TaskHandle_t ) pxTCB;

        यदि( task2free != रिक्त )
        {
            शून्य * tls = pvTaskGetThreadLocalStoragePointer( task2free, 0 );

            यदि( tls )
            {
                TLS_DEBUG( "Free task tls\r\n" );
                __mw_run_tls_dtor();
                v_पत्तनम्_Free( tls );
                v_Task_समुच्चयः_Thread_Local_Storage_Pointer( task2free, 0, रिक्त );
            }
        }
    }

    शून्य task_अन्तः_hook( शून्य * pxTCB )
    {
        free_task_tls( pxTCB );
    }

    स्थिर शून्य * get_isr_tls( शून्य )
    {
        /* In an ISR */
        स्थिर पूर्णाङ्क first = 1;

        यदि( _Rarely( first ) )
        {
            first = 0;
            __mw_run_tls_ctor(); /* Run constructors */
        }

        प्रत्यागम ( शून्य * ) _ftls;
    }
    #निर्देशः off_inline(get_isr_tls)

    स्थिर शून्य * get_task_tls( शून्य )
    {
        TaskHandle_t cur_task;

        cur_task = xTaskGetCurrentTaskHandle();

        यदि( cur_task == रिक्त )
        {
            प्रत्यागम get_isr_tls();
        }

        शून्य * tls = pvTaskGetThreadLocalStoragePointer( cur_task, 0 );

        यदि( tls == रिक्त )
        {
            tls = init_task_tls();

            यदि( tls )
            {
                v_Task_समुच्चयः_Thread_Local_Storage_Pointer( cur_task, 0, tls );
            }
            अन्यथा
            {
                tls = get_isr_tls();
            }
        }

        प्रत्यागम tls;
    }
    #निर्देशः off_inline(get_task_tls)

    #यदि _ARC /* for ARC XCALLs need to preserve flags */
        बाह्य शून्य * _Preserve_flags _mwget_tls( शून्य );
    #यदि_अन्तः

/*
 * Back end gens calls to find local data for this task
 */
    शून्य * _mwget_tls( शून्य )
    {
        यदि( _ftls == ( वर्ण * ) 0 )
        {
            executable_requires_tls_section();
        }

        यदि( exc_nest_गणनम् > 0 ) /* In ISR */
        {
            प्रत्यागम get_isr_tls();
        }
        अन्यथा /* In Task */
        {
            प्रत्यागम get_task_tls();
        }
    }


/* simple interface of thread safe */
    प्रकारनिर्देश xSemaphoreHandle तालकम्_t;
    #यदि configUSE_RECURSIVE_MUTEXES != 1
        #दोषः "configUSE_RECURSIVE_MUTEXES in FreeRTOSConfig.h need to 1"
    #यदि_अन्तः

    शून्य _mwmutex_create( तालकम्_t * mutex_ptr )
    {
        *mutex_ptr = xSemaphoreCreateRecursiveMutex();
    }

    शून्य _mwmutex_delete( तालकम्_t * mutex_ptr )
    {
        यदि( ( *mutex_ptr ) != रिक्त )
        {
            vSemaphoreDelete( *mutex_ptr );
        }
    }

    शून्य mwmutex_तालकम्( तालकम्_t mutex )
    {
        यदि( ( mutex ) != रिक्त )
        {
            यावत्( xSemaphoreTakeRecursive( mutex, पत्तनम्_MAX_DELAY ) != pdTRUE )
            {
            }
        }
    }

    शून्य _mwmutex_unlock( तालकम्_t mutex )
    {
        यदि( ( mutex ) != रिक्त )
        {
            xSemaphoreGiveRecursive( mutex );
        }
    }

#अन्यथा /* if defined( __MW__ ) */

#यदि_अन्तः /* __MW__ */
