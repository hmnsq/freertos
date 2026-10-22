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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_NO_CRITICAL_NESTING          ( ( size_t ) 0 )

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
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SP_ELx                       ( ( ರಾಶಿ_Type_t ) 0x01 )
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_SP_EL0                       ( ( ರಾಶಿ_Type_t ) 0x00 )

#ಆದರೆ defined( GUEST )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EL1                      ( ( ರಾಶಿ_Type_t ) 0x04 )
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_PSTATE           ( ಪೋರ್ಟ್_EL1 | ಪೋರ್ಟ್_SP_EL0 )
#ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_EL3                      ( ( ರಾಶಿ_Type_t ) 0x0c )
    /* At the time of writing, the BSP only supports EL3. */
    #ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_INITIAL_PSTATE           ( ಪೋರ್ಟ್_EL3 | ಪೋರ್ಟ್_SP_EL0 )
#ಆದರೆ_ಅಂತ್ಯ

/* Masks all bits in the APSR other than the mode bits. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_APSR_ಬಹುಲಕ_ಬಿಟ್ಟುಗಳು_ಮುಖವಾಡ    ( 0x0C )

/* The I bit in the DAIF bits. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_DAIF_I                 ( 0x80 )

/* Macro to unmask all interrupt priorities. */
/* s3_0_c4_c6_0 is ICC_PMR_EL1. */
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ()                     \
    {                                                  \
        __asm ಅಸ್ಥಿರ ( "MSR DAIFSET, #2        \n"   \
                         "DSB SY                 \n"   \
                         "ISB SY                 \n"   \
                         "MSR s3_0_c4_c6_0, %0   \n"   \
                         "DSB SY                 \n"   \
                         "ISB SY                 \n"   \
                         "MSR DAIFCLR, #2        \n"   \
                         "DSB SY                 \n"   \
                         "ISB SY                 \n"   \
                         ::"r" ( ಪೋರ್ಟ್_UNMASK_ಮೌಲ್ಯ ) ); \
    }

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit plus 2 64-bit status registers.*/
#ವ್ಯಾಖ್ಯಾನಿಸು ಪೋರ್ಟ್_FPU_ರಿಜಿಸ್ಟರ್_ಪದಗಳು     ( (32 * 2) + 2 )

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
ಬಾಹ್ಯ ಶೂನ್ಯ v_ಪೋರ್ಟ್_Restore_Task_Context( ಶೂನ್ಯ );

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
ಶೂನ್ಯ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR ) __attribute__((weak) );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
ಅಸ್ಥಿರ uint64_t ullCriticalNesting = 9999ULL;

/* Saved as part of the task context.  If ullPortTaskHasFPUContext is non-zero
 * then floating point context must be saved and restored for the task. */
uint64_t ull_ಪೋರ್ಟ್_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint64_t ull_ಪೋರ್ಟ್_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint64_t ull_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting = 0;

