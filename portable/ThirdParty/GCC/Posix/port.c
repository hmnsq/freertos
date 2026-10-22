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
#अगर_घोषित __linux__
    #घोषणा _GNU_SOURCE
#पूर्ण_अगर
#समावेश "portmacro.h"
#समावेश <errno.h>
#समावेश <pthread.h>
#समावेश <limits.h>
#समावेश <signal.h>
#समावेश <stdio.h>
#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश <sys/time.h>
#समावेश <sys/times.h>
#समावेश <time.h>
#समावेश <unistd.h>

/* Scheduler includes. */
#समावेश "FreeRTOS.h"
#समावेश "task.h"
#समावेश "timers.h"
#समावेश "utils/wait_for_event.h"
/*-----------------------------------------------------------*/

#घोषणा SIG_RESUME    SIGUSR1

प्रकार काष्ठा THREAD
{
    pthread_t pthread;
    TaskFunction_t pxCode;
    व्योम * pvParams;
    BaseType_t xDying;
    काष्ठा event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
अटल अंतरभूत Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    ढेर_Type_t * px_शीर्ष_Of_ढेर = *( ढेर_Type_t ** ) xTask;

    वापस ( Thread_t * ) ( px_शीर्ष_Of_ढेर + 1 );
}

/*-----------------------------------------------------------*/

अटल pthread_once_t hSigSetupThread = PTHREAD_ONCE_INIT;
अटल pthread_once_t h_Thread_कुंजी_Once = PTHREAD_ONCE_INIT;
अटल sigset_t xAllSignals;
अटल sigset_t xSchedulerOriginalSignalMask;
अटल pthread_t hMainThread = ( pthread_t ) शून्य;
अटल अस्थिर BaseType_t uxCriticalNesting;
अटल BaseType_t xSchedulerEnd = pdFALSE;
अटल pthread_t hTimerTickThread;
अटल bool xTimerTickThreadShouldRun;
अटल uint64_t prvStartTimeNs;
अटल pthread_key_t x_Thread_कुंजी = 0;
/*-----------------------------------------------------------*/

अटल व्योम prvSetupSignalsAndSchedulerPolicy( व्योम );
अटल व्योम prvSetupTimerInterrupt( व्योम );
अटल व्योम * prvWaitForStart( व्योम * pvParams );
अटल व्योम prvSwitchThread( Thread_t * xThreadToResume,
                             Thread_t * xThreadToSuspend );
अटल व्योम prvSuspendSelf( Thread_t * thread );
अटल व्योम prvResumeThread( Thread_t * xThreadId );
अटल व्योम vPortSystemTickHandler( पूर्णांक sig );
अटल व्योम vPortStartFirstTask( व्योम );
अटल व्योम prvPortYieldFromISR( व्योम );
अटल व्योम prv_Thread_कुंजी_Destructor( व्योम * pv_तथ्य );
अटल व्योम prv_Init_Thread_कुंजी( व्योम );
अटल व्योम prvMarkAsFreeRTOSThread( व्योम );
अटल BaseType_t prvIsFreeRTOSThread( व्योम );
अटल व्योम prv_Destroy_Thread_कुंजी( व्योम );
/*-----------------------------------------------------------*/

अटल व्योम prv_Thread_कुंजी_Destructor( व्योम * pv_तथ्य )
{
    मुक्त( pv_तथ्य );
}
/*-----------------------------------------------------------*/

अटल व्योम prv_Init_Thread_कुंजी( व्योम )
{
    pthread_key_create( &x_Thread_कुंजी, prv_Thread_कुंजी_Destructor );
    /* Destroy xThreadKey when the process exits. */
    निकास_पर( prv_Destroy_Thread_कुंजी );
}
/*-----------------------------------------------------------*/

अटल व्योम prvMarkAsFreeRTOSThread( व्योम )
{
    uint8_t * puc_Thread_तथ्य = शून्य;

    ( व्योम ) pthread_once( &h_Thread_कुंजी_Once, prv_Init_Thread_कुंजी );

    puc_Thread_तथ्य = दो_स्मृति( 1 );
    configASSERT( puc_Thread_तथ्य != शून्य );

    *puc_Thread_तथ्य = 1;

    pthread_setspecific( x_Thread_कुंजी, puc_Thread_तथ्य );
}
/*-----------------------------------------------------------*/

