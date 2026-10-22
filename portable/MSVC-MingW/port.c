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
#అన్తర్భావ <stdio.h>

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

#నిర్వచితమైతే WIN32_LEAN_AND_సగటు
    #అన్తర్భావ <winsock2.h>
#లేకపోతే
    #అన్తర్భావ <winsock.h>
#అయితే_ముగింపు

#నిర్వచితమైతే _MSC_VER
    #అన్తర్భావ <timeapi.h>
    #సూచన comment(lib, "winmm.lib")
#లేకపోతే
    #అన్తర్భావ <mmsystem.h>
#అయితే_ముగింపు

#నిర్వచించు పోర్టు_MAX_INTERRUPTS                          ( ( uint32_t ) పరిమాణం( uint32_t ) * 8UL ) /* The number of bits in an uint32_t. */
#నిర్వచించు పోర్టు_NO_CRITICAL_NESTING                     ( ( uint32_t ) 0 )

/* The priorities at which the various components of the simulation execute. */
#నిర్వచించు పోర్టు_DELETE_SELF_THREAD_ప్రాధాన్యత             THREAD_ప్రాధాన్యత_సమయం_CRITICAL /* Must be highest. */
#నిర్వచించు పోర్టు_SIMULATED_INTERRUPTS_THREAD_ప్రాధాన్యత    THREAD_ప్రాధాన్యత_సమయం_CRITICAL
#నిర్వచించు పోర్టు_SIMULATED_TIMER_THREAD_ప్రాధాన్యత         THREAD_ప్రాధాన్యత_HIGHEST
#నిర్వచించు పోర్టు_TASK_THREAD_ప్రాధాన్యత                    THREAD_ప్రాధాన్యత_ABOVE_సాధారణ

/*
 * Created as a high priority thread, this function uses a timer to simulate
 * a tick interrupt being generated on an embedded target.  In this Windows
 * environment the timer does not achieve anything approaching real time
 * performance though.
 */
స్థిర DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter );

/*
 * Process all the simulated interrupts - each represented by a bit in
 * ulPendingInterrupts variable.
 */
స్థిర శూన్య prvProcessSimulatedInterrupts( శూన్య );

/*
 * Interrupt handlers used by the kernel itself.  These are executed from the
 * simulated interrupt handler thread.
 */
స్థిర uint32_t prv_Process_Yield_అంతరాయం( శూన్య );
స్థిర uint32_t prv_Process_Tick_అంతరాయం( శూన్య );

/*
 * Exiting a critical section will cause the calling task to block on yield
 * event to wait for an interrupt to process if an interrupt was pended while
 * inside the critical section.  This variable protects against a recursive
 * attempt to obtain pvInterruptEventMutex if a critical section is used inside
 * an interrupt handler itself.
 */
అస్థిర పునాది_Type_t x_Inside_అంతరాయం = pdFALSE;

/*
 * Called when the process exits to let Windows know the high timer resolution
 * is no longer required.
 */
స్థిర BOOL WINAPI prv_చివర_Process( DWORD dwCtrlType );

/*-----------------------------------------------------------*/

/* The WIN32 simulator runs each task in a thread.  The context switching is
 * managed by the threads, so the task stack does not have to be managed directly,
 * although the task stack is still used to hold an xThreadState structure this is
 * the only thing it will ever hold.  The structure indirectly maps the task handle
 * to a thread handle. */
రకనిర్వచనం నిర్మాణం
{
    /* Handle of the thread that executes the task. */
    శూన్య * pvThread;

    /* Event used to make sure the thread does not execute past a yield point
     * between the call to SuspendThread() to suspend the thread and the
     * asynchronous SuspendThread() operation actually being performed. */
    శూన్య * pvYieldEvent;
} ThreadState_t;

/* Simulated interrupts waiting to be processed.  This is a bit mask where each
 * bit represents one interrupt, so a maximum of 32 interrupts can be simulated. */
స్థిర అస్థిర uint32_t ulPendingInterrupts = 0UL;

/* An event used to inform the simulated interrupt processing thread (a high
 * priority thread that simulated interrupt processing) that an interrupt is
 * pending. */
స్థిర శూన్య * pv_అంతరాయం_Event = ఖాళీ;

/* Mutex used to protect all the simulated interrupt variables that are accessed
 * by multiple threads. */
