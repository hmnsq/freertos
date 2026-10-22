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
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

/* Scheduler includes. */
#అన్తర్భావ "FreeRTOS.h"
#అన్తర్భావ "task.h"

#నిర్వచితం_కాకపోతే config_అంతరాయం_CONTROLLER_పునాది_చిరునామా
    #దోషం "configINTERRUPT_CONTROLLER_BASE_ADDRESS must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_అంతరాయం_CONTROLLER_CPU_INTERFACE_స్థానభ్రంశం
    #దోషం "configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_UNIQUE_అంతరాయం_PRIORITIES
    #దోషం "configUNIQUE_INTERRUPT_PRIORITIES must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే config_అమరిక_TICK_అంతరాయం
    #దోషం "configSETUP_TICK_INTERRUPT() must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#అయితే_ముగింపు /* configSETUP_TICK_INTERRUPT */

#నిర్వచితం_కాకపోతే config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత
    #దోషం "configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#అయితే_ముగింపు

#ఒకవేళ config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత == 0
    #దోషం "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#అయితే_ముగింపు

#ఒకవేళ config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత > config_UNIQUE_అంతరాయం_PRIORITIES
    #దోషం "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#అయితే_ముగింపు

#ఒకవేళ config_USE_పోర్టు_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #ఒకవేళ ( configMAX_PRIORITIES > 32 )
        #దోషం "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #అయితే_ముగింపు
#అయితే_ముగింపు /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#ఒకవేళ config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత <= ( config_UNIQUE_అంతరాయం_PRIORITIES / 2 )
    #దోషం "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#అయితే_ముగింపు

/* Some vendor specific files default configCLEAR_TICK_INTERRUPT() in
 * portmacro.h. */
#నిర్వచితం_కాకపోతే config_CLEAR_TICK_అంతరాయం
    #నిర్వచించు config_CLEAR_TICK_అంతరాయం()
#అయితే_ముగింపు

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#నిర్వచించు పోర్టు_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#నిర్వచించు పోర్టు_UNMASK_విలువ                 ( 0xFFUL )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#నిర్వచించు పోర్టు_NO_FLOATING_బిందువు_CONTEXT    ( ( దొంతర_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#నిర్వచించు పోర్టు_INITIAL_SPSR                 ( ( దొంతర_Type_t ) 0x1f ) /* System mode, ARM mode, IRQ enabled FIQ enabled. */
#నిర్వచించు పోర్టు_THUMB_బహుళకం_బిట్టు               ( ( దొంతర_Type_t ) 0x20 )
#నిర్వచించు పోర్టు_అంతరాయం_ENABLE_బిట్టు         ( 0x80UL )
#నిర్వచించు పోర్టు_THUMB_బహుళకం_చిరునామా           ( 0x01UL )

/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#నిర్వచించు పోర్టు_ద్విమాన_బిందువు_బిట్లు            ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#నిర్వచించు పోర్టు_APSR_బహుళకం_బిట్లు_ముసుగు          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#నిర్వచించు పోర్టు_APSR_USER_బహుళకం               ( 0x10 )

/* The critical section macros only mask interrupts up to an application
 * determined priority level.  Sometimes it is necessary to turn interrupt off in
 * the CPU itself before modifying certain hardware registers. */
#నిర్వచించు పోర్టు_CPU_IRQ_DISABLE()                  \
    __asm అస్థిర ( "CPSID i" ::: "memory" ); \
    __asm అస్థిర ( "DSB" );                  \
    __asm అస్థిర ( "ISB" );

#నిర్వచించు పోర్టు_CPU_IRQ_ENABLE()                   \
    __asm అస్థిర ( "CPSIE i" ::: "memory" ); \
    __asm అస్థిర ( "DSB" );                  \
    __asm అస్థిర ( "ISB" );


/* Macro to unmask all interrupt priorities. */
#నిర్వచించు పోర్టు_CLEAR_అంతరాయం_ముసుగు()                            \
    {                                                         \
        పోర్టు_CPU_IRQ_DISABLE();                                \
        పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_రిజిస్టరు = పోర్టు_UNMASK_విలువ; \
        __asm అస్థిర ( "DSB        \n"                      \
                         "ISB        \n" );                   \
        పోర్టు_CPU_IRQ_ENABLE();                                 \
    }

