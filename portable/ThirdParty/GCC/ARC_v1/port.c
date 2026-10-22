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

#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"
#ಅನ್ತರ್ಭಾವ "FreeRTOSConfig.h"

#ಅನ್ತರ್ಭಾವ "arc/arc_exception.h"
#ಅನ್ತರ್ಭಾವ "arc/arc_timer.h"
#ಅನ್ತರ್ಭಾವ "board.h"

#ಅನ್ತರ್ಭಾವ "arc_freertos_exceptions.h"

ಚಞ್ಚಲ unsigned ಪೂರ್ಣಾಙ್ಕ ulCriticalNesting = 999UL;
ಚಞ್ಚಲ unsigned ಪೂರ್ಣಾಙ್ಕ context_switch_reqflg; /* task context switch request flag in exceptions and interrupts handling */

/**
 * \var exc_nest_count
 * \brief the counter for exc/int processing, =0 no int/exc
 * >1 in int/exc processing
 * @}
 */
uint32_t exc_nest_ಎಣಿಕೆ;
/* --------------------------------------------------------------------------*/

/**
 * @brief kernel tick interrupt handler of freertos
 */
/* ----------------------------------------------------------------------------*/
ಸ್ಥಿರ ಶೂನ್ಯ vKernelTick( ಶೂನ್ಯ * ptr )
{
    /* clear timer interrupt */
    arc_timer_int_clear( BOARD_OS_TIMER_ID );
    board_timer_update( configTICK_RATE_HZ );

    ಯದಿ( xTaskIncrementTick() )
    {
        portYIELD_FROM_ISR(); /* need to make task switch */
    }
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  setup freertos kernel tick
 */
/* ----------------------------------------------------------------------------*/
ಸ್ಥಿರ ಶೂನ್ಯ prvSetupTimerInterrupt( ಶೂನ್ಯ )
{
    unsigned ಪೂರ್ಣಾಙ್ಕ cyc = configCPU_CLOCK_HZ / configTICK_RATE_HZ;

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
ರಾಶಿ_Type_t * px_Port_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_Of_ರಾಶಿ,
                                     TaskFunction_t pxCode,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_ತುದಿ_Of_ರಾಶಿ--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R0 */

    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pxCode; /* function body */

    /* PC */
    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) start_r; /* dispatch return address */

    px_ತುದಿ_Of_ರಾಶಿ--;
    *px_ತುದಿ_Of_ರಾಶಿ = ( ರಾಶಿ_Type_t ) portNO_CRITICAL_NESTING;
    ಪ್ರತ್ಯಾಗಮ px_ತುದಿ_Of_ರಾಶಿ;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  start the freertos scheduler, go to the first task
 *
 * @returns
 */
/* ----------------------------------------------------------------------------*/
BaseType_t xPortStartScheduler( ಶೂನ್ಯ )
{
    /* Start the timer that generates the tick ISR. */
    prvSetupTimerInterrupt();
    start_dispatch();

    /* Should not get here! */
    ಪ್ರತ್ಯಾಗಮ 0;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
ಶೂನ್ಯ vPortEndScheduler( ಶೂನ್ಯ )
{
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  generate a task switch request in ISR
 */
/* ----------------------------------------------------------------------------*/
ಶೂನ್ಯ vPortYieldFromIsr( ಶೂನ್ಯ )
{
    unsigned ಪೂರ್ಣಾಙ್ಕ status32;

    status32 = cpu_lock_save();
    context_switch_reqflg = true;
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
ಶೂನ್ಯ vPortYield( ಶೂನ್ಯ )
{
    unsigned ಪೂರ್ಣಾಙ್ಕ status32;

    status32 = cpu_lock_save();
    dispatch();
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
ಶೂನ್ಯ vPortEndTask( ಶೂನ್ಯ )
{
    #ಯದಿ ( INCLUDE_vTaskDelete == 1 )
        vTaskDelete( ರಿಕ್ತ ); /* Delete task itself */
    #endif

    ಯಾವತ್( 1 ) /* Yield to other task */
    {
        vPortYield();
    }
}

#ಯದಿ ARC_FEATURE_ರಾಶಿ_CHECK

/*
 * !!! Note !!!
 * This a trick!!!
 * It's a copy from task.c. We need to know the definition of TCB for the purpose of hardware
 * stack check. Pls don't forget to update it when FreeRTOS is updated.
 */
    ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ tskTaskControlBlock       /* The old naming convention is used to prevent breaking kernel aware debuggers. */
    {
        ಚಞ್ಚಲ ರಾಶಿ_Type_t * px_ತುದಿ_Of_ರಾಶಿ; /*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */

        #ಯದಿ ( portUSING_MPU_WRAPPERS == 1 )
            xMPU_SETTINGS xMPUSettings; /*< The MPU settings are defined as part of the port layer.  THIS MUST BE THE SECOND MEMBER OF THE TCB STRUCT. */
        #endif

        ListItem_t xStateListItem;                  /*< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
        ListItem_t xEventListItem;                  /*< Used to reference a task from an event list. */
        UBaseType_t uxPriority;                     /*< The priority of the task.  0 is the lowest priority. */
        ರಾಶಿ_Type_t * px_ರಾಶಿ;                      /*< Points to the start of the stack. */
        ವರ್ಣ pcTaskName[ configMAX_TASK_NAME_LEN ]; /*< Descriptive name given to the task when created.  Facilitates debugging only. */ /*lint !e971 Unqualified char types are allowed for strings and single characters only. */

        #ಯದಿ ( ( port_ರಾಶಿ_GROWTH > 0 ) || ( config_RECORD_ರಾಶಿ_ಮೇಲಿನ_ADDRESS == 1 ) )
            ರಾಶಿ_Type_t * px_End_Of_ರಾಶಿ; /*< Points to the highest valid address for the stack. */
        #endif

        #ಯದಿ ( portCRITICAL_NESTING_IN_TCB == 1 )
            UBaseType_t uxCriticalNesting; /*< Holds the critical section nesting depth for ports that do not maintain their own count in the port layer. */
        #endif

        #ಯದಿ ( configUSE_TRACE_FACILITY == 1 )
            UBaseType_t uxTCBNumber;  /*< Stores a number that increments each time a TCB is created.  It allows debuggers to determine when a task has been deleted and then recreated. */
            UBaseType_t ux_Task_ಸಂಖ್ಯೆ; /*< Stores a number specifically for use by third party trace code. */
        #endif

        #ಯದಿ ( configUSE_MUTEXES == 1 )
            UBaseType_t uxBasePriority; /*< The priority last assigned to the task - used by the priority inheritance mechanism. */
            UBaseType_t uxMutexesHeld;
        #endif

        #ಯದಿ ( configUSE_APPLICATION_TASK_TAG == 1 )
            TaskHookFunction_t pxTaskTag;
        #endif

        #ಯದಿ ( config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_POINTERS > 0 )
            ಶೂನ್ಯ * pvThreadLocalStoragePointers[ config_ಅಂಕೆ_THREAD_LOCAL_STORAGE_POINTERS ];
        #endif

        #ಯದಿ ( configGENERATE_RUN_TIME_STATS == 1 )
            uint32_t ulRunTimeCounter; /*< Stores the amount of time the task has spent in the Running state. */
        #endif

        #ಯದಿ ( configUSE_C_RUNTIME_TLS_SUPPORT == 1 )
            configTLS_BLOCK_TYPE xTLSBlock; /*< Memory block used as Thread Local Storage (TLS) Block for the task. */
        #endif

        #ಯದಿ ( configUSE_TASK_NOTIFICATIONS == 1 )
            ಚಞ್ಚಲ uint32_t ul_Notified_ಮೌಲ್ಯ;
            ಚಞ್ಚಲ uint8_t ucNotifyState;
        #endif

        /* See the comments above the definition of
         * tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE. */
        #ಯದಿ ( tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE != 0 ) /*lint !e731 !e9029 Macro has been consolidated for readability reasons. */
            uint8_t ucStaticallyAllocated;                     /*< Set to pdTRUE if the task is a statically allocated to ensure no attempt is made to free the memory. */
        #endif

        #ಯದಿ ( INCLUDE_xTaskAbortDelay == 1 )
            uint8_t ucDelayAborted;
        #endif

        #ಯದಿ ( configUSE_POSIX_ERRNO == 1 )
            ಪೂರ್ಣಾಙ್ಕ iTaskErrno;
        #endif
    } tskTCB;


    ಶೂನ್ಯ v_Port_Set_ರಾಶಿ_Check( TaskHandle_t old,
                             TaskHandle_t new )
    {
        ಯದಿ( new != ರಿಕ್ತ )
        {
            arc_aux_write( AUX_USTACK_BASE, ( uint32_t ) ( new->px_End_Of_ರಾಶಿ ) );
            arc_aux_write( AUX_USTACK_ತುದಿ, ( uint32_t ) ( new->px_ರಾಶಿ ) );
        }
    }
#endif /* if ARC_FEATURE_STACK_CHECK */
