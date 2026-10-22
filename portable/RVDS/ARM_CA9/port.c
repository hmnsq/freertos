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
#অন্তর্ভাব <stdlib.h>

/* Scheduler includes. */
#অন্তর্ভাব "FreeRTOS.h"
#অন্তর্ভাব "task.h"

#ifndef configINTERRUPT_CONTROLLER_BASE_ADDRESS
    #error "configINTERRUPT_CONTROLLER_BASE_ADDRESS must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#endif

#ifndef configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET
    #error "configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#endif

#ifndef configUNIQUE_INTERRUPT_PRIORITIES
    #error "configUNIQUE_INTERRUPT_PRIORITIES must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#endif

#ifndef configSETUP_TICK_INTERRUPT
    #error "configSETUP_TICK_INTERRUPT() must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#endif /* configSETUP_TICK_INTERRUPT */

#ifndef configMAX_API_CALL_INTERRUPT_PRIORITY
    #error "configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#endif

#যদি configMAX_API_CALL_INTERRUPT_PRIORITY == 0
    #error "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#endif

#যদি configMAX_API_CALL_INTERRUPT_PRIORITY > configUNIQUE_INTERRUPT_PRIORITIES
    #error "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#endif

#যদি configUSE_PORT_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #যদি ( configMAX_PRIORITIES > 32 )
        #error "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #endif
#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#যদি configMAX_API_CALL_INTERRUPT_PRIORITY <= ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )
    #error "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#endif

#ifndef configCLEAR_TICK_INTERRUPT
    #define configCLEAR_TICK_INTERRUPT()
#endif

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#যদি configUNIQUE_INTERRUPT_PRIORITIES == 16
    #define portPRIORITY_SHIFT            4
    #define port_MAX_দ্বিমিক_POINT_মান    3
#নোচেদ্যদি configUNIQUE_INTERRUPT_PRIORITIES == 32
    #define portPRIORITY_SHIFT            3
    #define port_MAX_দ্বিমিক_POINT_মান    2
#নোচেদ্যদি configUNIQUE_INTERRUPT_PRIORITIES == 64
    #define portPRIORITY_SHIFT            2
    #define port_MAX_দ্বিমিক_POINT_মান    1
#নোচেদ্যদি configUNIQUE_INTERRUPT_PRIORITIES == 128
    #define portPRIORITY_SHIFT            1
    #define port_MAX_দ্বিমিক_POINT_মান    0
#নোচেদ্যদি configUNIQUE_INTERRUPT_PRIORITIES == 256
    #define portPRIORITY_SHIFT            0
    #define port_MAX_দ্বিমিক_POINT_মান    0
#অন্যথা /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #error "Invalid configUNIQUE_INTERRUPT_PRIORITIES setting.  configUNIQUE_INTERRUPT_PRIORITIES must be set to the number of unique priorities implemented by the target hardware"
#endif /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#define portNO_CRITICAL_NESTING                              ( ( uint32_t ) 0 )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#define port_UNMASK_মান                                     ( 0xFFUL )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#define portNO_FLOATING_POINT_CONTEXT                        ( ( স্তূপ_Type_t ) 0 )

/* Interrupt controller access addresses. */
#define portICCPMR_PRIORITY_MASK_OFFSET                      ( 0x04 )
#define portICCIAR_INTERRUPT_ACKNOWLEDGE_OFFSET              ( 0x0C )
#define portICCEOIR_END_OF_INTERRUPT_OFFSET                  ( 0x10 )
#define port_ICCBPR_দ্বিমিক_POINT_OFFSET                       ( 0x08 )
#define portICCRPR_RUNNING_PRIORITY_OFFSET                   ( 0x14 )
#define portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS       ( configINTERRUPT_CONTROLLER_BASE_ADDRESS + configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET )
#define portICCPMR_PRIORITY_MASK_REGISTER                    ( *( ( চঞ্চল uint32_t * ) ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCPMR_PRIORITY_MASK_OFFSET ) ) )
#define portICCIAR_INTERRUPT_ACKNOWLEDGE_REGISTER_ADDRESS    ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCIAR_INTERRUPT_ACKNOWLEDGE_OFFSET )
#define portICCEOIR_END_OF_INTERRUPT_REGISTER_ADDRESS        ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCEOIR_END_OF_INTERRUPT_OFFSET )
#define portICCPMR_PRIORITY_MASK_REGISTER_ADDRESS            ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCPMR_PRIORITY_MASK_OFFSET )
#define port_ICCBPR_দ্বিমিক_POINT_REGISTER                     ( *( ( ধ্রুব চঞ্চল uint32_t * ) ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + port_ICCBPR_দ্বিমিক_POINT_OFFSET ) ) )
#define portICCRPR_RUNNING_PRIORITY_REGISTER                 ( *( ( ধ্রুব চঞ্চল uint32_t * ) ( portINTERRUPT_CONTROLLER_CPU_INTERFACE_ADDRESS + portICCRPR_RUNNING_PRIORITY_OFFSET ) ) )

