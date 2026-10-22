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
#ಅನ್ತರ್ಭಾವ <stdio.h>

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ WIN32_LEAN_AND_ಸರಾಸರಿ
    #ಅನ್ತರ್ಭಾವ <winsock2.h>
#ಇಲ್ಲದಿದ್ದರೆ
    #ಅನ್ತರ್ಭಾವ <winsock.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
    #ಅನ್ತರ್ಭಾವ <timeapi.h>
    #ಸೂಚನೆ comment(lib, "winmm.lib")
#ಇಲ್ಲದಿದ್ದರೆ
    #ಅನ್ತರ್ಭಾವ <mmsystem.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_INTERRUPTS                          ( ( uint32_t ) ಗಾತ್ರ( uint32_t ) * 8UL ) /* The number of bits in an uint32_t. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_NESTING                     ( ( uint32_t ) 0 )

/* The priorities at which the various components of the simulation execute. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DELETE_SELF_THREAD_ಆದ್ಯತೆ             THREAD_ಆದ್ಯತೆ_ಸಮಯ_CRITICAL /* Must be highest. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SIMULATED_INTERRUPTS_THREAD_ಆದ್ಯತೆ    THREAD_ಆದ್ಯತೆ_ಸಮಯ_CRITICAL
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SIMULATED_TIMER_THREAD_ಆದ್ಯತೆ         THREAD_ಆದ್ಯತೆ_HIGHEST
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_THREAD_ಆದ್ಯತೆ                    THREAD_ಆದ್ಯತೆ_ABOVE_ಸಾಮಾನ್ಯ

/*
 * Created as a high priority thread, this function uses a timer to simulate
 * a tick interrupt being generated on an embedded target.  In this Windows
 * environment the timer does not achieve anything approaching real time
 * performance though.
 */
ಸ್ಥಿರ DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter );

/*
 * Process all the simulated interrupts - each represented by a bit in
 * ulPendingInterrupts variable.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvProcessSimulatedInterrupts( ಶೂನ್ಯ );

/*
 * Interrupt handlers used by the kernel itself.  These are executed from the
 * simulated interrupt handler thread.
 */
ಸ್ಥಿರ uint32_t prv_Process_Yield_ಅಡಚಣೆ( ಶೂನ್ಯ );
ಸ್ಥಿರ uint32_t prv_Process_Tick_ಅಡಚಣೆ( ಶೂನ್ಯ );

/*
 * Exiting a critical section will cause the calling task to block on yield
 * event to wait for an interrupt to process if an interrupt was pended while
 * inside the critical section.  This variable protects against a recursive
 * attempt to obtain pvInterruptEventMutex if a critical section is used inside
 * an interrupt handler itself.
 */
ಅಸ್ಥಿರ ತಳ_Type_t x_Inside_ಅಡಚಣೆ = pdFALSE;

/*
 * Called when the process exits to let Windows know the high timer resolution
 * is no longer required.
 */
ಸ್ಥಿರ BOOL WINAPI prv_ಕೊನೆ_Process( DWORD dwCtrlType );

/*-----------------------------------------------------------*/

/* The WIN32 simulator runs each task in a thread.  The context switching is
 * managed by the threads, so the task stack does not have to be managed directly,
 * although the task stack is still used to hold an xThreadState structure this is
 * the only thing it will ever hold.  The structure indirectly maps the task handle
 * to a thread handle. */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    /* Handle of the thread that executes the task. */
    ಶೂನ್ಯ * pvThread;

    /* Event used to make sure the thread does not execute past a yield point
     * between the call to SuspendThread() to suspend the thread and the
     * asynchronous SuspendThread() operation actually being performed. */
    ಶೂನ್ಯ * pvYieldEvent;
} ThreadState_t;

/* Simulated interrupts waiting to be processed.  This is a bit mask where each
 * bit represents one interrupt, so a maximum of 32 interrupts can be simulated. */
ಸ್ಥಿರ ಅಸ್ಥಿರ uint32_t ulPendingInterrupts = 0UL;

/* An event used to inform the simulated interrupt processing thread (a high
 * priority thread that simulated interrupt processing) that an interrupt is
 * pending. */
