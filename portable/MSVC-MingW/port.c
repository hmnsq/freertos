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
#अन्तर्भाव <stdio.h>

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

#यदि_परिभाषितम् WIN32_LEAN_AND_माध्यम्
    #अन्तर्भाव <winsock2.h>
#अन्यथा
    #अन्तर्भाव <winsock.h>
#यदि_अन्तः

#यदि_परिभाषितम् _MSC_VER
    #अन्तर्भाव <timeapi.h>
    #निर्देशः comment(lib, "winmm.lib")
#अन्यथा
    #अन्तर्भाव <mmsystem.h>
#यदि_अन्तः

#परिभाषय पत्तनम्_MAX_INTERRUPTS                          ( ( uint32_t ) परिमाण( uint32_t ) * 8UL ) /* The number of bits in an uint32_t. */
#परिभाषय पत्तनम्_NO_CRITICAL_NESTING                     ( ( uint32_t ) 0 )

/* The priorities at which the various components of the simulation execute. */
#परिभाषय पत्तनम्_DELETE_SELF_THREAD_प्राथमिकता             THREAD_प्राथमिकता_TIME_CRITICAL /* Must be highest. */
#परिभाषय पत्तनम्_SIMULATED_INTERRUPTS_THREAD_प्राथमिकता    THREAD_प्राथमिकता_TIME_CRITICAL
#परिभाषय पत्तनम्_SIMULATED_TIMER_THREAD_प्राथमिकता         THREAD_प्राथमिकता_HIGHEST
#परिभाषय पत्तनम्_TASK_THREAD_प्राथमिकता                    THREAD_प्राथमिकता_ABOVE_प्रसामान्यम्

/*
 * Created as a high priority thread, this function uses a timer to simulate
 * a tick interrupt being generated on an embedded target.  In this Windows
 * environment the timer does not achieve anything approaching real time
 * performance though.
 */
स्थिर DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter );

/*
 * Process all the simulated interrupts - each represented by a bit in
 * ulPendingInterrupts variable.
 */
स्थिर शून्य prvProcessSimulatedInterrupts( शून्य );

/*
 * Interrupt handlers used by the kernel itself.  These are executed from the
 * simulated interrupt handler thread.
 */
स्थिर uint32_t prv_Process_Yield_व्यवधानम्( शून्य );
स्थिर uint32_t prv_Process_Tick_व्यवधानम्( शून्य );

/*
 * Exiting a critical section will cause the calling task to block on yield
 * event to wait for an interrupt to process if an interrupt was pended while
 * inside the critical section.  This variable protects against a recursive
 * attempt to obtain pvInterruptEventMutex if a critical section is used inside
 * an interrupt handler itself.
 */
चञ्चल आधारः_Type_t x_Inside_व्यवधानम् = pdFALSE;

/*
 * Called when the process exits to let Windows know the high timer resolution
 * is no longer required.
 */
स्थिर BOOL WINAPI prv_अन्तः_Process( DWORD dwCtrlType );

/*-----------------------------------------------------------*/

/* The WIN32 simulator runs each task in a thread.  The context switching is
 * managed by the threads, so the task stack does not have to be managed directly,
 * although the task stack is still used to hold an xThreadState structure this is
 * the only thing it will ever hold.  The structure indirectly maps the task handle
 * to a thread handle. */
प्रकारनिर्देश संरचना
{
    /* Handle of the thread that executes the task. */
    शून्य * pvThread;

    /* Event used to make sure the thread does not execute past a yield point
     * between the call to SuspendThread() to suspend the thread and the
     * asynchronous SuspendThread() operation actually being performed. */
    शून्य * pvYieldEvent;
} ThreadState_t;

/* Simulated interrupts waiting to be processed.  This is a bit mask where each
 * bit represents one interrupt, so a maximum of 32 interrupts can be simulated. */
स्थिर चञ्चल uint32_t ulPendingInterrupts = 0UL;

/* An event used to inform the simulated interrupt processing thread (a high
 * priority thread that simulated interrupt processing) that an interrupt is
 * pending. */
स्थिर शून्य * pv_व्यवधानम्_Event = रिक्त;

/* Mutex used to protect all the simulated interrupt variables that are accessed
 * by multiple threads. */
