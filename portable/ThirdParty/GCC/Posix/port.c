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
#यदि_परिभाषितम् __linux__
    #परिभाषय _GNU_SOURCE
#यदि_अन्तः
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

#परिभाषय SIG_RESUME    SIGUSR1

प्रकारनिर्देश संरचना THREAD
{
    pthread_t pthread;
    TaskFunction_t px_संहिता;
    शून्य * pvParams;
    आधारः_Type_t xDying;
    संरचना event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
स्थिर अन्तःस्थ Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः = *( राशिः_Type_t ** ) xTask;

    प्रत्यागम ( Thread_t * ) ( px_शिखरम्_सम्बन्धि_राशिः + 1 );
}

/*-----------------------------------------------------------*/

स्थिर pthread_once_t h_Sig_सज्जता_Thread = PTHREAD_ONCE_INIT;
स्थिर pthread_once_t h_Thread_कुञ्चिका_Once = PTHREAD_ONCE_INIT;
स्थिर sigset_t x_All_सङ्केताः;
स्थिर sigset_t x_Scheduler_Original_Signal_आवरणम्;
स्थिर pthread_t hMainThread = ( pthread_t ) रिक्त;
स्थिर चञ्चल आधारः_Type_t uxCriticalNesting;
स्थिर आधारः_Type_t x_Scheduler_अन्तः = pdFALSE;
स्थिर pthread_t hTimerTickThread;
स्थिर bool x_Timer_Tick_Thread_Should_सततम्;
स्थिर uint64_t prvStartTimeNs;
स्थिर pthread_key_t x_Thread_कुञ्चिका = 0;
/*-----------------------------------------------------------*/

स्थिर शून्य prv_सज्जता_सङ्केताः_And_Scheduler_Policy( शून्य );
स्थिर शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य );
स्थिर शून्य * prvWaitForStart( शून्य * pvParams );
स्थिर शून्य prvSwitchThread( Thread_t * x_Thread_गन्तव्यम्_Resume,
                             Thread_t * x_Thread_गन्तव्यम्_Suspend );
स्थिर शून्य prvSuspendSelf( Thread_t * thread );
स्थिर शून्य prvResumeThread( Thread_t * xThreadId );
स्थिर शून्य v_पत्तनम्_System_Tick_Handler( पूर्णाङ्क sig );
स्थिर शून्य v_पत्तनम्_Start_First_Task( शून्य );
स्थिर शून्य prv_पत्तनम्_Yield_From_ISR( शून्य );
स्थिर शून्य prv_Thread_कुञ्चिका_Destructor( शून्य * pv_दत्त );
स्थिर शून्य prv_Init_Thread_कुञ्चिका( शून्य );
स्थिर शून्य prvMarkAsFreeRTOSThread( शून्य );
स्थिर आधारः_Type_t prvIsFreeRTOSThread( शून्य );
स्थिर शून्य prv_Destroy_Thread_कुञ्चिका( शून्य );
/*-----------------------------------------------------------*/

