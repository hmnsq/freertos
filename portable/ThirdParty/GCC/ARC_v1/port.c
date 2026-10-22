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

#அந்தர்பாவ "FreeRTOS.h"
#அந்தர்பாவ "task.h"
#அந்தர்பாவ "FreeRTOSConfig.h"

#அந்தர்பாவ "arc/arc_exception.h"
#அந்தர்பாவ "arc/arc_timer.h"
#அந்தர்பாவ "board.h"

#அந்தர்பாவ "arc_freertos_exceptions.h"

நிலையற்ற unsigned முழு ulCriticalNesting = 999UL;
நிலையற்ற unsigned முழு context_switch_reqflg; /* task context switch request flag in exceptions and interrupts handling */

/**
 * \var exc_nest_count
 * \brief the counter for exc/int processing, =0 no int/exc
 * >1 in int/exc processing
 * @}
 */
uint32_t exc_nest_மொத்தம்;
/* --------------------------------------------------------------------------*/

/**
 * @brief kernel tick interrupt handler of freertos
 */
/* ----------------------------------------------------------------------------*/
நிலையான வெறுமை vKernelTick( வெறுமை * ptr )
{
    /* clear timer interrupt */
    arc_timer_int_clear( BOARD_OS_TIMER_ID );
    board_timer_update( configTICK_RATE_HZ );

    எனில்( xTaskIncrementTick() )
    {
        portYIELD_FROM_ISR(); /* need to make task switch */
    }
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  setup freertos kernel tick
 */
/* ----------------------------------------------------------------------------*/
நிலையான வெறுமை prvSetupTimerInterrupt( வெறுமை )
{
    unsigned முழு cyc = configCPU_CLOCK_HZ / configTICK_RATE_HZ;

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
அடுக்கு_Type_t * px_Port_Initialise_அடுக்கு( அடுக்கு_Type_t * px_உச்சி_Of_அடுக்கு,
                                     TaskFunction_t pxCode,
                                     வெறுமை * pvParameters )
{
    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_உச்சி_Of_அடுக்கு--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) pvParameters; /* R0 */

    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) pxCode; /* function body */

    /* PC */
    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) start_r; /* dispatch return address */

    px_உச்சி_Of_அடுக்கு--;
    *px_உச்சி_Of_அடுக்கு = ( அடுக்கு_Type_t ) portNO_CRITICAL_NESTING;
    திரும்பு px_உச்சி_Of_அடுக்கு;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  start the freertos scheduler, go to the first task
 *
 * @returns
 */
