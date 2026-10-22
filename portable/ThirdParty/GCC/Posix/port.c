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
#اگر_تعریف_شدہ __linux__
    #تعریف_کرو GNU_ماخذ
#اگر_ختم
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

#تعریف_کرو SIG_RESUME    SIGUSR1

قسمتعریف ساخت THREAD
{
    pthread_t pthread;
    TaskFunction_t px_رمز;
    خالی * pvParams;
    بنیاد_Type_t xDying;
    ساخت event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
ساکن اندرونی Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    ڈھیر_Type_t * px_چوٹی_کا_ڈھیر = *( ڈھیر_Type_t ** ) xTask;

    واپس ( Thread_t * ) ( px_چوٹی_کا_ڈھیر + 1 );
}

/*-----------------------------------------------------------*/

ساکن pthread_once_t h_Sig_تیاری_Thread = PTHREAD_ONCE_INIT;
ساکن pthread_once_t h_Thread_کلید_Once = PTHREAD_ONCE_INIT;
ساکن sigset_t x_All_اشارات;
ساکن sigset_t x_Scheduler_Original_Signal_نقاب;
ساکن pthread_t hMainThread = ( pthread_t ) تہی;
ساکن متلون بنیاد_Type_t uxCriticalNesting;
ساکن بنیاد_Type_t x_Scheduler_انتہا = pdFALSE;
ساکن pthread_t hTimerTickThread;
ساکن bool x_Timer_Tick_Thread_Should_تسلسل;
ساکن uint64_t prv_آغاز_وقت_Ns;
ساکن pthread_key_t x_Thread_کلید = 0;
/*-----------------------------------------------------------*/

ساکن خالی prv_تیاری_اشارات_And_Scheduler_Policy( خالی );
ساکن خالی prv_تیاری_Timer_مداخلت( خالی );
ساکن خالی * prv_Wait_For_آغاز( خالی * pvParams );
ساکن خالی prvSwitchThread( Thread_t * x_Thread_مقصد_Resume,
                             Thread_t * x_Thread_مقصد_Suspend );
ساکن خالی prvSuspendSelf( Thread_t * thread );
ساکن خالی prvResumeThread( Thread_t * xThreadId );
ساکن خالی v_پورٹ_System_Tick_Handler( صحیح sig );
ساکن خالی v_پورٹ_آغاز_پہلا_Task( خالی );
ساکن خالی prv_پورٹ_Yield_From_ISR( خالی );
ساکن خالی prv_Thread_کلید_Destructor( خالی * pv_ڈیٹا );
ساکن خالی prv_Init_Thread_کلید( خالی );
ساکن خالی prvMarkAsFreeRTOSThread( خالی );
ساکن بنیاد_Type_t prvIsFreeRTOSThread( خالی );
ساکن خالی prv_Destroy_Thread_کلید( خالی );
/*-----------------------------------------------------------*/

ساکن خالی prv_Thread_کلید_Destructor( خالی * pv_ڈیٹا )
{
    آزاد( pv_ڈیٹا );
}
/*-----------------------------------------------------------*/

ساکن خالی prv_Init_Thread_کلید( خالی )
{
    pthread_key_create( &x_Thread_کلید, prv_Thread_کلید_Destructor );
    /* Destroy xThreadKey when the process exits. */
    atexit( prv_Destroy_Thread_کلید );
}
/*-----------------------------------------------------------*/

ساکن خالی prvMarkAsFreeRTOSThread( خالی )
{
    uint8_t * puc_Thread_ڈیٹا = تہی;

    ( خالی ) pthread_once( &h_Thread_کلید_Once, prv_Init_Thread_کلید );

    puc_Thread_ڈیٹا = حافظہ_دو( 1 );
    configASSERT( puc_Thread_ڈیٹا != تہی );

    *puc_Thread_ڈیٹا = 1;

    pthread_setspecific( x_Thread_کلید, puc_Thread_ڈیٹا );
}
/*-----------------------------------------------------------*/

