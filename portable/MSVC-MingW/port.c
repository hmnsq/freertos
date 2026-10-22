/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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

/* Standard includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ WIN32_LEAN_AND_ਔਸਤ
    #ਅਨ੍ਤਰ੍ਭਾਵ <winsock2.h>
#ਨਹੀਂਤਾਂ
    #ਅਨ੍ਤਰ੍ਭਾਵ <winsock.h>
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
    #ਅਨ੍ਤਰ੍ਭਾਵ <timeapi.h>
    #ਹਦਾਇਤ comment(lib, "winmm.lib")
#ਨਹੀਂਤਾਂ
    #ਅਨ੍ਤਰ੍ਭਾਵ <mmsystem.h>
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_INTERRUPTS                          ( ( uint32_t ) ਆਕਾਰ( uint32_t ) * 8UL ) /* The number of bits in an uint32_t. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_CRITICAL_NESTING                     ( ( uint32_t ) 0 )

/* The priorities at which the various components of the simulation execute. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DELETE_SELF_THREAD_ਤਰਜੀਹ             THREAD_ਤਰਜੀਹ_ਸਮਾਂ_CRITICAL /* Must be highest. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SIMULATED_INTERRUPTS_THREAD_ਤਰਜੀਹ    THREAD_ਤਰਜੀਹ_ਸਮਾਂ_CRITICAL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SIMULATED_TIMER_THREAD_ਤਰਜੀਹ         THREAD_ਤਰਜੀਹ_HIGHEST
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_THREAD_ਤਰਜੀਹ                    THREAD_ਤਰਜੀਹ_ABOVE_ਸਾਧਾਰਨ

/*
 * Created as a high priority thread, this function uses a timer to simulate
 * a tick interrupt being generated on an embedded target.  In this Windows
 * environment the timer does not achieve anything approaching real time
 * performance though.
 */
ਸਥਿਰ DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter );

/*
 * Process all the simulated interrupts - each represented by a bit in
 * ulPendingInterrupts variable.
 */
ਸਥਿਰ ਖਾਲੀ prvProcessSimulatedInterrupts( ਖਾਲੀ );

/*
 * Interrupt handlers used by the kernel itself.  These are executed from the
 * simulated interrupt handler thread.
 */
ਸਥਿਰ uint32_t prv_Process_Yield_ਰੁਕਾਵਟ( ਖਾਲੀ );
ਸਥਿਰ uint32_t prv_Process_Tick_ਰੁਕਾਵਟ( ਖਾਲੀ );

/*
 * Exiting a critical section will cause the calling task to block on yield
 * event to wait for an interrupt to process if an interrupt was pended while
 * inside the critical section.  This variable protects against a recursive
 * attempt to obtain pvInterruptEventMutex if a critical section is used inside
 * an interrupt handler itself.
 */
ਅਸਥਿਰ ਅਧਾਰ_Type_t x_Inside_ਰੁਕਾਵਟ = pdFALSE;

/*
 * Called when the process exits to let Windows know the high timer resolution
 * is no longer required.
 */
ਸਥਿਰ BOOL WINAPI prv_ਸਿਰਾ_Process( DWORD dwCtrlType );

/*-----------------------------------------------------------*/

/* The WIN32 simulator runs each task in a thread.  The context switching is
 * managed by the threads, so the task stack does not have to be managed directly,
 * although the task stack is still used to hold an xThreadState structure this is
 * the only thing it will ever hold.  The structure indirectly maps the task handle
 * to a thread handle. */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    /* Handle of the thread that executes the task. */
    ਖਾਲੀ * pvThread;

    /* Event used to make sure the thread does not execute past a yield point
     * between the call to SuspendThread() to suspend the thread and the
     * asynchronous SuspendThread() operation actually being performed. */
    ਖਾਲੀ * pvYieldEvent;
} ThreadState_t;

/* Simulated interrupts waiting to be processed.  This is a bit mask where each
 * bit represents one interrupt, so a maximum of 32 interrupts can be simulated. */
ਸਥਿਰ ਅਸਥਿਰ uint32_t ulPendingInterrupts = 0UL;

/* An event used to inform the simulated interrupt processing thread (a high
 * priority thread that simulated interrupt processing) that an interrupt is
 * pending. */
