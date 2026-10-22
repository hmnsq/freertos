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
#समावेश <stdlib.h>
#समावेश <string.h>

/* Scheduler includes. */
#समावेश "FreeRTOS.h"
#समावेश "task.h"

#अगर configUSE_PORT_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #अगर ( configMAX_PRIORITIES > 32 )
        #त्रुटि configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a प्रणाली requires more than 10 to 15 difference priorities as tasks that share a priority will समय slice.
    #पूर्ण_अगर
#पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

#अगर_अघोषित configSETUP_TICK_INTERRUPT
    #त्रुटि configSETUP_TICK_INTERRUPT() must be defined in FreeRTOSConfig.h to call the function that sets up the tick interrupt.
#पूर्ण_अगर

#अगर_अघोषित configCLEAR_TICK_INTERRUPT
    #त्रुटि configCLEAR_TICK_INTERRUPT must be defined in FreeRTOSConfig.h to clear which ever interrupt was used to generate the tick interrupt.
#पूर्ण_अगर

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#घोषणा portNO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#घोषणा portNO_FLOATING_POINT_CONTEXT    ( ( ढेर_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#अगर_घोषित __ARMEB__
    #घोषणा portINITIAL_SPSR             ( ( ढेर_Type_t ) 0x21f ) /* System mode, ARM mode, IRQ enabled FIQ enabled, Big-endian. */
#अन्यथा
    #घोषणा portINITIAL_SPSR             ( ( ढेर_Type_t ) 0x01f ) /* System mode, ARM mode, IRQ enabled FIQ enabled, Little-endian. */
#पूर्ण_अगर
#घोषणा portTHUMB_MODE_BIT               ( ( ढेर_Type_t ) 0x20 )
#घोषणा portTHUMB_MODE_ADDRESS           ( 0x01UL )

/* Masks all bits in the APSR other than the mode bits. */
#घोषणा portAPSR_MODE_BITS_MASK          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#घोषणा portAPSR_USER_MODE               ( 0x10 )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#अगर_घोषित configTASK_RETURN_ADDRESS
    #घोषणा portTASK_RETURN_ADDRESS    configTASK_RETURN_ADDRESS
#अन्यथा
    #घोषणा portTASK_RETURN_ADDRESS    prvTaskExitError
#पूर्ण_अगर

/* The space on the stack required to hold the FPU registers. */
#अगर ( configFPU_D32 == 1 )
    #घोषणा port_FPU_REGISTER_शब्दगण     ( ( 32 * 2 ) + 1 ) /* D0-D31 and FPSCR. */
#अन्यथा
    #घोषणा port_FPU_REGISTER_शब्दगण     ( ( 16 * 2 ) + 1 ) /* D0-D15 and FPSCR. */
#पूर्ण_अगर /* configFPU_D32 */

/*-----------------------------------------------------------*/

/*
 * These functions are necessarily written in assembly code, so are implemented
 * in portASM.S.
 */
बाह्य व्योम vPortRestoreTaskContext( व्योम );
बाह्य व्योम vPortInitialiseFPSCR( व्योम );
बाह्य uint32_t ulReadAPSR( व्योम );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
अटल व्योम prvTaskExitError( व्योम );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
अस्थिर uint32_t ulCriticalNesting = 9999UL;

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task. */
अस्थिर uint32_t ulPortTaskHasFPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
अस्थिर uint32_t ulPortYieldRequired = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
अस्थिर uint32_t ulPortInterruptNesting = 0UL;

