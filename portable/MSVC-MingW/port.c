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

#اگر_تعریف_شده WIN32_LEAN_AND_میانگین
    #ضمن <winsock2.h>
#وإلا
    #ضمن <winsock.h>
#پایان_اگر

#اگر_تعریف_شده _MSC_VER
    #ضمن <timeapi.h>
    #رهنمود comment(lib, "winmm.lib")
#وإلا
    #ضمن <mmsystem.h>
#پایان_اگر

#تعریف_کن پورت_MAX_INTERRUPTS                          ( ( uint32_t ) حجم( uint32_t ) * 8UL ) /* The number of bits in an uint32_t. */
#تعریف_کن پورت_NO_CRITICAL_NESTING                     ( ( uint32_t ) 0 )

/* The priorities at which the various components of the simulation execute. */
#تعریف_کن پورت_DELETE_SELF_THREAD_اولویت             THREAD_اولویت_زمان_CRITICAL /* Must be highest. */
#تعریف_کن پورت_SIMULATED_INTERRUPTS_THREAD_اولویت    THREAD_اولویت_زمان_CRITICAL
#تعریف_کن پورت_SIMULATED_TIMER_THREAD_اولویت         THREAD_اولویت_HIGHEST
#تعریف_کن پورت_TASK_THREAD_اولویت                    THREAD_اولویت_ABOVE_نرمال

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
ساكن uint32_t prv_Process_Yield_وقفه( فراغ );
ساكن uint32_t prv_Process_Tick_وقفه( فراغ );

/*
 * Exiting a critical section will cause the calling task to block on yield
 * event to wait for an interrupt to process if an interrupt was pended while
 * inside the critical section.  This variable protects against a recursive
 * attempt to obtain pvInterruptEventMutex if a critical section is used inside
 * an interrupt handler itself.
 */
متطاير پایه_Type_t x_Inside_وقفه = pdFALSE;

/*
 * Called when the process exits to let Windows know the high timer resolution
 * is no longer required.
 */
ساكن BOOL WINAPI prv_انتها_Process( DWORD dwCtrlType );

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
ساكن فراغ * pv_وقفه_Event = عدم;

/* Mutex used to protect all the simulated interrupt variables that are accessed
 * by multiple threads. */
ساكن فراغ * pv_وقفه_Event_Mutex = عدم;

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
ساكن uint32_t (* ulIsrHandler[ پورت_MAX_INTERRUPTS ])( فراغ ) = { 0 };

/* Pointer to the TCB of the currently executing task. */
خارجي فراغ * متطاير pxCurrentTCB;

/* Used to ensure nothing is processed during the startup sequence. */
ساكن پایه_Type_t x_پورت_Running = pdFALSE;

/*-----------------------------------------------------------*/

ساكن DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter )
{
    TickType_t x_Minimum_Windows_بلوک_زمان;
    TIMECAPS x_زمان_Caps;
    TickType_t x_Wait_زمان_Between_Ticks = پورت_TICK_PERIOD_MS;
    HANDLE hTimer = عدم;
    LARGE_INTEGER li_Due_زمان;
    BOOL bSuccess;

    /* Set the timer resolution to the maximum possible. */
    إذا( زمان_Get_Dev_Caps( &x_زمان_Caps, حجم( x_زمان_Caps ) ) == MMSYSERR_NOERROR )
    {
        x_Minimum_Windows_بلوک_زمان = ( TickType_t ) x_زمان_Caps.wPeriodMin;
        زمان_Begin_Period( x_زمان_Caps.wPeriodMin );

        /* Register an exit handler so the timeBeginPeriod() function can be
         * matched with a timeEndPeriod() when the application exits. */
        مجموعه_Console_Ctrl_Handler( prv_انتها_Process, TRUE );
    }
    وإلا
    {
        x_Minimum_Windows_بلوک_زمان = ( TickType_t ) 20;
    }

    /* Just to prevent compiler warnings. */
    ( فراغ ) lpParameter;

    /* Tick time for the timer is adjusted with the maximum available
     resolution. */
    إذا( پورت_TICK_PERIOD_MS < x_Minimum_Windows_بلوک_زمان )
    {
        x_Wait_زمان_Between_Ticks = x_Minimum_Windows_بلوک_زمان;
    }

    /* Convert the tick time in milliseconds to nanoseconds resolution
     for the Waitable Timer. */
    li_Due_زمان.u.کم_Part = x_Wait_زمان_Between_Ticks * 1000 * 1000;
    li_Due_زمان.u.بالا_Part = 0;

    /* Create a synchronization Waitable Timer.*/
    hTimer = CreateWaitableTimer( عدم, FALSE, عدم );

    configASSERT( hTimer != عدم );

    /* Set the Waitable Timer. The timer is set to run periodically at every
    xWaitTimeBetweenTicks milliseconds. */
    bSuccess = مجموعه_Waitable_Timer( hTimer, &li_Due_زمان, x_Wait_زمان_Between_Ticks, عدم, عدم, 0 );
    configASSERT( bSuccess );

    طالما( x_پورت_Running == pdTRUE )
    {
        /* Wait until the timer expires and we can access the simulated interrupt
         * variables. */

        WaitForSingleObject( hTimer, INFINITE );

        v_پورت_Generate_Simulated_وقفه_From_Windows_Thread( پورت_وقفه_TICK );
    }

    أرجع 0;
}
/*-----------------------------------------------------------*/