స్థిర శూన్య * pv_అంతరాయం_Event_Mutex = ఖాళీ;

/* The critical nesting count for the currently executing task.  This is
 * initialised to a non-zero value so interrupts do not become enabled during
 * the initialisation phase.  As each task has its own critical nesting value
 * ulCriticalNesting will get set to zero when the first task runs.  This
 * initialisation is probably not critical in this simulated environment as the
 * simulated interrupt handlers do not get created until the FreeRTOS scheduler is
 * started anyway. */
స్థిర అస్థిర uint32_t ulCriticalNesting = 9999UL;

/* Handlers for all the simulated software interrupts.  The first two positions
 * are used for the Yield and Tick interrupts so are handled slightly differently,
 * all the other interrupts can be user defined. */
స్థిర uint32_t (* ulIsrHandler[ పోర్టు_MAX_INTERRUPTS ])( శూన్య ) = { 0 };

/* Pointer to the TCB of the currently executing task. */
బాహ్య శూన్య * అస్థిర pxCurrentTCB;

/* Used to ensure nothing is processed during the startup sequence. */
స్థిర పునాది_Type_t x_పోర్టు_Running = pdFALSE;

/*-----------------------------------------------------------*/

స్థిర DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter )
{
    TickType_t x_Minimum_Windows_ఖండం_సమయం;
    TIMECAPS x_సమయం_Caps;
    TickType_t x_Wait_సమయం_Between_Ticks = పోర్టు_TICK_PERIOD_MS;
    HANDLE hTimer = ఖాళీ;
    LARGE_INTEGER li_Due_సమయం;
    BOOL bSuccess;

    /* Set the timer resolution to the maximum possible. */
    ఒకవేళ( సమయం_Get_Dev_Caps( &x_సమయం_Caps, పరిమాణం( x_సమయం_Caps ) ) == MMSYSERR_NOERROR )
    {
        x_Minimum_Windows_ఖండం_సమయం = ( TickType_t ) x_సమయం_Caps.wPeriodMin;
        సమయం_Begin_Period( x_సమయం_Caps.wPeriodMin );

        /* Register an exit handler so the timeBeginPeriod() function can be
         * matched with a timeEndPeriod() when the application exits. */
        సమితి_Console_Ctrl_Handler( prv_చివర_Process, TRUE );
    }
    లేకపోతే
    {
        x_Minimum_Windows_ఖండం_సమయం = ( TickType_t ) 20;
    }

    /* Just to prevent compiler warnings. */
    ( శూన్య ) lpParameter;

    /* Tick time for the timer is adjusted with the maximum available
     resolution. */
    ఒకవేళ( పోర్టు_TICK_PERIOD_MS < x_Minimum_Windows_ఖండం_సమయం )
    {
        x_Wait_సమయం_Between_Ticks = x_Minimum_Windows_ఖండం_సమయం;
    }

    /* Convert the tick time in milliseconds to nanoseconds resolution
     for the Waitable Timer. */
    li_Due_సమయం.u.దిగువ_Part = x_Wait_సమయం_Between_Ticks * 1000 * 1000;
    li_Due_సమయం.u.ఎగువ_Part = 0;

    /* Create a synchronization Waitable Timer.*/
    hTimer = CreateWaitableTimer( ఖాళీ, FALSE, ఖాళీ );

    configASSERT( hTimer != ఖాళీ );

    /* Set the Waitable Timer. The timer is set to run periodically at every
    xWaitTimeBetweenTicks milliseconds. */
    bSuccess = సమితి_Waitable_Timer( hTimer, &li_Due_సమయం, x_Wait_సమయం_Between_Ticks, ఖాళీ, ఖాళీ, 0 );
    configASSERT( bSuccess );

    అయితే( x_పోర్టు_Running == pdTRUE )
    {
        /* Wait until the timer expires and we can access the simulated interrupt
         * variables. */

        WaitForSingleObject( hTimer, INFINITE );

        v_పోర్టు_Generate_Simulated_అంతరాయం_From_Windows_Thread( పోర్టు_అంతరాయం_TICK );
    }

    తిరిగి 0;
}
/*-----------------------------------------------------------*/

