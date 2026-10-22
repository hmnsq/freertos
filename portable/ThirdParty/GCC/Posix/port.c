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
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __linux__
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GNU_ਸਰੋਤ
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "portmacro.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <pthread.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <signal.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/time.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/times.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <time.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "timers.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "utils/wait_for_event.h"
/*-----------------------------------------------------------*/

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SIG_RESUME    SIGUSR1

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ THREAD
{
    pthread_t pthread;
    TaskFunction_t px_ਕੋਡ;
    ਖਾਲੀ * pvParams;
    ਅਧਾਰ_Type_t xDying;
    ਬਣਤਰ event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ = *( ਢੇਰ_Type_t ** ) xTask;

    ਵਾਪਸ ( Thread_t * ) ( px_ਸਿਖਰ_ਦਾ_ਢੇਰ + 1 );
}

/*-----------------------------------------------------------*/

ਸਥਿਰ pthread_once_t h_Sig_ਤਿਆਰੀ_Thread = PTHREAD_ONCE_INIT;
ਸਥਿਰ pthread_once_t h_Thread_ਕੁੰਜੀ_Once = PTHREAD_ONCE_INIT;
ਸਥਿਰ sigset_t x_All_ਸੰਕੇਤ;
ਸਥਿਰ sigset_t x_Scheduler_Original_Signal_ਨਕਾਬ;
ਸਥਿਰ pthread_t hMainThread = ( pthread_t ) ਨਿਰਾ;
ਸਥਿਰ ਅਸਥਿਰ ਅਧਾਰ_Type_t uxCriticalNesting;
ਸਥਿਰ ਅਧਾਰ_Type_t x_Scheduler_ਸਿਰਾ = pdFALSE;
ਸਥਿਰ pthread_t hTimerTickThread;
ਸਥਿਰ bool x_Timer_Tick_Thread_Should_ਲੜੀਵਾਰ;
ਸਥਿਰ uint64_t prv_ਸ਼ੁਰੂ_ਸਮਾਂ_Ns;
ਸਥਿਰ pthread_key_t x_Thread_ਕੁੰਜੀ = 0;
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_ਸੰਕੇਤ_And_Scheduler_Policy( ਖਾਲੀ );
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ );
ਸਥਿਰ ਖਾਲੀ * prv_Wait_For_ਸ਼ੁਰੂ( ਖਾਲੀ * pvParams );
ਸਥਿਰ ਖਾਲੀ prvSwitchThread( Thread_t * x_Thread_ਮੰਜ਼ਿਲ_Resume,
                             Thread_t * x_Thread_ਮੰਜ਼ਿਲ_Suspend );
