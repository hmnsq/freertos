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
#ضمن "portmacro.h"
#ضمن <errno.h>
#ضمن <pthread.h>
#ضمن <limits.h>
#ضمن <signal.h>
#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <string.h>
#ضمن <sys/time.h>
#ضمن <sys/times.h>
#ضمن <time.h>
#ضمن <unistd.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "timers.h"
#ضمن "utils/wait_for_event.h"
/*-----------------------------------------------------------*/

#define SIG_RESUME    SIGUSR1

تعريفنوع بنية THREAD
{
    pthread_t pthread;
    TaskFunction_t pxCode;
    فراغ * pvParams;
    BaseType_t xDying;
    بنية event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
ساكن مضمن Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    StackType_t * pxTopOfStack = *( StackType_t ** ) xTask;

    החזר ( Thread_t * ) ( pxTopOfStack + 1 );
}

/*-----------------------------------------------------------*/

ساكن pthread_once_t hSigSetupThread = PTHREAD_ONCE_INIT;
ساكن pthread_once_t hThreadKeyOnce = PTHREAD_ONCE_INIT;
ساكن sigset_t xAllSignals;
ساكن sigset_t xSchedulerOriginalSignalMask;
ساكن pthread_t hMainThread = ( pthread_t ) عدم;
ساكن متطاير BaseType_t uxCriticalNesting;
ساكن BaseType_t xSchedulerEnd = pdFALSE;
ساكن pthread_t hTimerTickThread;
ساكن bool xTimerTickThreadShouldRun;
ساكن uint64_t prvStartTimeNs;
ساكن pthread_key_t xThreadKey = 0;
/*-----------------------------------------------------------*/

ساكن فراغ prvSetupSignalsAndSchedulerPolicy( فراغ );
ساكن فراغ prvSetupTimerInterrupt( فراغ );
ساكن فراغ * prvWaitForStart( فراغ * pvParams );
ساكن فراغ prvSwitchThread( Thread_t * xThreadToResume,
                             Thread_t * xThreadToSuspend );
ساكن فراغ prvSuspendSelf( Thread_t * thread );
ساكن فراغ prvResumeThread( Thread_t * xThreadId );
ساكن فراغ vPortSystemTickHandler( صحيح sig );
ساكن فراغ vPortStartFirstTask( فراغ );
ساكن فراغ prvPortYieldFromISR( فراغ );
ساكن فراغ prvThreadKeyDestructor( فراغ * pvData );
ساكن فراغ prvInitThreadKey( فراغ );
ساكن فراغ prvMarkAsFreeRTOSThread( فراغ );
ساكن BaseType_t prvIsFreeRTOSThread( فراغ );
ساكن فراغ prvDestroyThreadKey( فراغ );
/*-----------------------------------------------------------*/

ساكن فراغ prvThreadKeyDestructor( فراغ * pvData )
{
    حرر( pvData );
}
/*-----------------------------------------------------------*/

ساكن فراغ prvInitThreadKey( فراغ )
{
    pthread_key_create( &xThreadKey, prvThreadKeyDestructor );
    /* Destroy xThreadKey when the process exits. */
    atexit( prvDestroyThreadKey );
}
/*-----------------------------------------------------------*/

ساكن فراغ prvMarkAsFreeRTOSThread( فراغ )
{
    uint8_t * pucThreadData = عدم;

    ( فراغ ) pthread_once( &hThreadKeyOnce, prvInitThreadKey );

    pucThreadData = malloc( 1 );
    configASSERT( pucThreadData != عدم );

    *pucThreadData = 1;

    pthread_setspecific( xThreadKey, pucThreadData );
}
/*-----------------------------------------------------------*/

ساكن BaseType_t prvIsFreeRTOSThread( فراغ )
{
    uint8_t * pucThreadData = عدم;
    BaseType_t xRet = pdFALSE;

    ( فراغ ) pthread_once( &hThreadKeyOnce, prvInitThreadKey );

    pucThreadData = ( uint8_t * ) pthread_getspecific( xThreadKey );

    אם( ( pucThreadData != عدم ) && ( *pucThreadData == 1 ) )
    {
        xRet = pdTRUE;
    }

    החזר xRet;
}
/*-----------------------------------------------------------*/

