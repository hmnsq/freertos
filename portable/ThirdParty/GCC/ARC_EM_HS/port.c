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

#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"
#అన్తర్భావ "FreeRTOSConfig.h"

#అన్తర్భావ "arc/arc_exception.h"
#అన్తర్భావ "arc/arc_timer.h"
#అన్తర్భావ "board.h"

#అన్తర్భావ "arc_freertos_exceptions.h"

అస్థిర గుర్తులేని పూర్ణాంకం ulCriticalNesting = 999UL;
అస్థిర గుర్తులేని పూర్ణాంకం context_switch_reqflg; /* task context switch request flag in exceptions and interrupts handling */

/**
 * \var exc_nest_count
 * \brief the counter for exc/int processing, =0 no int/exc
 * >1 in int/exc processing
 * @}
 */
uint32_t exc_nest_లెక్క;
/* --------------------------------------------------------------------------*/

/**
 * @brief kernel tick interrupt handler of freertos
 */
/* ----------------------------------------------------------------------------*/
స్థిర శూన్య vKernelTick( శూన్య * ptr )
{
    /* clear timer interrupt */
    arc_timer_int_clear( BOARD_OS_TIMER_ID );
    board_timer_update( config_TICK_రేటు_HZ );

    ఒకవేళ( xTaskIncrementTick() )
    {
        పోర్టు_YIELD_FROM_ISR(); /* need to make task switch */
    }
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  setup freertos kernel tick
 */
/* ----------------------------------------------------------------------------*/
స్థిర శూన్య prv_అమరిక_Timer_అంతరాయం( శూన్య )
{
    గుర్తులేని పూర్ణాంకం cyc = configCPU_CLOCK_HZ / config_TICK_రేటు_HZ;

    int_disable( BOARD_OS_TIMER_INTNO ); /* disable os timer interrupt */
    arc_timer_stop( BOARD_OS_TIMER_ID );
    arc_timer_ప్రారంభం( BOARD_OS_TIMER_ID, TIMER_CTRL_IE | TIMER_CTRL_NH, cyc );

    int_handler_install( BOARD_OS_TIMER_INTNO, ( INT_HANDLER_T ) vKernelTick );
    int_pri_సమితి( BOARD_OS_TIMER_INTNO, INT_PRI_MIN );
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
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_శిఖరం_యొక్క_దొంతర--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters; /* R0 */

    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం; /* function body */

    /* PC */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ప్రారంభం_r; /* dispatch return address */

    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_NO_CRITICAL_NESTING;
    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  start the freertos scheduler, go to the first task
 *
 * @returns
 */
/* ----------------------------------------------------------------------------*/
పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    /* Start the timer that generates the tick ISR. */
    prv_అమరిక_Timer_అంతరాయం();
    ప్రారంభం_dispatch();

    /* Should not get here! */
    తిరిగి 0;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  generate a task switch request in ISR
 */
/* ----------------------------------------------------------------------------*/
శూన్య v_పోర్టు_Yield_From_Isr( శూన్య )
{
    గుర్తులేని పూర్ణాంకం status32;

    status32 = cpu_తాళం_save();
    context_switch_reqflg = true;
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
శూన్య v_పోర్టు_Yield( శూన్య )
{
    గుర్తులేని పూర్ణాంకం status32;

    status32 = cpu_తాళం_save();
    dispatch();
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
శూన్య v_పోర్టు_చివర_Task( శూన్య )
{
    #ఒకవేళ ( INCLUDE_vTaskDelete == 1 )
        vTaskDelete( ఖాళీ ); /* Delete task itself */
    #అయితే_ముగింపు

    అయితే( 1 ) /* Yield to other task */
    {
        v_పోర్టు_Yield();
    }
}

#ఒకవేళ ARC_FEATURE_దొంతర_CHECK

/*
 * !!! Note !!!
 * This a trick!!!
 * It's a copy from task.c. We need to know the definition of TCB for the purpose of hardware
 * stack check. Pls don't forget to update it when FreeRTOS is updated.
 */
    రకనిర్వచనం నిర్మాణం tsk_Task_Control_ఖండం       /* The old naming convention is used to prevent breaking kernel aware debuggers. */
    {
        అస్థిర దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర; /*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */

        #ఒకవేళ ( పోర్టు_USING_MPU_WRAPPERS == 1 )
            xMPU_SETTINGS xMPUSettings; /*< The MPU settings are defined as part of the port layer.  THIS MUST BE THE SECOND MEMBER OF THE TCB STRUCT. */
        #అయితే_ముగింపు

        List_అంశం_t x_State_List_అంశం;                  /*< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
        List_అంశం_t x_Event_List_అంశం;                  /*< Used to reference a task from an event list. */
        UBaseType_t ux_ప్రాధాన్యత;                     /*< The priority of the task.  0 is the lowest priority. */
        దొంతర_Type_t * px_దొంతర;                      /*< Points to the start of the stack. */
        అక్షరం pcTaskName[ configMAX_TASK_NAME_LEN ]; /*< Descriptive name given to the task when created.  Facilitates debugging only. */ /*lint !e971 Unqualified char types are allowed for strings and single characters only. */

        #ఒకవేళ ( ( పోర్టు_దొంతర_GROWTH > 0 ) || ( config_రికార్డు_దొంతర_ఎగువ_చిరునామా == 1 ) )
            దొంతర_Type_t * px_చివర_యొక్క_దొంతర; /*< Points to the highest valid address for the stack. */
        #అయితే_ముగింపు

        #ఒకవేళ ( పోర్టు_CRITICAL_NESTING_లోపల_TCB == 1 )
            UBaseType_t uxCriticalNesting; /*< Holds the critical section nesting depth for ports that do not maintain their own count in the port layer. */
        #అయితే_ముగింపు

        #ఒకవేళ ( configUSE_TRACE_FACILITY == 1 )
            UBaseType_t uxTCBNumber;  /*< Stores a number that increments each time a TCB is created.  It allows debuggers to determine when a task has been deleted and then recreated. */
            UBaseType_t ux_Task_సంఖ్య; /*< Stores a number specifically for use by third party trace code. */
        #అయితే_ముగింపు

        #ఒకవేళ ( configUSE_MUTEXES == 1 )
            UBaseType_t ux_పునాది_ప్రాధాన్యత; /*< The priority last assigned to the task - used by the priority inheritance mechanism. */
            UBaseType_t uxMutexesHeld;
        #అయితే_ముగింపు

        #ఒకవేళ ( config_USE_APPLICATION_TASK_ట్యాగ్ == 1 )
            TaskHookFunction_t px_Task_ట్యాగ్;
        #అయితే_ముగింపు

        #ఒకవేళ ( config_అంకె_THREAD_LOCAL_STORAGE_సూచికలు > 0 )
            శూన్య * pv_Thread_Local_Storage_సూచికలు[ config_అంకె_THREAD_LOCAL_STORAGE_సూచికలు ];
        #అయితే_ముగింపు

        #ఒకవేళ ( config_GENERATE_నిరంతరం_సమయం_STATS == 1 )
            uint32_t ul_నిరంతరం_సమయం_Counter; /*< Stores the amount of time the task has spent in the Running state. */
        #అయితే_ముగింపు

        #ఒకవేళ ( configUSE_C_RUNTIME_TLS_SUPPORT == 1 )
            config_TLS_ఖండం_TYPE xTLSBlock; /*< Memory block used as Thread Local Storage (TLS) Block for the task. */
        #అయితే_ముగింపు

        #ఒకవేళ ( configUSE_TASK_NOTIFICATIONS == 1 )
            అస్థిర uint32_t ul_Notified_విలువ;
            అస్థిర uint8_t ucNotifyState;
        #అయితే_ముగింపు

        /* See the comments above the definition of
         * tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE. */
        #ఒకవేళ ( tsk_STATIC_AND_DYNAMIC_కేటాయింపు_POSSIBLE != 0 ) /*lint !e731 !e9029 Macro has been consolidated for readability reasons. */
            uint8_t ucStaticallyAllocated;                     /*< Set to pdTRUE if the task is a statically allocated to ensure no attempt is made to free the memory. */
        #అయితే_ముగింపు

        #ఒకవేళ ( INCLUDE_xTaskAbortDelay == 1 )
            uint8_t ucDelayAborted;
        #అయితే_ముగింపు

        #ఒకవేళ ( configUSE_POSIX_ERRNO == 1 )
            పూర్ణాంకం iTaskErrno;
        #అయితే_ముగింపు
    } tskTCB;


    శూన్య v_పోర్టు_సమితి_దొంతర_Check( TaskHandle_t old,
                             TaskHandle_t new )
    {
        ఒకవేళ( new != ఖాళీ )
        {
            #ఒకవేళ ARC_FEATURE_SEC_PRESENT
                arc_aux_write( AUX_S_KSTACK_పునాది, ( uint32_t ) ( new->px_చివర_యొక్క_దొంతర ) );
                arc_aux_write( AUX_S_KSTACK_శిఖరం, ( uint32_t ) ( new->px_దొంతర ) );
            #లేకపోతే
                arc_aux_write( AUX_KSTACK_పునాది, ( uint32_t ) ( new->px_చివర_యొక్క_దొంతర ) );
                arc_aux_write( AUX_KSTACK_శిఖరం, ( uint32_t ) ( new->px_దొంతర ) );
            #అయితే_ముగింపు
        }
    }
#అయితే_ముగింపు /* if ARC_FEATURE_STACK_CHECK */
