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
#অন্তর্ভাৱ "portmacro.h"
#অন্তর্ভাৱ <errno.h>
#অন্তর্ভাৱ <pthread.h>
#অন্তর্ভাৱ <limits.h>
#অন্তর্ভাৱ <signal.h>
#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ <sys/time.h>
#অন্তর্ভাৱ <sys/times.h>
#অন্তর্ভাৱ <time.h>
#অন্তর্ভাৱ <unistd.h>

/* Scheduler includes. */
#অন্তর্ভাৱ "FreeRTOS.h"
#অন্তর্ভাৱ "task.h"
#অন্তর্ভাৱ "timers.h"
#অন্তর্ভাৱ "utils/wait_for_event.h"
/*-----------------------------------------------------------*/

#define SIG_RESUME    SIGUSR1

প্রকারনির্দেশ সংরচনা THREAD
{
    pthread_t pthread;
    TaskFunction_t pxCode;
    শূন্য * pvParams;
    BaseType_t xDying;
    সংরচনা event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
স্থির অন্তঃস্থ Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    স্তূপ_Type_t * px_শীৰ্ষ_Of_স্তূপ = *( স্তূপ_Type_t ** ) xTask;

    ঘূৰাই ( Thread_t * ) ( px_শীৰ্ষ_Of_স্তূপ + 1 );
}

/*-----------------------------------------------------------*/

স্থির pthread_once_t hSigSetupThread = PTHREAD_ONCE_INIT;
স্থির pthread_once_t h_Thread_চাবি_Once = PTHREAD_ONCE_INIT;
স্থির sigset_t xAllSignals;
স্থির sigset_t xSchedulerOriginalSignalMask;
স্থির pthread_t hMainThread = ( pthread_t ) রিক্ত;
স্থির চঞ্চল BaseType_t uxCriticalNesting;
স্থির BaseType_t xSchedulerEnd = pdFALSE;
স্থির pthread_t hTimerTickThread;
স্থির bool xTimerTickThreadShouldRun;
স্থির uint64_t prvStartTimeNs;
স্থির pthread_key_t x_Thread_চাবি = 0;
/*-----------------------------------------------------------*/

স্থির শূন্য prvSetupSignalsAndSchedulerPolicy( শূন্য );
স্থির শূন্য prvSetupTimerInterrupt( শূন্য );
স্থির শূন্য * prvWaitForStart( শূন্য * pvParams );
স্থির শূন্য prvSwitchThread( Thread_t * xThreadToResume,
                             Thread_t * xThreadToSuspend );
স্থির শূন্য prvSuspendSelf( Thread_t * thread );
স্থির শূন্য prvResumeThread( Thread_t * xThreadId );
স্থির শূন্য vPortSystemTickHandler( পূর্ণাঙ্ক sig );
স্থির শূন্য vPortStartFirstTask( শূন্য );
স্থির শূন্য prvPortYieldFromISR( শূন্য );
স্থির শূন্য prv_Thread_চাবি_Destructor( শূন্য * pvData );
স্থির শূন্য prv_Init_Thread_চাবি( শূন্য );
স্থির শূন্য prvMarkAsFreeRTOSThread( শূন্য );
স্থির BaseType_t prvIsFreeRTOSThread( শূন্য );
স্থির শূন্য prv_Destroy_Thread_চাবি( শূন্য );
/*-----------------------------------------------------------*/

স্থির শূন্য prv_Thread_চাবি_Destructor( শূন্য * pvData )
{
    মুক্ত( pvData );
}
/*-----------------------------------------------------------*/

