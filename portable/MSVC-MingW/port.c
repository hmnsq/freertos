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
#شامل <stdio.h>

/* Scheduler includes. */
#شامل "FreeRTOS.h"
#شامل "task.h"

#اگر_تعریف_شدہ WIN32_LEAN_AND_اوسط
    #شامل <winsock2.h>
#ورنہ
    #شامل <winsock.h>
#اگر_ختم

#اگر_تعریف_شدہ _MSC_VER
    #شامل <timeapi.h>
    #ہدایت comment(lib, "winmm.lib")
#ورنہ
    #شامل <mmsystem.h>
#اگر_ختم

#تعریف_کرو پورٹ_MAX_INTERRUPTS                          ( ( uint32_t ) حجم( uint32_t ) * 8UL ) /* The number of bits in an uint32_t. */
#تعریف_کرو پورٹ_NO_CRITICAL_NESTING                     ( ( uint32_t ) 0 )

/* The priorities at which the various components of the simulation execute. */
#تعریف_کرو پورٹ_DELETE_SELF_THREAD_ترجیح             THREAD_ترجیح_وقت_CRITICAL /* Must be highest. */
#تعریف_کرو پورٹ_SIMULATED_INTERRUPTS_THREAD_ترجیح    THREAD_ترجیح_وقت_CRITICAL
#تعریف_کرو پورٹ_SIMULATED_TIMER_THREAD_ترجیح         THREAD_ترجیح_HIGHEST
#تعریف_کرو پورٹ_TASK_THREAD_ترجیح                    THREAD_ترجیح_ABOVE_معمول

/*
 * Created as a high priority thread, this function uses a timer to simulate
 * a tick interrupt being generated on an embedded target.  In this Windows
 * environment the timer does not achieve anything approaching real time
 * performance though.
 */
ساکن DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter );

/*
 * Process all the simulated interrupts - each represented by a bit in
 * ulPendingInterrupts variable.
 */
ساکن خالی prvProcessSimulatedInterrupts( خالی );

/*
 * Interrupt handlers used by the kernel itself.  These are executed from the
 * simulated interrupt handler thread.
 */
ساکن uint32_t prv_Process_Yield_مداخلت( خالی );
ساکن uint32_t prv_Process_Tick_مداخلت( خالی );

/*
 * Exiting a critical section will cause the calling task to block on yield
 * event to wait for an interrupt to process if an interrupt was pended while
 * inside the critical section.  This variable protects against a recursive
 * attempt to obtain pvInterruptEventMutex if a critical section is used inside
 * an interrupt handler itself.
 */
متلون بنیاد_Type_t x_Inside_مداخلت = pdFALSE;

/*
 * Called when the process exits to let Windows know the high timer resolution
 * is no longer required.
 */
ساکن BOOL WINAPI prv_انتہا_Process( DWORD dwCtrlType );

/*-----------------------------------------------------------*/

/* The WIN32 simulator runs each task in a thread.  The context switching is
 * managed by the threads, so the task stack does not have to be managed directly,
 * although the task stack is still used to hold an xThreadState structure this is
 * the only thing it will ever hold.  The structure indirectly maps the task handle
 * to a thread handle. */
قسمتعریف ساخت
{
    /* Handle of the thread that executes the task. */
    خالی * pvThread;

    /* Event used to make sure the thread does not execute past a yield point
     * between the call to SuspendThread() to suspend the thread and the
     * asynchronous SuspendThread() operation actually being performed. */
    خالی * pvYieldEvent;
} ThreadState_t;

/* Simulated interrupts waiting to be processed.  This is a bit mask where each
 * bit represents one interrupt, so a maximum of 32 interrupts can be simulated. */
ساکن متلون uint32_t ulPendingInterrupts = 0UL;

/* An event used to inform the simulated interrupt processing thread (a high
 * priority thread that simulated interrupt processing) that an interrupt is
 * pending. */
ساکن خالی * pv_مداخلت_Event = تہی;

/* Mutex used to protect all the simulated interrupt variables that are accessed
 * by multiple threads. */
ساکن خالی * pv_مداخلت_Event_Mutex = تہی;

/* The critical nesting count for the currently executing task.  This is
 * initialised to a non-zero value so interrupts do not become enabled during
 * the initialisation phase.  As each task has its own critical nesting value
 * ulCriticalNesting will get set to zero when the first task runs.  This
 * initialisation is probably not critical in this simulated environment as the
 * simulated interrupt handlers do not get created until the FreeRTOS scheduler is
 * started anyway. */
