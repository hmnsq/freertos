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
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __linux__
    #ವ್ಯಾಖ್ಯಾನಿಸು GNU_ಮೂಲ
#ಆದರೆ_ಅಂತ್ಯ
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

#ವ್ಯಾಖ್ಯಾನಿಸು SIG_RESUME    SIGUSR1

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ THREAD
{
    pthread_t pthread;
    TaskFunction_t px_ಸಂಕೇತ;
    ಶೂನ್ಯ * pvParams;
    ತಳ_Type_t xDying;
    ರಚನೆ event * ev;
} Thread_t;

/*
 * The additional per-thread data is stored at the beginning of the
 * task's stack.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ Thread_t * prvGetThreadFromTask( TaskHandle_t xTask )
{
    ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ = *( ರಾಶಿ_Type_t ** ) xTask;

    ಹಿಂತಿರುಗಿ ( Thread_t * ) ( px_ತುದಿ_ದ_ರಾಶಿ + 1 );
}

/*-----------------------------------------------------------*/

ಸ್ಥಿರ pthread_once_t h_Sig_ಸಿದ್ಧತೆ_Thread = PTHREAD_ONCE_INIT;
ಸ್ಥಿರ pthread_once_t h_Thread_ಕೀಲಿ_Once = PTHREAD_ONCE_INIT;
ಸ್ಥಿರ sigset_t x_All_ಸಂಕೇತಗಳು;
ಸ್ಥಿರ sigset_t x_Scheduler_Original_Signal_ಮುಖವಾಡ;
ಸ್ಥಿರ pthread_t hMainThread = ( pthread_t ) ಖಾಲಿ;
ಸ್ಥಿರ ಅಸ್ಥಿರ ತಳ_Type_t uxCriticalNesting;
ಸ್ಥಿರ ತಳ_Type_t x_Scheduler_ಕೊನೆ = pdFALSE;
ಸ್ಥಿರ pthread_t hTimerTickThread;
ಸ್ಥಿರ bool x_Timer_Tick_Thread_Should_ಸತತ;
ಸ್ಥಿರ uint64_t prv_ಆರಂಭ_ಸಮಯ_Ns;
ಸ್ಥಿರ pthread_key_t x_Thread_ಕೀಲಿ = 0;
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_ಸಂಕೇತಗಳು_And_Scheduler_Policy( ಶೂನ್ಯ );
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ );
ಸ್ಥಿರ ಶೂನ್ಯ * prv_Wait_For_ಆರಂಭ( ಶೂನ್ಯ * pvParams );
ಸ್ಥಿರ ಶೂನ್ಯ prvSwitchThread( Thread_t * x_Thread_ಗಮ್ಯ_Resume,
                             Thread_t * x_Thread_ಗಮ್ಯ_Suspend );
