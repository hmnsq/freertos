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

#ضمن "FreeRTOS.h"
#ضمن "task.h"
#ضمن "FreeRTOSConfig.h"

#ضمن "arc/arc_exception.h"
#ضمن "arc/arc_timer.h"
#ضمن "board.h"

#ضمن "arc_freertos_exceptions.h"

متطاير بنانشانی صحيح ulCriticalNesting = 999UL;
متطاير بنانشانی صحيح context_switch_reqflg; /* task context switch request flag in exceptions and interrupts handling */

/**
 * \var exc_nest_count
 * \brief the counter for exc/int processing, =0 no int/exc
 * >1 in int/exc processing
 * @}
 */
uint32_t exc_nest_گنتی;
/* --------------------------------------------------------------------------*/

/**
 * @brief kernel tick interrupt handler of freertos
 */
/* ----------------------------------------------------------------------------*/
ساكن فراغ vKernelTick( فراغ * ptr )
{
    /* clear timer interrupt */
    arc_timer_int_clear( BOARD_OS_TIMER_ID );
    board_timer_update( config_TICK_شرح_HZ );

    إذا( xTaskIncrementTick() )
    {
        پورٹ_YIELD_FROM_ISR(); /* need to make task switch */
    }
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  setup freertos kernel tick
 */
/* ----------------------------------------------------------------------------*/
ساكن فراغ prv_تیاری_Timer_رکاوٹ( فراغ )
{
    بنانشانی صحيح cyc = configCPU_CLOCK_HZ / config_TICK_شرح_HZ;

    int_disable( BOARD_OS_TIMER_INTNO ); /* disable os timer interrupt */
    arc_timer_stop( BOARD_OS_TIMER_ID );
    arc_timer_شروع( BOARD_OS_TIMER_ID, TIMER_CTRL_IE | TIMER_CTRL_NH, cyc );

    int_handler_install( BOARD_OS_TIMER_INTNO, ( INT_HANDLER_T ) vKernelTick );
    int_pri_سیٹ( BOARD_OS_TIMER_INTNO, INT_PRI_MIN );
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
ڈھیر_Type_t * px_پورٹ_Initialise_ڈھیر( ڈھیر_Type_t * px_چوٹی_دا_ڈھیر,
                                     TaskFunction_t px_کوڈ,
                                     فراغ * pvParameters )
{
    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_چوٹی_دا_ڈھیر--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) pvParameters; /* R0 */

    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) px_کوڈ; /* function body */

    /* PC */
    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) شروع_r; /* dispatch return address */

    px_چوٹی_دا_ڈھیر--;
    *px_چوٹی_دا_ڈھیر = ( ڈھیر_Type_t ) پورٹ_NO_CRITICAL_NESTING;
    أرجع px_چوٹی_دا_ڈھیر;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  start the freertos scheduler, go to the first task
 *
 * @returns
 */