अटल BaseType_t prvIsFreeRTOSThread( व्योम )
{
    uint8_t * puc_Thread_तथ्य = शून्य;
    BaseType_t xRet = pdFALSE;

    ( व्योम ) pthread_once( &h_Thread_कुंजी_Once, prv_Init_Thread_कुंजी );

    puc_Thread_तथ्य = ( uint8_t * ) pthread_getspecific( x_Thread_कुंजी );

    अगर( ( puc_Thread_तथ्य != शून्य ) && ( *puc_Thread_तथ्य == 1 ) )
    {
        xRet = pdTRUE;
    }

    वापस xRet;
}
/*-----------------------------------------------------------*/

अटल व्योम prv_Destroy_Thread_कुंजी( व्योम )
{
    pthread_key_delete( x_Thread_कुंजी );
}
/*-----------------------------------------------------------*/

अटल व्योम prvFatalError( स्थिर अक्षर * pcCall,
                           पूर्णांक iErrno ) __attribute__( ( __noreturn__ ) );

व्योम prvFatalError( स्थिर अक्षर * pcCall,
                    पूर्णांक iErrno )
{
    ख_लिखो( मानक_त्रुटि, "%s: %s\n", pcCall, म_त्रुटि( iErrno ) );
    पात();
}
/*-----------------------------------------------------------*/

