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
#અન્તર્ભાવ <stdio.h>

/* Scheduler includes. */
#અન્તર્ભાવ "FreeRTOS.h"
#અન્તર્ભાવ "task.h"

#ifdef WIN32_LEAN_AND_MEAN
    #અન્તર્ભાવ <winsock2.h>
#નહીંતર
    #અન્તર્ભાવ <winsock.h>
#endif

#ifdef _MSC_VER
    #અન્તર્ભાવ <timeapi.h>
    #pragma comment(lib, "winmm.lib")
#નહીંતર
    #અન્તર્ભાવ <mmsystem.h>
#endif

#define portMAX_INTERRUPTS                          ( ( uint32_t ) કદ( uint32_t ) * 8UL ) /* The number of bits in an uint32_t. */
#define portNO_CRITICAL_NESTING                     ( ( uint32_t ) 0 )

/* The priorities at which the various components of the simulation execute. */
#define portDELETE_SELF_THREAD_PRIORITY             THREAD_PRIORITY_TIME_CRITICAL /* Must be highest. */
#define portSIMULATED_INTERRUPTS_THREAD_PRIORITY    THREAD_PRIORITY_TIME_CRITICAL
#define portSIMULATED_TIMER_THREAD_PRIORITY         THREAD_PRIORITY_HIGHEST
#define portTASK_THREAD_PRIORITY                    THREAD_PRIORITY_ABOVE_NORMAL

/*
 * Created as a high priority thread, this function uses a timer to simulate
 * a tick interrupt being generated on an embedded target.  In this Windows
 * environment the timer does not achieve anything approaching real time
 * performance though.
 */
સ્થિર DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter );

/*
 * Process all the simulated interrupts - each represented by a bit in
 * ulPendingInterrupts variable.
 */
સ્થિર શૂન્ય prvProcessSimulatedInterrupts( શૂન્ય );

/*
 * Interrupt handlers used by the kernel itself.  These are executed from the
 * simulated interrupt handler thread.
 */
સ્થિર uint32_t prvProcessYieldInterrupt( શૂન્ય );
સ્થિર uint32_t prvProcessTickInterrupt( શૂન્ય );

/*
 * Exiting a critical section will cause the calling task to block on yield
 * event to wait for an interrupt to process if an interrupt was pended while
 * inside the critical section.  This variable protects against a recursive
 * attempt to obtain pvInterruptEventMutex if a critical section is used inside
 * an interrupt handler itself.
 */
અસ્થિર BaseType_t xInsideInterrupt = pdFALSE;

/*
 * Called when the process exits to let Windows know the high timer resolution
 * is no longer required.
 */
સ્થિર BOOL WINAPI prvEndProcess( DWORD dwCtrlType );

/*-----------------------------------------------------------*/

/* The WIN32 simulator runs each task in a thread.  The context switching is
 * managed by the threads, so the task stack does not have to be managed directly,
 * although the task stack is still used to hold an xThreadState structure this is
 * the only thing it will ever hold.  The structure indirectly maps the task handle
 * to a thread handle. */
પ્રકારવ્યાખ્યા સંરચના
{
    /* Handle of the thread that executes the task. */
    શૂન્ય * pvThread;

    /* Event used to make sure the thread does not execute past a yield point
     * between the call to SuspendThread() to suspend the thread and the
     * asynchronous SuspendThread() operation actually being performed. */
    શૂન્ય * pvYieldEvent;
} ThreadState_t;

/* Simulated interrupts waiting to be processed.  This is a bit mask where each
 * bit represents one interrupt, so a maximum of 32 interrupts can be simulated. */
સ્થિર અસ્થિર uint32_t ulPendingInterrupts = 0UL;

/* An event used to inform the simulated interrupt processing thread (a high
 * priority thread that simulated interrupt processing) that an interrupt is
 * pending. */
સ્થિર શૂન્ય * pvInterruptEvent = ખાલી;