/* Used in the ASM code. */
__attribute__( ( ಬಳಸಿದ ) ) ಸ್ಥಿರಾಂಕ uint64_t ull_Max_APIPriority_ಮುಖವಾಡ = ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ರಾಶಿ_Type_t * px_ಪೋರ್ಟ್_Initialise_ರಾಶಿ( ರಾಶಿ_Type_t * px_ತುದಿ_ದ_ರಾಶಿ,
                                     TaskFunction_t px_ಸಂಕೇತ,
                                     ಶೂನ್ಯ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First all the general purpose registers. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x0101010101010101ULL;        /* R1 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) pvParameters; /* R0 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x0303030303030303ULL;        /* R3 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x0202020202020202ULL;        /* R2 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x0505050505050505ULL;        /* R5 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x0404040404040404ULL;        /* R4 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x0707070707070707ULL;        /* R7 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x0606060606060606ULL;        /* R6 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x0909090909090909ULL;        /* R9 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x0808080808080808ULL;        /* R8 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x1111111111111111ULL;        /* R11 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x1010101010101010ULL;        /* R10 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x1313131313131313ULL;        /* R13 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x1212121212121212ULL;        /* R12 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x1515151515151515ULL;        /* R15 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x1414141414141414ULL;        /* R14 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x1717171717171717ULL;        /* R17 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x1616161616161616ULL;        /* R16 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x1919191919191919ULL;        /* R19 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x1818181818181818ULL;        /* R18 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x2121212121212121ULL;        /* R21 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x2020202020202020ULL;        /* R20 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x2323232323232323ULL;        /* R23 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x2222222222222222ULL;        /* R22 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x2525252525252525ULL;        /* R25 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x2424242424242424ULL;        /* R24 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x2727272727272727ULL;        /* R27 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x2626262626262626ULL;        /* R26 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x2929292929292929ULL;        /* R29 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = 0x2828282828282828ULL;        /* R28 */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00;         /* XZR - has no effect, used so there are an even number of registers. */
    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) 0x00;         /* R30 - procedure call link register. */

    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_INITIAL_PSTATE;

    px_ತುದಿ_ದ_ರಾಶಿ--;
    *px_ತುದಿ_ದ_ರಾಶಿ = ( ರಾಶಿ_Type_t ) px_ಸಂಕೇತ; /* Exception return address. */

    #ಆದರೆ ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_CRITICAL_NESTING;

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

        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = ಪೋರ್ಟ್_NO_CRITICAL_NESTING;

        px_ತುದಿ_ದ_ರಾಶಿ--;
        *px_ತುದಿ_ದ_ರಾಶಿ = pdTRUE;
        ull_ಪೋರ್ಟ್_Task_Has_FPUContext = pdTRUE;
    }
    #ಇಲ್ಲದಿದ್ದರೆ /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */
    {
        #ದೋಷ "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
    }
    #ಆದರೆ_ಅಂತ್ಯ /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */

    ಹಿಂತಿರುಗಿ px_ತುದಿ_ದ_ರಾಶಿ;
}
/*-----------------------------------------------------------*/

ತಳ_Type_t x_ಪೋರ್ಟ್_ಆರಂಭ_Scheduler( ಶೂನ್ಯ )
{
    uint32_t ulAPSR;

    __asm ಅಸ್ಥಿರ ( "MRS %0, CurrentEL" : "=r" ( ulAPSR ) );

    ulAPSR &= ಪೋರ್ಟ್_APSR_ಬಹುಲಕ_ಬಿಟ್ಟುಗಳು_ಮುಖವಾಡ;

    #ಆದರೆ defined( GUEST )
        configASSERT( ulAPSR == ಪೋರ್ಟ್_EL1 );

        ಆದರೆ( ulAPSR == ಪೋರ್ಟ್_EL1 )
    #ಇಲ್ಲದಿದ್ದರೆ
        configASSERT( ulAPSR == ಪೋರ್ಟ್_EL3 );

        ಆದರೆ( ulAPSR == ಪೋರ್ಟ್_EL3 )
    #ಆದರೆ_ಅಂತ್ಯ
    {
        /* Interrupts are turned off in the CPU itself to ensure a tick does
         * not execute while the scheduler is being started.  Interrupts are
         * automatically turned back on in the CPU when the first task starts
         * executing. */
        ಪೋರ್ಟ್_DISABLE_INTERRUPTS();

        /* Start the timer that generates the tick ISR. */
        config_ಸಿದ್ಧತೆ_TICK_ಅಡಚಣೆ();

        /* Start the first task executing. */
        v_ಪೋರ್ಟ್_Restore_Task_Context();
    }

    ಹಿಂತಿರುಗಿ 0;
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_ಕೊನೆ_Scheduler( ಶೂನ್ಯ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ullCriticalNesting == 1000ULL );
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Enter_Critical( ಶೂನ್ಯ )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ();

    /* Now interrupts are disabled ullCriticalNesting can be accessed
     * directly.  Increment ullCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ullCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    ಆದರೆ( ullCriticalNesting == 1ULL )
    {
        configASSERT( ull_ಪೋರ್ಟ್_ಅಡಚಣೆ_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Exit_Critical( ಶೂನ್ಯ )
{
    ಆದರೆ( ullCriticalNesting > ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ullCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        ಆದರೆ( ullCriticalNesting == ಪೋರ್ಟ್_NO_CRITICAL_NESTING )
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
    /* Must be the lowest possible priority. */
    #ಆದರೆ !defined( QEMU )
    {
        uint64_t ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ;
        /* s3_0_c12_c11_3 is ICC_RPR_EL1. */
        __asm ಅಸ್ಥಿರ ( "MRS %0, s3_0_c12_c11_3" : "=r" ( ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ ) );
        configASSERT( ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ == ( ಪೋರ್ಟ್_ಅತಿಕಡಿಮೆ_USABLE_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) );
    }
    #ಆದರೆ_ಅಂತ್ಯ

    /* Interrupts should not be enabled before this point. */
    #ಆದರೆ ( configASSERT_DEFINED == 1 )
    {
        uint32_t ul_ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು;

        __asm ಅಸ್ಥಿರ ( "MRS %0, DAIF" : "=r" ( ul_ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು )::"memory" );
        configASSERT( ( ul_ಮುಖವಾಡ_ಬಿಟ್ಟುಗಳು & ಪೋರ್ಟ್_DAIF_I ) != 0 );
    }
    #ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */

    /* Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated. */
    /* s3_0_c4_c6_0 is ICC_PMR_EL1. */
    __asm ಅಸ್ಥಿರ ( "MSR s3_0_c4_c6_0, %0      \n"
                     "DSB SY                    \n"
                     "ISB SY                    \n"
                     ::"r" ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) : "memory" );

    /* Ok to enable interrupts after the interrupt source has been cleared. */
    config_CLEAR_TICK_ಅಡಚಣೆ();
    ಪೋರ್ಟ್_ENABLE_INTERRUPTS();

    /* Increment the RTOS tick. */
    ಆದರೆ( xTaskIncrementTick() != pdFALSE )
    {
        ull_ಪೋರ್ಟ್_Yield_Required = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ();
}
/*-----------------------------------------------------------*/

