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
#અન્તર્ભાવ "portmacro.h"
#અન્તર્ભાવ <errno.h>
#અન્તર્ભાવ <pthread.h>
#અન્તર્ભાવ <limits.h>
#અન્તર્ભાવ <signal.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <sys/time.h>
#અન્તર્ભાવ <sys/times.h>
#અન્તર્ભાવ <time.h>
#અન્તર્ભાવ <unistd.h>

/* Scheduler includes. */
#અન્તર્ભાવ "FreeRTOS.h"
#અન્તર્ભાવ "task.h"
#અન્તર્ભાવ "timers.h"
#અન્તર્ભાવ "utils/wait_for_event.h"
/*-----------------------------------------------------------*/

#define SIG_RESUME    SIGUSR1

પ્રકારવ્યાખ્યા સંરચના THREAD
{
    pthread_t pthread;
    TaskFunction_t pxCode;
    શૂન્ય * pvParams;
    BaseType_t xDying;
    સંરચના event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
સ્થિર અંતઃરેખ Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    ઢગલો_Type_t * px_ટોચ_Of_ઢગલો = *( ઢગલો_Type_t ** ) xTask;

    પાછા ( Thread_t * ) ( px_ટોચ_Of_ઢગલો + 1 );
}

/*-----------------------------------------------------------*/

સ્થિર pthread_once_t hSigSetupThread = PTHREAD_ONCE_INIT;
સ્થિર pthread_once_t h_Thread_ચાવી_Once = PTHREAD_ONCE_INIT;
સ્થિર sigset_t xAllSignals;
સ્થિર sigset_t xSchedulerOriginalSignalMask;
સ્થિર pthread_t hMainThread = ( pthread_t ) ખાલી;
સ્થિર અસ્થિર BaseType_t uxCriticalNesting;
સ્થિર BaseType_t xSchedulerEnd = pdFALSE;
સ્થિર pthread_t hTimerTickThread;
સ્થિર bool xTimerTickThreadShouldRun;
સ્થિર uint64_t prvStartTimeNs;
સ્થિર pthread_key_t x_Thread_ચાવી = 0;
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prvSetupSignalsAndSchedulerPolicy( શૂન્ય );
સ્થિર શૂન્ય prvSetupTimerInterrupt( શૂન્ય );
સ્થિર શૂન્ય * prvWaitForStart( શૂન્ય * pvParams );
સ્થિર શૂન્ય prvSwitchThread( Thread_t * xThreadToResume,
                             Thread_t * xThreadToSuspend );