स्थिर शून्य prv_Thread_कुञ्चिका_Destructor( शून्य * pv_दत्त )
{
    मुक्त( pv_दत्त );
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_Init_Thread_कुञ्चिका( शून्य )
{
    pthread_key_create( &x_Thread_कुञ्चिका, prv_Thread_कुञ्चिका_Destructor );
    /* Destroy xThreadKey when the process exits. */
    atexit( prv_Destroy_Thread_कुञ्चिका );
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvMarkAsFreeRTOSThread( शून्य )
{
    uint8_t * puc_Thread_दत्त = रिक्त;

    ( शून्य ) pthread_once( &h_Thread_कुञ्चिका_Once, prv_Init_Thread_कुञ्चिका );

    puc_Thread_दत्त = स्मृतिं_देहि( 1 );
    configASSERT( puc_Thread_दत्त != रिक्त );

    *puc_Thread_दत्त = 1;

    pthread_setspecific( x_Thread_कुञ्चिका, puc_Thread_दत्त );
}
/*-----------------------------------------------------------*/

स्थिर आधारः_Type_t prvIsFreeRTOSThread( शून्य )
{
    uint8_t * puc_Thread_दत्त = रिक्त;
    आधारः_Type_t xRet = pdFALSE;

    ( शून्य ) pthread_once( &h_Thread_कुञ्चिका_Once, prv_Init_Thread_कुञ्चिका );

    puc_Thread_दत्त = ( uint8_t * ) pthread_getspecific( x_Thread_कुञ्चिका );

    यदि( ( puc_Thread_दत्त != रिक्त ) && ( *puc_Thread_दत्त == 1 ) )
    {
        xRet = pdTRUE;
    }

    प्रत्यागम xRet;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_Destroy_Thread_कुञ्चिका( शून्य )
{
    pthread_key_delete( x_Thread_कुञ्चिका );
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvFatalError( ध्रुव वर्ण * pcCall,
                           पूर्णाङ्क iErrno ) __attribute__( ( __noreturn__ ) );

शून्य prvFatalError( ध्रुव वर्ण * pcCall,
                    पूर्णाङ्क iErrno )
{
    fprintf( stderr, "%s: %s\n", pcCall, strerror( iErrno ) );
    abort();
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_पत्तनम्_समुच्चयः_Current_Thread_Name( ध्रुव वर्ण * pxThreadName )
{
    #यदि_परिभाषितम् __APPLE__
        pthread_setname_np( pxThreadName );
    #अन्यथा
        pthread_setname_np( pthread_self(), pxThreadName );
    #यदि_अन्तः
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     राशिः_Type_t * px_अन्तः_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t x_Thread_गुणाः;
    size_t ul_राशिः_आकार;
    पूर्णाङ्क iRet;

    ( शून्य ) pthread_once( &h_Sig_सज्जता_Thread, prv_सज्जता_सङ्केताः_And_Scheduler_Policy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_शिखरम्_सम्बन्धि_राशिः + 1 ) - 1;
    px_शिखरम्_सम्बन्धि_राशिः = ( राशिः_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_राशिः_आकार = ( size_t ) ( px_शिखरम्_सम्बन्धि_राशिः + 1 - px_अन्तः_सम्बन्धि_राशिः ) * परिमाण( *px_शिखरम्_सम्बन्धि_राशिः );
    configASSERT( ul_राशिः_आकार > परिमाण( Thread_t ) );
    ( शून्य ) ul_राशिः_आकार; /* suppress set but not used warning */

    thread->px_संहिता = px_संहिता;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &x_Thread_गुणाः );

    thread->ev = event_create();

    v_पत्तनम्_Enter_Critical();

    iRet = pthread_create( &thread->pthread, &x_Thread_गुणाः,
                           prvWaitForStart, thread );

    यदि( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    v_पत्तनम्_Exit_Critical();

    प्रत्यागम px_शिखरम्_सम्बन्धि_राशिः;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Start_First_Task( शून्य )
{
    Thread_t * pxFirstThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( pxFirstThread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    पूर्णाङ्क iSignal;
    sigset_t x_सङ्केताः;

    hMainThread = pthread_self();
    prv_पत्तनम्_समुच्चयः_Current_Thread_Name( "Scheduler" );

    /* Start the timer that generates the tick ISR(SIGALRM).
     * Interrupts are disabled here already. */
    prv_सज्जता_Timer_व्यवधानम्();

    /*
     * Block SIG_RESUME before starting any tasks so the main thread can sigwait on it.
     * To sigwait on an unblocked signal is undefined.
     * https://pubs.opengroup.org/onlinepubs/009604499/functions/sigwait.html
     */
    sigemptyset( &x_सङ्केताः );
    sigaddset( &x_सङ्केताः, SIG_RESUME );
    ( शून्य ) pthread_sigmask( SIG_BLOCK, &x_सङ्केताः, रिक्त );

    /* Start the first task. */
    v_पत्तनम्_Start_First_Task();

    /* Wait until signaled by vPortEndScheduler(). */
    यावत्( x_Scheduler_अन्तः != pdTRUE )
    {
        sigwait( &x_सङ्केताः, &iSignal );
    }

    /*
     * clear out the variable that is used to end the scheduler, otherwise
     * subsequent scheduler restarts will end immediately.
     */
    x_Scheduler_अन्तः = pdFALSE;

    /* Reset pthread_once_t, needed to restart the scheduler again.
     * memset the internal struct members for MacOS/Linux Compatibility */
    #यदि __APPLE__
        h_Sig_सज्जता_Thread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_कुञ्चिका_Once.__sig = _PTHREAD_ONCE_SIG_init;
        स्मृतिं_पूरय( ( शून्य * ) &h_Sig_सज्जता_Thread.__opaque, 0, परिमाण( h_Sig_सज्जता_Thread.__opaque ) );
        स्मृतिं_पूरय( ( शून्य * ) &h_Thread_कुञ्चिका_Once.__opaque, 0, परिमाण( h_Thread_कुञ्चिका_Once.__opaque ) );
    #अन्यथा /* Linux PTHREAD library*/
        h_Sig_सज्जता_Thread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_कुञ्चिका_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #यदि_अन्तः /* __APPLE__*/

    /* Restore original signal mask. */
    ( शून्य ) pthread_sigmask( SIG_SETMASK, &x_Scheduler_Original_Signal_आवरणम्, रिक्त );

    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    Thread_t * pxCurrentThread;
    आधारः_Type_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    x_Timer_Tick_Thread_Should_सततम् = false;
    pthread_join( hTimerTickThread, रिक्त );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    x_Scheduler_अन्तः = pdTRUE;
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

शून्य v_पत्तनम्_Enter_Critical( शून्य )
{
    यदि( uxCriticalNesting == 0 )
    {
        v_पत्तनम्_Disable_Interrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Exit_Critical( शून्य )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    यदि( uxCriticalNesting == 0 )
    {
        v_पत्तनम्_Enable_Interrupts();
    }
}
/*-----------------------------------------------------------*/

स्थिर शून्य prv_पत्तनम्_Yield_From_ISR( शून्य )
{
    Thread_t * x_Thread_गन्तव्यम्_Suspend;
    Thread_t * x_Thread_गन्तव्यम्_Resume;

    x_Thread_गन्तव्यम्_Suspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    x_Thread_गन्तव्यम्_Resume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( x_Thread_गन्तव्यम्_Resume, x_Thread_गन्तव्यम्_Suspend );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Yield( शून्य )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    v_पत्तनम्_Enter_Critical();

    prv_पत्तनम्_Yield_From_ISR();

    v_पत्तनम्_Exit_Critical();
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Disable_Interrupts( शून्य )
{
    यदि( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &x_All_सङ्केताः, रिक्त );
    }
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Enable_Interrupts( शून्य )
{
    यदि( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &x_All_सङ्केताः, रिक्त );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t x_पत्तनम्_समुच्चयः_व्यवधानम्_आवरणम्( शून्य )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    प्रत्यागम ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Clear_व्यवधानम्_आवरणम्( UBaseType_t ux_आवरणम् )
{
    ( शून्य ) ux_आवरणम्;
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

    prv_पत्तनम्_समुच्चयः_Current_Thread_Name( "Scheduler timer" );

    यावत्( x_Timer_Tick_Thread_Should_सततम् )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( पत्तनम्_TICK_दरः_MICROSECONDS );
    }

    प्रत्यागम रिक्त;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
शून्य prv_सज्जता_Timer_व्यवधानम्( शून्य )
{
    x_Timer_Tick_Thread_Should_सततम् = true;
    pthread_create( &hTimerTickThread, रिक्त, prvTimerTickHandler, रिक्त );

    prvStartTimeNs = prvGetTimeNs();
}
/*-----------------------------------------------------------*/

स्थिर शून्य v_पत्तनम्_System_Tick_Handler( पूर्णाङ्क sig )
{
    यदि( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * px_Thread_गन्तव्यम्_Suspend;
        Thread_t * px_Thread_गन्तव्यम्_Resume;

        ( शून्य ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        px_Thread_गन्तव्यम्_Suspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        यदि( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            px_Thread_गन्तव्यम्_Resume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( px_Thread_गन्तव्यम्_Resume, px_Thread_गन्तव्यम्_Suspend );
        }

        uxCriticalNesting--;
    }
    अन्यथा
    {
        fprintf( stderr, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Thread_Dying( शून्य * px_Task_गन्तव्यम्_Delete,
                       चञ्चल आधारः_Type_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( px_Task_गन्तव्यम्_Delete );

    ( शून्य ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Cancel_Thread( शून्य * px_Task_गन्तव्यम्_Delete )
{
    Thread_t * px_Thread_गन्तव्यम्_Cancel = prvGetThreadFromTask( px_Task_गन्तव्यम्_Delete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( px_Thread_गन्तव्यम्_Cancel->pthread );
    event_signal( px_Thread_गन्तव्यम्_Cancel->ev );
    pthread_join( px_Thread_गन्तव्यम्_Cancel->pthread, रिक्त );
    event_delete( px_Thread_गन्तव्यम्_Cancel->ev );
}
/*-----------------------------------------------------------*/

स्थिर शून्य * prvWaitForStart( शून्य * pvParams )
{
    Thread_t * pxThread = pvParams;

    prvMarkAsFreeRTOSThread();

    prvSuspendSelf( pxThread );

    /* Resumed for the first time, unblocks all signals. */
    uxCriticalNesting = 0;
    v_पत्तनम्_Enable_Interrupts();

    /* Set thread name */
    prv_पत्तनम्_समुच्चयः_Current_Thread_Name( pcTaskGetName( xTaskGetCurrentTaskHandle() ) );

    /* Call the task's entry point. */
    pxThread->px_संहिता( pxThread->pvParams );

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, so application writers can
     * catch the error. */
    configASSERT( pdFALSE );

    प्रत्यागम रिक्त;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvSwitchThread( Thread_t * px_Thread_गन्तव्यम्_Resume,
                             Thread_t * px_Thread_गन्तव्यम्_Suspend )
{
    आधारः_Type_t uxSavedCriticalNesting;

    यदि( px_Thread_गन्तव्यम्_Suspend != px_Thread_गन्तव्यम्_Resume )
    {
        /*
         * Switch tasks.
         *
         * The critical section nesting is per-task, so save it on the
         * stack of the current (suspending thread), restoring it when
         * we switch back to this task.
         */
        uxSavedCriticalNesting = uxCriticalNesting;

        prvResumeThread( px_Thread_गन्तव्यम्_Resume );

        यदि( px_Thread_गन्तव्यम्_Suspend->xDying == pdTRUE )
        {
            pthread_exit( रिक्त );
        }

        prvSuspendSelf( px_Thread_गन्तव्यम्_Suspend );

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

स्थिर शून्य prv_सज्जता_सङ्केताः_And_Scheduler_Policy( शून्य )
{
    संरचना sigaction sigtick;
    पूर्णाङ्क iRet;

    hMainThread = pthread_self();

    /* Initialise common signal masks. */
    sigfillset( &x_All_सङ्केताः );

    /* Don't block SIGINT so this can be used to break into GDB while
     * in a critical section. */
    sigdelset( &x_All_सङ्केताः, SIGINT );

    /*
     * Block all signals in this thread so all new threads
     * inherits this mask.
     *
     * When a thread is resumed for the first time, all signals
     * will be unblocked.
     */
    ( शून्य ) pthread_sigmask( SIG_SETMASK,
                              &x_All_सङ्केताः,
                              &x_Scheduler_Original_Signal_आवरणम् );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = v_पत्तनम्_System_Tick_Handler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, रिक्त );

    यदि( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_पत्तनम्_Get_सततम्_Time( शून्य )
{
    संरचना tms xTimes;

    times( &xTimes );

    प्रत्यागम ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
