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
#ضمن <stdlib.h>
#ضمن <string.h>

/* Scheduler includes. */
#ضمن "FreeRTOS.h"
#ضمن "task.h"

#جيڪڏهن_وصف_نه_ٿيل config_مداخلت_CONTROLLER_بنياد_پتو
    #غلطي config_مداخلت_CONTROLLER_بنياد_پتو must be defined.  Refer منزل Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل config_مداخلت_CONTROLLER_CPU_INTERFACE_وٿي
    #غلطي config_مداخلت_CONTROLLER_CPU_INTERFACE_وٿي must be defined.  Refer منزل Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل config_UNIQUE_مداخلت_PRIORITIES
    #غلطي config_UNIQUE_مداخلت_PRIORITIES must be defined.  Refer منزل Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل config_تياري_TICK_مداخلت
    #غلطي config_تياري_TICK_مداخلت() must be defined.  Refer منزل Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#جيڪڏهن_پورو /* configSETUP_TICK_INTERRUPT */

#جيڪڏهن_وصف_نه_ٿيل config_MAX_API_CALL_مداخلت_ترجيح
    #غلطي config_MAX_API_CALL_مداخلت_ترجيح must be defined.  Refer منزل Cortex-A equivalent: http: /*www.FreeRTOS.org/Using-FreeRTOS-on-Cortex-A-Embedded-Processors.html */
#جيڪڏهن_پورو

#إذا config_MAX_API_CALL_مداخلت_ترجيح == 0
    #غلطي config_MAX_API_CALL_مداخلت_ترجيح must not be سيٽ منزل 0
#جيڪڏهن_پورو

#إذا config_MAX_API_CALL_مداخلت_ترجيح > config_UNIQUE_مداخلت_PRIORITIES
    #غلطي config_MAX_API_CALL_مداخلت_ترجيح must be less than or equal منزل config_UNIQUE_مداخلت_PRIORITIES as the هيٺاهون the numeric ترجيح قدر the higher the logical مداخلت ترجيح
#جيڪڏهن_پورو

#إذا config_USE_پورٽ_OPTIMISED_TASK_SELECTION == 1
    /* Check the configuration. */
    #إذا ( configMAX_PRIORITIES > 32 )
        #غلطي config_USE_پورٽ_OPTIMISED_TASK_SELECTION can only be سيٽ منزل 1 when configMAX_PRIORITIES is less than or equal منزل 32.  It is very rare that a system requires وڌيڪ than 10 منزل 15 difference priorities as tasks that share a ترجيح will time ٽڪرو.
    #جيڪڏهن_پورو
#جيڪڏهن_پورو /* configUSE_PORT_OPTIMISED_TASK_SELECTION */

/* In case security extensions are implemented. */
#إذا config_MAX_API_CALL_مداخلت_ترجيح <= ( config_UNIQUE_مداخلت_PRIORITIES / 2 )
    #غلطي config_MAX_API_CALL_مداخلت_ترجيح must be greater than ( config_UNIQUE_مداخلت_PRIORITIES / 2 )
#جيڪڏهن_پورو

/*
 * __ARM_FP is defined by the c preprocessor when FPU support is enabled,
 * usually with the -mfpu= argument and -mfloat-abi=.
 *
 * Note: Some implementations of the c standard library may use FPU registers
 *       for generic memory operations (memcpy, etc).
 *       When setting configUSE_TASK_FPU_SUPPORT == 1, care must be taken to
 *       ensure that the FPU registers are not used without an FPU context.
 */
#إذا ( configUSE_TASK_FPU_SUPPORT == 0 )
    #جيڪڏهن_وصف_ٿيل __ARM_FP
        #غلطي __ARM_FP is defined, so configUSE_TASK_FPU_SUPPORT must be سيٽ منزل either منزل 1 or 2.
    #جيڪڏهن_پورو /* __ARM_FP */
#وإلاإذا ( configUSE_TASK_FPU_SUPPORT == 1 ) || ( configUSE_TASK_FPU_SUPPORT == 2 )
    #جيڪڏهن_وصف_نه_ٿيل __ARM_FP
        #غلطي __ARM_FP is not defined, so configUSE_TASK_FPU_SUPPORT must be سيٽ منزل 0.
    #جيڪڏهن_پورو /* __ARM_FP */