ಸ್ಥಿರ ಶೂನ್ಯ * pv_ಅಡಚಣೆ_Event = ಖಾಲಿ;

/* Mutex used to protect all the simulated interrupt variables that are accessed
 * by multiple threads. */
ಸ್ಥಿರ ಶೂನ್ಯ * pv_ಅಡಚಣೆ_Event_Mutex = ಖಾಲಿ;

/* The critical nesting count for the currently executing task.  This is
 * initialised to a non-zero value so interrupts do not become enabled during
 * the initialisation phase.  As each task has its own critical nesting value
 * ulCriticalNesting will get set to zero when the first task runs.  This
 * initialisation is probably not critical in this simulated environment as the
 * simulated interrupt handlers do not get created until the FreeRTOS scheduler is
 * started anyway. */
ಸ್ಥಿರ ಅಸ್ಥಿರ uint32_t ulCriticalNesting = 9999UL;

/* Handlers for all the simulated software interrupts.  The first two positions
 * are used for the Yield and Tick interrupts so are handled slightly differently,
 * all the other interrupts can be user defined. */
ಸ್ಥಿರ uint32_t (* ulIsrHandler[ ಪೋರ್ಟ್_MAX_INTERRUPTS ])( ಶೂನ್ಯ ) = { 0 };

/* Pointer to the TCB of the currently executing task. */
ಬಾಹ್ಯ ಶೂನ್ಯ * ಅಸ್ಥಿರ pxCurrentTCB;

/* Used to ensure nothing is processed during the startup sequence. */
ಸ್ಥಿರ ತಳ_Type_t x_ಪೋರ್ಟ್_Running = pdFALSE;

/*-----------------------------------------------------------*/