ساكن BOOL WINAPI prv_انتها_Process( DWORD dwCtrlType )
{
    TIMECAPS x_زمان_Caps;

    ( فراغ ) dwCtrlType;

    إذا( زمان_Get_Dev_Caps( &x_زمان_Caps, حجم( x_زمان_Caps ) ) == MMSYSERR_NOERROR )
    {
        /* Match the call to timeBeginPeriod( xTimeCaps.wPeriodMin ) made when
         * the process started with a timeEndPeriod() as the process exits. */
        زمان_انتها_Period( x_زمان_Caps.wPeriodMin );
    }

    أرجع pdFALSE;
}
/*-----------------------------------------------------------*/

پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    ThreadState_t * pxThreadState = عدم;
    int8_t * pc_بالاترین_از_پشته = ( int8_t * ) px_بالاترین_از_پشته;
    ثابت اندازه_T x_پشته_اندازه = 1024; /* Set the size to a small number which will get rounded up to the minimum possible. */

    /* In this simulated case a stack is not initialised, but instead a thread
     * is created that will execute the task being created.  The thread handles
     * the context switching itself.  The ThreadState_t object is placed onto
     * the stack that was created for the task - so the stack buffer is still
     * used, just not in the conventional way.  It will not be used for anything
     * other than holding this structure. */
    pxThreadState = ( ThreadState_t * ) ( pc_بالاترین_از_پشته - حجم( ThreadState_t ) );

    /* Create the event used to prevent the thread from executing past its yield
     * point if the SuspendThread() call that suspends the thread does not take
     * effect immediately (it is an asynchronous call). */
    pxThreadState->pvYieldEvent = CreateEvent( عدم,   /* Default security attributes. */
                                               FALSE,  /* Auto reset. */
                                               FALSE,  /* Start not signalled. */
                                               عدم ); /* No name. */


#اگر_تعریف_شده __GNUC__
    /* GCC reports the warning for the cast operation from TaskFunction_t to LPTHREAD_START_ROUTINE. */
    /* Disable this warning here by the #pragma option. */
#رهنمود GCC diagnostic افزودن
#رهنمود GCC diagnostic ignored "-Wcast-function-type"
#پایان_اگر
    /* Create the thread itself. */
    pxThreadState->pvThread = CreateThread( عدم, x_پشته_اندازه, ( LPTHREAD_شروع_ROUTINE ) px_کد, pvParameters, CREATE_SUSPENDED | پشته_اندازه_PARAM_IS_A_RESERVATION, عدم );
#اگر_تعریف_شده __GNUC__
#رهنمود GCC diagnostic برداشت
#پایان_اگر

    configASSERT( pxThreadState->pvThread ); /* See comment where TerminateThread() is called. */
    مجموعه_Thread_Affinity_ماسک( pxThreadState->pvThread, 0x01 );
    مجموعه_Thread_اولویت_Boost( pxThreadState->pvThread, TRUE );
    مجموعه_Thread_اولویت( pxThreadState->pvThread, پورت_TASK_THREAD_اولویت );

    أرجع ( پشته_Type_t * ) pxThreadState;
}
/*-----------------------------------------------------------*/

پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    فراغ * pvHandle = عدم;
    int32_t lSuccess;
    ThreadState_t * pxThreadState = عدم;
    SYSTEM_INFO xSystemInfo;

    /* This port runs windows threads with extremely high priority.  All the
     * threads execute on the same core - to prevent locking up the host only start
     * if the host has multiple cores. */
    GetSystemInfo( &xSystemInfo );

    إذا( xSystemInfo.dw_عدد_از_Processors <= 1 )
    {
        چاپ_کن( "This version of the FreeRTOS Windows port can only be used on multi-core hosts.\r\n" );
        lSuccess = pdFAIL;
    }
    وإلا
    {
        lSuccess = pdPASS;

        /* The highest priority class is used to [try to] prevent other Windows
         * activity interfering with FreeRTOS timing too much. */
        إذا( مجموعه_اولویت_Class( GetCurrentProcess(), REALTIME_اولویت_CLASS ) == 0 )
        {
            چاپ_کن( "SetPriorityClass() failed\r\n" );
        }

        /* Install the interrupt handlers used by the scheduler itself. */
        v_پورت_مجموعه_وقفه_Handler( پورت_وقفه_YIELD, prv_Process_Yield_وقفه );
        v_پورت_مجموعه_وقفه_Handler( پورت_وقفه_TICK, prv_Process_Tick_وقفه );

        /* Create the events and mutexes that are used to synchronise all the
         * threads. */
        pv_وقفه_Event_Mutex = CreateMutex( عدم, FALSE, عدم );
        pv_وقفه_Event = CreateEvent( عدم, FALSE, FALSE, عدم );

        إذا( ( pv_وقفه_Event_Mutex == عدم ) || ( pv_وقفه_Event == عدم ) )
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
        إذا( مجموعه_Thread_اولویت( pvHandle, پورت_SIMULATED_INTERRUPTS_THREAD_اولویت ) == 0 )
        {
            lSuccess = pdFAIL;
        }

        مجموعه_Thread_اولویت_Boost( pvHandle, TRUE );
        مجموعه_Thread_Affinity_ماسک( pvHandle, 0x01 );
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
            مجموعه_Thread_اولویت( pvHandle, پورت_SIMULATED_TIMER_THREAD_اولویت );
            مجموعه_Thread_اولویت_Boost( pvHandle, TRUE );
            مجموعه_Thread_Affinity_ماسک( pvHandle, 0x01 );
            ResumeThread( pvHandle );
        }

        /* Start the highest priority task by obtaining its associated thread
         * state structure, in which is stored the thread handle. */
        pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );
        ulCriticalNesting = پورت_NO_CRITICAL_NESTING;

        /* The scheduler is now running. */
        x_پورت_Running = pdTRUE;

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

ساكن uint32_t prv_Process_Yield_وقفه( فراغ )
{
    /* Always return true as this is a yield. */
    أرجع pdTRUE;
}
/*-----------------------------------------------------------*/

