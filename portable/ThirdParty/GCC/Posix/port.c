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
#अन्तर्भाव "portmacro.h"
#अन्तर्भाव <errno.h>
#अन्तर्भाव <pthread.h>
#अन्तर्भाव <limits.h>
#अन्तर्भाव <signal.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <sys/time.h>
#अन्तर्भाव <sys/times.h>
#अन्तर्भाव <time.h>
#अन्तर्भाव <unistd.h>

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"
#अन्तर्भाव "timers.h"
#अन्तर्भाव "utils/wait_for_event.h"
/*-----------------------------------------------------------*/

#define SIG_RESUME    SIGUSR1

प्रकारनिर्देश संरचना THREAD
{
    pthread_t pthread;
    TaskFunction_t pxCode;
    शून्य * pvParams;
    BaseType_t xDying;
    संरचना event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
स्थिर अन्तःस्थ Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    ढेर_Type_t * px_शीर्ष_Of_ढेर = *( ढेर_Type_t ** ) xTask;

    प्रत्यागम ( Thread_t * ) ( px_शीर्ष_Of_ढेर + 1 );
}

/*-----------------------------------------------------------*/

स्थिर pthread_once_t hSigSetupThread = PTHREAD_ONCE_INIT;
स्थिर pthread_once_t h_Thread_कुंजी_Once = PTHREAD_ONCE_INIT;
स्थिर sigset_t xAllSignals;
स्थिर sigset_t xSchedulerOriginalSignalMask;
स्थिर pthread_t hMainThread = ( pthread_t ) रिक्त;
स्थिर चञ्चल BaseType_t uxCriticalNesting;
स्थिर BaseType_t xSchedulerEnd = pdFALSE;
स्थिर pthread_t hTimerTickThread;
स्थिर bool xTimerTickThreadShouldRun;
स्थिर uint64_t prvStartTimeNs;
स्थिर pthread_key_t x_Thread_कुंजी = 0;
/*-----------------------------------------------------------*/

स्थिर शून्य prvSetupSignalsAndSchedulerPolicy( शून्य );
स्थिर शून्य prvSetupTimerInterrupt( शून्य );
स्थिर शून्य * prvWaitForStart( शून्य * pvParams );
स्थिर शून्य prvSwitchThread( Thread_t * xThreadToResume,
                             Thread_t * xThreadToSuspend );
स्थिर शून्य prvSuspendSelf( Thread_t * thread );
स्थिर शून्य prvResumeThread( Thread_t * xThreadId );
स्थिर शून्य vPortSystemTickHandler( पूर्णाङ्क sig );
स्थिर शून्य vPortStartFirstTask( शून्य );
स्थिर शून्य prvPortYieldFromISR( शून्य );
स्थिर शून्य prv_Thread_कुंजी_Destructor( शून्य * pvData );
स्थिर शून्य prv_Init_Thread_कुंजी( शून्य );
स्थिर शून्य prvMarkAsFreeRTOSThread( शून्य );
स्थिर BaseType_t prvIsFreeRTOSThread( शून्य );
स्थिर शून्य prv_Destroy_Thread_कुंजी( शून्य );
/*-----------------------------------------------------------*/