#جيڪڏهن_پورو /* configUSE_TASK_FPU_SUPPORT */

/*
 * Some vendor specific files default configCLEAR_TICK_INTERRUPT() in
 * portmacro.h.
 */
#جيڪڏهن_وصف_نه_ٿيل config_CLEAR_TICK_مداخلت
    #وصف_ڪريو config_CLEAR_TICK_مداخلت()
#جيڪڏهن_پورو

/*
 * A critical section is exited when the critical section nesting count reaches
 * this value.
 */
#وصف_ڪريو پورٽ_NO_CRITICAL_NESTING          ( ( uint32_t ) 0 )

/*
 * In all GICs 255 can be written to the priority mask register to unmask all
 * (but the lowest) interrupt priority.
 */
#وصف_ڪريو پورٽ_UNMASK_قدر                 ( 0xFFUL )

/*
 * Tasks are not created with a floating point context, but can be given a
 * floating point context after they have been created.  A variable is stored as
 * part of the tasks context that holds portNO_FLOATING_POINT_CONTEXT if the task
 * does not have an FPU context, or any other value if the task does have an FPU
 * context.
 */
#وصف_ڪريو پورٽ_NO_FLOATING_نقطو_CONTEXT    ( ( ڍير_Type_t ) 0 )

/* Constants required to setup the initial task context. */
#وصف_ڪريو پورٽ_INITIAL_SPSR                 ( ( ڍير_Type_t ) 0x1f ) /* System mode, ARM mode, IRQ enabled FIQ enabled. */
#وصف_ڪريو پورٽ_THUMB_گهڻائي_ٻٽو_انگ               ( ( ڍير_Type_t ) 0x20 )
#وصف_ڪريو پورٽ_مداخلت_ENABLE_ٻٽو_انگ         ( 0x80UL )
#وصف_ڪريو پورٽ_THUMB_گهڻائي_پتو           ( 0x01UL )

/*
 * Used by portASSERT_IF_INTERRUPT_PRIORITY_INVALID() when ensuring the binary
 * point is zero.
 */
#وصف_ڪريو پورٽ_ٻٽو_نقطو_بٽ            ( ( uint8_t ) 0x03 )

/* Masks all bits in the APSR other than the mode bits. */
#وصف_ڪريو پورٽ_APSR_گهڻائي_بٽ_نقاب          ( 0x1F )

/* The value of the mode bits in the APSR when the CPU is executing in user
 * mode. */
#وصف_ڪريو پورٽ_APSR_USER_گهڻائي               ( 0x10 )

/* The critical section macros only mask interrupts up to an application
 * determined priority level.  Sometimes it is necessary to turn interrupt off in
 * the CPU itself before modifying certain hardware registers. */
#وصف_ڪريو پورٽ_CPU_IRQ_DISABLE()                  \
    __asm متطاير ( "CPSID i" ::: "memory" ); \
    __asm متطاير ( "DSB" );                  \
    __asm متطاير ( "ISB" );

#وصف_ڪريو پورٽ_CPU_IRQ_ENABLE()                   \
    __asm متطاير ( "CPSIE i" ::: "memory" ); \
    __asm متطاير ( "DSB" );                  \
    __asm متطاير ( "ISB" );


/* Macro to unmask all interrupt priorities. */
#وصف_ڪريو پورٽ_CLEAR_مداخلت_نقاب()                            \
    {                                                         \
        پورٽ_CPU_IRQ_DISABLE();                                \
        پورٽ_ICCPMR_ترجيح_نقاب_رجسٽر = پورٽ_UNMASK_قدر; \
        __asm متطاير ( "DSB       \n"                       \
                         "ISB       \n" );                    \
        پورٽ_CPU_IRQ_ENABLE();                                 \
    }

#وصف_ڪريو پورٽ_مداخلت_ترجيح_رجسٽر_وٿي    0x400UL
#وصف_ڪريو پورٽ_MAX_8_ٻٽو_انگ_قدر                       ( ( uint8_t ) 0xff )
#وصف_ڪريو پورٽ_ٻٽو_انگ_0_سيٽ                             ( ( uint8_t ) 0x01 )

/*
 * Let the user override the pre-loading of the initial LR with the address of
 * prvTaskExitError() in case is messes up unwinding of the stack in the
 * debugger.
 */