ਸਥਿਰ ਖਾਲੀ * pv_ਰੁਕਾਵਟ_Event = ਨਿਰਾ;

/* Mutex used to protect all the simulated interrupt variables that are accessed
 * by multiple threads. */
ਸਥਿਰ ਖਾਲੀ * pv_ਰੁਕਾਵਟ_Event_Mutex = ਨਿਰਾ;

/* The critical nesting count for the currently executing task.  This is
 * initialised to a non-zero value so interrupts do not become enabled during
 * the initialisation phase.  As each task has its own critical nesting value
 * ulCriticalNesting will get set to zero when the first task runs.  This
 * initialisation is probably not critical in this simulated environment as the
 * simulated interrupt handlers do not get created until the FreeRTOS scheduler is
 * started anyway. */
ਸਥਿਰ ਅਸਥਿਰ uint32_t ulCriticalNesting = 9999UL;

/* Handlers for all the simulated software interrupts.  The first two positions
 * are used for the Yield and Tick interrupts so are handled slightly differently,
 * all the other interrupts can be user defined. */
ਸਥਿਰ uint32_t (* ulIsrHandler[ ਪੋਰਟ_MAX_INTERRUPTS ])( ਖਾਲੀ ) = { 0 };

/* Pointer to the TCB of the currently executing task. */
ਬਾਹਰੀ ਖਾਲੀ * ਅਸਥਿਰ pxCurrentTCB;

/* Used to ensure nothing is processed during the startup sequence. */
ਸਥਿਰ ਅਧਾਰ_Type_t x_ਪੋਰਟ_Running = pdFALSE;

/*-----------------------------------------------------------*/