/* Mutex used to protect all the simulated interrupt variables that are accessed
 * by multiple threads. */
સ્થિર શૂન્ય * pvInterruptEventMutex = ખાલી;

/* The critical nesting count for the currently executing task.  This is
 * initialised to a non-zero value so interrupts do not become enabled during
 * the initialisation phase.  As each task has its own critical nesting value
 * ulCriticalNesting will get set to zero when the first task runs.  This
 * initialisation is probably not critical in this simulated environment as the
 * simulated interrupt handlers do not get created until the FreeRTOS scheduler is
 * started anyway. */
સ્થિર અસ્થિર uint32_t ulCriticalNesting = 9999UL;

/* Handlers for all the simulated software interrupts.  The first two positions
 * are used for the Yield and Tick interrupts so are handled slightly differently,
 * all the other interrupts can be user defined. */
સ્થિર uint32_t (* ulIsrHandler[ portMAX_INTERRUPTS ])( શૂન્ય ) = { 0 };

/* Pointer to the TCB of the currently executing task. */
બાહ્ય શૂન્ય * અસ્થિર pxCurrentTCB;

/* Used to ensure nothing is processed during the startup sequence. */
સ્થિર BaseType_t xPortRunning = pdFALSE;

/*-----------------------------------------------------------*/

સ્થિર DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter )
{
    TickType_t xMinimumWindowsBlockTime;
    TIMECAPS xTimeCaps;
    TickType_t xWaitTimeBetweenTicks = portTICK_PERIOD_MS;
    HANDLE hTimer = ખાલી;
    LARGE_INTEGER liDueTime;
    BOOL bSuccess;

    /* Set the timer resolution to the maximum possible. */
    જો( timeGetDevCaps( &xTimeCaps, કદ( xTimeCaps ) ) == MMSYSERR_NOERROR )
    {
        xMinimumWindowsBlockTime = ( TickType_t ) xTimeCaps.wPeriodMin;
        timeBeginPeriod( xTimeCaps.wPeriodMin );

        /* Register an exit handler so the timeBeginPeriod() function can be
         * matched with a timeEndPeriod() when the application exits. */
        SetConsoleCtrlHandler( prvEndProcess, TRUE );
    }
    નહીંતર
    {
        xMinimumWindowsBlockTime = ( TickType_t ) 20;
    }

    /* Just to prevent compiler warnings. */
    ( શૂન્ય ) lpParameter;

    /* Tick time for the timer is adjusted with the maximum available
     resolution. */
    જો( portTICK_PERIOD_MS < xMinimumWindowsBlockTime )
    {
        xWaitTimeBetweenTicks = xMinimumWindowsBlockTime;
    }

    /* Convert the tick time in milliseconds to nanoseconds resolution
     for the Waitable Timer. */
    liDueTime.u.નીચલું_Part = xWaitTimeBetweenTicks * 1000 * 1000;
    liDueTime.u.ઉપલું_Part = 0;

    /* Create a synchronization Waitable Timer.*/
    hTimer = CreateWaitableTimer( ખાલી, FALSE, ખાલી );

    configASSERT( hTimer != ખાલી );

    /* Set the Waitable Timer. The timer is set to run periodically at every
    xWaitTimeBetweenTicks milliseconds. */
    bSuccess = SetWaitableTimer( hTimer, &liDueTime, xWaitTimeBetweenTicks, ખાલી, ખાલી, 0 );
    configASSERT( bSuccess );

    જ્યારે( xPortRunning == pdTRUE )
    {
        /* Wait until the timer expires and we can access the simulated interrupt
         * variables. */

        WaitForSingleObject( hTimer, INFINITE );

        vPortGenerateSimulatedInterruptFromWindowsThread( portINTERRUPT_TICK );
    }

    પાછા 0;
}
/*-----------------------------------------------------------*/

