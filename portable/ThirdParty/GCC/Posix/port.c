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
#నిర్వచితమైతే __linux__
    #నిర్వచించు GNU_ఆధారం
#అయితే_ముగింపు
#అన్తర్భావ "portmacro.h"
#అన్తర్భావ <errno.h>
#అన్తర్భావ <pthread.h>
#అన్తర్భావ <limits.h>
#అన్తర్భావ <signal.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ <sys/time.h>
#అన్తర్భావ <sys/times.h>
#అన్తర్భావ <time.h>
#అన్తర్భావ <unistd.h>

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "timers.h"
#అన్తర్భావ "utils/wait_for_event.h"
/*-----------------------------------------------------------*/

#నిర్వచించు SIG_RESUME    SIGUSR1

రకనిర్వచనం నిర్మాణం THREAD
{
    pthread_t pthread;
    TaskFunction_t px_సంకేతం;
    శూన్య * pvParams;
    పునాది_Type_t xDying;
    నిర్మాణం event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
స్థిర అంతఃవరుస Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర = *( దొంతర_Type_t ** ) xTask;

    తిరిగి ( Thread_t * ) ( px_శిఖరం_యొక్క_దొంతర + 1 );
}

/*-----------------------------------------------------------*/

స్థిర pthread_once_t h_Sig_అమరిక_Thread = PTHREAD_ONCE_INIT;
స్థిర pthread_once_t h_Thread_కీలకం_Once = PTHREAD_ONCE_INIT;
స్థిర sigset_t x_All_సంకేతాలు;
స్థిర sigset_t x_Scheduler_Original_Signal_ముసుగు;
స్థిర pthread_t hMainThread = ( pthread_t ) ఖాళీ;
స్థిర అస్థిర పునాది_Type_t uxCriticalNesting;
స్థిర పునాది_Type_t x_Scheduler_చివర = pdFALSE;
స్థిర pthread_t hTimerTickThread;
స్థిర bool x_Timer_Tick_Thread_Should_నిరంతరం;
స్థిర uint64_t prv_ప్రారంభం_సమయం_Ns;
స్థిర pthread_key_t x_Thread_కీలకం = 0;
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_అమరిక_సంకేతాలు_And_Scheduler_Policy( శూన్య );
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య );
స్థిర శూన్య * prv_Wait_For_ప్రారంభం( శూన్య * pvParams );
స్థిర శూన్య prvSwitchThread( Thread_t * x_Thread_గమ్యం_Resume,
                             Thread_t * x_Thread_గమ్యం_Suspend );