ਸਥਿਰ DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter )
{
    TickType_t x_Minimum_Windows_ਖੰਡ_ਸਮਾਂ;
    TIMECAPS x_ਸਮਾਂ_Caps;
    TickType_t x_Wait_ਸਮਾਂ_Between_Ticks = ਪੋਰਟ_TICK_PERIOD_MS;
    HANDLE hTimer = ਨਿਰਾ;
    LARGE_INTEGER li_Due_ਸਮਾਂ;
    BOOL bSuccess;

    /* Set the timer resolution to the maximum possible. */
    ਜੇ( ਸਮਾਂ_Get_Dev_Caps( &x_ਸਮਾਂ_Caps, ਆਕਾਰ( x_ਸਮਾਂ_Caps ) ) == MMSYSERR_NOERROR )
    {
        x_Minimum_Windows_ਖੰਡ_ਸਮਾਂ = ( TickType_t ) x_ਸਮਾਂ_Caps.wPeriodMin;
        ਸਮਾਂ_Begin_Period( x_ਸਮਾਂ_Caps.wPeriodMin );

        /* Register an exit handler so the timeBeginPeriod() function can be
         * matched with a timeEndPeriod() when the application exits. */
        ਸੈੱਟ_Console_Ctrl_Handler( prv_ਸਿਰਾ_Process, TRUE );
    }
    ਨਹੀਂਤਾਂ
    {
        x_Minimum_Windows_ਖੰਡ_ਸਮਾਂ = ( TickType_t ) 20;
    }

    /* Just to prevent compiler warnings. */
    ( ਖਾਲੀ ) lpParameter;

    /* Tick time for the timer is adjusted with the maximum available
     resolution. */
    ਜੇ( ਪੋਰਟ_TICK_PERIOD_MS < x_Minimum_Windows_ਖੰਡ_ਸਮਾਂ )
    {
        x_Wait_ਸਮਾਂ_Between_Ticks = x_Minimum_Windows_ਖੰਡ_ਸਮਾਂ;
    }

    /* Convert the tick time in milliseconds to nanoseconds resolution
     for the Waitable Timer. */
    li_Due_ਸਮਾਂ.u.ਨੀਵਾਂ_Part = x_Wait_ਸਮਾਂ_Between_Ticks * 1000 * 1000;
    li_Due_ਸਮਾਂ.u.ਉੱਚਾ_Part = 0;

    /* Create a synchronization Waitable Timer.*/
    hTimer = CreateWaitableTimer( ਨਿਰਾ, FALSE, ਨਿਰਾ );

    configASSERT( hTimer != ਨਿਰਾ );

    /* Set the Waitable Timer. The timer is set to run periodically at every
    xWaitTimeBetweenTicks milliseconds. */
    bSuccess = ਸੈੱਟ_Waitable_Timer( hTimer, &li_Due_ਸਮਾਂ, x_Wait_ਸਮਾਂ_Between_Ticks, ਨਿਰਾ, ਨਿਰਾ, 0 );
    configASSERT( bSuccess );

    ਜਦੋਂ( x_ਪੋਰਟ_Running == pdTRUE )
    {
        /* Wait until the timer expires and we can access the simulated interrupt
         * variables. */

        WaitForSingleObject( hTimer, INFINITE );

        v_ਪੋਰਟ_Generate_Simulated_ਰੁਕਾਵਟ_From_Windows_Thread( ਪੋਰਟ_ਰੁਕਾਵਟ_TICK );
    }

    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ BOOL WINAPI prv_ਸਿਰਾ_Process( DWORD dwCtrlType )
{
    TIMECAPS x_ਸਮਾਂ_Caps;

    ( ਖਾਲੀ ) dwCtrlType;

    ਜੇ( ਸਮਾਂ_Get_Dev_Caps( &x_ਸਮਾਂ_Caps, ਆਕਾਰ( x_ਸਮਾਂ_Caps ) ) == MMSYSERR_NOERROR )
    {
        /* Match the call to timeBeginPeriod( xTimeCaps.wPeriodMin ) made when
         * the process started with a timeEndPeriod() as the process exits. */
        ਸਮਾਂ_ਸਿਰਾ_Period( x_ਸਮਾਂ_Caps.wPeriodMin );
    }

    ਵਾਪਸ pdFALSE;
}
/*-----------------------------------------------------------*/

ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    ThreadState_t * pxThreadState = ਨਿਰਾ;
    int8_t * pc_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( int8_t * ) px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
    ਅਚਲ ਮਾਪ_T x_ਢੇਰ_ਮਾਪ = 1024; /* Set the size to a small number which will get rounded up to the minimum possible. */

    /* In this simulated case a stack is not initialised, but instead a thread
     * is created that will execute the task being created.  The thread handles
     * the context switching itself.  The ThreadState_t object is placed onto
     * the stack that was created for the task - so the stack buffer is still
     * used, just not in the conventional way.  It will not be used for anything
     * other than holding this structure. */
    pxThreadState = ( ThreadState_t * ) ( pc_ਸਿਖਰ_ਦਾ_ਢੇਰ - ਆਕਾਰ( ThreadState_t ) );

    /* Create the event used to prevent the thread from executing past its yield
     * point if the SuspendThread() call that suspends the thread does not take
     * effect immediately (it is an asynchronous call). */
    pxThreadState->pvYieldEvent = CreateEvent( ਨਿਰਾ,   /* Default security attributes. */
                                               FALSE,  /* Auto reset. */
                                               FALSE,  /* Start not signalled. */
                                               ਨਿਰਾ ); /* No name. */


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __GNUC__
    /* GCC reports the warning for the cast operation from TaskFunction_t to LPTHREAD_START_ROUTINE. */
    /* Disable this warning here by the #pragma option. */
#ਹਦਾਇਤ GCC diagnostic ਧੱਕੋ
#ਹਦਾਇਤ GCC diagnostic ignored "-Wcast-function-type"
#ਜੇ_ਅੰਤ
    /* Create the thread itself. */
    pxThreadState->pvThread = CreateThread( ਨਿਰਾ, x_ਢੇਰ_ਮਾਪ, ( LPTHREAD_ਸ਼ੁਰੂ_ROUTINE ) px_ਕੋਡ, pvParameters, CREATE_SUSPENDED | ਢੇਰ_ਮਾਪ_PARAM_IS_A_RESERVATION, ਨਿਰਾ );
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __GNUC__
#ਹਦਾਇਤ GCC diagnostic ਕੱਢੋ
#ਜੇ_ਅੰਤ

    configASSERT( pxThreadState->pvThread ); /* See comment where TerminateThread() is called. */
    ਸੈੱਟ_Thread_Affinity_ਨਕਾਬ( pxThreadState->pvThread, 0x01 );
    ਸੈੱਟ_Thread_ਤਰਜੀਹ_Boost( pxThreadState->pvThread, TRUE );
    ਸੈੱਟ_Thread_ਤਰਜੀਹ( pxThreadState->pvThread, ਪੋਰਟ_TASK_THREAD_ਤਰਜੀਹ );

    ਵਾਪਸ ( ਢੇਰ_Type_t * ) pxThreadState;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    ਖਾਲੀ * pvHandle = ਨਿਰਾ;
    int32_t lSuccess;
    ThreadState_t * pxThreadState = ਨਿਰਾ;
    SYSTEM_INFO xSystemInfo;

    /* This port runs windows threads with extremely high priority.  All the
     * threads execute on the same core - to prevent locking up the host only start
     * if the host has multiple cores. */
    GetSystemInfo( &xSystemInfo );

    ਜੇ( xSystemInfo.dw_ਸੰਖਿਆ_ਦਾ_Processors <= 1 )
    {
        ਲਿਖੋ( "This version of the FreeRTOS Windows port can only be used on multi-core hosts.\r\n" );
        lSuccess = pdFAIL;
    }
    ਨਹੀਂਤਾਂ
    {
        lSuccess = pdPASS;

        /* The highest priority class is used to [try to] prevent other Windows
         * activity interfering with FreeRTOS timing too much. */
        ਜੇ( ਸੈੱਟ_ਤਰਜੀਹ_Class( GetCurrentProcess(), REALTIME_ਤਰਜੀਹ_CLASS ) == 0 )
        {
            ਲਿਖੋ( "SetPriorityClass() failed\r\n" );
        }

        /* Install the interrupt handlers used by the scheduler itself. */
        v_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_Handler( ਪੋਰਟ_ਰੁਕਾਵਟ_YIELD, prv_Process_Yield_ਰੁਕਾਵਟ );
        v_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_Handler( ਪੋਰਟ_ਰੁਕਾਵਟ_TICK, prv_Process_Tick_ਰੁਕਾਵਟ );

        /* Create the events and mutexes that are used to synchronise all the
         * threads. */
        pv_ਰੁਕਾਵਟ_Event_Mutex = CreateMutex( ਨਿਰਾ, FALSE, ਨਿਰਾ );
        pv_ਰੁਕਾਵਟ_Event = CreateEvent( ਨਿਰਾ, FALSE, FALSE, ਨਿਰਾ );

        ਜੇ( ( pv_ਰੁਕਾਵਟ_Event_Mutex == ਨਿਰਾ ) || ( pv_ਰੁਕਾਵਟ_Event == ਨਿਰਾ ) )
        {
            lSuccess = pdFAIL;
        }

        /* Set the priority of this thread such that it is above the priority of
         * the threads that run tasks.  This higher priority is required to ensure
         * simulated interrupts take priority over tasks. */
        pvHandle = GetCurrentThread();

        ਜੇ( pvHandle == ਨਿਰਾ )
        {
            lSuccess = pdFAIL;
        }
    }

    ਜੇ( lSuccess == pdPASS )
    {
        ਜੇ( ਸੈੱਟ_Thread_ਤਰਜੀਹ( pvHandle, ਪੋਰਟ_SIMULATED_INTERRUPTS_THREAD_ਤਰਜੀਹ ) == 0 )
        {
            lSuccess = pdFAIL;
        }

        ਸੈੱਟ_Thread_ਤਰਜੀਹ_Boost( pvHandle, TRUE );
        ਸੈੱਟ_Thread_Affinity_ਨਕਾਬ( pvHandle, 0x01 );
    }

    ਜੇ( lSuccess == pdPASS )
    {
        /* Start the thread that simulates the timer peripheral to generate
         * tick interrupts.  The priority is set below that of the simulated
         * interrupt handler so the interrupt event mutex is used for the
         * handshake / overrun protection. */
        pvHandle = CreateThread( ਨਿਰਾ, 0, prvSimulatedPeripheralTimer, ਨਿਰਾ, CREATE_SUSPENDED, ਨਿਰਾ );

        ਜੇ( pvHandle != ਨਿਰਾ )
        {
            ਸੈੱਟ_Thread_ਤਰਜੀਹ( pvHandle, ਪੋਰਟ_SIMULATED_TIMER_THREAD_ਤਰਜੀਹ );
            ਸੈੱਟ_Thread_ਤਰਜੀਹ_Boost( pvHandle, TRUE );
            ਸੈੱਟ_Thread_Affinity_ਨਕਾਬ( pvHandle, 0x01 );
            ResumeThread( pvHandle );
        }

        /* Start the highest priority task by obtaining its associated thread
         * state structure, in which is stored the thread handle. */
        pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );
        ulCriticalNesting = ਪੋਰਟ_NO_CRITICAL_NESTING;

        /* The scheduler is now running. */
        x_ਪੋਰਟ_Running = pdTRUE;

        /* Start the first task. */
        ResumeThread( pxThreadState->pvThread );

        /* Handle all simulated interrupts - including yield requests and
         * simulated ticks. */
        prvProcessSimulatedInterrupts();
    }

    /* Would not expect to return from prvProcessSimulatedInterrupts(), so should
     * not get here. */
    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ uint32_t prv_Process_Yield_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    /* Always return true as this is a yield. */
    ਵਾਪਸ pdTRUE;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ uint32_t prv_Process_Tick_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    uint32_t ulSwitchRequired;

    /* Process the tick itself. */
    configASSERT( x_ਪੋਰਟ_Running );
    ulSwitchRequired = ( uint32_t ) xTaskIncrementTick();

    ਵਾਪਸ ulSwitchRequired;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvProcessSimulatedInterrupts( ਖਾਲੀ )
{
    uint32_t ulSwitchRequired, i;
    ThreadState_t * pxThreadState;
    ਖਾਲੀ * pvObjectList[ 2 ];
    CONTEXT xContext;
    DWORD x_Win_Api_ਨਤੀਜਾ;
    ਅਚਲ DWORD xTimeoutMilliseconds = 1000;

    /* Going to block on the mutex that ensured exclusive access to the simulated
     * interrupt objects, and the event that signals that a simulated interrupt
     * should be processed. */
    pvObjectList[ 0 ] = pv_ਰੁਕਾਵਟ_Event_Mutex;
    pvObjectList[ 1 ] = pv_ਰੁਕਾਵਟ_Event;

    /* Create a pending tick to ensure the first task is started as soon as
     * this thread pends. */
    ulPendingInterrupts |= ( 1UL << ਪੋਰਟ_ਰੁਕਾਵਟ_TICK );
    ਸੈੱਟ_Event( pv_ਰੁਕਾਵਟ_Event );

    ਜਦੋਂ( x_ਪੋਰਟ_Running == pdTRUE )
    {
        x_Inside_ਰੁਕਾਵਟ = pdFALSE;

        /* Wait with timeout so that we can exit from this loop when
         * the scheduler is stopped by calling vPortEndScheduler. */
        x_Win_Api_ਨਤੀਜਾ = Wait_For_ਗੁਣਜ_Objects( ਆਕਾਰ( pvObjectList ) / ਆਕਾਰ( ਖਾਲੀ * ), pvObjectList, TRUE, xTimeoutMilliseconds );

        ਜੇ( x_Win_Api_ਨਤੀਜਾ != WAIT_TIMEOUT )
        {
            /* Cannot be in a critical section to get here.  Tasks that exit a
             * critical section will block on a yield mutex to wait for an interrupt to
             * process if an interrupt was set pending while the task was inside the
             * critical section.  xInsideInterrupt prevents interrupts that contain
             * critical sections from doing the same. */
            x_Inside_ਰੁਕਾਵਟ = pdTRUE;

            /* Used to indicate whether the simulated interrupt processing has
             * necessitated a context switch to another task/thread. */
            ulSwitchRequired = pdFALSE;

            /* For each interrupt we are interested in processing, each of which is
             * represented by a bit in the 32bit ulPendingInterrupts variable. */
            ਲਈ( i = 0; i < ਪੋਰਟ_MAX_INTERRUPTS; i++ )
            {
                /* Is the simulated interrupt pending? */
                ਜੇ( ( ulPendingInterrupts & ( 1UL << i ) ) != 0 )
                {
                    /* Is a handler installed? */
                    ਜੇ( ulIsrHandler[ i ] != ਨਿਰਾ )
                    {
                        /* Run the actual handler.  Handlers return pdTRUE if they
                         * necessitate a context switch. */
                        ਜੇ( ulIsrHandler[ i ]() != pdFALSE )
                        {
                            /* A bit mask is used purely to help debugging. */
                            ulSwitchRequired |= ( 1UL << i );
                        }
                    }

                    /* Clear the interrupt pending bit. */
                    ulPendingInterrupts &= ~( 1UL << i );
                }
            }

            ਜੇ( ulSwitchRequired != pdFALSE )
            {
                /* Suspend the old thread. */
                pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );
                SuspendThread( pxThreadState->pvThread );

                /* Ensure the thread is actually suspended by performing a
                 * synchronous operation that can only complete when the thread
                 * is actually suspended. The below code asks for dummy register
                 * data. Experimentation shows that these two lines don't appear
                 * to do anything now, but according to
                 * https://devblogs.microsoft.com/oldnewthing/20150205-00/?p=44743
                 * they do - so as they do not harm (slight run-time hit). */
                xContext.ContextFlags = CONTEXT_INTEGER;
                ( ਖਾਲੀ ) GetThreadContext( pxThreadState->pvThread, &xContext );

                /* Select the next task to run. */
                vTaskSwitchContext();

                /* Obtain the state of the task now selected to enter the
                 * Running state. */
                pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pxCurrentTCB );

                /* pxThreadState->pvThread can be NULL if the task deleted
                 * itself - but a deleted task should never be resumed here. */
                configASSERT( pxThreadState->pvThread != ਨਿਰਾ );
                ResumeThread( pxThreadState->pvThread );
            }

            /* If the thread that is about to be resumed stopped running
             * because it yielded then it will wait on an event when it resumed
             * (to ensure it does not continue running after the call to
             * SuspendThread() above as SuspendThread() is asynchronous).
             * Signal the event to ensure the thread can proceed now it is
             * valid for it to do so.  Signaling the event is benign in the case that
             * the task was switched out asynchronously by an interrupt as the event
             * is reset before the task blocks on it. */
            pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pxCurrentTCB );
            ਸੈੱਟ_Event( pxThreadState->pvYieldEvent );
            ReleaseMutex( pv_ਰੁਕਾਵਟ_Event_Mutex );
        }
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Delete_Thread( ਖਾਲੀ * pv_Task_ਮੰਜ਼ਿਲ_Delete )
{
    ThreadState_t * pxThreadState;
    uint32_t ul_Error_ਕੋਡ;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( ਖਾਲੀ ) ul_Error_ਕੋਡ;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pv_Task_ਮੰਜ਼ਿਲ_Delete );

    /* Check that the thread is still valid, it might have been closed by
     * vPortCloseRunningThread() - which will be the case if the task associated
     * with the thread originally deleted itself rather than being deleted by a
     * different task. */
    ਜੇ( pxThreadState->pvThread != ਨਿਰਾ )
    {
        WaitForSingleObject( pv_ਰੁਕਾਵਟ_Event_Mutex, INFINITE );

        /* !!! This is not a nice way to terminate a thread, and will eventually
         * result in resources being depleted if tasks frequently delete other
         * tasks (rather than deleting themselves) as the task stacks will not be
         * freed. */
        ul_Error_ਕੋਡ = TerminateThread( pxThreadState->pvThread, 0 );
        configASSERT( ul_Error_ਕੋਡ );

        ul_Error_ਕੋਡ = CloseHandle( pxThreadState->pvThread );
        configASSERT( ul_Error_ਕੋਡ );

        ReleaseMutex( pv_ਰੁਕਾਵਟ_Event_Mutex );
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Close_Running_Thread( ਖਾਲੀ * pv_Task_ਮੰਜ਼ਿਲ_Delete,
                              ਅਸਥਿਰ ਅਧਾਰ_Type_t * pxPendYield )
{
    ThreadState_t * pxThreadState;
    ਖਾਲੀ * pvThread;
    uint32_t ul_Error_ਕੋਡ;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( ਖਾਲੀ ) ul_Error_ਕੋਡ;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pv_Task_ਮੰਜ਼ਿਲ_Delete );
    pvThread = pxThreadState->pvThread;

    /* Raise the Windows priority of the thread to ensure the FreeRTOS scheduler
     * does not run and swap it out before it is closed.  If that were to happen
     * the thread would never run again and effectively be a thread handle and
     * memory leak. */
    ਸੈੱਟ_Thread_ਤਰਜੀਹ( pvThread, ਪੋਰਟ_DELETE_SELF_THREAD_ਤਰਜੀਹ );

    /* This function will not return, therefore a yield is set as pending to
     * ensure a context switch occurs away from this thread on the next tick. */
    *pxPendYield = pdTRUE;

    /* Mark the thread associated with this task as invalid so
     * vPortDeleteThread() does not try to terminate it. */
    pxThreadState->pvThread = ਨਿਰਾ;

    /* Close the thread. */
    ul_Error_ਕੋਡ = CloseHandle( pvThread );
    configASSERT( ul_Error_ਕੋਡ );

    /* This is called from a critical section, which must be exited before the
     * thread stops. */
    taskEXIT_CRITICAL();

    /* Record that a yield is pending so that the next tick interrupt switches
     * out this thread regardless of the value of configUSE_PREEMPTION. This is
     * needed when a task deletes itself - the taskYIELD_WITHIN_API within
     * vTaskDelete does not get called because this function never returns. If
     * we do not pend portINTERRUPT_YIELD here, the next task is not scheduled
     * when configUSE_PREEMPTION is set to 0. */
    ਜੇ( pv_ਰੁਕਾਵਟ_Event_Mutex != ਨਿਰਾ )
    {
        WaitForSingleObject( pv_ਰੁਕਾਵਟ_Event_Mutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << ਪੋਰਟ_ਰੁਕਾਵਟ_YIELD );
        ReleaseMutex( pv_ਰੁਕਾਵਟ_Event_Mutex );
    }

    CloseHandle( pxThreadState->pvYieldEvent );
    ExitThread( 0 );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    x_ਪੋਰਟ_Running = pdFALSE;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Generate_Simulated_ਰੁਕਾਵਟ( uint32_t ul_ਰੁਕਾਵਟ_ਸੰਖਿਆ )
{
    ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

    configASSERT( x_ਪੋਰਟ_Running );

    ਜੇ( ( ul_ਰੁਕਾਵਟ_ਸੰਖਿਆ < ਪੋਰਟ_MAX_INTERRUPTS ) && ( pv_ਰੁਕਾਵਟ_Event_Mutex != ਨਿਰਾ ) )
    {
        WaitForSingleObject( pv_ਰੁਕਾਵਟ_Event_Mutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << ul_ਰੁਕਾਵਟ_ਸੰਖਿਆ );

        /* The simulated interrupt is now held pending, but don't actually
         * process it yet if this call is within a critical section.  It is
         * possible for this to be in a critical section as calls to wait for
         * mutexes are accumulative.  If in a critical section then the event
         * will get set when the critical section nesting count is wound back
         * down to zero. */
        ਜੇ( ulCriticalNesting == ਪੋਰਟ_NO_CRITICAL_NESTING )
        {
            ਸੈੱਟ_Event( pv_ਰੁਕਾਵਟ_Event );

            /* Going to wait for an event - make sure the event is not already
             * signaled. */
            ResetEvent( pxThreadState->pvYieldEvent );
        }

        ReleaseMutex( pv_ਰੁਕਾਵਟ_Event_Mutex );

        ਜੇ( ulCriticalNesting == ਪੋਰਟ_NO_CRITICAL_NESTING )
        {
            /* An interrupt was pended so ensure to block to allow it to
             * execute.  In most cases the (simulated) interrupt will have
             * executed before the next line is reached - so this is just to make
             * sure. */
            WaitForSingleObject( pxThreadState->pvYieldEvent, INFINITE );
        }
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Generate_Simulated_ਰੁਕਾਵਟ_From_Windows_Thread( uint32_t ul_ਰੁਕਾਵਟ_ਸੰਖਿਆ )
{
    ਜੇ( x_ਪੋਰਟ_Running == pdTRUE )
    {
        /* Can't proceed if in a critical section as pvInterruptEventMutex won't
         * be available. */
        WaitForSingleObject( pv_ਰੁਕਾਵਟ_Event_Mutex, INFINITE );

        /* Pending a user defined interrupt to be handled in simulated interrupt
         * handler thread. */
        ulPendingInterrupts |= ( 1UL << ul_ਰੁਕਾਵਟ_ਸੰਖਿਆ );

        /* The interrupt is now pending - notify the simulated interrupt
         * handler thread.  Must be outside of a critical section to get here so
         * the handler thread can execute immediately pvInterruptEventMutex is
         * released. */
        configASSERT( ulCriticalNesting == 0UL );
        ਸੈੱਟ_Event( pv_ਰੁਕਾਵਟ_Event );

        /* Give back the mutex so the simulated interrupt handler unblocks
         * and can access the interrupt handler variables. */
        ReleaseMutex( pv_ਰੁਕਾਵਟ_Event_Mutex );
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_Handler( uint32_t ul_ਰੁਕਾਵਟ_ਸੰਖਿਆ,
                               uint32_t ( * pvHandler )( ਖਾਲੀ ) )
{
    ਜੇ( ul_ਰੁਕਾਵਟ_ਸੰਖਿਆ < ਪੋਰਟ_MAX_INTERRUPTS )
    {
        ਜੇ( pv_ਰੁਕਾਵਟ_Event_Mutex != ਨਿਰਾ )
        {
            WaitForSingleObject( pv_ਰੁਕਾਵਟ_Event_Mutex, INFINITE );
            ulIsrHandler[ ul_ਰੁਕਾਵਟ_ਸੰਖਿਆ ] = pvHandler;
            ReleaseMutex( pv_ਰੁਕਾਵਟ_Event_Mutex );
        }
        ਨਹੀਂਤਾਂ
        {
            ulIsrHandler[ ul_ਰੁਕਾਵਟ_ਸੰਖਿਆ ] = pvHandler;
        }
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    ਜੇ( x_ਪੋਰਟ_Running == pdTRUE )
    {
        /* The interrupt event mutex is held for the entire critical section,
         * effectively disabling (simulated) interrupts. */
        WaitForSingleObject( pv_ਰੁਕਾਵਟ_Event_Mutex, INFINITE );
    }

    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    int32_t lMutexNeedsReleasing;

    /* The interrupt event mutex should already be held by this thread as it was
     * obtained on entry to the critical section. */
    lMutexNeedsReleasing = pdTRUE;

    ਜੇ( ulCriticalNesting > ਪੋਰਟ_NO_CRITICAL_NESTING )
    {
        ulCriticalNesting--;

        /* Don't need to wait for any pending interrupts to execute if the
         * critical section was exited from inside an interrupt. */
        ਜੇ( ( ulCriticalNesting == ਪੋਰਟ_NO_CRITICAL_NESTING ) && ( x_Inside_ਰੁਕਾਵਟ == pdFALSE ) )
        {
            /* Were any interrupts set to pending while interrupts were
             * (simulated) disabled? */
            ਜੇ( ulPendingInterrupts != 0UL )
            {
                ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

                configASSERT( x_ਪੋਰਟ_Running );

                /* The interrupt won't actually executed until
                 * pvInterruptEventMutex is released as it waits on both
                 * pvInterruptEventMutex and pvInterruptEvent.
                 * pvInterruptEvent is only set when the simulated
                 * interrupt is pended if the interrupt is pended
                 * from outside a critical section - hence it is set
                 * here. */
                ਸੈੱਟ_Event( pv_ਰੁਕਾਵਟ_Event );

                /* The calling task is going to wait for an event to ensure the
                 * interrupt that is pending executes immediately after the
                 * critical section is exited - so make sure the event is not
                 * already signaled. */
                ResetEvent( pxThreadState->pvYieldEvent );

                /* Mutex will be released now so the (simulated) interrupt can
                 * execute, so does not require releasing on function exit. */
                lMutexNeedsReleasing = pdFALSE;
                ReleaseMutex( pv_ਰੁਕਾਵਟ_Event_Mutex );
                WaitForSingleObject( pxThreadState->pvYieldEvent, INFINITE );
            }
        }
    }

    ਜੇ( pv_ਰੁਕਾਵਟ_Event_Mutex != ਨਿਰਾ )
    {
        ਜੇ( lMutexNeedsReleasing == pdTRUE )
        {
            configASSERT( x_ਪੋਰਟ_Running );
            ReleaseMutex( pv_ਰੁਕਾਵਟ_Event_Mutex );
        }
    }
}
/*-----------------------------------------------------------*/
