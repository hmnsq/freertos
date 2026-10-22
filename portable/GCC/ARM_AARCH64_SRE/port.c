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

/* Scheduler includes. */
#समावेश "FreeRTOS.h"
#समावेश "task.h"

#अगर_अघोषित configUNIQUE_INTERRUPT_PRIORITIES
    #त्रुटि "configUNIQUE_INTERRUPT_PRIORITIES must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#पूर्ण_अगर

#अगर_अघोषित configSETUP_TICK_INTERRUPT
    #त्रुटि "configSETUP_TICK_INTERRUPT() must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#पूर्ण_अगर /* configSETUP_TICK_INTERRUPT */

#अगर_अघोषित configMAX_API_CALL_INTERRUPT_PRIORITY
    #त्रुटि "configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#पूर्ण_अगर

#अगर configMAX_API_CALL_INTERRUPT_PRIORITY == 0
    #त्रुटि "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#पूर्ण_अगर

#अगर configMAX_API_CALL_INTERRUPT_PRIORITY > configUNIQUE_INTERRUPT_PRIORITIES
    #त्रुटि "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#पूर्ण_अगर

#अगर configUSE_PORT_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #अगर ( configMAX_PRIORITIES > 32 )
        #त्रुटि "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #पूर्ण_अगर
#पूर्ण_अगर /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#अगर configMAX_API_CALL_INTERRUPT_PRIORITY <= ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )
    #त्रुटि "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#पूर्ण_अगर

/* Some vendor specific files default configCLEAR_TICK_INTERRUPT() in
 * portmacro.h. */
#अगर_अघोषित configCLEAR_TICK_INTERRUPT
    #घोषणा configCLEAR_TICK_INTERRUPT()
#पूर्ण_अगर

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#घोषणा portNO_CRITICAL_NESTING          ( ( माप_प्रकार ) 0 )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#घोषणा port_UNMASK_मूल्य                 ( 0xFFUL )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#घोषणा portNO_FLOATING_POINT_CONTEXT    ( ( ढेर_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#घोषणा portSP_ELx                       ( ( ढेर_Type_t ) 0x01 )
#घोषणा portSP_EL0                       ( ( ढेर_Type_t ) 0x00 )

#अगर defined( GUEST )
    #घोषणा portEL1                      ( ( ढेर_Type_t ) 0x04 )
    #घोषणा portINITIAL_PSTATE           ( portEL1 | portSP_EL0 )
#अन्यथा
    #घोषणा portEL3                      ( ( ढेर_Type_t ) 0x0c )
    /* At the time of writing, the BSP only supports EL3. */
    #घोषणा portINITIAL_PSTATE           ( portEL3 | portSP_EL0 )
#पूर्ण_अगर

/* Masks all bits in the APSR other than the mode bits. */
#घोषणा portAPSR_MODE_BITS_MASK    ( 0x0C )

/* The I bit in the DAIF bits. */
#घोषणा portDAIF_I                 ( 0x80 )

/* Macro to unmask all interrupt priorities. */
/* s3_0_c4_c6_0 is ICC_PMR_EL1. */
#घोषणा portCLEAR_INTERRUPT_MASK()                     \
    {                                                  \
        __asm अस्थिर ( "MSR DAIFSET, #2        \n"   \
                         "DSB SY                 \n"   \
                         "ISB SY                 \n"   \
                         "MSR s3_0_c4_c6_0, %0   \n"   \
                         "DSB SY                 \n"   \
                         "ISB SY                 \n"   \
                         "MSR DAIFCLR, #2        \n"   \
                         "DSB SY                 \n"   \
                         "ISB SY                 \n"   \
                         ::"r" ( port_UNMASK_मूल्य ) ); \
    }

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit plus 2 64-bit status registers.*/
#घोषणा port_FPU_REGISTER_शब्दगण     ( (32 * 2) + 2 )

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
बाह्य व्योम vPortRestoreTaskContext( व्योम );

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
व्योम vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR ) __attribute__((weak) );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
अस्थिर uint64_t ullCriticalNesting = 9999ULL;

/* Saved as part of the task context.  If ullPortTaskHasFPUContext is non-zero
 * then floating point context must be saved and restored for the task. */
uint64_t ullPortTaskHasFPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint64_t ullPortYieldRequired = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint64_t ullPortInterruptNesting = 0;