#جيڪڏهن_وصف_ٿيل config_TASK_RETURN_پتو
    #وصف_ڪريو پورٽ_TASK_RETURN_پتو    config_TASK_RETURN_پتو
#وإلا
    #وصف_ڪريو پورٽ_TASK_RETURN_پتو    prvTaskExitError
#جيڪڏهن_پورو

#إذا ( configUSE_TASK_FPU_SUPPORT != 0 )

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
    #وصف_ڪريو پورٽ_FPU_رجسٽر_لفظ    ( ( 16 * 2 ) + 1 )
#جيڪڏهن_پورو /* configUSE_TASK_FPU_SUPPORT != 0 */

/*-----------------------------------------------------------*/

/*
 * Starts the first task executing.  This function is necessarily written in
 * assembly code so is implemented in portASM.s.
 */
خارجي فراغ v_پورٽ_Restore_Task_Context( فراغ );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
ساكن فراغ prvTaskExitError( فراغ );

#إذا ( configUSE_TASK_FPU_SUPPORT != 0 )

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
    فراغ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR ) __attribute__( ( weak ) );
#جيڪڏهن_پورو /* configUSE_TASK_FPU_SUPPORT != 0 */

/*-----------------------------------------------------------*/

/*
 * A variable is used to keep track of the critical section nesting.  This
 * variable has to be stored as part of the task context and must be initialised to
 * a non zero value to ensure interrupts don't inadvertently become unmasked before
 * the scheduler starts.  As it is stored as part of the task context it will
 * automatically be set to 0 when the first task is started.
 */
متطاير uint32_t ulCriticalNesting = 9999UL;

#إذا ( configUSE_TASK_FPU_SUPPORT != 0 )

/*
 * Saved as part of the task context.  If ulPortTaskHasFPUContext is non-zero then
 * a floating point context must be saved and restored for the task.
 */
    uint32_t ul_پورٽ_Task_Has_FPUContext = pdFALSE;
#جيڪڏهن_پورو /* configUSE_TASK_FPU_SUPPORT != 0 */

/* Set to 1 to pend a context switch from an ISR. */
uint32_t ul_پورٽ_Yield_Required = pdFALSE;

/*
 * Counts the interrupt nesting depth.  A context switch is only performed if
 * if the nesting depth is 0.
 */
uint32_t ul_پورٽ_مداخلت_Nesting = 0UL;