/* ----------------------------------------------------------------------------*/
BaseType_t xPortStartScheduler( வெறுமை )
{
    /* Start the timer that generates the tick ISR. */
    prvSetupTimerInterrupt();
    start_dispatch();

    /* Should not get here! */
    திரும்பு 0;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
வெறுமை vPortEndScheduler( வெறுமை )
{
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  generate a task switch request in ISR
 */
/* ----------------------------------------------------------------------------*/
வெறுமை vPortYieldFromIsr( வெறுமை )
{
    unsigned முழு status32;

    status32 = cpu_lock_save();
    context_switch_reqflg = true;
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
வெறுமை vPortYield( வெறுமை )
{
    unsigned முழு status32;

    status32 = cpu_lock_save();
    dispatch();
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
வெறுமை vPortEndTask( வெறுமை )
{
    #எனில் ( INCLUDE_vTaskDelete == 1 )
        vTaskDelete( வெற்று ); /* Delete task itself */
    #endif

    போது( 1 ) /* Yield to other task */
    {
        vPortYield();
    }
}

#எனில் ARC_FEATURE_அடுக்கு_CHECK

/*
 * !!! Note !!!
 * This a trick!!!
 * It's a copy from task.c. We need to know the definition of TCB for the purpose of hardware
 * stack check. Pls don't forget to update it when FreeRTOS is updated.
 */
    வகைவரை கட்டமைப்பு tskTaskControlBlock       /* The old naming convention is used to prevent breaking kernel aware debuggers. */
    {
        நிலையற்ற அடுக்கு_Type_t * px_உச்சி_Of_அடுக்கு; /*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */

        #எனில் ( portUSING_MPU_WRAPPERS == 1 )
            xMPU_SETTINGS xMPUSettings; /*< The MPU settings are defined as part of the port layer.  THIS MUST BE THE SECOND MEMBER OF THE TCB STRUCT. */
        #endif

        ListItem_t xStateListItem;                  /*< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
        ListItem_t xEventListItem;                  /*< Used to reference a task from an event list. */
        UBaseType_t uxPriority;                     /*< The priority of the task.  0 is the lowest priority. */
        அடுக்கு_Type_t * px_அடுக்கு;                      /*< Points to the start of the stack. */
        எழுத்து pcTaskName[ configMAX_TASK_NAME_LEN ]; /*< Descriptive name given to the task when created.  Facilitates debugging only. */ /*lint !e971 Unqualified char types are allowed for strings and single characters only. */

        #எனில் ( ( port_அடுக்கு_GROWTH > 0 ) || ( config_RECORD_அடுக்கு_உயர்வு_ADDRESS == 1 ) )
            அடுக்கு_Type_t * px_End_Of_அடுக்கு; /*< Points to the highest valid address for the stack. */
        #endif

        #எனில் ( portCRITICAL_NESTING_IN_TCB == 1 )
            UBaseType_t uxCriticalNesting; /*< Holds the critical section nesting depth for ports that do not maintain their own count in the port layer. */
        #endif

        #எனில் ( configUSE_TRACE_FACILITY == 1 )
            UBaseType_t uxTCBNumber;  /*< Stores a number that increments each time a TCB is created.  It allows debuggers to determine when a task has been deleted and then recreated. */
            UBaseType_t ux_Task_எண்; /*< Stores a number specifically for use by third party trace code. */
        #endif

        #எனில் ( configUSE_MUTEXES == 1 )
            UBaseType_t uxBasePriority; /*< The priority last assigned to the task - used by the priority inheritance mechanism. */
            UBaseType_t uxMutexesHeld;
        #endif

        #எனில் ( configUSE_APPLICATION_TASK_TAG == 1 )
            TaskHookFunction_t pxTaskTag;
        #endif

        #எனில் ( config_இலக்கம்_THREAD_LOCAL_STORAGE_POINTERS > 0 )
            வெறுமை * pvThreadLocalStoragePointers[ config_இலக்கம்_THREAD_LOCAL_STORAGE_POINTERS ];
        #endif

        #எனில் ( configGENERATE_RUN_TIME_STATS == 1 )
            uint32_t ulRunTimeCounter; /*< Stores the amount of time the task has spent in the Running state. */
        #endif

        #எனில் ( configUSE_C_RUNTIME_TLS_SUPPORT == 1 )
            configTLS_BLOCK_TYPE xTLSBlock; /*< Memory block used as Thread Local Storage (TLS) Block for the task. */
        #endif

        #எனில் ( configUSE_TASK_NOTIFICATIONS == 1 )
            நிலையற்ற uint32_t ul_Notified_மதிப்பு;
            நிலையற்ற uint8_t ucNotifyState;
        #endif

        /* See the comments above the definition of
         * tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE. */
        #எனில் ( tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE != 0 ) /*lint !e731 !e9029 Macro has been consolidated for readability reasons. */
            uint8_t ucStaticallyAllocated;                     /*< Set to pdTRUE if the task is a statically allocated to ensure no attempt is made to free the memory. */
        #endif

        #எனில் ( INCLUDE_xTaskAbortDelay == 1 )
            uint8_t ucDelayAborted;
        #endif

        #எனில் ( configUSE_POSIX_ERRNO == 1 )
            முழு iTaskErrno;
        #endif
    } tskTCB;


    வெறுமை v_Port_Set_அடுக்கு_Check( TaskHandle_t old,
                             TaskHandle_t new )
    {
        எனில்( new != வெற்று )
        {
            arc_aux_write( AUX_USTACK_BASE, ( uint32_t ) ( new->px_End_Of_அடுக்கு ) );
            arc_aux_write( AUX_USTACK_உச்சி, ( uint32_t ) ( new->px_அடுக்கு ) );
        }
    }
#endif /* if ARC_FEATURE_STACK_CHECK */