अटल व्योम prvPortSetCurrentThreadName( स्थिर अक्षर * pxThreadName )
{
    #अगर_घोषित __APPLE__
        pthread_setname_np( pxThreadName );
    #अन्यथा
        pthread_setname_np( pthread_self(), pxThreadName );
    #पूर्ण_अगर
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     ढेर_Type_t * px_End_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     व्योम * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t xThreadAttributes;
    माप_प्रकार ul_ढेर_आकार;
    पूर्णांक iRet;

    ( व्योम ) pthread_once( &hSigSetupThread, prvSetupSignalsAndSchedulerPolicy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_शीर्ष_Of_ढेर + 1 ) - 1;
    px_शीर्ष_Of_ढेर = ( ढेर_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_ढेर_आकार = ( माप_प्रकार ) ( px_शीर्ष_Of_ढेर + 1 - px_End_Of_ढेर ) * माप( *px_शीर्ष_Of_ढेर );
    configASSERT( ul_ढेर_आकार > माप( Thread_t ) );
    ( व्योम ) ul_ढेर_आकार; /* suppress set but not used warning */

    thread->pxCode = pxCode;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &xThreadAttributes );

    thread->ev = event_create();

    vPortEnterCritical();

    iRet = pthread_create( &thread->pthread, &xThreadAttributes,
                           prvWaitForStart, thread );

    अगर( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    vPortExitCritical();

    वापस px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

व्योम vPortStartFirstTask( व्योम )
{
    Thread_t * pxFirstThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( pxFirstThread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( व्योम )
{
    पूर्णांक iSignal;
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
    ( व्योम ) pthread_sigmask( SIG_BLOCK, &xSignals, शून्य );

    /* Start the first task. */
    vPortStartFirstTask();

    /* Wait until signaled by vPortEndScheduler(). */
    जबतक( xSchedulerEnd != pdTRUE )
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
    #अगर __APPLE__
        hSigSetupThread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_कुंजी_Once.__sig = _PTHREAD_ONCE_SIG_init;
        स_रखो( ( व्योम * ) &hSigSetupThread.__opaque, 0, माप( hSigSetupThread.__opaque ) );
        स_रखो( ( व्योम * ) &h_Thread_कुंजी_Once.__opaque, 0, माप( h_Thread_कुंजी_Once.__opaque ) );
    #अन्यथा /* Linux PTHREAD library*/
        hSigSetupThread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_कुंजी_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #पूर्ण_अगर /* __APPLE__*/

    /* Restore original signal mask. */
    ( व्योम ) pthread_sigmask( SIG_SETMASK, &xSchedulerOriginalSignalMask, शून्य );

    वापस 0;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    Thread_t * pxCurrentThread;
    BaseType_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    xTimerTickThreadShouldRun = false;
    pthread_join( hTimerTickThread, शून्य );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    xSchedulerEnd = pdTRUE;
    ( व्योम ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    अगर( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

व्योम vPortEnterCritical( व्योम )
{
    अगर( uxCriticalNesting == 0 )
    {
        vPortDisableInterrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

व्योम vPortExitCritical( व्योम )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    अगर( uxCriticalNesting == 0 )
    {
        vPortEnableInterrupts();
    }
}
/*-----------------------------------------------------------*/

अटल व्योम prvPortYieldFromISR( व्योम )
{
    Thread_t * xThreadToSuspend;
    Thread_t * xThreadToResume;

    xThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    xThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( xThreadToResume, xThreadToSuspend );
}
/*-----------------------------------------------------------*/

व्योम vPortYield( व्योम )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    vPortEnterCritical();

    prvPortYieldFromISR();

    vPortExitCritical();
}
/*-----------------------------------------------------------*/

व्योम vPortDisableInterrupts( व्योम )
{
    अगर( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &xAllSignals, शून्य );
    }
}
/*-----------------------------------------------------------*/

व्योम vPortEnableInterrupts( व्योम )
{
    अगर( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &xAllSignals, शून्य );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t xPortSetInterruptMask( व्योम )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    वापस ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

व्योम vPortClearInterruptMask( UBaseType_t uxMask )
{
    ( व्योम ) uxMask;
}
/*-----------------------------------------------------------*/

अटल uint64_t prvGetTimeNs( व्योम )
{
    काष्ठा timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    वापस ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

अटल व्योम * prvTimerTickHandler( व्योम * arg )
{
    ( व्योम ) arg;

    prvMarkAsFreeRTOSThread();

    prvPortSetCurrentThreadName( "Scheduler timer" );

    जबतक( xTimerTickThreadShouldRun )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( portTICK_RATE_MICROSECONDS );
    }

    वापस शून्य;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
व्योम prvSetupTimerInterrupt( व्योम )
{
    xTimerTickThreadShouldRun = true;
    pthread_create( &hTimerTickThread, शून्य, prvTimerTickHandler, शून्य );

    prvStartTimeNs = prvGetTimeNs();
}
/*-----------------------------------------------------------*/

अटल व्योम vPortSystemTickHandler( पूर्णांक sig )
{
    अगर( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * pxThreadToSuspend;
        Thread_t * pxThreadToResume;

        ( व्योम ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        pxThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        अगर( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            pxThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( pxThreadToResume, pxThreadToSuspend );
        }

        uxCriticalNesting--;
    }
    अन्यथा
    {
        ख_लिखो( मानक_त्रुटि, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

व्योम vPortThreadDying( व्योम * pxTaskToDelete,
                       अस्थिर BaseType_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( pxTaskToDelete );

    ( व्योम ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

व्योम vPortCancelThread( व्योम * pxTaskToDelete )
{
    Thread_t * pxThreadToCancel = prvGetThreadFromTask( pxTaskToDelete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( pxThreadToCancel->pthread );
    event_signal( pxThreadToCancel->ev );
    pthread_join( pxThreadToCancel->pthread, शून्य );
    event_delete( pxThreadToCancel->ev );
}
/*-----------------------------------------------------------*/

अटल व्योम * prvWaitForStart( व्योम * pvParams )
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

    वापस शून्य;
}
/*-----------------------------------------------------------*/

अटल व्योम prvSwitchThread( Thread_t * pxThreadToResume,
                             Thread_t * pxThreadToSuspend )
{
    BaseType_t uxSavedCriticalNesting;

    अगर( pxThreadToSuspend != pxThreadToResume )
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

        अगर( pxThreadToSuspend->xDying == pdTRUE )
        {
            pthread_exit( शून्य );
        }

        prvSuspendSelf( pxThreadToSuspend );

        uxCriticalNesting = uxSavedCriticalNesting;
    }
}
/*-----------------------------------------------------------*/

अटल व्योम prvSuspendSelf( Thread_t * thread )
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

अटल व्योम prvResumeThread( Thread_t * xThreadId )
{
    अगर( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

अटल व्योम prvSetupSignalsAndSchedulerPolicy( व्योम )
{
    काष्ठा sigaction sigtick;
    पूर्णांक iRet;

    hMainThread = pthread_self();

    /* Initialise common signal masks. */
    sigfillset( &xAllSignals );

    /* Don't block SIGINT so this can be used to break into GDB while
     * in a critical section. */
    sigdelset( &xAllSignals, संक_विघ्न );

    /*
     * Block all signals in this thread so all new threads
     * inherits this mask.
     *
     * When a thread is resumed for the first time, all signals
     * will be unblocked.
     */
    ( व्योम ) pthread_sigmask( SIG_SETMASK,
                              &xAllSignals,
                              &xSchedulerOriginalSignalMask );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = vPortSystemTickHandler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, शून्य );

    अगर( iRet == -1 )
    {
        prvFatalError( "sigaction", त्रुटि_सं );
    }
}
/*-----------------------------------------------------------*/

uint32_t ulPortGetRunTime( व्योम )
{
    काष्ठा tms xTimes;

    बार( &xTimes );

    वापस ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
