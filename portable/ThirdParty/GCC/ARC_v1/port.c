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

متطاير بیعلامت صحيح ulCriticalNesting = 999UL;
متطاير بیعلامت صحيح context_switch_reqflg; /* task context switch request flag in exceptions and interrupts handling */

/**
 * \var exc_nest_count
 * \brief the counter for exc/int processing, =0 no int/exc
 * >1 in int/exc processing
 * @}
 */
uint32_t exc_nest_شمار;
/* --------------------------------------------------------------------------*/

/**
 * @brief kernel tick interrupt handler of freertos
 */
/* ----------------------------------------------------------------------------*/
ساكن فراغ vKernelTick( فراغ * ptr )
{
    /* clear timer interrupt */
    arc_timer_int_clear( BOARD_OS_TIMER_ID );
    board_timer_update( config_TICK_نرخ_HZ );

    إذا( xTaskIncrementTick() )
    {
        پورت_YIELD_FROM_ISR(); /* need to make task switch */
    }
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  setup freertos kernel tick
 */
/* ----------------------------------------------------------------------------*/
ساكن فراغ prv_راهاندازی_Timer_وقفه( فراغ )
{
    بیعلامت صحيح cyc = configCPU_CLOCK_HZ / config_TICK_نرخ_HZ;

    int_disable( BOARD_OS_TIMER_INTNO ); /* disable os timer interrupt */
    arc_timer_stop( BOARD_OS_TIMER_ID );
    arc_timer_شروع( BOARD_OS_TIMER_ID, TIMER_CTRL_IE | TIMER_CTRL_NH, cyc );

    int_handler_install( BOARD_OS_TIMER_INTNO, ( INT_HANDLER_T ) vKernelTick );
    int_pri_مجموعه( BOARD_OS_TIMER_INTNO, INT_PRI_MIN );
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
پشته_Type_t * px_پورت_Initialise_پشته( پشته_Type_t * px_بالاترین_از_پشته,
                                     TaskFunction_t px_کد,
                                     فراغ * pvParameters )
{
    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_بالاترین_از_پشته--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_بالاترین_از_پشته = ( پشته_Type_t ) pvParameters; /* R0 */

    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) px_کد; /* function body */

    /* PC */
    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) شروع_r; /* dispatch return address */

    px_بالاترین_از_پشته--;
    *px_بالاترین_از_پشته = ( پشته_Type_t ) پورت_NO_CRITICAL_NESTING;
    أرجع px_بالاترین_از_پشته;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  start the freertos scheduler, go to the first task
 *
 * @returns
 */
/* ----------------------------------------------------------------------------*/
پایه_Type_t x_پورت_شروع_Scheduler( فراغ )
{
    /* Start the timer that generates the tick ISR. */
    prv_راهاندازی_Timer_وقفه();
    شروع_dispatch();

    /* Should not get here! */
    أرجع 0;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
فراغ v_پورت_انتها_Scheduler( فراغ )
{
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  generate a task switch request in ISR
 */
/* ----------------------------------------------------------------------------*/
فراغ v_پورت_Yield_From_Isr( فراغ )
{
    بیعلامت صحيح status32;

    status32 = cpu_قفل_save();
    context_switch_reqflg = true;
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
فراغ v_پورت_Yield( فراغ )
{
    بیعلامت صحيح status32;

    status32 = cpu_قفل_save();
    dispatch();
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
فراغ v_پورت_انتها_Task( فراغ )
{
    #إذا ( INCLUDE_vTaskDelete == 1 )
        vTaskDelete( عدم ); /* Delete task itself */
    #پایان_اگر

    طالما( 1 ) /* Yield to other task */
    {
        v_پورت_Yield();
    }
}

#إذا ARC_FEATURE_پشته_CHECK

/*
 * !!! Note !!!
 * This a trick!!!
 * It's a copy from task.c. We need to know the definition of TCB for the purpose of hardware
 * stack check. Pls don't forget to update it when FreeRTOS is updated.
 */
    تعريفنوع بنية tsk_Task_Control_بلوک       /* The old naming convention is used to prevent breaking kernel aware debuggers. */
    {
        متطاير پشته_Type_t * px_بالاترین_از_پشته; /*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */

        #إذا ( پورت_USING_MPU_WRAPPERS == 1 )
            xMPU_SETTINGS xMPUSettings; /*< The MPU settings are defined as part of the port layer.  THIS MUST BE THE SECOND MEMBER OF THE TCB STRUCT. */
        #پایان_اگر

        List_قلم_t x_State_List_قلم;                  /*< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
        List_قلم_t x_Event_List_قلم;                  /*< Used to reference a task from an event list. */
        UBaseType_t ux_اولویت;                     /*< The priority of the task.  0 is the lowest priority. */
        پشته_Type_t * px_پشته;                      /*< Points to the start of the stack. */
        حرف pcTaskName[ configMAX_TASK_NAME_LEN ]; /*< Descriptive name given to the task when created.  Facilitates debugging only. */ /*lint !e971 Unqualified char types are allowed for strings and single characters only. */

        #إذا ( ( پورت_پشته_GROWTH > 0 ) || ( config_رکورد_پشته_بالا_آدرس == 1 ) )
            پشته_Type_t * px_انتها_از_پشته; /*< Points to the highest valid address for the stack. */
        #پایان_اگر

        #إذا ( پورت_CRITICAL_NESTING_درون_TCB == 1 )
            UBaseType_t uxCriticalNesting; /*< Holds the critical section nesting depth for ports that do not maintain their own count in the port layer. */
        #پایان_اگر

        #إذا ( configUSE_TRACE_FACILITY == 1 )
            UBaseType_t uxTCBNumber;  /*< Stores a number that increments each time a TCB is created.  It allows debuggers to determine when a task has been deleted and then recreated. */
            UBaseType_t ux_Task_عدد; /*< Stores a number specifically for use by third party trace code. */
        #پایان_اگر

        #إذا ( configUSE_MUTEXES == 1 )
            UBaseType_t ux_پایه_اولویت; /*< The priority last assigned to the task - used by the priority inheritance mechanism. */
            UBaseType_t uxMutexesHeld;
        #پایان_اگر

        #إذا ( config_USE_APPLICATION_TASK_برچسب == 1 )
            TaskHookFunction_t px_Task_برچسب;
        #پایان_اگر

        #إذا ( config_رقم_THREAD_LOCAL_STORAGE_اشارهگرها > 0 )
            فراغ * pv_Thread_Local_Storage_اشارهگرها[ config_رقم_THREAD_LOCAL_STORAGE_اشارهگرها ];
        #پایان_اگر

        #إذا ( config_GENERATE_پیاپی_زمان_STATS == 1 )
            uint32_t ul_پیاپی_زمان_Counter; /*< Stores the amount of time the task has spent in the Running state. */
        #پایان_اگر

        #إذا ( configUSE_C_RUNTIME_TLS_SUPPORT == 1 )
            config_TLS_بلوک_TYPE xTLSBlock; /*< Memory block used as Thread Local Storage (TLS) Block for the task. */
        #پایان_اگر

        #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
            متطاير uint32_t ul_Notified_مقدار;
            متطاير uint8_t ucNotifyState;
        #پایان_اگر

        /* See the comments above the definition of
         * tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE. */
        #إذا ( tsk_STATIC_AND_DYNAMIC_تخصیص_POSSIBLE != 0 ) /*lint !e731 !e9029 Macro has been consolidated for readability reasons. */
            uint8_t ucStaticallyAllocated;                     /*< Set to pdTRUE if the task is a statically allocated to ensure no attempt is made to free the memory. */
        #پایان_اگر

        #إذا ( INCLUDE_xTaskAbortDelay == 1 )
            uint8_t ucDelayAborted;
        #پایان_اگر

        #إذا ( configUSE_POSIX_ERRNO == 1 )
            صحيح iTaskErrno;
        #پایان_اگر
    } tskTCB;


    فراغ v_پورت_مجموعه_پشته_Check( TaskHandle_t old,
                             TaskHandle_t new )
    {
        إذا( new != عدم )
        {
            arc_aux_write( AUX_USTACK_پایه, ( uint32_t ) ( new->px_انتها_از_پشته ) );
            arc_aux_write( AUX_USTACK_بالاترین, ( uint32_t ) ( new->px_پشته ) );
        }
    }
#پایان_اگر /* if ARC_FEATURE_STACK_CHECK */