ساكن فراغ prvDestroyThreadKey( فراغ )
{
    pthread_key_delete( xThreadKey );
}
/*-----------------------------------------------------------*/

ساكن فراغ prvFatalError( ثابت حرف * pcCall,
                           صحيح iErrno ) __attribute__( ( __noreturn__ ) );

فراغ prvFatalError( ثابت حرف * pcCall,
                    صحيح iErrno )
{
    fprintf( stderr, "%s: %s\n", pcCall, strerror( iErrno ) );
    abort();
}
/*-----------------------------------------------------------*/

ساكن فراغ prvPortSetCurrentThreadName( ثابت حرف * pxThreadName )
{
    #ifdef __APPLE__
        pthread_setname_np( pxThreadName );
    #אחרת
        pthread_setname_np( pthread_self(), pxThreadName );
    #endif
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
                                     StackType_t * pxEndOfStack,
                                     TaskFunction_t pxCode,
                                     فراغ * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t xThreadAttributes;
    size_t ulStackSize;
    صحيح iRet;

    ( فراغ ) pthread_once( &hSigSetupThread, prvSetupSignalsAndSchedulerPolicy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( pxTopOfStack + 1 ) - 1;
    pxTopOfStack = ( StackType_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ulStackSize = ( size_t ) ( pxTopOfStack + 1 - pxEndOfStack ) * حجم( *pxTopOfStack );
    configASSERT( ulStackSize > حجم( Thread_t ) );
    ( فراغ ) ulStackSize; /* suppress set but not used warning */

    thread->pxCode = pxCode;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &xThreadAttributes );

    thread->ev = event_create();

    vPortEnterCritical();

    iRet = pthread_create( &thread->pthread, &xThreadAttributes,
                           prvWaitForStart, thread );

    אם( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    vPortExitCritical();

    החזר pxTopOfStack;
}
/*-----------------------------------------------------------*/

فراغ vPortStartFirstTask( فراغ )
{
    Thread_t * pxFirstThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( pxFirstThread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( فراغ )
{
    صحيح iSignal;
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
    ( فراغ ) pthread_sigmask( SIG_BLOCK, &xSignals, عدم );

    /* Start the first task. */
    vPortStartFirstTask();

    /* Wait until signaled by vPortEndScheduler(). */
    כלעוד( xSchedulerEnd != pdTRUE )
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
    #אם __APPLE__
        hSigSetupThread.__sig = _PTHREAD_ONCE_SIG_init;
        hThreadKeyOnce.__sig = _PTHREAD_ONCE_SIG_init;
        memset( ( فراغ * ) &hSigSetupThread.__opaque, 0, حجم( hSigSetupThread.__opaque ) );
        memset( ( فراغ * ) &hThreadKeyOnce.__opaque, 0, حجم( hThreadKeyOnce.__opaque ) );
    #אחרת /* Linux PTHREAD library*/
        hSigSetupThread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        hThreadKeyOnce = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #endif /* __APPLE__*/

    /* Restore original signal mask. */
    ( فراغ ) pthread_sigmask( SIG_SETMASK, &xSchedulerOriginalSignalMask, عدم );

    החזר 0;
}
/*-----------------------------------------------------------*/

فراغ vPortEndScheduler( فراغ )
{
    Thread_t * pxCurrentThread;
    BaseType_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    xTimerTickThreadShouldRun = false;
    pthread_join( hTimerTickThread, عدم );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    xSchedulerEnd = pdTRUE;
    ( فراغ ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    אם( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

فراغ vPortEnterCritical( فراغ )
{
    אם( uxCriticalNesting == 0 )
    {
        vPortDisableInterrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ vPortExitCritical( فراغ )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    אם( uxCriticalNesting == 0 )
    {
        vPortEnableInterrupts();
    }
}
/*-----------------------------------------------------------*/

ساكن فراغ prvPortYieldFromISR( فراغ )
{
    Thread_t * xThreadToSuspend;
    Thread_t * xThreadToResume;

    xThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    xThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( xThreadToResume, xThreadToSuspend );
}
/*-----------------------------------------------------------*/

فراغ vPortYield( فراغ )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    vPortEnterCritical();

    prvPortYieldFromISR();

    vPortExitCritical();
}
/*-----------------------------------------------------------*/

فراغ vPortDisableInterrupts( فراغ )
{
    אם( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &xAllSignals, عدم );
    }
}
/*-----------------------------------------------------------*/

فراغ vPortEnableInterrupts( فراغ )
{
    אם( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &xAllSignals, عدم );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t xPortSetInterruptMask( فراغ )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    החזר ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

فراغ vPortClearInterruptMask( UBaseType_t uxMask )
{
    ( فراغ ) uxMask;
}
/*-----------------------------------------------------------*/

ساكن uint64_t prvGetTimeNs( فراغ )
{
    بنية timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    החזר ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

ساكن فراغ * prvTimerTickHandler( فراغ * arg )
{
    ( فراغ ) arg;

    prvMarkAsFreeRTOSThread();

    prvPortSetCurrentThreadName( "Scheduler timer" );

    כלעוד( xTimerTickThreadShouldRun )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( portTICK_RATE_MICROSECONDS );
    }

    החזר عدم;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
فراغ prvSetupTimerInterrupt( فراغ )
{
    xTimerTickThreadShouldRun = true;
    pthread_create( &hTimerTickThread, عدم, prvTimerTickHandler, عدم );

    prvStartTimeNs = prvGetTimeNs();
}
/*-----------------------------------------------------------*/

ساكن فراغ vPortSystemTickHandler( صحيح sig )
{
    אם( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * pxThreadToSuspend;
        Thread_t * pxThreadToResume;

        ( فراغ ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        pxThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        אם( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            pxThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( pxThreadToResume, pxThreadToSuspend );
        }

        uxCriticalNesting--;
    }
    אחרת
    {
        fprintf( stderr, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

فراغ vPortThreadDying( فراغ * pxTaskToDelete,
                       متطاير BaseType_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( pxTaskToDelete );

    ( فراغ ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

فراغ vPortCancelThread( فراغ * pxTaskToDelete )
{
    Thread_t * pxThreadToCancel = prvGetThreadFromTask( pxTaskToDelete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( pxThreadToCancel->pthread );
    event_signal( pxThreadToCancel->ev );
    pthread_join( pxThreadToCancel->pthread, عدم );
    event_delete( pxThreadToCancel->ev );
}
/*-----------------------------------------------------------*/

ساكن فراغ * prvWaitForStart( فراغ * pvParams )
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

    החזר عدم;
}
/*-----------------------------------------------------------*/

ساكن فراغ prvSwitchThread( Thread_t * pxThreadToResume,
                             Thread_t * pxThreadToSuspend )
{
    BaseType_t uxSavedCriticalNesting;

    אם( pxThreadToSuspend != pxThreadToResume )
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

        אם( pxThreadToSuspend->xDying == pdTRUE )
        {
            pthread_exit( عدم );
        }

        prvSuspendSelf( pxThreadToSuspend );

        uxCriticalNesting = uxSavedCriticalNesting;
    }
}
/*-----------------------------------------------------------*/

ساكن فراغ prvSuspendSelf( Thread_t * thread )
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

ساكن فراغ prvResumeThread( Thread_t * xThreadId )
{
    אם( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

ساكن فراغ prvSetupSignalsAndSchedulerPolicy( فراغ )
{
    بنية sigaction sigtick;
    صحيح iRet;

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
    ( فراغ ) pthread_sigmask( SIG_SETMASK,
                              &xAllSignals,
                              &xSchedulerOriginalSignalMask );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = vPortSystemTickHandler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, عدم );

    אם( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ulPortGetRunTime( فراغ )
{
    بنية tms xTimes;

    times( &xTimes );

    החזר ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