স্থির শূন্য prv_Init_Thread_চাবি( শূন্য )
{
    pthread_key_create( &x_Thread_চাবি, prv_Thread_চাবি_Destructor );
    /* Destroy xThreadKey when the process exits. */
    atexit( prv_Destroy_Thread_চাবি );
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvMarkAsFreeRTOSThread( শূন্য )
{
    uint8_t * pucThreadData = রিক্ত;

    ( শূন্য ) pthread_once( &h_Thread_চাবি_Once, prv_Init_Thread_চাবি );

    pucThreadData = malloc( 1 );
    configASSERT( pucThreadData != রিক্ত );

    *pucThreadData = 1;

    pthread_setspecific( x_Thread_চাবি, pucThreadData );
}
/*-----------------------------------------------------------*/

স্থির BaseType_t prvIsFreeRTOSThread( শূন্য )
{
    uint8_t * pucThreadData = রিক্ত;
    BaseType_t xRet = pdFALSE;

    ( শূন্য ) pthread_once( &h_Thread_চাবি_Once, prv_Init_Thread_চাবি );

    pucThreadData = ( uint8_t * ) pthread_getspecific( x_Thread_চাবি );

    যদি( ( pucThreadData != রিক্ত ) && ( *pucThreadData == 1 ) )
    {
        xRet = pdTRUE;
    }

    ঘূৰাই xRet;
}
/*-----------------------------------------------------------*/

স্থির শূন্য prv_Destroy_Thread_চাবি( শূন্য )
{
    pthread_key_delete( x_Thread_চাবি );
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvFatalError( ধ্রুৱ ৱর্ণ * pcCall,
                           পূর্ণাঙ্ক iErrno ) __attribute__( ( __noreturn__ ) );

শূন্য prvFatalError( ধ্রুৱ ৱর্ণ * pcCall,
                    পূর্ণাঙ্ক iErrno )
{
    fprintf( stderr, "%s: %s\n", pcCall, strerror( iErrno ) );
    abort();
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvPortSetCurrentThreadName( ধ্রুৱ ৱর্ণ * pxThreadName )
{
    #ifdef __APPLE__
        pthread_setname_np( pxThreadName );
    #অন্যথা
        pthread_setname_np( pthread_self(), pxThreadName );
    #endif
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীৰ্ষ_Of_স্তূপ,
                                     স্তূপ_Type_t * px_End_Of_স্তূপ,
                                     TaskFunction_t pxCode,
                                     শূন্য * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t xThreadAttributes;
    size_t ul_স্তূপ_Size;
    পূর্ণাঙ্ক iRet;

    ( শূন্য ) pthread_once( &hSigSetupThread, prvSetupSignalsAndSchedulerPolicy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_শীৰ্ষ_Of_স্তূপ + 1 ) - 1;
    px_শীৰ্ষ_Of_স্তূপ = ( স্তূপ_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_স্তূপ_Size = ( size_t ) ( px_শীৰ্ষ_Of_স্তূপ + 1 - px_End_Of_স্তূপ ) * পরিমাণ( *px_শীৰ্ষ_Of_স্তূপ );
    configASSERT( ul_স্তূপ_Size > পরিমাণ( Thread_t ) );
    ( শূন্য ) ul_স্তূপ_Size; /* suppress set but not used warning */

    thread->pxCode = pxCode;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &xThreadAttributes );

    thread->ev = event_create();

    vPortEnterCritical();

    iRet = pthread_create( &thread->pthread, &xThreadAttributes,
                           prvWaitForStart, thread );

    যদি( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    vPortExitCritical();

    ঘূৰাই px_শীৰ্ষ_Of_স্তূপ;
}
/*-----------------------------------------------------------*/

শূন্য vPortStartFirstTask( শূন্য )
{
    Thread_t * pxFirstThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( pxFirstThread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( শূন্য )
{
    পূর্ণাঙ্ক iSignal;
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
    ( শূন্য ) pthread_sigmask( SIG_BLOCK, &xSignals, রিক্ত );

    /* Start the first task. */
    vPortStartFirstTask();

    /* Wait until signaled by vPortEndScheduler(). */
    যেতিয়ালৈ( xSchedulerEnd != pdTRUE )
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
    #যদি __APPLE__
        hSigSetupThread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_চাবি_Once.__sig = _PTHREAD_ONCE_SIG_init;
        memset( ( শূন্য * ) &hSigSetupThread.__opaque, 0, পরিমাণ( hSigSetupThread.__opaque ) );
        memset( ( শূন্য * ) &h_Thread_চাবি_Once.__opaque, 0, পরিমাণ( h_Thread_চাবি_Once.__opaque ) );
    #অন্যথা /* Linux PTHREAD library*/
        hSigSetupThread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_চাবি_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #endif /* __APPLE__*/

    /* Restore original signal mask. */
    ( শূন্য ) pthread_sigmask( SIG_SETMASK, &xSchedulerOriginalSignalMask, রিক্ত );

    ঘূৰাই 0;
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    Thread_t * pxCurrentThread;
    BaseType_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    xTimerTickThreadShouldRun = false;
    pthread_join( hTimerTickThread, রিক্ত );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    xSchedulerEnd = pdTRUE;
    ( শূন্য ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    যদি( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

শূন্য vPortEnterCritical( শূন্য )
{
    যদি( uxCriticalNesting == 0 )
    {
        vPortDisableInterrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

শূন্য vPortExitCritical( শূন্য )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    যদি( uxCriticalNesting == 0 )
    {
        vPortEnableInterrupts();
    }
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvPortYieldFromISR( শূন্য )
{
    Thread_t * xThreadToSuspend;
    Thread_t * xThreadToResume;

    xThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    xThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( xThreadToResume, xThreadToSuspend );
}
/*-----------------------------------------------------------*/

শূন্য vPortYield( শূন্য )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    vPortEnterCritical();

    prvPortYieldFromISR();

    vPortExitCritical();
}
/*-----------------------------------------------------------*/

শূন্য vPortDisableInterrupts( শূন্য )
{
    যদি( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &xAllSignals, রিক্ত );
    }
}
/*-----------------------------------------------------------*/

শূন্য vPortEnableInterrupts( শূন্য )
{
    যদি( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &xAllSignals, রিক্ত );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t xPortSetInterruptMask( শূন্য )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    ঘূৰাই ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

শূন্য vPortClearInterruptMask( UBaseType_t uxMask )
{
    ( শূন্য ) uxMask;
}
/*-----------------------------------------------------------*/

স্থির uint64_t prvGetTimeNs( শূন্য )
{
    সংরচনা timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    ঘূৰাই ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

স্থির শূন্য * prvTimerTickHandler( শূন্য * arg )
{
    ( শূন্য ) arg;

    prvMarkAsFreeRTOSThread();

    prvPortSetCurrentThreadName( "Scheduler timer" );

    যেতিয়ালৈ( xTimerTickThreadShouldRun )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( portTICK_RATE_MICROSECONDS );
    }

    ঘূৰাই রিক্ত;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
শূন্য prvSetupTimerInterrupt( শূন্য )
{
    xTimerTickThreadShouldRun = true;
    pthread_create( &hTimerTickThread, রিক্ত, prvTimerTickHandler, রিক্ত );

    prvStartTimeNs = prvGetTimeNs();
}
/*-----------------------------------------------------------*/

স্থির শূন্য vPortSystemTickHandler( পূর্ণাঙ্ক sig )
{
    যদি( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * pxThreadToSuspend;
        Thread_t * pxThreadToResume;

        ( শূন্য ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        pxThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        যদি( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            pxThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( pxThreadToResume, pxThreadToSuspend );
        }

        uxCriticalNesting--;
    }
    অন্যথা
    {
        fprintf( stderr, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

শূন্য vPortThreadDying( শূন্য * pxTaskToDelete,
                       চঞ্চল BaseType_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( pxTaskToDelete );

    ( শূন্য ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

শূন্য vPortCancelThread( শূন্য * pxTaskToDelete )
{
    Thread_t * pxThreadToCancel = prvGetThreadFromTask( pxTaskToDelete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( pxThreadToCancel->pthread );
    event_signal( pxThreadToCancel->ev );
    pthread_join( pxThreadToCancel->pthread, রিক্ত );
    event_delete( pxThreadToCancel->ev );
}
/*-----------------------------------------------------------*/

স্থির শূন্য * prvWaitForStart( শূন্য * pvParams )
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

    ঘূৰাই রিক্ত;
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvSwitchThread( Thread_t * pxThreadToResume,
                             Thread_t * pxThreadToSuspend )
{
    BaseType_t uxSavedCriticalNesting;

    যদি( pxThreadToSuspend != pxThreadToResume )
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

        যদি( pxThreadToSuspend->xDying == pdTRUE )
        {
            pthread_exit( রিক্ত );
        }

        prvSuspendSelf( pxThreadToSuspend );

        uxCriticalNesting = uxSavedCriticalNesting;
    }
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvSuspendSelf( Thread_t * thread )
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

স্থির শূন্য prvResumeThread( Thread_t * xThreadId )
{
    যদি( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvSetupSignalsAndSchedulerPolicy( শূন্য )
{
    সংরচনা sigaction sigtick;
    পূর্ণাঙ্ক iRet;

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
    ( শূন্য ) pthread_sigmask( SIG_SETMASK,
                              &xAllSignals,
                              &xSchedulerOriginalSignalMask );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = vPortSystemTickHandler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, রিক্ত );

    যদি( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ulPortGetRunTime( শূন্য )
{
    সংরচনা tms xTimes;

    times( &xTimes );

    ঘূৰাই ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