#నిర్వచించు పోర్టు_అంతరాయం_ప్రాధాన్యత_రిజిస్టరు_స్థానభ్రంశం    0x400UL
#నిర్వచించు పోర్టు_MAX_8_బిట్టు_విలువ                       ( ( uint8_t ) 0xff )
#నిర్వచించు పోర్టు_బిట్టు_0_సమితి                             ( ( uint8_t ) 0x01 )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#నిర్వచితమైతే config_TASK_RETURN_చిరునామా
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా    config_TASK_RETURN_చిరునామా
#లేకపోతే
    #నిర్వచించు పోర్టు_TASK_RETURN_చిరునామా    prvTaskExitError
#అయితే_ముగింపు

/* The space on the stack required to hold the FPU registers.  This is 32 64-bit
 * registers, plus a 32-bit status register. */
#నిర్వచించు పోర్టు_FPU_రిజిస్టరు_పదాలు    ( ( 32 * 2 ) + 1 )

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
బాహ్య శూన్య v_పోర్టు_Restore_Task_Context( శూన్య );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
స్థిర శూన్య prvTaskExitError( శూన్య );

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
శూన్య vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR ) __attribute__( ( weak ) );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
అస్థిర uint32_t ulCriticalNesting = 9999UL;

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task. */
అస్థిర uint32_t ul_పోర్టు_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
అస్థిర uint32_t ul_పోర్టు_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
అస్థిర uint32_t ul_పోర్టు_అంతరాయం_Nesting = 0UL;

/* Used in the asm file. */
__attribute__( ( వాడిన ) ) స్థిరరాశి uint32_t ulICCIARAddress = పోర్టు_ICCIAR_అంతరాయం_ACKNOWLEDGE_రిజిస్టరు_చిరునామా;
__attribute__( ( వాడిన ) ) స్థిరరాశి uint32_t ulICCEOIRAddress = పోర్టు_ICCEOIR_చివర_యొక్క_అంతరాయం_రిజిస్టరు_చిరునామా;
__attribute__( ( వాడిన ) ) స్థిరరాశి uint32_t ulICCPMRAddress = పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_రిజిస్టరు_చిరునామా;
__attribute__( ( వాడిన ) ) స్థిరరాశి uint32_t ul_Max_APIPriority_ముసుగు = ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
దొంతర_Type_t * px_పోర్టు_Initialise_దొంతర( దొంతర_Type_t * px_శిఖరం_యొక్క_దొంతర,
                                     TaskFunction_t px_సంకేతం,
                                     శూన్య * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ఖాళీ;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ఖాళీ;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) ఖాళీ;
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_INITIAL_SPSR;

    ఒకవేళ( ( ( uint32_t ) px_సంకేతం & పోర్టు_THUMB_బహుళకం_చిరునామా ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_శిఖరం_యొక్క_దొంతర |= పోర్టు_THUMB_బహుళకం_బిట్టు;
    }

    px_శిఖరం_యొక్క_దొంతర--;

    /* Next the return address, which in this case is the start of the task. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) px_సంకేతం;
    px_శిఖరం_యొక్క_దొంతర--;

    /* Next all the registers other than the stack pointer. */
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) పోర్టు_TASK_RETURN_చిరునామా; /* R14 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x12121212;              /* R12 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x11111111;              /* R11 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x10101010;              /* R10 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x09090909;              /* R9 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x08080808;              /* R8 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x07070707;              /* R7 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x06060606;              /* R6 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x05050505;              /* R5 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x04040404;              /* R4 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x03030303;              /* R3 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x02020202;              /* R2 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) 0x01010101;              /* R1 */
    px_శిఖరం_యొక్క_దొంతర--;
    *px_శిఖరం_యొక్క_దొంతర = ( దొంతర_Type_t ) pvParameters;            /* R0 */
    px_శిఖరం_యొక్క_దొంతర--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_CRITICAL_NESTING;

    #ఒకవేళ ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /* The task will start without a floating point context.  A task that
         * uses the floating point hardware must call vPortTaskUsesFPU() before
         * executing any floating point instructions. */
        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = పోర్టు_NO_FLOATING_బిందువు_CONTEXT;
    }
    #లేదావేళ ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /* The task will start with a floating point context.  Leave enough
         * space for the registers - and ensure they are initialised to 0. */
        px_శిఖరం_యొక్క_దొంతర -= పోర్టు_FPU_రిజిస్టరు_పదాలు;
        memset( px_శిఖరం_యొక్క_దొంతర, 0x00, పోర్టు_FPU_రిజిస్టరు_పదాలు * పరిమాణం( దొంతర_Type_t ) );

        px_శిఖరం_యొక్క_దొంతర--;
        *px_శిఖరం_యొక్క_దొంతర = pdTRUE;
        ul_పోర్టు_Task_Has_FPUContext = pdTRUE;
    }
    #లేకపోతే /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */
    {
        #దోషం "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
    }
    #అయితే_ముగింపు /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */

    తిరిగి px_శిఖరం_యొక్క_దొంతర;
}
/*-----------------------------------------------------------*/

