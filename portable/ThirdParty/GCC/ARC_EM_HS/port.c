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

#समावेश "FreeRTOS.h"
#समावेश "task.h"
#समावेश "FreeRTOSConfig.h"

#समावेश "arc/arc_exception.h"
#समावेश "arc/arc_timer.h"
#समावेश "board.h"

#समावेश "arc_freertos_exceptions.h"

अस्थिर अचिन्हित पूर्णांक ulCriticalNesting = 999UL;
अस्थिर अचिन्हित पूर्णांक context_switch_reqflg; /* task context switch request flag in exceptions and interrupts handling */

/**
 * \var exc_nest_count
 * \brief the counter for exc/int processing, =0 no int/exc
 * >1 in int/exc processing
 * @}
 */
uint32_t exc_nest_गिनती;
/* --------------------------------------------------------------------------*/

/**
 * @brief kernel tick interrupt handler of freertos
 */
/* ----------------------------------------------------------------------------*/
अटल व्योम vKernelTick( व्योम * ptr )
{
    /* clear timer interrupt */
    arc_timer_int_clear( BOARD_OS_TIMER_ID );
    board_timer_update( configTICK_RATE_HZ );

    अगर( xTaskIncrementTick() )
    {
        portYIELD_FROM_ISR(); /* need to make task switch */
    }
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  setup freertos kernel tick
 */
/* ----------------------------------------------------------------------------*/
अटल व्योम prvSetupTimerInterrupt( व्योम )
{
    अचिन्हित पूर्णांक cyc = configCPU_CLOCK_HZ / configTICK_RATE_HZ;

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
ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     व्योम * pvParameters )
{
    /* To ensure asserts in tasks.c don't fail, although in this case the assert
     * is not really required. */
    px_शीर्ष_Of_ढेर--;

    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* When the task starts is will expect to find the function parameter in
     * R0. */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pvParameters; /* R0 */

    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pxCode; /* function body */

    /* PC */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) start_r; /* dispatch return address */

    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) portNO_CRITICAL_NESTING;
    वापस px_शीर्ष_Of_ढेर;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  start the freertos scheduler, go to the first task
 *
 * @returns
 */