स्थिर शून्य * pv_व्यवधानम्_Event_Mutex = रिक्त;

/* The critical nesting count for the currently executing task.  This is
 * initialised to a non-zero value so interrupts do not become enabled during
 * the initialisation phase.  As each task has its own critical nesting value
 * ulCriticalNesting will get set to zero when the first task runs.  This
 * initialisation is probably not critical in this simulated environment as the
 * simulated interrupt handlers do not get created until the FreeRTOS scheduler is
 * started anyway. */
स्थिर चञ्चल uint32_t ulCriticalNesting = 9999UL;

/* Handlers for all the simulated software interrupts.  The first two positions
 * are used for the Yield and Tick interrupts so are handled slightly differently,
 * all the other interrupts can be user defined. */
स्थिर uint32_t (* ulIsrHandler[ पत्तनम्_MAX_INTERRUPTS ])( शून्य ) = { 0 };

/* Pointer to the TCB of the currently executing task. */
बाह्य शून्य * चञ्चल pxCurrentTCB;

/* Used to ensure nothing is processed during the startup sequence. */
स्थिर आधारः_Type_t x_पत्तनम्_Running = pdFALSE;

/*-----------------------------------------------------------*/

स्थिर DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter )
{
    TickType_t x_Minimum_Windows_खण्डम्_Time;
    TIMECAPS xTimeCaps;
    TickType_t xWaitTimeBetweenTicks = पत्तनम्_TICK_PERIOD_MS;
    HANDLE hTimer = रिक्त;
    LARGE_INTEGER liDueTime;
    BOOL bSuccess;

    /* Set the timer resolution to the maximum possible. */
    यदि( timeGetDevCaps( &xTimeCaps, परिमाण( xTimeCaps ) ) == MMSYSERR_NOERROR )
    {
        x_Minimum_Windows_खण्डम्_Time = ( TickType_t ) xTimeCaps.wPeriodMin;
        timeBeginPeriod( xTimeCaps.wPeriodMin );

        /* Register an exit handler so the timeBeginPeriod() function can be
         * matched with a timeEndPeriod() when the application exits. */
        समुच्चयः_Console_Ctrl_Handler( prv_अन्तः_Process, TRUE );
    }
    अन्यथा
    {
        x_Minimum_Windows_खण्डम्_Time = ( TickType_t ) 20;
    }

    /* Just to prevent compiler warnings. */
    ( शून्य ) lpParameter;

    /* Tick time for the timer is adjusted with the maximum available
     resolution. */
    यदि( पत्तनम्_TICK_PERIOD_MS < x_Minimum_Windows_खण्डम्_Time )
    {
        xWaitTimeBetweenTicks = x_Minimum_Windows_खण्डम्_Time;
    }

    /* Convert the tick time in milliseconds to nanoseconds resolution
     for the Waitable Timer. */
    liDueTime.u.नीचः_Part = xWaitTimeBetweenTicks * 1000 * 1000;
    liDueTime.u.उच्चः_Part = 0;

    /* Create a synchronization Waitable Timer.*/
    hTimer = CreateWaitableTimer( रिक्त, FALSE, रिक्त );

    configASSERT( hTimer != रिक्त );

    /* Set the Waitable Timer. The timer is set to run periodically at every
    xWaitTimeBetweenTicks milliseconds. */
    bSuccess = समुच्चयः_Waitable_Timer( hTimer, &liDueTime, xWaitTimeBetweenTicks, रिक्त, रिक्त, 0 );
    configASSERT( bSuccess );

    यावत्( x_पत्तनम्_Running == pdTRUE )
    {
        /* Wait until the timer expires and we can access the simulated interrupt
         * variables. */

        WaitForSingleObject( hTimer, INFINITE );

        v_पत्तनम्_Generate_Simulated_व्यवधानम्_From_Windows_Thread( पत्तनम्_व्यवधानम्_TICK );
    }

    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

स्थिर BOOL WINAPI prv_अन्तः_Process( DWORD dwCtrlType )
{
    TIMECAPS xTimeCaps;

    ( शून्य ) dwCtrlType;

    यदि( timeGetDevCaps( &xTimeCaps, परिमाण( xTimeCaps ) ) == MMSYSERR_NOERROR )
    {
        /* Match the call to timeBeginPeriod( xTimeCaps.wPeriodMin ) made when
         * the process started with a timeEndPeriod() as the process exits. */
        time_अन्तः_Period( xTimeCaps.wPeriodMin );
    }

    प्रत्यागम pdFALSE;
}
/*-----------------------------------------------------------*/

राशिः_Type_t * px_पत्तनम्_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_सम्बन्धि_राशिः,
                                     TaskFunction_t px_संहिता,
                                     शून्य * pvParameters )
{
    ThreadState_t * pxThreadState = रिक्त;
    int8_t * pc_शिखरम्_सम्बन्धि_राशिः = ( int8_t * ) px_शिखरम्_सम्बन्धि_राशिः;
    ध्रुव आकार_T x_राशिः_आकार = 1024; /* Set the size to a small number which will get rounded up to the minimum possible. */

    /* In this simulated case a stack is not initialised, but instead a thread
     * is created that will execute the task being created.  The thread handles
     * the context switching itself.  The ThreadState_t object is placed onto
     * the stack that was created for the task - so the stack buffer is still
     * used, just not in the conventional way.  It will not be used for anything
     * other than holding this structure. */
    pxThreadState = ( ThreadState_t * ) ( pc_शिखरम्_सम्बन्धि_राशिः - परिमाण( ThreadState_t ) );

    /* Create the event used to prevent the thread from executing past its yield
     * point if the SuspendThread() call that suspends the thread does not take
     * effect immediately (it is an asynchronous call). */
    pxThreadState->pvYieldEvent = CreateEvent( रिक्त,   /* Default security attributes. */
                                               FALSE,  /* Auto reset. */
                                               FALSE,  /* Start not signalled. */
                                               रिक्त ); /* No name. */


#यदि_परिभाषितम् __GNUC__
    /* GCC reports the warning for the cast operation from TaskFunction_t to LPTHREAD_START_ROUTINE. */
    /* Disable this warning here by the #pragma option. */
#निर्देशः GCC diagnostic प्रक्षिप
#निर्देशः GCC diagnostic ignored "-Wcast-function-type"
#यदि_अन्तः
    /* Create the thread itself. */
    pxThreadState->pvThread = CreateThread( रिक्त, x_राशिः_आकार, ( LPTHREAD_START_ROUTINE ) px_संहिता, pvParameters, CREATE_SUSPENDED | राशिः_आकार_PARAM_IS_A_RESERVATION, रिक्त );
#यदि_परिभाषितम् __GNUC__
#निर्देशः GCC diagnostic निष्कासय
#यदि_अन्तः

    configASSERT( pxThreadState->pvThread ); /* See comment where TerminateThread() is called. */
    समुच्चयः_Thread_Affinity_आवरणम्( pxThreadState->pvThread, 0x01 );
    समुच्चयः_Thread_प्राथमिकता_Boost( pxThreadState->pvThread, TRUE );
    समुच्चयः_Thread_प्राथमिकता( pxThreadState->pvThread, पत्तनम्_TASK_THREAD_प्राथमिकता );

    प्रत्यागम ( राशिः_Type_t * ) pxThreadState;
}
/*-----------------------------------------------------------*/

