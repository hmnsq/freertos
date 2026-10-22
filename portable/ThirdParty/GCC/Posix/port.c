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
#ಅನ್ತರ್ಭಾವ "portmacro.h"
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <pthread.h>
#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <signal.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ <sys/time.h>
#ಅನ್ತರ್ಭಾವ <sys/times.h>
#ಅನ್ತರ್ಭಾವ <time.h>
#ಅನ್ತರ್ಭಾವ <unistd.h>

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "timers.h"
#ಅನ್ತರ್ಭಾವ "utils/wait_for_event.h"
/*-----------------------------------------------------------*/

#define SIG_RESUME    SIGUSR1

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ THREAD
{
    pthread_t pthread;
    TaskFunction_t pxCode;
    ಶೂನ್ಯ * pvParams;
    BaseType_t xDying;
    ಸಂರಚನಾ event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    ರಾಶಿ_Type_t * px_ತುದಿ_Of_ರಾಶಿ = *( ರಾಶಿ_Type_t ** ) xTask;

    ಪ್ರತ್ಯಾಗಮ ( Thread_t * ) ( px_ತುದಿ_Of_ರಾಶಿ + 1 );
}

/*-----------------------------------------------------------*/

ಸ್ಥಿರ pthread_once_t hSigSetupThread = PTHREAD_ONCE_INIT;
ಸ್ಥಿರ pthread_once_t h_Thread_ಕೀಲಿ_Once = PTHREAD_ONCE_INIT;
ಸ್ಥಿರ sigset_t xAllSignals;
ಸ್ಥಿರ sigset_t xSchedulerOriginalSignalMask;
ಸ್ಥಿರ pthread_t hMainThread = ( pthread_t ) ರಿಕ್ತ;
ಸ್ಥಿರ ಚಞ್ಚಲ BaseType_t uxCriticalNesting;
ಸ್ಥಿರ BaseType_t xSchedulerEnd = pdFALSE;
ಸ್ಥಿರ pthread_t hTimerTickThread;
ಸ್ಥಿರ bool xTimerTickThreadShouldRun;
ಸ್ಥಿರ uint64_t prvStartTimeNs;
ಸ್ಥಿರ pthread_key_t x_Thread_ಕೀಲಿ = 0;
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvSetupSignalsAndSchedulerPolicy( ಶೂನ್ಯ );
ಸ್ಥಿರ ಶೂನ್ಯ prvSetupTimerInterrupt( ಶೂನ್ಯ );
ಸ್ಥಿರ ಶೂನ್ಯ * prvWaitForStart( ಶೂನ್ಯ * pvParams );
ಸ್ಥಿರ ಶೂನ್ಯ prvSwitchThread( Thread_t * xThreadToResume,
                             Thread_t * xThreadToSuspend );