స్థిర శూన్య prvTaskExitError( శూన్య )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ul_పోర్టు_అంతరాయం_Nesting == ~0UL );
    పోర్టు_DISABLE_INTERRUPTS();

    కొరకు( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

పునాది_Type_t x_పోర్టు_ప్రారంభం_Scheduler( శూన్య )
{
    uint32_t ulAPSR;

    #ఒకవేళ ( configASSERT_DEFINED == 1 )
    {
        అస్థిర uint8_t uc_Original_ప్రాధాన్యత;
        అస్థిర uint8_t * స్థిరరాశి puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = ( అస్థిర uint8_t * స్థిరరాశి ) ( config_అంతరాయం_CONTROLLER_పునాది_చిరునామా + పోర్టు_అంతరాయం_ప్రాధాన్యత_రిజిస్టరు_స్థానభ్రంశం );
        అస్థిర uint8_t uc_Max_ప్రాధాన్యత_విలువ;

        /* Determine how many priority bits are implemented in the GIC.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ప్రాధాన్యత = *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు;

        /* Determine the number of priority bits available.  First write to
         * all possible bits. */
        *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = పోర్టు_MAX_8_బిట్టు_విలువ;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ప్రాధాన్యత_విలువ = *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు;

        /* Shift to the least significant bits. */
        అయితే( ( uc_Max_ప్రాధాన్యత_విలువ & పోర్టు_బిట్టు_0_సమితి ) != పోర్టు_బిట్టు_0_సమితి )
        {
            uc_Max_ప్రాధాన్యత_విలువ >>= ( uint8_t ) 0x01;
        }

        /* Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value. */
        configASSERT( uc_Max_ప్రాధాన్యత_విలువ == పోర్టు_అత్యల్ప_అంతరాయం_ప్రాధాన్యత );

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_మొదటి_User_ప్రాధాన్యత_రిజిస్టరు = uc_Original_ప్రాధాన్యత;
    }
    #అయితే_ముగింపు /* configASSERT_DEFINED */


    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    __asm అస్థిర ( "MRS %0, APSR" : "=r" ( ulAPSR )::"memory" );
    ulAPSR &= పోర్టు_APSR_బహుళకం_బిట్లు_ముసుగు;
    configASSERT( ulAPSR != పోర్టు_APSR_USER_బహుళకం );

    ఒకవేళ( ulAPSR != పోర్టు_APSR_USER_బహుళకం )
    {
        /* Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information. */
        configASSERT( ( పోర్టు_ICCBPR_ద్విమాన_బిందువు_రిజిస్టరు & పోర్టు_ద్విమాన_బిందువు_బిట్లు ) <= పోర్టు_MAX_ద్విమాన_బిందువు_విలువ );

        ఒకవేళ( ( పోర్టు_ICCBPR_ద్విమాన_బిందువు_రిజిస్టరు & పోర్టు_ద్విమాన_బిందువు_బిట్లు ) <= పోర్టు_MAX_ద్విమాన_బిందువు_విలువ )
        {
            /* Interrupts are turned off in the CPU itself to ensure tick does
             * not execute while the scheduler is being started.  Interrupts are
             * automatically turned back on in the CPU when the first task starts
             * executing. */
            పోర్టు_CPU_IRQ_DISABLE();

            /* Start the timer that generates the tick ISR. */
            config_అమరిక_TICK_అంతరాయం();

            /* Start the first task executing. */
            v_పోర్టు_Restore_Task_Context();
        }
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value.  prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( శూన్య ) prvTaskExitError;
    తిరిగి 0;
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_చివర_Scheduler( శూన్య )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Enter_Critical( శూన్య )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    ul_పోర్టు_సమితి_అంతరాయం_ముసుగు();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    ఒకవేళ( ulCriticalNesting == 1 )
    {
        configASSERT( ul_పోర్టు_అంతరాయం_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Exit_Critical( శూన్య )
{
    ఒకవేళ( ulCriticalNesting > పోర్టు_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        ఒకవేళ( ulCriticalNesting == పోర్టు_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            పోర్టు_CLEAR_అంతరాయం_ముసుగు();
        }
    }
}
/*-----------------------------------------------------------*/

శూన్య FreeRTOS_Tick_Handler( శూన్య )
{
    /* Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated. */
    పోర్టు_CPU_IRQ_DISABLE();
    పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_రిజిస్టరు = ( uint32_t ) ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు );
    __asm అస్థిర ( "dsb        \n"
                     "isb        \n" ::: "memory" );
    పోర్టు_CPU_IRQ_ENABLE();

    /* Increment the RTOS tick. */
    ఒకవేళ( xTaskIncrementTick() != pdFALSE )
    {
        ul_పోర్టు_Yield_Required = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    పోర్టు_CLEAR_అంతరాయం_ముసుగు();
    config_CLEAR_TICK_అంతరాయం();
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configUSE_TASK_FPU_SUPPORT != 2 )

    శూన్య v_పోర్టు_Task_ఉపయోగిస్తుంది_FPU( శూన్య )
    {
        uint32_t ulInitialFPSCR = 0;

        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        ul_పోర్టు_Task_Has_FPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        __asm అస్థిర ( "FMXR  FPSCR, %0" ::"r" ( ulInitialFPSCR ) : "memory" );
    }

#అయితే_ముగింపు /* configUSE_TASK_FPU_SUPPORT */
/*-----------------------------------------------------------*/

శూన్య v_పోర్టు_Clear_అంతరాయం_ముసుగు( uint32_t ul_New_ముసుగు_విలువ )
{
    ఒకవేళ( ul_New_ముసుగు_విలువ == pdFALSE )
    {
        పోర్టు_CLEAR_అంతరాయం_ముసుగు();
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_పోర్టు_సమితి_అంతరాయం_ముసుగు( శూన్య )
{
    uint32_t ulReturn;

    /* Interrupt in the CPU must be turned off while the ICCPMR is being
     * updated. */
    పోర్టు_CPU_IRQ_DISABLE();

    ఒకవేళ( పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_రిజిస్టరు == ( uint32_t ) ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    లేకపోతే
    {
        ulReturn = pdFALSE;
        పోర్టు_ICCPMR_ప్రాధాన్యత_ముసుగు_రిజిస్టరు = ( uint32_t ) ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు );
        __asm అస్థిర ( "dsb        \n"
                         "isb        \n" ::: "memory" );
    }

    పోర్టు_CPU_IRQ_ENABLE();

    తిరిగి ulReturn;
}
/*-----------------------------------------------------------*/

#ఒకవేళ ( configASSERT_DEFINED == 1 )

    శూన్య v_పోర్టు_Validate_అంతరాయం_ప్రాధాన్యత( శూన్య )
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
        configASSERT( పోర్టు_ICCRPR_RUNNING_ప్రాధాన్యత_రిజిస్టరు >= ( uint32_t ) ( config_MAX_API_CALL_అంతరాయం_ప్రాధాన్యత << పోర్టు_ప్రాధాన్యత_జరుపు ) );

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
        configASSERT( ( పోర్టు_ICCBPR_ద్విమాన_బిందువు_రిజిస్టరు & పోర్టు_ద్విమాన_బిందువు_బిట్లు ) <= పోర్టు_MAX_ద్విమాన_బిందువు_విలువ );
    }

#అయితే_ముగింపు /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

శూన్య vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR )
{
    ( శూన్య ) ulICCIAR;
    configASSERT( ( అస్థిర శూన్య * ) ఖాళీ );
}
