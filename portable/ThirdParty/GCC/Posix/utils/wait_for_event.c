/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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

#अन्तर्भाव <pthread.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <errno.h>

#अन्तर्भाव "wait_for_event.h"

संरचना event
{
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexattr;
    pthread_cond_t cond;
    bool event_triggered;
};
/*-----------------------------------------------------------*/

संरचना event * event_create( शून्य )
{
    संरचना event * ev = स्मृतिं_देहि( परिमाण( संरचना event ) );

    यदि( ev != रिक्त )
    {
        ev->event_triggered = false;
        pthread_mutexattr_init( &ev->mutexattr );
        #यदि_अपरिभाषितम् __APPLE__
            pthread_mutexattr_setrobust( &ev->mutexattr, PTHREAD_MUTEX_ROBUST );
        #यदि_अन्तः
        pthread_mutex_init( &ev->mutex, &ev->mutexattr );
        pthread_cond_init( &ev->cond, रिक्त );
    }

    प्रत्यागम ev;
}
/*-----------------------------------------------------------*/

शून्य event_delete( संरचना event * ev )
{
    pthread_mutex_destroy( &ev->mutex );
    pthread_mutexattr_destroy( &ev->mutexattr );
    pthread_cond_destroy( &ev->cond );
    मुक्त( ev );
}
/*-----------------------------------------------------------*/

bool event_wait( संरचना event * ev )
{
    यदि( pthread_mutex_lock( &ev->mutex ) == EOWNERDEAD )
    {
        #यदि_अपरिभाषितम् __APPLE__
            /* If the thread owning the mutex died, make the mutex consistent. */
            pthread_mutex_consistent( &ev->mutex );
        #यदि_अन्तः
    }

    यावत्( ev->event_triggered == false )
    {
        pthread_cond_wait( &ev->cond, &ev->mutex );
    }

    ev->event_triggered = false;
    pthread_mutex_unlock( &ev->mutex );
    प्रत्यागम true;
}
/*-----------------------------------------------------------*/

bool event_wait_timed( संरचना event * ev,
                       time_t ms )
{
    संरचना timespec ts;
    पूर्णाङ्क ret = 0;

    clock_gettime( CLOCK_REALTIME, &ts );
    ts.tv_sec += ms / 1000;
    ts.tv_nsec += ( ( ms % 1000 ) * 1000000 );
    यदि( pthread_mutex_lock( &ev->mutex ) == EOWNERDEAD )
    {
        #यदि_अपरिभाषितम् __APPLE__
            /* If the thread owning the mutex died, make the mutex consistent. */
            pthread_mutex_consistent( &ev->mutex );
        #यदि_अन्तः
    }

    यावत्( ( ev->event_triggered == false ) && ( ret == 0 ) )
    {
        ret = pthread_cond_timedwait( &ev->cond, &ev->mutex, &ts );

        यदि( ( ret == -1 ) && ( errno == ETIMEDOUT ) )
        {
            प्रत्यागम false;
        }
    }

    ev->event_triggered = false;
    pthread_mutex_unlock( &ev->mutex );
    प्रत्यागम true;
}
/*-----------------------------------------------------------*/

शून्य event_signal( संरचना event * ev )
{
    यदि( pthread_mutex_lock( &ev->mutex ) == EOWNERDEAD )
    {
        #यदि_अपरिभाषितम् __APPLE__
            /* If the thread owning the mutex died, make the mutex consistent. */
            pthread_mutex_consistent( &ev->mutex );
        #यदि_अन्तः
    }
    ev->event_triggered = true;
    pthread_cond_signal( &ev->cond );
    pthread_mutex_unlock( &ev->mutex );
}
/*-----------------------------------------------------------*/
