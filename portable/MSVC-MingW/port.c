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
#അന്തര്ഭാവ <stdio.h>

/* Scheduler includes. */
#അന്തര്ഭാവ "FreeRTOS.h"
#അന്തര്ഭാവ "task.h"

#ifdef WIN32_LEAN_AND_MEAN
    #അന്തര്ഭാവ <winsock2.h>
#അല്ലെങ്കിൽ
    #അന്തര്ഭാവ <winsock.h>
#endif

#ifdef _MSC_VER
    #അന്തര്ഭാവ <timeapi.h>
    #pragma comment(lib, "winmm.lib")
#അല്ലെങ്കിൽ
    #അന്തര്ഭാവ <mmsystem.h>
#endif

#define portMAX_INTERRUPTS                          ( ( uint32_t ) വലുപ്പം( uint32_t ) * 8UL ) /* The number of bits in an uint32_t. */
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
സ്ഥിതം DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter );

/*
 * Process all the simulated interrupts - each represented by a bit in
 * ulPendingInterrupts variable.
 */
സ്ഥിതം ശൂന്യം prvProcessSimulatedInterrupts( ശൂന്യം );

/*
 * Interrupt handlers used by the kernel itself.  These are executed from the
 * simulated interrupt handler thread.
 */
സ്ഥിതം uint32_t prvProcessYieldInterrupt( ശൂന്യം );
സ്ഥിതം uint32_t prvProcessTickInterrupt( ശൂന്യം );

/*
 * Exiting a critical section will cause the calling task to block on yield
 * event to wait for an interrupt to process if an interrupt was pended while
 * inside the critical section.  This variable protects against a recursive
 * attempt to obtain pvInterruptEventMutex if a critical section is used inside
 * an interrupt handler itself.
 */
അസ്ഥിര BaseType_t xInsideInterrupt = pdFALSE;

/*
 * Called when the process exits to let Windows know the high timer resolution
 * is no longer required.
 */
സ്ഥിതം BOOL WINAPI prvEndProcess( DWORD dwCtrlType );

/*-----------------------------------------------------------*/

/* The WIN32 simulator runs each task in a thread.  The context switching is
 * managed by the threads, so the task stack does not have to be managed directly,
 * although the task stack is still used to hold an xThreadState structure this is
 * the only thing it will ever hold.  The structure indirectly maps the task handle
 * to a thread handle. */
തരനിർവചനം ഘടന
{
    /* Handle of the thread that executes the task. */
    ശൂന്യം * pvThread;

    /* Event used to make sure the thread does not execute past a yield point
     * between the call to SuspendThread() to suspend the thread and the
     * asynchronous SuspendThread() operation actually being performed. */
    ശൂന്യം * pvYieldEvent;
} ThreadState_t;

/* Simulated interrupts waiting to be processed.  This is a bit mask where each
 * bit represents one interrupt, so a maximum of 32 interrupts can be simulated. */
സ്ഥിതം അസ്ഥിര uint32_t ulPendingInterrupts = 0UL;

/* An event used to inform the simulated interrupt processing thread (a high
 * priority thread that simulated interrupt processing) that an interrupt is
 * pending. */
സ്ഥിതം ശൂന്യം * pvInterruptEvent = ശൂന്യ;

/* Mutex used to protect all the simulated interrupt variables that are accessed
 * by multiple threads. */
സ്ഥിതം ശൂന്യം * pvInterruptEventMutex = ശൂന്യ;

/* The critical nesting count for the currently executing task.  This is
 * initialised to a non-zero value so interrupts do not become enabled during
 * the initialisation phase.  As each task has its own critical nesting value
 * ulCriticalNesting will get set to zero when the first task runs.  This
 * initialisation is probably not critical in this simulated environment as the
 * simulated interrupt handlers do not get created until the FreeRTOS scheduler is
 * started anyway. */
സ്ഥിതം അസ്ഥിര uint32_t ulCriticalNesting = 9999UL;

/* Handlers for all the simulated software interrupts.  The first two positions
 * are used for the Yield and Tick interrupts so are handled slightly differently,
 * all the other interrupts can be user defined. */
സ്ഥിതം uint32_t (* ulIsrHandler[ portMAX_INTERRUPTS ])( ശൂന്യം ) = { 0 };

/* Pointer to the TCB of the currently executing task. */
ബാഹ്യ ശൂന്യം * അസ്ഥിര pxCurrentTCB;

/* Used to ensure nothing is processed during the startup sequence. */
സ്ഥിതം BaseType_t xPortRunning = pdFALSE;

