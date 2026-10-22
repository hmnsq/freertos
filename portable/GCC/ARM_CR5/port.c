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

#अगर_अघोषित configINTERRUPT_CONTROLLER_BASE_ADDRESS
    #त्रुटि configINTERRUPT_CONTROLLER_BASE_ADDRESS must be defined.  Refer to Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#पूर्ण_अगर

#अगर_अघोषित configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET
    #त्रुटि configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET must be defined.  Refer to Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#पूर्ण_अगर

#अगर_अघोषित configUNIQUE_INTERRUPT_PRIORITIES
    #त्रुटि configUNIQUE_INTERRUPT_PRIORITIES must be defined.  Refer to Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#पूर्ण_अगर

#अगर_अघोषित configSETUP_TICK_INTERRUPT
    #त्रुटि configSETUP_TICK_INTERRUPT() must be defined.  Refer to Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#पूर्ण_अगर /* configSETUP_TICK_INTERRUPT */

#अगर_अघोषित configMAX_API_CALL_INTERRUPT_PRIORITY
    #त्रुटि configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  Refer to Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#पूर्ण_अगर

#अगर configMAX_API_CALL_INTERRUPT_PRIORITY == 0
    #त्रुटि configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0
#पूर्ण_अगर

#अगर configMAX_API_CALL_INTERRUPT_PRIORITY > configUNIQUE_INTERRUPT_PRIORITIES
    #त्रुटि configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority मूल्य the higher the logical interrupt priority
#पूर्ण_अगर

#अगर configUSE_PORT_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #अगर ( configMAX_PRIORITIES > 32 )
        #त्रुटि configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a प्रणाली requires more than 10 to 15 difference priorities as tasks that share a priority will समय slice.
    #पूर्ण_अगर
#पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#अगर configMAX_API_CALL_INTERRUPT_PRIORITY <= ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )
    #त्रुटि configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )
#पूर्ण_अगर

/*
 * __ARM_FP is defined by the c preprocessor when FPU support is enabled,
 * usually with the -mfpu= argument and -mfloat-abi=.
 *
 * Note: Some implementations of the c standard library may use FPU registers
 *       for generic memory operations (memcpy, etc).
 *       When setting configUSE_TASK_FPU_SUPPORT == 1, care must be taken to
 *       ensure that the FPU registers are not used without an FPU context.
 */
#अगर ( configUSE_TASK_FPU_SUPPORT == 0 )
    #अगर_घोषित __ARM_FP
        #त्रुटि __ARM_FP is defined, so configUSE_TASK_FPU_SUPPORT must be set to either to 1 or 2.
    #पूर्ण_अगर /* __ARM_FP */
#या_अगर ( configUSE_TASK_FPU_SUPPORT == 1 ) || ( configUSE_TASK_FPU_SUPPORT == 2 )
    #अगर_अघोषित __ARM_FP
        #त्रुटि __ARM_FP is not defined, so configUSE_TASK_FPU_SUPPORT must be set to 0.
    #पूर्ण_अगर /* __ARM_FP */
#पूर्ण_अगर /* configUSE_TASK_FPU_SUPPORT */

/*
 * Some vendor specific files default configCLEAR_TICK_INTERRUPT() in
 * portmacro.h.
 */
#अगर_अघोषित configCLEAR_TICK_INTERRUPT
    #घोषणा configCLEAR_TICK_INTERRUPT()
#पूर्ण_अगर

/*
 * A critical section is exited when the critical section nesting count reaches
 * this value.
 */
#घोषणा portNO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/*
 * In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority.
 */
#घोषणा port_UNMASK_मूल्य                 ( 0xFFUL )

/*
 * Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context.
 */
#घोषणा portNO_FLOATING_POINT_CONTEXT    ( ( ढेर_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#घोषणा portINITIAL_SPSR                 ( ( ढेर_Type_t ) 0x1f ) /* System mode, ARM mode, IRQ enabled FIQ enabled. */
#घोषणा portTHUMB_MODE_BIT               ( ( ढेर_Type_t ) 0x20 )
#घोषणा portINTERRUPT_ENABLE_BIT         ( 0x80UL )
#घोषणा portTHUMB_MODE_ADDRESS           ( 0x01UL )

/*
 * Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero.
 */
#घोषणा port_द्विआधारी_POINT_BITS            ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#घोषणा portAPSR_MODE_BITS_MASK          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#घोषणा portAPSR_USER_MODE               ( 0x10 )

/* The critical section macros only mask interrupts up to an application
 * determined priority level.  Sometimes it is necessary to turn interrupt off in
 * the CPU itself before modifying certain hardware registers. */
