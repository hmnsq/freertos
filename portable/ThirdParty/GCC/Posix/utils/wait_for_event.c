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

#ਅਨ੍ਤਰ੍ਭਾਵ <pthread.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "wait_for_event.h"

ਬਣਤਰ event
{
    pthread_mutex_t mutex;
    pthread_mutexattr_t mutexattr;
    pthread_cond_t cond;
    bool event_triggered;
};
/*-----------------------------------------------------------*/

ਬਣਤਰ event * event_create( ਖਾਲੀ )
{
    ਬਣਤਰ event * ev = ਸਮ੍ਰਿਤੀ_ਦਿਓ( ਆਕਾਰ( ਬਣਤਰ event ) );

    ਜੇ( ev != ਨਿਰਾ )
    {
        ev->event_triggered = false;
        pthread_mutexattr_init( &ev->mutexattr );
        #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __APPLE__
            pthread_mutexattr_setrobust( &ev->mutexattr, PTHREAD_MUTEX_ROBUST );
        #ਜੇ_ਅੰਤ
        pthread_mutex_init( &ev->mutex, &ev->mutexattr );
        pthread_cond_init( &ev->cond, ਨਿਰਾ );
    }

    ਵਾਪਸ ev;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ event_delete( ਬਣਤਰ event * ev )
{
    pthread_mutex_destroy( &ev->mutex );
    pthread_mutexattr_destroy( &ev->mutexattr );
    pthread_cond_destroy( &ev->cond );
    ਮੁਕਤ( ev );
}
/*-----------------------------------------------------------*/

bool event_wait( ਬਣਤਰ event * ev )
{
    ਜੇ( pthread_mutex_lock( &ev->mutex ) == EOWNERDEAD )
    {
        #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __APPLE__
            /* If the thread owning the mutex died, make the mutex consistent. */
            pthread_mutex_consistent( &ev->mutex );
        #ਜੇ_ਅੰਤ
    }

    ਜਦੋਂ( ev->event_triggered == false )
    {
        pthread_cond_wait( &ev->cond, &ev->mutex );
    }

    ev->event_triggered = false;
    pthread_mutex_unlock( &ev->mutex );
    ਵਾਪਸ true;
}
/*-----------------------------------------------------------*/

bool event_wait_timed( ਬਣਤਰ event * ev,
                       time_t ms )
{
    ਬਣਤਰ timespec ts;
    ਪੂਰਨ ret = 0;

    clock_gettime( CLOCK_REALTIME, &ts );
    ts.tv_sec += ms / 1000;
    ts.tv_nsec += ( ( ms % 1000 ) * 1000000 );
    ਜੇ( pthread_mutex_lock( &ev->mutex ) == EOWNERDEAD )
    {
        #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __APPLE__
            /* If the thread owning the mutex died, make the mutex consistent. */
            pthread_mutex_consistent( &ev->mutex );
        #ਜੇ_ਅੰਤ
    }

    ਜਦੋਂ( ( ev->event_triggered == false ) && ( ret == 0 ) )
    {
        ret = pthread_cond_timedwait( &ev->cond, &ev->mutex, &ts );

        ਜੇ( ( ret == -1 ) && ( errno == ETIMEDOUT ) )
        {
            ਵਾਪਸ false;
        }
    }

    ev->event_triggered = false;
    pthread_mutex_unlock( &ev->mutex );
    ਵਾਪਸ true;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ event_signal( ਬਣਤਰ event * ev )
{
    ਜੇ( pthread_mutex_lock( &ev->mutex ) == EOWNERDEAD )
    {
        #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __APPLE__
            /* If the thread owning the mutex died, make the mutex consistent. */
            pthread_mutex_consistent( &ev->mutex );
        #ਜੇ_ਅੰਤ
    }
    ev->event_triggered = true;
    pthread_cond_signal( &ev->cond );
    pthread_mutex_unlock( &ev->mutex );
}
/*-----------------------------------------------------------*/