స్థిర BOOL WINAPI prv_చివర_Process( DWORD dwCtrlType )
{
    TIMECAPS x_సమయం_Caps;

    ( శూన్య ) dwCtrlType;

    ఒకవేళ( సమయం_Get_Dev_Caps( &x_సమయం_Caps, పరిమాణం( x_సమయం_Caps ) ) == MMSYSERR_NOERROR )
    {
        /* Match the call to timeBeginPeriod( xTimeCaps.wPeriodMin ) made when
         * the process started with a timeEndPeriod() as the process exits. */
        సమయం_చివర_Period( x_సమయం_Caps.wPeriodMin );
    }

    తిరిగి pdFALSE;
}
/*-----------------------------------------------------------*/

దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    ThreadState_t * pxThreadState = ఖాళీ;
    int8_t * pc_శిఖరం_యొక్క_దొంతర = ( int8_t * ) px_శిఖరం_యొక్క_దొంతర;
    స్థిరరాశి కొలత_T x_దొంతర_కొలత = 1024; /* Set the size to a small number which will get rounded up to the minimum possible. */

    /* In this simulated case a stack is not initialised, but instead a thread
     * is created that will execute the task being created.  The thread handles
     * the context switching itself.  The ThreadState_t object is placed onto
     * the stack that was created for the task - so the stack buffer is still
     * used, just not in the conventional way.  It will not be used for anything
     * other than holding this structure. */
    pxThreadState = ( ThreadState_t * ) ( pc_శిఖరం_యొక్క_దొంతర - పరిమాణం( ThreadState_t ) );

    /* Create the event used to prevent the thread from executing past its yield
     * point if the SuspendThread() call that suspends the thread does not take
     * effect immediately (it is an asynchronous call). */
    pxThreadState->pvYieldEvent = CreateEvent( ఖాళీ,   /* Default security attributes. */
                                               FALSE,  /* Auto reset. */
                                               FALSE,  /* Start not signalled. */
                                               ఖాళీ ); /* No name. */


#నిర్వచితమైతే __GNUC__
    /* GCC reports the warning for the cast operation from TaskFunction_t to LPTHREAD_START_ROUTINE. */
    /* Disable this warning here by the #pragma option. */
#సూచన GCC diagnostic నెట్టు
#సూచన GCC diagnostic ignored "-Wcast-function-type"
#అయితే_ముగింపు
    /* Create the thread itself. */
    pxThreadState->pvThread = CreateThread( ఖాళీ, x_దొంతర_కొలత, ( LPTHREAD_ప్రారంభం_ROUTINE ) px_సంకేతం, pvParameters, CREATE_SUSPENDED | దొంతర_కొలత_PARAM_IS_A_RESERVATION, ఖాళీ );
