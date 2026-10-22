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
#अन्तर्भाव <stdlib.h>

/* Scheduler includes. */
#अन्तर्भाव "FreeRTOS.h"
#अन्तर्भाव "task.h"

#ifndef configINTERRUPT_CONTROLLER_BASE_ADDRESS
    #error "configINTERRUPT_CONTROLLER_BASE_ADDRESS must be defined. See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
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

#जइ configMAX_API_CALL_INTERRUPT_PRIORITY == 0
    #error "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#endif

#जइ configMAX_API_CALL_INTERRUPT_PRIORITY > configUNIQUE_INTERRUPT_PRIORITIES
    #error "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#endif

#जइ configUSE_PORT_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #जइ ( configMAX_PRIORITIES > 32 )
        #error "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #endif
#endif /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#जइ configMAX_API_CALL_INTERRUPT_PRIORITY <= ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )
    #error "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#endif

/* Some vendor specific files default configCLEAR_TICK_INTERRUPT() in
 * portmacro.h. */
#ifndef configCLEAR_TICK_INTERRUPT
    #define configCLEAR_TICK_INTERRUPT()
#endif

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#define portNO_CRITICAL_NESTING          ( ( size_t ) 0 )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#define port_UNMASK_मानम्                 ( 0xFFUL )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#define portNO_FLOATING_POINT_CONTEXT    ( ( राशिः_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#define portSP_ELx                       ( ( राशिः_Type_t ) 0x01 )
#define portSP_EL0                       ( ( राशिः_Type_t ) 0x00 )

#जइ defined( GUEST )
    #define portEL1                      ( ( राशिः_Type_t ) 0x04 )
    #define portINITIAL_PSTATE           ( portEL1 | portSP_EL0 )
#अण्णहा
    #define portEL3                      ( ( राशिः_Type_t ) 0x0c )
    /* At the time of writing, the BSP only supports EL3. */
    #define portINITIAL_PSTATE           ( portEL3 | portSP_EL0 )
#endif


/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#define port_द्विमान_POINT_BITS      ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#define portAPSR_MODE_BITS_MASK    ( 0x0C )

/* The I bit in the DAIF bits. */
#define portDAIF_I                 ( 0x80 )

/* Macro to unmask all interrupt priorities. */
#define portCLEAR_INTERRUPT_MASK()                            \
    {                                                         \
        portDISABLE_INTERRUPTS();                             \
        portICCPMR_PRIORITY_MASK_REGISTER = port_UNMASK_मानम्; \
        __asm चञ्चल ( "DSB SY     \n"                      \
                         "ISB SY     \n" );                   \
        portENABLE_INTERRUPTS();                              \
    }

/* Hardware specifics used when sanity checking the configuration. */
#define portINTERRUPT_PRIORITY_REGISTER_OFFSET    0x400UL
#define port_MAX_8_BIT_मानम्                       ( ( uint8_t ) 0xff )
#define portBIT_0_SET                             ( ( uint8_t ) 0x01 )

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit registers.*/
#define port_FPU_REGISTER_शब्दाः     ( 32 * 2 )

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
बाह्य शून्य vPortRestoreTaskContext( शून्य );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
चञ्चल uint64_t ullCriticalNesting = 9999ULL;

/* Saved as part of the task context.  If ullPortTaskHasFPUContext is non-zero
 * then floating point context must be saved and restored for the task. */
uint64_t ullPortTaskHasFPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint64_t ullPortYieldRequired = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint64_t ullPortInterruptNesting = 0;