ಸ್ಥಿರ ಶೂನ್ಯ prvSuspendSelf( Thread_t * thread );
ಸ್ಥಿರ ಶೂನ್ಯ prvResumeThread( Thread_t * xThreadId );
ಸ್ಥಿರ ಶೂನ್ಯ v_ಪೋರ್ಟ್_System_Tick_Handler( ಪೂರ್ಣಾಂಕ sig );
ಸ್ಥಿರ ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ );
ಸ್ಥಿರ ಶೂನ್ಯ prv_ಪೋರ್ಟ್_Yield_From_ISR( ಶೂನ್ಯ );
ಸ್ಥಿರ ಶೂನ್ಯ prv_Thread_ಕೀಲಿ_Destructor( ಶೂನ್ಯ * pv_ದತ್ತಾಂಶ );
ಸ್ಥಿರ ಶೂನ್ಯ prv_Init_Thread_ಕೀಲಿ( ಶೂನ್ಯ );
ಸ್ಥಿರ ಶೂನ್ಯ prvMarkAsFreeRTOSThread( ಶೂನ್ಯ );
ಸ್ಥಿರ ತಳ_Type_t prvIsFreeRTOSThread( ಶೂನ್ಯ );
ಸ್ಥಿರ ಶೂನ್ಯ prv_Destroy_Thread_ಕೀಲಿ( ಶೂನ್ಯ );
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_Thread_ಕೀಲಿ_Destructor( ಶೂನ್ಯ * pv_ದತ್ತಾಂಶ )
{
    ಬಿಡುಗಡೆ( pv_ದತ್ತಾಂಶ );
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
    uint8_t * puc_Thread_ದತ್ತಾಂಶ = ಖಾಲಿ;

    ( ಶೂನ್ಯ ) pthread_once( &h_Thread_ಕೀಲಿ_Once, prv_Init_Thread_ಕೀಲಿ );

    puc_Thread_ದತ್ತಾಂಶ = ಸ್ಮರಣೆ_ಕೊಡು( 1 );
    configASSERT( puc_Thread_ದತ್ತಾಂಶ != ಖಾಲಿ );

    *puc_Thread_ದತ್ತಾಂಶ = 1;

    pthread_setspecific( x_Thread_ಕೀಲಿ, puc_Thread_ದತ್ತಾಂಶ );
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ತಳ_Type_t prvIsFreeRTOSThread( ಶೂನ್ಯ )
{
    uint8_t * puc_Thread_ದತ್ತಾಂಶ = ಖಾಲಿ;
    ತಳ_Type_t xRet = pdFALSE;

    ( ಶೂನ್ಯ ) pthread_once( &h_Thread_ಕೀಲಿ_Once, prv_Init_Thread_ಕೀಲಿ );

    puc_Thread_ದತ್ತಾಂಶ = ( uint8_t * ) pthread_getspecific( x_Thread_ಕೀಲಿ );

    ಆದರೆ( ( puc_Thread_ದತ್ತಾಂಶ != ಖಾಲಿ ) && ( *puc_Thread_ದತ್ತಾಂಶ == 1 ) )
    {
        xRet = pdTRUE;
    }

    ಹಿಂತಿರುಗಿ xRet;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_Destroy_Thread_ಕೀಲಿ( ಶೂನ್ಯ )
{
    pthread_key_delete( x_Thread_ಕೀಲಿ );
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvFatalError( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pcCall,
                           ಪೂರ್ಣಾಂಕ iErrno ) __attribute__( ( __noreturn__ ) );

ಶೂನ್ಯ prvFatalError( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pcCall,
                    ಪೂರ್ಣಾಂಕ iErrno )
{
    fprintf( stderr, "%s: %s\n", pcCall, strerror( iErrno ) );
    abort();
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಪೋರ್ಟ್_ಗಣ_Current_Thread_Name( ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * pxThreadName )
{
    #ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __APPLE__
        pthread_setname_np( pxThreadName );
    #ಇಲ್ಲದಿದ್ದರೆ
        pthread_setname_np( pthread_self(), pxThreadName );
    #ಆದರೆ_ಅಂತ್ಯ
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     ರಾಶಿ_Type_t * px_ಕೊನೆ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    Thread_t * thread;
    pthread_attr_t x_Thread_ಗುಣಲಕ್ಷಣಗಳು;
    size_t ul_ರಾಶಿ_ಗಾತ್ರ;
    ಪೂರ್ಣಾಂಕ iRet;

    ( ಶೂನ್ಯ ) pthread_once( &h_Sig_ಸಿದ್ಧತೆ_Thread, prv_ಸಿದ್ಧತೆ_ಸಂಕೇತಗಳು_And_Scheduler_Policy );

    /*
     * Store the additional thread data at the start of the stack.
     */
    thread = ( Thread_t * ) ( px_ತುದಿ_ದ_ರಾಶಿ + 1 ) - 1;
    px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t * ) thread - 1;

    /* Ensure that there is enough space to store Thread_t on the stack. */
    ul_ರಾಶಿ_ಗಾತ್ರ = ( size_t ) ( px_ತುದಿ_ದ_ರಾಶಿ + 1 - px_ಕೊನೆ_ದ_ರಾಶಿ ) * ಗಾತ್ರ( *px_ತುದಿ_ದ_ರಾಶಿ );
    configASSERT( ul_ರಾಶಿ_ಗಾತ್ರ > ಗಾತ್ರ( Thread_t ) );
    ( ಶೂನ್ಯ ) ul_ರಾಶಿ_ಗಾತ್ರ; /* suppress set but not used warning */

    thread->px_ಸಂಕೇತ = px_ಸಂಕೇತ;
    thread->pvParams = pvParameters;
    thread->xDying = pdFALSE;

    pthread_attr_init( &x_Thread_ಗುಣಲಕ್ಷಣಗಳು );

    thread->ev = event_create();

    v_ಪೋರ್ಟ್_Enter_Critical();

    iRet = pthread_create( &thread->pthread, &x_Thread_ಗುಣಲಕ್ಷಣಗಳು,
                           prv_Wait_For_ಆರಂಭ, thread );

    ಆದರೆ( iRet != 0 )
    {
        prvFatalError( "pthread_create", iRet );
    }

    v_ಪೋರ್ಟ್_Exit_Critical();

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task( ಶೂನ್ಯ )
{
    Thread_t * px_ಮೊದಲ_Thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    /* Start the first task. */
    prvResumeThread( px_ಮೊದಲ_Thread );
}
/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    ಪೂರ್ಣಾಂಕ iSignal;
    sigset_t x_ಸಂಕೇತಗಳು;

    hMainThread = pthread_self();
    prv_ಪೋರ್ಟ್_ಗಣ_Current_Thread_Name( "Scheduler" );

    /* Start the timer that generates the tick ISR(SIGALRM).
     * Interrupts are disabled here already. */
    prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ();

    /*
     * Block SIG_RESUME before starting any tasks so the main thread can sigwait on it.
     * To sigwait on an unblocked signal is undefined.
     * https://pubs.opengroup.org/onlinepubs/009604499/functions/sigwait.html
     */
    sigemptyset( &x_ಸಂಕೇತಗಳು );
    sigaddset( &x_ಸಂಕೇತಗಳು, SIG_RESUME );
    ( ಶೂನ್ಯ ) pthread_sigmask( SIG_BLOCK, &x_ಸಂಕೇತಗಳು, ಖಾಲಿ );

    /* Start the first task. */
    v_ಪೋರ್ಟ್_ಆರಂಭ_ಮೊದಲ_Task();

    /* Wait until signaled by vPortEndScheduler(). */
    ಆಗ( x_Scheduler_ಕೊನೆ != pdTRUE )
    {
        sigwait( &x_ಸಂಕೇತಗಳು, &iSignal );
    }

    /*
     * clear out the variable that is used to end the scheduler, otherwise
     * subsequent scheduler restarts will end immediately.
     */
    x_Scheduler_ಕೊನೆ = pdFALSE;

    /* Reset pthread_once_t, needed to restart the scheduler again.
     * memset the internal struct members for MacOS/Linux Compatibility */
    #ಆದರೆ __APPLE__
        h_Sig_ಸಿದ್ಧತೆ_Thread.__sig = _PTHREAD_ONCE_SIG_init;
        h_Thread_ಕೀಲಿ_Once.__sig = _PTHREAD_ONCE_SIG_init;
        memset( ( ಶೂನ್ಯ * ) &h_Sig_ಸಿದ್ಧತೆ_Thread.__opaque, 0, ಗಾತ್ರ( h_Sig_ಸಿದ್ಧತೆ_Thread.__opaque ) );
        memset( ( ಶೂನ್ಯ * ) &h_Thread_ಕೀಲಿ_Once.__opaque, 0, ಗಾತ್ರ( h_Thread_ಕೀಲಿ_Once.__opaque ) );
    #ಇಲ್ಲದಿದ್ದರೆ /* Linux PTHREAD library*/
        h_Sig_ಸಿದ್ಧತೆ_Thread = ( pthread_once_t ) PTHREAD_ONCE_INIT;
        h_Thread_ಕೀಲಿ_Once = ( pthread_once_t ) PTHREAD_ONCE_INIT;
    #ಆದರೆ_ಅಂತ್ಯ /* __APPLE__*/

    /* Restore original signal mask. */
    ( ಶೂನ್ಯ ) pthread_sigmask( SIG_SETMASK, &x_Scheduler_Original_Signal_ಮುಖವಾಡ, ಖಾಲಿ );

    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    Thread_t * pxCurrentThread;
    ತಳ_Type_t xIsFreeRTOSThread;

    /* Stop the timer tick thread. */
    x_Timer_Tick_Thread_Should_ಸತತ = false;
    pthread_join( hTimerTickThread, ಖಾಲಿ );

    /* Check whether the current thread is a FreeRTOS thread.
     * This has to happen before the scheduler is signaled to exit
     * its loop to prevent data races on the thread key. */
    xIsFreeRTOSThread = prvIsFreeRTOSThread();

    /* Signal the scheduler to exit its loop. */
    x_Scheduler_ಕೊನೆ = pdTRUE;
    ( ಶೂನ್ಯ ) pthread_kill( hMainThread, SIG_RESUME );

    /* Waiting to be deleted here. */
    ಆದರೆ( xIsFreeRTOSThread == pdTRUE )
    {
        pxCurrentThread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        event_wait( pxCurrentThread->ev );
    }

    pthread_testcancel();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    ಆದರೆ( uxCriticalNesting == 0 )
    {
        v_ಪೋರ್ಟ್_Disable_Interrupts();
    }

    uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    uxCriticalNesting--;

    /* If we have reached 0 then re-enable the interrupts. */
    ಆದರೆ( uxCriticalNesting == 0 )
    {
        v_ಪೋರ್ಟ್_Enable_Interrupts();
    }
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಪೋರ್ಟ್_Yield_From_ISR( ಶೂನ್ಯ )
{
    Thread_t * x_Thread_ಗಮ್ಯ_Suspend;
    Thread_t * x_Thread_ಗಮ್ಯ_Resume;

    x_Thread_ಗಮ್ಯ_Suspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    vTaskSwitchContext();

    x_Thread_ಗಮ್ಯ_Resume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

    prvSwitchThread( x_Thread_ಗಮ್ಯ_Resume, x_Thread_ಗಮ್ಯ_Suspend );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Yield( ಶೂನ್ಯ )
{
    /* This must never be called from outside of a FreeRTOS-owned thread, or
     * the thread could get stuck in a suspended state. */
    configASSERT( prvIsFreeRTOSThread() == pdTRUE );

    v_ಪೋರ್ಟ್_Enter_Critical();

    prv_ಪೋರ್ಟ್_Yield_From_ISR();

    v_ಪೋರ್ಟ್_Exit_Critical();
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Disable_Interrupts( ಶೂನ್ಯ )
{
    ಆದರೆ( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_BLOCK, &x_All_ಸಂಕೇತಗಳು, ಖಾಲಿ );
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enable_Interrupts( ಶೂನ್ಯ )
{
    ಆದರೆ( prvIsFreeRTOSThread() == pdTRUE )
    {
        pthread_sigmask( SIG_UNBLOCK, &x_All_ಸಂಕೇತಗಳು, ಖಾಲಿ );
    }
}
/*-----------------------------------------------------------*/

UBaseType_t x_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ( ಶೂನ್ಯ )
{
    /* Interrupts are always disabled inside ISRs (signals
     * handlers). */
    ಹಿಂತಿರುಗಿ ( UBaseType_t ) 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( UBaseType_t ux_ಮುಖವಾಡ )
{
    ( ಶೂನ್ಯ ) ux_ಮುಖವಾಡ;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ uint64_t prv_Get_ಸಮಯ_Ns( ಶೂನ್ಯ )
{
    ರಚನೆ timespec t;

    clock_gettime( CLOCK_MONOTONIC, &t );

    ಹಿಂತಿರುಗಿ ( uint64_t ) t.tv_sec * ( uint64_t ) 1000000000UL + ( uint64_t ) t.tv_nsec;
}
/*-----------------------------------------------------------*/

/* commented as part of the code below in vPortSystemTickHandler,
 * to adjust timing according to full demo requirements */
/* static uint64_t prvTickCount; */

ಸ್ಥಿರ ಶೂನ್ಯ * prvTimerTickHandler( ಶೂನ್ಯ * arg )
{
    ( ಶೂನ್ಯ ) arg;

    prvMarkAsFreeRTOSThread();

    prv_ಪೋರ್ಟ್_ಗಣ_Current_Thread_Name( "Scheduler timer" );

    ಆಗ( x_Timer_Tick_Thread_Should_ಸತತ )
    {
        /*
         * signal to the active task to cause tick handling or
         * preemption (if enabled)
         */
        Thread_t * thread = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );
        pthread_kill( thread->pthread, SIGALRM );
        usleep( ಪೋರ್ಟ್_TICK_ದರ_MICROSECONDS );
    }

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}
/*-----------------------------------------------------------*/

/*
 * Setup the systick timer to generate the tick interrupts at the required
 * frequency.
 */
ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_Timer_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    x_Timer_Tick_Thread_Should_ಸತತ = true;
    pthread_create( &hTimerTickThread, ಖಾಲಿ, prvTimerTickHandler, ಖಾಲಿ );

    prv_ಆರಂಭ_ಸಮಯ_Ns = prv_Get_ಸಮಯ_Ns();
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ v_ಪೋರ್ಟ್_System_Tick_Handler( ಪೂರ್ಣಾಂಕ sig )
{
    ಆದರೆ( prvIsFreeRTOSThread() == pdTRUE )
    {
        Thread_t * px_Thread_ಗಮ್ಯ_Suspend;
        Thread_t * px_Thread_ಗಮ್ಯ_Resume;

        ( ಶೂನ್ಯ ) sig;

        uxCriticalNesting++; /* Signals are blocked in this signal handler. */

        px_Thread_ಗಮ್ಯ_Suspend = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

        ಆದರೆ( xTaskIncrementTick() != pdFALSE )
        {
            /* Select Next Task. */
            vTaskSwitchContext();

            px_Thread_ಗಮ್ಯ_Resume = prvGetThreadFromTask( xTaskGetCurrentTaskHandle() );

            prvSwitchThread( px_Thread_ಗಮ್ಯ_Resume, px_Thread_ಗಮ್ಯ_Suspend );
        }

        uxCriticalNesting--;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        fprintf( stderr, "vPortSystemTickHandler called from non-FreeRTOS thread\n" );
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Thread_Dying( ಶೂನ್ಯ * px_Task_ಗಮ್ಯ_Delete,
                       ಅಸ್ಥಿರ ತಳ_Type_t * pxPendYield )
{
    Thread_t * pxThread = prvGetThreadFromTask( px_Task_ಗಮ್ಯ_Delete );

    ( ಶೂನ್ಯ ) pxPendYield;

    pxThread->xDying = pdTRUE;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Cancel_Thread( ಶೂನ್ಯ * px_Task_ಗಮ್ಯ_Delete )
{
    Thread_t * px_Thread_ಗಮ್ಯ_Cancel = prvGetThreadFromTask( px_Task_ಗಮ್ಯ_Delete );

    /*
     * The thread has already been suspended so it can be safely cancelled.
     */
    pthread_cancel( px_Thread_ಗಮ್ಯ_Cancel->pthread );
    event_signal( px_Thread_ಗಮ್ಯ_Cancel->ev );
    pthread_join( px_Thread_ಗಮ್ಯ_Cancel->pthread, ಖಾಲಿ );
    event_delete( px_Thread_ಗಮ್ಯ_Cancel->ev );
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ * prv_Wait_For_ಆರಂಭ( ಶೂನ್ಯ * pvParams )
{
    Thread_t * pxThread = pvParams;

    prvMarkAsFreeRTOSThread();

    prvSuspendSelf( pxThread );

    /* Resumed for the first time, unblocks all signals. */
    uxCriticalNesting = 0;
    v_ಪೋರ್ಟ್_Enable_Interrupts();

    /* Set thread name */
    prv_ಪೋರ್ಟ್_ಗಣ_Current_Thread_Name( pcTaskGetName( xTaskGetCurrentTaskHandle() ) );

    /* Call the task's entry point. */
    pxThread->px_ಸಂಕೇತ( pxThread->pvParams );

    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to. If a task wants to exit it
     * should instead call vTaskDelete( NULL ). Artificially force an assert()
     * to be triggered if configASSERT() is defined, so application writers can
     * catch the error. */
    configASSERT( pdFALSE );

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvSwitchThread( Thread_t * px_Thread_ಗಮ್ಯ_Resume,
                             Thread_t * px_Thread_ಗಮ್ಯ_Suspend )
{
    ತಳ_Type_t uxSavedCriticalNesting;

    ಆದರೆ( px_Thread_ಗಮ್ಯ_Suspend != px_Thread_ಗಮ್ಯ_Resume )
    {
        /*
         * Switch tasks.
         *
         * The critical section nesting is per-task, so save it on the
         * stack of the current (suspending thread), restoring it when
         * we switch back to this task.
         */
        uxSavedCriticalNesting = uxCriticalNesting;

        prvResumeThread( px_Thread_ಗಮ್ಯ_Resume );

        ಆದರೆ( px_Thread_ಗಮ್ಯ_Suspend->xDying == pdTRUE )
        {
            pthread_exit( ಖಾಲಿ );
        }

        prvSuspendSelf( px_Thread_ಗಮ್ಯ_Suspend );

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
    ಆದರೆ( pthread_self() != xThreadId->pthread )
    {
        event_signal( xThreadId->ev );
    }
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prv_ಸಿದ್ಧತೆ_ಸಂಕೇತಗಳು_And_Scheduler_Policy( ಶೂನ್ಯ )
{
    ರಚನೆ sigaction sigtick;
    ಪೂರ್ಣಾಂಕ iRet;

    hMainThread = pthread_self();

    /* Initialise common signal masks. */
    sigfillset( &x_All_ಸಂಕೇತಗಳು );

    /* Don't block SIGINT so this can be used to break into GDB while
     * in a critical section. */
    sigdelset( &x_All_ಸಂಕೇತಗಳು, SIGINT );

    /*
     * Block all signals in this thread so all new threads
     * inherits this mask.
     *
     * When a thread is resumed for the first time, all signals
     * will be unblocked.
     */
    ( ಶೂನ್ಯ ) pthread_sigmask( SIG_SETMASK,
                              &x_All_ಸಂಕೇತಗಳು,
                              &x_Scheduler_Original_Signal_ಮುಖವಾಡ );

    sigtick.sa_flags = 0;
    sigtick.sa_handler = v_ಪೋರ್ಟ್_System_Tick_Handler;
    sigfillset( &sigtick.sa_mask );

    iRet = sigaction( SIGALRM, &sigtick, ಖಾಲಿ );

    ಆದರೆ( iRet == -1 )
    {
        prvFatalError( "sigaction", errno );
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_ಪೋರ್ಟ್_Get_ಸತತ_ಸಮಯ( ಶೂನ್ಯ )
{
    ರಚನೆ tms xTimes;

    times( &xTimes );

    ಹಿಂತಿರುಗಿ ( uint32_t ) xTimes.tms_utime;
}
/*-----------------------------------------------------------*/