/*-----------------------------------------------------------*/

സ്ഥിതം DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter )
{
    TickType_t xMinimumWindowsBlockTime;
    TIMECAPS xTimeCaps;
    TickType_t xWaitTimeBetweenTicks = portTICK_PERIOD_MS;
    HANDLE hTimer = ശൂന്യ;
    LARGE_INTEGER liDueTime;
    BOOL bSuccess;

    /* Set the timer resolution to the maximum possible. */
    എങ്കിൽ( timeGetDevCaps( &xTimeCaps, വലുപ്പം( xTimeCaps ) ) == MMSYSERR_NOERROR )
    {
        xMinimumWindowsBlockTime = ( TickType_t ) xTimeCaps.wPeriodMin;
        timeBeginPeriod( xTimeCaps.wPeriodMin );

        /* Register an exit handler so the timeBeginPeriod() function can be
         * matched with a timeEndPeriod() when the application exits. */
        SetConsoleCtrlHandler( prvEndProcess, TRUE );
    }
    അല്ലെങ്കിൽ
    {
        xMinimumWindowsBlockTime = ( TickType_t ) 20;
    }

    /* Just to prevent compiler warnings. */
    ( ശൂന്യം ) lpParameter;

    /* Tick time for the timer is adjusted with the maximum available
     resolution. */
    എങ്കിൽ( portTICK_PERIOD_MS < xMinimumWindowsBlockTime )
    {
        xWaitTimeBetweenTicks = xMinimumWindowsBlockTime;
    }

    /* Convert the tick time in milliseconds to nanoseconds resolution
     for the Waitable Timer. */
    liDueTime.u.താഴെയുള്ള_Part = xWaitTimeBetweenTicks * 1000 * 1000;
    liDueTime.u.മുകളിലെ_Part = 0;

    /* Create a synchronization Waitable Timer.*/
    hTimer = CreateWaitableTimer( ശൂന്യ, FALSE, ശൂന്യ );

    configASSERT( hTimer != ശൂന്യ );

    /* Set the Waitable Timer. The timer is set to run periodically at every
    xWaitTimeBetweenTicks milliseconds. */
    bSuccess = SetWaitableTimer( hTimer, &liDueTime, xWaitTimeBetweenTicks, ശൂന്യ, ശൂന്യ, 0 );
    configASSERT( bSuccess );

    ആകുമ്പോൾ( xPortRunning == pdTRUE )
    {
        /* Wait until the timer expires and we can access the simulated interrupt
         * variables. */

        WaitForSingleObject( hTimer, INFINITE );

        vPortGenerateSimulatedInterruptFromWindowsThread( portINTERRUPT_TICK );
    }

    തിരികെ 0;
}
/*-----------------------------------------------------------*/

സ്ഥിതം BOOL WINAPI prvEndProcess( DWORD dwCtrlType )
{
    TIMECAPS xTimeCaps;

    ( ശൂന്യം ) dwCtrlType;

    എങ്കിൽ( timeGetDevCaps( &xTimeCaps, വലുപ്പം( xTimeCaps ) ) == MMSYSERR_NOERROR )
    {
        /* Match the call to timeBeginPeriod( xTimeCaps.wPeriodMin ) made when
         * the process started with a timeEndPeriod() as the process exits. */
        timeEndPeriod( xTimeCaps.wPeriodMin );
    }

    തിരികെ pdFALSE;
}
/*-----------------------------------------------------------*/