સ્થિર BOOL WINAPI prvEndProcess( DWORD dwCtrlType )
{
    TIMECAPS xTimeCaps;

    ( શૂન્ય ) dwCtrlType;

    જો( timeGetDevCaps( &xTimeCaps, કદ( xTimeCaps ) ) == MMSYSERR_NOERROR )
    {
        /* Match the call to timeBeginPeriod( xTimeCaps.wPeriodMin ) made when
         * the process started with a timeEndPeriod() as the process exits. */
        timeEndPeriod( xTimeCaps.wPeriodMin );
    }

    પાછા pdFALSE;
}
/*-----------------------------------------------------------*/

ઢગલો_Type_t * px_Port_Initialise_ઢગલો( ઢગલો_Type_t * px_ટોચ_Of_ઢગલો,
                                     TaskFunction_t pxCode,
                                     શૂન્ય * pvParameters )
{
    ThreadState_t * pxThreadState = ખાલી;
    int8_t * pc_ટોચ_Of_ઢગલો = ( int8_t * ) px_ટોચ_Of_ઢગલો;
    અચલ SIZE_T x_ઢગલો_Size = 1024; /* Set the size to a small number which will get rounded up to the minimum possible. */

    /* In this simulated case a stack is not initialised, but instead a thread
     * is created that will execute the task being created.  The thread handles
     * the context switching itself.  The ThreadState_t object is placed onto
     * the stack that was created for the task - so the stack buffer is still
     * used, just not in the conventional way.  It will not be used for anything
     * other than holding this structure. */
    pxThreadState = ( ThreadState_t * ) ( pc_ટોચ_Of_ઢગલો - કદ( ThreadState_t ) );

    /* Create the event used to prevent the thread from executing past its yield
     * point if the SuspendThread() call that suspends the thread does not take
     * effect immediately (it is an asynchronous call). */
    pxThreadState->pvYieldEvent = CreateEvent( ખાલી,   /* Default security attributes. */
                                               FALSE,  /* Auto reset. */
                                               FALSE,  /* Start not signalled. */
                                               ખાલી ); /* No name. */


#ifdef __GNUC__
    /* GCC reports the warning for the cast operation from TaskFunction_t to LPTHREAD_START_ROUTINE. */
    /* Disable this warning here by the #pragma option. */
#pragma GCC diagnostic ધકેલો
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif
    /* Create the thread itself. */
    pxThreadState->pvThread = CreateThread( ખાલી, x_ઢગલો_Size, ( LPTHREAD_START_ROUTINE ) pxCode, pvParameters, CREATE_SUSPENDED | ઢગલો_SIZE_PARAM_IS_A_RESERVATION, ખાલી );
#ifdef __GNUC__
#pragma GCC diagnostic કાઢો
#endif

    configASSERT( pxThreadState->pvThread ); /* See comment where TerminateThread() is called. */
    SetThreadAffinityMask( pxThreadState->pvThread, 0x01 );
    SetThreadPriorityBoost( pxThreadState->pvThread, TRUE );
    SetThreadPriority( pxThreadState->pvThread, portTASK_THREAD_PRIORITY );

    પાછા ( ઢગલો_Type_t * ) pxThreadState;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( શૂન્ય )
{
    શૂન્ય * pvHandle = ખાલી;
    int32_t lSuccess;
    ThreadState_t * pxThreadState = ખાલી;
    SYSTEM_INFO xSystemInfo;

    /* This port runs windows threads with extremely high priority.  All the
     * threads execute on the same core - to prevent locking up the host only start
     * if the host has multiple cores. */
    GetSystemInfo( &xSystemInfo );

    જો( xSystemInfo.dw_સંખ્યા_Of_Processors <= 1 )
    {
        printf( "This version of the FreeRTOS Windows port can only be used on multi-core hosts.\r\n" );
        lSuccess = pdFAIL;
    }
    નહીંતર
    {
        lSuccess = pdPASS;

        /* The highest priority class is used to [try to] prevent other Windows
         * activity interfering with FreeRTOS timing too much. */
        જો( SetPriorityClass( GetCurrentProcess(), REALTIME_PRIORITY_CLASS ) == 0 )
        {
            printf( "SetPriorityClass() failed\r\n" );
        }

        /* Install the interrupt handlers used by the scheduler itself. */
        vPortSetInterruptHandler( portINTERRUPT_YIELD, prvProcessYieldInterrupt );
        vPortSetInterruptHandler( portINTERRUPT_TICK, prvProcessTickInterrupt );

        /* Create the events and mutexes that are used to synchronise all the
         * threads. */
        pvInterruptEventMutex = CreateMutex( ખાલી, FALSE, ખાલી );
        pvInterruptEvent = CreateEvent( ખાલી, FALSE, FALSE, ખાલી );

        જો( ( pvInterruptEventMutex == ખાલી ) || ( pvInterruptEvent == ખાલી ) )
        {
            lSuccess = pdFAIL;
        }

        /* Set the priority of this thread such that it is above the priority of
         * the threads that run tasks.  This higher priority is required to ensure
         * simulated interrupts take priority over tasks. */
        pvHandle = GetCurrentThread();

        જો( pvHandle == ખાલી )
        {
            lSuccess = pdFAIL;
        }
    }

    જો( lSuccess == pdPASS )
    {
        જો( SetThreadPriority( pvHandle, portSIMULATED_INTERRUPTS_THREAD_PRIORITY ) == 0 )
        {
            lSuccess = pdFAIL;
        }

        SetThreadPriorityBoost( pvHandle, TRUE );
        SetThreadAffinityMask( pvHandle, 0x01 );
    }

    જો( lSuccess == pdPASS )
    {
        /* Start the thread that simulates the timer peripheral to generate
         * tick interrupts.  The priority is set below that of the simulated
         * interrupt handler so the interrupt event mutex is used for the
         * handshake / overrun protection. */
        pvHandle = CreateThread( ખાલી, 0, prvSimulatedPeripheralTimer, ખાલી, CREATE_SUSPENDED, ખાલી );

        જો( pvHandle != ખાલી )
        {
            SetThreadPriority( pvHandle, portSIMULATED_TIMER_THREAD_PRIORITY );
            SetThreadPriorityBoost( pvHandle, TRUE );
            SetThreadAffinityMask( pvHandle, 0x01 );
            ResumeThread( pvHandle );
        }

        /* Start the highest priority task by obtaining its associated thread
         * state structure, in which is stored the thread handle. */
        pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );
        ulCriticalNesting = portNO_CRITICAL_NESTING;

        /* The scheduler is now running. */
        xPortRunning = pdTRUE;

        /* Start the first task. */
        ResumeThread( pxThreadState->pvThread );

        /* Handle all simulated interrupts - including yield requests and
         * simulated ticks. */
        prvProcessSimulatedInterrupts();
    }

    /* Would not expect to return from prvProcessSimulatedInterrupts(), so should
     * not get here. */
    પાછા 0;
}
/*-----------------------------------------------------------*/

