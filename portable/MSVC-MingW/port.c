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
#ضمن <stdio.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

#ifdef WIN32_LEAN_AND_MEAN
    #ضمن <winsock2.h>
#وإلا
    #ضمن <winsock.h>
#endif

#ifdef _MSC_VER
    #ضمن <timeapi.h>
    #pragma comment(lib, "winmm.lib")
#وإلا
    #ضمن <mmsystem.h>
#endif

#define portMAX_INTERRUPTS                          ( ( uint32_t ) حجم( uint32_t ) * 8UL ) /* The number of bits in an uint32_t. */
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
ساكن DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter );

/*
 * Process all the simulated interrupts - each represented by a bit in
 * ulPendingInterrupts variable.
 */
ساكن فراغ prvProcessSimulatedInterrupts( فراغ );

/*
 * Interrupt handlers used by the kernel itself.  These are executed from the
 * simulated interrupt handler thread.
 */
ساكن uint32_t prvProcessYieldInterrupt( فراغ );
ساكن uint32_t prvProcessTickInterrupt( فراغ );

/*
 * Exiting a critical section will cause the calling task to block on yield
 * event to wait for an interrupt to process if an interrupt was pended while
 * inside the critical section.  This variable protects against a recursive
 * attempt to obtain pvInterruptEventMutex if a critical section is used inside
 * an interrupt handler itself.
 */
متطاير BaseType_t xInsideInterrupt = pdFALSE;

/*
 * Called when the process exits to let Windows know the high timer resolution
 * is no longer required.
 */
ساكن BOOL WINAPI prvEndProcess( DWORD dwCtrlType );

/*-----------------------------------------------------------*/

/* The WIN32 simulator runs each task in a thread.  The context switching is
 * managed by the threads, so the task stack does not have to be managed directly,
 * although the task stack is still used to hold an xThreadState structure this is
 * the only thing it will ever hold.  The structure indirectly maps the task handle
 * to a thread handle. */
تعريفنوع بنية
{
    /* Handle of the thread that executes the task. */
    فراغ * pvThread;

    /* Event used to make sure the thread does not execute past a yield point
     * between the call to SuspendThread() to suspend the thread and the
     * asynchronous SuspendThread() operation actually being performed. */
    فراغ * pvYieldEvent;
} ThreadState_t;

/* Simulated interrupts waiting to be processed.  This is a bit mask where each
 * bit represents one interrupt, so a maximum of 32 interrupts can be simulated. */
ساكن متطاير uint32_t ulPendingInterrupts = 0UL;

/* An event used to inform the simulated interrupt processing thread (a high
 * priority thread that simulated interrupt processing) that an interrupt is
 * pending. */
ساكن فراغ * pvInterruptEvent = عدم;

/* Mutex used to protect all the simulated interrupt variables that are accessed
 * by multiple threads. */
ساكن فراغ * pvInterruptEventMutex = عدم;

/* The critical nesting count for the currently executing task.  This is
 * initialised to a non-zero value so interrupts do not become enabled during
 * the initialisation phase.  As each task has its own critical nesting value
 * ulCriticalNesting will get set to zero when the first task runs.  This
 * initialisation is probably not critical in this simulated environment as the
 * simulated interrupt handlers do not get created until the FreeRTOS scheduler is
 * started anyway. */
ساكن متطاير uint32_t ulCriticalNesting = 9999UL;

/* Handlers for all the simulated software interrupts.  The first two positions
 * are used for the Yield and Tick interrupts so are handled slightly differently,
 * all the other interrupts can be user defined. */
ساكن uint32_t (* ulIsrHandler[ portMAX_INTERRUPTS ])( فراغ ) = { 0 };

/* Pointer to the TCB of the currently executing task. */
خارجي فراغ * متطاير pxCurrentTCB;

/* Used to ensure nothing is processed during the startup sequence. */
ساكن BaseType_t xPortRunning = pdFALSE;

/*-----------------------------------------------------------*/