ಸ್ಥಿರ DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter )
{
    TickType_t x_Minimum_Windows_ಖಂಡ_ಸಮಯ;
    TIMECAPS x_ಸಮಯ_Caps;
    TickType_t x_Wait_ಸಮಯ_Between_Ticks = ಪೋರ್ಟ್_TICK_PERIOD_MS;
    HANDLE hTimer = ಖಾಲಿ;
    LARGE_INTEGER li_Due_ಸಮಯ;
    BOOL bSuccess;

    /* Set the timer resolution to the maximum possible. */
    ಆದರೆ( ಸಮಯ_Get_Dev_Caps( &x_ಸಮಯ_Caps, ಗಾತ್ರ( x_ಸಮಯ_Caps ) ) == MMSYSERR_NOERROR )
    {
        x_Minimum_Windows_ಖಂಡ_ಸಮಯ = ( TickType_t ) x_ಸಮಯ_Caps.wPeriodMin;
        ಸಮಯ_Begin_Period( x_ಸಮಯ_Caps.wPeriodMin );

        /* Register an exit handler so the timeBeginPeriod() function can be
         * matched with a timeEndPeriod() when the application exits. */
        ಗಣ_Console_Ctrl_Handler( prv_ಕೊನೆ_Process, TRUE );
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        x_Minimum_Windows_ಖಂಡ_ಸಮಯ = ( TickType_t ) 20;
    }

    /* Just to prevent compiler warnings. */
    ( ಶೂನ್ಯ ) lpParameter;

    /* Tick time for the timer is adjusted with the maximum available
     resolution. */
    ಆದರೆ( ಪೋರ್ಟ್_TICK_PERIOD_MS < x_Minimum_Windows_ಖಂಡ_ಸಮಯ )
    {
        x_Wait_ಸಮಯ_Between_Ticks = x_Minimum_Windows_ಖಂಡ_ಸಮಯ;
    }

    /* Convert the tick time in milliseconds to nanoseconds resolution
     for the Waitable Timer. */
    li_Due_ಸಮಯ.u.ಕೆಳಗಿನ_Part = x_Wait_ಸಮಯ_Between_Ticks * 1000 * 1000;
    li_Due_ಸಮಯ.u.ಮೇಲಿನ_Part = 0;

    /* Create a synchronization Waitable Timer.*/
    hTimer = CreateWaitableTimer( ಖಾಲಿ, FALSE, ಖಾಲಿ );

    configASSERT( hTimer != ಖಾಲಿ );

    /* Set the Waitable Timer. The timer is set to run periodically at every
    xWaitTimeBetweenTicks milliseconds. */
    bSuccess = ಗಣ_Waitable_Timer( hTimer, &li_Due_ಸಮಯ, x_Wait_ಸಮಯ_Between_Ticks, ಖಾಲಿ, ಖಾಲಿ, 0 );
    configASSERT( bSuccess );

    ಆಗ( x_ಪೋರ್ಟ್_Running == pdTRUE )
    {
        /* Wait until the timer expires and we can access the simulated interrupt
         * variables. */

        WaitForSingleObject( hTimer, INFINITE );

        v_ಪೋರ್ಟ್_Generate_Simulated_ಅಡಚಣೆ_From_Windows_Thread( ಪೋರ್ಟ್_ಅಡಚಣೆ_TICK );
    }

    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ BOOL WINAPI prv_ಕೊನೆ_Process( DWORD dwCtrlType )
{
    TIMECAPS x_ಸಮಯ_Caps;

    ( ಶೂನ್ಯ ) dwCtrlType;

    ಆದರೆ( ಸಮಯ_Get_Dev_Caps( &x_ಸಮಯ_Caps, ಗಾತ್ರ( x_ಸಮಯ_Caps ) ) == MMSYSERR_NOERROR )
    {
        /* Match the call to timeBeginPeriod( xTimeCaps.wPeriodMin ) made when
         * the process started with a timeEndPeriod() as the process exits. */
        ಸಮಯ_ಕೊನೆ_Period( x_ಸಮಯ_Caps.wPeriodMin );
    }

    ಹಿಂತಿರುಗಿ pdFALSE;
}
/*-----------------------------------------------------------*/

ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    ThreadState_t * pxThreadState = ಖಾಲಿ;
    int8_t * pc_ತುದಿ_ದ_ರಾಶಿ = ( int8_t * ) px_ತುದಿ_ದ_ರಾಶಿ;
    ಸ್ಥಿರಾಂಕ ಗಾತ್ರ_T x_ರಾಶಿ_ಗಾತ್ರ = 1024; /* Set the size to a small number which will get rounded up to the minimum possible. */

    /* In this simulated case a stack is not initialised, but instead a thread
     * is created that will execute the task being created.  The thread handles
     * the context switching itself.  The ThreadState_t object is placed onto
     * the stack that was created for the task - so the stack buffer is still
     * used, just not in the conventional way.  It will not be used for anything
     * other than holding this structure. */
    pxThreadState = ( ThreadState_t * ) ( pc_ತುದಿ_ದ_ರಾಶಿ - ಗಾತ್ರ( ThreadState_t ) );

    /* Create the event used to prevent the thread from executing past its yield
     * point if the SuspendThread() call that suspends the thread does not take
     * effect immediately (it is an asynchronous call). */
    pxThreadState->pvYieldEvent = CreateEvent( ಖಾಲಿ,   /* Default security attributes. */
                                               FALSE,  /* Auto reset. */
                                               FALSE,  /* Start not signalled. */
                                               ಖಾಲಿ ); /* No name. */


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __GNUC__
    /* GCC reports the warning for the cast operation from TaskFunction_t to LPTHREAD_START_ROUTINE. */
    /* Disable this warning here by the #pragma option. */
#ಸೂಚನೆ GCC diagnostic ತಳ್ಳು
#ಸೂಚನೆ GCC diagnostic ignored "-Wcast-function-type"
#ಆದರೆ_ಅಂತ್ಯ
    /* Create the thread itself. */
    pxThreadState->pvThread = CreateThread( ಖಾಲಿ, x_ರಾಶಿ_ಗಾತ್ರ, ( LPTHREAD_ಆರಂಭ_ROUTINE ) px_ಸಂಕೇತ, pvParameters, CREATE_SUSPENDED | ರಾಶಿ_ಗಾತ್ರ_PARAM_IS_A_RESERVATION, ಖಾಲಿ );
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __GNUC__
#ಸೂಚನೆ GCC diagnostic ತೆಗೆ_2
#ಆದರೆ_ಅಂತ್ಯ

    configASSERT( pxThreadState->pvThread ); /* See comment where TerminateThread() is called. */
    ಗಣ_Thread_Affinity_ಮುಖವಾಡ( pxThreadState->pvThread, 0x01 );
    ಗಣ_Thread_ಆದ್ಯತೆ_Boost( pxThreadState->pvThread, TRUE );
    ಗಣ_Thread_ಆದ್ಯತೆ( pxThreadState->pvThread, ಪೋರ್ಟ್_TASK_THREAD_ಆದ್ಯತೆ );

    ಹಿಂತಿರುಗಿ ( ರಾಶಿ_Type_t * ) pxThreadState;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    ಶೂನ್ಯ * pvHandle = ಖಾಲಿ;
    int32_t lSuccess;
    ThreadState_t * pxThreadState = ಖಾಲಿ;
    SYSTEM_INFO xSystemInfo;

    /* This port runs windows threads with extremely high priority.  All the
     * threads execute on the same core - to prevent locking up the host only start
     * if the host has multiple cores. */
    GetSystemInfo( &xSystemInfo );

    ಆದರೆ( xSystemInfo.dw_ಸಂಖ್ಯೆ_ದ_Processors <= 1 )
    {
        ಬರೆ( "This version of the FreeRTOS Windows port can only be used on multi-core hosts.\r\n" );
        lSuccess = pdFAIL;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        lSuccess = pdPASS;

        /* The highest priority class is used to [try to] prevent other Windows
         * activity interfering with FreeRTOS timing too much. */
        ಆದರೆ( ಗಣ_ಆದ್ಯತೆ_Class( GetCurrentProcess(), REALTIME_ಆದ್ಯತೆ_CLASS ) == 0 )
        {
            ಬರೆ( "SetPriorityClass() failed\r\n" );
        }

        /* Install the interrupt handlers used by the scheduler itself. */
        v_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_Handler( ಪೋರ್ಟ್_ಅಡಚಣೆ_YIELD, prv_Process_Yield_ಅಡಚಣೆ );
        v_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_Handler( ಪೋರ್ಟ್_ಅಡಚಣೆ_TICK, prv_Process_Tick_ಅಡಚಣೆ );

        /* Create the events and mutexes that are used to synchronise all the
         * threads. */
        pv_ಅಡಚಣೆ_Event_Mutex = CreateMutex( ಖಾಲಿ, FALSE, ಖಾಲಿ );
        pv_ಅಡಚಣೆ_Event = CreateEvent( ಖಾಲಿ, FALSE, FALSE, ಖಾಲಿ );

        ಆದರೆ( ( pv_ಅಡಚಣೆ_Event_Mutex == ಖಾಲಿ ) || ( pv_ಅಡಚಣೆ_Event == ಖಾಲಿ ) )
        {
            lSuccess = pdFAIL;
        }

        /* Set the priority of this thread such that it is above the priority of
         * the threads that run tasks.  This higher priority is required to ensure
         * simulated interrupts take priority over tasks. */
        pvHandle = GetCurrentThread();

        ಆದರೆ( pvHandle == ಖಾಲಿ )
        {
            lSuccess = pdFAIL;
        }
    }

    ಆದರೆ( lSuccess == pdPASS )
    {
        ಆದರೆ( ಗಣ_Thread_ಆದ್ಯತೆ( pvHandle, ಪೋರ್ಟ್_SIMULATED_INTERRUPTS_THREAD_ಆದ್ಯತೆ ) == 0 )
        {
            lSuccess = pdFAIL;
        }

        ಗಣ_Thread_ಆದ್ಯತೆ_Boost( pvHandle, TRUE );
        ಗಣ_Thread_Affinity_ಮುಖವಾಡ( pvHandle, 0x01 );
    }

    ಆದರೆ( lSuccess == pdPASS )
    {
        /* Start the thread that simulates the timer peripheral to generate
         * tick interrupts.  The priority is set below that of the simulated
         * interrupt handler so the interrupt event mutex is used for the
         * handshake / overrun protection. */
        pvHandle = CreateThread( ಖಾಲಿ, 0, prvSimulatedPeripheralTimer, ಖಾಲಿ, CREATE_SUSPENDED, ಖಾಲಿ );

        ಆದರೆ( pvHandle != ಖಾಲಿ )
        {
            ಗಣ_Thread_ಆದ್ಯತೆ( pvHandle, ಪೋರ್ಟ್_SIMULATED_TIMER_THREAD_ಆದ್ಯತೆ );
            ಗಣ_Thread_ಆದ್ಯತೆ_Boost( pvHandle, TRUE );
            ಗಣ_Thread_Affinity_ಮುಖವಾಡ( pvHandle, 0x01 );
            ResumeThread( pvHandle );
        }

        /* Start the highest priority task by obtaining its associated thread
         * state structure, in which is stored the thread handle. */
        pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );
        ulCriticalNesting = ಪೋರ್ಟ್_NO_CRITICAL_NESTING;

        /* The scheduler is now running. */
        x_ಪೋರ್ಟ್_Running = pdTRUE;

        /* Start the first task. */
        ResumeThread( pxThreadState->pvThread );

        /* Handle all simulated interrupts - including yield requests and
         * simulated ticks. */
        prvProcessSimulatedInterrupts();
    }

    /* Would not expect to return from prvProcessSimulatedInterrupts(), so should
     * not get here. */
    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ uint32_t prv_Process_Yield_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    /* Always return true as this is a yield. */
    ಹಿಂತಿರುಗಿ pdTRUE;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ uint32_t prv_Process_Tick_ಅಡಚಣೆ( ಶೂನ್ಯ )
{
    uint32_t ulSwitchRequired;

    /* Process the tick itself. */
    configASSERT( x_ಪೋರ್ಟ್_Running );
    ulSwitchRequired = ( uint32_t ) xTaskIncrementTick();

    ಹಿಂತಿರುಗಿ ulSwitchRequired;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvProcessSimulatedInterrupts( ಶೂನ್ಯ )
{
    uint32_t ulSwitchRequired, i;
    ThreadState_t * pxThreadState;
    ಶೂನ್ಯ * pvObjectList[ 2 ];
    CONTEXT xContext;
    DWORD x_Win_Api_ಫಲಿತಾಂಶ;
    ಸ್ಥಿರಾಂಕ DWORD xTimeoutMilliseconds = 1000;

    /* Going to block on the mutex that ensured exclusive access to the simulated
     * interrupt objects, and the event that signals that a simulated interrupt
     * should be processed. */
    pvObjectList[ 0 ] = pv_ಅಡಚಣೆ_Event_Mutex;
    pvObjectList[ 1 ] = pv_ಅಡಚಣೆ_Event;

    /* Create a pending tick to ensure the first task is started as soon as
     * this thread pends. */
    ulPendingInterrupts |= ( 1UL << ಪೋರ್ಟ್_ಅಡಚಣೆ_TICK );
    ಗಣ_Event( pv_ಅಡಚಣೆ_Event );

    ಆಗ( x_ಪೋರ್ಟ್_Running == pdTRUE )
    {
        x_Inside_ಅಡಚಣೆ = pdFALSE;

        /* Wait with timeout so that we can exit from this loop when
         * the scheduler is stopped by calling vPortEndScheduler. */
        x_Win_Api_ಫಲಿತಾಂಶ = Wait_For_ಅಪವರ್ತ್ಯ_Objects( ಗಾತ್ರ( pvObjectList ) / ಗಾತ್ರ( ಶೂನ್ಯ * ), pvObjectList, TRUE, xTimeoutMilliseconds );

        ಆದರೆ( x_Win_Api_ಫಲಿತಾಂಶ != WAIT_TIMEOUT )
        {
            /* Cannot be in a critical section to get here.  Tasks that exit a
             * critical section will block on a yield mutex to wait for an interrupt to
             * process if an interrupt was set pending while the task was inside the
             * critical section.  xInsideInterrupt prevents interrupts that contain
             * critical sections from doing the same. */
            x_Inside_ಅಡಚಣೆ = pdTRUE;

            /* Used to indicate whether the simulated interrupt processing has
             * necessitated a context switch to another task/thread. */
            ulSwitchRequired = pdFALSE;

            /* For each interrupt we are interested in processing, each of which is
             * represented by a bit in the 32bit ulPendingInterrupts variable. */
            ಗಾಗಿ( i = 0; i < ಪೋರ್ಟ್_MAX_INTERRUPTS; i++ )
            {
                /* Is the simulated interrupt pending? */
                ಆದರೆ( ( ulPendingInterrupts & ( 1UL << i ) ) != 0 )
                {
                    /* Is a handler installed? */
                    ಆದರೆ( ulIsrHandler[ i ] != ಖಾಲಿ )
                    {
                        /* Run the actual handler.  Handlers return pdTRUE if they
                         * necessitate a context switch. */
                        ಆದರೆ( ulIsrHandler[ i ]() != pdFALSE )
                        {
                            /* A bit mask is used purely to help debugging. */
                            ulSwitchRequired |= ( 1UL << i );
                        }
                    }

                    /* Clear the interrupt pending bit. */
                    ulPendingInterrupts &= ~( 1UL << i );
                }
            }

            ಆದರೆ( ulSwitchRequired != pdFALSE )
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
                ( ಶೂನ್ಯ ) GetThreadContext( pxThreadState->pvThread, &xContext );

                /* Select the next task to run. */
                vTaskSwitchContext();

                /* Obtain the state of the task now selected to enter the
                 * Running state. */
                pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pxCurrentTCB );

                /* pxThreadState->pvThread can be NULL if the task deleted
                 * itself - but a deleted task should never be resumed here. */
                configASSERT( pxThreadState->pvThread != ಖಾಲಿ );
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
            ಗಣ_Event( pxThreadState->pvYieldEvent );
            ReleaseMutex( pv_ಅಡಚಣೆ_Event_Mutex );
        }
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Delete_Thread( ಶೂನ್ಯ * pv_Task_ಗಮ್ಯ_Delete )
{
    ThreadState_t * pxThreadState;
    uint32_t ul_Error_ಸಂಕೇತ;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( ಶೂನ್ಯ ) ul_Error_ಸಂಕೇತ;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pv_Task_ಗಮ್ಯ_Delete );

    /* Check that the thread is still valid, it might have been closed by
     * vPortCloseRunningThread() - which will be the case if the task associated
     * with the thread originally deleted itself rather than being deleted by a
     * different task. */
    ಆದರೆ( pxThreadState->pvThread != ಖಾಲಿ )
    {
        WaitForSingleObject( pv_ಅಡಚಣೆ_Event_Mutex, INFINITE );

        /* !!! This is not a nice way to terminate a thread, and will eventually
         * result in resources being depleted if tasks frequently delete other
         * tasks (rather than deleting themselves) as the task stacks will not be
         * freed. */
        ul_Error_ಸಂಕೇತ = TerminateThread( pxThreadState->pvThread, 0 );
        configASSERT( ul_Error_ಸಂಕೇತ );

        ul_Error_ಸಂಕೇತ = CloseHandle( pxThreadState->pvThread );
        configASSERT( ul_Error_ಸಂಕೇತ );

        ReleaseMutex( pv_ಅಡಚಣೆ_Event_Mutex );
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Close_Running_Thread( ಶೂನ್ಯ * pv_Task_ಗಮ್ಯ_Delete,
                              ಅಸ್ಥಿರ ತಳ_Type_t * pxPendYield )
{
    ThreadState_t * pxThreadState;
    ಶೂನ್ಯ * pvThread;
    uint32_t ul_Error_ಸಂಕೇತ;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( ಶೂನ್ಯ ) ul_Error_ಸಂಕೇತ;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pv_Task_ಗಮ್ಯ_Delete );
    pvThread = pxThreadState->pvThread;

    /* Raise the Windows priority of the thread to ensure the FreeRTOS scheduler
     * does not run and swap it out before it is closed.  If that were to happen
     * the thread would never run again and effectively be a thread handle and
     * memory leak. */
    ಗಣ_Thread_ಆದ್ಯತೆ( pvThread, ಪೋರ್ಟ್_DELETE_SELF_THREAD_ಆದ್ಯತೆ );

    /* This function will not return, therefore a yield is set as pending to
     * ensure a context switch occurs away from this thread on the next tick. */
    *pxPendYield = pdTRUE;

    /* Mark the thread associated with this task as invalid so
     * vPortDeleteThread() does not try to terminate it. */
    pxThreadState->pvThread = ಖಾಲಿ;

    /* Close the thread. */
    ul_Error_ಸಂಕೇತ = CloseHandle( pvThread );
    configASSERT( ul_Error_ಸಂಕೇತ );

    /* This is called from a critical section, which must be exited before the
     * thread stops. */
    taskEXIT_CRITICAL();

    /* Record that a yield is pending so that the next tick interrupt switches
     * out this thread regardless of the value of configUSE_PREEMPTION. This is
     * needed when a task deletes itself - the taskYIELD_WITHIN_API within
     * vTaskDelete does not get called because this function never returns. If
     * we do not pend portINTERRUPT_YIELD here, the next task is not scheduled
     * when configUSE_PREEMPTION is set to 0. */
    ಆದರೆ( pv_ಅಡಚಣೆ_Event_Mutex != ಖಾಲಿ )
    {
        WaitForSingleObject( pv_ಅಡಚಣೆ_Event_Mutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << ಪೋರ್ಟ್_ಅಡಚಣೆ_YIELD );
        ReleaseMutex( pv_ಅಡಚಣೆ_Event_Mutex );
    }

    CloseHandle( pxThreadState->pvYieldEvent );
    ExitThread( 0 );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    x_ಪೋರ್ಟ್_Running = pdFALSE;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Generate_Simulated_ಅಡಚಣೆ( uint32_t ul_ಅಡಚಣೆ_ಸಂಖ್ಯೆ )
{
    ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

    configASSERT( x_ಪೋರ್ಟ್_Running );

    ಆದರೆ( ( ul_ಅಡಚಣೆ_ಸಂಖ್ಯೆ < ಪೋರ್ಟ್_MAX_INTERRUPTS ) && ( pv_ಅಡಚಣೆ_Event_Mutex != ಖಾಲಿ ) )
    {
        WaitForSingleObject( pv_ಅಡಚಣೆ_Event_Mutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << ul_ಅಡಚಣೆ_ಸಂಖ್ಯೆ );

        /* The simulated interrupt is now held pending, but don't actually
         * process it yet if this call is within a critical section.  It is
         * possible for this to be in a critical section as calls to wait for
         * mutexes are accumulative.  If in a critical section then the event
         * will get set when the critical section nesting count is wound back
         * down to zero. */
        ಆದರೆ( ulCriticalNesting == ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
        {
            ಗಣ_Event( pv_ಅಡಚಣೆ_Event );

            /* Going to wait for an event - make sure the event is not already
             * signaled. */
            ResetEvent( pxThreadState->pvYieldEvent );
        }

        ReleaseMutex( pv_ಅಡಚಣೆ_Event_Mutex );

        ಆದರೆ( ulCriticalNesting == ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
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

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Generate_Simulated_ಅಡಚಣೆ_From_Windows_Thread( uint32_t ul_ಅಡಚಣೆ_ಸಂಖ್ಯೆ )
{
    ಆದರೆ( x_ಪೋರ್ಟ್_Running == pdTRUE )
    {
        /* Can't proceed if in a critical section as pvInterruptEventMutex won't
         * be available. */
        WaitForSingleObject( pv_ಅಡಚಣೆ_Event_Mutex, INFINITE );

        /* Pending a user defined interrupt to be handled in simulated interrupt
         * handler thread. */
        ulPendingInterrupts |= ( 1UL << ul_ಅಡಚಣೆ_ಸಂಖ್ಯೆ );

        /* The interrupt is now pending - notify the simulated interrupt
         * handler thread.  Must be outside of a critical section to get here so
         * the handler thread can execute immediately pvInterruptEventMutex is
         * released. */
        configASSERT( ulCriticalNesting == 0UL );
        ಗಣ_Event( pv_ಅಡಚಣೆ_Event );

        /* Give back the mutex so the simulated interrupt handler unblocks
         * and can access the interrupt handler variables. */
        ReleaseMutex( pv_ಅಡಚಣೆ_Event_Mutex );
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_Handler( uint32_t ul_ಅಡಚಣೆ_ಸಂಖ್ಯೆ,
                               uint32_t ( * pvHandler )( ಶೂನ್ಯ ) )
{
    ಆದರೆ( ul_ಅಡಚಣೆ_ಸಂಖ್ಯೆ < ಪೋರ್ಟ್_MAX_INTERRUPTS )
    {
        ಆದರೆ( pv_ಅಡಚಣೆ_Event_Mutex != ಖಾಲಿ )
        {
            WaitForSingleObject( pv_ಅಡಚಣೆ_Event_Mutex, INFINITE );
            ulIsrHandler[ ul_ಅಡಚಣೆ_ಸಂಖ್ಯೆ ] = pvHandler;
            ReleaseMutex( pv_ಅಡಚಣೆ_Event_Mutex );
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
            ulIsrHandler[ ul_ಅಡಚಣೆ_ಸಂಖ್ಯೆ ] = pvHandler;
        }
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    ಆದರೆ( x_ಪೋರ್ಟ್_Running == pdTRUE )
    {
        /* The interrupt event mutex is held for the entire critical section,
         * effectively disabling (simulated) interrupts. */
        WaitForSingleObject( pv_ಅಡಚಣೆ_Event_Mutex, INFINITE );
    }

    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    int32_t lMutexNeedsReleasing;

    /* The interrupt event mutex should already be held by this thread as it was
     * obtained on entry to the critical section. */
    lMutexNeedsReleasing = pdTRUE;

    ಆದರೆ( ulCriticalNesting > ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
    {
        ulCriticalNesting--;

        /* Don't need to wait for any pending interrupts to execute if the
         * critical section was exited from inside an interrupt. */
        ಆದರೆ( ( ulCriticalNesting == ಪೋರ್ಟ್_NO_CRITICAL_NESTING ) && ( x_Inside_ಅಡಚಣೆ == pdFALSE ) )
        {
            /* Were any interrupts set to pending while interrupts were
             * (simulated) disabled? */
            ಆದರೆ( ulPendingInterrupts != 0UL )
            {
                ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

                configASSERT( x_ಪೋರ್ಟ್_Running );

                /* The interrupt won't actually executed until
                 * pvInterruptEventMutex is released as it waits on both
                 * pvInterruptEventMutex and pvInterruptEvent.
                 * pvInterruptEvent is only set when the simulated
                 * interrupt is pended if the interrupt is pended
                 * from outside a critical section - hence it is set
                 * here. */
                ಗಣ_Event( pv_ಅಡಚಣೆ_Event );

                /* The calling task is going to wait for an event to ensure the
                 * interrupt that is pending executes immediately after the
                 * critical section is exited - so make sure the event is not
                 * already signaled. */
                ResetEvent( pxThreadState->pvYieldEvent );

                /* Mutex will be released now so the (simulated) interrupt can
                 * execute, so does not require releasing on function exit. */
                lMutexNeedsReleasing = pdFALSE;
                ReleaseMutex( pv_ಅಡಚಣೆ_Event_Mutex );
                WaitForSingleObject( pxThreadState->pvYieldEvent, INFINITE );
            }
        }
    }

    ಆದರೆ( pv_ಅಡಚಣೆ_Event_Mutex != ಖಾಲಿ )
    {
        ಆದರೆ( lMutexNeedsReleasing == pdTRUE )
        {
            configASSERT( x_ಪೋರ್ಟ್_Running );
            ReleaseMutex( pv_ಅಡಚಣೆ_Event_Mutex );
        }
    }
}
/*-----------------------------------------------------------*/
