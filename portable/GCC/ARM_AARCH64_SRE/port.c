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
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES
    #ਗਲਤੀ "configUNIQUE_INTERRUPT_PRIORITIES must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ
    #ਗਲਤੀ "configSETUP_TICK_INTERRUPT() must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#ਜੇ_ਅੰਤ /* configSETUP_TICK_INTERRUPT */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ
    #ਗਲਤੀ "configMAX_API_CALL_INTERRUPT_PRIORITY must be defined.  See www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html"
#ਜੇ_ਅੰਤ

#ਜੇ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ == 0
    #ਗਲਤੀ "configMAX_API_CALL_INTERRUPT_PRIORITY must not be set to 0"
#ਜੇ_ਅੰਤ

#ਜੇ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ > config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES
    #ਗਲਤੀ "configMAX_API_CALL_INTERRUPT_PRIORITY must be less than or equal to configUNIQUE_INTERRUPT_PRIORITIES as the lower the numeric priority value the higher the logical interrupt priority"
#ਜੇ_ਅੰਤ

#ਜੇ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #ਜੇ ( configMAX_PRIORITIES > 32 )
        #ਗਲਤੀ "configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 difference priorities as tasks that share a priority will time slice."
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#ਜੇ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ <= ( config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES / 2 )
    #ਗਲਤੀ "configMAX_API_CALL_INTERRUPT_PRIORITY must be greater than ( configUNIQUE_INTERRUPT_PRIORITIES / 2 )"
#ਜੇ_ਅੰਤ

/* Some vendor specific files default configCLEAR_TICK_INTERRUPT() in
 * portmacro.h. */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_CLEAR_TICK_ਰੁਕਾਵਟ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_CLEAR_TICK_ਰੁਕਾਵਟ()
#ਜੇ_ਅੰਤ

/* A critical section is exited when the critical section nesting count reaches
 * this value. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_CRITICAL_NESTING          ( ( size_t ) 0 )

/* In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UNMASK_ਮੁੱਲ                 ( 0xFFUL )

/* Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_FLOATING_ਬਿੰਦੂ_CONTEXT    ( ( ਢੇਰ_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SP_ELx                       ( ( ਢੇਰ_Type_t ) 0x01 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_SP_EL0                       ( ( ਢੇਰ_Type_t ) 0x00 )

#ਜੇ defined( GUEST )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EL1                      ( ( ਢੇਰ_Type_t ) 0x04 )
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_PSTATE           ( ਪੋਰਟ_EL1 | ਪੋਰਟ_SP_EL0 )
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_EL3                      ( ( ਢੇਰ_Type_t ) 0x0c )
    /* At the time of writing, the BSP only supports EL3. */
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_PSTATE           ( ਪੋਰਟ_EL3 | ਪੋਰਟ_SP_EL0 )
#ਜੇ_ਅੰਤ

/* Masks all bits in the APSR other than the mode bits. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APSR_ਬਹੁਲਕ_ਬਿੱਟ_ਨਕਾਬ    ( 0x0C )

/* The I bit in the DAIF bits. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_DAIF_I                 ( 0x80 )

/* Macro to unmask all interrupt priorities. */
/* s3_0_c4_c6_0 is ICC_PMR_EL1. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ()                     \
    {                                                  \
        __asm ਅਸਥਿਰ ( "MSR DAIFSET, #2        \n"   \
                         "DSB SY                 \n"   \
                         "ISB SY                 \n"   \
                         "MSR s3_0_c4_c6_0, %0   \n"   \
                         "DSB SY                 \n"   \
                         "ISB SY                 \n"   \
                         "MSR DAIFCLR, #2        \n"   \
                         "DSB SY                 \n"   \
                         "ISB SY                 \n"   \
                         ::"r" ( ਪੋਰਟ_UNMASK_ਮੁੱਲ ) ); \
    }

/* The space on the stack required to hold the FPU registers.
 * There are 32 128-bit plus 2 64-bit status registers.*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPU_ਰਜਿਸਟਰ_ਸ਼ਬਦ     ( (32 * 2) + 2 )

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Restore_Task_Context( ਖਾਲੀ );

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
ਖਾਲੀ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR ) __attribute__((weak) );

/*-----------------------------------------------------------*/

/* A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started. */
ਅਸਥਿਰ uint64_t ullCriticalNesting = 9999ULL;

/* Saved as part of the task context.  If ullPortTaskHasFPUContext is non-zero
 * then floating point context must be saved and restored for the task. */
uint64_t ull_ਪੋਰਟ_Task_Has_FPUContext = pdFALSE;

/* Set to 1 to pend a context switch from an ISR. */
uint64_t ull_ਪੋਰਟ_Yield_Required = pdFALSE;

/* Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0. */
uint64_t ull_ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting = 0;

