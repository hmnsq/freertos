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

#جے_تعریف_شدہ WIN32_LEAN_AND_اوسط
    #ضمن <winsock2.h>
#وإلا
    #ضمن <winsock.h>
#جے_انت

#جے_تعریف_شدہ _MSC_VER
    #ضمن <timeapi.h>
    #ہدایت comment(lib, "winmm.lib")
#وإلا
    #ضمن <mmsystem.h>
#جے_انت

#تعریف_کرو پورٹ_MAX_INTERRUPTS                          ( ( uint32_t ) حجم( uint32_t ) * 8UL ) /* The number of bits in an uint32_t. */
#تعریف_کرو پورٹ_NO_CRITICAL_NESTING                     ( ( uint32_t ) 0 )

/* The priorities at which the various components of the simulation execute. */
#تعریف_کرو پورٹ_DELETE_SELF_THREAD_ترجیح             THREAD_ترجیح_ویلا_CRITICAL /* Must be highest. */
#تعریف_کرو پورٹ_SIMULATED_INTERRUPTS_THREAD_ترجیح    THREAD_ترجیح_ویلا_CRITICAL
#تعریف_کرو پورٹ_SIMULATED_TIMER_THREAD_ترجیح         THREAD_ترجیح_HIGHEST
#تعریف_کرو پورٹ_TASK_THREAD_ترجیح                    THREAD_ترجیح_ABOVE_عام

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
ساكن uint32_t prv_Process_Yield_رکاوٹ( فراغ );
ساكن uint32_t prv_Process_Tick_رکاوٹ( فراغ );

/*
 * Exiting a critical section will cause the calling task to block on yield
 * event to wait for an interrupt to process if an interrupt was pended while
 * inside the critical section.  This variable protects against a recursive
 * attempt to obtain pvInterruptEventMutex if a critical section is used inside
 * an interrupt handler itself.
 */
متطاير ادھار_Type_t x_Inside_رکاوٹ = pdFALSE;

/*
 * Called when the process exits to let Windows know the high timer resolution
 * is no longer required.
 */
ساكن BOOL WINAPI prv_سرا_Process( DWORD dwCtrlType );

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
ساكن فراغ * pv_رکاوٹ_Event = عدم;

/* Mutex used to protect all the simulated interrupt variables that are accessed
 * by multiple threads. */
ساكن فراغ * pv_رکاوٹ_Event_Mutex = عدم;

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
ساكن uint32_t (* ulIsrHandler[ پورٹ_MAX_INTERRUPTS ])( فراغ ) = { 0 };

/* Pointer to the TCB of the currently executing task. */
خارجي فراغ * متطاير pxCurrentTCB;

/* Used to ensure nothing is processed during the startup sequence. */
ساكن ادھار_Type_t x_پورٹ_Running = pdFALSE;

/*-----------------------------------------------------------*/

ساكن DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter )
{
    TickType_t x_Minimum_Windows_بلاک_ویلا;
    TIMECAPS x_ویلا_Caps;
    TickType_t x_Wait_ویلا_Between_Ticks = پورٹ_TICK_PERIOD_MS;
    HANDLE hTimer = عدم;
    LARGE_INTEGER li_Due_ویلا;
    BOOL bSuccess;

    /* Set the timer resolution to the maximum possible. */
    إذا( ویلا_Get_Dev_Caps( &x_ویلا_Caps, حجم( x_ویلا_Caps ) ) == MMSYSERR_NOERROR )
    {
        x_Minimum_Windows_بلاک_ویلا = ( TickType_t ) x_ویلا_Caps.wPeriodMin;
        ویلا_Begin_Period( x_ویلا_Caps.wPeriodMin );

        /* Register an exit handler so the timeBeginPeriod() function can be
         * matched with a timeEndPeriod() when the application exits. */
        سیٹ_Console_Ctrl_Handler( prv_سرا_Process, TRUE );
    }
    وإلا
    {
        x_Minimum_Windows_بلاک_ویلا = ( TickType_t ) 20;
    }

    /* Just to prevent compiler warnings. */
    ( فراغ ) lpParameter;

    /* Tick time for the timer is adjusted with the maximum available
     resolution. */
    إذا( پورٹ_TICK_PERIOD_MS < x_Minimum_Windows_بلاک_ویلا )
    {
        x_Wait_ویلا_Between_Ticks = x_Minimum_Windows_بلاک_ویلا;
    }

    /* Convert the tick time in milliseconds to nanoseconds resolution
     for the Waitable Timer. */
    li_Due_ویلا.u.کم_Part = x_Wait_ویلا_Between_Ticks * 1000 * 1000;
    li_Due_ویلا.u.بلند_Part = 0;

    /* Create a synchronization Waitable Timer.*/
    hTimer = CreateWaitableTimer( عدم, FALSE, عدم );

    configASSERT( hTimer != عدم );

    /* Set the Waitable Timer. The timer is set to run periodically at every
    xWaitTimeBetweenTicks milliseconds. */
    bSuccess = سیٹ_Waitable_Timer( hTimer, &li_Due_ویلا, x_Wait_ویلا_Between_Ticks, عدم, عدم, 0 );
    configASSERT( bSuccess );

    طالما( x_پورٹ_Running == pdTRUE )
    {
        /* Wait until the timer expires and we can access the simulated interrupt
         * variables. */

        WaitForSingleObject( hTimer, INFINITE );

        v_پورٹ_Generate_Simulated_رکاوٹ_From_Windows_Thread( پورٹ_رکاوٹ_TICK );
    }

    أرجع 0;
}
/*-----------------------------------------------------------*/

