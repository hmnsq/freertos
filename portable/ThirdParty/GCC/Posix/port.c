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
#شامل "portmacro.h"
#شامل <errno.h>
#شامل <pthread.h>
#شامل <limits.h>
#شامل <signal.h>
#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <string.h>
#شامل <sys/time.h>
#شامل <sys/times.h>
#شامل <time.h>
#شامل <unistd.h>

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"
#شامل "timers.h"
#شامل "utils/wait_for_event.h"
/*-----------------------------------------------------------*/

#define SIG_RESUME    SIGUSR1

تعریفنوع ساختار THREAD
{
    pthread_t pthread;
    TaskFunction_t pxCode;
    تهی * pvParams;
    BaseType_t xDying;
    ساختار event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
ایستا درونخطی Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    پشته_Type_t * px_بالاترین_Of_پشته = *( پشته_Type_t ** ) xTask;

    بازگشت ( Thread_t * ) ( px_بالاترین_Of_پشته + 1 );
}

/*-----------------------------------------------------------*/

ایستا pthread_once_t hSigSetupThread = PTHREAD_ONCE_INIT;
ایستا pthread_once_t h_Thread_کلید_Once = PTHREAD_ONCE_INIT;
ایستا sigset_t xAllSignals;
ایستا sigset_t xSchedulerOriginalSignalMask;
ایستا pthread_t hMainThread = ( pthread_t ) پوچ;
ایستا فرار BaseType_t uxCriticalNesting;
ایستا BaseType_t xSchedulerEnd = pdFALSE;
ایستا pthread_t hTimerTickThread;
ایستا bool xTimerTickThreadShouldRun;
ایستا uint64_t prvStartTimeNs;
ایستا pthread_key_t x_Thread_کلید = 0;
/*-----------------------------------------------------------*/

ایستا تهی prvSetupSignalsAndSchedulerPolicy( تهی );
ایستا تهی prvSetupTimerInterrupt( تهی );
ایستا تهی * prvWaitForStart( تهی * pvParams );
ایستا تهی prvSwitchThread( Thread_t * xThreadToResume,
                             Thread_t * xThreadToSuspend );
ایستا تهی prvSuspendSelf( Thread_t * thread );
ایستا تهی prvResumeThread( Thread_t * xThreadId );
ایستا تهی vPortSystemTickHandler( صحیح sig );
ایستا تهی vPortStartFirstTask( تهی );
ایستا تهی prvPortYieldFromISR( تهی );
ایستا تهی prv_Thread_کلید_Destructor( تهی * pvData );
ایستا تهی prv_Init_Thread_کلید( تهی );
ایستا تهی prvMarkAsFreeRTOSThread( تهی );
ایستا BaseType_t prvIsFreeRTOSThread( تهی );
ایستا تهی prv_Destroy_Thread_کلید( تهی );
/*-----------------------------------------------------------*/

ایستا تهی prv_Thread_کلید_Destructor( تهی * pvData )
{
    آزاد( pvData );
}
/*-----------------------------------------------------------*/

ایستا تهی prv_Init_Thread_کلید( تهی )
{
    pthread_key_create( &x_Thread_کلید, prv_Thread_کلید_Destructor );
    /* Destroy xThreadKey when the process exits. */
    atexit( prv_Destroy_Thread_کلید );
}
/*-----------------------------------------------------------*/

ایستا تهی prvMarkAsFreeRTOSThread( تهی )
{
    uint8_t * pucThreadData = پوچ;

    ( تهی ) pthread_once( &h_Thread_کلید_Once, prv_Init_Thread_کلید );

    pucThreadData = malloc( 1 );
    configASSERT( pucThreadData != پوچ );

    *pucThreadData = 1;

    pthread_setspecific( x_Thread_کلید, pucThreadData );
}
/*-----------------------------------------------------------*/

ایستا BaseType_t prvIsFreeRTOSThread( تهی )
{
    uint8_t * pucThreadData = پوچ;
    BaseType_t xRet = pdFALSE;

    ( تهی ) pthread_once( &h_Thread_کلید_Once, prv_Init_Thread_کلید );

    pucThreadData = ( uint8_t * ) pthread_getspecific( x_Thread_کلید );

    اگر( ( pucThreadData != پوچ ) && ( *pucThreadData == 1 ) )
    {
        xRet = pdTRUE;
    }

    بازگشت xRet;
}
/*-----------------------------------------------------------*/

