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

متطاير unsigned صحيح ulCriticalNesting = 999UL;
متطاير unsigned صحيح context_switch_reqflg; /* task context switch request flag in exceptions and interrupts handling */

/**
 * \var exc_nest_count
 * \brief the counter for exc/int processing, =0 no int/exc
 * >1 in int/exc processing
 * @}
 */
uint32_t exc_nest_سانى;
/* --------------------------------------------------------------------------*/

/**
 * @brief kernel tick interrupt handler of freertos
 */
/* ----------------------------------------------------------------------------*/
ساكن فراغ vKernelTick( فراغ * ptr )
{
    /* clear timer interrupt */
    arc_timer_int_clear( BOARD_OS_TIMER_ID );
    board_timer_update( configTICK_RATE_HZ );

    إذا( xTaskIncrementTick() )
    {
        portYIELD_FROM_ISR(); /* need to make task switch */
    }
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  setup freertos kernel tick
 */
/* ----------------------------------------------------------------------------*/
ساكن فراغ prvSetupTimerInterrupt( فراغ )
{
    unsigned صحيح cyc = configCPU_CLOCK_HZ / configTICK_RATE_HZ;

    int_disable( BOARD_OS_TIMER_INTNO ); /* disable os timer interrupt */
    arc_timer_stop( BOARD_OS_TIMER_ID );
    arc_timer_start( BOARD_OS_TIMER_ID, TIMER_CTRL_IE | TIMER_CTRL_NH, cyc );

    int_handler_install( BOARD_OS_TIMER_INTNO, ( INT_HANDLER_T ) vKernelTick );
    int_pri_set( BOARD_OS_TIMER_INTNO, INT_PRI_MIN );
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
دۆۋە_Type_t * px_Port_Initialise_دۆۋە( دۆۋە_Type_t * px_چوققا_Of_دۆۋە,
                                     TaskFunction_t pxCode,
                                     فراغ * pvParameters )
{
    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_چوققا_Of_دۆۋە--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_چوققا_Of_دۆۋە = ( دۆۋە_Type_t ) pvParameters; /* R0 */

    px_چوققا_Of_دۆۋە--;
    *px_چوققا_Of_دۆۋە = ( دۆۋە_Type_t ) pxCode; /* function body */

    /* PC */
    px_چوققا_Of_دۆۋە--;
    *px_چوققا_Of_دۆۋە = ( دۆۋە_Type_t ) start_r; /* dispatch return address */

    px_چوققا_Of_دۆۋە--;
    *px_چوققا_Of_دۆۋە = ( دۆۋە_Type_t ) portNO_CRITICAL_NESTING;
    أرجع px_چوققا_Of_دۆۋە;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  start the freertos scheduler, go to the first task
 *
 * @returns
 */
/* ----------------------------------------------------------------------------*/
BaseType_t xPortStartScheduler( فراغ )
{
    /* Start the timer that generates the tick ISR. */
    prvSetupTimerInterrupt();
    start_dispatch();

    /* Should not get here! */
    أرجع 0;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
فراغ vPortEndScheduler( فراغ )
{
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  generate a task switch request in ISR
 */
/* ----------------------------------------------------------------------------*/
فراغ vPortYieldFromIsr( فراغ )
{
    unsigned صحيح status32;

    status32 = cpu_lock_save();
    context_switch_reqflg = true;
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
فراغ vPortYield( فراغ )
{
    unsigned صحيح status32;

    status32 = cpu_lock_save();
    dispatch();
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
فراغ vPortEndTask( فراغ )
{
    #إذا ( INCLUDE_vTaskDelete == 1 )
        vTaskDelete( عدم ); /* Delete task itself */
    #endif

    طالما( 1 ) /* Yield to other task */
    {
        vPortYield();
    }
}

#إذا ARC_FEATURE_دۆۋە_CHECK

/*
 * !!! Note !!!
 * This a trick!!!
 * It's a copy from task.c. We need to know the definition of TCB for the purpose of hardware
 * stack check. Pls don't forget to update it when FreeRTOS is updated.
 */
    تعريفنوع بنية tskTaskControlBlock       /* The old naming convention is used to prevent breaking kernel aware debuggers. */
    {
        متطاير دۆۋە_Type_t * px_چوققا_Of_دۆۋە; /*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */

        #إذا ( portUSING_MPU_WRAPPERS == 1 )
            xMPU_SETTINGS xMPUSettings; /*< The MPU settings are defined as part of the port layer.  THIS MUST BE THE SECOND MEMBER OF THE TCB STRUCT. */
        #endif

        ListItem_t xStateListItem;                  /*< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
        ListItem_t xEventListItem;                  /*< Used to reference a task from an event list. */
        UBaseType_t uxPriority;                     /*< The priority of the task.  0 is the lowest priority. */
        دۆۋە_Type_t * px_دۆۋە;                      /*< Points to the start of the stack. */
        حرف pcTaskName[ configMAX_TASK_NAME_LEN ]; /*< Descriptive name given to the task when created.  Facilitates debugging only. */ /*lint !e971 Unqualified char types are allowed for strings and single characters only. */

        #إذا ( ( port_دۆۋە_GROWTH > 0 ) || ( config_RECORD_دۆۋە_يۇقىرى_ADDRESS == 1 ) )
            دۆۋە_Type_t * px_End_Of_دۆۋە; /*< Points to the highest valid address for the stack. */
        #endif

        #إذا ( portCRITICAL_NESTING_IN_TCB == 1 )
            UBaseType_t uxCriticalNesting; /*< Holds the critical section nesting depth for ports that do not maintain their own count in the port layer. */
        #endif

        #إذا ( configUSE_TRACE_FACILITY == 1 )
            UBaseType_t uxTCBNumber;  /*< Stores a number that increments each time a TCB is created.  It allows debuggers to determine when a task has been deleted and then recreated. */
            UBaseType_t ux_Task_سان; /*< Stores a number specifically for use by third party trace code. */
        #endif

        #إذا ( configUSE_MUTEXES == 1 )
            UBaseType_t uxBasePriority; /*< The priority last assigned to the task - used by the priority inheritance mechanism. */
            UBaseType_t uxMutexesHeld;
        #endif

        #إذا ( configUSE_APPLICATION_TASK_TAG == 1 )
            TaskHookFunction_t pxTaskTag;
        #endif

        #إذا ( config_رەقەم_THREAD_LOCAL_STORAGE_POINTERS > 0 )
            فراغ * pvThreadLocalStoragePointers[ config_رەقەم_THREAD_LOCAL_STORAGE_POINTERS ];
        #endif

        #إذا ( configGENERATE_RUN_TIME_STATS == 1 )
            uint32_t ulRunTimeCounter; /*< Stores the amount of time the task has spent in the Running state. */
        #endif

        #إذا ( configUSE_C_RUNTIME_TLS_SUPPORT == 1 )
            configTLS_BLOCK_TYPE xTLSBlock; /*< Memory block used as Thread Local Storage (TLS) Block for the task. */
        #endif

        #إذا ( configUSE_TASK_NOTIFICATIONS == 1 )
            متطاير uint32_t ul_Notified_قىممەت;
            متطاير uint8_t ucNotifyState;
        #endif

        /* See the comments above the definition of
         * tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE. */
        #إذا ( tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE != 0 ) /*lint !e731 !e9029 Macro has been consolidated for readability reasons. */
            uint8_t ucStaticallyAllocated;                     /*< Set to pdTRUE if the task is a statically allocated to ensure no attempt is made to free the memory. */
        #endif

        #إذا ( INCLUDE_xTaskAbortDelay == 1 )
            uint8_t ucDelayAborted;
        #endif

        #إذا ( configUSE_POSIX_ERRNO == 1 )
            صحيح iTaskErrno;
        #endif
    } tskTCB;


    فراغ v_Port_Set_دۆۋە_Check( TaskHandle_t old,
                             TaskHandle_t new )
    {
        إذا( new != عدم )
        {
            #إذا ARC_FEATURE_SEC_PRESENT
                arc_aux_write( AUX_S_KSTACK_BASE, ( uint32_t ) ( new->px_End_Of_دۆۋە ) );
                arc_aux_write( AUX_S_KSTACK_چوققا, ( uint32_t ) ( new->px_دۆۋە ) );
            #وإلا
                arc_aux_write( AUX_KSTACK_BASE, ( uint32_t ) ( new->px_End_Of_دۆۋە ) );
                arc_aux_write( AUX_KSTACK_چوققا, ( uint32_t ) ( new->px_دۆۋە ) );
            #endif
        }
    }
#endif /* if ARC_FEATURE_STACK_CHECK */