/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#define port_দ্বিমিক_POINT_BITS                                ( ( uint8_t ) 0x03 )

/* Constants required to setup the initial task context. */
#define portINITIAL_SPSR                                     ( ( স্তূপ_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#define portTHUMB_MODE_BIT                                   ( ( স্তূপ_Type_t ) 0x20 )
#define portTHUMB_MODE_ADDRESS                               ( 0x01UL )

/* Masks all bits in the APSR other than the mode bits. */
#define portAPSR_MODE_BITS_MASK                              ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#define portAPSR_USER_MODE                                   ( 0x10 )

/* Macro to unmask all interrupt priorities. */
#define portCLEAR_INTERRUPT_MASK()                            \
    {                                                         \
        __disable_irq();                                      \
        portICCPMR_PRIORITY_MASK_REGISTER = port_UNMASK_মান; \
        __asm( "DSB        \n"                                \
               "ISB        \n" );                             \
        __enable_irq();                                       \
    }

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
বাহ্য শূন্য vPortRestoreTaskContext( শূন্য );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
স্থির শূন্য prvTaskExitError( শূন্য );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
চঞ্চল uint32_t ulCriticalNesting = 9999UL;

/* Used to pass constants into the ASM code.  The address at which variables are
 * placed is the constant value so indirect loads in the asm code are not
 * required. */
uint32_t ulICCIAR __attribute__( ( at( portICCIAR_INTERRUPT_ACKNOWLEDGE_REGISTER_ADDRESS ) ) );
uint32_t ulICCEOIR __attribute__( ( at( portICCEOIR_END_OF_INTERRUPT_REGISTER_ADDRESS ) ) );
uint32_t ulICCPMR __attribute__( ( at( portICCPMR_PRIORITY_MASK_REGISTER_ADDRESS ) ) );
uint32_t ulAsmAPIPriorityMask __attribute__( ( at( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) ) );

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task. */
uint32_t ulPortTaskHasFPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ulPortYieldRequired = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint32_t ulPortInterruptNesting = 0UL;

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
স্তূপ_Type_t * px_Port_Initialise_স্তূপ( স্তূপ_Type_t * px_শীর্ষ_Of_স্তূপ,
                                     TaskFunction_t pxCode,
                                     শূন্য * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *px_শীর্ষ_Of_স্তূপ = রিক্ত;
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = রিক্ত;
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = রিক্ত;
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) portINITIAL_SPSR;

    যদি( ( ( uint32_t ) pxCode & portTHUMB_MODE_ADDRESS ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_শীর্ষ_Of_স্তূপ |= portTHUMB_MODE_BIT;
    }

    px_শীর্ষ_Of_স্তূপ--;

    /* Next the return address, which in this case is the start of the task. */
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pxCode;
    px_শীর্ষ_Of_স্তূপ--;

    /* Next all the registers other than the stack pointer. */
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) prvTaskExitError; /* R14 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x12121212;       /* R12 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x11111111;       /* R11 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x10101010;       /* R10 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x09090909;       /* R9 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x08080808;       /* R8 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x07070707;       /* R7 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x06060606;       /* R6 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x05050505;       /* R5 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x04040404;       /* R4 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x03030303;       /* R3 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x02020202;       /* R2 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) 0x01010101;       /* R1 */
    px_শীর্ষ_Of_স্তূপ--;
    *px_শীর্ষ_Of_স্তূপ = ( স্তূপ_Type_t ) pvParameters;     /* R0 */
    px_শীর্ষ_Of_স্তূপ--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_শীর্ষ_Of_স্তূপ = portNO_CRITICAL_NESTING;
    px_শীর্ষ_Of_স্তূপ--;

    /* The task will start without a floating point context.  A task that uses
     * the floating point hardware must call vPortTaskUsesFPU() before executing
     * any floating point instructions. */
    *px_শীর্ষ_Of_স্তূপ = portNO_FLOATING_POINT_CONTEXT;

    প্রত্যাগম px_শীর্ষ_Of_স্তূপ;
}
/*-----------------------------------------------------------*/