आधारः_Type_t x_पत्तनम्_Start_Scheduler( शून्य )
{
    शून्य * pvHandle = रिक्त;
    int32_t lSuccess;
    ThreadState_t * pxThreadState = रिक्त;
    SYSTEM_INFO xSystemInfo;

    /* This port runs windows threads with extremely high priority.  All the
     * threads execute on the same core - to prevent locking up the host only start
     * if the host has multiple cores. */
    GetSystemInfo( &xSystemInfo );

    यदि( xSystemInfo.dw_सङ्ख्या_सम्बन्धि_Processors <= 1 )
    {
        प्रारूप_लिख( "This version of the FreeRTOS Windows port can only be used on multi-core hosts.\r\n" );
        lSuccess = pdFAIL;
    }
    अन्यथा
    {
        lSuccess = pdPASS;

        /* The highest priority class is used to [try to] prevent other Windows
         * activity interfering with FreeRTOS timing too much. */
        यदि( समुच्चयः_प्राथमिकता_Class( GetCurrentProcess(), REALTIME_प्राथमिकता_CLASS ) == 0 )
        {
            प्रारूप_लिख( "SetPriorityClass() failed\r\n" );
        }

        /* Install the interrupt handlers used by the scheduler itself. */
        v_पत्तनम्_समुच्चयः_व्यवधानम्_Handler( पत्तनम्_व्यवधानम्_YIELD, prv_Process_Yield_व्यवधानम् );
        v_पत्तनम्_समुच्चयः_व्यवधानम्_Handler( पत्तनम्_व्यवधानम्_TICK, prv_Process_Tick_व्यवधानम् );

        /* Create the events and mutexes that are used to synchronise all the
         * threads. */
        pv_व्यवधानम्_Event_Mutex = CreateMutex( रिक्त, FALSE, रिक्त );
        pv_व्यवधानम्_Event = CreateEvent( रिक्त, FALSE, FALSE, रिक्त );

        यदि( ( pv_व्यवधानम्_Event_Mutex == रिक्त ) || ( pv_व्यवधानम्_Event == रिक्त ) )
        {
            lSuccess = pdFAIL;
        }

        /* Set the priority of this thread such that it is above the priority of
         * the threads that run tasks.  This higher priority is required to ensure
         * simulated interrupts take priority over tasks. */
        pvHandle = GetCurrentThread();

        यदि( pvHandle == रिक्त )
        {
            lSuccess = pdFAIL;
        }
    }

    यदि( lSuccess == pdPASS )
    {
        यदि( समुच्चयः_Thread_प्राथमिकता( pvHandle, पत्तनम्_SIMULATED_INTERRUPTS_THREAD_प्राथमिकता ) == 0 )
        {
            lSuccess = pdFAIL;
        }

        समुच्चयः_Thread_प्राथमिकता_Boost( pvHandle, TRUE );
        समुच्चयः_Thread_Affinity_आवरणम्( pvHandle, 0x01 );
    }

    यदि( lSuccess == pdPASS )
    {
        /* Start the thread that simulates the timer peripheral to generate
         * tick interrupts.  The priority is set below that of the simulated
         * interrupt handler so the interrupt event mutex is used for the
         * handshake / overrun protection. */
        pvHandle = CreateThread( रिक्त, 0, prvSimulatedPeripheralTimer, रिक्त, CREATE_SUSPENDED, रिक्त );

        यदि( pvHandle != रिक्त )
        {
            समुच्चयः_Thread_प्राथमिकता( pvHandle, पत्तनम्_SIMULATED_TIMER_THREAD_प्राथमिकता );
            समुच्चयः_Thread_प्राथमिकता_Boost( pvHandle, TRUE );
            समुच्चयः_Thread_Affinity_आवरणम्( pvHandle, 0x01 );
            ResumeThread( pvHandle );
        }

        /* Start the highest priority task by obtaining its associated thread
         * state structure, in which is stored the thread handle. */
        pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );
        ulCriticalNesting = पत्तनम्_NO_CRITICAL_NESTING;

        /* The scheduler is now running. */
        x_पत्तनम्_Running = pdTRUE;

        /* Start the first task. */
        ResumeThread( pxThreadState->pvThread );

        /* Handle all simulated interrupts - including yield requests and
         * simulated ticks. */
        prvProcessSimulatedInterrupts();
    }

    /* Would not expect to return from prvProcessSimulatedInterrupts(), so should
     * not get here. */
    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