/* ----------------------------------------------------------------------------*/
ادھار_Type_t x_پورٹ_شروع_Scheduler( فراغ )
{
    /* Start the timer that generates the tick ISR. */
    prv_تیاری_Timer_رکاوٹ();
    شروع_dispatch();

    /* Should not get here! */
    أرجع 0;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
فراغ v_پورٹ_سرا_Scheduler( فراغ )
{
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  generate a task switch request in ISR
 */
/* ----------------------------------------------------------------------------*/
فراغ v_پورٹ_Yield_From_Isr( فراغ )
{
    بنانشانی صحيح status32;

    status32 = cpu_جندرا_save();
    context_switch_reqflg = true;
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
فراغ v_پورٹ_Yield( فراغ )
{
    بنانشانی صحيح status32;

    status32 = cpu_جندرا_save();
    dispatch();
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
فراغ v_پورٹ_سرا_Task( فراغ )
{
    #إذا ( INCLUDE_vTaskDelete == 1 )
        vTaskDelete( عدم ); /* Delete task itself */
    #جے_انت

    طالما( 1 ) /* Yield to other task */
    {
        v_پورٹ_Yield();
    }
}

#إذا ARC_FEATURE_ڈھیر_CHECK

/*
 * !!! Note !!!
 * This a trick!!!
 * It's a copy from task.c. We need to know the definition of TCB for the purpose of hardware
 * stack check. Pls don't forget to update it when FreeRTOS is updated.
 */
    تعريفنوع بنية tsk_Task_Control_بلاک       /* The old naming convention is used to prevent breaking kernel aware debuggers. */
    {
        متطاير ڈھیر_Type_t * px_چوٹی_دا_ڈھیر; /*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */

        #إذا ( پورٹ_USING_MPU_WRAPPERS == 1 )
            xMPU_SETTINGS xMPUSettings; /*< The MPU settings are defined as part of the port layer.  THIS MUST BE THE SECOND MEMBER OF THE TCB STRUCT. */
        #جے_انت

        List_شے_t x_State_List_شے;                  /*< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
        List_شے_t x_Event_List_شے;                  /*< Used to reference a task from an event list. */
        UBaseType_t ux_ترجیح;                     /*< The priority of the task.  0 is the lowest priority. */
        ڈھیر_Type_t * px_ڈھیر;                      /*< Points to the start of the stack. */
        حرف pcTaskName[ configMAX_TASK_NAME_LEN ]; /*< Descriptive name given to the task when created.  Facilitates debugging only. */ /*lint !e971 Unqualified char types are allowed for strings and single characters only. */

        #إذا ( ( پورٹ_ڈھیر_GROWTH > 0 ) || ( config_ریکارڈ_ڈھیر_بلند_پتہ == 1 ) )
            ڈھیر_Type_t * px_سرا_دا_ڈھیر; /*< Points to the highest valid address for the stack. */
        #جے_انت

        #إذا ( پورٹ_CRITICAL_NESTING_وچ_TCB == 1 )
            UBaseType_t uxCriticalNesting; /*< Holds the critical section nesting depth for ports that do not maintain their own count in the port layer. */
        #جے_انت

        #إذا ( configUSE_TRACE_FACILITY == 1 )
            UBaseType_t uxTCBNumber;  /*< Stores a number that increments each time a TCB is created.  It allows debuggers to determine when a task has been deleted and then recreated. */
            UBaseType_t ux_Task_نمبر; /*< Stores a number specifically for use by third party trace code. */
        #جے_انت

        #إذا ( configUSE_MUTEXES == 1 )
            UBaseType_t ux_ادھار_ترجیح; /*< The priority last assigned to the task - used by the priority inheritance mechanism. */
            UBaseType_t uxMutexesHeld;
        #جے_انت

        #إذا ( config_USE_APPLICATION_TASK_ٹیگ == 1 )
            TaskHookFunction_t px_Task_ٹیگ;
        #جے_انت

        #إذا ( config_عدد_THREAD_LOCAL_STORAGE_سوچکاں > 0 )
            فراغ * pv_Thread_Local_Storage_سوچکاں[ config_عدد_THREAD_LOCAL_STORAGE_سوچکاں ];
        #جے_انت

        #إذا ( config_GENERATE_لگاتار_ویلا_STATS == 1 )
            uint32_t ul_لگاتار_ویلا_Counter; /*< Stores the amount of time the task has spent in the Running state. */
        #جے_انت

        #إذا ( configUSE_C_RUNTIME_TLS_SUPPORT == 1 )
            config_TLS_بلاک_TYPE xTLSBlock; /*< Memory block used as Thread Local Storage (TLS) Block for the task. */
        #جے_انت

        #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
            متطاير uint32_t ul_Notified_قدر;
            متطاير uint8_t ucNotifyState;
        #جے_انت

        /* See the comments above the definition of
         * tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE. */
        #إذا ( tsk_STATIC_AND_DYNAMIC_ونڈ_POSSIBLE != 0 ) /*lint !e731 !e9029 Macro has been consolidated for readability reasons. */
            uint8_t ucStaticallyAllocated;                     /*< Set to pdTRUE if the task is a statically allocated to ensure no attempt is made to free the memory. */
        #جے_انت

        #إذا ( INCLUDE_xTaskAbortDelay == 1 )
            uint8_t ucDelayAborted;
        #جے_انت

        #إذا ( configUSE_POSIX_ERRNO == 1 )
            صحيح iTaskErrno;
        #جے_انت
    } tskTCB;


    فراغ v_پورٹ_سیٹ_ڈھیر_Check( TaskHandle_t old,
                             TaskHandle_t new )
    {
        إذا( new != عدم )
        {
            #إذا ARC_FEATURE_SEC_PRESENT
                arc_aux_write( AUX_S_KSTACK_ادھار, ( uint32_t ) ( new->px_سرا_دا_ڈھیر ) );
                arc_aux_write( AUX_S_KSTACK_چوٹی, ( uint32_t ) ( new->px_ڈھیر ) );
            #وإلا
                arc_aux_write( AUX_KSTACK_ادھار, ( uint32_t ) ( new->px_سرا_دا_ڈھیر ) );
                arc_aux_write( AUX_KSTACK_چوٹی, ( uint32_t ) ( new->px_ڈھیر ) );
            #جے_انت
        }
    }
#جے_انت /* if ARC_FEATURE_STACK_CHECK */