/* Used in the ASM code. */
__attribute__( ( ਵਰਤਿਆ ) ) ਅਚਲ uint64_t ull_Max_APIPriority_ਨਕਾਬ = ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    /* Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro. */

    /* First all the general purpose registers. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0101010101010101ULL;        /* R1 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters; /* R0 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0303030303030303ULL;        /* R3 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0202020202020202ULL;        /* R2 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0505050505050505ULL;        /* R5 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0404040404040404ULL;        /* R4 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0707070707070707ULL;        /* R7 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0606060606060606ULL;        /* R6 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0909090909090909ULL;        /* R9 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x0808080808080808ULL;        /* R8 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1111111111111111ULL;        /* R11 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1010101010101010ULL;        /* R10 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1313131313131313ULL;        /* R13 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1212121212121212ULL;        /* R12 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1515151515151515ULL;        /* R15 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1414141414141414ULL;        /* R14 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1717171717171717ULL;        /* R17 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1616161616161616ULL;        /* R16 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1919191919191919ULL;        /* R19 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x1818181818181818ULL;        /* R18 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2121212121212121ULL;        /* R21 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2020202020202020ULL;        /* R20 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2323232323232323ULL;        /* R23 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2222222222222222ULL;        /* R22 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2525252525252525ULL;        /* R25 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2424242424242424ULL;        /* R24 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2727272727272727ULL;        /* R27 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2626262626262626ULL;        /* R26 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2929292929292929ULL;        /* R29 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = 0x2828282828282828ULL;        /* R28 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x00;         /* XZR - has no effect, used so there are an even number of registers. */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x00;         /* R30 - procedure call link register. */

    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_INITIAL_PSTATE;

    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ; /* Exception return address. */

    #ਜੇ ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_CRITICAL_NESTING;

        /* The task will start without a floating point context.  A task that
        * uses the floating point hardware must call vPortTaskUsesFPU() before
        * executing any floating point instructions. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_FLOATING_ਬਿੰਦੂ_CONTEXT;
    }
    #ਜਾਂਜੇ ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /* The task will start with a floating point context.  Leave enough
        * space for the registers - and ensure they are initialised to 0. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= ਪੋਰਟ_FPU_ਰਜਿਸਟਰ_ਸ਼ਬਦ;
        memset( px_ਸਿਖਰ_ਦਾ_ਢੇਰ, 0x00, ਪੋਰਟ_FPU_ਰਜਿਸਟਰ_ਸ਼ਬਦ * ਆਕਾਰ( ਢੇਰ_Type_t ) );

        /* The task will start with a critical nesting count of 0 as interrupts are
        * enabled. */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_CRITICAL_NESTING;

        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = pdTRUE;
        ull_ਪੋਰਟ_Task_Has_FPUContext = pdTRUE;
    }
    #ਨਹੀਂਤਾਂ /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */
    {
        #ਗਲਤੀ "Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be set to 1, 2, or left undefined."
    }
    #ਜੇ_ਅੰਤ /* if ( configUSE_TASK_FPU_SUPPORT == 1 ) */

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    uint32_t ulAPSR;

    __asm ਅਸਥਿਰ ( "MRS %0, CurrentEL" : "=r" ( ulAPSR ) );

    ulAPSR &= ਪੋਰਟ_APSR_ਬਹੁਲਕ_ਬਿੱਟ_ਨਕਾਬ;

    #ਜੇ defined( GUEST )
        configASSERT( ulAPSR == ਪੋਰਟ_EL1 );

        ਜੇ( ulAPSR == ਪੋਰਟ_EL1 )
    #ਨਹੀਂਤਾਂ
        configASSERT( ulAPSR == ਪੋਰਟ_EL3 );

        ਜੇ( ulAPSR == ਪੋਰਟ_EL3 )
    #ਜੇ_ਅੰਤ
    {
        /* Interrupts are turned off in the CPU itself to ensure a tick does
         * not execute while the scheduler is being started.  Interrupts are
         * automatically turned back on in the CPU when the first task starts
         * executing. */
        ਪੋਰਟ_DISABLE_INTERRUPTS();

        /* Start the timer that generates the tick ISR. */
        config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ();

        /* Start the first task executing. */
        v_ਪੋਰਟ_Restore_Task_Context();
    }

    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /* Not implemented in ports where there is nothing to return to.
     * Artificially force an assert. */
    configASSERT( ullCriticalNesting == 1000ULL );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    ux_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ();

    /* Now interrupts are disabled ullCriticalNesting can be accessed
     * directly.  Increment ullCriticalNesting to keep a count of how many times
     * portENTER_CRITICAL() has been called. */
    ullCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
     * assert() if it is being called from an interrupt context.  Only API
     * functions that end in "FromISR" can be used in an interrupt.  Only assert if
     * the critical nesting count is 1 to protect against recursive calls if the
     * assert function also uses a critical section. */
    ਜੇ( ullCriticalNesting == 1ULL )
    {
        configASSERT( ull_ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    ਜੇ( ullCriticalNesting > ਪੋਰਟ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being
         * exited. */
        ullCriticalNesting--;

        /* If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled. */
        ਜੇ( ullCriticalNesting == ਪੋਰਟ_NO_CRITICAL_NESTING )
        {
            /* Critical nesting has reached zero so all interrupt priorities
             * should be unmasked. */
            ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ();
        }
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ FreeRTOS_Tick_Handler( ਖਾਲੀ )
{
    /* Must be the lowest possible priority. */
    #ਜੇ !defined( QEMU )
    {
        uint64_t ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ;
        /* s3_0_c12_c11_3 is ICC_RPR_EL1. */
        __asm ਅਸਥਿਰ ( "MRS %0, s3_0_c12_c11_3" : "=r" ( ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) );
        configASSERT( ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ == ( ਪੋਰਟ_ਸਭ_ਤੋਂ_ਨੀਵਾਂ_USABLE_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ ) );
    }
    #ਜੇ_ਅੰਤ

    /* Interrupts should not be enabled before this point. */
    #ਜੇ ( configASSERT_DEFINED == 1 )
    {
        uint32_t ul_ਨਕਾਬ_ਬਿੱਟ;

        __asm ਅਸਥਿਰ ( "MRS %0, DAIF" : "=r" ( ul_ਨਕਾਬ_ਬਿੱਟ )::"memory" );
        configASSERT( ( ul_ਨਕਾਬ_ਬਿੱਟ & ਪੋਰਟ_DAIF_I ) != 0 );
    }
    #ਜੇ_ਅੰਤ /* configASSERT_DEFINED */

    /* Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated. */
    /* s3_0_c4_c6_0 is ICC_PMR_EL1. */
    __asm ਅਸਥਿਰ ( "MSR s3_0_c4_c6_0, %0      \n"
                     "DSB SY                    \n"
                     "ISB SY                    \n"
                     ::"r" ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ ) : "memory" );

    /* Ok to enable interrupts after the interrupt source has been cleared. */
    config_CLEAR_TICK_ਰੁਕਾਵਟ();
    ਪੋਰਟ_ENABLE_INTERRUPTS();

    /* Increment the RTOS tick. */
    ਜੇ( xTaskIncrementTick() != pdFALSE )
    {
        ull_ਪੋਰਟ_Yield_Required = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ();
}
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TASK_FPU_SUPPORT != 2 )

ਖਾਲੀ v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU( ਖਾਲੀ )
{
    /* A task is registering the fact that it needs an FPU context.  Set the
     * FPU flag (which is saved as part of the task context). */
    ull_ਪੋਰਟ_Task_Has_FPUContext = pdTRUE;

    /* Consider initialising the FPSR here - but probably not necessary in
     * AArch64. */
}

#ਜੇ_ਅੰਤ /* configUSE_TASK_FPU_SUPPORT */
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( UBaseType_t ux_New_ਨਕਾਬ_ਮੁੱਲ )
{
    ਜੇ( ux_New_ਨਕਾਬ_ਮੁੱਲ == pdFALSE )
    {
        ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ();
    }
}
/*-----------------------------------------------------------*/

UBaseType_t ux_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ( ਖਾਲੀ )
{
    uint32_t ulReturn;
    uint64_t ullPMRValue;

    /* Interrupt in the CPU must be turned off while the ICCPMR is being
     * updated. */
    ਪੋਰਟ_DISABLE_INTERRUPTS();
    /* s3_0_c4_c6_0 is ICC_PMR_EL1. */
    __asm ਅਸਥਿਰ ( "MRS %0, s3_0_c4_c6_0" : "=r" ( ullPMRValue ) );

    ਜੇ( ullPMRValue == ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    ਨਹੀਂਤਾਂ
    {
        ulReturn = pdFALSE;
        /* s3_0_c4_c6_0 is ICC_PMR_EL1. */
        __asm ਅਸਥਿਰ ( "MSR s3_0_c4_c6_0, %0      \n"
                         "DSB SY                    \n"
                         "ISB SY                    \n"
                         ::"r" ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ ) : "memory" );
    }

    ਪੋਰਟ_ENABLE_INTERRUPTS();

    ਵਾਪਸ ulReturn;
}
/*-----------------------------------------------------------*/

#ਜੇ ( configASSERT_DEFINED == 1 )

    ਖਾਲੀ v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ( ਖਾਲੀ )
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
        uint64_t ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ;
        /* s3_0_c12_c11_3 is ICC_RPR_EL1. */
        __asm ਅਸਥਿਰ ( "MRS %0, s3_0_c12_c11_3" : "=r" ( ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ ) );

        configASSERT( ull_Running_ਰੁਕਾਵਟ_ਤਰਜੀਹ >= ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ ) );
    }

#ਜੇ_ਅੰਤ /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/

ਖਾਲੀ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR )
{
    ( ਖਾਲੀ ) ulICCIAR;
    configASSERT( ( ਅਸਥਿਰ ਖਾਲੀ * ) ਨਿਰਾ );
}