#నిర్వచితమైతే __GNUC__
#సూచన GCC diagnostic తీయి
#అయితే_ముగింపు

    configASSERT( pxThreadState->pvThread ); /* See comment where TerminateThread() is called. */
    సమితి_Thread_Affinity_ముసుగు( pxThreadState->pvThread, 0x01 );
    సమితి_Thread_ప్రాధాన్యత_Boost( pxThreadState->pvThread, TRUE );
    సమితి_Thread_ప్రాధాన్యత( pxThreadState->pvThread, పోర్టు_TASK_THREAD_ప్రాధాన్యత );

    తిరిగి ( దొంతర_Type_t * ) pxThreadState;
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    శూన్య * pvHandle = ఖాళీ;
    int32_t lSuccess;
    ThreadState_t * pxThreadState = ఖాళీ;
    SYSTEM_INFO xSystemInfo;

    /* This port runs windows threads with extremely high priority.  All the
     * threads execute on the same core - to prevent locking up the host only start
     * if the host has multiple cores. */
    GetSystemInfo( &xSystemInfo );

    ఒకవేళ( xSystemInfo.dw_సంఖ్య_యొక్క_Processors <= 1 )
    {
        రాయి( "This version of the FreeRTOS Windows port can only be used on multi-core hosts.\r\n" );
        lSuccess = pdFAIL;
    }
    లేకపోతే
    {
        lSuccess = pdPASS;

        /* The highest priority class is used to [try to] prevent other Windows
         * activity interfering with FreeRTOS timing too much. */
        ఒకవేళ( సమితి_ప్రాధాన్యత_Class( GetCurrentProcess(), REALTIME_ప్రాధాన్యత_CLASS ) == 0 )
        {
            రాయి( "SetPriorityClass() failed\r\n" );
        }

        /* Install the interrupt handlers used by the scheduler itself. */
        v_పోర్టు_సమితి_అంతరాయం_Handler( పోర్టు_అంతరాయం_YIELD, prv_Process_Yield_అంతరాయం );
        v_పోర్టు_సమితి_అంతరాయం_Handler( పోర్టు_అంతరాయం_TICK, prv_Process_Tick_అంతరాయం );

        /* Create the events and mutexes that are used to synchronise all the
         * threads. */
        pv_అంతరాయం_Event_Mutex = CreateMutex( ఖాళీ, FALSE, ఖాళీ );
        pv_అంతరాయం_Event = CreateEvent( ఖాళీ, FALSE, FALSE, ఖాళీ );

        ఒకవేళ( ( pv_అంతరాయం_Event_Mutex == ఖాళీ ) || ( pv_అంతరాయం_Event == ఖాళీ ) )
        {
            lSuccess = pdFAIL;
        }

        /* Set the priority of this thread such that it is above the priority of
         * the threads that run tasks.  This higher priority is required to ensure
         * simulated interrupts take priority over tasks. */
        pvHandle = GetCurrentThread();

        ఒకవేళ( pvHandle == ఖాళీ )
        {
            lSuccess = pdFAIL;
        }
    }

    ఒకవేళ( lSuccess == pdPASS )
    {
        ఒకవేళ( సమితి_Thread_ప్రాధాన్యత( pvHandle, పోర్టు_SIMULATED_INTERRUPTS_THREAD_ప్రాధాన్యత ) == 0 )
        {
            lSuccess = pdFAIL;
        }

        సమితి_Thread_ప్రాధాన్యత_Boost( pvHandle, TRUE );
        సమితి_Thread_Affinity_ముసుగు( pvHandle, 0x01 );
    }

    ఒకవేళ( lSuccess == pdPASS )
    {
        /* Start the thread that simulates the timer peripheral to generate
         * tick interrupts.  The priority is set below that of the simulated
         * interrupt handler so the interrupt event mutex is used for the
         * handshake / overrun protection. */
        pvHandle = CreateThread( ఖాళీ, 0, prvSimulatedPeripheralTimer, ఖాళీ, CREATE_SUSPENDED, ఖాళీ );

        ఒకవేళ( pvHandle != ఖాళీ )
        {
            సమితి_Thread_ప్రాధాన్యత( pvHandle, పోర్టు_SIMULATED_TIMER_THREAD_ప్రాధాన్యత );
            సమితి_Thread_ప్రాధాన్యత_Boost( pvHandle, TRUE );
            సమితి_Thread_Affinity_ముసుగు( pvHandle, 0x01 );
            ResumeThread( pvHandle );
        }

        /* Start the highest priority task by obtaining its associated thread
         * state structure, in which is stored the thread handle. */
        pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );
        ulCriticalNesting = పోర్టు_NO_CRITICAL_NESTING;

        /* The scheduler is now running. */
        x_పోర్టు_Running = pdTRUE;

        /* Start the first task. */
        ResumeThread( pxThreadState->pvThread );

        /* Handle all simulated interrupts - including yield requests and
         * simulated ticks. */
        prvProcessSimulatedInterrupts();
    }

    /* Would not expect to return from prvProcessSimulatedInterrupts(), so should
     * not get here. */
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

స్థిర uint32_t prv_Process_Yield_అంతరాయం( శూన్య )
{
    /* Always return true as this is a yield. */
    తిరిగి pdTRUE;
}
/*-----------------------------------------------------------*/