ایستا تهی prv_Destroy_Thread_کلید( تهی )
{
    pthread_key_delete( x_Thread_کلید );
}
/*-----------------------------------------------------------*/

ایستا تهی prvFatalError( ثابت نویسه * pcCall,
                           صحیح iErrno ) __attribute__( ( __noreturn__ ) );

تهی prvFatalError( ثابت نویسه * pcCall,
                    صحیح iErrno )
{
    fprintf( stderr, "%s: %s\n", pcCall, strerror( iErrno ) );
    abort();
}
/*-----------------------------------------------------------*/

ایستا تهی prvPortSetCurrentThreadName( ثابت نویسه * pxThreadName )
{
    #ifdef __APPLE__
        pthread_setname_np( pxThreadName );
    #وگرنه
        pthread_setname_np( pthread_self(), pxThreadName );
    #endif
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
پشته_Type_t * px_Port_Initialise_پشته( پشته_Type_t * px_بالاترین_Of_پشته,
                                     پشته_Type_t * px_End_Of_پشته,
                                     TaskFunction_t pxCode,
                                     تهی * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t xThreadAttributes;
    size_t ul_پشته_Size;
    صحیح iRet;

    ( تهی ) pthread_once( &hSigSetupThread, prvSetupSignalsAndSchedulerPolicy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_بالاترین_Of_پشته + 1 ) - 1;
    px_بالاترین_Of_پشته = ( پشته_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_پشته_Size = ( size_t ) ( px_بالاترین_Of_پشته + 1 - px_End_Of_پشته ) * اندازه( *px_بالاترین_Of_پشته );
    configASSERT( ul_پشته_Size > اندازه( Thread_t ) );
    ( تهی ) ul_پشته_Size; /* suppress set but not used warning */

    thread->pxCode = pxCode;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &xThreadAttributes );

    thread->ev = event_create();

    vPortEnterCritical();

    iRet = pthread_create( &thread->pthread, &xThreadAttributes,
                           prvWaitForStart, thread );

    اگر( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    vPortExitCritical();

    بازگشت px_بالاترین_Of_پشته;
}
/*-----------------------------------------------------------*/

تهی vPortStartFirstTask( تهی )
{
    Thread_t * pxFirstThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( pxFirstThread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( تهی )
{
    صحیح iSignal;
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
    ( تهی ) pthread_sigmask( SIG_BLOCK, &xSignals, پوچ );

    /* Start the first task. */
    vPortStartFirstTask();

    /* Wait until signaled by vPortEndScheduler(). */
    وقتی( xSchedulerEnd != pdTRUE )
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
    #اگر __APPLE__
        hSigSetupThread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_کلید_Once.__sig = _PTHREAD_ONCE_SIG_init;
        memset( ( تهی * ) &hSigSetupThread.__opaque, 0, اندازه( hSigSetupThread.__opaque ) );
        memset( ( تهی * ) &h_Thread_کلید_Once.__opaque, 0, اندازه( h_Thread_کلید_Once.__opaque ) );
    #وگرنه /* Linux PTHREAD library*/
        hSigSetupThread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_کلید_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #endif /* __APPLE__*/

    /* Restore original signal mask. */
    ( تهی ) pthread_sigmask( SIG_SETMASK, &xSchedulerOriginalSignalMask, پوچ );

    بازگشت 0;
}
/*-----------------------------------------------------------*/

تهی vPortEndScheduler( تهی )
{
    Thread_t * pxCurrentThread;
    BaseType_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    xTimerTickThreadShouldRun = false;
    pthread_join( hTimerTickThread, پوچ );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    xSchedulerEnd = pdTRUE;
    ( تهی ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    اگر( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

تهی vPortEnterCritical( تهی )
{
    اگر( uxCriticalNesting == 0 )
    {
        vPortDisableInterrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

تهی vPortExitCritical( تهی )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    اگر( uxCriticalNesting == 0 )
    {
        vPortEnableInterrupts();
    }
}
/*-----------------------------------------------------------*/

ایستا تهی prvPortYieldFromISR( تهی )
{
    Thread_t * xThreadToSuspend;
    Thread_t * xThreadToResume;

    xThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    xThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( xThreadToResume, xThreadToSuspend );
}
/*-----------------------------------------------------------*/

تهی vPortYield( تهی )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    vPortEnterCritical();

    prvPortYieldFromISR();

    vPortExitCritical();
}
/*-----------------------------------------------------------*/

تهی vPortDisableInterrupts( تهی )
{
    اگر( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &xAllSignals, پوچ );
    }
}
/*-----------------------------------------------------------*/

تهی vPortEnableInterrupts( تهی )
{
    اگر( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &xAllSignals, پوچ );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t xPortSetInterruptMask( تهی )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    بازگشت ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

تهی vPortClearInterruptMask( UBaseType_t uxMask )
{
    ( تهی ) uxMask;
}
/*-----------------------------------------------------------*/

ایستا uint64_t prvGetTimeNs( تهی )
{
    ساختار timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    بازگشت ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

ایستا تهی * prvTimerTickHandler( تهی * arg )
{
    ( تهی ) arg;

    prvMarkAsFreeRTOSThread();

    prvPortSetCurrentThreadName( "Scheduler timer" );

    وقتی( xTimerTickThreadShouldRun )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( portTICK_RATE_MICROSECONDS );
    }

    بازگشت پوچ;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
تهی prvSetupTimerInterrupt( تهی )
{
    xTimerTickThreadShouldRun = true;
    pthread_create( &hTimerTickThread, پوچ, prvTimerTickHandler, پوچ );

    prvStartTimeNs = prvGetTimeNs();
}
/*-----------------------------------------------------------*/

ایستا تهی vPortSystemTickHandler( صحیح sig )
{
    اگر( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * pxThreadToSuspend;
        Thread_t * pxThreadToResume;

        ( تهی ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        pxThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        اگر( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            pxThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( pxThreadToResume, pxThreadToSuspend );
        }

        uxCriticalNesting--;
    }
    وگرنه
    {
        fprintf( stderr, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

تهی vPortThreadDying( تهی * pxTaskToDelete,
                       فرار BaseType_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( pxTaskToDelete );

    ( تهی ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

تهی vPortCancelThread( تهی * pxTaskToDelete )
{
    Thread_t * pxThreadToCancel = prvGetThreadFromTask( pxTaskToDelete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( pxThreadToCancel->pthread );
    event_signal( pxThreadToCancel->ev );
    pthread_join( pxThreadToCancel->pthread, پوچ );
    event_delete( pxThreadToCancel->ev );
}
/*-----------------------------------------------------------*/

ایستا تهی * prvWaitForStart( تهی * pvParams )
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

    بازگشت پوچ;
}
/*-----------------------------------------------------------*/

ایستا تهی prvSwitchThread( Thread_t * pxThreadToResume,
                             Thread_t * pxThreadToSuspend )
{
    BaseType_t uxSavedCriticalNesting;

    اگر( pxThreadToSuspend != pxThreadToResume )
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

        اگر( pxThreadToSuspend->xDying == pdTRUE )
        {
            pthread_exit( پوچ );
        }

        prvSuspendSelf( pxThreadToSuspend );

        uxCriticalNesting = uxSavedCriticalNesting;
    }
}
/*-----------------------------------------------------------*/

ایستا تهی prvSuspendSelf( Thread_t * thread )
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

ایستا تهی prvResumeThread( Thread_t * xThreadId )
{
    اگر( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

ایستا تهی prvSetupSignalsAndSchedulerPolicy( تهی )
{
    ساختار sigaction sigtick;
    صحیح iRet;

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
    ( تهی ) pthread_sigmask( SIG_SETMASK,
                              &xAllSignals,
                              &xSchedulerOriginalSignalMask );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = vPortSystemTickHandler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, پوچ );

    اگر( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ulPortGetRunTime( تهی )
{
    ساختار tms xTimes;

    times( &xTimes );

    بازگشت ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