స్థిర శూన్య prvSuspendSelf( Thread_t * thread );
స్థిర శూన్య prvResumeThread( Thread_t * xThreadId );
స్థిర శూన్య v_పోర్టు_System_Tick_Handler( పూర్ణాంకం sig );
స్థిర శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య );
స్థిర శూన్య prv_పోర్టు_Yield_From_ISR( శూన్య );
స్థిర శూన్య prv_Thread_కీలకం_Destructor( శూన్య * pv_దత్తాంశం );
స్థిర శూన్య prv_Init_Thread_కీలకం( శూన్య );
స్థిర శూన్య prvMarkAsFreeRTOSThread( శూన్య );
స్థిర పునాది_Type_t prvIsFreeRTOSThread( శూన్య );
స్థిర శూన్య prv_Destroy_Thread_కీలకం( శూన్య );
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_Thread_కీలకం_Destructor( శూన్య * pv_దత్తాంశం )
{
    విడుదల( pv_దత్తాంశం );
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_Init_Thread_కీలకం( శూన్య )
{
    pthread_key_create( &x_Thread_కీలకం, prv_Thread_కీలకం_Destructor );
    /* Destroy xThreadKey when the process exits. */
    atexit( prv_Destroy_Thread_కీలకం );
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prvMarkAsFreeRTOSThread( శూన్య )
{
    uint8_t * puc_Thread_దత్తాంశం = ఖాళీ;

    ( శూన్య ) pthread_once( &h_Thread_కీలకం_Once, prv_Init_Thread_కీలకం );

    puc_Thread_దత్తాంశం = జ్ఞాపకం_ఇవ్వు( 1 );
    configASSERT( puc_Thread_దత్తాంశం != ఖాళీ );

    *puc_Thread_దత్తాంశం = 1;

    pthread_setspecific( x_Thread_కీలకం, puc_Thread_దత్తాంశం );
}
/*-----------------------------------------------------------*/

స్థిర పునాది_Type_t prvIsFreeRTOSThread( శూన్య )
{
    uint8_t * puc_Thread_దత్తాంశం = ఖాళీ;
    పునాది_Type_t xRet = pdFALSE;

    ( శూన్య ) pthread_once( &h_Thread_కీలకం_Once, prv_Init_Thread_కీలకం );

    puc_Thread_దత్తాంశం = ( uint8_t * ) pthread_getspecific( x_Thread_కీలకం );

    ఒకవేళ( ( puc_Thread_దత్తాంశం != ఖాళీ ) && ( *puc_Thread_దత్తాంశం == 1 ) )
    {
        xRet = pdTRUE;
    }

    తిరిగి xRet;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_Destroy_Thread_కీలకం( శూన్య )
{
    pthread_key_delete( x_Thread_కీలకం );
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prvFatalError( స్థిరరాశి అక్షరం * pcCall,
                           పూర్ణాంకం iErrno ) __attribute__( ( __noreturn__ ) );

శూన్య prvFatalError( స్థిరరాశి అక్షరం * pcCall,
                    పూర్ణాంకం iErrno )
{
    fprintf( stderr, "%s: %s\n", pcCall, strerror( iErrno ) );
    abort();
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_పోర్టు_సమితి_Current_Thread_Name( స్థిరరాశి అక్షరం * pxThreadName )
{
    #నిర్వచితమైతే __APPLE__
        pthread_setname_np( pxThreadName );
    #లేకపోతే
        pthread_setname_np( pthread_self(), pxThreadName );
    #అయితే_ముగింపు
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     దొంతర_Type_t * px_చివర_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t x_Thread_లక్షణాలు;
    size_t ul_దొంతర_కొలత;
    పూర్ణాంకం iRet;

    ( శూన్య ) pthread_once( &h_Sig_అమరిక_Thread, prv_అమరిక_సంకేతాలు_And_Scheduler_Policy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_శిఖరం_యొక్క_దొంతర + 1 ) - 1;
    px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_దొంతర_కొలత = ( size_t ) ( px_శిఖరం_యొక్క_దొంతర + 1 - px_చివర_యొక్క_దొంతర ) * పరిమాణం( *px_శిఖరం_యొక్క_దొంతర );
    configASSERT( ul_దొంతర_కొలత > పరిమాణం( Thread_t ) );
    ( శూన్య ) ul_దొంతర_కొలత; /* suppress set but not used warning */

    thread->px_సంకేతం = px_సంకేతం;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &x_Thread_లక్షణాలు );

    thread->ev = event_create();

    v_పోర్టు_Enter_Critical();

    iRet = pthread_create( &thread->pthread, &x_Thread_లక్షణాలు,
                           prv_Wait_For_ప్రారంభం, thread );

    ఒకవేళ( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    v_పోర్టు_Exit_Critical();

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_ప్రారంభం_మొదటి_Task( శూన్య )
{
    Thread_t * px_మొదటి_Thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( px_మొదటి_Thread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    పూర్ణాంకం iSignal;
    sigset_t x_సంకేతాలు;

    hMainThread = pthread_self();
    prv_పోర్టు_సమితి_Current_Thread_Name( "Scheduler" );

    /* Start the timer that generates the tick ISR(SIGALRM).
     * Interrupts are disabled here already. */
    prv_అమరిక_Timer_అంతరాయం();

    /*
     * Block SIG_RESUME before starting any tasks so the main thread can sigwait on it.
     * To sigwait on an unblocked signal is undefined.
     * https://pubs.opengroup.org/onlinepubs/009604499/functions/sigwait.html
     */
    sigemptyset( &x_సంకేతాలు );
    sigaddset( &x_సంకేతాలు, SIG_RESUME );
    ( శూన్య ) pthread_sigmask( SIG_BLOCK, &x_సంకేతాలు, ఖాళీ );

    /* Start the first task. */
    v_పోర్టు_ప్రారంభం_మొదటి_Task();

    /* Wait until signaled by vPortEndScheduler(). */
    అయితే( x_Scheduler_చివర != pdTRUE )
    {
        sigwait( &x_సంకేతాలు, &iSignal );
    }

    /*
     * clear out the variable that is used to end the scheduler, otherwise
     * subsequent scheduler restarts will end immediately.
     */
    x_Scheduler_చివర = pdFALSE;

    /* Reset pthread_once_t, needed to restart the scheduler again.
     * memset the internal struct members for MacOS/Linux Compatibility */
    #ఒకవేళ __APPLE__
        h_Sig_అమరిక_Thread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_కీలకం_Once.__sig = _PTHREAD_ONCE_SIG_init;
        memset( ( శూన్య * ) &h_Sig_అమరిక_Thread.__opaque, 0, పరిమాణం( h_Sig_అమరిక_Thread.__opaque ) );
        memset( ( శూన్య * ) &h_Thread_కీలకం_Once.__opaque, 0, పరిమాణం( h_Thread_కీలకం_Once.__opaque ) );
    #లేకపోతే /* Linux PTHREAD library*/
        h_Sig_అమరిక_Thread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_కీలకం_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #అయితే_ముగింపు /* __APPLE__*/

    /* Restore original signal mask. */
    ( శూన్య ) pthread_sigmask( SIG_SETMASK, &x_Scheduler_Original_Signal_ముసుగు, ఖాళీ );

    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    Thread_t * pxCurrentThread;
    పునాది_Type_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    x_Timer_Tick_Thread_Should_నిరంతరం = false;
    pthread_join( hTimerTickThread, ఖాళీ );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    x_Scheduler_చివర = pdTRUE;
    ( శూన్య ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    ఒకవేళ( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    ఒకవేళ( uxCriticalNesting == 0 )
    {
        v_పోర్టు_Disable_Interrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    ఒకవేళ( uxCriticalNesting == 0 )
    {
        v_పోర్టు_Enable_Interrupts();
    }
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_పోర్టు_Yield_From_ISR( శూన్య )
{
    Thread_t * x_Thread_గమ్యం_Suspend;
    Thread_t * x_Thread_గమ్యం_Resume;

    x_Thread_గమ్యం_Suspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    x_Thread_గమ్యం_Resume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( x_Thread_గమ్యం_Resume, x_Thread_గమ్యం_Suspend );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Yield( శూన్య )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    v_పోర్టు_Enter_Critical();

    prv_పోర్టు_Yield_From_ISR();

    v_పోర్టు_Exit_Critical();
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Disable_Interrupts( శూన్య )
{
    ఒకవేళ( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &x_All_సంకేతాలు, ఖాళీ );
    }
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Enable_Interrupts( శూన్య )
{
    ఒకవేళ( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &x_All_సంకేతాలు, ఖాళీ );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t x_పోర్టు_సమితి_అంతరాయం_ముసుగు( శూన్య )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    తిరిగి ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు( UBaseType_t ux_ముసుగు )
{
    ( శూన్య ) ux_ముసుగు;
}
/*-----------------------------------------------------------*/

స్థిర uint64_t prv_Get_సమయం_Ns( శూన్య )
{
    నిర్మాణం timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    తిరిగి ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

స్థిర శూన్య * prvTimerTickHandler( శూన్య * arg )
{
    ( శూన్య ) arg;

    prvMarkAsFreeRTOSThread();

    prv_పోర్టు_సమితి_Current_Thread_Name( "Scheduler timer" );

    అయితే( x_Timer_Tick_Thread_Should_నిరంతరం )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( పోర్టు_TICK_రేటు_MICROSECONDS );
    }

    తిరిగి ఖాళీ;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    x_Timer_Tick_Thread_Should_నిరంతరం = true;
    pthread_create( &hTimerTickThread, ఖాళీ, prvTimerTickHandler, ఖాళీ );

    prv_ప్రారంభం_సమయం_Ns = prv_Get_సమయం_Ns();
}
/*-----------------------------------------------------------*/

స్థిర శూన్య v_పోర్టు_System_Tick_Handler( పూర్ణాంకం sig )
{
    ఒకవేళ( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * px_Thread_గమ్యం_Suspend;
        Thread_t * px_Thread_గమ్యం_Resume;

        ( శూన్య ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        px_Thread_గమ్యం_Suspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        ఒకవేళ( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            px_Thread_గమ్యం_Resume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( px_Thread_గమ్యం_Resume, px_Thread_గమ్యం_Suspend );
        }

        uxCriticalNesting--;
    }
    లేకపోతే
    {
        fprintf( stderr, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Thread_Dying( శూన్య * px_Task_గమ్యం_Delete,
                       అస్థిర పునాది_Type_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( px_Task_గమ్యం_Delete );

    ( శూన్య ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Cancel_Thread( శూన్య * px_Task_గమ్యం_Delete )
{
    Thread_t * px_Thread_గమ్యం_Cancel = prvGetThreadFromTask( px_Task_గమ్యం_Delete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( px_Thread_గమ్యం_Cancel->pthread );
    event_signal( px_Thread_గమ్యం_Cancel->ev );
    pthread_join( px_Thread_గమ్యం_Cancel->pthread, ఖాళీ );
    event_delete( px_Thread_గమ్యం_Cancel->ev );
}
/*-----------------------------------------------------------*/

స్థిర శూన్య * prv_Wait_For_ప్రారంభం( శూన్య * pvParams )
{
    Thread_t * pxThread = pvParams;

    prvMarkAsFreeRTOSThread();

    prvSuspendSelf( pxThread );

    /* Resumed for the first time, unblocks all signals. */
    uxCriticalNesting = 0;
    v_పోర్టు_Enable_Interrupts();

    /* Set thread name */
    prv_పోర్టు_సమితి_Current_Thread_Name( pcTaskGetName( xTaskGetCurrentTaskHandle() ) );

    /* Call the task's entry point. */
    pxThread->px_సంకేతం( pxThread->pvParams );

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, so application writers can
     * catch the error. */
    configASSERT( pdFALSE );

    తిరిగి ఖాళీ;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prvSwitchThread( Thread_t * px_Thread_గమ్యం_Resume,
                             Thread_t * px_Thread_గమ్యం_Suspend )
{
    పునాది_Type_t uxSavedCriticalNesting;

    ఒకవేళ( px_Thread_గమ్యం_Suspend != px_Thread_గమ్యం_Resume )
    {
        /*
         * Switch tasks.
         *
         * The critical section nesting is per-task, so save it on the
         * stack of the current (suspending thread), restoring it when
         * we switch back to this task.
         */
        uxSavedCriticalNesting = uxCriticalNesting;

        prvResumeThread( px_Thread_గమ్యం_Resume );

        ఒకవేళ( px_Thread_గమ్యం_Suspend->xDying == pdTRUE )
        {
            pthread_exit( ఖాళీ );
        }

        prvSuspendSelf( px_Thread_గమ్యం_Suspend );

        uxCriticalNesting = uxSavedCriticalNesting;
    }
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prvSuspendSelf( Thread_t * thread )
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

స్థిర శూన్య prvResumeThread( Thread_t * xThreadId )
{
    ఒకవేళ( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prv_అమరిక_సంకేతాలు_And_Scheduler_Policy( శూన్య )
{
    నిర్మాణం sigaction sigtick;
    పూర్ణాంకం iRet;

    hMainThread = pthread_self();

    /* Initialise common signal masks. */
    sigfillset( &x_All_సంకేతాలు );

    /* Don't block SIGINT so this can be used to break into GDB while
     * in a critical section. */
    sigdelset( &x_All_సంకేతాలు, SIGINT );

    /*
     * Block all signals in this thread so all new threads
     * inherits this mask.
     *
     * When a thread is resumed for the first time, all signals
     * will be unblocked.
     */
    ( శూన్య ) pthread_sigmask( SIG_SETMASK,
                              &x_All_సంకేతాలు,
                              &x_Scheduler_Original_Signal_ముసుగు );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = v_పోర్టు_System_Tick_Handler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, ఖాళీ );

    ఒకవేళ( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_పోర్టు_Get_నిరంతరం_సమయం( శూన్య )
{
    నిర్మాణం tms xTimes;

    times( &xTimes );

    తిరిగి ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