स्थिर शून्य prv_Thread_कुंजी_Destructor( शून्य * pvData )
{
    मुक्त( pvData );
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_Init_Thread_कुंजी( शून्य )
{
    pthread_key_create( &x_Thread_कुंजी, prv_Thread_कुंजी_Destructor );
    /* Destroy xThreadKey when the process exits. */
    निकास_पर( prv_Destroy_Thread_कुंजी );
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvMarkAsFreeRTOSThread( शून्य )
{
    uint8_t * pucThreadData = रिक्त;

    ( शून्य ) pthread_once( &h_Thread_कुंजी_Once, prv_Init_Thread_कुंजी );

    pucThreadData = दो_स्मृति( 1 );
    configASSERT( pucThreadData != रिक्त );

    *pucThreadData = 1;

    pthread_setspecific( x_Thread_कुंजी, pucThreadData );
}
/*-----------------------------------------------------------*/

स्थिर BaseType_t prvIsFreeRTOSThread( शून्य )
{
    uint8_t * pucThreadData = रिक्त;
    BaseType_t xRet = pdFALSE;

    ( शून्य ) pthread_once( &h_Thread_कुंजी_Once, prv_Init_Thread_कुंजी );

    pucThreadData = ( uint8_t * ) pthread_getspecific( x_Thread_कुंजी );

    यदि( ( pucThreadData != रिक्त ) && ( *pucThreadData == 1 ) )
    {
        xRet = pdTRUE;
    }

    प्रत्यागम xRet;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_Destroy_Thread_कुंजी( शून्य )
{
    pthread_key_delete( x_Thread_कुंजी );
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvFatalError( ध्रुव वर्ण * pcCall,
                           पूर्णाङ्क iErrno ) __attribute__( ( __noreturn__ ) );

शून्य prvFatalError( ध्रुव वर्ण * pcCall,
                    पूर्णाङ्क iErrno )
{
    ख_लिखो( मानक_त्रुटि, "%s: %s\n", pcCall, म_त्रुटि( iErrno ) );
    पात();
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvPortSetCurrentThreadName( ध्रुव वर्ण * pxThreadName )
{
    #ifdef __APPLE__
        pthread_setname_np( pxThreadName );
    #अन्यथा
        pthread_setname_np( pthread_self(), pxThreadName );
    #endif
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     ढेर_Type_t * px_End_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     शून्य * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t xThreadAttributes;
    माप_प्रकार ul_ढेर_Size;
    पूर्णाङ्क iRet;

    ( शून्य ) pthread_once( &hSigSetupThread, prvSetupSignalsAndSchedulerPolicy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_शीर्ष_Of_ढेर + 1 ) - 1;
    px_शीर्ष_Of_ढेर = ( ढेर_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_ढेर_Size = ( माप_प्रकार ) ( px_शीर्ष_Of_ढेर + 1 - px_End_Of_ढेर ) * परिमाण( *px_शीर्ष_Of_ढेर );
    configASSERT( ul_ढेर_Size > परिमाण( Thread_t ) );
    ( शून्य ) ul_ढेर_Size; /* suppress set but not used warning */

    thread->pxCode = pxCode;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &xThreadAttributes );

    thread->ev = event_create();

    vPortEnterCritical();

    iRet = pthread_create( &thread->pthread, &xThreadAttributes,
                           prvWaitForStart, thread );

    यदि( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    vPortExitCritical();

    प्रत्यागम px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

शून्य vPortStartFirstTask( शून्य )
{
    Thread_t * pxFirstThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( pxFirstThread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
BaseType_t xPortStartScheduler( शून्य )
{
    पूर्णाङ्क iSignal;
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
    ( शून्य ) pthread_sigmask( SIG_BLOCK, &xSignals, रिक्त );

    /* Start the first task. */
    vPortStartFirstTask();

    /* Wait until signaled by vPortEndScheduler(). */
    यावत्( xSchedulerEnd != pdTRUE )
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
    #यदि __APPLE__
        hSigSetupThread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_कुंजी_Once.__sig = _PTHREAD_ONCE_SIG_init;
        स_रखो( ( शून्य * ) &hSigSetupThread.__opaque, 0, परिमाण( hSigSetupThread.__opaque ) );
        स_रखो( ( शून्य * ) &h_Thread_कुंजी_Once.__opaque, 0, परिमाण( h_Thread_कुंजी_Once.__opaque ) );
    #अन्यथा /* Linux PTHREAD library*/
        hSigSetupThread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_कुंजी_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #endif /* __APPLE__*/

    /* Restore original signal mask. */
    ( शून्य ) pthread_sigmask( SIG_SETMASK, &xSchedulerOriginalSignalMask, रिक्त );

    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

शून्य vPortEndScheduler( शून्य )
{
    Thread_t * pxCurrentThread;
    BaseType_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    xTimerTickThreadShouldRun = false;
    pthread_join( hTimerTickThread, रिक्त );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    xSchedulerEnd = pdTRUE;
    ( शून्य ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    यदि( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

शून्य vPortEnterCritical( शून्य )
{
    यदि( uxCriticalNesting == 0 )
    {
        vPortDisableInterrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

शून्य vPortExitCritical( शून्य )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    यदि( uxCriticalNesting == 0 )
    {
        vPortEnableInterrupts();
    }
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvPortYieldFromISR( शून्य )
{
    Thread_t * xThreadToSuspend;
    Thread_t * xThreadToResume;

    xThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    xThreadToResume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( xThreadToResume, xThreadToSuspend );
}
/*-----------------------------------------------------------*/

शून्य vPortYield( शून्य )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    vPortEnterCritical();

    prvPortYieldFromISR();

    vPortExitCritical();
}
/*-----------------------------------------------------------*/

शून्य vPortDisableInterrupts( शून्य )
{
    यदि( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &xAllSignals, रिक्त );
    }
}
/*-----------------------------------------------------------*/

शून्य vPortEnableInterrupts( शून्य )
{
    यदि( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &xAllSignals, रिक्त );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t xPortSetInterruptMask( शून्य )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    प्रत्यागम ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

शून्य vPortClearInterruptMask( UBaseType_t uxMask )
{
    ( शून्य ) uxMask;
}
/*-----------------------------------------------------------*/

स्थिर uint64_t prvGetTimeNs( शून्य )
{
    संरचना timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    प्रत्यागम ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

स्थिर शून्य * prvTimerTickHandler( शून्य * arg )
{
    ( शून्य ) arg;

    prvMarkAsFreeRTOSThread();

    prvPortSetCurrentThreadName( "Scheduler timer" );

    यावत्( xTimerTickThreadShouldRun )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( portTICK_RATE_MICROSECONDS );
    }

    प्रत्यागम रिक्त;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
शून्य prvSetupTimerInterrupt( शून्य )
{
    xTimerTickThreadShouldRun = true;
    pthread_create( &hTimerTickThread, रिक्त, prvTimerTickHandler, रिक्त );

    prvStartTimeNs = prvGetTimeNs();
}
/*-----------------------------------------------------------*/

स्थिर शून्य vPortSystemTickHandler( पूर्णाङ्क sig )
{
    यदि( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * pxThreadToSuspend;
        Thread_t * pxThreadToResume;

        ( शून्य ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        pxThreadToSuspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        यदि( xTaskIncrementTick() != pdFALSE )
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

शून्य vPortThreadDying( शून्य * pxTaskToDelete,
                       चञ्चल BaseType_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( pxTaskToDelete );

    ( शून्य ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

शून्य vPortCancelThread( शून्य * pxTaskToDelete )
{
    Thread_t * pxThreadToCancel = prvGetThreadFromTask( pxTaskToDelete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( pxThreadToCancel->pthread );
    event_signal( pxThreadToCancel->ev );
    pthread_join( pxThreadToCancel->pthread, रिक्त );
    event_delete( pxThreadToCancel->ev );
}
/*-----------------------------------------------------------*/

स्थिर शून्य * prvWaitForStart( शून्य * pvParams )
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

    प्रत्यागम रिक्त;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvSwitchThread( Thread_t * pxThreadToResume,
                             Thread_t * pxThreadToSuspend )
{
    BaseType_t uxSavedCriticalNesting;

    यदि( pxThreadToSuspend != pxThreadToResume )
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

        यदि( pxThreadToSuspend->xDying == pdTRUE )
        {
            pthread_exit( रिक्त );
        }

        prvSuspendSelf( pxThreadToSuspend );

        uxCriticalNesting = uxSavedCriticalNesting;
    }
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvSuspendSelf( Thread_t * thread )
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

स्थिर शून्य prvResumeThread( Thread_t * xThreadId )
{
    यदि( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvSetupSignalsAndSchedulerPolicy( शून्य )
{
    संरचना sigaction sigtick;
    पूर्णाङ्क iRet;

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
    ( शून्य ) pthread_sigmask( SIG_SETMASK,
                              &xAllSignals,
                              &xSchedulerOriginalSignalMask );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = vPortSystemTickHandler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, रिक्त );

    यदि( iRet == -1 )
    {
        prvFatalError( "sigaction", त्रुटि_सं );
    }
}
/*-----------------------------------------------------------*/

uint32_t ulPortGetRunTime( शून्य )
{
    संरचना tms xTimes;

    बार( &xTimes );

    प्रत्यागम ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
