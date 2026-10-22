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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ config_CLEAR_TICK_ಅಡಚಣೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು config_CLEAR_TICK_ಅಡಚಣೆ()
#ಆದರೆ_ಅಂತ್ಯ

/* The number of bits to shift for an interrupt priority is dependent on the
 * number of bits implemented by the interrupt controller. */
#ಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 16
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            4
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    3
#ಅಥವಾಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 32
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            3
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    2
#ಅಥವಾಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 64
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            2
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    1
#ಅಥವಾಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 128
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            1
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    0
#ಅಥವಾಆದರೆ config_UNIQUE_ಅಡಚಣೆ_PRIORITIES == 256
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು            0
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ    0
#ಇಲ್ಲದಿದ್ದರೆ /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */
    #ದೋಷ "Invalid configUNIQUE_INTERRUPT_PRIORITIES setting.  configUNIQUE_INTERRUPT_PRIORITIES must be set to the number of unique priorities implemented by the target hardware"
#ಆದರೆ_ಅಂತ್ಯ /* if configUNIQUE_INTERRUPT_PRIORITIES == 16 */

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_NESTING                              ( ( uint32_t ) 0 )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_UNMASK_ಮೌಲ್ಯ                                     ( 0xFFUL )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_FLOATING_ಬಿಂದು_CONTEXT                        ( ( ರಾಶಿ_Type_t ) 0 )

/* Interrupt controller access addresses. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ಸ್ಥಾನಾಂತರ                      ( 0x04 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ICCIAR_ಅಡಚಣೆ_ACKNOWLEDGE_ಸ್ಥಾನಾಂತರ              ( 0x0C )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ICCEOIR_ಕೊನೆ_ದ_ಅಡಚಣೆ_ಸ್ಥಾನಾಂತರ                  ( 0x10 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ICCBPR_ದ್ವಿಮಾನ_ಬಿಂದು_ಸ್ಥಾನಾಂತರ                       ( 0x08 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ICCRPR_RUNNING_ಆದ್ಯತೆ_ಸ್ಥಾನಾಂತರ                   ( 0x14 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ಅಡಚಣೆ_CONTROLLER_CPU_INTERFACE_ವಿಳಾಸ       ( config_ಅಡಚಣೆ_CONTROLLER_ತಳ_ವಿಳಾಸ + config_ಅಡಚಣೆ_CONTROLLER_CPU_INTERFACE_ಸ್ಥಾನಾಂತರ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ರಿಜಿಸ್ಟರ್                    ( *( ( ಅಸ್ಥಿರ uint32_t * ) ( ಪೋರ್ಟ್_ಅಡಚಣೆ_CONTROLLER_CPU_INTERFACE_ವಿಳಾಸ + ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ಸ್ಥಾನಾಂತರ ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ICCIAR_ಅಡಚಣೆ_ACKNOWLEDGE_ರಿಜಿಸ್ಟರ್_ವಿಳಾಸ    ( ಪೋರ್ಟ್_ಅಡಚಣೆ_CONTROLLER_CPU_INTERFACE_ವಿಳಾಸ + ಪೋರ್ಟ್_ICCIAR_ಅಡಚಣೆ_ACKNOWLEDGE_ಸ್ಥಾನಾಂತರ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ICCEOIR_ಕೊನೆ_ದ_ಅಡಚಣೆ_ರಿಜಿಸ್ಟರ್_ವಿಳಾಸ        ( ಪೋರ್ಟ್_ಅಡಚಣೆ_CONTROLLER_CPU_INTERFACE_ವಿಳಾಸ + ಪೋರ್ಟ್_ICCEOIR_ಕೊನೆ_ದ_ಅಡಚಣೆ_ಸ್ಥಾನಾಂತರ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ರಿಜಿಸ್ಟರ್_ವಿಳಾಸ            ( ಪೋರ್ಟ್_ಅಡಚಣೆ_CONTROLLER_CPU_INTERFACE_ವಿಳಾಸ + ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ಸ್ಥಾನಾಂತರ )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ICCBPR_ದ್ವಿಮಾನ_ಬಿಂದು_ರಿಜಿಸ್ಟರ್                     ( *( ( ಸ್ಥಿರಾಂಕ ಅಸ್ಥಿರ uint32_t * ) ( ಪೋರ್ಟ್_ಅಡಚಣೆ_CONTROLLER_CPU_INTERFACE_ವಿಳಾಸ + ಪೋರ್ಟ್_ICCBPR_ದ್ವಿಮಾನ_ಬಿಂದು_ಸ್ಥಾನಾಂತರ ) ) )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ICCRPR_RUNNING_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್                 ( *( ( ಸ್ಥಿರಾಂಕ ಅಸ್ಥಿರ uint32_t * ) ( ಪೋರ್ಟ್_ಅಡಚಣೆ_CONTROLLER_CPU_INTERFACE_ವಿಳಾಸ + ಪೋರ್ಟ್_ICCRPR_RUNNING_ಆದ್ಯತೆ_ಸ್ಥಾನಾಂತರ ) ) )

/* Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_ದ್ವಿಮಾನ_ಬಿಂದು_ಬಿಟ್ಟುಗಳು                                ( ( uint8_t ) 0x03 )

/* Constants required to setup the initial task context. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_SPSR                                     ( ( ರಾಶಿ_Type_t ) 0x1f ) /* System mode, ARM mode, interrupts enabled. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ಬಿಟ್                                   ( ( ರಾಶಿ_Type_t ) 0x20 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_THUMB_ಬಹುಲಕ_ವಿಳಾಸ                               ( 0x01UL )

/* Masks all bits in the APSR other than the mode bits. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APSR_ಬಹುಲಕ_ಬಿಟ್ಟುಗಳು_ಮುಖವಾಡ                              ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APSR_USER_ಬಹುಲಕ                                   ( 0x10 )

/* Macro to unmask all interrupt priorities. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ()                            \
    {                                                         \
        __disable_irq();                                      \
        ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ರಿಜಿಸ್ಟರ್ = ಪೋರ್ಟ್_UNMASK_ಮೌಲ್ಯ; \
        __asm( "DSB        \n"                                \
               "ISB        \n" );                             \
        __enable_irq();                                       \
    }

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

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
ಅಸ್ಥಿರ uint32_t ulCriticalNesting = 9999UL;

/* Used to pass constants into the ASM code.  The address at which variables are
 * placed is the constant value so indirect loads in the asm code are not
 * required. */
