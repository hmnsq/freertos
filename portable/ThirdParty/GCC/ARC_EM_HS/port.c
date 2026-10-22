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

متطاير بینښه صحيح ulCriticalNesting = 999UL;
متطاير بینښه صحيح context_switch_reqflg; /* task context switch request flag in exceptions and interrupts handling */

/**
 * \var exc_nest_count
 * \brief the counter for exc/int processing, =0 no int/exc
 * >1 in int/exc processing
 * @}
 */
uint32_t exc_nest_شمېر;
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
        پورټ_YIELD_FROM_ISR(); /* need to make task switch */
    }
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  setup freertos kernel tick
 */
/* ----------------------------------------------------------------------------*/
ساكن فراغ prv_تیاری_Timer_مداخله( فراغ )
{
    بینښه صحيح cyc = configCPU_CLOCK_HZ / config_TICK_شرح_HZ;

    int_disable( BOARD_OS_TIMER_INTNO ); /* disable os timer interrupt */
    arc_timer_stop( BOARD_OS_TIMER_ID );
    arc_timer_پیل( BOARD_OS_TIMER_ID, TIMER_CTRL_IE | TIMER_CTRL_NH, cyc );

    int_handler_install( BOARD_OS_TIMER_INTNO, ( INT_HANDLER_T ) vKernelTick );
    int_pri_سېټ( BOARD_OS_TIMER_INTNO, INT_PRI_MIN );
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
ډېری_Type_t * px_پورټ_Initialise_ډېری( ډېری_Type_t * px_سر_د_ډېری,
                                     TaskFunction_t px_کوډ,
                                     فراغ * pvParameters )
{
    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_سر_د_ډېری--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_سر_د_ډېری = ( ډېری_Type_t ) pvParameters; /* R0 */

    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) px_کوډ; /* function body */

    /* PC */
    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پیل_r; /* dispatch return address */

    px_سر_د_ډېری--;
    *px_سر_د_ډېری = ( ډېری_Type_t ) پورټ_NO_CRITICAL_NESTING;
    أرجع px_سر_د_ډېری;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  start the freertos scheduler, go to the first task
 *
 * @returns
 */
/* ----------------------------------------------------------------------------*/
بنسټ_Type_t x_پورټ_پیل_Scheduler( فراغ )
{
    /* Start the timer that generates the tick ISR. */
    prv_تیاری_Timer_مداخله();
    پیل_dispatch();

    /* Should not get here! */
    أرجع 0;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
فراغ v_پورټ_پای_ټکی_Scheduler( فراغ )
{
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  generate a task switch request in ISR
 */
/* ----------------------------------------------------------------------------*/
فراغ v_پورټ_Yield_From_Isr( فراغ )
{
    بینښه صحيح status32;

    status32 = cpu_قلف_save();
    context_switch_reqflg = true;
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
فراغ v_پورټ_Yield( فراغ )
{
    بینښه صحيح status32;

    status32 = cpu_قلف_save();
    dispatch();
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
فراغ v_پورټ_پای_ټکی_Task( فراغ )
{
    #إذا ( INCLUDE_vTaskDelete == 1 )
        vTaskDelete( عدم ); /* Delete task itself */
    #د_که_پای

    طالما( 1 ) /* Yield to other task */
    {
        v_پورټ_Yield();
    }
}

#إذا ARC_FEATURE_ډېری_CHECK

/*
 * !!! Note !!!
 * This a trick!!!
 * It's a copy from task.c. We need to know the definition of TCB for the purpose of hardware
 * stack check. Pls don't forget to update it when FreeRTOS is updated.
 */
    تعريفنوع بنية tsk_Task_Control_بلاک       /* The old naming convention is used to prevent breaking kernel aware debuggers. */
    {
        متطاير ډېری_Type_t * px_سر_د_ډېری; /*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */

        #إذا ( پورټ_USING_MPU_WRAPPERS == 1 )
            xMPU_SETTINGS xMPUSettings; /*< The MPU settings are defined as part of the port layer.  THIS MUST BE THE SECOND MEMBER OF THE TCB STRUCT. */
        #د_که_پای

        List_توکی_t x_State_List_توکی;                  /*< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
        List_توکی_t x_Event_List_توکی;                  /*< Used to reference a task from an event list. */
        UBaseType_t ux_لومړیتوب;                     /*< The priority of the task.  0 is the lowest priority. */
        ډېری_Type_t * px_ډېری;                      /*< Points to the start of the stack. */
        حرف pcTaskName[ configMAX_TASK_NAME_LEN ]; /*< Descriptive name given to the task when created.  Facilitates debugging only. */ /*lint !e971 Unqualified char types are allowed for strings and single characters only. */

        #إذا ( ( پورټ_ډېری_GROWTH > 0 ) || ( config_ریکارډ_ډېری_لوړ_پته == 1 ) )
            ډېری_Type_t * px_پای_ټکی_د_ډېری; /*< Points to the highest valid address for the stack. */
        #د_که_پای

        #إذا ( پورټ_CRITICAL_NESTING_دننه_TCB == 1 )
            UBaseType_t uxCriticalNesting; /*< Holds the critical section nesting depth for ports that do not maintain their own count in the port layer. */
        #د_که_پای

        #إذا ( configUSE_TRACE_FACILITY == 1 )
            UBaseType_t uxTCBNumber;  /*< Stores a number that increments each time a TCB is created.  It allows debuggers to determine when a task has been deleted and then recreated. */
            UBaseType_t ux_Task_شمېره; /*< Stores a number specifically for use by third party trace code. */
        #د_که_پای

        #إذا ( configUSE_MUTEXES == 1 )
            UBaseType_t ux_بنسټ_لومړیتوب; /*< The priority last assigned to the task - used by the priority inheritance mechanism. */
            UBaseType_t uxMutexesHeld;
        #د_که_پای

        #إذا ( config_USE_APPLICATION_TASK_نښان == 1 )
            TaskHookFunction_t px_Task_نښان;
        #د_که_پای

        #إذا ( config_عدد_THREAD_LOCAL_STORAGE_اشارې > 0 )
            فراغ * pv_Thread_Local_Storage_اشارې[ config_عدد_THREAD_LOCAL_STORAGE_اشارې ];
        #د_که_پای

        #إذا ( config_GENERATE_پرلپسې_وخت_STATS == 1 )
            uint32_t ul_پرلپسې_وخت_Counter; /*< Stores the amount of time the task has spent in the Running state. */
        #د_که_پای

        #إذا ( configUSE_C_RUNTIME_TLS_SUPPORT == 1 )
            config_TLS_بلاک_TYPE xTLSBlock; /*< Memory block used as Thread Local Storage (TLS) Block for the task. */
        #د_که_پای

        #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
            متطاير uint32_t ul_Notified_ارزښت;
            متطاير uint8_t ucNotifyState;
        #د_که_پای

        /* See the comments above the definition of
         * tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE. */
        #إذا ( tsk_STATIC_AND_DYNAMIC_ویش_POSSIBLE != 0 ) /*lint !e731 !e9029 Macro has been consolidated for readability reasons. */
            uint8_t ucStaticallyAllocated;                     /*< Set to pdTRUE if the task is a statically allocated to ensure no attempt is made to free the memory. */
        #د_که_پای

        #إذا ( INCLUDE_xTaskAbortDelay == 1 )
            uint8_t ucDelayAborted;
        #د_که_پای

        #إذا ( configUSE_POSIX_ERRNO == 1 )
            صحيح iTaskErrno;
        #د_که_پای
    } tskTCB;


    فراغ v_پورټ_سېټ_ډېری_Check( TaskHandle_t old,
                             TaskHandle_t new )
    {
        إذا( new != عدم )
        {
            #إذا ARC_FEATURE_SEC_PRESENT
                arc_aux_write( AUX_S_KSTACK_بنسټ, ( uint32_t ) ( new->px_پای_ټکی_د_ډېری ) );
                arc_aux_write( AUX_S_KSTACK_سر, ( uint32_t ) ( new->px_ډېری ) );
            #وإلا
                arc_aux_write( AUX_KSTACK_بنسټ, ( uint32_t ) ( new->px_پای_ټکی_د_ډېری ) );
                arc_aux_write( AUX_KSTACK_سر, ( uint32_t ) ( new->px_ډېری ) );
            #د_که_پای
        }
    }
#د_که_پای /* if ARC_FEATURE_STACK_CHECK */