#ಆದರೆ ( configUSE_TASK_FPU_SUPPORT != 2 )

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Task_ಬಳಸುತ್ತದೆ_FPU( ಶೂನ್ಯ )
{
    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ull_ಪೋರ್ಟ್_Task_Has_FPUContext = pdTRUE;

    /* Consider initialising the FPSR here - but probably not necessary in
     * AArch64. */
}

#ಆದರೆ_ಅಂತ್ಯ /* configUSE_TASK_FPU_SUPPORT */
/*-----------------------------------------------------------*/

ಶೂನ್ಯ v_ಪೋರ್ಟ್_Clear_ಅಡಚಣೆ_ಮುಖವಾಡ( UBaseType_t ux_New_ಮುಖವಾಡ_ಮೌಲ್ಯ )
{
    ಆದರೆ( ux_New_ಮುಖವಾಡ_ಮೌಲ್ಯ == pdFALSE )
    {
        ಪೋರ್ಟ್_CLEAR_ಅಡಚಣೆ_ಮುಖವಾಡ();
    }
}
/*-----------------------------------------------------------*/

UBaseType_t ux_ಪೋರ್ಟ್_ಗಣ_ಅಡಚಣೆ_ಮುಖವಾಡ( ಶೂನ್ಯ )
{
    uint32_t ulReturn;
    uint64_t ullPMRValue;

    /* Interrupt in the CPU must be turned off while the ICCPMR is being
     * updated. */
    ಪೋರ್ಟ್_DISABLE_INTERRUPTS();
    /* s3_0_c4_c6_0 is ICC_PMR_EL1. */
    __asm ಅಸ್ಥಿರ ( "MRS %0, s3_0_c4_c6_0" : "=r" ( ullPMRValue ) );

    ಆದರೆ( ullPMRValue == ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
        ulReturn = pdFALSE;
        /* s3_0_c4_c6_0 is ICC_PMR_EL1. */
        __asm ಅಸ್ಥಿರ ( "MSR s3_0_c4_c6_0, %0      \n"
                         "DSB SY                    \n"
                         "ISB SY                    \n"
                         ::"r" ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) : "memory" );
    }

    ಪೋರ್ಟ್_ENABLE_INTERRUPTS();

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
        uint64_t ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ;
        /* s3_0_c12_c11_3 is ICC_RPR_EL1. */
        __asm ಅಸ್ಥಿರ ( "MRS %0, s3_0_c12_c11_3" : "=r" ( ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ ) );

        configASSERT( ull_Running_ಅಡಚಣೆ_ಆದ್ಯತೆ >= ( config_MAX_API_CALL_ಅಡಚಣೆ_ಆದ್ಯತೆ << ಪೋರ್ಟ್_ಆದ್ಯತೆ_ಸರಿಸು ) );
    }

#ಆದರೆ_ಅಂತ್ಯ /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

ಶೂನ್ಯ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR )
{
    ( ಶೂನ್ಯ ) ulICCIAR;
    configASSERT( ( ಅಸ್ಥಿರ ಶೂನ್ಯ * ) ಖಾಲಿ );
}