അട്ടി_Type_t * px_Port_Initialise_അട്ടി( അട്ടി_Type_t * px_മുകൾ_Of_അട്ടി,
                                     TaskFunction_t pxCode,
                                     ശൂന്യം * pvParameters )
{
    ThreadState_t * pxThreadState = ശൂന്യ;
    int8_t * pc_മുകൾ_Of_അട്ടി = ( int8_t * ) px_മുകൾ_Of_അട്ടി;
    സ്ഥിരം SIZE_T x_അട്ടി_Size = 1024; /* Set the size to a small number which will get rounded up to the minimum possible. */

    /* In this simulated case a stack is not initialised, but instead a thread
     * is created that will execute the task being created.  The thread handles
     * the context switching itself.  The ThreadState_t object is placed onto
     * the stack that was created for the task - so the stack buffer is still
     * used, just not in the conventional way.  It will not be used for anything
     * other than holding this structure. */
    pxThreadState = ( ThreadState_t * ) ( pc_മുകൾ_Of_അട്ടി - വലുപ്പം( ThreadState_t ) );

    /* Create the event used to prevent the thread from executing past its yield
     * point if the SuspendThread() call that suspends the thread does not take
     * effect immediately (it is an asynchronous call). */
    pxThreadState->pvYieldEvent = CreateEvent( ശൂന്യ,   /* Default security attributes. */
                                               FALSE,  /* Auto reset. */
                                               FALSE,  /* Start not signalled. */
                                               ശൂന്യ ); /* No name. */


#ifdef __GNUC__
    /* GCC reports the warning for the cast operation from TaskFunction_t to LPTHREAD_START_ROUTINE. */
    /* Disable this warning here by the #pragma option. */
#pragma GCC diagnostic തള്ളുക
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif
    /* Create the thread itself. */
    pxThreadState->pvThread = CreateThread( ശൂന്യ, x_അട്ടി_Size, ( LPTHREAD_START_ROUTINE ) pxCode, pvParameters, CREATE_SUSPENDED | അട്ടി_SIZE_PARAM_IS_A_RESERVATION, ശൂന്യ );
#ifdef __GNUC__
#pragma GCC diagnostic എടുക്കുക
#endif

    configASSERT( pxThreadState->pvThread ); /* See comment where TerminateThread() is called. */
    SetThreadAffinityMask( pxThreadState->pvThread, 0x01 );
    SetThreadPriorityBoost( pxThreadState->pvThread, TRUE );
    SetThreadPriority( pxThreadState->pvThread, portTASK_THREAD_PRIORITY );

    തിരികെ ( അട്ടി_Type_t * ) pxThreadState;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( ശൂന്യം )
{
    ശൂന്യം * pvHandle = ശൂന്യ;
    int32_t lSuccess;
    ThreadState_t * pxThreadState = ശൂന്യ;
    SYSTEM_INFO xSystemInfo;

    /* This port runs windows threads with extremely high priority.  All the
     * threads execute on the same core - to prevent locking up the host only start
     * if the host has multiple cores. */
    GetSystemInfo( &xSystemInfo );

    എങ്കിൽ( xSystemInfo.dw_സംഖ്യ_Of_Processors <= 1 )
    {
        printf( "This version of the FreeRTOS Windows port can only be used on multi-core hosts.\r\n" );
        lSuccess = pdFAIL;
    }
    അല്ലെങ്കിൽ
    {
        lSuccess = pdPASS;

        /* The highest priority class is used to [try to] prevent other Windows
         * activity interfering with FreeRTOS timing too much. */
        എങ്കിൽ( SetPriorityClass( GetCurrentProcess(), REALTIME_PRIORITY_CLASS ) == 0 )
        {
            printf( "SetPriorityClass() failed\r\n" );
        }

        /* Install the interrupt handlers used by the scheduler itself. */
        vPortSetInterruptHandler( portINTERRUPT_YIELD, prvProcessYieldInterrupt );
        vPortSetInterruptHandler( portINTERRUPT_TICK, prvProcessTickInterrupt );

        /* Create the events and mutexes that are used to synchronise all the
         * threads. */
        pvInterruptEventMutex = CreateMutex( ശൂന്യ, FALSE, ശൂന്യ );
        pvInterruptEvent = CreateEvent( ശൂന്യ, FALSE, FALSE, ശൂന്യ );

        എങ്കിൽ( ( pvInterruptEventMutex == ശൂന്യ ) || ( pvInterruptEvent == ശൂന്യ ) )
        {
            lSuccess = pdFAIL;
        }

        /* Set the priority of this thread such that it is above the priority of
         * the threads that run tasks.  This higher priority is required to ensure
         * simulated interrupts take priority over tasks. */
        pvHandle = GetCurrentThread();

        എങ്കിൽ( pvHandle == ശൂന്യ )
        {
            lSuccess = pdFAIL;
        }
    }

    എങ്കിൽ( lSuccess == pdPASS )
    {
        എങ്കിൽ( SetThreadPriority( pvHandle, portSIMULATED_INTERRUPTS_THREAD_PRIORITY ) == 0 )
        {
            lSuccess = pdFAIL;
        }

        SetThreadPriorityBoost( pvHandle, TRUE );
        SetThreadAffinityMask( pvHandle, 0x01 );
    }

    എങ്കിൽ( lSuccess == pdPASS )
    {
        /* Start the thread that simulates the timer peripheral to generate
         * tick interrupts.  The priority is set below that of the simulated
         * interrupt handler so the interrupt event mutex is used for the
         * handshake / overrun protection. */
        pvHandle = CreateThread( ശൂന്യ, 0, prvSimulatedPeripheralTimer, ശൂന്യ, CREATE_SUSPENDED, ശൂന്യ );

        എങ്കിൽ( pvHandle != ശൂന്യ )
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
    തിരികെ 0;
}
/*-----------------------------------------------------------*/

സ്ഥിതം uint32_t prvProcessYieldInterrupt( ശൂന്യം )
{
    /* Always return true as this is a yield. */
    തിരികെ pdTRUE;
}
/*-----------------------------------------------------------*/

സ്ഥിതം uint32_t prvProcessTickInterrupt( ശൂന്യം )
{
    uint32_t ulSwitchRequired;

    /* Process the tick itself. */
    configASSERT( xPortRunning );
    ulSwitchRequired = ( uint32_t ) xTaskIncrementTick();

    തിരികെ ulSwitchRequired;
}
/*-----------------------------------------------------------*/

സ്ഥിതം ശൂന്യം prvProcessSimulatedInterrupts( ശൂന്യം )
{
    uint32_t ulSwitchRequired, i;
    ThreadState_t * pxThreadState;
    ശൂന്യം * pvObjectList[ 2 ];
    CONTEXT xContext;
    DWORD xWinApiResult;
    സ്ഥിരം DWORD xTimeoutMilliseconds = 1000;

    /* Going to block on the mutex that ensured exclusive access to the simulated
     * interrupt objects, and the event that signals that a simulated interrupt
     * should be processed. */
    pvObjectList[ 0 ] = pvInterruptEventMutex;
    pvObjectList[ 1 ] = pvInterruptEvent;

    /* Create a pending tick to ensure the first task is started as soon as
     * this thread pends. */
    ulPendingInterrupts |= ( 1UL << portINTERRUPT_TICK );
    SetEvent( pvInterruptEvent );

    ആകുമ്പോൾ( xPortRunning == pdTRUE )
    {
        xInsideInterrupt = pdFALSE;

        /* Wait with timeout so that we can exit from this loop when
         * the scheduler is stopped by calling vPortEndScheduler. */
        xWinApiResult = WaitForMultipleObjects( വലുപ്പം( pvObjectList ) / വലുപ്പം( ശൂന്യം * ), pvObjectList, TRUE, xTimeoutMilliseconds );

        എങ്കിൽ( xWinApiResult != WAIT_TIMEOUT )
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
            വേണ്ടി( i = 0; i < portMAX_INTERRUPTS; i++ )
            {
                /* Is the simulated interrupt pending? */
                എങ്കിൽ( ( ulPendingInterrupts & ( 1UL << i ) ) != 0 )
                {
                    /* Is a handler installed? */
                    എങ്കിൽ( ulIsrHandler[ i ] != ശൂന്യ )
                    {
                        /* Run the actual handler.  Handlers return pdTRUE if they
                         * necessitate a context switch. */
                        എങ്കിൽ( ulIsrHandler[ i ]() != pdFALSE )
                        {
                            /* A bit mask is used purely to help debugging. */
                            ulSwitchRequired |= ( 1UL << i );
                        }
                    }

                    /* Clear the interrupt pending bit. */
                    ulPendingInterrupts &= ~( 1UL << i );
                }
            }

            എങ്കിൽ( ulSwitchRequired != pdFALSE )
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
                ( ശൂന്യം ) GetThreadContext( pxThreadState->pvThread, &xContext );

                /* Select the next task to run. */
                vTaskSwitchContext();

                /* Obtain the state of the task now selected to enter the
                 * Running state. */
                pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pxCurrentTCB );

                /* pxThreadState->pvThread can be NULL if the task deleted
                 * itself - but a deleted task should never be resumed here. */
                configASSERT( pxThreadState->pvThread != ശൂന്യ );
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

ശൂന്യം vPortDeleteThread( ശൂന്യം * pvTaskToDelete )
{
    ThreadState_t * pxThreadState;
    uint32_t ulErrorCode;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( ശൂന്യം ) ulErrorCode;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pvTaskToDelete );

    /* Check that the thread is still valid, it might have been closed by
     * vPortCloseRunningThread() - which will be the case if the task associated
     * with the thread originally deleted itself rather than being deleted by a
     * different task. */
    എങ്കിൽ( pxThreadState->pvThread != ശൂന്യ )
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

ശൂന്യം vPortCloseRunningThread( ശൂന്യം * pvTaskToDelete,
                              അസ്ഥിര BaseType_t * pxPendYield )
{
    ThreadState_t * pxThreadState;
    ശൂന്യം * pvThread;
    uint32_t ulErrorCode;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( ശൂന്യം ) ulErrorCode;

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
    pxThreadState->pvThread = ശൂന്യ;

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
    എങ്കിൽ( pvInterruptEventMutex != ശൂന്യ )
    {
        WaitForSingleObject( pvInterruptEventMutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << portINTERRUPT_YIELD );
        ReleaseMutex( pvInterruptEventMutex );
    }

    CloseHandle( pxThreadState->pvYieldEvent );
    ExitThread( 0 );
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEndScheduler( ശൂന്യം )
{
    xPortRunning = pdFALSE;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortGenerateSimulatedInterrupt( uint32_t ul_Interrupt_സംഖ്യ )
{
    ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

    configASSERT( xPortRunning );

    എങ്കിൽ( ( ul_Interrupt_സംഖ്യ < portMAX_INTERRUPTS ) && ( pvInterruptEventMutex != ശൂന്യ ) )
    {
        WaitForSingleObject( pvInterruptEventMutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << ul_Interrupt_സംഖ്യ );

        /* The simulated interrupt is now held pending, but don't actually
         * process it yet if this call is within a critical section.  It is
         * possible for this to be in a critical section as calls to wait for
         * mutexes are accumulative.  If in a critical section then the event
         * will get set when the critical section nesting count is wound back
         * down to zero. */
        എങ്കിൽ( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            SetEvent( pvInterruptEvent );

            /* Going to wait for an event - make sure the event is not already
             * signaled. */
            ResetEvent( pxThreadState->pvYieldEvent );
        }

        ReleaseMutex( pvInterruptEventMutex );

        എങ്കിൽ( ulCriticalNesting == portNO_CRITICAL_NESTING )
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

ശൂന്യം vPortGenerateSimulatedInterruptFromWindowsThread( uint32_t ul_Interrupt_സംഖ്യ )
{
    എങ്കിൽ( xPortRunning == pdTRUE )
    {
        /* Can't proceed if in a critical section as pvInterruptEventMutex won't
         * be available. */
        WaitForSingleObject( pvInterruptEventMutex, INFINITE );

        /* Pending a user defined interrupt to be handled in simulated interrupt
         * handler thread. */
        ulPendingInterrupts |= ( 1UL << ul_Interrupt_സംഖ്യ );

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

ശൂന്യം vPortSetInterruptHandler( uint32_t ul_Interrupt_സംഖ്യ,
                               uint32_t ( * pvHandler )( ശൂന്യം ) )
{
    എങ്കിൽ( ul_Interrupt_സംഖ്യ < portMAX_INTERRUPTS )
    {
        എങ്കിൽ( pvInterruptEventMutex != ശൂന്യ )
        {
            WaitForSingleObject( pvInterruptEventMutex, INFINITE );
            ulIsrHandler[ ul_Interrupt_സംഖ്യ ] = pvHandler;
            ReleaseMutex( pvInterruptEventMutex );
        }
        അല്ലെങ്കിൽ
        {
            ulIsrHandler[ ul_Interrupt_സംഖ്യ ] = pvHandler;
        }
    }
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortEnterCritical( ശൂന്യം )
{
    എങ്കിൽ( xPortRunning == pdTRUE )
    {
        /* The interrupt event mutex is held for the entire critical section,
         * effectively disabling (simulated) interrupts. */
        WaitForSingleObject( pvInterruptEventMutex, INFINITE );
    }

    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

ശൂന്യം vPortExitCritical( ശൂന്യം )
{
    int32_t lMutexNeedsReleasing;

    /* The interrupt event mutex should already be held by this thread as it was
     * obtained on entry to the critical section. */
    lMutexNeedsReleasing = pdTRUE;

    എങ്കിൽ( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        ulCriticalNesting--;

        /* Don't need to wait for any pending interrupts to execute if the
         * critical section was exited from inside an interrupt. */
        എങ്കിൽ( ( ulCriticalNesting == portNO_CRITICAL_NESTING ) && ( xInsideInterrupt == pdFALSE ) )
        {
            /* Were any interrupts set to pending while interrupts were
             * (simulated) disabled? */
            എങ്കിൽ( ulPendingInterrupts != 0UL )
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

    എങ്കിൽ( pvInterruptEventMutex != ശൂന്യ )
    {
        എങ്കിൽ( lMutexNeedsReleasing == pdTRUE )
        {
            configASSERT( xPortRunning );
            ReleaseMutex( pvInterruptEventMutex );
        }
    }
}
/*-----------------------------------------------------------*/
