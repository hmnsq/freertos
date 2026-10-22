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
#که_تعریف_شوی __linux__
    #تعریف_کړه GNU_سرچینه
#د_که_پای
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

#تعریف_کړه SIG_RESUME    SIGUSR1

تعريفنوع بنية THREAD
{
    pthread_t pthread;
    TaskFunction_t px_کوډ;
    فراغ * pvParams;
    بنسټ_Type_t xDying;
    بنية event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
ساكن مضمن Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    ډېری_Type_t * px_سر_د_ډېری = *( ډېری_Type_t ** ) xTask;

    أرجع ( Thread_t * ) ( px_سر_د_ډېری + 1 );
}

/*-----------------------------------------------------------*/

ساكن pthread_once_t h_Sig_تیاری_Thread = PTHREAD_ONCE_INIT;
ساكن pthread_once_t h_Thread_کلی_Once = PTHREAD_ONCE_INIT;
ساكن sigset_t x_All_سیګنالونه;
ساكن sigset_t x_Scheduler_Original_Signal_ماسک;
ساكن pthread_t hMainThread = ( pthread_t ) عدم;
ساكن متطاير بنسټ_Type_t uxCriticalNesting;
ساكن بنسټ_Type_t x_Scheduler_پای_ټکی = pdFALSE;
ساكن pthread_t hTimerTickThread;
ساكن bool x_Timer_Tick_Thread_Should_پرلپسې;
ساكن uint64_t prv_پیل_وخت_Ns;
ساكن pthread_key_t x_Thread_کلی = 0;
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_سیګنالونه_And_Scheduler_Policy( فراغ );
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ );
ساكن فراغ * prv_Wait_For_پیل( فراغ * pvParams );
ساكن فراغ prvSwitchThread( Thread_t * x_Thread_منزل_Resume,
                             Thread_t * x_Thread_منزل_Suspend );
ساكن فراغ prvSuspendSelf( Thread_t * thread );
ساكن فراغ prvResumeThread( Thread_t * xThreadId );
ساكن فراغ v_پورټ_System_Tick_Handler( صحيح sig );
ساكن فراغ v_پورټ_پیل_لومړی_Task( فراغ );
ساكن فراغ prv_پورټ_Yield_From_ISR( فراغ );
ساكن فراغ prv_Thread_کلی_Destructor( فراغ * pv_معلومات );
ساكن فراغ prv_Init_Thread_کلی( فراغ );
ساكن فراغ prvMarkAsFreeRTOSThread( فراغ );
ساكن بنسټ_Type_t prvIsFreeRTOSThread( فراغ );
ساكن فراغ prv_Destroy_Thread_کلی( فراغ );
/*-----------------------------------------------------------*/

ساكن فراغ prv_Thread_کلی_Destructor( فراغ * pv_معلومات )
{
    حرر( pv_معلومات );
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_Init_Thread_کلی( فراغ )
{
    pthread_key_create( &x_Thread_کلی, prv_Thread_کلی_Destructor );
    /* Destroy xThreadKey when the process exits. */
    atexit( prv_Destroy_Thread_کلی );
}
/*-----------------------------------------------------------*/

ساكن فراغ prvMarkAsFreeRTOSThread( فراغ )
{
    uint8_t * puc_Thread_معلومات = عدم;

    ( فراغ ) pthread_once( &h_Thread_کلی_Once, prv_Init_Thread_کلی );

    puc_Thread_معلومات = حافظه_ورکړه( 1 );
    configASSERT( puc_Thread_معلومات != عدم );

    *puc_Thread_معلومات = 1;

    pthread_setspecific( x_Thread_کلی, puc_Thread_معلومات );
}
/*-----------------------------------------------------------*/

ساكن بنسټ_Type_t prvIsFreeRTOSThread( فراغ )
{
    uint8_t * puc_Thread_معلومات = عدم;
    بنسټ_Type_t xRet = pdFALSE;

    ( فراغ ) pthread_once( &h_Thread_کلی_Once, prv_Init_Thread_کلی );

    puc_Thread_معلومات = ( uint8_t * ) pthread_getspecific( x_Thread_کلی );

    إذا( ( puc_Thread_معلومات != عدم ) && ( *puc_Thread_معلومات == 1 ) )
    {
        xRet = pdTRUE;
    }

    أرجع xRet;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_Destroy_Thread_کلی( فراغ )
{
    pthread_key_delete( x_Thread_کلی );
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

ساكن فراغ prv_پورټ_سېټ_Current_Thread_Name( ثابت حرف * pxThreadName )
{
    #که_تعریف_شوی __APPLE__
        pthread_setname_np( pxThreadName );
    #وإلا
        pthread_setname_np( pthread_self(), pxThreadName );
    #د_که_پای
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     ډېری_Type_t * px_پای_ټکی_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t x_Thread_ځانګړتیاوې;
    size_t ul_ډېری_اندازه;
    صحيح iRet;

    ( فراغ ) pthread_once( &h_Sig_تیاری_Thread, prv_تیاری_سیګنالونه_And_Scheduler_Policy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_سر_د_ډېری + 1 ) - 1;
    px_سر_د_ډېری = ( ډېری_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_ډېری_اندازه = ( size_t ) ( px_سر_د_ډېری + 1 - px_پای_ټکی_د_ډېری ) * حجم( *px_سر_د_ډېری );
    configASSERT( ul_ډېری_اندازه > حجم( Thread_t ) );
    ( فراغ ) ul_ډېری_اندازه; /* suppress set but not used warning */

    thread->px_کوډ = px_کوډ;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &x_Thread_ځانګړتیاوې );

    thread->ev = event_create();

    v_پورټ_Enter_Critical();

    iRet = pthread_create( &thread->pthread, &x_Thread_ځانګړتیاوې,
                           prv_Wait_For_پیل, thread );

    إذا( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    v_پورټ_Exit_Critical();

    أرجع px_سر_د_ډېری;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پیل_لومړی_Task( فراغ )
{
    Thread_t * px_لومړی_Thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( px_لومړی_Thread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    صحيح iSignal;
    sigset_t x_سیګنالونه;

    hMainThread = pthread_self();
    prv_پورټ_سېټ_Current_Thread_Name( "Scheduler" );

    /* Start the timer that generates the tick ISR(SIGALRM).
     * Interrupts are disabled here already. */
    prv_تیاری_Timer_مداخله();

    /*
     * Block SIG_RESUME before starting any tasks so the main thread can sigwait on it.
     * To sigwait on an unblocked signal is undefined.
     * https://pubs.opengroup.org/onlinepubs/009604499/functions/sigwait.html
     */
    sigemptyset( &x_سیګنالونه );
    sigaddset( &x_سیګنالونه, SIG_RESUME );
    ( فراغ ) pthread_sigmask( SIG_BLOCK, &x_سیګنالونه, عدم );

    /* Start the first task. */
    v_پورټ_پیل_لومړی_Task();

    /* Wait until signaled by vPortEndScheduler(). */
    طالما( x_Scheduler_پای_ټکی != pdTRUE )
    {
        sigwait( &x_سیګنالونه, &iSignal );
    }

    /*
     * clear out the variable that is used to end the scheduler, otherwise
     * subsequent scheduler restarts will end immediately.
     */
    x_Scheduler_پای_ټکی = pdFALSE;

    /* Reset pthread_once_t, needed to restart the scheduler again.
     * memset the internal struct members for MacOS/Linux Compatibility */
    #إذا __APPLE__
        h_Sig_تیاری_Thread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_کلی_Once.__sig = _PTHREAD_ONCE_SIG_init;
        memset( ( فراغ * ) &h_Sig_تیاری_Thread.__opaque, 0, حجم( h_Sig_تیاری_Thread.__opaque ) );
        memset( ( فراغ * ) &h_Thread_کلی_Once.__opaque, 0, حجم( h_Thread_کلی_Once.__opaque ) );
    #وإلا /* Linux PTHREAD library*/
        h_Sig_تیاری_Thread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_کلی_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #د_که_پای /* __APPLE__*/

    /* Restore original signal mask. */
    ( فراغ ) pthread_sigmask( SIG_SETMASK, &x_Scheduler_Original_Signal_ماسک, عدم );

    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
    Thread_t * pxCurrentThread;
    بنسټ_Type_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    x_Timer_Tick_Thread_Should_پرلپسې = false;
    pthread_join( hTimerTickThread, عدم );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    x_Scheduler_پای_ټکی = pdTRUE;
    ( فراغ ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    إذا( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Enter_Critical( فراغ )
{
    إذا( uxCriticalNesting == 0 )
    {
        v_پورټ_Disable_Interrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Exit_Critical( فراغ )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    إذا( uxCriticalNesting == 0 )
    {
        v_پورټ_Enable_Interrupts();
    }
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_پورټ_Yield_From_ISR( فراغ )
{
    Thread_t * x_Thread_منزل_Suspend;
    Thread_t * x_Thread_منزل_Resume;

    x_Thread_منزل_Suspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    x_Thread_منزل_Resume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( x_Thread_منزل_Resume, x_Thread_منزل_Suspend );
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Yield( فراغ )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    v_پورټ_Enter_Critical();

    prv_پورټ_Yield_From_ISR();

    v_پورټ_Exit_Critical();
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Disable_Interrupts( فراغ )
{
    إذا( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &x_All_سیګنالونه, عدم );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Enable_Interrupts( فراغ )
{
    إذا( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &x_All_سیګنالونه, عدم );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t x_پورټ_سېټ_مداخله_ماسک( فراغ )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    أرجع ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Clear_مداخله_ماسک( UBaseType_t ux_ماسک )
{
    ( فراغ ) ux_ماسک;
}
/*-----------------------------------------------------------*/

ساكن uint64_t prv_Get_وخت_Ns( فراغ )
{
    بنية timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    أرجع ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

ساكن فراغ * prvTimerTickHandler( فراغ * arg )
{
    ( فراغ ) arg;

    prvMarkAsFreeRTOSThread();

    prv_پورټ_سېټ_Current_Thread_Name( "Scheduler timer" );

    طالما( x_Timer_Tick_Thread_Should_پرلپسې )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( پورټ_TICK_شرح_MICROSECONDS );
    }

    أرجع عدم;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
فراغ prv_تیاری_Timer_مداخله( فراغ )
{
    x_Timer_Tick_Thread_Should_پرلپسې = true;
    pthread_create( &hTimerTickThread, عدم, prvTimerTickHandler, عدم );

    prv_پیل_وخت_Ns = prv_Get_وخت_Ns();
}
/*-----------------------------------------------------------*/

ساكن فراغ v_پورټ_System_Tick_Handler( صحيح sig )
{
    إذا( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * px_Thread_منزل_Suspend;
        Thread_t * px_Thread_منزل_Resume;

        ( فراغ ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        px_Thread_منزل_Suspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        إذا( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            px_Thread_منزل_Resume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( px_Thread_منزل_Resume, px_Thread_منزل_Suspend );
        }

        uxCriticalNesting--;
    }
    وإلا
    {
        fprintf( stderr, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Thread_Dying( فراغ * px_Task_منزل_Delete,
                       متطاير بنسټ_Type_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( px_Task_منزل_Delete );

    ( فراغ ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

فراغ v_پورټ_Cancel_Thread( فراغ * px_Task_منزل_Delete )
{
    Thread_t * px_Thread_منزل_Cancel = prvGetThreadFromTask( px_Task_منزل_Delete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( px_Thread_منزل_Cancel->pthread );
    event_signal( px_Thread_منزل_Cancel->ev );
    pthread_join( px_Thread_منزل_Cancel->pthread, عدم );
    event_delete( px_Thread_منزل_Cancel->ev );
}
/*-----------------------------------------------------------*/

ساكن فراغ * prv_Wait_For_پیل( فراغ * pvParams )
{
    Thread_t * pxThread = pvParams;

    prvMarkAsFreeRTOSThread();

    prvSuspendSelf( pxThread );

    /* Resumed for the first time, unblocks all signals. */
    uxCriticalNesting = 0;
    v_پورټ_Enable_Interrupts();

    /* Set thread name */
    prv_پورټ_سېټ_Current_Thread_Name( pcTaskGetName( xTaskGetCurrentTaskHandle() ) );

    /* Call the task's entry point. */
    pxThread->px_کوډ( pxThread->pvParams );

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, so application writers can
     * catch the error. */
    configASSERT( pdFALSE );

    أرجع عدم;
}
/*-----------------------------------------------------------*/

ساكن فراغ prvSwitchThread( Thread_t * px_Thread_منزل_Resume,
                             Thread_t * px_Thread_منزل_Suspend )
{
    بنسټ_Type_t uxSavedCriticalNesting;

    إذا( px_Thread_منزل_Suspend != px_Thread_منزل_Resume )
    {
        /*
         * Switch tasks.
         *
         * The critical section nesting is per-task, so save it on the
         * stack of the current (suspending thread), restoring it when
         * we switch back to this task.
         */
        uxSavedCriticalNesting = uxCriticalNesting;

        prvResumeThread( px_Thread_منزل_Resume );

        إذا( px_Thread_منزل_Suspend->xDying == pdTRUE )
        {
            pthread_exit( عدم );
        }

        prvSuspendSelf( px_Thread_منزل_Suspend );

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
    إذا( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_تیاری_سیګنالونه_And_Scheduler_Policy( فراغ )
{
    بنية sigaction sigtick;
    صحيح iRet;

    hMainThread = pthread_self();

    /* Initialise common signal masks. */
    sigfillset( &x_All_سیګنالونه );

    /* Don't block SIGINT so this can be used to break into GDB while
     * in a critical section. */
    sigdelset( &x_All_سیګنالونه, SIGINT );

    /*
     * Block all signals in this thread so all new threads
     * inherits this mask.
     *
     * When a thread is resumed for the first time, all signals
     * will be unblocked.
     */
    ( فراغ ) pthread_sigmask( SIG_SETMASK,
                              &x_All_سیګنالونه,
                              &x_Scheduler_Original_Signal_ماسک );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = v_پورټ_System_Tick_Handler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, عدم );

    إذا( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_پورټ_Get_پرلپسې_وخت( فراغ )
{
    بنية tms xTimes;

    times( &xTimes );

    أرجع ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
