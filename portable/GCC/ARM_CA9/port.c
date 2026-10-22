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
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

/* Scheduler includes. */
#ಅನ್ತರ್ಭಾವ "FreeRTOS.h"
#ಅನ್ತರ್ಭಾವ "task.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಅಡಚಣೆ_CONTROLLER_ತಳ_ವಿಳಾಸ
    #ದೋಷ "configINTERRUPT_CONTROLLER_BASE_ADDRESS must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಅಡಚಣೆ_CONTROLLER_CPU_INTERFACE_ಸ್ಥಾನಾಂತರ
    #ದೋಷ "configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES
    #ದೋಷ "configUNIQUE_INTERRUPT_PRIORITIES must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ
    #ದೋಷ "configSETUP_TICK_INTERRUPT() must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#ಆದರೆ_ಅಂತ್ಯ /* configSETUP_TICK_INTERRUPT */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ
    #ದೋಷ "configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ == 0
    #ದೋಷ "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ > config_UNIQUE_ಅಡಚಣೆ_PRIORITIES
    #ದೋಷ "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ config_USE_ಪೋರ್ಟ್_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #ಆದರೆ ( configMAX_PRIORITIES > 32 )
        #ದೋಷ "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#ಆದರೆ config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ <= ( config_UNIQUE_ಅಡಚಣೆ_PRIORITIES / 2 )
    #ದೋಷ "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#ಆದರೆ_ಅಂತ್ಯ