ساکن متلون uint32_t ulCriticalNesting = 9999UL;

/* Handlers for all the simulated software interrupts.  The first two positions
 * are used for the Yield and Tick interrupts so are handled slightly differently,
 * all the other interrupts can be user defined. */
ساکن uint32_t (* ulIsrHandler[ پورٹ_MAX_INTERRUPTS ])( خالی ) = { 0 };

/* Pointer to the TCB of the currently executing task. */
خارجی خالی * متلون pxCurrentTCB;

/* Used to ensure nothing is processed during the startup sequence. */
ساکن بنیاد_Type_t x_پورٹ_Running = pdFALSE;

/*-----------------------------------------------------------*/

ساکن DWORD WINAPI prvSimulatedPeripheralTimer( LPVOID lpParameter )
{
    TickType_t x_Minimum_Windows_بلاک_وقت;
    TIMECAPS x_وقت_Caps;
    TickType_t x_Wait_وقت_Between_Ticks = پورٹ_TICK_PERIOD_MS;
    HANDLE hTimer = تہی;
    LARGE_INTEGER li_Due_وقت;
    BOOL bSuccess;

    /* Set the timer resolution to the maximum possible. */
    اگر( وقت_Get_Dev_Caps( &x_وقت_Caps, حجم( x_وقت_Caps ) ) == MMSYSERR_NOERROR )
    {
        x_Minimum_Windows_بلاک_وقت = ( TickType_t ) x_وقت_Caps.wPeriodMin;
        وقت_Begin_Period( x_وقت_Caps.wPeriodMin );

        /* Register an exit handler so the timeBeginPeriod() function can be
         * matched with a timeEndPeriod() when the application exits. */
        سیٹ_Console_Ctrl_Handler( prv_انتہا_Process, TRUE );
    }
    ورنہ
    {
        x_Minimum_Windows_بلاک_وقت = ( TickType_t ) 20;
    }

    /* Just to prevent compiler warnings. */
    ( خالی ) lpParameter;

    /* Tick time for the timer is adjusted with the maximum available
     resolution. */
    اگر( پورٹ_TICK_PERIOD_MS < x_Minimum_Windows_بلاک_وقت )
    {
        x_Wait_وقت_Between_Ticks = x_Minimum_Windows_بلاک_وقت;
    }

    /* Convert the tick time in milliseconds to nanoseconds resolution
     for the Waitable Timer. */
    li_Due_وقت.u.کم_Part = x_Wait_وقت_Between_Ticks * 1000 * 1000;
    li_Due_وقت.u.بلند_Part = 0;

    /* Create a synchronization Waitable Timer.*/
    hTimer = CreateWaitableTimer( تہی, FALSE, تہی );

    configASSERT( hTimer != تہی );

    /* Set the Waitable Timer. The timer is set to run periodically at every
    xWaitTimeBetweenTicks milliseconds. */
    bSuccess = سیٹ_Waitable_Timer( hTimer, &li_Due_وقت, x_Wait_وقت_Between_Ticks, تہی, تہی, 0 );
    configASSERT( bSuccess );

    جب( x_پورٹ_Running == pdTRUE )
    {
        /* Wait until the timer expires and we can access the simulated interrupt
         * variables. */

        WaitForSingleObject( hTimer, INFINITE );

        v_پورٹ_Generate_Simulated_مداخلت_From_Windows_Thread( پورٹ_مداخلت_TICK );
    }

    واپس 0;
}
/*-----------------------------------------------------------*/