ساكن DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter )
{
    TickType_t xMinimumWindowsBlockTime;
    TIMECAPS xTimeCaps;
    TickType_t xWaitTimeBetweenTicks = portTICK_PERIOD_MS;
    HANDLE hTimer = عدم;
    LARGE_INTEGER liDueTime;
    BOOL bSuccess;

    /* Set the timer resolution to the maximum possible. */
    إذا( timeGetDevCaps( &xTimeCaps, حجم( xTimeCaps ) ) == MMSYSERR_NOERROR )
    {
        xMinimumWindowsBlockTime = ( TickType_t ) xTimeCaps.wPeriodMin;
        timeBeginPeriod( xTimeCaps.wPeriodMin );

        /* Register an exit handler so the timeBeginPeriod() function can be
         * matched with a timeEndPeriod() when the application exits. */
        SetConsoleCtrlHandler( prvEndProcess, TRUE );
    }
    وإلا
    {
        xMinimumWindowsBlockTime = ( TickType_t ) 20;
    }

    /* Just to prevent compiler warnings. */
    ( فراغ ) lpParameter;

    /* Tick time for the timer is adjusted with the maximum available
     resolution. */
    إذا( portTICK_PERIOD_MS < xMinimumWindowsBlockTime )
    {
        xWaitTimeBetweenTicks = xMinimumWindowsBlockTime;
    }

    /* Convert the tick time in milliseconds to nanoseconds resolution
     for the Waitable Timer. */
    liDueTime.u.كس_Part = xWaitTimeBetweenTicks * 1000 * 1000;
    liDueTime.u.سم_Part = 0;

    /* Create a synchronization Waitable Timer.*/
    hTimer = CreateWaitableTimer( عدم, FALSE, عدم );

    configASSERT( hTimer != عدم );

    /* Set the Waitable Timer. The timer is set to run periodically at every
    xWaitTimeBetweenTicks milliseconds. */
    bSuccess = SetWaitableTimer( hTimer, &liDueTime, xWaitTimeBetweenTicks, عدم, عدم, 0 );
    configASSERT( bSuccess );

    طالما( xPortRunning == pdTRUE )
    {
        /* Wait until the timer expires and we can access the simulated interrupt
         * variables. */

        WaitForSingleObject( hTimer, INFINITE );

        vPortGenerateSimulatedInterruptFromWindowsThread( portINTERRUPT_TICK );
    }

    أرجع 0;
}
/*-----------------------------------------------------------*/