uint32_t ulICCIAR __attribute__( ( at( ಪೋರ್ಟ್_ICCIAR_ಅಡಚಣೆ_ACKNOWLEDGE_ರಿಜಿಸ್ಟರ್_ವಿಳಾಸ ) ) );
uint32_t ulICCEOIR __attribute__( ( at( ಪೋರ್ಟ್_ICCEOIR_ಕೊನೆ_ದ_ಅಡಚಣೆ_ರಿಜಿಸ್ಟರ್_ವಿಳಾಸ ) ) );
uint32_t ulICCPMR __attribute__( ( at( ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ರಿಜಿಸ್ಟರ್_ವಿಳಾಸ ) ) );
uint32_t ul_Asm_APIPriority_ಮುಖವಾಡ __attribute__( ( at( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) ) );

/* Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task. */
uint32_t ul_ಪೋರ್ಟ್_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ul_ಪೋರ್ಟ್_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint32_t ul_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting = 0UL;

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
    *px_ತುದಿ_ದ_ರಾಶಿ = ಖಾಲಿ;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಖಾಲಿ;
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಖಾಲಿ;
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
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) prvTaskExitError; /* R14 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x12121212;       /* R12 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x11111111;       /* R11 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x10101010;       /* R10 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x09090909;       /* R9 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x08080808;       /* R8 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x07070707;       /* R7 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x06060606;       /* R6 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x05050505;       /* R5 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x04040404;       /* R4 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x03030303;       /* R3 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x02020202;       /* R2 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x01010101;       /* R1 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters;     /* R0 */
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* The task will start with a critical nesting count of 0 as interrupts are
     * enabled. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_CRITICAL_NESTING;
    px_ತುದಿ_ದ_ರಾಶಿ--;

    /* The task will start without a floating point context.  A task that uses
     * the floating point hardware must call vPortTaskUsesFPU() before executing
     * any floating point instructions. */
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_FLOATING_ಬಿಂದು_CONTEXT;

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

    /* Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start. */
    __asm( "MRS ulAPSR, APSR" );
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
            /* Start the timer that generates the tick ISR. */
            config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ();

            __enable_irq();
            v_ಪೋರ್ಟ್_Restore_Task_Context();
        }
    }

    /* Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value. */
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
    /* Disable interrupts as per portDISABLE_INTERRUPTS();  */
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
     * so there is no need to save and restore the current mask value. */
    __disable_irq();
    ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ರಿಜಿಸ್ಟರ್ = ( uint32_t ) ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು );
    __asm( "DSB        \n"
           "ISB        \n" );
    __enable_irq();

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

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU( ಶೂನ್ಯ )
{
    uint32_t ulInitialFPSCR = 0;

    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ul_ಪೋರ್ಟ್_Task_Has_FPUContext = pdTRUE;

    /* Initialise the floating point status register. */
    __asm( "FMXR    FPSCR, ulInitialFPSCR" );
}
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

    __disable_irq();

    ಆದರೆ( ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ರಿಜಿಸ್ಟರ್ == ( uint32_t ) ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        ulReturn = pdFALSE;
        ಪೋರ್ಟ್_ICCPMR_ಆದ್ಯತೆ_ಮುಖವಾಡ_ರಿಜಿಸ್ಟರ್ = ( uint32_t ) ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು );
        __asm( "DSB        \n"
               "ISB        \n" );
    }

    __enable_irq();

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
         * interrupt entry is as fast and simple as possible.
         *
         * The following links provide detailed information:
         * https://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html
         * https://www.freertos.org/Why-FreeRTOS/FAQs */
        configASSERT( ಪೋರ್ಟ್_ICCRPR_RUNNING_ಆದ್ಯತೆ_ರಿಜಿಸ್ಟರ್ >= ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) );

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
        configASSERT( ಪೋರ್ಟ್_ICCBPR_ದ್ವಿಮಾನ_ಬಿಂದು_ರಿಜಿಸ್ಟರ್ <= ಪೋರ್ಟ್_MAX_ದ್ವಿಮಾನ_ಬಿಂದು_ಮೌಲ್ಯ );
    }

#ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */
