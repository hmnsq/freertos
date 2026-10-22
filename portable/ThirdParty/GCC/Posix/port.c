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
#جيڪڏهن_وصف_ٿيل __linux__
    #وصف_ڪريو GNU_ذريعو
#جيڪڏهن_پورو
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

#وصف_ڪريو SIG_RESUME    SIGUSR1

تعريفنوع بنية THREAD
{
    pthread_t pthread;
    TaskFunction_t px_ڪوڊ;
    فراغ * pvParams;
    بنياد_Type_t xDying;
    بنية event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
ساكن مضمن Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    ڍير_Type_t * px_چوٽي_جو_ڍير = *( ڍير_Type_t ** ) xTask;

    أرجع ( Thread_t * ) ( px_چوٽي_جو_ڍير + 1 );
}

/*-----------------------------------------------------------*/

ساكن pthread_once_t h_Sig_تياري_Thread = PTHREAD_ONCE_INIT;
ساكن pthread_once_t h_Thread_ڪنجي_Once = PTHREAD_ONCE_INIT;
ساكن sigset_t x_All_سگنل;
ساكن sigset_t x_Scheduler_Original_Signal_نقاب;
ساكن pthread_t hMainThread = ( pthread_t ) عدم;
ساكن متطاير بنياد_Type_t uxCriticalNesting;
ساكن بنياد_Type_t x_Scheduler_پڇاڙي = pdFALSE;
ساكن pthread_t hTimerTickThread;
ساكن bool x_Timer_Tick_Thread_Should_لاڳيتو;
ساكن uint64_t prv_شروعات_وقت_Ns;
ساكن pthread_key_t x_Thread_ڪنجي = 0;
/*-----------------------------------------------------------*/

ساكن فراغ prv_تياري_سگنل_And_Scheduler_Policy( فراغ );
ساكن فراغ prv_تياري_Timer_مداخلت( فراغ );
ساكن فراغ * prv_Wait_For_شروعات( فراغ * pvParams );
ساكن فراغ prvSwitchThread( Thread_t * x_Thread_منزل_Resume,
                             Thread_t * x_Thread_منزل_Suspend );
ساكن فراغ prvSuspendSelf( Thread_t * thread );
ساكن فراغ prvResumeThread( Thread_t * xThreadId );
ساكن فراغ v_پورٽ_System_Tick_Handler( صحيح sig );
ساكن فراغ v_پورٽ_شروعات_پهريون_Task( فراغ );
ساكن فراغ prv_پورٽ_Yield_From_ISR( فراغ );
ساكن فراغ prv_Thread_ڪنجي_Destructor( فراغ * pv_معلومات );
ساكن فراغ prv_Init_Thread_ڪنجي( فراغ );
ساكن فراغ prvMarkAsFreeRTOSThread( فراغ );
ساكن بنياد_Type_t prvIsFreeRTOSThread( فراغ );
ساكن فراغ prv_Destroy_Thread_ڪنجي( فراغ );
/*-----------------------------------------------------------*/

