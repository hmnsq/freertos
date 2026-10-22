/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2020 Cambridge Consultants Ltd.
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

/*-----------------------------------------------------------
* Implementation of functions defined in portable.h for the Posix port.
*
* Each task has a pthread which eases use of standard debuggers
* (allowing backtraces of tasks etc). Threads for tasks that are not
* running are blocked in sigwait().
*
* Task switch is done by resuming the thread for the next task by
* signaling the condition variable and then waiting on a condition variable
* with the current thread.
*
* The timer interrupt uses SIGALRM and care is taken to ensure that
* the signal handler runs only on the thread for the current task.
*
* Use of part of the standard C library requires care as some
* functions can take pthread mutexes internally which can result in
* deadlocks as the FreeRTOS kernel can switch tasks while they're
* holding a pthread mutex.
*
* stdio (printf() and friends) should be called from a single task
* only or serialized with a FreeRTOS primitive such as a binary
* semaphore or mutex.
*
* Note: When using LLDB (the default debugger on macOS) with this port,
* suppress SIGUSR1 to prevent debugger interference. This can be
* done by adding the following line to ~/.lldbinit:
* `process handle SIGUSR1 -n true -p false -s false`
*----------------------------------------------------------*/
#ifdef __linux__
    #define _GNU_SOURCE
#endif
#அந்தர்பாவ "portmacro.h"
#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <pthread.h>
#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <signal.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ <sys/time.h>
#அந்தர்பாவ <sys/times.h>
#அந்தர்பாவ <time.h>
#அந்தர்பாவ <unistd.h>

/* Scheduler includes. */
#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"
#அந்தர்பாவ "timers.h"
#அந்தர்பாவ "utils/wait_for_event.h"
/*-----------------------------------------------------------*/

#define SIG_RESUME    SIGUSR1

வகைவரை கட்டமைப்பு THREAD
{
    pthread_t pthread;
    TaskFunction_t pxCode;
    வெறுமை * pvParams;
    BaseType_t xDying;
    கட்டமைப்பு event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
நிலையான உள்வரி Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    அடுக்கு_Type_t * px_உச்சி_Of_அடுக்கு = *( அடுக்கு_Type_t ** ) xTask;

    திரும்பு ( Thread_t * ) ( px_உச்சி_Of_அடுக்கு + 1 );
}

/*-----------------------------------------------------------*/

நிலையான pthread_once_t hSigSetupThread = PTHREAD_ONCE_INIT;
நிலையான pthread_once_t h_Thread_சாவி_Once = PTHREAD_ONCE_INIT;
நிலையான sigset_t xAllSignals;
நிலையான sigset_t xSchedulerOriginalSignalMask;
நிலையான pthread_t hMainThread = ( pthread_t ) வெற்று;
நிலையான நிலையற்ற BaseType_t uxCriticalNesting;
நிலையான BaseType_t xSchedulerEnd = pdFALSE;
நிலையான pthread_t hTimerTickThread;
நிலையான bool xTimerTickThreadShouldRun;
நிலையான uint64_t prvStartTimeNs;
நிலையான pthread_key_t x_Thread_சாவி = 0;
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvSetupSignalsAndSchedulerPolicy( வெறுமை );
நிலையான வெறுமை prvSetupTimerInterrupt( வெறுமை );
நிலையான வெறுமை * prvWaitForStart( வெறுமை * pvParams );
நிலையான வெறுமை prvSwitchThread( Thread_t * xThreadToResume,
                             Thread_t * xThreadToSuspend );
நிலையான வெறுமை prvSuspendSelf( Thread_t * thread );
நிலையான வெறுமை prvResumeThread( Thread_t * xThreadId );
நிலையான வெறுமை vPortSystemTickHandler( முழு sig );
நிலையான வெறுமை vPortStartFirstTask( வெறுமை );
நிலையான வெறுமை prvPortYieldFromISR( வெறுமை );
நிலையான வெறுமை prv_Thread_சாவி_Destructor( வெறுமை * pvData );
நிலையான வெறுமை prv_Init_Thread_சாவி( வெறுமை );
நிலையான வெறுமை prvMarkAsFreeRTOSThread( வெறுமை );
நிலையான BaseType_t prvIsFreeRTOSThread( வெறுமை );
நிலையான வெறுமை prv_Destroy_Thread_சாவி( வெறுமை );
/*-----------------------------------------------------------*/