સ્થિર શૂન્ય prvSuspendSelf( Thread_t * thread );
સ્થિર શૂન્ય prvResumeThread( Thread_t * xThreadId );
સ્થિર શૂન્ય vPortSystemTickHandler( પૂર્ણાંક sig );
સ્થિર શૂન્ય vPortStartFirstTask( શૂન્ય );
સ્થિર શૂન્ય prvPortYieldFromISR( શૂન્ય );
સ્થિર શૂન્ય prv_Thread_ચાવી_Destructor( શૂન્ય * pvData );
સ્થિર શૂન્ય prv_Init_Thread_ચાવી( શૂન્ય );
સ્થિર શૂન્ય prvMarkAsFreeRTOSThread( શૂન્ય );
સ્થિર BaseType_t prvIsFreeRTOSThread( શૂન્ય );
સ્થિર શૂન્ય prv_Destroy_Thread_ચાવી( શૂન્ય );
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prv_Thread_ચાવી_Destructor( શૂન્ય * pvData )
{
    મુક્ત( pvData );
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prv_Init_Thread_ચાવી( શૂન્ય )
{
    pthread_key_create( &x_Thread_ચાવી, prv_Thread_ચાવી_Destructor );
    /* Destroy xThreadKey when the process exits. */
    atexit( prv_Destroy_Thread_ચાવી );
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prvMarkAsFreeRTOSThread( શૂન્ય )
{
    uint8_t * pucThreadData = ખાલી;

    ( શૂન્ય ) pthread_once( &h_Thread_ચાવી_Once, prv_Init_Thread_ચાવી );

    pucThreadData = malloc( 1 );
    configASSERT( pucThreadData != ખાલી );

    *pucThreadData = 1;

    pthread_setspecific( x_Thread_ચાવી, pucThreadData );
}
/*-----------------------------------------------------------*/

સ્થિર BaseType_t prvIsFreeRTOSThread( શૂન્ય )
{
    uint8_t * pucThreadData = ખાલી;
    BaseType_t xRet = pdFALSE;

    ( શૂન્ય ) pthread_once( &h_Thread_ચાવી_Once, prv_Init_Thread_ચાવી );

    pucThreadData = ( uint8_t * ) pthread_getspecific( x_Thread_ચાવી );

    જો( ( pucThreadData != ખાલી ) && ( *pucThreadData == 1 ) )
    {
        xRet = pdTRUE;
    }

    પાછા xRet;
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prv_Destroy_Thread_ચાવી( શૂન્ય )
{
    pthread_key_delete( x_Thread_ચાવી );
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prvFatalError( અચલ અક્ષર * pcCall,
                           પૂર્ણાંક iErrno ) __attribute__( ( __noreturn__ ) );

શૂન્ય prvFatalError( અચલ અક્ષર * pcCall,
                    પૂર્ણાંક iErrno )
{
    fprintf( stderr, "%s: %s\n", pcCall, strerror( iErrno ) );
    abort();
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prvPortSetCurrentThreadName( અચલ અક્ષર * pxThreadName )
{
    #ifdef __APPLE__
        pthread_setname_np( pxThreadName );
    #નહીંતર
        pthread_setname_np( pthread_self(), pxThreadName );
    #endif
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ઢગલો_Type_t * px_Port_Initialise_ઢગલો( ઢગલો_Type_t * px_ટોચ_Of_ઢગલો,
                                     ઢગલો_Type_t * px_End_Of_ઢગલો,
                                     TaskFunction_t pxCode,
                                     શૂન્ય * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t xThreadAttributes;
    size_t ul_ઢગલો_Size;
    પૂર્ણાંક iRet;

    ( શૂન્ય ) pthread_once( &hSigSetupThread, prvSetupSignalsAndSchedulerPolicy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_ટોચ_Of_ઢગલો + 1 ) - 1;
    px_ટોચ_Of_ઢગલો = ( ઢગલો_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_ઢગલો_Size = ( size_t ) ( px_ટોચ_Of_ઢગલો + 1 - px_End_Of_ઢગલો ) * કદ( *px_ટોચ_Of_ઢગલો );
    configASSERT( ul_ઢગલો_Size > કદ( Thread_t ) );
    ( શૂન્ય ) ul_ઢગલો_Size; /* suppress set but not used warning */

    thread->pxCode = pxCode;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &xThreadAttributes );

    thread->ev = event_create();

    vPortEnterCritical();

    iRet = pthread_create( &thread->pthread, &xThreadAttributes,
                           prvWaitForStart, thread );

    જો( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    vPortExitCritical();

    પાછા px_ટોચ_Of_ઢગલો;
}
/*-----------------------------------------------------------*/

શૂન્ય vPortStartFirstTask( શૂન્ય )
{
    Thread_t * pxFirstThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( pxFirstThread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( શૂન્ય )
{
    પૂર્ણાંક iSignal;
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
    ( શૂન્ય ) pthread_sigmask( SIG_BLOCK, &xSignals, ખાલી );

    /* Start the first task. */
    vPortStartFirstTask();

    /* Wait until signaled by vPortEndScheduler(). */
    જ્યારે( xSchedulerEnd != pdTRUE )
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
    #જો __APPLE__
        hSigSetupThread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_ચાવી_Once.__sig = _PTHREAD_ONCE_SIG_init;
        memset( ( શૂન્ય * ) &hSigSetupThread.__opaque, 0, કદ( hSigSetupThread.__opaque ) );
        memset( ( શૂન્ય * ) &h_Thread_ચાવી_Once.__opaque, 0, કદ( h_Thread_ચાવી_Once.__opaque ) );
    #નહીંતર /* Linux PTHREAD library*/
        hSigSetupThread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_ચાવી_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #endif /* __APPLE__*/

    /* Restore original signal mask. */
    ( શૂન્ય ) pthread_sigmask( SIG_SETMASK, &xSchedulerOriginalSignalMask, ખાલી );

    પાછા 0;
}
/*-----------------------------------------------------------*/

શૂન્ય vPortEndScheduler( શૂન્ય )
{
    Thread_t * pxCurrentThread;
    BaseType_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    xTimerTickThreadShouldRun = false;
    pthread_join( hTimerTickThread, ખાલી );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    xSchedulerEnd = pdTRUE;
    ( શૂન્ય ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    જો( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

શૂન્ય vPortEnterCritical( શૂન્ય )
{
    જો( uxCriticalNesting == 0 )
    {
        vPortDisableInterrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

શૂન્ય vPortExitCritical( શૂન્ય )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    જો( uxCriticalNesting == 0 )
    {
        vPortEnableInterrupts();
    }
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prvPortYieldFromISR( શૂન્ય )
{
    Thread_t * xThreadToSuspend;
    Thread_t * xThreadToResume;

    xThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    xThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( xThreadToResume, xThreadToSuspend );
}
/*-----------------------------------------------------------*/

શૂન્ય vPortYield( શૂન્ય )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    vPortEnterCritical();

    prvPortYieldFromISR();

    vPortExitCritical();
}
/*-----------------------------------------------------------*/

શૂન્ય vPortDisableInterrupts( શૂન્ય )
{
    જો( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &xAllSignals, ખાલી );
    }
}
/*-----------------------------------------------------------*/

શૂન્ય vPortEnableInterrupts( શૂન્ય )
{
    જો( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &xAllSignals, ખાલી );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t xPortSetInterruptMask( શૂન્ય )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    પાછા ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

શૂન્ય vPortClearInterruptMask( UBaseType_t uxMask )
{
    ( શૂન્ય ) uxMask;
}
/*-----------------------------------------------------------*/

સ્થિર uint64_t prvGetTimeNs( શૂન્ય )
{
    સંરચના timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    પાછા ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

સ્થિર શૂન્ય * prvTimerTickHandler( શૂન્ય * arg )
{
    ( શૂન્ય ) arg;

    prvMarkAsFreeRTOSThread();

    prvPortSetCurrentThreadName( "Scheduler timer" );

    જ્યારે( xTimerTickThreadShouldRun )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( portTICK_RATE_MICROSECONDS );
    }

    પાછા ખાલી;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
શૂન્ય prvSetupTimerInterrupt( શૂન્ય )
{
    xTimerTickThreadShouldRun = true;
    pthread_create( &hTimerTickThread, ખાલી, prvTimerTickHandler, ખાલી );

    prvStartTimeNs = prvGetTimeNs();
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય vPortSystemTickHandler( પૂર્ણાંક sig )
{
    જો( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * pxThreadToSuspend;
        Thread_t * pxThreadToResume;

        ( શૂન્ય ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        pxThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        જો( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            pxThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( pxThreadToResume, pxThreadToSuspend );
        }

        uxCriticalNesting--;
    }
    નહીંતર
    {
        fprintf( stderr, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

શૂન્ય vPortThreadDying( શૂન્ય * pxTaskToDelete,
                       અસ્થિર BaseType_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( pxTaskToDelete );

    ( શૂન્ય ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

શૂન્ય vPortCancelThread( શૂન્ય * pxTaskToDelete )
{
    Thread_t * pxThreadToCancel = prvGetThreadFromTask( pxTaskToDelete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( pxThreadToCancel->pthread );
    event_signal( pxThreadToCancel->ev );
    pthread_join( pxThreadToCancel->pthread, ખાલી );
    event_delete( pxThreadToCancel->ev );
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય * prvWaitForStart( શૂન્ય * pvParams )
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

    પાછા ખાલી;
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prvSwitchThread( Thread_t * pxThreadToResume,
                             Thread_t * pxThreadToSuspend )
{
    BaseType_t uxSavedCriticalNesting;

    જો( pxThreadToSuspend != pxThreadToResume )
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

        જો( pxThreadToSuspend->xDying == pdTRUE )
        {
            pthread_exit( ખાલી );
        }

        prvSuspendSelf( pxThreadToSuspend );

        uxCriticalNesting = uxSavedCriticalNesting;
    }
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prvSuspendSelf( Thread_t * thread )
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

સ્થિર શૂન્ય prvResumeThread( Thread_t * xThreadId )
{
    જો( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prvSetupSignalsAndSchedulerPolicy( શૂન્ય )
{
    સંરચના sigaction sigtick;
    પૂર્ણાંક iRet;

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
    ( શૂન્ય ) pthread_sigmask( SIG_SETMASK,
                              &xAllSignals,
                              &xSchedulerOriginalSignalMask );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = vPortSystemTickHandler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, ખાલી );

    જો( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ulPortGetRunTime( શૂન્ય )
{
    સંરચના tms xTimes;

    times( &xTimes );

    પાછા ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