ساكن uint32_t prv_Process_Tick_وقفه( فراغ )
{
    uint32_t ulSwitchRequired;

    /* Process the tick itself. */
    configASSERT( x_پورت_Running );
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
    DWORD x_Win_Api_نتیجه;
    ثابت DWORD xTimeoutMilliseconds = 1000;

    /* Going to block on the mutex that ensured exclusive access to the simulated
     * interrupt objects, and the event that signals that a simulated interrupt
     * should be processed. */
    pvObjectList[ 0 ] = pv_وقفه_Event_Mutex;
    pvObjectList[ 1 ] = pv_وقفه_Event;

    /* Create a pending tick to ensure the first task is started as soon as
     * this thread pends. */
    ulPendingInterrupts |= ( 1UL << پورت_وقفه_TICK );
    مجموعه_Event( pv_وقفه_Event );

    طالما( x_پورت_Running == pdTRUE )
    {
        x_Inside_وقفه = pdFALSE;

        /* Wait with timeout so that we can exit from this loop when
         * the scheduler is stopped by calling vPortEndScheduler. */
        x_Win_Api_نتیجه = Wait_For_مضرب_Objects( حجم( pvObjectList ) / حجم( فراغ * ), pvObjectList, TRUE, xTimeoutMilliseconds );

        إذا( x_Win_Api_نتیجه != WAIT_TIMEOUT )
        {
            /* Cannot be in a critical section to get here.  Tasks that exit a
             * critical section will block on a yield mutex to wait for an interrupt to
             * process if an interrupt was set pending while the task was inside the
             * critical section.  xInsideInterrupt prevents interrupts that contain
             * critical sections from doing the same. */
            x_Inside_وقفه = pdTRUE;

            /* Used to indicate whether the simulated interrupt processing has
             * necessitated a context switch to another task/thread. */
            ulSwitchRequired = pdFALSE;

            /* For each interrupt we are interested in processing, each of which is
             * represented by a bit in the 32bit ulPendingInterrupts variable. */
            لكل( i = 0; i < پورت_MAX_INTERRUPTS; i++ )
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
            مجموعه_Event( pxThreadState->pvYieldEvent );
            ReleaseMutex( pv_وقفه_Event_Mutex );
        }
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Delete_Thread( فراغ * pv_Task_مقصد_Delete )
{
    ThreadState_t * pxThreadState;
    uint32_t ul_Error_کد;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( فراغ ) ul_Error_کد;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pv_Task_مقصد_Delete );

    /* Check that the thread is still valid, it might have been closed by
     * vPortCloseRunningThread() - which will be the case if the task associated
     * with the thread originally deleted itself rather than being deleted by a
     * different task. */
    إذا( pxThreadState->pvThread != عدم )
    {
        WaitForSingleObject( pv_وقفه_Event_Mutex, INFINITE );

        /* !!! This is not a nice way to terminate a thread, and will eventually
         * result in resources being depleted if tasks frequently delete other
         * tasks (rather than deleting themselves) as the task stacks will not be
         * freed. */
        ul_Error_کد = TerminateThread( pxThreadState->pvThread, 0 );
        configASSERT( ul_Error_کد );

        ul_Error_کد = CloseHandle( pxThreadState->pvThread );
        configASSERT( ul_Error_کد );

        ReleaseMutex( pv_وقفه_Event_Mutex );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Close_Running_Thread( فراغ * pv_Task_مقصد_Delete,
                              متطاير پایه_Type_t * pxPendYield )
{
    ThreadState_t * pxThreadState;
    فراغ * pvThread;
    uint32_t ul_Error_کد;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( فراغ ) ul_Error_کد;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pv_Task_مقصد_Delete );
    pvThread = pxThreadState->pvThread;

    /* Raise the Windows priority of the thread to ensure the FreeRTOS scheduler
     * does not run and swap it out before it is closed.  If that were to happen
     * the thread would never run again and effectively be a thread handle and
     * memory leak. */
    مجموعه_Thread_اولویت( pvThread, پورت_DELETE_SELF_THREAD_اولویت );

    /* This function will not return, therefore a yield is set as pending to
     * ensure a context switch occurs away from this thread on the next tick. */
    *pxPendYield = pdTRUE;

    /* Mark the thread associated with this task as invalid so
     * vPortDeleteThread() does not try to terminate it. */
    pxThreadState->pvThread = عدم;

    /* Close the thread. */
    ul_Error_کد = CloseHandle( pvThread );
    configASSERT( ul_Error_کد );

    /* This is called from a critical section, which must be exited before the
     * thread stops. */
    taskEXIT_CRITICAL();

    /* Record that a yield is pending so that the next tick interrupt switches
     * out this thread regardless of the value of configUSE_PREEMPTION. This is
     * needed when a task deletes itself - the taskYIELD_WITHIN_API within
     * vTaskDelete does not get called because this function never returns. If
     * we do not pend portINTERRUPT_YIELD here, the next task is not scheduled
     * when configUSE_PREEMPTION is set to 0. */
    إذا( pv_وقفه_Event_Mutex != عدم )
    {
        WaitForSingleObject( pv_وقفه_Event_Mutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << پورت_وقفه_YIELD );
        ReleaseMutex( pv_وقفه_Event_Mutex );
    }

    CloseHandle( pxThreadState->pvYieldEvent );
    ExitThread( 0 );
}
/*-----------------------------------------------------------*/

فراغ v_پورت_انتها_Scheduler( فراغ )
{
    x_پورت_Running = pdFALSE;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Generate_Simulated_وقفه( uint32_t ul_وقفه_عدد )
{
    ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

    configASSERT( x_پورت_Running );

    إذا( ( ul_وقفه_عدد < پورت_MAX_INTERRUPTS ) && ( pv_وقفه_Event_Mutex != عدم ) )
    {
        WaitForSingleObject( pv_وقفه_Event_Mutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << ul_وقفه_عدد );

        /* The simulated interrupt is now held pending, but don't actually
         * process it yet if this call is within a critical section.  It is
         * possible for this to be in a critical section as calls to wait for
         * mutexes are accumulative.  If in a critical section then the event
         * will get set when the critical section nesting count is wound back
         * down to zero. */
        إذا( ulCriticalNesting == پورت_NO_CRITICAL_NESTING )
        {
            مجموعه_Event( pv_وقفه_Event );

            /* Going to wait for an event - make sure the event is not already
             * signaled. */
            ResetEvent( pxThreadState->pvYieldEvent );
        }

        ReleaseMutex( pv_وقفه_Event_Mutex );

        إذا( ulCriticalNesting == پورت_NO_CRITICAL_NESTING )
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

فراغ v_پورت_Generate_Simulated_وقفه_From_Windows_Thread( uint32_t ul_وقفه_عدد )
{
    إذا( x_پورت_Running == pdTRUE )
    {
        /* Can't proceed if in a critical section as pvInterruptEventMutex won't
         * be available. */
        WaitForSingleObject( pv_وقفه_Event_Mutex, INFINITE );

        /* Pending a user defined interrupt to be handled in simulated interrupt
         * handler thread. */
        ulPendingInterrupts |= ( 1UL << ul_وقفه_عدد );

        /* The interrupt is now pending - notify the simulated interrupt
         * handler thread.  Must be outside of a critical section to get here so
         * the handler thread can execute immediately pvInterruptEventMutex is
         * released. */
        configASSERT( ulCriticalNesting == 0UL );
        مجموعه_Event( pv_وقفه_Event );

        /* Give back the mutex so the simulated interrupt handler unblocks
         * and can access the interrupt handler variables. */
        ReleaseMutex( pv_وقفه_Event_Mutex );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورت_مجموعه_وقفه_Handler( uint32_t ul_وقفه_عدد,
                               uint32_t ( * pvHandler )( فراغ ) )
{
    إذا( ul_وقفه_عدد < پورت_MAX_INTERRUPTS )
    {
        إذا( pv_وقفه_Event_Mutex != عدم )
        {
            WaitForSingleObject( pv_وقفه_Event_Mutex, INFINITE );
            ulIsrHandler[ ul_وقفه_عدد ] = pvHandler;
            ReleaseMutex( pv_وقفه_Event_Mutex );
        }
        وإلا
        {
            ulIsrHandler[ ul_وقفه_عدد ] = pvHandler;
        }
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Enter_Critical( فراغ )
{
    إذا( x_پورت_Running == pdTRUE )
    {
        /* The interrupt event mutex is held for the entire critical section,
         * effectively disabling (simulated) interrupts. */
        WaitForSingleObject( pv_وقفه_Event_Mutex, INFINITE );
    }

    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

فراغ v_پورت_Exit_Critical( فراغ )
{
    int32_t lMutexNeedsReleasing;

    /* The interrupt event mutex should already be held by this thread as it was
     * obtained on entry to the critical section. */
    lMutexNeedsReleasing = pdTRUE;

    إذا( ulCriticalNesting > پورت_NO_CRITICAL_NESTING )
    {
        ulCriticalNesting--;

        /* Don't need to wait for any pending interrupts to execute if the
         * critical section was exited from inside an interrupt. */
        إذا( ( ulCriticalNesting == پورت_NO_CRITICAL_NESTING ) && ( x_Inside_وقفه == pdFALSE ) )
        {
            /* Were any interrupts set to pending while interrupts were
             * (simulated) disabled? */
            إذا( ulPendingInterrupts != 0UL )
            {
                ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

                configASSERT( x_پورت_Running );

                /* The interrupt won't actually executed until
                 * pvInterruptEventMutex is released as it waits on both
                 * pvInterruptEventMutex and pvInterruptEvent.
                 * pvInterruptEvent is only set when the simulated
                 * interrupt is pended if the interrupt is pended
                 * from outside a critical section - hence it is set
                 * here. */
                مجموعه_Event( pv_وقفه_Event );

                /* The calling task is going to wait for an event to ensure the
                 * interrupt that is pending executes immediately after the
                 * critical section is exited - so make sure the event is not
                 * already signaled. */
                ResetEvent( pxThreadState->pvYieldEvent );

                /* Mutex will be released now so the (simulated) interrupt can
                 * execute, so does not require releasing on function exit. */
                lMutexNeedsReleasing = pdFALSE;
                ReleaseMutex( pv_وقفه_Event_Mutex );
                WaitForSingleObject( pxThreadState->pvYieldEvent, INFINITE );
            }
        }
    }

    إذا( pv_وقفه_Event_Mutex != عدم )
    {
        إذا( lMutexNeedsReleasing == pdTRUE )
        {
            configASSERT( x_پورت_Running );
            ReleaseMutex( pv_وقفه_Event_Mutex );
        }
    }
}
/*-----------------------------------------------------------*/