நிலையான வெறுமை prv_Thread_சாவி_Destructor( வெறுமை * pvData )
{
    விடுவி( pvData );
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prv_Init_Thread_சாவி( வெறுமை )
{
    pthread_key_create( &x_Thread_சாவி, prv_Thread_சாவி_Destructor );
    /* Destroy xThreadKey when the process exits. */
    atexit( prv_Destroy_Thread_சாவி );
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvMarkAsFreeRTOSThread( வெறுமை )
{
    uint8_t * pucThreadData = வெற்று;

    ( வெறுமை ) pthread_once( &h_Thread_சாவி_Once, prv_Init_Thread_சாவி );

    pucThreadData = malloc( 1 );
    configASSERT( pucThreadData != வெற்று );

    *pucThreadData = 1;

    pthread_setspecific( x_Thread_சாவி, pucThreadData );
}
/*-----------------------------------------------------------*/

நிலையான BaseType_t prvIsFreeRTOSThread( வெறுமை )
{
    uint8_t * pucThreadData = வெற்று;
    BaseType_t xRet = pdFALSE;

    ( வெறுமை ) pthread_once( &h_Thread_சாவி_Once, prv_Init_Thread_சாவி );

    pucThreadData = ( uint8_t * ) pthread_getspecific( x_Thread_சாவி );

    எனில்( ( pucThreadData != வெற்று ) && ( *pucThreadData == 1 ) )
    {
        xRet = pdTRUE;
    }

    திரும்பு xRet;
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prv_Destroy_Thread_சாவி( வெறுமை )
{
    pthread_key_delete( x_Thread_சாவி );
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvFatalError( மாறிலி எழுத்து * pcCall,
                           முழு iErrno ) __attribute__( ( __noreturn__ ) );

வெறுமை prvFatalError( மாறிலி எழுத்து * pcCall,
                    முழு iErrno )
{
    fprintf( stderr, "%s: %s\n", pcCall, strerror( iErrno ) );
    abort();
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvPortSetCurrentThreadName( மாறிலி எழுத்து * pxThreadName )
{
    #ifdef __APPLE__
        pthread_setname_np( pxThreadName );
    #இல்லையெனில்
        pthread_setname_np( pthread_self(), pxThreadName );
    #endif
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
அடுக்கு_Type_t * px_Port_Initialise_அடுக்கு( அடுக்கு_Type_t * px_உச்சி_Of_அடுக்கு,
                                     அடுக்கு_Type_t * px_End_Of_அடுக்கு,
                                     TaskFunction_t pxCode,
                                     வெறுமை * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t xThreadAttributes;
    size_t ul_அடுக்கு_Size;
    முழு iRet;

    ( வெறுமை ) pthread_once( &hSigSetupThread, prvSetupSignalsAndSchedulerPolicy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_உச்சி_Of_அடுக்கு + 1 ) - 1;
    px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_அடுக்கு_Size = ( size_t ) ( px_உச்சி_Of_அடுக்கு + 1 - px_End_Of_அடுக்கு ) * அளவு( *px_உச்சி_Of_அடுக்கு );
    configASSERT( ul_அடுக்கு_Size > அளவு( Thread_t ) );
    ( வெறுமை ) ul_அடுக்கு_Size; /* suppress set but not used warning */

    thread->pxCode = pxCode;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &xThreadAttributes );

    thread->ev = event_create();

    vPortEnterCritical();

    iRet = pthread_create( &thread->pthread, &xThreadAttributes,
                           prvWaitForStart, thread );

    எனில்( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    vPortExitCritical();

    திரும்பு px_உச்சி_Of_அடுக்கு;
}
/*-----------------------------------------------------------*/

வெறுமை vPortStartFirstTask( வெறுமை )
{
    Thread_t * pxFirstThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( pxFirstThread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( வெறுமை )
{
    முழு iSignal;
    sigset_t xSignals;

    hMainThread = pthread_self();
    prvPortSetCurrentThreadName( "Scheduler" );

    /* Start the timer that generates the tick ISR(SIGALRM).
     * Interrupts are disabled here already. */
    prvSetupTimerInterrupt();

    /*
     * Block SIG_RESUME before starting any tasks so the main thread can sigwait on it.
     * To sigwait on an unblocked signal is undefined.
     * https://pubs.opengroup.org/onlinepubs/009604499/functions/sigwait.html
     */
    sigemptyset( &xSignals );
    sigaddset( &xSignals, SIG_RESUME );
    ( வெறுமை ) pthread_sigmask( SIG_BLOCK, &xSignals, வெற்று );

    /* Start the first task. */
    vPortStartFirstTask();

    /* Wait until signaled by vPortEndScheduler(). */
    போது( xSchedulerEnd != pdTRUE )
    {
        sigwait( &xSignals, &iSignal );
    }

    /*
     * clear out the variable that is used to end the scheduler, otherwise
     * subsequent scheduler restarts will end immediately.
     */
    xSchedulerEnd = pdFALSE;

    /* Reset pthread_once_t, needed to restart the scheduler again.
     * memset the internal struct members for MacOS/Linux Compatibility */
    #எனில் __APPLE__
        hSigSetupThread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_சாவி_Once.__sig = _PTHREAD_ONCE_SIG_init;
        memset( ( வெறுமை * ) &hSigSetupThread.__opaque, 0, அளவு( hSigSetupThread.__opaque ) );
        memset( ( வெறுமை * ) &h_Thread_சாவி_Once.__opaque, 0, அளவு( h_Thread_சாவி_Once.__opaque ) );
    #இல்லையெனில் /* Linux PTHREAD library*/
        hSigSetupThread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_சாவி_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #endif /* __APPLE__*/

    /* Restore original signal mask. */
    ( வெறுமை ) pthread_sigmask( SIG_SETMASK, &xSchedulerOriginalSignalMask, வெற்று );

    திரும்பு 0;
}
/*-----------------------------------------------------------*/

வெறுமை vPortEndScheduler( வெறுமை )
{
    Thread_t * pxCurrentThread;
    BaseType_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    xTimerTickThreadShouldRun = false;
    pthread_join( hTimerTickThread, வெற்று );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    xSchedulerEnd = pdTRUE;
    ( வெறுமை ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    எனில்( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

வெறுமை vPortEnterCritical( வெறுமை )
{
    எனில்( uxCriticalNesting == 0 )
    {
        vPortDisableInterrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

வெறுமை vPortExitCritical( வெறுமை )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    எனில்( uxCriticalNesting == 0 )
    {
        vPortEnableInterrupts();
    }
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvPortYieldFromISR( வெறுமை )
{
    Thread_t * xThreadToSuspend;
    Thread_t * xThreadToResume;

    xThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    xThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( xThreadToResume, xThreadToSuspend );
}
/*-----------------------------------------------------------*/

வெறுமை vPortYield( வெறுமை )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    vPortEnterCritical();

    prvPortYieldFromISR();

    vPortExitCritical();
}
/*-----------------------------------------------------------*/

வெறுமை vPortDisableInterrupts( வெறுமை )
{
    எனில்( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &xAllSignals, வெற்று );
    }
}
/*-----------------------------------------------------------*/

வெறுமை vPortEnableInterrupts( வெறுமை )
{
    எனில்( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &xAllSignals, வெற்று );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t xPortSetInterruptMask( வெறுமை )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    திரும்பு ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

வெறுமை vPortClearInterruptMask( UBaseType_t uxMask )
{
    ( வெறுமை ) uxMask;
}
/*-----------------------------------------------------------*/

நிலையான uint64_t prvGetTimeNs( வெறுமை )
{
    கட்டமைப்பு timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    திரும்பு ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

நிலையான வெறுமை * prvTimerTickHandler( வெறுமை * arg )
{
    ( வெறுமை ) arg;

    prvMarkAsFreeRTOSThread();

    prvPortSetCurrentThreadName( "Scheduler timer" );

    போது( xTimerTickThreadShouldRun )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( portTICK_RATE_MICROSECONDS );
    }

    திரும்பு வெற்று;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
வெறுமை prvSetupTimerInterrupt( வெறுமை )
{
    xTimerTickThreadShouldRun = true;
    pthread_create( &hTimerTickThread, வெற்று, prvTimerTickHandler, வெற்று );

    prvStartTimeNs = prvGetTimeNs();
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை vPortSystemTickHandler( முழு sig )
{
    எனில்( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * pxThreadToSuspend;
        Thread_t * pxThreadToResume;

        ( வெறுமை ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        pxThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        எனில்( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            pxThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( pxThreadToResume, pxThreadToSuspend );
        }

        uxCriticalNesting--;
    }
    இல்லையெனில்
    {
        fprintf( stderr, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

வெறுமை vPortThreadDying( வெறுமை * pxTaskToDelete,
                       நிலையற்ற BaseType_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( pxTaskToDelete );

    ( வெறுமை ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

வெறுமை vPortCancelThread( வெறுமை * pxTaskToDelete )
{
    Thread_t * pxThreadToCancel = prvGetThreadFromTask( pxTaskToDelete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( pxThreadToCancel->pthread );
    event_signal( pxThreadToCancel->ev );
    pthread_join( pxThreadToCancel->pthread, வெற்று );
    event_delete( pxThreadToCancel->ev );
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை * prvWaitForStart( வெறுமை * pvParams )
{
    Thread_t * pxThread = pvParams;

    prvMarkAsFreeRTOSThread();

    prvSuspendSelf( pxThread );

    /* Resumed for the first time, unblocks all signals. */
    uxCriticalNesting = 0;
    vPortEnableInterrupts();

    /* Set thread name */
    prvPortSetCurrentThreadName( pcTaskGetName( xTaskGetCurrentTaskHandle() ) );

    /* Call the task's entry point. */
    pxThread->pxCode( pxThread->pvParams );

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, so application writers can
     * catch the error. */
    configASSERT( pdFALSE );

    திரும்பு வெற்று;
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvSwitchThread( Thread_t * pxThreadToResume,
                             Thread_t * pxThreadToSuspend )
{
    BaseType_t uxSavedCriticalNesting;

    எனில்( pxThreadToSuspend != pxThreadToResume )
    {
        /*
         * Switch tasks.
         *
         * The critical section nesting is per-task, so save it on the
         * stack of the current (suspending thread), restoring it when
         * we switch back to this task.
         */
        uxSavedCriticalNesting = uxCriticalNesting;

        prvResumeThread( pxThreadToResume );

        எனில்( pxThreadToSuspend->xDying == pdTRUE )
        {
            pthread_exit( வெற்று );
        }

        prvSuspendSelf( pxThreadToSuspend );

        uxCriticalNesting = uxSavedCriticalNesting;
    }
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvSuspendSelf( Thread_t * thread )
{
    /*
     * Suspend this thread by waiting for a pthread_cond_signal event.
     *
     * A suspended thread must not handle signals (interrupts) so
     * all signals must be blocked by calling this from:
     *
     * - Inside a critical section (vPortEnterCritical() /
     *   vPortExitCritical()).
     *
     * - From a signal handler that has all signals masked.
     *
     * - A thread with all signals blocked with pthread_sigmask().
     */
    event_wait( thread->ev );
    pthread_testcancel();
}

/*-----------------------------------------------------------*/

நிலையான வெறுமை prvResumeThread( Thread_t * xThreadId )
{
    எனில்( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

நிலையான வெறுமை prvSetupSignalsAndSchedulerPolicy( வெறுமை )
{
    கட்டமைப்பு sigaction sigtick;
    முழு iRet;

    hMainThread = pthread_self();

    /* Initialise common signal masks. */
    sigfillset( &xAllSignals );

    /* Don't block SIGINT so this can be used to break into GDB while
     * in a critical section. */
    sigdelset( &xAllSignals, SIGINT );

    /*
     * Block all signals in this thread so all new threads
     * inherits this mask.
     *
     * When a thread is resumed for the first time, all signals
     * will be unblocked.
     */
    ( வெறுமை ) pthread_sigmask( SIG_SETMASK,
                              &xAllSignals,
                              &xSchedulerOriginalSignalMask );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = vPortSystemTickHandler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, வெற்று );

    எனில்( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ulPortGetRunTime( வெறுமை )
{
    கட்டமைப்பு tms xTimes;

    times( &xTimes );

    திரும்பு ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