ساكن فراغ prv_Thread_ڪنجي_Destructor( فراغ * pv_معلومات )
{
    حرر( pv_معلومات );
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_Init_Thread_ڪنجي( فراغ )
{
    pthread_key_create( &x_Thread_ڪنجي, prv_Thread_ڪنجي_Destructor );
    /* Destroy xThreadKey when the process exits. */
    atexit( prv_Destroy_Thread_ڪنجي );
}
/*-----------------------------------------------------------*/

ساكن فراغ prvMarkAsFreeRTOSThread( فراغ )
{
    uint8_t * puc_Thread_معلومات = عدم;

    ( فراغ ) pthread_once( &h_Thread_ڪنجي_Once, prv_Init_Thread_ڪنجي );

    puc_Thread_معلومات = يادگيري_ڏيو( 1 );
    configASSERT( puc_Thread_معلومات != عدم );

    *puc_Thread_معلومات = 1;

    pthread_setspecific( x_Thread_ڪنجي, puc_Thread_معلومات );
}
/*-----------------------------------------------------------*/

ساكن بنياد_Type_t prvIsFreeRTOSThread( فراغ )
{
    uint8_t * puc_Thread_معلومات = عدم;
    بنياد_Type_t xRet = pdFALSE;

    ( فراغ ) pthread_once( &h_Thread_ڪنجي_Once, prv_Init_Thread_ڪنجي );

    puc_Thread_معلومات = ( uint8_t * ) pthread_getspecific( x_Thread_ڪنجي );

    إذا( ( puc_Thread_معلومات != عدم ) && ( *puc_Thread_معلومات == 1 ) )
    {
        xRet = pdTRUE;
    }

    أرجع xRet;
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_Destroy_Thread_ڪنجي( فراغ )
{
    pthread_key_delete( x_Thread_ڪنجي );
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

ساكن فراغ prv_پورٽ_سيٽ_Current_Thread_Name( ثابت حرف * pxThreadName )
{
    #جيڪڏهن_وصف_ٿيل __APPLE__
        pthread_setname_np( pxThreadName );
    #وإلا
        pthread_setname_np( pthread_self(), pxThreadName );
    #جيڪڏهن_پورو
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     ڍير_Type_t * px_پڇاڙي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t x_Thread_خاصيتون;
    size_t ul_ڍير_سائيز;
    صحيح iRet;

    ( فراغ ) pthread_once( &h_Sig_تياري_Thread, prv_تياري_سگنل_And_Scheduler_Policy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_چوٽي_جو_ڍير + 1 ) - 1;
    px_چوٽي_جو_ڍير = ( ڍير_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_ڍير_سائيز = ( size_t ) ( px_چوٽي_جو_ڍير + 1 - px_پڇاڙي_جو_ڍير ) * حجم( *px_چوٽي_جو_ڍير );
    configASSERT( ul_ڍير_سائيز > حجم( Thread_t ) );
    ( فراغ ) ul_ڍير_سائيز; /* suppress set but not used warning */

    thread->px_ڪوڊ = px_ڪوڊ;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &x_Thread_خاصيتون );

    thread->ev = event_create();

    v_پورٽ_Enter_Critical();

    iRet = pthread_create( &thread->pthread, &x_Thread_خاصيتون,
                           prv_Wait_For_شروعات, thread );

    إذا( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    v_پورٽ_Exit_Critical();

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_شروعات_پهريون_Task( فراغ )
{
    Thread_t * px_پهريون_Thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( px_پهريون_Thread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    صحيح iSignal;
    sigset_t x_سگنل;

    hMainThread = pthread_self();
    prv_پورٽ_سيٽ_Current_Thread_Name( "Scheduler" );

    /* Start the timer that generates the tick ISR(SIGALRM).
     * Interrupts are disabled here already. */
    prv_تياري_Timer_مداخلت();

    /*
     * Block SIG_RESUME before starting any tasks so the main thread can sigwait on it.
     * To sigwait on an unblocked signal is undefined.
     * https://pubs.opengroup.org/onlinepubs/009604499/functions/sigwait.html
     */
    sigemptyset( &x_سگنل );
    sigaddset( &x_سگنل, SIG_RESUME );
    ( فراغ ) pthread_sigmask( SIG_BLOCK, &x_سگنل, عدم );

    /* Start the first task. */
    v_پورٽ_شروعات_پهريون_Task();

    /* Wait until signaled by vPortEndScheduler(). */
    طالما( x_Scheduler_پڇاڙي != pdTRUE )
    {
        sigwait( &x_سگنل, &iSignal );
    }

    /*
     * clear out the variable that is used to end the scheduler, otherwise
     * subsequent scheduler restarts will end immediately.
     */
    x_Scheduler_پڇاڙي = pdFALSE;

    /* Reset pthread_once_t, needed to restart the scheduler again.
     * memset the internal struct members for MacOS/Linux Compatibility */
    #إذا __APPLE__
        h_Sig_تياري_Thread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_ڪنجي_Once.__sig = _PTHREAD_ONCE_SIG_init;
        memset( ( فراغ * ) &h_Sig_تياري_Thread.__opaque, 0, حجم( h_Sig_تياري_Thread.__opaque ) );
        memset( ( فراغ * ) &h_Thread_ڪنجي_Once.__opaque, 0, حجم( h_Thread_ڪنجي_Once.__opaque ) );
    #وإلا /* Linux PTHREAD library*/
        h_Sig_تياري_Thread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_ڪنجي_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #جيڪڏهن_پورو /* __APPLE__*/

    /* Restore original signal mask. */
    ( فراغ ) pthread_sigmask( SIG_SETMASK, &x_Scheduler_Original_Signal_نقاب, عدم );

    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    Thread_t * pxCurrentThread;
    بنياد_Type_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    x_Timer_Tick_Thread_Should_لاڳيتو = false;
    pthread_join( hTimerTickThread, عدم );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    x_Scheduler_پڇاڙي = pdTRUE;
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

فراغ v_پورٽ_Enter_Critical( فراغ )
{
    إذا( uxCriticalNesting == 0 )
    {
        v_پورٽ_Disable_Interrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Exit_Critical( فراغ )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    إذا( uxCriticalNesting == 0 )
    {
        v_پورٽ_Enable_Interrupts();
    }
}
/*-----------------------------------------------------------*/

ساكن فراغ prv_پورٽ_Yield_From_ISR( فراغ )
{
    Thread_t * x_Thread_منزل_Suspend;
    Thread_t * x_Thread_منزل_Resume;

    x_Thread_منزل_Suspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    x_Thread_منزل_Resume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( x_Thread_منزل_Resume, x_Thread_منزل_Suspend );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Yield( فراغ )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    v_پورٽ_Enter_Critical();

    prv_پورٽ_Yield_From_ISR();

    v_پورٽ_Exit_Critical();
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Disable_Interrupts( فراغ )
{
    إذا( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &x_All_سگنل, عدم );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Enable_Interrupts( فراغ )
{
    إذا( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &x_All_سگنل, عدم );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t x_پورٽ_سيٽ_مداخلت_نقاب( فراغ )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    أرجع ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Clear_مداخلت_نقاب( UBaseType_t ux_نقاب )
{
    ( فراغ ) ux_نقاب;
}
/*-----------------------------------------------------------*/

ساكن uint64_t prv_Get_وقت_Ns( فراغ )
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

    prv_پورٽ_سيٽ_Current_Thread_Name( "Scheduler timer" );

    طالما( x_Timer_Tick_Thread_Should_لاڳيتو )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( پورٽ_TICK_شرح_MICROSECONDS );
    }

    أرجع عدم;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
فراغ prv_تياري_Timer_مداخلت( فراغ )
{
    x_Timer_Tick_Thread_Should_لاڳيتو = true;
    pthread_create( &hTimerTickThread, عدم, prvTimerTickHandler, عدم );

    prv_شروعات_وقت_Ns = prv_Get_وقت_Ns();
}
/*-----------------------------------------------------------*/

ساكن فراغ v_پورٽ_System_Tick_Handler( صحيح sig )
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

فراغ v_پورٽ_Thread_Dying( فراغ * px_Task_منزل_Delete,
                       متطاير بنياد_Type_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( px_Task_منزل_Delete );

    ( فراغ ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Cancel_Thread( فراغ * px_Task_منزل_Delete )
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

ساكن فراغ * prv_Wait_For_شروعات( فراغ * pvParams )
{
    Thread_t * pxThread = pvParams;

    prvMarkAsFreeRTOSThread();

    prvSuspendSelf( pxThread );

    /* Resumed for the first time, unblocks all signals. */
    uxCriticalNesting = 0;
    v_پورٽ_Enable_Interrupts();

    /* Set thread name */
    prv_پورٽ_سيٽ_Current_Thread_Name( pcTaskGetName( xTaskGetCurrentTaskHandle() ) );

    /* Call the task's entry point. */
    pxThread->px_ڪوڊ( pxThread->pvParams );

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
    بنياد_Type_t uxSavedCriticalNesting;

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

ساكن فراغ prv_تياري_سگنل_And_Scheduler_Policy( فراغ )
{
    بنية sigaction sigtick;
    صحيح iRet;

    hMainThread = pthread_self();

    /* Initialise common signal masks. */
    sigfillset( &x_All_سگنل );

    /* Don't block SIGINT so this can be used to break into GDB while
     * in a critical section. */
    sigdelset( &x_All_سگنل, SIGINT );

    /*
     * Block all signals in this thread so all new threads
     * inherits this mask.
     *
     * When a thread is resumed for the first time, all signals
     * will be unblocked.
     */
    ( فراغ ) pthread_sigmask( SIG_SETMASK,
                              &x_All_سگنل,
                              &x_Scheduler_Original_Signal_نقاب );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = v_پورٽ_System_Tick_Handler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, عدم );

    إذا( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_پورٽ_Get_لاڳيتو_وقت( فراغ )
{
    بنية tms xTimes;

    times( &xTimes );

    أرجع ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