স্থির শূন্য prvTaskExitError( শূন্য )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ulPortInterruptNesting == ~0UL );
    portDISABLE_INTERRUPTS();

    প্রতি( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( শূন্য )
{
    uint32_t ulAPSR;

    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    __asm( "MRS ulAPSR, APSR" );
    ulAPSR &= portAPSR_MODE_BITS_MASK;
    configASSERT( ulAPSR != portAPSR_USER_MODE );

    যদি( ulAPSR != portAPSR_USER_MODE )
    {
        /* Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information. */
        configASSERT( ( port_ICCBPR_দ্বিমিক_POINT_REGISTER & port_দ্বিমিক_POINT_BITS ) <= port_MAX_দ্বিমিক_POINT_মান );

        যদি( ( port_ICCBPR_দ্বিমিক_POINT_REGISTER & port_দ্বিমিক_POINT_BITS ) <= port_MAX_দ্বিমিক_POINT_মান )
        {
            /* Start the timer that generates the tick ISR. */
            configSETUP_TICK_INTERRUPT();

            __enable_irq();
            vPortRestoreTaskContext();
        }
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. */
    প্রত্যাগম 0;
}
/*-----------------------------------------------------------*/

শূন্য vPortEndScheduler( শূন্য )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

শূন্য vPortEnterCritical( শূন্য )
{
    /* Disable interrupts as per portDISABLE_INTERRUPTS();  */
    ulPortSetInterruptMask();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    যদি( ulCriticalNesting == 1 )
    {
        configASSERT( ulPortInterruptNesting == 0 );
    }
}
/*-----------------------------------------------------------*/

শূন্য vPortExitCritical( শূন্য )
{
    যদি( ulCriticalNesting > portNO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        যদি( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            portCLEAR_INTERRUPT_MASK();
        }
    }
}
/*-----------------------------------------------------------*/

শূন্য FreeRTOS_Tick_Handler( শূন্য )
{
    /* Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value. */
    __disable_irq();
    portICCPMR_PRIORITY_MASK_REGISTER = ( uint32_t ) ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT );
    __asm( "DSB        \n"
           "ISB        \n" );
    __enable_irq();

    /* Increment the RTOS tick. */
    যদি( xTaskIncrementTick() != pdFALSE )
    {
        ulPortYieldRequired = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    portCLEAR_INTERRUPT_MASK();
    configCLEAR_TICK_INTERRUPT();
}
/*-----------------------------------------------------------*/

শূন্য vPortTaskUsesFPU( শূন্য )
{
    uint32_t ulInitialFPSCR = 0;

    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ulPortTaskHasFPUContext = pdTRUE;

    /* Initialise the floating point status register. */
    __asm( "FMXR    FPSCR, ulInitialFPSCR" );
}
/*-----------------------------------------------------------*/

শূন্য vPortClearInterruptMask( uint32_t ul_New_Mask_মান )
{
    যদি( ul_New_Mask_মান == pdFALSE )
    {
        portCLEAR_INTERRUPT_MASK();
    }
}
/*-----------------------------------------------------------*/

uint32_t ulPortSetInterruptMask( শূন্য )
{
    uint32_t ulReturn;

    __disable_irq();

    যদি( portICCPMR_PRIORITY_MASK_REGISTER == ( uint32_t ) ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    অন্যথা
    {
        ulReturn = pdFALSE;
        portICCPMR_PRIORITY_MASK_REGISTER = ( uint32_t ) ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT );
        __asm( "DSB        \n"
               "ISB        \n" );
    }

    __enable_irq();

    প্রত্যাগম ulReturn;
}
/*-----------------------------------------------------------*/

#যদি ( configASSERT_DEFINED == 1 )

    শূন্য vPortValidateInterruptPriority( শূন্য )
    {
        /* The following assertion will fail if a service routine (ISR) for
         * an interrupt that has been assigned a priority above
         * configMAX_SYSCALL_INTERRUPT_PRIORITY calls an ISR safe FreeRTOS API
         * function.  ISR safe FreeRTOS API functions must *only* be called
         * from interrupts that have been assigned a priority at or below
         * configMAX_SYSCALL_INTERRUPT_PRIORITY.
         *
         * Numerically low interrupt priority numbers represent logically high
         * interrupt priorities, therefore the priority of the interrupt must
         * be set to a value equal to or numerically *higher* than
         * configMAX_SYSCALL_INTERRUPT_PRIORITY.
         *
         * FreeRTOS maintains separate thread and ISR API functions to ensure
         * interrupt entry is as fast and simple as possible.
         *
         * The following links provide detailed information:
         * https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html
         * https://www.freertos.org/Why-FreeRTOS/FAQs */
        configASSERT( portICCRPR_RUNNING_PRIORITY_REGISTER >= ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) );

        /* Priority grouping:  The interrupt controller (GIC) allows the bits
         * that define each interrupt's priority to be split between bits that
         * define the interrupt's pre-emption priority bits and bits that define
         * the interrupt's sub-priority.  For simplicity all bits must be defined
         * to be pre-emption priority bits.  The following assertion will fail if
         * this is not the case (if some bits represent a sub-priority).
         *
         * The priority grouping is configured by the GIC's binary point register
         * (ICCBPR).  Writing 0 to ICCBPR will ensure it is set to its lowest
         * possible value (which may be above 0). */
        configASSERT( port_ICCBPR_দ্বিমিক_POINT_REGISTER <= port_MAX_দ্বিমিক_POINT_মান );
    }

#endif /* configASSERT_DEFINED */