/* Used in asm code. */
__attribute__( ( استعمال_ٿيل ) ) ثابت uint32_t ulICCIAR = پورٽ_ICCIAR_مداخلت_ACKNOWLEDGE_رجسٽر_پتو;
__attribute__( ( استعمال_ٿيل ) ) ثابت uint32_t ulICCEOIR = پورٽ_ICCEOIR_پڇاڙي_جو_مداخلت_رجسٽر_پتو;
__attribute__( ( استعمال_ٿيل ) ) ثابت uint32_t ulICCPMR = پورٽ_ICCPMR_ترجيح_نقاب_رجسٽر_پتو;
__attribute__( ( استعمال_ٿيل ) ) ثابت uint32_t ul_Max_APIPriority_نقاب = ( config_MAX_API_CALL_مداخلت_ترجيح << پورٽ_ترجيح_سرڪايو );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
ڍير_Type_t * px_پورٽ_Initialise_ڍير( ڍير_Type_t * px_چوٽي_جو_ڍير,
                                     TaskFunction_t px_ڪوڊ,
                                     فراغ * pvParameters )
{
    /*
     * Setup the initial stack of the task.  The stack is set exactly as
     * expected by the portRESTORE_CONTEXT() macro.
     *
     * The fist real value on the stack is the status register, which is set for
     * system mode, with interrupts enabled.  A few NULLs are added first to ensure
     * GDB does not try decoding a non-existent return address.
     */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) عدم;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) عدم;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) عدم;
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_INITIAL_SPSR;

    إذا( ( ( uint32_t ) px_ڪوڊ & پورٽ_THUMB_گهڻائي_پتو ) != 0x00UL )
    {
        /* The task will start in THUMB mode. */
        *px_چوٽي_جو_ڍير |= پورٽ_THUMB_گهڻائي_ٻٽو_انگ;
    }

    px_چوٽي_جو_ڍير--;

    /* Next the return address, which in this case is the start of the task. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) px_ڪوڊ;
    px_چوٽي_جو_ڍير--;

    /* Next all the registers other than the stack pointer. */
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) پورٽ_TASK_RETURN_پتو; /* R14 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x12121212;              /* R12 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x11111111;              /* R11 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x10101010;              /* R10 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x09090909;              /* R9 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x08080808;              /* R8 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x07070707;              /* R7 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x06060606;              /* R6 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x05050505;              /* R5 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x04040404;              /* R4 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x03030303;              /* R3 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x02020202;              /* R2 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) 0x01010101;              /* R1 */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = ( ڍير_Type_t ) pvParameters;            /* R0 */

    /*
     * The task will start with a critical nesting count of 0 as interrupts are
     * enabled.
     */
    px_چوٽي_جو_ڍير--;
    *px_چوٽي_جو_ڍير = پورٽ_NO_CRITICAL_NESTING;

    #إذا ( configUSE_TASK_FPU_SUPPORT == 1 )
    {
        /*
         * The task will start without a floating point context.
         * A task that uses the floating point hardware must call
         * vPortTaskUsesFPU() before executing any floating point
         * instructions.
         */
        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = پورٽ_NO_FLOATING_نقطو_CONTEXT;
    }
    #وإلاإذا ( configUSE_TASK_FPU_SUPPORT == 2 )
    {
        /*
         * The task will start with a floating point context. Leave enough
         * space for the registers and ensure they are initialized to 0.
         */
        px_چوٽي_جو_ڍير -= پورٽ_FPU_رجسٽر_لفظ;
        memset( px_چوٽي_جو_ڍير, 0x00, پورٽ_FPU_رجسٽر_لفظ * حجم( ڍير_Type_t ) );

        px_چوٽي_جو_ڍير--;
        *px_چوٽي_جو_ڍير = pdTRUE;
        ul_پورٽ_Task_Has_FPUContext = pdTRUE;
    }
    #وإلاإذا ( configUSE_TASK_FPU_SUPPORT != 0 )
    {
        #غلطي Invalid configUSE_TASK_FPU_SUPPORT setting - configUSE_TASK_FPU_SUPPORT must be سيٽ منزل 0, 1, or 2.
    }
    #جيڪڏهن_پورو /* configUSE_TASK_FPU_SUPPORT */

    أرجع px_چوٽي_جو_ڍير;
}
/*-----------------------------------------------------------*/