/* Used in the ASM code. */
__attribute__( ( used ) ) ध्रुव uint64_t ullICCEOIR = portICCEOIR_END_OF_INTERRUPT_REGISTER_ADDRESS;
__attribute__( ( used ) ) ध्रुव uint64_t ullICCIAR = portICCIAR_INTERRUPT_ACKNOWLEDGE_REGISTER_ADDRESS;
__attribute__( ( used ) ) ध्रुव uint64_t ullICCPMR = portICCPMR_PRIORITY_MASK_REGISTER_ADDRESS;
__attribute__( ( used ) ) ध्रुव uint64_t ullMaxAPIPriorityMask = ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
राशिः_Type_t * px_Port_Initialise_राशिः( राशिः_Type_t * px_शिखरम्_Of_राशिः,
                                     TaskFunction_t pxCode,
                                     शून्य * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First all the general purpose registers. */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x0101010101010101ULL;        /* R1 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) pvParameters; /* R0 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x0303030303030303ULL;        /* R3 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x0202020202020202ULL;        /* R2 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x0505050505050505ULL;        /* R5 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x0404040404040404ULL;        /* R4 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x0707070707070707ULL;        /* R7 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x0606060606060606ULL;        /* R6 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x0909090909090909ULL;        /* R9 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x0808080808080808ULL;        /* R8 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x1111111111111111ULL;        /* R11 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x1010101010101010ULL;        /* R10 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x1313131313131313ULL;        /* R13 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x1212121212121212ULL;        /* R12 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x1515151515151515ULL;        /* R15 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x1414141414141414ULL;        /* R14 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x1717171717171717ULL;        /* R17 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x1616161616161616ULL;        /* R16 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x1919191919191919ULL;        /* R19 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x1818181818181818ULL;        /* R18 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x2121212121212121ULL;        /* R21 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x2020202020202020ULL;        /* R20 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x2323232323232323ULL;        /* R23 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x2222222222222222ULL;        /* R22 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x2525252525252525ULL;        /* R25 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x2424242424242424ULL;        /* R24 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x2727272727272727ULL;        /* R27 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x2626262626262626ULL;        /* R26 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x2929292929292929ULL;        /* R29 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = 0x2828282828282828ULL;        /* R28 */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x00;         /* XZR - has no effect, used so there are an even number of registers. */
    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) 0x00;         /* R30 - procedure call link register. */

    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = portINITIAL_PSTATE;

    px_शिखरम्_Of_राशिः--;
    *px_शिखरम्_Of_राशिः = ( राशिः_Type_t ) pxCode; /* Exception return address. */

    #जइ ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_शिखरम्_Of_राशिः--;
        *px_शिखरम्_Of_राशिः = portNO_CRITICAL_NESTING;

        /* The task will start without a floating point context.  A task that
         * uses the floating point hardware must call vPortTaskUsesFPU() before
         * executing any floating point instructions. */
        px_शिखरम्_Of_राशिः--;
        *px_शिखरम्_Of_राशिः = portNO_FLOATING_POINT_CONTEXT;
    }
    #नोचेद्यदि ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /* The task will start with a floating point context.  Leave enough
         * space for the registers - and ensure they are initialised to 0. */
        px_शिखरम्_Of_राशिः -= port_FPU_REGISTER_शब्दाः;
        memset( px_शिखरम्_Of_राशिः, 0x00, port_FPU_REGISTER_शब्दाः * परिमाण( राशिः_Type_t ) );

        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_शिखरम्_Of_राशिः--;
        *px_शिखरम्_Of_राशिः = portNO_CRITICAL_NESTING;

        px_शिखरम्_Of_राशिः--;
        *px_शिखरम्_Of_राशिः = pdTRUE;
        ullPortTaskHasFPUContext = pdTRUE;
    }
    #अण्णहा /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */
    {
        #error "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
    }
    #endif /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */

    प्रत्यागम px_शिखरम्_Of_राशिः;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( शून्य )
{
    uint32_t ulAPSR;

    #जइ ( configASSERT_DEFINED == 1 )
    {
        चञ्चल uint8_t ucOriginalPriority;
        चञ्चल uint8_t * ध्रुव pucFirstUserPriorityRegister = ( चञ्चल uint8_t * ध्रुव ) ( configINTERRUPT_CONTROLLER_BASE_ADDRESS + portINTERRUPT_PRIORITY_REGISTER_OFFSET );
        चञ्चल uint8_t uc_Max_Priority_मानम्;

        /* Determine how many priority bits are implemented in the GIC.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        ucOriginalPriority = *pucFirstUserPriorityRegister;

        /* Determine the number of priority bits available.  First write to
         * all possible bits. */
        *pucFirstUserPriorityRegister = port_MAX_8_BIT_मानम्;

        /* Read the value back to see how many bits stuck. */
        uc_Max_Priority_मानम् = *pucFirstUserPriorityRegister;

        /* Shift to the least significant bits. */
        जाव( ( uc_Max_Priority_मानम् & portBIT_0_SET ) != portBIT_0_SET )
        {
            uc_Max_Priority_मानम् >>= ( uint8_t ) 0x01;
        }

        /* Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value. */

        configASSERT( uc_Max_Priority_मानम् >= portLOWEST_INTERRUPT_PRIORITY );


        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *pucFirstUserPriorityRegister = ucOriginalPriority;
    }
    #endif /* configASSERT_DEFINED */


    /* At the time of writing, the BSP only supports EL3. */
    __asm चञ्चल ( "MRS %0, CurrentEL" : "=r" ( ulAPSR ) );
    ulAPSR &= portAPSR_MODE_BITS_MASK;

    #जइ defined( GUEST )
    #warning "Building for execution as a guest under XEN. THIS IS NOT A FULLY TESTED PATH."
        configASSERT( ulAPSR == portEL1 );

        जइ( ulAPSR == portEL1 )
    #अण्णहा
        configASSERT( ulAPSR == portEL3 );

        जइ( ulAPSR == portEL3 )
    #endif
    {
        /* Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information. */
        configASSERT( ( port_ICCBPR_द्विमान_POINT_REGISTER & port_द्विमान_POINT_BITS ) <= port_MAX_द्विमान_POINT_मानम् );

        जइ( ( port_ICCBPR_द्विमान_POINT_REGISTER & port_द्विमान_POINT_BITS ) <= port_MAX_द्विमान_POINT_मानम् )
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
    }

    प्रत्यागम 0;
}
/*-----------------------------------------------------------*/