#घोषणा portCPU_IRQ_DISABLE()                  \
    __asm अस्थिर ( "CPSID i" ::: "memory" ); \
    __asm अस्थिर ( "DSB" );                  \
    __asm अस्थिर ( "ISB" );

#घोषणा portCPU_IRQ_ENABLE()                   \
    __asm अस्थिर ( "CPSIE i" ::: "memory" ); \
    __asm अस्थिर ( "DSB" );                  \
    __asm अस्थिर ( "ISB" );


/* Macro to unmask all interrupt priorities. */
#घोषणा portCLEAR_INTERRUPT_MASK()                            \
    {                                                         \
        portCPU_IRQ_DISABLE();                                \
        portICCPMR_PRIORITY_MASK_REGISTER = port_UNMASK_मूल्य; \
        __asm अस्थिर ( "DSB       \n"                       \
                         "ISB       \n" );                    \
        portCPU_IRQ_ENABLE();                                 \
    }

#घोषणा portINTERRUPT_PRIORITY_REGISTER_OFFSET    0x400UL
#घोषणा port_MAX_8_BIT_मूल्य                       ( ( uint8_t ) 0xff )
#घोषणा portBIT_0_SET                             ( ( uint8_t ) 0x01 )

/*
 * Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case is messes up unwinding of the stack in the
 * debugger.
 */
#अगर_घोषित configTASK_RETURN_ADDRESS
    #घोषणा portTASK_RETURN_ADDRESS    configTASK_RETURN_ADDRESS
#अन्यथा
    #घोषणा portTASK_RETURN_ADDRESS    prvTaskExitError
#पूर्ण_अगर

#अगर ( configUSE_TASK_FPU_SUPPORT != 0 )

/*
 * The space on the stack required to hold the FPU registers.
 *
 * The ARM Cortex R5 processor implements the VFPv3-D16 FPU
 * architecture. This includes only 16 double-precision registers,
 * instead of 32 as is in VFPv3. The register bank can be viewed
 * either as sixteen 64-bit double-word registers (D0-D15) or
 * thirty-two 32-bit single-word registers (S0-S31), in both cases
 * the size of the bank remains the same. The FPU has also a 32-bit
 * status register.
 */
    #घोषणा port_FPU_REGISTER_शब्दगण    ( ( 16 * 2 ) + 1 )
#पूर्ण_अगर /* configUSE_TASK_FPU_SUPPORT != 0 */

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
बाह्य व्योम vPortRestoreTaskContext( व्योम );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
अटल व्योम prvTaskExitError( व्योम );

#अगर ( configUSE_TASK_FPU_SUPPORT != 0 )

/*
 * If the application provides an implementation of vApplicationIRQHandler(),
 * then it will get called directly without saving the FPU registers on
 * interrupt entry, and this weak implementation of
 * vApplicationFPUSafeIRQHandler() is just provided to remove linkage errors -
 * it should never actually get called so its implementation contains a
 * call to configASSERT() that will always fail.
 *
 * If the application provides its own implementation of
 * vApplicationFPUSafeIRQHandler() then the implementation of
 * vApplicationIRQHandler() provided in portASM.S will save the FPU registers
 * before calling it.
 *
 * Therefore, if the application writer wants FPU registers to be saved on
 * interrupt entry their IRQ handler must be called
 * vApplicationFPUSafeIRQHandler(), and if the application writer does not want
 * FPU registers to be saved on interrupt entry their IRQ handler must be
 * called vApplicationIRQHandler().
 */
    व्योम vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR ) __attribute__( ( weak ) );
#पूर्ण_अगर /* configUSE_TASK_FPU_SUPPORT != 0 */

/*-----------------------------------------------------------*/

/*
 * A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started.
 */
अस्थिर uint32_t ulCriticalNesting = 9999UL;

#अगर ( configUSE_TASK_FPU_SUPPORT != 0 )

/*
 * Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task.
 */
    uint32_t ulPortTaskHasFPUContext = pdFALSE;
#पूर्ण_अगर /* configUSE_TASK_FPU_SUPPORT != 0 */

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ulPortYieldRequired = pdFALSE;

/*
 * Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0.
 */
uint32_t ulPortInterruptNesting = 0UL;