ಸ್ಥಿರ ಶೂನ್ಯ prvSuspendSelf( Thread_t * thread );
ಸ್ಥಿರ ಶೂನ್ಯ prvResumeThread( Thread_t * xThreadId );
ಸ್ಥಿರ ಶೂನ್ಯ vPortSystemTickHandler( ಪೂರ್ಣಾಙ್ಕ sig );
ಸ್ಥಿರ ಶೂನ್ಯ vPortStartFirstTask( ಶೂನ್ಯ );
ಸ್ಥಿರ ಶೂನ್ಯ prvPortYieldFromISR( ಶೂನ್ಯ );
ಸ್ಥಿರ ಶೂನ್ಯ prv_Thread_ಕೀಲಿ_Destructor( ಶೂನ್ಯ * pvData );
ಸ್ಥಿರ ಶೂನ್ಯ prv_Init_Thread_ಕೀಲಿ( ಶೂನ್ಯ );
ಸ್ಥಿರ ಶೂನ್ಯ prvMarkAsFreeRTOSThread( ಶೂನ್ಯ );
ಸ್ಥಿರ BaseType_t prvIsFreeRTOSThread( ಶೂನ್ಯ );
ಸ್ಥಿರ ಶೂನ್ಯ prv_Destroy_Thread_ಕೀಲಿ( ಶೂನ್ಯ );
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_Thread_ಕೀಲಿ_Destructor( ಶೂನ್ಯ * pvData )
{
    ಮುಕ್ತ( pvData );
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_Init_Thread_ಕೀಲಿ( ಶೂನ್ಯ )
{
    pthread_key_create( &x_Thread_ಕೀಲಿ, prv_Thread_ಕೀಲಿ_Destructor );
    /* Destroy xThreadKey when the process exits. */
    atexit( prv_Destroy_Thread_ಕೀಲಿ );
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvMarkAsFreeRTOSThread( ಶೂನ್ಯ )
{
    uint8_t * pucThreadData = ರಿಕ್ತ;

    ( ಶೂನ್ಯ ) pthread_once( &h_Thread_ಕೀಲಿ_Once, prv_Init_Thread_ಕೀಲಿ );

    pucThreadData = malloc( 1 );
    configASSERT( pucThreadData != ರಿಕ್ತ );

    *pucThreadData = 1;

    pthread_setspecific( x_Thread_ಕೀಲಿ, pucThreadData );
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ BaseType_t prvIsFreeRTOSThread( ಶೂನ್ಯ )
{
    uint8_t * pucThreadData = ರಿಕ್ತ;
    BaseType_t xRet = pdFALSE;

    ( ಶೂನ್ಯ ) pthread_once( &h_Thread_ಕೀಲಿ_Once, prv_Init_Thread_ಕೀಲಿ );

    pucThreadData = ( uint8_t * ) pthread_getspecific( x_Thread_ಕೀಲಿ );

    ಯದಿ( ( pucThreadData != ರಿಕ್ತ ) && ( *pucThreadData == 1 ) )
    {
        xRet = pdTRUE;
    }

    ಪ್ರತ್ಯಾಗಮ xRet;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_Destroy_Thread_ಕೀಲಿ( ಶೂನ್ಯ )
{
    pthread_key_delete( x_Thread_ಕೀಲಿ );
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvFatalError( ಧ್ರುವ ವರ್ಣ * pcCall,
                           ಪೂರ್ಣಾಙ್ಕ iErrno ) __attribute__( ( __noreturn__ ) );

ಶೂನ್ಯ prvFatalError( ಧ್ರುವ ವರ್ಣ * pcCall,
                    ಪೂರ್ಣಾಙ್ಕ iErrno )
{
    fprintf( stderr, "%s: %s\n", pcCall, strerror( iErrno ) );
    abort();
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvPortSetCurrentThreadName( ಧ್ರುವ ವರ್ಣ * pxThreadName )
{
    #ifdef __APPLE__
        pthread_setname_np( pxThreadName );
    #ಅನ್ಯಥಾ
        pthread_setname_np( pthread_self(), pxThreadName );
    #endif
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_Port_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_Of_ರಾಶಿ,
                                     ರಾಶಿ_Type_t * px_End_Of_ರಾಶಿ,
                                     TaskFunction_t pxCode,
                                     ಶೂನ್ಯ * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t xThreadAttributes;
    size_t ul_ರಾಶಿ_Size;
    ಪೂರ್ಣಾಙ್ಕ iRet;

    ( ಶೂನ್ಯ ) pthread_once( &hSigSetupThread, prvSetupSignalsAndSchedulerPolicy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_ತುದಿ_Of_ರಾಶಿ + 1 ) - 1;
    px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_ರಾಶಿ_Size = ( size_t ) ( px_ತುದಿ_Of_ರಾಶಿ + 1 - px_End_Of_ರಾಶಿ ) * ಪರಿಮಾಣ( *px_ತುದಿ_Of_ರಾಶಿ );
    configASSERT( ul_ರಾಶಿ_Size > ಪರಿಮಾಣ( Thread_t ) );
    ( ಶೂನ್ಯ ) ul_ರಾಶಿ_Size; /* suppress set but not used warning */

    thread->pxCode = pxCode;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &xThreadAttributes );

    thread->ev = event_create();

    vPortEnterCritical();

    iRet = pthread_create( &thread->pthread, &xThreadAttributes,
                           prvWaitForStart, thread );

    ಯದಿ( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    vPortExitCritical();

    ಪ್ರತ್ಯಾಗಮ px_ತುದಿ_Of_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortStartFirstTask( ಶೂನ್ಯ )
{
    Thread_t * pxFirstThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( pxFirstThread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( ಶೂನ್ಯ )
{
    ಪೂರ್ಣಾಙ್ಕ iSignal;
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
    ( ಶೂನ್ಯ ) pthread_sigmask( SIG_BLOCK, &xSignals, ರಿಕ್ತ );

    /* Start the first task. */
    vPortStartFirstTask();

    /* Wait until signaled by vPortEndScheduler(). */
    ಯಾವತ್( xSchedulerEnd != pdTRUE )
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
    #ಯದಿ __APPLE__
        hSigSetupThread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_ಕೀಲಿ_Once.__sig = _PTHREAD_ONCE_SIG_init;
        memset( ( ಶೂನ್ಯ * ) &hSigSetupThread.__opaque, 0, ಪರಿಮಾಣ( hSigSetupThread.__opaque ) );
        memset( ( ಶೂನ್ಯ * ) &h_Thread_ಕೀಲಿ_Once.__opaque, 0, ಪರಿಮಾಣ( h_Thread_ಕೀಲಿ_Once.__opaque ) );
    #ಅನ್ಯಥಾ /* Linux PTHREAD library*/
        hSigSetupThread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_ಕೀಲಿ_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #endif /* __APPLE__*/

    /* Restore original signal mask. */
    ( ಶೂನ್ಯ ) pthread_sigmask( SIG_SETMASK, &xSchedulerOriginalSignalMask, ರಿಕ್ತ );

    ಪ್ರತ್ಯಾಗಮ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEndScheduler( ಶೂನ್ಯ )
{
    Thread_t * pxCurrentThread;
    BaseType_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    xTimerTickThreadShouldRun = false;
    pthread_join( hTimerTickThread, ರಿಕ್ತ );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    xSchedulerEnd = pdTRUE;
    ( ಶೂನ್ಯ ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    ಯದಿ( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEnterCritical( ಶೂನ್ಯ )
{
    ಯದಿ( uxCriticalNesting == 0 )
    {
        vPortDisableInterrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortExitCritical( ಶೂನ್ಯ )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    ಯದಿ( uxCriticalNesting == 0 )
    {
        vPortEnableInterrupts();
    }
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvPortYieldFromISR( ಶೂನ್ಯ )
{
    Thread_t * xThreadToSuspend;
    Thread_t * xThreadToResume;

    xThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    xThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( xThreadToResume, xThreadToSuspend );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortYield( ಶೂನ್ಯ )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    vPortEnterCritical();

    prvPortYieldFromISR();

    vPortExitCritical();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortDisableInterrupts( ಶೂನ್ಯ )
{
    ಯದಿ( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &xAllSignals, ರಿಕ್ತ );
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortEnableInterrupts( ಶೂನ್ಯ )
{
    ಯದಿ( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &xAllSignals, ರಿಕ್ತ );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t xPortSetInterruptMask( ಶೂನ್ಯ )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    ಪ್ರತ್ಯಾಗಮ ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortClearInterruptMask( UBaseType_t uxMask )
{
    ( ಶೂನ್ಯ ) uxMask;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ uint64_t prvGetTimeNs( ಶೂನ್ಯ )
{
    ಸಂರಚನಾ timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    ಪ್ರತ್ಯಾಗಮ ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

ಸ್ಥಿರ ಶೂನ್ಯ * prvTimerTickHandler( ಶೂನ್ಯ * arg )
{
    ( ಶೂನ್ಯ ) arg;

    prvMarkAsFreeRTOSThread();

    prvPortSetCurrentThreadName( "Scheduler timer" );

    ಯಾವತ್( xTimerTickThreadShouldRun )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( portTICK_RATE_MICROSECONDS );
    }

    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
ಶೂನ್ಯ prvSetupTimerInterrupt( ಶೂನ್ಯ )
{
    xTimerTickThreadShouldRun = true;
    pthread_create( &hTimerTickThread, ರಿಕ್ತ, prvTimerTickHandler, ರಿಕ್ತ );

    prvStartTimeNs = prvGetTimeNs();
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ vPortSystemTickHandler( ಪೂರ್ಣಾಙ್ಕ sig )
{
    ಯದಿ( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * pxThreadToSuspend;
        Thread_t * pxThreadToResume;

        ( ಶೂನ್ಯ ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        pxThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        ಯದಿ( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            pxThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( pxThreadToResume, pxThreadToSuspend );
        }

        uxCriticalNesting--;
    }
    ಅನ್ಯಥಾ
    {
        fprintf( stderr, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortThreadDying( ಶೂನ್ಯ * pxTaskToDelete,
                       ಚಞ್ಚಲ BaseType_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( pxTaskToDelete );

    ( ಶೂನ್ಯ ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vPortCancelThread( ಶೂನ್ಯ * pxTaskToDelete )
{
    Thread_t * pxThreadToCancel = prvGetThreadFromTask( pxTaskToDelete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( pxThreadToCancel->pthread );
    event_signal( pxThreadToCancel->ev );
    pthread_join( pxThreadToCancel->pthread, ರಿಕ್ತ );
    event_delete( pxThreadToCancel->ev );
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ * prvWaitForStart( ಶೂನ್ಯ * pvParams )
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

    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvSwitchThread( Thread_t * pxThreadToResume,
                             Thread_t * pxThreadToSuspend )
{
    BaseType_t uxSavedCriticalNesting;

    ಯದಿ( pxThreadToSuspend != pxThreadToResume )
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

        ಯದಿ( pxThreadToSuspend->xDying == pdTRUE )
        {
            pthread_exit( ರಿಕ್ತ );
        }

        prvSuspendSelf( pxThreadToSuspend );

        uxCriticalNesting = uxSavedCriticalNesting;
    }
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvSuspendSelf( Thread_t * thread )
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

ಸ್ಥಿರ ಶೂನ್ಯ prvResumeThread( Thread_t * xThreadId )
{
    ಯದಿ( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvSetupSignalsAndSchedulerPolicy( ಶೂನ್ಯ )
{
    ಸಂರಚನಾ sigaction sigtick;
    ಪೂರ್ಣಾಙ್ಕ iRet;

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
    ( ಶೂನ್ಯ ) pthread_sigmask( SIG_SETMASK,
                              &xAllSignals,
                              &xSchedulerOriginalSignalMask );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = vPortSystemTickHandler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, ರಿಕ್ತ );

    ಯದಿ( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ulPortGetRunTime( ಶೂನ್ಯ )
{
    ಸಂರಚನಾ tms xTimes;

    times( &xTimes );

    ಪ್ರತ್ಯಾಗಮ ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
