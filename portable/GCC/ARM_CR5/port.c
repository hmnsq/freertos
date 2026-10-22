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
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

/* Scheduler includes. */
#ਅਨ੍ਤਰ੍ਭਾਵ "FreeRTOS.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "task.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਰੁਕਾਵਟ_CONTROLLER_ਅਧਾਰ_ਪਤਾ
    #ਗਲਤੀ config_ਰੁਕਾਵਟ_CONTROLLER_ਅਧਾਰ_ਪਤਾ must be defined.  Refer ਮੰਜ਼ਿਲ Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਰੁਕਾਵਟ_CONTROLLER_CPU_INTERFACE_ਵਿੱਥ
    #ਗਲਤੀ config_ਰੁਕਾਵਟ_CONTROLLER_CPU_INTERFACE_ਵਿੱਥ must be defined.  Refer ਮੰਜ਼ਿਲ Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES
    #ਗਲਤੀ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES must be defined.  Refer ਮੰਜ਼ਿਲ Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ
    #ਗਲਤੀ config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ() must be defined.  Refer ਮੰਜ਼ਿਲ Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#ਜੇ_ਅੰਤ /* configSETUP_TICK_INTERRUPT */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ
    #ਗਲਤੀ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ must be defined.  Refer ਮੰਜ਼ਿਲ Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#ਜੇ_ਅੰਤ

#ਜੇ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ == 0
    #ਗਲਤੀ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ must not be ਸੈੱਟ ਮੰਜ਼ਿਲ 0
#ਜੇ_ਅੰਤ

#ਜੇ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ > config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES
    #ਗਲਤੀ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ must be less than or equal ਮੰਜ਼ਿਲ config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES as the ਹੇਠਲਾ the numeric ਤਰਜੀਹ ਮੁੱਲ the higher the logical ਰੁਕਾਵਟ ਤਰਜੀਹ
#ਜੇ_ਅੰਤ

#ਜੇ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #ਜੇ ( configMAX_PRIORITIES > 32 )
        #ਗਲਤੀ config_USE_ਪੋਰਟ_OPTIMISED_TASK_SELECTION can only be ਸੈੱਟ ਮੰਜ਼ਿਲ 1 when configMAX_PRIORITIES is less than or equal ਮੰਜ਼ਿਲ 32.  It is very rare that a system requires ਹੋਰ than 10 ਮੰਜ਼ਿਲ 15 difference priorities as tasks that share a ਤਰਜੀਹ will time ਟੁਕੜਾ.
    #ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#ਜੇ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ <= ( config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES / 2 )
    #ਗਲਤੀ config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ must be greater than ( config_UNIQUE_ਰੁਕਾਵਟ_PRIORITIES / 2 )
#ਜੇ_ਅੰਤ

/*
 * __ARM_FP is defined by the c preprocessor when FPU support is enabled,
 * usually with the -mfpu= argument and -mfloat-abi=.
 *
 * Note: Some implementations of the c standard library may use FPU registers
 *       for generic memory operations (memcpy, etc).
 *       When setting configUSE_TASK_FPU_SUPPORT == 1, care must be taken to
 *       ensure that the FPU registers are not used without an FPU context.
 */
#ਜੇ ( configUSE_TASK_FPU_SUPPORT == 0 )
    #ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __ARM_FP
        #ਗਲਤੀ __ARM_FP is defined, so configUSE_TASK_FPU_SUPPORT must be ਸੈੱਟ ਮੰਜ਼ਿਲ either ਮੰਜ਼ਿਲ 1 or 2.
    #ਜੇ_ਅੰਤ /* __ARM_FP */
#ਜਾਂਜੇ ( configUSE_TASK_FPU_SUPPORT == 1 ) || ( configUSE_TASK_FPU_SUPPORT == 2 )
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __ARM_FP
        #ਗਲਤੀ __ARM_FP is not defined, so configUSE_TASK_FPU_SUPPORT must be ਸੈੱਟ ਮੰਜ਼ਿਲ 0.
    #ਜੇ_ਅੰਤ /* __ARM_FP */
