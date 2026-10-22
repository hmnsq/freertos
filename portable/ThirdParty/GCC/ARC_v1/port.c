/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2020 Synopsys, Inc. or its affiliates.  All Rights Reserved.
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

/*
 * Implementation of functions defined in portable.h
 */

#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOSConfig.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "arc/arc_exception.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "arc/arc_timer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "board.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "arc_freertos_exceptions.h"

ਅਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ulCriticalNesting = 999UL;
ਅਸਥਿਰ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ context_switch_reqflg; /* task context switch request flag in exceptions and interrupts handling */

/**
 * \var exc_nest_count
 * \brief the counter for exc/int processing, =0 no int/exc
 * >1 in int/exc processing
 * @}
 */
uint32_t exc_nest_ਗਿਣਤੀ;
/* --------------------------------------------------------------------------*/

/**
 * @brief kernel tick interrupt handler of freertos
 */
/* ----------------------------------------------------------------------------*/
ਸਥਿਰ ਖਾਲੀ vKernelTick( ਖਾਲੀ * ptr )
{
    /* clear timer interrupt */
    arc_timer_int_clear( BOARD_OS_TIMER_ID );
    board_timer_update( config_TICK_ਦਰ_HZ );

    ਜੇ( xTaskIncrementTick() )
    {
        ਪੋਰਟ_YIELD_FROM_ISR(); /* need to make task switch */
    }
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  setup freertos kernel tick
 */
/* ----------------------------------------------------------------------------*/
ਸਥਿਰ ਖਾਲੀ prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ( ਖਾਲੀ )
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ cyc = configCPU_CLOCK_HZ / config_TICK_ਦਰ_HZ;

    int_disable( BOARD_OS_TIMER_INTNO ); /* disable os timer interrupt */
    arc_timer_stop( BOARD_OS_TIMER_ID );
    arc_timer_ਸ਼ੁਰੂ( BOARD_OS_TIMER_ID, TIMER_CTRL_IE | TIMER_CTRL_NH, cyc );

    int_handler_install( BOARD_OS_TIMER_INTNO, ( INT_HANDLER_T ) vKernelTick );
    int_pri_ਸੈੱਟ( BOARD_OS_TIMER_INTNO, INT_PRI_MIN );
    int_enable( BOARD_OS_TIMER_INTNO );
}

/*
 * Setup the stack of a new task so it is ready to be placed under the
 * scheduler control.  The registers have to be placed on the stack in
 * the order that the port expects to find them.
 *
 * For ARC, task context switch is implemented with the help of SWI exception
 * It's not efficient but simple.
 *
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters; /* R0 */

    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ; /* function body */

    /* PC */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਸ਼ੁਰੂ_r; /* dispatch return address */

    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_NO_CRITICAL_NESTING;
    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  start the freertos scheduler, go to the first task
 *
 * @returns
 */
/* ----------------------------------------------------------------------------*/
ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    /* Start the timer that generates the tick ISR. */
    prv_ਤਿਆਰੀ_Timer_ਰੁਕਾਵਟ();
    ਸ਼ੁਰੂ_dispatch();

    /* Should not get here! */
    ਵਾਪਸ 0;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  generate a task switch request in ISR
 */
/* ----------------------------------------------------------------------------*/
ਖਾਲੀ v_ਪੋਰਟ_Yield_From_Isr( ਖਾਲੀ )
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ status32;

    status32 = cpu_ਤਾਲਾ_save();
    context_switch_reqflg = true;
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
ਖਾਲੀ v_ਪੋਰਟ_Yield( ਖਾਲੀ )
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ status32;

    status32 = cpu_ਤਾਲਾ_save();
    dispatch();
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Task( ਖਾਲੀ )
{
    #ਜੇ ( INCLUDE_vTaskDelete == 1 )
        vTaskDelete( ਨਿਰਾ ); /* Delete task itself */
    #ਜੇ_ਅੰਤ

    ਜਦੋਂ( 1 ) /* Yield to other task */
    {
        v_ਪੋਰਟ_Yield();
    }
}

#ਜੇ ARC_FEATURE_ਢੇਰ_CHECK