ساكن BOOL WINAPI prv_سرا_Process( DWORD dwCtrlType )
{
    TIMECAPS x_ویلا_Caps;

    ( فراغ ) dwCtrlType;

    إذا( ویلا_Get_Dev_Caps( &x_ویلا_Caps, حجم( x_ویلا_Caps ) ) == MMSYSERR_NOERROR )
    {
        /* Match the call to timeBeginPeriod( xTimeCaps.wPeriodMin ) made when
         * the process started with a timeEndPeriod() as the process exits. */
        ویلا_سرا_Period( x_ویلا_Caps.wPeriodMin );
    }

    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    ThreadState_t * pxThreadState = عدم;
    int8_t * pc_چوٹی_دا_ڈھیر = ( int8_t * ) px_چوٹی_دا_ڈھیر;
    ثابت ناپ_T x_ڈھیر_ناپ = 1024; /* Set the size to a small number which will get rounded up to the minimum possible. */

    /* In this simulated case a stack is not initialised, but instead a thread
     * is created that will execute the task being created.  The thread handles
     * the context switching itself.  The ThreadState_t object is placed onto
     * the stack that was created for the task - so the stack buffer is still
     * used, just not in the conventional way.  It will not be used for anything
     * other than holding this structure. */
    pxThreadState = ( ThreadState_t * ) ( pc_چوٹی_دا_ڈھیر - حجم( ThreadState_t ) );

    /* Create the event used to prevent the thread from executing past its yield
     * point if the SuspendThread() call that suspends the thread does not take
     * effect immediately (it is an asynchronous call). */
    pxThreadState->pvYieldEvent = CreateEvent( عدم,   /* Default security attributes. */
                                               FALSE,  /* Auto reset. */
                                               FALSE,  /* Start not signalled. */
                                               عدم ); /* No name. */


#جے_تعریف_شدہ __GNUC__
    /* GCC reports the warning for the cast operation from TaskFunction_t to LPTHREAD_START_ROUTINE. */
    /* Disable this warning here by the #pragma option. */
#ہدایت GCC diagnostic ڈالو
#ہدایت GCC diagnostic ignored "-Wcast-function-type"
#جے_انت
    /* Create the thread itself. */
    pxThreadState->pvThread = CreateThread( عدم, x_ڈھیر_ناپ, ( LPTHREAD_شروع_ROUTINE ) px_کوڈ, pvParameters, CREATE_SUSPENDED | ڈھیر_ناپ_PARAM_IS_A_RESERVATION, عدم );
#جے_تعریف_شدہ __GNUC__
#ہدایت GCC diagnostic نکالو
#جے_انت

    configASSERT( pxThreadState->pvThread ); /* See comment where TerminateThread() is called. */
    سیٹ_Thread_Affinity_نقاب( pxThreadState->pvThread, 0x01 );
    سیٹ_Thread_ترجیح_Boost( pxThreadState->pvThread, TRUE );
    سیٹ_Thread_ترجیح( pxThreadState->pvThread, پورٹ_TASK_THREAD_ترجیح );

    أرجع ( ڈھیر_Type_t * ) pxThreadState;
}
/*-----------------------------------------------------------*/

ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    فراغ * pvHandle = عدم;
    int32_t lSuccess;
    ThreadState_t * pxThreadState = عدم;
    SYSTEM_INFO xSystemInfo;

    /* This port runs windows threads with extremely high priority.  All the
     * threads execute on the same core - to prevent locking up the host only start
     * if the host has multiple cores. */
    GetSystemInfo( &xSystemInfo );

    إذا( xSystemInfo.dw_نمبر_دا_Processors <= 1 )
    {
        لکھو( "This version of the FreeRTOS Windows port can only be used on multi-core hosts.\r\n" );
        lSuccess = pdFAIL;
    }
    وإلا
    {
        lSuccess = pdPASS;

        /* The highest priority class is used to [try to] prevent other Windows
         * activity interfering with FreeRTOS timing too much. */
        إذا( سیٹ_ترجیح_Class( GetCurrentProcess(), REALTIME_ترجیح_CLASS ) == 0 )
        {
            لکھو( "SetPriorityClass() failed\r\n" );
        }

        /* Install the interrupt handlers used by the scheduler itself. */
        v_پورٹ_سیٹ_رکاوٹ_Handler( پورٹ_رکاوٹ_YIELD, prv_Process_Yield_رکاوٹ );
        v_پورٹ_سیٹ_رکاوٹ_Handler( پورٹ_رکاوٹ_TICK, prv_Process_Tick_رکاوٹ );

        /* Create the events and mutexes that are used to synchronise all the
         * threads. */
        pv_رکاوٹ_Event_Mutex = CreateMutex( عدم, FALSE, عدم );
        pv_رکاوٹ_Event = CreateEvent( عدم, FALSE, FALSE, عدم );

        إذا( ( pv_رکاوٹ_Event_Mutex == عدم ) || ( pv_رکاوٹ_Event == عدم ) )
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
        إذا( سیٹ_Thread_ترجیح( pvHandle, پورٹ_SIMULATED_INTERRUPTS_THREAD_ترجیح ) == 0 )
        {
            lSuccess = pdFAIL;
        }

        سیٹ_Thread_ترجیح_Boost( pvHandle, TRUE );
        سیٹ_Thread_Affinity_نقاب( pvHandle, 0x01 );
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
            سیٹ_Thread_ترجیح( pvHandle, پورٹ_SIMULATED_TIMER_THREAD_ترجیح );
            سیٹ_Thread_ترجیح_Boost( pvHandle, TRUE );
            سیٹ_Thread_Affinity_نقاب( pvHandle, 0x01 );
            ResumeThread( pvHandle );
        }

        /* Start the highest priority task by obtaining its associated thread
         * state structure, in which is stored the thread handle. */
        pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );
        ulCriticalNesting = پورٹ_NO_CRITICAL_NESTING;

        /* The scheduler is now running. */
        x_پورٹ_Running = pdTRUE;

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