ساکن بنیاد_Type_t prvIsFreeRTOSThread( خالی )
{
    uint8_t * puc_Thread_ڈیٹا = تہی;
    بنیاد_Type_t xRet = pdFALSE;

    ( خالی ) pthread_once( &h_Thread_کلید_Once, prv_Init_Thread_کلید );

    puc_Thread_ڈیٹا = ( uint8_t * ) pthread_getspecific( x_Thread_کلید );

    اگر( ( puc_Thread_ڈیٹا != تہی ) && ( *puc_Thread_ڈیٹا == 1 ) )
    {
        xRet = pdTRUE;
    }

    واپس xRet;
}
/*-----------------------------------------------------------*/

ساکن خالی prv_Destroy_Thread_کلید( خالی )
{
    pthread_key_delete( x_Thread_کلید );
}
/*-----------------------------------------------------------*/

ساکن خالی prvFatalError( ثابت حرف * pcCall,
                           صحیح iErrno ) __attribute__( ( __noreturn__ ) );

خالی prvFatalError( ثابت حرف * pcCall,
                    صحیح iErrno )
{
    fprintf( stderr, "%s: %s\n", pcCall, strerror( iErrno ) );
    abort();
}
/*-----------------------------------------------------------*/

ساکن خالی prv_پورٹ_سیٹ_Current_Thread_Name( ثابت حرف * pxThreadName )
{
    #اگر_تعریف_شدہ __APPLE__
        pthread_setname_np( pxThreadName );
    #ورنہ
        pthread_setname_np( pthread_self(), pxThreadName );
    #اگر_ختم
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     ڈھیر_Type_t * px_انتہا_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t x_Thread_اوصاف;
    size_t ul_ڈھیر_سائز;
    صحیح iRet;

    ( خالی ) pthread_once( &h_Sig_تیاری_Thread, prv_تیاری_اشارات_And_Scheduler_Policy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_چوٹی_کا_ڈھیر + 1 ) - 1;
    px_چوٹی_کا_ڈھیر = ( ڈھیر_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_ڈھیر_سائز = ( size_t ) ( px_چوٹی_کا_ڈھیر + 1 - px_انتہا_کا_ڈھیر ) * حجم( *px_چوٹی_کا_ڈھیر );
    configASSERT( ul_ڈھیر_سائز > حجم( Thread_t ) );
    ( خالی ) ul_ڈھیر_سائز; /* suppress set but not used warning */

    thread->px_رمز = px_رمز;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &x_Thread_اوصاف );

    thread->ev = event_create();

    v_پورٹ_Enter_Critical();

    iRet = pthread_create( &thread->pthread, &x_Thread_اوصاف,
                           prv_Wait_For_آغاز, thread );

    اگر( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    v_پورٹ_Exit_Critical();

    واپس px_چوٹی_کا_ڈھیر;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_آغاز_پہلا_Task( خالی )
{
    Thread_t * px_پہلا_Thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( px_پہلا_Thread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    صحیح iSignal;
    sigset_t x_اشارات;

    hMainThread = pthread_self();
    prv_پورٹ_سیٹ_Current_Thread_Name( "Scheduler" );

    /* Start the timer that generates the tick ISR(SIGALRM).
     * Interrupts are disabled here already. */
    prv_تیاری_Timer_مداخلت();

    /*
     * Block SIG_RESUME before starting any tasks so the main thread can sigwait on it.
     * To sigwait on an unblocked signal is undefined.
     * https://pubs.opengroup.org/onlinepubs/009604499/functions/sigwait.html
     */
    sigemptyset( &x_اشارات );
    sigaddset( &x_اشارات, SIG_RESUME );
    ( خالی ) pthread_sigmask( SIG_BLOCK, &x_اشارات, تہی );

    /* Start the first task. */
    v_پورٹ_آغاز_پہلا_Task();

    /* Wait until signaled by vPortEndScheduler(). */
    جب( x_Scheduler_انتہا != pdTRUE )
    {
        sigwait( &x_اشارات, &iSignal );
    }

    /*
     * clear out the variable that is used to end the scheduler, otherwise
     * subsequent scheduler restarts will end immediately.
     */
    x_Scheduler_انتہا = pdFALSE;

    /* Reset pthread_once_t, needed to restart the scheduler again.
     * memset the internal struct members for MacOS/Linux Compatibility */
    #اگر __APPLE__
        h_Sig_تیاری_Thread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_کلید_Once.__sig = _PTHREAD_ONCE_SIG_init;
        memset( ( خالی * ) &h_Sig_تیاری_Thread.__opaque, 0, حجم( h_Sig_تیاری_Thread.__opaque ) );
        memset( ( خالی * ) &h_Thread_کلید_Once.__opaque, 0, حجم( h_Thread_کلید_Once.__opaque ) );
    #ورنہ /* Linux PTHREAD library*/
        h_Sig_تیاری_Thread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_کلید_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #اگر_ختم /* __APPLE__*/

    /* Restore original signal mask. */
    ( خالی ) pthread_sigmask( SIG_SETMASK, &x_Scheduler_Original_Signal_نقاب, تہی );

    واپس 0;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    Thread_t * pxCurrentThread;
    بنیاد_Type_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    x_Timer_Tick_Thread_Should_تسلسل = false;
    pthread_join( hTimerTickThread, تہی );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    x_Scheduler_انتہا = pdTRUE;
    ( خالی ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    اگر( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Enter_Critical( خالی )
{
    اگر( uxCriticalNesting == 0 )
    {
        v_پورٹ_Disable_Interrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Exit_Critical( خالی )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    اگر( uxCriticalNesting == 0 )
    {
        v_پورٹ_Enable_Interrupts();
    }
}
/*-----------------------------------------------------------*/

ساکن خالی prv_پورٹ_Yield_From_ISR( خالی )
{
    Thread_t * x_Thread_مقصد_Suspend;
    Thread_t * x_Thread_مقصد_Resume;

    x_Thread_مقصد_Suspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    x_Thread_مقصد_Resume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( x_Thread_مقصد_Resume, x_Thread_مقصد_Suspend );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Yield( خالی )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    v_پورٹ_Enter_Critical();

    prv_پورٹ_Yield_From_ISR();

    v_پورٹ_Exit_Critical();
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Disable_Interrupts( خالی )
{
    اگر( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &x_All_اشارات, تہی );
    }
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Enable_Interrupts( خالی )
{
    اگر( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &x_All_اشارات, تہی );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t x_پورٹ_سیٹ_مداخلت_نقاب( خالی )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    واپس ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Clear_مداخلت_نقاب( UBaseType_t ux_نقاب )
{
    ( خالی ) ux_نقاب;
}
/*-----------------------------------------------------------*/

ساکن uint64_t prv_Get_وقت_Ns( خالی )
{
    ساخت timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    واپس ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

ساکن خالی * prvTimerTickHandler( خالی * arg )
{
    ( خالی ) arg;

    prvMarkAsFreeRTOSThread();

    prv_پورٹ_سیٹ_Current_Thread_Name( "Scheduler timer" );

    جب( x_Timer_Tick_Thread_Should_تسلسل )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( پورٹ_TICK_شرح_MICROSECONDS );
    }

    واپس تہی;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
خالی prv_تیاری_Timer_مداخلت( خالی )
{
    x_Timer_Tick_Thread_Should_تسلسل = true;
    pthread_create( &hTimerTickThread, تہی, prvTimerTickHandler, تہی );

    prv_آغاز_وقت_Ns = prv_Get_وقت_Ns();
}
/*-----------------------------------------------------------*/

ساکن خالی v_پورٹ_System_Tick_Handler( صحیح sig )
{
    اگر( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * px_Thread_مقصد_Suspend;
        Thread_t * px_Thread_مقصد_Resume;

        ( خالی ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        px_Thread_مقصد_Suspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        اگر( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            px_Thread_مقصد_Resume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( px_Thread_مقصد_Resume, px_Thread_مقصد_Suspend );
        }

        uxCriticalNesting--;
    }
    ورنہ
    {
        fprintf( stderr, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Thread_Dying( خالی * px_Task_مقصد_Delete,
                       متلون بنیاد_Type_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( px_Task_مقصد_Delete );

    ( خالی ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Cancel_Thread( خالی * px_Task_مقصد_Delete )
{
    Thread_t * px_Thread_مقصد_Cancel = prvGetThreadFromTask( px_Task_مقصد_Delete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( px_Thread_مقصد_Cancel->pthread );
    event_signal( px_Thread_مقصد_Cancel->ev );
    pthread_join( px_Thread_مقصد_Cancel->pthread, تہی );
    event_delete( px_Thread_مقصد_Cancel->ev );
}
/*-----------------------------------------------------------*/

ساکن خالی * prv_Wait_For_آغاز( خالی * pvParams )
{
    Thread_t * pxThread = pvParams;

    prvMarkAsFreeRTOSThread();

    prvSuspendSelf( pxThread );

    /* Resumed for the first time, unblocks all signals. */
    uxCriticalNesting = 0;
    v_پورٹ_Enable_Interrupts();

    /* Set thread name */
    prv_پورٹ_سیٹ_Current_Thread_Name( pcTaskGetName( xTaskGetCurrentTaskHandle() ) );

    /* Call the task's entry point. */
    pxThread->px_رمز( pxThread->pvParams );

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, so application writers can
     * catch the error. */
    configASSERT( pdFALSE );

    واپس تہی;
}
/*-----------------------------------------------------------*/

ساکن خالی prvSwitchThread( Thread_t * px_Thread_مقصد_Resume,
                             Thread_t * px_Thread_مقصد_Suspend )
{
    بنیاد_Type_t uxSavedCriticalNesting;

    اگر( px_Thread_مقصد_Suspend != px_Thread_مقصد_Resume )
    {
        /*
         * Switch tasks.
         *
         * The critical section nesting is per-task, so save it on the
         * stack of the current (suspending thread), restoring it when
         * we switch back to this task.
         */
        uxSavedCriticalNesting = uxCriticalNesting;

        prvResumeThread( px_Thread_مقصد_Resume );

        اگر( px_Thread_مقصد_Suspend->xDying == pdTRUE )
        {
            pthread_exit( تہی );
        }

        prvSuspendSelf( px_Thread_مقصد_Suspend );

        uxCriticalNesting = uxSavedCriticalNesting;
    }
}
/*-----------------------------------------------------------*/

ساکن خالی prvSuspendSelf( Thread_t * thread )
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

ساکن خالی prvResumeThread( Thread_t * xThreadId )
{
    اگر( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

ساکن خالی prv_تیاری_اشارات_And_Scheduler_Policy( خالی )
{
    ساخت sigaction sigtick;
    صحیح iRet;

    hMainThread = pthread_self();

    /* Initialise common signal masks. */
    sigfillset( &x_All_اشارات );

    /* Don't block SIGINT so this can be used to break into GDB while
     * in a critical section. */
    sigdelset( &x_All_اشارات, SIGINT );

    /*
     * Block all signals in this thread so all new threads
     * inherits this mask.
     *
     * When a thread is resumed for the first time, all signals
     * will be unblocked.
     */
    ( خالی ) pthread_sigmask( SIG_SETMASK,
                              &x_All_اشارات,
                              &x_Scheduler_Original_Signal_نقاب );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = v_پورٹ_System_Tick_Handler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, تہی );

    اگر( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_پورٹ_Get_تسلسل_وقت( خالی )
{
    ساخت tms xTimes;

    times( &xTimes );

    واپس ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