/* Used in the asm file to clear an interrupt. */
__attribute__( ( used ) ) स्थिर uint32_t ulICCEOIR = configEOI_ADDRESS;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     व्योम * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) शून्य;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) शून्य;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) शून्य;
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) portINITIAL_SPSR;

    अगर( ( ( uint32_t ) pxCode & portTHUMB_MODE_ADDRESS ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_शीर्ष_Of_ढेर |= portTHUMB_MODE_BIT;
    }

    px_शीर्ष_Of_ढेर--;

    /* Next the return address, which in this case is the start of the task. */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pxCode;
    px_शीर्ष_Of_ढेर--;

    /* Next all the registers other than the stack pointer. */
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) portTASK_RETURN_ADDRESS; /* R14 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x12121212;              /* R12 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x11111111;              /* R11 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x10101010;              /* R10 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x09090909;              /* R9 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x08080808;              /* R8 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x07070707;              /* R7 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x06060606;              /* R6 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x05050505;              /* R5 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x04040404;              /* R4 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x03030303;              /* R3 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x02020202;              /* R2 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x01010101;              /* R1 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pvParameters;            /* R0 */
    px_शीर्ष_Of_ढेर--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_शीर्ष_Of_ढेर = portNO_CRITICAL_NESTING;

    #अगर ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /* The task will start without a floating point context.  A task that uses
         * the floating point hardware must call vPortTaskUsesFPU() before executing
         * any floating point instructions. */
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = portNO_FLOATING_POINT_CONTEXT;
    }
    #या_अगर ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /* The task will start with a floating point context.  Leave enough
         * space for the registers - and ensure they are initialised to 0. */
        px_शीर्ष_Of_ढेर -= port_FPU_REGISTER_शब्दगण;
        स_रखो( px_शीर्ष_Of_ढेर, 0x00, port_FPU_REGISTER_शब्दगण * माप( ढेर_Type_t ) );

        /* Initialise the slot containing ulPortTaskHasFPUContext to true as
         * the task starts with a floating point context. */
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = pdTRUE;
        ulPortTaskHasFPUContext = pdTRUE;
    }
    #अन्यथा
    {
        #त्रुटि "Invalid configUSE_TASK_FPU_SUPPORT value - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
    }
    #पूर्ण_अगर /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */

    वापस px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

अटल व्योम prvTaskExitError( व्योम )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ulPortInterruptNesting == ~0UL );
    portDISABLE_INTERRUPTS();

    क्रम( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( व्योम )
{
    uint32_t ulAPSR;

    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    ulAPSR = ulReadAPSR();

    ulAPSR &= portAPSR_MODE_BITS_MASK;
    configASSERT( ulAPSR != portAPSR_USER_MODE );

    अगर( ulAPSR != portAPSR_USER_MODE )
    {
        /* Start the timer that generates the tick ISR. */
        portDISABLE_INTERRUPTS();
        configSETUP_TICK_INTERRUPT();

        /* Start the first task executing. */
        vPortRestoreTaskContext();
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value.  prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( व्योम ) prvTaskExitError;
    वापस 0;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

व्योम vPortEnterCritical( व्योम )
{
    portDISABLE_INTERRUPTS();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    अगर( ulCriticalNesting == 1 )
    {
        configASSERT( ulPortInterruptNesting == 0 );
    }
}
/*-----------------------------------------------------------*/

व्योम vPortExitCritical( व्योम )
{
    अगर( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        अगर( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            portENABLE_INTERRUPTS();
        }
    }
}
/*-----------------------------------------------------------*/

व्योम FreeRTOS_Tick_Handler( व्योम )
{
    uint32_t ulInterruptStatus;

    ulInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();

    /* Increment the RTOS tick. */
    अगर( xTaskIncrementTick() != pdFALSE )
    {
        ulPortYieldRequired = pdTRUE;
    }

    portCLEAR_INTERRUPT_MASK_FROM_ISR( ulInterruptStatus );

    configCLEAR_TICK_INTERRUPT();
}
/*-----------------------------------------------------------*/

#अगर ( configUSE_TASK_FPU_SUPPORT != 2 )

    व्योम vPortTaskUsesFPU( व्योम )
    {
        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        ulPortTaskHasFPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        vPortInitialiseFPSCR();
    }

#पूर्ण_अगर /* configUSE_TASK_FPU_SUPPORT */
/*-----------------------------------------------------------*/