/* Used in the ASM code. */
__attribute__( ( used ) ) स्थिर uint64_t ullMaxAPIPriorityMask = ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ढेर_Type_t * px_Port_Initialise_ढेर( ढेर_Type_t * px_शीर्ष_Of_ढेर,
                                     TaskFunction_t pxCode,
                                     व्योम * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First all the general purpose registers. */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x0101010101010101ULL;        /* R1 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pvParameters; /* R0 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x0303030303030303ULL;        /* R3 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x0202020202020202ULL;        /* R2 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x0505050505050505ULL;        /* R5 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x0404040404040404ULL;        /* R4 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x0707070707070707ULL;        /* R7 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x0606060606060606ULL;        /* R6 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x0909090909090909ULL;        /* R9 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x0808080808080808ULL;        /* R8 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x1111111111111111ULL;        /* R11 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x1010101010101010ULL;        /* R10 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x1313131313131313ULL;        /* R13 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x1212121212121212ULL;        /* R12 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x1515151515151515ULL;        /* R15 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x1414141414141414ULL;        /* R14 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x1717171717171717ULL;        /* R17 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x1616161616161616ULL;        /* R16 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x1919191919191919ULL;        /* R19 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x1818181818181818ULL;        /* R18 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x2121212121212121ULL;        /* R21 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x2020202020202020ULL;        /* R20 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x2323232323232323ULL;        /* R23 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x2222222222222222ULL;        /* R22 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x2525252525252525ULL;        /* R25 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x2424242424242424ULL;        /* R24 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x2727272727272727ULL;        /* R27 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x2626262626262626ULL;        /* R26 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x2929292929292929ULL;        /* R29 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = 0x2828282828282828ULL;        /* R28 */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x00;         /* XZR - has no effect, used so there are an even number of registers. */
    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) 0x00;         /* R30 - procedure call link register. */

    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = portINITIAL_PSTATE;

    px_शीर्ष_Of_ढेर--;
    *px_शीर्ष_Of_ढेर = ( ढेर_Type_t ) pxCode; /* Exception return address. */

    #अगर ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = portNO_CRITICAL_NESTING;

        /* The task will start without a floating point context.  A task that
        * uses the floating point hardware must call vPortTaskUsesFPU() before
        * executing any floating point instructions. */
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = portNO_FLOATING_POINT_CONTEXT;
    }
    #या_अगर ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /* The task will start with a floating point context.  Leave enough
        * space for the registers - and ensure they are initialised to 0. */
        px_शीर्ष_Of_ढेर -= port_FPU_REGISTER_शब्दगण;
        स_रखो( px_शीर्ष_Of_ढेर, 0x00, port_FPU_REGISTER_शब्दगण * माप( ढेर_Type_t ) );

        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = portNO_CRITICAL_NESTING;

        px_शीर्ष_Of_ढेर--;
        *px_शीर्ष_Of_ढेर = pdTRUE;
        ullPortTaskHasFPUContext = pdTRUE;
    }
    #अन्यथा /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */
    {
        #त्रुटि "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
    }
    #पूर्ण_अगर /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */

    वापस px_शीर्ष_Of_ढेर;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( व्योम )
{
    uint32_t ulAPSR;

    __asm अस्थिर ( "MRS %0, CurrentEL" : "=r" ( ulAPSR ) );

    ulAPSR &= portAPSR_MODE_BITS_MASK;

    #अगर defined( GUEST )
        configASSERT( ulAPSR == portEL1 );

        अगर( ulAPSR == portEL1 )
    #अन्यथा
        configASSERT( ulAPSR == portEL3 );

        अगर( ulAPSR == portEL3 )
    #पूर्ण_अगर
    {
        /* Interrupts are turned off in the CPU itself to ensure a tick does
         * not execute while the scheduler is being started.  Interrupts are
         * automatically turned back on in the CPU when the first task starts
         * executing. */
        portDISABLE_INTERRUPTS();

        /* Start the timer that generates the tick ISR. */
        configSETUP_TICK_INTERRUPT();

        /* Start the first task executing. */
        vPortRestoreTaskContext();
    }

    वापस 0;
}
/*-----------------------------------------------------------*/

व्योम vPortEndScheduler( व्योम )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ullCriticalNesting == 1000ULL );
}
/*-----------------------------------------------------------*/

व्योम vPortEnterCritical( व्योम )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    uxPortSetInterruptMask();

    /* Now interrupts are disabled ullCriticalNesting can be accessed
     * directly.  Increment ullCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ullCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    अगर( ullCriticalNesting == 1ULL )
    {
        configASSERT( ullPortInterruptNesting == 0 );
    }
}
/*-----------------------------------------------------------*/