स्थिर uint32_t prv_Process_Yield_व्यवधानम्( शून्य )
{
    /* Always return true as this is a yield. */
    प्रत्यागम pdTRUE;
}
/*-----------------------------------------------------------*/

स्थिर uint32_t prv_Process_Tick_व्यवधानम्( शून्य )
{
    uint32_t ulSwitchRequired;

    /* Process the tick itself. */
    configASSERT( x_पत्तनम्_Running );
    ulSwitchRequired = ( uint32_t ) xTaskIncrementTick();

    प्रत्यागम ulSwitchRequired;
}
/*-----------------------------------------------------------*/

स्थिर शून्य prvProcessSimulatedInterrupts( शून्य )
{
    uint32_t ulSwitchRequired, i;
    ThreadState_t * pxThreadState;
    शून्य * pvObjectList[ 2 ];
    CONTEXT xContext;
    DWORD x_Win_Api_परिणाम;
    ध्रुव DWORD xTimeoutMilliseconds = 1000;

    /* Going to block on the mutex that ensured exclusive access to the simulated
     * interrupt objects, and the event that signals that a simulated interrupt
     * should be processed. */
    pvObjectList[ 0 ] = pv_व्यवधानम्_Event_Mutex;
    pvObjectList[ 1 ] = pv_व्यवधानम्_Event;

    /* Create a pending tick to ensure the first task is started as soon as
     * this thread pends. */
    ulPendingInterrupts |= ( 1UL << पत्तनम्_व्यवधानम्_TICK );
    समुच्चयः_Event( pv_व्यवधानम्_Event );

    यावत्( x_पत्तनम्_Running == pdTRUE )
    {
        x_Inside_व्यवधानम् = pdFALSE;

        /* Wait with timeout so that we can exit from this loop when
         * the scheduler is stopped by calling vPortEndScheduler. */
        x_Win_Api_परिणाम = Wait_For_गुणजः_Objects( परिमाण( pvObjectList ) / परिमाण( शून्य * ), pvObjectList, TRUE, xTimeoutMilliseconds );

        यदि( x_Win_Api_परिणाम != WAIT_TIMEOUT )
        {
            /* Cannot be in a critical section to get here.  Tasks that exit a
             * critical section will block on a yield mutex to wait for an interrupt to
             * process if an interrupt was set pending while the task was inside the
             * critical section.  xInsideInterrupt prevents interrupts that contain
             * critical sections from doing the same. */
            x_Inside_व्यवधानम् = pdTRUE;

            /* Used to indicate whether the simulated interrupt processing has
             * necessitated a context switch to another task/thread. */
            ulSwitchRequired = pdFALSE;

            /* For each interrupt we are interested in processing, each of which is
             * represented by a bit in the 32bit ulPendingInterrupts variable. */
            प्रति( i = 0; i < पत्तनम्_MAX_INTERRUPTS; i++ )
            {
                /* Is the simulated interrupt pending? */
                यदि( ( ulPendingInterrupts & ( 1UL << i ) ) != 0 )
                {
                    /* Is a handler installed? */
                    यदि( ulIsrHandler[ i ] != रिक्त )
                    {
                        /* Run the actual handler.  Handlers return pdTRUE if they
                         * necessitate a context switch. */
                        यदि( ulIsrHandler[ i ]() != pdFALSE )
                        {
                            /* A bit mask is used purely to help debugging. */
                            ulSwitchRequired |= ( 1UL << i );
                        }
                    }

                    /* Clear the interrupt pending bit. */
                    ulPendingInterrupts &= ~( 1UL << i );
                }
            }

            यदि( ulSwitchRequired != pdFALSE )
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
                ( शून्य ) GetThreadContext( pxThreadState->pvThread, &xContext );

                /* Select the next task to run. */
                vTaskSwitchContext();

                /* Obtain the state of the task now selected to enter the
                 * Running state. */
                pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pxCurrentTCB );

                /* pxThreadState->pvThread can be NULL if the task deleted
                 * itself - but a deleted task should never be resumed here. */
                configASSERT( pxThreadState->pvThread != रिक्त );
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
            समुच्चयः_Event( pxThreadState->pvYieldEvent );
            ReleaseMutex( pv_व्यवधानम्_Event_Mutex );
        }
    }
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Delete_Thread( शून्य * pv_Task_गन्तव्यम्_Delete )
{
    ThreadState_t * pxThreadState;
    uint32_t ul_Error_संहिता;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( शून्य ) ul_Error_संहिता;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pv_Task_गन्तव्यम्_Delete );

    /* Check that the thread is still valid, it might have been closed by
     * vPortCloseRunningThread() - which will be the case if the task associated
     * with the thread originally deleted itself rather than being deleted by a
     * different task. */
    यदि( pxThreadState->pvThread != रिक्त )
    {
        WaitForSingleObject( pv_व्यवधानम्_Event_Mutex, INFINITE );

        /* !!! This is not a nice way to terminate a thread, and will eventually
         * result in resources being depleted if tasks frequently delete other
         * tasks (rather than deleting themselves) as the task stacks will not be
         * freed. */
        ul_Error_संहिता = TerminateThread( pxThreadState->pvThread, 0 );
        configASSERT( ul_Error_संहिता );

        ul_Error_संहिता = CloseHandle( pxThreadState->pvThread );
        configASSERT( ul_Error_संहिता );

        ReleaseMutex( pv_व्यवधानम्_Event_Mutex );
    }
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Close_Running_Thread( शून्य * pv_Task_गन्तव्यम्_Delete,
                              चञ्चल आधारः_Type_t * pxPendYield )
{
    ThreadState_t * pxThreadState;
    शून्य * pvThread;
    uint32_t ul_Error_संहिता;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( शून्य ) ul_Error_संहिता;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pv_Task_गन्तव्यम्_Delete );
    pvThread = pxThreadState->pvThread;

    /* Raise the Windows priority of the thread to ensure the FreeRTOS scheduler
     * does not run and swap it out before it is closed.  If that were to happen
     * the thread would never run again and effectively be a thread handle and
     * memory leak. */
    समुच्चयः_Thread_प्राथमिकता( pvThread, पत्तनम्_DELETE_SELF_THREAD_प्राथमिकता );

    /* This function will not return, therefore a yield is set as pending to
     * ensure a context switch occurs away from this thread on the next tick. */
    *pxPendYield = pdTRUE;

    /* Mark the thread associated with this task as invalid so
     * vPortDeleteThread() does not try to terminate it. */
    pxThreadState->pvThread = रिक्त;

    /* Close the thread. */
    ul_Error_संहिता = CloseHandle( pvThread );
    configASSERT( ul_Error_संहिता );

    /* This is called from a critical section, which must be exited before the
     * thread stops. */
    taskEXIT_CRITICAL();

    /* Record that a yield is pending so that the next tick interrupt switches
     * out this thread regardless of the value of configUSE_PREEMPTION. This is
     * needed when a task deletes itself - the taskYIELD_WITHIN_API within
     * vTaskDelete does not get called because this function never returns. If
     * we do not pend portINTERRUPT_YIELD here, the next task is not scheduled
     * when configUSE_PREEMPTION is set to 0. */
    यदि( pv_व्यवधानम्_Event_Mutex != रिक्त )
    {
        WaitForSingleObject( pv_व्यवधानम्_Event_Mutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << पत्तनम्_व्यवधानम्_YIELD );
        ReleaseMutex( pv_व्यवधानम्_Event_Mutex );
    }

    CloseHandle( pxThreadState->pvYieldEvent );
    ExitThread( 0 );
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_अन्तः_Scheduler( शून्य )
{
    x_पत्तनम्_Running = pdFALSE;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Generate_Simulated_व्यवधानम्( uint32_t ul_व्यवधानम्_सङ्ख्या )
{
    ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

    configASSERT( x_पत्तनम्_Running );

    यदि( ( ul_व्यवधानम्_सङ्ख्या < पत्तनम्_MAX_INTERRUPTS ) && ( pv_व्यवधानम्_Event_Mutex != रिक्त ) )
    {
        WaitForSingleObject( pv_व्यवधानम्_Event_Mutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << ul_व्यवधानम्_सङ्ख्या );

        /* The simulated interrupt is now held pending, but don't actually
         * process it yet if this call is within a critical section.  It is
         * possible for this to be in a critical section as calls to wait for
         * mutexes are accumulative.  If in a critical section then the event
         * will get set when the critical section nesting count is wound back
         * down to zero. */
        यदि( ulCriticalNesting == पत्तनम्_NO_CRITICAL_NESTING )
        {
            समुच्चयः_Event( pv_व्यवधानम्_Event );

            /* Going to wait for an event - make sure the event is not already
             * signaled. */
            ResetEvent( pxThreadState->pvYieldEvent );
        }

        ReleaseMutex( pv_व्यवधानम्_Event_Mutex );

        यदि( ulCriticalNesting == पत्तनम्_NO_CRITICAL_NESTING )
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

शून्य v_पत्तनम्_Generate_Simulated_व्यवधानम्_From_Windows_Thread( uint32_t ul_व्यवधानम्_सङ्ख्या )
{
    यदि( x_पत्तनम्_Running == pdTRUE )
    {
        /* Can't proceed if in a critical section as pvInterruptEventMutex won't
         * be available. */
        WaitForSingleObject( pv_व्यवधानम्_Event_Mutex, INFINITE );

        /* Pending a user defined interrupt to be handled in simulated interrupt
         * handler thread. */
        ulPendingInterrupts |= ( 1UL << ul_व्यवधानम्_सङ्ख्या );

        /* The interrupt is now pending - notify the simulated interrupt
         * handler thread.  Must be outside of a critical section to get here so
         * the handler thread can execute immediately pvInterruptEventMutex is
         * released. */
        configASSERT( ulCriticalNesting == 0UL );
        समुच्चयः_Event( pv_व्यवधानम्_Event );

        /* Give back the mutex so the simulated interrupt handler unblocks
         * and can access the interrupt handler variables. */
        ReleaseMutex( pv_व्यवधानम्_Event_Mutex );
    }
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_समुच्चयः_व्यवधानम्_Handler( uint32_t ul_व्यवधानम्_सङ्ख्या,
                               uint32_t ( * pvHandler )( शून्य ) )
{
    यदि( ul_व्यवधानम्_सङ्ख्या < पत्तनम्_MAX_INTERRUPTS )
    {
        यदि( pv_व्यवधानम्_Event_Mutex != रिक्त )
        {
            WaitForSingleObject( pv_व्यवधानम्_Event_Mutex, INFINITE );
            ulIsrHandler[ ul_व्यवधानम्_सङ्ख्या ] = pvHandler;
            ReleaseMutex( pv_व्यवधानम्_Event_Mutex );
        }
        अन्यथा
        {
            ulIsrHandler[ ul_व्यवधानम्_सङ्ख्या ] = pvHandler;
        }
    }
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Enter_Critical( शून्य )
{
    यदि( x_पत्तनम्_Running == pdTRUE )
    {
        /* The interrupt event mutex is held for the entire critical section,
         * effectively disabling (simulated) interrupts. */
        WaitForSingleObject( pv_व्यवधानम्_Event_Mutex, INFINITE );
    }

    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

शून्य v_पत्तनम्_Exit_Critical( शून्य )
{
    int32_t lMutexNeedsReleasing;

    /* The interrupt event mutex should already be held by this thread as it was
     * obtained on entry to the critical section. */
    lMutexNeedsReleasing = pdTRUE;

    यदि( ulCriticalNesting > पत्तनम्_NO_CRITICAL_NESTING )
    {
        ulCriticalNesting--;

        /* Don't need to wait for any pending interrupts to execute if the
         * critical section was exited from inside an interrupt. */
        यदि( ( ulCriticalNesting == पत्तनम्_NO_CRITICAL_NESTING ) && ( x_Inside_व्यवधानम् == pdFALSE ) )
        {
            /* Were any interrupts set to pending while interrupts were
             * (simulated) disabled? */
            यदि( ulPendingInterrupts != 0UL )
            {
                ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

                configASSERT( x_पत्तनम्_Running );

                /* The interrupt won't actually executed until
                 * pvInterruptEventMutex is released as it waits on both
                 * pvInterruptEventMutex and pvInterruptEvent.
                 * pvInterruptEvent is only set when the simulated
                 * interrupt is pended if the interrupt is pended
                 * from outside a critical section - hence it is set
                 * here. */
                समुच्चयः_Event( pv_व्यवधानम्_Event );

                /* The calling task is going to wait for an event to ensure the
                 * interrupt that is pending executes immediately after the
                 * critical section is exited - so make sure the event is not
                 * already signaled. */
                ResetEvent( pxThreadState->pvYieldEvent );

                /* Mutex will be released now so the (simulated) interrupt can
                 * execute, so does not require releasing on function exit. */
                lMutexNeedsReleasing = pdFALSE;
                ReleaseMutex( pv_व्यवधानम्_Event_Mutex );
                WaitForSingleObject( pxThreadState->pvYieldEvent, INFINITE );
            }
        }
    }

    यदि( pv_व्यवधानम्_Event_Mutex != रिक्त )
    {
        यदि( lMutexNeedsReleasing == pdTRUE )
        {
            configASSERT( x_पत्तनम्_Running );
            ReleaseMutex( pv_व्यवधानम्_Event_Mutex );
        }
    }
}
/*-----------------------------------------------------------*/