शून्य vPortEndScheduler( शून्य )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ullCriticalNesting == 1000ULL );
}
/*-----------------------------------------------------------*/

शून्य vPortEnterCritical( शून्य )
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
    जइ( ullCriticalNesting == 1ULL )
    {
        configASSERT( ullPortInterruptNesting == 0 );
    }
}
/*-----------------------------------------------------------*/

शून्य vPortExitCritical( शून्य )
{
    जइ( ullCriticalNesting > portNO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ullCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        जइ( ullCriticalNesting == portNO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            portCLEAR_INTERRUPT_MASK();
        }
    }
}
/*-----------------------------------------------------------*/

शून्य FreeRTOS_Tick_Handler( शून्य )
{
    /* Must be the lowest possible priority. */
    #जइ !defined( QEMU )
    {
        configASSERT( portICCRPR_RUNNING_PRIORITY_REGISTER == ( uint32_t ) ( portLOWEST_USABLE_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) );
    }
    #endif

    /* Interrupts should not be enabled before this point. */
    #जइ ( configASSERT_DEFINED == 1 )
    {
        uint32_t ulMaskBits;

        __asm चञ्चल ( "mrs %0, daif" : "=r" ( ulMaskBits )::"memory" );
        configASSERT( ( ulMaskBits & portDAIF_I ) != 0 );
    }
    #endif /* configASSERT_DEFINED */

    /* Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated. */
    portICCPMR_PRIORITY_MASK_REGISTER = ( uint32_t ) ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT );
    __asm चञ्चल ( "dsb sy     \n"
                     "isb sy     \n" ::: "memory" );

    /* Ok to enable interrupts after the interrupt source has been cleared. */
    configCLEAR_TICK_INTERRUPT();
    portENABLE_INTERRUPTS();

    /* Increment the RTOS tick. */
    जइ( xTaskIncrementTick() != pdFALSE )
    {
        ullPortYieldRequired = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    portCLEAR_INTERRUPT_MASK();
}
/*-----------------------------------------------------------*/

#जइ ( configUSE_TASK_FPU_SUPPORT != 2 )

    शून्य vPortTaskUsesFPU( शून्य )
    {
        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        ullPortTaskHasFPUContext = pdTRUE;

        /* Consider initialising the FPSR here - but probably not necessary in
         * AArch64. */
    }

#endif /* configUSE_TASK_FPU_SUPPORT */
/*-----------------------------------------------------------*/

शून्य vPortClearInterruptMask( UBaseType_t ux_New_Mask_मानम् )
{
    जइ( ux_New_Mask_मानम् == pdFALSE )
    {
        portCLEAR_INTERRUPT_MASK();
    }
}
/*-----------------------------------------------------------*/

UBaseType_t uxPortSetInterruptMask( शून्य )
{
    uint32_t ulReturn;

    /* Interrupt in the CPU must be turned off while the ICCPMR is being
     * updated. */
    portDISABLE_INTERRUPTS();

    जइ( portICCPMR_PRIORITY_MASK_REGISTER == ( uint32_t ) ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    अण्णहा
    {
        ulReturn = pdFALSE;
        portICCPMR_PRIORITY_MASK_REGISTER = ( uint32_t ) ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT );
        __asm चञ्चल ( "dsb sy     \n"
                         "isb sy     \n" ::: "memory" );
    }

    portENABLE_INTERRUPTS();

    प्रत्यागम ulReturn;
}
/*-----------------------------------------------------------*/

#जइ ( configASSERT_DEFINED == 1 )

    शून्य vPortValidateInterruptPriority( शून्य )
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
        configASSERT( portICCRPR_RUNNING_PRIORITY_REGISTER >= ( uint32_t ) ( configMAX_API_CALL_INTERRUPT_PRIORITY << portPRIORITY_SHIFT ) );

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
        configASSERT( ( port_ICCBPR_द्विमान_POINT_REGISTER & port_द्विमान_POINT_BITS ) <= port_MAX_द्विमान_POINT_मानम् );
    }

#endif /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/