ساکن BOOL WINAPI prv_انتہا_Process( DWORD dwCtrlType )
{
    TIMECAPS x_وقت_Caps;

    ( خالی ) dwCtrlType;

    اگر( وقت_Get_Dev_Caps( &x_وقت_Caps, حجم( x_وقت_Caps ) ) == MMSYSERR_NOERROR )
    {
        /* Match the call to timeBeginPeriod( xTimeCaps.wPeriodMin ) made when
         * the process started with a timeEndPeriod() as the process exits. */
        وقت_انتہا_Period( x_وقت_Caps.wPeriodMin );
    }

    واپس pdFALSE;
}
/*-----------------------------------------------------------*/

ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_کا_ڈھیر,
                                     TaskFunction_t px_رمز,
                                     خالی * pvParameters )
{
    ThreadState_t * pxThreadState = تہی;
    int8_t * pc_چوٹی_کا_ڈھیر = ( int8_t * ) px_چوٹی_کا_ڈھیر;
    ثابت سائز_T x_ڈھیر_سائز = 1024; /* Set the size to a small number which will get rounded up to the minimum possible. */

    /* In this simulated case a stack is not initialised, but instead a thread
     * is created that will execute the task being created.  The thread handles
     * the context switching itself.  The ThreadState_t object is placed onto
     * the stack that was created for the task - so the stack buffer is still
     * used, just not in the conventional way.  It will not be used for anything
     * other than holding this structure. */
    pxThreadState = ( ThreadState_t * ) ( pc_چوٹی_کا_ڈھیر - حجم( ThreadState_t ) );

    /* Create the event used to prevent the thread from executing past its yield
     * point if the SuspendThread() call that suspends the thread does not take
     * effect immediately (it is an asynchronous call). */
    pxThreadState->pvYieldEvent = CreateEvent( تہی,   /* Default security attributes. */
                                               FALSE,  /* Auto reset. */
                                               FALSE,  /* Start not signalled. */
                                               تہی ); /* No name. */


#اگر_تعریف_شدہ __GNUC__
    /* GCC reports the warning for the cast operation from TaskFunction_t to LPTHREAD_START_ROUTINE. */
    /* Disable this warning here by the #pragma option. */
#ہدایت GCC diagnostic ڈالو
#ہدایت GCC diagnostic ignored "-Wcast-function-type"
#اگر_ختم
    /* Create the thread itself. */
    pxThreadState->pvThread = CreateThread( تہی, x_ڈھیر_سائز, ( LPTHREAD_آغاز_ROUTINE ) px_رمز, pvParameters, CREATE_SUSPENDED | ڈھیر_سائز_PARAM_IS_A_RESERVATION, تہی );
#اگر_تعریف_شدہ __GNUC__
#ہدایت GCC diagnostic نکالو
#اگر_ختم

    configASSERT( pxThreadState->pvThread ); /* See comment where TerminateThread() is called. */
    سیٹ_Thread_Affinity_نقاب( pxThreadState->pvThread, 0x01 );
    سیٹ_Thread_ترجیح_Boost( pxThreadState->pvThread, TRUE );
    سیٹ_Thread_ترجیح( pxThreadState->pvThread, پورٹ_TASK_THREAD_ترجیح );

    واپس ( ڈھیر_Type_t * ) pxThreadState;
}
/*-----------------------------------------------------------*/

