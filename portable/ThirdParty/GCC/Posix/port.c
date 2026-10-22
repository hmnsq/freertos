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
#ଅନ୍ତର୍ଭାଵ "portmacro.h"
#ଅନ୍ତର୍ଭାଵ <errno.h>
#ଅନ୍ତର୍ଭାଵ <pthread.h>
#ଅନ୍ତର୍ଭାଵ <limits.h>
#ଅନ୍ତର୍ଭାଵ <signal.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ <sys/time.h>
#ଅନ୍ତର୍ଭାଵ <sys/times.h>
#ଅନ୍ତର୍ଭାଵ <time.h>
#ଅନ୍ତର୍ଭାଵ <unistd.h>

/* Scheduler includes. */
#ଅନ୍ତର୍ଭାଵ "FreeRTOS.h"
#ଅନ୍ତର୍ଭାଵ "task.h"
#ଅନ୍ତର୍ଭାଵ "timers.h"
#ଅନ୍ତର୍ଭାଵ "utils/wait_for_event.h"
/*-----------------------------------------------------------*/

#define SIG_RESUME    SIGUSR1

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା THREAD
{
    pthread_t pthread;
    TaskFunction_t pxCode;
    ଶୂନ୍ୟ * pvParams;
    BaseType_t xDying;
    ସଂରଚନା event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
ସ୍ଥିର ଧାଡ଼ିଭିତରେ Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    ଗଦା_Type_t * px_ଶୀର୍ଷ_Of_ଗଦା = *( ଗଦା_Type_t ** ) xTask;

    ଫେରନ୍ତୁ ( Thread_t * ) ( px_ଶୀର୍ଷ_Of_ଗଦା + 1 );
}

/*-----------------------------------------------------------*/

ସ୍ଥିର pthread_once_t hSigSetupThread = PTHREAD_ONCE_INIT;
ସ୍ଥିର pthread_once_t h_Thread_ଚାବି_Once = PTHREAD_ONCE_INIT;
ସ୍ଥିର sigset_t xAllSignals;
ସ୍ଥିର sigset_t xSchedulerOriginalSignalMask;
ସ୍ଥିର pthread_t hMainThread = ( pthread_t ) ଖାଲି;
ସ୍ଥିର ଅସ୍ଥିର BaseType_t uxCriticalNesting;
ସ୍ଥିର BaseType_t xSchedulerEnd = pdFALSE;
ସ୍ଥିର pthread_t hTimerTickThread;
ସ୍ଥିର bool xTimerTickThreadShouldRun;
ସ୍ଥିର uint64_t prvStartTimeNs;
ସ୍ଥିର pthread_key_t x_Thread_ଚାବି = 0;
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvSetupSignalsAndSchedulerPolicy( ଶୂନ୍ୟ );
ସ୍ଥିର ଶୂନ୍ୟ prvSetupTimerInterrupt( ଶୂନ୍ୟ );
ସ୍ଥିର ଶୂନ୍ୟ * prvWaitForStart( ଶୂନ୍ୟ * pvParams );
ସ୍ଥିର ଶୂନ୍ୟ prvSwitchThread( Thread_t * xThreadToResume,
                             Thread_t * xThreadToSuspend );