ساكن BOOL WINAPI prvEndProcess( DWORD dwCtrlType )
{
    TIMECAPS xTimeCaps;

    ( فراغ ) dwCtrlType;

    إذا( timeGetDevCaps( &xTimeCaps, حجم( xTimeCaps ) ) == MMSYSERR_NOERROR )
    {
        /* Match the call to timeBeginPeriod( xTimeCaps.wPeriodMin ) made when
         * the process started with a timeEndPeriod() as the process exits. */
        timeEndPeriod( xTimeCaps.wPeriodMin );
    }

    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

تر_Type_t * px_Port_Initialise_تر( تر_Type_t * px_كولي_Of_تر,
                                     TaskFunction_t pxCode,
                                     فراغ * pvParameters )
{
    ThreadState_t * pxThreadState = عدم;
    int8_t * pc_كولي_Of_تر = ( int8_t * ) px_كولي_Of_تر;
    ثابت SIZE_T x_تر_Size = 1024; /* Set the size to a small number which will get rounded up to the minimum possible. */

    /* In this simulated case a stack is not initialised, but instead a thread
     * is created that will execute the task being created.  The thread handles
     * the context switching itself.  The ThreadState_t object is placed onto
     * the stack that was created for the task - so the stack buffer is still
     * used, just not in the conventional way.  It will not be used for anything
     * other than holding this structure. */
    pxThreadState = ( ThreadState_t * ) ( pc_كولي_Of_تر - حجم( ThreadState_t ) );

    /* Create the event used to prevent the thread from executing past its yield
     * point if the SuspendThread() call that suspends the thread does not take
     * effect immediately (it is an asynchronous call). */
    pxThreadState->pvYieldEvent = CreateEvent( عدم,   /* Default security attributes. */
                                               FALSE,  /* Auto reset. */
                                               FALSE,  /* Start not signalled. */
                                               عدم ); /* No name. */


#ifdef __GNUC__
    /* GCC reports the warning for the cast operation from TaskFunction_t to LPTHREAD_START_ROUTINE. */
    /* Disable this warning here by the #pragma option. */
#pragma GCC diagnostic تور
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif
    /* Create the thread itself. */
    pxThreadState->pvThread = CreateThread( عدم, x_تر_Size, ( LPTHREAD_START_ROUTINE ) pxCode, pvParameters, CREATE_SUSPENDED | تر_SIZE_PARAM_IS_A_RESERVATION, عدم );
#ifdef __GNUC__
#pragma GCC diagnostic چرو
#endif

    configASSERT( pxThreadState->pvThread ); /* See comment where TerminateThread() is called. */
    SetThreadAffinityMask( pxThreadState->pvThread, 0x01 );
    SetThreadPriorityBoost( pxThreadState->pvThread, TRUE );
    SetThreadPriority( pxThreadState->pvThread, portTASK_THREAD_PRIORITY );

    أرجع ( تر_Type_t * ) pxThreadState;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( فراغ )
{
    فراغ * pvHandle = عدم;
    int32_t lSuccess;
    ThreadState_t * pxThreadState = عدم;
    SYSTEM_INFO xSystemInfo;

    /* This port runs windows threads with extremely high priority.  All the
     * threads execute on the same core - to prevent locking up the host only start
     * if the host has multiple cores. */
    GetSystemInfo( &xSystemInfo );

    إذا( xSystemInfo.dw_لمب_Of_Processors <= 1 )
    {
        printf( "This version of the FreeRTOS Windows port can only be used on multi-core hosts.\r\n" );
        lSuccess = pdFAIL;
    }
    وإلا
    {
        lSuccess = pdPASS;

        /* The highest priority class is used to [try to] prevent other Windows
         * activity interfering with FreeRTOS timing too much. */
        إذا( SetPriorityClass( GetCurrentProcess(), REALTIME_PRIORITY_CLASS ) == 0 )
        {
            printf( "SetPriorityClass() failed\r\n" );
        }

        /* Install the interrupt handlers used by the scheduler itself. */
        vPortSetInterruptHandler( portINTERRUPT_YIELD, prvProcessYieldInterrupt );
        vPortSetInterruptHandler( portINTERRUPT_TICK, prvProcessTickInterrupt );

        /* Create the events and mutexes that are used to synchronise all the
         * threads. */
        pvInterruptEventMutex = CreateMutex( عدم, FALSE, عدم );
        pvInterruptEvent = CreateEvent( عدم, FALSE, FALSE, عدم );

        إذا( ( pvInterruptEventMutex == عدم ) || ( pvInterruptEvent == عدم ) )
        {
            lSuccess = pdFAIL;
        }

        /* Set the priority of this thread such that it is above the priority of
         * the threads that run tasks.  This higher priority is required to ensure
         * simulated interrupts take priority over tasks. */
        pvHandle = GetCurrentThread();

        إذا( pvHandle == عدم )
        {
            lSuccess = pdFAIL;
        }
    }

    إذا( lSuccess == pdPASS )
    {
        إذا( SetThreadPriority( pvHandle, portSIMULATED_INTERRUPTS_THREAD_PRIORITY ) == 0 )
        {
            lSuccess = pdFAIL;
        }

        SetThreadPriorityBoost( pvHandle, TRUE );
        SetThreadAffinityMask( pvHandle, 0x01 );
    }

    إذا( lSuccess == pdPASS )
    {
        /* Start the thread that simulates the timer peripheral to generate
         * tick interrupts.  The priority is set below that of the simulated
         * interrupt handler so the interrupt event mutex is used for the
         * handshake / overrun protection. */
        pvHandle = CreateThread( عدم, 0, prvSimulatedPeripheralTimer, عدم, CREATE_SUSPENDED, عدم );

        إذا( pvHandle != عدم )
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
    أرجع 0;
}
/*-----------------------------------------------------------*/

ساكن uint32_t prvProcessYieldInterrupt( فراغ )
{
    /* Always return true as this is a yield. */
    أرجع pdTRUE;
}
/*-----------------------------------------------------------*/

ساكن uint32_t prvProcessTickInterrupt( فراغ )
{
    uint32_t ulSwitchRequired;

    /* Process the tick itself. */
    configASSERT( xPortRunning );
    ulSwitchRequired = ( uint32_t ) xTaskIncrementTick();

    أرجع ulSwitchRequired;
}
/*-----------------------------------------------------------*/

ساكن فراغ prvProcessSimulatedInterrupts( فراغ )
{
    uint32_t ulSwitchRequired, i;
    ThreadState_t * pxThreadState;
    فراغ * pvObjectList[ 2 ];
    CONTEXT xContext;
    DWORD xWinApiResult;
    ثابت DWORD xTimeoutMilliseconds = 1000;

    /* Going to block on the mutex that ensured exclusive access to the simulated
     * interrupt objects, and the event that signals that a simulated interrupt
     * should be processed. */
    pvObjectList[ 0 ] = pvInterruptEventMutex;
    pvObjectList[ 1 ] = pvInterruptEvent;

    /* Create a pending tick to ensure the first task is started as soon as
     * this thread pends. */
    ulPendingInterrupts |= ( 1UL << portINTERRUPT_TICK );
    SetEvent( pvInterruptEvent );

    طالما( xPortRunning == pdTRUE )
    {
        xInsideInterrupt = pdFALSE;

        /* Wait with timeout so that we can exit from this loop when
         * the scheduler is stopped by calling vPortEndScheduler. */
        xWinApiResult = WaitForMultipleObjects( حجم( pvObjectList ) / حجم( فراغ * ), pvObjectList, TRUE, xTimeoutMilliseconds );

        إذا( xWinApiResult != WAIT_TIMEOUT )
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
            لكل( i = 0; i < portMAX_INTERRUPTS; i++ )
            {
                /* Is the simulated interrupt pending? */
                إذا( ( ulPendingInterrupts & ( 1UL << i ) ) != 0 )
                {
                    /* Is a handler installed? */
                    إذا( ulIsrHandler[ i ] != عدم )
                    {
                        /* Run the actual handler.  Handlers return pdTRUE if they
                         * necessitate a context switch. */
                        إذا( ulIsrHandler[ i ]() != pdFALSE )
                        {
                            /* A bit mask is used purely to help debugging. */
                            ulSwitchRequired |= ( 1UL << i );
                        }
                    }

                    /* Clear the interrupt pending bit. */
                    ulPendingInterrupts &= ~( 1UL << i );
                }
            }

            إذا( ulSwitchRequired != pdFALSE )
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
                ( فراغ ) GetThreadContext( pxThreadState->pvThread, &xContext );

                /* Select the next task to run. */
                vTaskSwitchContext();

                /* Obtain the state of the task now selected to enter the
                 * Running state. */
                pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pxCurrentTCB );

                /* pxThreadState->pvThread can be NULL if the task deleted
                 * itself - but a deleted task should never be resumed here. */
                configASSERT( pxThreadState->pvThread != عدم );
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

فراغ vPortDeleteThread( فراغ * pvTaskToDelete )
{
    ThreadState_t * pxThreadState;
    uint32_t ulErrorCode;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( فراغ ) ulErrorCode;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pvTaskToDelete );

    /* Check that the thread is still valid, it might have been closed by
     * vPortCloseRunningThread() - which will be the case if the task associated
     * with the thread originally deleted itself rather than being deleted by a
     * different task. */
    إذا( pxThreadState->pvThread != عدم )
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

فراغ vPortCloseRunningThread( فراغ * pvTaskToDelete,
                              متطاير BaseType_t * pxPendYield )
{
    ThreadState_t * pxThreadState;
    فراغ * pvThread;
    uint32_t ulErrorCode;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( فراغ ) ulErrorCode;

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
    pxThreadState->pvThread = عدم;

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
    إذا( pvInterruptEventMutex != عدم )
    {
        WaitForSingleObject( pvInterruptEventMutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << portINTERRUPT_YIELD );
        ReleaseMutex( pvInterruptEventMutex );
    }

    CloseHandle( pxThreadState->pvYieldEvent );
    ExitThread( 0 );
}
/*-----------------------------------------------------------*/

فراغ vPortEndScheduler( فراغ )
{
    xPortRunning = pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ vPortGenerateSimulatedInterrupt( uint32_t ul_Interrupt_لمب )
{
    ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

    configASSERT( xPortRunning );

    إذا( ( ul_Interrupt_لمب < portMAX_INTERRUPTS ) && ( pvInterruptEventMutex != عدم ) )
    {
        WaitForSingleObject( pvInterruptEventMutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << ul_Interrupt_لمب );

        /* The simulated interrupt is now held pending, but don't actually
         * process it yet if this call is within a critical section.  It is
         * possible for this to be in a critical section as calls to wait for
         * mutexes are accumulative.  If in a critical section then the event
         * will get set when the critical section nesting count is wound back
         * down to zero. */
        إذا( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            SetEvent( pvInterruptEvent );

            /* Going to wait for an event - make sure the event is not already
             * signaled. */
            ResetEvent( pxThreadState->pvYieldEvent );
        }

        ReleaseMutex( pvInterruptEventMutex );

        إذا( ulCriticalNesting == portNO_CRITICAL_NESTING )
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

فراغ vPortGenerateSimulatedInterruptFromWindowsThread( uint32_t ul_Interrupt_لمب )
{
    إذا( xPortRunning == pdTRUE )
    {
        /* Can't proceed if in a critical section as pvInterruptEventMutex won't
         * be available. */
        WaitForSingleObject( pvInterruptEventMutex, INFINITE );

        /* Pending a user defined interrupt to be handled in simulated interrupt
         * handler thread. */
        ulPendingInterrupts |= ( 1UL << ul_Interrupt_لمب );

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

فراغ vPortSetInterruptHandler( uint32_t ul_Interrupt_لمب,
                               uint32_t ( * pvHandler )( فراغ ) )
{
    إذا( ul_Interrupt_لمب < portMAX_INTERRUPTS )
    {
        إذا( pvInterruptEventMutex != عدم )
        {
            WaitForSingleObject( pvInterruptEventMutex, INFINITE );
            ulIsrHandler[ ul_Interrupt_لمب ] = pvHandler;
            ReleaseMutex( pvInterruptEventMutex );
        }
        وإلا
        {
            ulIsrHandler[ ul_Interrupt_لمب ] = pvHandler;
        }
    }
}
/*-----------------------------------------------------------*/

فراغ vPortEnterCritical( فراغ )
{
    إذا( xPortRunning == pdTRUE )
    {
        /* The interrupt event mutex is held for the entire critical section,
         * effectively disabling (simulated) interrupts. */
        WaitForSingleObject( pvInterruptEventMutex, INFINITE );
    }

    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ vPortExitCritical( فراغ )
{
    int32_t lMutexNeedsReleasing;

    /* The interrupt event mutex should already be held by this thread as it was
     * obtained on entry to the critical section. */
    lMutexNeedsReleasing = pdTRUE;

    إذا( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        ulCriticalNesting--;

        /* Don't need to wait for any pending interrupts to execute if the
         * critical section was exited from inside an interrupt. */
        إذا( ( ulCriticalNesting == portNO_CRITICAL_NESTING ) && ( xInsideInterrupt == pdFALSE ) )
        {
            /* Were any interrupts set to pending while interrupts were
             * (simulated) disabled? */
            إذا( ulPendingInterrupts != 0UL )
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

    إذا( pvInterruptEventMutex != عدم )
    {
        إذا( lMutexNeedsReleasing == pdTRUE )
        {
            configASSERT( xPortRunning );
            ReleaseMutex( pvInterruptEventMutex );
        }
    }
}
/*-----------------------------------------------------------*/