#ਜੇ_ਅੰਤ /* configUSE_TASK_FPU_SUPPORT */

/*
 * Some vendor specific files default configCLEAR_TICK_INTERRUPT() in
 * portmacro.h.
 */
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ config_CLEAR_TICK_ਰੁਕਾਵਟ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ config_CLEAR_TICK_ਰੁਕਾਵਟ()
#ਜੇ_ਅੰਤ

/*
 * A critical section is exited when the critical section nesting count reaches
 * this value.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/*
 * In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_UNMASK_ਮੁੱਲ                 ( 0xFFUL )

/*
 * Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_NO_FLOATING_ਬਿੰਦੂ_CONTEXT    ( ( ਢੇਰ_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_INITIAL_SPSR                 ( ( ਢੇਰ_Type_t ) 0x1f ) /* System mode, ARM mode, IRQ enabled FIQ enabled. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਦੋਆਧਾਰੀ_ਅੰਕ               ( ( ਢੇਰ_Type_t ) 0x20 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰੁਕਾਵਟ_ENABLE_ਦੋਆਧਾਰੀ_ਅੰਕ         ( 0x80UL )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਪਤਾ           ( 0x01UL )

/*
 * Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਬਿੱਟ            ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APSR_ਬਹੁਲਕ_ਬਿੱਟ_ਨਕਾਬ          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_APSR_USER_ਬਹੁਲਕ               ( 0x10 )

/* The critical section macros only mask interrupts up to an application
 * determined priority level.  Sometimes it is necessary to turn interrupt off in
 * the CPU itself before modifying certain hardware registers. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CPU_IRQ_DISABLE()                  \
    __asm ਅਸਥਿਰ ( "CPSID i" ::: "memory" ); \
    __asm ਅਸਥਿਰ ( "DSB" );                  \
    __asm ਅਸਥਿਰ ( "ISB" );

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CPU_IRQ_ENABLE()                   \
    __asm ਅਸਥਿਰ ( "CPSIE i" ::: "memory" ); \
    __asm ਅਸਥਿਰ ( "DSB" );                  \
    __asm ਅਸਥਿਰ ( "ISB" );


/* Macro to unmask all interrupt priorities. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ()                            \
    {                                                         \
        ਪੋਰਟ_CPU_IRQ_DISABLE();                                \
        ਪੋਰਟ_ICCPMR_ਤਰਜੀਹ_ਨਕਾਬ_ਰਜਿਸਟਰ = ਪੋਰਟ_UNMASK_ਮੁੱਲ; \
        __asm ਅਸਥਿਰ ( "DSB       \n"                       \
                         "ISB       \n" );                    \
        ਪੋਰਟ_CPU_IRQ_ENABLE();                                 \
    }

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਰੁਕਾਵਟ_ਤਰਜੀਹ_ਰਜਿਸਟਰ_ਵਿੱਥ    0x400UL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_MAX_8_ਦੋਆਧਾਰੀ_ਅੰਕ_ਮੁੱਲ                       ( ( uint8_t ) 0xff )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_0_ਸੈੱਟ                             ( ( uint8_t ) 0x01 )

/*
 * Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case is messes up unwinding of the stack in the
 * debugger.
 */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ config_TASK_RETURN_ਪਤਾ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ    config_TASK_RETURN_ਪਤਾ
#ਨਹੀਂਤਾਂ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_TASK_RETURN_ਪਤਾ    prvTaskExitError
#ਜੇ_ਅੰਤ

#ਜੇ ( configUSE_TASK_FPU_SUPPORT != 0 )

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
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪੋਰਟ_FPU_ਰਜਿਸਟਰ_ਸ਼ਬਦ    ( ( 16 * 2 ) + 1 )
#ਜੇ_ਅੰਤ /* configUSE_TASK_FPU_SUPPORT != 0 */

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
ਬਾਹਰੀ ਖਾਲੀ v_ਪੋਰਟ_Restore_Task_Context( ਖਾਲੀ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ );

#ਜੇ ( configUSE_TASK_FPU_SUPPORT != 0 )

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
    ਖਾਲੀ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR ) __attribute__( ( weak ) );
#ਜੇ_ਅੰਤ /* configUSE_TASK_FPU_SUPPORT != 0 */

/*-----------------------------------------------------------*/

/*
 * A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started.
 */
ਅਸਥਿਰ uint32_t ulCriticalNesting = 9999UL;

#ਜੇ ( configUSE_TASK_FPU_SUPPORT != 0 )

/*
 * Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task.
 */
    uint32_t ul_ਪੋਰਟ_Task_Has_FPUContext = pdFALSE;
#ਜੇ_ਅੰਤ /* configUSE_TASK_FPU_SUPPORT != 0 */

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ul_ਪੋਰਟ_Yield_Required = pdFALSE;

/*
 * Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0.
 */
uint32_t ul_ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting = 0UL;

/* Used in asm code. */
__attribute__( ( ਵਰਤਿਆ ) ) ਅਚਲ uint32_t ulICCIAR = ਪੋਰਟ_ICCIAR_ਰੁਕਾਵਟ_ACKNOWLEDGE_ਰਜਿਸਟਰ_ਪਤਾ;
__attribute__( ( ਵਰਤਿਆ ) ) ਅਚਲ uint32_t ulICCEOIR = ਪੋਰਟ_ICCEOIR_ਸਿਰਾ_ਦਾ_ਰੁਕਾਵਟ_ਰਜਿਸਟਰ_ਪਤਾ;
__attribute__( ( ਵਰਤਿਆ ) ) ਅਚਲ uint32_t ulICCPMR = ਪੋਰਟ_ICCPMR_ਤਰਜੀਹ_ਨਕਾਬ_ਰਜਿਸਟਰ_ਪਤਾ;
__attribute__( ( ਵਰਤਿਆ ) ) ਅਚਲ uint32_t ul_Max_APIPriority_ਨਕਾਬ = ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ਢੇਰ_Type_t * px_ਪੋਰਟ_Initialise_ਢੇਰ( ਢੇਰ_Type_t * px_ਸਿਖਰ_ਦਾ_ਢੇਰ,
                                     TaskFunction_t px_ਕੋਡ,
                                     ਖਾਲੀ * pvParameters )
{
    /*
     * Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address.
     */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਨਿਰਾ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਨਿਰਾ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਨਿਰਾ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_INITIAL_SPSR;

    ਜੇ( ( ( uint32_t ) px_ਕੋਡ & ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਪਤਾ ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ |= ਪੋਰਟ_THUMB_ਬਹੁਲਕ_ਦੋਆਧਾਰੀ_ਅੰਕ;
    }

    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Next the return address, which in this case is the start of the task. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) px_ਕੋਡ;
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;

    /* Next all the registers other than the stack pointer. */
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) ਪੋਰਟ_TASK_RETURN_ਪਤਾ; /* R14 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x12121212;              /* R12 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x11111111;              /* R11 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x10101010;              /* R10 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x09090909;              /* R9 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x08080808;              /* R8 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x07070707;              /* R7 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x06060606;              /* R6 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x05050505;              /* R5 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x04040404;              /* R4 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x03030303;              /* R3 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x02020202;              /* R2 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) 0x01010101;              /* R1 */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ( ਢੇਰ_Type_t ) pvParameters;            /* R0 */

    /*
     * The task will start with a critical nesting count of 0 as interrupts are
     * enabled.
     */
    px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
    *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_CRITICAL_NESTING;

    #ਜੇ ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /*
         * The task will start without a floating point context.
         * A task that uses the floating point hardware must call
         * vPortTaskUsesFPU() before executing any floating point
         * instructions.
         */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = ਪੋਰਟ_NO_FLOATING_ਬਿੰਦੂ_CONTEXT;
    }
    #ਜਾਂਜੇ ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /*
         * The task will start with a floating point context. Leave enough
         * space for the registers and ensure they are initialized to 0.
         */
        px_ਸਿਖਰ_ਦਾ_ਢੇਰ -= ਪੋਰਟ_FPU_ਰਜਿਸਟਰ_ਸ਼ਬਦ;
        memset( px_ਸਿਖਰ_ਦਾ_ਢੇਰ, 0x00, ਪੋਰਟ_FPU_ਰਜਿਸਟਰ_ਸ਼ਬਦ * ਆਕਾਰ( ਢੇਰ_Type_t ) );

        px_ਸਿਖਰ_ਦਾ_ਢੇਰ--;
        *px_ਸਿਖਰ_ਦਾ_ਢੇਰ = pdTRUE;
        ul_ਪੋਰਟ_Task_Has_FPUContext = pdTRUE;
    }
    #ਜਾਂਜੇ ( configUSE_TASK_FPU_SUPPORT != 0 )
    {
        #ਗਲਤੀ Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be ਸੈੱਟ ਮੰਜ਼ਿਲ 0, 1, or 2.
    }
    #ਜੇ_ਅੰਤ /* configUSE_TASK_FPU_SUPPORT */

    ਵਾਪਸ px_ਸਿਖਰ_ਦਾ_ਢੇਰ;
}
/*-----------------------------------------------------------*/