/* Some vendor specific files default configCLEAR_TICK_INTERRUPT() in
 * portmacro.h. */
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_CLEAR_TICK_ಅಡಚಣೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು config_CLEAR_TICK_ಅಡಚಣೆ()
#ಆದರೆ_ಅಂತ್ಯ

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UNMASK_ಮೌಲ್ಯ                 ( 0xFFUL )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_FLOATING_ಬಿಂದು_CONTEXT    ( ( ರಾಶಿ_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_SPSR                 ( ( ರಾಶಿ_Type_t ) 0x1f ) /* System mode, ARM mode, IRQ enabled FIQ enabled. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್               ( ( ರಾಶಿ_Type_t ) 0x20 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅಡಚಣೆ_ENABLE_ಬಿಟ್         ( 0x80UL )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ವಿಳಾಸ           ( 0x01UL )

/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದ್ವಿಮಾನ_ಬಿಂದು_ಬಿಟ್ಟುಗಳು            ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APSR_ಬಹುಲಕ_ಬಿಟ್ಟುಗಳು_ಮುಖವಾಡ          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APSR_USER_ಬಹುಲಕ               ( 0x10 )

/* The critical section macros only mask interrupts up to an application
 * determined priority level.  Sometimes it is necessary to turn interrupt off in
 * the CPU itself before modifying certain hardware registers. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CPU_IRQ_DISABLE()                  \
    __asm ಅಸ್ಥಿರ ( "CPSID i" ::: "memory" ); \
    __asm ಅಸ್ಥಿರ ( "DSB" );                  \
    __asm ಅಸ್ಥಿರ ( "ISB" );

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CPU_IRQ_ENABLE()                   \
    __asm ಅಸ್ಥಿರ ( "CPSIE i" ::: "memory" ); \
    __asm ಅಸ್ಥಿರ ( "DSB" );                  \
    __asm ಅಸ್ಥಿರ ( "ISB" );


/* Macro to unmask all interrupt priorities. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ()                            \
    {                                                         \
        ಪೋರ್ಟ್_CPU_IRQ_DISABLE();                                \
        ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ರಿಜಿಸ್ಟರ್ = ಪೋರ್ಟ್_UNMASK_ಮೌಲ್ಯ; \
        __asm ಅಸ್ಥಿರ ( "DSB        \n"                      \
                         "ISB        \n" );                   \
        ಪೋರ್ಟ್_CPU_IRQ_ENABLE();                                 \
    }

#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅಡಚಣೆ_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್_ಸ್ಥಾನಾಂತರ    0x400UL
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_8_ಬಿಟ್_ಮೌಲ್ಯ                       ( ( uint8_t ) 0xff )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಬಿಟ್_0_ಗಣ                             ( ( uint8_t ) 0x01 )

/* Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case it messes up unwinding of the stack in the
 * debugger. */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ config_TASK_RETURN_ವಿಳಾಸ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ    config_TASK_RETURN_ವಿಳಾಸ
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ    prvTaskExitError
#ಆದರೆ_ಅಂತ್ಯ

/* The space on the stack required to hold the FPU registers.  This is 32 64-bit
 * registers, plus a 32-bit status register. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPU_ರಿಜಿಸ್ಟರ್_ಪದಗಳು    ( ( 32 * 2 ) + 1 )

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Restore_Task_Context( ಶೂನ್ಯ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ );

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
ಶೂನ್ಯ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR ) __attribute__( ( weak ) );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
ಅಸ್ಥಿರ uint32_t ulCriticalNesting = 9999UL;

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task. */
ಅಸ್ಥಿರ uint32_t ul_ಪೋರ್ಟ್_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
ಅಸ್ಥಿರ uint32_t ul_ಪೋರ್ಟ್_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
ಅಸ್ಥಿರ uint32_t ul_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting = 0UL;

/* Used in the asm file. */
__attribute__( ( ಬಳಸಿದ ) ) ಸ್ಥಿರಾಂಕ uint32_t ulICCIARAddress = ಪೋರ್ಟ್_ICCIAR_ಅಡಚಣೆ_ACKNOWLEDGE_ರಿಜಿಸ್ಟರ್_ವಿಳಾಸ;
__attribute__( ( ಬಳಸಿದ ) ) ಸ್ಥಿರಾಂಕ uint32_t ulICCEOIRAddress = ಪೋರ್ಟ್_ICCEOIR_ಕೊನೆ_ದ_ಅಡಚಣೆ_ರಿಜಿಸ್ಟರ್_ವಿಳಾಸ;
__attribute__( ( ಬಳಸಿದ ) ) ಸ್ಥಿರಾಂಕ uint32_t ulICCPMRAddress = ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ರಿಜಿಸ್ಟರ್_ವಿಳಾಸ;
__attribute__( ( ಬಳಸಿದ ) ) ಸ್ಥಿರಾಂಕ uint32_t ul_Max_APIPriority_ಮುಖವಾಡ = ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಖಾಲಿ;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಖಾಲಿ;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಖಾಲಿ;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_INITIAL_SPSR;

    ಆದರೆ( ( ( uint32_t ) px_ಸಂಕೇತ & ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ವಿಳಾಸ ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_ತುದಿ_ದ_ರಾಶಿ |= ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್;
    }

    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Next the return address, which in this case is the start of the task. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* Next all the registers other than the stack pointer. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) ಪೋರ್ಟ್_TASK_RETURN_ವಿಳಾಸ; /* R14 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x12121212;              /* R12 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x11111111;              /* R11 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x10101010;              /* R10 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x09090909;              /* R9 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x08080808;              /* R8 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x07070707;              /* R7 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x06060606;              /* R6 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x05050505;              /* R5 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x04040404;              /* R4 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x03030303;              /* R3 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x02020202;              /* R2 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x01010101;              /* R1 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;            /* R0 */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_CRITICAL_NESTING;

    #ಆದರೆ ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /* The task will start without a floating point context.  A task that
         * uses the floating point hardware must call vPortTaskUsesFPU() before
         * executing any floating point instructions. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_FLOATING_ಬಿಂದು_CONTEXT;
    }
    #ಅಥವಾಆದರೆ ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /* The task will start with a floating point context.  Leave enough
         * space for the registers - and ensure they are initialised to 0. */
        px_ತುದಿ_ದ_ರಾಶಿ -= ಪೋರ್ಟ್_FPU_ರಿಜಿಸ್ಟರ್_ಪದಗಳು;
        memset( px_ತುದಿ_ದ_ರಾಶಿ, 0x00, ಪೋರ್ಟ್_FPU_ರಿಜಿಸ್ಟರ್_ಪದಗಳು * ಗಾತ್ರ( ರಾಶಿ_Type_t ) );

        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = pdTRUE;
        ul_ಪೋರ್ಟ್_Task_Has_FPUContext = pdTRUE;
    }
    #ಇಲ್ಲದಿದ್ದರೆ /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */
    {
        #ದೋಷ "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
    }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ಸ್ಥಿರ ಶೂನ್ಯ prvTaskExitError( ಶೂನ್ಯ )
{
    /* A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error. */
    configASSERT( ul_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting == ~0UL );
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

    ಗಾಗಿ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    uint32_t ulAPSR;

    #ಆದರೆ ( configASSERT_DEFINED == 1 )
    {
        ಅಸ್ಥಿರ uint8_t uc_Original_ಆದ್ಯತೆ;
        ಅಸ್ಥಿರ uint8_t * ಸ್ಥಿರಾಂಕ puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ = ( ಅಸ್ಥಿರ uint8_t * ಸ್ಥಿರಾಂಕ ) ( config_ಅಡಚಣೆ_CONTROLLER_ತಳ_ವಿಳಾಸ + ಪೋರ್ಟ್_ಅಡಚಣೆ_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್_ಸ್ಥಾನಾಂತರ );
        ಅಸ್ಥಿರ uint8_t uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ;

        /* Determine how many priority bits are implemented in the GIC.
         *
         * Save the interrupt priority value that is about to be clobbered. */
        uc_Original_ಆದ್ಯತೆ = *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್;

        /* Determine the number of priority bits available.  First write to
         * all possible bits. */
        *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ = ಪೋರ್ಟ್_MAX_8_ಬಿಟ್_ಮೌಲ್ಯ;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ = *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್;

        /* Shift to the least significant bits. */
        ಆಗ( ( uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ & ಪೋರ್ಟ್_ಬಿಟ್_0_ಗಣ ) != ಪೋರ್ಟ್_ಬಿಟ್_0_ಗಣ )
        {
            uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ >>= ( uint8_t ) 0x01;
        }

        /* Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value. */
        configASSERT( uc_Max_ಆದ್ಯತೆ_ಮೌಲ್ಯ == ಪೋರ್ಟ್_ಅತಿಕಡಿಮೆ_ಅಡಚಣೆ_ಆದ್ಯತೆ );

        /* Restore the clobbered interrupt priority register to its original
         * value. */
        *puc_ಮೊದಲ_User_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ = uc_Original_ಆದ್ಯತೆ;
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */


    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    __asm ಅಸ್ಥಿರ ( "MRS %0, APSR" : "=r" ( ulAPSR )::"memory" );
    ulAPSR &= ಪೋರ್ಟ್_APSR_ಬಹುಲಕ_ಬಿಟ್ಟುಗಳು_ಮುಖವಾಡ;
    configASSERT( ulAPSR != ಪೋರ್ಟ್_APSR_USER_ಬಹುಲಕ );

    ಆದರೆ( ulAPSR != ಪೋರ್ಟ್_APSR_USER_ಬಹುಲಕ )
    {
        /* Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information. */
        configASSERT( ( ಪೋರ್ಟ್_ICCBPR_ದ್ವಿಮಾನ_ಬಿಂದು_ರಿಜಿಸ್ಟರ್ & ಪೋರ್ಟ್_ದ್ವಿಮಾನ_ಬಿಂದು_ಬಿಟ್ಟುಗಳು ) <= ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ );

        ಆದರೆ( ( ಪೋರ್ಟ್_ICCBPR_ದ್ವಿಮಾನ_ಬಿಂದು_ರಿಜಿಸ್ಟರ್ & ಪೋರ್ಟ್_ದ್ವಿಮಾನ_ಬಿಂದು_ಬಿಟ್ಟುಗಳು ) <= ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ )
        {
            /* Interrupts are turned off in the CPU itself to ensure tick does
             * not execute while the scheduler is being started.  Interrupts are
             * automatically turned back on in the CPU when the first task starts
             * executing. */
            ಪೋರ್ಟ್_CPU_IRQ_DISABLE();

            /* Start the timer that generates the tick ISR. */
            config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ();

            /* Start the first task executing. */
            v_ಪೋರ್ಟ್_Restore_Task_Context();
        }
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value.  prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address. */
    ( ಶೂನ್ಯ ) prvTaskExitError;
    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    ul_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ();

    /* Now that interrupts are disabled, ulCriticalNesting can be accessed
     * directly.  Increment ulCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ulCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    ಆದರೆ( ulCriticalNesting == 1 )
    {
        configASSERT( ul_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    ಆದರೆ( ulCriticalNesting > ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ulCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        ಆದರೆ( ulCriticalNesting == ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ();
        }
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ FreeRTOS_Tick_Handler( ಶೂನ್ಯ )
{
    /* Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated. */
    ಪೋರ್ಟ್_CPU_IRQ_DISABLE();
    ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ರಿಜಿಸ್ಟರ್ = ( uint32_t ) ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು );
    __asm ಅಸ್ಥಿರ ( "dsb        \n"
                     "isb        \n" ::: "memory" );
    ಪೋರ್ಟ್_CPU_IRQ_ENABLE();

    /* Increment the RTOS tick. */
    ಆದರೆ( xTaskIncrementTick() != pdFALSE )
    {
        ul_ಪೋರ್ಟ್_Yield_Required = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ();
    config_CLEAR_TICK_ಅಡಚಣೆ();
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TASK_FPU_SUPPORT != 2 )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU( ಶೂನ್ಯ )
    {
        uint32_t ulInitialFPSCR = 0;

        /* A task is registering the fact that it needs an FPU context.  Set the
         * FPU flag (which is saved as part of the task context). */
        ul_ಪೋರ್ಟ್_Task_Has_FPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        __asm ಅಸ್ಥಿರ ( "FMXR  FPSCR, %0" ::"r" ( ulInitialFPSCR ) : "memory" );
    }

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TASK_FPU_SUPPORT */
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( uint32_t ul_New_ಮುಖವಾಡ_ಮೌಲ್ಯ )
{
    ಆದರೆ( ul_New_ಮುಖವಾಡ_ಮೌಲ್ಯ == pdFALSE )
    {
        ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ();
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ( ಶೂನ್ಯ )
{
    uint32_t ulReturn;

    /* Interrupt in the CPU must be turned off while the ICCPMR is being
     * updated. */
    ಪೋರ್ಟ್_CPU_IRQ_DISABLE();

    ಆದರೆ( ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ರಿಜಿಸ್ಟರ್ == ( uint32_t ) ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        ulReturn = pdFALSE;
        ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ರಿಜಿಸ್ಟರ್ = ( uint32_t ) ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು );
        __asm ಅಸ್ಥಿರ ( "dsb        \n"
                         "isb        \n" ::: "memory" );
    }

    ಪೋರ್ಟ್_CPU_IRQ_ENABLE();

    ಹಿಂತಿರುಗಿ ulReturn;
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( configASSERT_DEFINED == 1 )

    ಶೂನ್ಯ v_ಪೋರ್ಟ್_Validate_ಅಡಚಣೆ_ಆದ್ಯತೆ( ಶೂನ್ಯ )
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
        configASSERT( ಪೋರ್ಟ್_ICCRPR_RUNNING_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ >= ( uint32_t ) ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) );

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
        configASSERT( ( ಪೋರ್ಟ್_ICCBPR_ದ್ವಿಮಾನ_ಬಿಂದು_ರಿಜಿಸ್ಟರ್ & ಪೋರ್ಟ್_ದ್ವಿಮಾನ_ಬಿಂದು_ಬಿಟ್ಟುಗಳು ) <= ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ );
    }

#ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR )
{
    ( ಶೂನ್ಯ ) ulICCIAR;
    configASSERT( ( ಅಸ್ಥಿರ ಶೂನ್ಯ * ) ಖಾಲಿ );
}
