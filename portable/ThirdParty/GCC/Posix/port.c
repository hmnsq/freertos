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
#അന്തര്ഭാവ "portmacro.h"
#അന്തര്ഭാവ <errno.h>
#അന്തര്ഭാവ <pthread.h>
#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <signal.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ <sys/time.h>
#അന്തര്ഭാവ <sys/times.h>
#അന്തര്ഭാവ <time.h>
#അന്തര്ഭാവ <unistd.h>

/* Scheduler includes. */
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"
#അന്തര്ഭാവ "timers.h"
#അന്തര്ഭാവ "utils/wait_for_event.h"
/*-----------------------------------------------------------*/

#define SIG_RESUME    SIGUSR1

തരനിർവചനം ഘടന THREAD
{
    pthread_t pthread;
    TaskFunction_t pxCode;
    ശൂന്യം * pvParams;
    BaseType_t xDying;
    ഘടന event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
സ്ഥിതം വരിയിൽ Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി = *( അട്ടി_Type_t ** ) xTask;

    തിരികെ ( Thread_t * ) ( px_മുകൾ_Of_അട്ടി + 1 );
}

/*-----------------------------------------------------------*/

സ്ഥിതം pthread_once_t hSigSetupThread = PTHREAD_ONCE_INIT;
സ്ഥിതം pthread_once_t h_Thread_താക്കോൽ_Once = PTHREAD_ONCE_INIT;
സ്ഥിതം sigset_t xAllSignals;
സ്ഥിതം sigset_t xSchedulerOriginalSignalMask;
സ്ഥിതം pthread_t hMainThread = ( pthread_t ) ശൂന്യ;
സ്ഥിതം അസ്ഥിര BaseType_t uxCriticalNesting;
സ്ഥിതം BaseType_t xSchedulerEnd = pdFALSE;
സ്ഥിതം pthread_t hTimerTickThread;
സ്ഥിതം bool xTimerTickThreadShouldRun;
സ്ഥിതം uint64_t prvStartTimeNs;
സ്ഥിതം pthread_key_t x_Thread_താക്കോൽ = 0;
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvSetupSignalsAndSchedulerPolicy( ശൂന്യം );
സ്ഥിതം ശൂന്യം prvSetupTimerInterrupt( ശൂന്യം );
സ്ഥിതം ശൂന്യം * prvWaitForStart( ശൂന്യം * pvParams );
സ്ഥിതം ശൂന്യം prvSwitchThread( Thread_t * xThreadToResume,
                             Thread_t * xThreadToSuspend );
സ്ഥിതം ശൂന്യം prvSuspendSelf( Thread_t * thread );
സ്ഥിതം ശൂന്യം prvResumeThread( Thread_t * xThreadId );
സ്ഥിതം ശൂന്യം vPortSystemTickHandler( പൂർണ്ണസംഖ്യ sig );
സ്ഥിതം ശൂന്യം vPortStartFirstTask( ശൂന്യം );
സ്ഥിതം ശൂന്യം prvPortYieldFromISR( ശൂന്യം );
സ്ഥിതം ശൂന്യം prv_Thread_താക്കോൽ_Destructor( ശൂന്യം * pvData );
സ്ഥിതം ശൂന്യം prv_Init_Thread_താക്കോൽ( ശൂന്യം );
സ്ഥിതം ശൂന്യം prvMarkAsFreeRTOSThread( ശൂന്യം );
സ്ഥിതം BaseType_t prvIsFreeRTOSThread( ശൂന്യം );
സ്ഥിതം ശൂന്യം prv_Destroy_Thread_താക്കോൽ( ശൂന്യം );
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prv_Thread_താക്കോൽ_Destructor( ശൂന്യം * pvData )
{
    സ്വതന്ത്രം( pvData );
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prv_Init_Thread_താക്കോൽ( ശൂന്യം )
{
    pthread_key_create( &x_Thread_താക്കോൽ, prv_Thread_താക്കോൽ_Destructor );
    /* Destroy xThreadKey when the process exits. */
    atexit( prv_Destroy_Thread_താക്കോൽ );
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvMarkAsFreeRTOSThread( ശൂന്യം )
{
    uint8_t * pucThreadData = ശൂന്യ;

    ( ശൂന്യം ) pthread_once( &h_Thread_താക്കോൽ_Once, prv_Init_Thread_താക്കോൽ );

    pucThreadData = malloc( 1 );
    configASSERT( pucThreadData != ശൂന്യ );

    *pucThreadData = 1;

    pthread_setspecific( x_Thread_താക്കോൽ, pucThreadData );
}
/*-----------------------------------------------------------*/

സ്ഥിതം BaseType_t prvIsFreeRTOSThread( ശൂന്യം )
{
    uint8_t * pucThreadData = ശൂന്യ;
    BaseType_t xRet = pdFALSE;

    ( ശൂന്യം ) pthread_once( &h_Thread_താക്കോൽ_Once, prv_Init_Thread_താക്കോൽ );

    pucThreadData = ( uint8_t * ) pthread_getspecific( x_Thread_താക്കോൽ );

    എങ്കിൽ( ( pucThreadData != ശൂന്യ ) && ( *pucThreadData == 1 ) )
    {
        xRet = pdTRUE;
    }

    തിരികെ xRet;
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prv_Destroy_Thread_താക്കോൽ( ശൂന്യം )
{
    pthread_key_delete( x_Thread_താക്കോൽ );
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvFatalError( സ്ഥിരം അക്ഷരം * pcCall,
                           പൂർണ്ണസംഖ്യ iErrno ) __attribute__( ( __noreturn__ ) );

ശൂന്യം prvFatalError( സ്ഥിരം അക്ഷരം * pcCall,
                    പൂർണ്ണസംഖ്യ iErrno )
{
    fprintf( stderr, "%s: %s\n", pcCall, strerror( iErrno ) );
    abort();
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvPortSetCurrentThreadName( സ്ഥിരം അക്ഷരം * pxThreadName )
{
    #ifdef __APPLE__
        pthread_setname_np( pxThreadName );
    #അല്ലെങ്കിൽ
        pthread_setname_np( pthread_self(), pxThreadName );
    #endif
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
അട്ടി_Type_t * px_Port_Initialise_അട്ടി( അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി,
                                     അട്ടി_Type_t * px_End_Of_അട്ടി,
                                     TaskFunction_t pxCode,
                                     ശൂന്യം * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t xThreadAttributes;
    size_t ul_അട്ടി_Size;
    പൂർണ്ണസംഖ്യ iRet;

    ( ശൂന്യം ) pthread_once( &hSigSetupThread, prvSetupSignalsAndSchedulerPolicy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_മുകൾ_Of_അട്ടി + 1 ) - 1;
    px_മുകൾ_Of_അട്ടി = ( അട്ടി_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_അട്ടി_Size = ( size_t ) ( px_മുകൾ_Of_അട്ടി + 1 - px_End_Of_അട്ടി ) * വലുപ്പം( *px_മുകൾ_Of_അട്ടി );
    configASSERT( ul_അട്ടി_Size > വലുപ്പം( Thread_t ) );
    ( ശൂന്യം ) ul_അട്ടി_Size; /* suppress set but not used warning */

    thread->pxCode = pxCode;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &xThreadAttributes );

    thread->ev = event_create();

    vPortEnterCritical();

    iRet = pthread_create( &thread->pthread, &xThreadAttributes,
                           prvWaitForStart, thread );

    എങ്കിൽ( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    vPortExitCritical();

    തിരികെ px_മുകൾ_Of_അട്ടി;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortStartFirstTask( ശൂന്യം )
{
    Thread_t * pxFirstThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( pxFirstThread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( ശൂന്യം )
{
    പൂർണ്ണസംഖ്യ iSignal;
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
    ( ശൂന്യം ) pthread_sigmask( SIG_BLOCK, &xSignals, ശൂന്യ );

    /* Start the first task. */
    vPortStartFirstTask();

    /* Wait until signaled by vPortEndScheduler(). */
    ആകുമ്പോൾ( xSchedulerEnd != pdTRUE )
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
    #എങ്കിൽ __APPLE__
        hSigSetupThread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_താക്കോൽ_Once.__sig = _PTHREAD_ONCE_SIG_init;
        memset( ( ശൂന്യം * ) &hSigSetupThread.__opaque, 0, വലുപ്പം( hSigSetupThread.__opaque ) );
        memset( ( ശൂന്യം * ) &h_Thread_താക്കോൽ_Once.__opaque, 0, വലുപ്പം( h_Thread_താക്കോൽ_Once.__opaque ) );
    #അല്ലെങ്കിൽ /* Linux PTHREAD library*/
        hSigSetupThread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_താക്കോൽ_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #endif /* __APPLE__*/

    /* Restore original signal mask. */
    ( ശൂന്യം ) pthread_sigmask( SIG_SETMASK, &xSchedulerOriginalSignalMask, ശൂന്യ );

    തിരികെ 0;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEndScheduler( ശൂന്യം )
{
    Thread_t * pxCurrentThread;
    BaseType_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    xTimerTickThreadShouldRun = false;
    pthread_join( hTimerTickThread, ശൂന്യ );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    xSchedulerEnd = pdTRUE;
    ( ശൂന്യം ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    എങ്കിൽ( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEnterCritical( ശൂന്യം )
{
    എങ്കിൽ( uxCriticalNesting == 0 )
    {
        vPortDisableInterrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortExitCritical( ശൂന്യം )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    എങ്കിൽ( uxCriticalNesting == 0 )
    {
        vPortEnableInterrupts();
    }
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvPortYieldFromISR( ശൂന്യം )
{
    Thread_t * xThreadToSuspend;
    Thread_t * xThreadToResume;

    xThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    xThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( xThreadToResume, xThreadToSuspend );
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortYield( ശൂന്യം )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    vPortEnterCritical();

    prvPortYieldFromISR();

    vPortExitCritical();
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortDisableInterrupts( ശൂന്യം )
{
    എങ്കിൽ( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &xAllSignals, ശൂന്യ );
    }
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEnableInterrupts( ശൂന്യം )
{
    എങ്കിൽ( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &xAllSignals, ശൂന്യ );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t xPortSetInterruptMask( ശൂന്യം )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    തിരികെ ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortClearInterruptMask( UBaseType_t uxMask )
{
    ( ശൂന്യം ) uxMask;
}
/*-----------------------------------------------------------*/

സ്ഥിതം uint64_t prvGetTimeNs( ശൂന്യം )
{
    ഘടന timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    തിരികെ ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

സ്ഥിതം ശൂന്യം * prvTimerTickHandler( ശൂന്യം * arg )
{
    ( ശൂന്യം ) arg;

    prvMarkAsFreeRTOSThread();

    prvPortSetCurrentThreadName( "Scheduler timer" );

    ആകുമ്പോൾ( xTimerTickThreadShouldRun )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( portTICK_RATE_MICROSECONDS );
    }

    തിരികെ ശൂന്യ;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
ശൂന്യം prvSetupTimerInterrupt( ശൂന്യം )
{
    xTimerTickThreadShouldRun = true;
    pthread_create( &hTimerTickThread, ശൂന്യ, prvTimerTickHandler, ശൂന്യ );

    prvStartTimeNs = prvGetTimeNs();
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം vPortSystemTickHandler( പൂർണ്ണസംഖ്യ sig )
{
    എങ്കിൽ( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * pxThreadToSuspend;
        Thread_t * pxThreadToResume;

        ( ശൂന്യം ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        pxThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        എങ്കിൽ( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            pxThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( pxThreadToResume, pxThreadToSuspend );
        }

        uxCriticalNesting--;
    }
    അല്ലെങ്കിൽ
    {
        fprintf( stderr, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortThreadDying( ശൂന്യം * pxTaskToDelete,
                       അസ്ഥിര BaseType_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( pxTaskToDelete );

    ( ശൂന്യം ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortCancelThread( ശൂന്യം * pxTaskToDelete )
{
    Thread_t * pxThreadToCancel = prvGetThreadFromTask( pxTaskToDelete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( pxThreadToCancel->pthread );
    event_signal( pxThreadToCancel->ev );
    pthread_join( pxThreadToCancel->pthread, ശൂന്യ );
    event_delete( pxThreadToCancel->ev );
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം * prvWaitForStart( ശൂന്യം * pvParams )
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

    തിരികെ ശൂന്യ;
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvSwitchThread( Thread_t * pxThreadToResume,
                             Thread_t * pxThreadToSuspend )
{
    BaseType_t uxSavedCriticalNesting;

    എങ്കിൽ( pxThreadToSuspend != pxThreadToResume )
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

        എങ്കിൽ( pxThreadToSuspend->xDying == pdTRUE )
        {
            pthread_exit( ശൂന്യ );
        }

        prvSuspendSelf( pxThreadToSuspend );

        uxCriticalNesting = uxSavedCriticalNesting;
    }
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvSuspendSelf( Thread_t * thread )
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

സ്ഥിതം ശൂന്യം prvResumeThread( Thread_t * xThreadId )
{
    എങ്കിൽ( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvSetupSignalsAndSchedulerPolicy( ശൂന്യം )
{
    ഘടന sigaction sigtick;
    പൂർണ്ണസംഖ്യ iRet;

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
    ( ശൂന്യം ) pthread_sigmask( SIG_SETMASK,
                              &xAllSignals,
                              &xSchedulerOriginalSignalMask );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = vPortSystemTickHandler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, ശൂന്യ );

    എങ്കിൽ( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ulPortGetRunTime( ശൂന്യം )
{
    ഘടന tms xTimes;

    times( &xTimes );

    തിരികെ ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