સ્થિર uint32_t prvProcessYieldInterrupt( શૂન્ય )
{
    /* Always return true as this is a yield. */
    પાછા pdTRUE;
}
/*-----------------------------------------------------------*/

સ્થિર uint32_t prvProcessTickInterrupt( શૂન્ય )
{
    uint32_t ulSwitchRequired;

    /* Process the tick itself. */
    configASSERT( xPortRunning );
    ulSwitchRequired = ( uint32_t ) xTaskIncrementTick();

    પાછા ulSwitchRequired;
}
/*-----------------------------------------------------------*/

સ્થિર શૂન્ય prvProcessSimulatedInterrupts( શૂન્ય )
{
    uint32_t ulSwitchRequired, i;
    ThreadState_t * pxThreadState;
    શૂન્ય * pvObjectList[ 2 ];
    CONTEXT xContext;
    DWORD xWinApiResult;
    અચલ DWORD xTimeoutMilliseconds = 1000;

    /* Going to block on the mutex that ensured exclusive access to the simulated
     * interrupt objects, and the event that signals that a simulated interrupt
     * should be processed. */
    pvObjectList[ 0 ] = pvInterruptEventMutex;
    pvObjectList[ 1 ] = pvInterruptEvent;

    /* Create a pending tick to ensure the first task is started as soon as
     * this thread pends. */
    ulPendingInterrupts |= ( 1UL << portINTERRUPT_TICK );
    SetEvent( pvInterruptEvent );

    જ્યારે( xPortRunning == pdTRUE )
    {
        xInsideInterrupt = pdFALSE;

        /* Wait with timeout so that we can exit from this loop when
         * the scheduler is stopped by calling vPortEndScheduler. */
        xWinApiResult = WaitForMultipleObjects( કદ( pvObjectList ) / કદ( શૂન્ય * ), pvObjectList, TRUE, xTimeoutMilliseconds );

        જો( xWinApiResult != WAIT_TIMEOUT )
        {
            /* Cannot be in a critical section to get here.  Tasks that exit a
             * critical section will block on a yield mutex to wait for an interrupt to
             * process if an interrupt was set pending while the task was inside the
             * critical section.  xInsideInterrupt prevents interrupts that contain
             * critical sections from doing the same. */
            xInsideInterrupt = pdTRUE;

            /* Used to indicate whether the simulated interrupt processing has
             * necessitated a context switch to another task/thread. */
            ulSwitchRequired = pdFALSE;

            /* For each interrupt we are interested in processing, each of which is
             * represented by a bit in the 32bit ulPendingInterrupts variable. */
            માટે( i = 0; i < portMAX_INTERRUPTS; i++ )
            {
                /* Is the simulated interrupt pending? */
                જો( ( ulPendingInterrupts & ( 1UL << i ) ) != 0 )
                {
                    /* Is a handler installed? */
                    જો( ulIsrHandler[ i ] != ખાલી )
                    {
                        /* Run the actual handler.  Handlers return pdTRUE if they
                         * necessitate a context switch. */
                        જો( ulIsrHandler[ i ]() != pdFALSE )
                        {
                            /* A bit mask is used purely to help debugging. */
                            ulSwitchRequired |= ( 1UL << i );
                        }
                    }

                    /* Clear the interrupt pending bit. */
                    ulPendingInterrupts &= ~( 1UL << i );
                }
            }

            જો( ulSwitchRequired != pdFALSE )
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
                ( શૂન્ય ) GetThreadContext( pxThreadState->pvThread, &xContext );

                /* Select the next task to run. */
                vTaskSwitchContext();

                /* Obtain the state of the task now selected to enter the
                 * Running state. */
                pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pxCurrentTCB );

                /* pxThreadState->pvThread can be NULL if the task deleted
                 * itself - but a deleted task should never be resumed here. */
                configASSERT( pxThreadState->pvThread != ખાલી );
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
            SetEvent( pxThreadState->pvYieldEvent );
            ReleaseMutex( pvInterruptEventMutex );
        }
    }
}
/*-----------------------------------------------------------*/