بنیاد_Type_t x_پورٹ_آغاز_Scheduler( خالی )
{
    خالی * pvHandle = تہی;
    int32_t lSuccess;
    ThreadState_t * pxThreadState = تہی;
    SYSTEM_INFO xSystemInfo;

    /* This port runs windows threads with extremely high priority.  All the
     * threads execute on the same core - to prevent locking up the host only start
     * if the host has multiple cores. */
    GetSystemInfo( &xSystemInfo );

    اگر( xSystemInfo.dw_نمبر_کا_Processors <= 1 )
    {
        لکھو( "This version of the FreeRTOS Windows port can only be used on multi-core hosts.\r\n" );
        lSuccess = pdFAIL;
    }
    ورنہ
    {
        lSuccess = pdPASS;

        /* The highest priority class is used to [try to] prevent other Windows
         * activity interfering with FreeRTOS timing too much. */
        اگر( سیٹ_ترجیح_Class( GetCurrentProcess(), REALTIME_ترجیح_CLASS ) == 0 )
        {
            لکھو( "SetPriorityClass() failed\r\n" );
        }

        /* Install the interrupt handlers used by the scheduler itself. */
        v_پورٹ_سیٹ_مداخلت_Handler( پورٹ_مداخلت_YIELD, prv_Process_Yield_مداخلت );
        v_پورٹ_سیٹ_مداخلت_Handler( پورٹ_مداخلت_TICK, prv_Process_Tick_مداخلت );

        /* Create the events and mutexes that are used to synchronise all the
         * threads. */
        pv_مداخلت_Event_Mutex = CreateMutex( تہی, FALSE, تہی );
        pv_مداخلت_Event = CreateEvent( تہی, FALSE, FALSE, تہی );

        اگر( ( pv_مداخلت_Event_Mutex == تہی ) || ( pv_مداخلت_Event == تہی ) )
        {
            lSuccess = pdFAIL;
        }

        /* Set the priority of this thread such that it is above the priority of
         * the threads that run tasks.  This higher priority is required to ensure
         * simulated interrupts take priority over tasks. */
        pvHandle = GetCurrentThread();

        اگر( pvHandle == تہی )
        {
            lSuccess = pdFAIL;
        }
    }

    اگر( lSuccess == pdPASS )
    {
        اگر( سیٹ_Thread_ترجیح( pvHandle, پورٹ_SIMULATED_INTERRUPTS_THREAD_ترجیح ) == 0 )
        {
            lSuccess = pdFAIL;
        }

        سیٹ_Thread_ترجیح_Boost( pvHandle, TRUE );
        سیٹ_Thread_Affinity_نقاب( pvHandle, 0x01 );
    }

    اگر( lSuccess == pdPASS )
    {
        /* Start the thread that simulates the timer peripheral to generate
         * tick interrupts.  The priority is set below that of the simulated
         * interrupt handler so the interrupt event mutex is used for the
         * handshake / overrun protection. */
        pvHandle = CreateThread( تہی, 0, prvSimulatedPeripheralTimer, تہی, CREATE_SUSPENDED, تہی );

        اگر( pvHandle != تہی )
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
    واپس 0;
}
/*-----------------------------------------------------------*/

ساکن uint32_t prv_Process_Yield_مداخلت( خالی )
{
    /* Always return true as this is a yield. */
    واپس pdTRUE;
}
/*-----------------------------------------------------------*/

ساکن uint32_t prv_Process_Tick_مداخلت( خالی )
{
    uint32_t ulSwitchRequired;

    /* Process the tick itself. */
    configASSERT( x_پورٹ_Running );
    ulSwitchRequired = ( uint32_t ) xTaskIncrementTick();

    واپس ulSwitchRequired;
}
/*-----------------------------------------------------------*/

ساکن خالی prvProcessSimulatedInterrupts( خالی )
{
    uint32_t ulSwitchRequired, i;
    ThreadState_t * pxThreadState;
    خالی * pvObjectList[ 2 ];
    CONTEXT xContext;
    DWORD x_Win_Api_نتیجہ;
    ثابت DWORD xTimeoutMilliseconds = 1000;

    /* Going to block on the mutex that ensured exclusive access to the simulated
     * interrupt objects, and the event that signals that a simulated interrupt
     * should be processed. */
    pvObjectList[ 0 ] = pv_مداخلت_Event_Mutex;
    pvObjectList[ 1 ] = pv_مداخلت_Event;

    /* Create a pending tick to ensure the first task is started as soon as
     * this thread pends. */
    ulPendingInterrupts |= ( 1UL << پورٹ_مداخلت_TICK );
    سیٹ_Event( pv_مداخلت_Event );

    جب( x_پورٹ_Running == pdTRUE )
    {
        x_Inside_مداخلت = pdFALSE;

        /* Wait with timeout so that we can exit from this loop when
         * the scheduler is stopped by calling vPortEndScheduler. */
        x_Win_Api_نتیجہ = Wait_For_مضرب_Objects( حجم( pvObjectList ) / حجم( خالی * ), pvObjectList, TRUE, xTimeoutMilliseconds );

        اگر( x_Win_Api_نتیجہ != WAIT_TIMEOUT )
        {
            /* Cannot be in a critical section to get here.  Tasks that exit a
             * critical section will block on a yield mutex to wait for an interrupt to
             * process if an interrupt was set pending while the task was inside the
             * critical section.  xInsideInterrupt prevents interrupts that contain
             * critical sections from doing the same. */
            x_Inside_مداخلت = pdTRUE;

            /* Used to indicate whether the simulated interrupt processing has
             * necessitated a context switch to another task/thread. */
            ulSwitchRequired = pdFALSE;

            /* For each interrupt we are interested in processing, each of which is
             * represented by a bit in the 32bit ulPendingInterrupts variable. */
            برائے( i = 0; i < پورٹ_MAX_INTERRUPTS; i++ )
            {
                /* Is the simulated interrupt pending? */
                اگر( ( ulPendingInterrupts & ( 1UL << i ) ) != 0 )
                {
                    /* Is a handler installed? */
                    اگر( ulIsrHandler[ i ] != تہی )
                    {
                        /* Run the actual handler.  Handlers return pdTRUE if they
                         * necessitate a context switch. */
                        اگر( ulIsrHandler[ i ]() != pdFALSE )
                        {
                            /* A bit mask is used purely to help debugging. */
                            ulSwitchRequired |= ( 1UL << i );
                        }
                    }

                    /* Clear the interrupt pending bit. */
                    ulPendingInterrupts &= ~( 1UL << i );
                }
            }

            اگر( ulSwitchRequired != pdFALSE )
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
                ( خالی ) GetThreadContext( pxThreadState->pvThread, &xContext );

                /* Select the next task to run. */
                vTaskSwitchContext();

                /* Obtain the state of the task now selected to enter the
                 * Running state. */
                pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pxCurrentTCB );

                /* pxThreadState->pvThread can be NULL if the task deleted
                 * itself - but a deleted task should never be resumed here. */
                configASSERT( pxThreadState->pvThread != تہی );
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
            ReleaseMutex( pv_مداخلت_Event_Mutex );
        }
    }
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Delete_Thread( خالی * pv_Task_مقصد_Delete )
{
    ThreadState_t * pxThreadState;
    uint32_t ul_Error_رمز;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( خالی ) ul_Error_رمز;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pv_Task_مقصد_Delete );

    /* Check that the thread is still valid, it might have been closed by
     * vPortCloseRunningThread() - which will be the case if the task associated
     * with the thread originally deleted itself rather than being deleted by a
     * different task. */
    اگر( pxThreadState->pvThread != تہی )
    {
        WaitForSingleObject( pv_مداخلت_Event_Mutex, INFINITE );

        /* !!! This is not a nice way to terminate a thread, and will eventually
         * result in resources being depleted if tasks frequently delete other
         * tasks (rather than deleting themselves) as the task stacks will not be
         * freed. */
        ul_Error_رمز = TerminateThread( pxThreadState->pvThread, 0 );
        configASSERT( ul_Error_رمز );

        ul_Error_رمز = CloseHandle( pxThreadState->pvThread );
        configASSERT( ul_Error_رمز );

        ReleaseMutex( pv_مداخلت_Event_Mutex );
    }
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Close_Running_Thread( خالی * pv_Task_مقصد_Delete,
                              متلون بنیاد_Type_t * pxPendYield )
{
    ThreadState_t * pxThreadState;
    خالی * pvThread;
    uint32_t ul_Error_رمز;

    /* Remove compiler warnings if configASSERT() is not defined. */
    ( خالی ) ul_Error_رمز;

    /* Find the handle of the thread being deleted. */
    pxThreadState = ( ThreadState_t * ) ( *( size_t * ) pv_Task_مقصد_Delete );
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
    pxThreadState->pvThread = تہی;

    /* Close the thread. */
    ul_Error_رمز = CloseHandle( pvThread );
    configASSERT( ul_Error_رمز );

    /* This is called from a critical section, which must be exited before the
     * thread stops. */
    taskEXIT_CRITICAL();

    /* Record that a yield is pending so that the next tick interrupt switches
     * out this thread regardless of the value of configUSE_PREEMPTION. This is
     * needed when a task deletes itself - the taskYIELD_WITHIN_API within
     * vTaskDelete does not get called because this function never returns. If
     * we do not pend portINTERRUPT_YIELD here, the next task is not scheduled
     * when configUSE_PREEMPTION is set to 0. */
    اگر( pv_مداخلت_Event_Mutex != تہی )
    {
        WaitForSingleObject( pv_مداخلت_Event_Mutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << پورٹ_مداخلت_YIELD );
        ReleaseMutex( pv_مداخلت_Event_Mutex );
    }

    CloseHandle( pxThreadState->pvYieldEvent );
    ExitThread( 0 );
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_انتہا_Scheduler( خالی )
{
    x_پورٹ_Running = pdFALSE;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Generate_Simulated_مداخلت( uint32_t ul_مداخلت_نمبر )
{
    ThreadState_t * pxThreadState = ( ThreadState_t * ) *( ( size_t * ) pxCurrentTCB );

    configASSERT( x_پورٹ_Running );

    اگر( ( ul_مداخلت_نمبر < پورٹ_MAX_INTERRUPTS ) && ( pv_مداخلت_Event_Mutex != تہی ) )
    {
        WaitForSingleObject( pv_مداخلت_Event_Mutex, INFINITE );
        ulPendingInterrupts |= ( 1UL << ul_مداخلت_نمبر );

        /* The simulated interrupt is now held pending, but don't actually
         * process it yet if this call is within a critical section.  It is
         * possible for this to be in a critical section as calls to wait for
         * mutexes are accumulative.  If in a critical section then the event
         * will get set when the critical section nesting count is wound back
         * down to zero. */
        اگر( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING )
        {
            سیٹ_Event( pv_مداخلت_Event );

            /* Going to wait for an event - make sure the event is not already
             * signaled. */
            ResetEvent( pxThreadState->pvYieldEvent );
        }

        ReleaseMutex( pv_مداخلت_Event_Mutex );

        اگر( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING )
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

خالی v_پورٹ_Generate_Simulated_مداخلت_From_Windows_Thread( uint32_t ul_مداخلت_نمبر )
{
    اگر( x_پورٹ_Running == pdTRUE )
    {
        /* Can't proceed if in a critical section as pvInterruptEventMutex won't
         * be available. */
        WaitForSingleObject( pv_مداخلت_Event_Mutex, INFINITE );

        /* Pending a user defined interrupt to be handled in simulated interrupt
         * handler thread. */
        ulPendingInterrupts |= ( 1UL << ul_مداخلت_نمبر );

        /* The interrupt is now pending - notify the simulated interrupt
         * handler thread.  Must be outside of a critical section to get here so
         * the handler thread can execute immediately pvInterruptEventMutex is
         * released. */
        configASSERT( ulCriticalNesting == 0UL );
        سیٹ_Event( pv_مداخلت_Event );

        /* Give back the mutex so the simulated interrupt handler unblocks
         * and can access the interrupt handler variables. */
        ReleaseMutex( pv_مداخلت_Event_Mutex );
    }
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_سیٹ_مداخلت_Handler( uint32_t ul_مداخلت_نمبر,
                               uint32_t ( * pvHandler )( خالی ) )
{
    اگر( ul_مداخلت_نمبر < پورٹ_MAX_INTERRUPTS )
    {
        اگر( pv_مداخلت_Event_Mutex != تہی )
        {
            WaitForSingleObject( pv_مداخلت_Event_Mutex, INFINITE );
            ulIsrHandler[ ul_مداخلت_نمبر ] = pvHandler;
            ReleaseMutex( pv_مداخلت_Event_Mutex );
        }
        ورنہ
        {
            ulIsrHandler[ ul_مداخلت_نمبر ] = pvHandler;
        }
    }
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Enter_Critical( خالی )
{
    اگر( x_پورٹ_Running == pdTRUE )
    {
        /* The interrupt event mutex is held for the entire critical section,
         * effectively disabling (simulated) interrupts. */
        WaitForSingleObject( pv_مداخلت_Event_Mutex, INFINITE );
    }

    ulCriticalNesting++;
}
/*-----------------------------------------------------------*/

خالی v_پورٹ_Exit_Critical( خالی )
{
    int32_t lMutexNeedsReleasing;

    /* The interrupt event mutex should already be held by this thread as it was
     * obtained on entry to the critical section. */
    lMutexNeedsReleasing = pdTRUE;

    اگر( ulCriticalNesting > پورٹ_NO_CRITICAL_NESTING )
    {
        ulCriticalNesting--;

        /* Don't need to wait for any pending interrupts to execute if the
         * critical section was exited from inside an interrupt. */
        اگر( ( ulCriticalNesting == پورٹ_NO_CRITICAL_NESTING ) && ( x_Inside_مداخلت == pdFALSE ) )
        {
            /* Were any interrupts set to pending while interrupts were
             * (simulated) disabled? */
            اگر( ulPendingInterrupts != 0UL )
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
                سیٹ_Event( pv_مداخلت_Event );

                /* The calling task is going to wait for an event to ensure the
                 * interrupt that is pending executes immediately after the
                 * critical section is exited - so make sure the event is not
                 * already signaled. */
                ResetEvent( pxThreadState->pvYieldEvent );

                /* Mutex will be released now so the (simulated) interrupt can
                 * execute, so does not require releasing on function exit. */
                lMutexNeedsReleasing = pdFALSE;
                ReleaseMutex( pv_مداخلت_Event_Mutex );
                WaitForSingleObject( pxThreadState->pvYieldEvent, INFINITE );
            }
        }
    }

    اگر( pv_مداخلت_Event_Mutex != تہی )
    {
        اگر( lMutexNeedsReleasing == pdTRUE )
        {
            configASSERT( x_پورٹ_Running );
            ReleaseMutex( pv_مداخلت_Event_Mutex );
        }
    }
}
/*-----------------------------------------------------------*/
