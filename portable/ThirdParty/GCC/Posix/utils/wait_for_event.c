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

#ضمن <pthread.h>
#ضمن <stdlib.h>
#ضمن <errno.h>

#ضمن "wait_for_event.h"

بنية event
{
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexattr;
    pthread_cond_t cond;
    bool event_triggered;
};
/*-----------------------------------------------------------*/

بنية event * event_create( فراغ )
{
    بنية event * ev = حافظه_ورکړه( حجم( بنية event ) );

    إذا( ev != عدم )
    {
        ev->event_triggered = false;
        pthread_mutexattr_init( &ev->mutexattr );
        #که_نه_تعریف_شوی __APPLE__
            pthread_mutexattr_setrobust( &ev->mutexattr, PTHREAD_MUTEX_ROBUST );
        #د_که_پای
        pthread_mutex_init( &ev->mutex, &ev->mutexattr );
        pthread_cond_init( &ev->cond, عدم );
    }

    أرجع ev;
}
/*-----------------------------------------------------------*/

فراغ event_delete( بنية event * ev )
{
    pthread_mutex_destroy( &ev->mutex );
    pthread_mutexattr_destroy( &ev->mutexattr );
    pthread_cond_destroy( &ev->cond );
    حرر( ev );
}
/*-----------------------------------------------------------*/

bool event_wait( بنية event * ev )
{
    إذا( pthread_mutex_lock( &ev->mutex ) == EOWNERDEAD )
    {
        #که_نه_تعریف_شوی __APPLE__
            /* If the thread owning the mutex died, make the mutex consistent. */
            pthread_mutex_consistent( &ev->mutex );
        #د_که_پای
    }

    طالما( ev->event_triggered == false )
    {
        pthread_cond_wait( &ev->cond, &ev->mutex );
    }

    ev->event_triggered = false;
    pthread_mutex_unlock( &ev->mutex );
    أرجع true;
}
/*-----------------------------------------------------------*/

bool event_wait_timed( بنية event * ev,
                       time_t ms )
{
    بنية timespec ts;
    صحيح ret = 0;

    clock_gettime( CLOCK_REALTIME, &ts );
    ts.tv_sec += ms / 1000;
    ts.tv_nsec += ( ( ms % 1000 ) * 1000000 );
    إذا( pthread_mutex_lock( &ev->mutex ) == EOWNERDEAD )
    {
        #که_نه_تعریف_شوی __APPLE__
            /* If the thread owning the mutex died, make the mutex consistent. */
            pthread_mutex_consistent( &ev->mutex );
        #د_که_پای
    }

    طالما( ( ev->event_triggered == false ) && ( ret == 0 ) )
    {
        ret = pthread_cond_timedwait( &ev->cond, &ev->mutex, &ts );

        إذا( ( ret == -1 ) && ( errno == ETIMEDOUT ) )
        {
            أرجع false;
        }
    }

    ev->event_triggered = false;
    pthread_mutex_unlock( &ev->mutex );
    أرجع true;
}
/*-----------------------------------------------------------*/

فراغ event_signal( بنية event * ev )
{
    إذا( pthread_mutex_lock( &ev->mutex ) == EOWNERDEAD )
    {
        #که_نه_تعریف_شوی __APPLE__
            /* If the thread owning the mutex died, make the mutex consistent. */
            pthread_mutex_consistent( &ev->mutex );
        #د_که_پای
    }
    ev->event_triggered = true;
    pthread_cond_signal( &ev->cond );
    pthread_mutex_unlock( &ev->mutex );
}
/*-----------------------------------------------------------*/