શૂન્ય vPortDeleteThread( શૂન્ય * pvTaskToDelete )
{
    ThreadState_t * pxThreadState;
    uint32_t ulErrorCode;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( શૂન્ય ) ulErrorCode;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pvTaskToDelete );

    /* Check that the thread is still valid, it might have been closed by
     * vPortCloseRunningThread() - which will be the case if the task associated
     * with the thread originally deleted itself rather than being deleted by a
     * different task. */
    જો( pxThreadState->pvThread != ખાલી )
    {
        WaitForSingleObject( pvInterruptEventMutex, INFINITE );

        /* !!! This is not a nice way to terminate a thread, and will eventually
         * result in resources being depleted if tasks frequently delete other
         * tasks (rather than deleting themselves) as the task stacks will not be
         * freed. */
        ulErrorCode = TerminateThread( pxThreadState->pvThread, 0 );
        configASSERT( ulErrorCode );

        ulErrorCode = CloseHandle( pxThreadState->pvThread );
        configASSERT( ulErrorCode );

        ReleaseMutex( pvInterruptEventMutex );
    }
}
/*-----------------------------------------------------------*/

શૂન્ય vPortCloseRunningThread( શૂન્ય * pvTaskToDelete,
                              અસ્થિર BaseType_t * pxPendYield )
{
    ThreadState_t * pxThreadState;
    શૂન્ય * pvThread;
    uint32_t ulErrorCode;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( શૂન્ય ) ulErrorCode;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pvTaskToDelete );
    pvThread = pxThreadState->pvThread;

    /* Raise the Windows priority of the thread to ensure the FreeRTOS scheduler
     * does not run and swap it out before it is closed.  If that were to happen
     * the thread would never run again and effectively be a thread handle and
     * memory leak. */
    SetThreadPriority( pvThread, portDELETE_SELF_THREAD_PRIORITY );

    /* This function will not return, therefore a yield is set as pending to
     * ensure a context switch occurs away from this thread on the next tick. */
    *pxPendYield = pdTRUE;

    /* Mark the thread associated with this task as invalid so
     * vPortDeleteThread() does not try to terminate it. */
    pxThreadState->pvThread = ખાલી;

    /* Close the thread. */
    ulErrorCode = CloseHandle( pvThread );
    configASSERT( ulErrorCode );

    /* This is called from a critical section, which must be exited before the
     * thread stops. */
    taskEXIT_CRITICAL();

    /* Record that a yield is pending so that the next tick interrupt switches
     * out this thread regardless of the value of configUSE_PREEMPTION. This is
     * needed when a task deletes itself - the taskYIELD_WITHIN_API within
     * vTaskDelete does not get called because this function never returns. If
     * we do not pend portINTERRUPT_YIELD here, the next task is not scheduled
     * when configUSE_PREEMPTION is set to 0. */
    જો( pvInterruptEventMutex != ખાલી )
    {
        WaitForSingleObject( pvInterruptEventMutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << portINTERRUPT_YIELD );
        ReleaseMutex( pvInterruptEventMutex );
    }

    CloseHandle( pxThreadState->pvYieldEvent );
    ExitThread( 0 );
}
/*-----------------------------------------------------------*/