ساكن فراغ prvTaskExitError( فراغ )
{
    /*
     * A function that implements a task must not exit or attempt to return to
     * its caller as there is nothing to return to.  If a task wants to exit it
     * should instead call vTaskDelete( NULL ).
     *
     * Artificially force an assert() to be triggered if configASSERT() is
     * defined, then stop here so application writers can catch the error.
     */
    configASSERT( ul_پورٽ_مداخلت_Nesting == ~0UL );
    پورٽ_DISABLE_INTERRUPTS();

    لكل( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_FPU_SUPPORT != 0 )

    فراغ vApplicationFPUSafeIRQHandler( uint32_t ulICCIAR ) /* __attribute__( ( weak ) ) */
    {
        ( فراغ ) ulICCIAR;
        configASSERT( ( متطاير فراغ * ) عدم );
    }

#جيڪڏهن_پورو /* configUSE_TASK_FPU_SUPPORT != 0 */
/*-----------------------------------------------------------*/

بنياد_Type_t x_پورٽ_شروعات_Scheduler( فراغ )
{
    uint32_t ulAPSR, ul_چڪرن = 8; /* 8 bits per byte. */

    #إذا ( configASSERT_DEFINED == 1 )
    {
        متطاير uint8_t uc_Original_ترجيح;
        متطاير uint8_t * ثابت puc_پهريون_User_ترجيح_رجسٽر = ( متطاير uint8_t * ثابت ) ( config_مداخلت_CONTROLLER_بنياد_پتو + پورٽ_مداخلت_ترجيح_رجسٽر_وٿي );
        متطاير uint8_t uc_Max_ترجيح_قدر;

        /*
         * Determine how many priority bits are implemented in the GIC.
         * Save the interrupt priority value that is about to be clobbered.
         */
        uc_Original_ترجيح = *puc_پهريون_User_ترجيح_رجسٽر;

        /*
         * Determine the number of priority bits available.  First write to
         * all possible bits.
         */
        *puc_پهريون_User_ترجيح_رجسٽر = پورٽ_MAX_8_ٻٽو_انگ_قدر;

        /* Read the value back to see how many bits stuck. */
        uc_Max_ترجيح_قدر = *puc_پهريون_User_ترجيح_رجسٽر;

        /* Shift to the least significant bits. */
        طالما( ( uc_Max_ترجيح_قدر & پورٽ_ٻٽو_انگ_0_سيٽ ) != پورٽ_ٻٽو_انگ_0_سيٽ )
        {
            uc_Max_ترجيح_قدر >>= ( uint8_t ) 0x01;

            /*
             * If ulCycles reaches 0 then ucMaxPriorityValue must have been
             * read as 0, indicating a misconfiguration.
             */
            ul_چڪرن--;

            إذا( ul_چڪرن == 0 )
            {
                اكسر;
            }
        }

        /*
         * Sanity check configUNIQUE_INTERRUPT_PRIORITIES matches the read
         * value.
         */
        configASSERT( uc_Max_ترجيح_قدر == پورٽ_سڀ_کان_هيٺ_مداخلت_ترجيح );

        /*
         * Restore the clobbered interrupt priority register to its original
         * value.
         */
        *puc_پهريون_User_ترجيح_رجسٽر = uc_Original_ترجيح;
    }
    #جيڪڏهن_پورو /* configASSERT_DEFINED */

    /*
     * Only continue if the CPU is not in User mode.  The CPU must be in a
     * Privileged mode for the scheduler to start.
     */
    __asm متطاير ( "MRS %0, APSR" : "=r" ( ulAPSR )::"memory" );
    ulAPSR &= پورٽ_APSR_گهڻائي_بٽ_نقاب;
    configASSERT( ulAPSR != پورٽ_APSR_USER_گهڻائي );

    إذا( ulAPSR != پورٽ_APSR_USER_گهڻائي )
    {
        /*
         * Only continue if the binary point value is set to its lowest possible
         * setting.  See the comments in vPortValidateInterruptPriority() below for
         * more information.
         */
        configASSERT( ( پورٽ_ICCBPR_ٻٽو_نقطو_رجسٽر & پورٽ_ٻٽو_نقطو_بٽ ) <= پورٽ_MAX_ٻٽو_نقطو_قدر );

        إذا( ( پورٽ_ICCBPR_ٻٽو_نقطو_رجسٽر & پورٽ_ٻٽو_نقطو_بٽ ) <= پورٽ_MAX_ٻٽو_نقطو_قدر )
        {
            /*
             * Interrupts are turned off in the CPU itself to ensure tick does
             * not execute  while the scheduler is being started.  Interrupts are
             * automatically turned back on in the CPU when the first task starts
             * executing.
             */
            پورٽ_CPU_IRQ_DISABLE();

            /* Start the timer that generates the tick ISR. */
            config_تياري_TICK_مداخلت();

            /* Start the first task executing. */
            v_پورٽ_Restore_Task_Context();
        }
    }

    /*
     * Will only get here if vTaskStartScheduler() was called with the CPU in
     * a non-privileged mode or the binary point register was not set to its lowest
     * possible value.  prvTaskExitError() is referenced to prevent a compiler
     * warning about it being defined but not referenced in the case that the user
     * defines their own exit address.
     */
    ( فراغ ) prvTaskExitError;

    أرجع 0;
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_پڇاڙي_Scheduler( فراغ )
{
    /*
     * Not implemented in ports where there is nothing to return to.
     * Artificially force an assert.
     */
    configASSERT( ulCriticalNesting == 1000UL );
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Enter_Critical( فراغ )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    ul_پورٽ_سيٽ_مداخلت_نقاب();

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
    إذا( ulCriticalNesting == 1 )
    {
        configASSERT( ul_پورٽ_مداخلت_Nesting == 0 );
    }
}
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Exit_Critical( فراغ )
{
    إذا( ulCriticalNesting > پورٽ_NO_CRITICAL_NESTING )
    {
        /* Decrement the nesting count as the critical section is being exited. */
        ulCriticalNesting--;

        /*
         * If the nesting level has reached zero then all interrupt
         * priorities must be re-enabled.
         */
        إذا( ulCriticalNesting == پورٽ_NO_CRITICAL_NESTING )
        {
            /*
             * Critical nesting has reached zero so all interrupt priorities
             * should be unmasked.
             */
            پورٽ_CLEAR_مداخلت_نقاب();
        }
    }
}
/*-----------------------------------------------------------*/

فراغ FreeRTOS_Tick_Handler( فراغ )
{
    /*
     * Set interrupt mask before altering scheduler structures.   The tick
     * handler runs at the lowest priority, so interrupts cannot already be masked,
     * so there is no need to save and restore the current mask value.  It is
     * necessary to turn off interrupts in the CPU itself while the ICCPMR is being
     * updated.
     */
    پورٽ_CPU_IRQ_DISABLE();
    پورٽ_ICCPMR_ترجيح_نقاب_رجسٽر = ( uint32_t ) ( config_MAX_API_CALL_مداخلت_ترجيح << پورٽ_ترجيح_سرڪايو );
    __asm متطاير ( "dsb       \n"
                     "isb       \n" ::: "memory" );
    پورٽ_CPU_IRQ_ENABLE();

    /* Increment the RTOS tick. */
    إذا( xTaskIncrementTick() != pdFALSE )
    {
        ul_پورٽ_Yield_Required = pdTRUE;
    }

    /* Ensure all interrupt priorities are active again. */
    پورٽ_CLEAR_مداخلت_نقاب();
    config_CLEAR_TICK_مداخلت();
}
/*-----------------------------------------------------------*/

#إذا ( configUSE_TASK_FPU_SUPPORT == 1 )

    فراغ v_پورٽ_Task_استعمال_ڪري_FPU( فراغ )
    {
        uint32_t ulInitialFPSCR = 0;

        /*
         * A task is registering the fact that it needs an FPU context. Set the
         * FPU flag (which is saved as part of the task context).
         */
        ul_پورٽ_Task_Has_FPUContext = pdTRUE;

        /* Initialise the floating point status register. */
        __asm متطاير ( "FMXR  FPSCR, %0" ::"r" ( ulInitialFPSCR ) : "memory" );
    }

#جيڪڏهن_پورو /* configUSE_TASK_FPU_SUPPORT == 1 */
/*-----------------------------------------------------------*/

فراغ v_پورٽ_Clear_مداخلت_نقاب( uint32_t ul_New_نقاب_قدر )
{
    إذا( ul_New_نقاب_قدر == pdFALSE )
    {
        پورٽ_CLEAR_مداخلت_نقاب();
    }
}
/*-----------------------------------------------------------*/

uint32_t ul_پورٽ_سيٽ_مداخلت_نقاب( فراغ )
{
    uint32_t ulReturn;

    /* Interrupts must be masked while ICCPMR is updated. */
    پورٽ_CPU_IRQ_DISABLE();

    إذا( پورٽ_ICCPMR_ترجيح_نقاب_رجسٽر == ( uint32_t ) ( config_MAX_API_CALL_مداخلت_ترجيح << پورٽ_ترجيح_سرڪايو ) )
    {
        /* Interrupts were already masked. */
        ulReturn = pdTRUE;
    }
    وإلا
    {
        ulReturn = pdFALSE;
        پورٽ_ICCPMR_ترجيح_نقاب_رجسٽر = ( uint32_t ) ( config_MAX_API_CALL_مداخلت_ترجيح << پورٽ_ترجيح_سرڪايو );
        __asm متطاير ( "dsb       \n"
                         "isb       \n" ::: "memory" );
    }

    پورٽ_CPU_IRQ_ENABLE();

    أرجع ulReturn;
}
/*-----------------------------------------------------------*/

#إذا ( configASSERT_DEFINED == 1 )

    فراغ v_پورٽ_Validate_مداخلت_ترجيح( فراغ )
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

        configASSERT( پورٽ_ICCRPR_RUNNING_ترجيح_رجسٽر >= ( uint32_t ) ( config_MAX_API_CALL_مداخلت_ترجيح << پورٽ_ترجيح_سرڪايو ) );

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
        configASSERT( ( پورٽ_ICCBPR_ٻٽو_نقطو_رجسٽر & پورٽ_ٻٽو_نقطو_بٽ ) <= پورٽ_MAX_ٻٽو_نقطو_قدر );
    }

#جيڪڏهن_پورو /* configASSERT_DEFINED */
/*-----------------------------------------------------------*/