స్థిర uint32_t prv_Process_Tick_అంతరాయం( శూన్య )
{
    uint32_t ulSwitchRequired;

    /* Process the tick itself. */
    configASSERT( x_పోర్టు_Running );
    ulSwitchRequired = ( uint32_t ) xTaskIncrementTick();

    తిరిగి ulSwitchRequired;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prvProcessSimulatedInterrupts( శూన్య )
{
    uint32_t ulSwitchRequired, i;
    ThreadState_t * pxThreadState;
    శూన్య * pvObjectList[ 2 ];
    CONTEXT xContext;
    DWORD x_Win_Api_ఫలితం;
    స్థిరరాశి DWORD xTimeoutMilliseconds = 1000;

    /* Going to block on the mutex that ensured exclusive access to the simulated
     * interrupt objects, and the event that signals that a simulated interrupt
     * should be processed. */
    pvObjectList[ 0 ] = pv_అంతరాయం_Event_Mutex;
    pvObjectList[ 1 ] = pv_అంతరాయం_Event;

    /* Create a pending tick to ensure the first task is started as soon as
     * this thread pends. */
    ulPendingInterrupts |= ( 1UL << పోర్టు_అంతరాయం_TICK );
    సమితి_Event( pv_అంతరాయం_Event );

    అయితే( x_పోర్టు_Running == pdTRUE )
    {
        x_Inside_అంతరాయం = pdFALSE;

        /* Wait with timeout so that we can exit from this loop when
         * the scheduler is stopped by calling vPortEndScheduler. */
        x_Win_Api_ఫలితం = Wait_For_గుణిజం_Objects( పరిమాణం( pvObjectList ) / పరిమాణం( శూన్య * ), pvObjectList, TRUE, xTimeoutMilliseconds );

        ఒకవేళ( x_Win_Api_ఫలితం != WAIT_TIMEOUT )
        {
            /* Cannot be in a critical section to get here.  Tasks that exit a
             * critical section will block on a yield mutex to wait for an interrupt to
             * process if an interrupt was set pending while the task was inside the
             * critical section.  xInsideInterrupt prevents interrupts that contain
             * critical sections from doing the same. */
            x_Inside_అంతరాయం = pdTRUE;

            /* Used to indicate whether the simulated interrupt processing has
             * necessitated a context switch to another task/thread. */
            ulSwitchRequired = pdFALSE;

            /* For each interrupt we are interested in processing, each of which is
             * represented by a bit in the 32bit ulPendingInterrupts variable. */
            కొరకు( i = 0; i < పోర్టు_MAX_INTERRUPTS; i++ )
            {
                /* Is the simulated interrupt pending? */
                ఒకవేళ( ( ulPendingInterrupts & ( 1UL << i ) ) != 0 )
                {
                    /* Is a handler installed? */
                    ఒకవేళ( ulIsrHandler[ i ] != ఖాళీ )
                    {
                        /* Run the actual handler.  Handlers return pdTRUE if they
                         * necessitate a context switch. */
                        ఒకవేళ( ulIsrHandler[ i ]() != pdFALSE )
                        {
                            /* A bit mask is used purely to help debugging. */
                            ulSwitchRequired |= ( 1UL << i );
                        }
                    }

                    /* Clear the interrupt pending bit. */
                    ulPendingInterrupts &= ~( 1UL << i );
                }
            }

            ఒకవేళ( ulSwitchRequired != pdFALSE )
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
                ( శూన్య ) GetThreadContext( pxThreadState->pvThread, &xContext );

                /* Select the next task to run. */
                vTaskSwitchContext();

                /* Obtain the state of the task now selected to enter the
                 * Running state. */
                pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pxCurrentTCB );

                /* pxThreadState->pvThread can be NULL if the task deleted
                 * itself - but a deleted task should never be resumed here. */
                configASSERT( pxThreadState->pvThread != ఖాళీ );
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
            సమితి_Event( pxThreadState->pvYieldEvent );
            ReleaseMutex( pv_అంతరాయం_Event_Mutex );
        }
    }
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Delete_Thread( శూన్య * pv_Task_గమ్యం_Delete )
{
    ThreadState_t * pxThreadState;
    uint32_t ul_Error_సంకేతం;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( శూన్య ) ul_Error_సంకేతం;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pv_Task_గమ్యం_Delete );

    /* Check that the thread is still valid, it might have been closed by
     * vPortCloseRunningThread() - which will be the case if the task associated
     * with the thread originally deleted itself rather than being deleted by a
     * different task. */
    ఒకవేళ( pxThreadState->pvThread != ఖాళీ )
    {
        WaitForSingleObject( pv_అంతరాయం_Event_Mutex, INFINITE );

        /* !!! This is not a nice way to terminate a thread, and will eventually
         * result in resources being depleted if tasks frequently delete other
         * tasks (rather than deleting themselves) as the task stacks will not be
         * freed. */
        ul_Error_సంకేతం = TerminateThread( pxThreadState->pvThread, 0 );
        configASSERT( ul_Error_సంకేతం );

        ul_Error_సంకేతం = CloseHandle( pxThreadState->pvThread );
        configASSERT( ul_Error_సంకేతం );

        ReleaseMutex( pv_అంతరాయం_Event_Mutex );
    }
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Close_Running_Thread( శూన్య * pv_Task_గమ్యం_Delete,
                              అస్థిర పునాది_Type_t * pxPendYield )
{
    ThreadState_t * pxThreadState;
    శూన్య * pvThread;
    uint32_t ul_Error_సంకేతం;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( శూన్య ) ul_Error_సంకేతం;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pv_Task_గమ్యం_Delete );
    pvThread = pxThreadState->pvThread;

    /* Raise the Windows priority of the thread to ensure the FreeRTOS scheduler
     * does not run and swap it out before it is closed.  If that were to happen
     * the thread would never run again and effectively be a thread handle and
     * memory leak. */
    సమితి_Thread_ప్రాధాన్యత( pvThread, పోర్టు_DELETE_SELF_THREAD_ప్రాధాన్యత );

    /* This function will not return, therefore a yield is set as pending to
     * ensure a context switch occurs away from this thread on the next tick. */
    *pxPendYield = pdTRUE;

    /* Mark the thread associated with this task as invalid so
     * vPortDeleteThread() does not try to terminate it. */
    pxThreadState->pvThread = ఖాళీ;

    /* Close the thread. */
    ul_Error_సంకేతం = CloseHandle( pvThread );
    configASSERT( ul_Error_సంకేతం );

    /* This is called from a critical section, which must be exited before the
     * thread stops. */
    taskEXIT_CRITICAL();

    /* Record that a yield is pending so that the next tick interrupt switches
     * out this thread regardless of the value of configUSE_PREEMPTION. This is
     * needed when a task deletes itself - the taskYIELD_WITHIN_API within
     * vTaskDelete does not get called because this function never returns. If
     * we do not pend portINTERRUPT_YIELD here, the next task is not scheduled
     * when configUSE_PREEMPTION is set to 0. */
    ఒకవేళ( pv_అంతరాయం_Event_Mutex != ఖాళీ )
    {
        WaitForSingleObject( pv_అంతరాయం_Event_Mutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << పోర్టు_అంతరాయం_YIELD );
        ReleaseMutex( pv_అంతరాయం_Event_Mutex );
    }

    CloseHandle( pxThreadState->pvYieldEvent );
    ExitThread( 0 );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    x_పోర్టు_Running = pdFALSE;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Generate_Simulated_అంతరాయం( uint32_t ul_అంతరాయం_సంఖ్య )
{
    ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

    configASSERT( x_పోర్టు_Running );

    ఒకవేళ( ( ul_అంతరాయం_సంఖ్య < పోర్టు_MAX_INTERRUPTS ) && ( pv_అంతరాయం_Event_Mutex != ఖాళీ ) )
    {
        WaitForSingleObject( pv_అంతరాయం_Event_Mutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << ul_అంతరాయం_సంఖ్య );

        /* The simulated interrupt is now held pending, but don't actually
         * process it yet if this call is within a critical section.  It is
         * possible for this to be in a critical section as calls to wait for
         * mutexes are accumulative.  If in a critical section then the event
         * will get set when the critical section nesting count is wound back
         * down to zero. */
        ఒకవేళ( ulCriticalNesting == పోర్టు_NO_CRITICAL_NESTING )
        {
            సమితి_Event( pv_అంతరాయం_Event );

            /* Going to wait for an event - make sure the event is not already
             * signaled. */
            ResetEvent( pxThreadState->pvYieldEvent );
        }

        ReleaseMutex( pv_అంతరాయం_Event_Mutex );

        ఒకవేళ( ulCriticalNesting == పోర్టు_NO_CRITICAL_NESTING )
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

శూన్య v_పోర్టు_Generate_Simulated_అంతరాయం_From_Windows_Thread( uint32_t ul_అంతరాయం_సంఖ్య )
{
    ఒకవేళ( x_పోర్టు_Running == pdTRUE )
    {
        /* Can't proceed if in a critical section as pvInterruptEventMutex won't
         * be available. */
        WaitForSingleObject( pv_అంతరాయం_Event_Mutex, INFINITE );

        /* Pending a user defined interrupt to be handled in simulated interrupt
         * handler thread. */
        ulPendingInterrupts |= ( 1UL << ul_అంతరాయం_సంఖ్య );

        /* The interrupt is now pending - notify the simulated interrupt
         * handler thread.  Must be outside of a critical section to get here so
         * the handler thread can execute immediately pvInterruptEventMutex is
         * released. */
        configASSERT( ulCriticalNesting == 0UL );
        సమితి_Event( pv_అంతరాయం_Event );

        /* Give back the mutex so the simulated interrupt handler unblocks
         * and can access the interrupt handler variables. */
        ReleaseMutex( pv_అంతరాయం_Event_Mutex );
    }
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_సమితి_అంతరాయం_Handler( uint32_t ul_అంతరాయం_సంఖ్య,
                               uint32_t ( * pvHandler )( శూన్య ) )
{
    ఒకవేళ( ul_అంతరాయం_సంఖ్య < పోర్టు_MAX_INTERRUPTS )
    {
        ఒకవేళ( pv_అంతరాయం_Event_Mutex != ఖాళీ )
        {
            WaitForSingleObject( pv_అంతరాయం_Event_Mutex, INFINITE );
            ulIsrHandler[ ul_అంతరాయం_సంఖ్య ] = pvHandler;
            ReleaseMutex( pv_అంతరాయం_Event_Mutex );
        }
        లేకపోతే
        {
            ulIsrHandler[ ul_అంతరాయం_సంఖ్య ] = pvHandler;
        }
    }
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    ఒకవేళ( x_పోర్టు_Running == pdTRUE )
    {
        /* The interrupt event mutex is held for the entire critical section,
         * effectively disabling (simulated) interrupts. */
        WaitForSingleObject( pv_అంతరాయం_Event_Mutex, INFINITE );
    }

    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    int32_t lMutexNeedsReleasing;

    /* The interrupt event mutex should already be held by this thread as it was
     * obtained on entry to the critical section. */
    lMutexNeedsReleasing = pdTRUE;

    ఒకవేళ( ulCriticalNesting > పోర్టు_NO_CRITICAL_NESTING )
    {
        ulCriticalNesting--;

        /* Don't need to wait for any pending interrupts to execute if the
         * critical section was exited from inside an interrupt. */
        ఒకవేళ( ( ulCriticalNesting == పోర్టు_NO_CRITICAL_NESTING ) && ( x_Inside_అంతరాయం == pdFALSE ) )
        {
            /* Were any interrupts set to pending while interrupts were
             * (simulated) disabled? */
            ఒకవేళ( ulPendingInterrupts != 0UL )
            {
                ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

                configASSERT( x_పోర్టు_Running );

                /* The interrupt won't actually executed until
                 * pvInterruptEventMutex is released as it waits on both
                 * pvInterruptEventMutex and pvInterruptEvent.
                 * pvInterruptEvent is only set when the simulated
                 * interrupt is pended if the interrupt is pended
                 * from outside a critical section - hence it is set
                 * here. */
                సమితి_Event( pv_అంతరాయం_Event );

                /* The calling task is going to wait for an event to ensure the
                 * interrupt that is pending executes immediately after the
                 * critical section is exited - so make sure the event is not
                 * already signaled. */
                ResetEvent( pxThreadState->pvYieldEvent );

                /* Mutex will be released now so the (simulated) interrupt can
                 * execute, so does not require releasing on function exit. */
                lMutexNeedsReleasing = pdFALSE;
                ReleaseMutex( pv_అంతరాయం_Event_Mutex );
                WaitForSingleObject( pxThreadState->pvYieldEvent, INFINITE );
            }
        }
    }

    ఒకవేళ( pv_అంతరాయం_Event_Mutex != ఖాళీ )
    {
        ఒకవేళ( lMutexNeedsReleasing == pdTRUE )
        {
            configASSERT( x_పోర్టు_Running );
            ReleaseMutex( pv_అంతరాయం_Event_Mutex );
        }
    }
}
/*-----------------------------------------------------------*/