શૂન્ય vPortEndScheduler( શૂન્ય )
{
    xPortRunning = pdFALSE;
}
/*-----------------------------------------------------------*/

શૂન્ય vPortGenerateSimulatedInterrupt( uint32_t ul_Interrupt_સંખ્યા )
{
    ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

    configASSERT( xPortRunning );

    જો( ( ul_Interrupt_સંખ્યા < portMAX_INTERRUPTS ) && ( pvInterruptEventMutex != ખાલી ) )
    {
        WaitForSingleObject( pvInterruptEventMutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << ul_Interrupt_સંખ્યા );

        /* The simulated interrupt is now held pending, but don't actually
         * process it yet if this call is within a critical section.  It is
         * possible for this to be in a critical section as calls to wait for
         * mutexes are accumulative.  If in a critical section then the event
         * will get set when the critical section nesting count is wound back
         * down to zero. */
        જો( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            SetEvent( pvInterruptEvent );

            /* Going to wait for an event - make sure the event is not already
             * signaled. */
            ResetEvent( pxThreadState->pvYieldEvent );
        }

        ReleaseMutex( pvInterruptEventMutex );

        જો( ulCriticalNesting == portNO_CRITICAL_NESTING )
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

શૂન્ય vPortGenerateSimulatedInterruptFromWindowsThread( uint32_t ul_Interrupt_સંખ્યા )
{
    જો( xPortRunning == pdTRUE )
    {
        /* Can't proceed if in a critical section as pvInterruptEventMutex won't
         * be available. */
        WaitForSingleObject( pvInterruptEventMutex, INFINITE );

        /* Pending a user defined interrupt to be handled in simulated interrupt
         * handler thread. */
        ulPendingInterrupts |= ( 1UL << ul_Interrupt_સંખ્યા );

        /* The interrupt is now pending - notify the simulated interrupt
         * handler thread.  Must be outside of a critical section to get here so
         * the handler thread can execute immediately pvInterruptEventMutex is
         * released. */
        configASSERT( ulCriticalNesting == 0UL );
        SetEvent( pvInterruptEvent );

        /* Give back the mutex so the simulated interrupt handler unblocks
         * and can access the interrupt handler variables. */
        ReleaseMutex( pvInterruptEventMutex );
    }
}
/*-----------------------------------------------------------*/

શૂન્ય vPortSetInterruptHandler( uint32_t ul_Interrupt_સંખ્યા,
                               uint32_t ( * pvHandler )( શૂન્ય ) )
{
    જો( ul_Interrupt_સંખ્યા < portMAX_INTERRUPTS )
    {
        જો( pvInterruptEventMutex != ખાલી )
        {
            WaitForSingleObject( pvInterruptEventMutex, INFINITE );
            ulIsrHandler[ ul_Interrupt_સંખ્યા ] = pvHandler;
            ReleaseMutex( pvInterruptEventMutex );
        }
        નહીંતર
        {
            ulIsrHandler[ ul_Interrupt_સંખ્યા ] = pvHandler;
        }
    }
}
/*-----------------------------------------------------------*/

શૂન્ય vPortEnterCritical( શૂન્ય )
{
    જો( xPortRunning == pdTRUE )
    {
        /* The interrupt event mutex is held for the entire critical section,
         * effectively disabling (simulated) interrupts. */
        WaitForSingleObject( pvInterruptEventMutex, INFINITE );
    }

    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

શૂન્ય vPortExitCritical( શૂન્ય )
{
    int32_t lMutexNeedsReleasing;

    /* The interrupt event mutex should already be held by this thread as it was
     * obtained on entry to the critical section. */
    lMutexNeedsReleasing = pdTRUE;

    જો( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        ulCriticalNesting--;

        /* Don't need to wait for any pending interrupts to execute if the
         * critical section was exited from inside an interrupt. */
        જો( ( ulCriticalNesting == portNO_CRITICAL_NESTING ) && ( xInsideInterrupt == pdFALSE ) )
        {
            /* Were any interrupts set to pending while interrupts were
             * (simulated) disabled? */
            જો( ulPendingInterrupts != 0UL )
            {
                ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

                configASSERT( xPortRunning );

                /* The interrupt won't actually executed until
                 * pvInterruptEventMutex is released as it waits on both
                 * pvInterruptEventMutex and pvInterruptEvent.
                 * pvInterruptEvent is only set when the simulated
                 * interrupt is pended if the interrupt is pended
                 * from outside a critical section - hence it is set
                 * here. */
                SetEvent( pvInterruptEvent );

                /* The calling task is going to wait for an event to ensure the
                 * interrupt that is pending executes immediately after the
                 * critical section is exited - so make sure the event is not
                 * already signaled. */
                ResetEvent( pxThreadState->pvYieldEvent );

                /* Mutex will be released now so the (simulated) interrupt can
                 * execute, so does not require releasing on function exit. */
                lMutexNeedsReleasing = pdFALSE;
                ReleaseMutex( pvInterruptEventMutex );
                WaitForSingleObject( pxThreadState->pvYieldEvent, INFINITE );
            }
        }
    }

    જો( pvInterruptEventMutex != ખાલી )
    {
        જો( lMutexNeedsReleasing == pdTRUE )
        {
            configASSERT( xPortRunning );
            ReleaseMutex( pvInterruptEventMutex );
        }
    }
}
/*-----------------------------------------------------------*/