ਸਥਿਰ ਖਾਲੀ prvSuspendSelf( Thread_t * thread );
ਸਥਿਰ ਖਾਲੀ prvResumeThread( Thread_t * xThreadId );
ਸਥਿਰ ਖਾਲੀ v_ਪੋਰਟ_System_Tick_Handler( ਪੂਰਨ sig );
ਸਥਿਰ ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ );
ਸਥਿਰ ਖਾਲੀ prv_ਪੋਰਟ_Yield_From_ISR( ਖਾਲੀ );
ਸਥਿਰ ਖਾਲੀ prv_Thread_ਕੁੰਜੀ_Destructor( ਖਾਲੀ * pv_ਅੰਕੜੇ );
ਸਥਿਰ ਖਾਲੀ prv_Init_Thread_ਕੁੰਜੀ( ਖਾਲੀ );
ਸਥਿਰ ਖਾਲੀ prvMarkAsFreeRTOSThread( ਖਾਲੀ );
ਸਥਿਰ ਅਧਾਰ_Type_t prvIsFreeRTOSThread( ਖਾਲੀ );
ਸਥਿਰ ਖਾਲੀ prv_Destroy_Thread_ਕੁੰਜੀ( ਖਾਲੀ );
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_Thread_ਕੁੰਜੀ_Destructor( ਖਾਲੀ * pv_ਅੰਕੜੇ )
{
    ਮੁਕਤ( pv_ਅੰਕੜੇ );
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_Init_Thread_ਕੁੰਜੀ( ਖਾਲੀ )
{
    pthread_key_create( &x_Thread_ਕੁੰਜੀ, prv_Thread_ਕੁੰਜੀ_Destructor );
    /* Destroy xThreadKey when the process exits. */
    atexit( prv_Destroy_Thread_ਕੁੰਜੀ );
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvMarkAsFreeRTOSThread( ਖਾਲੀ )
{
    uint8_t * puc_Thread_ਅੰਕੜੇ = ਨਿਰਾ;

    ( ਖਾਲੀ ) pthread_once( &h_Thread_ਕੁੰਜੀ_Once, prv_Init_Thread_ਕੁੰਜੀ );

    puc_Thread_ਅੰਕੜੇ = ਸਮ੍ਰਿਤੀ_ਦਿਓ( 1 );
    configASSERT( puc_Thread_ਅੰਕੜੇ != ਨਿਰਾ );

    *puc_Thread_ਅੰਕੜੇ = 1;

    pthread_setspecific( x_Thread_ਕੁੰਜੀ, puc_Thread_ਅੰਕੜੇ );
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਅਧਾਰ_Type_t prvIsFreeRTOSThread( ਖਾਲੀ )
{
    uint8_t * puc_Thread_ਅੰਕੜੇ = ਨਿਰਾ;
    ਅਧਾਰ_Type_t xRet = pdFALSE;

    ( ਖਾਲੀ ) pthread_once( &h_Thread_ਕੁੰਜੀ_Once, prv_Init_Thread_ਕੁੰਜੀ );

    puc_Thread_ਅੰਕੜੇ = ( uint8_t * ) pthread_getspecific( x_Thread_ਕੁੰਜੀ );

    ਜੇ( ( puc_Thread_ਅੰਕੜੇ != ਨਿਰਾ ) && ( *puc_Thread_ਅੰਕੜੇ == 1 ) )
    {
        xRet = pdTRUE;
    }

    ਵਾਪਸ xRet;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_Destroy_Thread_ਕੁੰਜੀ( ਖਾਲੀ )
{
    pthread_key_delete( x_Thread_ਕੁੰਜੀ );
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvFatalError( ਅਚਲ ਅੱਖਰ * pcCall,
                           ਪੂਰਨ iErrno ) __attribute__( ( __noreturn__ ) );

ਖਾਲੀ prvFatalError( ਅਚਲ ਅੱਖਰ * pcCall,
                    ਪੂਰਨ iErrno )
{
    fprintf( stderr, "%s: %s\n", pcCall, strerror( iErrno ) );
    abort();
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਪੋਰਟ_ਸੈੱਟ_Current_Thread_Name( ਅਚਲ ਅੱਖਰ * pxThreadName )
{
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __APPLE__
        pthread_setname_np( pxThreadName );
    #ਨਹੀਂਤਾਂ
        pthread_setname_np( pthread_self(), pxThreadName );
    #ਜੇ_ਅੰਤ
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     ਢੇਰ_Type_t * px_ਸਿਰਾ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t x_Thread_ਗੁਣ;
    size_t ul_ਢੇਰ_ਮਾਪ;
    ਪੂਰਨ iRet;

    ( ਖਾਲੀ ) pthread_once( &h_Sig_ਤਿਆਰੀ_Thread, prv_ਤਿਆਰੀ_ਸੰਕੇਤ_And_Scheduler_Policy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_ਸਿਖਰ_ਦਾ_ਢੇਰ + 1 ) - 1;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_ਢੇਰ_ਮਾਪ = ( size_t ) ( px_ਸਿਖਰ_ਦਾ_ਢੇਰ + 1 - px_ਸਿਰਾ_ਦਾ_ਢੇਰ ) * ਆਕਾਰ( *px_ਸਿਖਰ_ਦਾ_ਢੇਰ );
    configASSERT( ul_ਢੇਰ_ਮਾਪ > ਆਕਾਰ( Thread_t ) );
    ( ਖਾਲੀ ) ul_ਢੇਰ_ਮਾਪ; /* suppress set but not used warning */

    thread->px_ਕੋਡ = px_ਕੋਡ;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &x_Thread_ਗੁਣ );

    thread->ev = event_create();

    v_ਪੋਰਟ_Enter_Critical();

    iRet = pthread_create( &thread->pthread, &x_Thread_ਗੁਣ,
                           prv_Wait_For_ਸ਼ੁਰੂ, thread );

    ਜੇ( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    v_ਪੋਰਟ_Exit_Critical();

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task( ਖਾਲੀ )
{
    Thread_t * px_ਪਹਿਲਾ_Thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( px_ਪਹਿਲਾ_Thread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    ਪੂਰਨ iSignal;
    sigset_t x_ਸੰਕੇਤ;

    hMainThread = pthread_self();
    prv_ਪੋਰਟ_ਸੈੱਟ_Current_Thread_Name( "Scheduler" );

    /* Start the timer that generates the tick ISR(SIGALRM).
     * Interrupts are disabled here already. */
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();

    /*
     * Block SIG_RESUME before starting any tasks so the main thread can sigwait on it.
     * To sigwait on an unblocked signal is undefined.
     * https://pubs.opengroup.org/onlinepubs/009604499/functions/sigwait.html
     */
    sigemptyset( &x_ਸੰਕੇਤ );
    sigaddset( &x_ਸੰਕੇਤ, SIG_RESUME );
    ( ਖਾਲੀ ) pthread_sigmask( SIG_BLOCK, &x_ਸੰਕੇਤ, ਨਿਰਾ );

    /* Start the first task. */
    v_ਪੋਰਟ_ਸ਼ੁਰੂ_ਪਹਿਲਾ_Task();

    /* Wait until signaled by vPortEndScheduler(). */
    ਜਦੋਂ( x_Scheduler_ਸਿਰਾ != pdTRUE )
    {
        sigwait( &x_ਸੰਕੇਤ, &iSignal );
    }

    /*
     * clear out the variable that is used to end the scheduler, otherwise
     * subsequent scheduler restarts will end immediately.
     */
    x_Scheduler_ਸਿਰਾ = pdFALSE;

    /* Reset pthread_once_t, needed to restart the scheduler again.
     * memset the internal struct members for MacOS/Linux Compatibility */
    #ਜੇ __APPLE__
        h_Sig_ਤਿਆਰੀ_Thread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_ਕੁੰਜੀ_Once.__sig = _PTHREAD_ONCE_SIG_init;
        memset( ( ਖਾਲੀ * ) &h_Sig_ਤਿਆਰੀ_Thread.__opaque, 0, ਆਕਾਰ( h_Sig_ਤਿਆਰੀ_Thread.__opaque ) );
        memset( ( ਖਾਲੀ * ) &h_Thread_ਕੁੰਜੀ_Once.__opaque, 0, ਆਕਾਰ( h_Thread_ਕੁੰਜੀ_Once.__opaque ) );
    #ਨਹੀਂਤਾਂ /* Linux PTHREAD library*/
        h_Sig_ਤਿਆਰੀ_Thread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_ਕੁੰਜੀ_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #ਜੇ_ਅੰਤ /* __APPLE__*/

    /* Restore original signal mask. */
    ( ਖਾਲੀ ) pthread_sigmask( SIG_SETMASK, &x_Scheduler_Original_Signal_ਨਕਾਬ, ਨਿਰਾ );

    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    Thread_t * pxCurrentThread;
    ਅਧਾਰ_Type_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    x_Timer_Tick_Thread_Should_ਲੜੀਵਾਰ = false;
    pthread_join( hTimerTickThread, ਨਿਰਾ );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    x_Scheduler_ਸਿਰਾ = pdTRUE;
    ( ਖਾਲੀ ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    ਜੇ( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    ਜੇ( uxCriticalNesting == 0 )
    {
        v_ਪੋਰਟ_Disable_Interrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    ਜੇ( uxCriticalNesting == 0 )
    {
        v_ਪੋਰਟ_Enable_Interrupts();
    }
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਪੋਰਟ_Yield_From_ISR( ਖਾਲੀ )
{
    Thread_t * x_Thread_ਮੰਜ਼ਿਲ_Suspend;
    Thread_t * x_Thread_ਮੰਜ਼ਿਲ_Resume;

    x_Thread_ਮੰਜ਼ਿਲ_Suspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    x_Thread_ਮੰਜ਼ਿਲ_Resume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( x_Thread_ਮੰਜ਼ਿਲ_Resume, x_Thread_ਮੰਜ਼ਿਲ_Suspend );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    v_ਪੋਰਟ_Enter_Critical();

    prv_ਪੋਰਟ_Yield_From_ISR();

    v_ਪੋਰਟ_Exit_Critical();
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Disable_Interrupts( ਖਾਲੀ )
{
    ਜੇ( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &x_All_ਸੰਕੇਤ, ਨਿਰਾ );
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Enable_Interrupts( ਖਾਲੀ )
{
    ਜੇ( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &x_All_ਸੰਕੇਤ, ਨਿਰਾ );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t x_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ( ਖਾਲੀ )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    ਵਾਪਸ ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( UBaseType_t ux_ਨਕਾਬ )
{
    ( ਖਾਲੀ ) ux_ਨਕਾਬ;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ uint64_t prv_Get_ਸਮਾਂ_Ns( ਖਾਲੀ )
{
    ਬਣਤਰ timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    ਵਾਪਸ ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

ਸਥਿਰ ਖਾਲੀ * prvTimerTickHandler( ਖਾਲੀ * arg )
{
    ( ਖਾਲੀ ) arg;

    prvMarkAsFreeRTOSThread();

    prv_ਪੋਰਟ_ਸੈੱਟ_Current_Thread_Name( "Scheduler timer" );

    ਜਦੋਂ( x_Timer_Tick_Thread_Should_ਲੜੀਵਾਰ )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( ਪੋਰਟ_TICK_ਦਰ_MICROSECONDS );
    }

    ਵਾਪਸ ਨਿਰਾ;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    x_Timer_Tick_Thread_Should_ਲੜੀਵਾਰ = true;
    pthread_create( &hTimerTickThread, ਨਿਰਾ, prvTimerTickHandler, ਨਿਰਾ );

    prv_ਸ਼ੁਰੂ_ਸਮਾਂ_Ns = prv_Get_ਸਮਾਂ_Ns();
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ v_ਪੋਰਟ_System_Tick_Handler( ਪੂਰਨ sig )
{
    ਜੇ( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * px_Thread_ਮੰਜ਼ਿਲ_Suspend;
        Thread_t * px_Thread_ਮੰਜ਼ਿਲ_Resume;

        ( ਖਾਲੀ ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        px_Thread_ਮੰਜ਼ਿਲ_Suspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        ਜੇ( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            px_Thread_ਮੰਜ਼ਿਲ_Resume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( px_Thread_ਮੰਜ਼ਿਲ_Resume, px_Thread_ਮੰਜ਼ਿਲ_Suspend );
        }

        uxCriticalNesting--;
    }
    ਨਹੀਂਤਾਂ
    {
        fprintf( stderr, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Thread_Dying( ਖਾਲੀ * px_Task_ਮੰਜ਼ਿਲ_Delete,
                       ਅਸਥਿਰ ਅਧਾਰ_Type_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( px_Task_ਮੰਜ਼ਿਲ_Delete );

    ( ਖਾਲੀ ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Cancel_Thread( ਖਾਲੀ * px_Task_ਮੰਜ਼ਿਲ_Delete )
{
    Thread_t * px_Thread_ਮੰਜ਼ਿਲ_Cancel = prvGetThreadFromTask( px_Task_ਮੰਜ਼ਿਲ_Delete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( px_Thread_ਮੰਜ਼ਿਲ_Cancel->pthread );
    event_signal( px_Thread_ਮੰਜ਼ਿਲ_Cancel->ev );
    pthread_join( px_Thread_ਮੰਜ਼ਿਲ_Cancel->pthread, ਨਿਰਾ );
    event_delete( px_Thread_ਮੰਜ਼ਿਲ_Cancel->ev );
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ * prv_Wait_For_ਸ਼ੁਰੂ( ਖਾਲੀ * pvParams )
{
    Thread_t * pxThread = pvParams;

    prvMarkAsFreeRTOSThread();

    prvSuspendSelf( pxThread );

    /* Resumed for the first time, unblocks all signals. */
    uxCriticalNesting = 0;
    v_ਪੋਰਟ_Enable_Interrupts();

    /* Set thread name */
    prv_ਪੋਰਟ_ਸੈੱਟ_Current_Thread_Name( pcTaskGetName( xTaskGetCurrentTaskHandle() ) );

    /* Call the task's entry point. */
    pxThread->px_ਕੋਡ( pxThread->pvParams );

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, so application writers can
     * catch the error. */
    configASSERT( pdFALSE );

    ਵਾਪਸ ਨਿਰਾ;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvSwitchThread( Thread_t * px_Thread_ਮੰਜ਼ਿਲ_Resume,
                             Thread_t * px_Thread_ਮੰਜ਼ਿਲ_Suspend )
{
    ਅਧਾਰ_Type_t uxSavedCriticalNesting;

    ਜੇ( px_Thread_ਮੰਜ਼ਿਲ_Suspend != px_Thread_ਮੰਜ਼ਿਲ_Resume )
    {
        /*
         * Switch tasks.
         *
         * The critical section nesting is per-task, so save it on the
         * stack of the current (suspending thread), restoring it when
         * we switch back to this task.
         */
        uxSavedCriticalNesting = uxCriticalNesting;

        prvResumeThread( px_Thread_ਮੰਜ਼ਿਲ_Resume );

        ਜੇ( px_Thread_ਮੰਜ਼ਿਲ_Suspend->xDying == pdTRUE )
        {
            pthread_exit( ਨਿਰਾ );
        }

        prvSuspendSelf( px_Thread_ਮੰਜ਼ਿਲ_Suspend );

        uxCriticalNesting = uxSavedCriticalNesting;
    }
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvSuspendSelf( Thread_t * thread )
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

ਸਥਿਰ ਖਾਲੀ prvResumeThread( Thread_t * xThreadId )
{
    ਜੇ( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_ਸੰਕੇਤ_And_Scheduler_Policy( ਖਾਲੀ )
{
    ਬਣਤਰ sigaction sigtick;
    ਪੂਰਨ iRet;

    hMainThread = pthread_self();

    /* Initialise common signal masks. */
    sigfillset( &x_All_ਸੰਕੇਤ );

    /* Don't block SIGINT so this can be used to break into GDB while
     * in a critical section. */
    sigdelset( &x_All_ਸੰਕੇਤ, SIGINT );

    /*
     * Block all signals in this thread so all new threads
     * inherits this mask.
     *
     * When a thread is resumed for the first time, all signals
     * will be unblocked.
     */
    ( ਖਾਲੀ ) pthread_sigmask( SIG_SETMASK,
                              &x_All_ਸੰਕੇਤ,
                              &x_Scheduler_Original_Signal_ਨਕਾਬ );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = v_ਪੋਰਟ_System_Tick_Handler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, ਨਿਰਾ );

    ਜੇ( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_ਪੋਰਟ_Get_ਲੜੀਵਾਰ_ਸਮਾਂ( ਖਾਲੀ )
{
    ਬਣਤਰ tms xTimes;

    times( &xTimes );

    ਵਾਪਸ ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