/* ----------------------------------------------------------------------------*/
BaseType_t xPortStartScheduler( व्योम )
{
    /* Start the timer that generates the tick ISR. */
    prvSetupTimerInterrupt();
    start_dispatch();

    /* Should not get here! */
    वापस 0;
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
व्योम vPortEndScheduler( व्योम )
{
}

/* --------------------------------------------------------------------------*/

/**
 * @brief  generate a task switch request in ISR
 */
/* ----------------------------------------------------------------------------*/
व्योम vPortYieldFromIsr( व्योम )
{
    अचिन्हित पूर्णांक status32;

    status32 = cpu_lock_save();
    context_switch_reqflg = true;
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
व्योम vPortYield( व्योम )
{
    अचिन्हित पूर्णांक status32;

    status32 = cpu_lock_save();
    dispatch();
    cpu_unlock_restore( status32 );
}

/* --------------------------------------------------------------------------*/

/**
 * @brief
 */
/* ----------------------------------------------------------------------------*/
व्योम vPortEndTask( व्योम )
{
    #अगर ( INCLUDE_vTaskDelete == 1 )
        vTaskDelete( शून्य ); /* Delete task itself */
    #पूर्ण_अगर

    जबतक( 1 ) /* Yield to other task */
    {
        vPortYield();
    }
}

#अगर ARC_FEATURE_ढेर_CHECK

/*
 * !!! Note !!!
 * This a trick!!!
 * It's a copy from task.c. We need to know the definition of TCB for the purpose of hardware
 * stack check. Pls don't forget to update it when FreeRTOS is updated.
 */
    प्रकार काष्ठा tskTaskControlBlock       /* The old naming convention is used to prevent breaking kernel aware debuggers. */
    {
        अस्थिर ढेर_Type_t * px_शीर्ष_Of_ढेर; /*< Points to the location of the last item placed on the tasks stack.  THIS MUST BE THE FIRST MEMBER OF THE TCB STRUCT. */

        #अगर ( portUSING_MPU_WRAPPERS == 1 )
            xMPU_SETTINGS xMPUSettings; /*< The MPU settings are defined as part of the port layer.  THIS MUST BE THE SECOND MEMBER OF THE TCB STRUCT. */
        #पूर्ण_अगर

        ListItem_t xStateListItem;                  /*< The list that the state list item of a task is reference from denotes the state of that task (Ready, Blocked, Suspended ). */
        ListItem_t xEventListItem;                  /*< Used to reference a task from an event list. */
        UBaseType_t uxPriority;                     /*< The priority of the task.  0 is the lowest priority. */
        ढेर_Type_t * px_ढेर;                      /*< Points to the start of the stack. */
        अक्षर pcTaskName[ configMAX_TASK_NAME_LEN ]; /*< Descriptive name given to the task when created.  Facilitates debugging only. */ /*lint !e971 Unqualified char types are allowed for strings and single characters only. */

        #अगर ( ( port_ढेर_GROWTH > 0 ) || ( config_RECORD_ढेर_ऊपरी_ADDRESS == 1 ) )
            ढेर_Type_t * px_End_Of_ढेर; /*< Points to the highest valid address for the stack. */
        #पूर्ण_अगर

        #अगर ( portCRITICAL_NESTING_IN_TCB == 1 )
            UBaseType_t uxCriticalNesting; /*< Holds the critical section nesting depth for ports that do not maintain their own count in the port layer. */
        #पूर्ण_अगर

        #अगर ( configUSE_TRACE_FACILITY == 1 )
            UBaseType_t uxTCBNumber;  /*< Stores a number that increments each time a TCB is created.  It allows debuggers to determine when a task has been deleted and then recreated. */
            UBaseType_t ux_Task_संख्या; /*< Stores a number specifically for use by third party trace code. */
        #पूर्ण_अगर

        #अगर ( configUSE_MUTEXES == 1 )
            UBaseType_t uxBasePriority; /*< The priority last assigned to the task - used by the priority inheritance mechanism. */
            UBaseType_t uxMutexesHeld;
        #पूर्ण_अगर

        #अगर ( configUSE_APPLICATION_TASK_TAG == 1 )
            TaskHookFunction_t pxTaskTag;
        #पूर्ण_अगर

        #अगर ( config_अंक_THREAD_LOCAL_STORAGE_POINTERS > 0 )
            व्योम * pvThreadLocalStoragePointers[ config_अंक_THREAD_LOCAL_STORAGE_POINTERS ];
        #पूर्ण_अगर

        #अगर ( configGENERATE_RUN_TIME_STATS == 1 )
            uint32_t ul_Run_Time_गणक; /*< Stores the amount of time the task has spent in the Running state. */
        #पूर्ण_अगर

        #अगर ( configUSE_C_RUNTIME_TLS_SUPPORT == 1 )
            configTLS_BLOCK_TYPE xTLSBlock; /*< Memory block used as Thread Local Storage (TLS) Block for the task. */
        #पूर्ण_अगर

        #अगर ( configUSE_TASK_NOTIFICATIONS == 1 )
            अस्थिर uint32_t ul_Notified_मूल्य;
            अस्थिर uint8_t ucNotifyState;
        #पूर्ण_अगर

        /* See the comments above the definition of
         * tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE. */
        #अगर ( tskSTATIC_AND_DYNAMIC_ALLOCATION_POSSIBLE != 0 ) /*lint !e731 !e9029 Macro has been consolidated for readability reasons. */
            uint8_t ucStaticallyAllocated;                     /*< Set to pdTRUE if the task is a statically allocated to ensure no attempt is made to free the memory. */
        #पूर्ण_अगर

        #अगर ( INCLUDE_xTaskAbortDelay == 1 )
            uint8_t ucDelayAborted;
        #पूर्ण_अगर

        #अगर ( configUSE_POSIX_ERRNO == 1 )
            पूर्णांक iTaskErrno;
        #पूर्ण_अगर
    } tskTCB;


    व्योम v_Port_Set_ढेर_Check( TaskHandle_t old,
                             TaskHandle_t new )
    {
        अगर( new != शून्य )
        {
            #अगर ARC_FEATURE_SEC_PRESENT
                arc_aux_write( AUX_S_KSTACK_BASE, ( uint32_t ) ( new->px_End_Of_ढेर ) );
                arc_aux_write( AUX_S_KSTACK_शीर्ष, ( uint32_t ) ( new->px_ढेर ) );
            #अन्यथा
                arc_aux_write( AUX_KSTACK_BASE, ( uint32_t ) ( new->px_End_Of_ढेर ) );
                arc_aux_write( AUX_KSTACK_शीर्ष, ( uint32_t ) ( new->px_ढेर ) );
            #पूर्ण_अगर
        }
    }
#पूर्ण_अगर /* if ARC_FEATURE_STACK_CHECK */