ସ୍ଥିର ଶୂନ୍ୟ prvSuspendSelf( Thread_t * thread );
ସ୍ଥିର ଶୂନ୍ୟ prvResumeThread( Thread_t * xThreadId );
ସ୍ଥିର ଶୂନ୍ୟ vPortSystemTickHandler( ପୂର୍ଣ୍ଣସଂଖ୍ୟା sig );
ସ୍ଥିର ଶୂନ୍ୟ vPortStartFirstTask( ଶୂନ୍ୟ );
ସ୍ଥିର ଶୂନ୍ୟ prvPortYieldFromISR( ଶୂନ୍ୟ );
ସ୍ଥିର ଶୂନ୍ୟ prv_Thread_ଚାବି_Destructor( ଶୂନ୍ୟ * pvData );
ସ୍ଥିର ଶୂନ୍ୟ prv_Init_Thread_ଚାବି( ଶୂନ୍ୟ );
ସ୍ଥିର ଶୂନ୍ୟ prvMarkAsFreeRTOSThread( ଶୂନ୍ୟ );
ସ୍ଥିର BaseType_t prvIsFreeRTOSThread( ଶୂନ୍ୟ );
ସ୍ଥିର ଶୂନ୍ୟ prv_Destroy_Thread_ଚାବି( ଶୂନ୍ୟ );
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prv_Thread_ଚାବି_Destructor( ଶୂନ୍ୟ * pvData )
{
    ମୁକ୍ତ( pvData );
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prv_Init_Thread_ଚାବି( ଶୂନ୍ୟ )
{
    pthread_key_create( &x_Thread_ଚାବି, prv_Thread_ଚାବି_Destructor );
    /* Destroy xThreadKey when the process exits. */
    atexit( prv_Destroy_Thread_ଚାବି );
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvMarkAsFreeRTOSThread( ଶୂନ୍ୟ )
{
    uint8_t * pucThreadData = ଖାଲି;

    ( ଶୂନ୍ୟ ) pthread_once( &h_Thread_ଚାବି_Once, prv_Init_Thread_ଚାବି );

    pucThreadData = malloc( 1 );
    configASSERT( pucThreadData != ଖାଲି );

    *pucThreadData = 1;

    pthread_setspecific( x_Thread_ଚାବି, pucThreadData );
}
/*-----------------------------------------------------------*/

ସ୍ଥିର BaseType_t prvIsFreeRTOSThread( ଶୂନ୍ୟ )
{
    uint8_t * pucThreadData = ଖାଲି;
    BaseType_t xRet = pdFALSE;

    ( ଶୂନ୍ୟ ) pthread_once( &h_Thread_ଚାବି_Once, prv_Init_Thread_ଚାବି );

    pucThreadData = ( uint8_t * ) pthread_getspecific( x_Thread_ଚାବି );

    ଯଦି( ( pucThreadData != ଖାଲି ) && ( *pucThreadData == 1 ) )
    {
        xRet = pdTRUE;
    }

    ଫେରନ୍ତୁ xRet;
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prv_Destroy_Thread_ଚାବି( ଶୂନ୍ୟ )
{
    pthread_key_delete( x_Thread_ଚାବି );
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvFatalError( ଅଚଳ ଅକ୍ଷର * pcCall,
                           ପୂର୍ଣ୍ଣସଂଖ୍ୟା iErrno ) __attribute__( ( __noreturn__ ) );

ଶୂନ୍ୟ prvFatalError( ଅଚଳ ଅକ୍ଷର * pcCall,
                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା iErrno )
{
    fprintf( stderr, "%s: %s\n", pcCall, strerror( iErrno ) );
    abort();
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvPortSetCurrentThreadName( ଅଚଳ ଅକ୍ଷର * pxThreadName )
{
    #ifdef __APPLE__
        pthread_setname_np( pxThreadName );
    #ଅନ୍ୟଥା
        pthread_setname_np( pthread_self(), pxThreadName );
    #endif
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ଗଦା_Type_t * px_Port_Initialise_ଗଦା( ଗଦା_Type_t * px_ଶୀର୍ଷ_Of_ଗଦା,
                                     ଗଦା_Type_t * px_End_Of_ଗଦା,
                                     TaskFunction_t pxCode,
                                     ଶୂନ୍ୟ * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t xThreadAttributes;
    size_t ul_ଗଦା_Size;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା iRet;

    ( ଶୂନ୍ୟ ) pthread_once( &hSigSetupThread, prvSetupSignalsAndSchedulerPolicy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_ଶୀର୍ଷ_Of_ଗଦା + 1 ) - 1;
    px_ଶୀର୍ଷ_Of_ଗଦା = ( ଗଦା_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_ଗଦା_Size = ( size_t ) ( px_ଶୀର୍ଷ_Of_ଗଦା + 1 - px_End_Of_ଗଦା ) * ଆକାର( *px_ଶୀର୍ଷ_Of_ଗଦା );
    configASSERT( ul_ଗଦା_Size > ଆକାର( Thread_t ) );
    ( ଶୂନ୍ୟ ) ul_ଗଦା_Size; /* suppress set but not used warning */

    thread->pxCode = pxCode;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &xThreadAttributes );

    thread->ev = event_create();

    vPortEnterCritical();

    iRet = pthread_create( &thread->pthread, &xThreadAttributes,
                           prvWaitForStart, thread );

    ଯଦି( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    vPortExitCritical();

    ଫେରନ୍ତୁ px_ଶୀର୍ଷ_Of_ଗଦା;
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortStartFirstTask( ଶୂନ୍ୟ )
{
    Thread_t * pxFirstThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( pxFirstThread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( ଶୂନ୍ୟ )
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା iSignal;
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
    ( ଶୂନ୍ୟ ) pthread_sigmask( SIG_BLOCK, &xSignals, ଖାଲି );

    /* Start the first task. */
    vPortStartFirstTask();

    /* Wait until signaled by vPortEndScheduler(). */
    ଯେତେବେଳେ( xSchedulerEnd != pdTRUE )
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
    #ଯଦି __APPLE__
        hSigSetupThread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_ଚାବି_Once.__sig = _PTHREAD_ONCE_SIG_init;
        memset( ( ଶୂନ୍ୟ * ) &hSigSetupThread.__opaque, 0, ଆକାର( hSigSetupThread.__opaque ) );
        memset( ( ଶୂନ୍ୟ * ) &h_Thread_ଚାବି_Once.__opaque, 0, ଆକାର( h_Thread_ଚାବି_Once.__opaque ) );
    #ଅନ୍ୟଥା /* Linux PTHREAD library*/
        hSigSetupThread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_ଚାବି_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #endif /* __APPLE__*/

    /* Restore original signal mask. */
    ( ଶୂନ୍ୟ ) pthread_sigmask( SIG_SETMASK, &xSchedulerOriginalSignalMask, ଖାଲି );

    ଫେରନ୍ତୁ 0;
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortEndScheduler( ଶୂନ୍ୟ )
{
    Thread_t * pxCurrentThread;
    BaseType_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    xTimerTickThreadShouldRun = false;
    pthread_join( hTimerTickThread, ଖାଲି );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    xSchedulerEnd = pdTRUE;
    ( ଶୂନ୍ୟ ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    ଯଦି( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortEnterCritical( ଶୂନ୍ୟ )
{
    ଯଦି( uxCriticalNesting == 0 )
    {
        vPortDisableInterrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortExitCritical( ଶୂନ୍ୟ )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    ଯଦି( uxCriticalNesting == 0 )
    {
        vPortEnableInterrupts();
    }
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvPortYieldFromISR( ଶୂନ୍ୟ )
{
    Thread_t * xThreadToSuspend;
    Thread_t * xThreadToResume;

    xThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    xThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( xThreadToResume, xThreadToSuspend );
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortYield( ଶୂନ୍ୟ )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    vPortEnterCritical();

    prvPortYieldFromISR();

    vPortExitCritical();
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortDisableInterrupts( ଶୂନ୍ୟ )
{
    ଯଦି( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &xAllSignals, ଖାଲି );
    }
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortEnableInterrupts( ଶୂନ୍ୟ )
{
    ଯଦି( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &xAllSignals, ଖାଲି );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t xPortSetInterruptMask( ଶୂନ୍ୟ )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    ଫେରନ୍ତୁ ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortClearInterruptMask( UBaseType_t uxMask )
{
    ( ଶୂନ୍ୟ ) uxMask;
}
/*-----------------------------------------------------------*/

ସ୍ଥିର uint64_t prvGetTimeNs( ଶୂନ୍ୟ )
{
    ସଂରଚନା timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    ଫେରନ୍ତୁ ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

ସ୍ଥିର ଶୂନ୍ୟ * prvTimerTickHandler( ଶୂନ୍ୟ * arg )
{
    ( ଶୂନ୍ୟ ) arg;

    prvMarkAsFreeRTOSThread();

    prvPortSetCurrentThreadName( "Scheduler timer" );

    ଯେତେବେଳେ( xTimerTickThreadShouldRun )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( portTICK_RATE_MICROSECONDS );
    }

    ଫେରନ୍ତୁ ଖାଲି;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
ଶୂନ୍ୟ prvSetupTimerInterrupt( ଶୂନ୍ୟ )
{
    xTimerTickThreadShouldRun = true;
    pthread_create( &hTimerTickThread, ଖାଲି, prvTimerTickHandler, ଖାଲି );

    prvStartTimeNs = prvGetTimeNs();
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ vPortSystemTickHandler( ପୂର୍ଣ୍ଣସଂଖ୍ୟା sig )
{
    ଯଦି( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * pxThreadToSuspend;
        Thread_t * pxThreadToResume;

        ( ଶୂନ୍ୟ ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        pxThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        ଯଦି( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            pxThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( pxThreadToResume, pxThreadToSuspend );
        }

        uxCriticalNesting--;
    }
    ଅନ୍ୟଥା
    {
        fprintf( stderr, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortThreadDying( ଶୂନ୍ୟ * pxTaskToDelete,
                       ଅସ୍ଥିର BaseType_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( pxTaskToDelete );

    ( ଶୂନ୍ୟ ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

ଶୂନ୍ୟ vPortCancelThread( ଶୂନ୍ୟ * pxTaskToDelete )
{
    Thread_t * pxThreadToCancel = prvGetThreadFromTask( pxTaskToDelete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( pxThreadToCancel->pthread );
    event_signal( pxThreadToCancel->ev );
    pthread_join( pxThreadToCancel->pthread, ଖାଲି );
    event_delete( pxThreadToCancel->ev );
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ * prvWaitForStart( ଶୂନ୍ୟ * pvParams )
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

    ଫେରନ୍ତୁ ଖାଲି;
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvSwitchThread( Thread_t * pxThreadToResume,
                             Thread_t * pxThreadToSuspend )
{
    BaseType_t uxSavedCriticalNesting;

    ଯଦି( pxThreadToSuspend != pxThreadToResume )
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

        ଯଦି( pxThreadToSuspend->xDying == pdTRUE )
        {
            pthread_exit( ଖାଲି );
        }

        prvSuspendSelf( pxThreadToSuspend );

        uxCriticalNesting = uxSavedCriticalNesting;
    }
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvSuspendSelf( Thread_t * thread )
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

ସ୍ଥିର ଶୂନ୍ୟ prvResumeThread( Thread_t * xThreadId )
{
    ଯଦି( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

ସ୍ଥିର ଶୂନ୍ୟ prvSetupSignalsAndSchedulerPolicy( ଶୂନ୍ୟ )
{
    ସଂରଚନା sigaction sigtick;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା iRet;

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
    ( ଶୂନ୍ୟ ) pthread_sigmask( SIG_SETMASK,
                              &xAllSignals,
                              &xSchedulerOriginalSignalMask );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = vPortSystemTickHandler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, ଖାଲି );

    ଯଦି( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ulPortGetRunTime( ଶୂନ୍ୟ )
{
    ସଂରଚନା tms xTimes;

    times( &xTimes );

    ଫେରନ୍ତୁ ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