व्योम vPortExitCritical( व्योम )
{
    अगर( ullCriticalNesting > portNO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ullCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        अगर( ullCriticalNesting == portNO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            portCLEAR_INTERRUPT_MASK();
        }
    }
}
/*-----------------------------------------------------------*/

व्योम FreeRTOS_Tick_Handler( व्योम )
{
    /* Must be the lowest possible priority. */
    #अगर !defined( QEMU )
    {
        uint64_t ullRunningInterruptPriority;
        /* s3_0_c12_c11_3 is ICC_RPR_EL1. */
        __asm अस्थिर ( "MRS %0, s3_0_c12_c11_3" : "=r" ( ullRunningInterruptPriority ) );
        configASSERT( ullRunningInterruptPriority == ( portLOWEST_USABLE_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) );
    }
    #पूर्ण_अगर

    /* Interrupts should not be enabled before this point. */
    #अगर ( configASSERT_DEFINED == 1 )
    {
        uint32_t ulMaskBits;

        __asm अस्थिर ( "MRS %0, DAIF" : "=r" ( ulMaskBits )::"memory" );
        configASSERT( ( ulMaskBits & portDAIF_I ) != 0 );
    }
    #पूर्ण_अगर /* configASSERT_DEFINED */

    /* Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated. */
    /* s3_0_c4_c6_0 is ICC_PMR_EL1. */
    __asm अस्थिर ( "MSR s3_0_c4_c6_0, %0      \n"
                     "DSB SY                    \n"
                     "ISB SY                    \n"
                     ::"r" ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) : "memory" );

    /* Ok to enable interrupts after the interrupt source has been cleared. */
    configCLEAR_TICK_INTERRUPT();
    portENABLE_INTERRUPTS();

    /* Increment the RTOS tick. */
    अगर( xTaskIncrementTick() != pdFALSE )
    {
        ullPortYieldRequired = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    portCLEAR_INTERRUPT_MASK();
}
/*-----------------------------------------------------------*/

#अगर ( configUSE_TASK_FPU_SUPPORT != 2 )

व्योम vPortTaskUsesFPU( व्योम )
{
    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ullPortTaskHasFPUContext = pdTRUE;

    /* Consider initialising the FPSR here - but probably not necessary in
     * AArch64. */
}

#पूर्ण_अगर /* configUSE_TASK_FPU_SUPPORT */
/*-----------------------------------------------------------*/

व्योम vPortClearInterruptMask( UBaseType_t ux_New_Mask_मूल्य )
{
    अगर( ux_New_Mask_मूल्य == pdFALSE )
    {
        portCLEAR_INTERRUPT_MASK();
    }
}
/*-----------------------------------------------------------*/

UBaseType_t uxPortSetInterruptMask( व्योम )
{
    uint32_t ulReturn;
    uint64_t ullPMRValue;

    /* Interrupt in the CPU must be turned off while the ICCPMR is being
     * updated. */
    portDISABLE_INTERRUPTS();
    /* s3_0_c4_c6_0 is ICC_PMR_EL1. */
    __asm अस्थिर ( "MRS %0, s3_0_c4_c6_0" : "=r" ( ullPMRValue ) );

    अगर( ullPMRValue == ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    अन्यथा
    {
        ulReturn = pdFALSE;
        /* s3_0_c4_c6_0 is ICC_PMR_EL1. */
        __asm अस्थिर ( "MSR s3_0_c4_c6_0, %0      \n"
                         "DSB SY                    \n"
                         "ISB SY                    \n"
                         ::"r" ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) : "memory" );
    }

    portENABLE_INTERRUPTS();

    वापस ulReturn;
}
/*-----------------------------------------------------------*/

#अगर ( configASSERT_DEFINED == 1 )

    व्योम vPortValidateInterruptPriority( व्योम )
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
         * interrupt entry is as fast and simple as possible. */
        uint64_t ullRunningInterruptPriority;
        /* s3_0_c12_c11_3 is ICC_RPR_EL1. */
        __asm अस्थिर ( "MRS %0, s3_0_c12_c11_3" : "=r" ( ullRunningInterruptPriority ) );

        configASSERT( ullRunningInterruptPriority >= ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) );
    }

#पूर्ण_अगर /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

व्योम vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR )
{
    ( व्योम ) ulICCIAR;
    configASSERT( ( अस्थिर व्योम * ) शून्य );
}