/* Used in asm code. */
__attribute__( ( used ) ) स्थिर uint32_t ulICCIAR = portICCIAR_INTERRUPT_ACKNOWLEDGE_REGISTER_ADDRESS;
__attribute__( ( used ) ) स्थिर uint32_t ulICCEOIR = portICCEOIR_END_OF_INTERRUPT_REGISTER_ADDRESS;
__attribute__( ( used ) ) स्थिर uint32_t ulICCPMR = portICCPMR_PRIORITY_MASK_REGISTER_ADDRESS;
__attribute__( ( used ) ) स्थिर uint32_t ulMaxAPIPriorityMask = ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     व्योम * pvParameters )
{
    /*
     * Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address.
     */
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

    /*
     * The task will start with a critical nesting count of 0 as interrupts are
     * enabled.
     */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = portNO_CRITICAL_NESTING;

    #अगर ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /*
         * The task will start without a floating point context.
         * A task that uses the floating point hardware must call
         * vPortTaskUsesFPU() before executing any floating point
         * instructions.
         */
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = portNO_FLOATING_POINT_CONTEXT;
    }
    #या_अगर ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /*
         * The task will start with a floating point context. Leave enough
         * space for the registers and ensure they are initialized to 0.
         */
        px_शीर्ष_Of_ढेर -= port_FPU_REGISTER_शब्दगण;
        स_रखो( px_शीर्ष_Of_ढेर, 0x00, port_FPU_REGISTER_शब्दगण * माप( ढेर_Type_t ) );

        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = pdTRUE;
        ulPortTaskHasFPUContext = pdTRUE;
    }
    #या_अगर ( configUSE_TASK_FPU_SUPPORT != 0 )
    {
        #त्रुटि Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 0, 1, or 2.
    }
    #पूर्ण_अगर /* configUSE_TASK_FPU_SUPPORT */

    वापस px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

अटल व्योम prvTaskExitError( व्योम )
{
    /*
     * A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error.
     */
    configASSERT( ulPortInterruptNesting == ~0UL );
    portDISABLE_INTERRUPTS();

    क्रम( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

#अगर ( configUSE_TASK_FPU_SUPPORT != 0 )

    व्योम vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR ) /* __attribute__( ( weak ) ) */
    {
        ( व्योम ) ulICCIAR;
        configASSERT( ( अस्थिर व्योम * ) शून्य );
    }

#पूर्ण_अगर /* configUSE_TASK_FPU_SUPPORT != 0 */
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( व्योम )
{
    uint32_t ulAPSR, ulCycles = 8; /* 8 bits per byte. */

    #अगर ( configASSERT_DEFINED == 1 )
    {
        अस्थिर uint8_t ucOriginalPriority;
        अस्थिर uint8_t * स्थिर pucFirstUserPriorityRegister = ( अस्थिर uint8_t * स्थिर ) ( configINTERRUPT_CONTROLLER_BASE_ADDRESS + portINTERRUPT_PRIORITY_REGISTER_OFFSET );
        अस्थिर uint8_t uc_Max_Priority_मूल्य;

        /*
         * Determine how many priority bits are implemented in the GIC.
         * Save the interrupt priority value that is about to be clobbered.
         */
        ucOriginalPriority = *pucFirstUserPriorityRegister;

        /*
         * Determine the number of priority bits available.  First write to
         * all possible bits.
         */
        *pucFirstUserPriorityRegister = port_MAX_8_BIT_मूल्य;

        /* Read the value back to see how many bits stuck. */
        uc_Max_Priority_मूल्य = *pucFirstUserPriorityRegister;

        /* Shift to the least significant bits. */
        जबतक( ( uc_Max_Priority_मूल्य & portBIT_0_SET ) != portBIT_0_SET )
        {
            uc_Max_Priority_मूल्य >>= ( uint8_t ) 0x01;

            /*
             * If ulCycles reaches 0 then ucMaxPriorityValue must have been
             * read as 0, indicating a misconfiguration.
             */
            ulCycles--;

            अगर( ulCycles == 0 )
            {
                अवरोध;
            }
        }

        /*
         * Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value.
         */
        configASSERT( uc_Max_Priority_मूल्य == portLOWEST_INTERRUPT_PRIORITY );

        /*
         * Restore the clobbered interrupt priority register to its original
         * value.
         */
        *pucFirstUserPriorityRegister = ucOriginalPriority;
    }
    #पूर्ण_अगर /* configASSERT_DEFINED */

    /*
     * Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start.
     */
    __asm अस्थिर ( "MRS %0, APSR" : "=r" ( ulAPSR )::"memory" );
    ulAPSR &= portAPSR_MODE_BITS_MASK;
    configASSERT( ulAPSR != portAPSR_USER_MODE );

    अगर( ulAPSR != portAPSR_USER_MODE )
    {
        /*
         * Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information.
         */
        configASSERT( ( port_ICCBPR_द्विआधारी_POINT_REGISTER & port_द्विआधारी_POINT_BITS ) <= port_MAX_द्विआधारी_POINT_मूल्य );

        अगर( ( port_ICCBPR_द्विआधारी_POINT_REGISTER & port_द्विआधारी_POINT_BITS ) <= port_MAX_द्विआधारी_POINT_मूल्य )
        {
            /*
             * Interrupts are turned off in the CPU itself to ensure tick does
             * not execute  while the scheduler is being started.  Interrupts are
             * automatically turned back on in the CPU when the first task starts
             * executing.
             */
            portCPU_IRQ_DISABLE();

            /* Start the timer that generates the tick ISR. */
            configSETUP_TICK_INTERRUPT();

            /* Start the first task executing. */
            vPortRestoreTaskContext();
        }
    }

    /*
     * Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value.  prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address.
     */
    ( व्योम ) prvTaskExitError;

    वापस 0;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /*
     * Not implemented in ports where there is nothing to return to.
     * Artificially force an assert.
     */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

व्योम vPortEnterCritical( व्योम )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    ulPortSetInterruptMask();

    /*
     * Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called.
     */
    ulCriticalNesting++;

    /*
     * This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section.
     */
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
        /* Decrement the nesting count as the critical section is being exited. */
        ulCriticalNesting--;

        /*
         * If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled.
         */
        अगर( ulCriticalNesting == portNO_CRITICAL_NESTING )
        {
            /*
             * Critical nesting has reached zero so all interrupt priorities
             * should be unmasked.
             */
            portCLEAR_INTERRUPT_MASK();
        }
    }
}
/*-----------------------------------------------------------*/