/*
 * !!! Note !!!
 * This a trick!!!
 * It's a copy from task.c. We need to know the definition of TCB for the purpose of hardware
 * stack check. Pls don't forget to update it when FreeRTOS is updated.
 */
    ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ tsk_Task_Control_ਖੰਡ       /* The old naming convention is used to prevent breaking kernel aware debuggers. */
    {
        ਅਸਥਿਰ ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ; /*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */

        #ਜੇ ( ਪੋਰਟ_USING_MPU_WRAPPERS == 1 )
            xMPU_SETTINGS xMPUSettings; /*< The MPU settings are defined as part of the port layer.  THIS MUST BE THE SECOND MEMBER OF THE TCB STRUCT. */
        #ਜੇ_ਅੰਤ

        List_ਵਸਤੂ_t x_State_List_ਵਸਤੂ;                  /*< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
        List_ਵਸਤੂ_t x_Event_List_ਵਸਤੂ;                  /*< Used to reference a task from an event list. */
        UBaseType_t ux_ਤਰਜੀਹ;                     /*< The priority of the task.  0 is the lowest priority. */
        ਢੇਰ_Type_t * px_ਢੇਰ;                      /*< Points to the start of the stack. */
        ਅੱਖਰ pcTaskName[ configMAX_TASK_NAME_LEN ]; /*< Descriptive name given to the task when created.  Facilitates debugging only. */ /*lint !e971 Unqualified char types are allowed for strings and single characters only. */

        #ਜੇ ( ( ਪੋਰਟ_ਢੇਰ_GROWTH > 0 ) || ( config_ਰਿਕਾਰਡ_ਢੇਰ_ਉੱਚਾ_ਪਤਾ == 1 ) )
            ਢੇਰ_Type_t * px_ਸਿਰਾ_ਦਾ_ਢੇਰ; /*< Points to the highest valid address for the stack. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( ਪੋਰਟ_CRITICAL_NESTING_ਵਿੱਚ_TCB == 1 )
            UBaseType_t uxCriticalNesting; /*< Holds the critical section nesting depth for ports that do not maintain their own count in the port layer. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( configUSE_TRACE_FACILITY == 1 )
            UBaseType_t uxTCBNumber;  /*< Stores a number that increments each time a TCB is created.  It allows debuggers to determine when a task has been deleted and then recreated. */
            UBaseType_t ux_Task_ਸੰਖਿਆ; /*< Stores a number specifically for use by third party trace code. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( configUSE_MUTEXES == 1 )
            UBaseType_t ux_ਅਧਾਰ_ਤਰਜੀਹ; /*< The priority last assigned to the task - used by the priority inheritance mechanism. */
            UBaseType_t uxMutexesHeld;
        #ਜੇ_ਅੰਤ

        #ਜੇ ( config_USE_APPLICATION_TASK_ਟੈਗ == 1 )
            TaskHookFunction_t px_Task_ਟੈਗ;
        #ਜੇ_ਅੰਤ

        #ਜੇ ( config_ਅੰਕ_THREAD_LOCAL_STORAGE_ਸੂਚਕ_ਸਾਰੇ > 0 )
            ਖਾਲੀ * pv_Thread_Local_Storage_ਸੂਚਕ_ਸਾਰੇ[ config_ਅੰਕ_THREAD_LOCAL_STORAGE_ਸੂਚਕ_ਸਾਰੇ ];
        #ਜੇ_ਅੰਤ

        #ਜੇ ( config_GENERATE_ਲੜੀਵਾਰ_ਸਮਾਂ_STATS == 1 )
            uint32_t ul_ਲੜੀਵਾਰ_ਸਮਾਂ_Counter; /*< Stores the amount of time the task has spent in the Running state. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( configUSE_C_RUNTIME_TLS_SUPPORT == 1 )
            config_TLS_ਖੰਡ_TYPE xTLSBlock; /*< Memory block used as Thread Local Storage (TLS) Block for the task. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( configUSE_TASK_NOTIFICATIONS == 1 )
            ਅਸਥਿਰ uint32_t ul_Notified_ਮੁੱਲ;
            ਅਸਥਿਰ uint8_t ucNotifyState;
        #ਜੇ_ਅੰਤ

        /* See the comments above the definition of
         * tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE. */
        #ਜੇ ( tsk_STATIC_AND_DYNAMIC_ਵੰਡ_POSSIBLE != 0 ) /*lint !e731 !e9029 Macro has been consolidated for readability reasons. */
            uint8_t ucStaticallyAllocated;                     /*< Set to pdTRUE if the task is a statically allocated to ensure no attempt is made to free the memory. */
        #ਜੇ_ਅੰਤ

        #ਜੇ ( INCLUDE_xTaskAbortDelay == 1 )
            uint8_t ucDelayAborted;
        #ਜੇ_ਅੰਤ

        #ਜੇ ( configUSE_POSIX_ERRNO == 1 )
            ਪੂਰਨ iTaskErrno;
        #ਜੇ_ਅੰਤ
    } tskTCB;


    ਖਾਲੀ v_ਪੋਰਟ_ਸੈੱਟ_ਢੇਰ_Check( TaskHandle_t old,
                             TaskHandle_t new )
    {
        ਜੇ( new != ਨਿਰਾ )
        {
            arc_aux_write( AUX_USTACK_ਅਧਾਰ, ( uint32_t ) ( new->px_ਸਿਰਾ_ਦਾ_ਢੇਰ ) );
            arc_aux_write( AUX_USTACK_ਸਿਖਰ, ( uint32_t ) ( new->px_ਢੇਰ ) );
        }
    }
#ਜੇ_ਅੰਤ /* if ARC_FEATURE_STACK_CHECK */