ਸਥਿਰ ਖਾਲੀ prvTaskExitError( ਖਾਲੀ )
{
    /*
     * A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error.
     */
    configASSERT( ul_ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting == ~0UL );
    ਪੋਰਟ_DISABLE_INTERRUPTS();

    ਲਈ( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TASK_FPU_SUPPORT != 0 )

    ਖਾਲੀ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR ) /* __attribute__( ( weak ) ) */
    {
        ( ਖਾਲੀ ) ulICCIAR;
        configASSERT( ( ਅਸਥਿਰ ਖਾਲੀ * ) ਨਿਰਾ );
    }

#ਜੇ_ਅੰਤ /* configUSE_TASK_FPU_SUPPORT != 0 */
/*-----------------------------------------------------------*/

ਅਧਾਰ_Type_t x_ਪੋਰਟ_ਸ਼ੁਰੂ_Scheduler( ਖਾਲੀ )
{
    uint32_t ulAPSR, ul_ਚੱਕਰਾਂ = 8; /* 8 bits per byte. */

    #ਜੇ ( configASSERT_DEFINED == 1 )
    {
        ਅਸਥਿਰ uint8_t uc_Original_ਤਰਜੀਹ;
        ਅਸਥਿਰ uint8_t * ਅਚਲ puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ = ( ਅਸਥਿਰ uint8_t * ਅਚਲ ) ( config_ਰੁਕਾਵਟ_CONTROLLER_ਅਧਾਰ_ਪਤਾ + ਪੋਰਟ_ਰੁਕਾਵਟ_ਤਰਜੀਹ_ਰਜਿਸਟਰ_ਵਿੱਥ );
        ਅਸਥਿਰ uint8_t uc_Max_ਤਰਜੀਹ_ਮੁੱਲ;

        /*
         * Determine how many priority bits are implemented in the GIC.
         * Save the interrupt priority value that is about to be clobbered.
         */
        uc_Original_ਤਰਜੀਹ = *puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ;

        /*
         * Determine the number of priority bits available.  First write to
         * all possible bits.
         */
        *puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ = ਪੋਰਟ_MAX_8_ਦੋਆਧਾਰੀ_ਅੰਕ_ਮੁੱਲ;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ਤਰਜੀਹ_ਮੁੱਲ = *puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ;

        /* Shift to the least significant bits. */
        ਜਦੋਂ( ( uc_Max_ਤਰਜੀਹ_ਮੁੱਲ & ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_0_ਸੈੱਟ ) != ਪੋਰਟ_ਦੋਆਧਾਰੀ_ਅੰਕ_0_ਸੈੱਟ )
        {
            uc_Max_ਤਰਜੀਹ_ਮੁੱਲ >>= ( uint8_t ) 0x01;

            /*
             * If ulCycles reaches 0 then ucMaxPriorityValue must have been
             * read as 0, indicating a misconfiguration.
             */
            ul_ਚੱਕਰਾਂ--;

            ਜੇ( ul_ਚੱਕਰਾਂ == 0 )
            {
                ਰੋਕੋ;
            }
        }

        /*
         * Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value.
         */
        configASSERT( uc_Max_ਤਰਜੀਹ_ਮੁੱਲ == ਪੋਰਟ_ਸਭ_ਤੋਂ_ਨੀਵਾਂ_ਰੁਕਾਵਟ_ਤਰਜੀਹ );

        /*
         * Restore the clobbered interrupt priority register to its original
         * value.
         */
        *puc_ਪਹਿਲਾ_User_ਤਰਜੀਹ_ਰਜਿਸਟਰ = uc_Original_ਤਰਜੀਹ;
    }
    #ਜੇ_ਅੰਤ /* configASSERT_DEFINED */

    /*
     * Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start.
     */
    __asm ਅਸਥਿਰ ( "MRS %0, APSR" : "=r" ( ulAPSR )::"memory" );
    ulAPSR &= ਪੋਰਟ_APSR_ਬਹੁਲਕ_ਬਿੱਟ_ਨਕਾਬ;
    configASSERT( ulAPSR != ਪੋਰਟ_APSR_USER_ਬਹੁਲਕ );

    ਜੇ( ulAPSR != ਪੋਰਟ_APSR_USER_ਬਹੁਲਕ )
    {
        /*
         * Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information.
         */
        configASSERT( ( ਪੋਰਟ_ICCBPR_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਰਜਿਸਟਰ & ਪੋਰਟ_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਬਿੱਟ ) <= ਪੋਰਟ_MAX_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਮੁੱਲ );

        ਜੇ( ( ਪੋਰਟ_ICCBPR_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਰਜਿਸਟਰ & ਪੋਰਟ_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਬਿੱਟ ) <= ਪੋਰਟ_MAX_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਮੁੱਲ )
        {
            /*
             * Interrupts are turned off in the CPU itself to ensure tick does
             * not execute  while the scheduler is being started.  Interrupts are
             * automatically turned back on in the CPU when the first task starts
             * executing.
             */
            ਪੋਰਟ_CPU_IRQ_DISABLE();

            /* Start the timer that generates the tick ISR. */
            config_ਤਿਆਰੀ_TICK_ਰੁਕਾਵਟ();

            /* Start the first task executing. */
            v_ਪੋਰਟ_Restore_Task_Context();
        }
    }

    /*
     * Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value.  prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address.
     */
    ( ਖਾਲੀ ) prvTaskExitError;

    ਵਾਪਸ 0;
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_ਸਿਰਾ_Scheduler( ਖਾਲੀ )
{
    /*
     * Not implemented in ports where there is nothing to return to.
     * Artificially force an assert.
     */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Enter_Critical( ਖਾਲੀ )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    ul_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ();

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
    ਜੇ( ulCriticalNesting == 1 )
    {
        configASSERT( ul_ਪੋਰਟ_ਰੁਕਾਵਟ_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Exit_Critical( ਖਾਲੀ )
{
    ਜੇ( ulCriticalNesting > ਪੋਰਟ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being exited. */
        ulCriticalNesting--;

        /*
         * If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled.
         */
        ਜੇ( ulCriticalNesting == ਪੋਰਟ_NO_CRITICAL_NESTING )
        {
            /*
             * Critical nesting has reached zero so all interrupt priorities
             * should be unmasked.
             */
            ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ();
        }
    }
}
/*-----------------------------------------------------------*/

ਖਾਲੀ FreeRTOS_Tick_Handler( ਖਾਲੀ )
{
    /*
     * Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated.
     */
    ਪੋਰਟ_CPU_IRQ_DISABLE();
    ਪੋਰਟ_ICCPMR_ਤਰਜੀਹ_ਨਕਾਬ_ਰਜਿਸਟਰ = ( uint32_t ) ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ );
    __asm ਅਸਥਿਰ ( "dsb       \n"
                     "isb       \n" ::: "memory" );
    ਪੋਰਟ_CPU_IRQ_ENABLE();

    /* Increment the RTOS tick. */
    ਜੇ( xTaskIncrementTick() != pdFALSE )
    {
        ul_ਪੋਰਟ_Yield_Required = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ();
    config_CLEAR_TICK_ਰੁਕਾਵਟ();
}
/*-----------------------------------------------------------*/

#ਜੇ ( configUSE_TASK_FPU_SUPPORT == 1 )

    ਖਾਲੀ v_ਪੋਰਟ_Task_ਵਰਤਦਾ_FPU( ਖਾਲੀ )
    {
        uint32_t ulInitialFPSCR = 0;

        /*
         * A task is registering the fact that it needs an FPU context. Set the
         * FPU flag (which is saved as part of the task context).
         */
        ul_ਪੋਰਟ_Task_Has_FPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        __asm ਅਸਥਿਰ ( "FMXR  FPSCR, %0" ::"r" ( ulInitialFPSCR ) : "memory" );
    }

#ਜੇ_ਅੰਤ /* configUSE_TASK_FPU_SUPPORT == 1 */
/*-----------------------------------------------------------*/

ਖਾਲੀ v_ਪੋਰਟ_Clear_ਰੁਕਾਵਟ_ਨਕਾਬ( uint32_t ul_New_ਨਕਾਬ_ਮੁੱਲ )
{
    ਜੇ( ul_New_ਨਕਾਬ_ਮੁੱਲ == pdFALSE )
    {
        ਪੋਰਟ_CLEAR_ਰੁਕਾਵਟ_ਨਕਾਬ();
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_ਪੋਰਟ_ਸੈੱਟ_ਰੁਕਾਵਟ_ਨਕਾਬ( ਖਾਲੀ )
{
    uint32_t ulReturn;

    /* Interrupts must be masked while ICCPMR is updated. */
    ਪੋਰਟ_CPU_IRQ_DISABLE();

    ਜੇ( ਪੋਰਟ_ICCPMR_ਤਰਜੀਹ_ਨਕਾਬ_ਰਜਿਸਟਰ == ( uint32_t ) ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    ਨਹੀਂਤਾਂ
    {
        ulReturn = pdFALSE;
        ਪੋਰਟ_ICCPMR_ਤਰਜੀਹ_ਨਕਾਬ_ਰਜਿਸਟਰ = ( uint32_t ) ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ );
        __asm ਅਸਥਿਰ ( "dsb       \n"
                         "isb       \n" ::: "memory" );
    }

    ਪੋਰਟ_CPU_IRQ_ENABLE();

    ਵਾਪਸ ulReturn;
}
/*-----------------------------------------------------------*/

#ਜੇ ( configASSERT_DEFINED == 1 )

    ਖਾਲੀ v_ਪੋਰਟ_Validate_ਰੁਕਾਵਟ_ਤਰਜੀਹ( ਖਾਲੀ )
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

        configASSERT( ਪੋਰਟ_ICCRPR_RUNNING_ਤਰਜੀਹ_ਰਜਿਸਟਰ >= ( uint32_t ) ( config_MAX_API_CALL_ਰੁਕਾਵਟ_ਤਰਜੀਹ << ਪੋਰਟ_ਤਰਜੀਹ_ਖਿਸਕਾਓ ) );

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
        configASSERT( ( ਪੋਰਟ_ICCBPR_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਰਜਿਸਟਰ & ਪੋਰਟ_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਬਿੱਟ ) <= ਪੋਰਟ_MAX_ਦੁਆਧਾਰੀ_ਬਿੰਦੂ_ਮੁੱਲ );
    }

#ਜੇ_ਅੰਤ /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/