ساكن uint32_t prv_Process_Yield_رکاوٹ( فراغ )
{
    /* Always return true as this is a yield. */
    أرجع pdTRUE;
}
/*-----------------------------------------------------------*/

ساكن uint32_t prv_Process_Tick_رکاوٹ( فراغ )
{
    uint32_t ulSwitchRequired;

    /* Process the tick itself. */
    configASSERT( x_پورٹ_Running );
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
    DWORD x_Win_Api_نتیجہ;
    ثابت DWORD xTimeoutMilliseconds = 1000;

    /* Going to block on the mutex that ensured exclusive access to the simulated
     * interrupt objects, and the event that signals that a simulated interrupt
     * should be processed. */
    pvObjectList[ 0 ] = pv_رکاوٹ_Event_Mutex;
    pvObjectList[ 1 ] = pv_رکاوٹ_Event;

    /* Create a pending tick to ensure the first task is started as soon as
     * this thread pends. */
    ulPendingInterrupts |= ( 1UL << پورٹ_رکاوٹ_TICK );
    سیٹ_Event( pv_رکاوٹ_Event );

    طالما( x_پورٹ_Running == pdTRUE )
    {
        x_Inside_رکاوٹ = pdFALSE;

        /* Wait with timeout so that we can exit from this loop when
         * the scheduler is stopped by calling vPortEndScheduler. */
        x_Win_Api_نتیجہ = Wait_For_مضرب_Objects( حجم( pvObjectList ) / حجم( فراغ * ), pvObjectList, TRUE, xTimeoutMilliseconds );

        إذا( x_Win_Api_نتیجہ != WAIT_TIMEOUT )
        {
            /* Cannot be in a critical section to get here.  Tasks that exit a
             * critical section will block on a yield mutex to wait for an interrupt to
             * process if an interrupt was set pending while the task was inside the
             * critical section.  xInsideInterrupt prevents interrupts that contain
             * critical sections from doing the same. */
            x_Inside_رکاوٹ = pdTRUE;

            /* Used to indicate whether the simulated interrupt processing has
             * necessitated a context switch to another task/thread. */
            ulSwitchRequired = pdFALSE;

            /* For each interrupt we are interested in processing, each of which is
             * represented by a bit in the 32bit ulPendingInterrupts variable. */
            لكل( i = 0; i < پورٹ_MAX_INTERRUPTS; i++ )
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
            سیٹ_Event( pxThreadState->pvYieldEvent );
            ReleaseMutex( pv_رکاوٹ_Event_Mutex );
        }
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Delete_Thread( فراغ * pv_Task_منزل_Delete )
{
    ThreadState_t * pxThreadState;
    uint32_t ul_Error_کوڈ;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( فراغ ) ul_Error_کوڈ;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pv_Task_منزل_Delete );

    /* Check that the thread is still valid, it might have been closed by
     * vPortCloseRunningThread() - which will be the case if the task associated
     * with the thread originally deleted itself rather than being deleted by a
     * different task. */
    إذا( pxThreadState->pvThread != عدم )
    {
        WaitForSingleObject( pv_رکاوٹ_Event_Mutex, INFINITE );

        /* !!! This is not a nice way to terminate a thread, and will eventually
         * result in resources being depleted if tasks frequently delete other
         * tasks (rather than deleting themselves) as the task stacks will not be
         * freed. */
        ul_Error_کوڈ = TerminateThread( pxThreadState->pvThread, 0 );
        configASSERT( ul_Error_کوڈ );

        ul_Error_کوڈ = CloseHandle( pxThreadState->pvThread );
        configASSERT( ul_Error_کوڈ );

        ReleaseMutex( pv_رکاوٹ_Event_Mutex );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Close_Running_Thread( فراغ * pv_Task_منزل_Delete,
                              متطاير ادھار_Type_t * pxPendYield )
{
    ThreadState_t * pxThreadState;
    فراغ * pvThread;
    uint32_t ul_Error_کوڈ;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( فراغ ) ul_Error_کوڈ;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pv_Task_منزل_Delete );
    pvThread = pxThreadState->pvThread;

    /* Raise the Windows priority of the thread to ensure the FreeRTOS scheduler
     * does not run and swap it out before it is closed.  If that were to happen
     * the thread would never run again and effectively be a thread handle and
     * memory leak. */
    سیٹ_Thread_ترجیح( pvThread, پورٹ_DELETE_SELF_THREAD_ترجیح );

    /* This function will not return, therefore a yield is set as pending to
     * ensure a context switch occurs away from this thread on the next tick. */
    *pxPendYield = pdTRUE;

    /* Mark the thread associated with this task as invalid so
     * vPortDeleteThread() does not try to terminate it. */
    pxThreadState->pvThread = عدم;

    /* Close the thread. */
    ul_Error_کوڈ = CloseHandle( pvThread );
    configASSERT( ul_Error_کوڈ );

    /* This is called from a critical section, which must be exited before the
     * thread stops. */
    taskEXIT_CRITICAL();

    /* Record that a yield is pending so that the next tick interrupt switches
     * out this thread regardless of the value of configUSE_PREEMPTION. This is
     * needed when a task deletes itself - the taskYIELD_WITHIN_API within
     * vTaskDelete does not get called because this function never returns. If
     * we do not pend portINTERRUPT_YIELD here, the next task is not scheduled
     * when configUSE_PREEMPTION is set to 0. */
    إذا( pv_رکاوٹ_Event_Mutex != عدم )
    {
        WaitForSingleObject( pv_رکاوٹ_Event_Mutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << پورٹ_رکاوٹ_YIELD );
        ReleaseMutex( pv_رکاوٹ_Event_Mutex );
    }

    CloseHandle( pxThreadState->pvYieldEvent );
    ExitThread( 0 );
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
    x_پورٹ_Running = pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Generate_Simulated_رکاوٹ( uint32_t ul_رکاوٹ_نمبر )
{
    ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

    configASSERT( x_پورٹ_Running );

    إذا( ( ul_رکاوٹ_نمبر < پورٹ_MAX_INTERRUPTS ) && ( pv_رکاوٹ_Event_Mutex != عدم ) )
    {
        WaitForSingleObject( pv_رکاوٹ_Event_Mutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << ul_رکاوٹ_نمبر );

        /* The simulated interrupt is now held pending, but don't actually
         * process it yet if this call is within a critical section.  It is
         * possible for this to be in a critical section as calls to wait for
         * mutexes are accumulative.  If in a critical section then the event
         * will get set when the critical section nesting count is wound back
         * down to zero. */
        إذا( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING )
        {
            سیٹ_Event( pv_رکاوٹ_Event );

            /* Going to wait for an event - make sure the event is not already
             * signaled. */
            ResetEvent( pxThreadState->pvYieldEvent );
        }

        ReleaseMutex( pv_رکاوٹ_Event_Mutex );

        إذا( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING )
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

فراغ v_پورٹ_Generate_Simulated_رکاوٹ_From_Windows_Thread( uint32_t ul_رکاوٹ_نمبر )
{
    إذا( x_پورٹ_Running == pdTRUE )
    {
        /* Can't proceed if in a critical section as pvInterruptEventMutex won't
         * be available. */
        WaitForSingleObject( pv_رکاوٹ_Event_Mutex, INFINITE );

        /* Pending a user defined interrupt to be handled in simulated interrupt
         * handler thread. */
        ulPendingInterrupts |= ( 1UL << ul_رکاوٹ_نمبر );

        /* The interrupt is now pending - notify the simulated interrupt
         * handler thread.  Must be outside of a critical section to get here so
         * the handler thread can execute immediately pvInterruptEventMutex is
         * released. */
        configASSERT( ulCriticalNesting == 0UL );
        سیٹ_Event( pv_رکاوٹ_Event );

        /* Give back the mutex so the simulated interrupt handler unblocks
         * and can access the interrupt handler variables. */
        ReleaseMutex( pv_رکاوٹ_Event_Mutex );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_سیٹ_رکاوٹ_Handler( uint32_t ul_رکاوٹ_نمبر,
                               uint32_t ( * pvHandler )( فراغ ) )
{
    إذا( ul_رکاوٹ_نمبر < پورٹ_MAX_INTERRUPTS )
    {
        إذا( pv_رکاوٹ_Event_Mutex != عدم )
        {
            WaitForSingleObject( pv_رکاوٹ_Event_Mutex, INFINITE );
            ulIsrHandler[ ul_رکاوٹ_نمبر ] = pvHandler;
            ReleaseMutex( pv_رکاوٹ_Event_Mutex );
        }
        وإلا
        {
            ulIsrHandler[ ul_رکاوٹ_نمبر ] = pvHandler;
        }
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Enter_Critical( فراغ )
{
    إذا( x_پورٹ_Running == pdTRUE )
    {
        /* The interrupt event mutex is held for the entire critical section,
         * effectively disabling (simulated) interrupts. */
        WaitForSingleObject( pv_رکاوٹ_Event_Mutex, INFINITE );
    }

    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورٹ_Exit_Critical( فراغ )
{
    int32_t lMutexNeedsReleasing;

    /* The interrupt event mutex should already be held by this thread as it was
     * obtained on entry to the critical section. */
    lMutexNeedsReleasing = pdTRUE;

    إذا( ulCriticalNesting > پورٹ_NO_CRITICAL_NESTING )
    {
        ulCriticalNesting--;

        /* Don't need to wait for any pending interrupts to execute if the
         * critical section was exited from inside an interrupt. */
        إذا( ( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING ) && ( x_Inside_رکاوٹ == pdFALSE ) )
        {
            /* Were any interrupts set to pending while interrupts were
             * (simulated) disabled? */
            إذا( ulPendingInterrupts != 0UL )
            {
                ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

                configASSERT( x_پورٹ_Running );

                /* The interrupt won't actually executed until
                 * pvInterruptEventMutex is released as it waits on both
                 * pvInterruptEventMutex and pvInterruptEvent.
                 * pvInterruptEvent is only set when the simulated
                 * interrupt is pended if the interrupt is pended
                 * from outside a critical section - hence it is set
                 * here. */
                سیٹ_Event( pv_رکاوٹ_Event );

                /* The calling task is going to wait for an event to ensure the
                 * interrupt that is pending executes immediately after the
                 * critical section is exited - so make sure the event is not
                 * already signaled. */
                ResetEvent( pxThreadState->pvYieldEvent );

                /* Mutex will be released now so the (simulated) interrupt can
                 * execute, so does not require releasing on function exit. */
                lMutexNeedsReleasing = pdFALSE;
                ReleaseMutex( pv_رکاوٹ_Event_Mutex );
                WaitForSingleObject( pxThreadState->pvYieldEvent, INFINITE );
            }
        }
    }

    إذا( pv_رکاوٹ_Event_Mutex != عدم )
    {
        إذا( lMutexNeedsReleasing == pdTRUE )
        {
            configASSERT( x_پورٹ_Running );
            ReleaseMutex( pv_رکاوٹ_Event_Mutex );
        }
    }
}
/*-----------------------------------------------------------*/