व्योम FreeRTOS_Tick_Handler( व्योम )
{
    /*
     * Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated.
     */
    portCPU_IRQ_DISABLE();
    portICCPMR_PRIORITY_MASK_REGISTER = ( uint32_t ) ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT );
    __asm अस्थिर ( "dsb       \n"
                     "isb       \n" ::: "memory" );
    portCPU_IRQ_ENABLE();

    /* Increment the RTOS tick. */
    अगर( xTaskIncrementTick() != pdFALSE )
    {
        ulPortYieldRequired = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    portCLEAR_INTERRUPT_MASK();
    configCLEAR_TICK_INTERRUPT();
}
/*-----------------------------------------------------------*/

#अगर ( configUSE_TASK_FPU_SUPPORT == 1 )

    व्योम vPortTaskUsesFPU( व्योम )
    {
        uint32_t ulInitialFPSCR = 0;

        /*
         * A task is registering the fact that it needs an FPU context. Set the
         * FPU flag (which is saved as part of the task context).
         */
        ulPortTaskHasFPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        __asm अस्थिर ( "FMXR  FPSCR, %0" ::"r" ( ulInitialFPSCR ) : "memory" );
    }

#पूर्ण_अगर /* configUSE_TASK_FPU_SUPPORT == 1 */
/*-----------------------------------------------------------*/

व्योम vPortClearInterruptMask( uint32_t ul_New_Mask_मूल्य )
{
    अगर( ul_New_Mask_मूल्य == pdFALSE )
    {
        portCLEAR_INTERRUPT_MASK();
    }
}
/*-----------------------------------------------------------*/

uint32_t ulPortSetInterruptMask( व्योम )
{
    uint32_t ulReturn;

    /* Interrupts must be masked while ICCPMR is updated. */
    portCPU_IRQ_DISABLE();

    अगर( portICCPMR_PRIORITY_MASK_REGISTER == ( uint32_t ) ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    अन्यथा
    {
        ulReturn = pdFALSE;
        portICCPMR_PRIORITY_MASK_REGISTER = ( uint32_t ) ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT );
        __asm अस्थिर ( "dsb       \n"
                         "isb       \n" ::: "memory" );
    }

    portCPU_IRQ_ENABLE();

    वापस ulReturn;
}
/*-----------------------------------------------------------*/

#अगर ( configASSERT_DEFINED == 1 )

    व्योम vPortValidateInterruptPriority( व्योम )
    {
        /*
         * The following assertion will fail if a service routine (ISR) for
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
         */

        configASSERT( portICCRPR_RUNNING_PRIORITY_REGISTER >= ( uint32_t ) ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) );

        /*
         * Priority grouping:  The interrupt controller (GIC) allows the bits
         * that define each interrupt's priority to be split between bits that
         * define the interrupt's pre-emption priority bits and bits that define
         * the interrupt's sub-priority.  For simplicity all bits must be defined
         * to be pre-emption priority bits.  The following assertion will fail if
         * this is not the case (if some bits represent a sub-priority).
         *
         * The priority grouping is configured by the GIC's binary point register
         * (ICCBPR).  Writing 0 to ICCBPR will ensure it is set to its lowest
         * possible value (which may be above 0).
         */
        configASSERT( ( port_ICCBPR_द्विआधारी_POINT_REGISTER & port_द्विआधारी_POINT_BITS ) <= port_MAX_द्विआधारी_POINT_मूल्य );
    }

#पूर्ण_अगर /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/
